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

#ifndef _AD_CONVERTER_H_
#define _AD_CONVERTER_H_

#include <systemc-ams>

template<int NBits>
class ad_converter : public sca_tdf::sca_module
{
 public:
  sca_tdf::sca_in<double> in;
  sca_tdf::sca_out<sc_dt::sc_int<NBits> > out;

  ad_converter(sc_core::sc_module_name nm, double v_max_);

  void processing();

 private:
  const double v_max;
};


template<int NBits>
ad_converter<NBits>::ad_converter(sc_core::sc_module_name nm, double v_max_)
: in("in"), out("out"), v_max(v_max_)
{
  sc_assert((2 <= NBits) && (NBits <= 64));
  sc_assert(v_max_ > 0.0);
}

template<int NBits>
void ad_converter<NBits>::processing()
{
  using namespace std;

  double v_in = in.read();

  if (v_in < -v_max) {
    out.write(-((1 << (NBits - 1)) - 1));
  } else if (v_in > v_max) {
    out.write((1 << (NBits - 1)) - 1);
  } else {
    sc_dt::sc_int<NBits>
    q_v_in = lround((v_in / v_max) * ((1 << (NBits - 1)) - 1));
    out.write(q_v_in);
  }
}

#endif // _AD_CONVERTER_H_
