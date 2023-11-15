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
#include "..\include\hardware.h"
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


	if(amp > 3.16){
		amp *= 1.;
		ATT_0DB;
	}else if(amp > 1.){
		amp *= 3.16;
		ATT_10DB;
	}else if(amp > 0.316){
		amp *= 10.;
		ATT_20DB;
	}else if(amp > 0.1){
		amp *= 31.6;
		ATT_30DB;
	}else if(amp > 0.0316){
		amp *= 100.;
		ATT_40DB;
	}else if(amp > 0.01){
		amp *= 316.;
		ATT_50DB;
	}else {
		amp *= 1000.;
		ATT_60DB;
	}

	amp /= 11.23;
	amp *= VREF;

	dac.arb_amp = amp;
	dac.set();
	return 0;
}
