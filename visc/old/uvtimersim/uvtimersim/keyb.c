#include "keyb.h"

keyb_bs butt[keyb_nrbutt];


void keyb_processbuttons(void)
{
	u8 i;

	for(i=0;i<keyb_nrbutt;i++)
	{
		butt[i].cs = buttonstate[i];

		if(butt[i].cs)
		{
			if(butt[i].cnt<keyb_debtime)
				butt[i].cnt++;
		}
		else
			butt[i].cnt = 0;
		if(butt[i].cs && !butt[i].os)
			butt[i].p = 1;
		else
			butt[i].p = 0;
		if(butt[i].cs && butt[i].cnt==keyb_debtime)
			butt[i].h = 1;
		else
			butt[i].h = 0;

		butt[i].os = butt[i].cs;
	}
}