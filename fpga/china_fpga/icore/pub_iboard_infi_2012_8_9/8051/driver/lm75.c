/*------------------------------------------------------
   FILE NAME   : adc.c
   DESCRIPTION : adc driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/


//-----------------Include files-------------------------//


#include "..\include\i2c.h"
#include "..\include\lm75.h"


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
/*static int initialize(void)
   {

        return 0;
   }  */

/*-------------------------------------------------------
   NAME       : read
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
float
lm75_read(void)
{
	short int dat;
	float f;

	read_nbyte(LM75, 0, (unsigned char*)(&dat), 2);

	f = dat;
	f /= 32.0;
	f *= 0.125;

	return f;
}

