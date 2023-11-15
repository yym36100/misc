`default_nettype none

module nios_top(
	input wire clock,
	input wire button,
	output wire[3:0] leds
);

//assign leds = 5;
wire clock150;

pll1 mypll(
	.inclk0(clock),
	.c0(clock150)
);


nios_sys my_nios(
	.button_external_connection_export(button), // button_external_connection.export
	.reset_reset_n(1),                     		//                      reset.reset_n
	.clk_clk(clock150),                            //                        clk.clk
	.leds_external_connection_export(leds)      //   leds_external_connection.export
);

endmodule
	