`default_nettype none

module staticramtest(
	input[1:0] KEY,
	input CLOCK_50,
	output [7:0] LED,

	inout[33:0] top,
	//input[1:0] top_IN,

	inout[33:0] bottom
	//input[1:0] bottom_IN
);

`define iA {bottom[14],bottom[12],bottom[6],bottom[4],bottom[2],top[23],top[22],top[17],top[18],top[16],top[4],top[2],top[1],top[0],	bottom[28],bottom[26],	bottom[24],bottom[22],bottom[20]}
`define iD {top[6],top[8],top[9],top[10],top[12],top[13],top[15],top[14],bottom[10],bottom[17],bottom[19],bottom[21],bottom[23],bottom[25],bottom[27],bottom[29]}

reg[18:0] t_address;
reg[15:0] t_dataw;
wire[15:0] t_datar;
reg t_we;

wire rst = KEY[0];

assign LED = t_datar[7:0];

sram myram(
	t_address,
	t_dataw,
	t_datar,
	t_we,		
	// chip phisical interface
	`iA,
	`iD,
	bottom[18], bottom[16],top[3],top[7],top[5]
	);

	reg[31:0] slowclock;
reg[9:0] cnt;
reg state;

always@(posedge CLOCK_50) begin
	if(rst == 1) begin
				cnt<=0;
				t_address <= 0;
				t_dataw <= 0;
				t_we <= 0;
				state <= 0;
	end else begin
		slowclock <= slowclock + 1;
		if(state == 0)
		begin
			if(cnt[9] ==0) begin
				if(cnt[0]) begin
					cnt <= cnt + 1;	
					t_we <= 0;
					t_address <= t_address + 1;
					t_dataw <= t_dataw + 1;		
				end else begin			
					t_we <= 1;
				end			
			end else begin
				cnt<=0;
				t_address <= 0;
				t_we <= 0;
				state <= 1;
			end
		end else begin
			if(slowclock[24] ==1) begin
				slowclock <= 0;
				if(cnt[8] == 0) begin
					cnt <= cnt + 1;
					t_we <= 0;
					t_address <= cnt;
				end else cnt <= 0;
			end
		end
	end
end


endmodule
