#include "../inc/common.h"
#include "../inc/fat.h"
#include "../inc/fat32.h"
#include "../inc/device.h"
#include "../inc/hal.h"
////////////////////////////////////////
extern SYS_INFO_BLOCK DeviceInfo;
extern FILE_INFO ThisFile;
extern unsigned char DBUF[BUFFER_LENGTH];
unsigned char FATBUF[512];
////////////////////////////////////////

unsigned long FirstSectorofCluster(unsigned int clusterNum)
{
	unsigned long temp;
	temp=clusterNum-2;
	temp=temp*DeviceInfo.BPB_SecPerClus;
	temp=temp+DeviceInfo.FirstDataSector;
	return temp;
}

unsigned int ThisFatSecNum(unsigned int clusterNum)
{

   unsigned int temp;
   temp=clusterNum/(DeviceInfo.BPB_BytesPerSec/2);
   temp=temp+DeviceInfo.FatStartSector;
   return temp;

}

unsigned int ThisFatEntOffset(unsigned int clusterNum)
{    
	return (clusterNum%(DeviceInfo.BPB_BytesPerSec/2))*2;
}

unsigned int GetNextClusterNum(unsigned int clusterNum)
{
	unsigned int FatSecNum,FatEntOffset;
	
	FatSecNum=ThisFatSecNum(clusterNum);
	FatEntOffset=ThisFatEntOffset(clusterNum);
	if(ThisFile.FatSectorPointer!=FatSecNum)
	{	
		
		if(!SdReadSector(FatSecNum,1,FATBUF))
			return 0xFFFF;
		ThisFile.FatSectorPointer=FatSecNum;
	}
	
	///////////////////////////////////////////////////
	clusterNum=FATBUF[FatEntOffset+1];
	clusterNum=clusterNum<<8;
	clusterNum+=FATBUF[FatEntOffset];	
	return clusterNum;
}

unsigned char GoToPointer(unsigned long pointer)
{
	
	unsigned int clusterSize;
	
	clusterSize=DeviceInfo.BPB_SecPerClus*DeviceInfo.BPB_BytesPerSec;
	ThisFile.ClusterPointer=ThisFile.StartCluster;
	while(pointer>clusterSize)
	{
		pointer-=clusterSize;	
		ThisFile.ClusterPointer=GetNextClusterNum(ThisFile.ClusterPointer);
		if(ThisFile.ClusterPointer==0xffff)
		{
		return FALSE;
		}
	}
	ThisFile.SectorofCluster=pointer/DeviceInfo.BPB_BytesPerSec;
	ThisFile.SectorPointer=FirstSectorofCluster(ThisFile.ClusterPointer)+ThisFile.SectorofCluster;
	ThisFile.OffsetofSector=pointer%DeviceInfo.BPB_BytesPerSec;
	ThisFile.FatSectorPointer=0;
	return TRUE;
	
}

unsigned char DeleteClusterLink(unsigned int clusterNum)
{
	unsigned int FatSecNum,FatEntOffset;
	unsigned char i;
	while((clusterNum>1)&&(clusterNum<0xfff0))
	{
	FatSecNum=ThisFatSecNum(clusterNum);
	FatEntOffset=ThisFatEntOffset(clusterNum);
	if(SdReadSector(FatSecNum,1,DBUF))
		{
		 if(clusterNum<DeviceInfo.LastFreeCluster) DeviceInfo.LastFreeCluster=clusterNum; 
		 clusterNum=DBUF[FatEntOffset+1];
		 clusterNum=clusterNum<<8;
		 clusterNum+=DBUF[FatEntOffset];		 
		}
	else
		return FALSE;
	DBUF[FatEntOffset]=0x00;
	DBUF[FatEntOffset+1]=0x00;	
	for(i=0;i<DeviceInfo.BPB_NumFATs;i++)
		{
		DelayMs(5);
		if(!SdWriteSector(FatSecNum+i*DeviceInfo.BPB_FATSz16,1,DBUF))
			return FALSE;
		}	
	}
	return TRUE;
}

unsigned int GetFreeCusterNum(void)
{
	unsigned int clusterNum,i;
	unsigned long sectorNum;
	unsigned char j;
	clusterNum=0;
//	sectorNum=DeviceInfo.FatStartSector;

    sectorNum=ThisFatSecNum(DeviceInfo.LastFreeCluster);
    clusterNum=(sectorNum-DeviceInfo.FatStartSector)*(DeviceInfo.BPB_BytesPerSec/2);

	while(sectorNum<DeviceInfo.BPB_FATSz16+DeviceInfo.FatStartSector)
	{
		
		if(!SdReadSector(sectorNum,1,DBUF))
			return 0x0;
		for(i=0;i<DeviceInfo.BPB_BytesPerSec;i=i+2)
		  	{
		  	 if((DBUF[i]==0)&&(DBUF[i+1]==0))
		  	 	{	
		  	 	DBUF[i]=0xff;
		  	 	DBUF[i+1]=0xff;
				for(j=0;j<DeviceInfo.BPB_NumFATs;j++)
					{
					DelayMs(5);
					if(!SdWriteSector(sectorNum+j*DeviceInfo.BPB_FATSz16,1,DBUF))
						return FALSE;
					}
                clusterNum=clusterNum+i/2;
		        if((clusterNum-2)<DeviceInfo.TotCluster) 
				  {
				   if(clusterNum>DeviceInfo.LastFreeCluster) DeviceInfo.LastFreeCluster=clusterNum;
				   return clusterNum;
				  }
		  	  	else return	FALSE; 
		  	 	}
		  	 
		  	}	
		clusterNum+=DeviceInfo.BPB_BytesPerSec/2;		
		sectorNum++;
		DelayMs(1);
	}
	
	return 0x0;
}

unsigned int CreateClusterLink(unsigned int currentCluster)
{
	unsigned int newCluster;
	unsigned int FatSecNum,FatEntOffset;
	unsigned char i;

	newCluster=GetFreeCusterNum();

	if(newCluster==0)
		return 0x00;
			
	FatSecNum=ThisFatSecNum(currentCluster);
	FatEntOffset=ThisFatEntOffset(currentCluster);
	if(SdReadSector(FatSecNum,1,DBUF))
		{
		DBUF[FatEntOffset]=newCluster;
		DBUF[FatEntOffset+1]=newCluster>>8;
		for(i=0;i<DeviceInfo.BPB_NumFATs;i++)
			{
			DelayMs(5);
			if(!SdWriteSector(FatSecNum+i*DeviceInfo.BPB_FATSz16,1,DBUF))
				return FALSE;
			}		
		}
	else
		return 0x00;
	
	return newCluster;
}
