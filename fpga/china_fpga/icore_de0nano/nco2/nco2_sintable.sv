module single_port_rom
#(parameter DATA_WIDTH=8, parameter ADDR_WIDTH=4)
(
	input [(ADDR_WIDTH-1):0] addr,
	input clk, 
	output reg [(DATA_WIDTH-1):0] q
);
	
	reg [DATA_WIDTH-1:0] rom[2**ADDR_WIDTH-1:0];

	initial
	begin
		$readmemh("sintable.txt", rom);
	end

	always @ (posedge clk)
	begin
		q <= rom[addr];
	end

endmodule

module nco3(
	input clock50,
	output [7:0]port
);

	reg [3:0] addr;
	reg [7:0] data;

	single_port_rom sintable(addr,clock50,data);
	
	initial
	begin
		addr = 0;		
	end
	
	always_ff@(negedge clock50)
	begin
		addr++;
	end
	
	assign port = data;
	
endmodule

