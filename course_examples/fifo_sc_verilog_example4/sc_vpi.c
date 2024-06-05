#include <stdio.h>
#include <stdlib.h>
#include "vpi_user.h"

#include "sc_tb_ports.h"
#include "sc_tb_exports.h"

// CallBack Proto 
int sc_tb_calltf(char *user_data);
int sc_tb_interface(p_cb_data cb_data);

int sc_tb_calltf(char *user_data) {
  s_vpi_value  value_s;
  s_vpi_time  time_s;
  s_cb_data  cb_data_s;
  vpiHandle clk;
         
  time_s.type         = vpiSuppressTime;
  value_s.format      = vpiIntVal;
  
  // Set-Up Value Change callback option 
  cb_data_s.user_data = NULL;
  cb_data_s.reason    = cbValueChange;
  cb_data_s.cb_rtn    = sc_tb_interface;
  cb_data_s.time      = &time_s;
  cb_data_s.value     = &value_s;
  
  //Callback signal
  clk = vpi_handle_by_name("tb.clk", NULL);
  cb_data_s.obj  = clk;
  vpi_register_cb(&cb_data_s);
  
  init_sc();  // Initialize SystemC Model

  return(0);
  
}

//Value change simulation callback routine
int sc_tb_interface(p_cb_data cb_data)
{
  s_vpi_value  value_s;
  s_vpi_time time;
   
  // IO ports systemC testbench
  static INVECTOR   invector;
  static OUTVECTOR  outvector;
  
  //Blackbox
  vpiHandle rst      = vpi_handle_by_name("tb.rst", NULL);
  vpiHandle clk      = vpi_handle_by_name("tb.clk", NULL);
  vpiHandle wr_cs    = vpi_handle_by_name("tb.wr_cs", NULL);
  vpiHandle rd_cs    = vpi_handle_by_name("tb.rd_cs", NULL);
  vpiHandle data_in  = vpi_handle_by_name("tb.data_in", NULL);
  vpiHandle rd_en    = vpi_handle_by_name("tb.rd_en", NULL);
  vpiHandle wr_en    = vpi_handle_by_name("tb.wr_en", NULL);
  vpiHandle data_out = vpi_handle_by_name("tb.data_out", NULL);
  vpiHandle empty    = vpi_handle_by_name("tb.empty", NULL);
  vpiHandle full     = vpi_handle_by_name("tb.full", NULL);
  
  //Whitebox
  vpiHandle rd_pointer = vpi_handle_by_name("tb.dut.rd_pointer", NULL);
  vpiHandle wr_pointer = vpi_handle_by_name("tb.dut.wr_pointer", NULL);
  
  // Read current value from Verilog 
  value_s.format = vpiIntVal;

  vpi_get_value(clk, &value_s);
  invector.clk = value_s.value.integer;
    
  vpi_get_value(data_out, &value_s);
  invector.data_out = value_s.value.integer;
  
  vpi_get_value(empty, &value_s);
  invector.empty = value_s.value.integer;
  
  vpi_get_value(full, &value_s);
  invector.full = value_s.value.integer;
  
  vpi_get_value(rd_pointer, &value_s);
  invector.rd_pointer = value_s.value.integer;
  
  vpi_get_value(wr_pointer, &value_s);
  invector.wr_pointer = value_s.value.integer;
 
  sc_time sc_time_tmp (1, SC_NS);
  exec_sc(&invector, &outvector, sc_time_tmp);
 
  value_s.value.integer = outvector.rst;
  vpi_put_value(rst, &value_s, 0, vpiNoDelay);

  value_s.value.integer = outvector.wr_cs;
  vpi_put_value(wr_cs, &value_s, 0, vpiNoDelay);
  
  value_s.value.integer = outvector.rd_cs;
  vpi_put_value(rd_cs, &value_s, 0, vpiNoDelay);
  
  value_s.value.integer = outvector.data_in;
  vpi_put_value(data_in, &value_s, 0, vpiNoDelay);
  
  value_s.value.integer = outvector.rd_en;
  vpi_put_value(rd_en, &value_s, 0, vpiNoDelay);
  
  value_s.value.integer = outvector.wr_en;
  vpi_put_value(wr_en, &value_s, 0, vpiNoDelay);
  
  if (outvector.done) {
      
     exit_sc();

     vpi_control(vpiFinish);
  }
  return(0);
}

void sc_tb()
{
	s_vpi_systf_data tf;
	
	tf.type		=	vpiSysTask;
	tf.tfname	=	"$sc_tb";
	tf.calltf	=	sc_tb_calltf;
	tf.compiletf	=	NULL;
	tf.sizetf	=	0;
	tf.user_data	=	0;

	vpi_register_systf(&tf);
}

void (*vlog_startup_routines[])() = {
	sc_tb,
	0
};