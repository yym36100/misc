module burst(
	input rst,
	input wclk,
	input clk,
	input [15:0]number,
	output reg wave_ctl,
	output  pulse_out
	);
	
	reg[16:0] counter;
	
	reg edg_statea;
	reg edg_stateb;
	
	reg rst_pulse;
	assign pulse_out = !rst_pulse;
	
	always @(posedge clk)
	begin
	 
		 edg_stateb = edg_statea;
		 edg_statea = rst;
		 
		 if(edg_statea == 1 && edg_stateb == 0 )rst_pulse = 0;
			else rst_pulse = 1;
	end	
		
	always @(negedge wclk or negedge rst_pulse)
	begin
		if(!rst_pulse)begin
			counter <= 0;
			wave_ctl <= 0;
		end else begin
			if(counter >= number - 1 )begin
				wave_ctl <= 1;
				end else begin
					wave_ctl <= 0;
					counter <= counter +1;
				end
			end
	end
	
	endmodule
		
	