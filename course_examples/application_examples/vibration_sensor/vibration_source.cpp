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

#include "vibration_source.h"

vibration_source::vibration_source(sc_core::sc_module_name nm,
  double offset_,
  double amplitude_,
  double f_0_,
  int n_period_,
  int n_harmonic_)
: out("out"), offset(offset_), amplitude(amplitude_), f_0(f_0_),
  n_period(n_period_), n_harmonic(n_harmonic_),
  T_0(1.0 / f_0_), T_period(n_period * T_0)
{
  sc_assert(f_0_ > 0.0);
  sc_assert(n_period_ >= 1);
  sc_assert(n_harmonic_ >= 0);
}

void vibration_source::processing()
{
  double t = this->get_time().to_seconds();
  double t_pos = fmod(t, T_period);
  int harmonic = static_cast<int>(floor(t / T_period)) % (n_harmonic + 1);
  double val = offset;
  val += amplitude * sin(2.0 * M_PI * pow(2.0, harmonic) * f_0 * t_pos);
  out.write(val);
}
