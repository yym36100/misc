/*------------------------------------------------------
   FILE NAME   :function.c
   DESCRIPTION : iBoard title
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2011-12-18
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\evtft.h"
#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\title.h"
#include "..\include\waveform.h"
#include "..\include\config.h"
#include "..\include\main.h"
#include "..\include\systick.h"
#include "..\include\event.h"
#include "..\include\button.h"
#include "..\include\function.h"
#include "..\include\title.h"
#include "..\include\diagram.h"
#include "..\include\infomation.h"
#include "..\usb_include\usb_command.h"
#include "..\include\frame.h"
#include "..\include\frequency.h"
#include "..\include\amplitude.h"
#include "..\include\offset.h"
#include "..\include\arb.h"
#include "..\include\pwm.h"


#include <math.h>
#include <string.h>
#include <stdio.h>
//---------------- Function Prototype -------------------//
static int _waveform(void);
static int _frequency(void);
static int _amplitude(void);
static int _offset(void);
static int duty_cycle(void);
static int symmetry(void);
static int function_main(void);

static int get_freq_range(double freq);
static int show_adjust_freq(double freq, int position);


//---------------- Variable -----------------------------//
FUNCTION_T function = {
	.main = function_main
};

char const *  button_function[/*function */ 4][/* language */ 2][5] = {
	{ //common
		{
			"  波  形  ",
			"  频  率  ",
			"  幅  度  ",
			"直流偏置",
			NULL
		}, {
			" Waveform",
			" Frequency",
			" Amplitude",
			" DC Offset",
			NULL
		}
	}, {     //SQU
		{
			"  波  形  ",
			"  频  率  ",
			"  幅  度  ",
			"直流偏置",
			"  占空比 "
		}, {
			" Waveform",
			" Frequency",
			" Amplitude",
			" DC Offset",
			" Duty Cycle"
		}
	}, {     //TRI
		{
			"  波  形  ",
			"  频  率  ",
			"  幅  度  ",
			"直流偏置",
			"  对称度 "
		}, {
			" Waveform",
			" Frequency",
			" Amplitude",
			" DC Offset",
			" Symmetry"
		}
	}, {     //DC
		{
			"  波  形  ",
			"直流偏置",
			NULL,
			NULL,
			NULL
		}, {
			" Waveform",
			" DC Offset",
			NULL,
			NULL,
			NULL
		}
	}
};

static int fun_index[15] = {
	0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3
};
const double amplitude_weight[] = { 10.0, 1.0, 0.1, 0.01, 0.001 };
const double offset_weight[] = { 1.0, 0.1, 0.01, 0.001 };
const double duty_cycle_weight[] = { 100.0, 10.0, 1.0, 0.1 };


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
function_main(void)
{
	int i;
	int(*fun_function[4][5]) (void) = {
		{ //sine
			_waveform,
			_frequency,
			_amplitude,
			_offset,
			NULL
		}, { //squ
			_waveform,
			_frequency,
			_amplitude,
			_offset,
			duty_cycle
		}, { //tri
			_waveform,
			_frequency,
			_amplitude,
			_offset,
			symmetry
		}, {
			_waveform,
			_offset,
			NULL,
			NULL,
			NULL
		}
	};

	event = KEY_F1;
	infomation.initialize();

	while (1) {
		for (i = 0; i < 5; i++) {
			if (event == f_event_queue[i]) {
				event = EVENT_CLEAR;
				if (fun_function[fun_index[ag.waveform]][i] != NULL) {
					button.main = &button_function[fun_index[ag.waveform]][sys.language];
					button.active = i;
					button.drawb(button.main, button.active);

					fun_function[fun_index[ag.waveform]][i]();
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
			event == KEY_M5 ||
			event == KEY_ESC
			) return 0;
	}
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
_waveform(void)
{
	int flag = 1;
	const char * wave_index[2] = {
		" 正弦 方波 三角波 锯齿波 负锯齿 SINC 噪声 升指数\n 降指数 正全波 负全波 正半波 负半波 高斯函数 直流",
		" SIN SQU TRI RAMP N_RAMP SINC Noise EXP_R\n EXP_F FULL_P FULL_N HALF_P HALF_N GAUSSIAN DC "
	};

	int j;

	int position = ag.waveform;

	INVERSE_T pin;
	STRING_T s;
	char const *p;
	int i;
	int start;


	event = EVENT_CLEAR;
	frame.set_window(0);

	while (1) {
		if (
			event == KEY_F2 ||
			event == KEY_F3 ||
			event == KEY_F4 ||
			event == KEY_F5
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;

		if (event == KEY_LEFT || event == KEY_UP) {
			event = EVENT_CLEAR;
			position--;

			flag = 1;

			if (position < 0) {
				position = 0;
				flag = 0;
			}
		}

		if (event == KEY_RIGHT || event == KEY_DOWN) {
			event = EVENT_CLEAR;
			position++;

			flag = 1;

			if (position > 14) {
				position = 14;
				flag = 0;
			}
		}


		if (flag) {
			flag = 0;

			font._default.single_byte = &fixedsys;


			s.x = 4;
			s.y = 193;
			s.space.line = 5;
			s.space.word = 0;
			s.background_color = COLOR_WINDOW_BACKGROUND;

			s.color = COLOR_BLACK;

			p = wave_index[sys.language];


			start = 0;

			i = 0;
			while (*p != NULL) {
				if (*p == ' ') i++;
				if (i > position) break;
				p++;
				start++;
			}
			p++;
			pin.start = start + 1;

			for (i = 0; p[i] != NULL; i++) if (p[i] == ' ') break;
			pin.end = start + i;

			pin.next = NULL;
			pin.color = COLOR_BLACK;
			pin.background_color = sys.color;
			s.inverse = &pin;

			font.printf(&s, wave_index[sys.language]);

			ag.waveform = position;

			button.main = &button_function[fun_index[ag.waveform]][sys.language];
			button.active = i;
			button.drawb(button.main, 0);

			if (ag.waveform == SQUA) diagram.show(ag.waveform, ag.duty_cycle / 100.);
			else if (ag.waveform == TRI) diagram.show(ag.waveform, ag.symmetry / 100.);
			else diagram.show(ag.waveform, 0);

			title.wave_index(ag.waveform);

			if (ag.waveform == SQUA) waveform.set(ag.waveform, ag.duty_cycle);
			else if (ag.waveform == TRI) waveform.set(ag.waveform, ag.symmetry);
			else waveform.set(ag.waveform, 0);
		}
		usb_command.capture_handle();
		if (systick.flash_trig) {
			infomation.show_function(0, systick.flash_trig == 2 ? COLOR_LIME : make_rgb565(44, 71, 0));
			systick.flash_trig = 0;
		}

		if (first_run == 1) {
			for (j = 0; j < 100000; j++) ;
			for (i = 0; i <= 100; i++) {
				pwm.initialize(i);
				for (j = 0; j < 20000; j++) ;
				first_run = 0;
			}
		}
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
_frequency(void)
{
	int flag = 1;
	int position = 5;
	const double frequency_weight[] = { 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1, 0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001 };

	event = EVENT_CLEAR;

	frame.set_window(1);
	while (1) {
		if (
			event == KEY_F1 ||
			event == KEY_F3 ||
			event == KEY_F4 ||
			event == KEY_F5
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;

		if (event == KEY_LEFT) {
			event = EVENT_CLEAR;
			position--;

			flag = 1;

			if (position < 0) {
				position = 0;
				flag = 0;
			}
		}
		if (event == KEY_RIGHT) {
			event = EVENT_CLEAR;
			position++;
			flag = 1;
			if (position > 13) {
				position = 13;
				flag = 0;
			}
		}
		if (event == KEY_UP) {
			event = EVENT_CLEAR;
			ag.frequency += frequency_weight[position];

			flag = 1;
			if (ag.frequency > 10000000.) {
				ag.frequency = 10000000.;
			}
		}
		if (event == KEY_DOWN) {
			event = EVENT_CLEAR;
			ag.frequency -= frequency_weight[position];
			flag = 1;
			if (ag.frequency < 0) {
				ag.frequency = 0;
			}
		}

		if (flag) {
			flag = 0;
			show_adjust_freq(ag.frequency, position);
			frequency.set(ag.frequency);
		}
		usb_command.capture_handle();
		if (systick.flash_trig) {
			infomation.show_function(1, systick.flash_trig == 2 ? COLOR_LIME : make_rgb565(44, 71, 0));
			systick.flash_trig = 0;
		}
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
_amplitude(void)
{
	int flag = 1;
	static int position = 0;
	const int pos[2][5] = {
		{ 0, 1, 3, 4, 5 },
		{ 0, 1, 2, 3, 4 }
	};
	INVERSE_T pin;
	STRING_T s;

	event = EVENT_CLEAR;

	frame.set_window(1);
	while (1) {
		if (
			event == KEY_F1 ||
			event == KEY_F2 ||
			event == KEY_F4 ||
			event == KEY_F5
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;

		if (event == KEY_LEFT) {
			event = EVENT_CLEAR;
			position--;
			if (position < 0) position = 0;

			flag = 1;
		}
		if (event == KEY_RIGHT) {
			event = EVENT_CLEAR;
			position++;
			if (position > 4) position = 4;

			flag = 1;
		}
		if (event == KEY_UP) {
			event = EVENT_CLEAR;
			ag.amplitude += amplitude_weight[position];
			if (ag.amplitude > 10) ag.amplitude = 10.0;

			flag = 1;
		}
		if (event == KEY_DOWN) {
			event = EVENT_CLEAR;
			ag.amplitude -= amplitude_weight[position];
			if (ag.amplitude < 0) ag.amplitude = .001;

			flag = 1;
		}


		if (flag) {
			flag = 0;
			font._default.single_byte = &tahoma26;

			if (ag.amplitude < 1.0) pin.start = pin.end = pos[1][position];
			else pin.start = pin.end = pos[0][position];

			pin.color = COLOR_WINDOW_BACKGROUND;
			pin.background_color = sys.color;
			pin.next = NULL;

			s.x = 10;
			s.y = 190;
			s.space.line = 0;
			s.space.word = 0;
			s.color = COLOR_WINDOW_BACKGROUND;
			s.background_color = COLOR_BLACK;
			s.inverse = &pin;



			if (ag.amplitude < 1.0) font.printf(&s, "%05.0f mVpp   ", ag.amplitude * 1000);
			else font.printf(&s, "%06.3f Vpp   ", ag.amplitude);

			amplitude.set(ag.amplitude);
		}
		usb_command.capture_handle();
		if (systick.flash_trig) {
			infomation.show_function(2, systick.flash_trig == 2 ? COLOR_LIME : make_rgb565(44, 71, 0));
			systick.flash_trig = 0;
		}
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
_offset(void)
{
	int flag = 1;
	static int position = 0;
	const int pos[2][4] = {
		{ 1, 3, 4, 5 },
		{ 1, 2, 3, 4 }
	};
	INVERSE_T pin;
	STRING_T s;

	event = EVENT_CLEAR;
	frame.set_window(1);
	while (1) {
		if (
			event == KEY_F1 ||
			event == KEY_F2 ||
			event == KEY_F3 ||
			event == KEY_F5
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;


		if (event == KEY_LEFT) {
			event = EVENT_CLEAR;
			position--;
			if (position < 0) position = 0;

			flag = 1;
		}
		if (event == KEY_RIGHT) {
			event = EVENT_CLEAR;
			position++;
			if (position > 3) position = 3;

			flag = 1;
		}
		if (event == KEY_UP) {
			event = EVENT_CLEAR;
			ag.offset += offset_weight[position];
			if (ag.offset > 5) ag.offset = 5;

			flag = 1;
		}
		if (event == KEY_DOWN) {
			event = EVENT_CLEAR;
			ag.offset -= offset_weight[position];
			if (ag.offset < -5) ag.offset = -5;

			flag = 1;
		}

		if (flag) {
			flag = 0;
			font._default.single_byte = &tahoma26;

			if (ag.offset < 1.0 && ag.offset > -0.999) pin.start = pin.end = pos[1][position];
			else pin.start = pin.end = pos[0][position];

			pin.color = COLOR_WINDOW_BACKGROUND;
			pin.background_color = sys.color;
			pin.next = NULL;

			s.x = 10;
			s.y = 190;
			s.space.line = 0;
			s.space.word = 0;
			s.color = COLOR_WINDOW_BACKGROUND;
			s.background_color = COLOR_BLACK;
			s.inverse = &pin;

			if (ag.offset < 1.0 && ag.offset > -0.999) font.printf(&s, "%+05.0f mVdc   ", ag.offset * 1000);
			else font.printf(&s, "%+06.3f Vdc   ", ag.offset);

			offset.set(ag.offset);
		}

		usb_command.capture_handle();
		if (systick.flash_trig) {
			infomation.show_function(3, systick.flash_trig == 2 ? COLOR_LIME : make_rgb565(44, 71, 0));
			systick.flash_trig = 0;
		}
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
duty_cycle(void)
{
	int flag = 1;
	static int position = 1;
	const int pos[4] = {
		0, 1, 2, 4
	};
	INVERSE_T pin;
	STRING_T s;

	event = EVENT_CLEAR;
	frame.set_window(1);

	while (1) {
		if (
			event == KEY_F1 ||
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

		if (event == KEY_LEFT) {
			event = EVENT_CLEAR;
			position--;
			if (position < 0) position = 0;

			flag = 1;
		}
		if (event == KEY_RIGHT) {
			event = EVENT_CLEAR;
			position++;
			if (position > 3) position = 3;

			flag = 1;
		}
		if (event == KEY_UP) {
			event = EVENT_CLEAR;
			ag.duty_cycle += duty_cycle_weight[position];
			if (ag.duty_cycle > 99.9) ag.duty_cycle = 99.9;

			flag = 1;
		}
		if (event == KEY_DOWN) {
			event = EVENT_CLEAR;
			ag.duty_cycle -= duty_cycle_weight[position];
			if (ag.duty_cycle < 0.1) ag.duty_cycle = 0.1;

			flag = 1;
		}


		if (flag) {
			flag = 0;
			font._default.single_byte = &tahoma26;

			pin.start = pin.end = pos[position];

			pin.color = COLOR_WINDOW_BACKGROUND;
			pin.background_color = sys.color;
			pin.next = NULL;

			s.x = 10;
			s.y = 190;
			s.space.line = 0;
			s.space.word = 0;
			s.color = COLOR_WINDOW_BACKGROUND;
			s.background_color = COLOR_BLACK;
			s.inverse = &pin;

			font.printf(&s, "%05.1f %%  ", ag.duty_cycle);

			diagram.show(ag.waveform, ag.duty_cycle / 100.);
			waveform.set(ag.waveform, ag.duty_cycle);
		}
		usb_command.capture_handle();
		if (systick.flash_trig) {
			infomation.show_function(4, systick.flash_trig == 2 ? COLOR_LIME : make_rgb565(44, 71, 0));
			systick.flash_trig = 0;
		}
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
symmetry(void)
{
	int flag = 1;
	static int position = 1;
	const int pos[4] = {
		0, 1, 2, 4
	};
	INVERSE_T pin;
	STRING_T s;

	event = EVENT_CLEAR;
	frame.set_window(1);

	while (1) {
		if (
			event == KEY_F1 ||
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

		if (event == KEY_LEFT) {
			event = EVENT_CLEAR;
			position--;
			if (position < 0) position = 0;

			flag = 1;
		}
		if (event == KEY_RIGHT) {
			event = EVENT_CLEAR;
			position++;
			if (position > 3) position = 3;

			flag = 1;
		}
		if (event == KEY_UP) {
			event = EVENT_CLEAR;
			ag.symmetry += duty_cycle_weight[position];
			if (ag.symmetry > 100) ag.symmetry = 100;

			flag = 1;
		}
		if (event == KEY_DOWN) {
			event = EVENT_CLEAR;
			ag.symmetry -= duty_cycle_weight[position];
			if (ag.symmetry < 0) ag.symmetry = 0;

			flag = 1;
		}


		if (flag) {
			flag = 0;
			font._default.single_byte = &tahoma26;

			pin.start = pin.end = pos[position];

			pin.color = COLOR_WINDOW_BACKGROUND;
			pin.background_color = sys.color;
			pin.next = NULL;

			s.x = 10;
			s.y = 190;
			s.space.line = 0;
			s.space.word = 0;
			s.color = COLOR_WINDOW_BACKGROUND;
			s.background_color = COLOR_BLACK;
			s.inverse = &pin;


			font.printf(&s, "%05.1f %%  ", ag.symmetry);
			diagram.show(ag.waveform, ag.symmetry / 100.);
			waveform.set(ag.waveform, ag.symmetry);
		}
		usb_command.capture_handle();
		if (systick.flash_trig) {
			infomation.show_function(4, systick.flash_trig == 2 ? COLOR_LIME : make_rgb565(44, 71, 0));
			systick.flash_trig = 0;
		}
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
get_freq_range(double freq)
{
	if (freq < 0.001) return RANGE_uHz;
	else if (freq < 1.0) return RANGE_mHz;
	else if (freq < 1000.0) return RANGE_Hz;
	else if (freq < 1000000.0) return RANGE_kHz;
	else return RANGE_MHz;
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
show_adjust_freq(double freq, int position)
{
	STRING_T s;
	int i, j, a, b, w;
	char buffer[30];
	char const * weight[] = {
		"uHz", "mHz", "Hz", "kHz", "MHz"
	};
	INVERSE_T pin;
	RECT_T r;

	memset(buffer, 0, sizeof(buffer));

	switch (w = get_freq_range(freq)) {
	case RANGE_uHz:
		sprintf(buffer, "%014.0f", freq * 1000000.0);
		break;
	case RANGE_mHz:
		sprintf(buffer, "%015.3f", freq * 1000.0);
		break;
	case RANGE_Hz:
		sprintf(buffer, "%015.6f", freq);
		break;
	case RANGE_kHz:
		sprintf(buffer, "%015.9f", freq / 1000.0);
		break;
	case RANGE_MHz:
		sprintf(buffer, "%015.12f", freq / 1000000.0);
		break;
	}


	if (w == 0) b = 13;
	else b = 14;
	a = 17;

	for (j = 0; j < 4; j++) {
		for (i = 0; i < 3; i++) buffer[a--] = buffer[b--];
		if (buffer[b] == '.') {
			buffer[a--] = buffer[b--];
		}else buffer[a--] = '\'';
	}


	font._default.single_byte = &tahoma26;

	pin.start = pin.end = position + (position + 1) / 3;
	pin.color = COLOR_WINDOW_BACKGROUND;
	pin.background_color = sys.color;
	pin.next = NULL;

	s.x = 10;
	s.y = 190;
	s.space.line = 0;
	s.space.word = 0;
	s.color = COLOR_WINDOW_BACKGROUND;
	s.background_color = COLOR_BLACK;
	s.inverse = &pin;


	font.printf(&s, "%s %s", buffer, weight[w]);

	r.x = s.x;
	r.y = 190;
	r.width = 396 - s.x;
	r.height = 36;
	r.fill_flag = 1;
	r.color = COLOR_BLACK;

	gui.rect(&r);


	return 0;
}
