module ledmatrixtest(
	input clock,
	
	//external pin interfaces
	output r1,r2,g1,g2,b1,b2,
	output a,b,c,d,
	output oe,latch, clk
);

assign clk = clock;

wire out;
assign r1=out;

ledmx_line my_ledline(
	clock,
	out,
	oe,latch
);

reg[3:0] line;

assign a = line[0];
assign b = line[1];
assign c = line[2];
assign d = line[3];

always@(negedge clock)
begin
	reg[4:0] cnt;
	
	cnt <= cnt + 1;
	if(cnt == 9)
		begin
			cnt <= 0;
			
			//switch line
			line <= line + 1;
			
		end
	
end

endmodule

//--------------------------------------------------------
module ledmx_line(
	input clock,
	
	//external pin interfaces
	output reg out,
	output reg oe,latch
);

assign clk = clock;

always@(negedge clock)
begin
	reg[3:0] cnt;
	cnt <= cnt + 1;
	
	case(cnt)
		0: out <= 1;
		1: out <= 0;
		2: out <= 1;
		3: out <= 0;
		4: out <= 1;
		5: out <= 0;
		6: out <= 1;
		7: out <= 0;
		
		8: latch <= 1;
		9: begin latch <= 0; cnt<=0; end
	endcase
	
end

endmodule


