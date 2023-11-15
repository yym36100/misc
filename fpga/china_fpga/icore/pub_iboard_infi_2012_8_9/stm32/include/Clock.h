/*------------------------------------------------------
FILE NAME   : clock.h
DESCRIPTION : clock header
VERSION     : 0.0.0
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\

--------------------------------------------------------*/

#ifndef __clock_h__
#define __clock_h__


//---------------- Include Files ------------------------//

//----------------- Define ------------------------------//
 


//----------------- Data Struct -------------------------//

typedef struct{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	float temp;
}CALENDAR_T;

//---------------- Extern Resource ----------------------//

extern CALENDAR_T calendar;

#endif //__clock_h__

