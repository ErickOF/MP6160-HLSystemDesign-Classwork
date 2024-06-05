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

#ifndef _DCDC_CONVERTER_H_
#define _DCDC_CONVERTER_H_

#include <systemc-ams>

#include "compensator.h"
#include "dcdc_pwm.h"
#include "diode.h"

SC_MODULE(dcdc_converter)
{
  sca_eln::sca_terminal vout;
  sca_tdf::sca_in<double> vsupply;
  sca_tdf::sca_in<double> vref;

  // parameters
  double l_value;
  double c_value;
  sca_core::sca_time sample_time;

  //declare instance references for external access
  compensator i_compensator;
  sca_eln::sca_tdf_vsource i_vsupply;
  sca_eln::sca_tdf_rswitch i_switch;
  sca_eln::sca_l i_sca_l;
  sca_eln::sca_c i_sca_c;
  sca_eln::sca_tdf_vsink i_sca_tdf_vsink;
  dcdc_pwm i_dcdc_pwm;
  diode i_diode;

  dcdc_converter(sc_core::sc_module_name name,
    double l_val_ = 6.5e-3,
    double c_val_ = 6e-6,
    sc_core::sc_time sample_time_ = sc_core::SC_ZERO_TIME);

 private:
  //node and signal references for external access
  sca_tdf::sca_signal<bool> rsw;
  sca_tdf::sca_signal<double> ctrl;
  sca_tdf::sca_signal<double> s_vout;
  sca_eln::sca_node_ref gnd;
  sca_eln::sca_node vx;
  sca_eln::sca_node n_supply;
};

#endif // _DCDC_CONVERTER_H_
