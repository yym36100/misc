`default_nettype none

module rotaryencoder(
	input CLOCK_50,
	output[7:0] LED,
	inout[33:0] top,
	input[1:0] top_IN 
);

wire enc_a;
wire enc_b;

// encoder connection
assign enc_a = top[25];
assign enc_b = top[27];

reg[15:0] slowclock;

always@ (posedge CLOCK_50)
begin
	slowclock <= slowclock + 1;
end

wire [8:0] dummy;
assign LED = dummy[8:1];
quad #(9) myquad(slowclock[15],enc_a,enc_b,dummy);
endmodule

