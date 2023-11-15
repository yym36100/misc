/*------------------------------------------------------
FILE NAME   : button.h
DESCRIPTION : -
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __button_h__
#define __button_h__

//-----------------Include files-------------------------//

#include "..\include\hardware.h"
#include "..\include\color.h"

//----------------- Define ------------------------------//

 


//----------------- Typedef------------------------------//
typedef struct{
	int (* drawb)( char *[5],int active);
	int (* drawl)( char *[5],int active);
	void * main;
	int active;
}BUTTON_T ;
 

//----------------- Extern ------------------------------//
extern BUTTON_T button;
 

#endif //__button_h__
