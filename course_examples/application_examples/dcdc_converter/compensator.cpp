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

#include "compensator.h"


void compensator::initialize()
{
  // linear transfer function - zeros coefficients
  zeros(0) = -2.0 * M_PI * fz1;
  zeros(1) = -2.0 * M_PI * fz2;

  // linear transfer function - poles coefficients
  poles(0) = -2.0 * M_PI * fp1;
  poles(1) = -2.0 * M_PI * fp2;
  poles(2) = 0.0;

  // scale due SystemC zp uses (s-k) like Matlab and Verilog-AMS (1-s/k)
  scale = fp1 * fp2 / fz1 / fz2 * gain;
}

void compensator::processing()
{
  outp = -scale * ltfzp(zeros, poles, inp - ref);
}

// constructor
compensator::compensator(sc_core::sc_module_name nm,
  double fz1_,
  double fz2_,
  double fp1_,
  double fp2_,
  double gain_ )
: inp("inp"),
  ref("ref"),
  outp("outp"),
  fz1(fz1_),
  fz2(fz2_),
  fp1(fp1_),
  fp2(fp2_),
  gain(gain_)
{
  accept_attribute_changes();
}
