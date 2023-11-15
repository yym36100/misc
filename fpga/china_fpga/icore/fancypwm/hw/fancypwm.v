`default_nettype none

module fancypwm(
	input CLOCK_50,
	output [7:0] LED,
	input[1:0] KEY,
	inout[33:0] top,
	input[1:0] top_IN	
);

reg[31:0] slowclock;
always@(posedge CLOCK_50) slowclock <= slowclock + 1;

reg[7:0] pwmduty_addr;
wire[15:0] pwmduty_val;


wire o1,o2,o3,o4;

rom_cie myrom(pwmduty_addr,slowclock[17],pwmduty_val);


pwm mypwm1(slowclock[2],pwmduty_val,o1);
pwm2 mypwm2(slowclock[2],pwmduty_val,o2);
pwm3 mypwm3(slowclock[2],pwmduty_val,o3);
pwm4 mypwm4(slowclock[2],pwmduty_val,o4);

/*
pwm2 mypwm5(slowclock[2],pwmduty_val/8,LED[3]);
pwm2 mypwm6(slowclock[2],pwmduty_val/16,LED[4]);
pwm2 mypwm7(slowclock[2],pwmduty_val/32,LED[5]);
pwm2 mypwm8(slowclock[2],pwmduty_val/64,LED[6]);
pwm2 mypwm9(slowclock[2],pwmduty_val/128,LED[7]);
*/


always@(posedge slowclock[20])
begin
	pwmduty_addr <= pwmduty_addr + 1;
end


assign LED[0] = o1;
assign LED[1] = o2;
assign LED[2] = o3;
assign LED[3] = o4;

assign top[31] = o1;
assign top[33] = o2;
assign top[29] = o4;

endmodule
