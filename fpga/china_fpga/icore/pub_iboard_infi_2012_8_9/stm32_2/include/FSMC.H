/*------------------------------------------------------
FILE NAME   : fsmc.h
DESCRIPTION : fsmc driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __fsmc_h__
#define __fsmc_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Typedef -----------------------------//
typedef struct{
	int (* initialize)(void);

}FSMC_T;

//---------------- Extern -------------------------------//

extern FSMC_T fsmc;


#endif //__fsmc_h__
