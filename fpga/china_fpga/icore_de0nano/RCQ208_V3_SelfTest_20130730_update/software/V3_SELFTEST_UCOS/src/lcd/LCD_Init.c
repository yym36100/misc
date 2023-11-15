
#include "stdio.h"
#include "LCD.h"

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
void delay_ms(unsigned int delay_value);

void TFT_Clear_Region(alt_u16 x,alt_u16 y,alt_u32 width,alt_u32 high,alt_u16 color)
{
	alt_u32 i;
	Address_Window_Set(y,x,high,width);
	Address_Window_Start(y,x);

    SET_LCD_RS;     //data control
    CLR_LCD_CS;     //chip on     
    SET_LCD_RD;     //write mode  
	for(i=0; i<width*high; i++)
    {	
        SET_DATA(color >> 8);    
        CLR_LCD_WR;  
        SET_LCD_WR;   

        SET_DATA(color);    
        CLR_LCD_WR;  
        SET_LCD_WR;			
    }
    SET_LCD_CS;  	
}


void LcmInit(void)
{
    int i;
    	 
	CLR_LCD_RST;
	delay_ms(100);
	SET_LCD_RST;
	delay_ms(100);		

	Send_LcmCommand(0x00E3);   Send_LcmData(0x3008); // Set internal timing
	Send_LcmCommand(0x00E7);   Send_LcmData(0x0012); // Set internal timing
	Send_LcmCommand(0x00EF);   Send_LcmData(0x1231); // Set internal timing
	Send_LcmCommand(0x0000);   Send_LcmData(0x0001); 
	Send_LcmCommand(0x0001);   Send_LcmData(0x0100); //0x0100->0x0000 // set SS and SM bit
	Send_LcmCommand(0x0002);   Send_LcmData(0x0700); // set 1 line inversion

	//Send_LcmCommand(0x0003);   Send_LcmData(0x0030); // set GRAM write direction and BGR=1 16bits.
    Send_LcmCommand(0x0003);   Send_LcmData(0x0028 | (1 << 12)); // set GRAM write direction and BGR=1 16bits.

	Send_LcmCommand(0x0004);   Send_LcmData(0x0000); // Resize register
	//Send_LcmCommand(0x00,0x08);   Send_LcmData(0x02,0x02); // set the back porch and front porch
	Send_LcmCommand(0x0008);   Send_LcmData(0x0808); // set the back porch and front porch for M158N bug 996 噪声

	Send_LcmCommand(0x0009);   Send_LcmData(0x0000); // set non-display area refresh cycle ISC[3:0]
	Send_LcmCommand(0x000A);   Send_LcmData(0x0008); // FMARK function
	Send_LcmCommand(0x000C);   Send_LcmData(0x0000); // RGB interface setting
	Send_LcmCommand(0x000D);   Send_LcmData(0x0000); // Frame marker Position
	Send_LcmCommand(0x000F);   Send_LcmData(0x0000); // RGB interface polarity
	//=************Power On sequence ***************=/
	Send_LcmCommand(0x0010);   Send_LcmData(0x0000); // SAP);   Send_LcmData(BT[3:0]);   Send_LcmData(AP);   Send_LcmData(DSTB);   Send_LcmData(SLP);   Send_LcmData(STB
	Send_LcmCommand(0x0011);   Send_LcmData(0x0007); // DC1[2:0]);   Send_LcmData(DC0[2:0]);   Send_LcmData(VC[2:0]
	Send_LcmCommand(0x0012);   Send_LcmData(0x0000); // VREG1OUT voltage
	Send_LcmCommand(0x0013);   Send_LcmData(0x0000); // VDV[4:0] for VCOM amplitude
	delay_ms(200); // Dis-charge capacitor power voltage
	Send_LcmCommand(0x0010);   Send_LcmData(0x1190); // SAP);   Send_LcmData(BT[3:0]);   Send_LcmData(AP);   Send_LcmData(DSTB);   Send_LcmData(SLP);   Send_LcmData(STB
	Send_LcmCommand(0x0011);   Send_LcmData(0x0227); // Set DC1[2:0]);   Send_LcmData(DC0[2:0]);   Send_LcmData(VC[2:0]
	delay_ms(50); // Delay 50ms
	Send_LcmCommand(0x0012);   Send_LcmData(0x001D); 
	delay_ms(50); // Delay 50ms
	Send_LcmCommand(0x0013);   Send_LcmData(0x1a00); // Set VDV[4:0] for VCOM amplitude
	Send_LcmCommand(0x0029);   Send_LcmData(0x0035); // SetVCM[5:0] for VCOMH
	//Send_LcmCommand(0x00,0x2B);   Send_LcmData(0x00,0x0A); // Set Frame Rate 60Hz
	Send_LcmCommand(0x002B);   Send_LcmData(0x000D);   // Set Frame Rate 91Hz for M158N bug 996 噪声0x0D->0x0E 91Hz->112Hz //changed back(0x0E->0x0D) 因为主板发出噪音（）

	delay_ms(50); // Delay 50ms
	Send_LcmCommand(0x0020);   Send_LcmData(0x0000); // GRAM horizontal Address
	Send_LcmCommand(0x0021);   Send_LcmData(0x0000); // GRAM Vertical Address
	// ----------- Adjust the Gamma Curve ----------//
	Send_LcmCommand(0x0030);   Send_LcmData(0x0001);
	Send_LcmCommand(0x0031);   Send_LcmData(0x0507);
	Send_LcmCommand(0x0032);   Send_LcmData(0x0305);
	Send_LcmCommand(0x0035);   Send_LcmData(0x0103);
	Send_LcmCommand(0x0036);   Send_LcmData(0x1C0C);//??
	Send_LcmCommand(0x0037);   Send_LcmData(0x0103);
	Send_LcmCommand(0x0038);   Send_LcmData(0x0000);//??
	Send_LcmCommand(0x0039);   Send_LcmData(0x0707);
	Send_LcmCommand(0x003C);   Send_LcmData(0x0301);
	Send_LcmCommand(0x003D);   Send_LcmData(0x1B09);

	//------------------ Set GRAM area ---------------//
	Send_LcmCommand(0x0050);   Send_LcmData(0x0000); // Horizontal GRAM Start Address
	Send_LcmCommand(0x0051);   Send_LcmData(0x00EF); // Horizontal GRAM End Address
	Send_LcmCommand(0x0052);   Send_LcmData(0x0000); // Vertical GRAM Start Address
	Send_LcmCommand(0x0053);   Send_LcmData(0x013F); // Vertical GRAM Start Address
	Send_LcmCommand(0x0060);   Send_LcmData(0xA700); //0xA700->0x2700  // Gate Scan Line
	Send_LcmCommand(0x0061);   Send_LcmData(0x0001); // NDL,VLE);   Send_LcmData(REV
	Send_LcmCommand(0x006A);   Send_LcmData(0x0000); // set scrolling line
	//-------------- Partial Display Control ---------//
	Send_LcmCommand(0x0080);   Send_LcmData(0x0000);
	Send_LcmCommand(0x0081);   Send_LcmData(0x0000);
	Send_LcmCommand(0x0082);   Send_LcmData(0x0000);
	Send_LcmCommand(0x0083);   Send_LcmData(0x0000);
	Send_LcmCommand(0x0084);   Send_LcmData(0x0000);
	Send_LcmCommand(0x0085);   Send_LcmData(0x0000);
	//-------------- Panel Control -------------------//
	Send_LcmCommand(0x0090);   Send_LcmData(0x0010);
	Send_LcmCommand(0x0092);   Send_LcmData(0x0000);
	Send_LcmCommand(0x0093);   Send_LcmData(0x0003);
	Send_LcmCommand(0x0095);   Send_LcmData(0x0110);
	Send_LcmCommand(0x0097);   Send_LcmData(0x0000);
	Send_LcmCommand(0x0098);   Send_LcmData(0x0000);
	Send_LcmCommand(0x0007);   Send_LcmData(0x0133); // 262K color and display ON
    Send_LcmCommand(0x0022); //write data  
    TFT_Clear_Region(0, 0, 320, 240, 0);
}
	    

  
void Address_Window_Set(alt_u16 Pos_x, alt_u16 Pos_y, alt_u16 width, alt_u16 height)
{
	Send_LcmCommand(0x0050);// Horizontal Address Start
	Send_LcmData(Pos_x);        

	Send_LcmCommand(0x0051); //Horizontal Address end
	Send_LcmData(Pos_x + width - 1);        

	Send_LcmCommand(0x0052);//Vertical Address Start Position
	Send_LcmData(Pos_y);        

	Send_LcmCommand(0x0053); //Vertical Address end Position
	Send_LcmData(Pos_y + height - 1);     

	Send_LcmCommand(0x0022); //write data   
}

 void Address_Window_Start(alt_u16 Pos_x,alt_u16 Pos_y)
{
    Send_LcmCommand(0x0020);// Horizontal Address Start
    Send_LcmData(Pos_x);             

    Send_LcmCommand(0x0021);//Vertical Address Start Position
    Send_LcmData(Pos_y);          

    Send_LcmCommand(0x0022); //write data   
}


void Send_LcmCommand(unsigned short CMD)
{
//	UINT8 i;
	CLR_LCD_CS;     //chip on	
	CLR_LCD_RS;     //command control
	SET_LCD_RD;     //write mode 
	
	SET_DATA(CMD);
	CLR_LCD_WR;      
	SET_LCD_WR;    
 	
	SET_LCD_CS; 
}

void Send_LcmData(unsigned short DATA)
{
	CLR_LCD_CS;     //chip on	
	SET_LCD_RS;     //data control
	SET_LCD_RD;     //write mode 
  
	SET_DATA(DATA);   
	CLR_LCD_WR;     
	SET_LCD_WR;  
 		
	SET_LCD_CS; 
}

void delay_ms(unsigned int delay_value)
{   
    //int i;
    //for(i=0;i<200000;i++)
    //for(; delay_value != 0; delay_value--);
    while(--delay_value)
		usleep(1000);
}
