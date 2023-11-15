/*------------------------------------------------------
FILE NAME   : ds1302.h
DESCRIPTION : hardware file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __ds1302_h__
#define __ds1302_h__

//-----------------Include files-------------------------//
 

//----------------- Typedef -----------------------------//

typedef struct{
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
	unsigned char month;
	unsigned char week;
	unsigned char year;
}RTC_T;

extern void init_ds1302(void);
extern void get_ds1302(void);
extern void set_ds1302(unsigned char *);

extern RTC_T rtc;

#endif //__ds1302_h__
















