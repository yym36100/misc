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
			SYSCLK,                // ����ʱ��50MHz
			RST_B,                   // ���ذ���RST
  
			VGA_HS,                  // VGA�ܽ� ��ͬ��
			VGA_VS,                  // VGA�ܽ� ��ͬ��
			VGA_R,                   // VGA�ܽ� ��
			VGA_G,                   // VGA�ܽ� ��
			VGA_B                    // VGA�ܽ� ��
			);

//===========================================================================
//Input and output declaration
//===========================================================================
input       SYSCLK;                // ����ʱ��50MHz
input       RST_B;                   // ���ذ���RST

output      VGA_HS;                  // VGA�ܽ� ��ͬ��
output		VGA_VS;                  // VGA�ܽ� ��ͬ��
output		VGA_R;                   // VGA�ܽ� ��
output		VGA_G;                   // VGA�ܽ� ��
output		VGA_B;                    // VGA�ܽ� ��

//===========================================================================
//Wire and reg declaration
//===========================================================================
wire		SYSCLK;                // ����ʱ��50MHz
wire		RST_B;                   // ���ذ���RST

wire		VGA_HS;                  // VGA�ܽ� ��ͬ��
wire		VGA_VS;                  // VGA�ܽ� ��ͬ��
wire		VGA_R;                   // VGA�ܽ� ��
wire		VGA_G;                   // VGA�ܽ� ��
wire		VGA_B;                    // VGA�ܽ� ��  

//===========================================================================
//Wire and reg in the module 
//===========================================================================
wire [9:0]	x_pos_buf;
wire [9:0]	y_pos_buf;
wire		red_buf;
wire 		green_buf;
wire		blue_buf; 

//Instance 
//������� x_pos_buf , y_pos_buf �źţ����ֿ���ȡ��Ӧ��ĵ�������
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

//��� x_pos_buf , y_pos_buf �źŵ�disp_char������������RGBֵ���뵽
//VGAɨ���ź��С�
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
