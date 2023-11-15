/*------------------------------------------------------
FILE NAME   : offset.h
DESCRIPTION : ---
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\r
--------------------------------------------------------*/
#ifndef __offset_h__
#define __offset_h__

//-----------------Include files-------------------------//


//----------------- Define ------------------------------//
 

//----------------- Typedef------------------------------//
typedef const struct{
	int (* set)(double);
}OFFSET_T;


extern OFFSET_T offset;

#endif //__offset_h__
