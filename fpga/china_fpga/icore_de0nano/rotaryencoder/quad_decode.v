`default_nettype none

module quad
#(parameter CNT_WIDTH=8)
(
	input clk,
	input quadA,
	input quadB,
	output[CNT_WIDTH-1:0]count,
	output reg dir
);

wire count_enable = quadA ^ quadA_delayed ^ quadB ^ quadB_delayed;
wire count_direction = quadA ^ quadB_delayed;

reg quadA_delayed, quadB_delayed;
reg[CNT_WIDTH:0] icount;

assign count = icount[CNT_WIDTH:1];

always @(posedge clk)
begin
	quadA_delayed <= quadA;
	quadB_delayed <= quadB;

  if(count_enable)
  begin
    if(count_direction) 
		begin
		dir <= 1;
		icount <= icount+1;
		end
	else 
		begin
		dir <= 0;
		icount <= icount-1;
		end
  end
end

endmodule
