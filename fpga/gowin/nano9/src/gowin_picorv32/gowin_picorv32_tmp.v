//Copyright (C)2014-2023 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: Template file for instantiation
//GOWIN Version: V1.9.8.11 Education
//Part Number: GW1NR-LV9QN88PC6/I5
//Device: GW1NR-9
//Device Version: C
//Created Time: Fri Jul 14 16:33:41 2023

//Change the instance name and port connections to the signal names
//--------Copy here to design--------

	Gowin_PicoRV32_Top your_instance_name(
		.ser_tx(ser_tx_o), //output ser_tx
		.ser_rx(ser_rx_i), //input ser_rx
		.gpio_io(gpio_io_io), //inout [31:0] gpio_io
		.io_spi_clk(io_spi_clk_io), //inout io_spi_clk
		.io_spi_csn(io_spi_csn_io), //inout io_spi_csn
		.io_spi_mosi(io_spi_mosi_io), //inout io_spi_mosi
		.io_spi_miso(io_spi_miso_io), //inout io_spi_miso
		.jtag_TDI(jtag_TDI_i), //input jtag_TDI
		.jtag_TDO(jtag_TDO_o), //output jtag_TDO
		.jtag_TCK(jtag_TCK_i), //input jtag_TCK
		.jtag_TMS(jtag_TMS_i), //input jtag_TMS
		.clk_in(clk_in_i), //input clk_in
		.resetn_in(resetn_in_i) //input resetn_in
	);

//--------Copy end-------------------
