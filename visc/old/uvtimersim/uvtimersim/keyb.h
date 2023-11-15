#include "pic18.h"
#include "cdef.h"

#define keyb_debtime	(40)
#define keyb_nrbutt		(2)

typedef struct keyb_bs{
	u8 cs,os,p,h,cnt;
}keyb_bs;

extern keyb_bs butt[keyb_nrbutt];

void keyb_processbuttons(void); 