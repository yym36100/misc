

//==============================================================================
//RedCore RCQ208_V3 USB (CH376T) Example
//==============================================================================

/* 2008.10.18
****************************************
**  Copyright  (C)  W.ch  1999-2009   **
**  Web:  http://www.winchiphead.com  **
****************************************
**  USB Host File Interface for CH376 **
**  TC2.0@PC, KC7.0@MCS51             **
****************************************
*/
/* CH376 主机文件系统接口 */

/* MCS-51单片机C语言的U盘文件读写示例程序 */
/* 本程序演示字节读写,文件枚举, 用于将U盘中的/C51/CH376HFT.C文件中的前200个字符显示出来,
   如果找不到原文件CH376HFT.C, 那么该程序将显示C51子目录下所有以CH376开头的文件名,
   如果找不到C51子目录, 那么该程序将显示根目录下的所有文件名 */

#include <stdio.h>
#include <string.h>
#include "includes.h"

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "Main.h"
#include "CH376INC.H"
#include "fpga_io.h"

//#include "CH376.H"

#include "HAL.H"
#include "HAL_BASE.C"
#include "DEBUG.H"
#include "DEBUG.C"
//#include "PARA_HW.C"		/* 硬件总线并口连接方式 */
//#include "..\PARA_SW.C"		/* 软件模拟并口连接方式 */
//#include "..\SPI_HW.C"		/* 硬件SPI连接方式 */
#include "SPI_SW.C"		/* 软件模拟SPI方式 */
//#include "..\UART_HW.C"		/* 硬件异步串口连接方式 */
#include "FILE_SYS.H"
#include "FILE_SYS.C"

void host(void);
void device(void);
void CH376OffUSB(void);
void CH376DeviceInit(void);
void mCh375Interrupt(void);
void delay_USB_us(UINT32 i);

extern char USBH_info[];
extern char USBS_info[];

UINT8	buf[64];

UINT8V	FreeUSBmS;

//----------------------------------------------------------------------------
//Main function
//----------------------------------------------------------------------------

//CH376 是高电平复位，正常工作时是低电平
int USB_Test(void)
{
#if 0
    while(1)
    {
        printf("\r\n %s \r\n",__FUNCTION__);
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
    return;
#endif

	SET_USB_RST_O(1);	
	delay_USB_us(100000);
	SET_USB_RST_O(0);	
	delay_USB_us(100000);
    
    while(1)
    {
    	if(GET_PC_CONNECT_I())
    	{
            //Print_USB_Msg();
			memset(USBH_info,0x0,28);
			sprintf(USBH_info,"Not work in Host mode.");
    		printf( "USB Device mode\r\n" );
    		device();
			
			OSTimeDlyHMSM(0, 0, 0, 100);
    	}
    	else
    	{
            //Print_USB_Msg();
			memset(USBS_info,0x0,28);
			sprintf(USBS_info,"Not work in Device mode.");
    		printf( "USB Host mode\r\n" );
        	host();
			
			OSTimeDlyHMSM(0, 0, 1, 0);
    	}
    }
}
//----------------------------------------------------------------------------

void Print_USB_Msg(void)
{
  printf("\n----------------------------------------------\r\n");
  printf(" Task2:RedCore RCQ208_V3 USB (CH376T) Start\r\n");
  printf("----------------------------------------------\r\n"); 
}

//----------------------------------------------------------------------------
void delay_USB_us(UINT32 i)
{
	usleep(i);
}
//----------------------------------------------------------------------------
//  END OF FILE
//----------------------------------------------------------------------------

void host(void)
{
	UINT8	i, s;
	UINT8	TotalCount;
	UINT16	RealCount;
	P_FAT_DIR_INFO	pDir;

	s = mInitCH376Host( );  /* 初始化CH376 */
	mStopIfError( s );
/* 其它电路初始化 */


		printf( "Wait Udisk/SD\r\n" );
		while ( CH376DiskConnect( ) != USB_INT_SUCCESS ) {  /* 检查U盘是否连接,等待U盘插入,对于SD卡,可以由单片机直接查询SD卡座的插拔状态引脚 */
			//if ( IsKeyPress( ) ) {  /* 有键按下 */
			//	printf( "Exit USB host mode\n" );
			//	return;
			//}
			printf( "No USB Host connect\r\n" );
			memset(USBH_info,0x0,28);
			sprintf(USBH_info, "No USB connect");
			mDelaymS( 250 ); mDelaymS( 250 );mDelaymS( 250 );mDelaymS( 250 ); /* 没必要频繁查询 */
            return;
		}
		printf("DOT LED\r\n");//LED_UDISK_IN( );  /* LED亮 */
		
		mDelaymS( 200 );  /* 延时,可选操作,有的USB存储器需要几十毫秒的延时 */

/* 对于检测到USB设备的,最多等待100*50mS,主要针对有些MP3太慢,对于检测到USB设备并且连接DISK_MOUNTED的,最多等待5*50mS,主要针对DiskReady不过的 */
		for ( i = 0; i < 100; i ++ ) {  /* 最长等待时间,100*50mS */
			mDelaymS( 50 );
			printf( "Ready ?\r\n" );
			s = CH376DiskMount( );  /* 初始化磁盘并测试磁盘是否就绪 */
			printf( "CH376DiskMount = %02x\r\n",s);
			if ( s == USB_INT_SUCCESS ) break;  /* 准备好 */
			else if ( s == ERR_DISK_DISCON ) break;  /* 检测到断开,重新检测并计时 */
			if ( CH376GetDiskStatus( ) >= DEF_DISK_MOUNTED && i >= 5 ) break;  /* 有的U盘总是返回未准备好,不过可以忽略,只要其建立连接MOUNTED且尝试5*50mS */
		}
		if ( s == ERR_DISK_DISCON ) {  /* 检测到断开,重新检测并计时 */
			printf( "Device gone\r\n" );
			return;
		}
		if ( CH376GetDiskStatus( ) < DEF_DISK_MOUNTED ) {  /* 未知USB设备,例如USB键盘、打印机等 */
			printf( "Unknown device\r\n" );
			goto UnknownUsbDevice;
		}
		i = CH376ReadBlock( buf );  /* 如果需要,可以读取数据块CH376_CMD_DATA.DiskMountInq,返回长度 */
		if ( i == sizeof( INQUIRY_DATA ) ) {  /* U盘的厂商和产品信息 */
			buf[ i ] = 0;
			printf( "UdiskInfo: %s\r\n", ((P_INQUIRY_DATA)buf) -> VendorIdStr );
			memset(USBH_info,0x0,28);
			memcpy(USBH_info,((P_INQUIRY_DATA)buf) -> VendorIdStr,28);
		}

/* 读取原文件 */
		printf( "Open\r\n" );
		strcpy( buf, "\\C51\\CH376HFT.C" );  /* 源文件名,多级目录下的文件名和路径名必须复制到RAM中再处理,而根目录或者当前目录下的文件名可以在RAM或者ROM中 */
		s = CH376FileOpenPath( buf );  /* 打开文件,该文件在C51子目录下 */
		if ( s == ERR_MISS_DIR || s == ERR_MISS_FILE ) {  /* 没有找到目录或者没有找到文件 */
/* 列出文件,完整枚举可以参考EXAM13全盘枚举 */
			if ( s == ERR_MISS_DIR ) strcpy( buf, "\\*" );  /* C51子目录不存在则列出根目录下的文件 */
			else strcpy( buf, "\\C51\\CH376*" );  /* CH376HFT.C文件不存在则列出\C51子目录下的以CH376开头的文件 */
			printf( "List file %s\r\n", buf );
			s = CH376FileOpenPath( buf );  /* 枚举多级目录下的文件或者目录,输入缓冲区必须在RAM中 */
			while ( s == USB_INT_DISK_READ ) {  /* 枚举到匹配的文件 */
				CH376ReadBlock( buf );  /* 读取枚举到的文件的FAT_DIR_INFO结构,返回长度总是sizeof( FAT_DIR_INFO ) */
				pDir = (P_FAT_DIR_INFO)buf;  /* 当前文件目录信息 */
				if ( pDir -> DIR_Name[0] != '.' ) {  /* 不是本级或者上级目录名则继续,否则必须丢弃不处理 */
					if ( pDir -> DIR_Name[0] == 0x05 ) pDir -> DIR_Name[0] = 0xE5;  /* 特殊字符替换 */
					pDir -> DIR_Attr = 0;  /* 强制文件名字符串结束以便打印输出 */
					printf( "*** EnumName: %s\r\n", pDir -> DIR_Name );  /* 打印名称,原始8+3格式,未整理成含小数点分隔符 */
				}
				xWriteCH376Cmd( CMD0H_FILE_ENUM_GO );  /* 继续枚举文件和目录 */
				xEndCH376Cmd( );
				s = Wait376Interrupt( );
			}
			if ( s != ERR_MISS_FILE ) mStopIfError( s );  /* 操作出错 */
		}
		else {  /* 找到文件或者出错 */
			mStopIfError( s );
			TotalCount = 200;  /* 准备读取总长度 */
			printf( "从文件中读出的前%d个字符是:\r\n",(UINT16)TotalCount );
			while ( TotalCount ) {  /* 如果文件比较大,一次读不完,可以再调用CH376ByteRead继续读取,文件指针自动向后移动 */
				if ( TotalCount > sizeof(buf) ) i = sizeof(buf);  /* 剩余数据较多,限制单次读写的长度不能超过缓冲区大小 */
				else i = TotalCount;  /* 最后剩余的字节数 */
				s = CH376ByteRead( buf, i, &RealCount );  /* 以字节为单位读取数据块,单次读写的长度不能超过缓冲区大小,第二次调用时接着刚才的向后读 */
				mStopIfError( s );
				TotalCount -= (UINT8)RealCount;  /* 计数,减去当前实际已经读出的字符数 */
				for ( s=0; s!=RealCount; s++ ) printf( "%C", buf[s] );  /* 显示读出的字符 */
				if ( RealCount < i ) {  /* 实际读出的字符数少于要求读出的字符数,说明已经到文件的结尾 */
					printf( "\r\n" );
					printf( "文件已经结束\r\n" );
					break;
				}
			}
			printf( "Close\r\n" );
			s = CH376FileClose( FALSE );  /* 关闭文件 */
			mStopIfError( s );
		}

UnknownUsbDevice:
		printf( "Take out\r\n" );
		//while ( CH376DiskConnect( ) == USB_INT_SUCCESS ) {  /* 检查U盘是否连接,等待U盘拔出 */
			//mDelaymS( 100 );
		//}
		//printf("TURN OFF LED\r\n");//LED_UDISK_OUT( );  /* LED灭 */
		mDelaymS( 100 );
}

void device(void)
{
	CH376DeviceInit( );  /* 初始化USB设备模式 */
	FreeUSBmS = 0;  /* 清除USB空闲计时 */

	xWriteCH376Cmd( CMD20_SET_SDO_INT );  /* 设置SPI的SDO引脚的中断方式 */
	xWriteCH376Data( 0x16 );
	xWriteCH376Data( 0x90 );  /* SDO引脚在SCS片选无效时兼做中断请求输出 */
	xEndCH376Cmd( );
	
		if(!GET_SDO_I())
		{
			mCh375Interrupt();
			//mDelaymS( 250 );mDelaymS( 250 );mDelaymS( 250 );mDelaymS( 250 );
			//CH376OffUSB( );  /* 关闭USB设备 */	
			/* USB设备模式全部在中断服务中处理,主程序可以做其它事情,当然也可以在主程序中使用查询方式处理USB设备的通讯 */
		}
}

/* CH376初始化子程序 */
void CH376DeviceInit( void ) 
{
	UINT8 i;
/* 设置USB工作模式, 必要操作 */
	xWriteCH376Cmd( CMD_SET_USB_MODE );
	xWriteCH376Data( 2 );  /* 设置为使用内置固件的USB设备方式 */
	for ( i=100; i!=0; i-- )
	{
		if ( xReadCH376Data( ) == CMD_RET_SUCCESS )
		{
			printf("Set USB device mode success\r\n");
			memset(USBS_info,0x0,28);
			sprintf(USBS_info,"SET USB Deivce mode sucess.");
			break;  /* 等待操作成功,通常需要等待10uS-20uS */
		}
	}
	xEndCH376Cmd( );  /* 结束CH376命令,仅用于SPI接口方式 */
/*	if ( i == 0 ) { CH372/CH375/CH376芯片内部或者物理连接存在硬件错误 }; */

/* 下面启用USB中断,CH376的INT#引脚可以连接到单片机的中断引脚,中断为低电平有效或者下降沿有效,
   如果不使用中断,那么也可以用查询方式,由单片机程序查询CH376的INT#引脚为低电平 */
///	IT0 = 0;  /* 置外部信号为低电平触发 */
///	IE0 = 0;  /* 清中断标志 */
///	EX0 = 1;  /* 允许CH376中断,假定CH376的INT#引脚连接到单片机的INT0 */
}

/* CH375中断服务程序,使用寄存器组1 */
void	mCh375Interrupt(void)
{
	static unsigned char j = 0;
	static unsigned char k = 0;
	unsigned char InterruptStatus;
	unsigned char i, length;
	unsigned char buffer[ 64 ];

	//printf("mCh375Interrupt\r\n" );
	
	xWriteCH376Cmd( CMD_GET_STATUS );  /* 获取中断状态并取消中断请求 */
	InterruptStatus = xReadCH376Data( );  /* 获取中断状态 */
	switch ( InterruptStatus ) {  /* 分析中断状态处理 */
		case USB_INT_EP2_OUT: {  /* 批量端点下传成功 */
			if(j++ == 200)
			{
			  if(k++ % 20 == 0)
			  	printf("\r\n");
			  printf(".");
			}
			xWriteCH376Cmd( CMD_RD_USB_DATA );  /* 从当前USB中断的端点缓冲区读取数据块,并释放缓冲区 */
			length = xReadCH376Data( );  /* 首先读取后续数据长度 */
			if(length > sizeof(buffer))
			{
				printf("buffer overflow length:%d \r\n",length);
				length = sizeof(buffer);
			}
			for ( i = 0; i < length; i ++ ) buffer[ i ] = xReadCH376Data( );  /* 接收数据包 */
			
			if(buffer[0] == 0x21)
			{
			  memset(USBS_info,0x0,28);
			  sprintf(USBS_info,"USB Connected to PC, Rec DATA");
			}
			  
			/* 测试数据正确性,将接收到的命令包数据取反后返回给PC机 */
			xWriteCH376Cmd( CMD_WR_USB_DATA7 );  /* 向USB端点2的发送缓冲区写入数据块 */
			xWriteCH376Data( length );  /* 首先写入后续数据长度,回传刚接收到的数据长度 */
			for ( i = 0; i < length; i ++ ) xWriteCH376Data( ~ buffer[ i ] );  /* 数据取反后返回,由计算机应用程序测试数据是否正确 */
			break;
		}
		case USB_INT_EP2_IN: {  /* 批量数据发送成功 */
			xWriteCH376Cmd( CMD_UNLOCK_USB );  /* 释放当前USB缓冲区 */
			break;
		}
		default: {  /* 其它中断,未用到,解锁后退出即可 */
			xWriteCH376Cmd( CMD_UNLOCK_USB );  /* 释放当前USB缓冲区 */
			break;
		}
	}
	xEndCH376Cmd( );//置CS无效，让SDO作为下一次中断。	
}

/* 关闭CH376的所有USB通讯 */
void	CH376OffUSB(void) 
{
///	EX0 = 0;  /* 关闭USB中断,本程序中USB主机模式下使用查询方式 */
/* 设置USB工作模式, 必要操作 */
	xWriteCH376Cmd( CMD_SET_USB_MODE );
	xWriteCH376Data( 0 );  /* 设置为未启用的USB设备方式 */
	xEndCH376Cmd( );  /* 结束CH376命令,仅用于SPI接口方式 */
	mDelaymS( 10 );  /* 为USB主从切换进行时间缓冲,这是必要的延时操作,用于让计算机认为USB设备已经撤离 */
/* 如果CH376仍然连接着计算机,而程序使CH376切换到USB主机模式,那么会导致与计算机之间双USB主机冲突 */
}
