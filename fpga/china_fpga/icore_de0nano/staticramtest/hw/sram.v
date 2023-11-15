`default_nettype none

// 512Kx16 sram

module sram(
	// module interface	
	input[18:0] address,
	input[15:0] dataw,
	output[15:0] datar,
	input we,		
		
	// chip phisical interface
	output[18:0] A,
	inout [15:0] D,
	output CEn, WEn,OEn,LBn,UBn
);

assign CEn = 0;
assign LBn = 0;
assign UBn = 0;
assign OEn =0;

assign WEn = !we;
assign D = we==1? dataw:16'bz;
assign A = address;
assign datar = D;

endmodule

