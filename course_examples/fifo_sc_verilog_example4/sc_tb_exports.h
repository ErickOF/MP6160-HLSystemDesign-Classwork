#include "sc_tb.h"

#ifndef SC_TB_EXPORTS_H
#define SC_TB_EXPORTS_H

#ifdef __cplusplus
extern "C" {
#endif
void init_sc     ();
void exit_sc     ();
void sample_hdl  (void *Invector);
void drive_hdl   (void *Outvector);
void advance_sim (sc_time simtime);
void exec_sc     (void *invector, void *outvector, sc_time simtime);
#ifdef __cplusplus
}
#endif

#endif
