/*------------------------------------------------------
FILE NAME   : evtft.h
DESCRIPTION : fsmc driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __evtft_h__
#define __evtft_h__

//-----------------Include files-------------------------//

#include "..\include\hardware.h"
#include "..\include\color.h"

//----------------- Define ------------------------------//

#define	LCD_XSIZE	480
#define	LCD_YSIZE	272

#define LCD_DATA	*((volatile unsigned short int *)(0x60100000))
#define LCD_ADDX	*((volatile unsigned short int *)(0x60120000))
#define LCD_ADDY	*((volatile unsigned short int *)(0x60140000))
#define LCD_CTL		*((volatile unsigned short int *)(0x60160000))


#define DISPLAY_ON	1
#define	DISPLAY_OFF	0

#define	CSRMODE_H	0
#define	CSRMODE_V	1

#define lcd_data(x)	LCD_DATA=x
#define	lcd_csrx(x)	LCD_ADDX=x
#define	lcd_csry(x)	LCD_ADDY=x

#define	lcd_ctl(x)	LCD_CTL=x


//----------------- Typedef------------------------------//

typedef struct{
	int (* initialize)(void);
	int (* set_point)(int /* x */,int /* y */, unsigned short int /* color */);
	unsigned short int (* get_point)(int /* x */,int /* y */);
	int (* cls)(COLOR_T);
	void (* change)(void);
	int (* write_a)(void);
	int (* write_b)(void);
}LCD_T;

typedef union {
			struct {
			 unsigned short int dispen:1;
			 unsigned short int tmode:5;
			 unsigned short int csrmode:1;
			 unsigned short int write_buf:1;
			 unsigned short int disp_buf:1;
			 unsigned short int reserve1:6;
			 unsigned short int LED:1;			
		}b;
		unsigned short int w;
}LCD_CTL_T;

//----------------- Extern ------------------------------//
extern LCD_T lcd;
extern LCD_CTL_T lcd_ctl;

#endif //__evtft_h__
