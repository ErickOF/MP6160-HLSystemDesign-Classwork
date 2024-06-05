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

#include "vibration_sensor.h"

vibration_sensor::vibration_sensor(sc_core::sc_module_name nm, double k_)
: x_in("x_in"),
  v_out("v_out"),
  k(k_),
  start_up(true),
  x_in_last(0.0),
  x_dot(0.0)
{}

void vibration_sensor::processing()
{
  // Calculate velocity as 1st time derivative of displacement by
  // evaluating Newton's difference quotient for the current and
  // last sample.
  if (!start_up) {
    x_dot = (x_in.read() - x_in_last) / x_in.get_timestep().to_seconds();
  } else {
    start_up = false;
  }
  x_in_last = x_in.read();

  // Convert vibration velocity to output voltage via conversion factor k
  v_out.write(k * x_dot);
}
