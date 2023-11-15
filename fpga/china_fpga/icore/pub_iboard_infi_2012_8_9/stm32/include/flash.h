/*------------------------------------------------------
FILE NAME   : flash.h
DESCRIPTION : flash header.
VERSION     : 0.0.0 (C)aureole
AUTHOR      : Aureole
CREATE DATE : 10.27.2006
MODIFY DATE : 
LOGS        :-\

M25P16 Drivers.
--------------------------------------------------------*/
#ifndef __flash_h__
#define __flash_h__


#define READ_ID				0x9f							
#define EN_WRITE_FLASH		0x06
#define DIS_WRITE_FLASH		0x04
#define	ERASE				0xc7
#define	EN_WRITE_REGISTER	0x50
#define WRITE_REGISTER		0x01
#define READ_REGISTER		0x05
#define READ_FLASH			0x03

#define UNBUSY_FLAG			0x43

#define WRITE_FLASH			0X02

#define	SECTOR_ERASE		0XD8


#define	FLASH_SECTOR		65536

//-----------------Extern Define----------------------//



typedef struct{
	unsigned long int (* read_jedec_id)(void);
	unsigned char (* read)(unsigned long int /* address */);
	int (* read_32)(unsigned long int /* addr */, char * /* buf */);
 	int (* read_72)(unsigned long int /* addr */, char * /* buf */);
	int (* read_256)(unsigned long int /* addr */, char * /* buf */);
	
	int (* write)(unsigned long int /* address */, char /* dat */);
	int (* write_256)(unsigned long int /* address */, char * /* buf */);

	int (* chip_erase)(void);
	int (* lock)(void);
	int (* unlock)(void);
	int (* sector_erase)(int sector);
}SFLASH_T;



//-----------------Extern functions----------------------//	 

extern SFLASH_T flash;



#endif //__flash_h__

