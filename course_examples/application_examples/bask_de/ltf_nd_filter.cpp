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

#include "ltf_nd_filter.h"

ltf_nd_filter::ltf_nd_filter( sc_core::sc_module_name nm, double fc_, double h0_)
: in("in"), out("out"), fc(fc_), h0(h0_)
{}

void ltf_nd_filter::initialize()
{
  num(0) = 1.0;
  den(0) = 1.0;
  den(1) = 1.0 /( 2.0* M_PI * fc );
}
 
void ltf_nd_filter::processing()
{
  double tmp = ltf_nd( num, den, in.read(), h0 );
  out.write(tmp);
}
