/*------------------------------------------------------
FILE NAME   : main.h
DESCRIPTION :  
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __main_h__
#define __main_h__

//-----------------Include files-------------------------//

 
 
//----------------- Define ------------------------------//


#define LANGUAGE_CN		0
 #define LANGUAGE_EN	1


//----------------- Typedef------------------------------//
typedef struct{
	int current;
	int sum;
}PAGE_T;

typedef struct{
 	int language;
	int output;
	int color;
	int brightness;
	PAGE_T page;
}SYS_T;



//----------------- Extern ------------------------------//
 
extern SYS_T sys;

extern const char rev[];
 
extern int first_run;

#endif //__main_h__
