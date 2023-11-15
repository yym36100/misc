/*------------------------------------------------------
FILE NAME   : Color.h
DESCRIPTION : Color header
VERSION     : 0.0.0
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\

--------------------------------------------------------*/

#ifndef __Color_h__
#define __Color_h__


//---------------- Include Files ------------------------//

//----------------- Define ------------------------------//

#define COLOR_BLACK     0x0000
#define COLOR_NAVY      0x0010
#define COLOR_GREEN     0x0400
#define COLOR_TEAL      0x0410
#define COLOR_MAROON    0x8000
#define COLOR_PURPLE    0x8010
#define COLOR_OLIVE     0x8400
#define COLOR_GRAY      0x8410
#define COLOR_SILVER    0xC618
#define COLOR_BLUE      0x001F
#define COLOR_LIME      0x07E0
#define COLOR_AQUA      0x07FF
#define COLOR_RED       0xF800
#define COLOR_FUCHSIA   0xF81F
#define COLOR_YELLOW    0xFFE0
#define COLOR_WHITE     0xFFFF
//#define	COLOR_ORANGE	0XFC80
#define COLOR_ORANGE		0xfc00
#define COLOR_DARK_GREEN	0x2a40
#define COLOR_DARK_GRAY		0x4208
#define	COLOR_DARK_BLUE		0x0018

#define	COLOR_WINDOW_BACKGROUND 0xce79 //	0xc618//0xd699
#define COLOR_WINDOW_SHADOW		0x8430

#define COLOR_DARK 0X39E7

#define COLOR_SYSTEM	0X9680


#define	get_rgb565_b_value(rgb)	((rgb&0x1f)<<3)
#define	get_rgb565_g_value(rgb)	(((rgb>>5)&0x3f)<<2)
#define get_rgb565_r_value(rgb)	(((rgb>>11)&0x1f)<<3)

#define	make_rgb565(r,g,b)	((r>>3)<<11 | (g>>2)<<5 | (b>>3))


//----------------- Data Struct -------------------------//

typedef  unsigned short int COLOR_T;
//---------------- Extern Resource ----------------------//


#endif //__Color_h__

