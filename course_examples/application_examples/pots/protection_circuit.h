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

#ifndef _PROTECTION_CIRCUIT_H_
#define _PROTECTION_CIRCUIT_H_

#include <systemc-ams>

SC_MODULE(protection_circuit)
{
  // terminals
  sca_eln::sca_terminal tip_slic;
  sca_eln::sca_terminal ring_slic;
  sca_eln::sca_terminal tip;
  sca_eln::sca_terminal ring;

  // electrical primitives
  sca_eln::sca_r rprot1, rprot2, rprot3, rprot4;
  sca_eln::sca_c cprot1, cprot2;

  protection_circuit( sc_core::sc_module_name,
    double rprot1_val = 20.0,
    double rprot2_val = 20.0,
    double rprot3_val = 20.0,
    double rprot4_val = 20.0,
    double cprot1_val = 18.0e-9,
    double cprot2_val = 18.0e-9 );

 private:
  // nodes
  sca_eln::sca_node n_tip, n_ring;
  sca_eln::sca_node_ref gnd;
};

#endif // _PROTECTION_CIRCUIT_H_
