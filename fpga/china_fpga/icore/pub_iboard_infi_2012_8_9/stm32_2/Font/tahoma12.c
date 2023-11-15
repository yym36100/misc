/*------------------------------------------------------
   FILE NAME   : tahoma12.c
   DESCRIPTION : tahoma12
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-8
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/
/*
   #ASCII font offset file.
   #FONT NAME: Tahoma
   #FONT SIZE:12
   #FONT TYPE: visible ascii
   #FONT NUMBER:95
   #FONT LIST
   ---------------------
   !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
   ---------------------
 */

//---------------- Include files ------------------------//
#include "..\include\font.h"
#include <string.h>

//---------------- Function Prototype -------------------//
static int get(FONT_MATRIX_T *);

//---------------- Variable -----------------------------//
const short int tahoma12_offset[] = {
	//    !   "   #   $   %   &  '    (    )
	0, 9, 13, 19, 31, 40, 56, 67, 70, 76,
	// *   +   ,   -   .   /   0   1   2   3
	82, 91, 102, 107, 114, 119, 127, 137, 146, 155,
	// 4   5   6   7   8   9   :   ;   <
	164, 173, 182, 191, 200, 209, 218, 223, 230, 242,
	// =   >   ?   @   A   B   C   D   E   F
	255, 265, 274, 289, 300, 309, 319, 330, 339, 347,
	// G   H   I   J   K   L   M   N   O   P
	358, 369, 374, 382, 391, 399, 411, 422, 434, 443,
	// Q   R   S   T   U   V   W   X   Y   Z
	455, 465, 474, 484, 495, 505, 519, 528, 538, 547,
	// [   \   ]   ^   _   `   a   b   c   d
	553, 560, 566, 577, 587, 594, 603, 612, 619, 628,
	// e   f   g   h   i   j   k   l   m   n
	636, 641, 650, 659, 662, 668, 676, 680, 693, 703,
	// o   p   q   r   s   t   u   v   w   x
	712, 721, 730, 736, 743, 749, 758, 766, 778, 786,
	// y   z   {   |   }   ~
	794, 801, 810, 814, 823, 835
};

const char tahoma12_dat[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xD8, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x58, 0x09, 0xE0, 0x1E, 0x40, 0x68, 0x40,
	0x08, 0x40, 0x08, 0x58, 0x09, 0xE0, 0x1E, 0x40, 0x68, 0x40, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0E, 0x10, 0x11, 0x08, 0x11, 0x08, 0x7F, 0xFF, 0x10, 0x88, 0x10, 0x88, 0x08, 0x70, 0x00, 0x00,
	0x00, 0x00, 0x3E, 0x00, 0x41, 0x00, 0x41, 0x00, 0x41, 0x08, 0x41, 0x30, 0x3E, 0x40, 0x01, 0x80,
	0x06, 0x00, 0x09, 0xF0, 0x32, 0x08, 0x42, 0x08, 0x02, 0x08, 0x02, 0x08, 0x01, 0xF0, 0x00, 0x00,
	0x00, 0xE0, 0x39, 0x10, 0x46, 0x08, 0x42, 0x08, 0x43, 0x08, 0x44, 0x88, 0x38, 0x50, 0x00, 0x60,
	0x03, 0x90, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0,
	0x30, 0x0C, 0x40, 0x02, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x40, 0x02, 0x30, 0x0C,
	0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x28, 0x00, 0x10, 0x00, 0xFE, 0x00, 0x10, 0x00,
	0x28, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
	0x1F, 0xF0, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x1C, 0x00, 0xE0, 0x07, 0x00, 0x38, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1F, 0xE0, 0x20, 0x10, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x20, 0x10, 0x1F, 0xE0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x10, 0x08, 0x7F, 0xF8, 0x00, 0x08, 0x00, 0x08,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x18, 0x40, 0x28, 0x40, 0x48, 0x40, 0x88, 0x41, 0x08,
	0x22, 0x08, 0x1C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x40, 0x08, 0x42, 0x08, 0x42, 0x08,
	0x42, 0x08, 0x25, 0x10, 0x18, 0xE0, 0x00, 0x00, 0x01, 0x80, 0x02, 0x80, 0x04, 0x80, 0x08, 0x80,
	0x10, 0x80, 0x20, 0x80, 0x7F, 0xF8, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x10, 0x44, 0x08,
	0x44, 0x08, 0x44, 0x08, 0x44, 0x08, 0x42, 0x10, 0x41, 0xE0, 0x00, 0x00, 0x0F, 0xE0, 0x12, 0x10,
	0x24, 0x08, 0x44, 0x08, 0x44, 0x08, 0x44, 0x08, 0x42, 0x10, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00,
	0x40, 0x00, 0x40, 0x18, 0x40, 0x60, 0x41, 0x80, 0x46, 0x00, 0x58, 0x00, 0x60, 0x00, 0x00, 0x00,
	0x18, 0xE0, 0x25, 0x10, 0x42, 0x08, 0x42, 0x08, 0x42, 0x08, 0x42, 0x08, 0x25, 0x10, 0x18, 0xE0,
	0x00, 0x00, 0x1E, 0x00, 0x21, 0x08, 0x40, 0x88, 0x40, 0x88, 0x40, 0x88, 0x40, 0x90, 0x21, 0x20,
	0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x0C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x02, 0x80, 0x02, 0x80, 0x04, 0x40, 0x04, 0x40, 0x08, 0x20, 0x08, 0x20, 0x10, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40,
	0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x08, 0x20, 0x08, 0x20, 0x04, 0x40, 0x04, 0x40, 0x02, 0x80, 0x02, 0x80, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x40, 0xD8, 0x41, 0x00, 0x22, 0x00,
	0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x18, 0x18, 0x20, 0x04, 0x23, 0xC4, 0x44, 0x22,
	0x48, 0x12, 0x48, 0x12, 0x48, 0x12, 0x48, 0x22, 0x2F, 0xF0, 0x20, 0x10, 0x18, 0x10, 0x07, 0xE0,
	0x00, 0x00, 0x00, 0x18, 0x00, 0xE0, 0x07, 0x80, 0x38, 0x80, 0x40, 0x80, 0x40, 0x80, 0x38, 0x80,
	0x07, 0x80, 0x00, 0xE0, 0x00, 0x18, 0x00, 0x00, 0x7F, 0xF8, 0x42, 0x08, 0x42, 0x08, 0x42, 0x08,
	0x42, 0x08, 0x46, 0x08, 0x39, 0x10, 0x00, 0xE0, 0x00, 0x00, 0x0F, 0xC0, 0x30, 0x30, 0x20, 0x10,
	0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x20, 0x10, 0x00, 0x00, 0x7F, 0xF8,
	0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x20, 0x10, 0x20, 0x10, 0x18, 0x60,
	0x07, 0x80, 0x00, 0x00, 0x7F, 0xF8, 0x42, 0x08, 0x42, 0x08, 0x42, 0x08, 0x42, 0x08, 0x42, 0x08,
	0x42, 0x08, 0x42, 0x08, 0x00, 0x00, 0x7F, 0xF8, 0x42, 0x00, 0x42, 0x00, 0x42, 0x00, 0x42, 0x00,
	0x42, 0x00, 0x42, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x30, 0x30, 0x20, 0x10, 0x40, 0x08, 0x40, 0x08,
	0x41, 0x08, 0x41, 0x08, 0x41, 0x08, 0x41, 0x08, 0x21, 0xF0, 0x00, 0x00, 0x7F, 0xF8, 0x02, 0x00,
	0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x7F, 0xF8,
	0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x7F, 0xF8, 0x40, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
	0x00, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x7F, 0xF0, 0x00, 0x00, 0x7F, 0xF8, 0x01, 0x00,
	0x03, 0x00, 0x04, 0x80, 0x08, 0x40, 0x10, 0x20, 0x20, 0x10, 0x40, 0x08, 0x00, 0x00, 0x7F, 0xF8,
	0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x7F, 0xF8,
	0x60, 0x00, 0x18, 0x00, 0x06, 0x00, 0x01, 0x80, 0x00, 0x40, 0x01, 0x80, 0x06, 0x00, 0x18, 0x00,
	0x60, 0x00, 0x7F, 0xF8, 0x00, 0x00, 0x7F, 0xF8, 0x20, 0x00, 0x10, 0x00, 0x0C, 0x00, 0x02, 0x00,
	0x01, 0x00, 0x00, 0xC0, 0x00, 0x20, 0x00, 0x10, 0x7F, 0xF8, 0x00, 0x00, 0x0F, 0xC0, 0x30, 0x30,
	0x20, 0x10, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x40, 0x08, 0x20, 0x10, 0x30, 0x30,
	0x0F, 0xC0, 0x00, 0x00, 0x7F, 0xF8, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80, 0x40, 0x80,
	0x21, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x30, 0x30, 0x20, 0x10, 0x40, 0x08, 0x40, 0x08,
	0x40, 0x08, 0x40, 0x0E, 0x40, 0x09, 0x20, 0x11, 0x30, 0x31, 0x0F, 0xC1, 0x00, 0x00, 0x7F, 0xF8,
	0x41, 0x00, 0x41, 0x00, 0x41, 0x00, 0x41, 0x80, 0x42, 0x40, 0x3C, 0x20, 0x00, 0x10, 0x00, 0x08,
	0x00, 0x00, 0x1C, 0x10, 0x22, 0x08, 0x42, 0x08, 0x42, 0x08, 0x41, 0x08, 0x41, 0x08, 0x41, 0x10,
	0x20, 0xE0, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x7F, 0xF8, 0x40, 0x00,
	0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0x7F, 0xE0, 0x00, 0x10, 0x00, 0x08, 0x00, 0x08,
	0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x10, 0x7F, 0xE0, 0x00, 0x00, 0x60, 0x00,
	0x1C, 0x00, 0x03, 0x80, 0x00, 0x70, 0x00, 0x08, 0x00, 0x70, 0x03, 0x80, 0x1C, 0x00, 0x60, 0x00,
	0x00, 0x00, 0x60, 0x00, 0x1F, 0x00, 0x00, 0xF0, 0x00, 0x18, 0x01, 0xE0, 0x3E, 0x00, 0x40, 0x00,
	0x3E, 0x00, 0x01, 0xE0, 0x00, 0x18, 0x00, 0xF0, 0x1F, 0x00, 0x60, 0x00, 0x00, 0x00, 0x40, 0x08,
	0x30, 0x30, 0x08, 0x40, 0x07, 0x80, 0x07, 0x80, 0x08, 0x40, 0x30, 0x30, 0x40, 0x08, 0x00, 0x00,
	0x40, 0x00, 0x30, 0x00, 0x08, 0x00, 0x06, 0x00, 0x01, 0xF8, 0x06, 0x00, 0x08, 0x00, 0x30, 0x00,
	0x40, 0x00, 0x00, 0x00, 0x40, 0x18, 0x40, 0x28, 0x40, 0xC8, 0x41, 0x08, 0x42, 0x08, 0x4C, 0x08,
	0x50, 0x08, 0x60, 0x08, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
	0x00, 0x00, 0xC0, 0x00, 0x38, 0x00, 0x07, 0x00, 0x00, 0xE0, 0x00, 0x1C, 0x00, 0x03, 0x00, 0x00,
	0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x04, 0x00,
	0x08, 0x00, 0x30, 0x00, 0x40, 0x00, 0x40, 0x00, 0x30, 0x00, 0x08, 0x00, 0x04, 0x00, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02,
	0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x20, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x04, 0x88, 0x09, 0x08, 0x09, 0x08, 0x09, 0x08,
	0x09, 0x10, 0x07, 0xF8, 0x00, 0x00, 0xFF, 0xF8, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x04, 0x10, 0x03, 0xE0, 0x00, 0x00, 0x03, 0xE0, 0x04, 0x10, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x04, 0x10, 0x00, 0x00, 0x03, 0xE0, 0x04, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x10, 0xFF, 0xF8, 0x00, 0x00, 0x03, 0xE0, 0x04, 0x90, 0x08, 0x88, 0x08, 0x88,
	0x08, 0x88, 0x04, 0x88, 0x03, 0x90, 0x00, 0x00, 0x08, 0x00, 0x7F, 0xF8, 0x88, 0x00, 0x88, 0x00,
	0x80, 0x00, 0x03, 0xE0, 0x04, 0x12, 0x08, 0x09, 0x08, 0x09, 0x08, 0x09, 0x08, 0x09, 0x08, 0x12,
	0x0F, 0xFC, 0x00, 0x00, 0xFF, 0xF8, 0x04, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x6F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x08, 0x01, 0x08, 0x01, 0x6F, 0xFE, 0x00, 0x00, 0xFF, 0xF8, 0x00, 0x80, 0x01, 0x80, 0x02, 0x40,
	0x04, 0x20, 0x08, 0x10, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x0F, 0xF8, 0x04, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x07, 0xF8, 0x04, 0x00,
	0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x04, 0x00,
	0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x04, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x03, 0xE0,
	0x04, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x10, 0x03, 0xE0, 0x00, 0x00,
	0x0F, 0xFF, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x10, 0x03, 0xE0,
	0x00, 0x00, 0x03, 0xE0, 0x04, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10,
	0x0F, 0xFF, 0x00, 0x00, 0x0F, 0xF8, 0x04, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x07, 0x10, 0x08, 0x88, 0x08, 0x88, 0x08, 0x88, 0x08, 0x88, 0x04, 0x70, 0x00, 0x00, 0x08, 0x00,
	0x7F, 0xF0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x10, 0x00, 0x08,
	0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x10, 0x0F, 0xF8, 0x00, 0x00, 0x0C, 0x00, 0x03, 0x80,
	0x00, 0x60, 0x00, 0x18, 0x00, 0x60, 0x03, 0x80, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x03, 0xC0,
	0x00, 0x38, 0x00, 0x60, 0x03, 0x80, 0x0C, 0x00, 0x03, 0x80, 0x00, 0x60, 0x00, 0x38, 0x03, 0xC0,
	0x0C, 0x00, 0x00, 0x00, 0x08, 0x08, 0x04, 0x10, 0x03, 0x60, 0x00, 0x80, 0x03, 0x60, 0x04, 0x10,
	0x08, 0x08, 0x00, 0x00, 0x0C, 0x00, 0x03, 0x80, 0x00, 0x67, 0x00, 0x18, 0x00, 0x60, 0x03, 0x80,
	0x0C, 0x00, 0x00, 0x00, 0x08, 0x18, 0x08, 0x28, 0x08, 0xC8, 0x09, 0x08, 0x0A, 0x08, 0x0C, 0x08,
	0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x80, 0x7C, 0x7E, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01,
	0x80, 0x01, 0x80, 0x01, 0x7C, 0x7E, 0x02, 0x80, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xC0, 0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x80, 0x03, 0x00, 0x00, 0x00,
};

struct {
	const short int  * offset;
	const char *  dat;
} tahoma12_rc = {
	.offset = tahoma12_offset,
	.dat = tahoma12_dat
};


SINGLE_BYTE_FONT_T tahoma12 = {
	.name = "Tahoma 12",
	.id = FONT_UNREGISTERED,
	.height = 16,
	.width = 0, //proportional font
	.first_char = ' ',
	.dat = &tahoma12_rc,
	.get_matrix = get,

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
get(FONT_MATRIX_T *f)
{
	f->direction = DIRECTION_V;
	f->height = 16;
	f->width = tahoma12_rc.offset[f->character[0] - ' ' + 1] - tahoma12_rc.offset[f->character[0] - ' '];
	f->dat = tahoma12_rc.dat + tahoma12_rc.offset[f->character[0] - ' '] * 2;

	return 0;
}

