#include "process.hpp"

PROCESS::PROCESS(sc_core::sc_module_name name)
  : sc_module(name),
    clk("clk", 1, sc_core::SC_SEC)
{
  // Register a method
  SC_METHOD(method);
  // Register a thread
  SC_THREAD(thread);
  // Register a clocked thread
  SC_CTHREAD(cthread, clk);
}

// Define the cthread member function
void PROCESS::cthread()
{
  // Infinite loop
  while (true)
  {
    std::cout << "Cthread triggered @ " << sc_core::sc_time_stamp()
      << std::endl;
    // Wait for next clk event, which comes after 1a
    wait();
  }
}

// Define the method member function
void PROCESS::method(void)
{
  // No while loop here
  std::cout << "Method triggered @ " << sc_core::sc_time_stamp() << std::endl;
  // Trigger after 1s
  next_trigger(sc_core::sc_time(1, sc_core::SC_SEC));
}

// Define the thread member function
void PROCESS::thread()
{
  // Infinite loop make sure it never exits 
  while (true)
  {
    std::cout << "Thread triggered @ " << sc_core::sc_time_stamp()
      << std::endl;
    // Wait 1s before execute again
    wait(1, sc_core::SC_SEC);
  }
}
