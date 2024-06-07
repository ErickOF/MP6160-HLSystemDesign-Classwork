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

#include "bask_mod_de.h"

bask_mod_de::bask_mod_de( sc_core::sc_module_name nm )
: in("in"),out("out"),
  sine("sine", 1.0 , 1.0e7, sca_core::sca_time( 5.0, sc_core::SC_NS ) ),
  mix("mix")
{
  sine.out(carrier);
  mix.in_wav(carrier);
  mix.in_bin(in);
  mix.out(out);
}
