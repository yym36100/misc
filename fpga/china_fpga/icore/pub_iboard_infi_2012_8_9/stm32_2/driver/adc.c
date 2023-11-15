/*------------------------------------------------------
   FILE NAME   : adc.c
   DESCRIPTION : adc driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/


//-----------------Include files-------------------------//
#include "..\include\stm32f10x_reg.h"
#include "..\include\config.h"
#include "..\include\adc.h"
#include "..\include\usart.h"
#include "..\include\hardware.h"
#include "..\include\dac.h"



static int initialize(void);
static int read_adc(int);


SYS_ADC_T adc = {
	.initialize = initialize,
	.read = read_adc
};
//-----------------Function------------------------------//
/*-------------------------------------------------------
   NAME       : initialize
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int initialize(void)
{
	RCC->CFGR.B.ADCPRE = 3; //ADCPRE：ADC预分频
	//00：PCLK2 2分频后作为ADC时钟
	//01：PCLK2 4分频后作为ADC时钟
	//10：PCLK2 6分频后作为ADC时钟
	//11：PCLK2 8分频后作为ADC时钟


	RCC->APB2ENR.B.ADC1EN = 1;

	GPIOA->CRL.B.MODE0 = 0; //Configure PA.1 (ADC Channel1) as analog input
	GPIOA->CRL.B.CNF0 = 0;

	GPIOA->CRL.B.MODE1 = 0; //Configure PA.1 (ADC Channel1) as analog input
	GPIOA->CRL.B.CNF1 = 0;

	GPIOA->CRL.B.MODE2 = 0; //Configure PA.3 (ADC Channel0) as analog input
	GPIOA->CRL.B.CNF2 = 0;

	GPIOA->CRL.B.MODE3 = 0; //Configure PA.3 (ADC Channel0) as analog input
	GPIOA->CRL.B.CNF3 = 0;

	ADC1->SMPR2.B.SMP1 = 7;

	ADC1->CR2.B.TSVREFE = 0;
	ADC1->CR1.B.AWDEN = 1;

	ADC1->CR2.B.ADON = 0;

	ADC1->CR2.B.CAL = 1;

	ADC1->CR2.B.ADON = 1;   //ADC power on
   
	return 0;
}

/*-------------------------------------------------------
   NAME       : sort
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
void sort(unsigned short int a[], int n)
{
	int i, j, t;

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
}
/*-------------------------------------------------------
   NAME       : read_adc
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
read_adc(int channel)
{
	unsigned short int data[20];
	int i;
	float temp;

	LED_ON;

	ADC1->SQR1.B.L = 0;
	ADC1->SQR3.B.SQ1 = channel;
	ADC1->CR2.B.EXTSEL = 7;
	ADC1->CR2.B.SWSTART = 1;
	ADC1->CR2.B.CONT = 1;
	ADC1->CR2.B.ADON = 1;   //ADC power on

	for (i = 0; i < 20; i++) {
		while (ADC1->SR.B.EOC == 0) ;
		data[i] = ADC1->DR.W;
	}

	sort(data, 20);

	temp = data[10];
	temp /= 4095.0;
	temp *= VREF;

	adc.value = temp;
	LED_OFF;

	return 0;
}




