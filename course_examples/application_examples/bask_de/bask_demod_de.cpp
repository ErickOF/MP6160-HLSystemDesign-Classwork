//----------------------------------------------------------------------
//   Copyright 2009-2020 NXP
//   Copyright 2009 Vienna University of Technology
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

#include "bask_demod_de.h"

bask_demod_de::bask_demod_de( sc_core::sc_module_name nm )
: in("in"), out("out"), rc("rc"), lp("lp", 3.3e6), sp("sp"), rc_out("rc_out"), lp_out("lp_out")
{
  rc.in(in);
  rc.out(rc_out);

  lp.in(rc_out);
  lp.out(lp_out);

  sp.in(lp_out);
  sp.out(out);
}
