`default_nettype none

module PT8211_DAC
(
	//internal interface
	input bitclock,
	input[15:0] data,
	
	//device pins interface
	output clk,
	output reg ws,
	output reg da
);

reg[5:0] time_cnt;
reg[15:0] captured_data;
assign clk = bitclock;

always@(negedge bitclock)
begin
	time_cnt <= time_cnt + 1;
	case(time_cnt)
	0: begin captured_data = data ; ws <= 1; da <= captured_data[15]; end
	1: da <= captured_data[14];
	2: da <= captured_data[13];
	3: da <= captured_data[12];
	4: da <= captured_data[11];
	5: da <= captured_data[10];
	6: da <= captured_data[9];
	7: da <= captured_data[8];
	8: da <= captured_data[7];
	9: da <= captured_data[6];
	10: da <= captured_data[5];
	11: da <= captured_data[4];
	12: da <= captured_data[3];
	13: da <= captured_data[2];
	14: da <= captured_data[1];
	15: da <= captured_data[0];
	16: begin ws <= 0; da <= captured_data[15]; end
	17: da <= captured_data[14];
	18: da <= captured_data[13];
	19: da <= captured_data[12];
	20: da <= captured_data[11];
	21: da <= captured_data[10];
	22: da <= captured_data[9];
	23: da <= captured_data[8];
	24: da <= captured_data[7];
	25: da <= captured_data[6];
	26: da <= captured_data[5];
	27: da <= captured_data[4];
	28: da <= captured_data[3];
	29: da <= captured_data[2];
	30: da <= captured_data[1];
	31: begin da <= captured_data[0];time_cnt <= 0;end	
	endcase
end

endmodule

