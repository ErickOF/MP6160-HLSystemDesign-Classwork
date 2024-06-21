// Learn with Examples, 2020, MIT license
// https://www.edaplayground.com/x/2pu5
#include <systemc>

#include "process.hpp"


int sc_main(int, char*[]) {
  // Init module
  PROCESS process("process");

  std::cout << "Execution phase begins @ " << sc_core::sc_time_stamp()
    << std::endl;

  // Run simulation for 2 second
  sc_core::sc_start(2, sc_core::SC_SEC);

  std::cout << "Execution phase ends @ " << sc_core::sc_time_stamp()
    << std::endl;

  return 0;
}