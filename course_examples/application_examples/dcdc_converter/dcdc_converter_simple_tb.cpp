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

#include <systemc-ams>

#include "dcdc_converter.h"
#include "const_src.h"

int sc_main(int argc, char* argv[])
{
  sc_core::sc_set_time_resolution(1.0, sc_core::SC_FS);

  ////////////////////////////////////////////////////////////////////////////
  // signal declarations                                                    //
  ////////////////////////////////////////////////////////////////////////////

  sca_tdf::sca_signal<double> input_s("input_s");
  sca_tdf::sca_signal<double> vsupply_s("vsupply_s");
  sca_tdf::sca_signal<double> vref_s("vref_s");
  sca_tdf::sca_signal<double> vout_s("vout_s");
  sc_core::sc_signal<double> rload_s("rload_s");

  sca_eln::sca_node n_out("n_out");
  sca_eln::sca_node_ref gnd("gnd");

  const_src i_const_vsupp("i_const_vsupp");
  i_const_vsupp.value = 42.0;
  i_const_vsupp.outp(vsupply_s);

  const_src i_const_vref("i_const_vref");
  i_const_vref.value = 4.8;
  i_const_vref.outp(vref_s); //output port

  dcdc_converter dut("dut", 5.0e-3, 10.0e-6, sca_core::sca_time(0.7777, sc_core::SC_US));
  dut.vref(vref_s);
  dut.vsupply(vsupply_s);
  dut.vout(n_out);

  //load resitance
  sca_eln::sca_de_r i_sca_de_rload("i_sca_de_rload");
  i_sca_de_rload.scale = 1.0;
  i_sca_de_rload.p(n_out);
  i_sca_de_rload.n(gnd);
  i_sca_de_rload.inp(rload_s);

  // trace signals                                                          //

  sca_util::sca_trace_file *tf = sca_util::sca_create_tabular_trace_file(
      "dcdc_converter_trace.dat");
  sca_util::sca_trace(tf, n_out, "vout");
  sca_util::sca_trace(tf, i_sca_de_rload, "iout");
  sca_util::sca_trace(tf, vsupply_s, "vsupply");
  sca_util::sca_trace(tf, vref_s, "vref");
  
  // vcd trace signals                                                          //

  sca_util::sca_trace_file *dcdc_vcd = sca_util::sca_create_vcd_trace_file(
      "dcdc_converter_trace.vcd");
  sca_util::sca_trace(dcdc_vcd, n_out, "vout");
  sca_util::sca_trace(dcdc_vcd, i_sca_de_rload, "iout");
  sca_util::sca_trace(dcdc_vcd, vsupply_s, "vsupply");
  sca_util::sca_trace(dcdc_vcd, vref_s, "vref");

  ////////////////////////////////////////////////////////////////////////////
  // time domain simulation                                                 //
  ////////////////////////////////////////////////////////////////////////////

  std::cout << "Simulation started..." << std::endl;

  //set load resistance to 2.4 Ohm
  rload_s.write(2.4);

  //run 25ms
  sc_core::sc_start(25.0, sc_core::SC_MS);

  //set load resistance to 5 Ohm
  rload_s.write(5.0);

  //run 15 ms
  sc_core::sc_start(15.0, sc_core::SC_MS);

  //stop simulation - print statistics
  sc_core::sc_stop();

  std::cout << "Simulation finished." << std::endl;

  return 0;
}
