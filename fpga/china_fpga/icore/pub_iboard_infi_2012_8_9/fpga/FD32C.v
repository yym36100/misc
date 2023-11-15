module fd32c(input[31:0] din,input clk,input aclr,output reg[31:0] dout);


always @(posedge clk, posedge aclr)
begin
	if(aclr)dout <= 0;
		else dout <= din;
end

endmodule
		