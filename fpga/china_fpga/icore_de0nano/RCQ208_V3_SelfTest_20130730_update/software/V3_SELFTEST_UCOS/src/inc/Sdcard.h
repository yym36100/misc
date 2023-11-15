#ifndef SDCARD_H_
#define SDCARD_H_

#include "alt_types.h"

/********************宏定义***************************/
/************卡命令*************/
#define CMD0    0   /*卡复位*/
#define CMD1    1
#define CMD8    8   /*命令8， 查询支持电压范围*/
#define CMD9    9   /*命令9， 读CSD数据*/
#define CMD10   10  /*命令10，读CID数据*/
#define CMD12   12  /*命令12，停止数据传输*/
#define CMD16   16  /*命令16，设置SectorSize,应返回0x00*/
#define CMD17   17  /*命令17, 读sector*/
#define CMD18   18  /*命令18, 读Multi Sector*/
#define CMD23   23  /*命令23, 设置多sector写入前预先擦除N个block*/
#define CMD24   24  /*命令24, 写Sector*/
#define CMD25   25  /*命令25, 写Multi sector*/
#define CMD41   41  /*命令41, 应返回0x00*/
#define CMD55   55  /*命令55, 应返回0x01*/
#define CMD58   58  /*命令58, 读OCR信息*/
#define CMD59   59  /*命令59, 使能/禁止CRC, 应返回0x00*/

#define   u8          alt_u8
#define   u16        alt_u16
#define   u32        alt_u32
/**********SD卡类型定义**********/
#define SD_TYPE_ERR 0xff
#define SD_TYPE_MMC 0x01
#define SD_TYPE_V1  0x02
#define SD_TYPE_V2  0x04
#define SD_TYPE_V2HC    0x08



/********************函数声明*************************/
u8 sdcard_init(void);
u32 sdcard_sector_count(void);
u16 sdcard_read_sector(u8 *buff, u32 sector, u16 cnt);
u16 sdcard_write_sector(const u8 *buff, u32 sector, u8 cnt);

#endif /*SDCARD_H_*/
