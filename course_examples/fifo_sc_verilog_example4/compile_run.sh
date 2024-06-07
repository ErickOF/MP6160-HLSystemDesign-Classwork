#!/bin/sh
echo 'Cleaning the directory'
rm -rf *.o *.vvp *.vpi *vcd
echo 'Compiling *.c *cpp files'
g++ -fpic -c sc_tb_vpi.c sc_vpi.c sc_tb.cpp -I /usr/include/iverilog/ -I /usr/local/systemc-2.3.2/include/ -I /usr/local/scv-2.0.1/include/
echo 'Creating vpi file'
g++ -shared -L /usr/local/systemc-2.3.2/lib-linux64 -L /usr/local/scv-2.0.1/lib-linux64 -Wl,-rpath=/usr/local/systemc-2.3.2/lib-linux64 -Wl,-rpath=/usr/local/scv-2.0.1/lib-linux64 -o sc_tb_vpi.vpi *.o -lsystemc -lm -lvpi -lscv
echo 'Compiling verilog files'
iverilog -o tb.vvp tb.v sync_fifo.v ram_dp_ar_aw.v
echo 'Simulation Started'
vvp -n -M. -msc_tb_vpi tb.vvp 
echo 'Simulation Ended'