#include "..\usb_include\usb_lib.h" //USBЭ��ͷ�ļ�
#include "..\usb_include\usb.h"
#include "..\usb_include\usb_desc.h"
#include "..\usb_include\usb_istr.h"
#include "..\usb_include\usb_prop.h"
#include "..\usb_include\usb_pwr.h"
#include "..\include\evtft.h"
#include "..\usb_include\usb_command.h"
#include <string.h>



static int initialize(void);
static int send_data(unsigned char *send_buffer);



SYS_USB_T usb = {
	.initialize = initialize,
	.send_data = send_data,
};


static int initialize(void)
{
	//��USBʱ��
	RCC->CFGR.B.USBPRE = 0; //PLLʱ��1.5��Ƶ��72/1.5=48��
	RCC->APB1ENR.B.USBEN = 1; //��USBʱ��
	//��usb�ж�
	NVIC->ISER1.B.USB_LP_CAN_RX0 = 1;
	NVIC->IPR6.B.USB_LP_CAN_RX0 = 0;

	USBEN_OUTPUT;
	USBEN_ON;

	USB_Init();

	return 0;
}

static int send_data(unsigned char *send_buffer)
{
	UserToPMABufferCopy(send_buffer, ENDP1_TXADDR, 64);
	SetEPTxCount(ENDP1, 64);
	SetEPTxValid(ENDP1);
	return 0;
}


int USB_LP_CAN_RX0_IRQHandler(void)
{
	USB_Istr();
	return 0;
}
