/*------------------------------------------------------
   FILE NAME   :waveform.c
   DESCRIPTION : iBoard ARB --> waveform driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2011-12-18
   MODIFY DATE :
   LOGS        :-\r
   --------------------------------------------------------*/

//---------------- Include files ------------------------//
#include "..\include\waveform.h"
#include "..\include\config.h"
#include "..\include\main.h"
#include "..\include\fpga.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//---------------- Function Prototype -------------------//
static int set(int wave, float sp);
//---------------- Variable -----------------------------//
WAVEFORM_T waveform = {
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
static int set(int wave, float sp)
{
	int i;
	float temp, temp1, temp2;

	sp /= 100.;

	fpga_ctl.b.ctl1 = 0;
	fpga_ctl.b.ctl2 = 0;
	fpga_ctl.b.ctl3 = 1;
	fpga_ctl.b.ctl6 = 1;
	fpga.ctl();

	switch (wave) {
//----------------------------------------//
	case SINE:
		for (i = 0; i < 4096; i++) {
			temp = i;
			temp /= 4096;
			temp *= 2;
			temp *= 3.1415926;
			temp = sin(temp);
			temp += 1;
			temp /= 2.0;
			temp *= 255;

			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case SQUA:
		for (i = 0; i < 4096; i++) {
			if (i < sp * 4095)
				temp = 255;
			else
				temp = 0;

			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case TRI:
		temp1 = 4095 * sp;

		temp = 0;
		for (i = 0; i < 4096; i++) {
			if (temp1 == 0) {
				temp = 4095 - i;
				temp /= 16.;
			} else {
				if (i < temp1) {
					temp = 4095;
					temp /= temp1;
					temp *= i;

					temp /= 16.;
				} else {
					temp = 4095 - temp1;
					temp = 4095 / temp;
					temp *= (i - temp1);
					temp = 4095 - temp;

					temp /= 16.;
				}
			}

			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case RAMP:
		for (i = 0; i < 4096; i++) {
			temp = i / 16.;
			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case NRAM:
		for (i = 0; i < 4096; i++) {
			temp = (4095 - i) / 16.;
			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case SINC:
		for (i = -2048; i < 2048; i++) {
			temp = 20. * PI;
			temp /= 4096.;

			temp *= i;
			temp1 = temp;
			temp = sin(temp);
			temp /= temp1;

			temp += 1;
			temp *= 128;
			if (i == 0)
				temp = 255;
			temp2 = temp;

			FPGA_WR2 = temp2;
		}
		break;
//----------------------------------------//
	case EXPR:
		for (i = 0; i < 4096; i++) {
			temp = i;
			temp /= 4096;
			temp *= 99;
			temp += 1;
			temp = log10(temp);
			temp *= 128;

			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case EXPF:
		for (i = 0; i < 4096; i++) {
			temp = i;
			temp /= 4096;
			temp *= 99;
			temp += 1;
			temp = log10(temp);
			temp *= 128;

			FPGA_WR2 = 255 - temp;
		}
		break;
//----------------------------------------//
	case NOISE:
		srand(0);
		for (i = 0; i < 4096; i++) {
			FPGA_WR2 = rand() % 255;
		}
		break;
//----------------------------------------//
	case FULL_SIN_P:
		for (i = 0; i < 4096; i++) {
			temp = i;
			temp /= 4096;
			temp *= 2;
			temp *= 3.1415926;
			temp = sin(temp);
			temp += 1;
			temp /= 2.0;
			temp *= 255;

			if (i > 2048)
				temp = 255 - temp;

			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case FULL_SIN_N:
		for (i = 0; i < 4096; i++) {
			temp = i;
			temp /= 4096;
			temp *= 2;
			temp *= 3.1415926;
			temp = sin(temp);
			temp += 1;
			temp /= 2.0;
			temp *= 255;

			if (i < 2048)
				temp = 255 - temp;

			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case HALF_SIN_P:
		for (i = 0; i < 4096; i++) {
			if (i < 2048) {
				temp = i;
				temp /= 4096;
				temp *= 2;
				temp *= 3.1415926;
				temp = sin(temp);
				temp += 1;
				temp /= 2.0;
				temp *= 255;
			} else
				temp = 128;

			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case HALF_SIN_N:
		for (i = 0; i < 4096; i++) {
			if (i < 2048) {
				temp = i;
				temp /= 4096;
				temp *= 2;
				temp *= 3.1415926;
				temp = sin(temp);
				temp += 1;
				temp /= 2.0;
				temp *= 255;
				temp = 255 - temp;
			} else
				temp = 128;

			FPGA_WR2 = temp;
		}
		break;
//----------------------------------------//
	case GAUSSIAN:
		for (i = -2048; i < 2048; i++) {
			temp = i;
			temp /= 410;
			temp = temp * temp;

			temp /= 2;
			temp = -temp;
			temp = pow(E, temp);
			temp2 = temp * 255;

			FPGA_WR2 = temp2;
		}
		break;
//----------------------------------------//
	case DC:
		for (i = 0; i < 4096; i++) {
			FPGA_WR2 = 128;
		}
		break;
	}



	fpga_ctl.b.ctl6 = 0;
	fpga.ctl();

	return 0;
}
