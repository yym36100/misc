/*------------------------------------------------------
   FILE NAME   : fsmc.c
   DESCRIPTION : fsmc driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\fsmc.h"

//---------------- Function Prototype -------------------//

static int initialize(void);


//---------------- Variable -----------------------------//

FSMC_T fsmc = {
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
static int initialize(void)
{
	GPIOD->CRH.W = 0xbbbbbbbb;
	GPIOD->CRL.W = 0xbbbbbbbb;

	GPIOE->CRH.W = 0xbbbbbbbb;
	GPIOE->CRL.W = 0xbbbbbbbb;

	FSMC_Bank1->BCR1 &= ~(1 << 1 | 1 << 2 | 1 << 3);

	FSMC_Bank1->BCR1 |= 1 << 14; //EXTMOD

	FSMC_Bank1->BTR1 = 0x601;

	FSMC_Bank1E->BWTR1 = 0X300;

	return 0;
}


