//----------------------------------------------------------------------
//   Copyright 2009-2020 NXP
//   Copyright 2009 Vienna University of Technology
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

#ifndef _BASK_DEMOD_DE_H_
#define _BASK_DEMOD_DE_H_

#include <systemc-ams>

#include "rectifier.h"
#include "ltf_nd_filter.h"
#include "sampler_de.h"

SC_MODULE(bask_demod_de)
{
  sca_tdf::sca_in<double> in;
  sc_core::sc_out<bool>   out;
	
  rectifier     rc;
  ltf_nd_filter lp;
  sampler_de    sp;

  SCA_CTOR(bask_demod_de);

 private:
  sca_tdf::sca_signal<double> rc_out, lp_out;
};

#endif // _BASK_DEMOD_DE_H_
