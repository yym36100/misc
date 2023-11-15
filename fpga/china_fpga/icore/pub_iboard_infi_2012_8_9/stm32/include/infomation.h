/*------------------------------------------------------
FILE NAME   : infomation.h
DESCRIPTION : ---
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\r
--------------------------------------------------------*/
#ifndef __infomation_h__
#define __infomation_h__

//-----------------Include files-------------------------//
#include "..\include\color.h"

//----------------- Define ------------------------------//


//----------------- Typedef------------------------------//
typedef struct{
 	int (*initialize)(void);
	int (* show_function)(int,COLOR_T);
 
}INFOMATION_T; 


extern INFOMATION_T infomation;

#endif //__infomation_h__
