/* -*- mode: c++ -*- */
/*
    Copyright 2012 John Brzustowski

    Licence: GPL version 2 or later
*/

#ifndef _PULSE_FINDER_H
#define _PULSE_FINDER_H

// Pulsefinder: search an input sequence for pulses of width n, using this probe function:
//
//             +1|               ---- (n) ----
//               |
//               |
//               |
//              0|
//               |
//          -0.25| ---- (4n) ----              ---- (4n) ----
//
//             A pulse is flagged every time the probe function convolved with the input sequence
//             reaches a maximum over a window of 2n+1 consecutive slots.  

#include <boost/circular_buffer.hpp>

template < typename DATATYPE >
class PulseFinder {
 public:
  PulseFinder (size_t n = 1) :
    m_pulse_width(n),
    m_4pw(2*n),
    m_5pw(3*n),
    m_sample_buf (9 * n),
    m_probe_buf (2* n + 1),
    m_probe_sum (0),
    m_max_probe_index (-1),
    m_got_pulse(false)
  {
  };

  bool got_pulse () {  // have we seen a pulse? True if the probe value was maximum at the centre of the 2n+1-sized window.
    return m_got_pulse;
  }

  DATATYPE pulse_val () { // the value of the pulse probe; only valid if got_pulse() is true
    return m_pulse_val;
  }

  void process(DATATYPE d) { // process a value from the data stream
    m_got_pulse = false;

    if (m_sample_buf.full())
      m_probe_sum += 0.125 * m_sample_buf[0];  // the first sample is moving from the left negative zone out of the probe window

    int n = m_sample_buf.size();

    if (n >= m_4pw)
      m_probe_sum += 1.125 * m_sample_buf[n - m_4pw]; // a sample is moving from the right negative zone to the central positive zone
    if (n >= m_5pw)
      m_probe_sum += -1.125 * m_sample_buf[n - m_5pw]; // a sample is moving from the central positive zone to the left negative zone

    // the new sample moves into the right negative zone
    m_probe_sum += -0.125 * d;
    m_sample_buf.push_back(d);

    if (m_sample_buf.full()) {
      // we have a full probe value; push it into the probe buffer
      // and recalculate the buffer maximum

      // note whether the current max position must move
      bool max_will_move = m_probe_buf.full();

      m_probe_buf.push_back(m_probe_sum);
      if (m_max_probe_index < 0 || m_probe_sum >= m_max_probe) {
	m_max_probe = m_probe_sum;
	m_max_probe_index = m_probe_buf.size() - 1;
      } else if (max_will_move) {
	// the location of the max will change
	if (m_max_probe_index == 0) {
	  // the max was shifted out so rescan
	  m_max_probe_index = 0;
	  m_max_probe = m_probe_buf[0];
	  for (unsigned i=1; i < m_probe_buf.capacity(); ++i) {
	    if (m_probe_buf[i] > m_max_probe) {
	      m_max_probe_index = i;
	      m_max_probe = m_probe_buf[i];
	    }
	  }
	} else {
	  // the max value is unchanged, but the window has advanced one slot
	  -- m_max_probe_index;
	}
      }
      if (m_max_probe_index == m_pulse_width) {
	// the central value in the probe buffer is the maximum,
	// so indicate we have a pulse.
	m_got_pulse = true;
	m_pulse_val = m_max_probe;
      }
    }
  }
      
 protected:
  int m_pulse_width;
  int m_4pw;
  int m_5pw;
  boost::circular_buffer < DATATYPE > m_sample_buf;
  boost::circular_buffer < DATATYPE > m_probe_buf;
  DATATYPE m_probe_sum;
  int m_max_probe_index;
  DATATYPE m_max_probe;
  bool m_got_pulse;
  DATATYPE m_pulse_val;
  
};

#endif //  _PULSE_FINDER_H
