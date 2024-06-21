#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <systemc>


SC_MODULE(PROCESS)
{
  // Declares a clock
  sc_core::sc_clock clk;

  // Instantiate a clock with 1s periodicity
  SC_CTOR(PROCESS);

  // Define the method member function
  void method(void);
  // Define the thread member function
  void thread();
  // Define the cthread member function
  void cthread();
};
#endif // PROCESS_HPP
