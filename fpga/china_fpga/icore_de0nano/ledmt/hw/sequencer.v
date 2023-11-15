`default_nettype none

module sequencer(
	input wire clock,
	input wire pwm_clock,
	
	output reg load_rq,
	output wire [3:0] bit,
	
	input wire data_ready,
	input wire[7:0] data_in,
	output reg[7:0] data_out
);

reg[2:0]state;
reg[3:0] bit_cnt;
reg[7:0] data_copy;
assign bit = bit_cnt;
reg wait_expired;

reg pwm_go, pwm_init;

reg [11:0] pwm_cnt;
reg [3:0] prev_bit;

reg prev_pwm_go;

initial begin
	state = 0;
	bit_cnt= 0;
	data_copy= 0;
	wait_expired= 0;
	pwm_go= 0;
	pwm_init= 0;
	pwm_cnt= 0;
	prev_bit= 0;
	prev_pwm_go= 0;
	
	load_rq = 0;
	data_out = 0;
	
end

always@(posedge pwm_clock) begin	
	if(pwm_init) begin
		pwm_cnt <= 1;
		wait_expired <= 0;
		prev_bit <= 2;
	end else begin		
		if(pwm_go & ~prev_pwm_go) begin : l_pwm_go
			reg [3:0] i;
			pwm_cnt <= pwm_cnt + 1;			
			for(i = 12;i!=0;i = i-1) begin
				if(pwm_cnt[i-1]) begin
					prev_bit <= i;
					if(i != prev_bit) begin
						wait_expired <= 1;
						prev_pwm_go <= 1;
						disable l_pwm_go;
					end
				end
			end			
		end
		
		if(~pwm_go) begin
			prev_pwm_go <= 0;
			wait_expired <= 0;
		end
	end
	
end


always@(posedge clock) begin
	case(state)
		0: begin
				bit_cnt<=0;				
				load_rq <=1;
				
				state <= 1;
			end
			
		1: begin
				bit_cnt <= bit_cnt + 1;
				load_rq <=0;
				if(data_ready) begin
					data_copy <= data_in;
					
					state <= 2;
				end
			end
			
		2: begin
				load_rq<=1;
				pwm_init <= 1;
				
				state <=3;
			end
			
		3: begin
				load_rq <= 0;
				
				if(bit_cnt!=11)
					bit_cnt <= bit_cnt + 1;
				else
					begin
						bit_cnt <= 0;
						pwm_init <= 1;
					end
				data_out <= data_copy;				
				
				state<= 4;
			end
			
		4: begin				
				pwm_init <= 0;
				if(wait_expired) begin
					pwm_go <= 0;					
					data_out <= 0;
					if(data_ready) begin
						data_copy <= data_in;
						load_rq <= 1;
						state <= 3;						
					end
				end else begin
					pwm_go <= 1;
				end
			end

	endcase
end



endmodule
