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

#ifndef _CTSD_LOOP_FILTER_H_
#define _CTSD_LOOP_FILTER_H_

#include <systemc>
#include <systemc-ams>

SC_MODULE(ctsd_loop_filter)
{
  sca_lsf::sca_in x;
  sca_tdf::sca_out<double> v;
  sca_tdf::sca_in<double> w;

  sca_lsf::sca_tdf::sca_source tdf2lsf;
  sca_lsf::sca_sub sub1;
  sca_lsf::sca_integ integ1, integ2, integ3;
  sca_lsf::sca_gain gain2, gain3;
  sca_lsf::sca_add add1, add2;
  sca_lsf::sca_tdf::sca_sink lsf2tdf;

  ctsd_loop_filter( sc_core::sc_module_name, double k1, double k2, double k3 );

  void trace_diff( sca_util::sca_trace_file* tf );

 private:
  sca_lsf::sca_signal sig_t, sig_i, sig_i1, sig_i2, sig_i3;
  sca_lsf::sca_signal sig_a1, sig_a2, sig_a3, sig_u;
};

#endif // _CTSD_LOOP_FILTER_H_
