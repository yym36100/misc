/*------------------------------------------------------
FILE NAME   : font.h
DESCRIPTION : font header
VERSION     : 0.0.0
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-8
MODIFY DATE :
LOGS        :-\

--------------------------------------------------------*/

#ifndef __font_h__
#define __font_h__


//---------------- Include Files ------------------------//
#include "..\include\gui_core.h"

//----------------- Define ------------------------------//
#define	DIRECTION_H	0
#define	DIRECTION_V	1

#define	FONT_UNREGISTERED	99999

#define	EFFECT_NONE	0
#define	EFFECT_INVERSE	1



#define max(a,b)	(a>b?a:b)
#define	min(a,b)	(a>b?b:a)

//----------------- Data Struct -------------------------//
typedef struct _FONT_MATRIX {
	unsigned char character[2];
	int direction;
	int height;
	int width;
	 char const * dat;
}FONT_MATRIX_T;

typedef	struct	_SINGLE_BYTE_FONT{
char * name;
unsigned long int id;
int	height;
int width; //width!=0 is monospaced font, width==0 is proportional font
char first_char;

int (*get_matrix)(FONT_MATRIX_T *);
void * dat;
struct _SINGLE_BYTE_FONT * pre;
struct _SINGLE_BYTE_FONT * next;
}SINGLE_BYTE_FONT_T;



typedef struct _DOUBLE_BYTE_FONT{
	char * name;
	unsigned long int id;
	int height;
	int width;
	int (*get_matrix)(FONT_MATRIX_T *);
	void * dat;
	struct _DOUBLE_BYTE_FONT * pre;
	struct _DOUBLE_BYTE_FONT * next;
}DOUBLE_BYTE_FONT_T;



typedef struct _LOGIC_FONT{
	char * name;
	int height;
	SINGLE_BYTE_FONT_T * single_byte;
	DOUBLE_BYTE_FONT_T * double_byte;
}LOGIC_FONT_T;


typedef struct _INVERSE{

	int start;
	int end;
	COLOR_T color;
	COLOR_T background_color;

	struct _INVERSE * next;

}INVERSE_T;



typedef struct{
	int x;
	int y;
	int color;
	int background_color;
	int effect;

	INVERSE_T * inverse;
	struct{
		int word;
		int line;
	}space;

}STRING_T;



typedef struct{
	LOGIC_FONT_T  _default;
	int (* initialize)(void);
	int (* register_single_byte_font)(SINGLE_BYTE_FONT_T *);
	int (* register_double_byte_font)(DOUBLE_BYTE_FONT_T *);
	int (* unregister_single_byte_font)(SINGLE_BYTE_FONT_T *);
	int (* unregister_double_byte_font)(DOUBLE_BYTE_FONT_T *);
	int (* printf)(STRING_T *,const char *,...);

}FONT_T;

//---------------- Extern Resource ----------------------//
extern char font_buffer[];
extern  FONT_T font;
extern SINGLE_BYTE_FONT_T * single_font;
extern DOUBLE_BYTE_FONT_T * double_font;


extern SINGLE_BYTE_FONT_T tahoma8;
extern SINGLE_BYTE_FONT_T tahoma9;
extern SINGLE_BYTE_FONT_T tahoma10;
extern SINGLE_BYTE_FONT_T tahoma11;
extern SINGLE_BYTE_FONT_T tahoma12;
extern SINGLE_BYTE_FONT_T tahoma26;
extern DOUBLE_BYTE_FONT_T simsun12;
extern DOUBLE_BYTE_FONT_T simsun16;
extern DOUBLE_BYTE_FONT_T simsun16f;
extern SINGLE_BYTE_FONT_T borlandTE;
extern SINGLE_BYTE_FONT_T fixedsys;
extern SINGLE_BYTE_FONT_T monaco;
extern SINGLE_BYTE_FONT_T courier;
extern SINGLE_BYTE_FONT_T	nix96;
extern SINGLE_BYTE_FONT_T	nix48;
extern SINGLE_BYTE_FONT_T swave;


extern DOUBLE_BYTE_FONT_T	simhei24;

//extern SINGLE_BYTE_FONT_T swave;





#endif //__font_h__

