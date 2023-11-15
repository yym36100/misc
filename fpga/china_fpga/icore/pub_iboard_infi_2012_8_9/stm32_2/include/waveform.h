/*------------------------------------------------------
FILE NAME   : waveform.h
DESCRIPTION : ---
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\r
--------------------------------------------------------*/
#ifndef __waveform_h__
#define __waveform_h__

//-----------------Include files-------------------------//


//----------------- Define ------------------------------//
#define	SINE	0
#define	SQUA	1
#define	TRI		2
#define	RAMP	3	
#define	NRAM	4
#define	SINC	5
#define	NOISE	6
#define	EXPR	7
#define	EXPF	8
#define FULL_SIN_P	9
#define FULL_SIN_N	10
#define HALF_SIN_P	11
#define HALF_SIN_N	12
#define GAUSSIAN	13
#define	DC			14
#define	ARB			15


//----------------- Typedef------------------------------//
typedef const struct{
	int (* set)(int /* wave */,float /* sp */);
}WAVEFORM_T;


extern WAVEFORM_T waveform;

#endif //__waveform_h__

