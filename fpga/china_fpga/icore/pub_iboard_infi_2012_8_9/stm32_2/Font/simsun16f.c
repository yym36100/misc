/*------------------------------------------------------
   FILE NAME   : simsun16f.c
   DESCRIPTION : simsun16
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-8
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include <string.h>
#include "..\include\config.h"
#include "..\include\font.h"
#include "..\include\flash.h"

//---------------- Function Prototype -------------------//
static int get(FONT_MATRIX_T *f);
//---------------- Variable -----------------------------//

DOUBLE_BYTE_FONT_T simsun16f = {
	.name = "Simsun 16 ·±",
	.id = FONT_UNREGISTERED,
	.height = 16,
	.width = 16,
	.dat = NULL,
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
	unsigned long int offset;

	offset = f->character[0];
	offset -= 0xa1;
	offset *= 94;
	offset += f->character[1];
	offset -= 0xa1;
	offset *= 32;

	f->direction = DIRECTION_H;
	f->height = simsun16.height;
	f->width = simsun16.width;

	flash.read_32(offset + SIMSUN16F_ADDRESS_BASE, font_buffer);
	f->dat = font_buffer;

	return 0;
}

