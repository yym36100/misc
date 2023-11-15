/*------------------------------------------------------
   FILE NAME   :frequency.c
   DESCRIPTION : iBoard frequency driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2011-12-18
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\evtft.h"
#include "..\include\gui_core.h"
#include "..\include\font.h"
#include "..\include\title.h"
#include "..\include\waveform.h"
#include "..\include\config.h"
#include "..\include\main.h"
#include "..\include\fpga.h"
#include "..\include\frequency.h"
#include <math.h>
#include <string.h>
//---------------- Function Prototype -------------------//
static int set(double freq);
//---------------- Variable -----------------------------//
const FREQUENCY_T frequency = {
	.set = set
};

//-----------------Function------------------------------//
/*-------------------------------------------------------
   NAME       : ---
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
set(double freq)
{
	double temp = 281474976710656. / 100000000.;
	unsigned long long int fword;

	if (freq > 10000000. || freq < 0.) return -1;

	temp *= freq;
	fword = temp;

	fpga_ctl.b.ctl1 = 0;
	fpga_ctl.b.ctl2 = 0;
	fpga_ctl.b.ctl3 = 0;
	fpga.ctl();

	FPGA_WR2 = (fword >> 32) & 0xffff;

	fpga_ctl.b.ctl1 = 1;
	fpga_ctl.b.ctl2 = 0;
	fpga_ctl.b.ctl3 = 0;
	fpga.ctl();

	FPGA_WR2 = (fword >> 16) & 0xffff;

	fpga_ctl.b.ctl1 = 0;
	fpga_ctl.b.ctl2 = 1;
	fpga_ctl.b.ctl3 = 0;
	fpga.ctl();

	FPGA_WR2 = fword & 0xffff;

	return 0;
}

