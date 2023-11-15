`default_nettype none

module pwm(
	input clock,
	input [19:0] duty,
	output pwm
	);

reg [19:0] counter = 0;

assign pwm = counter < duty ? 1 : 0;		

always @(posedge clock)
begin
	counter <= counter + 1;		
end
	
endmodule	
