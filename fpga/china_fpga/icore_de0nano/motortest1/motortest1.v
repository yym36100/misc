/*
TOP 027 A
TOP 029 B
TOP 031 BN
TOP 033 AN
*/

module motortest1(

	//////////// CLOCK //////////
	CLOCK_50,

	//////////// LED //////////
	LED,

	//////////// KEY //////////
	KEY,

	//////////// SW //////////
	SW,

	//////////// SDRAM //////////
	DRAM_ADDR,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_CKE,
	DRAM_CLK,
	DRAM_CS_N,
	DRAM_DQ,
	DRAM_DQM,
	DRAM_RAS_N,
	DRAM_WE_N,

	//////////// EPCS //////////
	EPCS_ASDO,
	EPCS_DATA0,
	EPCS_DCLK,
	EPCS_NCSO,

	//////////// Accelerometer and EEPROM //////////
	G_SENSOR_CS_N,
	G_SENSOR_INT,
	I2C_SCLK,
	I2C_SDAT,

	//////////// ADC //////////
	ADC_CS_N,
	ADC_SADDR,
	ADC_SCLK,
	ADC_SDAT,

	//////////// 2x13 GPIO Header //////////
	GPIO_2,
	GPIO_2_IN,

	//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
	top,
	top_IN,

	//////////// GPIO_1, GPIO_1 connect to GPIO Default //////////
	bottom,
	bottom_IN 
);

//=======================================================
//  PARAMETER declarations
//=======================================================


//=======================================================
//  PORT declarations
//=======================================================

//////////// CLOCK //////////
input 		          		CLOCK_50;

//////////// LED //////////
output		     [7:0]		LED;

//////////// KEY //////////
input 		     [1:0]		KEY;

//////////// SW //////////
input 		     [3:0]		SW;

//////////// SDRAM //////////
output		    [12:0]		DRAM_ADDR;
output		     [1:0]		DRAM_BA;
output		          		DRAM_CAS_N;
output		          		DRAM_CKE;
output		          		DRAM_CLK;
output		          		DRAM_CS_N;
inout 		    [15:0]		DRAM_DQ;
output		     [1:0]		DRAM_DQM;
output		          		DRAM_RAS_N;
output		          		DRAM_WE_N;

//////////// EPCS //////////
output		          		EPCS_ASDO;
input 		          		EPCS_DATA0;
output		          		EPCS_DCLK;
output		          		EPCS_NCSO;

//////////// Accelerometer and EEPROM //////////
output		          		G_SENSOR_CS_N;
input 		          		G_SENSOR_INT;
output		          		I2C_SCLK;
inout 		          		I2C_SDAT;

//////////// ADC //////////
output		          		ADC_CS_N;
output		          		ADC_SADDR;
output		          		ADC_SCLK;
input 		          		ADC_SDAT;

//////////// 2x13 GPIO Header //////////
inout 		    [12:0]		GPIO_2;
input 		     [2:0]		GPIO_2_IN;

//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
inout 		    [33:0]		top;
input 		     [1:0]		top_IN;

//////////// GPIO_1, GPIO_1 connect to GPIO Default //////////
inout 		    [33:0]		bottom;
input 		     [1:0]		bottom_IN;


//=======================================================
//  REG/WIRE declarations
//=======================================================




//=======================================================
//  Structural coding
//=======================================================

wire slowclock;
wire[1:0] phase;
wire dir;

reg[31:0] cnt;

always @(posedge CLOCK_50)
begin
	cnt<=cnt+1;
end

assign slowclock = cnt[17];
assign LED[0] = slowclock;
assign dir = cnt[27];
assign LED[7:1] = adc_data[11:4];

smc mysmc(slowclock,dir,phase);

wire[11:0] adc_data;
adc myadc(
	cnt[0],
	adc_data,
	
	ADC_CS_N,
	ADC_SADDR,
	ADC_SCLK,
	ADC_SDAT	
	);

//phase a
assign top[27] = phase[0];
assign top[33] = ~phase[0];

//phase b
assign top[29] = phase[1];
assign top[31] = ~phase[1];


endmodule
