/*
 * 红芯电子 I2C 测试程序
 * 如果你使用 24C64 ,I2C 寄存器地址是16位的，两字节。
 * 如果你使用 24C08 ,请屏蔽多发一个字节的地址,说见函数注释
 */

#include <stdio.h>

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
#include "../../inc/i2c.h"

extern char ADC_char[];

alt_u8 eeprom_Status = 0;

int i2c_main(void)
{
	uchar i;
	uchar ret;

	uchar buff_w[EEPROM_SIZE];
	uchar buff_r[EEPROM_SIZE];	

#if 1	
	srand(ADC_char[7] + ADC_char[9] + ADC_char[10]);

	printf("Rand data generate and list : \r\n");

	for(i=0; i<EEPROM_SIZE; i++)	
		buff_w[i] = rand();	

	for(i=0; i<EEPROM_SIZE; i++)
	{
		if((i % 8) == 0)
			printf("\r\n");
		printf("%02x ",buff_w[i]);	
	}
	printf("\r\n");

	printf("Write_to_i2c start ... \r\n");
	ret = Write_to_i2c(EEPROM_ADDR,REG_ADDR,buff_w,EEPROM_SIZE);
	if(ret == false)
	{
		printf("Write_to_i2c failure ... \r\n\n");
		while(1);
	}
	printf("Write_to_i2c success ... \r\n");	

#endif

	for(i=0; i<EEPROM_SIZE; i++)	
		buff_r[i] = 0x00;

	for(i=0; i<10; i++)	//must delay enough time
	{
		delay_us(255);
		delay_us(255);
		delay_us(255);	
	}

	ret = Read_from_i2c(EEPROM_ADDR,REG_ADDR,buff_r,EEPROM_SIZE);
	if(ret == false)
	{
		printf("Read_to_i2c failure ... \r\n\n");
		while(1);
	}
	printf("Read_from_i2c success ... \r\n");	

	printf("Then list read data : \r\n");
	for(i=0; i<EEPROM_SIZE; i++)
	{
		if((i % 8) == 0)
			printf("\r\n");
		printf("%02x ",buff_r[i]);
	}
	printf("\r\n");
	printf ("\r------------------------------------------------\r\n"); 	
        
        for(i=0; i<EEPROM_SIZE; i++)
        {
                if(buff_r[i] != buff_w[i])
                {
                        printf("Compile data err buff_w[%d] = %02x, buff_r[%d] = %02x\r\n",i,buff_w[i],i,buff_r[i]);
						eeprom_Status = 0;
                        return 0;
                }
        } 
		eeprom_Status = 1;  
        
        printf("All EEPROM data compare Success \r\n");

  	return 1;
}

/*******************************************************************/
void delay_us(uchar i)//i=248 delay 500us ;i=3 delay 10us ;2x+4=delay(us)
{
	 usleep(i);
}

/*******************************************************************/
void I2CStart(void)
{
	//EA=0;
	SET_SDA_OUTPUT();
	SET_SDA(1);
	SET_SCL(1);
	delay_us(5);
	SET_SDA(0);
	delay_us(5);
	SET_SCL(0);
}
/*******************************************************************/
void I2CStop(void)
{
	SET_SDA_OUTPUT();
	SET_SCL(0);
	SET_SDA(0);
	delay_us(5);
	SET_SCL(1);
	delay_us(5);
	SET_SDA(1);
}
/*******************************************************************/
uchar WaitAck(void)
{
	uchar errtime=255;

	SET_SDA_INPUT();//在SCL为0时就释放总线
	delay_us(5);
	SET_SCL(1);
	delay_us(5);

	while(GET_SDA())
	{
		errtime--;
		delay_us(1);

		if(!errtime)
		{
			I2CStop();
			printf("WaitAck error\r\n");
			return false;
		}
	}
		
	//printf("WaitAck OK\r\n");
	delay_us(5);	
	SET_SCL(0);
	return true;
}
/*******************************************************************/
void SendAck(void)
{
	SET_SDA_OUTPUT();
	SET_SDA(0);
	delay_us(5);
	SET_SCL(1);
	delay_us(5);
	SET_SCL(0);
}
/*******************************************************************/
void SendNotAck(void)
{
	SET_SDA_OUTPUT();
	SET_SDA(1);
	delay_us(5);
	SET_SCL(1);
	delay_us(5);
	SET_SCL(0);
}
/*******************************************************************/
void I2CSendByte(uchar ch)
{
	uchar i=8;
	
	SET_SDA_OUTPUT();
	//printf("Send byte : %02x\r\n",ch);
	while(i--)
	{
		SET_SCL(0);
		delay_us(5);
		
		SET_SDA((ch & 0x80) ? 1 : 0);
			
		ch <<= 1;
		delay_us(5);
		SET_SCL(1);
		delay_us(5);
	}
	SET_SCL(0);
}
/*******************************************************************/
uchar I2CReceiveByte(void)
{
	uchar i=8;
	uchar ddata=0;
	//SET_SDA_OUTPUT();
	//SET_SDA(1);
	
	SET_SDA_INPUT();

	while(i--)
	{
		ddata <<= 1;
		SET_SCL(0);
		delay_us(5);
		SET_SCL(1);
		delay_us(5);
		
		ddata |= GET_SDA();	
	}
	SET_SCL(0);	
	return ddata;
}
/*******************************************************************/
uchar Read_from_i2c(uchar DeviceAddr,uchar RegAddr,uchar *buff,uchar len)
{
	uchar i;
	uchar ret;
	I2CStart();
	I2CSendByte(DeviceAddr);
	ret = WaitAck();
	if(ret == false)
		return false;
	
	//24c64 需要2个字节的寄存器地址，所以这里多发了一次。
	//如果你使用 24C08 ,请屏蔽多发的这一个字节的地址
	I2CSendByte(0x00);
	ret = WaitAck();
	if(ret == false)
		return false;
    //end  
        
    I2CSendByte(RegAddr);
    ret = WaitAck();
    if(ret == false)
        return false;        
	
	I2CStart();
	I2CSendByte(DeviceAddr | 0x01);
	ret = WaitAck();
	if(ret == false)
		return false;
	
	for(i=0; i<len; i++)
	{
		*(buff + i) = I2CReceiveByte();
		//printf("read data : %02x - %d\r\n",*(buff + i),i);
		if(i != (len-1))
		{
           SendAck();
		}
	}	
	
	SendNotAck();
	I2CStop();
	return true;
}

/*******************************************************************/

uchar Write_to_i2c(uchar DeviceAddr,uchar RegAddr,uchar *buff,uchar len)
{
	uchar i;
	uchar ret = false;
	
	I2CStart();
	I2CSendByte(DeviceAddr);
	
	ret = WaitAck();
	if(ret == false)
	{
		printf("error 1\r\n");
		return false;
	}

	//24c64 需要2个字节的寄存器地址，所以这里多发了一次。
	//如果你使用 24C08 ,请屏蔽多发的这一个字节的地址	
	I2CSendByte(0x00);

	ret = WaitAck();
	if(ret == false)
	{
		printf("error 2\r\n");
		return false;
	}
	// end
	
    I2CSendByte(RegAddr);

    ret = WaitAck();
    if(ret == false)
    {
        printf("error 2\r\n");
        return false;
    }    
	
	for(i=0;i<len;i++)
	{
		I2CSendByte(*(buff + i));
		//printf("Send data : %02x - %d\r\n",*(buff + i),i);
		ret = WaitAck();
		if(ret == false)
		{
			printf("error 3\r\n");
			return false;
		}
	}

	I2CStop();
	return true;
}
/*******************************************************************/

