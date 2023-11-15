
#include "stdio.h"
#include "LCD.h"
#include "Code_ascii_8x16.h"

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

void Lcd_Show_char_8x16(unsigned short pos_x, unsigned char pos_y, unsigned char * show_char, unsigned char char_num, unsigned short Top_clour, unsigned short black_clour,unsigned int TB_Change)
{	 
    int i,j,k;
    unsigned char  show_char_data;
    unsigned short show_char_start_addr;
    unsigned char  show_data;
    
    //Address_Window_Set(pos_x,pos_y,9,(char_num*16));
    
    for(i=0; i<char_num ; i++)
        {            
            show_char_data       = *(show_char + i);
            show_char_start_addr = show_char_data * 16;
  
            Address_Window_Set(pos_y, (pos_x + 8*i),16,8);
            Address_Window_Start(pos_y, (pos_x + 8*i));
                        
            for(j=0; j<16; j++)
               {
                    show_data = code_ascii[show_char_start_addr + j];
                    for(k=0; k<8; k++)
                        {
                            if(show_data & 0x80)
                            {
                              if(!TB_Change)
                              Send_LcmData(Top_clour);
                              else
                              Send_LcmData(black_clour);
                            }                              
                            else
                            {
                              if(!TB_Change)
                              Send_LcmData(black_clour);
                              else
                              Send_LcmData(Top_clour);
                            }  
                              
                            show_data = show_data << 1;
                            
                        }             
               }
        }
}

