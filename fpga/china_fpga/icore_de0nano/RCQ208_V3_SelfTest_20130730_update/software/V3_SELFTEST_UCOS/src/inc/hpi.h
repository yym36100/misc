/////////////////hpi.h////////////////////////////////
typedef struct Command_D{
  unsigned char CLass;
  unsigned long len;
  unsigned char Parameter[32];
} Command_Def;

typedef struct Response_D{
  unsigned char Result;
  unsigned long len;
} Response_Def;

#define MaxLFNum 20

typedef struct ShowFileName_D{
  unsigned char LongName[256];	//long file name,end by 00 00
  unsigned char item[32];	//short file name & dir
} ShowFileName_Def;

void UartSendRsp(void);
unsigned char UartHandler(void);
unsigned char List(void);
unsigned char OpenFile(unsigned char *pBuffer);
unsigned char ReadFile(unsigned long readLength,unsigned char *pBuffer);
unsigned char SetFilePointer(unsigned long pointer);

unsigned char CreateFile(unsigned long len,unsigned char *pBuffer,unsigned char *pName);
unsigned char WriteFile(unsigned long writeLength,unsigned char *pBuffer);
unsigned char RemoveFile(unsigned char *pBuffer);
unsigned char GetCapacity(void);

unsigned char CreateDir(unsigned long len,unsigned char *pBuffer,unsigned char *pName);
unsigned char DownDir(unsigned char *pBuffer);
unsigned char UpDir(void);
unsigned char UpRootDir(void);
unsigned char RemoveDir(unsigned char *pBuffer);

