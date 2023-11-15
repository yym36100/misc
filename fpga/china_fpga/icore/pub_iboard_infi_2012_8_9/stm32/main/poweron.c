/*------------------------------------------------------
   FILE NAME   : poweron.c
   DESCRIPTION : poweron
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\nvic.h"
#include "..\include\rcc.h"
#include "..\usb_include\usb.h"
#include "..\usb_include\usb_command.h"
#include "..\include\evtft.h"
#include "..\include\pwm.h"
#include "..\include\fsmc.h"
#include "..\include\color.h"
#include "..\include\gui_core.h"
#include "..\include\event.h"

#include "..\include\systick.h"
#include "..\include\usart.h"
#include "..\include\spi.h"
#include "..\include\flash.h"
#include "..\include\button.h"
#include "..\include\diagram.h"

#include "..\include\main.h"
#include "..\include\frame.h"


#include "..\include\function.h"
#include "..\include\infomation.h"

#include "..\include\font.h"

#include "..\include\config.h"
#include "..\include\adc.h"
#include "..\include\dac.h"
#include "..\include\power_on.h"
#include "..\include\test.h"
#include "..\include\clock.h"


#include <string.h>
//---------------- Function Prototype -------------------//


//---------------- Variable -----------------------------//

char *  button_sel_language[5] = {
	"简体中文",
	"繁體中文",
	"   English  ", NULL, NULL
};



//-----------------Function------------------------------//
void delay(int i)
{
	int j, k;

	for (k = 0; k < i; k++) for (j = 0; j < 2000000; j++) ;
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
int
power_on(void)
{
	int i, j;
	BOX_T b;
	int bak;
	STRING_T s;
	char buf[32];
	SPLITTER_T sp;
	INVERSE_T pin;

	rcc.initialize();
	nvic.initialize();
	fsmc.initialize();
	pwm.initialize(0);
	for (i = 0; i < 1000000; i++) ;
	lcd.initialize();

	usart1.initialize(19200);
	usart3.initialize(19200);
	systick.initialize();
	dac.initialize();
	adc.initialize();
	spi1.initialize();
	usb.initialize();
	font.initialize();


	lcd.cls(COLOR_WINDOW_BACKGROUND);

	if(event == KEY_RIGHT)test.key();	 //enter key  test
	if(event == KEY_LEFT)test.lcd(); //enter lcd test
	b.startx = 1;
	b.starty = 1;
	b.endx = 479;
	b.endy = 231;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK;
	gui.box(&b);


	sp.x = 0;
	sp.y = 235;
	sp.extend = 480;
	sp.attrib = SPLITTER_H | SPLITTER_RECESSED;

	gui.splitter(&sp);

	for (i = 0; i <= 100; i++) {
		for (j = 0; j < 50000; j++) ;
		pwm.initialize(i);
	}

	

	for (j = 0; j < 365; j += 3) {
		pin.start = 0;
		pin.end = 0;
		pin.color = COLOR_RED;
		pin.background_color = COLOR_BLACK;
		pin.next = NULL;

		s.x = 370 - j;

		s.y = 5;
		s.space.line = 2;
		s.space.word = 0;
		s.color = COLOR_LIME;
		s.background_color = COLOR_BLACK;
		s.inverse = &pin;

		font._default.single_byte = &tahoma26;
		font.printf(&s, "X-GUI ");
		for (i = 0; i < 1000; i++) ;
	}
	font.printf(&s, "\n");

	font._default.single_byte = &fixedsys;
	s.inverse = NULL;
	s.x = 5;
	font.printf(&s, "* sys start......\n"); delay(1);

	s.x = 5;
	font.printf(&s, "* Initialize sys tick......OK!\n"); delay(1);

	s.x = 5;
	font.printf(&s, "* System temperature is %.1f ...... OK!\n",calendar.temp); delay(1);

	s.x = 5;
	font.printf(&s, "* Initialize uart......OK!\n"); delay(1);

	s.x = 5;
	font.printf(&s, "* Initialize key / led driver......OK!\n"); delay(1);

	s.x = 5;
	font.printf(&s, "* Initialize spi driver......OK!\n"); delay(1);

	s.x = 5;
	font.printf(&s, "* Detect simplified chinese character libruary......"); delay(1);

	flash.read_32(4272, buf);

	if (buf[0] == 0x28) {
		font.printf(&s, "OK!\n"); delay(1);
		s.color = COLOR_RED;
		s.x = 5;
	}else font.printf(&s, "Fail!\n");

	//complicated chinese character
	s.color = COLOR_LIME;
	s.x = 5;
	font.printf(&s, "* Detect complicated chinese character libruary......"); delay(1);

	flash.read_32(SIMSUN16F_ADDRESS_BASE + 4272, buf);
	font._default.double_byte = &simsun16f;
	if (buf[0] == 0x28) {
		font.printf(&s, "OK!\n"); delay(2);
		s.color = COLOR_RED;
		s.x = 5;
	}else font.printf(&s, "Fail!\n");

	bak = s.y;

	font._default.double_byte = &simsun16;


	button.drawb(button_sel_language, 7);
	s.x = 86;
	s.y = 246;
	s.color = COLOR_BLACK;
	s.background_color = COLOR_WINDOW_BACKGROUND;

	s.space.line = 0;
	s.space.word = 0;
	s.inverse = NULL;

	font._default.double_byte = &simsun16f;

	font.printf(&s, "繁体中文");

	font._default.double_byte = &simsun16;
	font._default.single_byte = &fixedsys;
	s.x = 5;
	s.y = bak;
	s.space.line = 2;
	s.space.word = 0;
	s.color = COLOR_LIME;
	s.background_color = COLOR_BLACK;
	s.inverse = NULL;

	for (i = 2; i >= 0; i--) {
		if (event == KEY_F1 || event == KEY_F2 || event == KEY_F3) break;

		s.x = 5;
		s.y = bak;
		font.printf(&s, "* Please select the language(请选择语言)... <%d>  ", i);
		delay(1);
	}

	if (event == KEY_F1) {
		sys.language = LANGUAGE_CN;
		font._default.double_byte = &simsun16;
	}else if (event == KEY_F2) {
		sys.language = LANGUAGE_CN;
		font._default.double_byte = &simsun16f;
	}else if (event == KEY_F3) {
		sys.language = LANGUAGE_EN;
		font._default.double_byte = &simsun16;
	}else {
		sys.language = LANGUAGE_CN;
		font._default.double_byte = &simsun16;
	}

	event = EVENT_CLEAR;


	LED_OUTPUT;
	LED_ON;
	show_logo();


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
int show_logo(void)
{
	int i, j;
	unsigned short int *p;
	char buf[256];
	RECT_T r;
	STRING_T s;



	for (i = 0; i <= 100; i++) {
		pwm.initialize(100 - i);
		for (j = 0; j < 20000; j++) ;
	}

	lcd_ctl.b.write_buf = 0;
	lcd_ctl.b.disp_buf = 0;
	lcd_ctl.b.csrmode = 0;
	LCD_CTL = lcd_ctl.w;

	lcd_csrx(0);
	lcd_csry(0);

	for (i = 0; i < 1020; i++) {
		flash.read_256(LOGO_ADDRESS_BASE + i * 256, buf);

		p = (unsigned short int*)buf;
		for (j = 0; j < 128; j++) lcd_data(*p++);
	}

	for (i = 0; i <= 100; i++) {
		pwm.initialize(i);
		for (j = 0; j < 20000; j++) ;
	}

	r.x = 0;
	r.y = 230;
	r.width = 480;
	r.height = 42;
	r.fill_flag = 1;
	r.color = COLOR_RED;

	gui.rect(&r);
	font._default.single_byte = &fixedsys;

 
	s.x = 10;
	s.y = 235;
	s.color = COLOR_WHITE;
	s.background_color =COLOR_RED;

	s.space.line = 2;
	s.space.word = 0;
	s.inverse = NULL;

	font.printf(&s, "[iBoard infinity] firmware packages, Rev <%s>\nCopyRight XiaomaGee, http://www.heijin.org, %s",rev,__DATE__);

	return 0;
}
