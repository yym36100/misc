/*------------------------------------------------------
   FILE NAME   : fixedsys.c
   DESCRIPTION : fixedsys
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
extern const unsigned char rc_fixedsys[];

SINGLE_BYTE_FONT_T fixedsys = {
	.name = "Fixedsys",
	.id = FONT_UNREGISTERED,
	.height = 16,
	.width = 8,
	.dat = (void*)rc_fixedsys,
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
	f->height = fixedsys.height;
	f->width = fixedsys.width;
	f->dat = (char*)fixedsys.dat + (f->character[0] - ' ') * 16;

	return 0;
}

