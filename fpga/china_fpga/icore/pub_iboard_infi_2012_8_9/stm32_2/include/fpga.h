/*------------------------------------------------------
FILE NAME   : fpga.h
DESCRIPTION : fpga driver file header
VERSION     : 0.0.0 (C)XiaomaGee
AUTHOR      : XiaomaGee
CREATE DATE : 2010-6-3
MODIFY DATE :
LOGS        :-\
--------------------------------------------------------*/
#ifndef __fpga_h__
#define __fpga_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- define -----------------------------//

#define FPGA_CTL0		*((volatile unsigned short int *)(0x60000000))
#define FPGA_CTL1		*((volatile unsigned short int *)(0x60020000))
#define FPGA_WR2		*((volatile unsigned short int *)(0x60040000))
#define FPGA_WR3		*((volatile unsigned short int *)(0x60060000))
#define FPGA_WR4		*((volatile unsigned short int *)(0x60080000))
#define FPGA_WR5		*((volatile unsigned short int *)(0x600A0000))
#define FPGA_WR6		*((volatile unsigned short int *)(0x600C0000))
#define FPGA_WR7		*((volatile unsigned short int *)(0x600E0000))

//---------------- typedef ----------------------------//

typedef union {
		struct {
			 unsigned int ctl0:1;
			 unsigned int ctl1:1;
			 unsigned int ctl2:1;
			 unsigned int ctl3:1;
			 unsigned int ctl4:1;
			 unsigned int ctl5:1;
			 unsigned int ctl6:1;
			 unsigned int ctl7:1;
			 unsigned int ctl8:1;
			 unsigned int ctl9:1;
			 unsigned int ctl10:1;
			 unsigned int ctl11:1;
			 unsigned int ctl12:1;
			 unsigned int ctl13:1;
			 unsigned int ctl14:1;
			 unsigned int ctl15:1;
			 unsigned int ctl16:1;
			 unsigned int ctl17:1;
			 unsigned int x_scale:4;
			 unsigned int ctl22:1;
			 unsigned int ctl23:1;
			 unsigned int ctl24:1;
			 unsigned int ctl25:1;
			 unsigned int ctl26:1;
			 unsigned int ctl27:1;
			 unsigned int ctl28:1;
			 unsigned int ctl29:1;
			 unsigned int ctl30:1;
			 unsigned int ctl31:1;
		}b;
		unsigned long int w;
}FPGA_CTL_T;

typedef struct{
	int (* initialize)(void);
	int (* ctl)(void);
}FPGA_T;

//---------------- Extern -------------------------------//
extern FPGA_T fpga;
extern FPGA_CTL_T fpga_ctl;
#endif //__fpga_h__
