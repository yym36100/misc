/*------------------------------------------------------
   FILE NAME   : tab.c
   DESCRIPTION : tab
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-9
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\gui_core.h"
#include "..\include\tab.h"
#include <string.h>

//---------------- Function Prototype -------------------//

//---------------- Variable -----------------------------//

//-----------------Function------------------------------//
/*-------------------------------------------------------
   NAME       : get_string_info
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int get_string_info(TAB_T * t, char * s, int * x, int * y)
{
	FONT_MATRIX_T f;
	int i;
	int tx = 0, ty[5];

	*x = 0;
	*y = 0;

	for (i = 0; i < 5; i++) ty[i] = 0;
	i = 0;

	while (*s != NULL) {
		if (*s >= ' ' && *s < 0x7f) {      //ascii
			f.character[0] = *s++;
			t->sfont->get_matrix(&f);

			tx += f.width;
			if (f.height > ty[i]) ty[i] = f.height;
		}else if (*s >= 0x7f) { //ºº×Ö
			f.character[0] = *s++;
			f.character[1] = *s++;
			t->dfont->get_matrix(&f);

			tx += f.width;
			if (f.height > ty[i]) ty[i] = f.height;
		}else if (*s == '\n') {
			if (tx > *x) *x = tx;
			tx = 0;
			*y += ty[i];
			i++;
			if (i > 4) return -1;
			s++;
		}
	}

	if (tx > *x) *x = tx;

	*y += ty[i];


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
int tab(TAB_T * t)
{
	int h, l;
	int x = t->x + 3;
	int y = t->y + 3;
	char ** p;
	int i = 0;
	int sub_h = 0, sub_l;
	STRING_T s;
	BOX_T b;
	DOUBLE_BYTE_FONT_T * fbak = font._default.double_byte;

	p = t->title;

	while (*p != NULL) {
		get_string_info(t, *p++, &l, &h);
		if (h > sub_h) sub_h = h;
	}

	sub_h += 10;

	for (i = 0; i < sub_h + 10; i++) gui.line(t->x, t->y + i, t->x + t->width, t->y + i, COLOR_WINDOW_BACKGROUND);


	p = t->title;


	font._default.single_byte = t->sfont;
	font._default.double_byte = t->dfont;

	b.startx = t->x;
	b.starty = y + sub_h + 1;
	b.endx = t->x + t->width;
	b.endy = t->y + t->height;
	b.attrib = BOX_RAISED;
	b.color = COLOR_WINDOW_BACKGROUND;
	gui.box(&b);


	i = 0;

	while (*p != NULL) {
		get_string_info(t, *p, &l, &h);

		sub_l = l + 10;
		if (i == t->active) {
			gui.line(x - 3, y - 3, x + sub_l + 3, y - 3, COLOR_WHITE);
			gui.line(x - 3, y - 3, x - 3, y + sub_h, COLOR_WHITE);
			gui.line(x + sub_l + 4, y - 3, x + sub_l + 4, y + sub_h, COLOR_GRAY);

			gui.line(x - 2, y + sub_h + 1, x + sub_l + 4, y + sub_h + 1, COLOR_WINDOW_BACKGROUND);
		}else if ((i + 1) == t->active) {
			gui.line(x, y, x + sub_l - 2, y, COLOR_WHITE);
			gui.line(x, y, x, y + sub_h, COLOR_WHITE);
		}else if ((i - 1) == t->active) {
			gui.line(x + 3, y, x + sub_l, y, COLOR_WHITE);

			gui.line(x + sub_l + 1, y, x + sub_l + 1, y + sub_h, COLOR_GRAY);
		}else {
			gui.line(x, y, x + sub_l, y, COLOR_WHITE);
			gui.line(x, y, x, y + sub_h, COLOR_WHITE);
			gui.line(x + sub_l + 1, y, x + sub_l + 1, y + sub_h, COLOR_GRAY);
		}

		s.x = x + 5;
		if (i == t->active) s.y = y + 2;
		else s.y = y + 5;
		s.background_color = COLOR_WINDOW_BACKGROUND;

		s.color = COLOR_BLACK;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;
		font.printf(&s, *p);

		x += sub_l + 2;

		i++;
		p++;
	}

	font._default.double_byte = fbak;
	return 0;
}
