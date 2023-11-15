module nco2
#(
	parameter NR_SAMPLES = 16
)
(
	input clk,			// system clock
	input [31:0]freq,	// nco desired output frequency
	output reg[8:0]port  // 9 bit signal output 0xff = 0 balanced
);

	// local vars
	reg[31:0] phAcc; // phase accumlator 	u32 phAcc;
	reg[31:0] phInc; // phase increment 	u32 phInc;
	reg sign;		  // sign of output
		

	reg [3:0] addr;
	reg [7:0] data;
	reg [8:0] sindex;
	
	reg[15:0] phases;
	
	function[8:0] phase2index(input [15:0] phase);		
		reg[7:0] res;
		automatic reg sign = 0;
		reg[8:0] result;
		parameter NR_SAMPLES = 16;
		
		if(phase < 1 * NR_SAMPLES)
		begin
			sign = 0;
			res = phase;
		end
		else if((phase >= 1 * NR_SAMPLES) && (phase < 2* NR_SAMPLES))
		begin
			//q2
			sign = 0;
			res = 2* NR_SAMPLES - 1 - phase;
		end
		else if((phase >= 2 * NR_SAMPLES) && (phase < 3* NR_SAMPLES))
		begin
			//q3
			sign = 1;
			res = phase - 2 * NR_SAMPLES;
		end
		else 
		begin
			//q4
			sign = 1;
			res = 4 * NR_SAMPLES - 1 - phase;
		end
		result = {sign,res};
		return result;
	endfunction
	
	single_port_rom sintable(addr,clk,data);
	
	initial
	begin
		addr = 0;	
		phAcc	= 0;
		phInc = 0;
	end
		
	always@(posedge clk)
	begin
		phInc = freq; 
		phases = phAcc[31:16];
	  sindex = phase2index(phases);
		sign = sindex[8];
		addr = sindex[7:0];
		
		
		if(phAcc[31:16]>=(4*NR_SAMPLES))
		begin
			phAcc-=((4*NR_SAMPLES)<<16);
		end
		
		phAcc +=phInc;
		
//		sign = 0;
		if(sign == 0)
		begin
			port = 256 + data;
		end
		else
		begin
			port = 256 - data;
		end
	end
	
endmodule

module testbench;
  reg clk;
  reg[8:0] iport;
  reg[31:0]fr;
  
  nco2 testitem(clk,fr,iport);
  
  initial
  begin
  fr = 1<<16;
  clk = 0;
  end
  
  always
  begin
  #10 clk = !clk;
  end
  
endmodule


