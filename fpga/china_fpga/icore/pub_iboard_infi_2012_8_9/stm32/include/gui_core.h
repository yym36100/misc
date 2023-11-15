/*------------------------------------------------------
FILE NAME   : gui_core.h
DESCRIPTION : gui_core header
VERSION     : 0.0.0
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\

--------------------------------------------------------*/

#ifndef __gui_core_h__
#define __gui_core_h__


//---------------- Include Files ------------------------//
#include "..\include\color.h"
#include "..\include\font.h"
//----------------- Define ------------------------------//
#define BOX_RECESSED	0
#define	BOX_RAISED	1
#define	BOX_FRAME	2

#define SPLITTER_H	0
#define	SPLITTER_V	1
#define	SPLITTER_RECESSED	0X0
#define	SPLITTER_RAISED	0X2
  
#define	SPLITTER_CLEAR	0X80

#define FILL_NONE	0
#define FILL_COLOR	1
#define FILL_PICTURE	2

//----------------- Data Struct -------------------------//

typedef struct{
	int startx;
	int starty;
	int endx;
	int endy;
	COLOR_T color;
	unsigned short attrib;
}BOX_T;



typedef struct{
	int x;
	int y;
	int height;
	int width;
	int fill_flag;
	COLOR_T color;
	const unsigned short int *p;
}RECT_T;


typedef struct{
	int x0;
	int y0;
	int x1;
	int y1;
}REGION_T;

typedef struct{
	int x;
	int y;
	int width;
	int percentage;
	COLOR_T color;
}PROCESSBAR_T;


typedef struct{
	int attrib;
	int x;
	int y;
	int extend;
}SPLITTER_T;

typedef struct{
	int attrib;
	int x;
	int y;
}CHECK_BOX_T;




typedef struct{
	REGION_T region;
	int (* dot)(int ,int ,COLOR_T /* c */);
	int (* line)(int /* x0 */,int /* y0 */,int /* x1 */,int /* y1 */,COLOR_T c);
	int (* rect)(RECT_T * /* r */);
	int (* box)(BOX_T * /* b */ );
	int (* set_cursor)(int /* x */,int /* y */);
	int (* line_to)(int /* x */,int /* y */,COLOR_T /* c */);
	int (* arrow)(int x,int y,int dir,COLOR_T c);
	int (* processbar)(PROCESSBAR_T *);
	int (* splitter)(SPLITTER_T *);
	int (* check_box)(CHECK_BOX_T *);
	int (* circle)(int x,int y,int r,int fill,COLOR_T c);

}GUI_T;


//---------------- Extern Resource ----------------------//
extern GUI_T gui;

#endif //__gui_core_h__

