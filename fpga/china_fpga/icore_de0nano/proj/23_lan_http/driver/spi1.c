/*
 * FILE								: spi1.c
 * DESCRIPTION				: This file is iCore3 driver demo.
 * Author							: XiaomaGee@Gmail.com
 * Copyright					:
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 12/20/2015
 *
 * create.
 * -------------------
 */
//-----------------Include files-------------------------//
 
#include "..\include\spi1.h"
#include "..\fwlib\inc\stm32f4xx_gpio.h"
#include "..\fwlib\inc\stm32f4xx_rcc.h"
#include "..\fwlib\inc\stm32f4xx_spi.h"

#include <stdio.h>

//---------------- Function Prototype ------------------//

static int initialize_spi(void);
static int write(int number, unsigned char * buf);
static unsigned char send_data(unsigned char data);

//-----------------Variable-----------------------------//  
SPI1_T spi1 = {
	.initialize = initialize_spi,
	.write = write,
	.send_data = send_data
};
//-----------------Function-----------------------------//

/*
 * Name								: initialize_spi1
 * Description				: ---
 * Author							: XiaomaGee.
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 12/20/2015
 * 
 * create.
 * -------------------
 */

static int initialize_spi(void)
{
	GPIO_InitTypeDef GPIO_uInitStructure;
	SPI_InitTypeDef SPI_InitStructure;
				 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);  
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_uInitStructure.GPIO_OType = GPIO_OType_PP;  
	GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_UP;;
	GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 2M
	
	GPIO_Init(GPIOA,&GPIO_uInitStructure);
	SPI1_CS_ON;
				 
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_uInitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_UP;;
	GPIO_Init(GPIOB,&GPIO_uInitStructure);
	
	GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_uInitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_UP;;
	GPIO_Init(GPIOA,&GPIO_uInitStructure);
				 
	SPI_Cmd(SPI1,DISABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex ;  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                                                                                                                                                       
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;  
	SPI_InitStructure.SPI_CPOL = 0x00;                                                    
	SPI_InitStructure.SPI_CPHA = 0x00;   
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  
	SPI_InitStructure.SPI_CRCPolynomial = 7; 
	SPI_Init(SPI1,&SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
		
	return 0;
}
/*
 * Name								: initialize_spi1
 * Description				: ---
 * Author							: XiaomaGee.
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 12/20/2015
 * 
 * create.
 * -------------------
 */

static unsigned char send_data(unsigned char data)
{
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == 0);

	SPI_I2S_SendData(SPI1,data);

	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == 0);
	return SPI_I2S_ReceiveData(SPI1);
}
/*
 * Name								: write
 * Description				: ---
 * Author							: XiaomaGee.
 *
 * History
 * -------------------
 * Rev								: 0.00
 * Date								: 12/20/2015
 * 
 * create.
 * -------------------
 */

static int write(int number, unsigned char * buf)
{
	int i;
	SPI1_CS_OFF;
	for (i = 0; i < number; i++){
		buf[i] = send_data(buf[i]);
	}
	SPI1_CS_ON;

	return 0;
}
