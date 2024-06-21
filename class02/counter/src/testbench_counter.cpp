//-----------------------------------------------------
// Testbench for the 4-bit up-counter ---------------->
// Example from www.asic-world.com (with fixes)
//-----------------------------------------------------
#include "systemc.h"
#include "first_counter.hpp"


int sc_main(int, char*[])
{
  sc_signal<bool> clock;
  sc_signal<bool> reset;
  sc_signal<bool> enable;
  sc_signal<sc_uint<4> > counter_out;

  int i = 0;

  // Connect the DUT
  first_counter counter("COUNTER");
  counter.clock(clock);
  counter.reset(reset);
  counter.enable(enable);
  counter.counter_out(counter_out);

  sc_start(1, SC_NS);

  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("counter");

  // Dump the desired signals
  sc_trace(wf, clock, "clock");
  sc_trace(wf, reset, "reset");
  sc_trace(wf, enable, "enable");
  sc_trace(wf, counter_out, "count");

  // Initialize all variables
  // initial value of reset
  reset = 0;
  // initial value of enable
  enable = 0;

  for (i = 0; i < 5; ++i)
  {
    clock = 0;
    sc_start(1, SC_NS);

    clock = 1;
    sc_start(1, SC_NS);
  }

  // Assert the reset
  reset = 1;

  std::cout << "@" << sc_time_stamp() << " Asserting reset\n" << std::endl;

  for (i = 0; i < 10; ++i)
  {
    clock = 0;
    sc_start(1, SC_NS);

    clock = 1;
    sc_start(1, SC_NS);
  }

  // De-assert the reset
  reset = 0;

  std::cout << "@" << sc_time_stamp() << " De-Asserting reset\n" << std::endl;

  for (i = 0; i < 5; ++i)
  {
    clock = 0; 
    sc_start(1, SC_NS);

    clock = 1; 
    sc_start(1, SC_NS);
  }

  std::cout << "@" << sc_time_stamp() << " Asserting Enable\n" << std::endl;

  // Assert enable
  enable = 1;

  for (i = 0; i < 20; ++i)
  {
    clock = 0;
    sc_start(1, SC_NS);

    clock = 1;
    sc_start(1, SC_NS);
  }

  std::cout << "@" << sc_time_stamp() << " De-Asserting Enable\n" << std::endl;

  // De-assert enable
  enable = 0;

  std::cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << std::endl;

  sc_close_vcd_trace_file(wf);

  // Terminate simulation
  return 0;
}
