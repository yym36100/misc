module fdc(input din,input clk,input aclr,output reg dout);


always @(posedge clk, posedge aclr)
begin
	if(aclr)dout <= 0;
		else dout <= din;
end

endmodule
		