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

#include "diode_dtdf.h"

void diode_dtdf::initialize()
  {
    //iteration at time zero is possible
    rout.initialize(roff);
    vth.initialize(0.0);
    ron_state = true;

    recalculate = 0;
    activations = 0;
    iterations = 0;
    max_iterations = 0;
    timestep_cnt = 0;
  }

void diode_dtdf::processing()
{
  double vin_tmp = vin.read();

  if (this->get_timestep() > sc_core::SC_ZERO_TIME)
    timestep_cnt++;

  //switch between states
  if (ron_state) {
    //hysteresis due curves do not fit exactly
    if (vin_tmp > vth_p) {
      recalculate = 0;
    }
    else {
      recalculate++;
      ron_state = false;
    }
  } else {
    if (vin_tmp < vth_p) {
      recalculate = 0;
    } else {
      recalculate++;
      ron_state = true;
    }
  }

  //set resistance and threshold in dependency of the state
  if (ron_state) {
    rout.write(ron);
    vth.write(vth_p);
  } else {
    rout.write(roff);
    vth.write(0.0);
  }
}

void diode_dtdf::end_of_simulation()
{
  std::ostringstream str;

  str << "Repeat timestep requests: " << iterations << " from: "
      << timestep_cnt << " valid timesteps. ";
  str << " overall timesteps: " << activations;
  str << " maximum repeat of a timestep: " << max_iterations;
  SC_REPORT_INFO("diode_dtdf", str.str().c_str());
}
  
void diode_dtdf::set_attributes()
{
  vth.set_delay(1);
  rout.set_delay(1);
}

void diode_dtdf::change_attributes()
{
  activations++;

  if (recalculate > 0)
  {
    //invalid, repeat last timestep
    request_next_activation(sc_core::SC_ZERO_TIME);

    if (recalculate > 30) {
      SC_REPORT_ERROR("diode_dtdf", "Convergence failed");
    }

    iterations++;
    if (recalculate > max_iterations)
      max_iterations = recalculate;
  }
}

  // constructor
diode_dtdf::diode_dtdf(sc_core::sc_module_name nm,
  double ron_,
  double roff_,
  double vth_p_)
: vin("vin"), vth("vth"), rout("rout"),
  ron(ron_), roff(roff_), vth_p(vth_p_)
{
  accept_attribute_changes();
  does_attribute_changes();
}

