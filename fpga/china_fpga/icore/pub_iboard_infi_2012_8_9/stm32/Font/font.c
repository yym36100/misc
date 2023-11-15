/*------------------------------------------------------
   FILE NAME   : font.c
   DESCRIPTION : font
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-8
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\font.h"
#include "..\include\evtft.h"
//#include "..\include\common.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

//---------------- Function Prototype -------------------//
static int init(void);
static int register_single_byte_font(SINGLE_BYTE_FONT_T *);
static int register_double_byte_font(DOUBLE_BYTE_FONT_T *);
static int xprintf(STRING_T *s, const char *fmt, ...);

//---------------- Variable -----------------------------//
FONT_T font = {
	.initialize = init,
	.register_single_byte_font = register_single_byte_font,
	.register_double_byte_font = register_double_byte_font,
	.printf = xprintf
};
SINGLE_BYTE_FONT_T * single_font;
DOUBLE_BYTE_FONT_T * double_font;

char bufb[1000];
char font_buffer[1332];     
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
init(void)
{
//	register_single_byte_fnt
	register_single_byte_font(&tahoma8);
	register_single_byte_font(&tahoma9);
	register_single_byte_font(&tahoma10);
	register_single_byte_font(&tahoma11);
	register_single_byte_font(&tahoma12);
	register_single_byte_font(&borlandTE);
	register_single_byte_font(&courier);
	register_single_byte_font(&fixedsys);
	register_single_byte_font(&monaco);
	register_single_byte_font(&tahoma26);
	register_single_byte_font(&nix96);
	register_single_byte_font(&nix48);

	//	register_double_byte_fnt
	register_double_byte_font(&simsun16);
	register_double_byte_font(&simsun12);
	register_double_byte_font(&simsun16f);
	register_double_byte_font(&simhei24);

	font._default.single_byte = &tahoma8;
	font._default.double_byte = &simsun12;
	font._default.height = max(font._default.single_byte->height, font._default.double_byte->height);

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
register_single_byte_font(SINGLE_BYTE_FONT_T *f)
{
	static int id = 0;

	if (f->id != FONT_UNREGISTERED) return -1;

	if (id == 0) { // first run
		single_font = f;
		single_font->pre = NULL;
		single_font->next = NULL;

		id++;

		return 0;
	}

	single_font->next = f;
	f->pre = single_font;
	single_font = f;
	f->id = id++;

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
register_double_byte_font(DOUBLE_BYTE_FONT_T *f)
{
	static int id = 0;

	if (f->id != FONT_UNREGISTERED) return -1;

	if (id == 0) { // first run
		double_font = f;
		double_font->pre = NULL;
		double_font->next = NULL;

		id++;

		return 0;
	}

	double_font->next = f;
	f->pre = double_font;
	double_font = f;
	f->id = id++;

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
xprint(STRING_T * s, const char *buf)
{
	int x_back = s->x;
	int len;
	int i, j, k, a;
	FONT_MATRIX_T f;
	int n_byte;
	char const * p;
	int no_double_byte_flag = 0;
	COLOR_T cf = 0, cb = 0;
	INVERSE_T *pinverse;

	if (s == NULL) return -1;

	if (font._default.double_byte == NULL) no_double_byte_flag = 1;

	len = strlen(buf);

	for (i = 0; i < len; ) {
		//inverse
		if (s->inverse == NULL) {
			cf = s->color;
			cb = s->background_color;
		}else {
			cf = s->color;
			cb = s->background_color;


			pinverse = s->inverse;

			while (pinverse != NULL) {
				if (i >= pinverse->start && i <= pinverse->end) {
					cf = pinverse->color;
					cb = pinverse->background_color;
					break;
				}
				pinverse = pinverse->next;
			}
		}



		if (buf[i] >= ' ' && buf[i] < 0x7f) { //ascii
			f.character[0] = buf[i++];
			font._default.single_byte->get_matrix(&f);
		}else if (buf[i] >= 0x7f) { //ºº×Ö
			f.character[0] = buf[i++];
			f.character[1] = buf[i++];
			if (no_double_byte_flag == 0) font._default.double_byte->get_matrix(&f);
		}else if (buf[i] == '\n') {
			s->x = x_back;
			s->y += max(font._default.single_byte->height, font._default.double_byte->height) + s->space.line;

			i++;
			continue;
		}else {
			i++;
			continue;
		}


		if (s->x + f.width > gui.region.x1 || s->x + f.width < gui.region.x0) return -1;
		if (s->y > gui.region.y1 || s->y < gui.region.y0) return -1;


		//display

		lcd_ctl.b.csrmode = f.direction;
		lcd_ctl(lcd_ctl.w);
		p = f.dat;

		if (f.direction == DIRECTION_H) {
			n_byte = f.width / 8;
			for (a = 0; a < f.height; a++) {
				lcd_csrx(s->x);
				lcd_csry(s->y + a);
				for (j = 0; j < n_byte; j++) {
					for (k = 0; k < 8; k++) if (*p & (1 << (7 - k))) lcd_data(cf);
						else lcd_data(cb);
					p++;
				}

				for (k = 0; k < f.width - 8 * n_byte; k++) if (*p & (1 << (7 - k))) lcd_data(cf);
					else lcd_data(cb);
				if (k != 0) p++;
			}
		}

		if (f.direction == DIRECTION_V) {
			n_byte = f.height / 8;
			for (a = 0; a < f.width; a++) {
				lcd_csrx(s->x + a);
				lcd_csry(s->y);
				for (j = 0; j < n_byte; j++) {
					for (k = 0; k < 8; k++) if (*p & (1 << (7 - k))) lcd_data(cf);
						else lcd_data(cb);
					p++;
				}
			}
		}

		s->x += f.width + s->space.word;
	}

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
xprint_nix(STRING_T * s, const char *buf)
{
	int len;
	int i, j, k, a;
	FONT_MATRIX_T f;
	int n_byte;
	char const * p;
	COLOR_T cf = 0, cb = 0;
	INVERSE_T *pinverse;



	if (s == NULL) return -1;


	len = strlen(buf);


	for (i = 0; i < len; ) {
				//inverse
		if (s->inverse == NULL) {
			cf = s->color;
			cb = s->background_color;
		}else {
			cf = s->color;
			cb = s->background_color;


			pinverse = s->inverse;

			while (pinverse != NULL) {
				if (i >= pinverse->start && i <= pinverse->end) {
					cf = pinverse->color;
					cb = pinverse->background_color;
					break;
				}
				pinverse = pinverse->next;
			}
		}

		
		
		if (buf[i + 1] == '.') {
			f.character[0] = buf[i] + 100;
			i++;
		}else
			f.character[0] = buf[i];

		font._default.single_byte->get_matrix(&f);

		i++;
		//display

		lcd_ctl.b.csrmode = f.direction;
		lcd_ctl(lcd_ctl.w);
		p = f.dat;


		n_byte = f.width / 8;
		for (a = 0; a < f.height; a++) {
			lcd_csrx(s->x);
			lcd_csry(s->y + a);
			for (j = 0; j < n_byte; j++) {
				for (k = 0; k < 8; k++) if (*p & (1 << (7 - k))) lcd_data(cf);
					else lcd_data(cb);
				p++;
			}
		}

		s->x += f.width;
	}

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
xprintf(STRING_T *s, const char *fmt, ...)
{
	va_list arg_ptr;

	memset(bufb, '\0', sizeof(bufb));

	va_start(arg_ptr, fmt);
	vsprintf(bufb, fmt, arg_ptr);
	va_end(arg_ptr);

	if (font._default.single_byte == &nix96 ||
	    font._default.single_byte == &nix48
	    ) xprint_nix(s, bufb);
	else xprint(s, bufb);

	return 0;
}
