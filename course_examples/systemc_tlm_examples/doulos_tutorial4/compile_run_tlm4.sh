#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf tlm4.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 tlm4.cpp  -lsystemc -lm -o tlm4.o
echo 'Simulation Started'
./tlm4.o
echo 'Simulation Ended'
