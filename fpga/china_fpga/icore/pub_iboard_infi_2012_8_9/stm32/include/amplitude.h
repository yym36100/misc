/*------------------------------------------------------
FILE NAME   : amplitude.h
DESCRIPTION : ---
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\r
--------------------------------------------------------*/
#ifndef __amplitude_h__
#define __amplitude_h__

//-----------------Include files-------------------------//
#include "..\include\hardware.h"

//----------------- Define ------------------------------//
#define  ATT_0DB	ARB_ATT0_ON;ARB_ATT1_ON;ARB_ATT2_OFF;
#define  ATT_10DB	ARB_ATT0_ON;ARB_ATT1_OFF;ARB_ATT2_OFF;
#define  ATT_20DB	ARB_ATT0_OFF;ARB_ATT1_ON;ARB_ATT2_OFF;
#define  ATT_30DB	ARB_ATT0_ON;ARB_ATT1_ON;ARB_ATT2_ON;
#define  ATT_40DB	ARB_ATT0_ON;ARB_ATT1_OFF;ARB_ATT2_ON;
#define  ATT_50DB	ARB_ATT0_OFF;ARB_ATT1_ON;ARB_ATT2_ON;
#define  ATT_60DB	ARB_ATT0_OFF;ARB_ATT1_OFF;ARB_ATT2_ON;
//----------------- Typedef------------------------------//
typedef const struct{
	int (* set)(double);
}AMPLITUDE_T;


extern AMPLITUDE_T amplitude;

#endif //__amplitude_h__
