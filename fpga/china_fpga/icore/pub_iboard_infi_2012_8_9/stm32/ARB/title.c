/*------------------------------------------------------
   FILE NAME   :title.c
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
#include <math.h>
#include <string.h>
//---------------- Function Prototype -------------------//
static int small_wave_index(int active);
static int name(void);
//---------------- Variable -----------------------------//
const TITLE_T title = {
	.wave_index = small_wave_index,
	.name = name
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
name(void)
{
	BOX_T b;
	STRING_T s;

	b.startx = 2;
	b.starty = 2;
	b.endx = 55;
	b.endy = 22;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK;
	gui.box(&b);

	font._default.single_byte = &tahoma9;
	s.x = 9;
	s.y = 4;
	s.space.line = 0;
	s.space.word = 0;
	s.color = COLOR_LIME;
	s.background_color = COLOR_BLACK;
	s.inverse = NULL;

	font.printf(&s, "%s", sys.language == 1 ? "i-Board" : "i-Board");

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
small_wave_index(int active)
{
	BOX_T b;
	STRING_T s;
	INVERSE_T pin;

	//small wave index

	b.startx = 57;
	b.starty = 2;
	b.endx = 400;
	b.endy = 22;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK;
	gui.box(&b);

	font._default.single_byte = &swave;
	s.x = 63;
	s.y = 4;
	s.space.line = 0;
	s.space.word = 3;
	s.color = make_rgb565(44, 71, 0);
	s.background_color = COLOR_BLACK;
	s.inverse = &pin;

	pin.start = active;
	pin.end = active;
	pin.color = COLOR_LIME;
	pin.background_color = COLOR_BLACK;
	pin.next = NULL;

	font.printf(&s, "abcdefghijklmnop");

	return 0;
}

