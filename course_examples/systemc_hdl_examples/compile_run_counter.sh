#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf counter.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.2/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 counter_tb.cpp counter.cpp  -lsystemc -lm -o counter.o
echo 'Simulation Started'
./counter.o
echo 'Simulation Ended'