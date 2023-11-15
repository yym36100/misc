`default_nettype none

module chinasound(
	input CLOCK_50,
	output[7:0] LED,
	input[1:0] KEY,
	inout[33:0] top,
	input[1:0] top_IN 
);

wire bitclock_x8;
reg[7:0] bitclock;
wire[15:0] data;
reg[7:0] sample_addr;

wire sample_clock = bitclock[7];
wire ms_clock = bitclock[4];

//wire dac_bitclock = bitclock[2];
//dac pins
wire dac_clk, dac_ws, dac_da;

assign top[0] = dac_clk;
assign top[1] = dac_da;
assign top[3] = dac_ws;

reg dbgled;
assign LED[0] = dbgled;
assign top[5] = dbgled;

wire[15:0] ms_data;

always@(posedge bitclock_x8) bitclock <= bitclock + 1;
always@(posedge sample_clock) sample_addr <= sample_addr + 6; 
always@(posedge bitclock_x8) dbgled <= ~dbgled;

wire [15:0] data_mux = KEY[0]? ms_data : data;

// inst
mypll mypll_inst(CLOCK_50, bitclock_x8); //11.29MHz
PT8211_DAC myPT8211_DAC(bitclock_x8 ,data_mux, dac_clk, dac_ws, dac_da);	
sample_rom mysample_rom(sample_addr, ~sample_clock, data);

multisample_x8(ms_clock,data,ms_data);


endmodule
