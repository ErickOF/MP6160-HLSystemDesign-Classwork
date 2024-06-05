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

#ifndef _COMPENSATOR_H_
#define _COMPENSATOR_H_

#include <systemc-ams>

SCA_TDF_MODULE(compensator)
{
  // sca tdf ports
  sca_tdf::sca_in<double > inp;
  sca_tdf::sca_in<double> ref;
  sca_tdf::sca_out<double> outp;

  void initialize();
  void processing();

  // constructor
  compensator(sc_core::sc_module_name nm, double fz1_ = 806.0/2.0,
    double fz2_ = 806.0/2.0, double fp1_ = 7.5e3, double fp2_ = 531.0e3,
    double gain_ = 100.0);

  // parameters
  double fz1, fz2, fp1, fp2, gain;

private:
  //vectors for filter coefficients
  sca_util::sca_vector<sca_util::sca_complex> zeros, poles;
  double scale;

  //object for filter function
  sca_tdf::sca_ltf_zp ltfzp;
};

#endif // _COMPENSATOR_H_
