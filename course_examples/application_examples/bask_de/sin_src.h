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

#ifndef _SIN_SRC_H_
#define _SIN_SRC_H_

#include <systemc-ams>

SCA_TDF_MODULE(sin_src)
{
  sca_tdf::sca_out<double> out; // output port

  sin_src( sc_core::sc_module_name nm, double ampl_ = 1.0, double freq_ = 1.0e7,
           sca_core::sca_time Tm_ = sca_core::sca_time(0.125, sc_core::SC_MS) );

  void set_attributes();

  void processing();

 private:
  double ampl; // amplitude
  double freq; // frequency
  sca_core::sca_time Tm; // module time step
};

#endif // _SIN_SRC_H_
