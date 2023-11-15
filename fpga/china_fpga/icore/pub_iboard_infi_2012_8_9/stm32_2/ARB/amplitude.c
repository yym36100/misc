/*------------------------------------------------------
   FILE NAME   : amplitude.c
   DESCRIPTION : iBoard frequency driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2011-12-18
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\config.h"
#include "..\include\main.h"
#include "..\include\fpga.h"
#include "..\include\amplitude.h"
#include "..\include\dac.h"
#include <math.h>
#include <string.h>
//---------------- Function Prototype -------------------//
static int set(double amp);
//---------------- Variable -----------------------------//
const AMPLITUDE_T amplitude = {
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
static int set(double amp)
{
	if (amp > 10. || amp < 0.)
		return -1;

	amp /= 11.6;
	amp *= VREF;

	dac.arb_amp = amp;
	dac.set();
	return 0;
}
