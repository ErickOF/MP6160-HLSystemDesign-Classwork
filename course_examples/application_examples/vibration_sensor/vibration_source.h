//----------------------------------------------------------------------
//   Copyright 2009-2020 NXP
//   Copyright 2009-2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
//   Copyright 2015-2020 COSEDA Technologies GmbH
//   Copyright 2015-2020 Sorbonne Université, CNRS, LIP6
//   All Rights Reserved Worldwide
//
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//----------------------------------------------------------------------

#ifndef _VIBRATION_SOURCE_H_
#define _VIBRATION_SOURCE_H_

#include <systemc-ams>

class vibration_source : public sca_tdf::sca_module
{
 public:
  sca_tdf::sca_out<double> out;

  // Construct sinusoidal wavelets waveform generator
  vibration_source(sc_core::sc_module_name nm,
                   double offset_, double amplitude_, double f_0_,
                   int n_period_ = 1, int n_harmonic_ = 3);

  // Calculate and output value of waveform at time t
  void processing();

 private:
  const double offset;    // Offset of the sine wave
  const double amplitude; // Amplitude of the sine wave
  const double f_0;       // Base frequency of the sine wave
  const int n_period;     // Number of periods for one wavelet with f_0_
  const int n_harmonic;   // Number of harmonics in the wavelet sequence
  const double T_0;       // Period of sine wave with f_0_
  const double T_period;  // Period of a sine wavelet
};

#endif // _VIBRATION_SOURCE_H_
