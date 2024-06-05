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

#include <systemc-ams>

#include "bask_mod.h"
#include "bask_demod.h"
#include "bit_src.h"

int sc_main(int argc, char* argv[])
{
  sc_core::sc_set_time_resolution(1.0, sc_core::SC_FS);

  sca_util::sca_information_off();
  
  sca_tdf::sca_signal<bool> in_bits, out_bits;
  sca_tdf::sca_signal<double> wave;

  bit_src bs("bs"); // random bit source
    bs.out(in_bits);

  bask_mod mod("mod"); // modulator
    mod.in(in_bits);
    mod.out(wave);

  bask_demod demod("demod"); // demodulator
    demod.in(wave);
    demod.out(out_bits);

  // tracing
  sca_util::sca_trace_file* atf = sca_util::sca_create_vcd_trace_file( "tr.vcd" );
  sca_util::sca_trace( atf, in_bits, "in_bits" );
  sca_util::sca_trace( atf, wave, "wave" );
  sca_util::sca_trace( atf, out_bits, "out_bits" );

  std::cout << "Simulation started..." << std::endl;

  sc_core::sc_start(1, sc_core::SC_US);

  std::cout << "Simulation finished." << std::endl;

  sca_util::sca_close_vcd_trace_file( atf );

  return 0;
}
