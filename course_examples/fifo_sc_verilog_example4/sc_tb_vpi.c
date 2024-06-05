#include "sc_tb_ports.h"
#include "sc_tb_exports.h"
#include "strings.h"

// Instantiate Top-Level DUT
sc_tb    u_sc_tb("u_sc_tb");

// Input Signals
  sc_signal<bool>    clk;
  sc_signal<sc_uint<8> >    data_out;
  sc_signal<bool>    empty;
  sc_signal<bool>   full;

  // Output Signals
  sc_signal<bool>  rst;
  sc_signal<bool>  wr_cs;
  sc_signal<bool>  rd_cs;
  sc_signal<sc_uint<8> >  data_in;
  sc_signal<bool>  rd_en;
  sc_signal<bool>  wr_en;
  sc_signal<bool>  done; //Terminate sim 
  
  //whitebox
  sc_signal<sc_uint<8> >  rd_pointer;
  sc_signal<sc_uint<8> >  wr_pointer;

// Top-Level testbench
void init_sc() {

  // Input signals
  u_sc_tb.intf->clk(clk);
  u_sc_tb.intf->data_out(data_out);
  u_sc_tb.intf->empty(empty);
  u_sc_tb.intf->full(full);
 
  //Output Signals
  u_sc_tb.intf->rst(rst);
  u_sc_tb.intf->wr_cs(wr_cs);
  u_sc_tb.intf->rd_cs(rd_cs);
  u_sc_tb.intf->data_in(data_in);
  u_sc_tb.intf->rd_en(rd_en);
  u_sc_tb.intf->wr_en(wr_en);
  u_sc_tb.intf->done(done);
  
  //whitebox
  u_sc_tb.intf->rd_pointer(rd_pointer);
  u_sc_tb.intf->wr_pointer(wr_pointer);
  
  // Initialize
  sc_start();
  cout<<"@"<<sc_time_stamp()<<" Started SystemC Scheduler"<<endl;
}

void sample_hdl(void *Invector) {
  INVECTOR *pInvector = (INVECTOR *)Invector;
  clk.write(pInvector->clk);
  data_out.write(pInvector->data_out);
  empty.write(pInvector->empty);
  full.write(pInvector->full);
  rd_pointer.write(pInvector->rd_pointer);
  wr_pointer.write(pInvector->wr_pointer);
}

void drive_hdl(void *Outvector) {
  OUTVECTOR *pOutvector = (OUTVECTOR *)Outvector;
  pOutvector->rst     = rst.read();
  pOutvector->wr_cs   = wr_cs.read();
  pOutvector->rd_cs   = rd_cs.read();
  pOutvector->data_in = data_in.read();
  pOutvector->rd_en   = rd_en.read();
  pOutvector->wr_en   = wr_en.read();
  pOutvector->done    = done.read();
}

void advance_sim(sc_time simtime) {
  sc_start(simtime);
}

//void exec_sc(void *invector, void *outvector, unsigned long simtime) {
void exec_sc(void *invector, void *outvector, sc_time simtime) {
  sample_hdl(invector);    // Input-Stimuli
  advance_sim(simtime);   // Advance Simulator
  drive_hdl(outvector);  // Output Vectors
}

void exit_sc() {
  cout<<"@"<<sc_time_stamp()<<" Stopping SystemC Scheduler"<<endl;
  sc_stop();
}
