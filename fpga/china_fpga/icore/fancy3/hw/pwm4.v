 `default_nettype none
 `timescale 10 ns / 10 ns
 
module pwm4
#(
	parameter NO_BITS = 5'd16
)
(
	input wire clock,
	input wire go,
	input wire[NO_BITS - 1:0] duty,
	output wire done,	
	output reg out	
);

reg [NO_BITS :0] cnt;
assign done = cnt == 2**NO_BITS;


always@(posedge clock) begin	
  if(go) begin : t1
	reg [4:0]i;
	if(done) cnt <= 0;
  else cnt <= cnt + 17'b1;
	$display("---");
	for(i=NO_BITS;i!=5'b0;i = i - 5'b1) begin :t2
	  $display("bit=%d",i-1);
		if(cnt[i-1]) begin : t3
		  $display("outputting=%d",i-1);
			out<= duty[i-1];
			disable t1;
		end
	end
	end else begin
	  cnt<=0;
	  out<=0;
  end
end

initial begin
  cnt = 0;
  out = 0;
end

endmodule


`timescale 10 ns / 10 ns

module pwm4_tb;
parameter Nbits = 4;
reg clock;
reg go;
wire done, out;
reg[Nbits-1:0] duty;

pwm4 #(.NO_BITS(Nbits) ) pwm_ti (
	.clock(clock),
	.go(go),
	.duty(duty),
	.done(done),	
	.out(out)	
);


reg[Nbits+1:0] cnt;
initial begin
	clock = 1;
	duty = 0;
	cnt = 0;
	go = 1;
end

always  begin
	#1 clock = ~clock;
	cnt = cnt + 1;
	if(done & go) begin
		go = 0;
		duty = duty + 1;
	end
	if(cnt == 2**(Nbits+1) + 5) begin
		go = 1;
		cnt = 0;
	end
end
 
endmodule
