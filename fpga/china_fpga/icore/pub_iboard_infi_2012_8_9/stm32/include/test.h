/*------------------------------------------------------
FILE NAME   : test.h
DESCRIPTION :  
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2012-03-22
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __test_h__
#define __test_h__

//-----------------Include files-------------------------//

 
 
//----------------- Define ------------------------------//



//----------------- Typedef------------------------------//
typedef const struct{
	int (* key)(void);
	int (* lcd)(void);
}TEST_T;

//----------------- Extern ------------------------------//
extern TEST_T test;

#endif //__test_h__
