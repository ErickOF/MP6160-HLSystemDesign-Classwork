//----------------------------------------------------------------------
//   Copyright 2009-2020 NXP
//   Copyright 2009-2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
//   Copyright 2015-2020 COSEDA Technologies GmbH
//   Copyright 2015-2020 Sorbonne Université, CNRS, LIP6
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

#include "programmable_gain_amplifier.h"

programmable_gain_amplifier::programmable_gain_amplifier(sc_core::sc_module_name nm, double v_supply_)
: in("in"), k_in("k_in"), out("out"), v_supply(v_supply_)
{
  sc_assert(v_supply > 0.0);
}

void programmable_gain_amplifier::processing()
{
  double k = k_in.read();
  
  // Amplify input value to output value
  double val = std::pow(2.0, k) * in.read();
  
  // Test if output saturates.
  if (val > v_supply) {
    out.write(v_supply);
  } else if (val < -v_supply) {
    out.write(-v_supply);
  } else {
    out.write(val);
  }
}
