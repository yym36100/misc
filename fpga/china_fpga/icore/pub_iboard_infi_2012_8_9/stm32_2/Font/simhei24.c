/*------------------------------------------------------
   FILE NAME   : simhei24.c
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

DOUBLE_BYTE_FONT_T simhei24 = {
	.name = "Simhei 24 ¼ò",
	.id = FONT_UNREGISTERED,
	.height = 24,
	.width = 24,
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
	offset -= 15;
	offset *= 94;
	offset += f->character[1];
	offset -= 0xa1;
	offset *= 72;

	f->direction = DIRECTION_V;
	f->height = simhei24.height;
	f->width = simhei24.width;

	flash.read_72(offset + SIMHEI24_ADDRESS_BASE, font_buffer);
	f->dat = font_buffer;

	return 0;
}

