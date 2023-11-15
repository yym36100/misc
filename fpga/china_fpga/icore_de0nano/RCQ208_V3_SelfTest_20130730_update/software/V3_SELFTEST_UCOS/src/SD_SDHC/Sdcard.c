
#include "stdio.h"
#include "unistd.h"
#include "altera_avalon_pio_regs.h"

#include "../inc/sdcard_hw.h"
#include "../inc/sdcard.h"
#include "../inc/common.h"
#include "../inc/delay.h"
#include "../inc/hpi.h"
#include "../inc/device.h"

#define _DEBUG_ 1

/*用来记录SD卡的类型*/
static u8 sd_type = SD_TYPE_ERR;


FLAGS bFlags;
unsigned char DBUF[BUFFER_LENGTH];
unsigned char UARTBUF[UARTBUF_LENGTH];
Command_Def Command;
SYS_INFO_BLOCK DeviceInfo;   
FILE_INFO ThisFile;

extern char SD_info[];
void sd_main(void)
{
	u32 size = 0;
	int d1,d2;

    while(TRUE)
    {   
   		if(sdcard_init() == 0xfd)//SD 小容量
	   	{
			size = sdcard_sector_count();	
			size >>= 11;
			d1 = size >> 10;
			d2 = size%1000;
			printf(" d1 : %d ,d2 : %d\r\n",d1,d2);

			memset(SD_info,0x0,28);

			if(size < 1024)	
				sprintf(SD_info,"SD find ,Size : %d MB",size);	
			else
				sprintf(SD_info,"SD find ,Size : %d.%d GB",d1,d2);
	   	}
		else if(sdcard_init() == 0xfe)//SDHC 大容量
	   	{
			size = sdcard_sector_count();	
			size >>= 11;
			d1 = size >> 10;
			d2 = size%1000;
			printf(" d1 : %d ,d2 : %d\r\n",d1,d2);

			memset(SD_info,0x0,28);

			if(size < 1024)	
				sprintf(SD_info,"SDHC find ,Size : %d MB",size);	
			else
				sprintf(SD_info,"SDHC find ,Size : %d.%d GB",d1,d2);
	   	}
		else{
			printf(" SdInit failure\r\n");
			memset(SD_info,0x0,28);
			sprintf(SD_info,"No SD Card connect");	
		}
		OSTimeDlyHMSM(0, 0, 1, 0);	
    }  
}

/*功能:发送命令
 *参数:   
 *  cmd --> 命令代码
 *  arg --> 参数
 *  crc --> 命令和参数的crc编码
 *返回值:命令返回值
 */
static u8 send_cmd(u8 cmd, u32 arg, u8 crc)
{
	u8 i = 0;
	u8 r1 = 0;
	
	if (sdcard_assert())
		return 0xff;	/*片选失败*/
	sdcard_write(cmd | 0x40);
	sdcard_write(((u8 *)&arg)[3]);
	sdcard_write(((u8 *)&arg)[2]);
	sdcard_write(((u8 *)&arg)[1]);
	sdcard_write(((u8 *)&arg)[0]);
	sdcard_write(crc);
	if (cmd == CMD12)
		sdcard_read();
	i = 0x1f;
	do {
		r1 = sdcard_read();
	} while ((r1 & 0x80) && i--);
	sdcard_deassert();
	return r1;
}
/*功能:发送命令,但依然保持片选状态
 *参数:   
 *  cmd --> 命令代码
 *  arg --> 参数
 *  crc --> 命令和参数的crc编码
 *返回值:命令返回值
 */
static u8 send_cmd_assert(u8 cmd, u32 arg, u8 crc)
{
	u8 i = 0;
	u8 r1 = 0;
	
	if (sdcard_assert())
		return 0xff;	/*片选失败*/
	
	sdcard_write(cmd | 0x40);
	sdcard_write(((u8 *)&arg)[3]);
	sdcard_write(((u8 *)&arg)[2]);
	sdcard_write(((u8 *)&arg)[1]);
	sdcard_write(((u8 *)&arg)[0]);
	sdcard_write(crc);
	if (cmd == CMD12)
		sdcard_read();
	i = 0x1f;
	do {
		r1 = sdcard_read();
	} while ((r1 & 0x80) && i--);
	return r1;
}
/*功能:初始化sdcard
 *参数:   无
 *返回值:
 *  0 --> 成功
 *  其他值 --> 失败
 */

//===============================================
//Description : the main function :
//	send 74 clk 
//	judge SD is V2.0 prototype or not
//	judge the range of SD is 2.7~3.3v or not
//	judge the type of SD is HCSD or not
//===============================================

u8 sdcard_init()
{
    u32 i = 0;
    u32 r1 = 0;
    u8 buff[4];
    sdcard_io_init();
    #if _DEBUG_
    printf("sdcard_init\r\n");
    #endif
    /*上电延时*/
    for (i = 0; i < 10; i++)    /*循环大于74个脉冲*/
        sdcard_write(0xff);
    
    /*发送CMD0使卡进入Idle状态*/
    for (i = 0; i < 20; i++) {
        r1 = send_cmd(CMD0, 0, 0x95);   /*进行IDLE状态*/
        if (r1 == 0x01) /*如果进入空闲状态*/
            break;  
        #if _DEBUG_
        //printf("r1:%#x\r\n", r1);
        #endif
    }
    if (r1 == 0x01) {   /*进入空闲成功*/
        #if _DEBUG_
        printf("SD卡进入空闲状态\r\n");
        #endif
        if (send_cmd_assert(CMD8, 0x1aa, 0x87) == 1) {  /*SD V2.0协议*/
        
            #if _DEBUG_
            printf("SD V2.0协议\r\n");
            #endif
            for (i = 0; i < 4; i++) {
                buff[i] = sdcard_read();
                #if _DEBUG_
                printf("the buffer[%d] is : %02x\r\n",i,buff[i]);
                #endif
            }
            /*取消片选SD卡*/
            sdcard_deassert();/*end of send_cmd_assert(CMD8, 0x1aa, 0x87)*/
            if (buff[2] == 1 && buff[3] == 0xaa) {  /*卡支持2.7~3.6V电压*/
                   
            i = 0xfff;
            do {
                send_cmd(CMD55, 0, 0x0);    /*指示下一条为App类CMD*/
                r1 = send_cmd(CMD41,1 << 30 /*HCS位,参看《SD卡协议物理层》P107*/, 0x00);  /*告知SD卡,主机支持大容量否则插入大容量卡会出错*/
				usleep(10000);
			} while (r1 && i--);
             #if _DEBUG_
             printf("ACMD41返回值:%#x\r\n", r1);
             #endif
			 if (!r1 && !send_cmd_assert(CMD58, 0, 0)) {	/*ACMD41返回0代表初始化成功,并成功读取OCR*/
             #if _DEBUG_
             printf("激活SD卡初始完成\r\n");
             #endif
                    /*读OCR的值*/
                    for (i = 0; i < 4; i++) 
                        buff[i] = sdcard_read();
                    sdcard_deassert();/*send_cmd_assert(CMD58, 0, 0)*/
                    
                    /*判断卡的类型*/
                    if (buff[0] & 0x40 /*OCR的CCS位*/) {
                        sd_type = SD_TYPE_V2HC; /*大容量卡*/
                        #if _DEBUG_
                        printf("大容量卡\r\n");
                        #endif
						return 0xfe;
                    }
                    else {
                        sd_type = SD_TYPE_V2;   /*小容量卡*/    
                        #if _DEBUG_
                        printf("小容量卡\r\n");
                        printf("CMD16:%#x\r\n", send_cmd(CMD16,512,0X00));
                        #endif
						return 0xfd;
                    }
                }
                #if _DEBUG_
                else printf("SD卡ACMD41初始化失败,或读取OCR失败\r\n");
                #endif
            } 
            #if _DEBUG_
            else printf("不支持2.7V ~ 3.3V电压\r\n");
            #endif
        } else {    /*SD V1.x协议或MMC V3,这里没有卡所以还没有实现*/
            #if _DEBUG_
            printf("SD V1.x协议或MMC V3*\r\n");
            #endif
            r1 = send_cmd(CMD55, 0, 0x01);
            printf("CMD55 %#x\r\n", r1);
            r1 = send_cmd(CMD41, 0, 0x01);
            #if _DEBUG_
            printf("CMD41返回值%#x\r\n", r1);
            #endif
        }
    } 
    #if _DEBUG_
    else {      /*进入空闲状态失败*/
        
        printf("SD卡进入空闲状态失败\r\n");
        
    }
    #endif
    
    /*将SPI设置为高速*/
    //SPI1->CR1 &= ~(7 << 3);/*36Mhz*/
    //SPI_Cmd(SPI1, ENABLE);
    //replace  : beacause other chip types not support,so the function disabled.
    if (sd_type != SD_TYPE_ERR) {
        #if _DEBUG_
        printf("sdcard_init return 0\r\n");
        #endif
        return 0xff;
    }
    else if (r1) {
        #if _DEBUG_
        printf("sdcard_init return %02x\r\n", r1);
        #endif
        return r1;
    }
    else {
        #if _DEBUG_
        printf("sdcard_init return 0xff\r\n");
        #endif
        return 0xff;
    }
}

/*功能:获得SD卡的CSD寄存器内容
 *参数:   
 *  buff --> 接收缓冲区,至少16byte
 *返回值:
 *  0 --> 成功
 *  非0 --> 失败
 */
static u8 get_csd(u8 *buff)
{
	u8 r1 = 0;
	r1 = send_cmd_assert(CMD9, 0, 0x00);
	
	if (!r1)	/*读取CSD成功*/
		sdcard_block_read(buff, 16);
	sdcard_deassert();
	
	return r1;
	
}
/*功能:获得SD卡的容量
 *参数:   
 *  buff --> 接收缓冲区,至少16byte
 *返回值:
 *  0 --> 失败
 *  非0 --> 容量的扇区数
 */
u32 sdcard_sector_count()
{
    u8 csd[16];
    u16 mul;
    u16 csize;
    u32 sector_cnt;

    if (get_csd(csd)) { /*失败*/
        #if _DEBUG_
        printf("获取CSD寄存器失败\r\n");
        #endif
        return 0;
    }
	printf(" sam  : csd & 0x40 : %02x\r\n",(csd[0] & 0xc0));
    if ((csd[0] & 0xc0) == 0x40) {  /*V2.0 大容量卡*/
        csize = csd[9] + ((u16)csd[8] << 8) + 1;
        sector_cnt = (u32)csize << (9 + 1);     /*具体计算方法,参看<<SD卡协议(物理层)>>P87*/
        #if _DEBUG_
        printf("csd:%#x, %#x transpeed:%#x, READ_LN%#x\r\n", csd[0], csd[1], csd[3], csd[5] & 0xf);
        #endif
    } else {    /*V2.0小容量卡或V1.x卡*/
        csize = ((((u16)csd[6] & 0x3) << 10) | (csd[7] << 2) | (csd[8]) >> 6) + 1;
        mul = (u16)(((csd[10] >> 1) & 0x1) | (csd[9] & 0x3) << 1) + 2 + (u16)(csd[5] & 0xf);
        sector_cnt = csize << (mul - 9);
        #if _DEBUG_
        printf("csize:%#x,mul:%#x,block_len:%#x\r\n", csize, mul, csd[5] & 0xf);
        #endif
    }
    return sector_cnt;
}
/*功能:获得SD卡的某个扇区
 *参数:   
 *  buff --> 接收缓冲区,至少512 字节
 *  sector --> 扇区号
 *  cnt --> 读取的扇区数
 *返回值:
 *  0 --> 成功
 *  非0 --> 失败
 */
u16 sdcard_read_sector(u8 *buff, u32 sector, u16 cnt)
{
    u8 r1;
    #if _DEBUG_
    if (!cnt) printf("sdcard_read_sector ERR!!!!!!!\r\n");
    #endif
 	sdcard_assert();   
    if (sd_type != SD_TYPE_V2HC)    /*HC卡是以扇区号为读写地址的，而其他卡是以字节为读取地址的*/
        sector <<= 9;
            
    if (cnt == 1) {
        r1 = send_cmd_assert(CMD17, sector, 0x00);
        if (!r1)
            r1 = sdcard_block_read(buff, 512);
    } else {
        r1 = send_cmd_assert(CMD18, sector, 0x00);
        do {
            r1 = sdcard_block_read(buff, 512);
            buff += 512;
        }while (--cnt && r1 ==0);
        send_cmd(CMD12, 0, 0x00);
    }
    sdcard_deassert();
    return r1;
}
/*功能:向SD卡的某个扇区中写数据
 *参数:   
 *  buff --> 发送缓冲区
 *  sector --> 扇区号
 *  cnt --> 缓冲区中的扇区的数据
 *返回值:
 *  0 --> 成功
 *  非0 --> 失败
 */
u16 sdcard_write_sector(const u8 *buff, u32 sector, u8 cnt)
{
    u8 r1;
    #if _DEBUG_
    if (!cnt) printf("sdcard_read_sector ERR!!!!!!!\r\n");
    #endif
    
    if (sd_type != SD_TYPE_V2HC)    /*HC卡是以扇区号为读写地址的，而其他卡是以字节为读取地址的*/
        sector <<= 9;
    if (cnt == 1) {
        r1 = send_cmd_assert(CMD24, sector, 0x00);
        if (!r1)
            r1 = sdcard_block_write(buff, 0xfe);
    } else {
        if (sd_type != SD_TYPE_MMC) {   /*如果不是MMC卡可以先预擦除, 可以更快的来写入*/
            send_cmd(CMD55, 0, 0);
            send_cmd(CMD23, cnt, 0);
        }
        #if _DEBUG_
        printf("写多块\r\n");
        #endif
        r1 = send_cmd_assert(CMD25, sector, 0); /*连续写命令*/
        if (r1 == 0) {  /*成功发送命令*/
            do {
                r1 = sdcard_block_write(buff, 0xfc);    /*写512个字节*/
                #if _DEBUG_
                printf("CMD25:%#x\r\n", r1);
                #endif
                buff += 512;
            } while (--cnt && r1 == 0);
            r1 = sdcard_block_write(0, 0xfd);   /*停止发送*/
        }   
    }
    sdcard_deassert();
    
    #if _DEBUG_
    if (!r1) printf("写入成功\r\n"); else printf("写入失败\r\n");
    #endif
    
    return r1;
        
}

