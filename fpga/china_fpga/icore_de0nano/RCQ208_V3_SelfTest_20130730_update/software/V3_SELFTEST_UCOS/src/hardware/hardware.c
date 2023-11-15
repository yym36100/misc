#include <stdio.h>
#include "includes.h"

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "../lcd/LCD.h"
#include "./hardware.h"

char logo_char[] = "RedCore EP2C8 V3 EVB Hardware Test!     ";
char logo2_char[]= "                                        ";
char Temp_char[] = "Temp : 00.0 'C";
char Time_char[] = "Time : 00:00:00";
char ADC_char[]  = "ADC  : 0.00V";
char IR_char[]   = "IR   IN : 0000";
char Uart_char[] = "UART IN : 0000";
char PS2_char[]  = "PS2  IN : 0000";
char SD_char[]   = "SD Card    :";
char USBH_char[] = "USB Host   :";
char USBS_char[] = "USB Device :";
char LAN_char[]  = "LAN        :";
char SD_info[28]   = "";
char USBH_info[28] = "";
char USBS_info[28] = "";
char LAN_info[28]  = "";
char EEPROM_char_OK[]    = "EEPROM     :OK   ";
char EEPROM_char_ERROR[] = "EEPROM     :ERROR";

extern alt_u8 eeprom_Status;

void Show_Temp(void);
void Show_Time(void);
void Show_UART(void);
void Show_IR(void);
void Show_PS2(void);
void Show_ADC(void);

unsigned char   IR_DATA_0 = 0x30;     
unsigned char   IR_DATA_1 = 0x30;     
unsigned char   IR_DATA_2 = 0x30;     
unsigned char   IR_DATA_3 = 0x30;  

unsigned char   PS2_DATA_0 = 0x30;    
unsigned char   PS2_DATA_1 = 0x30;    
unsigned char   PS2_DATA_2 = 0x30;    
unsigned char   PS2_DATA_3 = 0x30;   

unsigned char   UART_DATA_0 = 0x30;     
unsigned char   UART_DATA_1 = 0x30;     
unsigned char   UART_DATA_2 = 0x30;     
unsigned char   UART_DATA_3 = 0x30; 

void hardware_test (void) 
{
    Lcd_Show_char_8x16(0,(240-16*1) , logo2_char, (sizeof(logo2_char) - 1), 0xF800, 0xFFFF,0); 
	Lcd_Show_char_8x16(0,(240-20*1) , logo_char,  (sizeof(logo_char) - 1),  0xF800, 0xFFFF,0); 
    Lcd_Show_char_8x16(0,(235-20*6) , SD_char,    (sizeof(SD_char) - 1),    0xFFFF, 0x0000,0);
    Lcd_Show_char_8x16(0,(235-20*7) , USBH_char,  (sizeof(USBH_char) - 1),  0xFFFF, 0x0000,0);
    Lcd_Show_char_8x16(0,(235-20*8) , USBS_char,  (sizeof(USBS_char) - 1),  0xFFFF, 0x0000,0); 
    Lcd_Show_char_8x16(0,(235-20*9) , LAN_char,   (sizeof(LAN_char) - 1),   0xFFFF, 0x0000,0);       
	Lcd_Show_char_8x16(0,(235-20*10) , EEPROM_char_ERROR,   (sizeof(EEPROM_char_ERROR) - 1),   0xFFFF, 0x0000,0); 
	
    while(1)
    {
        Show_Temp();
        Show_Time();
        Show_UART();
        Show_IR();
        Show_PS2();
        Show_ADC();
        
        Lcd_Show_char_8x16(0  ,(235-20*2) , Temp_char, (sizeof(Temp_char) - 1), 0xFFFF, 0x0000,0);
        Lcd_Show_char_8x16(160,(235-20*2) , IR_char,   (sizeof(IR_char) - 1),   0xFFFF, 0x0000,0);
        Lcd_Show_char_8x16(0  ,(235-20*3) , Time_char, (sizeof(Time_char) - 1), 0xFFFF, 0x0000,0);
        Lcd_Show_char_8x16(160,(235-20*3) , Uart_char, (sizeof(Uart_char) - 1), 0xFFFF, 0x0000,0);
        Lcd_Show_char_8x16(0  ,(235-20*4) , ADC_char,  (sizeof(ADC_char) - 1),  0xFFFF, 0x0000,0);
        Lcd_Show_char_8x16(160,(235-20*4) , PS2_char,  (sizeof(PS2_char) - 1),  0xFFFF, 0x0000,0);

        Lcd_Show_char_8x16(100,(235-20*6) , SD_info, (sizeof(SD_info) - 1), 0xFFFF, 0x0000,0);
        Lcd_Show_char_8x16(100,(235-20*7) , USBH_info, (sizeof(USBH_info) - 1), 0xFFFF, 0x0000,0);
        Lcd_Show_char_8x16(100,(235-20*8) , USBS_info,  (sizeof(USBS_info) - 1),  0xFFFF, 0x0000,0);
        Lcd_Show_char_8x16(100,(235-20*9) , LAN_info,  (sizeof(LAN_info) - 1),  0xFFFF, 0x0000,0);

		if(eeprom_Status)
    		Lcd_Show_char_8x16(0,(235-20*10) , EEPROM_char_OK,   (sizeof(EEPROM_char_OK) - 1),   0xFFFF, 0x0000,0); 
	  	else
    		Lcd_Show_char_8x16(0,(235-20*10) , EEPROM_char_ERROR,   (sizeof(EEPROM_char_ERROR) - 1),   0xF800, 0x0000,0); 
                       
        OSTimeDlyHMSM(0, 0, 0, 100);
    }
} 

void Show_Temp(void)
{
    unsigned short  TEMP_DATA;  
    unsigned char   TEMP_D0, TEMP_D1, TEMP_D2;
    
    TEMP_DATA = READ_TEMP_DATA;
    
    TEMP_D2   = ((TEMP_DATA & 0x07F0) >>4) /10 + 0x30;
    TEMP_D1   = ((TEMP_DATA & 0x07F0) >>4) %10 + 0x30;   
    TEMP_D0   = ((TEMP_DATA & 0x000F)) %10 + 0x30;

    Temp_char[7]  = TEMP_D2;
    Temp_char[8]  = TEMP_D1;    
    Temp_char[10] = TEMP_D0; 
}

void Show_ADC(void)
{
    unsigned char  ADC_DATA;  
    unsigned char  ADC_D0, ADC_D1, ADC_D2;
    float vol = 0;
    
    ADC_DATA = READ_ADC_DATA;
    
    ADC_D0   = (ADC_DATA *5          )/255 + 0x30;
    ADC_D1   = (ADC_DATA *5 *10 /255) %10  + 0x30;
    ADC_D2   = (ADC_DATA *5 *100/255) %10  + 0x30;
    
    vol = (ADC_DATA *2)/255;

    ADC_char[7]  = ADC_D0;
    ADC_char[9]  = ADC_D1;    
    ADC_char[10] = ADC_D2; 
    
    printf("adc data = %02x,vol = %f\r\n",ADC_DATA,vol);
}

void Show_Time(void)
{
    unsigned int    RTC_DATA;
    unsigned char   RTC_D0, RTC_D1, RTC_D2, RTC_D3, RTC_D4, RTC_D5;       
   
    RTC_DATA  = READ_RTC_DATA;
        
    RTC_D0    = ((RTC_DATA & 0x00F00000) >> 20) + 0x30; 
    RTC_D1    = ((RTC_DATA & 0x000F0000) >> 16) + 0x30; 
    RTC_D2    = ((RTC_DATA & 0x0000F000) >> 12) + 0x30; 
    RTC_D3    = ((RTC_DATA & 0x00000F00) >> 8) + 0x30; 
    RTC_D4    = ((RTC_DATA & 0x000000F0) >> 4) + 0x30; 
    RTC_D5    = ((RTC_DATA & 0x0000000F)) + 0x30; 
    
    Time_char[7]   =  RTC_D0;
    Time_char[8]   =  RTC_D1;
    Time_char[10]  =  RTC_D2;
    Time_char[11]  =  RTC_D3;
    Time_char[13]  =  RTC_D4;
    Time_char[14]  =  RTC_D5;
	
	//printf("Time_char = %06x\r\n",RTC_DATA);
}

void Show_UART(void)
{
    if(READ_UART_DATA != UART_DATA_0)
    {
        UART_DATA_3  = UART_DATA_2;        
        UART_DATA_2  = UART_DATA_1;        
        UART_DATA_1  = UART_DATA_0;        
        UART_DATA_0  = READ_UART_DATA; 
        
        Uart_char[13]  =  UART_DATA_0;
        Uart_char[12]  =  UART_DATA_1;
        Uart_char[11]  =  UART_DATA_2;
        Uart_char[10]  =  UART_DATA_3;       
    } 
}

void Show_IR(void)
{
    unsigned int    IR_DATA_REC = 0;
    unsigned char   IR_DATA_NEW = 0x30;
      
    IR_DATA_REC   = READ_IR_DATA;
  
    if(((IR_DATA_REC & 0xFFFF0000) >> 16) == 0xFF02) //IR custerm code.
    {
        switch(((IR_DATA_REC & 0x0000FF00) >> 8))
        {
            case 0xCF : IR_DATA_NEW = 0x30; break;
            case 0xF7 : IR_DATA_NEW = 0x31; break;
            case 0x77 : IR_DATA_NEW = 0x32; break;
            case 0xB7 : IR_DATA_NEW = 0x33; break;
            case 0xD7 : IR_DATA_NEW = 0x34; break;
            case 0x57 : IR_DATA_NEW = 0x35; break;
            case 0x97 : IR_DATA_NEW = 0x36; break;
            case 0xE7 : IR_DATA_NEW = 0x37; break;
            case 0x67 : IR_DATA_NEW = 0x38; break;
            case 0xA7 : IR_DATA_NEW = 0x39; break;
            default   :                 break;
        }
    } 
    
    if(IR_DATA_NEW != IR_DATA_0)
    {
    IR_DATA_3 = IR_DATA_2;    	
    IR_DATA_2 = IR_DATA_1;    	
    IR_DATA_1 = IR_DATA_0;    	
    IR_DATA_0 = IR_DATA_NEW; 
    
    IR_char[13]  =  IR_DATA_0;
    IR_char[12]  =  IR_DATA_1;
    IR_char[11]  =  IR_DATA_2;
    IR_char[10]  =  IR_DATA_3;   	
    }
}

void Show_PS2(void) 
{
    unsigned short  PS2_DATA_REC = 0;
    unsigned short  PS2_DATA_NEW = 0x30;
    
    PS2_DATA_REC   = READ_PS2_DATA;

    switch(PS2_DATA_REC & 0x00FF)
    {
        case 0x16 : PS2_DATA_NEW = 0x31 ; break;//{ 1 }        
        case 0x1E : PS2_DATA_NEW = 0x32 ; break;//{ 2 }        
        case 0x26 : PS2_DATA_NEW = 0x33 ; break;//{ 3 }        
        case 0x25 : PS2_DATA_NEW = 0x34 ; break;//{ 4 }        
        case 0x2E : PS2_DATA_NEW = 0x35 ; break;//{ 5 }        
        case 0x36 : PS2_DATA_NEW = 0x36 ; break;//{ 6 }        
        case 0x3D : PS2_DATA_NEW = 0x37 ; break;//{ 7 }        
        case 0x3E : PS2_DATA_NEW = 0x38 ; break;//{ 8 }        
        case 0x46 : PS2_DATA_NEW = 0x39 ; break;//{ 9 }        
        case 0x45 : PS2_DATA_NEW = 0x30 ; break;//{ 0 }        
        case 0x1C : PS2_DATA_NEW = 0x61 ; break;//{ a }        
        case 0x32 : PS2_DATA_NEW = 0x62 ; break;//{ b }        
        case 0x21 : PS2_DATA_NEW = 0x63 ; break;//{ c }        
        case 0x23 : PS2_DATA_NEW = 0x64 ; break;//{ d }        
        case 0x24 : PS2_DATA_NEW = 0x65 ; break;//{ e }        
        case 0x2B : PS2_DATA_NEW = 0x66 ; break;//{ f }        
        case 0x34 : PS2_DATA_NEW = 0x67 ; break;//{ g }        
        case 0x33 : PS2_DATA_NEW = 0x68 ; break;//{ h }        
        case 0x43 : PS2_DATA_NEW = 0x69 ; break;//{ i }        
        case 0x3B : PS2_DATA_NEW = 0x6A ; break;//{ j }        
        case 0x42 : PS2_DATA_NEW = 0x6B ; break;//{ k }        
        case 0x4B : PS2_DATA_NEW = 0x6C ; break;//{ l }        
        case 0x3A : PS2_DATA_NEW = 0x6D ; break;//{ m }        
        case 0x31 : PS2_DATA_NEW = 0x6E ; break;//{ n }        
        case 0x44 : PS2_DATA_NEW = 0x6F ; break;//{ o }        
        case 0x4D : PS2_DATA_NEW = 0x70 ; break;//{ p }        
        case 0x15 : PS2_DATA_NEW = 0x71 ; break;//{ q }        
        case 0x2D : PS2_DATA_NEW = 0x72 ; break;//{ r }        
        case 0x1B : PS2_DATA_NEW = 0x73 ; break;//{ s }        
        case 0x2C : PS2_DATA_NEW = 0x74 ; break;//{ t }        
        case 0x3C : PS2_DATA_NEW = 0x75 ; break;//{ u }        
        case 0x2A : PS2_DATA_NEW = 0x76 ; break;//{ v }        
        case 0x1D : PS2_DATA_NEW = 0x77 ; break;//{ w }        
        case 0x22 : PS2_DATA_NEW = 0x78 ; break;//{ x }        
        case 0x35 : PS2_DATA_NEW = 0x79 ; break;//{ y }        
        case 0x1A : PS2_DATA_NEW = 0x7A ; break;//{ z }        
        case 0x54 : PS2_DATA_NEW = 0x5B ; break;//{ [ }        
        case 0x5B : PS2_DATA_NEW = 0x5D ; break;//{ ] }        
        case 0x4C : PS2_DATA_NEW = 0x3B ; break;//{ ; }        
        case 0x52 : PS2_DATA_NEW = 0x27 ; break;//{ }          
        case 0x41 : PS2_DATA_NEW = 0x2C ; break;//{ , }        
        case 0x49 : PS2_DATA_NEW = 0x2E ; break;//{ . }        
        case 0x4A : PS2_DATA_NEW = 0x2F ; break;//{ / }        
        case 0x4E : PS2_DATA_NEW = 0x2D ; break;//{ - }        
        case 0x55 : PS2_DATA_NEW = 0x3D ; break;//{ = }        
        case 0x5D : PS2_DATA_NEW = 0x5C ; break;//{ }          
        case 0xE  : PS2_DATA_NEW = 0x60 ; break;//{ ` }        
        case 0x5A : PS2_DATA_NEW = 0x20 ; break;//{ enter }    
        case 0x5  : PS2_DATA_NEW = 0x0  ; break;//{ f1 }       
        case 0x6  : PS2_DATA_NEW = 0x1  ; break;//{ f2 }       
        case 0x4  : PS2_DATA_NEW = 0x2  ; break;//{ f3 }       
        case 0xC  : PS2_DATA_NEW = 0x3  ; break;//{ f4 }       
        case 0x3  : PS2_DATA_NEW = 0x4  ; break;//{ f5 }       
        case 0xB  : PS2_DATA_NEW = 0x5  ; break;//{ f6 }       
        case 0x83 : PS2_DATA_NEW = 0x6  ; break;//{ f7 }       
        case 0xA  : PS2_DATA_NEW = 0x7  ; break;//{ f8 }       
        case 0x1  : PS2_DATA_NEW = 0x8  ; break;//{ f9 }       
        case 0x9  : PS2_DATA_NEW = 0x9  ; break;//{ f10 }      
        case 0x78 : PS2_DATA_NEW = 0xA  ; break;//{ f11 }      
        case 0x7  : PS2_DATA_NEW = 0xB  ; break;//{ f12 }      
        case 0x66 : PS2_DATA_NEW = 0xC  ; break;//{ back }     
        case 0xE0 : PS2_DATA_NEW = 0xD  ; break;//{ home }     
        case 0x69 : PS2_DATA_NEW = 0xE  ; break;//{ end }      
        case 0x7D : PS2_DATA_NEW = 0xF  ; break;//{ pageup }   
        case 0x7A : PS2_DATA_NEW = 0x10 ; break;//{ pagedown } 
        case 0x75 : PS2_DATA_NEW = 0x11 ; break;//{ up }       
        case 0x72 : PS2_DATA_NEW = 0x12 ; break;//{ down }     
        case 0x6B : PS2_DATA_NEW = 0x13 ; break;//{ left }     
        case 0x74 : PS2_DATA_NEW = 0x14 ; break;//{ right }    
        case 0x71 : PS2_DATA_NEW = 0x15 ; break;//{ del }      
        case 0x70 : PS2_DATA_NEW = 0x16 ; break;//{ insert }   
        case 0xE1 : PS2_DATA_NEW = 0x17 ; break;//{ pause }    
        case 0x76 : PS2_DATA_NEW = 0x18 ; break;//{ esc }      
        case 0xD  : PS2_DATA_NEW = 0x19 ; break;//{ tab }      
        case 0x58 : PS2_DATA_NEW = 0x1A ; break;//{ caps }     
        case 0x14 : PS2_DATA_NEW = 0x1B ; break;//{ ctrl }     
        case 0x11 : PS2_DATA_NEW = 0x1C ; break;//{ alt }      
        case 0x29 : PS2_DATA_NEW = 0x1D ; break;//{ space }    
        case 0x1F : PS2_DATA_NEW = 0x1E ; break;//{ win }      
        case 0x2F : PS2_DATA_NEW = 0x1F ; break;//{ winright } 
        //case 0xE  : PS2_DATA = 0x7E ; break;//{ ~ }        
    }  
    
    if(PS2_DATA_NEW != PS2_DATA_0)
    {
        PS2_DATA_3 = PS2_DATA_2;
        PS2_DATA_2 = PS2_DATA_1;
        PS2_DATA_1 = PS2_DATA_0;    
        PS2_DATA_0 = PS2_DATA_NEW;
 
        PS2_char[13]  =  PS2_DATA_0;
        PS2_char[12]  =  PS2_DATA_1;
        PS2_char[11]  =  PS2_DATA_2;
        PS2_char[10]  =  PS2_DATA_3;      
    }
}





