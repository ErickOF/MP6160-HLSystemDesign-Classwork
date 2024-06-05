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

#ifndef _DCDC_PWM_H_
#define _DCDC_PWM_H_

#include <systemc-ams>

SCA_TDF_MODULE(dcdc_pwm)
{
  sca_tdf::sca_in<double > inp;
  sca_tdf::sca_out<bool> outp;

  // parameters
  sc_core::sc_time clk_period;
  double sawtooth_amp;
  sca_core::sca_time sample_time;

  void initialize();

  void processing();

  void set_attributes();

  // constructor
  dcdc_pwm(sc_core::sc_module_name nm,
    sc_core::sc_time clk_period_ = sc_core::sc_time(25.0, sc_core::SC_US),
    double sawtooth_amp_ = 2.5,
    sca_core::sca_time sample_time_ = sc_core::SC_ZERO_TIME);

private:
  // states
  double sum;
  double sawtooth;
  bool rswitch;
};

#endif // _DCDC_PWM_H_
