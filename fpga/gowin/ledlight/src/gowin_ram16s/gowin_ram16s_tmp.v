//Copyright (C)2014-2023 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: Template file for instantiation
//GOWIN Version: V1.9.8.11 Education
//Part Number: GW1NR-LV9QN88PC6/I5
//Device: GW1NR-9
//Device Version: C
//Created Time: Sat Jul 15 23:34:48 2023

//Change the instance name and port connections to the signal names
//--------Copy here to design--------

    Gowin_RAM16S your_instance_name(
        .dout(dout_o), //output [31:0] dout
        .di(di_i), //input [31:0] di
        .ad(ad_i), //input [2:0] ad
        .wre(wre_i), //input wre
        .clk(clk_i) //input clk
    );

//--------Copy end-------------------
