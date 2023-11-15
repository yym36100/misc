/*------------------------------------------------------
   FILE NAME   : ds1302.c
   DESCRIPTION : main function
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/

//---------------- Include files ------------------------/
#include "..\include\stc11fxx.h"
#include "..\include\ds1302.h"
#include <intrins.h>

//---------------- Function Prototype -------------------/
//---------------- Variable -----------------------------/

sbit DS1302_SCLK = P1 ^ 5;
sbit DS1302_IO = P3 ^ 6;
sbit DS1302_RST = P3 ^ 7;

sbit ACC0 = ACC ^ 0;
sbit ACC7 = ACC ^ 7;

RTC_T rtc;


//---------------- Function -----------------------------//
/*-------------------------------------------------------
   NAME       : bcd2hex
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

unsigned char bcd2hex(unsigned char value)
{
	unsigned char i;

	i = value & 0x0f;
	value >>= 4;
	value &= 0x0f;
	value *= 10.0;
	i += value;

	return i;
}
/*-------------------------------------------------------
   NAME       : hex2bcd
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
unsigned char hex2bcd(unsigned char value)
{
	unsigned char i, j;

	i = value / 10;
	j = value % 10;

	return(j + (i << 4));
}
/*-------------------------------------------------------
   NAME       : delay
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

void dly(void)
{
	unsigned char i;
	for (i = 0; i < 10; i++) {
		_nop_();
		_nop_();
		_nop_();
	}
}
/*-------------------------------------------------------
   NAME       : read_byte
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

unsigned char  read_byte()
{
	unsigned char i;
	for (i = 8; i > 0; i--) {
		ACC = ACC >> 1;
		DS1302_IO = 1;
		ACC7 = DS1302_IO;              //由于ds1302读数据的时候，第一个数据读取在发一个Byte命令后，在第八位的下降沿
		DS1302_SCLK = 1;
		//  dly();
		DS1302_SCLK = 0;              //产生下降沿输出一位数据
		//	  dly();
	}
	return(ACC);
}


/*-------------------------------------------------------
   NAME       : write_byte
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
void  write_byte(unsigned char tdata)
{
	unsigned char i;
	ACC = tdata;
	for (i = 8; i > 0; i--) {
		DS1302_IO = ACC0;
		DS1302_SCLK = 1;
		//	  dly();
		DS1302_SCLK = 0;              //产生上升沿输入数据
		//	  dly();
		ACC = ACC >> 1;
	}
}


/*-------------------------------------------------------
   NAME       : write_data_ds1302
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

void write_data_ds1302(unsigned char taddr, unsigned char tdata)
{
	DS1302_RST = 0;
	DS1302_SCLK = 0;
	DS1302_RST = 1;
	//dly();
	write_byte(taddr);
	write_byte(tdata);
//	dly();
	DS1302_RST = 0;
	DS1302_SCLK = 1;
}

/*-------------------------------------------------------
   NAME       : read_data_ds1302
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/
unsigned char read_data_ds1302(unsigned char taddr)
{
	unsigned char tdata;

	DS1302_RST = 0;
	DS1302_SCLK = 0;
	DS1302_RST = 1;
	//dly();
	write_byte(taddr);
	tdata = read_byte();
	//dly();
	DS1302_RST = 0;
	DS1302_SCLK = 1;
	return(tdata);
}


/*-------------------------------------------------------
   NAME       : set_ds1302
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

void set_ds1302(unsigned char *p1302)
{
	unsigned char i;
	unsigned char taddr = 0x80;

	write_data_ds1302(0x8e, 0x00);                  /* 控制命令,WP=0,写操作*/

	for (i = 7; i > 0; i--) {
		write_data_ds1302(taddr, hex2bcd(*p1302));                   /* 秒 分 时 日 月 星期 年 */
		p1302++;
		taddr += 2;
	}

	write_data_ds1302(0x8e, 0x80);                  /* 控制命令,WP=1,写保护*/
}
/*-------------------------------------------------------
   NAME       : get_ds1302
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

void get_ds1302()
{
	unsigned char k;
	unsigned char taddr = 0x81;
	unsigned char da = 0;
	unsigned char *p = &rtc.second;

	for (k = 0; k < 7; k++) {
		da = read_data_ds1302(taddr);                /*格式为: 秒 分 时 日 月 星期 年 */
		p[k] = bcd2hex(da);
		taddr += 2;
	}
}
/*-------------------------------------------------------
   NAME       : init_ds1302
   ENTRY  TYPE: void
   RETURN TYPE: void
   PURPOSE    : ---
   VERSION    : 0.0.0
   DESCRIPTION:
   CREATE DATE: ---
   LOGS       :
   ---------------------------------------------------------*/

void init_ds1302()
{
	DS1302_RST = 0;
	DS1302_SCLK = 0;
}
