/*------------------------------------------------------
FILE NAME   : led.h
DESCRIPTION : led driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-11-23
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __led_h__
#define __led_h__

//-----------------Include files-------------------------//
#include "..\include\hardware.h"

//----------------- define------------------------------//
#define	 LED_SDI_CONFIG_OUTPUT	  GPIOE->CRL.B.MODE4=0X3;\
								  GPIOE->CRL.B.CNF4=0;
#define	 LED_RCLK_CONFIG_OUTPUT	  GPIOE->CRL.B.MODE2=0X3;\
								  GPIOE->CRL.B.CNF2=0;
#define	 LED_SRCLK_CONFIG_OUTPUT  GPIOE->CRL.B.MODE3=0X3;\
								  GPIOE->CRL.B.CNF3=0;

#define	LED_SDI_ON	GPIOE->BSRR.B.SETIO4=1
#define LED_SDI_OFF	GPIOE->BSRR.B.CLRIO4=1

#define	LED_RCLK_ON	GPIOE->BSRR.B.SETIO2=1
#define LED_RCLK_OFF	GPIOE->BSRR.B.CLRIO2=1

#define	LED_SRCLK_ON	GPIOE->BSRR.B.SETIO3=1
#define LED_SRCLK_OFF	GPIOE->BSRR.B.CLRIO3=1


//-----------------LED DEFINE----------------------------//

#define	LED_W1			led.value.bits.bit4  //
#define	LED_W2			led.value.bits.bit5 //
#define	LED_W3			led.value.bits.bit6	 //
#define	LED_W4			led.value.bits.bit7	 //
#define	LED_W5			led.value.bits.bit3	   //
#define	LED_W6			led.value.bits.bit2	  //

#define	LED_M1 			led.value.bits.bit1   //
#define	LED_M2	 		led.value.bits.bit0	   //
#define	LED_M3	 		led.value.bits.bit15   //
#define	LED_SAVE	 	led.value.bits.bit12
#define	LED_TRIG	 	led.value.bits.bit15
#define	LED_M4			led.value.bits.bit4
#define	LED_M5			led.value.bits.bit9
#define	LED_M6			led.value.bits.bit10  //
#define	LED_RECALL	 	led.value.bits.bit13  //
#define	LED_OUTPUT	 	led.value.bits.bit8   //

#define	LED_M1_FLASH 			led.flash.bits.bit1
#define	LED_M2_FLASH	 		led.flash.bits.bit0
#define	LED_M3_FLASH	 		led.flash.bits.bit15
#define	LED_SAVE_FLASH	 		led.flash.bits.bit12
#define	LED_TRIG_FLASH	 		led.flash.bits.bit15
#define	LED_M4_FLASH			led.flash.bits.bit4
#define	LED_M5_FLASH			led.flash.bits.bit9
#define	LED_M6_FLASH			led.flash.bits.bit10
#define	LED_RECALL_FLASH	 	led.flash.bits.bit13
#define	LED_OUTPUT_FLASH	 	led.flash.bits.bit8

//-----------------Typedef ------------------------------//
typedef struct{
	union {
		struct{
			unsigned short int bit0:1;
			unsigned short int bit1:1;
			unsigned short int bit2:1;
			unsigned short int bit3:1;
			unsigned short int bit4:1;
			unsigned short int bit5:1;
			unsigned short int bit6:1;
			unsigned short int bit7:1;
			unsigned short int bit8:1;
			unsigned short int bit9:1;
			unsigned short int bit10:1;
			unsigned short int bit11:1;
			unsigned short int bit12:1;
			unsigned short int bit13:1;
			unsigned short int bit14:1;
			unsigned short int bit15:1;
		}bits;
		unsigned short int word;
	}value;
	union {
		struct{
			unsigned short int bit0:1;
			unsigned short int bit1:1;
			unsigned short int bit2:1;
			unsigned short int bit3:1;
			unsigned short int bit4:1;
			unsigned short int bit5:1;
			unsigned short int bit6:1;
			unsigned short int bit7:1;
			unsigned short int bit8:1;
			unsigned short int bit9:1;
			unsigned short int bit10:1;
			unsigned short int bit11:1;
			unsigned short int bit12:1;
			unsigned short int bit13:1;
			unsigned short int bit14:1;
			unsigned short int bit15:1;
		}bits;
		unsigned short int word;
	}flash;
	int (* initialize)(void);
	int (* set)(unsigned short int);
	int (* clear_wave)(void);
}LED_T;

//----------------- Extern ------------------------------//

extern LED_T led;

#endif //__led_h__
