/*
 * FILE								: spi.h
 * DESCRIPTION				: This file is iHMI43 spi header.
 * Author							: XiaomaGee@Gmail.com
 * Copyright					:
 *
 * History
 * --------------------
 * Rev								: 0.00
 * Date								: 03/05/2012
 *
 * create.
 * --------------------
 */
#ifndef __SPI6_H__
#define __SPI6_H__
//-----------------Include files-------------------------//

//------------------- Define ----------------------------//

#define  SPI1_CS_OFF		GPIO_ResetBits(GPIOA,GPIO_Pin_15)                                  
#define  SPI1_CS_ON		GPIO_SetBits(GPIOA,GPIO_Pin_15)

//------------------- Typedef --------------------------//

typedef  struct{
	int (* initialize)(void);
	int (* write)(int /*  number */,unsigned char * /* buffer */);
	unsigned char  (* send_data)(unsigned char );
}SPI1_T;

//------------------- Extern --------------------------//

extern SPI1_T spi1;

#endif //__SPI6_H__
