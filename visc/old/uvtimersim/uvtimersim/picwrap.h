#include "cdef.h"

extern u8 buttonstate[2];
extern u8 dispbuffer[10];
void CSHDL_vInitReset(void);
void CAM_v25Active(void);
void DISP_vUpdate(char *t);