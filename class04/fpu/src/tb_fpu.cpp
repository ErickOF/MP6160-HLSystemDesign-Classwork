#include <systemc.h>
#ifdef FPU_PV_MODEL
#include "sc_fpu_pv_model.cpp"
#elif defined(FPU_LT_MODEL)
#include "sc_fpu_lt_model.cpp"
#elif defined(FPU_AT_MODEL)
#include "sc_fpu_at_model.cpp"
#elif defined(FPU_CA_MODEL)
#include "sc_fpu_ca_model.cpp"
#else
#error "No model specified"
#endif // FPU_AT_MODEL

#ifndef TB_NAME
#define TB_NAME "default"
#endif // TB_NAME

int sc_main (int, char*[])
{
#ifndef FPU_AT_MODEL
  float op_a;
  float op_b;
  float op_c;
#else
  sc_signal<float> op_a;
  sc_signal<float> op_b;
  sc_signal<float> op_c;
#endif // FPU_AT_MODEL

  fpu_unit fpu("fpu");
#ifdef FPU_AT_MODEL
  fpu.op_a(op_a);
  fpu.op_b(op_b);
  fpu.op_c(op_c);
#endif // FPU_AT_MODEL

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

#ifndef FPU_AT_MODEL
  printf("ADD: op_a = %0.2f, op_b = %0.2f\n", op_a, op_b);
#else
  printf("ADD: op_a = %0.2f, op_b = %0.2f\n", op_a.read(), op_b.read());

#endif // FPU_AT_MODEL

#ifdef FPU_PV_MODEL
  fpu.add(op_a, op_b, op_c);
#elif defined(FPU_LT_MODEL)
  fpu.add(op_a, op_b, &op_c);
  sc_start(5, SC_NS);
#elif defined(FPU_AT_MODEL)
  fpu.add();
  sc_start(5, SC_NS);
#elif defined(FPU_CA_MODEL)
#endif // FPU_XX_MODEL

#ifndef FPU_AT_MODEL
  printf("RESULT: op_c = %0.2f\n", op_c);
#else
  cout << "@" << sc_time_stamp();
  printf(" - RESULT: op_c = %0.2f\n", op_c.read());
#endif // FPU_AT_MODEL

#ifndef FPU_AT_MODEL
  printf("SUBS: op_a = %0.2f, op_b = %0.2f\n", op_a, op_b);
#else
  printf("SUBS: op_a = %0.2f, op_b = %0.2f\n", op_a.read(), op_b.read());
#endif // FPU_AT_MODEL

#ifdef FPU_PV_MODEL
  fpu.subs(op_a, op_b, op_c);
#elif defined(FPU_LT_MODEL)
  fpu.subs(op_a, op_b, &op_c);
  sc_start(5, SC_NS);
#elif defined(FPU_AT_MODEL)
  fpu.subs();
  sc_start(5, SC_NS);
#elif defined(FPU_CA_MODEL)
#endif // FPU_XX_MODEL

#ifndef FPU_AT_MODEL
  printf("RESULT: op_c = %0.2f\n", op_c);
#else
  cout << "@" << sc_time_stamp();
  printf(" - RESULT: op_c = %0.2f\n", op_c.read());
#endif // FPU_AT_MODEL

#ifndef FPU_AT_MODEL
  printf("MULT: op_a = %0.2f, op_b = %0.2f\n", op_a, op_b);
#else
  printf("MULT: op_a = %0.2f, op_b = %0.2f\n", op_a.read(), op_b.read());
#endif // FPU_AT_MODEL

  op_b = 10.0f;
#ifdef FPU_PV_MODEL
  fpu.mult(op_a, op_b, op_c);
#elif defined(FPU_LT_MODEL)
  fpu.mult(op_a, op_b, &op_c);
  sc_start(5, SC_NS);
#elif defined(FPU_AT_MODEL)
  fpu.mult();
  sc_start(5, SC_NS);
#elif defined(FPU_CA_MODEL)
#endif // FPU_XX_MODEL

#ifndef FPU_AT_MODEL
  printf("RESULT: op_c = %0.2f\n", op_c);
#else
  cout << "@" << sc_time_stamp();
  printf(" - RESULT: op_c = %0.2f\n", op_c.read());
#endif // FPU_AT_MODEL

#ifndef FPU_AT_MODEL
  printf("DIV: op_a = %0.2f, op_b = %0.2f\n", op_a, op_b);
#else
  printf("DIV: op_a = %0.2f, op_b = %0.2f\n", op_a.read(), op_b.read());
#endif // FPU_AT_MODEL
#ifdef FPU_PV_MODEL
  fpu.div(op_a, op_b, op_c);
#elif defined(FPU_LT_MODEL)
  fpu.div(op_a, op_b, &op_c);
  sc_start(5, SC_NS);
#elif defined(FPU_AT_MODEL)
  fpu.div();
  sc_start(5, SC_NS);
#elif defined(FPU_CA_MODEL)
#endif // FPU_XX_MODEL

#ifndef FPU_AT_MODEL
  printf("RESULT: op_c = %0.2f\n", op_c);
#else
  cout << "@" << sc_time_stamp();
  printf(" - RESULT: op_c = %0.2f\n", op_c.read());
#endif // FPU_AT_MODEL

  cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;

#ifndef FPU_PV_MODEL
  sc_close_vcd_trace_file(wf);
#endif // FPU_PV_MODEL

  // Terminate simulation
  return 0;
}
