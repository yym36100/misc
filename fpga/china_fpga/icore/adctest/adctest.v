
module adctest(
	CLOCK_50,
	LED,

	ADC_CS_N,
	ADC_SADDR,
	ADC_SCLK,
	ADC_SDAT,
	
	top
	
);



input CLOCK_50;
output[7:0] LED;


// ADC
output ADC_CS_N;
output ADC_SADDR;
output ADC_SCLK;
input ADC_SDAT;

inout[33:0]top;

wire[11:0] adcdata;

//assign LED[6:0] = adcdata[11:5];
assign LED[6:0] = pos[6:0];

reg[5:0] slowclock;
always@(posedge CLOCK_50)
begin
	slowclock <= slowclock + 1;
end

adc myadc(
	1'b0,
	slowclock[5],
	3'b000,
	adcdata,
	
	ADC_CS_N,
	ADC_SADDR,
	ADC_SCLK,
	ADC_SDAT	
);

/// motor stuff

wire slowclock2;
wire[1:0] phase;
//wire dir;
wire dir;
assign dir = di;

reg[31:0] cnt;

always @(posedge CLOCK_50)
begin
	cnt<=cnt+1;
end

assign slowclock2 = cnt[19];
//assign dir = cnt[27];
assign LED[7] = di;

smc mysmc(slowclock2 & go,dir,phase);

//phase a
assign top[27] = phase[0];
assign top[33] = ~phase[0] ^ ~go;

//phase b
assign top[29] = phase[1];
assign top[31] = ~phase[1]^ ~go;

//-----------------------
// motor dir - pot pos
reg go;
reg di;
reg[7:0] pos;
wire[7:0] refpos;
assign refpos = adcdata[11:4];

always@( posedge slowclock2)
begin
	if( pos < refpos)
		begin
		pos<= pos +1;
		di <= 1;
		end
	if(pos > refpos)
		begin
		pos<= pos - 1;
		di <= 0;
		end
	if(pos == refpos)
		go <= 0;
	else
		go <= 1;

end


endmodule
