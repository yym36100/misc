/*------------------------------------------------------
FILE NAME   : tab.h
DESCRIPTION : gui tab driver
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __tab_h__
#define __tab_h__

//-----------------Include files-------------------------//

 
#include "..\include\color.h"
#include "..\include\font.h"

//----------------- Define ------------------------------//

 


//----------------- Typedef------------------------------//
typedef struct{
	int x;
	int y;
	int height;
	int width;
	int active;
	char ** title;
	DOUBLE_BYTE_FONT_T * dfont;
	SINGLE_BYTE_FONT_T * sfont;
	
}TAB_T;


//----------------- Extern ------------------------------//
extern int tab(TAB_T *); 

#endif //__tab_h__
