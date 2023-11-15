
module nios_sys (
	clk_clk,
	reset_reset_n,
	button_external_connection_export,
	leds_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	input		button_external_connection_export;
	output	[7:0]	leds_external_connection_export;
endmodule
