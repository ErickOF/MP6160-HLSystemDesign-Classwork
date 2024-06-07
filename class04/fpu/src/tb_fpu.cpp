#include <systemc.h>
#ifdef FPU_PV_MODEL
#include "sc_fpu_pv_model.cpp"
#elif defined(FPU_LT_MODEL)
#include "sc_fpu_lt_model.cpp"
#elif defined(FPU_AT_MODEL)
#include "sc_fpu_at_model.cpp"
#elif defined(FPU_AC_MODEL)
#include "sc_fpu_ac_model.cpp"
#else
#error "No model specified"
#endif // FPU_AT_MODEL

#ifndef TB_NAME
#define TB_NAME "default"
#endif // TB_NAME

int sc_main (int, char*[])
{
  float op_a, op_b, op_c;

  fpu_unit fpu("fpu");

#ifndef FPU_PV_MODEL
  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file(TB_NAME);
  wf->set_time_unit(1, SC_NS);

  // Dump the desired signals
  sc_trace(wf, op_a, "op_a");
  sc_trace(wf, op_b, "op_b");
  sc_trace(wf, op_c, "op_c");
#endif // FPU_PV_MODEL

  sc_start();

  cout << "@" << sc_time_stamp() << endl;

  printf("Writing in zero time\n");

  op_a = 5.5f;
  op_b = 5.3f;

  printf("ADD: op_a = %0.2f, op_b = %0.2f\n", op_a, op_b);
#ifdef FPU_PV_MODEL
  fpu.add(op_a, op_b, op_c);
#elif defined(FPU_LT_MODEL)
  fpu.add(op_a, op_b, &op_c);
  sc_start(5, SC_NS);
#elif defined(FPU_AT_MODEL)
#elif defined(FPU_AC_MODEL)
#endif
  printf("RESULT: op_c = %0.2f\n", op_c);

  printf("SUBS: op_a = %0.2f, op_b = %0.2f\n", op_a, op_b);
#ifdef FPU_PV_MODEL
  fpu.subs(op_a, op_b, op_c);
#elif defined(FPU_LT_MODEL)
  fpu.subs(op_a, op_b, &op_c);
  sc_start(5, SC_NS);
#elif defined(FPU_AT_MODEL)
#elif defined(FPU_AC_MODEL)
#endif
  printf("RESULT: op_c = %0.2f\n", op_c);

  printf("MULT: op_a = %0.2f, op_b = %0.2f\n", op_a, op_b);
  op_b = 10.0f;
#ifdef FPU_PV_MODEL
  fpu.mult(op_a, op_b, op_c);
#elif defined(FPU_LT_MODEL)
  fpu.mult(op_a, op_b, &op_c);
  sc_start(5, SC_NS);
#elif defined(FPU_AT_MODEL)
#elif defined(FPU_AC_MODEL)
#endif
  printf("RESULT: op_c = %0.2f\n", op_c);

  printf("DIV: op_a = %0.2f, op_b = %0.2f\n", op_a, op_b);
#ifdef FPU_PV_MODEL
  fpu.div(op_a, op_b, op_c);
#elif defined(FPU_LT_MODEL)
  fpu.div(op_a, op_b, &op_c);
  sc_start(5, SC_NS);
#elif defined(FPU_AT_MODEL)
#elif defined(FPU_AC_MODEL)
#endif
  printf("RESULT: op_c = %0.2f\n", op_c);

  cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;

#ifndef FPU_PV_MODEL
  sc_close_vcd_trace_file(wf);
#endif // FPU_PV_MODEL

  // Terminate simulation
  return 0;
}
