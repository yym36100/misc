`default_nettype none
`timescale 10 ns / 10 ns

module ramtest(	
	CLOCK_50,	
	LED,	
	KEY,	
	top,
	top_IN 
);


input wire 	      CLOCK_50;
output wire	 [7:0]LED;
input wire 	 [1:0]KEY;
inout wire 	[33:0]top;
input wire 	 [1:0]top_IN;

reg[4:0] address;
wire clock = CLOCK_50;
wire [7:0] q;

assign LED = q;

simplerom my_rom(
	.address(address),
	.clock(clock),
	.q(q)
);

always@(posedge clock) begin
	address <= address + 1;
end

initial begin
	address  = 0;
end

endmodule
