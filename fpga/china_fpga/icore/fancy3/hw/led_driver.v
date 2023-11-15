 `default_nettype none
 `timescale 10 ns / 10 ns
 
module led_driver(
	input wire clock,
	input wire si,
	input wire oe,
	input wire ltch,
	output wire [7:0] out
);

reg[7:0] data;
reg[7:0] outdata;

assign out = oe?outdata:8'b0;

always@(ltch) begin
	if(ltch)
		outdata <= data;
end

always@(posedge clock) begin
	if(~ltch)
	data <= {si,data[7:1]};
end

initial begin
  data = 0;
  outdata = 0;  
end

endmodule
