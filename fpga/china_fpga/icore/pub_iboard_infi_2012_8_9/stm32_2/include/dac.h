/*------------------------------------------------------
FILE NAME   : dac.h
DESCRIPTION : nvic driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __dac_h__
#define __dac_h__

//------------------- Define ---------------------------//
#define	 DAC_SEL0_OUTPUT	GPIOC->CRH.B.MODE9=0X3;\
							GPIOC->CRH.B.CNF9=0

#define	 DAC_SEL1_OUTPUT	GPIOC->CRH.B.MODE8=0X3;\
							GPIOC->CRH.B.CNF8=0

#define	 DAC_SEL2_OUTPUT	GPIOC->CRL.B.MODE7=0X3;\
							GPIOC->CRL.B.CNF7=0

#define	DAC_SEL0_ON			GPIOC->BSRR.B.SETIO9=1
#define DAC_SEL0_OFF		GPIOC->BSRR.B.CLRIO9=1


#define	DAC_SEL1_ON			GPIOC->BSRR.B.SETIO8=1
#define DAC_SEL1_OFF		GPIOC->BSRR.B.CLRIO8=1


#define	DAC_SEL2_ON			GPIOC->BSRR.B.SETIO7=1
#define DAC_SEL2_OFF		GPIOC->BSRR.B.CLRIO7=1



#define VREF 2.482

//----------------- Typedef------------------------------//

typedef  struct{
	int (* initialize)(void);
	int (* set)(void);
	float dso_vgan;
	float dso_offset;
	float arb_offset;
	float edac;
	float arb_amp;
	float trig_dc;
	float dso_vgap;


}DA_T;

//----------------- Extern ------------------------------//

extern DA_T dac;
extern int dac_value[];

#endif //__dac_h__

