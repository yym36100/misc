#ifndef SDCARD_H_
#define SDCARD_H_

#include "alt_types.h"

/********************�궨��***************************/
/************������*************/
#define CMD0    0   /*����λ*/
#define CMD1    1
#define CMD8    8   /*����8�� ��ѯ֧�ֵ�ѹ��Χ*/
#define CMD9    9   /*����9�� ��CSD����*/
#define CMD10   10  /*����10����CID����*/
#define CMD12   12  /*����12��ֹͣ���ݴ���*/
#define CMD16   16  /*����16������SectorSize,Ӧ����0x00*/
#define CMD17   17  /*����17, ��sector*/
#define CMD18   18  /*����18, ��Multi Sector*/
#define CMD23   23  /*����23, ���ö�sectorд��ǰԤ�Ȳ���N��block*/
#define CMD24   24  /*����24, дSector*/
#define CMD25   25  /*����25, дMulti sector*/
#define CMD41   41  /*����41, Ӧ����0x00*/
#define CMD55   55  /*����55, Ӧ����0x01*/
#define CMD58   58  /*����58, ��OCR��Ϣ*/
#define CMD59   59  /*����59, ʹ��/��ֹCRC, Ӧ����0x00*/

#define   u8          alt_u8
#define   u16        alt_u16
#define   u32        alt_u32
/**********SD�����Ͷ���**********/
#define SD_TYPE_ERR 0xff
#define SD_TYPE_MMC 0x01
#define SD_TYPE_V1  0x02
#define SD_TYPE_V2  0x04
#define SD_TYPE_V2HC    0x08



/********************��������*************************/
u8 sdcard_init(void);
u32 sdcard_sector_count(void);
u16 sdcard_read_sector(u8 *buff, u32 sector, u16 cnt);
u16 sdcard_write_sector(const u8 *buff, u32 sector, u8 cnt);

#endif /*SDCARD_H_*/
