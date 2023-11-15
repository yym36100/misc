/*------------------------------------------------------
FILE NAME   : nvic.h
DESCRIPTION : nvic driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __nvic_h__
#define __nvic_h__

//-----------------Include files-------------------------//

//----------------- Typedef------------------------------//

typedef  struct{
	int (* initialize)(void);
}SYSNVIC_T;

//----------------- Extern ------------------------------//

extern SYSNVIC_T nvic;

#endif //__nvic_h__
