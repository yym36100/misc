module  disp_char(
  input        i_clk,
  input        i_rst_n,                 // 异步复位
  //
  input  [9:0] i_x_pos,
  input  [9:0] i_y_pos,
  output [3:0] o_red,
  output [3:0] o_green,
  output [3:0] o_blue  
);

//++++++++++++++++++++++++++++++++++++++
// 将1个16x16汉字字符显示成16x16 开始
//++++++++++++++++++++++++++++++++++++++
wire char_16x16_area =  (i_x_pos >= 512 && i_x_pos < 544) &&
                        (i_y_pos >= 480 && i_y_pos < 496);

//wire char_16x16_area =  (i_x_pos >= 0 && (i_x_pos < (0 + 32))) &&
//                        (i_y_pos >= 16 && (i_y_pos < (16 + 16)));


wire [1:1] char_16x16_addr     = i_x_pos[4:4];    // 这一位是取字库中的第1个还是第2个字

//将从下面的行和列地址中取出一个点的数据。
wire [3:0] char_16x16_col_addr = i_x_pos[3:0];    // 列，比16x16放大2^0x2^0=1倍
wire [3:0] char_16x16_row_addr = i_y_pos[3:0];    // 行，比16x16放大2^0x2^0=1倍

// 横向16点
wire [15:0] pixels_16_to_16;                      

char_16x16_rom char_16x16_u0(
  .addr({char_16x16_addr, char_16x16_row_addr}),//这里决定取字符的哪一行数据
  .data(pixels_16_to_16)//得到字符的一行数据
);

reg pixels_16x16_valid;

// 并转串
// 取出横向16点数据，再依次打到VGA上
always @ (posedge i_clk, negedge i_rst_n)
  if (!i_rst_n)
    pixels_16x16_valid <= 0;
  else
    case (char_16x16_col_addr)//取出一行字符中哪一列数据(即具体第几位)
      4'h0 : pixels_16x16_valid <= pixels_16_to_16[15];
      4'h1 : pixels_16x16_valid <= pixels_16_to_16[14];
      4'h2 : pixels_16x16_valid <= pixels_16_to_16[13];
      4'h3 : pixels_16x16_valid <= pixels_16_to_16[12]; 
      4'h4 : pixels_16x16_valid <= pixels_16_to_16[11];
      4'h5 : pixels_16x16_valid <= pixels_16_to_16[10];
      4'h6 : pixels_16x16_valid <= pixels_16_to_16[ 9];
      4'h7 : pixels_16x16_valid <= pixels_16_to_16[ 8];
      4'h8 : pixels_16x16_valid <= pixels_16_to_16[ 7];
      4'h9 : pixels_16x16_valid <= pixels_16_to_16[ 6];
      4'hA : pixels_16x16_valid <= pixels_16_to_16[ 5];
      4'hB : pixels_16x16_valid <= pixels_16_to_16[ 4];
      4'hC : pixels_16x16_valid <= pixels_16_to_16[ 3];
      4'hD : pixels_16x16_valid <= pixels_16_to_16[ 2];
      4'hE : pixels_16x16_valid <= pixels_16_to_16[ 1];
      4'hF : pixels_16x16_valid <= pixels_16_to_16[ 0];
    endcase 
//--------------------------------------
// 将1个16x16汉字字符显示成16x16 结束
//--------------------------------------


//++++++++++++++++++++++++++++++++++++++
// 将1个16x16汉字字符显示成32x32 开始
//++++++++++++++++++++++++++++++++++++++
wire char_32x32_area =  (i_x_pos >= 512 && i_x_pos < 576) &&
                        (i_y_pos >= 448 && i_y_pos < 480);

wire [1:1] char_32x32_addr     = i_x_pos[5:5];    // 0~1 2个字
wire [3:0] char_32x32_col_addr = i_x_pos[4:1];    // 比16x16放大2^1x2^1=4倍
wire [3:0] char_32x32_row_addr = i_y_pos[4:1];    // 比16x16放大2^1x2^1=4倍

wire [15:0] pixels_16_to_32;                      // 横向16点

char_16x16_rom char_32x32_u0(
  .addr({char_32x32_addr, char_32x32_row_addr}),
  .data(pixels_16_to_32)
);

reg pixels_32x32_valid;

// 并转串
// 取出横向16点数据，再依次打到VGA上
always @ (posedge i_clk, negedge i_rst_n)
  if (!i_rst_n)
    pixels_32x32_valid <= 0;
  else
    case (char_32x32_col_addr)
      4'h0 : pixels_32x32_valid <= pixels_16_to_32[15];
      4'h1 : pixels_32x32_valid <= pixels_16_to_32[14];
      4'h2 : pixels_32x32_valid <= pixels_16_to_32[13];
      4'h3 : pixels_32x32_valid <= pixels_16_to_32[12]; 
      4'h4 : pixels_32x32_valid <= pixels_16_to_32[11];
      4'h5 : pixels_32x32_valid <= pixels_16_to_32[10];
      4'h6 : pixels_32x32_valid <= pixels_16_to_32[ 9];
      4'h7 : pixels_32x32_valid <= pixels_16_to_32[ 8];
      4'h8 : pixels_32x32_valid <= pixels_16_to_32[ 7];
      4'h9 : pixels_32x32_valid <= pixels_16_to_32[ 6];
      4'hA : pixels_32x32_valid <= pixels_16_to_32[ 5];
      4'hB : pixels_32x32_valid <= pixels_16_to_32[ 4];
      4'hC : pixels_32x32_valid <= pixels_16_to_32[ 3];
      4'hD : pixels_32x32_valid <= pixels_16_to_32[ 2];
      4'hE : pixels_32x32_valid <= pixels_16_to_32[ 1];
      4'hF : pixels_32x32_valid <= pixels_16_to_32[ 0];
    endcase 
//--------------------------------------
// 将1个16x16汉字字符显示成32x32 结束
//--------------------------------------


//++++++++++++++++++++++++++++++++++++++
// 将1个16x16汉字字符显示成64x64 开始
//++++++++++++++++++++++++++++++++++++++
wire char_64x64_area =  (i_x_pos >= 512 && i_x_pos < 640) &&
                        (i_y_pos >= 384 && i_y_pos < 448);

wire [1:1] char_64x64_addr     = i_x_pos[6:6];    // 0~1 2个字
wire [3:0] char_64x64_col_addr = i_x_pos[5:2];    // 比16x16放大2^2x2^2=16倍
wire [3:0] char_64x64_row_addr = i_y_pos[5:2];    // 比16x16放大2^2x2^2=16倍

wire [15:0] pixels_16_to_64;                      // 横向16点

char_16x16_rom char_64x64_u0(
  .addr             ({char_64x64_addr, char_64x64_row_addr}),
  .data             (pixels_16_to_64)
);

reg pixels_64x64_valid;

// 并转串
// 取出横向16点数据，再依次打到VGA上
always @ (posedge i_clk, negedge i_rst_n)
  if (!i_rst_n)
    pixels_64x64_valid <= 0;
  else
    case (char_64x64_col_addr)
      4'h0 : pixels_64x64_valid <= pixels_16_to_64[15];
      4'h1 : pixels_64x64_valid <= pixels_16_to_64[14];
      4'h2 : pixels_64x64_valid <= pixels_16_to_64[13];
      4'h3 : pixels_64x64_valid <= pixels_16_to_64[12]; 
      4'h4 : pixels_64x64_valid <= pixels_16_to_64[11];
      4'h5 : pixels_64x64_valid <= pixels_16_to_64[10];
      4'h6 : pixels_64x64_valid <= pixels_16_to_64[ 9];
      4'h7 : pixels_64x64_valid <= pixels_16_to_64[ 8];
      4'h8 : pixels_64x64_valid <= pixels_16_to_64[ 7];
      4'h9 : pixels_64x64_valid <= pixels_16_to_64[ 6];
      4'hA : pixels_64x64_valid <= pixels_16_to_64[ 5];
      4'hB : pixels_64x64_valid <= pixels_16_to_64[ 4];
      4'hC : pixels_64x64_valid <= pixels_16_to_64[ 3];
      4'hD : pixels_64x64_valid <= pixels_16_to_64[ 2];
      4'hE : pixels_64x64_valid <= pixels_16_to_64[ 1];
      4'hF : pixels_64x64_valid <= pixels_16_to_64[ 0];
    endcase 
//--------------------------------------
// 将1个16x16汉字字符显示成64x64 结束
//--------------------------------------


//++++++++++++++++++++++++++++++++++++++
// 将1个16x16汉字字符显示成128x128 开始
//++++++++++++++++++++++++++++++++++++++
wire char_128x128_area =  (i_x_pos >= 512 && i_x_pos < 768) &&
                          (i_y_pos >= 256 && i_y_pos < 384);

wire [1:1] char_128x128_addr     = i_x_pos[7:7];  // 0~1 2个字
wire [3:0] char_128x128_col_addr = i_x_pos[6:3];  // 比16x16放大2^3x2^3=64倍
wire [3:0] char_128x128_row_addr = i_y_pos[6:3];  // 比16x16放大2^3x2^3=64倍

wire [15:0] pixels_16_to_128;                     // 横向16点

char_16x16_rom char_128x128_u0(
  .addr({char_128x128_addr, char_128x128_row_addr}),
  .data(pixels_16_to_128)
);

reg pixels_128x128_valid;

// 并转串
// 取出横向16点数据，再依次打到VGA上
always @ (posedge i_clk, negedge i_rst_n)
  if (!i_rst_n)
    pixels_128x128_valid <= 0;
  else
    case (char_128x128_col_addr)
      4'h0 : pixels_128x128_valid <= pixels_16_to_128[15];
      4'h1 : pixels_128x128_valid <= pixels_16_to_128[14];
      4'h2 : pixels_128x128_valid <= pixels_16_to_128[13];
      4'h3 : pixels_128x128_valid <= pixels_16_to_128[12]; 
      4'h4 : pixels_128x128_valid <= pixels_16_to_128[11];
      4'h5 : pixels_128x128_valid <= pixels_16_to_128[10];
      4'h6 : pixels_128x128_valid <= pixels_16_to_128[ 9];
      4'h7 : pixels_128x128_valid <= pixels_16_to_128[ 8];
      4'h8 : pixels_128x128_valid <= pixels_16_to_128[ 7];
      4'h9 : pixels_128x128_valid <= pixels_16_to_128[ 6];
      4'hA : pixels_128x128_valid <= pixels_16_to_128[ 5];
      4'hB : pixels_128x128_valid <= pixels_16_to_128[ 4];
      4'hC : pixels_128x128_valid <= pixels_16_to_128[ 3];
      4'hD : pixels_128x128_valid <= pixels_16_to_128[ 2];
      4'hE : pixels_128x128_valid <= pixels_16_to_128[ 1];
      4'hF : pixels_128x128_valid <= pixels_16_to_128[ 0];
    endcase 
//--------------------------------------
// 将1个16x16汉字字符显示成128x128 结束
//--------------------------------------


//++++++++++++++++++++++++++++++++++++++
// 将1个16x16汉字字符显示成256x256 开始
//++++++++++++++++++++++++++++++++++++++
wire char_256x256_area =  (i_x_pos >= 512 && i_x_pos < 768) &&
                          (i_y_pos >= 0   && i_y_pos < 256);

wire [1:1] char_256x256_addr     = i_x_pos[8:8];  // 0~1 2个字
wire [3:0] char_256x256_col_addr = i_x_pos[7:4];  // 比16x16放大2^4x2^4=256倍
wire [3:0] char_256x256_row_addr = i_y_pos[7:4];  // 比16x16放大2^4x2^4=256倍

wire [15:0] pixels_16_to_256;                     // 横向16点

char_16x16_rom char_256x256_u0(
  .addr({char_256x256_addr, char_256x256_row_addr}),
  .data(pixels_16_to_256)
);

reg pixels_256x256_valid;

// 并转串
// 取出横向16点数据，再依次打到VGA上
always @ (posedge i_clk, negedge i_rst_n)
  if (!i_rst_n)
    pixels_256x256_valid <= 0;
  else
    case (char_256x256_col_addr)
      4'h0 : pixels_256x256_valid <= pixels_16_to_256[15];
      4'h1 : pixels_256x256_valid <= pixels_16_to_256[14];
      4'h2 : pixels_256x256_valid <= pixels_16_to_256[13];
      4'h3 : pixels_256x256_valid <= pixels_16_to_256[12]; 
      4'h4 : pixels_256x256_valid <= pixels_16_to_256[11];
      4'h5 : pixels_256x256_valid <= pixels_16_to_256[10];
      4'h6 : pixels_256x256_valid <= pixels_16_to_256[ 9];
      4'h7 : pixels_256x256_valid <= pixels_16_to_256[ 8];
      4'h8 : pixels_256x256_valid <= pixels_16_to_256[ 7];
      4'h9 : pixels_256x256_valid <= pixels_16_to_256[ 6];
      4'hA : pixels_256x256_valid <= pixels_16_to_256[ 5];
      4'hB : pixels_256x256_valid <= pixels_16_to_256[ 4];
      4'hC : pixels_256x256_valid <= pixels_16_to_256[ 3];
      4'hD : pixels_256x256_valid <= pixels_16_to_256[ 2];
      4'hE : pixels_256x256_valid <= pixels_16_to_256[ 1];
      4'hF : pixels_256x256_valid <= pixels_16_to_256[ 0];
    endcase 
//--------------------------------------
// 将1个16x16汉字字符显示成256x256 结束
//--------------------------------------


//++++++++++++++++++++++++++++++++++++++
// 将1个16x16汉字字符显示成512x512 开始
//++++++++++++++++++++++++++++++++++++++
wire char_512x512_area =  (i_x_pos >= 0 && i_x_pos < 512) &&
                          (i_y_pos >= 0 && i_y_pos < 512);

wire [1:1] char_512x512_addr     = i_x_pos[9:9];  // 0~1 2个字
wire [3:0] char_512x512_col_addr = i_x_pos[8:5];  // 比16x16放大2^5x2^5=1024倍
wire [3:0] char_512x512_row_addr = i_y_pos[8:5];  // 比16x16放大2^5x2^5=1024倍

wire [15:0] pixels_16_to_512;                     // 横向16点

char_16x16_rom char_512x512_u0(
  .addr({char_512x512_addr, char_512x512_row_addr}),
  .data(pixels_16_to_512)
);

reg pixels_512x512_valid;

// 并转串
// 取出横向16点数据，再依次打到VGA上
always @ (posedge i_clk, negedge i_rst_n)
  if (!i_rst_n)
    pixels_512x512_valid <= 0;
  else
    case (char_512x512_col_addr)
      4'h0 : pixels_512x512_valid <= pixels_16_to_512[15];
      4'h1 : pixels_512x512_valid <= pixels_16_to_512[14];
      4'h2 : pixels_512x512_valid <= pixels_16_to_512[13];
      4'h3 : pixels_512x512_valid <= pixels_16_to_512[12]; 
      4'h4 : pixels_512x512_valid <= pixels_16_to_512[11];
      4'h5 : pixels_512x512_valid <= pixels_16_to_512[10];
      4'h6 : pixels_512x512_valid <= pixels_16_to_512[ 9];
      4'h7 : pixels_512x512_valid <= pixels_16_to_512[ 8];
      4'h8 : pixels_512x512_valid <= pixels_16_to_512[ 7];
      4'h9 : pixels_512x512_valid <= pixels_16_to_512[ 6];
      4'hA : pixels_512x512_valid <= pixels_16_to_512[ 5];
      4'hB : pixels_512x512_valid <= pixels_16_to_512[ 4];
      4'hC : pixels_512x512_valid <= pixels_16_to_512[ 3];
      4'hD : pixels_512x512_valid <= pixels_16_to_512[ 2];
      4'hE : pixels_512x512_valid <= pixels_16_to_512[ 1];
      4'hF : pixels_512x512_valid <= pixels_16_to_512[ 0];
    endcase 
//--------------------------------------
// 将1个16x16汉字字符显示成512x512 结束
//--------------------------------------


//++++++++++++++++++++++++++++++++++++++
wire [3:0] valid_buf =  ( 
                          (char_16x16_area   && pixels_16x16_valid)   ||
                          (char_32x32_area   && pixels_32x32_valid)   ||
                          (char_64x64_area   && pixels_64x64_valid)   ||
                          (char_128x128_area && pixels_128x128_valid) || 
                          (char_256x256_area && pixels_256x256_valid) || 
                          (char_512x512_area && pixels_512x512_valid)
                        ) ? 4'hF : 4'h0;
 
// 有效则显示为蓝点 
assign o_red   = valid_buf;
assign o_green = 1'b0;//valid_buf;
assign o_blue  = 1'b0;//valid_buf;
//-------------------------------------- 
  
endmodule
