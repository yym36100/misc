module pwm_control(
					//inputs
					address,
					chipselect,					
					a_50_MHZ_CLK,
					reset_n,
					write_n,
					writedata,
					
					// output. 
					readdata,
					pwmDrive,
					done
					);
					
					
parameter S_idle = 0;
parameter S_pwm = 1;
parameter S_waiting = 2; 

input   [  1: 0] 	address;
input            	chipselect;
input            	a_50_MHZ_CLK;
input            	reset_n;
input            	write_n;
input   [ 31: 0] 	writedata;
output  [ 31: 0] 	readdata;
output 	[1:0] 		  pwmDrive; 
output				done; 

// output registers. 
reg 	[1:0] 		pwmDrive;
reg 	[ 31: 0] 	readdata;
reg 				done; 

// register whose values will be written by Avalon Memory Master
reg 	[31:0] 		peroidReg; 
reg 	[7:0] 		cyclesReg;  // 32nd bit of cycles Reg is start Reg. 
reg					start; 

reg 	[31:0] 		peroidCount;
reg 				initializeData;  
reg 	[1:0] 		state, nextState;

wire    [  31: 0] 	read_mux_out;
wire				clk_en; 


  assign clk_en = 1;
  //s1, which is an e_avalon_slave
  assign read_mux_out = (({32 {(address == 0)}} & peroidReg)   | ({32 {(address == 1)}} & {23'h00 ,start, cyclesReg})); // nine bits. 
	
  always @(posedge a_50_MHZ_CLK or negedge reset_n)
    begin
      if (reset_n == 0)
          readdata <= 0;
      else if (clk_en)
		readdata <= read_mux_out;
          //readdata <= {{{32 - 8}{1'b0}},read_mux_out};
    end
	
	always @(posedge a_50_MHZ_CLK or negedge reset_n)
    begin
      if (reset_n == 0)
          peroidReg <= 0;
      else if (chipselect && ~write_n && (address == 0)) begin
          peroidReg <= writedata[31 : 0];
          peroidCount <= 0; 
        end
    end
	
	always @(posedge a_50_MHZ_CLK or negedge reset_n)
    begin
      if (reset_n == 0)
          {start, cyclesReg} <= 0;
      else if (chipselect && ~write_n && (address == 1))
          {start, cyclesReg} <= writedata[8 : 0];
    end	

always @ (posedge a_50_MHZ_CLK) begin
	if( 	reset_n == 0) begin
		state <= S_idle;
	end
	else begin
		state <= nextState;	
	end
end	

always @ ( * ) begin
	done = 0;
	pwmDrive[0] = 0;
	pwmDrive[1] = 0;	
	case ( state )	
		S_idle: begin
			done = 1;
			if( reset_n == 0) nextState = S_idle; 
			else begin
				if( cyclesReg > 0) begin
					nextState = S_pwm; 
				end			
			end		
		end
		S_pwm: begin
			if( reset_n == 0) nextState = S_idle; 
			else begin
				if( cyclesReg > 0) begin
					pwmDrive[0] = ~cyclesReg[0];
					pwmDrive[1] = cyclesReg[0];	
					done = 0;
				end
				else begin
					nextState = S_idle; 				
				end
			end
		end
	endcase
end

always@(posedge a_50_MHZ_CLK) begin
	if( peroidCount < peroidReg ) begin
		peroidCount <= peroidCount + 1; 
	end
	else begin
		peroidCount <= 0; 
		if( cyclesReg > 0 )
			cyclesReg <= cyclesReg - 1; 
	end
end
endmodule
