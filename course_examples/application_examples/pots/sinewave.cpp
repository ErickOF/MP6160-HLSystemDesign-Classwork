//----------------------------------------------------------------------
//   Copyright 2015-2020 COSEDA Technologies GmbH
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

#include "sinewave.h"

void sinewave::set_attributes()
{
  outp.set_timestep(p.sample_time);
}

sinewave::sinewave(sc_core::sc_module_name nm,params pa) : p(pa)
{
}

// frequency domain implementation
void sinewave::ac_processing()
{
  // we use for ac-domain for all frequencies the same amplitude and a phase=0
  sca_ac_analysis::sca_ac (outp) = p.ampl;
}

// time domain implementation
void sinewave::processing()
{
  outp = p.ampl * sin(2.0 * M_PI * p.freq * get_time().to_seconds()) + p.offset;
}
