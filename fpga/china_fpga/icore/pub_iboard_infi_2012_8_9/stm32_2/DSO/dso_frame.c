/*------------------------------------------------------
   FILE NAME   : dso_frame.c
   DESCRIPTION : frame
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\dso_frame.h"
#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\dso.h"
#include "..\include\evtft.h"
#include "..\include\main.h"
#include "..\include\dso_menu.h"

#include <string.h>

//---------------- Function Prototype -------------------//
static int show_grid(void);
static int show_gnd(void);
static int show_position(void);
static int show_trig(void);
static int show_trig_icon(int);
static int show_xscale(void);
static int show_yscale(void);
static int show_measure_frame(int);
static int show_title(void);
static int show_coupling(void);
static int show_trigged(void);
static int frame_main(void);
static int show_about(void);


//---------------- Variable -----------------------------//
DSO_FRAME_T dso_frame = {
	.grid = show_grid,
	.gnd = show_gnd,
	.position = show_position,
	.trig = show_trig,
	.xscale = show_xscale,
	.yscale = show_yscale,
	.measure = show_measure_frame,
	.trig_icon = show_trig_icon,
	.title = show_title,
	.coupling = show_coupling,
	.trigged = show_trigged,
	.main = frame_main,
	.about = show_about
};
int last = 0;
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
static int
frame_main(void)
{
	dso_frame.measure(dso.measure_number);
	dso_frame.xscale();
	dso_frame.yscale();
	dso_frame.trigged();
	dso_frame.coupling();


	if (last) {
		dso_frame.gnd();
		dso_frame.trig();
	}else {
		dso_frame.trig();
		dso_frame.gnd();
	}
	dso_frame.position();
	dso_frame.trig_icon(0);

	if (dso.about_flag) dso_frame.about();

	return 0;
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
static int
show_grid(void)
{
	BOX_T b;
	RECT_T r;
	int i, j;

	b.startx = 2;
	b.starty = 24 - 22;
	b.endx = 416;
	b.endy = 237;
	b.attrib = (BOX_RECESSED);
	b.color = COLOR_BLACK;
	gui.box(&b);


	r.x = 4 + 8;
	r.y = 26 + 8 - 24;
	r.height = 199;
	r.width = 399;
	r.fill_flag = 0;
	r.color = make_rgb565(44, 71, 0);
	gui.rect(&r);


	lcd_ctl.b.csrmode = CSRMODE_V;
	lcd_ctl(lcd_ctl.w);

	for (i = 1; i < 16; i++) {
		if (i == 8) continue;
		//gui.line(12+i*25,34,12+i*25,234,make_rgb565(44,71,0));
		lcd_csrx(i * 25 + 12);
		lcd_csry(35 - 24);

		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));

		for (j = 2; j < 40; j++) {
			lcd_data(0);
			lcd_data(0);
			lcd_data(0);
			lcd_data(0);
			lcd_data(make_rgb565(44, 71, 0));
		}
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
	}


	lcd_ctl.b.csrmode = CSRMODE_H;
	lcd_ctl(lcd_ctl.w);

	for (i = 1; i < 8; i++) {
		if (i == 4) continue;
		lcd_csrx(13);
		lcd_csry(i * 25 + 34 - 24);


		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		for (j = 2; j < 80; j++) {
			lcd_data(0);
			lcd_data(0);
			lcd_data(0);
			lcd_data(0);
			lcd_data(make_rgb565(44, 71, 0));
		}
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
		lcd_data(make_rgb565(44, 71, 0));
	}
	gui.line(212, 34 - 24, 212, 233 - 24, make_rgb565(44, 71, 0));
	gui.line(12, 134 - 24, 411, 134 - 24, make_rgb565(44, 71, 0));

	return 0;
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
static int
show_gnd(void)
{
	const unsigned short int pic_cursor[] = {
		COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
		COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_BLACK, COLOR_BLACK,
		COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_BLACK,
		COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME,
		COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_BLACK,
		COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_BLACK, COLOR_BLACK,
		COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_LIME, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
	};
	RECT_T r;

	r.x = 4;
	r.y = 34 - 3 - 24 + (1 - dso.offset) * 100;
	r.width = 8;
	r.height = 7;
	r.fill_flag = FILL_PICTURE;
	r.p = pic_cursor;

	gui.rect(&r);


	return 0;
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
static int
show_trig(void)
{
	const unsigned short int pic_cursor[] = {
		COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
		COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK,
		COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,
		COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
		COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK,
		COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK,
		COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
	};
	RECT_T r;

	r.x = 4;
	r.y = 10 + (1 - dso.trigger_level) * 200 - 3;
	r.width = 8;
	r.height = 7;
	r.fill_flag = FILL_PICTURE;
	r.p = pic_cursor;

	gui.rect(&r);


	return 0;
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
static int
show_position(void)
{
	const unsigned short int pic_cursor[] = {
		make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0),
		COLOR_BLACK, make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), COLOR_BLACK,
		COLOR_BLACK, COLOR_BLACK, make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), make_rgb565(44, 71, 0), COLOR_BLACK, COLOR_BLACK,
		COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, make_rgb565(44, 71, 0), COLOR_BLACK, COLOR_BLACK, COLOR_BLACK,
	};
	RECT_T r;

	r.y = 6;
	r.x = 209;
	r.width = 7;
	r.height = 4;
	r.fill_flag = FILL_PICTURE;
	r.p = pic_cursor;

	gui.rect(&r);


	return 0;
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
static int
show_measure_frame(int number)
{
	BOX_T b;
	STRING_T s;
	int i;
	const char * str_frequency[] = {
		"频率", "Freq"
	};
	const char * str_vpp[] = {
		"峰峰值", "Vpk-pk"
	};
	const char * str_vrms[] = {
		"有效值", "Vrms"
	};
	const char * str_vavg[] = {
		"平均值", "Vavg"
	};

	font._default.double_byte = &simsun12;
	font._default.single_byte = &fixedsys;

	if (number > 4) number = 4;

	for (i = 3; i >= 4 - number; i--) {
		b.startx = 280;
		b.starty = 90 + i * 30;
		b.endx = 400;
		b.endy = 110 + i * 30;
		b.attrib = BOX_RAISED;
		b.color = COLOR_WINDOW_BACKGROUND;
		gui.box(&b);

		if (measure_buffer[3 - i].type == MEASURE_FREQUENCY) {
			s.x = 282;
			s.y = 92 + 30 * i;
			s.inverse = NULL;
			s.color = COLOR_BLACK;
			s.background_color = COLOR_WINDOW_BACKGROUND;
			s.space.line = 0;
			s.space.word = 0;

			if (dso.frequency > 1000000.) font.printf(&s, "%s：%.3fMHz", str_frequency[sys.language], dso.frequency / 1000000.);
			else if (dso.frequency > 1000.) font.printf(&s, "%s：%.2fkHz", str_frequency[sys.language], dso.frequency / 1000.);
			else font.printf(&s, "%s：%.2fHz", str_frequency[sys.language], dso.frequency);
		}

		if (measure_buffer[3 - i].type == MEASURE_VPP) {
			s.x = 282;
			s.y = 92 + 30 * i;
			s.inverse = NULL;
			s.color = COLOR_BLACK;
			s.background_color = COLOR_WINDOW_BACKGROUND;
			s.space.line = 0;
			s.space.word = 0;

			font.printf(&s, "%s：%.2fV", str_vpp[sys.language], dso.vpp);
		}

		if (measure_buffer[3 - i].type == MEASURE_VRMS) {
			s.x = 282;
			s.y = 92 + 30 * i;
			s.inverse = NULL;
			s.color = COLOR_BLACK;
			s.background_color = COLOR_WINDOW_BACKGROUND;
			s.space.line = 0;
			s.space.word = 0;

			font.printf(&s, "%s：%.2fV", str_vrms[sys.language], dso.vrms);
		}

		if (measure_buffer[3 - i].type == MEASURE_VAVG) {
			s.x = 282;
			s.y = 92 + 30 * i;
			s.inverse = NULL;
			s.color = COLOR_BLACK;
			s.background_color = COLOR_WINDOW_BACKGROUND;
			s.space.line = 0;
			s.space.word = 0;

			font.printf(&s, "%s：%.0fmV", str_vavg[sys.language], dso.vavg * 1000);
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
show_title(void)
{
	STRING_T s;


	font._default.single_byte = &tahoma9;
	s.x = 75;
	s.y = 217;
	s.space.line = 0;
	s.space.word = 0;
	s.color = make_rgb565(44, 71, 0);
	s.background_color = COLOR_BLACK;
	s.inverse = NULL;

	font.printf(&s, "[ iBoard DSO ]");

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
show_trig_icon(int flag)
{
	int i;

	flag = dso.trigger_type;
	//posedge
	gui.set_cursor(381, 230);
	gui.line_to(385, 230, flag == 0 ? COLOR_LIME : make_rgb565(44, 71, 0));
	gui.line_to(385, 215, flag == 0 ? COLOR_LIME : make_rgb565(44, 71, 0));
	gui.line_to(389, 215, flag == 0 ? COLOR_LIME : make_rgb565(44, 71, 0));

	for (i = 0; i <= 10; i++) {
		gui.set_cursor(385, 220);
		gui.line_to(380 + i, 225, flag == 0 ? COLOR_LIME : make_rgb565(44, 71, 0));
	}
	//negedge

	gui.set_cursor(409, 230);
	gui.line_to(405, 230, flag == 1 ? COLOR_LIME : make_rgb565(44, 71, 0));
	gui.line_to(405, 215, flag == 1 ? COLOR_LIME : make_rgb565(44, 71, 0));
	gui.line_to(401, 215, flag == 1 ? COLOR_LIME : make_rgb565(44, 71, 0));

	for (i = 0; i <= 10; i++) {
		gui.set_cursor(405, 225);
		gui.line_to(400 + i, 220, flag == 1 ? COLOR_LIME : make_rgb565(44, 71, 0));
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
show_xscale(void)
{
	char * x_str[] = {
		"1us/", "2us/", "5us/", "10us/", "20us/", "50us/", "100us/", "200us/", "500us/", "1ms/", "2ms/", "5ms/", "10ms/", "20ms/", "50ms/", "100ms/"
	};

	STRING_T s;

	font._default.single_byte = &tahoma9;

	s.x = 210;
	s.y = 217;
	s.space.line = 0;
	s.space.word = 0;
	s.color = COLOR_LIME;
	s.background_color = COLOR_BLACK;
	s.inverse = NULL;

	font.printf(&s, "%s", x_str[dso.x_scale]);

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
show_yscale(void)
{
	char * y_str[] = {
		"5V/", "2V/", "1V/", "500mV/", "200mV/", "100mV/", " 50mV/", "20mV/", "10mV/"
	};
	STRING_T s;

	font._default.single_byte = &tahoma9;

	s.x = 14;
	s.y = 217;
	s.space.line = 0;
	s.space.word = 0;
	s.color = COLOR_LIME;
	s.background_color = COLOR_BLACK;
	s.inverse = NULL;

	font.printf(&s, "%s", y_str[dso.y_scale]);

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
show_coupling(void)
{
	STRING_T s;
	int i;
	const char * coup_str[2][3] = {
		{ "直流", "交流", "地" },
		{ " DC ", " AC ", "GND " }
	};

	font._default.single_byte = &tahoma9;
	font._default.double_byte = &simsun12;

	for (i = 0; i < 3; i++) {
		s.x = 75 + i * 35;
		s.y = 217;
		s.space.line = 0;
		s.space.word = 0;
		s.color = dso.coupling == i ? COLOR_LIME : make_rgb565(44, 71, 0);
		s.background_color = COLOR_BLACK;
		s.inverse = NULL;

		font.printf(&s, "%s", coup_str[sys.language][i]);
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
show_trigged(void)
{
	STRING_T s;

	font._default.single_byte = &tahoma9;
	font._default.double_byte = &simsun12;


	s.x = 320;
	s.y = 217;
	s.space.line = 0;
	s.space.word = 0;
	s.color = (dso.trigged == 1 ? COLOR_LIME : make_rgb565(44, 71, 0));
	s.background_color = COLOR_BLACK;
	s.inverse = NULL;

	font.printf(&s, "%s", sys.language == 0 ? "已触发" : "Trigged");


	return 0;
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

static int
show_about(void)
{
	SPLITTER_T sp;
	BOX_T b;
	STRING_T s;

	const char * about[2] = {
		"　　基于  iBoard  的数字存储示波器，\n版权所有 XiaomaGee。欢迎完善，但不\n得用于商业目的！\n　　本系统基于 X-GUI 完成人机界面。\n",
		"  Digital Storage Oscilloscope(DSO) \n  based on iBoard. Copyright XiaomaGee.\n  The DSO user interface Based on X-GUI.\n\n"
	};

	b.startx = 40;
	b.starty = 50;
	b.endx = 265;
	b.endy = 200;
	b.attrib = BOX_RAISED;
	b.color = COLOR_WINDOW_BACKGROUND;
	gui.box(&b);

	sp.x = 40;
	sp.y = 80;
	sp.extend = 224;
	sp.attrib = SPLITTER_H | SPLITTER_RECESSED;
	gui.splitter(&sp);

	font._default.single_byte = &fixedsys;
	font._default.double_byte = &simsun16;

	s.x = 80;
	s.y = 56;
	s.background_color = COLOR_WINDOW_BACKGROUND;

	s.color = COLOR_BLACK;
	s.space.line = 0;
	s.space.word = 0;
	s.inverse = NULL;
	font.printf(&s, "%s", sys.language == 0 ? "关于 iBoard DSO..." : "About iBoard DSO...");

	font._default.single_byte = &tahoma8;
	font._default.double_byte = &simsun12;
	s.x = 50;
	s.y = 90;
	s.background_color = COLOR_WINDOW_BACKGROUND;

	s.color = COLOR_BLACK;
	s.space.line = 2;
	s.space.word = 0;
	s.inverse = NULL;
	font.printf(&s, "%s  V%s %s C%d\n  [XiaomaGee@Gmail.com] QQ:15959622", about[sys.language], rev, __DATE__, __ARMCC_VERSION);

	return 0;
}
