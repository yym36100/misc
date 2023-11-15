/*************************************************************************
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
**************************************************************************
* Description:                                                           *
* The following is a simple hello world program running MicroC/OS-II.The * 
* purpose of the design is to be a very simple application that just     *
* demonstrates MicroC/OS-II running on NIOS II.The design doesn't account*
* for issues such as checking system call return codes. etc.             *
*                                                                        *
* Requirements:                                                          *
*   -Supported Example Hardware Platforms                                *
*     Standard                                                           *
*     Full Featured                                                      *
*     Low Cost                                                           *
*   -Supported Development Boards                                        *
*     Nios II Development Board, Stratix II Edition                      *
*     Nios Development Board, Stratix Professional Edition               *
*     Nios Development Board, Stratix Edition                            *
*     Nios Development Board, Cyclone Edition                            *
*   -System Library Settings                                             *
*     RTOS Type - MicroC/OS-II                                           *
*     Periodic System Timer                                              *
*   -Know Issues                                                         *
*     If this design is run on the ISS, terminal output will take several*
*     minutes per iteration.                                             *
**************************************************************************/


#include <stdio.h>
#include "includes.h"

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "./src/lcd/LCD.h"
#include "./src/hardware/hardware.h"
#include "./src/hardware/key_ctl.h"
//#include "./src/SD_card/src/SD_Test.h"
#include "./src/USB/Main.h"
#include "./src/Ethernet/Main.h"

//#define SHOW_MORE_PICTURE

#include "picture_3.h"

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       32*1024
OS_STK    ETH_stk[TASK_STACKSIZE];
OS_STK    USB_stk[TASK_STACKSIZE];
OS_STK    SD_stk [TASK_STACKSIZE];
OS_STK    HARD_stk[TASK_STACKSIZE];
OS_STK    KEY_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */

#define ETH_PRIORITY      7
#define USB_PRIORITY      8
#define HARD_PRIORITY     5
#define SD_PRIORITY       9
#define KEY_PRIORITY      6

/* The main function creates two task and starts multi-tasking */
extern void  LcmInit(void);   //LCD ≥ı ºªØ
extern int i2c_main(void);
extern void Digital_tube_main(void);
extern void sd_main(void);
void  Dis_pic(alt_u8 *p);



int main(void)
{
  UINT8 i;
  printf ("\r------------------------------------------------\r\n");  
  printf ("\rThis is RedCore RCQ208_V3 selftest Example\r\n");  
  printf ("\r------------------------------------------------\r\n");  
  printf ("\rPower on program start... \r\n"); 
  
  Digital_tube_main();  
  printf ("\rdigital tube test end\r\n");
  
  LcmInit();
  delay_ms(10); 

  printf ("\rLCM initial end\r\n");
 
  Dis_pic(gImage_picture_3);
  printf ("\rshow pic 3 \r\n");
    
  delay_ms(1500);	
   
  TFT_Clear_Region(0, 0, 320, 240, 0);
		
  i2c_main();
  printf ("\rI2c test end \r\n");

 // USB_Test();
 
   printf ("\rStart create ucos mulit task  \r\n");
  
	OSTaskCreateExt(WebServer_main,
                  NULL,
                  (void *)&ETH_stk[TASK_STACKSIZE-1],
                  ETH_PRIORITY,
                  ETH_PRIORITY,
                  ETH_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

	OSTaskCreateExt(USB_Test,
                  NULL,
                  (void *)&USB_stk[TASK_STACKSIZE-1],
                  USB_PRIORITY,
                  USB_PRIORITY,
                  USB_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
	OSTaskCreateExt(sd_main,
                  NULL,
                  (void *)&SD_stk[TASK_STACKSIZE-1],
                  SD_PRIORITY,
                  SD_PRIORITY,
                  SD_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
                  
	OSTaskCreateExt(hardware_test,
                  NULL,
                  (void *)&HARD_stk[TASK_STACKSIZE-1],
                  HARD_PRIORITY,
                  HARD_PRIORITY,
                  HARD_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
                  
                  
	OSTaskCreateExt(key_ctl_test,
                  NULL,
                  (void *)&KEY_stk[TASK_STACKSIZE-1],
                  KEY_PRIORITY,
                  KEY_PRIORITY,
                  KEY_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  printf ("\rOs running  \r\n");                  
  OSStart();
  return 0;
}


/*----------------------------------------------------------------------------
  Show picture function.
 *----------------------------------------------------------------------------*/

 void Address_Set(void);

void  Dis_pic(alt_u8 *p)
{
    alt_u32 i;   
    alt_u16 width;
    alt_u16 high;
	alt_u8 data_1;
	alt_u8 data_2;

    width = 320;
    high =  240;    

	Address_Window_Set(0,0,240,320);
	Address_Window_Start(0,0);
		
    p += 8;

    //printf("width*high = %d\r\n",width*high);

    SET_LCD_RS;     //data control
    CLR_LCD_CS;     //chip on     
    SET_LCD_RD;     //write mode  

    for(i=0; i<width*high; i++)
    {
    	data_1 = *(p++);    	
		data_2 = *(p++);
		
        SET_DATA((data_2 << 8) | data_1);    
        CLR_LCD_WR; 
        SET_LCD_WR;	
    }
    SET_LCD_CS; 
}

 void Address_Set(void)
{
	Send_LcmCommand(0x0050);// Horizontal Address Start
	Send_LcmData(0x0000);        

	Send_LcmCommand(0x0051); //Horizontal Address end
	Send_LcmData(0x00EF);        

	Send_LcmCommand(0x0052);//Vertical Address Start Position
	Send_LcmData(0x0000);        

	Send_LcmCommand(0x0053); //Vertical Address end Position
	Send_LcmData(0x013F);     

	Send_LcmCommand(0x0022); //write data   
}
/*******************************************************************/

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/
