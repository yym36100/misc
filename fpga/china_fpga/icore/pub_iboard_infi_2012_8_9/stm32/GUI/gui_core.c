/*------------------------------------------------------
   FILE NAME   : gui_core.c
   DESCRIPTION : gui_core
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


#include <math.h>
#include <stdlib.h>

//---------------- Function Prototype -------------------//
static int dot(int x, int y, COLOR_T c);
static int line(int /* x0 */, int /* y0 */, int /* x1 */, int /* y1 */, COLOR_T);
static int rect(RECT_T *);
static int box(BOX_T *);
static int line_to(int /* x */, int /* y */, COLOR_T /* c */);
static int set_cursor(int /* x */, int /* y */);
static int draw_arrow(int x, int y, int dir, COLOR_T c);
static int processbar(PROCESSBAR_T *);
static int splitter(SPLITTER_T *);
static int check_box(CHECK_BOX_T *);
static int circle(int x, int y, int r, int fill, COLOR_T c);



//---------------- Variable -----------------------------//
GUI_T gui = {
	.dot = dot,
	.line = line,
	.rect = rect,
	.box = box,
	.arrow = draw_arrow,
	.set_cursor = set_cursor,
	.line_to = line_to,
	.processbar = processbar,
	.splitter = splitter,
	.check_box = check_box,
	.circle = circle,
	.region.x0 = 0,
	.region.y0 = 0,
	.region.x1 = LCD_XSIZE,
	.region.y1 = LCD_YSIZE
};

static int cursor_x = 0;
static int cursor_y = 0;

//-----------------Function------------------------------//

/*-------------------------------------------------------
   NAME       : line
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
line(int x1, int y1, int x2, int y2, COLOR_T c)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int ux = ((dx > 0) << 1) - 1; //x的增量方向，取或-1
	int uy = ((dy > 0) << 1) - 1; //y的增量方向，取或-1
	int x = x1, y = y1, eps; //eps为累加误差

	int w = x2 - x1;
	int h = y2 - y1;
	int i;

	int absw = abs(w);
	int absh = abs(h);



	if (h == 0) {
		lcd_ctl.b.csrmode = CSRMODE_H;
		lcd_ctl(lcd_ctl.w);

		lcd_csrx(x2 > x1 ? x1 : x2);
		lcd_csry(y1);



		for (i = 0; i < absw + 1; i++) lcd_data(c);

		return 0;
	}

	if (w == 0) {
		lcd_csrx(x1);
		lcd_csry(y2 > y1 ? y1 : y2);

		lcd_ctl.b.csrmode = CSRMODE_V;
		lcd_ctl(lcd_ctl.w);

		for (i = 0; i < absh + 1; i++) lcd_data(c);

		return 0;
	}



	eps = 0; dx = abs(dx); dy = abs(dy);
	if (dx > dy) {
		for (x = x1; x != x2; x += ux) {
			gui.dot(x, y, c);
			eps += dy;
			if ((eps << 1) >= dx) {
				y += uy; eps -= dx;
			}
		}
	}else  {
		for (y = y1; y != y2; y += uy) {
			dot(x, y, c);
			eps += dx;
			if ((eps << 1) >= dy) {
				x += ux; eps -= dy;
			}
		}
	}

	return 0;
}



/*

     int  w,h,k,i,flagx=0,flagy=0,absw,absh;

     w=x1-x0;
     h=y1-y0;

     absw=abs(w);
     absh=abs(h);

     if(x1>x0)flagx=1;
             else flagx=-1;

     if(y1>y0)flagy=1;
             else flagy=-1;

     if(h==0){
             lcd_ctl.b.csrmode=CSRMODE_H;
             lcd_ctl(lcd_ctl.w);

             lcd_csrx(x1>x0?x0:x1);
             lcd_csry(y0);



             for(i=0;i<absw+1;i++)lcd_data(c);

             return 0;
     }

     if(w==0){

             lcd_csrx(x0);
             lcd_csry(y1>y0?y0:y1);

             lcd_ctl.b.csrmode=CSRMODE_V;
             lcd_ctl(lcd_ctl.w);

             for(i=0;i<absh+1;i++)lcd_data(c);

             return 0;
     }

     if(absw>absh){

             k=absh*1000000;
             k/=absw;
             k*=flagy;

             for(i=0;i<absw;i++){
                     lcd_csrx(i*flagx+x0);
                     lcd_csry((k*i)/1000000+y0);
                     lcd_data(c);
             }
     }else{
              k=absw*1000000;
              k/=absh;
              k*=flagx;

             for(i=0;i<absh;i++){
                     lcd_csrx((k*i)/1000000+x0);
                     lcd_csry(y0+i*flagy);
                     lcd_data(c);
             }
     }

     return 0;

   }

 */
/*-------------------------------------------------------
   NAME       : rect
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
rect(RECT_T * r)
{
	int i, j;

	if (r->fill_flag == 2) {
		lcd_ctl.b.csrmode = 0;
		lcd_ctl(lcd_ctl.w);

		for (j = 0; j < r->height; j++) {
			for (i = 0; i < r->width; i++) gui.dot(r->x + i, r->y + j, *r->p++);
		}
	}else if (r->fill_flag == 1) {
		if (r->height > r->width) {
			lcd_ctl.b.csrmode = CSRMODE_V;
			lcd_ctl(lcd_ctl.w);
			for (i = 0; i < r->width; i++) {
				lcd_csrx(i + r->x);
				lcd_csry(r->y);
				for (j = 0; j < r->height; j++) {
					lcd_data(r->color);
				}
			}
		}else{
			lcd_ctl.b.csrmode = CSRMODE_H;
			lcd_ctl(lcd_ctl.w);

			for (i = 0; i < r->height; i++) {
				lcd_csrx(r->x);
				lcd_csry(r->y + i);
				for (j = 0; j < r->width; j++) {
					lcd_data(r->color);
				}
			}
		}
	}else { //no fill
		lcd_ctl.b.csrmode = CSRMODE_H;
		lcd_ctl(lcd_ctl.w);

		lcd_csrx(r->x);
		lcd_csry(r->y);
		for (i = 0; i < r->width; i++) lcd_data(r->color);

		lcd_csrx(r->x);
		lcd_csry(r->y + r->height);
		for (i = 0; i < r->width; i++) lcd_data(r->color);

		lcd_ctl.b.csrmode = CSRMODE_V;
		lcd_ctl(lcd_ctl.w);

		lcd_csrx(r->x);
		lcd_csry(r->y);
		for (i = 0; i < r->height; i++) lcd_data(r->color);

		lcd_csrx(r->x + r->width);
		lcd_csry(r->y);
		for (i = 0; i < r->height + 1; i++) lcd_data(r->color);
	}

	return 0;
}
/*-------------------------------------------------------
   NAME       : box
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   -fix bug 2011.12.19
   ---------------------------------------------------------*/
static int
box(BOX_T * b)
{
	RECT_T r;


	r.x = b->startx + 1;
	r.y = b->starty + 1;
	r.height = b->endy - b->starty - 1;
	r.width = b->endx - b->startx - 2;
	r.color = b->color;
	r.fill_flag = 1;
	gui.rect(&r);





	switch (b->attrib) {
	case BOX_FRAME:

		b->endx -= 1;
		b->endy -= 1;

		gui.line(b->startx, b->starty, b->endx, b->starty, COLOR_GRAY);
		gui.line(b->startx, b->starty, b->startx, b->endy, COLOR_GRAY);
		gui.line(b->startx, b->endy, b->endx, b->endy, COLOR_GRAY);
		gui.line(b->endx, b->starty, b->endx, b->endy, COLOR_GRAY);

		gui.line(b->startx + 1, b->starty + 1, b->endx - 1, b->starty + 1, COLOR_WHITE);
		gui.line(b->startx + 1, b->starty + 1, b->startx + 1, b->endy - 1, COLOR_WHITE);
		gui.line(b->startx, b->endy + 1, b->endx + 1, b->endy + 1, COLOR_WHITE);
		gui.line(b->endx + 1, b->starty, b->endx + 1, b->endy + 1, COLOR_WHITE);

		break;

	case BOX_RECESSED:

		gui.line(b->startx, b->starty, b->endx - 1, b->starty, COLOR_GRAY);
		gui.line(b->startx, b->starty, b->startx, b->endy - 1, COLOR_GRAY);
		gui.line(b->startx, b->endy, b->endx - 1, b->endy, COLOR_WHITE);
		gui.line(b->endx - 1, b->starty, b->endx - 1, b->endy - 1, COLOR_WHITE);

		break;


	case BOX_RAISED:


		gui.line(b->startx, b->starty, b->endx - 1, b->starty, COLOR_WHITE);
		gui.line(b->startx, b->starty, b->startx, b->endy - 1, COLOR_WHITE);
		gui.line(b->startx, b->endy, b->endx - 1, b->endy, COLOR_GRAY);
		gui.line(b->endx - 1, b->starty, b->endx - 1, b->endy - 1, COLOR_GRAY);


		break;
	}

	return 0;
}

/*-------------------------------------------------------
   NAME       : set_cursor
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
set_cursor(int x, int y)
{
	cursor_x = x;
	cursor_y = y;

	return 0;
}

/*-------------------------------------------------------
   NAME       : line_to
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
line_to(int x, int y, COLOR_T c)
{
	line(cursor_x, cursor_y, x, y, c);
	set_cursor(x, y);

	return 0;
}
/*-------------------------------------------------------
   NAME       : dot
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
dot(int x, int y, COLOR_T c)
{
	lcd_csrx(x);
	lcd_csry(y);
	lcd_data(c);

	return 0;
}
/*-------------------------------------------------------
   NAME       : draw_arrow
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int draw_arrow(int x, int y, int dir, COLOR_T c)
{
	int i;

	switch (dir) {
	case 0:
		for (i = 0; i <= 10; i++) gui.line(x, y, x - 5 + i, y + 15, c);
		break;

	case 1:
		for (i = 0; i <= 10; i++) gui.line(x, y, x - 15, y - 5 + i, c);
		break;

	case 2:
		for (i = 0; i <= 10; i++) gui.line(x, y, x - 5 + i, y - 15, c);
		break;
	case 3:
		for (i = 0; i <= 10; i++) gui.line(x, y, x + 15, y - 5 + i, c);
		break;
	}

	return 0;
}
/*-------------------------------------------------------
   NAME       : processbar
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
processbar(PROCESSBAR_T * p)
{
	BOX_T b;
	RECT_T r;
	float temp;


	b.startx = p->x;
	b.starty = p->y;
	b.endx = p->x + p->width;
	b.endy = p->y + 19;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_WINDOW_BACKGROUND;

	gui.box(&b);

	r.x = p->x + 3;
	r.y = p->y + 3;
	r.height = 14;

	temp = p->width - 6;
	temp *= p->percentage;
	temp /= 100.0;

	r.fill_flag = 1;
	r.color = p->color;

	r.width = temp;

	gui.rect(&r);

	return 0;
}
/*-------------------------------------------------------
   NAME       : splitter
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
splitter(SPLITTER_T *s)
{
	int clear = s->attrib & SPLITTER_CLEAR;

	s->attrib &= ~SPLITTER_CLEAR;

	switch (s->attrib & 0xff) {
	case SPLITTER_H | SPLITTER_RECESSED:
		line(s->x, s->y, s->x + s->extend, s->y, clear ? COLOR_WINDOW_BACKGROUND : COLOR_GRAY);
		line(s->x, s->y + 1, s->x + s->extend, s->y + 1, clear ? COLOR_WINDOW_BACKGROUND : COLOR_WHITE);
		break;

	case SPLITTER_H | SPLITTER_RAISED:
		line(s->x, s->y, s->x + s->extend, s->y, clear ? COLOR_WINDOW_BACKGROUND : COLOR_GRAY);
		line(s->x, s->y - 1, s->x + s->extend, s->y - 1, clear ? COLOR_WINDOW_BACKGROUND : COLOR_WHITE);
		break;

	case SPLITTER_V | SPLITTER_RECESSED:
		line(s->x, s->y, s->x, s->y + s->extend, clear ? COLOR_WINDOW_BACKGROUND : COLOR_GRAY);
		line(s->x + 1, s->y, s->x + 1, s->y + s->extend, clear ? COLOR_WINDOW_BACKGROUND : COLOR_WHITE);
		break;

	case SPLITTER_V | SPLITTER_RAISED:
		line(s->x, s->y, s->x, s->y + s->extend, clear ? COLOR_WINDOW_BACKGROUND : COLOR_GRAY);
		line(s->x - 1, s->y, s->x - 1, s->y + s->extend, clear ? COLOR_WINDOW_BACKGROUND : COLOR_WHITE);
		break;
	}

	return 0;
}

/*-------------------------------------------------------
   NAME       : check_box
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
check_box(CHECK_BOX_T * c)
{
	BOX_T b;
	RECT_T r;

	b.startx = c->x;
	b.starty = c->y;
	b.endx = c->x + 10;
	b.endy = c->y + 9;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_WHITE;
	gui.box(&b);

	if (c->attrib == 1) {
		r.x = c->x + 2;
		r.y = c->y + 2;
		r.width = 6;
		r.height = 6;
		r.fill_flag = 1;
		r.color = COLOR_BLACK;

		rect(&r);
	}

	return 0;
}

/*-------------------------------------------------------
   NAME       : check_box
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/


static
void _draw_circle_8(int xc, int yc, int x, int y, COLOR_T c)
{
	gui.dot(xc + x, yc + y, c);

	gui.dot(xc - x, yc + y, c);

	gui.dot(xc + x, yc - y, c);

	gui.dot(xc - x, yc - y, c);

	gui.dot(xc + y, yc + x, c);

	gui.dot(xc - y, yc + x, c);

	gui.dot(xc + y, yc - x, c);

	gui.dot(xc - y, yc - x, c);
}

static int
circle(int xc, int yc, int r, int fill, COLOR_T c)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;


	if (fill) {
		// 如果填充（画实心圆）

		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi, c);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else {
		// 如果不填充（画空心圆）

		while (x <= y) {
			_draw_circle_8(xc, yc, x, y, c);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
	return 0;
}
