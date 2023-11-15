/*------------------------------------------------------
   FILE NAME   : main.c
   DESCRIPTION : main function
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------/

#include "..\include\stc11fxx.h"
#include <stdio.h>
#include <stdlib.h>   
#include <string.h>

#include "..\include\key.h"
#include "..\include\ds1302.h"
#include "..\include\lm75.h"

//---------------- Function Prototype -------------------/
//---------------- Variable -----------------------------/
#define CRYSTAL         11059200.0
#define BAUDRATE        19200.

sbit LED = P3 ^ 5;

sbit SEL0 = P1 ^ 1;
sbit SEL1 = P1 ^ 2;
sbit SEL2 = P1 ^ 3;
sbit SEL3 = P1 ^ 4;

sbit BEEP = P3 ^ 4;


unsigned char idata nix_value[4];


unsigned char code nix_tab[] = {
	0xc0, 0xf9, 0xa4, 0xb0,
	0x99, 0x92, 0x82, 0xf8,
	0x80, 0x90, 0x88, 0x83,
	0xc6, 0xa1, 0x86, 0x8e, //0~f
	0xff, 0xbf                                       // ,-,
};

unsigned char idata receive_buffer[20];
unsigned char receive_ok = 0;


//---------------- Function -----------------------------//

/*-------------------------------------------------------
   NAME       : display
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

void display(float a)
{
	unsigned char idata buf[10];
	bit flag = 0;


	if (a < 0) {
		flag = 1;
		a = 0 - a;
		nix_value[0] = 17;
	}else nix_value[0] = 16;

	if (a < 10) {
		sprintf(buf, "%.2f", a);
		nix_value[0] += 100;
		nix_value[1] = buf[0] - '0';
		nix_value[2] = buf[2] - '0';
		nix_value[3] = buf[3] - '0';
	}else if (a < 100) {
		sprintf(buf, "%.1f", a);
		nix_value[1] = buf[0] - '0';
		nix_value[2] = buf[1] - '0' + 100;
		nix_value[3] = buf[3] - '0';
	}else if (a < 1000) {
		sprintf(buf, "%.0f", a);
		nix_value[1] = buf[0] - '0';
		nix_value[2] = buf[1] - '0';
		nix_value[3] = buf[2] - '0';
	} else {
		nix_value[0] = 0xe;
		nix_value[1] = 16;
		nix_value[2] = 16;
		nix_value[3] = 16;

		return;
	}
}
/*-------------------------------------------------------
   NAME       : receive_char
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/


void receive_char(void) interrupt 4
{
	static unsigned char idata count = 0;

	RI = 0;
	receive_buffer[count++] = SBUF;

	if (receive_buffer[count - 1] == 0x0a) {
		receive_ok = 1;
		receive_buffer[count] = '\0';
		count = 0;
	}
}
/*-------------------------------------------------------
   NAME       : init_uart
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

void init_uart(void)
{
	float temp;
	unsigned char bps;

	TMOD |= 0X20;
	PCON |= 0x80;
	SCON = 0X50;

	temp = CRYSTAL;
	temp /= BAUDRATE;
	temp /= 32.;

	temp /= 12.;

	temp *= 2.;

	temp = 256. - temp;
	bps = (unsigned char)temp;

	TH1 = bps;
	TL1 = bps;

	TR1 = 1;
	ES = 1;
	EA = 1;
	PS = 1; //uart 优先级最高
}
/*-------------------------------------------------------
   NAME       : send_string
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

char send_string(char *ss)
{
	unsigned char i = 0;


	ES = 0;
	while (ss[i] != '\0') {
		SBUF = ss[i];
		while (!TI) ;
		TI = 0;
		i++;
	}
	ES = 1;


	return 1;
}


/*-------------------------------------------------------
   NAME       : init_timer0
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

void init_timer0(void)
{
	TMOD &= 0xf0;
	TMOD |= 0X01; //M0=1,M1=0;

	TH0 = 0Xef;
	TL0 = 0X0;

	ET0 = 1; //enable t0 interrupt;
	EA = 1;    //enable system interrupt
	TR0 = 1; //start t0
}

/*-------------------------------------------------------
   NAME       : timer0
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/


void timer0(void) interrupt 1
{
	static unsigned char i = 0;
	static unsigned char key_code_bak = 0;
	unsigned char key_code;


	TH0 = 0Xef;
	TL0 = 0X0;

	EA = 0;

	if (i == 0) SEL3 = 0;
	else SEL3 = 1;

	if (i == 1) SEL2 = 0;
	else SEL2 = 1;

	if (i == 2) SEL1 = 0;
	else SEL1 = 1;

	if (i == 3) SEL0 = 0;
	else SEL0 = 1;


	P0 = nix_value[i] > 99 ? nix_tab[nix_value[i] - 100] & 0x7f : nix_tab[nix_value[i]];
	i++;
	if (i > 3) i = 0;


	key_code = read_key();

	if (key_code == key_code_bak || key_code == 0) {
		goto end;
	}
	event = key_code;
 end: key_code_bak = key_code;
	EA = 1;
}
/*-------------------------------------------------------
   NAME       : main
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

int main(void)
{
	long int i = 0, j;
	idata char buffer[30];
	unsigned char bak = 0;
	char *p;


	init_timer0();


	AUXR1 |= 0X80; //remap uart

	init_uart();

	display(1.23);
	init_ds1302();
	

	for (i = 0; i < 50; i++) {
		BEEP = 0;
		for (j = 0; j < 110; j++) ;
		BEEP = 1;
		for (j = 0; j < 110; j++) ;
	}
	for (i = 0; i < 250; i++) {
		BEEP = 0;
		for (j = 0; j < 40; j++) ;
		BEEP = 1;
		for (j = 0; j < 40; j++) ;
	}

	
	while (1) {
		if (i++ == 10000) LED = 1;

		if (event) {
			sprintf(buffer, "event %bu\n", event);
			send_string(buffer);
			display(event);
			event = 0;
		}

		if (i % 1000 == 0) {
			get_ds1302();
			if (bak != rtc.second) {
				sprintf(buffer, "RTC 20%02bu,%bu,%bu,%bu,%bu,%bu,%f\n", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second, lm75_read());
				send_string(buffer);
			}
			bak = rtc.second;
		}

		if (i > 20000) {
			LED = 0;
			i = 0;

		}

		if(receive_ok){
	   receive_ok=0;
		 if(
		 receive_buffer[0] == 'R' &&  
		 receive_buffer[1] == 'T' && 
		 receive_buffer[2] == 'C' 
			){
			p = receive_buffer;
			p = strchr(p,' ');
			p ++ ;
			rtc.year = atoi(p);
			
			p = strchr(p,',');
			p ++;
			rtc.month = atoi(p);
			
			p = strchr(p,',');
			p ++;
			rtc.day = atoi(p);
			
			p = strchr(p,',');
			p ++;
			rtc.hour = atoi(p);
			
			p = strchr(p,',');
			p ++;
			rtc.minute = atoi(p);
			
			p = strchr(p,',');
			p ++;
			rtc.second = atoi(p);
		
			set_ds1302((unsigned char*)&rtc);
			}
	   }

	}


	return 0;
}