#include <systemc.h>
#include "memory.cpp"

int sc_main (int argc, char* argv[]) {
 
  int data;
  
  ram mem("MEM",1024);
            
  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("memory");
  wf->set_time_unit(1, SC_NS);
  
  // Dump the desired signals
  sc_trace(wf, data, "data");
  
  sc_start(0,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  
  printf("Writing in zero time\n");
  printf("WR: addr = 0x10, data = 0xaced\n");
  printf("WR: addr = 0x12, data = 0xbeef\n");
  printf("WR: addr = 0x13, data = 0xdead\n");
  printf("WR: addr = 0x14, data = 0x1234\n");
  
  mem.write(0x10, 0xaced);
  sc_start(10,SC_NS);
  //data = mem.read(0x10);
  //printf("Rd: addr = 0x10, data = %x\n",data);
    
  mem.write(0x11, 0xbeef);
  
  sc_start(10,SC_NS);
  mem.write(0x12, 0xdead);
  
  sc_start(10,SC_NS);
  mem.write(0x13, 0x1234);
  
  sc_start(10,SC_NS);
  
  data = mem.read(0x10);
  sc_start(10,SC_NS);
  printf("Rd: addr = 0x10, data = %x\n",data);
  
  data = mem.read(0x11);
  sc_start(10,SC_NS);
  printf("Rd: addr = 0x11, data = %x\n",data);
  
   
  data = mem.read(0x12);
  sc_start(10,SC_NS);
  printf("Rd: addr = 0x12, data = %x\n",data);
  

  data = mem.read(0x13);
  sc_start(10,SC_NS);
  printf("Rd: addr = 0x13, data = %x\n",data);
  
  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  sc_close_vcd_trace_file(wf);
  return 0;// Terminate simulation

 }