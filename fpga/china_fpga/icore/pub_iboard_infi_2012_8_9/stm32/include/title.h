/*------------------------------------------------------
FILE NAME   : title.h
DESCRIPTION : iBoard title header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2011-12-18
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __title_h__
#define __title_h__

//-----------------Include files-------------------------//

 
//----------------- Define ------------------------------//

 


//----------------- Typedef------------------------------//
typedef struct{
	int (* wave_index)(int /* active */);
	int (* overflow)(void);
	int (* name)(void);
}TITLE_T;
 
//----------------- Extern ------------------------------//

extern const TITLE_T title;

#endif //__title_h__
