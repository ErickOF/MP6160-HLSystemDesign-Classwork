//-----------------------------------------------------
// This is my second Systemc Example
// Design Name : first_counter
// File Name : first_counter.cpp
// Function : This is a 4 bit up-counter with
// Synchronous active high reset and
// with active high enable signal
//-----------------------------------------------------
#include "systemc.h"

SC_MODULE (arbiter) {
  sc_in_clk     clock ;      // Clock input of the design
  sc_in<bool>   reset ;      // active high, synchronous Reset input
  sc_in<bool>   req0; 
  sc_in<bool>   req1; 
  sc_out<bool>   gnt0; 
  sc_out<bool>   gnt1; 

  //------------Local Variables Here---------------------
  sc_signal<sc_lv<2> >   state;
  sc_signal<sc_lv<2> >   next_state;
  

  //------------Code Starts Here-------------------------
  void state_reg () {
    
    if (reset.read() == 1) {
      state=0;
    } else {
      state=next_state;
    }
  }  

  void next_state_comb () {
    
    if (req0.read() == 1) {
      next_state=1;
    } else if (req1.read() == 1){
      next_state=2;
    } else {
      next_state=0;   
    }
  }  
  
  void outputs_comb () {
    // At every rising edge of clock we check if reset is active
    if (state.read() == 1) {
      gnt0.write(1);
      gnt1.write(0);
    } else if (state.read() == 2){
      gnt0.write(0);
      gnt1.write(1);
    } else {
      gnt0.write(0);
      gnt1.write(0);   
    }
  } // End of state function 
  
  // Constructor for arbiter
  SC_CTOR(arbiter) {
    SC_METHOD(state_reg);
    sensitive << reset;
    sensitive << clock.pos();
    SC_METHOD(next_state_comb);
    sensitive << req0 << req1;
    SC_METHOD(outputs_comb);
    sensitive << state;
  } // End of Constructor

}; // End of Module arbiter