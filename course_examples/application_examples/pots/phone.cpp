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

#include "phone.h"

phone::phone( sc_core::sc_module_name nm,
  double cr_val,
  double rr_val,
  double rs_val,
  double cp_val,
  double rp_val )
: tip("tip"), ring("ring"), voice("voice"), hook("hook"),
  sw1("sw1"), sw2("sw2"), cr("cr", cr_val), cp("cp", cp_val),
  rr("rr", rr_val), rs("rs", rs_val), rp("rp", rp_val), mic("mic"),
  w_offhook("w_offhook"), w_onhook("w_onhook"), w1("w1"), w2("w2"), wring("wring")
{
  // architecture
  sw1.p(tip);
  sw1.n(w_onhook);
  sw1.ctrl(hook);
  sw1.off_state = true;
  sw1.ron=1e-3;
  sw1.roff=1e7;

  sw2.p(tip);
  sw2.n(w_offhook);
  sw2.ctrl(hook);
  sw2.ron=1e-3;
  sw2.roff=1e7;

  cr.p(wring);
  cr.n(w_onhook);

  rr.p(wring);
  rr.n(ring);

  rs.p(w1);
  rs.n(w2);

  cp.p(w1);
  cp.n(w_offhook);

  rp.p(w_offhook);
  rp.n(w1);

  mic.p(w2);
  mic.n(ring);
  mic.inp(voice);
}
