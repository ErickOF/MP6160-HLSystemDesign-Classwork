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

#ifndef _DIODE_H_
#define _DIODE_H_

#include <systemc-ams>
#include "diode_dtdf.h"

SC_MODULE(diode)
{
  // ports
  sca_eln::sca_terminal np;
  sca_eln::sca_terminal nn;

  // components
  diode_dtdf i_diode_characteristic;
  sca_eln::sca_tdf_vsource i_vth;
  sca_eln::sca_tdf_vsink i_vdiode2tdf;
  sca_eln::sca_tdf_r i_rdiode;

  diode(sc_core::sc_module_name name, double vth_p_ = 0.7, double ron_ = 1e-3, double roff_ = 1e9);

 private:
  //declare node and signal references for external access
  sca_tdf::sca_signal<double> s_rout;
  sca_tdf::sca_signal<double> s_vth;
  sca_eln::sca_node n_rdiode;
  sca_tdf::sca_signal<double> s_vdiode;
};

#endif // _DIODE_H_
