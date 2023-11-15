//==============================================================================
// File Name   : DS1302Z_APP.v
// Module Name : 
// Description : DS1302主控层,初始化DS1302Z后就读取时间信息并在数码管上显示
// Author      : xsyan1225 (红芯电子_飞哥)
// HomePage    : http://shop57125352.taobao.com/
// Date        : 2011/05/02
// Rev.        : 0.1
//------------------------------------------------------------------------------
// Rev. Date       Description
//------------------------------------------------------------------------------
// 0.1  2011/05/02 1st Release
//==============================================================================
// 说明:在开始看代码之前请务必先分析DS1302的数据手册，各寄存器含义和时序要求
//==============================================================================
`define UD #1

module DS1302_APP
(
	RST_B,
	SYSCLK,

	RTC_RST,
	RTC_CLK,
	RTC_IO,

	RTC_DATA
);
//==============================================================================
//	Input and output declaration
//==============================================================================
input 		RST_B;		//主复位信号，低有效
input 		SYSCLK;		//系统时钟，50MHz

output	 	RTC_RST;	//DS1302Z SPI总线的RST信号
output	 	RTC_CLK;	//DS1302Z SPI总线的CLK信号 
inout	 	RTC_IO;		//DS1302Z SPI总线的IO信号,双向三态信号

output	[23:0]	RTC_DATA;

//==============================================================================
//	Wire and reg declaration
//==============================================================================
wire		RSY_B;
wire		SYSCLK;

wire		RTC_RST;		
wire		RTC_CLK;
wire		RTC_IO;

wire	[23:0]	RTC_DATA;

//==============================================================================
//	Macro definition
//==============================================================================

parameter	FUNC_SEC_ADDR		= 8'h80;
parameter	FUNC_MIN_ADDR		= 8'h82;
parameter	FUNC_HR_ADDR		= 8'h84;
parameter	FUNC_DATE_ADDR		= 8'h86;
parameter	FUNC_MONTH_ADDR 	= 8'h88;
parameter	FUNC_DAY_ADDR		= 8'h8a;
parameter	FUNC_YEAR_ADDR		= 8'h8c;
parameter	FUNC_CONTROL_ADDR	= 8'h8e;
parameter	FUNC_TRICKLE_ADDR	= 8'h90;
parameter	FUNC_CLK_BURST_ADDR 	= 8'hbe;

parameter	INIT_SEC		= 5'h0;
parameter	INIT_MIN		= 5'h1;
parameter	INIT_HR			= 5'h2;
parameter	INIT_DATE		= 5'h3;
parameter	INIT_MONTH 		= 5'h4;
parameter	INIT_DAY		= 5'h5;
parameter	INIT_YEAR		= 5'h6;
parameter	INIT_CONTROL		= 5'h7;
parameter	INIT_TRICKLE		= 5'h8;
//parameter	INIT_CLK_BURST 		= 5'h9;

parameter	READ_SEC		= 5'ha;
parameter	READ_MIN		= 5'hb;
parameter	READ_HR			= 5'hc;
parameter	READ_DATE		= 5'hd;
parameter	READ_MONTH 		= 5'he;
parameter	READ_DAY		= 5'hf;
parameter	READ_YEAR		= 5'h10;

parameter	INIT_SEC_DATA		= 8'h00;
parameter	INIT_MIN_DATA		= 8'h00;
parameter	INIT_HR_DATA		= 8'h00;
parameter	INIT_DATE_DATA		= 8'h0;
parameter	INIT_MONTH_DATA 	= 8'h0;
parameter	INIT_DAY_DATA		= 8'h0;
parameter	INIT_YEAR_DATA		= 8'h0;
parameter	INIT_CONTROL_DATA	= 8'h0;
parameter	INIT_TRICKLE_DATA	= 8'h0;
parameter	INIT_CLK_BURST_DATA 	= 8'h0;
//==============================================================================
//	Wire and reg in the module
//==============================================================================
	
reg		OP_RTC_START; 
reg		OP_WR;		//0 ,write ,1 read

reg		OP_RTC_START_N; 
reg		OP_WR_N;
		
reg	[7:0]	OP_ADDR;	//Which Address will be wrote or read
      	           
reg	[7:0]	DATA_W;		//Write data to RTC after address wrote
wire	[7:0]	DATA_R;		//Read data from RTC after address wrote

reg	[7:0]	DATA_W_N;
reg	[7:0]	OP_ADDR_N;

wire		RTC_BUSY;

reg	[3:0]	TIME_CNT;
reg	[3:0]	TIME_CNT_N;

reg	[4:0]	RTC_FSM_CS;
reg	[4:0]	RTC_FSM_NS;

reg	[4:0]	BYTE_CNT;
reg	[4:0]	BYTE_CN_N;

reg	[7:0]	SEC_DATA;	//Save RTC second data
reg	[7:0]	SEC_DATA_N;	

reg	[7:0]	MIN_DATA;	//Save RTC minute data
reg	[7:0]	MIN_DATA_N;	

reg	[7:0]	HR_DATA;	//Save RTC hour data
reg	[7:0]	HR_DATA_N;	

//==============================================================================
//	Logic
//==============================================================================

assign RTC_DATA = {HR_DATA[7:0],MIN_DATA[7:0],SEC_DATA[7:0]};

//reg [1:0]	RTC_BUSY_REG;
//always@ (posedge SYSCLK) RTC_BUSY_REG <= {RTC_BUSY_REG[0],RTC_BUSY};

always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  SEC_DATA <= `UD 8'h0;
 else
  SEC_DATA <= `UD SEC_DATA_N;
end

always @ (*)
begin
 if((RTC_FSM_CS == READ_SEC) && (RTC_FSM_NS == READ_MIN))
  SEC_DATA_N = DATA_R;
 else
  SEC_DATA_N = SEC_DATA;
end

//==============================================================================
always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  MIN_DATA <= `UD 8'h0;
 else
  MIN_DATA <= `UD MIN_DATA_N;
end

always @ (*)
begin
 if((RTC_FSM_CS == READ_MIN) && (RTC_FSM_NS == READ_HR))
  MIN_DATA_N = DATA_R;
 else
  MIN_DATA_N = MIN_DATA;
end
//==============================================================================
always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  HR_DATA <= `UD 8'h0;
 else
  HR_DATA <= `UD HR_DATA_N;
end

always @ (*)
begin
 if((RTC_FSM_CS == READ_HR) && (RTC_FSM_NS == READ_DATE))
  HR_DATA_N = DATA_R;
 else
  HR_DATA_N = HR_DATA;
end
//==============================================================================

always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  OP_RTC_START <= `UD 1'b0;
 else
  OP_RTC_START <= `UD OP_RTC_START_N;
end

always @ (*)
begin
 //if((!RTC_BUSY_SYNC) && RTC_BUSY_SYNC_N)
 if((TIME_CNT == 4'h1) && (RTC_BUSY))
  OP_RTC_START_N = 1'h1;
 else
  OP_RTC_START_N = 1'h0; 
end

//==============================================================================

always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  OP_WR <= `UD 1'b1;
 else
  OP_WR <= `UD OP_WR_N;
end

always @ (*)
begin
 case(RTC_FSM_CS)
  INIT_SEC,
  INIT_MIN,
  INIT_HR,
  INIT_DATE,
  INIT_MONTH,
  INIT_DAY,
  INIT_YEAR,
  INIT_CONTROL,
  INIT_TRICKLE:
//  INIT_CLK_BURST:
   OP_WR_N = 1'b0;
   
  READ_SEC,   
  READ_MIN,   
  READ_HR,   
  READ_DATE,   
  READ_MONTH,   
  READ_DAY,   
  READ_YEAR:
  
   OP_WR_N = 1'b1;

  default : 
   OP_WR_N = 1'b1;
  
 endcase
end


always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  TIME_CNT <= `UD 4'b0;
 else
  TIME_CNT <= `UD TIME_CNT_N;
end

always @ (*)
begin
 if(RTC_FSM_CS != RTC_FSM_NS)
  TIME_CNT_N = 4'h0;
 else if(TIME_CNT == 4'h8)
  TIME_CNT_N = TIME_CNT;
 else
  TIME_CNT_N = TIME_CNT + 4'h1;
end

//FSM for RTC initial & read data control

always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  RTC_FSM_CS <= `UD READ_SEC;
 else
  RTC_FSM_CS <= `UD RTC_FSM_NS;
end

always @ (*)
begin
 case(RTC_FSM_CS)
  INIT_CONTROL:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = INIT_SEC;
    else
     RTC_FSM_NS = RTC_FSM_CS;
 
  INIT_SEC:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = INIT_MIN;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  INIT_MIN:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = INIT_HR;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  INIT_HR:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = INIT_DATE;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  INIT_DATE:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = INIT_MONTH;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  INIT_MONTH:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = INIT_DAY;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  INIT_DAY:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = INIT_YEAR;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  INIT_YEAR:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = INIT_TRICKLE;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
//  INIT_CONTROL:
//    if((TIME_CNT == 4'h8) && RTC_BUSY)
//     RTC_FSM_NS = INIT_TRICKLE;
//    else
//     RTC_FSM_NS = RTC_FSM_CS;
     
  INIT_TRICKLE:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = READ_SEC;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
//  INIT_CLK_BURST:
//    if((TIME_CNT == 4'h8) && RTC_BUSY)
//     RTC_FSM_NS = READ_SEC;
//    else
//     RTC_FSM_NS = RTC_FSM_CS;


  // Note : 
  // The bit 7 of Second register indicate the crystal is running or not,
  // so, if you read is "0", means DS1302 has been initialized.Otherwise, need
  // into the initialization process.
  READ_SEC:
    if((TIME_CNT == 4'h8) && RTC_BUSY && (DATA_R & 8'h80))//need initial
     RTC_FSM_NS = INIT_CONTROL;  
    else if((TIME_CNT == 4'h8) && RTC_BUSY && (!(DATA_R & 8'h80)))
     RTC_FSM_NS = READ_MIN; 
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  READ_MIN:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = READ_HR;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  READ_HR:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = READ_DATE;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  READ_DATE:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = READ_MONTH;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  READ_MONTH:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = READ_DAY;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  READ_DAY:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = READ_YEAR;
    else
     RTC_FSM_NS = RTC_FSM_CS;
     
  READ_YEAR:
    if((TIME_CNT == 4'h8) && RTC_BUSY)
     RTC_FSM_NS = READ_SEC;
    else
     RTC_FSM_NS = RTC_FSM_CS;

 default : 
     RTC_FSM_NS = READ_SEC;

 endcase
end

//------------------------------------------------------------------------------

always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  OP_ADDR <= `UD FUNC_SEC_ADDR;
 else
  OP_ADDR <= `UD OP_ADDR_N;
end

always @ (*)
begin
 case(RTC_FSM_CS) 
  INIT_SEC,
  READ_SEC:	OP_ADDR_N = FUNC_SEC_ADDR; 
  
  INIT_MIN,
  READ_MIN:	OP_ADDR_N = FUNC_MIN_ADDR;
  
  INIT_HR,
  READ_HR:	OP_ADDR_N = FUNC_HR_ADDR; 
  
  INIT_DATE,
  READ_DATE:	OP_ADDR_N = FUNC_DATE_ADDR; 
  
  INIT_MONTH,
  READ_MONTH:	OP_ADDR_N = FUNC_MONTH_ADDR; 
  
  INIT_DAY,
  READ_DAY:	OP_ADDR_N = FUNC_DAY_ADDR; 
  
  INIT_YEAR,
  READ_YEAR:	OP_ADDR_N = FUNC_YEAR_ADDR;
  
  INIT_CONTROL:	OP_ADDR_N = FUNC_CONTROL_ADDR;
  
  INIT_TRICKLE:	OP_ADDR_N = FUNC_TRICKLE_ADDR;
  
//  INIT_CLK_BURST:OP_ADDR_N = FUNC_CLK_BURST_ADDR;
 
  default : OP_ADDR_N = FUNC_SEC_ADDR;
 endcase
end
//------------------------------------------------------------------------------
always @ (posedge SYSCLK or negedge RST_B)
begin
 if(!RST_B)
  DATA_W <= `UD 8'h0;
 else
  DATA_W <= `UD DATA_W_N;
end

always @ (*)
begin
 case(RTC_FSM_CS) 
 INIT_SEC	:DATA_W_N = INIT_SEC_DATA;
 INIT_MIN	:DATA_W_N = INIT_MIN_DATA;
 INIT_HR	:DATA_W_N = INIT_HR_DATA;
 INIT_DATE	:DATA_W_N = INIT_DATE_DATA;
 INIT_MONTH	:DATA_W_N = INIT_MONTH_DATA;
 INIT_DAY	:DATA_W_N = INIT_DAY_DATA;
 INIT_YEAR	:DATA_W_N = INIT_YEAR_DATA;
 INIT_CONTROL	:DATA_W_N = INIT_CONTROL_DATA;
 INIT_TRICKLE	:DATA_W_N = INIT_TRICKLE_DATA;
// INIT_CLK_BURST	:DATA_W_N = INIT_CLK_BURST_DATA;
 default 	:DATA_W_N = INIT_SEC_DATA;
 endcase
end

//==============================================================================
//	Instance
//==============================================================================
// 例化RTC2103_CTL, 读回其时间信息

DS1302_CTL	I_DS1302_CTL
(
	.RST_B          (RST_B          ),
	.SYSCLK         (SYSCLK         ),
	
	.OP_RTC_START   (OP_RTC_START   ),
	.OP_WR		(OP_WR	        ),
	.OP_ADDR    	(OP_ADDR        ),

	.RTC_RST        (RTC_RST        ),
	.RTC_CLK        (RTC_CLK        ),

	.RTC_IO		(RTC_IO       	),
	
	.DATA_W 	(DATA_W 	),
	.DATA_R  	(DATA_R  	),
	.RTC_BUSY	(RTC_BUSY	)
);

endmodule

//==============================================================================
//	End of file
//==============================================================================


