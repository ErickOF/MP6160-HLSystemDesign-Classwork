//-----------------------------------------------------
#include <systemc.h>

typedef enum {
  SC_FPU_ADD = 1,
  SC_FPU_SUB = 2,
  SC_FPU_MULT = 3,
  SC_FPU_DIV = 4
} sc_fpu_op_t;

SC_MODULE (fpu_unit) {
  
  //-----------Internal variables-------------------
  float op_a;
  float op_b;
  float *op_c;
  sc_fpu_op_t op_type;

  sc_event event_op;

  // Constructor for fpu
  SC_HAS_PROCESS(fpu_unit);
  fpu_unit(sc_module_name name) : sc_module(name) {
    SC_THREAD(exec_op);
  } // End of Constructor

  //------------Code Starts Here-------------------------
  void add(float op_a, float op_b, float *op_c) {
    this->op_a = op_a;
    this->op_b = op_b;
    this->op_c = op_c;
    this->op_type = SC_FPU_ADD;
    this->event_op.notify(1, SC_NS);
  }

  void subs(float op_a, float op_b, float *op_c) {
    this->op_a = op_a;
    this->op_b = op_b;
    this->op_c = op_c;
    this->op_type = SC_FPU_SUB;
    this->event_op.notify(1, SC_NS);
  }

  void mult(float op_a, float op_b, float *op_c) {
    this->op_a = op_a;
    this->op_b = op_b;
    this->op_c = op_c;
    this->op_type = SC_FPU_MULT;
    this->event_op.notify(2, SC_NS);
  }

  void div(float op_a, float op_b, float *op_c) {
    this->op_a = op_a;
    this->op_b = op_b;
    this->op_c = op_c;
    this->op_type = SC_FPU_DIV;
    this->event_op.notify(3, SC_NS);
  }

  void exec_op() {
    while (true) {
      wait(event_op);

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
};
