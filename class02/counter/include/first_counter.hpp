//-----------------------------------------------------
// A 4 bit up-counter with synchronous active high reset
// and with active high enable signal
// Example from www.asic-world.com
//-----------------------------------------------------
#ifndef FIRST_COUNTER_HPP
#define FIRST_COUNTER_HPP
#include "systemc.h"


SC_MODULE(first_counter)
{
  // Clock input of the design
  sc_in_clk clock;
  // Active high, synchronous Reset input
  sc_in<bool> reset;
  // Active high enable signal for counter
  sc_in<bool> enable;
  // 4 bit vector output of the counter
  sc_out<sc_uint<4> > counter_out;

  //------------Local Variables Here---------------------
  sc_uint<4> count;

  //------------Code Starts Here-------------------------
  // Constructor for the counter
  // Since this counter is a positive edge trigged one,
  // We trigger the below block with respect to positive
  // edge of the clock and also when ever reset changes state
  SC_CTOR(first_counter);

  // Below function implements actual counter logic
  void incr_count();
};

#endif // FIRST_COUNTER_HPP
