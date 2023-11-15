`default_nettype none

module uarttest(
	input CLOCK_50,
	output[7:0] LED,
	input[1:0] KEY,

	output[12:0] DRAM_ADDR,
	output[1:0] DRAM_BA,
	output DRAM_CAS_N,
	output DRAM_CKE,
	output DRAM_CLK,
	output DRAM_CS_N,
	inout[15:0] DRAM_DQ,
	output[1:0] DRAM_DQM,
	output DRAM_RAS_N,
	output DRAM_WE_N,

	inout[33:0] top,
	input[1:0] top_IN	
);
/*
assign top[0] = tx;
assign top[1] = tx;

reg[8:0] baudclock;
reg [3:0] bitcnt;
reg tx;

wire[7:0] txdata = q;


reg[5:0]  address;
reg clock;
wire[7:0]  q;
	
rom myrom(address,clock,q);

always@(posedge CLOCK_50) begin
	if(baudclock == 434) 
	begin 
		clock <= ~clock;
		//txdata = 'h41;
		baudclock <= 0;
		if(bitcnt == 14)
			begin
			bitcnt <= 0;
			address <= address + 1;
			end
		else bitcnt <= bitcnt + 1;
		
		
		case(bitcnt)
			0: tx<= 1; // idle
			1: tx<= 1;
			2: tx<= 0; // start
			3: tx<= txdata[0];
			4: tx<= txdata[1];
			5: tx<= txdata[2];
			6: tx<= txdata[3];
			7: tx<= txdata[4];
			8: tx<= txdata[5];
			9: tx<= txdata[6];
			10: tx<= txdata[7];
			11: tx <= ^txdata;
			12: tx<= 1; // stop
			13: tx<= 1; //idle
			default: tx<= 1;						
		endcase
		
	end
	else baudclock <= baudclock + 1;
end

*/

reg[3:0] rx_state;
reg[8:0] rx_cnt;
reg[10:0] rx_data;
wire rx_pin;
assign rx_pin = top[3];
assign LED = rx_data[9:2];

always@(posedge CLOCK_50)begin
	if(rx_state == 0) begin	
		if(rx_pin == 0) rx_state <= 1;
		rx_cnt <= 217;
	end else begin
	if(rx_cnt == 0) begin
		rx_cnt <= 434;
		rx_state <= rx_state + 1;
		
		case(rx_state)
		1: rx_data[0] <= rx_pin; // start
		2: rx_data[1] <= rx_pin;
		3: rx_data[2] <= rx_pin;
		4: rx_data[3] <= rx_pin;
		5: rx_data[4] <= rx_pin;
		6: rx_data[5] <= rx_pin;
		7: rx_data[6] <= rx_pin;
		8: rx_data[7] <= rx_pin;
		9: rx_data[8] <= rx_pin;
	  10: rx_data[9] <= rx_pin;  //parity
	  11: rx_data[10] <= rx_pin; //stop
	   default: rx_state <= 0;
		endcase
		
	end else rx_cnt <= rx_cnt - 1;	
	end	
end

endmodule
