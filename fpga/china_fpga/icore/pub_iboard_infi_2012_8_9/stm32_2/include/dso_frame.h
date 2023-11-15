/*------------------------------------------------------
FILE NAME   : dso_frame.h
DESCRIPTION :  
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __dso_frame_h__
#define __dso_frame_h__

//-----------------Include files-------------------------//

 
 
//----------------- Define ------------------------------//

 

//----------------- Typedef------------------------------//

typedef const struct{
 	int (* grid)(void);
	int (* gnd)(void);
	int (* position)(void);
	int (* trig)(void);
	int (* xscale)(void);
	int (* yscale)(void);
	int (* measure)(int);
	int (* trig_icon)(int);
	int (* title)(void);
	int (* coupling)(void);
	int (* trigged)(void);
	int (* main)(void);
	int (* about)(void);
	
	
	 
}DSO_FRAME_T;
//----------------- Extern ------------------------------//
 
extern DSO_FRAME_T dso_frame;
extern int last;


#endif //__dso_frame_h__
