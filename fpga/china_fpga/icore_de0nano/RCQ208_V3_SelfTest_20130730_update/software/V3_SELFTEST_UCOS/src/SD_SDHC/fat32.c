#include "../inc/common.h"
#include "../inc/fat.h"
#include "../inc/fat32.h"
#include "../inc/device.h"
#include "../inc/hal.h"
////////////////////////////////////////
extern SYS_INFO_BLOCK DeviceInfo;
extern FILE_INFO ThisFile;
extern unsigned char DBUF[BUFFER_LENGTH];
extern unsigned char FATBUF[512];
////////////////////////////////////////

unsigned long FirstSectorofCluster32(unsigned long clusterNum)
{
	unsigned long temp;
	temp=clusterNum-2;
	temp=temp*DeviceInfo.BPB_SecPerClus;
	temp=temp+DeviceInfo.FirstDataSector;
	return temp;
}

unsigned long ThisFatSecNum32(unsigned long clusterNum)
{
   unsigned long temp;
   temp=clusterNum/(DeviceInfo.BPB_BytesPerSec/4);
   temp=temp+DeviceInfo.FatStartSector;
   return temp;
}

unsigned long ThisFatEntOffset32(unsigned long clusterNum)
{
	return (clusterNum%(DeviceInfo.BPB_BytesPerSec/4))*4;
}

unsigned long GetNextClusterNum32(unsigned long clusterNum)
{
	unsigned long FatSecNum,FatEntOffset;
	
	FatSecNum=ThisFatSecNum32(clusterNum);
	FatEntOffset=ThisFatEntOffset32(clusterNum);
	if(ThisFile.FatSectorPointer!=FatSecNum)
	{	
		
		if(!SdReadSector(FatSecNum,1,FATBUF))
			return 0xFFFFFFFF;
		ThisFile.FatSectorPointer=FatSecNum;
	}
	
	///////////////////////////////////////////////////
	clusterNum=LSwapINT32(FATBUF[FatEntOffset],FATBUF[FatEntOffset+1],FATBUF[FatEntOffset+2],FATBUF[FatEntOffset+3]);
	return clusterNum;
}

unsigned char GoToPointer32(unsigned long pointer)
{
	
	unsigned int clusterSize;
	
	clusterSize=DeviceInfo.BPB_SecPerClus*DeviceInfo.BPB_BytesPerSec;
	ThisFile.ClusterPointer=ThisFile.StartCluster;
	while(pointer>clusterSize)
	{
		pointer-=clusterSize;	
		ThisFile.ClusterPointer=GetNextClusterNum32(ThisFile.ClusterPointer);
		if(ThisFile.ClusterPointer==0xffffffff)
		{
		return FALSE;
		}
	}
	ThisFile.SectorofCluster=pointer/DeviceInfo.BPB_BytesPerSec;
	ThisFile.SectorPointer=FirstSectorofCluster32(ThisFile.ClusterPointer)+ThisFile.SectorofCluster;
	ThisFile.OffsetofSector=pointer%DeviceInfo.BPB_BytesPerSec;
	ThisFile.FatSectorPointer=0;
	return TRUE;
	
}

unsigned char DeleteClusterLink32(unsigned long clusterNum)
{
	unsigned long FatSecNum,FatEntOffset;
	unsigned char i;
	while((clusterNum>1)&&(clusterNum<DeviceInfo.TotCluster))
	{
	FatSecNum=ThisFatSecNum32(clusterNum);
	FatEntOffset=ThisFatEntOffset32(clusterNum);
	if(SdReadSector(FatSecNum,1,DBUF))
       {
         if(clusterNum<DeviceInfo.LastFreeCluster) DeviceInfo.LastFreeCluster=clusterNum; 
		 clusterNum=LSwapINT32(DBUF[FatEntOffset],DBUF[FatEntOffset+1],DBUF[FatEntOffset+2],DBUF[FatEntOffset+3]);
       }
	else
		return FALSE;
	DBUF[FatEntOffset]=0x00;DBUF[FatEntOffset+1]=0x00;DBUF[FatEntOffset+2]=0x00;DBUF[FatEntOffset+3]=0x00;			
	for(i=0;i<DeviceInfo.BPB_NumFATs;i++)
		{
		DelayMs(5);
		if(!SdWriteSector(FatSecNum+i*DeviceInfo.BPB_FATSz32,1,DBUF))
			return FALSE;
		}	
	}
	return TRUE;
}

unsigned long GetFreeCusterNum32(void)
{
	unsigned long clusterNum,i;
	unsigned long sectorNum;
	unsigned char j;
	sectorNum=ThisFatSecNum32(DeviceInfo.LastFreeCluster);
    clusterNum=(sectorNum-DeviceInfo.FatStartSector)*(DeviceInfo.BPB_BytesPerSec/4);

	while(sectorNum<DeviceInfo.BPB_FATSz32+DeviceInfo.FatStartSector)
	{		
		if(!SdReadSector(sectorNum,1,DBUF))
			return 0x0;
		for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+4)
		  	{
		  	 if((DBUF[i]==0)&&(DBUF[i+1]==0)&&(DBUF[i+2]==0)&&(DBUF[i+3]==0))
		  	 	{	
		  	 	DBUF[i]=0xff;DBUF[i+1]=0xff;DBUF[i+2]=0xff;DBUF[i+3]=0xff;
				for(j=0;j<DeviceInfo.BPB_NumFATs;j++)
					{
					DelayMs(5);
					if(!SdWriteSector(sectorNum+j*DeviceInfo.BPB_FATSz32,1,DBUF))
						return FALSE;
					}	
                clusterNum=clusterNum+i/4;
		        if((clusterNum-2)<DeviceInfo.TotCluster) 
				  {
				   if(clusterNum>DeviceInfo.LastFreeCluster) DeviceInfo.LastFreeCluster=clusterNum;
				   return clusterNum;
				  }
		  	  	else return	FALSE; 
		  	 	}
		  	}	
		clusterNum+=DeviceInfo.BPB_BytesPerSec/4;		
		sectorNum++;
		DelayMs(1);
	}	
	return 0x0;
}

unsigned long CreateClusterLink32(unsigned long currentCluster)
{
	unsigned long newCluster;
	unsigned long FatSecNum,FatEntOffset;
	unsigned char i;

	newCluster=GetFreeCusterNum32();
		
	FatSecNum=ThisFatSecNum32(currentCluster);
	FatEntOffset=ThisFatEntOffset32(currentCluster);
	if(SdReadSector(FatSecNum,1,DBUF))
		{
		DBUF[FatEntOffset]=newCluster;
		DBUF[FatEntOffset+1]=newCluster>>8;
		DBUF[FatEntOffset+2]=newCluster>>16;
		DBUF[FatEntOffset+3]=newCluster>>24;
		for(i=0;i<DeviceInfo.BPB_NumFATs;i++)
			{
			DelayMs(5);
			if(!SdWriteSector(FatSecNum+i*DeviceInfo.BPB_FATSz32,1,DBUF))
				return FALSE;
			}		
		}
	else
		return 0x00;
	
	return newCluster;
}
