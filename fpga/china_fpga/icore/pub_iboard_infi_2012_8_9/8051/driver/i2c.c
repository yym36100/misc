/*------------------------------------------------------
   FILE NAME   : i2c.c
   DESCRIPTION : nvic driver
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------//

#include "..\include\stc11fxx.h"
#include "..\include\i2c.h"
#include <intrins.h>

//---------------- Function Prototype -------------------//


//static int initialize(void);
static unsigned char read(void);
static int write(unsigned char dat);
static int start(void);
static int stop(void);

static int ack(char);
int read_nbyte(unsigned char sla, unsigned char suba, unsigned char *s, unsigned char no);
int write_nbyte(unsigned char sla, unsigned char suba, unsigned char *s, unsigned char no);



//---------------- Variable -----------------------------//
sbit SDA = P3 ^ 2;
sbit SCL = P3 ^ 3;

 #define SDA_ON         SDA = 1
 #define SDA_OFF        SDA = 0

 #define SCL_ON         SCL = 1
 #define SCL_OFF        SCL = 0

static bit ack_flag = 0;


//-----------------Function------------------------------//

void delay(void)
{
	_nop_();
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
/*
   static int initialize(void)
   {

        SDA_ON;
        SCL_ON;


        return 0;
   }
 */
/*-------------------------------------------------------
   NAME       : start
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static
int start(void)
{
//	SDA_OUTPUT;

	SDA_ON;

	delay();

	SCL_ON;
	delay();

	SDA_OFF;
	delay();

	SCL_OFF;
	delay();


	return 0;
}
/*-------------------------------------------------------
   NAME       : start
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static
int stop(void)
{
//	SDA_OUTPUT;


	SDA_OFF;
	delay();

	SCL_ON;

	delay();


	SDA_ON;

	delay();

	return 0;
}
/*-------------------------------------------------------
   NAME       : ack
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static int
ack(char a)
{
	if (a) {
		SDA_OFF;
	}else {
		SDA_ON;
	}
	delay();
	SCL_ON;
	delay();
	SCL_OFF;

	delay();


	return 0;
}


/*-------------------------------------------------------
   NAME       : write
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

static int
write(unsigned char dat)
{
	unsigned char i = 8;



	for (i = 0; i < 8; i++) { /*要传送的数据长度为8 位*/
		if ((dat << i) & 0x80) SDA_ON;  /*判断发送位*/
		else SDA_OFF;
		delay();
		SCL_ON;
		delay();
		SCL_OFF;
	}
	SDA_ON;
	delay();


	delay();
	SCL_ON;

	delay();
	if (SDA) ack_flag = 0;
	else ack_flag = 1;  /*判断是否接收到应答信号*/
	SCL_OFF;

	delay();

	return 0;
}
/*-------------------------------------------------------
   NAME       : read
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
static unsigned char read(void)
{
	unsigned char retc;
	unsigned char BitCnt;


	retc = 0;

	SDA_ON; /*置数据线为输入方式*/


	for (BitCnt = 0; BitCnt < 8; BitCnt++) {
		delay();
		SCL_OFF; /*置时钟线为低，准备接收数据位*/
		delay();
		SCL_ON; /*置时钟线为高使数据线上数据有效*/
		delay();
		retc = retc << 1;
		if (SDA == 1) retc = retc + 1;  /*读数据位,接收的数据位放入retc 中 */
		delay();
	}
	SCL_OFF;
	delay();

	return(retc);
}
/*-------------------------------------------------------
   NAME       : read_nbyte
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
int
read_nbyte(unsigned char sla, unsigned char suba, unsigned char *s, unsigned char no)
{
	unsigned char i;

	start(); /*启动总线*/
	write(sla); /*发送器件地址*/
//	if(ack_flag==0)return(0);
	write(suba); /*发送器件子地址*/
//	if(ack_flag==0)return(0);
	start();
	write(sla + 1);
//	if(ack_flag==0)return(0);
	for (i = 0; i < no - 1; i++) {
		*s = read(); /*发送数据*/
		ack(1); /*发送就答位*/
		s++;
	}
	*s = read();
	ack(0);
	stop();


	return(1);
}
/*-------------------------------------------------------
   NAME       : write_nbyte
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
/*
   int
   write_nbyte(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no)
   {
        unsigned char i;

        start();
        write(sla);
        if(ack_flag==0) return(0);
        write(suba);
        if(ack_flag==0) return(0);

        for(i=0;i<no;i++)
        {
                write(*s);
                if(ack_flag==0) return(0);
                s++;
        }
        stop();

        return(1);
   }
 */















