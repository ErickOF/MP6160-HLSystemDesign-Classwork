//-----------------------------------------------------
#include "systemc.h"


SC_MODULE(fpu_unit)
{
  //-----------Internal variables-------------------
  // Constructor for fpu
  SC_CTOR(fpu_unit)
  {
  }

  //------------Code Starts Here-------------------------
  void add(float op_a, float op_b, float &op_c)
  {
    op_c = op_a + op_b;
  }  

  void subs(float op_a, float op_b, float &op_c)
  {
    op_c = op_a - op_b;
  }

  void mult(float op_a, float op_b, float &op_c)
  {
    op_c =  op_a * op_b;
  }

  void div(float op_a, float op_b, float &op_c)
  {
    op_c = op_a / op_b;
  }
};
