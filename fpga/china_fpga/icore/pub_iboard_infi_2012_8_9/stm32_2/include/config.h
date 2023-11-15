//config.h


#ifndef __config_h__
#define __config_h__


//-----------------Include files-------------------------//

//----------------- DEFINE ------------------------------//


#define BUFFER_SIZE	200
#define PI	3.14159265
#define	E	2.718281828

#define CPU_CLK	72000000.
#define ARB_CLK	100000000.



#define	SIMSUN16_ADDRESS_BASE	0
#define	SIMSUN16F_ADDRESS_BASE	65536*5

#define SIMSUN12_ADDRESS_BASE	65536*10

#define SIMHEI24_ADDRESS_BASE	65536*15

#define LOGO_ADDRESS_BASE		65536*24


#define TRUE	1
#define	FALSE	0

#define	END_FLAG	'\n'

#define	ON	1
#define	OFF	0



#define	RANGE_uHz	0
#define	RANGE_mHz	1
#define	RANGE_Hz	2
#define	RANGE_kHz	3
#define	RANGE_MHz	4


//DEBUG
//#define FONT_DEMO


#endif //__config_h__
