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

#ifndef _DIODE_DTDF_H_
#define _DIODE_DTDF_H_

#include <systemc-ams>

SCA_TDF_MODULE(diode_dtdf)
{
  // ports
  sca_tdf::sca_in<double > vin;
  sca_tdf::sca_out<double> vth;
  sca_tdf::sca_out<double> rout;

  // parameters
  double ron;
  double roff;
  double vth_p;

  void initialize();

  void processing();

  void end_of_simulation();
  
  void set_attributes();

  void change_attributes();

  // constructor
  diode_dtdf(sc_core::sc_module_name nm, double ron_ = 1e-3, double roff_ = 1e9, double vth_p_ = 0.7 );

 private:
  //states
  bool ron_state;
  long recalculate;
  long activations;
  long iterations;
  long max_iterations;
  long timestep_cnt;
};

#endif // _DIODE_DTDF_H_
