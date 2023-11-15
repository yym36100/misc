

`define UD  #1

module vga_drive(  
  			SYSCLK,
  			RST_B,
 
  			o_x_pos,
  			o_y_pos,
  			i_red,
  			i_green,
  			i_blue,

  			o_vga_hs,
  			o_vga_vs,
  			o_vga_r,
  			o_vga_g,
  			o_vga_b  
			);
			
//===========================================================================
//Input and output declaration
//===========================================================================			

  input        	SYSCLK;                 // VGA像素时钟
  input        	RST_B;               // 异步复位信号 
  //
  output [10:0]	o_x_pos;               // 像素横坐标位置 0~799
  output [10:0]	o_y_pos;               // 像素纵坐标位置 0~599
  input  		i_red;                 // 红色数字值0~F
  input  		i_green;               // 绿色数字值0~F
  input  		i_blue;                // 蓝色数字值0~F
                                      
  //
  output    	o_vga_hs;              // VGA管脚 行同步
  output    	o_vga_vs;              // VGA管脚 场同步
  output 		o_vga_r;               // VGA管脚 红 
  output 		o_vga_g;               // VGA管脚 绿
  output 		o_vga_b;               // VGA管脚 蓝  

//===========================================================================
//Wire and reg declaration
//===========================================================================

  wire        	SYSCLK;
  wire        	RST_B;
  //
  //reg	[9:0]	o_x_pos;
  //reg	[9:0]	o_y_pos;
  wire			i_red;
  wire			i_green;
  wire			i_blue;
  //
  reg    		o_vga_hs;
  reg    		o_vga_vs;
  wire 			o_vga_r;
  wire 			o_vga_g;
  wire 			o_vga_b;

//++++++++++++++++++++++++++++++++++++++
// 800x600@72Hz 参数定义 开始
//++++++++++++++++++++++++++++++++++++++
// p = 56+120+64+800 = 1040 pixels/line
// l = 37+6+23+600 = 666 lines/screen
// s = 72 screens/second
// pixel_rate = p * l * s ~= 50M pixel/second
/* 行参数
 *       ________________________      _____
 * |同步|后沿|     显示     |前沿|同步|后沿|
 * |____|                        |____|
 *  _________ ______________ ______________
 *  不显示   |     显示     |    不显示    |
 *  _________ _____________________________
 *           |       显示一行帧长          |
 */
parameter H_FRONT    = 56;                        // 前沿
parameter H_SYNC     = 120;                       // 同步
parameter H_BACK     = 64;                        // 后沿
parameter H_NOT_DISP = H_FRONT+H_SYNC+H_BACK;     // 不显示 
parameter H_DISP     = 800;                       // 显示 
parameter H_TOTAL    = H_NOT_DISP+H_DISP;         // 帧长

/* 场参数
 *       ________________________      _____
 * |同步|后沿|     显示     |前沿|同步|后沿|
 * |____|                        |____|
 *  _________ ______________ ______________
 *  不显示   |     显示     |    不显示    |
 *  _________ _____________________________
 *           |       显示一列(场)帧长      |
 */
parameter V_FRONT    = 37+16;                        // 前沿
parameter V_SYNC     = 6;                         // 同步
parameter V_BACK     = 23;                        // 后沿
parameter V_NOT_DISP = V_FRONT+V_SYNC+V_BACK;     // 不显示
parameter V_DISP     = 600;                       // 显示
parameter V_TOTAL    = V_NOT_DISP+V_DISP;         // 帧长
//--------------------------------------
// 800x600@72Hz 参数定义 结束
//--------------------------------------

reg [10:0]	h_cnt;                       // 行计数子
reg [10:0]	h_cnt_n;

reg			o_vga_hs_n;

//===========================================================================
// 行计数器,0 ~ H_TOTAL-1
// Horizontal scan counter, between 0 ~ H_TOTAL-1
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
   h_cnt <= `UD 11'h0;
  else
   h_cnt <= `UD h_cnt_n;   
end

always @ (*)
begin
  if (h_cnt == H_TOTAL-1)
   h_cnt_n = 0;    
  else
   h_cnt_n = h_cnt + 11'h1;
end
//===========================================================================
// 行同步信号发生器
// Horizontal Sync generator
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
   o_vga_hs <= `UD 1'h0;
  else
   o_vga_hs <= `UD o_vga_hs_n;   
end

always @ (*)
begin 
  if(h_cnt == 11'h0)						
   o_vga_hs_n = 1'h0;

  //同步肪冲宽度是120
  //H sync puls width 
  else if(h_cnt == H_SYNC-1)				
   o_vga_hs_n = 1'h1;   
  else
   o_vga_hs_n = o_vga_hs;
end

//===========================================================================

reg [10:0]	v_cnt;                       // 场帧计数子
reg [10:0]	v_cnt_n; 

reg			o_vga_vs_n;

// 场计数器,0 ~ V_TOTAL-1
// Vertical scan counter, between 0 ~ V_TOTAL-1
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
   v_cnt <= `UD 11'h0;
  else
   v_cnt <= `UD v_cnt_n;   
end

always @ (*)
begin
  if(v_cnt == V_TOTAL-1)			
   v_cnt_n = 11'h0;  

  //每一个行同步加1
  //every hsync puls v counter add 1
  else if(h_cnt == H_SYNC-1)
   v_cnt_n = v_cnt + 11'h1;
  else
   v_cnt_n = v_cnt;
end


//===========================================================================
// 场同步信号发生器
// Vertical Sync generator
always @ (posedge SYSCLK or negedge RST_B)
begin
  if(!RST_B)
   o_vga_vs <= `UD 1'h0;
  else
   o_vga_vs <= `UD o_vga_vs_n;   
end

always @ (*)
begin
  if(v_cnt == 11'h0)			
   o_vga_vs_n = 1'h0; 
   
 //同步肪冲宽度是6
 //V sync puls width    
  else if(v_cnt == V_SYNC - 1)
   o_vga_vs_n = 1'h1; 
  else
   o_vga_vs_n = o_vga_vs;
end

//===========================================================================

//`define TEST

// 产生像素位置 开始
// o_x_pos 和 o_y_pos 只在显示区范围内变化

`ifdef TEST
wire	[9:0]	o_x_pos;
wire	[9:0]	o_y_pos;

assign o_x_pos = (h_cnt >= H_SYNC + H_BACK) ? (h_cnt - H_SYNC - H_BACK) : 10'h0;
assign o_y_pos = (v_cnt >= V_SYNC + V_BACK) ? (v_cnt - V_SYNC - V_BACK) : 10'h0;

`else

reg	[9:0]	o_x_pos;
reg	[9:0]	o_y_pos;

always @ (*)
begin
 if(h_cnt >= H_SYNC + H_BACK)
  o_x_pos = (h_cnt - H_SYNC - H_BACK); 
 else
  o_x_pos = 10'h0; 
end


always @ (*)
begin
 if(v_cnt >= V_SYNC + V_BACK)
  o_y_pos = (v_cnt - V_SYNC - V_BACK); 
 else
  o_y_pos = 10'h0; 
end

`endif

// 根据像素位置，填入像素内容 开始
assign o_vga_r = (o_x_pos > 0) ? i_red   : 1'h0;
assign o_vga_g = (o_x_pos > 0) ? i_green : 1'h0;
assign o_vga_b = (o_x_pos > 0) ? i_blue  : 1'h0; 

endmodule
