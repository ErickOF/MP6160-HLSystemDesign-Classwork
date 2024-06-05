#include "systemc.h"

#define DATA_WIDTH        8 
#define ADDR_WIDTH        8 
#define RAM_DEPTH         1 << ADDR_WIDTH

SC_MODULE (ram) {
  sc_in_clk clock;
  sc_in    <sc_uint<ADDR_WIDTH> > address_0;
  sc_in    <bool> cs_0 ;
  sc_in    <bool> we_0 ;
  sc_in    <bool> oe_0  ;
  sc_inout <sc_uint<DATA_WIDTH> > data_0;
  
  //-----------Internal variables-------------------
  sc_uint <DATA_WIDTH> mem [RAM_DEPTH];
 
  //-----------Constructor--------------------------
  SC_CTOR(ram) {
    SC_METHOD (READ_0);
      sensitive << address_0 << cs_0 << we_0 << oe_0;
    SC_METHOD (WRITE_0);
      sensitive << clock.pos();
  }

  //-----------Methods------------------------------
    
  void  READ_0 () {
    if (cs_0.read() && oe_0.read() && !we_0.read()) {
      //next_trigger(1,SC_NS);
      data_0 = mem[address_0.read()];
    }
  }

  void  WRITE_0 () {
    if (cs_0.read() && we_0.read()) {
      //next_trigger(1,SC_NS);
      mem[address_0.read()] = data_0.read();
    } 
  }
};