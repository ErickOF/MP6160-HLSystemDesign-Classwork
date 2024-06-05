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

#ifndef _PHONE_H_
#define _PHONE_H_

#include <systemc-ams>

SC_MODULE(phone)
{
  // terminals and ports
  sca_eln::sca_terminal tip;
  sca_eln::sca_terminal ring;
  sca_tdf::sca_in<double> voice;
  sc_core::sc_in<bool> hook;

  // electrical primitives
  sca_eln::sca_de::sca_rswitch sw1;
  sca_eln::sca_de::sca_rswitch sw2;
  sca_eln::sca_c cr, cp;
  sca_eln::sca_r rr, rs, rp;
  sca_eln::sca_tdf::sca_vsource mic;

  phone( sc_core::sc_module_name nm,
		 double cr_val = 1.0e-6,
		 double rr_val = 1.0e3,
		 double rs_val = 220.0,
		 double cp_val = 115.0e-9,
		 double rp_val = 820.0 );

 private:
  // nodes
  sca_eln::sca_node w_offhook, w_onhook, w1, w2, wring;
};  

#endif // _PHONE_H_
