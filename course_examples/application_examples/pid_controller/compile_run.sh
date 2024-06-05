#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf comparator-tdf.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
export LD_LIBRARY_PATH=/usr/local/systemc-ams-2.3/lib-linux64/:$SYSTEMC_HOME/lib-linux64/
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 -I/usr/local/systemc-ams-2.3/include -L/usr/local/systemc-ams-2.3/lib-linux64 sc_main.cpp ltf_nd_filter.cpp ltf_pid.cpp pid_controller.cpp  -lsystemc -lsystemc-ams -lm -o pid.o
echo 'Simulation Started'
./pid.o
echo 'Simulation Ended'
