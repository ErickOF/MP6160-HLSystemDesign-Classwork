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

#include "dcdc_converter.h"

dcdc_converter::dcdc_converter(sc_core::sc_module_name name,
  double l_val_,
  double c_val_,
  sc_core::sc_time sample_time_)
: vout("vout"),
  vsupply("vsupply"),
  vref("vref"),
  l_value(l_val_),
  c_value(c_val_),
  sample_time(sample_time_),
  i_compensator("i_compensator", 806.0/2.0, 806.0/2.0, 7.5e3, 531.0e3, 100.0),
  i_vsupply("i_vsupply", 1.0),
  i_switch("i_switch", 1e-3, 1e9, false),
  i_sca_l("i_sca_l", l_value, 0.0),
  i_sca_c("i_sca_c", c_value, 0.0),
  i_sca_tdf_vsink("i_sca_tdf_vsink", 1.0),
  i_dcdc_pwm("i_dcdc_pwm", sc_core::sc_time(40.0, sc_core::SC_US), 2.5, sample_time_),
  i_diode("i_diode", 0.7, 1e-3, 1e9),
  rsw("rsw"),  ctrl("ctrl"), s_vout("s_vout"),
  gnd("gnd"), vx("vx"), n_supply("n_supply")
{
  // component binding (netlist)
  i_compensator.inp(s_vout);
  i_compensator.ref(vref);
  i_compensator.outp(ctrl);

  i_vsupply.p(n_supply);
  i_vsupply.n(gnd);
  i_vsupply.inp(vsupply);

  i_switch.p(n_supply);
  i_switch.n(vx);
  i_switch.ctrl(rsw);

  i_sca_l.p(vx);
  i_sca_l.n(vout);

  i_sca_c.p(gnd);
  i_sca_c.n(vout);

  i_sca_tdf_vsink.p(vout);
  i_sca_tdf_vsink.n(gnd);
  i_sca_tdf_vsink.outp(s_vout);

  i_dcdc_pwm.inp(ctrl);
  i_dcdc_pwm.outp(rsw);

  i_diode.np(gnd);
  i_diode.nn(vx);
 }

