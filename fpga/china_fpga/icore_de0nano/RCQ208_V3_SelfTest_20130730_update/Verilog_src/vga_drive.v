

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

  input        	SYSCLK;                 // VGA����ʱ��
  input        	RST_B;               // �첽��λ�ź� 
  //
  output [10:0]	o_x_pos;               // ���غ�����λ�� 0~799
  output [10:0]	o_y_pos;               // ����������λ�� 0~599
  input  		i_red;                 // ��ɫ����ֵ0~F
  input  		i_green;               // ��ɫ����ֵ0~F
  input  		i_blue;                // ��ɫ����ֵ0~F
                                      
  //
  output    	o_vga_hs;              // VGA�ܽ� ��ͬ��
  output    	o_vga_vs;              // VGA�ܽ� ��ͬ��
  output 		o_vga_r;               // VGA�ܽ� �� 
  output 		o_vga_g;               // VGA�ܽ� ��
  output 		o_vga_b;               // VGA�ܽ� ��  

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
// 800x600@72Hz �������� ��ʼ
//++++++++++++++++++++++++++++++++++++++
// p = 56+120+64+800 = 1040 pixels/line
// l = 37+6+23+600 = 666 lines/screen
// s = 72 screens/second
// pixel_rate = p * l * s ~= 50M pixel/second
/* �в���
 *       ________________________      _____
 * |ͬ��|����|     ��ʾ     |ǰ��|ͬ��|����|
 * |____|                        |____|
 *  _________ ______________ ______________
 *  ����ʾ   |     ��ʾ     |    ����ʾ    |
 *  _________ _____________________________
 *           |       ��ʾһ��֡��          |
 */
parameter H_FRONT    = 56;                        // ǰ��
parameter H_SYNC     = 120;                       // ͬ��
parameter H_BACK     = 64;                        // ����
parameter H_NOT_DISP = H_FRONT+H_SYNC+H_BACK;     // ����ʾ 
parameter H_DISP     = 800;                       // ��ʾ 
parameter H_TOTAL    = H_NOT_DISP+H_DISP;         // ֡��

/* ������
 *       ________________________      _____
 * |ͬ��|����|     ��ʾ     |ǰ��|ͬ��|����|
 * |____|                        |____|
 *  _________ ______________ ______________
 *  ����ʾ   |     ��ʾ     |    ����ʾ    |
 *  _________ _____________________________
 *           |       ��ʾһ��(��)֡��      |
 */
parameter V_FRONT    = 37+16;                        // ǰ��
parameter V_SYNC     = 6;                         // ͬ��
parameter V_BACK     = 23;                        // ����
parameter V_NOT_DISP = V_FRONT+V_SYNC+V_BACK;     // ����ʾ
parameter V_DISP     = 600;                       // ��ʾ
parameter V_TOTAL    = V_NOT_DISP+V_DISP;         // ֡��
//--------------------------------------
// 800x600@72Hz �������� ����
//--------------------------------------

reg [10:0]	h_cnt;                       // �м�����
reg [10:0]	h_cnt_n;

reg			o_vga_hs_n;

//===========================================================================
// �м�����,0 ~ H_TOTAL-1
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
// ��ͬ���źŷ�����
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

  //ͬ����������120
  //H sync puls width 
  else if(h_cnt == H_SYNC-1)				
   o_vga_hs_n = 1'h1;   
  else
   o_vga_hs_n = o_vga_hs;
end

//===========================================================================

reg [10:0]	v_cnt;                       // ��֡������
reg [10:0]	v_cnt_n; 

reg			o_vga_vs_n;

// ��������,0 ~ V_TOTAL-1
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

  //ÿһ����ͬ����1
  //every hsync puls v counter add 1
  else if(h_cnt == H_SYNC-1)
   v_cnt_n = v_cnt + 11'h1;
  else
   v_cnt_n = v_cnt;
end


//===========================================================================
// ��ͬ���źŷ�����
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
   
 //ͬ����������6
 //V sync puls width    
  else if(v_cnt == V_SYNC - 1)
   o_vga_vs_n = 1'h1; 
  else
   o_vga_vs_n = o_vga_vs;
end

//===========================================================================

//`define TEST

// ��������λ�� ��ʼ
// o_x_pos �� o_y_pos ֻ����ʾ����Χ�ڱ仯

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

// ��������λ�ã������������� ��ʼ
assign o_vga_r = (o_x_pos > 0) ? i_red   : 1'h0;
assign o_vga_g = (o_x_pos > 0) ? i_green : 1'h0;
assign o_vga_b = (o_x_pos > 0) ? i_blue  : 1'h0; 

endmodule
