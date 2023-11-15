//Copyright (C)2014-2023 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: IP file
//GOWIN Version: V1.9.8.11 Education
//Part Number: GW1NR-LV9QN88PC6/I5
//Device: GW1NR-9
//Device Version: C
//Created Time: Sat Jul 15 23:34:48 2023

module Gowin_RAM16S (dout, di, ad, wre, clk);

output [31:0] dout;
input [31:0] di;
input [2:0] ad;
input wre;
input clk;

wire gw_gnd;

assign gw_gnd = 1'b0;

RAM16S4 ram16s_inst_0 (
    .DO(dout[3:0]),
    .DI(di[3:0]),
    .AD({gw_gnd,ad[2:0]}),
    .WRE(wre),
    .CLK(clk)
);

defparam ram16s_inst_0.INIT_0 = 16'h0000;
defparam ram16s_inst_0.INIT_1 = 16'h0000;
defparam ram16s_inst_0.INIT_2 = 16'h0000;
defparam ram16s_inst_0.INIT_3 = 16'h0000;

RAM16S4 ram16s_inst_1 (
    .DO(dout[7:4]),
    .DI(di[7:4]),
    .AD({gw_gnd,ad[2:0]}),
    .WRE(wre),
    .CLK(clk)
);

defparam ram16s_inst_1.INIT_0 = 16'h0000;
defparam ram16s_inst_1.INIT_1 = 16'h0000;
defparam ram16s_inst_1.INIT_2 = 16'h0000;
defparam ram16s_inst_1.INIT_3 = 16'h0000;

RAM16S4 ram16s_inst_2 (
    .DO(dout[11:8]),
    .DI(di[11:8]),
    .AD({gw_gnd,ad[2:0]}),
    .WRE(wre),
    .CLK(clk)
);

defparam ram16s_inst_2.INIT_0 = 16'h0000;
defparam ram16s_inst_2.INIT_1 = 16'h0000;
defparam ram16s_inst_2.INIT_2 = 16'h0000;
defparam ram16s_inst_2.INIT_3 = 16'h0000;

RAM16S4 ram16s_inst_3 (
    .DO(dout[15:12]),
    .DI(di[15:12]),
    .AD({gw_gnd,ad[2:0]}),
    .WRE(wre),
    .CLK(clk)
);

defparam ram16s_inst_3.INIT_0 = 16'h0000;
defparam ram16s_inst_3.INIT_1 = 16'h0000;
defparam ram16s_inst_3.INIT_2 = 16'h0000;
defparam ram16s_inst_3.INIT_3 = 16'h0000;

RAM16S4 ram16s_inst_4 (
    .DO(dout[19:16]),
    .DI(di[19:16]),
    .AD({gw_gnd,ad[2:0]}),
    .WRE(wre),
    .CLK(clk)
);

defparam ram16s_inst_4.INIT_0 = 16'h0000;
defparam ram16s_inst_4.INIT_1 = 16'h0000;
defparam ram16s_inst_4.INIT_2 = 16'h0000;
defparam ram16s_inst_4.INIT_3 = 16'h0000;

RAM16S4 ram16s_inst_5 (
    .DO(dout[23:20]),
    .DI(di[23:20]),
    .AD({gw_gnd,ad[2:0]}),
    .WRE(wre),
    .CLK(clk)
);

defparam ram16s_inst_5.INIT_0 = 16'h0000;
defparam ram16s_inst_5.INIT_1 = 16'h0000;
defparam ram16s_inst_5.INIT_2 = 16'h0000;
defparam ram16s_inst_5.INIT_3 = 16'h0000;

RAM16S4 ram16s_inst_6 (
    .DO(dout[27:24]),
    .DI(di[27:24]),
    .AD({gw_gnd,ad[2:0]}),
    .WRE(wre),
    .CLK(clk)
);

defparam ram16s_inst_6.INIT_0 = 16'h0000;
defparam ram16s_inst_6.INIT_1 = 16'h0000;
defparam ram16s_inst_6.INIT_2 = 16'h0000;
defparam ram16s_inst_6.INIT_3 = 16'h0000;

RAM16S4 ram16s_inst_7 (
    .DO(dout[31:28]),
    .DI(di[31:28]),
    .AD({gw_gnd,ad[2:0]}),
    .WRE(wre),
    .CLK(clk)
);

defparam ram16s_inst_7.INIT_0 = 16'h0000;
defparam ram16s_inst_7.INIT_1 = 16'h0000;
defparam ram16s_inst_7.INIT_2 = 16'h0000;
defparam ram16s_inst_7.INIT_3 = 16'h0000;

endmodule //Gowin_RAM16S
