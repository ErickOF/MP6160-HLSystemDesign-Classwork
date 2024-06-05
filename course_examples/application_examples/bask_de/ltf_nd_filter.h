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

#ifndef _LTF_ND_FILTER_H_
#define _LTF_ND_FILTER_H_

#include <systemc-ams>

SCA_TDF_MODULE(ltf_nd_filter)
{
  sca_tdf::sca_in<double> in;
  sca_tdf::sca_out<double> out;

  ltf_nd_filter( sc_core::sc_module_name nm, double fc_, double h0_ = 1.0);

  void initialize();

  void processing();

 private:
  sca_tdf::sca_ltf_nd ltf_nd; // Laplace transfer function
  sca_util::sca_vector<double> num, den; // numerator and denominator coefficients
  double fc; // 3dB cutoff frequency in Hz
  double h0; // DC gain
};

#endif // _LTF_ND_FILTER_H_
