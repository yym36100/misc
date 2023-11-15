/*------------------------------------------------------
   FILE NAME   : bignumber.c
   DESCRIPTION : bignumber
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-10
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/


//---------------- Include files ------------------------//
#include "..\include\font.h"
#include <string.h>

//---------------- Function Prototype -------------------//
static int get(FONT_MATRIX_T *);

//---------------- Variable -----------------------------//


SINGLE_BYTE_FONT_T courier = {
	.name = "Courier 10",
	.id = FONT_UNREGISTERED,
	.height = 16,
	.width = 8,
	.dat = (void*)rc_courier,
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
	f->height = courier.height;
	f->width = courier.width;
	f->dat = (char*)courier.dat + (f->character[0] - ' ') * 16;

	return 0;
}

