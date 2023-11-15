/*------------------------------------------------------
   FILE NAME   : clock.c
   DESCRIPTION :
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
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
#include "..\include\clock.h"


#include <string.h>
#include <stdlib.h>
#include <math.h>

//-----------------Variable------------------------------//
CALENDAR_T calendar;

//-----------------Function------------------------------//

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
int clock_main(void)
{
	STRING_T s;
	int m = 0;
	int i, j;
	RECT_T r;
	int bak;

	lcd.cls(0);

	while (1) {
		while (bak == calendar.second) ;

		bak = m = calendar.second;

		s.x = 7;
		s.y = 150;
		s.background_color = COLOR_BLACK;

		s.color = COLOR_BLUE;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;
		font._default.single_byte = &nix96;


		if (m % 2) font.printf(&s, "%02d %02d", calendar.hour, calendar.minute);
		else font.printf(&s, "%02d:%02d", calendar.hour, calendar.minute);


		font._default.single_byte = &nix48;
		s.x = 7;
		s.y = 10;
		s.background_color = COLOR_BLACK;

		s.color = COLOR_BLUE;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "%d-%02d-%02d", calendar.year, calendar.month, calendar.day);

		for (i = 0; i < 60; i++) {
			r.x = i * 8;
			r.y = (i == m - 1 ? 90 : 103);
			r.width = 4;
			r.height = (i == m - 1 ? 20 : 7);
			r.fill_flag = 1;
			r.color = COLOR_BLACK;
			gui.rect(&r);

			if (m == 0) {
				r.x = 8 * 59;
				r.y = 90;
				r.width = 4;
				r.height = 20;
				r.fill_flag = 1;
				r.color = COLOR_BLACK;
				gui.rect(&r);
			}

			r.x = i * 8;
			r.y = (i == m ? 90 : 103);
			r.width = 4;
			r.height = (i == m ? 20 : 7);
			r.fill_flag = 1;
			r.color = COLOR_BLUE;
			gui.rect(&r);
		}

		usb_command.capture_handle();

		if (event == KEY_ESC) {
			event = 0;
			return 0;
		}       else event = 0;


		if (first_run == 1) {
			for (j = 0; j < 100000; j++) ;
			for (i = 0; i <= 100; i++) {
				pwm.initialize(i);
				for (j = 0; j < 20000; j++) ;
				first_run = 0;
			}
		}
	}
}

