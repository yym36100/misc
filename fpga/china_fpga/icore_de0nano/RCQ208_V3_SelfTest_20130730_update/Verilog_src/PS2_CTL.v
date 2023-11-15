//==========================================================================
//Filename  :PS2_CTL.v
//modulename:PS2_CTL
//Author    :xp.wu
//Date	    :2010-01-08
//Function  :This is a PS2 receiver module which can receive PS2 interface
//           input, example PS2 keyboard..
//Uesedfor  :RedCore_EP2C5_V3_EVB, made by redcore.
//Taobao    :http://redcore-1.taobao.com
//E-mail    :xingping99@163.com
//QQ	    :109019299
//==========================================================================

`define	UD #1

module PS2_CTL
	(
	//Global ports.
	SYSCLK,
	RST_B,
	
	//PS2 ports.
	PS2_CLK,
	PS2_DATA,
	DATA_REC,
	DATA_NEW
	);
	
//==========================================================================
//Input and output declararion
//==========================================================================

input		SYSCLK;
input		RST_B;
input		PS2_CLK;
input		PS2_DATA;

output	[15:0]	DATA_REC;
output		DATA_NEW;

//==========================================================================
//Wire and reg declaration
//==========================================================================

wire		SYSCLK;
wire		RST_B;
wire		PS2_CLK;
wire		PS2_DATA;

reg	[15:0]	DATA_REC;
reg		DATA_NEW;

//==========================================================================
//Wire and reg in the module
//==========================================================================

wire		TIME_OUT;		//The ps2_data last more then 100ms.
wire		DATA_EN;

reg	[1:0]	PS2_CLK_REG;		//Save the PS2_CLK one clock.
reg	[1:0]	PS2_CLK_REG_N;


reg	[31:0]	TIME_CNT;
reg	[31:0]	TIME_CNT_N;

reg	[3:0]	BIT_CNT;
reg	[3:0]	BIT_CNT_N;

reg	[10:0]	BIT_SHIFT;
reg	[10:0]	BIT_SHIFT_N;

reg	[39:0]	DATA_SHIFT;
reg	[39:0]	DATA_SHIFT_N;

reg	[15:0]	DATA_REC_N;
reg		DATA_NEW_N;

//==========================================================================
//Logic
//==========================================================================

//==========================================================================
//Time out control.
//==========================================================================

//Time control, when ps2_clk last high level longer than 100ms, soft reset.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    TIME_CNT	<= `UD 32'h0;
  else
    TIME_CNT	<= `UD TIME_CNT_N;
end

always @ (*)
begin
  if(!PS2_CLK)
    TIME_CNT_N	= 32'h0;
  else if(TIME_CNT == 32'h6000)
    TIME_CNT_N	= 32'h0;
  else
    TIME_CNT_N  = TIME_CNT + 32'h1;
end

//Time out control.
assign	TIME_OUT = (TIME_CNT == 32'h26000);

//==========================================================================
//Data reciver
//==========================================================================

//Save the ps2 clk one clock.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    PS2_CLK_REG	<= `UD 2'h3;
  else
    PS2_CLK_REG <= `UD PS2_CLK_REG_N;
end

always @ (*)
begin
  if(TIME_OUT)
    PS2_CLK_REG_N = 2'h3;
  else
    PS2_CLK_REG_N = {PS2_CLK_REG[0] , PS2_CLK};
end

//There is a avild bit.
assign	DATA_EN = (PS2_CLK_REG == 2'h2) ? 1'h1 : 1'h0; //2'b10

//Bit number counter, recie 11 bits one time.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    BIT_CNT	<= `UD 4'h0;
  else
    BIT_CNT	<= `UD BIT_CNT_N;
end

always @ (*)
begin
  if(TIME_OUT)
    BIT_CNT_N	 = 4'h0;
  else if(BIT_CNT == 4'hB)
    BIT_CNT_N	 = 4'h0;
  else if(DATA_EN)
    BIT_CNT_N    = BIT_CNT + 4'h1;
  else
    BIT_CNT_N	 = BIT_CNT;
end

//Bit shift, save the bit.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    BIT_SHIFT	<= `UD 11'h0;
  else
    BIT_SHIFT	<= `UD BIT_SHIFT_N;
end

always @ (*)
begin
  if(TIME_OUT)
    BIT_SHIFT_N  = 11'h0;
  else if(DATA_EN)
    BIT_SHIFT_N  = {PS2_DATA , BIT_SHIFT[10:1]};
  else
    BIT_SHIFT_N  = BIT_SHIFT;
end

//Data shift, recie the data transmit from keybord.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    DATA_SHIFT	<= `UD 40'h0;
  else
    DATA_SHIFT	<= `UD DATA_SHIFT_N;
end

always @ (*)
begin
  if(TIME_OUT)
    DATA_SHIFT_N = 40'h0;
  else if(BIT_CNT == 4'hB)
    DATA_SHIFT_N = {DATA_SHIFT[31:0] , BIT_SHIFT[8:1]};
  else
    DATA_SHIFT_N = DATA_SHIFT;
end

//==========================================================================
//Output control
//==========================================================================

//Avild data had recieved.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    DATA_REC	<= `UD 16'h0;
  else
    DATA_REC	<= `UD DATA_REC_N;
end

always @ (*)
begin
  if(TIME_OUT)
    DATA_REC_N	 = 16'h0;
  else if((DATA_SHIFT_N[15:8] == 8'hF0) && (DATA_SHIFT_N[23:16] == 8'hE0))
    DATA_REC_N	 = {8'hE0 , DATA_SHIFT_N[7:0]};
  else if((DATA_SHIFT_N[15:8] == 8'hF0) && (DATA_SHIFT_N[23:16] != 8'hE0))
    DATA_REC_N   = {8'h0, DATA_SHIFT_N[7:0]};
  else
    DATA_REC_N   = DATA_REC;
end

//Creat one single when there is a avild single.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    DATA_NEW	<= `UD 1'h0;
  else
    DATA_NEW	<= `UD DATA_NEW_N;
end

always @ (*)
begin
  if(TIME_OUT)
    DATA_NEW_N	 = 1'h0;
  else if((DATA_SHIFT_N[15:8] == 8'hF0) && (DATA_SHIFT[15:8] != 8'hF0))
    DATA_NEW_N	 = 1'h1;
  else 
    DATA_NEW_N	 = 1'h0;
end	  



endmodule








