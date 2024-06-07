//----------------------------------------------------------------------
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

#ifndef _SINEWAVE_H_
#define _SINEWAVE_H_

#include <systemc-ams>

SCA_TDF_MODULE(sinewave)
{
  sca_tdf::sca_out<double> outp;

  struct params
  {
    double  freq;
    double  ampl;
    double  offset;
    sca_core::sca_time sample_time;

    params()
    {
      ampl = 1.0;
      offset=0.0;
      freq = 1e3;
      sample_time = sca_core::sca_time(10.0,sc_core::SC_US);
    }
  };

  void set_attributes();
  void ac_processing();
  void processing();

  sinewave(sc_core::sc_module_name nm, params pa=params());

  params p;
};

#endif // _SINEWAVE_H_
