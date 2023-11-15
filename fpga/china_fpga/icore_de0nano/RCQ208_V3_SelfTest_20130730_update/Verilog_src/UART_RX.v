//==========================================================================
//Filename  :UART_RX.v
//modulename:UART_RX
//Author    :xp.wu
//Date	    :2009-9-27
//Function  :This is a reciver sub module of the UART.
//Uesedfor  :Altera cyclon EP2C5T144C8/EP2C8T144C8, made by xsyan.
//==========================================================================

`define UD #1

module UART_RX
	(
	//Input ports
	SYSCLK,
	RST_B,
	UART_RX,

	//Output ports
	RX_DATA,
	RX_FINISH
	);

//==========================================================================
//Input and output declaration
//==========================================================================

input		SYSCLK;		//Global clock, 50MHz.
input		RST_B;		//Global reset, low active.
input		UART_RX;	//UART receive port.

output	[7:0]	RX_DATA;	//The data has received.
output		RX_FINISH;	//Receeved a complet byte.

//==========================================================================
//Wire and reg declaration
//==========================================================================

wire		SYSCLK;
wire		RST_B;
wire		UART_RX;
wire		RX_FINISH;

reg	[7:0]	RX_DATA;

//==========================================================================
//Wire and reg in the module
//==========================================================================

reg	[15:0]	CLK_DIV_CNT;	//Count for division the clock.
reg	[15:0]	CLK_DIV_CNT_N;	//Multi cache.
reg	[7:0]	RX_DATA_N;	//Next value of RX_DATA_N.
reg		UART_RX_REG;	//Save UART_RX one cycle.
reg		UART_RX_REG_N;	//Save UART_RX one cycle.
wire		START;		//Active when start a byte receive.
wire		DATA_FINISH;	//Active when 8 bits data has received.


//==========================================================================
//Logic
//==========================================================================

//Some control single.
always @ (posedge SYSCLK) UART_RX_REG <= `UD UART_RX;
always @ (posedge SYSCLK) UART_RX_REG_N <= `UD UART_RX_REG;
assign	START	    = (!UART_RX) && (UART_RX_REG || UART_RX_REG_N);
assign	RX_FINISH   = (CLK_DIV_CNT == 16'hFF5);


//Division the clock to satisfy baud rate.
//This counter will add 1 when 1 Byte is rec.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    CLK_DIV_CNT	   <= `UD 16'h0;
  else
    CLK_DIV_CNT	   <= `UD CLK_DIV_CNT_N;
end

always @ (*)
begin
  if((START)&& (CLK_DIV_CNT == 16'h0))
     CLK_DIV_CNT_N   = 16'h1;
  else if(CLK_DIV_CNT == 16'hFF5)
     CLK_DIV_CNT_N   = 16'h0;
  else if(CLK_DIV_CNT != 16'h0)
    CLK_DIV_CNT_N   = CLK_DIV_CNT + 16'h1;
  else
    CLK_DIV_CNT_N   = CLK_DIV_CNT;
end

//==========================================================================
//Receive state machine
//==========================================================================

always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    RX_DATA   <= `UD 8'h0;
  else
    RX_DATA   <= `UD RX_DATA_N;
end

always @ (*)
begin
  if((CLK_DIV_CNT == 16'h2D0)||
     (CLK_DIV_CNT == 16'h47E)||
     (CLK_DIV_CNT == 16'h62C)||
     (CLK_DIV_CNT == 16'h7DA)||
     (CLK_DIV_CNT == 16'h988)||
     (CLK_DIV_CNT == 16'hB36)||
     (CLK_DIV_CNT == 16'hCE4)||
     (CLK_DIV_CNT == 16'hE92))
    RX_DATA_N  = {UART_RX , RX_DATA[7:1]};
  else
    RX_DATA_N  = RX_DATA;
end

endmodule




