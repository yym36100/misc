module fd48c(input[47:0] din,input clk,input aclr,output reg[47:0] dout);


always @(posedge clk, posedge aclr)
begin
	if(aclr)dout <= 0;
		else dout <= din;
end

endmodule
		