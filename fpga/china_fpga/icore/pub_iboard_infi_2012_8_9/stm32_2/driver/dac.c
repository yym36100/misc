/*------------------------------------------------------
   FILE NAME   : dac.c
   DESCRIPTION : dac driver for stm32
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   ------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\dac.h"


//---------------- Function Prototype -------------------//

static int initialize(void);
static int set(void);

int dac_value[10];

//---------------- Variable -----------------------------//

DA_T dac = {
	.initialize = initialize,
	.set = set
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
initialize(void)
{
	GPIOA->CRL.B.MODE5 = 0X3;         //PA4 as DAC output
	GPIOA->CRL.B.CNF5 = 2;

	DAC->CR.B.TEN1 = 1;
	DAC->CR.B.BOFF1 = 1;

	DAC->CR.B.TSEL1 = 7;              //software trig

	DAC->CR.B.EN1 = 1;


	//DAC Sweep control
	DAC_SEL0_OUTPUT;
	DAC_SEL1_OUTPUT;
	DAC_SEL2_OUTPUT;

	dac.arb_amp = 2.4;
	dac.arb_offset = 1.25;
	dac.dso_offset = 1;
	dac.dso_vgap = 0.0;
	dac.dso_vgan = 2;
	dac.edac = 1.0;
	dac.trig_dc = 1.2;

	set();

	return 0;
}
/*-------------------------------------------------------
   NAME       : set
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
set(void)
{
	dac_value[0] = (dac.dso_vgan / VREF) * 4095;
	dac_value[1] = (dac.dso_offset / VREF) * 4095; //dac.dso_offset;
	dac_value[2] = (dac.arb_offset / VREF) * 4095;  //arb offset
	dac_value[3] = (dac.edac / VREF) * 4095; //dac.edaca;
	dac_value[4] = (dac.arb_amp / VREF) * 4095; //dac.arb_amp;

	dac_value[5] = (dac.trig_dc / VREF) * 4095; //dac.edacb;

	dac_value[6] = (dac.dso_vgap / VREF) * 4095; //dac.dso_vgap;

	return 0;
}
