/*------------------------------------------------------
FILE NAME   : diagram.h
DESCRIPTION : iBoard diagram header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2011-12-18
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __diagram_h__
#define __diagram_h__

//-----------------Include files-------------------------//

 
//----------------- Define ------------------------------//

 


//----------------- Typedef------------------------------//
typedef struct{
	int (* show)(int /* active */,float);
 
}DIAGRAM_T;
 
//----------------- Extern ------------------------------//

extern const DIAGRAM_T diagram;

#endif //__diagram_h__
