/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Vamp

    An API for audio analysis and feature extraction plugins.

    Centre for Digital Music, Queen Mary, University of London.
    Copyright 2006 Chris Cannam.

    VAMP license:

        Permission is hereby granted, free of charge, to any person
        obtaining a copy of this software and associated documentation
        files (the "Software"), to deal in the Software without
        restriction, including without limitation the rights to use, copy,
        modify, merge, publish, distribute, sublicense, and/or sell copies
        of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:
    
        The above copyright notice and this permission notice shall be
        included in all copies or substantial portions of the Software.
    
        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
        EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
        MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
        NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
        ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
        CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
        WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
        Except as contained in this notice, the names of the Centre for
        Digital Music; Queen Mary, University of London; and Chris Cannam
        shall not be used in advertising or otherwise to promote the sale,
        use or other dealings in this Software without prior written
        authorization.
    
    FindPulseFDBatch.cpp - find pulses from Lotek tags - frequency domain
    (just like FindPulseFD.cpp except output suitable for vamp-rt-host)
    Copyright 2012 John Brzustowski

    License: GPL v 2.0 or later.  This is required in order to use fftw.

*/

#include "FindPulseFDBatch.h"

using std::stringstream;
using std::string;
using std::vector;
using std::cerr;
using std::endl;

const char * FindPulseFDBatch::fftw_wisdom_filename = "./fftw_wisdom.dat";

// slightly modified from Audacity 2.0.1's src/FreqWindow.cpp:

float
FindPulseFDBatch::CubicMaximize(float y0, float y1, float y2, float y3)
{
   // Find coefficients of cubic

   float a, b, c;

   a = y0 / -6.0 + y1 / 2.0 - y2 / 2.0 + y3 / 6.0;
   b = y0 - 5.0 * y1 / 2.0 + 2.0 * y2 - y3 / 2.0;
   c = -11.0 * y0 / 6.0 + 3.0 * y1 - 3.0 * y2 / 2.0 + y3 / 3.0;

   // Take derivative

   float da, db, dc;

   da = 3 * a;
   db = 2 * b;
   dc = c;

   // Find zeroes of derivative using quadratic equation

   float discriminant = db * db - 4 * da * dc;
   if (discriminant < 0.0)
      return float(-1.0);              // error

   float x1 = (-db + sqrt(discriminant)) / (2 * da);
   float x2 = (-db - sqrt(discriminant)) / (2 * da);

   // The one which corresponds to a local _maximum_ in the
   // cubic is the one we want - the one with a negative
   // second derivative

   float dda = 2 * da;
   float ddb = db;

   if (dda * x1 + ddb < 0)
   {
      return x1;
   }
   else
   {
      return x2;
   }
}

FindPulseFDBatch::FindPulseFDBatch(float inputSampleRate) :
    Plugin(inputSampleRate),
    m_stepSize(0),
    m_blockSize(0),
    m_plen(m_default_plen),
    m_min_pulse_SNR_dB (m_default_min_pulse_SNR_dB),
    m_fft_win_size (m_default_fft_win_size),
    m_noise_win_size (m_default_noise_win_size),
    m_min_pulse_sep (m_default_min_pulse_sep),
    m_min_freq (m_default_min_freq),
    m_max_freq (m_default_max_freq),
    m_have_fft_plan(false)
{
    // silently fail if wisdom cannot be found
    (void) fftwf_import_wisdom_from_filename(fftw_wisdom_filename);
}

FindPulseFDBatch::~FindPulseFDBatch()
{
    if (m_have_fft_plan) {
        for (int i=0; i < 4; ++i) {
            fftwf_destroy_plan(m_plan[i]);
            fftw_free(m_windowed[i]); 
        }
        fftw_free(m_fft[0]);
        fftw_free(m_fft[1]);
        m_have_fft_plan = false;
    }
    // silently fail if we can't export wisdom
    (void) fftwf_export_wisdom_to_filename(fftw_wisdom_filename);
}

string
FindPulseFDBatch::getIdentifier() const
{
    return "findpulsefdbatch";
}

string
FindPulseFDBatch::getName() const
{
    return "Find Pulses in Frequency Domain (Batch)";
}

string
FindPulseFDBatch::getDescription() const
{
    return "Find pulses (e.g. from Lotek telemetry tags)";
}

string
FindPulseFDBatch::getMaker() const
{
    return "flightcalls.org jbrzusto@fastmail.fm";
}

int
FindPulseFDBatch::getPluginVersion() const
{
    return 1;
}

string
FindPulseFDBatch::getCopyright() const
{
    return "GPL version 2 or later";
}

bool
FindPulseFDBatch::initialise(size_t channels, size_t stepSize, size_t blockSize)
{
    if (channels < getMinChannelCount() ||
	channels > getMaxChannelCount()) return false;

    m_channels = channels;
    m_stepSize = stepSize;
    m_blockSize = blockSize;

    m_plen_in_samples = (m_plen / 1000.0) * m_inputSampleRate;

    m_pf_size = roundf(m_plen_in_samples / (m_fft_win_size / 2));

    int num_bins = m_fft_win_size / 2 + 1;

    m_freq_bin_pulse_finder = std::vector < PulseFinder < float > > (num_bins, PulseFinder < float > (m_pf_size, m_pf_size * m_noise_win_size, m_pf_size * m_min_pulse_sep));

    // allocate time-domain sample buffers for each channel which are large enough to contain
    // the samples for a pulse when it has been detected.  Because pulses are not
    // detected until the sliding window determines them to be maximal in the
    // frequency domain, we need to keep a rather long window.

    int buf_size = m_fft_win_size * ((1 + m_noise_win_size + m_min_pulse_sep) * m_pf_size) / 2.0; // takes us back to centre of pulse from current sample
    buf_size += m_plen_in_samples / 2.0; // takes us back a further half pulse width to the start of the pulse

    for (int i=0; i < 2; ++i) 
        m_sample_buf[i] = boost::circular_buffer < float > (round(buf_size));

    // allocate windowed sample buffers, fft output buffers and plans
    // for finer dfreq estimates based on pulse samples

    for (int i=0; i < 2; ++i) {
        m_windowed_fine[i] = (float *) fftwf_malloc(m_plen_in_samples * sizeof(float));
        m_fft_fine[i] = (fftwf_complex *) fftwf_malloc((m_plen_in_samples / 2 + 1) * sizeof(fftwf_complex));
        m_plan_fine[i] = fftwf_plan_dft_r2c_1d(m_plen_in_samples, m_windowed_fine[i], m_fft_fine[i], FFTW_PATIENT);
    }

    // allocate fft output buffers for pulse finding
    for (int i=0; i < 2; ++i)
        m_fft[i] = (fftwf_complex *) fftwf_malloc((m_fft_win_size / 2 + 1) * sizeof(fftwf_complex) );

    // allocate two input windows for each channel; for each channel, both phase windows use the same output array
    for (unsigned i=0; i < 2 * m_channels; ++i) {
        m_windowed[i] = (float *) fftwf_malloc(m_fft_win_size * sizeof(float));
        m_plan[i] = fftwf_plan_dft_r2c_1d(m_fft_win_size, m_windowed[i], m_fft[i / 2], FFTW_PATIENT);
    }

    // cap frequency limits at Nyquist
    if (m_min_freq > m_inputSampleRate / 2000)
        m_min_freq = m_inputSampleRate / 2000;
    if (m_max_freq > m_inputSampleRate / 2000)
        m_max_freq = m_inputSampleRate / 2000;
    
    m_first_freq_bin = floorf(m_min_freq * 1000.0 / (m_inputSampleRate / m_fft_win_size) + 0.5);
    m_last_freq_bin =  floorf(m_max_freq * 1000.0 / (m_inputSampleRate / m_fft_win_size) - 0.5);
    if (m_last_freq_bin < m_first_freq_bin)
        m_last_freq_bin = m_first_freq_bin;

    m_num_windowed_samples[0] = 0;

    // ugly hack to simplify accumulation in odd-phase sliding window
    m_num_windowed_samples[1] = m_fft_win_size / 2;

    // calculate coefficients for window function
    m_window = std::vector < float > (m_fft_win_size);

    // use Hamming window
    m_win_s1 = m_win_s2 = 0.0;
    for (int i=0; i < m_fft_win_size; ++i) {
        m_window[i] = 0.54 - 0.46 * cos (2 * M_PI * i / m_fft_win_size);
        m_win_s1 += m_window[i];
        m_win_s2 += m_window[i] * m_window[i];
    }

    m_probe_scale = m_channels * (m_win_s1 * m_win_s1 / 2);
    m_min_pulse_SNR = exp10(m_min_pulse_SNR_dB / 10.0);

    m_dcma[0] = MovingAverager < float, float > (5 * m_fft_win_size);
    if (m_channels == 2)
        m_dcma[1] = MovingAverager < float, float > (5 * m_fft_win_size);

    m_odd_phase_window_is_bogus = true;

    return true;
}

void
FindPulseFDBatch::reset()
{
}

FindPulseFDBatch::ParameterList
FindPulseFDBatch::getParameterDescriptors() const
{
    ParameterList list;

    ParameterDescriptor d;
    d.identifier = "plen";
    d.name = "Pulse Length (unit: milliseconds)";
    d.description = "Duration of a transmitted pulse in milliseconds";
    d.unit = "milliseconds";
    d.minValue = 0.1;
    d.maxValue = 50;
    d.defaultValue = FindPulseFDBatch::m_default_plen;
    d.isQuantized = false;
    list.push_back(d);

    d.identifier = "minsnr";
    d.name = "Minimum Pulse SNR (unit: dB)";
    d.description = "Minimum pulse signal-to-noise ratio";
    d.unit = "dB";
    d.minValue = 0;
    d.maxValue = 96;
    d.defaultValue = FindPulseFDBatch::m_default_min_pulse_SNR_dB;
    d.isQuantized = false;
    list.push_back(d);

    d.identifier = "fftsize";
    d.name = "Size of FFT window (unit: samples)";
    d.description = "The number of samples in each window for which an FFT is computed.  Windows are non-overlapping.  A window of 96 samples for 96kHz sampling means one FFT calculated each millisecond";
    d.unit = "samples";
    d.minValue = 10;
    d.maxValue = 1000;
    d.defaultValue = FindPulseFDBatch::m_default_fft_win_size;
    d.isQuantized = true;
    d.quantizeStep = 1;
    list.push_back(d);

    d.identifier = "noisesize";
    d.name = "Size of noise window (unit: pulse length)";
    d.description = "Size of window on each side of signal that is used to estimate noise.  In multiples of signal pulse length.";
    d.unit = "pulses";
    d.minValue = 1;
    d.maxValue = 100;
    d.defaultValue = FindPulseFDBatch::m_default_noise_win_size;
    d.isQuantized = true;
    d.quantizeStep = 1;
    list.push_back(d);

    d.identifier = "pulsesep";
    d.name = "Minimum separation of pulses (unit: pulse length)";
    d.description = "Minimum separation between a pulse and adjacent pulses in order to be detected, in units of pulse length.";
    d.unit = "pulses";
    d.minValue = 1;
    d.maxValue = 100;
    d.defaultValue = FindPulseFDBatch::m_default_min_pulse_sep;
    d.isQuantized = true;
    d.quantizeStep = 1;
    list.push_back(d);

    d.identifier = "minfreq";
    d.name = "Minimum Tag Offset Frequency (unit: kHz)";
    d.description = "Minimum frequency by which tag differs from receiver, in kHz";
    d.unit = "kHz";
    d.minValue = 0;
    d.maxValue = m_inputSampleRate / 2000;
    d.defaultValue = FindPulseFDBatch::m_default_min_freq;
    d.isQuantized = false;
    list.push_back(d);

    d.identifier = "maxfreq";
    d.name = "Maximum Tag Offset Frequency (unit: kHz)";
    d.description = "Maximum frequency by which tag differs from receiver, in kHz";
    d.unit = "kHz";
    d.minValue = 0;
    d.maxValue = m_inputSampleRate / 2000;
    d.defaultValue = FindPulseFDBatch::m_default_max_freq;
    d.isQuantized = false;
    list.push_back(d);

    return list;
}

float
FindPulseFDBatch::getParameter(string id) const
{
    if (id == "plen") {
        return m_plen;
    } else if (id == "minsnr") {
        return m_min_pulse_SNR_dB;
    } else if (id == "fftsize") {
        return m_fft_win_size;
    } else if (id == "noisesize") {
        return m_noise_win_size;
    } else if (id == "pulsesep") {
        return m_min_pulse_sep;
    } else if (id == "minfreq") {
        return m_min_freq;
    } else if (id == "maxfreq") {
        return m_max_freq;
    }
    return 0.f;
}

void
FindPulseFDBatch::setParameter(string id, float value)
{
    if (id == "plen") {
        FindPulseFDBatch::m_default_plen = m_plen = value;
    } else if (id == "minsnr") {
        FindPulseFDBatch::m_default_min_pulse_SNR_dB = m_min_pulse_SNR_dB = value;
    } else if (id == "fftsize") {
        FindPulseFDBatch::m_default_fft_win_size = m_fft_win_size = value;
    } else if (id == "noisesize") {
        FindPulseFDBatch::m_default_noise_win_size = m_noise_win_size = value;
    } else if (id == "pulsesep") {
        FindPulseFDBatch::m_default_min_pulse_sep = m_min_pulse_sep = value;
    } else if (id == "minfreq") {
        FindPulseFDBatch::m_default_min_freq = m_min_freq = value;
    } else if (id == "maxfreq") {
        FindPulseFDBatch::m_default_max_freq = m_max_freq = value;
    }
}


FindPulseFDBatch::OutputList
FindPulseFDBatch::getOutputDescriptors() const
{
    OutputList list;

    OutputDescriptor zc;

    zc.identifier = "pulses";
    zc.name = "Pulses";
    zc.description = "The locations and features of pulses";
    zc.unit = "";
    zc.hasFixedBinCount = true;
    zc.binCount = 3;
    zc.sampleType = OutputDescriptor::VariableSampleRate;
    zc.sampleRate = m_inputSampleRate;
    list.push_back(zc);

    return list;
}

FindPulseFDBatch::FeatureSet
FindPulseFDBatch::process(const float *const *inputBuffers,
                      Vamp::RealTime timestamp)
{
    FeatureSet returnFeatures;

    if (m_stepSize == 0) {
	cerr << "ERROR: FindPulseFDBatch::process: "
	     << "FindPulseFDBatch has not been initialised"
	     << endl;
	return returnFeatures;
    }

    for (unsigned int i=0; i < m_blockSize; ++i) {
        m_dcma[0].process(inputBuffers[0][i]);
        m_sample_buf[0].push_back(inputBuffers[0][i]);

        if (m_channels == 2) {
            m_dcma[1].process(inputBuffers[1][i]);
            m_sample_buf[1].push_back(inputBuffers[1][i]);
        }

        if (! m_dcma[0].have_average())
            continue;

        // append each weighted sample to each window
        float avg = m_dcma[0].get_average();
        m_windowed[0][m_num_windowed_samples[0]] = (inputBuffers[0][i] - avg) * m_window[m_num_windowed_samples[0]];
        m_windowed[1][m_num_windowed_samples[1]] = (inputBuffers[0][i] - avg) * m_window[m_num_windowed_samples[1]];
        if (m_channels == 2) {
            avg = m_dcma[1].get_average();
            m_windowed[0 + 2][m_num_windowed_samples[0]] = (inputBuffers[1][i] - avg) * m_window[m_num_windowed_samples[0]];
            m_windowed[1 + 2][m_num_windowed_samples[1]] = (inputBuffers[1][i] - avg) * m_window[m_num_windowed_samples[1]];
        }

        for (unsigned short w=0; w < 2; ++w) {
            ++m_num_windowed_samples[w];

            if (m_num_windowed_samples[w] == m_fft_win_size) {
                m_num_windowed_samples[w] = 0;
                if (w == 1 && m_odd_phase_window_is_bogus) {
                    // discard the first odd phase window; it only had half the samples
                    m_odd_phase_window_is_bogus = false;
                    break;
                }

                fftwf_execute(m_plan[w]);
                if (m_channels == 2)
                    fftwf_execute(m_plan[w + 2]);

                for (int j = m_first_freq_bin; j <= m_last_freq_bin; ++j) {
                    // for each bin, process total power across both channels in that bin
                    float pwr = m_fft[0][j][0] * m_fft[0][j][0] + m_fft[0][j][1] * m_fft[0][j][1];
                    if (m_channels == 2)
                        pwr += m_fft[1][j][0] * m_fft[1][j][0] + m_fft[1][j][1] * m_fft[1][j][1];
                    m_freq_bin_pulse_finder[j].process(pwr);
                }            
                // Any frequency bin may have seen a pulse (local max).
                // Ouput only the pulse with highest signal power whose SNR exceeds the threshold.

                int best = -1;
                float highest_probe_signal = 0;

                for (int j = m_first_freq_bin; j <= m_last_freq_bin; ++j) {
                    float bin_probe;
                    if (m_freq_bin_pulse_finder[j].got_pulse() 
                        && m_freq_bin_pulse_finder[j].pulse_SNR() >= m_min_pulse_SNR
                        && (bin_probe = m_freq_bin_pulse_finder[j].pulse_signal()) >= highest_probe_signal ) {
                        highest_probe_signal = bin_probe;
                        best = j;
                    }
                }
                if (best >= 0) {
                            // dump the feature
                    Feature feature;
                    feature.hasTimestamp = true;
                    feature.hasDuration = false;
                    
                    // The pulse timestamp is taken to be the centre of the fft window
                    
                    feature.timestamp = timestamp +
                        Vamp::RealTime::frame2RealTime((signed int) i - m_fft_win_size * ((1 + m_noise_win_size + m_min_pulse_sep) * m_pf_size) / 2.0, (size_t) m_inputSampleRate);
                    // compute a finer estimate of pulse offset frequency
                    
                    for (unsigned i = 0; i < m_channels; ++i ) {
                        // copy samples from ring buffer to fft input buffer
                        boost::circular_buffer < float > :: iterator b = m_sample_buf[i].begin();
                        for (int j = 0; j < m_plen_in_samples; ++j, ++b)
                            m_windowed_fine[i][j] = (float) *b;
                        // perform fft
                        fftwf_execute(m_plan_fine[i]);
                    }

                    // among those frequency bins covered by the
                    // current coarse estimate of pulse frequency,
                    // find the max power

                    int bin_low = std::max(1, (best - 1) * m_plen_in_samples / m_fft_win_size);
                    int bin_high = std::min(m_plen_in_samples / 2, (best + 1) * m_plen_in_samples / m_fft_win_size);

                    // int bin_low = 1;
                    // int bin_high = m_plen_in_samples / 2;

                    float max_power = 0.0;
                    int max_bin = -1;
                    for (int j = bin_low; j < bin_high; ++j) {
                        float pwr = m_fft_fine[0][j][0] * m_fft_fine[0][j][0] + m_fft_fine[0][j][1] * m_fft_fine[0][j][1];
                        if (m_channels == 2)
                            pwr += m_fft_fine[1][j][0] * m_fft_fine[1][j][0] + m_fft_fine[1][j][1] * m_fft_fine[1][j][1];
                        if (pwr > max_power) {
                            max_power = pwr;
                            max_bin = j;
                        }
                    }

                    // use a cubic estimator to find the peak frequency estimate using nearby bins
                    bin_low = std::max(1, std::min(m_plen_in_samples / 2 - 4, max_bin - 2));  // avoid the DC bin
                    
                    float bin_est = -1.0;
                    if (bin_low + 4 <= m_plen_in_samples / 2) {
                        float pwr[4];
                        for (int j = bin_low; j < bin_low + 4; ++j) {
                            pwr[j - bin_low] = m_fft_fine[0][j][0] * m_fft_fine[0][j][0] + m_fft_fine[0][j][1] * m_fft_fine[0][j][1];
                            if (m_channels == 2)
                                pwr[j - bin_low] += m_fft_fine[1][j][0] * m_fft_fine[1][j][0] + m_fft_fine[1][j][1] * m_fft_fine[1][j][1];
                        }
                        bin_est = bin_low + CubicMaximize(pwr[0], pwr[1], pwr[2], pwr[3]);
                    }
                    if (bin_est < 0)
                        bin_est = max_bin;

                    feature.values.push_back((bin_est * ((float) m_inputSampleRate / m_plen_in_samples)) / 1000.0);
                    feature.values.push_back(10 * log10(m_freq_bin_pulse_finder[best].pulse_signal() / m_probe_scale));
                    feature.values.push_back(10 * log10(m_freq_bin_pulse_finder[best].pulse_noise() / m_probe_scale));
                    returnFeatures[0].push_back(feature);
                }
            }
        }
    }
    return returnFeatures;
}

FindPulseFDBatch::FeatureSet
FindPulseFDBatch::getRemainingFeatures()
{
    return FeatureSet();
}

float FindPulseFDBatch::m_default_plen = 2.5; // milliseconds
float FindPulseFDBatch::m_default_min_pulse_SNR_dB = 5; // dB
int FindPulseFDBatch::m_default_fft_win_size = 24; // 0.5 milliseconds @ 48kHz
int FindPulseFDBatch::m_default_noise_win_size = 5; // pulse lengths
int FindPulseFDBatch::m_default_min_pulse_sep = 1; //pulse lengths
float FindPulseFDBatch::m_default_min_freq = 2.0; // 2 kHz
float FindPulseFDBatch::m_default_max_freq = 24.0; // 24 kHz
