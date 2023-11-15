/*------------------------------------------------------
   FILE NAME   : meter.c
   DESCRIPTION : meter functions
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/


//-----------------Include files-------------------------//
#include "..\include\stm32f10x_reg.h"
#include "..\include\font.h"
#include "..\include\gui_core.h"
#include "..\include\meter.h"
#include "..\include\usart.h"
#include "..\include\systick.h"
#include "..\include\hardware.h"
#include "..\include\evtft.h"
#include "..\include\adc.h"
#include "..\include\event.h"
#include "..\usb_include\usb_command.h"
#include "..\include\main.h"
#include "..\include\pwm.h"


#include <string.h>
#include <stdlib.h>

static int initialize(void);
static int meter_main(void);
static int sel_range(int);


//---------------- Variable -----------------------------//

const METER_T meter = {
	.main = meter_main
};

static int acdc = 1;
COLOR_T color = COLOR_RED;
const CAL_T cal_ac[4] = {
	[0].k = 263.15789473684210526315789473684,
	[0].b = 7.3684210526315789473684210526316,
	[0].min = 200.,
	[0].max = 500.,

	[1].k = 107.6233183856502242152466367713,
	[1].b = 2.2242152466367713004484304932735,
	[1].min = 20.,
	[1].max = 200.,

	[2].k = 10.781671159029649595687331536388,
	[2].b = 0.1832884097035040431266846361186,
	[2].min = 2.0,
	[2].max = 20.,

	[3].k = 1.0849909584086799276672694394213,
	[3].b = 0.,
	[3].min = -0.1,
	[3].max = 2.
};

const CAL_T cal_dc[4] = {
	[0].k = 485.73163327261687917425622343655,
	[0].b = -613.23618700667880995749848208865,
	[0].min = 200.,
	[0].max = 500.,

	[1].k = 197.77503090234857849196538936959,
	[1].b = -247.8121137206427688504326328801,
	[1].min = 20.,
	[1].max = 200.,

	[2].k = 19.728729963008631319358816276202,
	[2].b = -24.680641183723797780517879161529,
	[2].min = 2.,
	[2].max = 20.,

	[3].k = 1.9875776397515527950310559006211,
	[3].b = -2.4724968944099378881987577639752,
	[3].min = 0.,
	[3].max = 2.
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
int get_event(void)
{
	RECT_T r;
	STRING_T s;

	//AC DC
	if (event) {
		if (event == KEY_M4) acdc = 1;
		if (event == KEY_M5) acdc = 0;
		if (event == KEY_ESC) return 1;


		event = 0;
		r.x = 400;
		r.y = 168;
		r.width = 79;
		r.height = 50;
		r.fill_flag = 1;
		r.color = (acdc == 1 ? color : COLOR_BLACK);;
		gui.rect(&r);

		r.x = 400;
		r.y = 218;
		r.width = 79;
		r.height = 50;
		r.fill_flag = 1;
		r.color = (acdc == 0 ? color : COLOR_BLACK);;
		gui.rect(&r);

		r.x = 400;
		r.y = 168;
		r.width = 79;
		r.height = 50;
		r.fill_flag = 0;
		r.color = color;
		gui.rect(&r);

		r.x = 400;
		r.y = 218;
		r.width = 79;
		r.height = 50;
		r.fill_flag = 0;
		r.color = color;
		gui.rect(&r);

		font._default.single_byte = &tahoma26;
		s.x = 415;
		s.y = 175;
		s.background_color = (acdc == 1 ? color : COLOR_BLACK);

		s.color = (acdc == 1 ? COLOR_BLACK : color);
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "DC");

		font._default.single_byte = &tahoma26;
		s.x = 415;
		s.y = 225;
		s.background_color = (acdc == 1 ? COLOR_BLACK : color);

		s.color = (acdc == 1 ? color : COLOR_BLACK);
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "AC");

		font._default.single_byte = &borlandTE;
		s.x = 415;
		s.y = 145;
		s.background_color = COLOR_BLACK;

		s.color = color;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "%s MODE", acdc ? "DC" : "AC");

		lcd.change();
		r.x = 400;
		r.y = 168;
		r.width = 79;
		r.height = 50;
		r.fill_flag = 1;
		r.color = (acdc == 1 ? color : COLOR_BLACK);;
		gui.rect(&r);

		r.x = 400;
		r.y = 218;
		r.width = 79;
		r.height = 50;
		r.fill_flag = 1;
		r.color = (acdc == 0 ? color : COLOR_BLACK);;
		gui.rect(&r);

		r.x = 400;
		r.y = 168;
		r.width = 79;
		r.height = 50;
		r.fill_flag = 0;
		r.color = color;
		gui.rect(&r);

		r.x = 400;
		r.y = 218;
		r.width = 79;
		r.height = 50;
		r.fill_flag = 0;
		r.color = color;
		gui.rect(&r);

		font._default.single_byte = &tahoma26;
		s.x = 415;
		s.y = 175;
		s.background_color = (acdc == 1 ? color : COLOR_BLACK);

		s.color = (acdc == 1 ? COLOR_BLACK : color);
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "DC");

		font._default.single_byte = &tahoma26;
		s.x = 415;
		s.y = 225;
		s.background_color = (acdc == 1 ? COLOR_BLACK : color);

		s.color = (acdc == 1 ? color : COLOR_BLACK);
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "AC");

		font._default.single_byte = &borlandTE;
		s.x = 415;
		s.y = 145;
		s.background_color = COLOR_BLACK;

		s.color = color;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "%s MODE", acdc ? "DC" : "AC");

		lcd.change();
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
static int
show_grid(void)
{
	int i;
	RECT_T r;


	r.x = 0;
	r.y = 168;
	r.width = 350;
	r.height = 100;
	r.fill_flag = 1;
	r.color = COLOR_BLACK;
	gui.rect(&r);

	for (i = 1; i < 10; i++) gui.line(0, 168 + i * 10, 350, 168 + i * 10, make_rgb565(44, 71, 0));

	for (i = 1; i < 35; i++) gui.line(i * 10, 168, i * 10, 268, make_rgb565(44, 71, 0));

	r.x = 0;
	r.y = 168;
	r.width = 350;
	r.height = 100;
	r.fill_flag = 0;
	r.color = make_rgb565(44, 71, 0);
	gui.rect(&r);

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
static int
show_wave(short int * buf, int number, COLOR_T c)
{
	int i;

	gui.set_cursor(1, (218 - buf[0]));

	for (i = 2; i < number; i++) gui.line_to(i, 218 - buf[i], c);

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
static int
sel_range(int range)
{
	switch (range) {
	case 0:
		SET_R0_ON;               //r3
		SET_R1_OFF;
		SET_R2_OFF;
		break;
	case 1:
		SET_R0_OFF;              //r2
		SET_R1_ON;
		SET_R2_OFF;
		break;
	case 2:
		SET_R0_ON;               //r1
		SET_R1_ON;
		SET_R2_OFF;
		break;
	case 3:
		SET_R0_OFF;              //r0
		SET_R1_OFF;
		SET_R2_OFF;
		break;
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
static int
measure_ac(MEASURE_T * m)
{
	int i;
	static int j = 3;


	double temp = 0;

	temp = 0;

	for (i = 0; i < 200; i++) {
		adc.read(CH_AC);
		temp += adc.value;
	}
	temp /= 200;

	temp *= cal_ac[j].k;
	temp += cal_ac[j].b;

	if (temp > cal_ac[j].min && temp <= cal_ac[j].max) goto aa;

	for (j = 0; j < 4; j++) {
		sel_range(j);

		for (i = 0; i < 100000; i++) ;
		for (i = 0; i < 1000; i++) adc.read(CH_AC);

		temp = 0;
		for (i = 0; i < 100; i++) {
			adc.read(CH_AC);
			temp += adc.value;
		}
		temp /= 100;

		temp *= cal_ac[j].k;
		temp += cal_ac[j].b;

		if (temp >= cal_ac[j].min) break;
	}

 aa:     temp = 0;
	for (i = 0; i < 1000; i++) {
		adc.read(CH_AC);
		temp += adc.value;
	}
	temp /= 1000;

	if (j > 3) j = 3;

	temp *= cal_ac[j].k;
	temp += cal_ac[j].b;

	m->value = temp;

	m->range = j;

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

static int
measure_dc(MEASURE_T * m)
{
	int i;
	static int j = 3;

	double temp = 0;

	temp = 0;
	for (i = 0; i < 100; i++) {
		adc.read(CH_DC);
		temp += adc.value;
	}
	temp /= 100;

	temp *= cal_dc[j].k;
	temp += cal_dc[j].b;

	if (
		(temp >= cal_dc[j].min && temp <= cal_dc[j].max) ||
		(temp >= cal_dc[j].max * -1 && temp <= cal_dc[j].min * -1)
		) goto aa;  //not need change range

	//change range
	for (j = 0; j < 4; j++) {
		sel_range(j);

		for (i = 0; i < 100; i++) adc.read(CH_DC);
		temp = 0;

		for (i = 0; i < 100; i++) {
			adc.read(CH_DC);
			temp += adc.value;
		}
		temp /= 100;

		temp *= cal_dc[j].k;
		temp += cal_dc[j].b;

		if (temp > cal_dc[j].min || temp < (-1. * cal_dc[j].min)) break;
	}

 aa:     temp = 0;
	for (i = 0; i < 1000; i++) {
		adc.read(CH_DC);
		temp += adc.value;
	}
	temp /= 1000;

	if (j > 3) j = 3;

	temp *= cal_dc[j].k;
	temp += cal_dc[j].b;

	m->value = temp;

	m->range = j;


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

static int
show_scale(int range)
{
	STRING_T s;
	static int rbak;
	int i;
	//0V
	font._default.single_byte = &borlandTE;
	s.x = 352;
	s.y = 168;
	s.background_color = COLOR_BLACK;

	s.color = make_rgb565(44, 71, 0);
	s.space.line = 0;
	s.space.word = 0;
	s.inverse = NULL;

	switch (range) {
	case 0:
		font.printf(&s, " 500V");
		break;
	case 1:
		font.printf(&s, " 200V");
		break;
	case 2:
		font.printf(&s, "  20V");
		break;
	case 3:
		font.printf(&s, "   2V");
		break;
	}
	s.x = 352;
	s.y = 210;
	s.background_color = COLOR_BLACK;

	s.color = make_rgb565(44, 71, 0);
	s.space.line = 0;
	s.space.word = 0;
	s.inverse = NULL;

	font.printf(&s, "   0V");

	s.x = 352;
	s.y = 255;
	s.background_color = COLOR_BLACK;

	s.color = make_rgb565(44, 71, 0);
	s.space.line = 0;
	s.space.word = 0;
	s.inverse = NULL;

	switch (range) {
	case 0:
		font.printf(&s, "-500V");
		break;
	case 1:
		font.printf(&s, "-200V");
		break;
	case 2:
		font.printf(&s, " -20V");
		break;
	case 3:
		font.printf(&s, "  -2V");
		break;
	}

	if (range != rbak) {
		s.x = 352;
		s.y = 145;
		s.background_color = color;

		s.color = COLOR_BLACK;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "RANGE");
		lcd.change();
		s.x = 352;
		s.y = 145;
		s.background_color = color;

		s.color = COLOR_BLACK;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		font.printf(&s, "RANGE");
		lcd.change();
		for (i = 0; i < 1000000; i++) ;
	}


	s.x = 352;
	s.y = 145;
	s.background_color = COLOR_BLACK;

	s.color = color;
	s.space.line = 0;
	s.space.word = 0;
	s.inverse = NULL;

	font.printf(&s, "RANGE");
	rbak = range;

	return 0;
};

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
	STRING_T s;

	SET_R0_OUTPUT;
	SET_R1_OUTPUT;
	SET_R2_OUTPUT;

	//clear lcd


	lcd.change();
	lcd.cls(0);
	lcd.change();
	lcd.cls(0);

	event = KEY_M4;

	show_grid();
	lcd.change();
	show_grid();

	font._default.single_byte = &borlandTE;
	s.x = 5;
	s.y = 145;
	s.background_color = COLOR_BLACK;

	s.color = color;
	s.space.line = 0;
	s.space.word = 0;
	s.inverse = NULL;

	font.printf(&s, "iBoard Voltmeter %s//XiaomaGee", rev);

	lcd.change();
	font._default.single_byte = &borlandTE;
	s.x = 5;
	s.y = 145;
	s.background_color = COLOR_BLACK;

	s.color = color;
	s.space.line = 0;
	s.space.word = 0;
	s.inverse = NULL;

	font.printf(&s, "iBoard Voltmeter %s//XiaomaGee", rev);

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
static int
meter_main(void)
{
	int i, j;
	static float temp, temp_bak = 0;
	float temp1;
	STRING_T s;
	MEASURE_T m;
	char c;
	const double scale_weight[] = { 500, 200, 20, 2 };

	short int buf[350];
	float buf_f[350];
	int counter = 0;

	initialize();

	while (1) {
		usb_command.capture_handle();

		if (acdc) measure_dc(&m);
		else measure_ac(&m);

		temp = m.value;

		temp = temp * 0.7 + temp_bak * 0.3;


//		temp=read_abs(CH_AC,3);

		if (temp > -0.005 && temp < 0.005) temp = 0;

		usart1.printf("%f\n", temp);

		font._default.single_byte = &nix96;
		s.x = 0;
		s.y = 10;
		s.background_color = COLOR_BLACK;

		s.color = color;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;

		if (temp < 0) {
			temp1 = -temp;
			c = '-';
		}else {
			c = ' ';
			temp1 = temp;
		}

		if (temp1 < 2) font.printf(&s, "%c%5.3f", c, temp1);
		else if (temp1 < 20) font.printf(&s, "%c%05.2f", c, temp1);
		else if (temp1 < 200) font.printf(&s, "%%05.1f", c, temp1);
		else font.printf(&s, "%c%03.0f ", c, temp1);


		show_scale(m.range);


		if (get_event()) return 0;

		if (counter < 349) buf_f[counter] = temp;
		else {
			for (i = 0; i < 348; i++) buf_f[i] = buf_f[i + 1];
			buf_f[348] = temp;
		}

		for (i = 0; i < 349; i++) {
			buf[i] = (buf_f[i] * 50. / scale_weight[m.range]);
			if (buf[i] > 49) buf[i] = 49;
			if (buf[i] < -49) buf[i] = -49;
		}
		show_grid();
		show_wave(buf, counter, color);
		counter++;
		if (counter > 349) counter = 349;

		lcd.change();
		temp_bak = temp;

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


