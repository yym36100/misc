/*------------------------------------------------------
   FILE NAME   : fpga.c
   DESCRIPTION : fpga driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\fpga.h"

//---------------- Function Prototype -------------------//

static int initialize(void);
static int ctl(void);


//---------------- Variable -----------------------------//

FPGA_T fpga = {
	.initialize = initialize,
	.ctl = ctl
};


FPGA_CTL_T fpga_ctl;

//-----------------Function------------------------------//

/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int initialize(void)
{
	fpga_ctl.w = 0;

	return 0;
}

/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int ctl(void)
{
	FPGA_CTL0 = (fpga_ctl.w & 0xffff);
	FPGA_CTL1 = (fpga_ctl.w >> 16);

	return 0;
}
