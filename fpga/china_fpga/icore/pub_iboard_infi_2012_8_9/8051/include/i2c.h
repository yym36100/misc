/*------------------------------------------------------
FILE NAME   : i2c.h
DESCRIPTION : i2c driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __i2c_h__
#define __i2c_h__

//-----------------Include files-------------------------//
 


//----------------- Typedef------------------------------//
 

//----------------- Extern ------------------------------//
extern int read_nbyte(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no);
extern int write_nbyte(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no);


#endif //__i2c_h__
