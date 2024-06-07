#include <systemc.h>
#include "arbiter.cpp"

int sc_main (int argc, char* argv[]) {
  sc_signal<bool>   reset;
  sc_signal<bool>   req0; 
  sc_signal<bool>   req1; 
  sc_signal<bool>   gnt0; 
  sc_signal<bool>   gnt1; 
  
  //sc_clock clock("clock", 10, 0.5, 1, false);
  sc_clock clock("clock", 2, SC_NS ,0.5);
  
  // Connect the DUT
  arbiter arb("ARB");
    arb.clock(clock);
    arb.reset(reset);
    arb.req0(req0); 
    arb.req1(req1); 
    arb.gnt0(gnt0); 
    arb.gnt1(gnt1);
    
  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("arbiter");
  wf->set_time_unit(1, SC_NS);
  
  // Dump the desired signals
  sc_trace(wf, clock, "clock");
  sc_trace(wf, reset, "reset");
  sc_trace(wf, req0, "req0");
  sc_trace(wf, req1, "req1");
  sc_trace(wf, gnt0, "gnt0");
  sc_trace(wf, gnt1, "gnt1");
  
  sc_start(0,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  // Initialize all variables
  reset = 1;       // initial value of reset
  cout << "@" << sc_time_stamp()<< endl;
  sc_start(10,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  reset = 0;
  req0 = 1;
  req1 = 0;
  sc_start(10,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  req0 = 0;
  req1 = 1;
  sc_start(10,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  req0 = 1;
  req1 = 1;
  sc_start(10,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;

  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  sc_close_vcd_trace_file(wf);
  return 0;// Terminate simulation

 }