
#include "picwrap.h"
#include "string.h"

u8 buttonstate[2];
u8 dispbuffer[10];
u8 dbgmsgbuffer[80];

u8 volatile dummy;

extern void app_v25Active(void);
extern void app_vInit(void);

void CSHDL_vInitReset(void)
{
	app_vInit();
}

void CAM_v25Active(void)
{
	dummy++;
	app_v25Active();
}

void DISP_vUpdate(char *t)
{
	strcpy(dispbuffer,t);
}

