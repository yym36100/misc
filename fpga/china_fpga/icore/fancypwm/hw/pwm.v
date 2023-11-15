`default_nettype none

module pwm(
	input clock,
	input[15:0] duty,
	
	output reg out	
);

reg [15:0] cnt;

always@(posedge clock)
begin
	cnt <= cnt + 1;
	if(cnt < duty)
		out <= 1;
	else
		out <= 0;
end

endmodule
 