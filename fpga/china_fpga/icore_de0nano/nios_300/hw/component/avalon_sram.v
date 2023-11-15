module avalon_sram(
	input clk, reset,
	
	// avalon interface
	input [18:0] address,
	input cs_n, read_n, write_n,
	input [1:0] byteenable_n,
	input [15:0] data_write,
	output [15:0] data_read,
	
	// conduit
	output [18:0] sram_addr,
	inout [15:0] sram_data,
	output sram_ce_n,sram_oe_n, sram_we_n,
	output sram_lb_n, sram_ub_n	
);

reg [18:0] addr_reg;
reg [15:0] data_read_reg, data_write_reg;
reg ce_n_reg, lb_n_reg,ub_n_reg, oe_n_reg, we_n_reg;

always @(posedge clk, posedge reset)
if (reset)
	begin
	addr_reg <= 0;
	data_read_reg <= 0;
	data_write_reg <= 0;
	ce_n_reg <= 1;
	lb_n_reg <= 1;
	ub_n_reg <= 1;
	oe_n_reg <= 1;
	we_n_reg <= 1;
	end
else
	begin	
	addr_reg <= address;
	data_read_reg <= sram_data;
	data_write_reg <= data_write;
	ce_n_reg <= cs_n;
	lb_n_reg <= byteenable_n[0];
	ub_n_reg <= byteenable_n[1];
	oe_n_reg <= read_n;
	we_n_reg <= write_n;	
	end
	
// avalon
assign data_read = data_read_reg;

// sram
assign sram_addr = addr_reg;	
assign sram_ce_n = ce_n_reg;
assign sram_lb_n = lb_n_reg;
assign sram_ub_n = ub_n_reg;
assign sram_oe_n = oe_n_reg;
assign sram_we_n = we_n_reg;
// tristate
assign sram_data = (~we_n_reg) ? data_write_reg: 16'bz;
endmodule
