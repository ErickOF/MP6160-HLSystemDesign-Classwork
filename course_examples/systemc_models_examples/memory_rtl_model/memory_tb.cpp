#include <systemc.h>
#include "memory.cpp"

#define DATA_WIDTH        8 
#define ADDR_WIDTH        8 
#define RAM_DEPTH         1 << ADDR_WIDTH

int sc_main (int argc, char* argv[]) {
  sc_signal <sc_uint<ADDR_WIDTH> > address;
  sc_signal <bool> cs ;
  sc_signal <bool> we ;
  sc_signal <bool> oe ;
  sc_signal <sc_uint<DATA_WIDTH> > data; 
  
  sc_clock clock("clock", 2, SC_NS ,0.5);
  
  // Connect the DUT
  ram mem("MEM");
    mem.clock(clock);
    mem.address_0(address);
    mem.cs_0(cs);
    mem.we_0(we);
    mem.oe_0(oe);
    mem.data_0(data);
            
  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("memory");
  wf->set_time_unit(1, SC_NS);
  
  // Dump the desired signals
  sc_trace(wf, clock, "clock");
  sc_trace(wf, address, "address");
  sc_trace(wf, cs, "cs");
  sc_trace(wf, we, "we");
  sc_trace(wf, oe, "oe");
  sc_trace(wf, data, "data");
  
  sc_start(0,SC_NS);
  address = 0x0;
  data = 0x0;
  cs = 0;
  we = 0;
  oe = 0;
  sc_start(10,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  address = 0x10;
  data = 0xac;
  cs = 1;
  we = 1;
  oe = 0;
  sc_start(10,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  address = 0x11;
  data = 0xde;
  cs = 1;
  we = 1;
  oe = 0;
  sc_start(10,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  address = 0x10;
  cs = 1;
  we = 0;
  oe = 1;
  sc_start(10,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  address = 0x11;
  cs = 1;
  we = 0;
  oe = 1;
  sc_start(10,SC_NS);
  
  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  sc_close_vcd_trace_file(wf);
  return 0;// Terminate simulation

 }