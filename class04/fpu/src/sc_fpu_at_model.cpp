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
  // Operation type
  sc_fpu_op_t op_type;
  // Events to trigger the operation execution
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
        this->op_c.write(this->op_a.read() + this->op_b.read());
        break;
      case SC_FPU_SUB:
        this->op_c.write(this->op_a.read() - this->op_b.read());
        break;
      case SC_FPU_MULT:
        this->op_c.write(this->op_a.read() * this->op_b.read());
        break;
      case SC_FPU_DIV:
        this->op_c.write(this->op_a.read() / this->op_b.read());
        break;
      default:
        break;
      }
    }
  }

public:
  // First operand
  sc_in<float> op_a;
  // Second operand
  sc_in<float> op_b;
  // Result
  sc_out<float> op_c;

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
   */
  void add()
  {
    this->op_type = SC_FPU_ADD;
    this->event_op.notify(1, SC_NS);
  }

  /**
   * @brief Divides two float numbers
   */
  void div()
  {
    this->op_type = SC_FPU_DIV;
    this->event_op.notify(3, SC_NS);
  }

  /**
   * @brief Multiplies two float numbers
   * 
   */
  void mult() {
    this->op_type = SC_FPU_MULT;
    this->event_op.notify(3, SC_NS);
  }

  /**
   * @brief Subtracts two float numbers
   * 
   */
  void subs()
  {
    this->op_type = SC_FPU_SUB;
    this->event_op.notify(1, SC_NS);
  }
};
