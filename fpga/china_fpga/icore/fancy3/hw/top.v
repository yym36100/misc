module top(
	input RST_B,
	input SYSCLK,
	input[6:0] KEY,
	output[5:0] LED_DATA,
	output BUZZER_OUT,
	output dbg
);

assign BUZZER_OUT = 0;
assign LED_DATA[5:1] = 5'b11111;
wire dummy;
assign dbg = LED_DATA[0];

reg [10:0] slowclock;
reg [15:0] duty;

always@(posedge SYSCLK) slowclock <= slowclock +11'b1;
always@(posedge slowclock[10]) duty <= duty + 16'b1;

pwm4 my_pwm(SYSCLK,KEY,duty,dummy,LED_DATA[0]);

endmodule
