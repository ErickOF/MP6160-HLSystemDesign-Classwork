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

#ifndef _MIXER_H_
#define _MIXER_H_

#include <systemc-ams>

SCA_TDF_MODULE(mixer) 
{
  sca_tdf::sca_in<bool>     in_bin;  // input port baseband signal
  sca_tdf::sca_in<double>   in_wav;  // input port carrier signal
  sca_tdf::sca_out<double>  out;     // output port modulated signal
	
  SCA_CTOR(mixer);
	
  void set_attributes();
	
  void processing();

 private:
  unsigned long rate;
};

#endif // _MIXER_H_
