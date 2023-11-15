
#include <stdio.h>

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#include "../inc/common.h"
#include "../inc/hal.h"
#include "../inc/delay.h"

extern unsigned char DBUF[BUFFER_LENGTH];

/* This function is only for GPIO test */
void IO_test(void)
{
    if(SD_DO)
    {
        SD_CS(1);
        SD_CLK(0);
        SD_DI(1);
        printf("High\n");
    }
    else
    {
        SD_CS(0);
        SD_CLK(1);
        SD_DI(0);
        printf("Low\n");        
    }               
}

/* Write one byte to sd/mmc card*/
void SdWrite(unsigned char  n)
{    
    unsigned char i;
    
    for(i=8;i;i--)
    {
        SD_CLK(0);
        if(n & 0x80)
          SD_DI(1);
        else
          SD_DI(0);
        n <<= 1;
        SD_CLK(1);
    }
    SD_DI(1);//SD_DI=1;      
}   

/* Read one byte to sd/mmc card*/
unsigned char SdRead(void)
{
    unsigned char n,i;
    
    n = 0;
    for(i=8;i;i--)
    {   
        SD_CLK(0);
        SD_CLK(1);
        n <<= 1;
        if(SD_DO) n|= 1;
    }
    return n;
}

/* Read sd/mmc card response */
unsigned char SdResponse(void)
{
  unsigned char i=0,response;
  
  while(i <= 8)
  {
    response = SdRead();
    //printf("\r%02x \r\n" ,response);
    if(response == 0x00)
      break;
    if(response == 0x01)
      break;
    i++;
  }
  return response;
}  
//================================================================
void SdCommand(unsigned char command, unsigned long argument, unsigned char crc)
{
#if 0
	unsigned char argu[4];
	argu[0] = argument & 0xff;
	argu[2] = (argument >> 8) & 0xff;
	argu[2] = (argument >> 16) & 0xff;
	argu[3] = (argument >> 24) & 0xff;	

	//printf("argu : %02x,%02x,%02x,%02x \n",argu[0],argu[1],argu[2],argu[3]);	

	SdWrite(command | 0x40);
	SdWrite(argu[0]);
	SdWrite(argu[1]);
	SdWrite(argu[2]);
	SdWrite(argu[3]);
	SdWrite(crc);
#else
	SdWrite(command | 0x40);
	SdWrite(((unsigned char *)&argument)[3]);
	SdWrite(((unsigned char *)&argument)[2]);
	SdWrite(((unsigned char *)&argument)[1]);
	SdWrite(((unsigned char *)&argument)[0]);
	SdWrite(crc);
#endif
}
//================================================================
unsigned char SdInit(void)
{
  ///int delay=0, trials=0;
  unsigned int i;//,j;
  unsigned char response=0x01;

  SD_CS(1);
  for(i=0;i<=0x0f;i++)
  usleep(5);
  SdWrite(0xff);
  SD_CS(0);
  
  //Send Command 0 to put MMC in SPI mode
 // for(i=0; i<200; i++)
    for(i=0; i<1; i++)
  {
	SdCommand(0x00,0,0x95);

	response = SdResponse();
    
	if(response != 0x01)
	{
		//return 0;
		continue;
	} 
	break;
  }

  if(i >= 200)
  {
	printf(" response err ,time out\r\n");
    SD_CS(1);	
	return 0;
  }

  i = 0;

  while(response == 0x01)
  {
    SD_CS(1);
    SdWrite(0xff);
    SD_CS(0);
    SdCommand(0x01,0x00ffc000,0xff);
    //SdCommand(0x01,0,0xff);
    response = SdResponse();
	
	if((i++) >= 2000)
	{
  		SD_CS(1);
		printf("CMD1 response err\n");		
		return 0;
	}
  }
  
  SD_CS(1);
  SdWrite(0xff);
  return 1;  
}
//================================================================
unsigned char SdWriteBlock(unsigned char *Block, unsigned long address)
{
  unsigned char  count;
  unsigned char dataResp;
  //Block size is 512 bytes exactly
  //First Lower SS
  
  SD_CS(0);//SD_CS=0;
  //Then send write command
  SdCommand(0x18,address,0xff);
  
  if(SdResponse()==00)
  {
    SdWrite(0xff);
	SdWrite(0xff);
	SdWrite(0xff);
    //command was a success - now send data
    //start with DATA TOKEN = 0xFE
    SdWrite(0xfe);
    //now send data
    for(count=0;count<128;count++)
    {
      SdWrite(*Block++);
	  SdWrite(*Block++);
	  SdWrite(*Block++);
	  SdWrite(*Block++);
    }
    //data block sent - now send checksum
    SdWrite(0xff);
    SdWrite(0xff);
    //Now read in the DATA RESPONSE token
    dataResp=SdRead();
    //Following the DATA RESPONSE token
    //are a number of BUSY bytes
    //a zero byte indicates the MMC is busy

    while(SdRead()==0);

    dataResp=dataResp&0x0f;	//mask the high byte of the DATA RESPONSE token
    SD_CS(1);//SD_CS=1;
    SdWrite(0xff);
    if(dataResp==0x0b)
      {
      //printf("DATA WAS NOT ACCEPTED BY CARD -- CRC ERROR\n");
      return 0;
      }
    if(dataResp==0x05)
      return 1;
      
    printf("Invalid data Response token.\r\n");
    return 0;
 }
  printf("Command 0x18 (Write) was not received by the MMC.\r\n");
  return 0;
}
//=======================================================================
unsigned char SdReadBlock(unsigned char *Block, unsigned long address)
{
   unsigned char count;
   unsigned char spon;
  //Block size is 512 bytes exactly
  //First Lower SS
  
  //printf(" MMC_read_block, address : %08x\n",address);
  
  SD_CS(0);//SD_CS=0;
  //Then send write command
  SdCommand(0x11,address,0xff);

  spon = SdResponse();
  //if(SdResponse()==0x00)
  if(!spon)
  {
    //command was a success - now send data
    //start with DATA TOKEN = 0xFE
    while(SdRead()!=0xfe);

    for(count=0;count<128;count++)
    {
      *Block++ = SdRead();
	  *Block++ = SdRead();
	  *Block++ = SdRead();
	  *Block++ = SdRead();
    }
    //data block sent - now send checksum
    SdRead();
    SdRead();
    //Now read in the DATA RESPONSE token
    SD_CS(1);//SD_CS=1;
    SdRead();
    return 1;
 }
  printf(" Command 0x11 (Read) was not received by the MMC.spon = %02x\r\n",spon);
  return 0;
}
//================================================================

void ComSendByte(unsigned char c)
{
	//SBUF=c;
	//while(!TI);
	//TI=0;
	//printf("[%02x][%c]\n",c,c);
	//UART0_putc_wait(c);
	
}

//================================================================
void DelayMs(unsigned char nFactor)
{
	usleep(nFactor*1000);
}

unsigned int LSwapINT16(unsigned short dData1,unsigned short dData2)
{
    unsigned int dData;
    dData = ((dData2<<8)&0xff00)|(dData1&0x00ff);
	return dData;
}

unsigned long LSwapINT32(unsigned long dData1,unsigned long dData2,unsigned long dData3,unsigned long dData4)
{
    unsigned long dData;
    dData = ((dData4<<24)&0xff000000)|((dData3<<16)&0xff0000)|((dData2<<8)&0xff00)|(dData1&0xff);
	return dData;
}

