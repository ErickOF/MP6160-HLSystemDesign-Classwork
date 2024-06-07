#include <systemc.h>
#include "memory.cpp"

int sc_main (int argc, char* argv[]) {
  int data; 
  
  ram mem("MEM", 1024);
            
  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("memory");
  wf->set_time_unit(1, SC_NS);
  
  // Dump the desired signals
  sc_trace(wf, data, "data");
  
  sc_start();
  cout << "@" << sc_time_stamp()<< endl;
  
  printf("Writing in zero time\n");
  printf("WR: addr = 0x10, data = 0xaced\n");
  printf("WR: addr = 0x12, data = 0xbeef\n");
  printf("WR: addr = 0x13, data = 0xdead\n");
  printf("WR: addr = 0x14, data = 0x1234\n");
  
  mem.wr(0x10, 0xaced);
  mem.wr(0x11, 0xbeef);
  mem.wr(0x12, 0xdead);
  mem.wr(0x13, 0x1234);
  
  cout << "@" << sc_time_stamp()<< endl;
  
  cout << "Reading in zero time" <<endl; 
  data = mem.rd(0x10);
  printf("Rd: addr = 0x10, data = %x\n",data);
  data = mem.rd(0x11);
  printf("Rd: addr = 0x11, data = %x\n",data);
  data = mem.rd(0x12);
  printf("Rd: addr = 0x12, data = %x\n",data);
  data = mem.rd(0x13);
  printf("Rd: addr = 0x13, data = %x\n",data);
  
  cout << "@" << sc_time_stamp()<< endl;  

  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  sc_close_vcd_trace_file(wf);
  return 0;// Terminate simulation

 }