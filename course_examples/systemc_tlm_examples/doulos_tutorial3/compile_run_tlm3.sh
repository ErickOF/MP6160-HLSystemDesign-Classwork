#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf tlm3.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 tlm3.cpp  -lsystemc -lm -o tlm3.o
echo 'Simulation Started'
./tlm3.o
echo 'Simulation Ended'
