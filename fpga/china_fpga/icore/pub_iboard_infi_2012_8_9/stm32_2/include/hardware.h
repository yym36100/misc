/*------------------------------------------------------
FILE NAME   : hardware.h
DESCRIPTION : hardware file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __hardware_h__
#define __hardware_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Typedef -----------------------------//
 
#define	 LED_OUTPUT	  GPIOE->CRL.B.MODE2=0X3;\
						  GPIOE->CRL.B.CNF2=0


#define	LED_ON		GPIOE->BSRR.B.SETIO2=1
#define LED_OFF	GPIOE->BSRR.B.CLRIO2=1


#define	 TFTBL	  GPIOA->CRL.B.MODE6=0X3;\
						  GPIOA->CRL.B.CNF6=0


#define	TFTBLON		GPIOA->BSRR.B.SETIO6=1
#define TFTBLOFF	GPIOA->BSRR.B.CLRIO6=1


#define ARB_ATT0_OUTPUT    GPIOB->CRH.B.MODE12=0X3;\
							GPIOB->CRH.B.CNF12=0
#define ARB_ATT1_OUTPUT    GPIOB->CRH.B.MODE13=0X3;\
							GPIOB->CRH.B.CNF13=0
#define ARB_ATT2_OUTPUT    GPIOB->CRH.B.MODE14=0X3;\
							GPIOB->CRH.B.CNF14=0

#define	ARB_ATT0_ON		GPIOB->BSRR.B.SETIO12=1
#define ARB_ATT0_OFF	GPIOB->BSRR.B.CLRIO12=1


#define	ARB_ATT1_ON		GPIOB->BSRR.B.SETIO13=1
#define ARB_ATT1_OFF	GPIOB->BSRR.B.CLRIO13=1


#define	ARB_ATT2_ON		GPIOB->BSRR.B.SETIO14=1
#define ARB_ATT2_OFF	GPIOB->BSRR.B.CLRIO14=1

#define SET_R0_OUTPUT    GPIOB->CRL.B.MODE2=0X3;\
						 GPIOB->CRL.B.CNF2=0

#define SET_R1_OUTPUT    GPIOB->CRL.B.MODE1=0X3;\
						 GPIOB->CRL.B.CNF1=0

#define SET_R2_OUTPUT    GPIOB->CRL.B.MODE0=0X3;\
						 GPIOB->CRL.B.CNF0=0

#define	SET_R0_ON		GPIOB->BSRR.B.SETIO2=1
#define SET_R0_OFF		GPIOB->BSRR.B.CLRIO2=1

#define	SET_R1_ON		GPIOB->BSRR.B.SETIO1=1
#define SET_R1_OFF		GPIOB->BSRR.B.CLRIO1=1

#define	SET_R2_ON		GPIOB->BSRR.B.SETIO0=1
#define SET_R2_OFF		GPIOB->BSRR.B.CLRIO0=1


#define	 DSO_ACDC_OUTPUT  GPIOB->CRH.B.MODE11=0X3;\
						  GPIOB->CRH.B.CNF11=0


#define	DSO_ACDC_ON		GPIOB->BSRR.B.SETIO11=1
#define DSO_ACDC_OFF	GPIOB->BSRR.B.CLRIO11=1


#define	 DSO_ATT_OUTPUT  GPIOB->CRH.B.MODE10=0X3;\
						  GPIOB->CRH.B.CNF10=0


#define	DSO_ATT_ON		GPIOB->BSRR.B.SETIO10=1
#define DSO_ATT_OFF	GPIOB->BSRR.B.CLRIO10=1







#endif //__hardware_h__
















