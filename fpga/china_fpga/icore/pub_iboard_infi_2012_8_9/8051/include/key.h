/*------------------------------------------------------
FILE NAME   : key.h
DESCRIPTION : hardware file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __key_h__
#define __key_h__

//-----------------Include files-------------------------//

//-----------------define--------------------------------//
#define KEY_NONE	0
#define KEY_UP		255
#define KEY_DOWN	254

#define KEY_F1		126
#define KEY_F2		190	 
#define KEY_F3		222
#define KEY_F4		238
#define KEY_F5		125

#define KEY_M1		235
#define KEY_M2		219	 
#define KEY_M3		187
#define KEY_M4		123
#define KEY_M5		237


//----------------- Typedef -----------------------------//


extern unsigned char read_key(void);
extern unsigned char event;
 

#endif //__key_h__
















