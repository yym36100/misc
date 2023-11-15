/*------------------------------------------------------
FILE NAME   : beep.h
DESCRIPTION : beep driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __beep_h__
#define __beep_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Define ------------------------------//
#define	DO	523
#define	RE	578
#define	MI	659
#define	FA	698
#define	SO	784
#define	LA	880
#define	SI	988

#define HDO	1046
#define	HRE	1175
#define	HMI	1318
#define	HFA	1397
#define	HSO	1568
#define	HLA	1760
#define	HSI	1976

//----------------- Typedef -----------------------------//
typedef struct{
	int (* initialize)(void);
	int (* frequency)(int );
}BEEP_T;

//---------------- Extern -------------------------------//

extern BEEP_T beep;


#endif //__beep_h__
