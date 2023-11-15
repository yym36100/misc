
//=============================================================================
//IO Operation
//=============================================================================
/*#define LCD_DATA_BASE	0x04002040
#define LCD_CS_BASE	    0x04002050
#define LCD_RST_BASE	0x04002080
#define LCD_RD_BASE	    0x04002070
#define LCD_RS_BASE	    0x04002060
#define LCD_WR_BASE	    0x04002090*/

#define	SET_LCD_WR	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_WR_BASE, 1)
#define	CLR_LCD_WR	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_WR_BASE, 0)

#define	SET_LCD_RST   IOWR_ALTERA_AVALON_PIO_DATA(LCD_RST_BASE, 1)
#define	CLR_LCD_RST   IOWR_ALTERA_AVALON_PIO_DATA(LCD_RST_BASE, 0)

#define	SET_LCD_RD	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE, 1)
#define	CLR_LCD_RD    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE, 0)

#define	SET_LCD_RS    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE, 1)
#define	CLR_LCD_RS    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE, 0)

#define	SET_LCD_CS    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE, 1)
#define	CLR_LCD_CS    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE, 0)      

#define	SET_DATA(data)  IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, data);


//==============================================================================
//Functiom define
//==============================================================================
extern void  Send_LcmCommand(unsigned short CMD);
extern void  Send_LcmData(unsigned short DATA);
extern void  Address_Window_Set(unsigned short Pos_x, unsigned short Pos_y, unsigned short width, unsigned short height);
extern void  LcmInit(void);   //LCD ≥ı ºªØ
extern void  delay_ms(unsigned int delay_value);
extern void  Lcd_Show_char_8x16(unsigned short pos_x, unsigned char pos_y, unsigned char * show_char, unsigned char char_num, unsigned short Top_clour, unsigned short black_clour,unsigned int TB_Change);
extern void  Address_Window_Start(unsigned short Pos_x, unsigned short Pos_y);



