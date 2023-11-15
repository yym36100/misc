/*------------------------------------------------------
FILE NAME   : frequency.h
DESCRIPTION : ---
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\r
--------------------------------------------------------*/
#ifndef __frequency_h__
#define __frequency_h__

//-----------------Include files-------------------------//


//----------------- Define ------------------------------//
 

//----------------- Typedef------------------------------//
typedef const struct{
	int (* set)(double);
}FREQUENCY_T;


extern FREQUENCY_T frequency;

#endif //__frequency_h__
