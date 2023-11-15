/*------------------------------------------------------
FILE NAME   : function.h
DESCRIPTION : iBoard function file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __function_h__
#define __function_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Typedef -----------------------------//
#define	EVENT_CLEAR	0


typedef  struct{
	int (* main)(void);
 

}FUNCTION_T;


//----------------- Extern ------------------------------//

extern FUNCTION_T function;


#endif //__function_h__


