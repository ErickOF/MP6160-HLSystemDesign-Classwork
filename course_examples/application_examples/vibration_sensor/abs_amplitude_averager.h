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

#ifndef _ABS_AMPLITUDE_AVERAGER_H_
#define _ABS_AMPLITUDE_AVERAGER_H_

#include <systemc-ams>

template<int NBits>
class abs_amplitude_averager : public sca_tdf::sca_module
{
 public:
  sca_tdf::sca_in<sc_dt::sc_int<NBits> > in;
  sca_tdf::sca_de::sca_out<bool> clk;
  sca_tdf::sca_de::sca_out<sc_dt::sc_int<NBits> > out;

  explicit abs_amplitude_averager(sc_core::sc_module_name nm, long n_samples_);

  void set_attributes();

  void initialize();

  void processing();

 private:
  const long n_samples; // Number of averaged samples
};


template<int NBits>
abs_amplitude_averager<NBits>::abs_amplitude_averager(sc_core::sc_module_name nm,
  long n_samples_)
: in("in"), clk("clk"), out("out"), n_samples(n_samples_)
{
  sc_assert((2 <= NBits) && (NBits <= 64));
  sc_assert(n_samples_ > 0);
}

template<int NBits>
void abs_amplitude_averager<NBits>::set_attributes()
{
  in.set_rate(n_samples);
  clk.set_rate(2);
  clk.set_delay(2);
  out.set_rate(1);
  out.set_delay(1);
}

template<int NBits>
void abs_amplitude_averager<NBits>::initialize()
{
  clk.initialize(true, 0);
  clk.initialize(false, 1);
  out.initialize(0);
}

template<int NBits>
void abs_amplitude_averager<NBits>::processing()
{
  // Generate clock signal
  clk.write(true, 0);
  clk.write(false, 1);

  // Calculate and output average of absolute amplitudes
  long sum = 0;
  for (long i = 0; i < n_samples; ++i) {
    sum += std::labs((long)in.read(i));
  }

  long avg = sum / n_samples;
  out.write(avg);
}

#endif // _ABS_AMPLITUDE_AVERAGER_H_
