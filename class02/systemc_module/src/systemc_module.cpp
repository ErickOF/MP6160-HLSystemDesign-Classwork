// Learn with Examples, 2020, MIT license
// https://www.edaplayground.com/x/2QA6
#include <systemc>

using namespace sc_core;

// Approach #1, use systemC provided SC_MODULE macro
SC_MODULE(MODULE_A)
{
  // Default constructor
  SC_CTOR(MODULE_A)
  {
    // name() returns the object name, which is provided during instantization
    std::cout << name() << " constructor" << std::endl;
  }
};

// Approach #2, this uses C++ syntax and is more readable
struct MODULE_B : public sc_module
{
  SC_CTOR(MODULE_B)
  {
    std::cout << name() << " constructor" << std::endl;
  }
};

// Approach #3, use class instead of struct
class MODULE_C : public sc_module
{
// Have to explicitly declare constructor function as public
public:
  SC_CTOR(MODULE_C)
  {
    std::cout << name() << " constructor" << std::endl;
  }
};

// SystemC entry point
int sc_main(int, char*[])
{
  // Declare and instantiate module_a, it's common practice to assign module
  // name == object name
  MODULE_A module_a("module_a");
  // Declare and instantiate module_b, module name != object name
  MODULE_B module_b("modb");
  // Declare and instantiate module_c
  MODULE_C module_c("module_c");

  // This can be skipped in this example because module instantiation happens
  // during elaboration phase which is before sc_start
  sc_start();

  return 0;
}
