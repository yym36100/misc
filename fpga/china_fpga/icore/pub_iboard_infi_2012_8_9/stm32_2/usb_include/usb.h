#ifndef __USB_H__
#define __USB_H__


#define SEND_COMMAND_SIZE 

#define USBEN_OUTPUT    GPIOC->CRH.B.MODE12=0X3;\
							GPIOC->CRH.B.CNF12=0

#define	USBEN_ON	GPIOC->BSRR.B.SETIO12=1
#define USBEN_OFF	GPIOC->BSRR.B.CLRIO12=1

typedef  struct{

	int (* initialize)(void);
	int (* send_data)(unsigned char * /*send_buffer*/);
}SYS_USB_T;


extern SYS_USB_T usb;

#endif //__USB_H__
