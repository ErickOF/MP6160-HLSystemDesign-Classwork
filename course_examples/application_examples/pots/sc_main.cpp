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

#include "sinewave.h"
#include "phone.h"
#include "protection_circuit.h"
#include "slic.h"

int sc_main(int argc,char* argv[])
{
  sc_core::sc_set_time_resolution(1.0, sc_core::SC_FS);

  sca_eln::sca_node n_slic_tip("n_slic_tip"), n_slic_ring("n_slic_ring");
  sca_eln::sca_node n_tip_a1("n_tip_a1"), n_tip_b1("n_tip_b1"), n_ring_a2("n_ring_a2"), n_ring_b2("n_ring_b2");

  sca_tdf::sca_signal<double> s_v_tip_ring("s_v_tip_ring");
  sca_tdf::sca_signal<double> s_i_trans("s_i_trans");
  sca_tdf::sca_signal<double> s_voice("s_voice");

  sc_core::sc_signal<bool> s_hook("s_hook");

  sinewave::params p_src_vtr;
    p_src_vtr.ampl=0.0;
    p_src_vtr.offset=10.0;  //dc offset
    p_src_vtr.freq=1e3;

  sinewave src_vtr("src_vtr",p_src_vtr);
    src_vtr.outp(s_v_tip_ring);

  slic i_slic("i_slic");
    i_slic.tip(n_slic_tip);
    i_slic.ring(n_slic_ring);
    i_slic.v2w(s_v_tip_ring);
    i_slic.i_trans(s_i_trans);

  protection_circuit i_protection_circuit("i_protection_circuit");
    i_protection_circuit.tip_slic(n_slic_tip);
    i_protection_circuit.ring_slic(n_slic_ring);
    i_protection_circuit.tip(n_tip_a1);
    i_protection_circuit.ring(n_ring_a2);
 
  sca_eln::sca_transmission_line i_transmission_line("i_transmission_line", 
                                                     50.0, sc_core::sc_time(1.0,sc_core::SC_US), 0.0);
    i_transmission_line.a1(n_tip_a1);
    i_transmission_line.a2(n_ring_a2);
    i_transmission_line.b1(n_tip_b1);
    i_transmission_line.b2(n_ring_b2);

  phone i_phone("i_phone");
    i_phone.tip(n_tip_b1);
    i_phone.ring(n_ring_b2);
    i_phone.voice(s_voice);
    i_phone.hook(s_hook);


  sinewave::params p_src_voice;
    p_src_voice.ampl=1.0;
    p_src_voice.offset=0.0;
    p_src_voice.freq=1e3;

  sinewave src_voice("src_voice", p_src_voice);
    src_voice.outp(s_voice);

  //////////////////////////////////////////////////////////////////////////////

  // trace signals, nodes and current
  sca_util::sca_trace_file* tf = sca_util::sca_create_tabular_trace_file("pots_fe.dat");
  sca_util::sca_trace(tf, n_tip_b1,"n_tip_b1");
  sca_util::sca_trace(tf, n_ring_b2,"n_ring_b2");
  sca_util::sca_trace(tf, n_slic_tip,"n_slic_tip");
  sca_util::sca_trace(tf, n_slic_ring,"n_slic_ring");
  sca_util::sca_trace(tf, s_i_trans,"s_i_trans");
  sca_util::sca_trace(tf, s_voice,"s_voice");
  sca_util::sca_trace(tf, s_v_tip_ring,"s_v_tip_ring");
  sca_util::sca_trace(tf, i_phone.rr,"i_phone.i_rr");
  sca_util::sca_trace(tf, i_phone.rs,"i_phone.i_rs");

  //////////////////////////////////////////////////////////////////////////////

  // send signal from  phone
  src_voice.p.ampl = 1.0;
  src_voice.p.freq = 1.0e3;
  src_vtr.p.ampl = 0.0;

  s_hook.write(false);  // set subscriber onhook

  std::cout << "Simulation started..." << std::endl;

  // simulate 5ms
  sc_core::sc_start(5.0, sc_core::SC_MS);

  s_hook.write(true);  // set subscriber offhook

  // simulate 5ms
  sc_core::sc_start(5.0, sc_core::SC_MS);

  // send signal from central office to phone
  src_voice.p.ampl = 0.0;
  src_vtr.p.ampl = 1.0;
  src_vtr.p.freq = 1.0e3;

  // simulate 5ms
  sc_core::sc_start(5.0, sc_core::SC_MS);

  s_hook.write(false);  // set subscriber onhook

  // simulate 5ms
  sc_core::sc_start(5.0, sc_core::SC_MS);

  // send signal from phone and central office
  src_voice.p.ampl = 1.0;
  src_voice.p.freq = 1.0e3;
  src_vtr.p.ampl = 1.0;
  src_vtr.p.freq = 1.33e3;

  // simulate 5ms
  sc_core::sc_start(5.0, sc_core::SC_MS);

  s_hook.write(true);  // set subscriber offhook

  // send signal from phone and central office
  src_voice.p.ampl = 1.0;
  src_voice.p.freq = 1.0e3;
  src_vtr.p.ampl = 1.0;
  src_vtr.p.freq = 1.33e3;

  // simulate 5ms
  sc_core::sc_start(5.0, sc_core::SC_MS);

  // let the phone ring (large 50Hz signal from central office)
  src_voice.p.ampl = 0.0;
  src_vtr.p.ampl = 10.0;
  src_vtr.p.freq = 50.0;

  // simulate 100ms
  sc_core::sc_start(100.0, sc_core::SC_MS);

  s_hook.write(false);  // set subscriber onhook

  // simulate 100ms
  sc_core::sc_start(100.0, sc_core::SC_MS);

  // re-direct tracing to a new file
  tf->reopen("pots_fe_ac_on_vtr.dat");

  // set ac tracing to the DB / DEG format
  tf->set_mode(sca_util::sca_ac_format(sca_util::SCA_AC_DB_DEG));

  // send signal from central office
  src_voice.p.ampl = 0.0;
  src_vtr.p.ampl = 1.0;

  // perform ac simulation from 10Hz to 64kHz with 1000 logarithmically spaced points
  // -> transfer functions from central office to all signals and nodes is calculated for onhook
  //    and stored in pots_fe_ac_on_vtr.dat
  sca_ac_analysis::sca_ac_start(10.0, 64e3, 1000, sca_ac_analysis::SCA_LOG);

  // re-direct tracing to a new file
  tf->reopen("pots_fe_ac_on_voice.dat");

  // send signal from phone (no signal from central office)
  src_voice.p.ampl = 1.0;
  src_vtr.p.ampl = 0.0;

  // perform ac simulation from 10Hz to 64kHz with 1000 logarithmically spaced points
  // -> transfer functions from phone to all signals and nodes is calculated for onhook
  //    and stored in pots_fe_ac_on_voice.dat
  sca_ac_analysis::sca_ac_start(10.0, 64e3, 1000, sca_ac_analysis::SCA_LOG);

  // tracing disabled to prevent writing to the AC file
  tf->disable();

  // alternatively continue the tracing (append) to the time domain file
  // tf->reopen("pots_fe.dat",std::ios::app);
  s_hook.write(true);  // set subscriber offhook

  // simulate 1ms to propagate signal
  sc_core::sc_start(1.0, sc_core::SC_MS);

  // send signal from central office
  src_voice.p.ampl = 0.0;
  src_vtr.p.ampl = 1.0;

  // re-direct tracing to a new file
  tf->reopen("pots_fe_ac_off_vtr.dat");

  // enable tracing
  tf->enable();

  // perform ac simulation from 10Hz to 64kHz with 1000 logarithmically spaced points
  // -> transfer functions from central office to all signals and nodes is calculated for offhook
  //    and stored in pots_fe_ac_off_vtr.dat
  sca_ac_analysis::sca_ac_start(10.0, 64e3,1000, sca_ac_analysis::SCA_LOG);

  // re-direct tracing to a new file
  tf->reopen("pots_fe_ac_off_voice.dat");

  // send signal from phone
  src_voice.p.ampl = 1.0;
  src_vtr.p.ampl = 0.0;

  // perform ac simulation from 10Hz to 64kHz with 1000 logarithmically spaced points
  // -> transfer functions from phone to all signals and nodes is calculated for offhook
  //    and stored in pots_fe_ac_off_voice.dat
  sca_ac_analysis::sca_ac_start(10.0, 64e3, 1000, sca_ac_analysis::SCA_LOG);

  sc_core::sc_stop(); // stop simulation -> end_of_simulation callbacks called

  std::cout << sc_core::sc_time_stamp() << " simulation finished." << std::endl;

  sca_util::sca_close_vcd_trace_file(tf);

  return 0;
};
