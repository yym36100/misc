/*
 * File						: burst.c
 * Description		: This file is ...
 * Author					: XiaomaGee@Gmail.com
 * Copyright			:
 *
 * History
 *--------------------
 * Rev						: 0.00
 * Date						: 07/26/2012
 *
 * create.
 *--------------------
 */
 
//----------------- Include files ------------------------//
 
 #include "..\include\config.h" 
 #include "..\include\burst.h"
 #include "..\include\main.h"
 #include "..\include\button.h"
 #include "..\include\font.h"
 #include "..\include\gui_core.h"
 #include "..\include\color.h"
 #include "..\include\arb.h"
 #include "..\include\config.h"  
 #include "..\include\fpga.h"
 
 #include "..\include\systick.h"
 #include "..\include\event.h"   
 #include "..\include\frame.h"
 #include "..\usb_include\usb_command.h"
     
 #include <string.h>
 #include <math.h>
 
//----------------- Define -------------------------------//

//----------------- Function Prototype -------------------//
 //menu
 static int burst_main(void);
 static int state(void);
 static int number(void);
 static int cycle(void);
 
 static int burst_figure(int);
 
 //hardware operation
 
 static int set_cycle(double cycle);
 static int set_number(int number);
 static int set_state(int);
 
//----------------- Variable -----------------------------//
 BURST_T burst = {
	 .main = burst_main
 };
 
 char const *  button_burst[/* language */ 2][5] = {
		{
			"猝发状态",
			"波形个数",
			"猝发周期",
				NULL,
				NULL
		}, {
			"Burst state",
			"  Number  ",
			"   Cycle  ",
			NULL,
			NULL
		}
	};
//----------------- Function -----------------------------//

/*
 * Name						: burst_main
 * Description		: ---
 * Author					: XiaomaGee.
 *
 * History
 * -----------------------
 * Rev						: 0.00
 * Date						: 00/00/2012
 * 
 * create.
 * ----------------------
 */
 static int
 burst_main(void)
 {
	 	int(*fun_burst[3]) (void) = { 
			state,
			number,
			cycle
		};
		BOX_T b;
		
		int i;
		
	b.startx = 7;
	b.starty = 60;
	b.endx = 395;
	b.endy = 176;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK;
	gui.box(&b);
	 
	event = KEY_F1;

	
		while (1) {
		for (i = 0; i < 3; i++) {
			if (event == f_event_queue[i]) {
				event = EVENT_CLEAR;
				if (fun_burst[i] != NULL) {
					button.main = &button_burst[sys.language];
					button.active = i;
					button.drawb(button.main, button.active);

					fun_burst[i]();
				}else {
					event = EVENT_CLEAR;
				}
			}
		}
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) {
				set_state(OFF);
				ag.burst_state = 0;
				return 0;
			}
				
	}
}
/*
 * Name						: state
 * Description		: ---
 * Author					: XiaomaGee.
 *
 * History
 * -----------------------
 * Rev						: 0.00
 * Date						: 00/00/2012
 * 
 * create.
 * ----------------------
 */
static int
state(void)
{
	int flag = 1;
	STRING_T s;
	
	event = EVENT_CLEAR;
	frame.set_window(0);
	
		while (1) {
			usb_command.capture_handle();
		if (
			event == KEY_F2 ||
			event == KEY_F3 
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;
	
		  if(
				event == KEY_LEFT  ||
				event == KEY_RIGHT ||
				event == KEY_UP    ||
				event == KEY_DOWN
			){
				event = 0;
				ag.burst_state = !ag.burst_state;
				
				flag = 1;
			}
			
			if(flag){
				flag = 0;
				burst_figure(0);
				
				font._default.single_byte = &fixedsys;
				font._default.double_byte = &simsun16;
				
				s.x = 10;
				s.y = 205;
				s.space.line = 0;
				s.space.word = 0;
				s.inverse = NULL;
				s.background_color = ag.burst_state?COLOR_WINDOW_BACKGROUND:sys.color;
				s.color = COLOR_BLACK;
				font.printf(&s,"%s",sys.language==LANGUAGE_EN?" OFF ":" 关闭 ");	
				
				s.background_color = COLOR_WINDOW_BACKGROUND;
				s.color = COLOR_BLACK;
				font.printf(&s,"  ");
				
				s.background_color = ag.burst_state == 0 ? COLOR_WINDOW_BACKGROUND : sys.color;
				s.color = COLOR_BLACK;
				font.printf(&s,"%s",sys.language==LANGUAGE_EN?" ON ":" 开启 ");	
				
				set_number(ag.burst_number);
				set_cycle(ag.burst_cycle);
				set_state(ag.burst_state);
				
			}
		}
		
		return 0;
}
/*
 * Name						: number
 * Description		: ---
 * Author					: XiaomaGee.
 *
 * History
 * -----------------------
 * Rev						: 0.00
 * Date						: 00/00/2012
 * 
 * create.
 * ----------------------
 */
static int
number(void)
{
	int flag = 1;
	STRING_T s;
	int position = 4;
	INVERSE_T pin;
	
	const int weight[]={
		10000,1000,100,10,1
	};
	
	event = EVENT_CLEAR;
	frame.set_window(1);
	
		while (1) {
			usb_command.capture_handle();
		if (
			event == KEY_F1 ||
			event == KEY_F3 
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;

			if(event == KEY_LEFT){
					event = 0;
					position --;
					if(position < 0)position = 0;
					flag = 1;
			}
			if(event == KEY_RIGHT){
					event = 0;
					position ++;
					if(position > 4)position = 4;
					flag = 1;
			}	
		if(event == KEY_UP){
					event = 0;         
					ag.burst_number += weight[position];
					if(ag.burst_number > 65535)ag.burst_number = 65535;
					flag = 1;
			}			
		if(event == KEY_DOWN){
					event = 0;         
					ag.burst_number -= weight[position];
					if(ag.burst_number < 0)ag.burst_number = 0;
					flag = 1;
			}			
						
			if(flag){
				flag = 0;   
				burst_figure(0);
				
				font._default.single_byte = &tahoma26;
				
				pin.start = position;
				pin.end = position;
				pin.color = COLOR_WINDOW_BACKGROUND;
				pin.background_color = sys.color;
				pin.next = NULL;

				s.x = 10;
	s.y = 190;
	s.space.line = 0;
	s.space.word = 0;
	s.color = COLOR_WINDOW_BACKGROUND;
	s.background_color = COLOR_BLACK;
	s.inverse = &pin;
  
		font.printf(&s, "%05d", ag.burst_number);
	
		set_number(ag.burst_number);
			}
	if (systick.flash_trig) {
		  if(systick.flash_trig ==1)burst_figure(0);
			else burst_figure(1);
		
			systick.flash_trig = 0;
		}
		}
		return 0;
}
/*
 * Name						: cycle
 * Description		: ---
 * Author					: XiaomaGee.
 *
 * History
 * -----------------------
 * Rev						: 0.00
 * Date						: 00/00/2012
 * 
 * create.
 * ----------------------
 */
static int
cycle(void)
{
int flag = 1;
	STRING_T s;
	int position = 4;
	INVERSE_T pin;
	int unit;
	const double weight[]={
		100000000,10000000,1000000,100000,10000,1000,100,10,1
	};
	const int pos_weight[3][9]={
		{0,1,2,4,5,6,7,8,9},
		{0,1,2,3,4,5,7,8,9},
		{0,1,2,3,4,5,6,7,8}
	};
	
	event = EVENT_CLEAR;
	frame.set_window(1);
	
		while (1) {
			usb_command.capture_handle();
		if (
			event == KEY_F1 ||
			event == KEY_F2 
			) break;
		if (
			event == KEY_M1 ||
			event == KEY_M2 ||
			event == KEY_M3 ||
			event == KEY_M4 ||
			event == KEY_M5 ||
			event == KEY_ESC
			) break;

			if(event == KEY_LEFT){
					event = 0;
					position --;
					if(position < 0)position = 0;
					flag = 1;
			}
			if(event == KEY_RIGHT){
					event = 0;
					position ++;
					if(position > 8)position = 8;
					flag = 1;
			}	
		if(event == KEY_UP){
					event = 0;         
					ag.burst_cycle += weight[position];
					if(ag.burst_cycle > 100000000.)ag.burst_cycle = 100000000.;
					flag = 1;
			}			
		if(event == KEY_DOWN){
					event = 0;         
					ag.burst_cycle -= weight[position];
					if(ag.burst_cycle < 1)ag.burst_cycle = 1;
					flag = 1;
			}			
						
			if(flag){
				flag = 0;
			
				if(ag.burst_cycle < 1000)unit = 2;     //  us
					else if(ag.burst_cycle < 1000000)unit = 1;   //ms
					else unit = 0; //s
				
				font._default.single_byte = &tahoma26;
				
				pin.start = pos_weight[unit][position];
				pin.end = pos_weight[unit][position];
				pin.color = COLOR_WINDOW_BACKGROUND;
				pin.background_color = sys.color;
				pin.next = NULL;

				s.x = 10;
	s.y = 190;
	s.space.line = 0;
	s.space.word = 0;
	s.color = COLOR_WINDOW_BACKGROUND;
	s.background_color = COLOR_BLACK;
	s.inverse = &pin;

	if(unit ==0)font.printf(&s,"%010.6f s  ",ag.burst_cycle / 1000000.);
	else if(unit == 1)font.printf(&s,"%010.3f ms  ",ag.burst_cycle / 1000.);
	else font.printf(&s,"%09.0f us  ",ag.burst_cycle);
 	
	set_cycle(ag.burst_cycle);
	
		}
	if (systick.flash_trig) {
		  if(systick.flash_trig ==1)burst_figure(0);
			else burst_figure(2);
		
			systick.flash_trig = 0;
		}
		}	
		return 0;
}
/*
 * Name						: burst_figure
 * Description		: ---
 * Author					: XiaomaGee.
 *
 * History
 * -----------------------
 * Rev						: 0.00
 * Date						: 00/00/2012
 * 
 * create.
 * ----------------------
 */
 static int
 burst_figure(int par)
 {

	STRING_T s;
	COLOR_T color;
	COLOR_T color_cycle;
	COLOR_T color_number;
  float temp;
  int i;
	 
	
	if(ag.burst_state)color = COLOR_LIME;
		else color =  make_rgb565(44, 71, 0);
	if(ag.burst_state){
		if(par == 0){
			
			color_cycle =  make_rgb565(44, 71, 0);
			color_number = make_rgb565(44, 71, 0);
		}else if(par == 1){
			color_number = COLOR_LIME;
			color_cycle = make_rgb565(44, 71, 0);
		} else {
			color_cycle = COLOR_LIME;
			color_number = make_rgb565(44, 71, 0);
		}
		} else	color_number = color_cycle =  make_rgb565(44, 71, 0);

	 gui.line(9,118,30,118,color);
	
	 gui.set_cursor(30,118);
	 
	 for(i = 0; i< 41;i++){
		 temp = i;
		 temp *= 2;
		 temp *= PI;
		 temp /= 40;
		 
		 temp = sin(temp);
 		 
		 temp *= -35.;
		 
		 gui.line_to(i + 30,temp + 118,color);
	 }
		for(i = 0; i< 20; i+=3){
			gui.dot(70 + i,118,color);
	  }
	
		gui.set_cursor(90,118);
	 
	 for(i = 0; i< 41;i++){
		 temp = i;
		 temp *= 2;
		 temp *= PI;
		 temp /= 40;
		 
		 temp = sin(temp);
 		 
		 temp *= -35.;
		 
		 gui.line_to(i + 90,temp + 118,color);
	 }
	 
	 gui.line(131,118,269,118,color);
	 
	 	 gui.set_cursor(270,118);
	 
	 for(i = 0; i< 41;i++){
		 temp = i;
		 temp *= 2;
		 temp *= PI;
		 temp /= 40;
		 
		 temp = sin(temp);
 		 
		 temp *= -35.;
		 
		 gui.line_to(i + 270,temp + 118,color);
	 }
		for(i = 310; i< 330; i+=3){
			gui.dot(i,118,color);
	  }
	
		gui.set_cursor(330,118);
	 
	 for(i = 0; i< 41;i++){
		 temp = i;
		 temp *= 2;
		 temp *= PI;
		 temp /= 40;
		 
		 temp = sin(temp);
 		 
		 temp *= -35.;
		 
		 gui.line_to(i + 330,temp + 118,color);
	 }
	 gui.line(371,118,393,118,color);
	 
	 //show number
	 gui.line(30 ,88,30,64,color_number);
	 gui.line(130,108,130,64,color_number);
	 
	 gui.line(9,71,155,71,color_number);
	 
	 gui.arrow(30,71,1,color_number);
	 gui.arrow(130,71,3,color_number);
	 
	  //show cycle
	 gui.line(30 ,128,30,172,color_cycle);
	 gui.line(270,128,270,172,color_cycle);
	 
	 gui.line(30,165,65,165,color_cycle);
	 
	 gui.line(235,165,270,165,color_cycle);
	 
	 gui.arrow(30,165,3,color_cycle);
	 gui.arrow(270,165,1,color_cycle);
	 
	 font._default.single_byte = &fixedsys;
	 font._default.double_byte = &simsun12;
	 s.x = 160;
	 s.y = 64;
	 s.color = color_number;
	 s.background_color = COLOR_BLACK; 
	 s.space.line = 0;
	 s.space.word = 0;
	 s.inverse = NULL;
	 
	 font.printf(&s,"%s:%d        ",sys.language == LANGUAGE_CN?"波形个数":"Number",ag.burst_number);
	 
	 s.x = 65;
	 s.y = 158;
	 s.color = color_cycle;
	 s.background_color = COLOR_BLACK; 
	 s.space.line = 0;
	 s.space.word = 0;
	 s.inverse = NULL;
	 
	 if(ag.burst_cycle < 1000)font.printf(&s," %s:%.0f us",sys.language == LANGUAGE_CN?"猝发周期":"Cycle",ag.burst_cycle);
		else if(ag.burst_cycle < 1000000)font.printf(&s," %s:%.3f ms",sys.language == LANGUAGE_CN?"猝发周期":"Cycle",ag.burst_cycle / 1000.);
			else font.printf(&s," %s:%.6f s",sys.language == LANGUAGE_CN?"猝发周期":"Cycle",ag.burst_cycle / 1000000.);
		
	 while(s.x < 232 )font.printf(&s," ");
	 
	 return 0;
 }
 /*
 * Name						: set_cycle
 * Description		: ---
 * Author					: XiaomaGee.
 *
 * History
 * -----------------------
 * Rev						: 0.00
 * Date						: 00/00/2012
 * 
 * create.
 * ----------------------
 */
 static int
 set_cycle(double cycle)
 {

	double temp = 4294967296. / 100000000.;    // 2^32/100M
	unsigned  long int fword;

	//if (cycle > 100. || cycle < .000001 ) return -1; //1us ~ 100s
  
	cycle /= 1000000.;
	 
	temp /= cycle;
	
	fword = temp;

 
	fpga_ctl.b.ctl1 = 1;
	fpga_ctl.b.ctl2 = 0;
	fpga_ctl.b.ctl3 = 1;
	fpga_ctl.b.ctl4 = 0;
	fpga.ctl();

	FPGA_WR2 = (fword >> 16) & 0xffff;

	fpga_ctl.b.ctl1 = 0;
	fpga_ctl.b.ctl2 = 1;
	fpga_ctl.b.ctl3 = 1;
	fpga_ctl.b.ctl4 = 0;
	fpga.ctl();

	FPGA_WR2 = fword & 0xffff;	 
	
	 return 0;
 }
  /*
 * Name						: set_state
 * Description		: ---
 * Author					: XiaomaGee.
 *
 * History
 * -----------------------
 * Rev						: 0.00
 * Date						: 00/00/2012
 * 
 * create.
 * ----------------------
 */
 static int
 set_state(int state)
 {
	fpga_ctl.b.ctl7 = state;
	fpga.ctl();
	 
	return 0;
	 
 }
 /*
 * Name						: set_number
 * Description		: ---
 * Author					: XiaomaGee.
 *
 * History
 * -----------------------
 * Rev						: 0.00
 * Date						: 00/00/2012
 * 
 * create.
 * ----------------------
 */
 static int
 set_number(int num)
 {
	fpga_ctl.b.ctl1 = 1;
	fpga_ctl.b.ctl2 = 1;
	fpga_ctl.b.ctl3 = 1;
	fpga_ctl.b.ctl4 = 0;
	fpga.ctl();

	FPGA_WR2 = num;
	 
	fpga_ctl.b.ctl1 = 1;
	fpga_ctl.b.ctl2 = 1;
	fpga_ctl.b.ctl3 = 0;
	fpga_ctl.b.ctl4 = 0;
	fpga.ctl();

	FPGA_WR2 = 0;
	 
	return 0;
 }

 