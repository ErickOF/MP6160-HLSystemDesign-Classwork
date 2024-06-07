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

#ifndef _SLIC_H_
#define _SLIC_H_

#include <systemc-ams>

SC_MODULE(slic)
{
  // terminals and ports
  sca_eln::sca_terminal tip;
  sca_eln::sca_terminal ring;
  sca_tdf::sca_in<double> v2w;
  sca_tdf::sca_out<double> i_trans;

  // electrical primitives
  sca_eln::sca_tdf::sca_vsource driver1, driver2;
  sca_eln::sca_tdf::sca_vsink itr_meas;
  sca_eln::sca_cccs mirror1, mirror2;
  sca_eln::sca_r rtr;

  slic( sc_core::sc_module_name nm,
    double scale_v_tr = 1.0,
    double scale_i_tr = 1.0 );

 private:
  // nodes
  sca_eln::sca_node n_tr_i, n_tip_gnd, n_ring_gnd;
  sca_eln::sca_node_ref gnd;
};

#endif // _SLIC_H_
