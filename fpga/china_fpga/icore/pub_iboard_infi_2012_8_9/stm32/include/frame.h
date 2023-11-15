/*------------------------------------------------------
FILE NAME   : frame.h
DESCRIPTION : ---
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\r
--------------------------------------------------------*/
#ifndef __frame_h__
#define __frame_h__

//-----------------Include files-------------------------//


//----------------- Define ------------------------------//


//----------------- Typedef------------------------------//
typedef struct{
	int (* set_window)(int);
	//int (* diagram)(void);
//	int (* infomation)(void);
	//int (* cymometer)(void);
}FRAME_T; 


extern FRAME_T frame;

#endif //__frame_h__
