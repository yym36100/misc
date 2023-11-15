
#include <stdio.h>
#include "../inc/common.h"
#include "../inc/device.h"
#include "../inc/hpi.h"
#include "../inc/hal.h"
#include "../inc/fat.h"
#include "../inc/fat32.h"
#include "../inc/hpi32.h"

extern FLAGS bFlags;
extern unsigned char DBUF[BUFFER_LENGTH];
//////////////////////////////////////////
extern unsigned char UARTBUF[UARTBUF_LENGTH];
extern SYS_INFO_BLOCK DeviceInfo;
extern FILE_INFO ThisFile;

extern Command_Def Command;
extern Response_Def Response;

unsigned long DirStartCluster32,NowCluster32;
extern unsigned long NowSector;
extern ShowFileName_Def ShowFileName[MaxLFNum];	//long file struct
/////////////////////////////////////////////

unsigned char UartHandler32(void)
{
  Response.Result=0;Response.len=0;
  //printf(" Command.CLass = %02x\r\n",Command.CLass);
  switch(Command.CLass)
  {
    case 0x00:	//List	
    	printf(" List32\r\n"); 
    	Response.Result=List32();				
		printf(" Response.Result = %d -- line : %d\r\n",Response.Result,__LINE__);
    	break;  
  	case 0x01:	//Open File
    	printf(" OpenFile32\r\n");
 		Response.Result=OpenFile32(Command.Parameter);				
		printf(" Response.Result = %d -- line : %d\r\n",Response.Result,__LINE__);		
     	break;
	case 0x02:	//Read File	
    	//printf(" ReadFile32\r\n");	
		Response.Result=ReadFile32(Command.len,UARTBUF);				
		//printf(" Response.Result = %d -- line : %d\r\n",Response.Result,__LINE__);		
		break;   
    case 0x03:	//Set Pointer
    	printf(" SetFilePointer32\r\n");
		Response.Result=SetFilePointer32(Command.len);	
		break;
	case 0x04:	//Great File
    	printf(" OpenFile32\r\n");
		Response.Result=OpenFile32(Command.Parameter);
		if(Response.Result)
		{
			Response.Result=SetFilePointer32(ThisFile.LengthInByte);
		}
		else
    		Response.Result=CreateFile32(Command.len,Command.Parameter,UARTBUF);    	
    	break; 
	case 0x05:	//Write File
    	Response.Result=WriteFile32(Command.len,UARTBUF);
    	break; 
    case 0x06:	//Remove File
    	ThisFile.bFileOpen=0;	
    	Response.Result=RemoveFile32(Command.Parameter);
    	break; 	
	case 0x07:	//Get Space    	
    	Response.Result=GetCapacity32();
    	break;     
	case 0x08:  //DetectDisk
		if(bFlags.bits.SLAVE_IS_ATTACHED)
			Response.Result=1;
		break;
	case 0x09:  //Great Dir
		Response.Result=DownDir32(Command.Parameter);
		if(!Response.Result)
			Response.Result=CreateDir32(Command.len,Command.Parameter,UARTBUF);    	
    	break; 
	case 0x0a:	//Down Dir
		Response.Result=DownDir32(Command.Parameter);
		break;
	case 0x0b:	//Up Dir
		Response.Result=UpDir32();
		break;	
	case 0x0c:	//Up RootDir
		Response.Result=UpRootDir32();
		break;	
  }

  //UartSendRsp();
  ///////////////////////////////
  return TRUE;  
}

unsigned char List32(void)
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
//////////////////////////////////////////////////////////////////   			
	NowCluster32=DirStartCluster32;	

	do
	{
		NowSector = FirstSectorofCluster32(NowCluster32);
		printf(" NowSector : %d , Addr : %08x\r\n",NowSector, NowSector * 512);
		for(sector=0; sector<DeviceInfo.BPB_SecPerClus; sector++)
    	{   
			if(!SdReadSector(NowSector+sector, 1 ,DBUF))
				return FALSE;
			
			for(i=0; i<DeviceInfo.BPB_BytesPerSec; i=i+32)
			{
				if(DBUF[i] == 0x00)
				{
					bstop = 1;
					break;
				}
				else if(DBUF[i] == 0xE5)
					continue;			
				else
				{
					for(k=0;k<32;k++)
					{
						UARTBUF[item*32 + k] = DBUF[i+k];
					}
					
					item=item+1;
					
				if(item>=(UARTBUF_LENGTH/32))  
				{
					bstop=1;
					break;
				}  //串口缓冲 只能有512项目录，强行结束
				/////////////////////////////////
				if(Lcount < MaxLFNum)
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
						{
							ShowFileName[Lcount].item[k]=DBUF[i+k];
						}
			 		   Lcount++;							
					}	
			      }
			/////////////////////////////////
				}
			}
			if(bstop==1)break;		
    	}
		if(bstop==1)break;

		NowCluster32=GetNextClusterNum32(NowCluster32); 
		
	}while(NowCluster32<=DeviceInfo.TotCluster);

	Response.len = item * 32;

	#if 1
	printf(" file num = %d\r\n",item);

	printf("\r\n");

	for(i=0; i<item; i++)
	{
		for(k=0; k<11; k++)
		{
			printf("%c",UARTBUF[i*32 + k]);
		}
		printf("\r\n");	
	}
	printf("\r\n");	
	#endif
			
	return TRUE;	
}

/*
typedef struct file

void FilePaser32(unsigned char *buf)
{
	char file_name;
	char file_ext;
	unsigned char file_attrib;
	unsigned long file_StartClu;
	unsigned long file_length;
	
}*/

unsigned char OpenFile32(unsigned char *pBuffer)
{
	unsigned int i = 0;
	unsigned char j = 0,bstop = 0,sector = 0;
		
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;			
	ThisFile.bFileOpen=0;
	NowCluster32=DirStartCluster32;		
		do
		{
			NowSector=FirstSectorofCluster32(NowCluster32);
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
			NowCluster32=GetNextClusterNum32(NowCluster32);			
		}while(NowCluster32<=DeviceInfo.TotCluster);
		
	if(NowCluster32>DeviceInfo.TotCluster)
	   	return FALSE;

	ThisFile.bFileOpen=1;
	ThisFile.StartCluster=LSwapINT32(UARTBUF[26],UARTBUF[27],UARTBUF[20],UARTBUF[21]);
	ThisFile.LengthInByte=LSwapINT32(UARTBUF[28],UARTBUF[29],UARTBUF[30],UARTBUF[31]);
	ThisFile.ClusterPointer=ThisFile.StartCluster;	
	ThisFile.SectorPointer=FirstSectorofCluster32(ThisFile.StartCluster);
	ThisFile.OffsetofSector=0;
	ThisFile.SectorofCluster=0;	
	ThisFile.FatSectorPointer=0;	
	ThisFile.pointer=0;
	
	Response.len=32;
	return TRUE;	
}

unsigned char ReadFile32(unsigned long readLength,unsigned char *pBuffer)
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
		 		 ThisFile.ClusterPointer=GetNextClusterNum32(ThisFile.ClusterPointer);
		 		 if(ThisFile.ClusterPointer>DeviceInfo.TotCluster)
		 		 	   return FALSE;			 		 	
		 		 ThisFile.SectorPointer=FirstSectorofCluster32(ThisFile.ClusterPointer); 	
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

unsigned char SetFilePointer32(unsigned long pointer)
{
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;		
	if(!ThisFile.bFileOpen)
		return FALSE;		
	///////////////////////////////////////////////////////////
	ThisFile.pointer=pointer;
	if(ThisFile.pointer>ThisFile.LengthInByte)
		return FALSE;	

	if(!GoToPointer32(ThisFile.pointer))
	{
	ThisFile.bFileOpen=0;
	return FALSE;	
	}
	//////////////////////////////////////////////
	return TRUE;
}

unsigned char CreateFile32(unsigned long len,unsigned char *pBuffer,unsigned char *pName)
{
	unsigned int sector,i,j,DirCount;
	unsigned long cnum;
	unsigned char bstop = 0,InByte = 0,bwrite = 0;
	unsigned long ClusterPointer;
	
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;
	if((len%32)!=0)
		return FALSE;
	if((len+32)>DeviceInfo.BPB_BytesPerSec)
		return FALSE;

	ThisFile.bFileOpen=0;	

	cnum=GetFreeCusterNum32();
	if(cnum<0x02)
		return FALSE;	

	pBuffer[21]=(unsigned char)(cnum>>24);
	pBuffer[20]=(unsigned char)(cnum>>16);
	pBuffer[27]=(unsigned char)(cnum>>8);
	pBuffer[26]=(unsigned char)(cnum);

	pBuffer[28]=0;pBuffer[29]=0;pBuffer[30]=0;pBuffer[31]=0;
	bstop=0;

	NowCluster32=DirStartCluster32;		
		do
		{
			NowSector=FirstSectorofCluster32(NowCluster32);
			ClusterPointer=NowCluster32;
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
	
			NowCluster32=GetNextClusterNum32(NowCluster32);
			if(NowCluster32>DeviceInfo.TotCluster)
	    	{
			NowCluster32=CreateClusterLink32(ClusterPointer);
		 	if(NowCluster32==0x00)
		 		 return FALSE;
			NowSector=FirstSectorofCluster32(NowCluster32);
			for(i=0;i<DeviceInfo.BPB_BytesPerSec;i++) DBUF[i]=0x00;
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
				{
				if(!SdWriteSector(NowSector+sector,1,DBUF))
		  	 		return FALSE;
				}
			}
		}while(NowCluster32<=DeviceInfo.TotCluster);	
////////////////////////////////////////////////////////////////
	
	ThisFile.StartCluster=cnum;
	ThisFile.LengthInByte=0;
	ThisFile.ClusterPointer=ThisFile.StartCluster;
	ThisFile.SectorPointer=FirstSectorofCluster32(ThisFile.StartCluster);
	ThisFile.OffsetofSector=0;
	ThisFile.SectorofCluster=0;
	ThisFile.bFileOpen=1;
	ThisFile.pointer=0;
	ThisFile.FatSectorPointer=0;
	
	return TRUE;
}


unsigned char WriteFile32(unsigned long writeLength,unsigned char *pBuffer)
{
    unsigned long cnum;
	unsigned int  len,sector,i,tlen;
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
		 		 ThisFile.ClusterPointer=CreateClusterLink32(ThisFile.ClusterPointer);
		 		 if(ThisFile.ClusterPointer==0x00)
		 		 	return FALSE;		 		
		 		 ThisFile.SectorPointer=FirstSectorofCluster32(ThisFile.ClusterPointer); 	
		   	}
		   	else
		   		ThisFile.SectorPointer=ThisFile.SectorPointer+1;
		    }
		
	
	}//end while
	ThisFile.pointer+=tlen;
	///////////更新文件目录信息/////////////////////////////
	if(bSuccess==1)
	{
		NowCluster32=DirStartCluster32;		
			do
			{
				NowSector=FirstSectorofCluster32(NowCluster32);
				for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
	   		 	{   
					if(!SdReadSector(NowSector+sector,1,DBUF))
						return FALSE;				
					for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+32)
					{
						cnum=LSwapINT32(DBUF[i+26],DBUF[i+27],DBUF[i+20],DBUF[i+21]);
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
				NowCluster32=GetNextClusterNum32(NowCluster32);			
			}while(NowCluster32<=DeviceInfo.TotCluster);
		
		if(NowCluster32>DeviceInfo.TotCluster)
	    	return FALSE;		
	}
	
	ThisFile.bFileOpen=1;
	//////////////////////////////////////////////
	return TRUE;
}


unsigned char RemoveFile32(unsigned char *pBuffer)
{
	unsigned int sector,i;
	unsigned char bStop = 0,j = 0;
	int k;
		
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;
////////////// 清除目录/////////////////////////////////////		
	NowCluster32=DirStartCluster32;		
		do
		{
			NowSector=FirstSectorofCluster32(NowCluster32);
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
						ThisFile.StartCluster=LSwapINT32(DBUF[i+26],DBUF[i+27],DBUF[i+20],DBUF[i+21]);
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
						if(!DeleteClusterLink32(ThisFile.StartCluster))
							return FALSE;					
					 	bStop=1;
					 	break;
						}
				}
				if(bStop==1)break;		
	    	}
			if(bStop==1)break;	
			NowCluster32=GetNextClusterNum32(NowCluster32);			
		}while(NowCluster32<=DeviceInfo.TotCluster);	
	
	if(NowCluster32>DeviceInfo.TotCluster)
	    return FALSE;
	
	return TRUE;
}


unsigned char GetCapacity32(void)
{
	unsigned int sectorNum,i;	
	unsigned long FreeSize,Freesectorcnt;

	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;
		
	////////////////////////////////////////////////////////////////////////
	sectorNum=DeviceInfo.FatStartSector;
	Freesectorcnt=0;
	while(sectorNum<DeviceInfo.BPB_FATSz32+DeviceInfo.FatStartSector)
	{
		
		if(SdReadSector(sectorNum,1,DBUF))
		{
		  for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+4)
		  	{		  	 
		  	 if((DBUF[i]||DBUF[i+1]||DBUF[i+2]||DBUF[i+3])==0x00)
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


unsigned char CreateDir32(unsigned long len,unsigned char *pBuffer,unsigned char *pName)
{
	unsigned int sector,i,j,DirCount;
	unsigned long cnum;
	unsigned char bstop = 0,InByte = 0,bwrite = 0;
	unsigned long ClusterPointer;
	
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;
	if((len%32)!=0)
		return FALSE;
	if((len+32)>DeviceInfo.BPB_BytesPerSec)
		return FALSE;

	ThisFile.bFileOpen=0;
	ThisFile.FatSectorPointer=0;

	cnum=GetFreeCusterNum32();
	if(cnum<0x02)
		return FALSE;	
	
	pBuffer[11]=0x10;
	pBuffer[21]=(unsigned char)(cnum>>24);
	pBuffer[20]=(unsigned char)(cnum>>16);
	pBuffer[27]=(unsigned char)(cnum>>8);
	pBuffer[26]=(unsigned char)(cnum);
	pBuffer[28]=0;pBuffer[29]=0;pBuffer[30]=0;pBuffer[31]=0;
	bstop=0;

	NowCluster32=DirStartCluster32;		
		do
		{
			NowSector=FirstSectorofCluster32(NowCluster32);
			ClusterPointer=NowCluster32;
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
	
			NowCluster32=GetNextClusterNum32(NowCluster32);
			if(NowCluster32>DeviceInfo.TotCluster)
	    	{
			NowCluster32=CreateClusterLink32(ClusterPointer);
		 	if(NowCluster32==0x00)
		 		 return FALSE;
			NowSector=FirstSectorofCluster32(NowCluster32);
			for(i=0;i<DeviceInfo.BPB_BytesPerSec;i++) DBUF[i]=0x00;
			for(sector=0;sector<DeviceInfo.BPB_SecPerClus;sector++)
				{
				if(!SdWriteSector(NowSector+sector,1,DBUF))
		  	 		return FALSE;
				}
			}
		}while(NowCluster32<=DeviceInfo.TotCluster);
	
	if(NowCluster32>DeviceInfo.TotCluster)
	    return FALSE;
////////////////////////////////////////////////////////////////
	for(i=64;i<DeviceInfo.BPB_BytesPerSec;i++)	DBUF[i]=0x00;
	
	for(i=0;i<43;i++) DBUF[i]=0x20;
	
	DBUF[0]=0x2e;
	for(i=11;i<32;i++) DBUF[i]=pBuffer[i];

	DBUF[32]=0x2e;DBUF[33]=0x2e;
	for(i=43;i<64;i++) DBUF[i]=pBuffer[i-32];

	if(DirStartCluster32==DeviceInfo.RootStartCluster)	//Root Dir
		{
		DBUF[53]=0;DBUF[52]=0;DBUF[59]=0;DBUF[58]=0;
		}
	else
		{
		DBUF[53]=(unsigned char)(DirStartCluster32>>24);
		DBUF[52]=(unsigned char)(DirStartCluster32>>16);
		DBUF[59]=(unsigned char)(DirStartCluster32>>8);
		DBUF[58]=(unsigned char)(DirStartCluster32);
		}

	NowSector=FirstSectorofCluster32(cnum);
	if(!SdWriteSector(NowSector,1,DBUF))
		return FALSE;	

	DirStartCluster32=cnum;
//	ThisFile.ClusterPointer=DirStartCluster32;
	ThisFile.ClusterPointer=0;		
	return TRUE;	
}

unsigned char DownDir32(unsigned char *pBuffer)
{
	unsigned int i = 0;
	unsigned char j = 0,bstop = 0,sector = 0;	
		
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;	
	
	ThisFile.bFileOpen=0;
	bstop=0;

	NowCluster32=DirStartCluster32;		
		do
		{
			NowSector=FirstSectorofCluster32(NowCluster32);
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
			NowCluster32=GetNextClusterNum32(NowCluster32);			
		}while(NowCluster32<=DeviceInfo.TotCluster);
		
	if(NowCluster32>DeviceInfo.TotCluster)
	   	return FALSE;

	DirStartCluster32=LSwapINT32(DBUF[i+26],DBUF[i+27],DBUF[i+20],DBUF[i+21]);	
//	ThisFile.ClusterPointer=DirStartCluster32;
	ThisFile.ClusterPointer=0;		
	return TRUE;
}

unsigned char UpDir32()
{
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;	
	if(DirStartCluster32==DeviceInfo.RootStartCluster)	//Root Dir
		return TRUE;	
	
	ThisFile.bFileOpen=0;

	NowSector=FirstSectorofCluster32(DirStartCluster32);
	if(!SdReadSector(NowSector,1,DBUF))
			return FALSE;
	if(DBUF[32]!=0x2e&&DBUF[33]!=0x2e)	//..
			return FALSE;

	DirStartCluster32=LSwapINT32(DBUF[58],DBUF[59],DBUF[52],DBUF[53]);
	if(DirStartCluster32==0)	//Root Dir
		DirStartCluster32=DeviceInfo.RootStartCluster;	
//	ThisFile.ClusterPointer=DirStartCluster32;
	ThisFile.ClusterPointer=0;		
	return TRUE;
}

unsigned char UpRootDir32()
{
	if(!bFlags.bits.SLAVE_IS_ATTACHED)
		return FALSE;

	ThisFile.bFileOpen=0;
	DirStartCluster32=DeviceInfo.RootStartCluster;	//Root Dir
			
	return TRUE;
}

