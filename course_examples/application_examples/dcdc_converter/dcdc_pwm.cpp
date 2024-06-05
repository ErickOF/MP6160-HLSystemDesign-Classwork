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

#include "dcdc_pwm.h"

void dcdc_pwm::initialize()
{
  // initialize delay value
  outp.initialize(false);
}

void dcdc_pwm::processing()
{
  // do not iterate - use first result
  if (this->get_timestep() > sc_core::SC_ZERO_TIME)
  {
    // generate sawtooth
    double freq = 1.0 / clk_period.to_seconds();

    // circular integration between -pi and pi
    double increment = freq * (this->get_timestep()).to_seconds();

    if (sum + increment > 1.0)
    {
      sum = sum + increment - 1.0;
    }
    else if (sum + increment < 0.0) //at time zero
    {
      sum = 0.0;
    }
    else
    {
      sum += increment;
    }

    sawtooth = sawtooth_amp * sum;

    // calculate switch output
    rswitch = (sawtooth > inp.read()) ? false : true;
  }

  outp.write(rswitch);
}

void dcdc_pwm::set_attributes()
{
  if (sample_time != sc_core::SC_ZERO_TIME)
  {
    set_timestep(sample_time);
  }
  outp.set_delay(1);
}

// constructor
dcdc_pwm::dcdc_pwm(sc_core::sc_module_name nm,
  sc_core::sc_time clk_period_,
  double sawtooth_amp_,
  sca_core::sca_time sample_time_)
: inp("inp"),
  outp("outp"),
  clk_period(clk_period_),
  sawtooth_amp(sawtooth_amp_),
  sample_time(sample_time_)
{
  accept_attribute_changes();

  // initial value for internal states
  sum = 0.0;
  sawtooth = 0.0;
  rswitch = false;
}
