#include <systemc.h>
#include "memory.cpp"

int sc_main (int argc, char* argv[]) {
  sc_signal<sc_uint<32> > data; 
  sc_signal<sc_uint<32> > address;
  
  ram mem("MEM");
    mem.address(address);
    mem.data(data);
            
  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("memory");
  wf->set_time_unit(1, SC_NS);
  
  // Dump the desired signals
  sc_trace(wf, data, "data");
  sc_trace(wf, address, "address");
  sc_trace(wf, mem.mem[0x10], "data0");
  sc_trace(wf, mem.mem[0x11], "data1");
    
  sc_start(0,SC_NS);
  cout << "@" << sc_time_stamp()<< endl;
  
  printf("WR: addr = 0x10, data = 0xaced\n");
  address=0x10;
  data=0xaced;
  mem.write();
  sc_start(10,SC_NS);
  
  printf("WR: addr = 0x11, data = 0xbeef\n");
  address=0x11;
  data=0xbeef;
  mem.write();
  sc_start(10,SC_NS);
  
  printf("WR: addr = 0x12, data = 0xdead\n");
  address=0x12;
  data=0xdead;
  mem.write();
  sc_start(10,SC_NS);
  
  printf("WR: addr = 0x13, data = 0x1234\n");
  address=0x13;
  data=0x1234;
  mem.write();
  sc_start(10,SC_NS);
  
  address=0x10;
  mem.read();
  sc_start(10,SC_NS);
  printf("Rd: addr = 0x10 ");
  cout<< "data = " << hex << data.read()<<endl;
  
  address=0x11;
  mem.read();
  sc_start(10,SC_NS);
  printf("Rd: addr = 0x11");
  cout<< "data = " << hex << data.read()<<endl;
  
  address=0x12;
  mem.read();
  sc_start(10,SC_NS);
  printf("Rd: addr = 0x12"); 
  cout<< "data = " << hex << data.read()<<endl;
  
  address=0x13;
  mem.read();
  sc_start(10,SC_NS);
  printf("Rd: addr = 0x13");
  cout<< "data = " << hex << data.read()<<endl;
  
  cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
  sc_close_vcd_trace_file(wf);
  return 0;// Terminate simulation

 }