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

#include "ctsd_loop_filter.h"

ctsd_loop_filter::ctsd_loop_filter( sc_core::sc_module_name nm, double k1, double k2, double k3 )
: x("x"), v("v"), w("w"), tdf2lsf("tdf2lsf"), sub1("sub1"), integ1("integ1", k1), integ2("integ2"),
  integ3("integ3"), gain2("gain2", k2), gain3("gain3", k3), add1("add1"), add2("add2"),
  lsf2tdf("lsf2tdf"), sig_t("sig_t"), sig_i("sig_1"), sig_i1("sig_i1"), sig_i2("sig_i2"),
  sig_i3("sig_i3"), sig_a1("sig_a1"), sig_a2("sig_a2"), sig_a3("sig_a3"), sig_u("sig_u")
{
  tdf2lsf.inp(w);
  tdf2lsf.y(sig_t);

  sub1.x1(x);
  sub1.x2(sig_t);
  sub1.y(sig_i);

  integ3.x(sig_i);
  integ3.y(sig_i3);

  integ2.x(sig_i3);
  integ2.y(sig_i2);

  integ1.x(sig_i2);
  integ1.y(sig_i1);

  gain3.x(sig_i3);
  gain3.y(sig_a1);

  gain2.x(sig_i2);
  gain2.y(sig_a2);

  add1.x1(sig_a1);
  add1.x2(sig_a2);
  add1.y(sig_a3);

  add2.x1(sig_a3);
  add2.x2(sig_i1);
  add2.y(sig_u);

  lsf2tdf.x(sig_u);
  lsf2tdf.outp(v);
}

void ctsd_loop_filter::trace_diff( sca_util::sca_trace_file* tf )
{
  sca_util::sca_trace(tf,sig_i,"s_d");
}

