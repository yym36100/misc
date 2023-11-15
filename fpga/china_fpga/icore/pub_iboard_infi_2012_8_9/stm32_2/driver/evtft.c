/*------------------------------------------------------
   FILE NAME   : evtft.c
   DESCRIPTION : evtft driver for evtft36 / evtft43 /evga86
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\evtft.h"
#include "..\include\color.h"


//---------------- Function Prototype -------------------//
static int initialize(void);
static int set_point(int /* x */, int /* y */, unsigned short int /* color */);
static unsigned short int get_point(int /* x */, int /* y */);
static int cls(COLOR_T c);
static int write_a(void);
static int write_b(void);
void change(void);


//---------------- Variable -----------------------------//
LCD_T lcd = {
	.initialize = initialize,
	.set_point = set_point,
	.get_point = get_point,
	.cls = cls,
	.write_a = write_a,
	.write_b = write_b,
	.change = change
};

LCD_CTL_T lcd_ctl;

//-----------------Function------------------------------//
/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
initialize(void)
{
	int i;

	lcd_ctl.w = 1;
	lcd_ctl.b.csrmode = 0;

	LCD_CTL = DISPLAY_OFF;

	LCD_ADDX = 0;
	LCD_ADDY = 0;

	for (i = 0; i < LCD_XSIZE * LCD_YSIZE; i++) LCD_DATA = 0;

	LCD_CTL = DISPLAY_ON;

	return 0;
}
/*-------------------------------------------------------
   NAME       : set_point
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
set_point(int x, int y, unsigned short int color)
{
	LCD_ADDX = x;
	LCD_ADDY = y;

	LCD_DATA = color;

	return 0;
}
/*-------------------------------------------------------
   NAME       : get_point
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static unsigned short int
get_point(int x, int y)
{
	LCD_ADDX = x;
	LCD_ADDY = y;

	return LCD_DATA;
}
/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
cls(COLOR_T c)
{
	int i;


	lcd_ctl.b.csrmode = 0;
	lcd_ctl(lcd_ctl.w);
	LCD_ADDX = 0;
	LCD_ADDY = 0;

	for (i = 0; i < LCD_XSIZE * LCD_YSIZE; i++) LCD_DATA = c;


	return 0;
}
/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
write_a(void)
{
	lcd_ctl.b.write_buf = 0;

	lcd_ctl(lcd_ctl.w);

	return 0;
}
/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
write_b(void)
{
	lcd_ctl.b.write_buf = 1;

	lcd_ctl(lcd_ctl.w);

	return 0;
}

/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
void change(void)
{
	static int i = 0;

	if (i++ % 2) {
		lcd_ctl.b.disp_buf = 1;
		lcd_ctl.b.write_buf = 0;
		LCD_CTL = lcd_ctl.w;
	}else {
		lcd_ctl.b.disp_buf = 0;
		lcd_ctl.b.write_buf = 1;
		LCD_CTL = lcd_ctl.w;
	}
}
