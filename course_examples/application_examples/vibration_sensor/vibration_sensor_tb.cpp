//----------------------------------------------------------------------
//   Copyright 2009-2020 NXP
//   Copyright 2009-2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
//   Copyright 2015-2020 COSEDA Technologies GmbH
//   Copyright 2015-2020 LIP6 - Sorbonne Université, CNRS, LIP6
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

#include "vibration_sensor.h"
#include "vibration_source.h"
#include "sensor_frontend.h"

int sc_main(int argc, char* argv[])
{
  using namespace sc_core;
  using namespace sca_util;
  using namespace std;

  // vibration sensor transducer constant for transformation of speed into voltage
  const double k_trans = 1.0;   // V s / m

  // Resolution of the ADC
  const int NBitsADC = 5;
  
  // ADC sampling period (equal to TDF time step)
  const sc_time dt_adc(10.0, SC_US);

  // Absolute amplitude averager parameters
  const long avg_n_samples = 50;

  // Gain controller parameters
  const int amp_low_threshold = (int)(0.2 * ((1 << (NBitsADC - 1)) - 1));
  const int amp_high_threshold = (int)(0.66 * ((1 << (NBitsADC - 1)) - 1));
  const int k_0 = 8;
  const int k_min = 0;
  const int k_max = 16;

  // Supply voltages for pre-amplifier and ADC
  const double v_supply = 5.0; // V

  // Vibration test signal
  const double x_offset = -8.0e-6;   // m
  const double x_amplitude = 4.0e-6; // m
  const double x_f_0 = 2.0e3; // Hz
  const int x_n_period = 8;
  const int x_n_harmonic = 2;

  // Simulation stop time
  const sc_time t_stop(25.0, SC_MS);

  // Signals
  sca_tdf::sca_signal<double> x_sig("x_sig"), v_sig("v_sig");
  sca_tdf::sca_signal<sc_dt::sc_int<NBitsADC> > adc_sig("adc_sig");
  sc_core::sc_signal<int> k_sig("k_sig");

  // Mechanical vibration source x(t)
  vibration_source vib_src("vib_src", x_offset, x_amplitude, x_f_0, x_n_period, x_n_harmonic);
  vib_src.out(x_sig);

  // Vibration sensor with displacement input and velocity proportional voltage output
  vibration_sensor vib_sensor("vib_sensor", k_trans);
  vib_sensor.x_in(x_sig);
  vib_sensor.v_out(v_sig);

  // Sensor frontend with PGA and gain controller to use fully the dynamic range of its ADC
  sensor_frontend<NBitsADC> frontend("frontend", dt_adc, v_supply, avg_n_samples,
                                        amp_low_threshold, amp_high_threshold, k_0, k_min, k_max);
  frontend.v_in(v_sig);
  frontend.adc_out(adc_sig);
  frontend.k_out(k_sig);

  // Tracing
  sca_trace_file *tfp = sca_create_tabular_trace_file("vibration_sensor_tb");
  sca_trace(tfp, x_sig, x_sig.name());
  sca_trace(tfp, v_sig, v_sig.name());
  sca_trace(tfp, adc_sig, "adc_sig");
  sca_trace(tfp, k_sig, "k_sig");
  
  // VCD
  sca_trace_file *sensor_vcd = sca_create_vcd_trace_file("vibration_sensor_tb.vcd");
  sca_trace(sensor_vcd, x_sig, x_sig.name());
  sca_trace(sensor_vcd, v_sig, v_sig.name());
  sca_trace(sensor_vcd, adc_sig, "adc_sig");
  sca_trace(sensor_vcd, k_sig, "k_sig");

  cout << "Simulation started..." << endl;

  // Simulation
  sc_start(t_stop);

  // Close and save trace file
  sca_close_tabular_trace_file(tfp);
  
  // Close and save vcd file
  sca_close_vcd_trace_file(sensor_vcd);

  sc_stop();
  
  cout << "Simulation finished." << endl;

  return 0;
}
