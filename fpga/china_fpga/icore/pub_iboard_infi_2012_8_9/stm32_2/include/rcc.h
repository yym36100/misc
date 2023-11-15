/*------------------------------------------------------
FILE NAME   : rcc.h
DESCRIPTION : rcc driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __rcc_h__
#define __rcc_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Typedef------------------------------//

typedef  struct{
	int (* initialize)(void);
}SYS_RCC_T;

//----------------- Extern ------------------------------//

extern SYS_RCC_T rcc;

#endif //__rcc_h__

