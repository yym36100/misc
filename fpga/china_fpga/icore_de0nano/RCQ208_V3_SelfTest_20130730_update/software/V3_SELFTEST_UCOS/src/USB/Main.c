

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
/* CH376 �����ļ�ϵͳ�ӿ� */

/* MCS-51��Ƭ��C���Ե�U���ļ���дʾ������ */
/* ��������ʾ�ֽڶ�д,�ļ�ö��, ���ڽ�U���е�/C51/CH376HFT.C�ļ��е�ǰ200���ַ���ʾ����,
   ����Ҳ���ԭ�ļ�CH376HFT.C, ��ô�ó�����ʾC51��Ŀ¼��������CH376��ͷ���ļ���,
   ����Ҳ���C51��Ŀ¼, ��ô�ó�����ʾ��Ŀ¼�µ������ļ��� */

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
//#include "PARA_HW.C"		/* Ӳ�����߲������ӷ�ʽ */
//#include "..\PARA_SW.C"		/* ���ģ�Ⲣ�����ӷ�ʽ */
//#include "..\SPI_HW.C"		/* Ӳ��SPI���ӷ�ʽ */
#include "SPI_SW.C"		/* ���ģ��SPI��ʽ */
//#include "..\UART_HW.C"		/* Ӳ���첽�������ӷ�ʽ */
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

//CH376 �Ǹߵ�ƽ��λ����������ʱ�ǵ͵�ƽ
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

	s = mInitCH376Host( );  /* ��ʼ��CH376 */
	mStopIfError( s );
/* ������·��ʼ�� */


		printf( "Wait Udisk/SD\r\n" );
		while ( CH376DiskConnect( ) != USB_INT_SUCCESS ) {  /* ���U���Ƿ�����,�ȴ�U�̲���,����SD��,�����ɵ�Ƭ��ֱ�Ӳ�ѯSD�����Ĳ��״̬���� */
			//if ( IsKeyPress( ) ) {  /* �м����� */
			//	printf( "Exit USB host mode\n" );
			//	return;
			//}
			printf( "No USB Host connect\r\n" );
			memset(USBH_info,0x0,28);
			sprintf(USBH_info, "No USB connect");
			mDelaymS( 250 ); mDelaymS( 250 );mDelaymS( 250 );mDelaymS( 250 ); /* û��ҪƵ����ѯ */
            return;
		}
		printf("DOT LED\r\n");//LED_UDISK_IN( );  /* LED�� */
		
		mDelaymS( 200 );  /* ��ʱ,��ѡ����,�е�USB�洢����Ҫ��ʮ�������ʱ */

/* ���ڼ�⵽USB�豸��,���ȴ�100*50mS,��Ҫ�����ЩMP3̫��,���ڼ�⵽USB�豸��������DISK_MOUNTED��,���ȴ�5*50mS,��Ҫ���DiskReady������ */
		for ( i = 0; i < 100; i ++ ) {  /* ��ȴ�ʱ��,100*50mS */
			mDelaymS( 50 );
			printf( "Ready ?\r\n" );
			s = CH376DiskMount( );  /* ��ʼ�����̲����Դ����Ƿ���� */
			printf( "CH376DiskMount = %02x\r\n",s);
			if ( s == USB_INT_SUCCESS ) break;  /* ׼���� */
			else if ( s == ERR_DISK_DISCON ) break;  /* ��⵽�Ͽ�,���¼�Ⲣ��ʱ */
			if ( CH376GetDiskStatus( ) >= DEF_DISK_MOUNTED && i >= 5 ) break;  /* �е�U�����Ƿ���δ׼����,�������Ժ���,ֻҪ�佨������MOUNTED�ҳ���5*50mS */
		}
		if ( s == ERR_DISK_DISCON ) {  /* ��⵽�Ͽ�,���¼�Ⲣ��ʱ */
			printf( "Device gone\r\n" );
			return;
		}
		if ( CH376GetDiskStatus( ) < DEF_DISK_MOUNTED ) {  /* δ֪USB�豸,����USB���̡���ӡ���� */
			printf( "Unknown device\r\n" );
			goto UnknownUsbDevice;
		}
		i = CH376ReadBlock( buf );  /* �����Ҫ,���Զ�ȡ���ݿ�CH376_CMD_DATA.DiskMountInq,���س��� */
		if ( i == sizeof( INQUIRY_DATA ) ) {  /* U�̵ĳ��̺Ͳ�Ʒ��Ϣ */
			buf[ i ] = 0;
			printf( "UdiskInfo: %s\r\n", ((P_INQUIRY_DATA)buf) -> VendorIdStr );
			memset(USBH_info,0x0,28);
			memcpy(USBH_info,((P_INQUIRY_DATA)buf) -> VendorIdStr,28);
		}

/* ��ȡԭ�ļ� */
		printf( "Open\r\n" );
		strcpy( buf, "\\C51\\CH376HFT.C" );  /* Դ�ļ���,�༶Ŀ¼�µ��ļ�����·�������븴�Ƶ�RAM���ٴ���,����Ŀ¼���ߵ�ǰĿ¼�µ��ļ���������RAM����ROM�� */
		s = CH376FileOpenPath( buf );  /* ���ļ�,���ļ���C51��Ŀ¼�� */
		if ( s == ERR_MISS_DIR || s == ERR_MISS_FILE ) {  /* û���ҵ�Ŀ¼����û���ҵ��ļ� */
/* �г��ļ�,����ö�ٿ��Բο�EXAM13ȫ��ö�� */
			if ( s == ERR_MISS_DIR ) strcpy( buf, "\\*" );  /* C51��Ŀ¼���������г���Ŀ¼�µ��ļ� */
			else strcpy( buf, "\\C51\\CH376*" );  /* CH376HFT.C�ļ����������г�\C51��Ŀ¼�µ���CH376��ͷ���ļ� */
			printf( "List file %s\r\n", buf );
			s = CH376FileOpenPath( buf );  /* ö�ٶ༶Ŀ¼�µ��ļ�����Ŀ¼,���뻺����������RAM�� */
			while ( s == USB_INT_DISK_READ ) {  /* ö�ٵ�ƥ����ļ� */
				CH376ReadBlock( buf );  /* ��ȡö�ٵ����ļ���FAT_DIR_INFO�ṹ,���س�������sizeof( FAT_DIR_INFO ) */
				pDir = (P_FAT_DIR_INFO)buf;  /* ��ǰ�ļ�Ŀ¼��Ϣ */
				if ( pDir -> DIR_Name[0] != '.' ) {  /* ���Ǳ��������ϼ�Ŀ¼�������,������붪�������� */
					if ( pDir -> DIR_Name[0] == 0x05 ) pDir -> DIR_Name[0] = 0xE5;  /* �����ַ��滻 */
					pDir -> DIR_Attr = 0;  /* ǿ���ļ����ַ��������Ա��ӡ��� */
					printf( "*** EnumName: %s\r\n", pDir -> DIR_Name );  /* ��ӡ����,ԭʼ8+3��ʽ,δ����ɺ�С����ָ��� */
				}
				xWriteCH376Cmd( CMD0H_FILE_ENUM_GO );  /* ����ö���ļ���Ŀ¼ */
				xEndCH376Cmd( );
				s = Wait376Interrupt( );
			}
			if ( s != ERR_MISS_FILE ) mStopIfError( s );  /* �������� */
		}
		else {  /* �ҵ��ļ����߳��� */
			mStopIfError( s );
			TotalCount = 200;  /* ׼����ȡ�ܳ��� */
			printf( "���ļ��ж�����ǰ%d���ַ���:\r\n",(UINT16)TotalCount );
			while ( TotalCount ) {  /* ����ļ��Ƚϴ�,һ�ζ�����,�����ٵ���CH376ByteRead������ȡ,�ļ�ָ���Զ�����ƶ� */
				if ( TotalCount > sizeof(buf) ) i = sizeof(buf);  /* ʣ�����ݽ϶�,���Ƶ��ζ�д�ĳ��Ȳ��ܳ�����������С */
				else i = TotalCount;  /* ���ʣ����ֽ��� */
				s = CH376ByteRead( buf, i, &RealCount );  /* ���ֽ�Ϊ��λ��ȡ���ݿ�,���ζ�д�ĳ��Ȳ��ܳ�����������С,�ڶ��ε���ʱ���Ÿղŵ����� */
				mStopIfError( s );
				TotalCount -= (UINT8)RealCount;  /* ����,��ȥ��ǰʵ���Ѿ��������ַ��� */
				for ( s=0; s!=RealCount; s++ ) printf( "%C", buf[s] );  /* ��ʾ�������ַ� */
				if ( RealCount < i ) {  /* ʵ�ʶ������ַ�������Ҫ��������ַ���,˵���Ѿ����ļ��Ľ�β */
					printf( "\r\n" );
					printf( "�ļ��Ѿ�����\r\n" );
					break;
				}
			}
			printf( "Close\r\n" );
			s = CH376FileClose( FALSE );  /* �ر��ļ� */
			mStopIfError( s );
		}

UnknownUsbDevice:
		printf( "Take out\r\n" );
		//while ( CH376DiskConnect( ) == USB_INT_SUCCESS ) {  /* ���U���Ƿ�����,�ȴ�U�̰γ� */
			//mDelaymS( 100 );
		//}
		//printf("TURN OFF LED\r\n");//LED_UDISK_OUT( );  /* LED�� */
		mDelaymS( 100 );
}

void device(void)
{
	CH376DeviceInit( );  /* ��ʼ��USB�豸ģʽ */
	FreeUSBmS = 0;  /* ���USB���м�ʱ */

	xWriteCH376Cmd( CMD20_SET_SDO_INT );  /* ����SPI��SDO���ŵ��жϷ�ʽ */
	xWriteCH376Data( 0x16 );
	xWriteCH376Data( 0x90 );  /* SDO������SCSƬѡ��Чʱ�����ж�������� */
	xEndCH376Cmd( );
	
		if(!GET_SDO_I())
		{
			mCh375Interrupt();
			//mDelaymS( 250 );mDelaymS( 250 );mDelaymS( 250 );mDelaymS( 250 );
			//CH376OffUSB( );  /* �ر�USB�豸 */	
			/* USB�豸ģʽȫ�����жϷ����д���,�������������������,��ȻҲ��������������ʹ�ò�ѯ��ʽ����USB�豸��ͨѶ */
		}
}

/* CH376��ʼ���ӳ��� */
void CH376DeviceInit( void ) 
{
	UINT8 i;
/* ����USB����ģʽ, ��Ҫ���� */
	xWriteCH376Cmd( CMD_SET_USB_MODE );
	xWriteCH376Data( 2 );  /* ����Ϊʹ�����ù̼���USB�豸��ʽ */
	for ( i=100; i!=0; i-- )
	{
		if ( xReadCH376Data( ) == CMD_RET_SUCCESS )
		{
			printf("Set USB device mode success\r\n");
			memset(USBS_info,0x0,28);
			sprintf(USBS_info,"SET USB Deivce mode sucess.");
			break;  /* �ȴ������ɹ�,ͨ����Ҫ�ȴ�10uS-20uS */
		}
	}
	xEndCH376Cmd( );  /* ����CH376����,������SPI�ӿڷ�ʽ */
/*	if ( i == 0 ) { CH372/CH375/CH376оƬ�ڲ������������Ӵ���Ӳ������ }; */

/* ��������USB�ж�,CH376��INT#���ſ������ӵ���Ƭ�����ж�����,�ж�Ϊ�͵�ƽ��Ч�����½�����Ч,
   �����ʹ���ж�,��ôҲ�����ò�ѯ��ʽ,�ɵ�Ƭ�������ѯCH376��INT#����Ϊ�͵�ƽ */
///	IT0 = 0;  /* ���ⲿ�ź�Ϊ�͵�ƽ���� */
///	IE0 = 0;  /* ���жϱ�־ */
///	EX0 = 1;  /* ����CH376�ж�,�ٶ�CH376��INT#�������ӵ���Ƭ����INT0 */
}

/* CH375�жϷ������,ʹ�üĴ�����1 */
void	mCh375Interrupt(void)
{
	static unsigned char j = 0;
	static unsigned char k = 0;
	unsigned char InterruptStatus;
	unsigned char i, length;
	unsigned char buffer[ 64 ];

	//printf("mCh375Interrupt\r\n" );
	
	xWriteCH376Cmd( CMD_GET_STATUS );  /* ��ȡ�ж�״̬��ȡ���ж����� */
	InterruptStatus = xReadCH376Data( );  /* ��ȡ�ж�״̬ */
	switch ( InterruptStatus ) {  /* �����ж�״̬���� */
		case USB_INT_EP2_OUT: {  /* �����˵��´��ɹ� */
			if(j++ == 200)
			{
			  if(k++ % 20 == 0)
			  	printf("\r\n");
			  printf(".");
			}
			xWriteCH376Cmd( CMD_RD_USB_DATA );  /* �ӵ�ǰUSB�жϵĶ˵㻺������ȡ���ݿ�,���ͷŻ����� */
			length = xReadCH376Data( );  /* ���ȶ�ȡ�������ݳ��� */
			if(length > sizeof(buffer))
			{
				printf("buffer overflow length:%d \r\n",length);
				length = sizeof(buffer);
			}
			for ( i = 0; i < length; i ++ ) buffer[ i ] = xReadCH376Data( );  /* �������ݰ� */
			
			if(buffer[0] == 0x21)
			{
			  memset(USBS_info,0x0,28);
			  sprintf(USBS_info,"USB Connected to PC, Rec DATA");
			}
			  
			/* ����������ȷ��,�����յ������������ȡ���󷵻ظ�PC�� */
			xWriteCH376Cmd( CMD_WR_USB_DATA7 );  /* ��USB�˵�2�ķ��ͻ�����д�����ݿ� */
			xWriteCH376Data( length );  /* ����д��������ݳ���,�ش��ս��յ������ݳ��� */
			for ( i = 0; i < length; i ++ ) xWriteCH376Data( ~ buffer[ i ] );  /* ����ȡ���󷵻�,�ɼ����Ӧ�ó�����������Ƿ���ȷ */
			break;
		}
		case USB_INT_EP2_IN: {  /* �������ݷ��ͳɹ� */
			xWriteCH376Cmd( CMD_UNLOCK_USB );  /* �ͷŵ�ǰUSB������ */
			break;
		}
		default: {  /* �����ж�,δ�õ�,�������˳����� */
			xWriteCH376Cmd( CMD_UNLOCK_USB );  /* �ͷŵ�ǰUSB������ */
			break;
		}
	}
	xEndCH376Cmd( );//��CS��Ч����SDO��Ϊ��һ���жϡ�	
}

/* �ر�CH376������USBͨѶ */
void	CH376OffUSB(void) 
{
///	EX0 = 0;  /* �ر�USB�ж�,��������USB����ģʽ��ʹ�ò�ѯ��ʽ */
/* ����USB����ģʽ, ��Ҫ���� */
	xWriteCH376Cmd( CMD_SET_USB_MODE );
	xWriteCH376Data( 0 );  /* ����Ϊδ���õ�USB�豸��ʽ */
	xEndCH376Cmd( );  /* ����CH376����,������SPI�ӿڷ�ʽ */
	mDelaymS( 10 );  /* ΪUSB�����л�����ʱ�仺��,���Ǳ�Ҫ����ʱ����,�����ü������ΪUSB�豸�Ѿ����� */
/* ���CH376��Ȼ�����ż����,������ʹCH376�л���USB����ģʽ,��ô�ᵼ��������֮��˫USB������ͻ */
}
