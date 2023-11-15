
#include <stdio.h>

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

typedef unsigned char  UINT8;
typedef unsigned short UINT16;

//#define TUBE_BASE	    	0x04002290
//#define TUBE_BUS_BASE		0x04002040

#define	SET_TUBE_EN(data)	IOWR_ALTERA_AVALON_PIO_DATA(TUBE_EN_BASE, data);
#define	SET_TUBE_BUS(data)	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, data);

#define	SH		(0x01 << 7)
#define	SG		(0x01 << 14)
#define	SF		(0x01 << 8)
#define	SE		(0x01 << 9)
#define	SD		(0x01 << 10)
#define	SC		(0x01 << 11)
#define	SB		(0x01 << 12)
#define	SA		(0x01 << 13)

const UINT16 DIGData[] =
{
	SA |SB |SC | SD |SE |SF,		//0
	SB | SC,						//01
	SA |SB |SG | SE | SD,			//02
	SA |SB |SC | SD | SG,			//03
	SB |SF | SG | SC,				//04
	SA |SF |SG |SC  | SD,			//05
	SA |SC | SD | SE | SG | SF,	//06
	SA | SB| SC,					//07
	SA |SB |SC | SD | SE | SF | SG,//08
	SA |SB |SC|SD | SF | SG	,	//09
	0,							//mask - 10	
	SG							//minus - 11		
};

void Refresh_LED(UINT16 dat);

void Digital_tube_main(void)
{
	UINT16 i,j,k;
	k = 2000;
	while(k--)
	{
		Refresh_LED(1234);
		delay_ms(2);
	}
	SET_TUBE_EN(0x0f);
	
}

void Refresh_LED(UINT16 dat)
{
	static UINT8 i = 0;	
	UINT8 a,b,c,d;

	a = dat /1000;
	b = dat % 1000 /100;
	c = dat % 1000 % 100 /10;
	d = dat % 1000 % 100 % 10;	

	//printf("\ra = %d,b = %d,c = %d,d = %d\n",a,b,c,d);
	
	switch(i)
	{
		case 0:
		i++;
		SET_TUBE_EN(~(0x01 << 0));	
		SET_TUBE_BUS(~DIGData[d]);
		break;
			
		case 1:
		i++;
		SET_TUBE_EN(~(0x01 << 1));			
		SET_TUBE_BUS(~DIGData[c]);
		break;
			
		case 2:
		i++;
		SET_TUBE_EN(~(0x01 << 2));		
		SET_TUBE_BUS(~DIGData[b]);
		break;
			
		case 3:
		i = 0;
		SET_TUBE_EN(~(0x01 << 3));			
		SET_TUBE_BUS(~DIGData[a]);
		break;

		default:
		i = 0;
		SET_TUBE_EN(0x0f);			
		SET_TUBE_BUS(0xff);
		break;	
			
	}

}

