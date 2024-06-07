#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf arbiter.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.2/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 arbiter_tb.cpp arbiter.cpp  -lsystemc -lm -o arbiter.o
echo 'Simulation Started'
./arbiter.o
echo 'Simulation Ended'