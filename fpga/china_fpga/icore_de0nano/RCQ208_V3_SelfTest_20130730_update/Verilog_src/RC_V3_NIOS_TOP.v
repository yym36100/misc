
`define UD #1

module RC_V3_NIOS_TOP
	(
	//Global ports.
	SYSCLK,
	SYSCLK_40MHZ,
	RST_B,

	//SDRAM ports.
	SDRAM_ADDR,
	SDRAM_BA,
	SDRAM_CAS,
	SDRAM_CKE,
	SDRAM_CS,
	SDRAM_DQ,
	SDRAM_DQM,
	SDRAM_RAS,
	SDRAM_WE,
	SDRAM_CLK,

	//Uart ports.
	UART_TX,
	UART_RX,

	//LCD ports.
	LCD_DATA,
	LCD_CS,
	LCD_RD,
	LCD_RS,
	LCD_RST,
	LCD_WR,

	//DS18B20 port
	TEMP_IO,
	
	//PS2 ports.
	PS2_CLK,
	PS2_DATA,

	//RTC ports.
	RTC_CLK,
	RTC_RST,
	RTC_IO,

	//I2C ports.
	I2C_SCL,
	I2C_SDA,

	//IR ports.
	IR_IO,
	
	//Key ports.
	KEY,
	
	//Buzzer ports.
	BUZZER_OUT,
	
	//LED ports.
	LED_DATA,
	
	//DAC ports.
	DAC_CLK,
	DAC_DATA,
	
	//ADC ports																				
	ADC_CS,											 
	ADC_CLK,
	ADC_DAT,

	//SD Card ports	
	SD_CS,											 
	SD_DI,
	SD_CLK,
	SD_DO,

	//USB ports.
	USB_SCS_O,
	USB_SDO_I,
	USB_SDI_O,
	USB_SCK_O,
	USB_INT_I,
	USB_RST_O,
	USB_PC_I,

	//ETH ports.
	ETH_RESET_O,
	ETH_SCK_O,
	ETH_SI_O,
	ETH_SO_I,
	ETH_CLKOUT_I,
	ETH_INT_I,
	ETH_CS_O,
	ETH_WOL_I,
	
	//Digital TUBE on_off, test code in nios c code.
	TUBE_EN,
	
	//VGA
	VGA_RED,
	VGA_GREEN,
	VGA_BLUE,
	VGA_VSYNC,
	VGA_HSYNC	
	);      
                
//===========================================================================
//Input and output declaration.
//===========================================================================

input		SYSCLK;
input		SYSCLK_40MHZ;
input		RST_B;

output	[12:0]	SDRAM_ADDR;
output	[1:0]	SDRAM_BA;
output		SDRAM_CAS;
output		SDRAM_CKE;
output		SDRAM_CS;
inout	[15:0]	SDRAM_DQ;
output	[1:0]	SDRAM_DQM;
output		SDRAM_RAS;
output		SDRAM_WE;
output		SDRAM_CLK;

input		UART_RX;
output		UART_TX;     
/*
output	[4:0]	LCD_CTL;
*/
output	[15:0]	LCD_DATA;
output		LCD_CS;
output		LCD_RD;
output		LCD_RS;
output		LCD_RST;
output		LCD_WR;

inout		TEMP_IO;

input		PS2_CLK;
input		PS2_DATA;

output		RTC_CLK;
output		RTC_RST;
inout		RTC_IO; 

output		I2C_SCL;
inout		I2C_SDA;

input		IR_IO;

input	[6:0]	KEY;
output	[5:0]	LED_DATA;
output		DAC_CLK;	
output	[7:0]	DAC_DATA;
output		BUZZER_OUT;

output		ADC_CLK;
input	[7:0]	ADC_DAT;
output		ADC_CS;

output		SD_CS;
output		SD_DI;
output		SD_CLK;
input		SD_DO;

output		USB_SCS_O;
input		USB_SDO_I;
output		USB_SDI_O;
output		USB_SCK_O;
input		USB_INT_I;
output		USB_RST_O;
input		USB_PC_I;


output		ETH_RESET_O;
output		ETH_SCK_O;
output		ETH_SI_O;
input		ETH_SO_I;
input		ETH_CLKOUT_I;
input		ETH_INT_I;
output		ETH_CS_O;
input		ETH_WOL_I;

output [3:0]	TUBE_EN;

output		VGA_RED;
output		VGA_GREEN;
output		VGA_BLUE;
output		VGA_VSYNC;
output		VGA_HSYNC;

//===========================================================================
//Wire and reg declaration.
//===========================================================================

wire		SYSCLK;		//Use the active crystal 50MHz on board.
wire		SYSCLK_40MHZ;	//Use the active crystal 40MHz on board.
wire		RST_B;

wire	[12:0]	SDRAM_ADDR;
wire	[1:0]	SDRAM_BA;
wire		SDRAM_CAS;
wire		SDRAM_CKE;
wire		SDRAM_CS;
wire	[15:0]	SDRAM_DQ;
wire	[1:0]	SDRAM_DQM;
wire		SDRAM_RAS;
wire		SDRAM_WE;
wire		SDRAM_CLK;

wire		UART_RX;
wire		UART_TX;
/*
wire	[4:0]	LCD_CTL;
*/
wire	[15:0]	LCD_DATA;
wire		LCD_CS;
wire		LCD_RD;
wire		LCD_RS;
wire		LCD_RST;
wire		LCD_WR;

wire		TEMP_IO;

wire		PS2_CLK;
wire		PS2_DATA;

wire		RTC_CLK;
wire		RTC_RST;
wire		RTC_IO;

wire		I2C_SCL;
wire		I2C_SDA;

wire		IR_IO;

wire	[6:0]	KEY;
wire	[5:0]	LED_DATA;
wire		DAC_CLK;	
wire	[7:0]	DAC_DATA;
wire		BUZZER_OUT;

wire		ADC_CLK;
wire	[7:0]	ADC_DAT;
wire		ADC_CS;

wire		SD_CS;
wire		SD_DI;
wire		SD_CLK;
wire		SD_DO;

wire		USB_SCS_O;
wire		USB_SDO_I;
wire		USB_SDI_O;
wire		USB_SCK_O;
wire		USB_INT_I;
wire		USB_RST_O;
wire		USB_PC_I;

wire		ETH_RESET_O;
wire		ETH_SCK_O;
wire		ETH_SI_O;
wire		ETH_SO_I;
wire		ETH_CLKOUT_I;
wire		ETH_INT_I;
wire		ETH_CS_O;
wire		ETH_WOL_I;

wire [3:0]	TUBE_EN;

wire		VGA_RED;
wire		VGA_GREEN;
wire		VGA_BLUE;
wire		VGA_VSYNC;
wire		VGA_HSYNC;

//===========================================================================
//Wire and reg in the module.
//===========================================================================

wire		CLK_100M;
wire		CLK_50M;

wire	[15:0]	TEMP_DATA;
wire	[15:0]	PS2_DATA_REC;
wire	[7:0]	UART_RX_DATA;
wire	[23:0]	RTC_DATA;
wire	[31:0]	IR_DATA;

wire		BUZZER;
wire	[3:0]	KEY_FOCUS;

wire	[7:0]	ADC_DATA_REC;

wire		VGA_KEY = 1'b1;

wire		BUZZER__EN;
wire		BUZZER_OUT1;
wire		BUZZER_OUT2;
//===========================================================================
//Instance.
//===========================================================================

assign BUZZER_OUT = (KEY != 7'h7f) ? BUZZER_OUT2 	: BUZZER_OUT1;
assign BUZZER__EN = (KEY != 7'h7f) ? 1'h1 		: 1'h0;

//Buzzer control.
BUZZER_CTL I_BUZZER_CTL
	(
	.SYSCLK		(SYSCLK),
	.RST_B		(RST_B),
	.BUZZER_EN	(BUZZER__EN),
	.BUZZER		(BUZZER_OUT2)
	);


//Instance the PLL.
PLL I_PLL
	(
	.inclk0		(SYSCLK),
	.c0		(CLK_50M),
	.c1		(CLK_100M),
	.c2		(SDRAM_CLK)
	);

//Instance Nios CPU.
RC_2C8V3_Nios_CPU I_RC_2C8V3_Nios_CPU
(
	.clk_0					(CLK_100M	),
	.reset_n				(RST_B		),
	/*
	.out_port_from_the_BUZZER_EN_Port	(),
	.in_port_to_the_IR_Port			(),
	.out_port_from_the_LED_Port		(),
	.in_port_to_the_PS2_Port		(),
	.in_port_to_the_RTC_Port		(),
	.in_port_to_the_Temp_Port		(),
	.out_port_from_the_LCD_CTL_Port		(LCD_CTL	),
	*/

	.out_port_from_the_TUBE_EN		(TUBE_EN	),	

	.in_port_to_the_BUZZER_DATA		(BUZZER		),
	.in_port_to_the_DAC_DATA		(DAC_DATA	),
	.in_port_to_the_LED_DATA		(LED_DATA	),
	.in_port_to_the_KEY_FOCUS		(KEY_FOCUS	),
        .in_port_to_the_TEMP_DATA		(TEMP_DATA	),
	.in_port_to_the_PS2_DATA_REC		(PS2_DATA_REC	),  	
	.in_port_to_the_UART_RX_DATA		(UART_RX_DATA	),
	.in_port_to_the_RTC_DATA		(RTC_DATA	),     	
	.in_port_to_the_IR_DATA			(IR_DATA	),
	.in_port_to_the_ADC_DATA		(ADC_DATA_REC	),

	// the_SCL
	.out_port_from_the_SCL			(I2C_SCL	),

	// the_SDA
	.bidir_port_to_and_from_the_SDA		(I2C_SDA	),

	.out_port_from_the_LCD_DATA		(LCD_DATA	),
        .out_port_from_the_LCD_CS		(LCD_CS	        ),
        .out_port_from_the_LCD_RD		(LCD_RD	        ),
        .out_port_from_the_LCD_RS		(LCD_RS	        ),
        .out_port_from_the_LCD_RST		(LCD_RST	),
        .out_port_from_the_LCD_WR		(LCD_WR	        ),

	.out_port_from_the_SD_CS		(SD_CS		),
	.out_port_from_the_SD_DI		(SD_DI		),     	
	.out_port_from_the_SD_CLK		(SD_CLK		),
	.in_port_to_the_SD_DO			(SD_DO		),

	
	.out_port_from_the_USB_SCS_O		(USB_SCS_O	),
        .in_port_to_the_USB_SDO_I		(USB_SDO_I	),
        .out_port_from_the_USB_SDI_O		(USB_SDI_O	),
        .out_port_from_the_USB_SCK_O		(USB_SCK_O	),
        .in_port_to_the_USB_INT_I		(USB_INT_I	),
        .out_port_from_the_USB_RST_O		(USB_RST_O	),
        .in_port_to_the_USB_PC_I		(USB_PC_I	),

	.out_port_from_the_ETH_RESET_O		(ETH_RESET_O	),
        .out_port_from_the_ETH_SCK_O		(ETH_SCK_O  	),
        .out_port_from_the_ETH_SI_O		(ETH_SI_O   	),
        .in_port_to_the_ETH_SO_I		(ETH_SO_I   	),
        .in_port_to_the_ETH_CLKOUT_I		(ETH_CLKOUT_I	),
        .in_port_to_the_ETH_INT_I		(ETH_INT_I  	),
	.out_port_from_the_ETH_CS_O		(ETH_CS_O   	),
        .in_port_to_the_ETH_WOL_I		(ETH_WOL_I  	),

	.zs_addr_from_the_sdram_0		(SDRAM_ADDR	),
	.zs_ba_from_the_sdram_0			(SDRAM_BA	),
	.zs_cas_n_from_the_sdram_0		(SDRAM_CAS	),
	.zs_cke_from_the_sdram_0		(SDRAM_CKE	),
	.zs_cs_n_from_the_sdram_0		(SDRAM_CS	),
	.zs_dq_to_and_from_the_sdram_0		(SDRAM_DQ	),
	.zs_dqm_from_the_sdram_0		(SDRAM_DQM	),
	.zs_ras_n_from_the_sdram_0		(SDRAM_RAS	),
	.zs_we_n_from_the_sdram_0		(SDRAM_WE	),

	.rxd_to_the_uart_0			(UART_RX	),
	.txd_from_the_uart_0			(UART_TX	)
	);

//Instance DS18B20 controller.
DS18B20_CTL I_DS18B20_CTL
	(
	.SYSCLK		(CLK_50M	),
	.RST_B		(RST_B		),
	.TEMP_IO	(TEMP_IO	),
	.TEMP_D1	(TEMP_DATA[7:0]	),
	.TEMP_D2	(TEMP_DATA[15:8])
	);

//Instance PS2 controller.
PS2_CTL I_PS2_CTL
	(
	.SYSCLK		(CLK_50M	),
	.RST_B		(RST_B		),
	.PS2_CLK	(PS2_CLK	),
	.PS2_DATA	(PS2_DATA	),
	.DATA_REC	(PS2_DATA_REC	),
	.DATA_NEW	(		)
	);

//Instance UART RX controller.	
UART_RX I_UART_RX
	(
	.SYSCLK		(CLK_50M	),
	.RST_B		(RST_B		),
	.UART_RX	(UART_RX	),
	.RX_DATA	(UART_RX_DATA	),
	.RX_FINISH	(		)
	);

//Instance DS1302Z controller.		
DS1302_APP  I_RTC                        
	(                    	
	.SYSCLK		(CLK_50M	),              
	.RST_B		(RST_B		),               
	.RTC_CLK	(RTC_CLK	),             
	.RTC_RST	(RTC_RST	),             
	.RTC_IO		(RTC_IO		),                 
	.RTC_DATA 	(RTC_DATA 	)           
	);  

//Instance NEC IR controller.
IR_CTL I_IR_CTL
	(
	.SYSCLK		(CLK_50M	),
	.RST_B		(RST_B		),
	.IR_IO		(IR_IO		),
	.IR_DATA	(IR_DATA	),
	.IR_EN		(		)
	);	

//Instance User key controller.
USER_KEY_CTL I_USER_KEY_CTL
	(
	.SYSCLK		(CLK_50M	),
	.SYSCLK_40MHZ	(SYSCLK_40MHZ	),	
	.RST_B		(RST_B		),
	.KEY		(KEY		),
	.LED_DATA	(LED_DATA	),
	.BUZZER		(BUZZER		),
	.DAC_CS		(		),
	.DAC_CLK	(DAC_CLK	),
	.DAC_DATA	(DAC_DATA	),
	.BUZZER_OUT	(BUZZER_OUT1),
	.KEY_FOCUS      (KEY_FOCUS      )
	);

//Instance ADC controller.
ADC_CTL I_ADC_CTL
	(
	.SYSCLK		(CLK_50M	),
	.RST_B		(RST_B		),
	.ADC_CS		(ADC_CS		),
	.ADC_CLK	(ADC_CLK	),
	.ADC_DAT	(ADC_DAT	),
	.ADC_DATA_REC	(ADC_DATA_REC	)
	);

//Instance VGA controller.
VGA_CTL I_VGA_CTL
	(
	.SYSCLK		(CLK_50M	),
	.RST_B		(RST_B		),
	//.KEY_B		(VGA_KEY	),
	.VGA_R		(VGA_RED	),
	.VGA_G		(VGA_GREEN	),
	.VGA_B		(VGA_BLUE	),
	.VGA_VS		(VGA_VSYNC	),
	.VGA_HS		(VGA_HSYNC	)
	);


endmodule               
