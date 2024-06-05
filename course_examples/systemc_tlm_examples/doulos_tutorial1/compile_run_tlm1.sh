#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf tlm1.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 tlm1.cpp  -lsystemc -lm -o tlm1.o
echo 'Simulation Started'
./tlm1.o
echo 'Simulation Ended'
