#include <stdio.h>
#include "includes.h"

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "../lcd/LCD.h"
#include "./key_ctl.h"

char init_char[] = "DAC BUZZER LED2 LED3 LED4 LED5 LED6 LED7 ";
char ON_char[]   = "ON ";
char OFF_char[]  = "OFF";
char DAC_char[]  = "0.00V";

int  init = 0;

unsigned int key_focus_reg;
unsigned int led_data_reg;
unsigned int buzzer_reg;
unsigned int dac_data_reg;

void key_ctl_test (void) 
{

    unsigned int key_focus;
    unsigned int led_data;
    unsigned int buzzer;
    unsigned int dac_data;
    
    unsigned char DAC_D0, DAC_D1, DAC_D2;
    
    Lcd_Show_char_8x16(0, 20, init_char, (sizeof(init_char) - 1), 0xFFFF, 0x0000 , 1); 

    while(1)
    {    
        key_focus = READ_KEY_FOCUS;
        led_data  = READ_LED_DATA & 0x3F;
        buzzer    = READ_BUZZER_DATA;
		//printf("buzzer : %d\r\n",buzzer);
        dac_data  = READ_DAC_DATA;
        
        DAC_D0    = (dac_data*100*5 /255) /100 + 0x30;
        DAC_D1    = ((dac_data*100*5 /255) %100) /10 + 0x30;  
        DAC_D2    = ((dac_data*100*5 /255) %100) %10 + 0x30; 
        
        DAC_char[0] =  DAC_D0;
        DAC_char[2] =  DAC_D1;
        DAC_char[3] =  DAC_D2;
        
        Lcd_Show_char_8x16(0  , 4 , DAC_char, (sizeof(DAC_char) - 1), 0xFFFF, 0x0000,(key_focus == 0));
        
        if(buzzer)
          Lcd_Show_char_8x16(56  , 4 , ON_char,  (sizeof(ON_char) - 1), 0xF800, 0x0000,(key_focus == 1)); 
        else
          Lcd_Show_char_8x16(56  , 4 , OFF_char, (sizeof(OFF_char) - 1), 0xFFFF, 0x0000,(key_focus == 1));   
          
        if(led_data & 0x20)
          Lcd_Show_char_8x16(88  , 4 , OFF_char, (sizeof(OFF_char) - 1), 0xFFFF, 0x0000,(key_focus == 2)); 
        else
          Lcd_Show_char_8x16(88  , 4 , ON_char,  (sizeof(ON_char) - 1), 0xF800, 0x0000,(key_focus == 2)); 
    
            
        if(led_data & 0x10)
          Lcd_Show_char_8x16(128  , 4 , OFF_char, (sizeof(OFF_char) - 1), 0xFFFF, 0x0000,(key_focus == 3)); 
        else
          Lcd_Show_char_8x16(128  , 4 , ON_char,  (sizeof(ON_char) - 1), 0xF800, 0x0000,(key_focus == 3)); 
            
        if(led_data & 0x08)
          Lcd_Show_char_8x16(168  , 4 , OFF_char, (sizeof(OFF_char) - 1), 0xFFFF, 0x0000,(key_focus == 4));  
        else
          Lcd_Show_char_8x16(168  , 4 , ON_char,  (sizeof(ON_char) - 1), 0xF800, 0x0000,(key_focus == 4)); 
           
        if(led_data & 0x04)
          Lcd_Show_char_8x16(208  , 4 , OFF_char, (sizeof(OFF_char) - 1), 0xFFFF, 0x0000,(key_focus == 5)); 
        else
          Lcd_Show_char_8x16(208  , 4 , ON_char,  (sizeof(ON_char) - 1), 0xF800, 0x0000,(key_focus == 5)); 
            
        if(led_data & 0x02)
          Lcd_Show_char_8x16(248  , 4 , OFF_char, (sizeof(OFF_char) - 1), 0xFFFF, 0x0000,(key_focus == 6)); 
        else
          Lcd_Show_char_8x16(248  , 4 , ON_char,  (sizeof(ON_char) - 1), 0xF800, 0x0000,(key_focus == 6)); 
            
        if(led_data & 0x01)
          Lcd_Show_char_8x16(288  , 4 , OFF_char, (sizeof(OFF_char) - 1), 0xFFFF, 0x0000,(key_focus == 7));   
        else
          Lcd_Show_char_8x16(288  , 4 , ON_char,  (sizeof(ON_char) - 1), 0xF800, 0x0000,(key_focus == 7)); 
          
        OSTimeDlyHMSM(0, 0, 0, 100);
    }
                    

} 






