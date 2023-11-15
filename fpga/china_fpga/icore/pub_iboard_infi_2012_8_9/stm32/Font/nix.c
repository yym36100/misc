/*------------------------------------------------------
   FILE NAME   : nix.c
   DESCRIPTION : nix
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-8
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include <string.h>
#include "..\include\font.h"
#include "..\include\config.h"


//---------------- Function Prototype -------------------//
static int get96(FONT_MATRIX_T *f);
static int get48(FONT_MATRIX_T *f);
//---------------- Variable -----------------------------//
extern const unsigned char rc_nix96[10][1332];

SINGLE_BYTE_FONT_T nix96 = {
	.name = "Nix96",
	.id = FONT_UNREGISTERED,
	.height = 111,
	.width = 96,
	.dat = (void*)rc_nix96,
	.get_matrix = get96,
	.pre = NULL,
	.next = NULL
};
extern const unsigned char rc_nix48[10][336];

SINGLE_BYTE_FONT_T nix48 = {
	.name = "Nix48",
	.id = FONT_UNREGISTERED,
	.height = 56,
	.width = 48,
	.dat = (void*)rc_nix48,
	.get_matrix = get48,
	.pre = NULL,
	.next = NULL
};
//-----------------Function------------------------------//
/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
get96(FONT_MATRIX_T *f)
{
	int i;
	int flag = 0;


	f->direction = DIRECTION_H;
	f->height = 111;
	f->width = 96;

	if (f->character[0] > 100) {
		f->character[0] -= 100;
		flag = 1;
	}

	switch (f->character[0]) {
	case '0':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[0][i] | rc_nix96[1][i] | rc_nix96[2][i] | rc_nix96[3][i] | rc_nix96[4][i] | rc_nix96[5][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '1':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[1][i] | rc_nix96[2][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '2':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[0][i] | rc_nix96[1][i] | rc_nix96[6][i] | rc_nix96[3][i] | rc_nix96[4][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '3':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[0][i] | rc_nix96[1][i] | rc_nix96[2][i] | rc_nix96[3][i] | rc_nix96[6][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '4':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[1][i] | rc_nix96[2][i] | rc_nix96[5][i] | rc_nix96[6][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '5':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[0][i] | rc_nix96[2][i] | rc_nix96[3][i] | rc_nix96[5][i] | rc_nix96[6][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '6':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[0][i] | rc_nix96[2][i] | rc_nix96[3][i] | rc_nix96[4][i] | rc_nix96[5][i] | rc_nix96[6][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '7':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[0][i] | rc_nix96[1][i] | rc_nix96[2][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '8':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[0][i] | rc_nix96[1][i] | rc_nix96[2][i] | rc_nix96[3][i] | rc_nix96[4][i] | rc_nix96[5][i] | rc_nix96[6][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '9':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[0][i] | rc_nix96[1][i] | rc_nix96[2][i] | rc_nix96[3][i] | rc_nix96[5][i] | rc_nix96[6][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case '-':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = (rc_nix96[6][i] | (flag ? rc_nix96[7][i] : 0));
		}
		break;
	case ':':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = rc_nix96[8][i];
		}

		break;
	case ' ':
		for (i = 0; i < 1332; i++) {
			font_buffer[i] = rc_nix96[9][i];
		}
		break;
	}

	f->dat = font_buffer;

	return 0;
}

/*-------------------------------------------------------
   NAME       : --
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
get48(FONT_MATRIX_T *f)
{
	int i;
	int flag = 0;


	f->direction = DIRECTION_H;
	f->height = 56;
	f->width = 48;

	if (f->character[0] > 100) {
		f->character[0] -= 100;
		flag = 1;
	}

	switch (f->character[0]) {
	case '0':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[0][i] | rc_nix48[1][i] | rc_nix48[2][i] | rc_nix48[3][i] | rc_nix48[4][i] | rc_nix48[5][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '1':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[1][i] | rc_nix48[2][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '2':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[0][i] | rc_nix48[1][i] | rc_nix48[6][i] | rc_nix48[3][i] | rc_nix48[4][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '3':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[0][i] | rc_nix48[1][i] | rc_nix48[2][i] | rc_nix48[3][i] | rc_nix48[6][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '4':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[1][i] | rc_nix48[2][i] | rc_nix48[5][i] | rc_nix48[6][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '5':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[0][i] | rc_nix48[2][i] | rc_nix48[3][i] | rc_nix48[5][i] | rc_nix48[6][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '6':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[0][i] | rc_nix48[2][i] | rc_nix48[3][i] | rc_nix48[4][i] | rc_nix48[5][i] | rc_nix48[6][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '7':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[0][i] | rc_nix48[1][i] | rc_nix48[2][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '8':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[0][i] | rc_nix48[1][i] | rc_nix48[2][i] | rc_nix48[3][i] | rc_nix48[4][i] | rc_nix48[5][i] | rc_nix48[6][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '9':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[0][i] | rc_nix48[1][i] | rc_nix48[2][i] | rc_nix48[3][i] | rc_nix48[5][i] | rc_nix48[6][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case '-':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = (rc_nix48[6][i] | (flag ? rc_nix48[7][i] : 0));
		}
		break;
	case ':':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = rc_nix48[8][i];
		}

		break;
	case ' ':
		for (i = 0; i < 336; i++) {
			font_buffer[i] = rc_nix48[9][i];
		}
		break;
	}

	f->dat = font_buffer;

	return 0;
}

