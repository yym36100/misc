//==========================================================================
//Filename  :BUZZER_CTL.v
//modulename:BUZZER_CTL
//Author    :xp.wu
//Date	    :2009-9-25
//Function  :This is a buzzer contral module, when give a enable single,
//	     the buzzer will make a sound 100kHz. 
//Uesedfor  :Altera cyclon EP1C3T144C8, made by xsyan.
//==========================================================================

`define	UD #1

module	BUZZER_CTL
	(
	//Input ports.
	SYSCLK,
	RST_B,
	BUZZER_EN,

	//Output ports.
	BUZZER
	);

//==========================================================================
//Input and output declaration
//==========================================================================

input		SYSCLK;		//Free running clock, 50MHz.
input		RST_B;		//Global reset, low active.
input		BUZZER_EN;	//The enable of the buzzer.

output		BUZZER;		//BUZZER output, 400HZ.	

//==========================================================================
//Wire and reg declaration
//==========================================================================

wire		SYSCLK;
wire		RST_B;
wire		BUZZER_EN;

reg	     	BUZZER;

//==========================================================================
//Wire and reg in the module
//==========================================================================

reg	[23:0]	CLK_DIV_CNT;	//Count the clock for division clock.
reg	[23:0]	CLK_DIV_CNT_N;	//Next value of CLK_DIV_CNT.
reg		BUZZER_N;	//Next value of BUZZER.

//==========================================================================
//Logic
//==========================================================================

//First, Division the clock to 400 Hz.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    CLK_DIV_CNT	   <= `UD 24'h0;
  else
    CLK_DIV_CNT	   <= `UD CLK_DIV_CNT_N;
end

always @ (*)
begin
  if(CLK_DIV_CNT == 24'hF080)
    CLK_DIV_CNT_N   = 24'h0;
  else
    CLK_DIV_CNT_N   = CLK_DIV_CNT + 24'h1;
end

//Second, contral the output.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    BUZZER	   <= `UD 1'h1;
  else
    BUZZER	   <= `UD BUZZER_N;
end

always @ (*)
begin
  if((BUZZER_EN) && (CLK_DIV_CNT == 24'hF080))
    BUZZER_N	    = (~ BUZZER);
  else
    BUZZER_N	    = BUZZER;
end

endmodule
