#include "../inc/common.h"
#include "../inc/hal.h"
#include "../inc/hpi.h"
#include "../inc/hpi32.h"

extern FLAGS bFlags;
extern unsigned char UARTBUF[UARTBUF_LENGTH];
extern Command_Def Command;			
//////////////////////////////////////////
void ISR_COMM(void)
{
#if 0
	unsigned char *pBuf=(unsigned char *)&Command;  //Low Bit at Head
	unsigned long timecount;
	unsigned int cnt;
	
	MCU_LED3=0;

	if(RI==0)
	{
		MCU_LED3=1;
		return;
	}

	for(cnt=0;cnt<37;cnt++)
	{
		timecount=0;
		while(!RI && ++timecount<20005);
		if(timecount > 20000)	
		{
			Command.CLass=0xff;
			bFlags.bits.bUartInDone=1;
			RI=0;
			MCU_LED3=1;
			return;
		}		
		*(pBuf+cnt)=SBUF;
		RI=0;
	}
	
	/////// data phase /////////////////////
	if(Command.CLass == 0x04 || \
	   Command.CLass == 0x05 || \
	   Command.CLass == 0x09) ///GreatFile/GreatDir/WriteFile
	{
		if(Command.len > MAX_WRITE_LENGTH)
		{
			Command.CLass=0xff;
			bFlags.bits.bUartInDone=1;
			MCU_LED3=1;
			return;
		}

		for(cnt=0; cnt<Command.len; cnt++)
		{
			timecount = 0;
			while(!RI && ++timecount<20005);
			if(timecount > 20000)	
			{
				Command.CLass = 0xff;
				bFlags.bits.bUartInDone = 1;
				RI = 0;
				MCU_LED3 = 1;
				return;
			}
			UARTBUF[cnt] = SBUF;
			RI=0;
		}
	}	
	//////////////////////////
	bFlags.bits.bUartInDone=1;
	RI=0;	
	MCU_LED3=1;
#endif
}


