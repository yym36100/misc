`default_nettype none

 module blinky
(
	input FPGA_CLK2,	
	output LED_FPGA2,
	output[2:0] LED_RGB,
	
	// FSMC interface
	input[2:0] AB,
	inout[15:0] DB,
	
	input CS0,
	input RD,
	input WR
	
);

//wire clock_100;
//mypll mypll1(FPGA_CLK2,clock_100);

//pwm pwm1(clock_100,1048570*rgb_cnt[0],LED_RGB[0]);
//pwm pwm2(clock_100,1048570*rgb_cnt[1],LED_RGB[1]);
//pwm pwm3(clock_100,1048570*rgb_cnt[2],LED_RGB[2]);

reg[15:0] reg1 = 0;
wire enable, ew, er;

assign enable = (CS0 == 0) && (AB == 0);
assign ew = enable && (WR==0);
assign er = enable && (RD==0);

assign LED_RGB[0] = reg1[15];
assign LED_RGB[1] = reg1[14];
assign LED_RGB[2] = reg1[13];


always@(posedge ew)
begin
		reg1 <= DB;
end

assign DB = er ? reg1 : 16'bz;

/*
reg[22:0] slowclock = 0;
reg led = 0;

reg[2:0] rgb_cnt = 0;

assign LED_FPGA2 = led;
//assign LED_RGB = rgb_cnt;

always@(posedge FPGA_CLK2)
begin
	if(slowclock == 2500000)
		begin
			slowclock <= 0;
			led <= led ^ 1;		
			rgb_cnt <= rgb_cnt + 1;
		end
	else
		begin
			slowclock <= slowclock + 1;
		end
		
end
*/
endmodule
