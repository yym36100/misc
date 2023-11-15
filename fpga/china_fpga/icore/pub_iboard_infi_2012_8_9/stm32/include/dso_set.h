/*------------------------------------------------------
FILE NAME   : dso_set.h
DESCRIPTION :  
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __dso_set_h__
#define __dso_set_h__

//-----------------Include files-------------------------//

 
 
//----------------- Define ------------------------------//

//----------------- Typedef------------------------------//
typedef const struct{
	int (* xscale)(void);
	int (* yscale)(void);
	int (* coupling)(void);
	int (* trigger_level)(void);
	int (* offset)(void);
}DSO_SET_T;

//----------------- Extern ------------------------------//
 
extern DSO_SET_T dso_set; 

#endif //__dso_set_h__
