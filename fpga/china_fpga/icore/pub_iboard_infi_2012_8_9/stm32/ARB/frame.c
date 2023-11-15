/*------------------------------------------------------
   FILE NAME   : frame.c
   DESCRIPTION : frame
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\frame.h"
#include "..\include\gui_core.h"
//---------------- Function Prototype -------------------//
static int set_window(int);
static int diagram(void);
static int infomation(void);
static int cymometer(void);


//---------------- Variable -----------------------------//
FRAME_T frame = {
	.set_window = set_window,
//	.diagram = diagram,
//	.infomation = infomation,
	//.cymometer = cymometer
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
set_window(int type)
{
	BOX_T b;

	//freq
	b.startx = 2;
	b.starty = 185;
	b.endx = 399 + type;
	b.endy = 236;
	b.attrib = (type == 0 ? BOX_FRAME : BOX_RECESSED);
	b.color = (type == 0 ? COLOR_WINDOW_BACKGROUND : COLOR_BLACK);
	gui.box(&b);

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
diagram(void)
{
	BOX_T b;

	b.startx = 2;
	b.starty = 23;
	b.endx = 285;
	b.endy = 184;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK;
	gui.box(&b);

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
infomation(void)
{
	BOX_T b;

	b.startx = 286;
	b.starty = 23;
	b.endx = 478;
	b.endy = 184;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK;
	gui.box(&b);

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
cymometer(void)
{
	BOX_T b;

	//freq
	b.startx = 2;
	b.starty = 23;
	b.endx = 478;
	b.endy = 184;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK;
	gui.box(&b);

	b.startx = 2;
	b.starty = 185;
	b.endx = 478;
	b.endy = 236;
	b.attrib = BOX_FRAME;
	b.color = COLOR_WINDOW_BACKGROUND;
	gui.box(&b);

	return 0;
}   
