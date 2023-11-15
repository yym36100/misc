module nios1
(
	CLOCK_50,
	LED
);
input CLOCK_50;
output [7:0] LED;

mynios1 mynios1_inst
(
	.clk_clk (CLOCK_50),
	.pio_led_external_connection_export (LED),
	.reset_reset_n (1'b1)
);
endmodule