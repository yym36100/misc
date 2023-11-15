`default_nettype none

module multisample_x8(
	input clock,
	input signed[15:0] data_in,
	output reg signed[15:0] data_out
);

reg[2:0] index;
reg signed[15:0] memory[7:0];
always@(posedge clock)
begin
	index <= index + 1;
	memory[index] <= data_in / 8;
	data_out <= memory[0] + memory[1] + memory[2] + memory[3] +
					memory[4] + memory[5] + memory[6] + memory[7];
end

endmodule
