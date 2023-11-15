/*------------------------------------------------------
   FILE NAME   : main.c
   DESCRIPTION :
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2012-1-10
   MODIFY DATE :
   LOGS        :-\

  《iBoard 电子学堂》 DEMO代码
  博客：XiaomaGee.cnblogs.com
  论坛：www.oshcn.com
  店铺：i-Board.taobao.com
  QQ群：204255896	165201798	215053598	215054675	215055211

   --------------------------------------------------------*/

//-----------------Include files-------------------------//
#include "..\include\nvic.h"
#include "..\include\rcc.h"
#include "..\include\dac.h"
#include "..\include\usart.h"
#include "..\include\adc.h"
#include "..\include\hardware.h"
#include "..\include\systick.h"
#include "..\include\evtft.h"
#include "..\include\pwm.h"
#include "..\include\fpga.h"
#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\spi.h"
#include "..\include\flash.h"
#include "..\usb_include\usb.h"
#include "..\usb_include\usb_command.h"
#include "..\include\event.h"
#include "..\include\arb.h"
#include "..\include\main.h"
#include "..\include\dso.h"
#include "..\include\meter.h"
#include "..\include\power_on.h"


#include <string.h>
#include <stdlib.h>
#include <math.h>


SYS_T sys = {
	.color = COLOR_ORANGE,
	.language = 0,
	.brightness = 100
};



const char rev[] = {
#include "..\rev.dat"
};

int first_run = 1;

//-----------------Function------------------------------//
extern int clock_main(void);
/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
__asm void system_reset(void)
{
	MOV R0, # 1
	MSR FAULTMASK, R0
	LDR R0, = 0xE000ED0C
	LDR R1, = 0x05FA0004
	STR R1, [R0]

deadloop
	B deadloop
}

/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
int main(void)
{
	STRING_T s;
	int i, j;
	char * main_str[2][4] = {
		{ " 信号源 ", " 示波器 ", " 电压表 ", " 时 钟 " },
		{ "   ARB  ", "   DSO  ", "Voltmeter ", " Clock " }
	};
	int main_fun = 0;
	int flag = 1;
	int(*fun[4]) (void) = {
		arb.main,
		dso.main,
		meter.main,
		clock_main
	};

	power_on();

	while (1) {
		usb_command.capture_handle();

		if (event == KEY_LEFT || event == KEY_UP) {
			main_fun--;
			if (main_fun < 0) main_fun = 0;
			flag = 1;
		}
		if (event == KEY_RIGHT || event == KEY_DOWN) {
			main_fun++;
			if (main_fun > 3) main_fun = 3;
			flag = 1;
		}

		if (event == KEY_ENTER) {
			for (i = 0; i <= 100; i++) {
				pwm.initialize(100 - i);
				for (j = 0; j < 20000; j++) ;
			}

			fun[main_fun]();
			first_run = 1;
			event = 0;
			flag = 1;
			show_logo();
		}

		if (flag) {
			event = 0;
			flag = 0;
			font._default.single_byte = &fixedsys;
			font._default.double_byte = &simsun16;
			for (i = 0; i < 4; i++) {
				s.x = 170 + i * 77;
				s.y = 235;
				s.color = COLOR_BLACK;
				s.background_color = main_fun == i ? COLOR_ORANGE : COLOR_WHITE;

				s.space.line = 0;
				s.space.word = 0;
				s.inverse = NULL;

				font.printf(&s, "%s", main_str[sys.language][i]);
			}
		}
	}
}
