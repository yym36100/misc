/*------------------------------------------------------
   FILE NAME   : nvic.c
   DESCRIPTION : nvic driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\nvic.h"

//---------------- Function Prototype -------------------//

static int initialize(void);

//---------------- Variable -----------------------------//

SYSNVIC_T nvic = {
	.initialize = initialize,
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
	SCB->VTOR.W = ((unsigned long)0x08000000); //Set the Vector Table base location at 0x08000000

	//uart0
	NVIC->IPR10.W = 0x00000000;
	NVIC->ISER2.W = 0x00000020;

	return 0;
}


