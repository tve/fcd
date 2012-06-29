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
    m_min_pulse_score(FindPulseFD::m_default_min_pulse_score),
    m_fft_win_size(FindPulseFD::m_default_fft_win_size),
    m_noise_estimator_decay(FindPulseFD::m_default_noise_estimator_decay),
    m_have_fft_plan(false),
    m_num_power_samples(0)
{
}

FindPulseFD::~FindPulseFD()
{
    if (m_have_fft_plan) {
         fftwf_destroy_plan(m_plan);
         fftw_free(m_power); 
         fftw_free(m_fft);
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

    m_pf_size = m_inputSampleRate * (m_plen / 1000.0) / m_fft_win_size;

    int num_bins = m_fft_win_size / 2 + 1;
    m_power_adjust = - 10 * log10f(2 * m_fft_win_size); // dB to adjust power due to fftw not scaling

    m_last_timestamp = std::vector < Vamp::RealTime > (num_bins, Vamp::RealTime(-1, 0));

    m_freq_bin_peak_finder = std::vector < PeakFinder < float > > (num_bins, PeakFinder < float > (m_pf_size));

    m_freq_bin_noise_mean = std::vector <float> (num_bins, 0);
    m_freq_bin_noise_dev = std::vector <float> (num_bins, 1);

    m_power = fftwf_alloc_real(m_fft_win_size);
    m_fft = fftwf_alloc_complex(m_fft_win_size / 2 + 1);
    m_plan = fftwf_plan_dft_r2c_1d(m_fft_win_size, m_power, m_fft, FFTW_MEASURE);
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

    d.identifier = "minscore";
    d.name = "Minimum Pulse Score";
    d.description = "Minimum z-score of a pulse in its frequency bin, measured against background mean and SD in bin; lower scoring pulses are discarded";
    d.unit = "SD above mean";
    d.minValue = 0;
    d.maxValue = 50;
    d.defaultValue = FindPulseFD::m_default_min_pulse_score;
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

    d.identifier = "noiseestdecay";
    d.name = "Noise estimator decay constant";
    d.description = "Constant by which existing noise sum and sum of squares is multiplied before adding new noise sample";
    d.unit = "";
    d.minValue = 0;
    d.maxValue = 1;
    d.defaultValue = FindPulseFD::m_default_noise_estimator_decay;
    d.isQuantized = false;
    list.push_back(d);

    return list;
}

float
FindPulseFD::getParameter(string id) const
{
    if (id == "plen") {
        return m_plen;
    } else if (id == "minscore") {
        return m_min_pulse_score;
    } else if (id == "fftsize") {
        return m_fft_win_size;
    } else if (id == "noiseestdecay") {
        return m_noise_estimator_decay;
    }
    return 0.f;
}

void
FindPulseFD::setParameter(string id, float value)
{
    if (id == "plen") {
        FindPulseFD::m_default_plen = m_plen = value;
    } else if (id == "minscore") {
        FindPulseFD::m_default_min_pulse_score = m_min_pulse_score = value;
    } else if (id == "fftsize") {
        FindPulseFD::m_default_fft_win_size = m_fft_win_size = value;
    } else if (id == "noiseestdecay") {
        FindPulseFD::m_default_noise_estimator_decay = m_noise_estimator_decay = value;
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

    if (m_stepSize == 0) {
	cerr << "ERROR: FindPulseFD::process: "
	     << "FindPulseFD has not been initialised"
	     << endl;
	return returnFeatures;
    }

    unsigned n_freq_bins = m_fft_win_size / 2;

    for (unsigned int i=0; i < m_blockSize; ++i) {
        float sample_power = sqrtf(inputBuffers[0][i] * inputBuffers[0][i] 
                                   + inputBuffers[1][i] * inputBuffers[1][i]);
        m_power[m_num_power_samples++] = sample_power;
        if (m_num_power_samples == m_fft_win_size) {
            m_num_power_samples = 0;

            fftwf_execute(m_plan);

            for (unsigned int j = 1; j < n_freq_bins; ++j) {
                // replace each bin's real component with bin power
                m_fft[j][0] = m_fft[j][0] * m_fft[j][0]
                    + m_fft[j][1] * m_fft[j][1];

                // process power in each freq bin
                m_freq_bin_peak_finder[j].process(m_fft[j][0]);
            }            
            // Any frequency bin may have seen a peak (local max).
            // This will be called a "pulse candidate" if it has a
            // z-score (against bin noise) of at least
            // m_min_pulse_score.  Looking across bins, for any
            // contiguous sequence of pulse candidates, we accept as a
            // pulse only the pulse candidate with the largest score.
            // This avoids reporting multiple pulses when a single pulse
            // is smeared across adjacent frequency bins.

            unsigned int best_in_seq = 0;
            float best_score_in_seq = 0;
            bool in_seq = false;
            for (unsigned int j = 1; j <= n_freq_bins; ++j) {
                float bin_score;
                if (j < n_freq_bins && m_freq_bin_peak_finder[j].got_peak() 
                    && (bin_score = (m_freq_bin_peak_finder[j].peak_val() - m_freq_bin_noise_mean[j]) / m_freq_bin_noise_dev[j]) >= m_min_pulse_score) {
                    // it's a pulse candidate
                    if ((! in_seq) || (in_seq && (bin_score > best_score_in_seq))) {
                        best_score_in_seq = bin_score;
                        best_in_seq = j;
                        in_seq = true;
                    }
                } else {
                    // not a pulse candidate
                    if (in_seq) {
                        // dump the feature from the just-ended sequence
                        // of pulse candidates
                        Feature feature;
                        feature.hasTimestamp = true;
                        feature.hasDuration = false;

                        // The pulse timestamp is taken to be the centre of the moving average window.

                        feature.timestamp = timestamp +
                            Vamp::RealTime::frame2RealTime((signed int) i - m_fft_win_size * (1 + m_pf_size / 2), (size_t)m_inputSampleRate);
                        std::stringstream ss;
                        ss.precision(3);
                        // frequency is that of middle of bin
                        ss << "freq: " << (best_in_seq * ((float) m_inputSampleRate / m_fft_win_size)) / 1000
                           << " kHz; pwr: " << 10 * log10f(m_freq_bin_peak_finder[best_in_seq].peak_val()) + m_power_adjust
                           << " dB; score: " << best_score_in_seq
                           << "; noise: " << 10 * log10f(m_freq_bin_noise_mean[best_in_seq]) + m_power_adjust << " dB";
                        ss.precision(2);
                        if (m_last_timestamp[best_in_seq].sec >= 0) {
                            Vamp::RealTime gap =  feature.timestamp - m_last_timestamp[best_in_seq];
                            if (gap.sec < 1) {
                                ss.precision(0);
                                ss << "; Gap: " << gap.msec() << " ms";
                            } else {
                                ss.precision(1);
                                ss << "; Gap: " << gap.sec + (double) gap.msec()/1000 << " s";
                            }
                        }
                        m_last_timestamp[best_in_seq] = feature.timestamp;
                        feature.label = ss.str();
                        returnFeatures[0].push_back(feature);
                        in_seq = false;
                    }
                    // update the background noise estimates
                    // with the power from this bin
                    m_freq_bin_noise_mean[j] *= m_noise_estimator_decay;
                    m_freq_bin_noise_mean[j] += (1 - m_noise_estimator_decay) * m_fft[j][0];
                    m_freq_bin_noise_dev[j] *= m_noise_estimator_decay;
                    m_freq_bin_noise_dev[j] += (1 - m_noise_estimator_decay) * fabsf(m_fft[j][0] - m_freq_bin_noise_mean[j]);
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
float FindPulseFD::m_default_min_pulse_score = 2.5; // z-score
int FindPulseFD::m_default_fft_win_size = 48; // 0.5 milliseconds
float FindPulseFD::m_default_noise_estimator_decay = 0.9999; // half-life of 6931 samples
