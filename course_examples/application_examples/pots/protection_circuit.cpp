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

#include "protection_circuit.h"

protection_circuit::protection_circuit( sc_core::sc_module_name nm,
		                                double rprot1_val,
		                                double rprot2_val,
                                        double rprot3_val,
                                        double rprot4_val,
                                        double cprot1_val,
                                        double cprot2_val )
: tip_slic("tip_slic"), ring_slic("ring_slic"), tip("tip"), ring("ring"),
  rprot1("rprot1", rprot1_val), rprot2("rprot2", rprot2_val),
  rprot3("rprot3", rprot3_val), rprot4("rprot4", rprot4_val),
  cprot1("cprot1", cprot1_val), cprot2("cprot2", cprot2_val),
  n_tip("n_tip"), n_ring("n_ring"), gnd("gnd")
{
  // architecture
  rprot1.p(tip);
  rprot1.n(n_tip);

  rprot2.p(tip_slic);
  rprot2.n(n_tip);

  cprot1.p(n_tip);
  cprot1.n(gnd);

  rprot3.p(ring);
  rprot3.n(n_ring);

  rprot4.p(ring_slic);
  rprot4.n(n_ring);

  cprot2.p(n_ring);
  cprot2.n(gnd);
}
