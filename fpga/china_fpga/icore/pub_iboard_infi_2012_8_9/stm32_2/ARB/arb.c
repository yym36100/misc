/*------------------------------------------------------
   FILE NAME   :arb.c
   DESCRIPTION : iBoard offset driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2011-12-18
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\config.h"
#include "..\include\main.h"
#include "..\include\fpga.h"
#include "..\include\arb.h"
#include "..\include\dac.h"
#include "..\include\waveform.h"
#include "..\include\infomation.h"
#include "..\include\function.h"
#include "..\include\fpga.h"
#include "..\include\frequency.h"
#include "..\include\amplitude.h"
#include "..\include\offset.h"
#include "..\include\system.h"
#include "..\include\button.h"
#include "..\include\systick.h"
#include "..\include\title.h"
#include "..\include\frame.h"
#include "..\include\diagram.h"
#include "..\include\gui_core.h"
#include "..\include\event.h"
#include "..\include\tab.h"
#include "..\include\pwm.h"
#include "..\include\evtft.h"

#include <math.h>
#include <string.h>
//---------------- Function Prototype -------------------//

static int arb_main(void);

//---------------- Variable -----------------------------//
const ARB_T arb = {
	.main = arb_main
};

AG_T ag = {
	.waveform = SINE,
	.frequency = 1000.,
	.amplitude = 5.,
	.offset = 0.,
	.duty_cycle = 20.,
	.symmetry = 50.
};

char * menu_main[2][5] = {
	{ " 基 本\n 函 数", "任意波", " 猝 发", " 系 统", NULL },
	{ "Function", "Arbitrary", " Burst", " Utility", NULL },
};
char * menu_tab[2][5] = {
	{ "基本函数", "任意波", "猝发", "系统", NULL },
	{ "Function", "Arbitrary ", "Burst", "Utility", NULL }
};

//-----------------Function------------------------------//
/*-------------------------------------------------------
   NAME       : ---
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
	lcd.cls(COLOR_WINDOW_BACKGROUND);

	title.name();

	ARB_ATT0_OUTPUT;
	ARB_ATT1_OUTPUT;
	ARB_ATT2_OUTPUT;

	ARB_ATT0_ON;
	ARB_ATT1_ON;
	ARB_ATT2_OFF;

	waveform.set(0, 20);
	amplitude.set(2.0);
	frequency.set(100);
	offset.set(0);


	return 0;
}
/*-------------------------------------------------------
   NAME       : ---
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
arb_main(void)
{
	STRING_T s;
	TAB_T t;
	char * button_null[] = { NULL, NULL, NULL, NULL, NULL };
	int fmain = 0;



	initialize();
	event = KEY_M1;

	while (1) {
		if (event) {
			if (event == KEY_M1) fmain = 0;
			if (event == KEY_M2) fmain = 1;
			if (event == KEY_M3) fmain = 2;
			if (event == KEY_M4) fmain = 3;
			if (event == KEY_ESC) return 0;

			t.sfont = &fixedsys;
			t.dfont = &simsun12;
			t.x = 3;
			t.y = 26;
			t.title = menu_tab[sys.language];
			t.active = fmain;
			t.height = 155;
			t.width = 396;

			tab(&t);

			button.drawl(menu_main[sys.language], fmain);

			switch (fmain) {
			case 0:
				event = 0;
				function.main();
				break;
			case 1:
				event = 0;
				s.x = 12;
				s.y = 65;
				s.space.line = 5;
				s.space.word = 0;
				s.color = COLOR_BLACK;
				s.background_color = COLOR_WINDOW_BACKGROUND;
				s.inverse = NULL;
				font.printf(&s, "本功能尚未开放，敬请期待！");
				button.drawb(button_null, 0);
				frame.set_window(0);
				while (1) if (event) break;
				break;
			case 2:
				event = 0;
				s.x = 12;
				s.y = 65;
				s.space.line = 5;
				s.space.word = 0;
				s.color = COLOR_BLACK;
				s.background_color = COLOR_WINDOW_BACKGROUND;
				s.inverse = NULL;
				font.printf(&s, "本功能尚未开放，敬请期待！");
				button.drawb(button_null, 0);
				frame.set_window(0);
				while (1) if (event) break;
				break;
			case 3:
				event = 0;
				_system();
				break;
			}
		}
	}
}
