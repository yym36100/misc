//===========================================================================
// File Name   : VGA_CTL.v
// Module Name : VGA_CTL
// Description : This is a muxer module.
// Project     : 
// Belong to   : 
// Author      : xsyan1225
// E-Mail      : xs.yan@163.com
// QQ	       : 376412054
// HomePage    : http://shop57125352.taobao.com/
// Date        : 2010-01-25
// Rev.        : 1.01
//---------------------------------------------------------------------------
// Rev. Date       Description
//---------------------------------------------------------------------------
// 1.01 2010/01/25 1st Release
// 1.01 2012/02/14 1st modified
//===========================================================================
 
module VGA_CTL(
			SYSCLK,                // 板载时钟50MHz
			RST_B,                   // 板载按键RST
  
			VGA_HS,                  // VGA管脚 行同步
			VGA_VS,                  // VGA管脚 场同步
			VGA_R,                   // VGA管脚 红
			VGA_G,                   // VGA管脚 绿
			VGA_B                    // VGA管脚 蓝
			);

//===========================================================================
//Input and output declaration
//===========================================================================
input       SYSCLK;                // 板载时钟50MHz
input       RST_B;                   // 板载按键RST

output      VGA_HS;                  // VGA管脚 行同步
output		VGA_VS;                  // VGA管脚 场同步
output		VGA_R;                   // VGA管脚 红
output		VGA_G;                   // VGA管脚 绿
output		VGA_B;                    // VGA管脚 蓝

//===========================================================================
//Wire and reg declaration
//===========================================================================
wire		SYSCLK;                // 板载时钟50MHz
wire		RST_B;                   // 板载按键RST

wire		VGA_HS;                  // VGA管脚 行同步
wire		VGA_VS;                  // VGA管脚 场同步
wire		VGA_R;                   // VGA管脚 红
wire		VGA_G;                   // VGA管脚 绿
wire		VGA_B;                    // VGA管脚 蓝  

//===========================================================================
//Wire and reg in the module 
//===========================================================================
wire [9:0]	x_pos_buf;
wire [9:0]	y_pos_buf;
wire		red_buf;
wire 		green_buf;
wire		blue_buf; 

//Instance 
//从输入的 x_pos_buf , y_pos_buf 信号，查字库后获取对应点的点阵数据
disp_char I_disp_char
(
  .i_clk            (SYSCLK	),
  .i_rst_n          (RST_B	),
  //
  .i_x_pos          (x_pos_buf	),//input
  .i_y_pos          (y_pos_buf	),//input
  .o_red            (red_buf	),//output
  .o_green          (green_buf	),//output
  .o_blue           (blue_buf	) //output
);

//输出 x_pos_buf , y_pos_buf 信号到disp_char查表，并将查表后的RGB值载入到
//VGA扫描信号中。
vga_drive I_vga_drive
( 
  .SYSCLK            (SYSCLK	),
  .RST_B             (RST_B	), 
  //
  .o_x_pos          (x_pos_buf	),//output
  .o_y_pos          (y_pos_buf	),//output
  .i_red            (red_buf	),//input
  .i_green          (green_buf	),//input
  .i_blue           (blue_buf	),//input
  //
  .o_vga_hs         (VGA_HS	),
  .o_vga_vs         (VGA_VS	),
  .o_vga_r          (VGA_R	),
  .o_vga_g          (VGA_G	),
  .o_vga_b          (VGA_B	)  
);


endmodule
