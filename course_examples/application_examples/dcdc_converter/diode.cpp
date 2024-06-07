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

#include "diode.h"
#include "diode_dtdf.h"

diode::diode(sc_core::sc_module_name nm,
  double vth_p_,
  double ron_,
  double roff_)
: np("np"),
  nn("nn"),
  i_diode_characteristic("i_diode_characteristic", ron_, roff_, vth_p_),
  i_vth("i_vth", 1.0),
  i_vdiode2tdf("i_vdiode2tdf", 1.0),
  i_rdiode("i_rdiode", 1.0),
  s_rout("s_rout"),
  s_vth("s_vth"),
  n_rdiode("n_rdiode"),
  s_vdiode("s_vdiode")
{
  // netlist
  i_diode_characteristic.vin(s_vdiode);
  i_diode_characteristic.vth(s_vth);
  i_diode_characteristic.rout(s_rout);

  i_vth.p(np);
  i_vth.n(n_rdiode);
  i_vth.inp(s_vth);

  i_vdiode2tdf.p(np);
  i_vdiode2tdf.n(nn);
  i_vdiode2tdf.outp(s_vdiode);

  i_rdiode.p(nn);
  i_rdiode.n(n_rdiode);
  i_rdiode.inp(s_rout);
}
