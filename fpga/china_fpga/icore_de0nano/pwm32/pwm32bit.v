//pwm32bit
`default_nettype none


module pwm32bit(
	input rst,
	input clock,
	input [31:0] duty,
	output pwm
	);

reg [31:0] counter;
	
always @(posedge clock)
begin
	if(rst == 1) begin
		counter <= 0;
	end else begin
		counter <= counter + 1;		
	end

end

assign pwm = counter < duty ? 0 : 1;	
	
endmodule	