/////////////////hpi32.h////////////////////////////////
unsigned char UartHandler32(void);
unsigned char List32(void);
unsigned char OpenFile32(unsigned char *pBuffer);


unsigned char ReadFile32(unsigned long readLength,unsigned char *pBuffer);
unsigned char SetFilePointer32(unsigned long pointer);
unsigned char CreateFile32(unsigned long len,unsigned char *pBuffer,unsigned char *pName);
unsigned char WriteFile32(unsigned long writeLength,unsigned char *pBuffer);
unsigned char RemoveFile32(unsigned char *pBuffer);
unsigned char GetCapacity32(void);


unsigned char CreateDir32(unsigned long len,unsigned char *pBuffer,unsigned char *pName);
unsigned char DownDir32(unsigned char *pBuffer);
unsigned char UpDir32(void);
unsigned char UpRootDir32(void);
