`default_nettype none

module lcdtest(
	input CLOCK_50,
	output[7:0] LED,
	input[1:0] KEY,
	inout[33:0] top
);
`define RS	{top[9]}
`define RW  {top[11]}
`define E	{top[13]}
`define DB	{top[21],top[19],top[17],top[15],top[14],top[12],top[10],top[8]}

reg[31:0] slowclock;

always@(posedge CLOCK_50) begin
	if(KEY[0] == 0) slowclock <= 0;
	else slowclock <= slowclock + 1;
end

reg[7:0] state;
reg dbg;

assign LED[0] = dbg;

assign `RW = 0; // always write

wire[7:0]cnt = slowclock[15+1+7:15+1+0];

reg rRS,rE;
reg[7:0]rDB;

assign top[7] = rE;
assign `RS = rRS;
assign `E = rE;
assign `DB = rDB;
reg[7:0] dig1, dig2;
reg[9:0] cnt2;
reg[7:0]tstval;

wire[3:0] hundreds;
wire[3:0] tens;
wire[3:0] ones;
 
 bcd mybcd(
	 tstval,
	 hundreds,
	 tens,
	 ones
  );
	 
always@(posedge slowclock[15]/*1.31ms*/ ,negedge KEY[0]) begin
	if(KEY[0] == 0) begin
		dbg <= 0;
		state <= 0;		
		dig1 <='h30;
		dig2 <='h61;
	end else begin		
		case(state)
			0: // lcd init
			// delay 40ms
			// function set x 2 + onoff + clear + entry mode set			
			begin
				if(cnt == 31) state <= 1; // 40ms elapsed
			end			
			// function set x2
			1: begin state <= 2; rE <= 1; rRS <= 0; rDB <= 8'b001_110_00; end
			2: begin state <= 3; rE <= 0; end
			3: begin state <= 4; rE <= 1; rRS <= 0; rDB <= 8'b001_110_00; end
			4: begin state <= 5; rE <= 0; end			
			// disp on + cursor on + blink
			5: begin state <= 6; rE <= 1; rRS <= 0; rDB <= 8'b0000_1_111; end
			6: begin state <= 7; rE <= 0; end			
			// disp clear
			7: begin state <= 8; rE <= 1; rRS <= 0; rDB <= 8'b0000_0001; end
			8: begin state <= 9; rE <= 0; end			
			// entry mode set
			9: begin state <=10; rE <= 1; rRS <= 0; rDB <= 8'b0000_01_10; end
		  10: begin state <=11; rE <= 0; end
		  
		  // show some values
		  11: begin state <=12; rE <= 1; rRS <= 1; rDB <= 8'h31; end
		  12: begin state <=13; rE <= 0; end
		  
		  13: begin state <=14; rE <= 1; rRS <= 1; rDB <= 8'h32; end
		  14: begin state <=15; rE <= 0; end
		  
		  15: begin state <=16; rE <= 1; rRS <= 1; rDB <= 8'h33; end
		  16: begin state <=17; rE <= 0; end
		  
		  // move to next line
		  17: begin state <=18; rE <= 1; rRS <= 0; rDB <= 8'b1_100_0000; end
		  18: begin state <=19; rE <= 0; end
		  
		    // show some values
		  19: begin state <=20; rE <= 1; rRS <= 1; rDB <= 8'h41; end
		  20: begin state <=21; rE <= 0; end
		  21: begin state <=22; rE <= 1; rRS <= 1; rDB <= 8'h42; end
		  22: begin state <=23; rE <= 0; end
		  23: begin state <=24; rE <= 1; rRS <= 1; rDB <= 8'h43; end
		  24: begin state <=25; rE <= 0; end
		  
		  25: begin state <=26; rE <= 1; rRS <= 1; rDB <= 8'h20; end // space
		  26: begin state <=27; rE <= 0; end
		  
		  27: begin state <=28; rE <= 1; rRS <= 1; rDB <= dig1; end
		  28: begin state <=29; rE <= 0; end
		  29: begin state <=30; rE <= 1; rRS <= 1; rDB <= dig2; end
		  30: begin state <=31; rE <= 0; cnt2<=0; end
		  
		  31: begin state <=32; rE <= 1; rRS <= 1; rDB <= 8'h20; end // space
		  32: begin state <=33; rE <= 0; end
		  
		  33: begin state <=34; rE <= 1; rRS <= 1; rDB <= hundreds + 'h30; end
		  34: begin state <=35; rE <= 0; end
		  35: begin state <=36; rE <= 1; rRS <= 1; rDB <= tens + 'h30; end
		  36: begin state <=37; rE <= 0; cnt2<=0; end
		  37: begin state <=38; rE <= 1; rRS <= 1; rDB <= ones + 'h30; end
		  38: begin state <=39; rE <= 0; cnt2<=0; end
		  
		  
		  39: //wait some time
			begin
				if(cnt2==763) begin
					cnt2<=0;
					tstval = tstval + 1;
					
					dig1 = tstval[7:4];
					dig2 = tstval[3:0];
					
					if(dig1 >= 10) dig1 = dig1 + 'h61-10;
						else dig1 = dig1 + 'h30;
						
					if(dig2 >= 10) dig2 = dig2 + 'h61-10;
						else dig2 = dig2 + 'h30;
					
					state<=17;
				end else begin
					cnt2<= cnt2 + 1;
				end
			end
			
			default: begin rE <= 0; end
		endcase
	end

end

endmodule

// http://www.eng.utah.edu/~nmcdonal/Tutorials/BCDTutorial/BCDConversion.html
// also here http://www.tkt.cs.tut.fi/kurssit/1426/S12/Ex/ex4/Binary2BCD.pdf

module bcd (
    input [7:0] binary,
    output reg [3:0] hundreds,
    output reg [3:0] tens,
    output reg [3:0] ones);

integer i;
always @(binary) begin
    // set 100's, 10's, and 1's to zero
    hundreds = 4'd0;
    tens = 4'd0;
    ones = 4'd0;

    for (i=7; i>=0; i=i-1) begin
        // add 3 to columns >= 5
        if (hundreds >= 5)
            hundreds = hundreds + 3;
        if (tens >= 5)
            tens = tens + 3;
        if (ones >= 5)
            ones = ones + 3;

        // shift left one
        hundreds = hundreds << 1;
        hundreds[0] = tens[3];
        tens = tens << 1;
        tens[0] = ones[3];
        ones = ones << 1;
        ones[0] = binary[i];
    end
end
endmodule
