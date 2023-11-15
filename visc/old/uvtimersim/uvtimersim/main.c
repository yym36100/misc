#include "pic18.h"
#include "cdef.h"

#include "keyb.h"

u8 m,s;
u8 buffer[10];


void app_vInit(void)
{
	m=12;
	s=34;
	DBG_vMessage("InitReset");
}

#define hellotime	(40)
#define blinkcycle	(10)
#define timerblink	(20)
#define expiredblink	(5)
//#define seccycle	(40)
#define seccycle	(2)
//#define alarmtime	(400)
#define alarmtime	(40)
enum estate{noinit,hello,ready,timing,expired,freerun,pause};
u8 state = noinit;
u16 cnt;

typedef struct ttimer{
	u8 m,s,l;
	u8 seccnt;
	u16 alarmcnt;
}ttimer;

typedef struct tadjust{
	u8 md1,md2,nrlamp;
	u8 adjust;
	u8 blinkphase;
	u8 blinkcnt;
}tadjust;

tadjust adjust = { 3,0,4,1,0,blinkcycle};
ttimer timer = {30,0,4,seccycle,0};

void app_v25Active(void)
{
	keyb_processbuttons();
	switch(state)
	{
	case noinit:
		cnt = hellotime;
		state = hello;
		DBG_vMessage("S/R = select/reset");
		DBG_vMessage("A/P = adjust/play-puase");
		DBG_vMessage("nrlamps-:minutes");
		DBG_vMessage("BEEP");
		break;
	case hello:
		if(--cnt==0)
		{
			state = ready;
			DBG_vMessage("ready");

		}
		else
		{
			sprintf(buffer,"88:88");
		}		
		break;
	case ready:
		if(--adjust.blinkcnt==0)
		{
			adjust.blinkphase ^= 1;
			adjust.blinkcnt = blinkcycle;
		}

		switch(adjust.adjust)
		{
		case 0:		
			if(butt[1].p||butt[1].h)
			{				
				if(++adjust.nrlamp==5)
					adjust.nrlamp=1;
				sprintf(buffer,"%c-:%c%c",'0'+adjust.nrlamp,'0'+adjust.md1,'0'+adjust.md2);
			}
			else
				sprintf(buffer,"%c-:%c%c",adjust.blinkphase?'0'+adjust.nrlamp:'_','0'+adjust.md1,'0'+adjust.md2);				
			if(butt[0].p) adjust.adjust=1;
			break;
		case 1:
			sprintf(buffer,"%c%c:%c%c",'0'+adjust.nrlamp,adjust.blinkphase?'-':'_','0'+adjust.md1,'0'+adjust.md2);
			if(butt[0].p) adjust.adjust=2;
			if(butt[1].p)
			{
				if(adjust.md1==0 && adjust.md2==0)
				{
					;
				}
				else
				{
				DBG_vMessage("timer started");
				state = timing;
				timer.l=adjust.nrlamp;
				timer.m = adjust.md1*10+adjust.md2;
				timer.s = 0;
				adjust.blinkcnt = timerblink;
				}
			}
			break;
		case 2:

			if(butt[1].p||butt[1].h)
			{
				adjust.md1++;
				if(adjust.md1==10)
					adjust.md1=0;

				sprintf(buffer,"%c-:%c%c",'0'+adjust.nrlamp,'0'+adjust.md1,'0'+adjust.md2);
			}
			else
				sprintf(buffer,"%c-:%c%c",'0'+adjust.nrlamp,adjust.blinkphase?'0'+adjust.md1:'_','0'+adjust.md2);				
			if(butt[0].p) adjust.adjust=3;
			break;
		case 3:
			if(butt[1].p||butt[1].h)
			{
				adjust.md2++;
				if(adjust.md2==10)
					adjust.md2=0;

				sprintf(buffer,"%c-:%c%c",'0'+adjust.nrlamp,'0'+adjust.md1,'0'+adjust.md2);
			}
			else
				sprintf(buffer,"%c-:%c%c",'0'+adjust.nrlamp,'0'+adjust.md1,adjust.blinkphase?'0'+adjust.md2:'_');

			if(butt[0].p) adjust.adjust=0;
		}
		break;
	case timing:
		if(--adjust.blinkcnt==0)
		{
			adjust.blinkphase ^= 1;
			adjust.blinkcnt = timerblink;
		}
		sprintf(buffer,"%02d%c%02d",timer.m,adjust.blinkphase?':':' ',timer.s);

		if(--timer.seccnt == 0)
		{
			timer.seccnt = seccycle;
			if(timer.s-- == 0)
			{
				timer.s = 59;
				if(timer.m--==0)
				{
					DBG_vMessage("timer expired");
					state = expired;
					adjust.blinkcnt = expiredblink;
					timer.alarmcnt = alarmtime;
				}
			}				
		}
		if(butt[0].p)
		{
			DBG_vMessage("reset");
			state = ready;
		}
		if(butt[1].p)
		{
			DBG_vMessage("pause");
			state = pause;
		}
		break;
	case pause:
		if(--adjust.blinkcnt==0)
		{
			adjust.blinkphase ^= 1;
			adjust.blinkcnt = timerblink;
		}
		if(adjust.blinkphase)
			sprintf(buffer,"%02d%c%02d",timer.m,':',timer.s);
		else
			sprintf(buffer,"     ");
		if(butt[0].p)
		{
			DBG_vMessage("reset");
			state = ready;
		}
		if(butt[1].p)
		{
			DBG_vMessage("resume");
			state = timing;
		}

		break;

	case expired:
		if(adjust.blinkcnt--==0)
		{
			adjust.blinkphase ^= 1;
			adjust.blinkcnt = expiredblink;
		}

		if(adjust.blinkphase)
			sprintf(buffer,"--:--");
		else sprintf(buffer,"     ");

		if(timer.alarmcnt--==0)
		{
			DBG_vMessage("free running");
			state = freerun;
			timer.m = 0;
			timer.s = 0;
			adjust.blinkcnt = timerblink;
		}
		if(butt[0].p)
		{
			DBG_vMessage("free running");
			state = freerun;
			timer.m = 0;
			timer.s = 0;
			adjust.blinkcnt = timerblink;
		}
		else if(butt[1].p)
		{
			DBG_vMessage("reset");
			state = ready;
			adjust.blinkcnt = timerblink;
		}
		break;

	case freerun:
		if(--adjust.blinkcnt==0)
		{
			adjust.blinkphase ^= 1;
			adjust.blinkcnt = timerblink;
		}
		sprintf(buffer,"%02d%c%02d",timer.m,adjust.blinkphase?':':' ',timer.s);

		if(--timer.seccnt == 0)
		{
			timer.seccnt = seccycle;
			if(timer.s++ == 60)
			{
				timer.s = 0;
				if(timer.m++==60)
				{
					timer.m=0;					
				}
			}			
		}
		if(butt[0].p || butt[1].p)
		{
			DBG_vMessage("reset");
			state = ready;
		}
		break;
	}


	DISP_vUpdate(buffer);
}