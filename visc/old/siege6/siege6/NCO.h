#pragma once
#include "cdef.h"

class CNCO
{
public:

	enum {
		NR_SAMPLES = 64,
		MAX_AMPL = 256,
	};

	u32 phAcc;
	u32 phInc;
	u8 pac[NR_SAMPLES];
	u8 sign;

	CNCO(void)
		:phAcc(0),phInc(1)
	{
		buildPAC();
	}

	void buildPAC(void)
	{
		for(u16 i=0;i<NR_SAMPLES;i++)
		{
			pac[i] = MAX_AMPL * sin( 2*3.14159265/4.0 * i/NR_SAMPLES);
		}
	}

	u16 phase2index(u16 phase)
	{
		u16 idx;
		if(phase < 1 * NR_SAMPLES)
		{
			sign = 0;
			idx = phase;
		}
		else if((phase >= 1 * NR_SAMPLES) && (phase < 2* NR_SAMPLES))
		{
			//q2
			sign = 0;
			idx = 2* NR_SAMPLES - 1 - phase;
		}
		else if((phase >= 2 * NR_SAMPLES) && (phase < 3* NR_SAMPLES))
		{
			//q3
			sign = 1;
			idx = phase - 2 * NR_SAMPLES;
		}
		else 
		{
			//q4
			sign = 1;
			idx = 4 * NR_SAMPLES - 1 - phase;
		}
		return idx;
	}

	~CNCO(void)
	{
	}

	void setFreq(u32 freq)
	{
		phInc = freq;
	}

	i16 getVal(void)
	{
		u16 idx = phase2index(phAcc>>16);
		u16 val;
		phAcc +=phInc;

		if((phAcc>>16)>=(4*NR_SAMPLES))
		{
			phAcc-=((4*NR_SAMPLES)<<16);
		}
		u16 res = 1;
		
		val =pac[idx];
		if (sign==1) val=-val;
		return val;
	}
};
