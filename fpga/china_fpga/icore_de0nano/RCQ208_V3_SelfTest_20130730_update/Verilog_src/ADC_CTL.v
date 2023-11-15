//==========================================================================
//Filename  :ADC_2_SEQ.v
//modulename:ADC_2_SEQ
//Author    :xp.wu
//Date	    :2011-9-1
//Function  :This is a ADC control of TLC549 module which read the voltage 
//	    :and show on seq.
//Uesedfor  :RedCore_EP2C8Q_V1_EVB, made by redcore.
//Taobao    :http://redcore-1.taobao.com
//E-mail    :xingping99@163.com
//QQ	    :109019299
//==========================================================================

`define UD #1

module ADC_CTL
	(
	//Input ports.
	SYSCLK,
	RST_B,
	
	//ADC ports.
	ADC_CS,
	ADC_CLK,
	ADC_DAT,
	
	//ADC to nios ports.
	ADC_DATA_REC
	);
	
//============================================================================
//Input and output declaration.
//============================================================================

input		SYSCLK;
input		RST_B;

output		ADC_CLK;
input	[7:0]	ADC_DAT;
output		ADC_CS;

output	[7:0]	ADC_DATA_REC;

//============================================================================
//Wire and reg declaration.
//============================================================================

wire		SYSCLK;
wire		RST_B;

reg		ADC_CLK;
wire	[7:0]	ADC_DAT;
wire		ADC_CS;

//============================================================================
//Wire and reg in the module.
//============================================================================

reg	[7:0]	ADC_DATA_REC;
reg	[7:0]	ADC_DATA_REC_N;

wire		ADC_CLK_N;

reg	[23:0]	TIME_CNT;
wire	[23:0]	TIME_CNT_N;

	
//============================================================================
//Logic.
//============================================================================


//============================================================================
//ADC control.
//============================================================================

assign	ADC_CS = 1'h0;

always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    ADC_CLK	 <= `UD 1'h0;
  else
    ADC_CLK 	 <= `UD ADC_CLK_N;
end

assign	ADC_CLK_N = ~ ADC_CLK;


//Save the data read from ADC.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    ADC_DATA_REC <= `UD 8'h0;
  else
    ADC_DATA_REC <= `UD ADC_DATA_REC_N;
end

always @ (*)
begin
  if(TIME_CNT == 24'h0)
    ADC_DATA_REC_N = ADC_DAT;
  else
    ADC_DATA_REC_N = ADC_DATA_REC;
end

//TIME_CNT, Change the voltog on SEQ every 0.33s.
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
    TIME_CNT	 <= `UD 24'h0;
  else
    TIME_CNT	 <= `UD TIME_CNT_N;
end

assign	TIME_CNT_N = TIME_CNT + 24'h1;



endmodule



