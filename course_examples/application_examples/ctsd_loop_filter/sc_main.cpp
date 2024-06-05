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

#include <systemc>
#include <systemc-ams>

#include "quantizer.h"
#include "dac.h"
#include "ctsd_loop_filter.h"

int sc_main(int argc, char* argv[])
{
  sc_core::sc_set_time_resolution(1.0, sc_core::SC_FS);
  
  sca_lsf::sca_signal s_x;
  sca_tdf::sca_signal<double> s_v, s_w;
  sca_tdf::sca_signal<bool> s_y;
  
  double vref = 2.0;
  double freq = 1e3; // 1kHz
  
  // module instantiation
  sca_lsf::sca_source lsf_source("lsf_source1", 0.0, 0.0, vref, freq );
  quantizer quant1("quant1");
  dac dac1("dac1", vref);
  ctsd_loop_filter lf("lf", 1.0, 1.0, 1.0); 

  // bindings
  lsf_source.y(s_x);
  lsf_source.set_timestep(1.0, sc_core::SC_US);

  lf.x(s_x);
  lf.v(s_v);
  lf.w(s_w);

  quant1.in(s_v);
  quant1.out(s_y);
  
  dac1.in(s_y);
  dac1.out(s_w);
  
  // VCD tracing
  sca_util::sca_trace_file* tf = sca_util::sca_create_vcd_trace_file("ctsd_loop_filter");
  sca_util::sca_trace(tf,s_x,"s_x");
  lf.trace_diff(tf); // difference signal s_d is an internal/private signal 
  sca_util::sca_trace(tf,s_v,"s_v");
  sca_util::sca_trace(tf,s_y,"s_y");
  sca_util::sca_trace(tf,s_w,"s_w");

  // tabular trace format
  sca_util::sca_trace_file* tft = sca_util::sca_create_tabular_trace_file("ctsd_loop_filter");
  sca_util::sca_trace(tft,s_x,"s_x");
  lf.trace_diff(tft); // difference signal s_d is an internal/private signal
  sca_util::sca_trace(tft,s_v,"s_v");
  sca_util::sca_trace(tft,s_y,"s_y");
  sca_util::sca_trace(tft,s_w,"s_w");

  std::cout << "Simulation started..." << std::endl;

  sc_core::sc_start(2, sc_core::SC_MS);
  
  std::cout << "Simulation finished." << std::endl;

  sca_util::sca_close_vcd_trace_file(tf);
  sca_util::sca_close_tabular_trace_file(tft);
  
  return 0;
}
