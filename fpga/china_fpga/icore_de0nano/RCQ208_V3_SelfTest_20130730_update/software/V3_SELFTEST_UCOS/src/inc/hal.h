///////////////////////////hal.h//////////////////////////


unsigned char SdInit(void);
unsigned char SdReadBlock(unsigned char *Block, unsigned long address);
unsigned char SdWriteBlock(unsigned char *Block, unsigned long address);


void DelayMs(unsigned char nFactor);
unsigned long SwapINT32(unsigned long dData);
void ComSendByte(unsigned char c);

unsigned int LSwapINT16(unsigned short dData1,unsigned short dData2);
unsigned long LSwapINT32(unsigned long dData1,unsigned long dData2,unsigned long dData3,unsigned long dData4);
unsigned long SwapINT32(unsigned long dData);
void IO_test(void);


