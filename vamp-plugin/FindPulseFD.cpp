/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Vamp

    An API for audio analysis and feature extraction plugins.

    Centre for Digital Music, Queen Mary, University of London.
    Copyright 2006 Chris Cannam.

    FindPulseFD.cpp - find pulses from Lotek tags - frequency domain
    Copyright 2012 John Brzustowski

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
*/

#include "FindPulseFD.h"

using std::stringstream;
using std::string;
using std::vector;
using std::cerr;
using std::endl;

#include <cmath>
#include <sstream>

FindPulseFD::FindPulseFD(float inputSampleRate) :
    Plugin(inputSampleRate),
    m_stepSize(0),
    m_blockSize(0),
    m_plen(FindPulseFD::m_default_plen),
    m_min_pulse_power_dB(FindPulseFD::m_default_min_pulse_power_dB),
    m_fft_win_size(FindPulseFD::m_default_fft_win_size),
    m_min_freq(FindPulseFD::m_default_min_freq),
    m_max_freq(FindPulseFD::m_default_max_freq),
    m_have_fft_plan(false)
{
}

FindPulseFD::~FindPulseFD()
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
}

string
FindPulseFD::getIdentifier() const
{
    return "findpulseFD";
}

string
FindPulseFD::getName() const
{
    return "Find Pulses in Frequency Domain";
}

string
FindPulseFD::getDescription() const
{
    return "Find pulses (e.g. from Lotek telemetry tags)";
}

string
FindPulseFD::getMaker() const
{
    return "flightcalls.org jbrzusto@fastmail.fm";
}

int
FindPulseFD::getPluginVersion() const
{
    return 1;
}

string
FindPulseFD::getCopyright() const
{
    return "GPL version 2 or later";
}

bool
FindPulseFD::initialise(size_t channels, size_t stepSize, size_t blockSize)
{
    if (channels < getMinChannelCount() ||
	channels > getMaxChannelCount()) return false;

    m_channels = channels;
    m_stepSize = stepSize;
    m_blockSize = blockSize;

    m_pf_size = roundf(m_inputSampleRate * (m_plen / 1000.0) / (m_fft_win_size / 2));

    int num_bins = m_fft_win_size / 2 + 1;

    m_last_timestamp = std::vector < Vamp::RealTime > (num_bins, Vamp::RealTime(-1, 0));

    m_freq_bin_pulse_finder = std::vector < PulseFinder < float > > (num_bins, PulseFinder < float > (m_pf_size));

    for (int i=0; i < 2; ++i)
        m_fft[i] = (fftwf_complex *) fftwf_malloc((m_fft_win_size / 2 + 1) * sizeof(fftwf_complex) );

    // allocate two input windows for each channel; for each channel, both phase windows use the same output array
    for (int i=0; i < 4; ++i) {
        m_windowed[i] = (float *) fftwf_malloc(m_fft_win_size * sizeof(float));
        m_plan[i] = fftwf_plan_dft_r2c_1d(m_fft_win_size, m_windowed[i], m_fft[i / 2], FFTW_PATIENT);
    }

    m_probe_scale = 2 * m_pf_size * 2 * m_fft_win_size * m_fft_win_size / (M_PI * M_PI);
    m_min_probe = exp10(m_min_pulse_power_dB / 10.0) * m_probe_scale;

    m_first_freq_bin = floorf(m_min_freq * 1000.0 / (m_inputSampleRate / m_fft_win_size));
    m_last_freq_bin =  ceilf(m_max_freq * 1000.0 / (m_inputSampleRate / m_fft_win_size));

    m_num_windowed_samples[0] = 0;

    // ugly hack to simplify accumulation in odd-phase sliding window
    m_num_windowed_samples[1] = m_fft_win_size / 2;
    return true;
}

void
FindPulseFD::reset()
{
}

FindPulseFD::ParameterList
FindPulseFD::getParameterDescriptors() const
{
    ParameterList list;

    ParameterDescriptor d;
    d.identifier = "plen";
    d.name = "Pulse Length";
    d.description = "Duration of a transmitted pulse in milliseconds";
    d.unit = "milliseconds";
    d.minValue = 0.1;
    d.maxValue = 50;
    d.defaultValue = FindPulseFD::m_default_plen;
    d.isQuantized = false;
    list.push_back(d);

    d.identifier = "minpower";
    d.name = "Minimum Pulse Power";
    d.description = "Minimum pulse power, in dB";
    d.unit = "dB";
    d.minValue = -100;
    d.maxValue = 0;
    d.defaultValue = FindPulseFD::m_default_min_pulse_power_dB;
    d.isQuantized = false;
    list.push_back(d);

    d.identifier = "fftsize";
    d.name = "Size of FFT window";
    d.description = "The number of samples in each window for which an FFT is computed.  Windows are non-overlapping.  A window of 96 samples for 96kHz sampling means one FFT calculated each millisecond";
    d.unit = "samples";
    d.minValue = 10;
    d.maxValue = 1000;
    d.defaultValue = FindPulseFD::m_default_fft_win_size;
    d.isQuantized = true;
    d.quantizeStep = 1;
    list.push_back(d);

    d.identifier = "minfreq";
    d.name = "Minimum Tag Offset Frequency";
    d.description = "Minimum frequency by which tag differs from receiver, in kHz";
    d.unit = "kHz";
    d.minValue = 0;
    d.maxValue = 48;
    d.defaultValue = FindPulseFD::m_default_min_freq;
    d.isQuantized = false;
    list.push_back(d);

    d.identifier = "maxfreq";
    d.name = "Maximum Tag Offset Frequency";
    d.description = "Maximum frequency by which tag differs from receiver, in kHz";
    d.unit = "kHz";
    d.minValue = 0;
    d.maxValue = 48;
    d.defaultValue = FindPulseFD::m_default_max_freq;
    d.isQuantized = false;
    list.push_back(d);

    return list;
}

float
FindPulseFD::getParameter(string id) const
{
    if (id == "plen") {
        return m_plen;
    } else if (id == "minpower") {
        return m_min_pulse_power_dB;
    } else if (id == "fftsize") {
        return m_fft_win_size;
    } else if (id == "minfreq") {
        return m_min_freq;
    } else if (id == "maxfreq") {
        return m_max_freq;
    }
    return 0.f;
}

void
FindPulseFD::setParameter(string id, float value)
{
    if (id == "plen") {
        FindPulseFD::m_default_plen = m_plen = value;
    } else if (id == "minpower") {
        FindPulseFD::m_default_min_pulse_power_dB = m_min_pulse_power_dB = value;
    } else if (id == "fftsize") {
        FindPulseFD::m_default_fft_win_size = m_fft_win_size = value;
    } else if (id == "minfreq") {
        FindPulseFD::m_default_min_freq = m_min_freq = value;
    } else if (id == "maxfreq") {
        FindPulseFD::m_default_max_freq = m_max_freq = value;
    }
}


FindPulseFD::OutputList
FindPulseFD::getOutputDescriptors() const
{
    OutputList list;

    OutputDescriptor zc;

    zc.identifier = "pulses";
    zc.name = "Pulses";
    zc.description = "The locations and features of pulses";
    zc.unit = "";
    zc.hasFixedBinCount = true;
    zc.binCount = 0;
    zc.sampleType = OutputDescriptor::VariableSampleRate;
    zc.sampleRate = m_inputSampleRate;
    list.push_back(zc);

    return list;
}

FindPulseFD::FeatureSet
FindPulseFD::process(const float *const *inputBuffers,
                      Vamp::RealTime timestamp)
{
    FeatureSet returnFeatures;

    static bool odd_phase_window_is_bogus = true;

    if (m_stepSize == 0) {
	cerr << "ERROR: FindPulseFD::process: "
	     << "FindPulseFD has not been initialised"
	     << endl;
	return returnFeatures;
    }

    for (unsigned int i=0; i < m_blockSize; ++i) {
        // append each weighted sample to each window
        m_windowed[0][m_num_windowed_samples[0]] = inputBuffers[0][i] * (1 - 2 * abs(m_num_windowed_samples[0] - m_fft_win_size / 2) / m_fft_win_size);
        m_windowed[1][m_num_windowed_samples[1]] = inputBuffers[0][i] - m_windowed[0][m_num_windowed_samples[0]];
        m_windowed[0 + 2][m_num_windowed_samples[0]] = inputBuffers[1][i] * (1 - 2 * abs(m_num_windowed_samples[0] - m_fft_win_size / 2) / m_fft_win_size);
        m_windowed[1 + 2][m_num_windowed_samples[1]] = inputBuffers[1][i] - m_windowed[0 + 2][m_num_windowed_samples[0]];

        for (unsigned short w=0; w < 2; ++w) {
            ++m_num_windowed_samples[w];

            if (m_num_windowed_samples[w] == m_fft_win_size) {
                m_num_windowed_samples[w] = 0;
                if (w == 1 && odd_phase_window_is_bogus) {
                    // discard the first odd phase window; it only had half the samples
                    odd_phase_window_is_bogus = false;
                    break;
                }

                fftwf_execute(m_plan[w]);
                fftwf_execute(m_plan[w + 2]);

                for (int j = m_first_freq_bin; j <= m_last_freq_bin; ++j) {
                    // for each bin, process total powerr across both channels in that bin
                    m_freq_bin_pulse_finder[j].process( m_fft[0][j][0] * m_fft[0][j][0] +
                                                        m_fft[0][j][1] * m_fft[0][j][1] +
                                                        m_fft[1][j][0] * m_fft[1][j][0] +
                                                        m_fft[1][j][1] * m_fft[1][j][1]);
                }            
                // Any frequency bin may have seen a pulse (local max).
                // Ouput only the loudest pulse, and only if it exceeds 
                // the threshold

                int best = -1;
                float highest_probe = m_min_probe;

                for (int j = m_first_freq_bin; j <= m_last_freq_bin; ++j) {
                    float bin_probe;
                    if (m_freq_bin_pulse_finder[j].got_pulse() 
                        && (bin_probe = m_freq_bin_pulse_finder[j].pulse_val()) >= highest_probe ) {
                        highest_probe = bin_probe;
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
                        Vamp::RealTime::frame2RealTime((signed int) i - m_fft_win_size * ((5 * m_pf_size - 3) / 2), (size_t) m_inputSampleRate);
                    std::stringstream ss;
                    ss.precision(3);
                    // frequency is that of middle of bin
                    ss << "freq: " << ((best + 0.5) * ((float) m_inputSampleRate / m_fft_win_size)) / 1000
                       << " kHz; pwr: " << 10 * log10(highest_probe / m_probe_scale)
                       << " dB";
                    ss.precision(2);
                    if (m_last_timestamp[best].sec >= 0) {
                        Vamp::RealTime gap =  feature.timestamp - m_last_timestamp[best];
                        if (gap.sec < 1) {
                            ss.precision(0);
                            ss << "; Gap: " << gap.msec() << " ms";
                        } else {
                            ss.precision(1);
                            ss << "; Gap: " << gap.sec + (double) gap.msec()/1000 << " s";
                        }
                    }
                    m_last_timestamp[best] = feature.timestamp;
                    feature.label = ss.str();
                    returnFeatures[0].push_back(feature);
                }
            }
        }
    }
    return returnFeatures;
}

FindPulseFD::FeatureSet
FindPulseFD::getRemainingFeatures()
{
    return FeatureSet();
}

float FindPulseFD::m_default_plen = 2.5; // milliseconds
float FindPulseFD::m_default_min_pulse_power_dB = -55; // dB
int FindPulseFD::m_default_fft_win_size = 24; // 0.5 milliseconds
float FindPulseFD::m_default_min_freq = 2.0; // 2 kHz
float FindPulseFD::m_default_max_freq = 12.0; // 12 kHz
