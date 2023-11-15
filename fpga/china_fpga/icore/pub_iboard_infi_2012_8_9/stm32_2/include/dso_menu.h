/*------------------------------------------------------
FILE NAME   : dso_menu.h
DESCRIPTION :  
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __dso_menu_h__
#define __dso_menu_h__

//-----------------Include files-------------------------//

 
 
//----------------- Define ------------------------------//
#define MEASURE_FREQUENCY	0
#define MEASURE_VPP			1
#define MEASURE_VRMS		2
#define MEASURE_VAVG		3
 

//----------------- Typedef------------------------------//
typedef struct{
	int type;
	char buffer[30];
}MEASURE_BUFFER_T; 
//----------------- Extern ------------------------------//
 
extern int dso_menu(void);
extern MEASURE_BUFFER_T measure_buffer[4];

#endif //__dso_menu_h__
