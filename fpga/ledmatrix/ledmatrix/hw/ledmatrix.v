module ledmatrix(
	input RST_B,
	input SYSCLK,
	input[6:0] KEY,
	output[5:0] LED_DATA,
	output BUZZER_OUT
);

wire r1,r2,g1,g2,b1,b2;
wire a,b,c,d;
wire  oe,latch, clk;

ledmatrixtest test_inst(
	SYSCLK,
	
	r1,r2,g1,g2,b1,b2,
	a,b,c,d,
   oe,latch, clk,	
);


endmodule
