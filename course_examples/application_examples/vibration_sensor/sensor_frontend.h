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

#ifndef _SENSOR_FRONTEND_H_
#define _SENSOR_FRONTEND_H_

#include <systemc-ams>

#include "programmable_gain_amplifier.h"
#include "ad_converter.h"
#include "abs_amplitude_averager.h"
#include "gain_controller.h"

template<int NBitsADC>
class sensor_frontend : public sc_core::sc_module
{
 public:
  sca_tdf::sca_in<double> v_in;
  sca_tdf::sca_out<sc_dt::sc_int<NBitsADC> > adc_out;
  sc_core::sc_out<int> k_out;

  sensor_frontend(sc_core::sc_module_name nm,
    sca_core::sca_time dt_adc_,
    double v_supply_,
    long avg_n_samples_,
    int amp_low_threshold_,
    int amp_high_threshold_,
    int k_0_,
    int k_min_,
    int k_max_);

 private:
  sca_tdf::sca_signal<double> v_amp_sig;
  sc_core::sc_signal<bool> clk_sig;
  sc_core::sc_signal<sc_dt::sc_int<NBitsADC> > amp_sig;

  programmable_gain_amplifier pga_1;
  ad_converter<NBitsADC> adc_1;
  abs_amplitude_averager<NBitsADC> avg_1;
  gain_controller<NBitsADC> gain_ctrl_1;
};


template<int NBitsADC>
sensor_frontend<NBitsADC>::sensor_frontend(
  sc_core::sc_module_name nm,
  sca_core::sca_time dt_adc_,
  double v_supply_,
  long avg_n_samples_,
  int amp_low_threshold_,
  int amp_high_threshold_,
  int k_0_,
  int k_min_,
  int k_max_)
: v_in("v_in"),
  adc_out("adc_out"),
  k_out("k_out"),
  v_amp_sig("v_amp_sig"),
  clk_sig("clk_sig"),
  amp_sig("amp_sig"),
  pga_1("pga_1", v_supply_),
  adc_1("adc_1", v_supply_),
  avg_1("avg_1", avg_n_samples_),
  gain_ctrl_1("gain_ctrl_1", amp_low_threshold_, amp_high_threshold_, k_0_, k_min_, k_max_)
{
  // netlist
  pga_1.in(v_in);
  pga_1.k_in(k_out);
  pga_1.out(v_amp_sig);

  adc_1.set_timestep(dt_adc_);
  adc_1.in(v_amp_sig);
  adc_1.out(adc_out);

  avg_1.in(adc_out);
  avg_1.clk(clk_sig);
  avg_1.out(amp_sig);

  gain_ctrl_1.clk(clk_sig);
  gain_ctrl_1.amp_in(amp_sig);
  gain_ctrl_1.k_out(k_out);
}

#endif // _SENSOR_FRONTEND_H_
