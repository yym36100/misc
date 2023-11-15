#ifndef __SPI_H__
#define __SPI_H__

#include "..\include\hardware.h"




#define  SPI1_CS_OFF	GPIOB->BSRR.B.CLRIO6=1                                   
#define  SPI1_CS_ON		GPIOB->BSRR.B.SETIO6=1 


typedef  struct{
	int (* initialize)(void);
	int (* write)(int /*  number */,unsigned char * /* buffer */);
}SYS_SPI_T;

extern SYS_SPI_T spi1;



#endif //__SPI_H__
