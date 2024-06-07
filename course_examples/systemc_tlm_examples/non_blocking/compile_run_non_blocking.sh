#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf non_blocking.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 non_blocking.cpp  -lsystemc -lm -o non_blocking.o
echo 'Simulation Started'
./non_blocking.o
echo 'Simulation Ended'
