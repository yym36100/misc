/*------------------------------------------------------
   FILE NAME   :diagram.c
   DESCRIPTION : iBoard diagram
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
#include "..\include\diagram.h"
#include "..\include\waveform.h"
#include "..\include\config.h"
#include "..\include\main.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
//---------------- Function Prototype -------------------//
static int show(int active, float fpar);


//---------------- Variable -----------------------------//
const DIAGRAM_T diagram = {
	.show = show
};

static int ramp_buffer[7][2];
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
show_grid(void)
{
	int i;
	BOX_T b;

	b.startx = 180;
	b.starty = 60;
	b.endx = 395;
	b.endy = 176;
	b.attrib = BOX_RECESSED;
	b.color = COLOR_BLACK;
	gui.box(&b);

	for (i = 0; i <= 8; i++) gui.line(182, 62 + i * 14, 392, 62 + i * 14, make_rgb565(44, 71, 0));

	for (i = 0; i <= 15; i++) gui.line(182 + i * 14, 62, 182 + i * 14, 174, make_rgb565(44, 71, 0));


	return 0;
}

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
static int make_tri_data(float spar)
{
	ramp_buffer[0][0] = 182 + 35 * 0;
	ramp_buffer[0][1] = 173;

	ramp_buffer[1][0] = 182 + 35 * (spar * 2);
	ramp_buffer[1][1] = 63;

	ramp_buffer[2][0] = 182 + 35 * 2;
	ramp_buffer[2][1] = 173;

	ramp_buffer[3][0] = 182 + 35 * (2 + spar * 2);
	ramp_buffer[3][1] = 63;

	ramp_buffer[4][0] = 182 + 35 * 4;
	ramp_buffer[4][1] = 173;

	ramp_buffer[5][0] = 182 + 35 * (4 + spar * 2);
	ramp_buffer[5][1] = 63;

	ramp_buffer[6][0] = 182 + 35 * 6;
	ramp_buffer[6][1] = 173;


	return 0;
}
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
show(int active, float spar)
{
	int i;
	float f, f1;
	int point[14][2] = {
		{ 182 + 35 * 0, 63 },
		{ 182 + 35 * 0, 173 },
		{ 182 + 35 * (2 - spar * 2), 173 },
		{ 182 + 35 * (2 - spar * 2), 63 },
		{ 182 + 35 * 2, 63 },
		{ 182 + 35 * 2, 173 },
		{ 182 + 35 * (2 + 2 - spar * 2), 173 },
		{ 182 + 35 * (2 + 2 - spar * 2), 63 },
		{ 182 + 35 * 4, 63 },
		{ 182 + 35 * 4, 173 },
		{ 182 + 35 * (4 + 2 - spar * 2), 173 },
		{ 182 + 35 * (4 + 2 - spar * 2), 63 },
		{ 182 + 35 * 6, 63 },
		{ 182 + 35 * 6, 173 },
	};

	show_grid();

	switch (active) {
	case SINE:
		gui.set_cursor(182, 118);
		for (i = 0; i <= 210; i++) {
			f = i;
			f *= PI;
			f *= 2;
			f /= 70;
			f = sin(f);
			f *= -55;

			if (f < 0) f = ceil(f);
			else f = floor(f);

			gui.line_to(182 + i, 118 + f, COLOR_LIME);
		}
		break;
	case SQUA:
		gui.set_cursor(182, 118);

		for (i = 0; i < 14; i++) {
			gui.line_to(point[i][0], point[i][1], COLOR_LIME);
		}
		break;

	case TRI:
		gui.set_cursor(182, 173);

		make_tri_data(spar);
		for (i = 0; i < 7; i++) {
			gui.line_to(ramp_buffer[i][0], ramp_buffer[i][1], COLOR_LIME);
		}
		break;
	case RAMP:
		gui.set_cursor(182, 173);

		make_tri_data(1);

		for (i = 0; i < 7; i++) {
			gui.line_to(ramp_buffer[i][0], ramp_buffer[i][1], COLOR_LIME);
		}
		break;
	case NRAM:
		gui.set_cursor(182, 173);

		make_tri_data(0);

		for (i = 0; i < 7; i++) {
			gui.line_to(ramp_buffer[i][0], ramp_buffer[i][1], COLOR_LIME);
		}
		break;
	case SINC:
		gui.set_cursor(182, 117);

		for (i = -105; i < 105; i++) {
			f = 21 * PI / 210;
			f *= i;

			f1 = f;

			f = sin(f);
			f /= f1;

			f *= 55;
			f *= -1;
			if (i == 0) f = -55;


			if (f < 0) f = ceil(f);
			else f = floor(f);

			gui.line_to(182 + i + 105, 118 + f, COLOR_LIME);
		}
		break;
	case NOISE:

		gui.set_cursor(182, 118);
		srand(0);
		for (i = 0; i <= 210; i++) {
			f = rand() % 100;
			f -= 55;

			gui.line_to(182 + i, 118 + f, COLOR_LIME);
		}

		break;
	case EXPR:

		gui.set_cursor(182, 173);
		for (i = 0; i < 210; i++) {
			f = i;
			f /= 210;
			f *= 99;
			f += 1;
			f = log10(f);
			f *= 55;
			f -= 55;

			f *= -1;

			gui.line_to(182 + i, 118 + f, COLOR_LIME);
		}

		break;
	case EXPF:

		gui.set_cursor(182, 63);
		for (i = 0; i < 210; i++) {
			f = i;
			f /= 210;
			f *= 99;
			f += 1;
			f = log10(f);
			f *= 55;
			f -= 55;

			gui.line_to(182 + i, 118 + f, COLOR_LIME);
		}

		break;
	case FULL_SIN_P:
		gui.set_cursor(182, 118);
		for (i = 0; i <= 210; i++) {
			f = i;
			f *= PI;
			f *= 2;
			f /= 70;
			f = sin(f);
			f *= 55;
			f *= -1;

			if (f > 0) f *= -1;

			if (f < 0) f = ceil(f);
			else f = floor(f);

			gui.line_to(182 + i, 118 + f, COLOR_LIME);
		}
		break;
	case FULL_SIN_N:
		gui.set_cursor(182, 118);
		for (i = 0; i <= 210; i++) {
			f = i;
			f *= PI;
			f *= 2;
			f /= 70;
			f = sin(f);
			f *= 55;
			f *= -1;

			if (f < 0) f *= -1;

			if (f < 0) f = ceil(f);
			else f = floor(f);

			gui.line_to(182 + i, 118 + f, COLOR_LIME);
		}
		break;
	case HALF_SIN_P:
		gui.set_cursor(182, 118);
		for (i = 0; i <= 210; i++) {
			f = i;
			f *= PI;
			f *= 2;
			f /= 70;
			f = sin(f);
			f *= 55;
			f *= -1;

			if (f > 0) f = 0;

			if (f < 0) f = ceil(f);
			else f = floor(f);

			gui.line_to(182 + i, 118 + f, COLOR_LIME);
		}
		break;
	case HALF_SIN_N:
		gui.set_cursor(182, 118);
		for (i = 0; i <= 210; i++) {
			f = i;
			f *= PI;
			f *= 2;
			f /= 70;
			f = sin(f);
			f *= 55;
			f *= -1;

			if (f < 0) f = 0;

			if (f < 0) f = ceil(f);
			else f = floor(f);

			gui.line_to(182 + i, 118 + f, COLOR_LIME);
		}
		break;
	case GAUSSIAN:
		gui.set_cursor(182, 170);
		for (i = -105; i <= 105; i++) {
			f = i;
			f /= 42;
			f = f * f;
			f = pow(E, -f);
			f1 = (f - .5) * -105;

			if (f1 < 0) f = ceil(f1);
			else f1 = floor(f1);

			gui.line_to(182 + i + 105, 118 + f1, COLOR_LIME);
		}
		break;

	case DC:
		gui.set_cursor(182, 117);

		gui.line_to(182 + 210, 117, COLOR_LIME);

		break;
	default:
		break;
	}

	return 0;
}
