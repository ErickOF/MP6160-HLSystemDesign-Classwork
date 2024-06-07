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

#ifndef _GAIN_CONTROLLER_H_
#define _GAIN_CONTROLLER_H_

#include <systemc-ams>

template<int NBits>
class gain_controller : public sc_core::sc_module
{
 public:
  sc_core::sc_in<bool> clk;
  sc_core::sc_in<sc_dt::sc_int<NBits> > amp_in;
  sc_core::sc_out<int> k_out;

  SC_HAS_PROCESS(gain_controller);
  
  explicit gain_controller(sc_core::sc_module_name nm,
                           int low_threshold_ = 0.2 * ((1 << (NBits - 1)) - 1),
                           int high_threshold_ = 0.8 * ((1 << (NBits - 1)) - 1),
                           int k_0_ = 0, int k_min_ = 0, int k_max_ = 16);

  void gain_fsm();

 private:
  const int low_threshold;     // Low threshold for amplitude to increase gain
  const int high_threshold;    // High threshold for amplitude to lower gain
  const int k_min;             // Minimum gain power
  const int k_max;             // Maximum gain power

  enum state_type {KEEP_GAIN, INCREASE_GAIN, DECREASE_GAIN};
  
  state_type state;            // Current state
  int k;                       // Current gain power
};

template<int NBits>
gain_controller<NBits>::gain_controller(sc_core::sc_module_name nm,
 int low_threshold_,
 int high_threshold_,
 int k_0_,
 int k_min_,
 int k_max_)
: clk("clk"), amp_in("amp_in"), k_out("k_out"),
  low_threshold(low_threshold_), high_threshold(high_threshold_),
  k_min(k_min_), k_max(k_max_), state(KEEP_GAIN), k(k_0_)
{
  sc_assert(low_threshold_ > 0);
  sc_assert(low_threshold_ < high_threshold_);
  sc_assert(high_threshold_ < ((1 << (NBits - 1)) - 1));
  sc_assert(k_min_ < k_max_);
  sc_assert(k_min_ <= k_0_ && k_0_ <= k_max_);

  SC_METHOD(gain_fsm);
  sensitive << clk.pos();
}

template<int NBits>
void gain_controller<NBits>::gain_fsm()
{
  switch (state) {
  case KEEP_GAIN:
    if (amp_in.read() < low_threshold) {
      state = INCREASE_GAIN;
      ++k;
    } else if (amp_in.read() >= high_threshold) {
      state = DECREASE_GAIN;
      --k;
    }
    break;
  case INCREASE_GAIN:
    if (amp_in.read() < high_threshold) {
      ++k;
    } else {
      state = DECREASE_GAIN;
      --k;
    }
    break;
  case DECREASE_GAIN:
    if (amp_in.read() < high_threshold) {
      state = KEEP_GAIN;
    } else {
      --k;
    }
    break;
  default:
    SC_REPORT_ERROR("/vibration_sensor/gain_controller", "Unexpected state.");
  }

  // Limit and set new gain
  if (k < k_min) { k = k_min; }
  if (k > k_max) { k = k_max; }
  k_out.write(k);
}

#endif // _GAIN_CONTROLLER_H_
