`default_nettype none

module pwm2(
	input clock,
	input[15:0] duty,
	
	output reg out	
);

reg [15:0] cnt;

always@(posedge clock)
begin
	cnt <= cnt + 1;
	if     (cnt<2**0) out = 0;
	else if(cnt<2**1) out = duty[0];
	else if(cnt<2**2) out = duty[1];
	else if(cnt<2**3) out = duty[2];
	else if(cnt<2**4) out = duty[3];
	else if(cnt<2**5) out = duty[4];
	else if(cnt<2**6) out = duty[5];
	else if(cnt<2**7) out = duty[6];
	else if(cnt<2**8) out = duty[7];
	else if(cnt<2**9) out = duty[8];
	else if(cnt<2**10) out = duty[9];
	else if(cnt<2**11) out = duty[10];
	else if(cnt<2**12) out = duty[11];
	else if(cnt<2**13) out = duty[12];
	else if(cnt<2**14) out = duty[13];
	else if(cnt<2**15)out = duty[14];
	else out = duty[15];
	
end

endmodule
 