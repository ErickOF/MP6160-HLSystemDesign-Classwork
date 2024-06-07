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

#ifndef _PROGRAMMABLE_GAIN_AMPLIFIER_H_
#define _PROGRAMMABLE_GAIN_AMPLIFIER_H_

#include <systemc-ams>

class programmable_gain_amplifier : public sca_tdf::sca_module
{
 public:
  sca_tdf::sca_in<double> in;
  sca_tdf::sca_de::sca_in<int> k_in;
  sca_tdf::sca_out<double> out;

  programmable_gain_amplifier(sc_core::sc_module_name nm, double v_supply_);

  void processing();

 private:
  const double v_supply; // Supply voltage limiting output
};

#endif // _PROGRAMMABLE_GAIN_AMPLIFIER_H_
