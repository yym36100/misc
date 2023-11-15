 
module szamlalo (
		orajel,
		kimenet
);

input orajel ;
output [31:0] kimenet;
reg [31:0] kimenet;

always @ (posedge orajel)
	begin
		kimenet <= kimenet * (kimenet-3);
	end
	
endmodule
