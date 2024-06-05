`timescale 1ns / 1ns
// Testbench top level
module tb();
reg      clk; 
reg      rst;
reg      wr_cs;
reg      rd_cs;
reg  [7:0]  data_in;
reg      rd_en;
reg      wr_en;
wire [7:0] data_out;
wire     empty;
wire     full;   

initial begin
 $dumpfile("verilog.vcd");
 $dumpvars(0);
 $display("[DUT]: Starting...");
 $sc_tb;// Testbench Connection
 clk = 0;
end
// Clock generator
always #1 clk = ~clk;
  
// DUT connection
sync_fifo dut (
  clk      , 
  rst      ,
  wr_cs    ,
  rd_cs    ,
  data_in  ,
  rd_en    ,
  wr_en    ,
  data_out ,
  empty    ,
  full      
);    

endmodule