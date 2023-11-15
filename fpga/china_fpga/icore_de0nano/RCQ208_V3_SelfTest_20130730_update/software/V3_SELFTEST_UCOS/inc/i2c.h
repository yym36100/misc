
//----------------------------------------------------------------------------------------------------
#define uchar unsigned char
#define true  1
#define false 0

/* Defintions for direction-register operation with bi-directional PIOs */
//#define ALTERA_AVALON_PIO_DIRECTION_INPUT  0
//#define ALTERA_AVALON_PIO_DIRECTION_OUTPUT 1

//=============================================================================
//IO Operation
//=============================================================================
//#define I2C_SCL_BASE        0x04002270
//#define I2C_SDA_BASE        0x04002280

#define SET_SDA_INPUT()     IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE,ALTERA_AVALON_PIO_DIRECTION_INPUT)

#define SET_SDA_OUTPUT()    IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE,ALTERA_AVALON_PIO_DIRECTION_OUTPUT)

#define SET_SCL(a)          IOWR_ALTERA_AVALON_PIO_DATA(SCL_BASE, a)
#define SET_SDA(a)          IOWR_ALTERA_AVALON_PIO_DATA(SDA_BASE, a)

#define GET_SDA()           IORD_ALTERA_AVALON_PIO_DATA(SDA_BASE)

#define EEPROM_ADDR 0xa0
#define REG_ADDR    0x10

//ע��:24C02һ����32ҳ��ÿҳ8���ֽڣ�һ����256�ֽڡ�ÿ������дʱ���ó���8���ֽڡ�
#define EEPROM_SIZE 8 

void delay_us(uchar i);
void UART_initial(void);
void I2CStart(void);
void I2CStop(void);
uchar WaitAck(void);
void SendAck(void);
void SendNotAck(void);
void I2CSendByte(uchar ch);
uchar I2CReceiveByte(void);
uchar Write_to_i2c(uchar DeviceAddr,uchar RegAddr,uchar *buff,uchar len);
uchar Read_from_i2c(uchar DeviceAddr,uchar RegAddr,uchar *buff,uchar len);
int i2c_main(void);

//----------------------------------------------------------------------------------------------------

