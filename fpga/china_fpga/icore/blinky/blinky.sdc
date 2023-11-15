
create_clock -period 40 [get_ports FPGA_CLK2]

derive_pll_clocks

derive_clock_uncertainty

