/*------------------------------------------------------
   FILE NAME   : system.c
   DESCRIPTION : ---
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\function.h"
#include "..\include\systick.h"
#include "..\include\button.h"
#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\diagram.h"
#include "..\include\frame.h"

#include "..\include\main.h"

#include "..\include\usart.h"
#include "..\include\infomation.h"
#include "..\include\pwm.h"
#include "..\include\event.h"

#include "..\include\evtft.h"

#include "..\include\system.h"
#include "..\usb_include\usb_command.h"
#include "..\include\arb.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//---------------- Function Prototype -------------------//
static int theme(void);
static int brightness(void);


//配色方案 复位 亮度 校准 RS-232  >>> <<< USB 键盘测试 液晶测试 关于
//---------------- Variable -----------------------------//
char *  button_system[/* language */ 2][6] = {
	{
		"配色方案",
		"  亮  度  ",
		NULL,
		NULL,
		NULL
	}, {
		" Theme",
		" Brightness",
		NULL,
		NULL,
		NULL
	}
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
int
_system(void)
{
	int i;
	int(*fun_system[5]) (void) = {
		theme,
		brightness,
		NULL,
		NULL,
		NULL
	};
	event = KEY_F1;
	STRING_T s;
	const char * about[] = {
		" 基于 iBoard 的函数/任意波发生器，版权所有 \nXiaomaGee。欢迎完善，但不得用于商业目的！\n 本系统基于 X-GUI 完成人机界面。\n",
		" Arbitrary Function Generator based on iBoard. \nCopyright XiaomaGee.\n The user interface Based on X-GUI.\n"
	};


	frame.set_window(0);
	font._default.single_byte = &fixedsys;

	s.x = 18;
	s.y = 70;
	s.space.line = 4;
	s.space.word = 0;
	s.color = COLOR_BLACK;
	s.background_color = COLOR_WINDOW_BACKGROUND;
	s.inverse = NULL;
	font.printf(&s, "%s V%s %s C%d\n [XiaomaGee@Gmail.com] QQ:15959622", about[sys.language], rev, __DATE__, __ARMCC_VERSION);


	button.drawb(button_system[sys.language], 0);

	while (1) {
		for (i = 0; i < 6; i++) {
			if (event == f_event_queue[i]) {
				event = EVENT_CLEAR;
				if (fun_system[i] != NULL) {
					button.drawb(button_system[sys.language], i);

					fun_system[i]();
				}else {
					event = EVENT_CLEAR;
				}
			}
		}
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5
			) break;
	}

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
theme(void)
{
	int sys_color[] = {
		COLOR_ORANGE,
		COLOR_BLUE,
		COLOR_LIME,
		COLOR_RED,
		COLOR_FUCHSIA,
		COLOR_YELLOW,
		COLOR_AQUA,
		COLOR_WHITE
	};
	int i;
	static int position = 0;
	int flag = 1;
	CHECK_BOX_T c;
	BOX_T b;

	frame.set_window(0);


	for (i = 0; i < sizeof(sys_color) / sizeof(int); i++) {
		b.startx = 15 + i * 45;
		b.starty = 195;
		b.endx = 55 + i * 45;
		b.endy = 220;
		b.attrib = BOX_RECESSED; //(i==position?BOX_RECESSED:BOX_RAISED);
		b.color = sys_color[i];
		gui.box(&b);
	}

	while (1) {
		if (
			event == KEY_F2 ||
			event == KEY_F3 ||
			event == KEY_F4
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;

		if (event == KEY_LEFT || event == KEY_DOWN) {
			event = EVENT_CLEAR;
			position--;
			if (position < 0) position = 0;

			flag = 1;
		}
		if (event == KEY_RIGHT || event == KEY_UP) {
			event = EVENT_CLEAR;
			position++;
			if (position >= (sizeof(sys_color) / sizeof(int)) - 1) position = (sizeof(sys_color) / sizeof(int)) - 1;

			flag = 1;
		}

		if (flag) {
			flag = 0;

			for (i = 0; i < sizeof(sys_color) / sizeof(int); i++) {
				c.x = 30 + i * 45;
				c.y = 222;
				c.attrib = (i == position ? 1 : 0);
				gui.check_box(&c);
			}

			sys.color = sys_color[position];
			button.drawb(button_system[sys.language], 0);
			button.drawl(menu_main[sys.language], 3);
		}
		usb_command.capture_handle();
	}
	return 0;
};
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
brightness(void)
{
	int flag = 1;
	PROCESSBAR_T p;
	STRING_T s;

	frame.set_window(0);

	while (1) {
		if (
			event == KEY_F1 ||
			event == KEY_F3 ||
			event == KEY_F4
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;

		if (event == KEY_LEFT || event == KEY_DOWN) {
			event = EVENT_CLEAR;
			sys.brightness -= 5;

			if (sys.brightness < 5) sys.brightness = 5;

			flag = 1;
		}
		if (event == KEY_RIGHT || event == KEY_UP) {
			event = EVENT_CLEAR;
			sys.brightness += 5;

			if (sys.brightness > 100) sys.brightness = 100;
			flag = 1;
		}
		usb_command.capture_handle();

		if (flag) {
			flag = 0;
			p.x = 20;
			p.y = 200;
			p.width = 200;
			p.color = sys.color;
			p.percentage = sys.brightness;
			gui.processbar(&p);

			font._default.single_byte = &tahoma26;
			s.x = 260;
			s.y = 192;
			s.space.line = 0;
			s.space.word = 0;
			s.color = COLOR_BLACK;
			s.background_color = COLOR_WINDOW_BACKGROUND;
			s.inverse = NULL;

			font.printf(&s, "%d%%  ", sys.brightness);

			pwm.initialize(sys.brightness);
		}
	}
	return 0;
}
