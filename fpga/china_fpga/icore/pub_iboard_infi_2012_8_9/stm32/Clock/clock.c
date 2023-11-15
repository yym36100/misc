/*------------------------------------------------------
   FILE NAME   : clock.c
   DESCRIPTION :
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
   ------------------------------------------------------*/

//-----------------Include files-------------------------//
#include "..\include\nvic.h"
#include "..\include\rcc.h"
#include "..\include\dac.h"
#include "..\include\usart.h"
#include "..\include\adc.h"
#include "..\include\hardware.h"
#include "..\include\systick.h"
#include "..\include\evtft.h"
#include "..\include\pwm.h"
#include "..\include\fpga.h"
#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\spi.h"
#include "..\include\flash.h"
#include "..\usb_include\usb.h"
#include "..\usb_include\usb_command.h"
#include "..\include\event.h"
#include "..\include\arb.h"
#include "..\include\main.h"
#include "..\include\dso.h"
#include "..\include\meter.h"
#include "..\include\clock.h"
 
#include <string.h>
#include <stdlib.h>
#include <math.h>

//-----------------Variable------------------------------//
CALENDAR_T calendar;

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
   ------------------------------------------------------*/
static int set_time(void)
{

	if(calendar.year < 2000)calendar.year = 2000;
	if(calendar.month < 1 || calendar.month > 12)calendar.month = 1;
	if(calendar.day < 1  || calendar.day > 31)calendar.day = 1;
	if(calendar.hour < 0 || calendar.hour > 23)calendar.hour = 0;
	if(calendar.minute < 0 || calendar.minute > 59)calendar.minute = 0;
	if(calendar.second <0 || calendar.second > 59)calendar.second = 0;
	
	usart1.printf("RTC %d,%d,%d,%d,%d,%d\n", calendar.year-2000, calendar.month, calendar.day, calendar.hour, calendar.minute,calendar.second);
	
	return 0;
}
/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ------------------------------------------------------*/
int clock_main(void)
{
	STRING_T s;
	int m = 0;
	int i, j;
	RECT_T r;
	int set_flag = 0;
	int set_date_flag = 0;
	int position = 0;
	const int flash_position[2][6] = {
	{
		2,3,5,6,8,9
	},{
		0,1,3,4,0,0
	}
 };

	INVERSE_T pin;

	lcd.cls(0);
	event = 0;

	while (1) {
		systick.flash_trig = 0;
		
		while(systick.flash_trig == 0) ;
		m = calendar.second;
		
		font._default.single_byte = &nix96;

		s.x = 7;
		s.y = 150;
		s.background_color = COLOR_BLACK;
 		s.color = COLOR_BLUE;
		s.space.line = 0;
		s.space.word = 0;

		pin.start = flash_position[set_date_flag][position];
		pin.end = flash_position[set_date_flag][position];
		pin.color = make_rgb565(0,0,50);
		pin.background_color  = COLOR_BLACK;
		pin.next = NULL;
       
		if(systick.flash_trig ==2 && set_date_flag == 1 && set_flag)s.inverse = & pin;
			else s.inverse = NULL;

		if (m % 2) font.printf(&s, "%02d %02d", calendar.hour, calendar.minute);
			else font.printf(&s, "%02d:%02d", calendar.hour, calendar.minute);
 
		font._default.single_byte = &nix48;
		s.x = 7;
		s.y = 10;
		s.background_color = COLOR_BLACK;

		s.color = COLOR_BLUE;
		s.space.line = 0;
		s.space.word = 0;
	
		pin.start = flash_position[set_date_flag][position];
		pin.end = flash_position[set_date_flag][position];
		pin.color = make_rgb565(0,0,50);
		pin.background_color  = COLOR_BLACK;
		pin.next = NULL;
       
		if(systick.flash_trig ==2 && set_date_flag == 0 && set_flag)s.inverse = & pin;
			else s.inverse = NULL;

		font.printf(&s, "%04d-%02d-%02d", calendar.year, calendar.month, calendar.day);

		usb_command.capture_handle();
		if(event == KEY_LEFT && set_flag){
			event = 0;
			
			position --;
			if(position < 0 && set_date_flag == 1){
					position = 5;
					set_date_flag = 0;
			}
			if(position < 0 && set_date_flag == 0){
				 position = 0;
			}
  	}
		if(event == KEY_RIGHT && set_flag ){
			event = 0;
			position ++;
			if(position > 5 && set_date_flag == 0){
				position = 0;
				set_date_flag = 1;
			}	
			if(position > 3 && set_date_flag == 1){
				position = 3;
			}					
		}

		if(event == KEY_UP && set_flag ){
			event = 0;
			if(set_date_flag == 0){
				 switch(position){
					  case 0:
							calendar.year += 10;
						break;
						case 1:
							calendar.year += 1;
						break;
						case 2:
							calendar.month += 10;
						break;
						case 3:
							calendar.month += 1;
						break;
						case 4:
							calendar.day += 10;
						break;
						case 5:
							calendar.day += 1;
						break;
							
				 }
			}else {
				 switch(position){
					 case 0:
						 calendar.hour += 10;
					 break;
					 case 1:
						 calendar.hour += 1;
					 break;
					 case 2:
						 calendar.minute += 10;
					 break;
					 case 3:
						 calendar.minute += 1;
					 break;
				 }
			 }
		//overflow
			 if(calendar.year > 2099 )calendar.year = 2099;
			 if(calendar.month > 12)calendar.month = 12;
			 
			 if(calendar.month == 2 && !(calendar.year%4) && calendar.day > 29) calendar.day = 29;
				else if(calendar.month == 2 && (calendar.year % 4) && calendar.day > 28)calendar.day = 28;
				else if(
						(
						calendar.month == 1 ||
						calendar.month == 3 ||
						calendar.month == 5 ||
						calendar.month == 7 ||
						calendar.month == 8 ||
						calendar.month == 10 ||
						calendar.month == 12
					) && calendar.day > 31
				)calendar.day = 31;
				else if(calendar.day > 30)calendar.day = 30;
				
				if(calendar.hour > 23)calendar.hour = 23;
				if(calendar.minute > 59)calendar.minute = 59;
			
				set_time();
				}
	
			if(event == KEY_DOWN && set_flag){
			event = 0;
			if(set_date_flag == 0){
				 switch(position){
					  case 0:
							calendar.year -= 10;
						break;
						case 1:
							calendar.year -= 1;
						break;
						case 2:
							calendar.month -= 10;
						break;
						case 3:
							calendar.month -= 1;
						break;
						case 4:
							calendar.day -= 10;
						break;
						case 5:
							calendar.day -= 1;
						break;
  			 }
			}else {
				 switch(position){
					 case 0:
						 calendar.hour -= 10;
					 break;
					 case 1:
						 calendar.hour -= 1;
					 break;
					 case 2:
						 calendar.minute -= 10;
					 break;
					 case 3:
						 calendar.minute -= 1;
					 break;
				 }
			 }
		//overflow
	
			 if(calendar.year < 2000 )calendar.year = 2000;
			 if(calendar.month < 1)calendar.month = 1;
			 if(calendar.day < 1)calendar.day = 1;
			 if(calendar.hour < 0)calendar.hour = 0;
			 if(calendar.minute < 0)calendar.minute = 0;
				
			 set_time();	 
		}
		if(set_flag == 0 && (event == KEY_RIGHT || event == KEY_LEFT || event == KEY_UP || event == KEY_DOWN)){
		  event = 0;
			}
		if(event == KEY_ENTER){
			event = 0;
			set_flag = !set_flag;
		}
		
		if (event == KEY_ESC) {
			event = 0;
			return 0;
		}  
		//display second
	
		r.x = 1;
		r.y = 98;
		r.width = 476;
		r.height = 20;
		r.color = COLOR_BLUE;
		r.fill_flag = 0;
		gui.rect(&r);
		
		for(i = 0; i < m; i++){
		r.x = i*8 + 5;
		r.y = 101;
		r.width = 5;
		r.height = 15;
		r.color = COLOR_BLUE;
		r.fill_flag = 1;
		gui.rect(&r);
		}
		for(i = m; i < 59; i++){
		r.x = i*8 + 5;
		r.y = 101;
		r.width = 5;
		r.height = 15;
		r.color = COLOR_BLACK;
		r.fill_flag = 1;
		gui.rect(&r);
		}
	 //first run
		
		if (first_run == 1) {
			for (j = 0; j < 100000; j++) ;
			for (i = 0; i <= 100; i++) {
				pwm.initialize(i);
				for (j = 0; j < 20000; j++) ;
				first_run = 0;
			}
		}
	}
}
