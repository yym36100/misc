/*------------------------------------------------------
   FILE NAME   : key.c
   DESCRIPTION : main function
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------/
#include "..\include\stc11fxx.h"
#include "..\include\key.h"
#include <intrins.h>

//---------------- Function Prototype -------------------/
//---------------- Variable -----------------------------/

sbit KEYOUT0 = P2 ^ 4;
sbit KEYOUT1 = P2 ^ 5;
sbit KEYOUT2 = P2 ^ 6;
sbit KEYOUT3 = P2 ^ 7;

sbit KEYDOWN = P2 ^ 3;
sbit KEYUP = P1 ^ 0;


unsigned char event = 0;
//---------------- Function -----------------------------//

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
unsigned char read_key(void)
{
	unsigned char i;
	code unsigned char weight[4] = { 0x7f, 0xbf, 0xdf, 0xef };


	if (KEYDOWN == 0) return KEY_DOWN;
	if (KEYUP == 0) return KEY_UP;

	for (i = 0; i < 4; i++) {
		P2 = weight[i];
		if ((P2 & 0x0f) != 0x0f) return P2;
	}
	return 0;
}