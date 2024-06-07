//-----------------------------------------------------
#include <systemc.h>

/**
 * @brief Enum that represents the main FPU operations
 * 
 */
typedef enum {
  SC_FPU_ADD = 1,
  SC_FPU_SUB = 2,
  SC_FPU_MULT = 3,
  SC_FPU_DIV = 4
} sc_fpu_op_t;

/**
 * @brief Class the represent and FPU using PV model
 * 
 */
SC_MODULE (fpu_unit) {
protected:
  //----------------------------Internal variables----------------------------
  // First operand
  float op_a;
  // Second operand
  float op_b;
  // Result
  float *op_c;
  // Operation type
  sc_fpu_op_t op_type;

  // Event to trigger the operation execution
  sc_event event_op;

  //-----------------------------Internal methods-----------------------------
  /**
   * @brief Performs the operation between the operands
   * 
   */
  void exec_op()
  {
    while (true)
    {
      wait(event_op);

      // Perform the operations
      switch (this->op_type)
      {
      case SC_FPU_ADD:
        std::cout << "Performing ADD operation"<< std::endl;
        *(this->op_c) = this->op_a + this->op_b;
        break;
      case SC_FPU_SUB:
        std::cout << "Performing SUB operation"<< std::endl;
        *(this->op_c) = this->op_a - this->op_b;
        break;
      case SC_FPU_MULT:
        std::cout << "Performing MULT operation"<< std::endl;
        *(this->op_c) = this->op_a * this->op_b;
        break;
      case SC_FPU_DIV:
        std::cout << "Performing DIV operation"<< std::endl;
        *(this->op_c) = this->op_a / this->op_b;
        break;
      default:
        break;
      }
    }
  }

public:
  SC_HAS_PROCESS(fpu_unit);
  /**
   * @brief Construct a new fpu unit object
   * 
   * @param name - name of the module
   */
  fpu_unit(sc_module_name name) : sc_module(name)
  {
    SC_THREAD(exec_op);
  } // End of Constructor

  //------------------------------Public methods------------------------------
  /**
   * @brief Adds two float numbers
   * 
   * @param op_a - first operand
   * @param op_b - second operand
   * @param op_c - result of the operation
   */
  void add(float op_a, float op_b, float *op_c)
  {
    this->op_a = op_a;
    this->op_b = op_b;
    this->op_c = op_c;
    this->op_type = SC_FPU_ADD;

    this->event_op.notify(1, SC_NS);
  }

  /**
   * @brief Divides two float numbers
   * 
   * @param op_a - first operand
   * @param op_b - second operand
   * @param op_c - result of the operation
   */
  void div(float op_a, float op_b, float *op_c)
  {
    this->op_a = op_a;
    this->op_b = op_b;
    this->op_c = op_c;
    this->op_type = SC_FPU_DIV;

    this->event_op.notify(3, SC_NS);
  }

  /**
   * @brief Multiplies two float numbers
   * 
   * @param op_a - first operand
   * @param op_b - second operand
   * @param op_c - result of the operation
   */
  void mult(float op_a, float op_b, float *op_c) {
    this->op_a = op_a;
    this->op_b = op_b;
    this->op_c = op_c;
    this->op_type = SC_FPU_MULT;

    this->event_op.notify(2, SC_NS);
  }

  /**
   * @brief Subtracts two float numbers
   * 
   * @param op_a - first operand
   * @param op_b - second operand
   * @param op_c - result of the operation
   */
  void subs(float op_a, float op_b, float *op_c)
  {
    this->op_a = op_a;
    this->op_b = op_b;
    this->op_c = op_c;
    this->op_type = SC_FPU_SUB;

    this->event_op.notify(1, SC_NS);
  }
};
