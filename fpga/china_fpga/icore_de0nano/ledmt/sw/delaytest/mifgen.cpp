#include <stdio.h>
#include <math.h>

unsigned short cnt, prev_cnt;
static unsigned short prev_bit, cur_bit;
bool bcm_wait(bool init)
{
	bool res = 0;
	if(init )
	{
		cnt = 1;
		prev_cnt = 0;
		prev_bit =1;
		cur_bit = 0;
	}
	else
	{
		for(int i = 12;i!=0;i--)
		{
			if(cnt & (1<<(i-1)))
			{
				cur_bit = i-1;
				if(prev_bit != cur_bit)
				{
					res = 1;
					printf("%5d : bit %2d [%5d]\n",cnt,cur_bit, cnt - prev_cnt);
					prev_cnt = cnt;
				}
				prev_bit = cur_bit;
				break;
			}
		}
		//if first bit changed, return 1
		cnt++;
		//if(cnt==4096) cnt = 1;
	}
	return res;
}


int main(int argc, char* argv[])
{

	int start = 0;
#define max (8)
	for(int i=0;i<max;i++)
	{
		printf("%d - %d %d %d %d %d %d %d %d \n",(i+start)%max, 
			(i^start+0),(i^start+1),(i^start+2),(i^start+3),(i^start+4),(i^start+5),(i^start+6),(i^start+7));
	}


#if 0
	int i = 0;
	bcm_wait(1);
	while(i++<9000)
	{
		bcm_wait(0);
	}
#endif
}

