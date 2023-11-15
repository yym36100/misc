/*------------------------------------------------------
   FILE NAME   : usart.c
   DESCRIPTION : usart driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-9-10
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/



//-----------------Include files-------------------------//
//#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "..\include\stm32f10x_reg.h"
#include "..\include\usart.h"
#include "..\include\hardware.h"



//-----------------Variable------------------------------//
static int send_string_to_usart1(char * str);
static int send_byte_to_usart1(char data);
static int initialize_usart1(int baudrate);
static int my_printf1(const char * fmt, ...);

static int send_string_to_usart3(char * str);
//static int send_byte_to_usart1(char data);
static int initialize_usart3(int baudrate);
static int my_printf3(const char * fmt, ...);



UART_T usart1 = {
	.receive_ok_flag = 0,
	.receive_count = 0,
	.send_byte = send_byte_to_usart1,
	.send_string = send_string_to_usart1,
	.initialize = initialize_usart1,
	.printf = my_printf1
};


UART_T usart3 = {
	.receive_ok_flag = 0,
	.receive_count = 0,
//	.send_byte = send_byte_to_usart3,
	.send_string = send_string_to_usart3,
	.initialize = initialize_usart3,
	.printf = my_printf3
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
static int initialize_usart3(int baudrate)
{
	float temp;
	int temp2;

	AFIO->MAPR.B.USART3_REMAP = 1; //


	RCC->APB1ENR.B.USART3EN = 1;

	/* USART1 configuration ------------------------------------------------------*/
	/* USART1 configured as follow:
	    - BaudRate = 115200 baud
	    - Word Length = 8 Bits
	    - One Stop Bit
	    - No parity
	    - Hardware flow control disabled (RTS and CTS signals)
	    - Receive and transmit enabled
	    - USART Clock disabled
	    - USART CPOL: Clock is active low
	    - USART CPHA: Data is captured on the middle
	    - USART LastBit: The clock pulse of the last data bit is not output to
	                     the SCLK pin
	 */
	GPIOC->CRH.B.MODE10 = 3;  // Configure USART1 Tx (PC.10) as alternate function push-pull
	GPIOC->CRH.B.CNF10 = 2;
	GPIOC->CRH.B.MODE11 = 0; // Configure USART1 Rx (PC.11) as input floating
	GPIOC->CRH.B.CNF11 = 1;

	temp = CPU_CLK / (16 * 2 * baudrate);
	temp2 = floor(temp);
	temp = temp - temp2;
	temp *= 16;

	USART3->BRR.B.DIV_Fraction = temp; //DIV_Fraction[3:0]��USARTDIV����������
	//��4λ������USART��Ƶ����������(USARTDIV)��С�����֡�
	// 15 115200
	USART3->BRR.B.DIV_Mantissa = temp2;

	//DIV_Mantissa[11:0]��USARTDIV��С������
	//��12λ������USART��Ƶ����������(USARTDIV)���������֡�
	//113 115200
	USART3->CR1.B.M = 0;              //0��һ����ʼλ��8������λ��n��ֹͣλ��
	USART3->CR2.B.STOP = 0;   //00��1��ֹͣλ��
	USART3->CR1.B.PCE = 0;    //0��У����Ʊ���ֹ��
	USART3->CR3.B.RTSE = 0;   //0��RTSӲ�������Ʊ���ֹ��
	USART3->CR3.B.CTSE = 0;   //0��CTSӲ�������Ʊ���ֹ��
	USART3->CR1.B.TE = 1;             //1�����ͱ�ʹ�ܡ�
	USART3->CR1.B.RE = 1;             //1�����ܱ�ʹ�ܡ�
	USART3->CR2.B.CLKEN = 0;  //1��SCLK���ű�ʹ�ܡ�
	USART3->CR2.B.CPOL = 0;   //0�����߿���ʱSCLK�����ϱ��ֵ͵�ƽ��
	USART3->CR2.B.CPHA = 1;   //1��ʱ�ӵڶ������ؽ������ݲ���
	USART3->CR2.B.LBCL = 0;   //0�����һλ���ݵ�ʱ�����岻��SCLK�����


	USART3->CR1.B.PEIE = 1;   //1����USART_SR�е�PEΪ1ʱ������USART�жϡ�
	USART3->CR1.B.RXNEIE = 1; //1����USART_SR�е�ORE����RXNEΪ1ʱ������USART�жϡ�

	USART3->CR1.B.UE = 1;             //1��USARTģ��ʹ�ܡ�

	return 0;
}




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
static int initialize_usart1(int baudrate)
{
	float temp;
	int temp2;


	RCC->APB2ENR.B.IOPAEN = 1;              //Enable GPIOA clocks
	RCC->APB2ENR.B.USART1EN = 1;
	/* USART1 configuration ------------------------------------------------------*/
	/* USART1 configured as follow:
	    - BaudRate = 115200 baud
	    - Word Length = 8 Bits
	    - One Stop Bit
	    - No parity
	    - Hardware flow control disabled (RTS and CTS signals)
	    - Receive and transmit enabled
	    - USART Clock disabled
	    - USART CPOL: Clock is active low
	    - USART CPHA: Data is captured on the middle
	    - USART LastBit: The clock pulse of the last data bit is not output to
	                     the SCLK pin
	 */
	GPIOA->CRH.B.MODE9 = 3;  // Configure USART1 Tx (PA.09) as alternate function push-pull
	GPIOA->CRH.B.CNF9 = 2;
	GPIOA->CRH.B.MODE10 = 0; // Configure USART1 Rx (PA.10) as input floating
	GPIOA->CRH.B.CNF10 = 1;

	temp = CPU_CLK / (16 * baudrate);
	temp2 = floor(temp);
	temp = temp - temp2;
	temp *= 16;

	USART1->BRR.B.DIV_Fraction = temp; //DIV_Fraction[3:0]��USARTDIV����������
	//��4λ������USART��Ƶ����������(USARTDIV)��С�����֡�
	// 15 115200
	USART1->BRR.B.DIV_Mantissa = temp2;

	//DIV_Mantissa[11:0]��USARTDIV��С������
	//��12λ������USART��Ƶ����������(USARTDIV)���������֡�
	//113 115200
	USART1->CR1.B.M = 0;              //0��һ����ʼλ��8������λ��n��ֹͣλ��
	USART1->CR2.B.STOP = 0;   //00��1��ֹͣλ��
	USART1->CR1.B.PCE = 0;    //0��У����Ʊ���ֹ��
	USART1->CR3.B.RTSE = 0;   //0��RTSӲ�������Ʊ���ֹ��
	USART1->CR3.B.CTSE = 0;   //0��CTSӲ�������Ʊ���ֹ��
	USART1->CR1.B.TE = 1;             //1�����ͱ�ʹ�ܡ�
	USART1->CR1.B.RE = 1;             //1�����ܱ�ʹ�ܡ�
	USART1->CR2.B.CLKEN = 0;  //1��SCLK���ű�ʹ�ܡ�
	USART1->CR2.B.CPOL = 0;   //0�����߿���ʱSCLK�����ϱ��ֵ͵�ƽ��
	USART1->CR2.B.CPHA = 1;   //1��ʱ�ӵڶ������ؽ������ݲ���
	USART1->CR2.B.LBCL = 0;   //0�����һλ���ݵ�ʱ�����岻��SCLK�����


	USART1->CR1.B.PEIE = 1;   //1����USART_SR�е�PEΪ1ʱ������USART�жϡ�
	USART1->CR1.B.RXNEIE = 1; //1����USART_SR�е�ORE����RXNEΪ1ʱ������USART�жϡ�

	USART1->CR1.B.UE = 1;             //1��USARTģ��ʹ�ܡ�

	return 0;
}
/*-------------------------------------------------------
   NAME       : send_byte_to_usart1
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
send_byte_to_usart1(char data)
{
	USART1->DR.W = data;
	while (!(USART1->SR.B.TC == 1)) ;

	return 0;
}
/*-------------------------------------------------------
   NAME       : send_string_to_usart1
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
send_string_to_usart1(char * str)
{
	while (*str != '\0') {
		while (!(USART1->SR.B.TC == 1)) ;
		USART1->DR.W = (*str++);
	}
	return 0;
}

static int
send_string_to_usart3(char * str)
{
	while (*str != '\0') {
		while (!(USART3->SR.B.TC == 1)) ;
		USART3->DR.W = (*str++);
	}
	return 0;
}

/*-------------------------------------------------------
   NAME       : USART1_IRQHandler
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

int
USART1_IRQHandler(void)
{
	while (USART1->SR.B.RXNE == 0) ;
	usart1.receive_buffer[usart1.receive_count++] = USART1->DR.W;


	if (usart1.receive_buffer[usart1.receive_count - 1] == '\n') {
		usart1.receive_count = 0;
		usart1.receive_ok_flag = 1;
	}

	return 0;
}
int
USART3_IRQHandler(void)
{
	while (USART3->SR.B.RXNE == 0) ;
	usart1.receive_buffer[usart3.receive_count++] = USART3->DR.W;


	if (usart3.receive_buffer[usart3.receive_count - 1] == '\n') {
		usart3.receive_count = 0;
		usart3.receive_ok_flag = 1;
	}

	return 0;
}
/*-------------------------------------------------------
   NAME       : printf
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
my_printf1(const char * fmt, ...)
{
	va_list arg_ptr;
	char buf[BUFFER_SIZE];

	memset(buf, '\0', sizeof(buf));

	va_start(arg_ptr, fmt);
	vsprintf(buf, fmt, arg_ptr);
	va_end(arg_ptr);

	send_string_to_usart1(buf);

	return 0;
}
/*-------------------------------------------------------
   NAME       : printf
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
my_printf3(const char * fmt, ...)
{
	va_list arg_ptr;
	char buf[BUFFER_SIZE];

	memset(buf, '\0', sizeof(buf));

	va_start(arg_ptr, fmt);
	vsprintf(buf, fmt, arg_ptr);
	va_end(arg_ptr);

	send_string_to_usart3(buf);

	return 0;
}