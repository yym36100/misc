 /****************************************
 *Copyright (c) findstr 5/11/2012
 *Version 0.1 for stm32f103
 *SD������IO����
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
/*����:��sd��
 *����:   ��
 *����ֵ�������ķ���ֵ
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

/*����:дsd��
 *����:   
 *  data --> Ҫд�������
 *����ֵ����
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

/*����:�ȴ�SD�����ھ���״̬
 *����:   ��
 *����ֵ:
 *  0 --> SD������
 *  1 --> SD������æ
 *˵��������SD����д��ʱ�ὫSD��DATA0����(��SPI��MISO����
 */
static u8 wait_ready()
{
    u32 t = 0xffffff;
    
    while (t--) {
        if (sdcard_read() == 0xff)
        return 0;
    }
    
    #if _DEBUG_
    printf("wait_ready ʧ��\r\n");
    #endif
    return 1;
}


/*���ڼ�¼SD���Ƿ�Ƭѡ��
 * 0 --> û�б�Ƭѡ
 * 1 --> �Ѿ���Ƭѡ
 */
static volatile u8 sdcard_asserted = 0;
/*����:Ƭѡ
 *����:   ��
 *����ֵ��
 *  0 -->Ƭѡ�ɹ�
 *  1 -->Ƭѡʧ��
 */
u8 sdcard_assert()
{
    if (!sdcard_asserted) { /*û�б�Ƭѡ*/
        SD_CS(0);
        if (!wait_ready()) {    /*�豸����,��ֱ�ӷ���*/
          sdcard_asserted = 1;
          return 0;
        }
        SD_CS(1);
        return 1;
    } else { /*�Ѿ�Ƭѡ����*/
        return 0;
    }
}

/*����:ȡ��Ƭѡ
 *����:   ��
 *����ֵ����
 */
void sdcard_deassert()
{
    if (sdcard_asserted) {  /*�Ѿ�Ƭѡ����*/
        SD_CS(1);
        sdcard_write(0xff);
        sdcard_asserted = 0;
    } else {    /*SD�����ڷ�Ƭѡ״̬*/
        
    }
}

/*����:������ʱƥ�����ݵĿ�ʼ�ı�ʶ
 *����:   
 *  token --> Ҫƥ���token
 *����ֵ:
 *  0 --> ƥ��
 *  1 --> ƥ�䳬ʱ
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
/*����:������n������
 *����:   
 *  buff --> ���ջ���
 *  cnt --> Ҫ��ȡ���ٸ��ֽ�
 *����ֵ:
 *  0 --> ʧ��
 *  ���� --> �������ֽ���
 */
u8 sdcard_block_read(u8 *buff, u16 cnt)
{   
    u8 n = cnt;
    u16 i = 0;
	
	sdcard_assert();
    /*���ȵõ����ݵ�token,Ȼ���������*/
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
   /*���һ�������ֽڵ�CRC*/
    sdcard_read();
    sdcard_read();
	sdcard_deassert();	
    return n;
}
/*����:����д����
 *����:   
 *  buff -->���ͻ�����
 *  cmd --> �����ֽڵ�����
 *����ֵ:
 *  0 --> �ɹ�
 *  ��0 --> ʧ��
 */
u8 sdcard_block_write(const u8 *buff, u8 cmd)
{
    u16 t,count;
	u16 i = 0;
	sdcard_assert();
    if (wait_ready())
        return 1;   /*��æ*/
	
    sdcard_write(cmd);  /*������������*/
    if (cmd != 0xfd) {  /*���ǽ�����������*/
	{
		for(i=0; i<512; i++)
		{
			sdcard_write(*(buff++));
		}
    }
	
    /*����CRC*/
    sdcard_write(0xff);
    sdcard_write(0xff);
    /*����������Ӧ*/
    t = sdcard_read();
	sdcard_deassert();
    if ((t & 0x1f) != 0x05) /*�ο���SD�������Э�顷P111*/
        return 2;   /*����*/
    #if _DEBUG_
    printf("д����ֵ:%#x\r\n", t);
    #endif
    }   
  return 0;
}
