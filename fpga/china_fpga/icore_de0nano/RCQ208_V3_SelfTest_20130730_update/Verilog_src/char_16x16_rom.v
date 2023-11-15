module char_16x16_rom(
  input       [4:0] addr,
  output reg [15:0] data
);
  
always @(addr)
  case (addr)
    // 2个16x16点阵仿宋体     

    5'h00 : data = 16'h1000;            // 红
    5'h01 : data = 16'h1000;
    5'h02 : data = 16'h2004;
    5'h03 : data = 16'h25FE;
    5'h04 : data = 16'h4420;
    5'h05 : data = 16'hF820;
    5'h06 : data = 16'h0820;
    5'h07 : data = 16'h1020;
    5'h08 : data = 16'h2020;
    5'h09 : data = 16'hFC20;
    5'h0A : data = 16'h4020;
    5'h0B : data = 16'h0020;
    5'h0C : data = 16'h1C20;
    5'h0D : data = 16'hE024;
    5'h0E : data = 16'h47FE;    
    5'h0F : data = 16'h0000; 

    5'h10 : data = 16'h0420;            // 芯
    5'h11 : data = 16'h0420;
    5'h12 : data = 16'h7FFE;
    5'h13 : data = 16'h0420;
    5'h14 : data = 16'h0420;
    5'h15 : data = 16'h0200;
    5'h16 : data = 16'h0100;
    5'h17 : data = 16'h0990;
    5'h18 : data = 16'h0888;
    5'h19 : data = 16'h4884;
    5'h1A : data = 16'h4806;
    5'h1B : data = 16'h4814;
    5'h1C : data = 16'h8810;
    5'h1D : data = 16'h0818;
    5'h1E : data = 16'h07F0;
    5'h1F : data = 16'h0000; 

    /*
    5'h00 : data = 16'h0100;            // 电
    5'h01 : data = 16'h0100;
    5'h02 : data = 16'h0100;
    5'h03 : data = 16'h3FF8;
    5'h04 : data = 16'h2108;
    5'h05 : data = 16'h2108;
    5'h06 : data = 16'h3FF8;
    5'h07 : data = 16'h2108;
    5'h08 : data = 16'h2108;
    5'h09 : data = 16'h2108;
    5'h0A : data = 16'h3FF8;
    5'h0B : data = 16'h2108;
    5'h0C : data = 16'h0102;
    5'h0D : data = 16'h0102;
    5'h0E : data = 16'h00FE;    
    5'h0F : data = 16'h0000; 

    5'h10 : data = 16'h0000;            // 子
    5'h11 : data = 16'h3FF0;
    5'h12 : data = 16'h0020;
    5'h13 : data = 16'h0040;
    5'h14 : data = 16'h0080;
    5'h15 : data = 16'h0100;
    5'h16 : data = 16'h0100;
    5'h17 : data = 16'h0104;
    5'h18 : data = 16'hFFFE;
    5'h19 : data = 16'h0100;
    5'h1A : data = 16'h0100;
    5'h1B : data = 16'h0100;
    5'h1C : data = 16'h0100;
    5'h1D : data = 16'h0100;
    5'h1E : data = 16'h0500;
    5'h1F : data = 16'h0200; */
    
    default: data = 16'h0000;
  endcase

endmodule
