
#ifndef UINT_H_
#define UINT_H_
typedef	unsigned char	UINT8;
typedef unsigned short	UINT16;
typedef unsigned int	UINT32;

#endif
//----------------------------------------------------------------------------
//function decerlation
//----------------------------------------------------------------------------
void Print_ETH_Msg(void);
void delay_ETH_us(UINT32 i);


extern int WebServer_main(void);
extern int Ethernet_test(void);


