//==========================================================================
//Filename  :DS18B20_CTL.v
//modulename:DS18B20_CTL
//Author    :xp.wu
//Date	    :2010-5-25
//Function  :This is a DS18B20 control, which mapped the register of ds18B20
//           to ports. 
//Uesedfor  :RedCore_EP2C5_V3_EVB, made by redcore.
//Taobao    :http://redcore-1.taobao.com
//E-mail    :xingping99@163.com
//QQ	    :109019299
//==========================================================================

`define UD #1

`define ALL_CLEAR_T 16'h0	//0 at start, set to 0
`define INIT_SETZ_T 16'h61A8	//500us @ 50MHz
`define INIT_SAMP_T 16'h7148	//580us @ 50MHz
`define INIT_END_T  16'hC350	//1ms   @ 50MHz
`define WR_SETVAL_T 16'hFA	//5us   @ 50MHz
`define WR_SETZ_T   16'hEA6	//75us  @ 50MHz
`define WR_END_T    16'hFA0	//80us  @ 50MHz
`define RD_SETZ_T   16'h64	//2us   @ 50MHz
`define RD_SAMP_T   16'h28A	//13us  @ 50MHz
`define RD_END_T    16'hFA0	//80us  @ 50MHz
`define BIT_DELAY   16'hDAC	//70us  @ 50MHz
`define BYTE_DELAY  16'h618A	//500us @ 50MHz

module DS18B20_CTL
	(
	//Global input ports.
	SYSCLK,
	RST_B,
	
	//TEMP ports.
	TEMP_IO,
	
	//Output ports.
	TEMP_D1,
	TEMP_D2
	);
	
//===========================================================================
//Input and output declaration.
//===========================================================================

input		SYSCLK;
input		RST_B;

inout		TEMP_IO;

output	[7:0]	TEMP_D1;
output	[7:0]	TEMP_D2;

//===========================================================================
//Wire and reg declaration.
//===========================================================================

wire		SYSCLK;
wire		RST_B;
wire		TEMP_IO;

reg	[7:0]	TEMP_D1;
reg	[7:0]	TEMP_D2;


//===========================================================================
//Wire and reg in the module.
//===========================================================================

//Used for bit control.
reg	[3:0]	BIT_CS;
reg	[3:0]	BIT_NS;

parameter	BIT_IDLE  = 4'h0;
parameter	BIT_INIT  = 4'h1;
parameter	BIT_READ  = 4'h2;
parameter	BIT_WRITE = 4'h3;
parameter	BIT_DELAY = 4'h4;
parameter	BIT_END	  = 4'h5;

reg	[15:0]	TIME_CNT;
reg	[15:0]	TIME_CNT_N;

reg	[1:0]	TEMP_IOREG;
reg	[1:0]	TEMP_IOREG_N;

reg		TEMP_IO_FLAG;

parameter	SET0 = 2'h0;
parameter	SET1 = 2'h1;
parameter	SETZ = 2'h2;
parameter	NSET = 2'h3;

wire		CMD_INIT;
wire		CMD_READ;
wire		CMD_WRITE;

//Used for byte control.
parameter	BYTE_IDLE  = 4'h0;
parameter	BYTE_INIT  = 4'h1;
parameter	BYTE_READ  = 4'h2;
parameter	BYTE_WRITE = 4'h3;
parameter	BYTE_DELAY = 4'h4;
parameter	BYTE_END   = 4'h5;

reg	[3:0]	BYTE_CS;
reg	[3:0]	BYTE_NS;

wire	[2:0]	CTL_FLAG;
reg	[2:0]	CTL_FLAG_N;

reg	[3:0]	BIT_CNT;
reg	[3:0]	BIT_CNT_N;

reg	[7:0]	SHIFT_REG_IO;
reg	[7:0]	SHIFT_REG_IO_N;
/*
//Used for flow control.
parameter	FLOW_IDLE  = 4'h0;
parameter	FLOW_INIT  = 4'h1;
parameter	FLOW_START = 4'h2;
parameter	FLOW_POLL  = 4'h3;
*/
parameter	FLAG_IDLE  = 3'h0;
parameter	FLAG_INIT  = 3'h1;
parameter	FLAG_READ  = 3'h2;
parameter	FLAG_WRITE = 3'h3;
parameter	FLAG_DELAY = 3'h4;

reg	[3:0]	FLOW_CS;
reg	[3:0]	FLOW_NS;
	
reg	[4:0]	BYTE_CNT;
reg	[4:0]	BYTE_CNT_N;

wire	[7:0]	TEMP_DI;

reg	[7:0]	TEMP_D1_N;
reg	[7:0]	TEMP_D2_N;

	
//===========================================================================
//Bit Control Logic.
//===========================================================================

//----------------------------------------------------------------------------
//Some control single of Bit control logic.
//----------------------------------------------------------------------------

//Command of input by outside.
assign CMD_INIT	 = (BYTE_CS == BYTE_INIT);
assign CMD_READ	 = (BYTE_CS == BYTE_READ);
assign CMD_WRITE = (BYTE_CS == BYTE_WRITE);

//TIME_CNT, time count for timing of TEMP.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    TIME_CNT	<= `UD 16'h0;
  else
    TIME_CNT	<= `UD TIME_CNT_N;
end

always @ (*)
begin
  if((BIT_CS != BIT_NS) || (BYTE_CS != BYTE_NS))
    TIME_CNT_N	 = 16'h0;
  else
    TIME_CNT_N   = TIME_CNT + 16'h1;
end

//----------------------------------------------------------------------------
//State machine of Bit control logic.
//----------------------------------------------------------------------------

//Bit control state machine.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    BIT_CS	<= `UD BIT_IDLE;
  else
    BIT_CS	<= `UD BIT_NS;
end

always @ (*)
begin
  case(BIT_CS)
    BIT_IDLE   	:  	if(CMD_INIT)
    			  BIT_NS = BIT_INIT;
    	      		else if(CMD_READ)
	    	          BIT_NS = BIT_READ;
	    	      	else if(CMD_WRITE)
	    		  BIT_NS = BIT_WRITE;
	    	      	else
	    	          BIT_NS = BIT_CS;
	    	       
    BIT_INIT	:	if(TIME_CNT == `INIT_END_T)
    			  BIT_NS = BIT_DELAY;
    			else
    			  BIT_NS = BIT_CS;
	    	       
    BIT_READ	:	if(TIME_CNT == `RD_END_T)
    			  BIT_NS = BIT_DELAY;
    			else
    			  BIT_NS = BIT_CS;
    			  	    	       
    BIT_WRITE	:	if(TIME_CNT == `WR_END_T)
    			  BIT_NS = BIT_DELAY;
    			else
    			  BIT_NS = BIT_CS;

    BIT_DELAY   :       if(TIME_CNT == `BIT_DELAY)
    			  BIT_NS = BIT_END;
    			else
    			  BIT_NS = BIT_CS;
    			  	    	       
    BIT_END	:	  BIT_NS = BIT_IDLE;
    default	:	  BIT_NS = BIT_IDLE;
  endcase
end

//---------------------------------------------------------------------------
//18B20 output bit control.
//---------------------------------------------------------------------------

//TEMP_IO, this is a tri-state io connect to 18B20.
//But it need a register for save the current time, otherwise latch.
//First, Register is 2bit , 2'h0 for 0 , 2'h1 for 1, 2'h2 for z.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    TEMP_IOREG	<= `UD SETZ;
  else
    TEMP_IOREG <= `UD TEMP_IOREG_N;
end
   
always @ (*)
begin
  case(BIT_CS)
    BIT_IDLE   	:  	TEMP_IOREG_N = SETZ;
	    	       
    BIT_INIT	:	if(TIME_CNT == `ALL_CLEAR_T)
    			  TEMP_IOREG_N = SET0;
    			else if(TIME_CNT == `INIT_SETZ_T)
    			  TEMP_IOREG_N = SETZ;
    			else 
    			  TEMP_IOREG_N = TEMP_IOREG;
	    	       
    BIT_READ	:	if(TIME_CNT == `ALL_CLEAR_T)
    			  TEMP_IOREG_N = SET0;
    			else if(TIME_CNT == `RD_SETZ_T)
    			  TEMP_IOREG_N = SETZ;
    			else 
    			  TEMP_IOREG_N = TEMP_IOREG;
    			  	    	       
    BIT_WRITE	:	if(TIME_CNT == `ALL_CLEAR_T)
    			  TEMP_IOREG_N = SET0;
    			else if(TIME_CNT == `WR_SETVAL_T)
    			  TEMP_IOREG_N = NSET;
    			else  if(TIME_CNT == `WR_SETZ_T)
    			  TEMP_IOREG_N = SETZ;
    			else
    			  TEMP_IOREG_N = TEMP_IOREG;

    default	:	  TEMP_IOREG_N = TEMP_IOREG;
  endcase
end

//Second, set the value of 18B20_I0.
always @ (*)
begin
  case(TEMP_IOREG)
    SET0	:	TEMP_IO_FLAG = 1'h0;
    SET1	:	TEMP_IO_FLAG = 1'h1;
    SETZ	:	TEMP_IO_FLAG = 1'hz;
    NSET	:	TEMP_IO_FLAG = SHIFT_REG_IO[0];
    default	:	TEMP_IO_FLAG = 1'hz;
  endcase
end

assign TEMP_IO = (TEMP_IOREG == SETZ) ? 1'hz : TEMP_IO_FLAG;
	         

//===========================================================================
//Byte control logic.
//===========================================================================
    			      			  
//---------------------------------------------------------------------------
//Some control singles.
//---------------------------------------------------------------------------


//Bit control, count when every bit end.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    BIT_CNT	<= `UD 4'h0;
  else
    BIT_CNT	<= `UD BIT_CNT_N;
end

always @ (*)
begin
  if(BYTE_CS == BYTE_IDLE)
    BIT_CNT_N	=  4'h0;
  else if(BIT_CS == BIT_END)
    BIT_CNT_N	=  BIT_CNT + 4'h1;
  else
    BIT_CNT_N	=  BIT_CNT;
end  


//Shift reg for read/write the TEMP.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    SHIFT_REG_IO <= `UD 8'h0;
  else
    SHIFT_REG_IO <= `UD SHIFT_REG_IO_N;
end

always @ (*)
begin
  if((BYTE_CS == BYTE_IDLE) && (BYTE_NS == BYTE_READ))
    SHIFT_REG_IO_N  = 8'h0;
  else if((BYTE_CS == BYTE_READ) && (BIT_CS == BIT_READ) && (TIME_CNT == `RD_SAMP_T))
    SHIFT_REG_IO_N  = {TEMP_IO /*1'h1*/ , SHIFT_REG_IO[7:1]};
  else if((BYTE_CS == BYTE_IDLE) && (BYTE_NS == BYTE_WRITE))
    SHIFT_REG_IO_N  = TEMP_DI;
  else if((BYTE_CS == BYTE_WRITE) && (BIT_CS == BIT_END))
    SHIFT_REG_IO_N  = {1'h0,SHIFT_REG_IO[7:1]};
  else
    SHIFT_REG_IO_N  = SHIFT_REG_IO;
end

    

//---------------------------------------------------------------------------
//Byte control state machine.
//---------------------------------------------------------------------------

//State machine.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    BYTE_CS	<= `UD BYTE_IDLE;
  else
    BYTE_CS	<= `UD BYTE_NS;
end

always @ (*)
begin
  case(BYTE_CS)
    BYTE_IDLE    :	if(CTL_FLAG == FLAG_INIT)
    			  BYTE_NS = BYTE_INIT;
    			else if(CTL_FLAG == FLAG_READ)
    			  BYTE_NS = BYTE_READ;
    			else if(CTL_FLAG == FLAG_WRITE)
    			  BYTE_NS = BYTE_WRITE;
		  	else if(CTL_FLAG == FLAG_DELAY)
    			  BYTE_NS = BYTE_DELAY;
    			else
    			  BYTE_NS = BYTE_CS;
    
    BYTE_INIT	 :	if(BIT_CS == BIT_END)
    			  BYTE_NS = BYTE_END;
    			else
    			  BYTE_NS = BYTE_CS;
    			  
    BYTE_READ	 :	if((BIT_CNT == 4'h7) && (BIT_CS == BIT_END))
    			  BYTE_NS = BYTE_DELAY;
    			else
    			  BYTE_NS = BYTE_CS;

    BYTE_WRITE	 :	if((BIT_CNT == 4'h7) && (BIT_CS == BIT_END))
    			  BYTE_NS = BYTE_END;
    			else
    			  BYTE_NS = BYTE_CS;

    BYTE_DELAY	 :	if(TIME_CNT == `BYTE_DELAY)
    			  BYTE_NS = BYTE_END;
    			else
    			  BYTE_NS = BYTE_CS;

    BYTE_END	 :	BYTE_NS = BYTE_IDLE;
    default	 :	BYTE_NS = BYTE_IDLE;
  endcase
end  

//============================================================================
//Flow control.
//============================================================================

//----------------------------------------------------------------------------
//Some control single for flow control.
//----------------------------------------------------------------------------

//Byte count, count when every byte end.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    BYTE_CNT	<= `UD 5'h0;
  else
    BYTE_CNT	<= `UD BYTE_CNT_N;
end

always @ (*)
begin
  if(FLOW_CS != FLOW_NS)
    BYTE_CNT_N	=  5'h0;
  else if(BYTE_CS == BYTE_END)
    BYTE_CNT_N	=  BYTE_CNT + 5'h1;
  else
    BYTE_CNT_N	=  BYTE_CNT;
end

//---------------------------------------------------------------------------
//Flow control state machine.
//---------------------------------------------------------------------------

//parameter	FLOW_IDLE  = 4'h0;
//parameter	FLOW_INIT  = 4'h1;
//parameter	FLOW_START = 4'h2;
//parameter	FLOW_POLL  = 4'h3;

parameter	FLOW_IDLE	= 4'h0;
parameter	FLOW_1_INIT	= 4'h1;
parameter	FLOW_2_CMD	= 4'h2;
parameter	FLOW_3_DELAY	= 4'h3;
parameter	FLOW_4_CMD	= 4'h4;
parameter	FLOW_5_INIT	= 4'h5;
parameter	FLOW_6_CMD	= 4'h6;
parameter	FLOW_7_DELAY	= 4'h7;
parameter	FLOW_8_CMD	= 4'h8;
parameter	FLOW_9_DELAY	= 4'h9;
parameter	FLOW_A_RD_D1	= 4'hA;
parameter	FLOW_B_DELAY	= 4'hB;
parameter	FLOW_C_RD_D2	= 4'hC;
parameter	FLOW_D_DELAY	= 4'hD;
parameter	FLOW_E_END	= 4'hE;


//State machine.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    FLOW_CS	<= `UD FLOW_IDLE;
  else
    FLOW_CS	<= `UD FLOW_NS;
end

always @ (*)
begin
  case(FLOW_CS)
    FLOW_IDLE	:	FLOW_NS = FLOW_1_INIT;

    FLOW_1_INIT	:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_2_CMD;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_2_CMD	:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_3_DELAY;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_3_DELAY:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_4_CMD;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_4_CMD	:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_5_INIT;
		        else
			  FLOW_NS = FLOW_CS;


    FLOW_5_INIT	:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_6_CMD;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_6_CMD	:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_7_DELAY;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_7_DELAY:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_8_CMD;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_8_CMD	:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_9_DELAY;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_9_DELAY:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_A_RD_D1;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_A_RD_D1:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_B_DELAY;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_B_DELAY:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_C_RD_D2;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_C_RD_D2:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_D_DELAY;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_D_DELAY:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_E_END;
		        else
			  FLOW_NS = FLOW_CS;

    FLOW_E_END	:	if(BYTE_CS == BYTE_IDLE)
			  FLOW_NS = FLOW_IDLE;
		        else
			  FLOW_NS = FLOW_CS;

    default	:	FLOW_NS = FLOW_IDLE;
  endcase
end

//---------------------------------------------------------------------------
//State control output, only delay/read/write/init for states.
//---------------------------------------------------------------------------


reg	[10:0]	BYTE_STATUS;

assign	CTL_FLAG = BYTE_STATUS[10:8];
assign	TEMP_DI  = BYTE_STATUS[7:0];

always @ (*)
begin
  case(FLOW_CS) 
    FLOW_IDLE	 : BYTE_STATUS = {FLAG_IDLE	, 8'h00};
    FLOW_1_INIT	 : BYTE_STATUS = {FLAG_INIT	, 8'h00};
    FLOW_2_CMD	 : BYTE_STATUS = {FLAG_WRITE	, 8'hCC};
    FLOW_3_DELAY : BYTE_STATUS = {FLAG_DELAY	, 8'h00};
    FLOW_4_CMD	 : BYTE_STATUS = {FLAG_WRITE	, 8'h44};
    FLOW_5_INIT	 : BYTE_STATUS = {FLAG_INIT	, 8'h00};
    FLOW_6_CMD	 : BYTE_STATUS = {FLAG_WRITE	, 8'hCC};
    FLOW_7_DELAY : BYTE_STATUS = {FLAG_DELAY	, 8'h00};
    FLOW_8_CMD	 : BYTE_STATUS = {FLAG_WRITE	, 8'hBE};
    FLOW_9_DELAY : BYTE_STATUS = {FLAG_DELAY	, 8'h00};
    FLOW_A_RD_D1 : BYTE_STATUS = {FLAG_READ	, 8'h00};
    FLOW_B_DELAY : BYTE_STATUS = {FLAG_DELAY	, 8'h00};
    FLOW_C_RD_D2 : BYTE_STATUS = {FLAG_READ	, 8'h00};
    FLOW_D_DELAY : BYTE_STATUS = {FLAG_DELAY	, 8'h00};
    FLOW_E_END	 : BYTE_STATUS = {FLAG_IDLE	, 8'h00};
    default	 : BYTE_STATUS = {FLAG_IDLE	, 8'h00};
  endcase
end


//===========================================================================
//Output control, first and second data in the 18B20
//===========================================================================

//Ram data 1, TEMP_D1.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    TEMP_D1	<= `UD 8'h0;
  else
    TEMP_D1	<= `UD TEMP_D1_N;
end

always @ (*)
begin
  if((FLOW_CS == FLOW_B_DELAY) && (BYTE_CS == BYTE_IDLE))
    TEMP_D1_N	 = SHIFT_REG_IO;
  else
    TEMP_D1_N	 = TEMP_D1;
end

//Ram data 2, TEMP_D2.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    TEMP_D2	<= `UD 8'h0;
  else
    TEMP_D2	<= `UD TEMP_D2_N;
end

always @ (*)
begin
  if((FLOW_CS == FLOW_D_DELAY) && (BYTE_CS == BYTE_IDLE))
    TEMP_D2_N	 = SHIFT_REG_IO;
  else
    TEMP_D2_N	 = TEMP_D2;
end


endmodule
