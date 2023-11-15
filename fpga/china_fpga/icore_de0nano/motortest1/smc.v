module smc
(
	input step,dir,
	output reg[1:0] mphase
);

reg[1:0] state;
always @(posedge step)
begin
if(dir)
	state <= state + 1;
	else
	state <= state - 1;
end

always@(*)
begin
	case(state)
		0: mphase = 2'b00;
		1: mphase = 2'b01;
		2: mphase = 2'b11;
		3: mphase = 2'b10;
	endcase
end

endmodule
