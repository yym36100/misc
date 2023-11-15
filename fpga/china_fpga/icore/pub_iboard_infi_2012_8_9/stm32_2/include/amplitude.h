/*------------------------------------------------------
FILE NAME   : amplitude.h
DESCRIPTION : ---
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\r
--------------------------------------------------------*/
#ifndef __amplitude_h__
#define __amplitude_h__

//-----------------Include files-------------------------//


//----------------- Define ------------------------------//
 

//----------------- Typedef------------------------------//
typedef const struct{
	int (* set)(double);
}AMPLITUDE_T;


extern AMPLITUDE_T amplitude;

#endif //__amplitude_h__
