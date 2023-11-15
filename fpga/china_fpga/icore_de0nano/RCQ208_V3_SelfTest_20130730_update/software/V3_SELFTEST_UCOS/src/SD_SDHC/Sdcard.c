
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

/*������¼SD��������*/
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
   		if(sdcard_init() == 0xfd)//SD С����
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
		else if(sdcard_init() == 0xfe)//SDHC ������
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

/*����:��������
 *����:   
 *  cmd --> �������
 *  arg --> ����
 *  crc --> ����Ͳ�����crc����
 *����ֵ:�����ֵ
 */
static u8 send_cmd(u8 cmd, u32 arg, u8 crc)
{
	u8 i = 0;
	u8 r1 = 0;
	
	if (sdcard_assert())
		return 0xff;	/*Ƭѡʧ��*/
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
/*����:��������,����Ȼ����Ƭѡ״̬
 *����:   
 *  cmd --> �������
 *  arg --> ����
 *  crc --> ����Ͳ�����crc����
 *����ֵ:�����ֵ
 */
static u8 send_cmd_assert(u8 cmd, u32 arg, u8 crc)
{
	u8 i = 0;
	u8 r1 = 0;
	
	if (sdcard_assert())
		return 0xff;	/*Ƭѡʧ��*/
	
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
/*����:��ʼ��sdcard
 *����:   ��
 *����ֵ:
 *  0 --> �ɹ�
 *  ����ֵ --> ʧ��
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
    /*�ϵ���ʱ*/
    for (i = 0; i < 10; i++)    /*ѭ������74������*/
        sdcard_write(0xff);
    
    /*����CMD0ʹ������Idle״̬*/
    for (i = 0; i < 20; i++) {
        r1 = send_cmd(CMD0, 0, 0x95);   /*����IDLE״̬*/
        if (r1 == 0x01) /*����������״̬*/
            break;  
        #if _DEBUG_
        //printf("r1:%#x\r\n", r1);
        #endif
    }
    if (r1 == 0x01) {   /*������гɹ�*/
        #if _DEBUG_
        printf("SD���������״̬\r\n");
        #endif
        if (send_cmd_assert(CMD8, 0x1aa, 0x87) == 1) {  /*SD V2.0Э��*/
        
            #if _DEBUG_
            printf("SD V2.0Э��\r\n");
            #endif
            for (i = 0; i < 4; i++) {
                buff[i] = sdcard_read();
                #if _DEBUG_
                printf("the buffer[%d] is : %02x\r\n",i,buff[i]);
                #endif
            }
            /*ȡ��ƬѡSD��*/
            sdcard_deassert();/*end of send_cmd_assert(CMD8, 0x1aa, 0x87)*/
            if (buff[2] == 1 && buff[3] == 0xaa) {  /*��֧��2.7~3.6V��ѹ*/
                   
            i = 0xfff;
            do {
                send_cmd(CMD55, 0, 0x0);    /*ָʾ��һ��ΪApp��CMD*/
                r1 = send_cmd(CMD41,1 << 30 /*HCSλ,�ο���SD��Э������㡷P107*/, 0x00);  /*��֪SD��,����֧�ִ������������������������*/
				usleep(10000);
			} while (r1 && i--);
             #if _DEBUG_
             printf("ACMD41����ֵ:%#x\r\n", r1);
             #endif
			 if (!r1 && !send_cmd_assert(CMD58, 0, 0)) {	/*ACMD41����0�����ʼ���ɹ�,���ɹ���ȡOCR*/
             #if _DEBUG_
             printf("����SD����ʼ���\r\n");
             #endif
                    /*��OCR��ֵ*/
                    for (i = 0; i < 4; i++) 
                        buff[i] = sdcard_read();
                    sdcard_deassert();/*send_cmd_assert(CMD58, 0, 0)*/
                    
                    /*�жϿ�������*/
                    if (buff[0] & 0x40 /*OCR��CCSλ*/) {
                        sd_type = SD_TYPE_V2HC; /*��������*/
                        #if _DEBUG_
                        printf("��������\r\n");
                        #endif
						return 0xfe;
                    }
                    else {
                        sd_type = SD_TYPE_V2;   /*С������*/    
                        #if _DEBUG_
                        printf("С������\r\n");
                        printf("CMD16:%#x\r\n", send_cmd(CMD16,512,0X00));
                        #endif
						return 0xfd;
                    }
                }
                #if _DEBUG_
                else printf("SD��ACMD41��ʼ��ʧ��,���ȡOCRʧ��\r\n");
                #endif
            } 
            #if _DEBUG_
            else printf("��֧��2.7V ~ 3.3V��ѹ\r\n");
            #endif
        } else {    /*SD V1.xЭ���MMC V3,����û�п����Ի�û��ʵ��*/
            #if _DEBUG_
            printf("SD V1.xЭ���MMC V3*\r\n");
            #endif
            r1 = send_cmd(CMD55, 0, 0x01);
            printf("CMD55 %#x\r\n", r1);
            r1 = send_cmd(CMD41, 0, 0x01);
            #if _DEBUG_
            printf("CMD41����ֵ%#x\r\n", r1);
            #endif
        }
    } 
    #if _DEBUG_
    else {      /*�������״̬ʧ��*/
        
        printf("SD���������״̬ʧ��\r\n");
        
    }
    #endif
    
    /*��SPI����Ϊ����*/
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

/*����:���SD����CSD�Ĵ�������
 *����:   
 *  buff --> ���ջ�����,����16byte
 *����ֵ:
 *  0 --> �ɹ�
 *  ��0 --> ʧ��
 */
static u8 get_csd(u8 *buff)
{
	u8 r1 = 0;
	r1 = send_cmd_assert(CMD9, 0, 0x00);
	
	if (!r1)	/*��ȡCSD�ɹ�*/
		sdcard_block_read(buff, 16);
	sdcard_deassert();
	
	return r1;
	
}
/*����:���SD��������
 *����:   
 *  buff --> ���ջ�����,����16byte
 *����ֵ:
 *  0 --> ʧ��
 *  ��0 --> ������������
 */
u32 sdcard_sector_count()
{
    u8 csd[16];
    u16 mul;
    u16 csize;
    u32 sector_cnt;

    if (get_csd(csd)) { /*ʧ��*/
        #if _DEBUG_
        printf("��ȡCSD�Ĵ���ʧ��\r\n");
        #endif
        return 0;
    }
	printf(" sam  : csd & 0x40 : %02x\r\n",(csd[0] & 0xc0));
    if ((csd[0] & 0xc0) == 0x40) {  /*V2.0 ��������*/
        csize = csd[9] + ((u16)csd[8] << 8) + 1;
        sector_cnt = (u32)csize << (9 + 1);     /*������㷽��,�ο�<<SD��Э��(�����)>>P87*/
        #if _DEBUG_
        printf("csd:%#x, %#x transpeed:%#x, READ_LN%#x\r\n", csd[0], csd[1], csd[3], csd[5] & 0xf);
        #endif
    } else {    /*V2.0С��������V1.x��*/
        csize = ((((u16)csd[6] & 0x3) << 10) | (csd[7] << 2) | (csd[8]) >> 6) + 1;
        mul = (u16)(((csd[10] >> 1) & 0x1) | (csd[9] & 0x3) << 1) + 2 + (u16)(csd[5] & 0xf);
        sector_cnt = csize << (mul - 9);
        #if _DEBUG_
        printf("csize:%#x,mul:%#x,block_len:%#x\r\n", csize, mul, csd[5] & 0xf);
        #endif
    }
    return sector_cnt;
}
/*����:���SD����ĳ������
 *����:   
 *  buff --> ���ջ�����,����512 �ֽ�
 *  sector --> ������
 *  cnt --> ��ȡ��������
 *����ֵ:
 *  0 --> �ɹ�
 *  ��0 --> ʧ��
 */
u16 sdcard_read_sector(u8 *buff, u32 sector, u16 cnt)
{
    u8 r1;
    #if _DEBUG_
    if (!cnt) printf("sdcard_read_sector ERR!!!!!!!\r\n");
    #endif
 	sdcard_assert();   
    if (sd_type != SD_TYPE_V2HC)    /*HC������������Ϊ��д��ַ�ģ��������������ֽ�Ϊ��ȡ��ַ��*/
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
/*����:��SD����ĳ��������д����
 *����:   
 *  buff --> ���ͻ�����
 *  sector --> ������
 *  cnt --> �������е�����������
 *����ֵ:
 *  0 --> �ɹ�
 *  ��0 --> ʧ��
 */
u16 sdcard_write_sector(const u8 *buff, u32 sector, u8 cnt)
{
    u8 r1;
    #if _DEBUG_
    if (!cnt) printf("sdcard_read_sector ERR!!!!!!!\r\n");
    #endif
    
    if (sd_type != SD_TYPE_V2HC)    /*HC������������Ϊ��д��ַ�ģ��������������ֽ�Ϊ��ȡ��ַ��*/
        sector <<= 9;
    if (cnt == 1) {
        r1 = send_cmd_assert(CMD24, sector, 0x00);
        if (!r1)
            r1 = sdcard_block_write(buff, 0xfe);
    } else {
        if (sd_type != SD_TYPE_MMC) {   /*�������MMC��������Ԥ����, ���Ը������д��*/
            send_cmd(CMD55, 0, 0);
            send_cmd(CMD23, cnt, 0);
        }
        #if _DEBUG_
        printf("д���\r\n");
        #endif
        r1 = send_cmd_assert(CMD25, sector, 0); /*����д����*/
        if (r1 == 0) {  /*�ɹ���������*/
            do {
                r1 = sdcard_block_write(buff, 0xfc);    /*д512���ֽ�*/
                #if _DEBUG_
                printf("CMD25:%#x\r\n", r1);
                #endif
                buff += 512;
            } while (--cnt && r1 == 0);
            r1 = sdcard_block_write(0, 0xfd);   /*ֹͣ����*/
        }   
    }
    sdcard_deassert();
    
    #if _DEBUG_
    if (!r1) printf("д��ɹ�\r\n"); else printf("д��ʧ��\r\n");
    #endif
    
    return r1;
        
}

