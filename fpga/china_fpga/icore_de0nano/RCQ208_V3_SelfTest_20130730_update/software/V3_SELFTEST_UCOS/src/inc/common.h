/*
-----------------------------------------------------------------
ºìÐ¾µç×Ó
-----------------------------------------------------------------*/
//typedef unsigned char	UINT8 ;
typedef unsigned short	UINT16 ;
typedef unsigned int	UINT32 ;

typedef int				INT32 ;
typedef short int		INT16 ;
typedef char			INT8 ;

typedef enum 
{
	LOW,
	HIGH	
}Level_e;

//--------------------------------------------------------------------------------
// LED port define
#define Turn_OFF_LED1()
#define Turn_ON_LED1()

#define Turn_OFF_LED2()
#define Turn_ON_LED2()

#define Turn_OFF_LED3()
#define Turn_ON_LED3()

#define Turn_OFF_LED4()	
#define Turn_ON_LED4()

#define Turn_OFF_LED5()	
#define Turn_ON_LED5()

#define Turn_OFF_LED6()	LED6_WR(1)
#define Turn_ON_LED6()	LED6_WR(0)

#define Turn_OFF_LED7()	LED7_WR(1)
#define Turn_ON_LED7()	LED7_WR(0)

// LED define
// RCQ208_V3


//--------------------------------------------------------------------------------

#define TRUE   		1
#define FALSE  		0

#define UARTBUF_LENGTH	512//16384//520//
#define BUFFER_LENGTH	 (2 * 1024)// 8192//520 //
#define MAX_READ_LENGTH	 (8 * 1024)// 16384//1024//
#define MAX_WRITE_LENGTH (1 * 1024)// 2048//1024//

// Disable all interrupts
#define DISABLE_INTERRUPTS//	EA = 0

// Enable all interrupts
#define ENABLE_INTERRUPTS//		EA = 1

typedef union __FLAGS
{
  struct _FLAGS
  {
    unsigned char   SLAVE_IS_ATTACHED	;
    unsigned char   SLAVE_REMOVED		;
    unsigned char   SLAVE_FOUND		;	// Slave USB device found
    unsigned char   SLAVE_ENUMERATED	;	// slave USB device enumeration done
    unsigned char   SLAVE_ONLINE		;
    unsigned char   TIMEOUT_ERR		;				// timeout error during data endpoint transfer
    unsigned char   DATA_STOP		;					// device unplugged during data transfer
    unsigned char   bData1			;
    unsigned char   bUartInDone		;		
    unsigned char   bMassDevice		; 	
  } bits;	
} FLAGS;

#define  u8  alt_u8
#define  u16 alt_u16
#define  u32 alt_u32

//#define LED6_WR(a)    IOWR_ALTERA_AVALON_PIO_DATA(LED6_BASE_BASE, a)
//#define LED7_WR(a)    IOWR_ALTERA_AVALON_PIO_DATA(LED7_BASE_BASE, a)

#define SD_CS(a)	IOWR_ALTERA_AVALON_PIO_DATA(SD_CS_BASE, a)			
#define SD_DI(a)	IOWR_ALTERA_AVALON_PIO_DATA(SD_DI_BASE, a)	
#define SD_CLK(a)	IOWR_ALTERA_AVALON_PIO_DATA(SD_CLK_BASE,a)
#define SD_DO		IORD_ALTERA_AVALON_PIO_DATA(SD_DO_BASE)//Read SDCard data port


//#define SET_START_O(a)	IOWR_ALTERA_AVALON_PIO_DATA(START_BASE, a)			
//#define GET_FIFO_WR_USE_DW_I()	IORD_ALTERA_AVALON_PIO_DATA(FIFO_WR_USEDW_BASE)

//#define GET_FIFO_WR_FULL_I()	IORD_ALTERA_AVALON_PIO_DATA(FIFO_WR_FULL_I_BASE)
//#define SET_FIFO_WR_CLK_O(a)	IOWR_ALTERA_AVALON_PIO_DATA(FIFO_WR_CLK_O_BASE, a)			
//#define SET_FIFO_WR_REQ_O(a)	IOWR_ALTERA_AVALON_PIO_DATA(FIFO_WR_REQ_O_BASE, a)	
//#define SET_FIFO_WR_DATA_O(a)	IOWR_ALTERA_AVALON_PIO_DATA(FIFO_WR_DATA_O_BASE,a)



