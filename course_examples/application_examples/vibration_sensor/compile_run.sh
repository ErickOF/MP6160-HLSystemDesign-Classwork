#!/bin/sh
echo 'Compiling *.c *cpp files'
rm -rf comparator-tdf.o
export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
export LD_LIBRARY_PATH=/usr/local/systemc-ams-2.3/lib-linux64/:$SYSTEMC_HOME/lib-linux64/
g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 -I/usr/local/systemc-ams-2.3/include -L/usr/local/systemc-ams-2.3/lib-linux64 programmable_gain_amplifier.cpp vibration_sensor.cpp vibration_source.cpp vibration_sensor_tb.cpp -lsystemc -lsystemc-ams -lm -o sensor.o
echo 'Simulation Started'
./sensor.o
echo 'Simulation Ended'

