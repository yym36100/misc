/*------------------------------------------------------
   FILE NAME   : systick.c
   DESCRIPTION : systick driver for stm32
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\systick.h"
#include "..\include\beep.h"
#include "..\include\dac.h"
#include "..\include\event.h"
#include "..\include\usart.h"
#include "..\include\clock.h"

#include <stdlib.h>
#include <string.h>



//---------------- Function Prototype -------------------//

static int initialize(void);
int event = 0;


//---------------- Variable -----------------------------//

SYS_TICK_T systick = {
	.initialize = initialize,
	.flash_trig = 0,
};

const int f_event_queue[] = {
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5
};

//-----------------Function------------------------------//
static int get_event(void)
{
	char *p;

	if (usart1.receive_ok_flag) {
		if (memcmp(usart1.receive_buffer, "event", strlen("event")) == 0) {
			p = strchr(usart1.receive_buffer, ' ');
			p++;
			event = atoi(p);
		}

		if (memcmp(usart1.receive_buffer, "RTC", strlen("RTC")) == 0) {
			p = strchr(usart1.receive_buffer, ' ');
			p++;
			calendar.year = atoi(p);

			p = strchr(p, ',');
			p++;
			calendar.month = atoi(p);

			p = strchr(p, ',');
			p++;
			calendar.day = atoi(p);

			p = strchr(p, ',');
			p++;
			calendar.hour = atoi(p);

			p = strchr(p, ',');
			p++;
			calendar.minute = atoi(p);

			p = strchr(p, ',');
			p++;
			calendar.second = atoi(p);
		}



		usart1.receive_ok_flag = 0;
	}
	return 0;
}
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

int read_key(void)
{
	if ((GPIOC->IDR.W & 1 << 6) == 0) return KEY_OK;
	else if ((GPIOA->IDR.W & 1 << 8) == 0) return KEY_LEFT;
	else if ((GPIOB->IDR.W & 1 << 15) == 0) return KEY_RIGHT;
	else return 0;
}

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
	SYSTICK->LOAD.B.RELOAD = 90000;  //1MS
	SYSTICK->CTRL.B.ENABLE = 1;
	SYSTICK->CTRL.B.TICKINT = 1;
	SYSTICK->CTRL.B.CLKSOURCE = 0;
	return 0;
}
/*-------------------------------------------------------
   NAME       : SysTick_Handler
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
void SysTick_Handler(void)
{
	static int i = 6;
	static int key_code_bak = 0;
	int key_code = 0;
	static int counter = 0;


	if (counter++ == 25) {
		systick.flash_trig = 1;
	}else if (counter == 50) {
		systick.flash_trig = 2;
		counter = 0;
	}

	get_event();

	DAC_SEL0_ON;
	DAC_SEL1_ON;
	DAC_SEL2_ON;

	DAC->DHR12R1.B.DACC1DHR = dac_value[i];
	DAC->SWTRIGR.B.SWTRIG1 = 1;


	if (i & 0x01) {
		DAC_SEL0_ON;
	}else {
		DAC_SEL0_OFF;
	}


	if (i & 0x02) {
		DAC_SEL1_ON;
	}else {
		DAC_SEL1_OFF;
	}


	if (i & 0x04) {
		DAC_SEL2_ON;
	}else {
		DAC_SEL2_OFF;
	}


	i--;

	if (i < 0) i = 6;

	//read key
	key_code = read_key();

	if (key_code == key_code_bak || key_code == 0) {
		key_code_bak = key_code;
		return;
	}
	event = key_code;
	key_code_bak = key_code;
}

