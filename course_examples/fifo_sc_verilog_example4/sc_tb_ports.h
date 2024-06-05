#ifndef SC_TB_PORTS_H
#define SC_TB_PORTS_H

// Define Complex Type of Input and Out for DUT
struct tagInput {
  unsigned long  clk;
  unsigned long  data_out;
  unsigned long  empty;
  unsigned long  full; 
  unsigned long  rd_pointer; //whitebox 
  unsigned long  wr_pointer; //whitebox 
};

struct tagOutput {
  unsigned long  rst;
  unsigned long  wr_cs;
  unsigned long  rd_cs;
  unsigned long  data_in;
  unsigned long  rd_en;
  unsigned long  wr_en;
  int done;
};

typedef struct tagInput    INVECTOR;
typedef struct tagOutput  OUTVECTOR;

#endif
