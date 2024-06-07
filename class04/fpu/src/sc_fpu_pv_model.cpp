//-----------------------------------------------------
#include "systemc.h"

/**
 * @brief Class the represent and FPU using LT model
 * 
 */
SC_MODULE(fpu_unit)
{
  //-----------Internal variables-------------------
  /**
   * @brief Construct a new fpu_unit
   * 
   */
  SC_CTOR(fpu_unit)
  {
  }

  //------------Code Starts Here-------------------------
  /**
   * @brief Adds two float numbers
   * 
   * @param op_a - first operand
   * @param op_b - second operand
   * @param op_c - result of the operation
   */
  void add(float op_a, float op_b, float &op_c)
  {
    op_c = op_a + op_b;
  }

  /**
   * @brief Subtracts two float numbers
   * 
   * @param op_a - first operand
   * @param op_b - second operand
   * @param op_c - result of the operation
   */
  void subs(float op_a, float op_b, float &op_c)
  {
    op_c = op_a - op_b;
  }

  /**
   * @brief Multiplies two float numbers
   * 
   * @param op_a - first operand
   * @param op_b - second operand
   * @param op_c - result of the operation
   */
  void mult(float op_a, float op_b, float &op_c)
  {
    op_c =  op_a * op_b;
  }

  /**
   * @brief Divides two float numbers
   * 
   * @param op_a - first operand
   * @param op_b - second operand
   * @param op_c - result of the operation
   */
  void div(float op_a, float op_b, float &op_c)
  {
    op_c = op_a / op_b;
  }
};
