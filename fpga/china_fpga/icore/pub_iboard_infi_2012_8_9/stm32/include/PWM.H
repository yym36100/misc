/*------------------------------------------------------
FILE NAME   : pwm.h
DESCRIPTION : pwm driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __pwm_h__
#define __pwm_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Typedef -----------------------------//
typedef struct{
	int (* initialize)(int /* light */);
}PWM_T;

//---------------- Extern -------------------------------//

extern PWM_T pwm;


#endif //__pwm_h__
