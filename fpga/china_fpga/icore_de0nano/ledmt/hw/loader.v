`default_nettype none

module loader(
	input wire clock,
	input wire [3:0] bit,
	input wire [10:0] address,
	input wire load_rq,
	output reg data_ready,
	output reg[7:0] data_out	
);


reg[7:0]  gamma_address;
wire[11:0] gamma_output;

reg[10:0] ledwave_address;	
wire[7:0]  ledwave_output;

gamma 	 my_gamma_rom(gamma_address,clock,gamma_output);
wave_rom  my_wave_rom(ledwave_address,clock,ledwave_output);

reg[3:0] state;
reg[3:0] nextstate;

reg[3:0] r_bit;
reg[3:0] r_next_bit;
reg[7:0] r_data_out;

reg load_rq_old;

initial begin
	gamma_address = 0;
	ledwave_address = 0;
	state = 0;
	nextstate = 0;
	r_bit = 0;
	r_next_bit = 0;
	r_data_out = 0;
	load_rq_old = 0;
	
	data_ready = 0;
	data_out = 0;
end

always@(posedge clock) begin
	load_rq_old<= load_rq;
	case(state)
		0: begin
				if(load_rq & ~load_rq_old)
				begin
					state <= 1;					
					r_next_bit <= bit;
					ledwave_address <= address;
				end
			end
		1: begin
				ledwave_address <= ledwave_address + 1;
				gamma_address <= ledwave_output;
				state <= 2;
			end
		2: begin
				ledwave_address <= ledwave_address + 1;
				gamma_address <= ledwave_output;
				r_bit<=r_next_bit;
				r_data_out[0] <= gamma_output[r_bit];
				state <= 3;
			end
		3: begin
			ledwave_address <= ledwave_address + 1;
			gamma_address <= ledwave_output;
			r_data_out[1] <= gamma_output[r_bit];
			state <= 4;
			data_ready <= 0;
		end
		4: begin
			ledwave_address <= ledwave_address + 1;
			gamma_address <= ledwave_output;
			r_data_out[2] <= gamma_output[r_bit];
			state <= 5;			
		end
		5: begin
			ledwave_address <= ledwave_address + 1;
			gamma_address <= ledwave_output;
			r_data_out[3] <= gamma_output[r_bit];
			state <= 6;			
		end
		6: begin
			ledwave_address <= ledwave_address + 1;
			gamma_address <= ledwave_output;
			r_data_out[4] <= gamma_output[r_bit];
			state <= 7;			
		end
		7: begin
			ledwave_address <= ledwave_address + 1;
			gamma_address <= ledwave_output;
			r_data_out[5] <= gamma_output[r_bit];
			state <= 8;			
		end
		8: begin
			ledwave_address <= ledwave_address + 1;
			gamma_address <= ledwave_output;
			r_data_out[6] <= gamma_output[r_bit];
			state <= 9;
			if(load_rq & ~load_rq_old)
			begin
				ledwave_address <= address;
				r_next_bit <= bit;
				nextstate <= 2;				
			end else begin
				nextstate <= 0;				
			end
		end
		9: begin
			ledwave_address <= ledwave_address + 1;
			gamma_address <= ledwave_output;
			r_data_out[7] <= gamma_output[bit];
						
			data_out <= r_data_out;
			data_ready <= 1;
			
			state <= nextstate;			
		end
		
			
	endcase
end

endmodule
