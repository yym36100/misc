 `default_nettype none

module nios_300_top(

	//////////// CLOCK //////////
	CLOCK_50,

	//////////// LED //////////
	LED,

	//////////// KEY //////////
	KEY,

	//////////// SDRAM //////////
	DRAM_ADDR,
	DRAM_BA,
	DRAM_CAS_N,
	DRAM_CKE,
	DRAM_CLK,
	DRAM_CS_N,
	DRAM_DQ,
	DRAM_DQM,
	DRAM_RAS_N,
	DRAM_WE_N,

	//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
	top,
	top_IN 
);

//////////// CLOCK //////////
input 		          		CLOCK_50;

//////////// LED //////////
output		     [7:0]		LED;

//////////// KEY //////////
input 		     [1:0]		KEY;

//////////// SDRAM //////////
output		    [12:0]		DRAM_ADDR;
output		     [1:0]		DRAM_BA;
output		          		DRAM_CAS_N;
output		          		DRAM_CKE;
output		          		DRAM_CLK;
output		          		DRAM_CS_N;
inout 		    [15:0]		DRAM_DQ;
output		     [1:0]		DRAM_DQM;
output		          		DRAM_RAS_N;
output		          		DRAM_WE_N;

//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
inout 		    [33:0]		top;
input 		     [1:0]		top_IN;



nios_300 my_nios_300(
		.clk_clk(CLOCK_50),
		.buttons_external_connection_export(KEY),
		.led_external_connection_export(LED)  
	);

endmodule
