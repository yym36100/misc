module adc
(

// internal interface
input rst,
input clock,
input[2:0] addr,
output reg[11:0] data,

//adc pins
output CS_N,
output SADDR,
output SCLK,
input SDAT
);

reg[4:0] state;
reg cs, mosi,mclk;
reg[11:0] miso;

assign SCLK = clock;
assign SADDR = mosi;
assign CS_N = cs;

always@(negedge clock, posedge rst)
begin
	if(rst)
		begin
		state <= 0;
		cs <= 1;		
		end
	else
		begin		
		state<= state + 1;		
		
		case(state)
			0: begin
				cs <= 0;				
				end
			1: mosi <= 0; // don't care
			2: mosi <= 0; // don't care
			3: mosi <= addr[2]; // a2
			4: mosi <= addr[1]; // a1
			5: mosi <= addr[0]; // a0
			16: cs <= 1;
			20: state <= 0;
			
		endcase
		
	end

end

always@(posedge clock)
begin

case(state)
	0: miso <= 12'b0;
	5: miso[11] <= SDAT;
	6: miso[10] <= SDAT;
	7: miso[9] <= SDAT;
	8: miso[8] <= SDAT;
	9: miso[7] <= SDAT;
	10: miso[6] <= SDAT;
	11: miso[5] <= SDAT;
	12: miso[4] <= SDAT;
	13: miso[3] <= SDAT;
	14: miso[2] <= SDAT;
	15: miso[1] <= SDAT;
	16: begin
		miso[0] <= SDAT;
		//cs<=1;
		end
	17: begin 
		data<=miso;
		//state<=0;
		end
endcase
end


endmodule
