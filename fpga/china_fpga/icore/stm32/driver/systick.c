

#include "..\include\hardware.h"
#include "..\include\systick.h"
#include "..\include\usart.h"
#include "..\include\key.h"

#include <stdlib.h>
#include <string.h>


static int initialize(void);


SYS_TICK_T systick = {
	.initialize = initialize
};

static int initialize(void) {
	SYSTICK->LOAD.B.RELOAD = 90000;  //9MHz main clock,90000 = 10ms
	SYSTICK->CTRL.B.ENABLE = 1;
	SYSTICK->CTRL.B.TICKINT = 1;
	SYSTICK->CTRL.B.CLKSOURCE = 0;
	return 0;
}

void SysTick_Handler(void) {
	static int counter = 0;
	static int i = 0;
	static int key_code_bak = 0;
	int key_code = 0;

	counter++;
	if (counter > 50) { //500ms
		counter = 0;
		if (i++ % 5) LED_ON;
		else LED_OFF;
	}
	//read key
	key_code = key.read();

	if (key_code == key_code_bak || key_code == 0) {
		key_code_bak = key_code;
		return;
	}
	event = key_code;
	key_code_bak = key_code;
}
