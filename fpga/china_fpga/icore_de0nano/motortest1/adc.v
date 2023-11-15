// reads first channel only

module adc
(

// internal interface
input clock,
output reg[11:0] data,

//adc pins
output CS_N,
output SADDR,
output SCLK,
input SDAT
);

reg[4:0] state;
reg cs;
reg din;

assign SADDR = din;
assign SCLK = ~cs & clock;

assign CS_N = cs;
always@(negedge clock)
begin
	case(state)
	0:cs <= 0;
	1: din <= 0;
	2: din <= 0;
	3: din <= 0;
	4: din <= 1;
	15:cs <= 1;
	endcase
	
	state <= state + 1;
end

always@(posedge clock)
begin
	case(state)
	4:data[11] = SDAT;
	5:data[10] = SDAT;
	6:data[9] = SDAT;
	7:data[8] = SDAT;
	8:data[7] = SDAT;
	9:data[6] = SDAT;
	10:data[5] = SDAT;
	11:data[4] = SDAT;
	12:data[3] = SDAT;
	13:data[2] = SDAT;
	14:data[1] = SDAT;
	15:data[01] = SDAT;
	endcase
end

endmodule
