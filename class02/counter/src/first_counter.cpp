#include "first_counter.hpp"

// Constructor for the counter
// Since this counter is a positive edge trigged one,
// We trigger the below block with respect to positive
// edge of the clock and also when ever reset changes state
first_counter::first_counter(sc_module_name name) : sc_module(name)
{
  std::cout << "Executing new" << std::endl;

  SC_METHOD(incr_count);
  sensitive << reset;
  sensitive << clock.pos();
}

// Below function implements actual counter logic
void first_counter::incr_count()
{
  // At every rising edge of clock we check if reset is active
  // If active, we load the counter output with 4'b0000
  if (reset.read() == 1)
  {
    count =  0;
    counter_out.write(count);
  }
  // If enable is active, then we increment the counter
  else if (enable.read() == 1)
  {
    count++;

    counter_out.write(count);

    std::cout << "@" << sc_time_stamp() << " :: Incremented Counter "
      << counter_out.read() << std::endl;
  }
}