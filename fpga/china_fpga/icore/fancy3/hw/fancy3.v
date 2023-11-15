 `default_nettype none
 `timescale 10 ns / 10 ns
  
module fancy3(
	input wire CLOCK_50,
	output wire [7:0] LED,
	input wire [1:0] KEY,
	inout wire [33:0] top,
	input wire [1:0] top_IN
);

wire[5:0] address;
wire[31:0] read_data;
wire [7:0] led_dummy;

    sopc my_spoc (
        .clk_clk                        (CLOCK_50),          	//                     clk.clk
        .pio_external_connection_export (led_dummy),				// pio_external_connection.export
        .dualport_ram_clk2_clk          (CLOCK_50),         	//       dualport_ram_clk2.clk
        .dualport_ram_s2_address        (address),        		//         dualport_ram_s2.address
        .dualport_ram_s2_chipselect     (1'b1),     				//                        .chipselect
        .dualport_ram_s2_clken          (1'b1),          		//                        .clken
        .dualport_ram_s2_write          (1'b0/* read only */), //                        .write
        .dualport_ram_s2_readdata       (read_data),       		//                        .readdata
        .dualport_ram_s2_writedata      (0),      					//                        .writedata
        .dualport_ram_s2_byteenable     (4'b111),     			//                        .byteenable
        .dualport_ram_reset2_reset      (0/*not used*/),      	//     dualport_ram_reset2.reset
        .dualport_ram_reset2_reset_req  (1'b0)   					//                        .reset_req
    );
	 
wire pwm_clock;

reg[15:0] duty[7:0];

pwm my_pwm1( .clock(pwm_clock),.duty(duty[0]), .out(LED[0]));
pwm my_pwm2( .clock(pwm_clock),.duty(duty[1]), .out(LED[1]));
pwm my_pwm3( .clock(pwm_clock),.duty(duty[2]), .out(LED[2]));
pwm my_pwm4( .clock(pwm_clock),.duty(duty[3]), .out(LED[3]));
pwm my_pwm5( .clock(pwm_clock),.duty(duty[4]), .out(LED[4]));
pwm my_pwm6( .clock(pwm_clock),.duty(duty[5]), .out(LED[5]));
pwm my_pwm7( .clock(pwm_clock),.duty(duty[6]), .out(LED[6]));
pwm my_pwm8( .clock(pwm_clock),.duty(duty[7]), .out(LED[7]));

reg [3:0] slowclock;

always@(posedge CLOCK_50) slowclock <= slowclock + 1;

assign pwm_clock  = slowclock[3];

reg[1:0] state;
reg[2:0] led_cnt;

parameter s_set_address = 0;
parameter s_read_data = 1;

assign address = {3'b0,led_cnt};
always@(posedge slowclock[3]) begin
		case(state)
			s_set_address: 
				begin
					//address <= address + 1;
					led_cnt <= led_cnt + 1;
					state <= s_read_data;
				end
				
			s_read_data:
				begin
					//led_cnt <= led_cnt + 1;
					//LED[led_cnt] <= read_data[0];
					duty[led_cnt] <= read_data[15:0];
					state <= s_set_address;
				end
		endcase
end

endmodule
