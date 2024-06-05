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

#include "mixer_de.h"
	
mixer_de::mixer_de( sc_core::sc_module_name nm )
: in_bin("in_bin"), in_wav("in_wav"), out("out"), rate(40) // use wave data rate of 40
{}
	
void mixer_de::set_attributes()
{
  in_wav.set_rate(rate);
  out.set_rate(rate);
}
	
void mixer_de::processing()
{
  for( unsigned long i = 0; i < rate; i++)
  {
    if( in_bin.read() )
      out.write( in_wav.read(i), i );
    else out.write( 0.0 , i );
  }
}
