/*------------------------------------------------------
FILE NAME   : lm75.h
DESCRIPTION : lm75 driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __lm75_h__
#define __lm75_h__

//-----------------Include files-------------------------//


 #define LM75	0X90

//----------------- Typedef------------------------------//


//----------------- Extern ------------------------------//
extern float lm75_read(void);

#endif //__lm75_h__
