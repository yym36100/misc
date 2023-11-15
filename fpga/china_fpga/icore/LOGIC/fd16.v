module fd16(
	input[15:0] d,
	input clk,
	output reg[15:0] q
	);
	
always @(posedge clk )
	q <= d;

endmodule
