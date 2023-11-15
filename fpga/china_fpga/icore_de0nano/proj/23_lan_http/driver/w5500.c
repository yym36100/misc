/*
 * FILE						: w5500.c
 * DESCRIPTION		: This file is iCore3 files.
 * Author					: ysloveivy
 * Copyright			:
 *
 * History
 * --------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * --------------------
 */
 
//--------------------------- Include ---------------------------//

#include "..\include\spi1.h"
#include "..\fwlib\inc\stm32f4xx_gpio.h"
#include "..\include\w5500.h"
#include "..\include\main.h"

//--------------------- Function Prototype ----------------------//
static void delay(int ms);
static int initialize(void);

//--------------------------- Variable --------------------------//
W5500_T w5500={
	.initialize=initialize,
	.mac = {0x00,0x98,0xdc,0x42,0x61,0x11},
	.ip = {192,168,0,10},
	.sub = {255,255,255,0},
	.gw = {192,168,0,1}		
};

unsigned char txsize[MAX_SOCK_NUM] = {2,2,2,2,2,2,2,2};
unsigned char rxsize[MAX_SOCK_NUM] = {2,2,2,2,2,2,2,2};
static unsigned char I_STATUS[MAX_SOCK_NUM];
static unsigned short int SSIZE[MAX_SOCK_NUM];                             /**< Max Tx buffer size by each channel */
static unsigned short int RSIZE[MAX_SOCK_NUM];                             /**< Max Rx buffer size by each channel */

//--------------------------- Function --------------------------//
/*
 * Name						: getISR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned char getISR(unsigned char s)
{
  return I_STATUS[s];
}
/*
 * Name						: putISR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void putISR(unsigned char s, unsigned char val)
{
   I_STATUS[s] = val;
}
/*
 * Name						: getIINCHIP_RxMAX
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned short int getIINCHIP_RxMAX(unsigned char s)
{
   return RSIZE[s];
}
/*
 * Name						: getIINCHIP_TxMAX
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned short int getIINCHIP_TxMAX(unsigned char s)
{
   return SSIZE[s];
}
/*
 * Name						: IINCHIP_CSoff
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void IINCHIP_CSoff(void)
{
	SPI1_CS_OFF;
}
/*
 * Name						: IINCHIP_CSon
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void IINCHIP_CSon(void)
{
	SPI1_CS_ON;
}
/*
 * Name						: IINCHIP_SpiSendData
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned char  IINCHIP_SpiSendData(unsigned char dat)
{
   return(spi1.send_data(dat));
}
/*
 * Name						: IINCHIP_WRITE
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void IINCHIP_WRITE( unsigned long int addrbsb,  unsigned char data)
{
   SPI1_CS_OFF;
   spi1.send_data( (addrbsb & 0x00FF0000)>>16);                                // Address byte 1
   spi1.send_data( (addrbsb & 0x0000FF00)>> 8);                                // Address byte 2
   spi1.send_data( (addrbsb & 0x000000F8) + 4);                                // Data write command and Write data length 1
   spi1.send_data(data);                                                       // Data write (write 1byte data)
	 SPI1_CS_ON;
}
/*
 * Name						: IINCHIP_READ
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned char IINCHIP_READ(unsigned long int addrbsb)
{
   unsigned char data = 0;

   SPI1_CS_OFF;
   spi1.send_data( (addrbsb & 0x00FF0000)>>16);                                // Address byte 1
   spi1.send_data( (addrbsb & 0x0000FF00)>> 8);                                // Address byte 2
   spi1.send_data( (addrbsb & 0x000000F8))    ;                                // Data read command and Read data length 1
   data = spi1.send_data(0x00);                                                // Data read (read 1byte data)
	 SPI1_CS_ON;

   return data;  
}
/*
 * Name						: wiz_write_buf
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned short int wiz_write_buf(unsigned long int addrbsb,unsigned char* buf,unsigned short int len)
{
	 unsigned short int idx = 0;
	 
   SPI1_CS_OFF;
   spi1.send_data( (addrbsb & 0x00FF0000)>>16);                                // Address byte 1
   spi1.send_data( (addrbsb & 0x0000FF00)>> 8);                                // Address byte 2
   spi1.send_data( (addrbsb & 0x000000F8) + 4);                                // Data write command and Write data length 1
   for(idx = 0; idx < len; idx++)                                              // Write data in loop
   {
     spi1.send_data(buf[idx]);
   }
	 SPI1_CS_ON;
   return len; 
}
/*
 * Name						: wiz_read_buf
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned short int wiz_read_buf(unsigned long int addrbsb, unsigned char* buf,unsigned short int len)
{
  unsigned short int idx = 0;

  SPI1_CS_OFF;
	spi1.send_data( (addrbsb & 0x00FF0000)>>16);                                 // Address byte 1
  spi1.send_data( (addrbsb & 0x0000FF00)>> 8);                                 // Address byte 2
  spi1.send_data( (addrbsb & 0x000000F8));                                     // Data write command and Write data length 1
  for(idx = 0; idx < len; idx++)                                               // Write data in loop
  {
    buf[idx] = spi1.send_data(0x00);
  }
	SPI1_CS_ON;
	
  return len;
}

/*
 * Name						: iinchip_init
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void iinchip_init(void)
{
  setMR( MR_RST );
}
/*
 * Name						: sysinit
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void sysinit( unsigned char * tx_size, unsigned char * rx_size  )
{
  short int i;
  short int ssum,rsum;
  ssum = 0;
  rsum = 0;

  for (i = 0 ; i < MAX_SOCK_NUM; i++)                      // Set the size, masking and base address of Tx & Rx memory by each channel
  {
		IINCHIP_WRITE( (Sn_TXMEM_SIZE(i)), tx_size[i]);
		IINCHIP_WRITE( (Sn_RXMEM_SIZE(i)), rx_size[i]);
          
    SSIZE[i] = (int16)(0);
    RSIZE[i] = (int16)(0);


    if (ssum <= 16384)
    {
         switch( tx_size[i] )
      {
      case 1:
        SSIZE[i] = (int16)(1024);
        break;
      case 2:
        SSIZE[i] = (int16)(2048);
        break;
      case 4:
        SSIZE[i] = (int16)(4096);
        break;
      case 8:
        SSIZE[i] = (int16)(8192);
        break;
      case 16:
        SSIZE[i] = (int16)(16384);
      break;
      default :
        RSIZE[i] = (int16)(2048);
        break;
      }
    }

   if (rsum <= 16384)
    {
         switch( rx_size[i] )
      {
      case 1:
        RSIZE[i] = (int16)(1024);
        break;
      case 2:
        RSIZE[i] = (int16)(2048);
        break;
      case 4:
        RSIZE[i] = (int16)(4096);
        break;
      case 8:
        RSIZE[i] = (int16)(8192);
        break;
      case 16:
        RSIZE[i] = (int16)(16384);
        break;
      default :
        RSIZE[i] = (int16)(2048);
        break;
      }
    }
    ssum += SSIZE[i];
    rsum += RSIZE[i];

  }
}

/*
 * Name						: setGAR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setGAR(unsigned char * addr)
{
    wiz_write_buf(GAR0, addr, 4);
}

/*
 * Name						: getGWIP
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void getGWIP(unsigned char * addr)
{
    wiz_read_buf(GAR0, addr, 4);
}

/*
 * Name						: setSUBR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setSUBR(unsigned char * addr)
{   
    wiz_write_buf(SUBR0, addr, 4);
}
/*
 * Name						: setSHAR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setSHAR(unsigned char * addr)
{
  wiz_write_buf(SHAR0, addr, 6);  
}

/*
 * Name						: setSIPR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setSIPR(unsigned char * addr)
{
    wiz_write_buf(SIPR0, addr, 4);  
}
/*
 * Name						: getGAR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void getGAR(unsigned char * addr)
{
    wiz_read_buf(GAR0, addr, 4);
}
/*
 * Name						: getSUBR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void getSUBR(unsigned char * addr)
{
    wiz_read_buf(SUBR0, addr, 4);
}
/*
 * Name						: getSHAR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void getSHAR(unsigned char * addr)
{
    wiz_read_buf(SHAR0, addr, 6);
}
/*
 * Name						: getSIPR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void getSIPR(unsigned char * addr)
{
    wiz_read_buf(SIPR0, addr, 4);
}
/*
 * Name						: setMR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setMR(unsigned char val)
{
  IINCHIP_WRITE(MR,val);
}
/*
 * Name						: getIR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned char getIR( void )
{
   return IINCHIP_READ(IR);
}
/*
 * Name						: setRTR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setRTR(unsigned short int timeout)
{
  IINCHIP_WRITE(RTR0,(unsigned char)((timeout & 0xff00) >> 8));
  IINCHIP_WRITE(RTR1,(unsigned char)(timeout & 0x00ff));
}
/*
 * Name						: setRCR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setRCR(unsigned char retry)
{
  IINCHIP_WRITE(WIZ_RCR,retry);
}
/*
 * Name						: clearIR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void clearIR(unsigned char mask)
{
  IINCHIP_WRITE(IR, ~mask | getIR() ); // must be setted 0x10.
}
/*
 * Name						: setSn_MSS
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setSn_MSS(SOCKET s, unsigned short int Sn_MSSR)
{
  IINCHIP_WRITE( Sn_MSSR0(s), (unsigned char)((Sn_MSSR & 0xff00) >> 8));
  IINCHIP_WRITE( Sn_MSSR1(s), (unsigned char)(Sn_MSSR & 0x00ff));
}
/*
 * Name						: setSn_TTL
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setSn_TTL(SOCKET s, unsigned char ttl)
{    
   IINCHIP_WRITE( Sn_TTL(s) , ttl);
}
/*
 * Name						: getSn_IR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned char getSn_IR(SOCKET s)
{
   return IINCHIP_READ(Sn_IR(s));
}
/*
 * Name						: getSn_SR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned char getSn_SR(SOCKET s)
{
   return IINCHIP_READ(Sn_SR(s));
}
/*
 * Name						: getSn_TX_FSR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned short int getSn_TX_FSR(SOCKET s)
{
  unsigned short int val=0,val1=0;
  do
  {
    val1 = IINCHIP_READ(Sn_TX_FSR0(s));
    val1 = (val1 << 8) + IINCHIP_READ(Sn_TX_FSR1(s));
      if (val1 != 0)
    {
        val = IINCHIP_READ(Sn_TX_FSR0(s));
        val = (val << 8) + IINCHIP_READ(Sn_TX_FSR1(s));
    }
  } while (val != val1);
   return val;
}
/*
 * Name						: getSn_RX_RSR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
unsigned short int getSn_RX_RSR(SOCKET s)
{
  unsigned short int val=0,val1=0;
  do
  {
    val1 = IINCHIP_READ(Sn_RX_RSR0(s));
    val1 = (val1 << 8) + IINCHIP_READ(Sn_RX_RSR1(s));
    if(val1 != 0)
    {
        val = IINCHIP_READ(Sn_RX_RSR0(s));
        val = (val << 8) + IINCHIP_READ(Sn_RX_RSR1(s));
    }
  } while (val != val1);
   return val;
}
/*
 * Name						: send_data_processing
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void send_data_processing(SOCKET s, unsigned char *data, unsigned short int len)
{
  unsigned short int ptr = 0;
  unsigned long int addrbsb = 0;
  ptr = IINCHIP_READ( Sn_TX_WR0(s) );
  ptr = ((ptr & 0x00ff) << 8) + IINCHIP_READ(Sn_TX_WR1(s));

  addrbsb = ((uint32)ptr<<8) + (s<<5) + 0x10;
  wiz_write_buf(addrbsb, data, len);

  ptr += len;
  IINCHIP_WRITE( Sn_TX_WR0(s) ,(uint8)((ptr & 0xff00) >> 8));
  IINCHIP_WRITE( Sn_TX_WR1(s),(uint8)(ptr & 0x00ff));
}
/*
 * Name						: recv_data_processing
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void recv_data_processing(SOCKET s, unsigned char *data, unsigned short int len)
{
  unsigned short int ptr = 0;
  unsigned long int addrbsb = 0;
  
  ptr = IINCHIP_READ( Sn_RX_RD0(s) );
  ptr = ((ptr & 0x00ff) << 8) + IINCHIP_READ( Sn_RX_RD1(s) );

  addrbsb = ((uint32)ptr<<8) + (s<<5) + 0x18;
  wiz_read_buf(addrbsb, data, len);
  ptr += len;

  IINCHIP_WRITE( Sn_RX_RD0(s), (uint8)((ptr & 0xff00) >> 8));
  IINCHIP_WRITE( Sn_RX_RD1(s), (uint8)(ptr & 0x00ff));
}
/*
 * Name						: setSn_IR
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
void setSn_IR(unsigned char s, unsigned char val)
{
    IINCHIP_WRITE(Sn_IR(s), val);
}
/*
 * Name						: initialize
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
static int initialize(void)                                   //初始化设置
{
	delay(2000);
	while((IINCHIP_READ(PHYCFGR)& LINK)==0);                    //等待以太网连接完成
	
	setMR( MR_RST );
	delay(100);	
	
	setSHAR(w5500.mac);
	setSUBR(w5500.sub);
	setGAR(w5500.gw);
	setSIPR(w5500.ip);

  sysinit(txsize,rxsize);	
	
	setRTR(2000);                                              /*设置溢出时间值*/
	setRCR(8);                                                 /*设置最大重新发送次数*/
	
	IINCHIP_WRITE( IMR,IM_IR7 | IM_IR6); 
	IINCHIP_WRITE( SIMR, S0_IMR);  
	IINCHIP_WRITE( Sn_IMR(0), IMR_SENDOK | IMR_TIMEOUT | IMR_RECV | IMR_DISCON | IMR_CON);

	return 0;
}
/*
 * Name						: delay
 * Description		: ---
 * Author					: ysloveivy.
 *
 * History
 * ----------------------
 * Rev						: 0.00
 * Date						: 12/20/2015
 *
 * create.
 * ----------------------
 */
static void delay(int ct) //ms
{
	int i, j;

	for (i = 0; i < ct; i++) 
	{
		for (j = 0; j < 10000; j++) ;
	}
}

