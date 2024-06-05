//-----------------------------------------------------
#include "systemc.h"

SC_MODULE (ram) {
    
  //-----------Internal variables-------------------
  int * mem;
  
  // Constructor for memory
  //SC_CTOR(ram) {
  SC_HAS_PROCESS(ram);
    ram(sc_module_name ram, int size=8) : sc_module(ram) {
    mem = new int [size];
  } // End of Constructor

   //------------Code Starts Here-------------------------
  void wr(int address, int data) {
    sleep(1); //will not move time stamp either
    mem [address] = data;
  }  
  
  int rd(int address) {
    return mem [address];
  }  

  
}; // End of Module memory
