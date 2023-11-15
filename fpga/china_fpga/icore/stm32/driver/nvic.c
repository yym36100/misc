
#include "..\include\hardware.h"
#include "..\include\nvic.h"


static int initialize(void);


SYSNVIC_T nvic = {
	.initialize = initialize,
};


static int initialize(void)
{
	SCB->VTOR.W = ((unsigned long)0x08000000); //Set the Vector Table base location at 0x08000000

	NVIC->IPR10.W = 0x00000000;

	NVIC->ISER2.B.USART1_ = 1;

	return 0;
}
