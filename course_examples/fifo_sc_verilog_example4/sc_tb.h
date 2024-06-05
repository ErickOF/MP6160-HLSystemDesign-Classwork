#ifndef SC_TB_TEST_H
#define SC_TB_TEST_H

#include "systemc.h"
#include "scv.h"


SC_MODULE (interface) {
  
  // Input Signals
  sc_inout<bool>    clk;
  sc_inout<sc_uint<8> >    data_out;
  sc_inout<bool>    empty;
  sc_inout<bool>   full;

  // Output Signals
  sc_out<bool>  rst;
  sc_out<bool>  wr_cs;
  sc_out<bool>  rd_cs;
  sc_out<sc_uint<8> >  data_in;
  sc_out<bool>  rd_en;
  sc_out<bool>  wr_en;
  sc_out<bool>  done; //Terminate sim 
  
  //whitebox
  sc_in<sc_uint<8> >  rd_pointer;
  sc_in<sc_uint<8> >  wr_pointer;
 
  SC_CTOR(interface) {
    
  }
  
};


SC_MODULE (functional_cov) {
  
  interface *intf_int; 
  int wr_ptr_full_evt;
  int rd_ptr_empty_evt;
    
  SC_HAS_PROCESS(functional_cov);
  functional_cov(sc_module_name cov, interface *intf_ext) {
         
    //Interface
    intf_int = intf_ext;
    
    SC_THREAD(funct_cov)
      sensitive<<intf_ext->clk.pos();
  }
  
  void funct_cov();
  void print_cov();
};

SC_MODULE (scoreboard) {
  
  sc_fifo<sc_uint<8> > fifo;
    
  SC_CTOR(scoreboard) {
    sc_fifo<sc_uint<8> > fifo (100); //FIXME this should be dynamic allocation.    
  }
};

class data_rnd_constraint : public scv_constraint_base {
public:
  scv_smart_ptr< sc_uint<8> > data;
  
  SCV_CONSTRAINT_CTOR(data_rnd_constraint) {
    // Soft Constraint
    SCV_SOFT_CONSTRAINT ( data() < 20 ); // Max 
    SCV_SOFT_CONSTRAINT ( data() < 15 );   // Min 
    // Hard Constraint
    SCV_CONSTRAINT ( data() > 10 );  
  }
};

SC_MODULE(stim_gen) {
     
  SC_HAS_PROCESS(stim_gen);
  stim_gen(sc_module_name stim_gen) {
  }
  
  sc_uint<8 > data_rnd_gen(){
    scv_random::set_global_seed(scv_random::pick_random_seed()); //FIXME: needs to come from test seed
    data_rnd_constraint data_rnd ("data_rnd_constraint");
    data_rnd.next();
    return data_rnd.data.read();
  }
    
};


SC_MODULE (driver) {
  
  stim_gen *stim_gen_inst;    
  interface *intf_int; 
  scoreboard *scb_int;
  
 
 
  SC_HAS_PROCESS(driver);
  driver(sc_module_name driver, scoreboard *scb_ext, interface *intf_ext) {
         
    //Interface
    intf_int = intf_ext;
    //Scoreboard
    scb_int = scb_ext;
  }
 
  void reset();
  void write();
  void read();

};

SC_MODULE (monitor) {
  
  interface *intf_int;   
  scoreboard *scb_int;
  
  sc_uint<8> data_out_exp;
  sc_uint<8> data_out_read;
 
  SC_HAS_PROCESS(monitor);
  monitor(sc_module_name monitor, scoreboard *scb_ext, interface *intf_ext) {
    //Interface
    intf_int=intf_ext;
    //Scoreboard
    scb_int = scb_ext;
    SC_THREAD(mnt_out);
      sensitive << intf_ext->rd_en.pos();
  }
 
  void mnt_out();
 
};

SC_MODULE (environment) {
  
  driver *drv;
  monitor *mnt;
  scoreboard *scb;
  functional_cov *cov;
  interface *intf_int; 
  
  SC_HAS_PROCESS(environment);
  environment(sc_module_name environment, interface *intf_ext) {
    
    intf_int = intf_ext;
    //functional_cov
    cov = new functional_cov("cov",intf_ext);
    //Scoreboard
    scb = new scoreboard("scb");
    //Driver
    drv = new driver("drv",scb,intf_ext);
    //Monitor
    mnt = new monitor("mnt",scb,intf_ext);
        
  }
};

SC_MODULE (base_test) {

  environment *env;
  interface *intf_int; 
   
  void test ();
  
  SC_HAS_PROCESS(base_test);
  base_test(sc_module_name base_test, interface *intf_ext) {
    
    intf_int = intf_ext;
    //environment
    env = new environment("env",intf_ext);
    SC_THREAD(test)
      sensitive << intf_ext->clk.pos();
        
  }
};

SC_MODULE (sc_tb) {
   
  base_test *test1;
  interface *intf;
  
  SC_CTOR(sc_tb) {
    intf = new interface("intf");
    test1 = new base_test("test1",intf);

  }
};

#endif
