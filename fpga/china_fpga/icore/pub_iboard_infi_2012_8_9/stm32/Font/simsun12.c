/*------------------------------------------------------
   FILE NAME   : simsun16.c
   DESCRIPTION : simsun16
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-8
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include <string.h>
#include "..\include\font.h"
#include "..\include\config.h"
#include "..\include\flash.h"

//---------------- Function Prototype -------------------//
static int get(FONT_MATRIX_T *f);
//---------------- Variable -----------------------------//

DOUBLE_BYTE_FONT_T simsun12 = {
	.name = "Simsun 12 ¼ò",
	.id = FONT_UNREGISTERED,
	.height = 16,
	.width = 12,
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
	f->height = simsun12.height;
	f->width = simsun12.width;

	flash.read_32(offset + SIMSUN12_ADDRESS_BASE, font_buffer);
	f->dat = font_buffer;

	return 0;
}

