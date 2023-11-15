module dso_clock(input reset,input clock,input[3:0] sel,output reg clkout);

reg [20:0] ct;
reg [20:0] counter;

reg out;

always @(posedge clock)
begin
clkout <= out;
end

always @ (sel)
begin
	case (sel)
		4'd0:ct<=2;
		4'd1:ct<=4;
		4'd2:ct<=10;
		4'd3:ct<=20;
		4'd4:ct<=40;
		4'd5:ct<=100;
		4'd6:ct<=200;
		4'd7:ct<=400;
		4'd8:ct<=1000;
		4'd9:ct<=2000;
		4'd10:ct<=4000;
		4'd11:ct<=10000;
		4'd12:ct<=20000;
		4'd13:ct<=40000;
		4'd14:ct<=100000;
		4'd15:ct<=200000;
	endcase
end

always @(posedge clock,posedge reset)
begin
		if(reset)begin
			out <= 0;
			counter <= 0;
		end else begin
		
		if(counter == (ct/2 -1))begin
			counter <= 0;
			out <= ~out;
			end else begin
			counter <= counter + 1;
			end
		end
end
endmodule
			
		
