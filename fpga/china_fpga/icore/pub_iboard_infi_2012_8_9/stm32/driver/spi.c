//spi.c

//-----------------Include files-------------------------//
#include "..\include\stm32f10x_reg.h"

#include "..\include\spi.h"


#include <stdio.h>


static int initialize_spi1(void);
static int write(int number, unsigned char * buf);



SYS_SPI_T spi1 = {
	.initialize = initialize_spi1,
	.write = write
};


static int initialize_spi1(void)
{
	RCC->APB2ENR.B.IOPBEN = 1;              //Enable GPIOB clocks
	RCC->APB2ENR.B.SPI1EN = 1;

	AFIO->MAPR.B.SPI1_REMAP = 1; //Remap SPI1 PB3/4/5 PA15


	//enable SW / disable JTAG
	AFIO->MAPR.B.SWJ_CFG = 2;

	GPIOB->CRL.B.MODE6 = 0x3;       //NSS 50M
	GPIOB->CRL.B.CNF6 = 0x0;        //10�����ù����������ģʽ
	GPIOB->CRL.B.MODE3 = 0x3;       //CSK 50M
	GPIOB->CRL.B.CNF3 = 0x2;        //10�����ù����������ģʽ
	GPIOB->CRL.B.MODE5 = 0x3;       //MOSI 50M
	GPIOB->CRL.B.CNF5 = 0x2;        //10�����ù����������ģʽ

	GPIOB->CRL.B.MODE4 = 0x0;       //MISO
	GPIOB->CRL.B.CNF4 = 0x1;        //01����������ģʽ(��λ���״̬)
	//10������/��������ģʽ


	SPI1->CR1.B.BR = 0;             //000�� fPCLK/2
	//001�� fPCLK/4
	//010�� fPCLK/8
	//011�� fPCLK/16
	//100�� fPCLK/32
	//101�� fPCLK/64
	//110�� fPCLK/128	36M/128
	//111�� fPCLK/256
	SPI1->CR1.B.BIDIMODE = 0;         //0��ѡ��˫��˫��ģʽ��
	SPI1->CR1.B.CPOL = 0;
	SPI1->CR1.B.CPHA = 0;
	SPI1->CR1.B.DFF = 0;            //1��ʹ��16λ����֡��ʽ���з���/���գ�
	//0��ʹ��8λ����֡��ʽ���з���/���գ�
	SPI1->CR1.B.LSBFIRST = 0;       //0���ȷ���MSB��
	SPI1->CR2.B.SSOE = 1;           //1���豸����ʱ��������ģʽ��SS���
	SPI1->CR1.B.MSTR = 1;           //1������Ϊ���豸��

	SPI1->CR1.B.SSM = 1;
	SPI1->CR1.B.SSI = 1;    //???

	SPI1->CR1.B.SPE = 1;            //1������SPI�豸��

	SPI1_CS_ON;

	return 0;
}

static unsigned char send_data(unsigned char data)
{
	while (!(SPI1->SR.B.TXE == 1)) ;

	SPI1->DR = data;

	while (!(SPI1->SR.B.RXNE == 1)) ;

	return SPI1->DR;
}

static int write(int number, unsigned char * buf)
{
	int i;

	SPI1_CS_OFF;


	for (i = 0; i < number; i++) buf[i] = send_data(buf[i]);

	SPI1_CS_ON;

	return 0;
}

