#include "cdef.h"
#include "subbitdec.h"

sbd_tstate sbd_state;

void sbd_init(void)
{
	//save restart and error
	u8 t1,t2;
	t1 = sbd_state.nr_errors;
	t2 = sbd_state.nr_restarts;
	memset(&sbd_state,0,sizeof(sbd_state));

	sbd_state.nr_errors = t1;
	sbd_state.nr_restarts = t2;
}

u8 sbd_getbitval(u16 time)
{
	u16 const t = sbd_bittime;
	u16 const d = sbd_bittolerance;

	if(  (time>=(1*t-d)) && (time<(1*t+d))  ) return 0x10;
	if(  (time>=(2*t-d)) && (time<(2*t+d))  ) return 0x11;
	if(  (time>=(sbd_starttime-d)) && (time<(sbd_starttime+d))  ) return 0x15;

	//just for testing end of transmission
	//if(  (time>=(4*t-d)) && (time<(4*t+d))  ) return 0xff;

	//todo maybe differentiate between longer than start and small spikes
	return 0;	
}


void add_bit(char bb)
{
	sbd_state.recbuffer[sbd_state.b] |= (bb<<(7-sbd_state.i));

	if(sbd_state.i==7)
	{
		sbd_state.i = 0;
		sbd_state.b++;		
	}
	else
	{
		sbd_state.i++;
	}
}


void sbd_decode(u16 time)
{
	u8 bit = sbd_getbitval(time);
	switch (sbd_state.recstate)
	{
	case idle:
		if(bit == 0x15)
		{
			sbd_init();
			sbd_state.recstate = receiving;
			sbd_state.nr_restarts++;
		}
		else
		{
			//ignor other bits or errors
		}
		break;
	case receiving:
		switch (bit)
		{
		case 0x10:
			// 0 bit decoded
			add_bit(0);
			break;
		case 0x11:
			// 1 bit decoded
			add_bit(1);
			break;
		case 0x15:
			// start (error reinit)	
			{				
				sbd_init();
				sbd_state.nr_restarts++;
				sbd_state.recstate = receiving;
			}
			break;
		case 0:
			{
				//error reinit				
				//sbd_init(); ignore error
				//sbd_state.recstate = idle;
				sbd_state.nr_errors++;
			}
			break;
		case 0xff:
			// end of transmission
			break;
		}
		break;
	case done:
		break;
	}
}
