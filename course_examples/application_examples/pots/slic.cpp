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

#include "slic.h"

slic::slic( sc_core::sc_module_name nm,
  double scale_v_tr,
  double scale_i_tr ) : tip("tip"), ring("ring"), v2w("v2w"), i_trans("i_trans"),
  driver1("driver1", scale_v_tr/2.0),
  driver2("driver2", -scale_v_tr/2.0),
  itr_meas("itr_meas", scale_i_tr),
  mirror1("mirror1", 0.5), mirror2("mirror2", -0.5), rtr("rtr", 1.0),
  n_tr_i("n_tr_i"), n_tip_gnd("n_tip_gnd"), n_ring_gnd("n_ring_gnd"),
  gnd("gnd")
{
  // architecture
  driver1.inp(v2w);
  driver1.p(tip);
  driver1.n(n_tip_gnd);

  driver2.inp(v2w);
  driver2.p(ring);
  driver2.n(n_ring_gnd);

  mirror1.ncp(n_tip_gnd);
  mirror1.ncn(gnd);
  mirror1.np(n_tr_i);
  mirror1.nn(gnd);

  mirror2.ncp(n_ring_gnd);
  mirror2.ncn(gnd);
  mirror2.np(n_tr_i);
  mirror2.nn(gnd);

  rtr.p(n_tr_i);
  rtr.n(gnd);

  itr_meas.p(n_tr_i);
  itr_meas.n(gnd);
  itr_meas.outp(i_trans);
}
