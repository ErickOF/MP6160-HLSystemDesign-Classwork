//-----------------------------------------------------
#include "systemc.h"

SC_MODULE (ram) {
 
  //-----------Internal variables-------------------
  int * mem;
  int data;
  int address;
  sc_event rd_t, wr_t;
  
  // Constructor for memory
  //SC_CTOR(ram) {
  SC_HAS_PROCESS(ram);
    ram(sc_module_name ram, int size=8) {
    mem = new int [size];
    SC_THREAD(wr);
         
  } // End of Constructor

   //------------Code Starts Here-------------------------
  void write(int addr, int dat) {
    data = dat;
    address = addr;
    wr_t.notify(2, SC_NS);
  }  
  
  int read(int address) {
    data = mem [address];
    return data;
  }  

  void wr() {
    while(true) {
      wait(wr_t);
      mem [address] = data;
    }  
  }

  
}; // End of Module memory
