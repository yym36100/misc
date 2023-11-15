/*------------------------------------------------------
   FILE NAME   :offset.c
   DESCRIPTION : iBoard offset driver
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
#include "..\include\offset.h"
#include "..\include\dac.h"
#include <math.h>
#include <string.h>
//---------------- Function Prototype -------------------//
static int set(double offset);
//---------------- Variable -----------------------------//
const OFFSET_T offset = {
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
set(double offs)
{
	if (offs > 5. || offs < -5.) return -1;

	offs /= 5.;

	offs += 1.24;

	dac.arb_offset = offs;
	dac.set();

	return 0;
}

