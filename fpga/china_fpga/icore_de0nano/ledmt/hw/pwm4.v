 `default_nettype none

module pwm4(
	input clock,
	input[15:0] duty,
	
	output reg out	
);

reg [15:0] cnt;

always@(posedge clock)
begin
	cnt <= cnt + 1;
	if(cnt[15]) out <= duty[15];
	else if(cnt[14]) out <= duty[14];
	else if(cnt[13]) out <= duty[13];
	else if(cnt[12]) out <= duty[12];
	else if(cnt[11]) out <= duty[11];
	else if(cnt[10]) out <= duty[10];
	else if(cnt[9]) out <= duty[9];
	else if(cnt[8]) out <= duty[8];
	else if(cnt[7]) out <= duty[7];
	else if(cnt[6]) out <= duty[6];
	else if(cnt[5]) out <= duty[5];
	else if(cnt[4]) out <= duty[4];
	else if(cnt[3]) out <= duty[3];
	else if(cnt[2]) out <= duty[2];
	else if(cnt[1]) out <= duty[1];
	else if(cnt[0]) out <= duty[0];
	else out<= 0;
end

endmodule
 