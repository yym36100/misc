/*------------------------------------------------------
FILE NAME   : meter.h
DESCRIPTION : meter driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __meter_h__
#define __meter_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Typedef -----------------------------//
typedef struct{
	double value;
	int range;
}MEASURE_T;

typedef struct{
	double k;
	double b;
	double min;
	double max;
	}CAL_T;
	
		
typedef struct{
	int (* main)(void);
}METER_T;

//---------------- Extern -------------------------------//

extern const METER_T meter;


#endif //__meter_h__
