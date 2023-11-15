
#include <stdio.h>
#include "alt_types.h"
#include "../inc/common.h"
#include "../inc/device.h"
#include "../inc/hal.h"
#include "../inc/hpi.h"
#include "../inc/hpi32.h"



unsigned char DBUF[BUFFER_LENGTH];
	
///////////////////////////////////////////////////////////////////////////
unsigned char InitFileSystem(void)
{
//	unsigned int i;
	unsigned int ReservedSectorsNum;
	unsigned long size;
	////////////////////////////////////////////////////
	DeviceInfo.BPB_BytesPerSec=512; //暂假设为512
	
	if(!SdReadSector(0x0,1,DBUF))
	{
		printf("<xsyan> Read sector fail: __%d__(%s:%s)\r\n",__LINE__,__FILE__,__FUNCTION__);
		return FALSE;
	}
	
    if(DBUF[510] != 0x55 || DBUF[511] != 0xaa) 
    {
		printf("not match 0x55 & 0xaa ,line:%d\r\n",__LINE__);	
		return FALSE;
    }

#if 0
	printf(" read 1\n");	
	for(i=0; i<512; i++)
	{
		if(i % 16 == 0)
		{
			printf("\n [%03d] -- ",i);
		}
		printf("%02x ",DBUF[i]);		
	}
	printf("\n");

//	printf("DBUF[0] = %02x,DBUF[446] = %02x\n",DBUF[0],DBUF[446]);
#endif	
	//////////////////////////////////
	if(DBUF[0] == 0xeb || DBUF[0] == 0xe9)
	{
		DeviceInfo.StartSector=0;
	}
	else
	{
		 if(DBUF[446] != 0x80 && DBUF[446] != 0)
		 {
			printf(" DBUF[446] not match 0x80 & 0x00 ,line:%d\r\n",__LINE__);	
		 	return FALSE;
		 }
		 DeviceInfo.StartSector = LSwapINT32(DBUF[454],DBUF[455],DBUF[456],DBUF[457]);
	}

	size = LSwapINT32(DBUF[458],DBUF[459],DBUF[460],DBUF[461]);

	size *= 512;

	size /= (1024*1024);

	printf(" SD Card Size : %d MB\n",size);	
	
	///////////////////////////////////////////////////////
	if(!SdReadSector(DeviceInfo.StartSector,1,DBUF))
	{
		printf(" Read StartSector %d ,failure\r\n",DeviceInfo.StartSector);
		return FALSE;
	}

	printf(" Read StartSector = %d, success\r\n",DeviceInfo.StartSector);
		
#if 0
	printf(" read 2\n");	
	for(i=0; i<512; i++)
	{
		if(i % 16 == 0)
		{
			printf("\n [%03d] -- ",i);
		}
		printf("%02x ",DBUF[i]);		
	}
	printf("\n");

#endif	

	if(DBUF[510] != 0x55 || DBUF[511] != 0xaa) 
	{
		printf(" not match 0x55 & 0xaa ,line:%d\r\n",__LINE__);		
		return FALSE;
	}

	DeviceInfo.BPB_BytesPerSec = LSwapINT16(DBUF[11],DBUF[12]);
	printf(" BPB_BytesPerSec : %d\r\n",DeviceInfo.BPB_BytesPerSec);
	
	DeviceInfo.BPB_SecPerClus = DBUF[13];
	printf(" BPB_SecPerClus : %d\r\n",DeviceInfo.BPB_SecPerClus);
	
	ReservedSectorsNum = LSwapINT16(DBUF[14],DBUF[15]);
	printf(" ReservedSectorsNum : %d\r\n",ReservedSectorsNum);
	
	DeviceInfo.BPB_NumFATs = DBUF[16];
	printf(" BPB_NumFATs : %d\r\n",DeviceInfo.BPB_NumFATs);

	if(DBUF[82]=='F'&&DBUF[83]=='A'&&DBUF[84]=='T'&&DBUF[85]=='3'&&DBUF[86]=='2')
	{		
		DeviceInfo.BPB_RootEntCnt   = LSwapINT16(DBUF[17],DBUF[18]);
		DeviceInfo.BPB_RootEntCnt   = (DeviceInfo.BPB_RootEntCnt)*32/DeviceInfo.BPB_BytesPerSec;
		DeviceInfo.BPB_TotSec32     = LSwapINT32(DBUF[32],DBUF[33],DBUF[34],DBUF[35]);
		printf(" BPB_TotSec32 : %d\r\n",DeviceInfo.BPB_TotSec32);
		
		DeviceInfo.BPB_FATSz32      = LSwapINT32(DBUF[36],DBUF[37],DBUF[38],DBUF[39]);
		printf(" BPB_FATSz32 : %d\r\n",DeviceInfo.BPB_FATSz32);
		
		DeviceInfo.RootStartCluster = LSwapINT32(DBUF[44],DBUF[45],DBUF[46],DBUF[47]);
		printf(" RootStartCluster : %d\r\n",DeviceInfo.RootStartCluster);
		
		DeviceInfo.FatStartSector   = DeviceInfo.StartSector+ReservedSectorsNum;
		printf(" FatStartSector : %d\r\n",DeviceInfo.FatStartSector);
		
		DeviceInfo.FirstDataSector  = DeviceInfo.FatStartSector+DeviceInfo.BPB_NumFATs*DeviceInfo.BPB_FATSz32;
		printf(" FirstDataSector : %d\r\n",DeviceInfo.FirstDataSector);
		
		//DeviceInfo.TotCluster     = (DeviceInfo.BPB_TotSec32-DeviceInfo.FirstDataSector+1)/DeviceInfo.BPB_SecPerClus+1;
		DeviceInfo.TotCluster       = (DeviceInfo.BPB_TotSec32-ReservedSectorsNum-DeviceInfo.BPB_NumFATs*DeviceInfo.BPB_FATSz32-DeviceInfo.BPB_RootEntCnt)/DeviceInfo.BPB_SecPerClus;
		printf(" TotCluster : %d\r\n",DeviceInfo.TotCluster);

		DirStartCluster32           = DeviceInfo.RootStartCluster;
		DeviceInfo.FAT              = 1;	//FAT16=0,FAT32=1;
	}
	else
	{		
		DeviceInfo.BPB_RootEntCnt   = LSwapINT16(DBUF[17],DBUF[18]);
		DeviceInfo.BPB_RootEntCnt   = (DeviceInfo.BPB_RootEntCnt)*32/DeviceInfo.BPB_BytesPerSec;	
		DeviceInfo.BPB_TotSec16     = LSwapINT16(DBUF[19],DBUF[20]);	
		if(DeviceInfo.BPB_TotSec16 == 0)
		  DeviceInfo.BPB_TotSec16   = LSwapINT32(DBUF[32],DBUF[33],DBUF[34],DBUF[35]);
		DeviceInfo.BPB_FATSz16      = LSwapINT16(DBUF[22],DBUF[23]);			
		DeviceInfo.FatStartSector   = DeviceInfo.StartSector+ReservedSectorsNum;
		DeviceInfo.RootStartSector  = DeviceInfo.StartSector+DeviceInfo.BPB_NumFATs*DeviceInfo.BPB_FATSz16+ReservedSectorsNum;	
		DeviceInfo.FirstDataSector  = DeviceInfo.FatStartSector+DeviceInfo.BPB_NumFATs*DeviceInfo.BPB_FATSz16+DeviceInfo.BPB_RootEntCnt;
		DeviceInfo.TotCluster       = (DeviceInfo.BPB_TotSec16-DeviceInfo.BPB_RootEntCnt-DeviceInfo.BPB_NumFATs*DeviceInfo.BPB_FATSz16-1)/DeviceInfo.BPB_SecPerClus;
        if(DeviceInfo.TotCluster < 4085) 
        {
			printf(" FAT12 not support\r\n");
			return FALSE;	//FAT12 不被支持
        }
		DeviceInfo.FAT=0;
	}		
	///////////////////////////////////////////////////////
	ThisFile.bFileOpen=0;	
	///////////////////////////////////////////////////////
	return TRUE;
}

unsigned char SdReadSector(unsigned long sector,unsigned char len,unsigned char *pBuffer)
{
	u16 ret;
	ret = sdcard_read_sector(pBuffer, sector, len);
	if(ret == 0)
	 return 1;
	else
	 return 0;
#if 0
   //	printf("\r\nsector = %d\r\n",sector);
	while(len--)
	{
		if(SdReadBlock(pBuffer,sector << 9)==0) 
		{
			printf(" SdReadBlock fail\r\n");
			return 0;
		}
		pBuffer += 512;
	}
  return 1;
#endif  
}

unsigned char SdWriteSector(unsigned long sector,unsigned char len,unsigned char *pBuffer)
{
	u16 ret;
	ret = sdcard_write_sector(pBuffer, sector, len);

	if(ret == 0)
	 return 1;
	else
	 return 0;
#if 0	
	while(len--)
	 {
	  if(SdWriteBlock(pBuffer,sector << 9)==0) 
	  {
	  	return 0;
	  }
      pBuffer += 512;
	 }
 return 1;  
#endif 
}
