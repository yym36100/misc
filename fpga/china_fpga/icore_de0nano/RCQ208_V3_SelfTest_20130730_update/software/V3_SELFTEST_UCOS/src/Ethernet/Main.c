

//==============================================================================
//RedCore RCQ208_V3 Ethernet (EN28J60) Example
//==============================================================================
#include <stdio.h>
#include "includes.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "types.h"
#include "Main.h"
#include "fpga_io.h"


void delay_ETH_us(UINT32 i)
{
	UINT8 j = 50;
	while(--i)
	{
	 while(j--);
	}
}
//----------------------------------------------------------------------------
//	END OF FILE
//----------------------------------------------------------------------------

