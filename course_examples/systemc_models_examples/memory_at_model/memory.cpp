//-----------------------------------------------------
#include "systemc.h"

SC_MODULE (ram) {
    
  sc_inout<sc_uint<32> > data; 
  sc_in<sc_uint<32> > address;
 
  //-----------Internal variables-------------------
  sc_uint <32> mem[1024];
  sc_event rd_t, wr_t;
  
  // Constructor for memory
  //SC_CTOR(ram) {
  SC_HAS_PROCESS(ram);
    ram(sc_module_name ram) {
    SC_THREAD(wr);
    SC_THREAD(rd);
         
  } // End of Constructor

   //------------Code Starts Here-------------------------
  void write() {
    wr_t.notify(2, SC_NS);
  }  
  
  void read() {
    rd_t.notify(2, SC_NS);  
  }  

  void wr() {
    while(true) {
      wait(wr_t);
      mem [address.read()] = data.read();
    }  
  }

  void rd() {
    while(true) {
      wait(rd_t);
      data = mem [address.read()];
    }  
  }
  
}; // End of Module memory
