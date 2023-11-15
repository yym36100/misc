/*------------------------------------------------------
   FILE NAME   : monaco.c
   DESCRIPTION : monaco
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-9
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\font.h"
#include <string.h>

//---------------- Function Prototype -------------------//
static int get(FONT_MATRIX_T *);

//---------------- Variable -----------------------------//
extern const unsigned char rc_monaco[];

SINGLE_BYTE_FONT_T monaco = {
	.name = "Monaco",
	.id = FONT_UNREGISTERED,
	.height = 16,
	.width = 8,
	.dat = (void*)rc_monaco,
	.get_matrix = get,
	.pre = NULL,
	.next = NULL
};
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
get(FONT_MATRIX_T *f)
{
	f->direction = DIRECTION_V;
	f->height = monaco.height;
	f->width = monaco.width;
	f->dat = (char*)monaco.dat + (f->character[0] - ' ') * 16;

	return 0;
}

