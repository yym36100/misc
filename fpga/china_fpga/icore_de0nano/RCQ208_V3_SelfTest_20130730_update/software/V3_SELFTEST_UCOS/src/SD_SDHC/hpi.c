

//#include <stm32f10x_lib.h>                        // STM32F10x Library Definitions

#include <stdio.h>
#include "../inc/common.h"
#include "../inc/device.h"
#include "../inc/hpi.h"
#include "../inc/hal.h"
#include "../inc/fat.h"
#include "../inc/fat32.h"
#include "../inc/hpi32.h"

#include "../inc/main.h"

extern FLAGS bFlags;
extern unsigned char DBUF[BUFFER_LENGTH];
//////////////////////////////////////////
unsigned char UARTBUF[UARTBUF_LENGTH];
SYS_INFO_BLOCK DeviceInfo;
FILE_INFO ThisFile;

Command_Def Command;
Response_Def Response;

unsigned int DirStartCluster,NowCluster;
unsigned long NowSector;
ShowFileName_Def ShowFileName[MaxLFNum];	//long file struct
/////////////////////////////////////////////

#define UART_LSR_TX_RDY	(1<<0)
#define UART_LSR_RX_RDY	(1<<1)
#define UART_TX_EMPTY		(1<<6)
#define UART_RX_EMPTY		(1<<7)

#define UART0_tx_rdy()		(regs0->uart0_lsr & UART_LSR_TX_RDY)
#define UART0_rx_rdy()		(regs0->uart0_lsr & UART_LSR_RX_RDY)
#define UART0_tx_empty()	(regs0->uart0_lsr & UART_TX_EMPTY)
#define UART0_sft_reset()		(regs0->uart0_lsr & (1 << 7))
#define UART0_RxEmpty()		(!UART0_rx_rdy())
#define UART0_Getc()			(regs0->uart0_data)
#define UART0_Putc(c)		(regs0->uart0_data = (c))
#define UART0_tx_wait()		do { while (!UART0_tx_rdy()); } while (0)
#define UART0_putc_wait(c)	do { UART0_tx_wait(); UART0_Putc(c); } while (0)

void UartSendRsp(void)
{
	unsigned int i;
	unsigned char *pBuf=(unsigned char *)&Response;
	Turn_OFF_LED4();//MCU_LED4=0;
	for(i=0;i<5;i++)
	{
		ComSendByte(*(pBuf+i));
		//printf(" %2x",*(pBuf+i));
	}	
	if(Response.len != 0)
	{
		for(i=0; i<Response.len; i++)
		{
			ComSendByte(UARTBUF[i]);			
		}
	}
	Turn_ON_LED4();//MCU_LED4=1;
}

unsigned char UartHandler(void)
{
  Response.Result=0;Response.len=0;
  printf(" Command.CLass = %02x\n",Command.CLass);
  switch(Command.CLass)
  {
    case 0x00:	//List	
    	printf(" List\n");    
    	Response.Result=List();
    	break;  
  	case 0x01:	//Open File
    	printf(" OpenFile\n");
 		Response.Result=OpenFile(Command.Parameter);		
     	break;
	case 0x02:	//Read File	
    	printf(" ReadFile\n");	
		Response.Result=ReadFile(Command.len,UARTBUF);
		break;   
    case 0x03:	//Set Pointer
    	printf(" SetFilePointer\n");
		Response.Result=SetFilePointer(Command.len);	
		break;
	case 0x04:	//Great File
    	printf(" OpenFile\n");
		Response.Result=OpenFile(Command.Parameter);
		if(Response.Result)
			{
			Response.Result=SetFilePointer(ThisFile.LengthInByte);
			}
		else
    		Response.Result=CreateFile(Command.len,Command.Parameter,UARTBUF);    	
    	break; 
	case 0x05:	//Write File
    	Response.Result=WriteFile(Command.len,UARTBUF);
    	break; 
    case 0x06:	//Remove File
    	ThisFile.bFileOpen=0;	
    	Response.Result=RemoveFile(Command.Parameter);
    	break; 	
	case 0x07:	//Get Space    	
    	Response.Result=GetCapacity();
    	break;     
	case 0x08:  //DetectDisk
		if(bFlags.bits.SLAVE_IS_ATTACHED)
			Response.Result=1;
		break;
	case 0x09:  //Great Dir
		Response.Result=DownDir(Command.Parameter);
		if(!Response.Result)
			Response.Result=CreateDir(Command.len,Command.Parameter,UARTBUF);    	
    	break; 
	case 0x0a:	//Down Dir
		Response.Result=DownDir(Command.Parameter);
		break;
	case 0x0b:	//Up Dir
		Response.Result=UpDir();
		break;	
	case 0x0c:	//Up RootDir
		Response.Result=UpRootDir();
		break;	
  }

  UartSendRsp();
  ///////////////////////////////
  return TRUE;  
}

unsigned char List(void)
{
	unsigned int item,i;
	unsigned char k,bstop,sector;
	unsigned char Lcount,Ncount,base;
	
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;			
	item=0;
	bstop=0;
	////////////////////////////////////
	Lcount=0;
	for(i=0;i<MaxLFNum;i++)
	{
		ShowFileName[i].LongName[0]=0x00;
		ShowFileName[i].LongName[1]=0x00;
	}
	/////////////////////////////////////

	if(DirStartCluster==0)	//Root Dir
	{
		for(sector=0;sector<DeviceInfo.BPB_RootEntCnt;sector++)
		{   
			if(!SdReadSector(DeviceInfo.RootStartSector+sector,1,DBUF))
				return FALSE;			
			for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
				{
				if(DBUF[i]==0x00)
					{bstop=1;
					break;}
				else if(DBUF[i]==0xE5)
					continue;			
				else
					{
					for(k=0;k<32;k++)
						UARTBUF[item*32+k]=DBUF[i+k];
					item=item+1;
				    if(item>=(UARTBUF_LENGTH/32))  {bstop=1;break;}  //串口缓冲 只能有512项目录，强行结束
					/////////////////////////////////
					if(Lcount<MaxLFNum)
					{
					if(DBUF[i+11]==0x0F)
						{
						base=((DBUF[i]&0x1F)-1)*26;
						if(base<=224)
						{
						Ncount=0;
						for(k=1;k<11;k++)
							{
							ShowFileName[Lcount].LongName[base+Ncount]=DBUF[i+k];
							Ncount++;
							}
						for(k=14;k<26;k++)
							{
							ShowFileName[Lcount].LongName[base+Ncount]=DBUF[i+k];
							Ncount++;
							}
						for(k=28;k<32;k++)
							{
							ShowFileName[Lcount].LongName[base+Ncount]=DBUF[i+k];
							Ncount++;
							}
						}
						}
					else
						{
						for(k=0;k<32;k++)
							ShowFileName[Lcount].item[k]=DBUF[i+k];
					    Lcount++;					
						}
					}//if(Lcount<MaxLFNum)
					/////////////////////////////////
					}
				}
			
			if(bstop==1)break;		
		}
	Response.len=item*32;
	return TRUE;
	}
//////////////////////////////////////////////////////////////////   
	else		//Son Dir
	{
		NowCluster=DirStartCluster;		
		do
		{
			NowSector=FirstSectorofCluster(NowCluster);
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
	    	{   
				if(!SdReadSector(NowSector+sector,1,DBUF))
					return FALSE;				
				for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
				{
					if(DBUF[i]==0x00)
						{bstop=1;break;}
					else if(DBUF[i]==0xE5)
						continue;			
					else
					{
						for(k=0;k<32;k++)
							UARTBUF[item*32+k]=DBUF[i+k];
						item=item+1;
						/////////////////////////////////
						if(DBUF[i+11]==0x0F)
						{
							base=((DBUF[i]&0x1F)-1)*26;
							if(base<=224)
							{
								Ncount=0;
								for(k=1;k<11;k++)
								{
									ShowFileName[Lcount].LongName[base+Ncount]=DBUF[i+k];
									Ncount++;
								}
								for(k=14;k<26;k++)
								{
									ShowFileName[Lcount].LongName[base+Ncount]=DBUF[i+k];
									Ncount++;
								}
								for(k=28;k<32;k++)
								{
									ShowFileName[Lcount].LongName[base+Ncount]=DBUF[i+k];
									Ncount++;
								}
							}
						}
						else
						{
							for(k=0;k<32;k++)
								ShowFileName[Lcount].item[k]=DBUF[i+k];
				 		   Lcount++;							
						}			
				/////////////////////////////////
					}
				}
				if(bstop==1)break;		
	    	}

			if(bstop==1)break;
	
			NowCluster=GetNextClusterNum(NowCluster); 
			
		}while(NowCluster<=0xffef);

	Response.len=item*32;
	return TRUE;
	}
}

unsigned char OpenFile(unsigned char *pBuffer)
{
	unsigned int i;
	unsigned char j,bstop,sector;
	bstop = 0;
	sector = 0;
		
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;			
	ThisFile.bFileOpen=0;

	if(DirStartCluster==0)	//Root Dir
	{
	for(sector=0;sector<DeviceInfo.BPB_RootEntCnt;sector++)
	    {   
		if(!SdReadSector(DeviceInfo.RootStartSector+sector,1,DBUF))
			return FALSE;
		for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
			{
			if(DBUF[i]==0x00)
				return FALSE;
			j=0;
			while(DBUF[i+j]==*(pBuffer+j))
				{
				 j=j+1;
				 if(j>10)
				 	break;
				}
			
			if(j>10&&(DBUF[i+11]&0x10)!=0x10)
			    {
			    for(j=0;j<32;j++)
			    	UARTBUF[j]=DBUF[i+j];		    
			    bstop=1;
			    break;}
			
			}
		if(bstop==1)break;
		}
	    
	    if(sector>=DeviceInfo.BPB_RootEntCnt)
	    	return FALSE;	
	}
///////////////////////////////////////////////////////////////////////////////////////
	else
	{
		NowCluster=DirStartCluster;		
		do
		{
			NowSector=FirstSectorofCluster(NowCluster);
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
	    	{   
				if(!SdReadSector(NowSector+sector,1,DBUF))
					return FALSE;				
				for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
				{
					if(DBUF[i]==0x00)
						return FALSE;
					j=0;
					while(DBUF[i+j]==*(pBuffer+j))
					{
						 j=j+1;
						 if(j>10)
						 	break;
					}
					if(j>10&&(DBUF[i+11]&0x10)!=0x10)
				    	{ 
						for(j=0;j<32;j++)
			    			UARTBUF[j]=DBUF[i+j];			    
			    		bstop=1;
			    		break;
						}
				}
				if(bstop==1)break;		
	    	}
			if(bstop==1)break;	
			NowCluster=GetNextClusterNum(NowCluster);			
		}while(NowCluster<=0xffef);
		
		if(NowCluster>0xffef)
	    	return FALSE;
	}

	ThisFile.bFileOpen=1;
	ThisFile.StartCluster=LSwapINT16(UARTBUF[26],UARTBUF[27]);
	ThisFile.LengthInByte=LSwapINT32(UARTBUF[28],UARTBUF[29],UARTBUF[30],UARTBUF[31]);
	ThisFile.ClusterPointer=ThisFile.StartCluster;	
	ThisFile.SectorPointer=FirstSectorofCluster(ThisFile.StartCluster);
	ThisFile.OffsetofSector=0;
	ThisFile.SectorofCluster=0;	
	ThisFile.FatSectorPointer=0;	
	ThisFile.pointer=0;
	
	Response.len=32;
	return TRUE;	
}

unsigned char ReadFile(unsigned long readLength,unsigned char *pBuffer)
{

	unsigned int len,i;
	unsigned int tlen;	
	unsigned long blen;

	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;		
	if(!ThisFile.bFileOpen)
		return FALSE;

	blen=readLength;

	tlen=0;
	if(readLength>MAX_READ_LENGTH)
		return FALSE;	
	
	if(readLength+ThisFile.pointer>ThisFile.LengthInByte)
		return FALSE;	
		
	////////////////////////////////////////////		
		while(readLength>0)
		{
		   if(readLength+ThisFile.OffsetofSector>DeviceInfo.BPB_BytesPerSec)
		   	len=DeviceInfo.BPB_BytesPerSec;
		   else
		   	len=readLength+ThisFile.OffsetofSector;
		   
		   //////////////////////////////////////////////////////
		   if(ThisFile.OffsetofSector>0)
		   	{
		   	if(SdReadSector(ThisFile.SectorPointer,1,DBUF))
		   		{
		   		
		   		len=len-ThisFile.OffsetofSector;
		   		for(i=0;i<len;i++)
		   			
		   			*(pBuffer+i)=DBUF[ThisFile.OffsetofSector+i];
		   		ThisFile.OffsetofSector=ThisFile.OffsetofSector+len;
		   		}
		   	else
		   		return FALSE;		   		
		   	}
		   else
		   	{
		   		if(!SdReadSector(ThisFile.SectorPointer,1,pBuffer+tlen))
		   				return FALSE;	
		   		ThisFile.OffsetofSector=len;
		   	}
		   ////////////////////////////////////////////////////////////
		   readLength-=len;
		   tlen+=len;
		  
		   /////////////////////////////////////////////////////////
		   if(ThisFile.OffsetofSector>DeviceInfo.BPB_BytesPerSec-1)
		   {	
		   	ThisFile.OffsetofSector-=DeviceInfo.BPB_BytesPerSec;
		   	ThisFile.SectorofCluster+=1;
		   	if(ThisFile.SectorofCluster>DeviceInfo.BPB_SecPerClus-1)
		   	{
		   		ThisFile.SectorofCluster=0;
		 		 ThisFile.ClusterPointer=GetNextClusterNum(ThisFile.ClusterPointer);
		 		 if(ThisFile.ClusterPointer>0xffef)
		 		 	   return FALSE;			 		 	
		 		 ThisFile.SectorPointer=FirstSectorofCluster(ThisFile.ClusterPointer); 	
		   	}
		   	else
		   		ThisFile.SectorPointer=ThisFile.SectorPointer+1;
		    }
		   //////////////////////////////////////////////////////////////////
		}//end while
		
	ThisFile.bFileOpen=1;
	ThisFile.pointer+=tlen;
	//////////////////////////////////////////////
	Response.len=blen;

	return TRUE;
}

unsigned char SetFilePointer(unsigned long pointer)
{
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;		
	if(!ThisFile.bFileOpen)
		return FALSE;		
	///////////////////////////////////////////////////////////
	ThisFile.pointer=pointer;
	if(ThisFile.pointer>ThisFile.LengthInByte)
		return FALSE;	

	if(!GoToPointer(ThisFile.pointer))
	{
	ThisFile.bFileOpen=0;
	return FALSE;	
	}
	//////////////////////////////////////////////
	return TRUE;
}

unsigned char CreateFile(unsigned long len,unsigned char *pBuffer,unsigned char *pName)
{
	unsigned int sector,i,j,DirCount;
	unsigned int cnum,ClusterPointer;
	unsigned char bstop = 0,InByte = 0,bwrite = 0;
	
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;
	if((len%32)!=0)
		return FALSE;
	if((len+32)>DeviceInfo.BPB_BytesPerSec)
		return FALSE;

	ThisFile.bFileOpen=0;	

	cnum=GetFreeCusterNum();
	if(cnum<0x02)
		return FALSE;	

	pBuffer[26]=(unsigned char)(cnum);
	pBuffer[27]=(unsigned char)(cnum>>8);
	pBuffer[28]=0;pBuffer[29]=0;pBuffer[30]=0;pBuffer[31]=0;
	bstop=0;
	
	if(DirStartCluster==0)	
	{
	/////// Search a free space in the root dir space and build the item ///
	for(sector=0;sector<DeviceInfo.BPB_RootEntCnt;sector++)
	    {   
		if(!SdReadSector(DeviceInfo.RootStartSector+sector,1,DBUF))
			return FALSE;
		DirCount=0;bwrite=0;
		for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
			{
			if(len==0)
				{
				if((DBUF[i]==0x00)||(DBUF[i]==0xE5))
				{
				for(j=0;j<32;j++)
					DBUF[i+j]=*(pBuffer+j);
				if(!SdWriteSector(DeviceInfo.RootStartSector+sector,1,DBUF))
		  	 		return FALSE;		  	 		
				bstop=1;
				break;
				}
				}
			else
			{
			if(DirCount==0)
				InByte=i;
			if(DBUF[i]==0xE5)				
				DirCount++;				
			else if(DBUF[i]==0x00)
				{	
				DirCount++;	
				DBUF[i]=0xE5;
				bwrite=1;				
				}
			else
				DirCount=0;

			if((DirCount*32)>=(len+32))
				{
				for(j=0;j<len;j++)
					DBUF[InByte+j]=*(pName+j);

				for(j=0;j<32;j++)
					DBUF[InByte+len+j]=*(pBuffer+j);

				if(!SdWriteSector(DeviceInfo.RootStartSector+sector,1,DBUF))
		  	 		return FALSE;		  	 		
				bstop=1;
				break;
				}
			 }
			}		
		if(bstop==1)break;
		
		if((len!=0)&&(bwrite==1))
			{
			if(!SdWriteSector(DeviceInfo.RootStartSector+sector,1,DBUF))
		  		return FALSE;
	    	}
		}

	if(sector>=DeviceInfo.BPB_RootEntCnt)
		return FALSE;
	}
////////////////////////////////////////////////////////////
	else
	{
		NowCluster=DirStartCluster;		
		do
		{
			NowSector=FirstSectorofCluster(NowCluster);
			ClusterPointer=NowCluster;
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
	    	{   
				if(!SdReadSector(NowSector+sector,1,DBUF))
					return FALSE;
				DirCount=0;bwrite=0;

				for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
				{
				if(len==0)
					{
					if((DBUF[i]==0x00)||(DBUF[i]==0xE5))
					{
					for(j=0;j<32;j++)
						DBUF[i+j]=*(pBuffer+j);
					if(!SdWriteSector(NowSector+sector,1,DBUF))
		  	 			return FALSE;		  	 		
					bstop=1;
					break;
					}		
					}
				else
				{
				if(DirCount==0)
					InByte=i;
				if(DBUF[i]==0xE5)				
					DirCount++;				
				else if(DBUF[i]==0x00)
					{	
					DirCount++;	
					DBUF[i]=0xE5;
					bwrite=1;
					}
				else
					DirCount=0;

				if((DirCount*32)>=(len+32))
					{
					for(j=0;j<len;j++)
						DBUF[InByte+j]=*(pName+j);
					for(j=0;j<32;j++)
						DBUF[InByte+len+j]=*(pBuffer+j);
					if(!SdWriteSector(NowSector+sector,1,DBUF))
		  		 		return FALSE;		  	 		
					bstop=1;
					break;
					}
				 }
				}
				if(bstop==1)break;
				
				if((len!=0)&&(bwrite==1))
				{
				if(!SdWriteSector(NowSector+sector,1,DBUF))
		  			return FALSE;
	    		}
	    	}
			if(bstop==1)break;
	
			NowCluster=GetNextClusterNum(NowCluster);
			if(NowCluster>0xffef)
	    	{
			NowCluster=CreateClusterLink(ClusterPointer);
		 	if(NowCluster==0x00)
		 		 return FALSE;
			NowSector=FirstSectorofCluster(NowCluster);
			for(i=0;i<DeviceInfo.BPB_BytesPerSec;i++) DBUF[i]=0x00;
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
				{
				if(!SdWriteSector(NowSector+sector,1,DBUF))
		  	 		return FALSE;
				}
			}
		}while(NowCluster<=0xffef);
	
	
	if(NowCluster>0xffef)
	    return FALSE;
	}
////////////////////////////////////////////////////////////////
	
	ThisFile.StartCluster=cnum;
	ThisFile.LengthInByte=0;
	ThisFile.ClusterPointer=ThisFile.StartCluster;
	ThisFile.SectorPointer=FirstSectorofCluster(ThisFile.StartCluster);
	ThisFile.OffsetofSector=0;
	ThisFile.SectorofCluster=0;
	ThisFile.bFileOpen=1;
	ThisFile.pointer=0;
	ThisFile.FatSectorPointer=0;
	
	return TRUE;
}

unsigned char WriteFile(unsigned long writeLength,unsigned char *pBuffer)
{
	unsigned int  len,sector,i,cnum,tlen;
	unsigned char bSuccess,bStop;
	
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;		
	if(!ThisFile.bFileOpen)
		return FALSE;
	ThisFile.bFileOpen=0;
	bSuccess=1;
	bStop=0;
	tlen=0;

	while(writeLength>0)
	{
		if(writeLength+ThisFile.OffsetofSector>DeviceInfo.BPB_BytesPerSec)
		   	len=DeviceInfo.BPB_BytesPerSec;
		else
		   	len=writeLength+ThisFile.OffsetofSector;
		   
		 //////////////////////////////////////////////////////
		 if(ThisFile.OffsetofSector>0)
		 	{
		 	if(SdReadSector(ThisFile.SectorPointer,1,DBUF))
		   		{
		   		
		   		len=len-ThisFile.OffsetofSector;
		   		for(i=0;i<len;i++)
		   			
		   			DBUF[ThisFile.OffsetofSector+i]=*(pBuffer+i);
		   		if(!SdWriteSector(ThisFile.SectorPointer,1,DBUF))
		   			return FALSE;			   			
		   		ThisFile.OffsetofSector=ThisFile.OffsetofSector+len;
		   		}
		   	else
		   		return FALSE;		   		
		 	}
		 else
		 	{
		 	if(!SdWriteSector(ThisFile.SectorPointer,1,pBuffer+tlen))
		   		return FALSE;		   		
		   	ThisFile.OffsetofSector=len;
		 	}
		 /////////////////////////////////////////////////////
		   writeLength-=len;
		   tlen+=len;
		 /////////////更新文件指针 //////////////////////////////
		  if(ThisFile.OffsetofSector>DeviceInfo.BPB_BytesPerSec-1)
		   {	
		   	ThisFile.OffsetofSector-=DeviceInfo.BPB_BytesPerSec;
		   	ThisFile.SectorofCluster+=1;
		   	if(ThisFile.SectorofCluster>DeviceInfo.BPB_SecPerClus-1)
		   	{
		   		ThisFile.SectorofCluster=0;
		 		 ThisFile.ClusterPointer=CreateClusterLink(ThisFile.ClusterPointer);
		 		 if(ThisFile.ClusterPointer==0x00)
		 		 	return FALSE;		 		
		 		 ThisFile.SectorPointer=FirstSectorofCluster(ThisFile.ClusterPointer); 	
		   	}
		   	else
		   		ThisFile.SectorPointer=ThisFile.SectorPointer+1;
		    }
		
	
	}//end while
	ThisFile.pointer+=tlen;
    DelayMs(200);
	///////////更新文件目录信息/////////////////////////////
	if(bSuccess==1)
	{
		if(DirStartCluster==0)	
		{
		for(sector=0;sector<DeviceInfo.BPB_RootEntCnt;sector++)
	    	{   
		//////////////////////////////////////////////////
		if(!SdReadSector(DeviceInfo.RootStartSector+sector,1,DBUF))
			return FALSE;				
		///////////////////////////////////////////////////
		for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
			{
			cnum=LSwapINT16(DBUF[i+26],DBUF[i+27]);
			if((cnum==ThisFile.StartCluster)&&(DBUF[i]!=0xe5))
				{
				if(ThisFile.pointer>ThisFile.LengthInByte)
					ThisFile.LengthInByte=ThisFile.pointer;				
				DBUF[i+28]=(unsigned char)(ThisFile.LengthInByte&0xff);
				DBUF[i+29]=(unsigned char)((ThisFile.LengthInByte>>8)&0xff);
				DBUF[i+30]=(unsigned char)((ThisFile.LengthInByte>>16)&0xff);
				DBUF[i+31]=(unsigned char)((ThisFile.LengthInByte>>24)&0xff);
				if(!SdWriteSector(DeviceInfo.RootStartSector+sector,1,DBUF))
		   			return FALSE;		   	
				 bStop=1;
				 break;
				}
			}
		if(bStop==1)
			break;		
	       }
		}
//////////////////////////////////////////////////////////////////////////////
		else
		{
			NowCluster=DirStartCluster;		
			do
			{
				NowSector=FirstSectorofCluster(NowCluster);
				for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
	   		 	{   
					if(!SdReadSector(NowSector+sector,1,DBUF))
						return FALSE;				
					for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
					{
						cnum=LSwapINT16(DBUF[i+26],DBUF[i+27]);
						if((cnum==ThisFile.StartCluster)&&(DBUF[i]!=0xe5))
							{
							if(ThisFile.pointer>ThisFile.LengthInByte)
								ThisFile.LengthInByte=ThisFile.pointer;				
							DBUF[i+28]=(unsigned char)(ThisFile.LengthInByte&0xff);
							DBUF[i+29]=(unsigned char)((ThisFile.LengthInByte>>8)&0xff);
							DBUF[i+30]=(unsigned char)((ThisFile.LengthInByte>>16)&0xff);
							DBUF[i+31]=(unsigned char)((ThisFile.LengthInByte>>24)&0xff);
							if(!SdWriteSector(NowSector+sector,1,DBUF))
		   						return FALSE;		   	
							 bStop=1;
							 break;
							}							
	    			}
					if(bStop==1)break;
				}
				if(bStop==1)break;
				NowCluster=GetNextClusterNum(NowCluster);			
			}while(NowCluster<=0xffef);
		
		if(NowCluster>0xffef)
	    	return FALSE;
		}
	}
	
	ThisFile.bFileOpen=1;
	//////////////////////////////////////////////
	return TRUE;
}

unsigned char RemoveFile(unsigned char *pBuffer)
{
	unsigned int sector,i;
	unsigned char bStop = 0,j = 0;
	int k;
		
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;		
	if(DirStartCluster==0)	
	{
	////////////// 清除目录/////////////////////////////////////
	for(sector=0;sector<DeviceInfo.BPB_RootEntCnt;sector++)
	    	{   
		//////////////////////////////////////////////////
		if(!SdReadSector(DeviceInfo.RootStartSector+sector,1,DBUF))
			return FALSE;			
		///////////////////////////////////////////////////
		for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
			{
			if(DBUF[i]==0x00)
				return FALSE;			
			///////////////////////////////////////////
			j=0;
			while(DBUF[i+j]==*(pBuffer+j))
				{
				 j=j+1;
				 if(j>10) break;
				 }
			
			if(j>10)
			 	{	
			 	DBUF[i]=0xE5;
			 	ThisFile.StartCluster=LSwapINT16(DBUF[i+26],DBUF[i+27]);
			
				for(k=(i-32);k>=0;k=k-32)
					{
					if(DBUF[k+11]==0x0F)
						DBUF[k]=0xE5;
					else
						break;
					}
				DelayMs(15);
				if(!SdWriteSector(DeviceInfo.RootStartSector+sector,1,DBUF))
					return FALSE;
/*
			 	k=sector-1;
				if(k>=0)
					{
					if(!SdReadSector(DeviceInfo.RootStartSector+k,1,DBUF))
						return FALSE;	
					for(k=DeviceInfo.BPB_BytesPerSec;k>=0;k=k-32)
						{
						if(DBUF[k+11]==0x0F)
							DBUF[k]=0xE5;
						else
							break;
						}
				//	DelayMs(15);
			 		if(!SdWriteSector(DeviceInfo.RootStartSector+sector-1,1,DBUF))
						return FALSE;
					}
*/			
				//////////////////// 清除FAT中的纪录////////////////////////
				DelayMs(10);
				if(!DeleteClusterLink(ThisFile.StartCluster))
					return FALSE;					
			 	bStop=1;
			 	break;
			 	}
			
			}//end for
		if(bStop==1)
			break;
		
	       }//end search
	if(sector>=DeviceInfo.BPB_RootEntCnt)
		return FALSE;	
	}
	else
	{
	NowCluster=DirStartCluster;		
		do
		{
			NowSector=FirstSectorofCluster(NowCluster);
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
	    	{   
				if(!SdReadSector(NowSector+sector,1,DBUF))
					return FALSE;				
				for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
				{
					if(DBUF[i]==0x00)
						return FALSE;
					j=0;
					while(DBUF[i+j]==*(pBuffer+j))
					{
						 j=j+1;
						 if(j>10)
						 	break;
					}
					if(j>10)
				    	{ 
						DBUF[i]=0xE5;
					 	ThisFile.StartCluster=LSwapINT16(DBUF[i+26],DBUF[i+27]);
						for(k=(i-32);k>=0;k=k-32)
						{
						if(DBUF[k+11]==0x0F)
							DBUF[k]=0xE5;
						else
							break;
						}
					 	DelayMs(15);
					 	if(!SdWriteSector(NowSector+sector,1,DBUF))
							return FALSE;					
				//////////////////// 清除FAT中的纪录////////////////////////
						DelayMs(10);
						if(!DeleteClusterLink(ThisFile.StartCluster))
							return FALSE;					
					 	bStop=1;
					 	break;
						}
				}
				if(bStop==1)break;		
	    	}
			if(bStop==1)break;	
			NowCluster=GetNextClusterNum(NowCluster);			
		}while(NowCluster<=0xffef);
		
		if(NowCluster>0xffef)
	    	return FALSE;
	}
	return TRUE;
}

unsigned char GetCapacity(void)
{
	unsigned int sectorNum,i;	
	unsigned long FreeSize,Freesectorcnt;

	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;
		
	////////////////////////////////////////////////////////////////////////
	sectorNum=DeviceInfo.FatStartSector;
	Freesectorcnt=0;
	while(sectorNum<DeviceInfo.BPB_FATSz16+DeviceInfo.FatStartSector)
	{
		
		if(SdReadSector(sectorNum,1,DBUF))
		{
		  for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+2)
		  	{		  	 
		  	 if((DBUF[i]==0x00)&&(DBUF[i+1]==0x00))
		  	 	{	
		  	 	Freesectorcnt++;
		  	 	}	  
		  	}	
		}
		else			
			return FALSE;			
		sectorNum++;
	}
	
	////////////////////////////////////////////////////////////////////////
	FreeSize=DeviceInfo.BPB_BytesPerSec*DeviceInfo.BPB_SecPerClus;
	FreeSize=Freesectorcnt*FreeSize;
	
	UARTBUF[0]=(unsigned char)((FreeSize>>24)&0xff);
	UARTBUF[1]=(unsigned char)((FreeSize>>16)&0xff);
	UARTBUF[2]=(unsigned char)((FreeSize>>8)&0xff);
	UARTBUF[3]=(unsigned char)(FreeSize&0xff);
	Response.len=4;
	return TRUE;
}

unsigned char CreateDir(unsigned long len,unsigned char *pBuffer,unsigned char *pName)
{
	unsigned int sector,i,j,DirCount;
	unsigned int cnum,ClusterPointer;
	unsigned char bstop = 0,InByte = 0,bwrite = 0;
	
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;
	if((len%32)!=0)
		return FALSE;
	if((len+32)>DeviceInfo.BPB_BytesPerSec)
		return FALSE;

	ThisFile.bFileOpen=0;
	ThisFile.FatSectorPointer=0;

	cnum=GetFreeCusterNum();
	if(cnum<0x02)
		return FALSE;	

	pBuffer[11]=0x10;
	pBuffer[26]=(unsigned char)(cnum);
	pBuffer[27]=(unsigned char)(cnum>>8);
	pBuffer[28]=0;pBuffer[29]=0;pBuffer[30]=0;pBuffer[31]=0;
	bstop=0;

	if(DirStartCluster==0)	
	{
	/////// Search a free space in the root dir space and build the item ///
	for(sector=0;sector<DeviceInfo.BPB_RootEntCnt;sector++)
	    {   
		if(!SdReadSector(DeviceInfo.RootStartSector+sector,1,DBUF))
			return FALSE;	
		DirCount=0;bwrite=0;
		for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
			{
			if(len==0)
				{
				if((DBUF[i]==0x00)||(DBUF[i]==0xE5))
				{
				for(j=0;j<32;j++)
					DBUF[i+j]=*(pBuffer+j);
				if(!SdWriteSector(DeviceInfo.RootStartSector+sector,1,DBUF))
		  	 		return FALSE;		  	 		
				bstop=1;
				break;
				}
				}
			else
			{
			if(DirCount==0)
				InByte=i;
			if(DBUF[i]==0xE5)				
				DirCount++;				
			else if(DBUF[i]==0x00)
				{	
				DirCount++;	
				DBUF[i]=0xE5;	
				bwrite=1;			
				}
			else
				DirCount=0;

			if((DirCount*32)>=(len+32))
				{
				for(j=0;j<len;j++)
					DBUF[InByte+j]=*(pName+j);

				for(j=0;j<32;j++)
					DBUF[InByte+len+j]=*(pBuffer+j);

				if(!SdWriteSector(DeviceInfo.RootStartSector+sector,1,DBUF))
		  	 		return FALSE;		  	 		
				bstop=1;
				break;
				}
			 }
			}		
		if(bstop==1)break;	

		if((len!=0)&&(bwrite==1))
			{
			if(!SdWriteSector(DeviceInfo.RootStartSector+sector,1,DBUF))
		  		return FALSE;
	    	}
	    }

	if(sector>=DeviceInfo.BPB_RootEntCnt)
		return FALSE;
	}
////////////////////////////////////////////////////////////
	else
	{
		NowCluster=DirStartCluster;		
		do
		{
			NowSector=FirstSectorofCluster(NowCluster);
			ClusterPointer=NowCluster;
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
	    	{   
				if(!SdReadSector(NowSector+sector,1,DBUF))
					return FALSE;
				DirCount=0;bwrite=0;
				for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
				{
				if(len==0)
					{
					if((DBUF[i]==0x00)||(DBUF[i]==0xE5))
					{
					for(j=0;j<32;j++)
						DBUF[i+j]=*(pBuffer+j);
					if(!SdWriteSector(NowSector+sector,1,DBUF))
		  	 			return FALSE;		  	 		
					bstop=1;
					break;
					}		
					}
				else
				{
				if(DirCount==0)
					InByte=i;
				if(DBUF[i]==0xE5)				
					DirCount++;				
				else if(DBUF[i]==0x00)
					{	
					DirCount++;	
					DBUF[i]=0xE5;
					bwrite=1;
					}
				else
					DirCount=0;

				if((DirCount*32)>=(len+32))
					{
					for(j=0;j<len;j++)
						DBUF[InByte+j]=*(pName+j);
					for(j=0;j<32;j++)
						DBUF[InByte+len+j]=*(pBuffer+j);
					if(!SdWriteSector(NowSector+sector,1,DBUF))
		  		 		return FALSE;		  	 		
					bstop=1;
					break;
					}
				 }			
				}
				if(bstop==1)break;
				if((len!=0)&&(bwrite==1))
				{
				if(!SdWriteSector(NowSector+sector,1,DBUF))
		  			return FALSE;
	    		}
	    	}
			if(bstop==1)break;
	
			NowCluster=GetNextClusterNum(NowCluster);
			if(NowCluster>0xffef)
	    	{
			NowCluster=CreateClusterLink(ClusterPointer);
		 	if(NowCluster==0x00)
		 		 return FALSE;
			NowSector=FirstSectorofCluster(NowCluster);
			for(i=0;i<DeviceInfo.BPB_BytesPerSec;i++) DBUF[i]=0x00;
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
				{
				if(!SdWriteSector(NowSector+sector,1,DBUF))
		  	 		return FALSE;
				}
			}
		}while(NowCluster<=0xffef);
	
	if(NowCluster>0xffef)
	    return FALSE;
	}
////////////////////////////////////////////////////////////////
	for(i=64;i<DeviceInfo.BPB_BytesPerSec;i++)	DBUF[i]=0x00;
	
	for(i=0;i<43;i++) DBUF[i]=0x20;
	
	DBUF[0]=0x2e;
	for(i=11;i<32;i++) DBUF[i]=pBuffer[i];

	DBUF[32]=0x2e;DBUF[33]=0x2e;
	for(i=43;i<64;i++) DBUF[i]=pBuffer[i-32];
	DBUF[58]=(unsigned char)(DirStartCluster);
	DBUF[59]=(unsigned char)(DirStartCluster>>8);

	NowSector=FirstSectorofCluster(cnum);
	if(!SdWriteSector(NowSector,1,DBUF))
		return FALSE;	

	DirStartCluster=cnum;
//	ThisFile.ClusterPointer=DirStartCluster;
	ThisFile.ClusterPointer=0;		
	return TRUE;	
}

unsigned char DownDir(unsigned char *pBuffer)
{
	unsigned int i = 0;
	unsigned char j,bstop,sector;	
		
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;	
	
	ThisFile.bFileOpen=0;
	bstop=0;

	if(DirStartCluster==0)	//Root Dir
	{
	for(sector=0;sector<DeviceInfo.BPB_RootEntCnt;sector++)
	    {   
		if(!SdReadSector(DeviceInfo.RootStartSector+sector,1,DBUF))
			return FALSE;
		for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
			{
			if(DBUF[i]==0x00)
				return FALSE;		
			j=0;
			while(DBUF[i+j]==*(pBuffer+j))
				{
				 j=j+1;
				 if(j>10)
				 	break;
				}
			
			if(j>10&&(DBUF[i+11]&0x10))
			    {			   
			    bstop=1;
			     break;}
			
			}
		if(bstop==1)break;		
	    }
	    
	    if(sector>=DeviceInfo.BPB_RootEntCnt)
	    	return FALSE;		
	    	
	DirStartCluster=LSwapINT16(DBUF[i+26],DBUF[i+27]);
//	ThisFile.ClusterPointer=DirStartCluster;
	ThisFile.ClusterPointer=0;
	return TRUE;
	}
	////////////////////////////////////////////
	else
	{
		NowCluster=DirStartCluster;		
		do
		{
			NowSector=FirstSectorofCluster(NowCluster);
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
	    	{   
				if(!SdReadSector(NowSector+sector,1,DBUF))
					return FALSE;				
				for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
				{
					if(DBUF[i]==0x00)
						return FALSE;
					j=0;
					while(DBUF[i+j]==*(pBuffer+j))
					{
						 j=j+1;
						 if(j>10)
						 	break;
					}
					if(j>10&&(DBUF[i+11]&0x10))
				    	{bstop=1;break;}
				}
				if(bstop==1)break;		
	    	}
			if(bstop==1)break;	
			NowCluster=GetNextClusterNum(NowCluster);			
		}while(NowCluster<=0xffef);
		
	if(NowCluster>0xffef)
	    	return FALSE;
		
	DirStartCluster=LSwapINT16(DBUF[i+26],DBUF[i+27]);
//	ThisFile.ClusterPointer=DirStartCluster;
	ThisFile.ClusterPointer=0;		
	return TRUE;		
	}
}

unsigned char UpDir()
{
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;	
	if(DirStartCluster==0)	//Root Dir
		return TRUE;	
	
	ThisFile.bFileOpen=0;

	NowSector=FirstSectorofCluster(DirStartCluster);
	if(!SdReadSector(NowSector,1,DBUF))
			return FALSE;
	if(DBUF[32]!=0x2e&&DBUF[33]!=0x2e)	//..
			return FALSE;
	
	DirStartCluster=LSwapINT16(DBUF[58],DBUF[59]);
//	ThisFile.ClusterPointer=DirStartCluster;
	ThisFile.ClusterPointer=0;		
	return TRUE;
}

unsigned char UpRootDir()
{
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;

	ThisFile.bFileOpen=0;
	DirStartCluster=0;	//Root Dir
			
	return TRUE;
}

