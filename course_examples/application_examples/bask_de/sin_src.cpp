//----------------------------------------------------------------------
//   Copyright 2009-2020 NXP
//   Copyright 2009-2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
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

#include "sin_src.h"

sin_src::sin_src( sc_core::sc_module_name nm, double ampl_,
		          double freq_, sca_core::sca_time Tm_ )
: out("out"), ampl(ampl_), freq(freq_), Tm(Tm_)
{}

void sin_src::set_attributes()
{
  set_timestep(Tm);
}

void sin_src::processing()
{
  double t = get_time().to_seconds(); // actual time
  out.write( ampl * std::sin( 2.0 * M_PI * freq * t ) );
}

