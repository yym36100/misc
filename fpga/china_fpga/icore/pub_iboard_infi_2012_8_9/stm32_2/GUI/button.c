/*------------------------------------------------------
   FILE NAME   : button.c
   DESCRIPTION : button
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\evtft.h"
#include "..\include\gui_core.h"
#include "..\include\hardware.h"
#include "..\include\button.h"
#include "..\include\font.h"
#include "..\include\main.h"
#include <string.h>


#include <math.h>
#include <stdlib.h>

//---------------- Function Prototype -------------------//

static int drawb(char *[5], int active);
static int drawl(char *[5], int active);

//---------------- Variable -----------------------------//
BUTTON_T button = {
	.drawb = drawb,
	.drawl = drawl
};


//-----------------Function------------------------------//

/*-------------------------------------------------------
   NAME       : draw
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
drawb(char *p[5], int active)
{
	int i;
	STRING_T s;
	BOX_T b;
	RECT_T r;

	font._default.single_byte = &tahoma10;
	font._default.double_byte = &simsun16;


	for (i = 0; i < 5; i++) {
	}

	s.inverse = NULL;

	for (i = 0; i < 5; i++) {
		if (p[i] != NULL) {
			b.startx = 3 + 80 * i;
			b.starty = 240;
			b.endx = 77 + 80 * i;
			b.endy = 269;
			b.attrib = (i == active ? 0 : 1);
			b.color = i == active ? sys.color : COLOR_WINDOW_BACKGROUND;
			gui.box(&b);
		}else {
			r.x = 3 + 80 * i;
			r.y = 240;
			r.height = 30;
			r.width = 74;
			r.fill_flag = 1;
			r.color = COLOR_WINDOW_BACKGROUND;

			gui.rect(&r);
		}


		if (p[i] == NULL) continue;
		s.x = 6 + 80 * i + (i == active ? 1 : 0);
		s.y = 246 + (i == active ? 1 : 0);
		s.background_color = i == active ? sys.color : COLOR_WINDOW_BACKGROUND;

		s.color = COLOR_BLACK;
		s.space.line = 0;
		s.space.word = 0;
		s.inverse = NULL;
		font.printf(&s, "%s", p[i]);
	}
	return 0;
}
/*-------------------------------------------------------
   NAME       : draw
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
drawl(char *p[5], int active)
{
	int i;
	STRING_T s;
	BOX_T b;
	RECT_T r;
	int flag[5] = { 0, 0, 0, 0, 0 };

	font._default.single_byte = &tahoma10;
	font._default.double_byte = &simsun16;


	for (i = 0; i < 5; i++) {
		if (strchr(p[i], '\n') == NULL) flag[i] = 0;
		else flag[i] = 1;
	}

	s.inverse = NULL;

	for (i = 0; i < 5; i++) {
		if (p[i] != NULL) {
			b.startx = 418;
			b.starty = 2 + i * 54;
			b.endx = 478;
			b.endy = 53 + i * 54;
			b.attrib = (i == active ? 0 : 1);
			b.color = i == active ? sys.color : COLOR_WINDOW_BACKGROUND;;
			gui.box(&b);
		}else {
			r.x = 418;
			r.y = 3 + i * 54;
			r.height = 54;
			r.width = 63;
			r.fill_flag = 1;
			r.color = COLOR_WINDOW_BACKGROUND;

			gui.rect(&r);
		}


		if (p[i] == NULL) continue;
		s.x = 422 + (i == active ? 1 : 0);
		s.y = (flag[i] ? 7 : 17) + 55 * i + (i == active ? 1 : 0);
		s.background_color = i == active ? sys.color : COLOR_WINDOW_BACKGROUND;

		s.color = COLOR_BLACK;
		s.space.line = 5;
		s.space.word = 0;
		s.inverse = 0;
		font.printf(&s, "%s", p[i]);
	}
	return 0;
}


