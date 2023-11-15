/*------------------------------------------------------
   FILE NAME   : pwm.c
   DESCRIPTION : pwm driver for evtft36 / evtft43 /evga86
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\pwm.h"

//---------------- Function Prototype -------------------//

static int initialize(int /* bl */);


//---------------- Variable -----------------------------//
PWM_T pwm = {
	.initialize = initialize
};

//-----------------Function------------------------------//
/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
initialize(int bl)
{
	float temp = 100 - bl;

	GPIOA->CRL.B.MODE6 = 0x3;       //	50M  //PA6 AS TFT back light
	GPIOA->CRL.B.CNF6 = 0x2;        // ¸´ÓÃ ÍÆÍì


	TIM3->CCMR1.B_COMP.CC1S = 0;
	TIM3->CCMR1.B_COMP.OC1FE = 1;
	TIM3->CCMR1.B_COMP.OC1M = 6; //pmw mode 1
	TIM3->CCMR1.B_COMP.OC1PE = 1; //auto load

	temp /= 100.0;
	temp *= 65535;

	TIM3->ARR = 65535; //Ô¤×°¼Ä´æÆ÷
	TIM3->CCR1 = temp; //

	TIM3->PSC = 3;

	TIM3->CCER.B.CC1E = 1;

	TIM3->CR1.B.ARPE = 1;
	TIM3->CR1.B.DIR = 1;
	TIM3->CR1.B.CEN = 1;







	return 0;
}

