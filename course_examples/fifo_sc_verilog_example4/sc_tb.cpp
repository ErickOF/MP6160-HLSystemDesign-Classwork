#include "sc_tb.h"

  void functional_cov::funct_cov(){
    while(true){
      wait(1);
      if (intf_int->full.read() == true && intf_int->wr_pointer.read() == 0xFF){
        wr_ptr_full_evt++;
        cout<<"@"<<sc_time_stamp()<<" wr_ptr & full event" << endl;
      }
      if (intf_int->empty.read() == true && intf_int->rd_pointer.read() == 0x0){
        rd_ptr_empty_evt++;
        cout<<"@"<<sc_time_stamp()<<" rd_ptr & empty event" << endl;
      }
    }
  }
  
  void functional_cov::print_cov(){
    
    cout<<"Functional Coverage Results: "<< endl;
    cout<<"Event: wr_ptr & full = " <<  wr_ptr_full_evt << endl;
    cout<<"Event: rd_ptr & empty = " << rd_ptr_empty_evt << endl;
  }
  
  void driver::reset(){
    intf_int->rst = true;
    cout<<"@"<<sc_time_stamp()<<" Started Reset " << endl;
    wait(10);
    intf_int->rst = false;
    intf_int->wr_cs = true;
    intf_int->rd_cs = true;
    cout<<"@"<<sc_time_stamp()<<" Finished Reset " << endl;
  }
  
  void driver::write(){
    intf_int->data_in = stim_gen_inst->data_rnd_gen();
    intf_int->wr_en = true;
    wait(1);
    scb_int->fifo.write(intf_int->data_in);
    intf_int->data_in = 0;
    intf_int->wr_en = false;
       
  }
  
  void driver::read(){
    cout<<"@"<<sc_time_stamp()<<" Reading " << endl;
    intf_int->rd_en = true;
    wait(1);
    intf_int->rd_en = false;
  }

  void monitor::mnt_out(){
    while(true){
    wait(1);
    data_out_exp = scb_int->fifo.read();
    data_out_read = intf_int->data_out;
    cout<<"@"<<sc_time_stamp()<<" Monitor data_out:" << data_out_exp << endl;
    cout<<"@"<<sc_time_stamp()<<" Scoreboard data_out:" << data_out_read << endl;
    //Checker 
    if (data_out_exp != data_out_read)
      //assert(data_out_exp == data_out_read);
      cout<<"@"<<sc_time_stamp()<<" ERROR: data read and expected mismatch!" << endl;  
    }
  }


  //Test
  void base_test::test() {
    intf_int->done = 0;
    env->drv->reset();
    wait(10);
    for (int i=0; i<10; i++){
      env->drv->write();
      wait(10);
    }
    wait(10);
    for (int i=0; i<100; i++){
      env->drv->read();
      wait(10);
    }
    // Request for simulation termination
    cout << "=======================================" << endl;
    cout << " SIMULATION END" << endl;
    cout << "=======================================" << endl;
    env->cov->print_cov();
    intf_int->done = 1;
    // Just wait for few cycles
  }
