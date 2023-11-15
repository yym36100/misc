/*------------------------------------------------------
FILE NAME   : dso.h
DESCRIPTION :  
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __dso_h__
#define __dso_h__

//-----------------Include files-------------------------//

 
 
//----------------- Define ------------------------------//

#define COUPLING_DC		0
#define COUPLING_AC		1
#define COUPLING_GND	2

//----------------- Typedef------------------------------//
 
  
typedef struct{
	int x_scale;
	int y_scale;
	int trigger_type;
	int coupling;
	float offset;
	float trigger_level;
	int trigged;
	int about_flag;

	float frequency;
	float period;
	float vpp;
	float vrms;
	float vavg;
	int measure_number;
	int (* main)(void);
}DSO_T;
//----------------- Extern ------------------------------//
 
extern DSO_T dso;


#endif //__dso_h__
