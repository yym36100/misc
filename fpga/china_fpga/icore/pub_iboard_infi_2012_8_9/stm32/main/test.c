/*------------------------------------------------------
   FILE NAME   : test.c
   DESCRIPTION : key & lcd test
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2012-3-22
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\nvic.h"
#include "..\include\rcc.h"
#include "..\usb_include\usb.h"
#include "..\usb_include\usb_command.h"
#include "..\include\evtft.h"
#include "..\include\pwm.h"
#include "..\include\fsmc.h"
#include "..\include\color.h"
#include "..\include\gui_core.h"
#include "..\include\event.h"

#include "..\include\systick.h"
#include "..\include\usart.h"
#include "..\include\spi.h"
#include "..\include\flash.h"
#include "..\include\button.h"
#include "..\include\diagram.h"

#include "..\include\main.h"
#include "..\include\frame.h"


#include "..\include\function.h"
#include "..\include\infomation.h"

#include "..\include\font.h"

#include "..\include\config.h"
#include "..\include\adc.h"
#include "..\include\dac.h"
#include "..\include\test.h"


#include <string.h>
//---------------- Function Prototype -------------------//
static int test_key(void);
static int test_lcd(void);


//---------------- Variable -----------------------------//

TEST_T test={
	.key=test_key,
	.lcd=test_lcd
};

const int key_tab[]={
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_ESC,
	KEY_ENTER,
	KEY_M1,
	KEY_M2,
	KEY_M3,
	KEY_M4,
	KEY_M5,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN
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
show_key(int active)
{
	BOX_T b;
	int i,j;
 	
	j=0;
	for(i = 0;i < 5; i ++ ){  //f1~5
		b.startx = 40 + i*55;
		b.starty = 170;
		b.endx = 80 + i*55;
		b.endy = 195;
		b.attrib = (active == i+j)?BOX_RECESSED:BOX_RAISED;
	//	b.color = (active == i+j)?COLOR_ORANGE:COLOR_WINDOW_BACKGROUND;
		b.color = COLOR_WINDOW_BACKGROUND;
		gui.box(&b);
	}
	j=5;

	for(i = 0;i < 2; i ++ ){   //esc enter
		b.startx = 310 + i*55;
		b.starty = 210;
		b.endx = 350 + i*55;
		b.endy = 235;
		b.attrib = (active == i+j)?BOX_RECESSED:BOX_RAISED;
	//	b.color = (active == i+j)?COLOR_ORANGE:COLOR_WINDOW_BACKGROUND;
		b.color = COLOR_WINDOW_BACKGROUND;
		gui.box(&b);
	}
	j=7;
	for(i = 0;i < 5; i ++ ){  //m1~5
		b.startx = 405;
		b.starty = 40+i*30;
		b.endx = 445;
		b.endy = 65+i*30;
		b.attrib = (active == i+j)?BOX_RECESSED:BOX_RAISED;
	//	b.color = (active == i+j)?COLOR_ORANGE:COLOR_WINDOW_BACKGROUND;
		b.color = COLOR_WINDOW_BACKGROUND;
		gui.box(&b);
	}
	j=12;
	for(i = 0;i < 2; i ++ ){   //<- ->
		b.startx = 310 + i*55;
		b.starty = 3;
		b.endx = 350 + i*55;
		b.endy = 27;
		b.attrib = (active == i+j)?BOX_RECESSED:BOX_RAISED;
	//	b.color = (active == i+j)?COLOR_ORANGE:COLOR_WINDOW_BACKGROUND;
		b.color = COLOR_WINDOW_BACKGROUND;
		gui.box(&b);
	}
	j=14;
	for(i = 0;i < 2; i ++ ){   //^ v
		b.startx = 453;
		b.starty = 152+i*50;
		b.endx = 478;
		b.endy = 192+i*50;
		b.attrib = (active == i+j)?BOX_RECESSED:BOX_RAISED;
	//	b.color = (active == i+j)?COLOR_ORANGE:COLOR_WINDOW_BACKGROUND;
		b.color = COLOR_WINDOW_BACKGROUND;
		gui.box(&b);
	}

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
test_key(void)
{
	BOX_T b;
	int flag = 0;
	int i;


	pwm.initialize(100);

	lcd.cls(COLOR_WINDOW_BACKGROUND);

	b.startx = 30;
	b.starty = 30;
	b.endx = 450;
	b.endy = 242;
	b.attrib = BOX_FRAME;
	b.color = COLOR_WINDOW_BACKGROUND;
	gui.box(&b);

	show_key(100);

	while(1){
		if(event){
			if(event == KEY_ENTER){
				if(flag)break ;
					else flag = 1;
				}else flag = 0;
			for(i=0;i<sizeof(key_tab);i++){
				if(key_tab[i] == event)break;
			}
			event = 0;
			show_key(i);
			for(i=0;i<1000000;i++);
			show_key(100);

		   }
		}
	lcd.cls(COLOR_WINDOW_BACKGROUND);

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
test_lcd(void)
{
 	int i, j;
 
	BOX_T b;
	int sys_color[]={
		COLOR_WHITE,
		COLOR_BLACK,

		COLOR_RED,
		COLOR_GREEN,
		COLOR_BLUE
	};

  pwm.initialize(100);

for(i=0;i<sizeof(sys_color)/4;i++){	
		lcd.cls(sys_color[i]);

		for(j=0;j<10000000;j++);
	}

 	lcd.cls(COLOR_WINDOW_BACKGROUND);
   
for(i=0;i<5;i++){
   	b.startx=10+i*90;
	b.starty=20;
	b.endx=80+i*90;
	b.endy=130;
	b.attrib=BOX_RECESSED;
	b.color=sys_color[i];
	gui.box(&b);
}	
 for(i=0;i<20000000;i++);
	return 0;
}

