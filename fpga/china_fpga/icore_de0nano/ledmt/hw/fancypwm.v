`default_nettype none

module fancypwm(
	input wire CLOCK_50,
	output wire[7:0] LED,
	input wire[1:0] KEY,
	inout wire[33:0] top,
	input wire[1:0] top_IN	
);

wire CLOCK_200;

//`define test

`ifdef test
parameter b_17 = 18;
parameter b_11 = 6;
`else

parameter b_17 = 4;
parameter b_11 = 0;

`endif

// 17 =  190.73 Hz anim freq
// 11 =  12.21 kHz pwm clock
reg[b_17:0] slowclock;
mypll my_pll(CLOCK_50,CLOCK_200);

always@(posedge CLOCK_50) slowclock <= slowclock + 1;


wire load_rq;
wire[3:0] bit;
wire data_ready;
wire[7:0] led_bit_data;

reg[10:0] address;

initial begin
	slowclock = 0;
	address = 0;
end

loader my_loader(
	.clock(CLOCK_200),
	.bit(bit),
	.address(address),
	.load_rq(load_rq),
	.data_ready(data_ready),
	.data_out(led_bit_data)	
);


sequencer my_sequencer(
	.clock(slowclock[b_17]),
	.pwm_clock(slowclock[b_11]),
	
	.load_rq(load_rq),
	.bit(bit),
	
	.data_ready(data_ready),
	.data_in(led_bit_data),
	.data_out(LED)
);


always@(posedge slowclock[b_17]) address<= address + 8;


endmodule
