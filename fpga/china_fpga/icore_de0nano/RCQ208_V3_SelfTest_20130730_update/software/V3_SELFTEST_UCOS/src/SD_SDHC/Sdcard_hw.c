 /****************************************
 *Copyright (c) findstr 5/11/2012
 *Version 0.1 for stm32f103
 *SD卡数据IO部分
 *****************************************
 */
#include "stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
 
#include "../inc/sdcard_hw.h"
#include "../inc/sdcard.h"
#include "../inc/common.h"

#define _DEBUG_ 1
void sdcard_io_init()
{   
	SD_CS(1);
}
/*功能:读sd卡
 *参数:   无
 *返回值：读到的返回值
 */
inline u8 sdcard_read()
{
    u8 n,i;   
    n = 0;
    for(i=8;i;i--)
    {   
        SD_CLK(0);
        n <<= 1;		
        SD_CLK(1);
        if(SD_DO) 
			n|= 1;		
    }
    return n;
}

/*功能:写sd卡
 *参数:   
 *  data --> 要写入的数据
 *返回值：无
 */
inline void sdcard_write(u8 n)
{
    u8 i;
    
    for(i=8;i;i--)
    {
        SD_CLK(0);
        if(n & 0x80)
          SD_DI(1);
        else
          SD_DI(0);
        SD_CLK(1);
        n <<= 1;		
    }
    SD_DI(1);//SD_DI=1;   
}

/*功能:等待SD卡处于就绪状态
 *参数:   无
 *返回值:
 *  0 --> SD卡空闲
 *  1 --> SD卡正在忙
 *说明：由于SD卡在写入时会将SD卡DATA0引脚(即SPI的MISO引脚
 */
static u8 wait_ready()
{
    u32 t = 0xffffff;
    
    while (t--) {
        if (sdcard_read() == 0xff)
        return 0;
    }
    
    #if _DEBUG_
    printf("wait_ready 失败\r\n");
    #endif
    return 1;
}


/*用于记录SD卡是否被片选过
 * 0 --> 没有被片选
 * 1 --> 已经被片选
 */
static volatile u8 sdcard_asserted = 0;
/*功能:片选
 *参数:   无
 *返回值：
 *  0 -->片选成功
 *  1 -->片选失败
 */
u8 sdcard_assert()
{
    if (!sdcard_asserted) { /*没有被片选*/
        SD_CS(0);
        if (!wait_ready()) {    /*设备空闲,则直接返回*/
          sdcard_asserted = 1;
          return 0;
        }
        SD_CS(1);
        return 1;
    } else { /*已经片选过了*/
        return 0;
    }
}

/*功能:取消片选
 *参数:   无
 *返回值：无
 */
void sdcard_deassert()
{
    if (sdcard_asserted) {  /*已经片选过了*/
        SD_CS(1);
        sdcard_write(0xff);
        sdcard_asserted = 0;
    } else {    /*SD卡处于非片选状态*/
        
    }
}

/*功能:读数据时匹配数据的开始的标识
 *参数:   
 *  token --> 要匹配的token
 *返回值:
 *  0 --> 匹配
 *  1 --> 匹配超时
 */
static u8 match_token(u8 token)
{
    u16 timeout = 0xffff;
    while ((sdcard_read() != token) && timeout--)
        ;
    if (!timeout)
        return 1;
    return 0;
}
/*功能:连续读n个数据
 *参数:   
 *  buff --> 接收缓冲
 *  cnt --> 要读取多少个字节
 *返回值:
 *  0 --> 失败
 *  其他 --> 读到的字节数
 */
u8 sdcard_block_read(u8 *buff, u16 cnt)
{   
    u8 n = cnt;
    u16 i = 0;
	
	sdcard_assert();
    /*首先得到数据的token,然后才是数据*/
    if (match_token(0xfe))
    {
	    #if _DEBUG_
	    printf("not match token\r\n");
	    #endif    
		sdcard_deassert();
        return 0;
    }

    for(i=0;i<cnt;i++)
    {
      *(buff++) = sdcard_read();//spi_dma_read(buff, cnt);
    }	
    //data block sent - now send checksum
   /*虚读一下两个字节的CRC*/
    sdcard_read();
    sdcard_read();
	sdcard_deassert();	
    return n;
}
/*功能:连续写数据
 *参数:   
 *  buff -->发送缓冲区
 *  cmd --> 发送字节的令牌
 *返回值:
 *  0 --> 成功
 *  非0 --> 失败
 */
u8 sdcard_block_write(const u8 *buff, u8 cmd)
{
    u16 t,count;
	u16 i = 0;
	sdcard_assert();
    if (wait_ready())
        return 1;   /*卡忙*/
	
    sdcard_write(cmd);  /*发送数据令牌*/
    if (cmd != 0xfd) {  /*不是结束数据令牌*/
	{
		for(i=0; i<512; i++)
		{
			sdcard_write(*(buff++));
		}
    }
	
    /*两个CRC*/
    sdcard_write(0xff);
    sdcard_write(0xff);
    /*接收命令响应*/
    t = sdcard_read();
	sdcard_deassert();
    if ((t & 0x1f) != 0x05) /*参看《SD卡物理层协议》P111*/
        return 2;   /*错误*/
    #if _DEBUG_
    printf("写返回值:%#x\r\n", t);
    #endif
    }   
  return 0;
}
