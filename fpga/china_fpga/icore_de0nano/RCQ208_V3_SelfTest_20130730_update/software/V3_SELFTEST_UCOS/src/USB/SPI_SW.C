/* CH376оƬ ����ģ��SPI�������ӵ�Ӳ������� V1.0 */
/* �ṩI/O�ӿ��ӳ��� */

#include	"HAL.H"
#include	"fpga_io.h"

/* �����е�Ӳ�����ӷ�ʽ����(ʵ��Ӧ�õ�·���Բ����޸��������弰�ӳ���) */
/* ��Ƭ��������    CH376оƬ������
      P1.4                 SCS
      P1.5                 SDI
      P1.6                 SDO
      P1.7                 SCK      */
//sbit	P14					=	P1^4;
//sbit	P15					=	P1^5;
//sbit	P16					=	P1^6;
//sbit	P17					=	P1^7;

//IO Set function
#define	SET_USB_SCS_O(a)	IOWR_ALTERA_AVALON_PIO_DATA(USB_SCS_O_BASE, a)
#define	SET_USB_SDI_O(a)	IOWR_ALTERA_AVALON_PIO_DATA(USB_SDI_O_BASE, a)
#define	SET_USB_SCK_O(a)	IOWR_ALTERA_AVALON_PIO_DATA(USB_SCK_O_BASE, a)
#define	SET_USB_RST_O(a)	IOWR_ALTERA_AVALON_PIO_DATA(USB_RST_O_BASE, a)

//IO Get function
#define	GET_SDO_I()	    	IORD_ALTERA_AVALON_PIO_DATA(USB_SDO_I_BASE			)
#define	GET_INT_I()	    	IORD_ALTERA_AVALON_PIO_DATA(USB_INT_I_BASE			)
#define	GET_PC_CONNECT_I()	IORD_ALTERA_AVALON_PIO_DATA(USB_PC_I_BASE			)

//#define	CH376_SPI_SCS	//		P14		/* �ٶ�CH376��SCS���� */
//#define	CH376_SPI_SDI	//		P15		/* �ٶ�CH376��SDI���� */
#define	CH376_SPI_SDO	1//		P16		/* �ٶ�CH376��SDO���� */
//#define	CH376_SPI_SCK	//		P17		/* �ٶ�CH376��SCK���� */
/*#define	CH376_SPI_BZ			P10*/		/* �ٶ�CH376��BZ���� */

///#define CH376_INT_WIRE		//	xsyan mask.INT0	/* �ٶ�CH376��INT#����,���δ������ôҲ����ͨ����ѯ�����ж������SDO����״̬ʵ�� */

void	CH376_PORT_INIT( void )  /* ����ʹ������ģ��SPI��дʱ��,���Խ��г�ʼ�� */
{
/* �����Ӳ��SPI�ӿ�,��ô��ʹ��mode3(CPOL=1&CPHA=1)��mode0(CPOL=0&CPHA=0),CH376��ʱ�������ز�������,�½������,����λ�Ǹ�λ��ǰ */
	SET_USB_SCS_O(1);//CH376_SPI_SCS = 1;  /* ��ֹSPIƬѡ */
	SET_USB_SCK_O(1);//CH376_SPI_SCK = 1;  /* Ĭ��Ϊ�ߵ�ƽ,SPIģʽ3,Ҳ������SPIģʽ0,��ģ���������������޸� */
/* ����˫��I/O����ģ��SPI�ӿ�,��ô�����ڴ�����SPI_SCS,SPI_SCK,SPI_SDIΪ�������,SPI_SDOΪ���뷽�� */
}

void	mDelay0_5uS( void )  /* ������ʱ0.5uS,���ݵ�Ƭ����Ƶ���� */
{
	usleep(1);
}

void	Spi376OutByte( UINT8 d )  /* SPI���8��λ���� */
{  /* �����Ӳ��SPI�ӿ�,Ӧ�����Ƚ�����д��SPI���ݼĴ���,Ȼ���ѯSPI״̬�Ĵ����Եȴ�SPI�ֽڴ������ */
	UINT8	i;
	for (i=0; i<8; i++) 
	{		
		SET_USB_SCK_O(0);//CH376_SPI_SCK = 0;	
		if (d & 0x80) 
			SET_USB_SDI_O(1);//CH376_SPI_SDI = 1;
		else 
			SET_USB_SDI_O(0);//CH376_SPI_SDI = 0;

		d <<= 1;  /* ����λ�Ǹ�λ��ǰ */		

		SET_USB_SCK_O(1);//CH376_SPI_SCK = 1;  /* CH376��ʱ�������ز������� */
	}
	//SET_USB_SCK_O(0);
}

UINT8	Spi376InByte( void )  /* SPI����8��λ���� */
{  /* �����Ӳ��SPI�ӿ�,Ӧ�����Ȳ�ѯSPI״̬�Ĵ����Եȴ�SPI�ֽڴ������,Ȼ���SPI���ݼĴ����������� */
	UINT8 i, d = 0;
	d = 0;
	for ( i = 0; i < 8; i ++ ) 
	{
		SET_USB_SCK_O(0);//CH376_SPI_SCK = 1;	
		d <<= 1;
		if (GET_SDO_I()/*CH376_SPI_SDO*/ ) 
			d++;
		SET_USB_SCK_O(1);//CH376_SPI_SCK = 0;  /* CH376��ʱ���½������ */
	}	
	return( d );
}

#define	xEndCH376Cmd( )	{ SET_USB_SCS_O(1);/*CH376_SPI_SCS = 1;*/ }  /* SPIƬѡ��Ч,����CH376����,������SPI�ӿڷ�ʽ */

void	xWriteCH376Cmd( UINT8 mCmd )  /* ��CH376д���� */
{
#ifdef	CH376_SPI_BZ
	UINT8	i;
#endif
	SET_USB_SCS_O(1);//CH376_SPI_SCS = 1;  /* ��ֹ֮ǰδͨ��xEndCH376Cmd��ֹSPIƬѡ */
	mDelay0_5uS( );
/* ����˫��I/O����ģ��SPI�ӿ�,��ô����ȷ���Ѿ�����SPI_SCS,SPI_SCK,SPI_SDIΪ�������,SPI_SDOΪ���뷽�� */
	SET_USB_SCS_O(0);//CH376_SPI_SCS = 0;  /* SPIƬѡ��Ч */
	Spi376OutByte( mCmd );  /* ���������� */
#ifdef	CH376_SPI_BZ
	for ( i = 30; i != 0 && CH376_SPI_BZ; -- i );  /* SPIæ״̬��ѯ,�ȴ�CH376��æ,��������һ�е���ʱ1.5uS���� */
#else
	mDelay0_5uS( ); mDelay0_5uS( ); mDelay0_5uS( );  /* ��ʱ1.5uSȷ����д���ڴ���1.5uS,����������һ�е�״̬��ѯ���� */
#endif
}

#ifdef	FOR_LOW_SPEED_MCU  /* ����Ҫ��ʱ */
#define	xWriteCH376Data( d )	{ Spi376OutByte( d ); }  /* ��CH376д���� */
#define	xReadCH376Data( )		( Spi376InByte( ) )  /* ��CH376������ */
#else
void	xWriteCH376Data( UINT8 mData )  /* ��CH376д���� */
{
	Spi376OutByte( mData );
	mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
}
UINT8	xReadCH376Data( void )  /* ��CH376������ */
{
	mDelay0_5uS( );  /* ȷ����д���ڴ���0.6uS */
	return( Spi376InByte( ) );
}
#endif

/* ��ѯCH376�ж�(INT#�͵�ƽ) */
UINT8	Query376Interrupt( void )
{
#ifdef	CH376_INT_WIRE
	return( CH376_INT_WIRE ? FALSE : TRUE );  /* ���������CH376���ж�������ֱ�Ӳ�ѯ�ж����� */
#else
	return( GET_SDO_I()/*CH376_SPI_SDO*/ ? FALSE : TRUE );  /* ���δ����CH376���ж��������ѯ�����ж������SDO����״̬ */
#endif
}

UINT8	mInitCH376Host( void )  /* ��ʼ��CH376 */
{
	UINT8	res;
	while(1)
	{
		CH376_PORT_INIT( );  /* �ӿ�Ӳ����ʼ�� */	

		xWriteCH376Cmd(CMD_GET_IC_VER);
		res = xReadCH376Data( );
		printf("CMD_GET_IC_VER = %02x\r\n",res);
		xEndCH376Cmd();
		
		xWriteCH376Cmd( CMD11_CHECK_EXIST );  /* ���Ե�Ƭ����CH376֮���ͨѶ�ӿ� */
		xWriteCH376Data( 0x65 );
		res = xReadCH376Data( );
		xEndCH376Cmd();
		if ( res != 0x9A ) 
		{
			printf("ERR_USB_UNKNOWN\r\n");
			usleep(1000000);
			//return( ERR_USB_UNKNOWN );  /* ͨѶ�ӿڲ�����,����ԭ����:�ӿ������쳣,�����豸Ӱ��(Ƭѡ��Ψһ),���ڲ�����,һֱ�ڸ�λ,���񲻹��� */
			continue;
		}
		break;
	}
	
	xWriteCH376Cmd( CMD11_SET_USB_MODE );  /* �豸USB����ģʽ */
	xWriteCH376Data( 0x06 );
	mDelayuS( 20 );
	res = xReadCH376Data( );
	xEndCH376Cmd( );
#ifndef	CH376_INT_WIRE
#ifdef	CH376_SPI_SDO
	xWriteCH376Cmd( CMD20_SET_SDO_INT );  /* ����SPI��SDO���ŵ��жϷ�ʽ */
	xWriteCH376Data( 0x16 );
	xWriteCH376Data( 0x90 );  /* SDO������SCSƬѡ��Чʱ�����ж�������� */
	xEndCH376Cmd( );
#endif
#endif
	if ( res == CMD_RET_SUCCESS ) return( USB_INT_SUCCESS );
	else return( ERR_USB_UNKNOWN );  /* ����ģʽ���� */
}