#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf comparator-tdf.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
export LD_LIBRARY_PATH=/usr/local/systemc-ams-2.3/lib-linux64/:$SYSTEMC_HOME/lib-linux64/
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 -I/usr/local/systemc-ams-2.3/include -L/usr/local/systemc-ams-2.3/lib-linux64 compensator.cpp const_src.cpp dcdc_converter.cpp dcdc_pwm.cpp diode_dtdf.cpp diode.cpp dcdc_converter_simple_tb.cpp -lsystemc -lsystemc-ams -lm -o dcdc.o
echo 'Simulation Started'
./dcdc.o
echo 'Simulation Ended'

