
#include "..\include\nvic.h"
#include "..\include\rcc.h"
#include "..\include\fsmc.h"
#include "..\include\hardware.h"
#include "..\include\fpga.h"
#include "..\include\usart.h"
#include "..\include\terminal.h"
#include "..\include\key.h"
#include "..\include\systick.h"
#include "..\include\adc.h"
#include "..\include\dac.h"

#include <string.h>
#include <stdlib.h>


void SystemInit(void) {}

int main(void) {
    unsigned int i, j;
    unsigned int dat;


    for (i = 0; i < 500000; i++);  //delay waiting fpga ready...

    rcc.initialize();
    nvic.initialize();

    LED_OUTPUT;
    LED_ON;

    fpga.initialize();
    usart1.initialize(115200);
    terminal.initialize();
    dac.initialize();
    adc.initialize();
    key.initialize();

    //check fsmc and fpga

    for (i = 0; i < 60000; i++) {
        fpga_write(7, i);

        dat = fpga_read(0);

        if ((dat + i) != 65535) {
            usart1.printf("FPGA/FSMC Error!");
            while (1) {
                for (j = 0; j < 100000; j++);
                LED_ON;
                for (j = 0; j < 100000; j++);
                LED_OFF;
            }
        }
    }

    usart1.printf("\r\nFPGA reading OK!\r\nFSMK OK!\r\n");
    usart1.printf("Please make sure ARM-LED / FPGA-LED Flashed!\r\n");

    systick.initialize();

    i = 0;

    while (1) {
        terminal.ci();

        if (i++ > 2000000) {

            i = 0;
           // if (adc.read(0) > 3200 || adc.read(0) < 3000) usart1.printf("Please connect PA4 - PA0 by a dupont Line.\r\n");
            //else
			usart1.printf("adc = %d\r\n",adc.read(0));
        }

        if (event) {
            if (event == KEYA) usart1.printf("Oh Yeah, KEYA is pressed\r\n");
            else if (event == KEYB) usart1.printf("Oh Yeah, KEYB is pressed\r\n");
            else if (event == KEYC) usart1.printf("Oh Yeah, KEYC is pressed\r\n");

            event = 0;
        }
    }
}
