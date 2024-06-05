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

#ifndef _VIBRATION_SENSOR_H_
#define _VIBRATION_SENSOR_H_

#include <systemc-ams>

class vibration_sensor : public sca_tdf::sca_module
{
 public:
  sca_tdf::sca_in<double> x_in;    // Displacement [m]
  sca_tdf::sca_out<double> v_out;  // Sensor output voltage [V]

  // Construct TDF vibration sensor from its name and conversion
  // factor from vibration speed to output voltage [V s / m].
  vibration_sensor(sc_core::sc_module_name nm, double k_);

  void processing();

 private:
  double k;          // Conversion factor from vibration velocity to output voltage [V s / m]
  bool start_up;     // Flag to mark first execution of processing()
  double x_in_last;  // Last displacement read in previous processing() execution
  double x_dot;      // 1st time derivative of displacement, a.k.a. velocity
};

#endif // _VIBRATION_SENSOR_H_
