 `default_nettype none

module pwm3(
	input clock,
	input[15:0] duty,	
	output  out	
);

reg [15:0] cnt,n;
assign out = |(n & duty);



always@(posedge clock)
begin
	cnt <= cnt + 1;	
	 n = cnt;
	 n = n|(n >>  1);
    n = n|(n >>  2);
    n = n|(n >>  4);
    n = n|(n >>  8);    
    n = n - (n >> 1);
end

endmodule
 