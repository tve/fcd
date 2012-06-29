/* -*- mode:c++; c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Vamp

    An API for audio analysis and feature extraction plugins.

    Centre for Digital Music, Queen Mary, University of London.
    Copyright 2006 Chris Cannam.

    FindPulseFD.h
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

#ifndef _FIND_PULSEFD_PLUGIN_H_
#define _FIND_PULSEFD_PLUGIN_H_

#include <boost/circular_buffer.hpp>
#include "vamp-sdk/Plugin.h"
#include "PeakFinder.h"
#include <complex>
#include <fftw3.h>

/**
 * Look for pulses from Lotek tags - Frequency Domain version
*/

class FindPulseFD : public Vamp::Plugin
{
public:
    FindPulseFD(float inputSampleRate);
    virtual ~FindPulseFD();

    bool initialise(size_t channels, size_t stepSize, size_t blockSize);
    void reset();

    InputDomain getInputDomain() const { return TimeDomain; }
    size_t getMinChannelCount() const {return 2;}
    size_t getMaxChannelCount() const {return 2;}
    size_t getPreferredStepSize() const {return 1024;}
    size_t getPreferredBlockSize() const {return 1024;}
    std::string getIdentifier() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getMaker() const;
    int getPluginVersion() const;
    std::string getCopyright() const;

    ParameterList getParameterDescriptors() const;
    float getParameter(std::string id) const;
    void setParameter(std::string id, float value);

    OutputList getOutputDescriptors() const;

    FeatureSet process(const float *const *inputBuffers,
                       Vamp::RealTime timestamp);

    FeatureSet getRemainingFeatures();

protected:
    size_t m_channels;
    size_t m_stepSize;
    size_t m_blockSize;
    
    // paramters
    float m_plen;        // width of pulse we're trying to detect, in ms
    float m_min_pulse_score; // min score of pulse power vs. mean noise power to be accepted
    int m_fft_win_size;  // number of consecutive samples in non-overlapping FFT windows
    float m_noise_estimator_decay; // constant multiplier in [0,1] of current mean noise when computing new mean noise estimate
    
    // parameter defaults
    static float m_default_plen;           // width of pulse we're trying to detect, in ms
    static float m_default_min_pulse_score;       // min score of pulse power vs. mean noise power to be accepted
    static int   m_default_fft_win_size;            // number of consecutive samples in non-overlapping FFT wi
    static float m_default_noise_estimator_decay; // constant multiplier in [0,1] of current mean noise when computing new mean noise estimate

    // internal registers
    float *m_power; // power in time domain
    fftwf_complex *m_fft; // DFT of power
    fftwf_plan m_plan;
    bool m_have_fft_plan;
    int m_pf_size; // size of peak finder moving average window (in units of fft windows)
    float m_power_adjust; // 10 * log10( 1 / sqrt(m_fft_win_size)) adjustment to raw power to account for fftw3 not scaling

    std::vector < Vamp::RealTime > m_last_timestamp;

    int m_num_power_samples;  // number of samples put in m_power array since last fft

    std::vector < PeakFinder < float > > m_freq_bin_peak_finder;
    std::vector < float > m_freq_bin_noise_mean;
    std::vector < float > m_freq_bin_noise_dev;
};


#endif // _FIND_PULSEFD_PLUGIN_H_
