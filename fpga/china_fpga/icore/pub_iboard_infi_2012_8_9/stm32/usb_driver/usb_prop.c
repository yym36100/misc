/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_prop.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : All processings related to Custom HID Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "..\usb_include\usb_lib.h"
#include "..\usb_include\usb_prop.h"
#include "..\usb_include\usb_desc.h"
#include "..\usb_include\usb_pwr.h"







/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
unsigned long int ProtocolValue;

/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table =
{
	EP_NUM, //��2�����������0�˵���Ŀ
	1   //����
};


//�ṹ���Ա�ܶ��ǻص��������ص���������������
DEVICE_PROP Device_Property =      //USB�ں˽����û�����Ĺ���
{
	CustomHID_init,
	CustomHID_Reset,
	CustomHID_Status_In,
	CustomHID_Status_Out,
	CustomHID_Data_Setup,
	CustomHID_NoData_Setup,
	CustomHID_Get_Interface_Setting,
	CustomHID_GetDeviceDescriptor,
	CustomHID_GetConfigDescriptor,
	CustomHID_GetStringDescriptor,
	0,
	0x40 /*MAX PACKET SIZE*/
};
USER_STANDARD_REQUESTS User_Standard_Requests = //��ȡ���б�׼�������û�������ȡ������������⣩
{
	CustomHID_GetConfiguration,
	CustomHID_SetConfiguration,
	CustomHID_GetInterface,
	CustomHID_SetInterface,
	CustomHID_GetStatus,
	CustomHID_ClearFeature,
	CustomHID_SetEndPointFeature,
	CustomHID_SetDeviceFeature,
	CustomHID_SetDeviceAddress
};
//�������������Ǻͱ�����������Ӧ��
ONE_DESCRIPTOR Device_Descriptor =
{
	(unsigned char*)CustomHID_DeviceDescriptor,
	CUSTOMHID_SIZ_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor =
{
	(unsigned char*)CustomHID_ConfigDescriptor,
	CUSTOMHID_SIZ_CONFIG_DESC
};

ONE_DESCRIPTOR CustomHID_Report_Descriptor =
{
	(unsigned char*)CustomHID_ReportDescriptor,
	CUSTOMHID_SIZ_REPORT_DESC
};

ONE_DESCRIPTOR CustomHID_Hid_Descriptor =
{
	(unsigned char*)CustomHID_ConfigDescriptor + CUSTOMHID_OFF_HID_DESC,
	CUSTOMHID_SIZ_HID_DESC
};

ONE_DESCRIPTOR String_Descriptor[4] =
{
	{ (unsigned char*)CustomHID_StringLangID, CUSTOMHID_SIZ_STRING_LANGID },
	{ (unsigned char*)CustomHID_StringVendor, CUSTOMHID_SIZ_STRING_VENDOR },
	{ (unsigned char*)CustomHID_StringProduct, CUSTOMHID_SIZ_STRING_PRODUCT },
	{ (unsigned char*)CustomHID_StringSerial, CUSTOMHID_SIZ_STRING_SERIAL }
};

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


//�ṹ���Ա������Ӧ�ص�����
/*******************************************************************************
* Function Name  : CustomHID_init.
* Description    : Custom HID init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CustomHID_init(void)
{
	/* Update the serial number string descriptor with the data from the unique
	   ID*/
	Get_SerialNum();

	pInformation->Current_Configuration = 0;
	/* Connect the device */
	PowerOn();
	/* USB interrupts initialization */
	_SetISTR(0);         /* clear pending interrupts */
	wInterrupt_Mask = IMR_MSK;
	_SetCNTR(wInterrupt_Mask); /* set interrupts mask */

	bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : CustomHID_Reset.
* Description    : Custom HID reset routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CustomHID_Reset(void)
{
	/* Set Joystick_DEVICE as not configured */
	pInformation->Current_Configuration = 0;
	pInformation->Current_Interface = 0; /*the default Interface*/

	/* Current Feature initialization */
	pInformation->Current_Feature = CustomHID_ConfigDescriptor[7];

	SetBTABLE(BTABLE_ADDRESS);

	/* Initialize Endpoint 0 */
	SetEPType(ENDP0, EP_CONTROL);
	SetEPTxStatus(ENDP0, EP_TX_STALL);
	SetEPRxAddr(ENDP0, ENDP0_RXADDR);
	SetEPTxAddr(ENDP0, ENDP0_TXADDR);
	Clear_Status_Out(ENDP0);
//  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
	SetEPRxCount(ENDP0, 64);
	SetEPRxValid(ENDP0);

	/* Initialize Endpoint 1 */
	SetEPType(ENDP1, EP_INTERRUPT);
	SetEPTxAddr(ENDP1, ENDP1_TXADDR);
	SetEPRxAddr(ENDP1, ENDP1_RXADDR);
	SetEPTxCount(ENDP1, 64);
	SetEPRxCount(ENDP1, 64);
	SetEPRxStatus(ENDP1, EP_RX_VALID);
	SetEPTxStatus(ENDP1, EP_TX_NAK);

	bDeviceState = ATTACHED;

	/* Set this device to response on default address */
	SetDeviceAddress(0);
}
/*******************************************************************************
* Function Name  : CustomHID_SetConfiguration.
* Description    : Udpade the device state to configured and command the ADC
*                  conversion.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CustomHID_SetConfiguration(void)
{
	if (pInformation->Current_Configuration != 0) {
		/* Device configured */
		bDeviceState = CONFIGURED;
	}
}
/*******************************************************************************
* Function Name  : CustomHID_SetConfiguration.
* Description    : Udpade the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CustomHID_SetDeviceAddress(void)
{
	bDeviceState = ADDRESSED;
}
/*******************************************************************************
* Function Name  : CustomHID_Status_In.
* Description    : Joystick status IN routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CustomHID_Status_In(void)
{
}

/*******************************************************************************
* Function Name  : CustomHID_Status_Out
* Description    : Joystick status OUT routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CustomHID_Status_Out(void)
{
}

/*******************************************************************************
* Function Name  : CustomHID_Data_Setup
* Description    : Handle the data class specific requests.
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT CustomHID_Data_Setup(unsigned char RequestNo)
{
	unsigned char *(*CopyRoutine)(unsigned short int);

	CopyRoutine = NULL;

	if ((RequestNo == GET_DESCRIPTOR)
	    && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
	    && (pInformation->USBwIndex0 == 0)) {
		if (pInformation->USBwValue1 == REPORT_DESCRIPTOR) {
			CopyRoutine = CustomHID_GetReportDescriptor;
		}else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE) {
			CopyRoutine = CustomHID_GetHIDDescriptor;
		}
	} /* End of GET_DESCRIPTOR */
	  /*** GET_PROTOCOL ***/
	else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
		 && RequestNo == GET_PROTOCOL) {
		CopyRoutine = CustomHID_GetProtocolValue;
	}

	if (CopyRoutine == NULL) {
		return USB_UNSUPPORT;
	}

	pInformation->Ctrl_Info.CopyData = CopyRoutine;
	pInformation->Ctrl_Info.Usb_wOffset = 0;
	(*CopyRoutine)(0);
	return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : CustomHID_NoData_Setup
* Description    : handle the no data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT CustomHID_NoData_Setup(unsigned char RequestNo)
{
	if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
	    && (RequestNo == SET_PROTOCOL)) {
		return CustomHID_SetProtocol();
	}else  {
		return USB_UNSUPPORT;
	}
}

/*******************************************************************************
* Function Name  : CustomHID_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
unsigned char *CustomHID_GetDeviceDescriptor(unsigned short int Length)
{
	return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
* Function Name  : CustomHID_GetConfigDescriptor.
* Description    : Gets the configuration descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
unsigned char *CustomHID_GetConfigDescriptor(unsigned short int Length)
{
	return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
* Function Name  : CustomHID_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
unsigned char *CustomHID_GetStringDescriptor(unsigned short int Length)
{
	unsigned char wValue0 = pInformation->USBwValue0;
	if (wValue0 > 4) {
		return NULL;
	}else  {
		return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
	}
}

/*******************************************************************************
* Function Name  : CustomHID_GetReportDescriptor.
* Description    : Gets the HID report descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
unsigned char *CustomHID_GetReportDescriptor(unsigned short int Length)
{
	return Standard_GetDescriptorData(Length, &CustomHID_Report_Descriptor);
}

/*******************************************************************************
* Function Name  : CustomHID_GetHIDDescriptor.
* Description    : Gets the HID descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
unsigned char *CustomHID_GetHIDDescriptor(unsigned short int Length)
{
	return Standard_GetDescriptorData(Length, &CustomHID_Hid_Descriptor);
}

/*******************************************************************************
* Function Name  : CustomHID_Get_Interface_Setting.
* Description    : tests the interface and the alternate setting according to the
*                  supported one.
* Input          : - Interface : interface number.
*                  - AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : USB_SUCCESS or USB_UNSUPPORT.
*******************************************************************************/
RESULT CustomHID_Get_Interface_Setting(unsigned char Interface, unsigned char AlternateSetting)
{
	if (AlternateSetting > 0) {
		return USB_UNSUPPORT;
	}else if (Interface > 0) {
		return USB_UNSUPPORT;
	}
	return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : CustomHID_SetProtocol
* Description    : Joystick Set Protocol request routine.
* Input          : None.
* Output         : None.
* Return         : USB SUCCESS.
*******************************************************************************/
RESULT CustomHID_SetProtocol(void)
{
	unsigned char wValue0 = pInformation->USBwValue0;
	ProtocolValue = wValue0;
	return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : CustomHID_GetProtocolValue
* Description    : get the protocol value
* Input          : Length.
* Output         : None.
* Return         : address of the protcol value.
*******************************************************************************/
unsigned char *CustomHID_GetProtocolValue(unsigned short int Length)
{
	if (Length == 0) {
		pInformation->Ctrl_Info.Usb_wLength = 1;
		return NULL;
	}else  {
		return (unsigned char*)(&ProtocolValue);
	}
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
	unsigned long int Device_Serial0, Device_Serial1, Device_Serial2;

	Device_Serial0 = *(unsigned long int*)(0x1FFFF7E8);
	Device_Serial1 = *(unsigned long int*)(0x1FFFF7EC);
	Device_Serial2 = *(unsigned long int*)(0x1FFFF7F0);

	if (Device_Serial0 != 0) {
		CustomHID_StringSerial[2] = (unsigned char)(Device_Serial0 & 0x000000FF);
		CustomHID_StringSerial[4] = (unsigned char)((Device_Serial0 & 0x0000FF00) >> 8);
		CustomHID_StringSerial[6] = (unsigned char)((Device_Serial0 & 0x00FF0000) >> 16);
		CustomHID_StringSerial[8] = (unsigned char)((Device_Serial0 & 0xFF000000) >> 24);

		CustomHID_StringSerial[10] = (unsigned char)(Device_Serial1 & 0x000000FF);
		CustomHID_StringSerial[12] = (unsigned char)((Device_Serial1 & 0x0000FF00) >> 8);
		CustomHID_StringSerial[14] = (unsigned char)((Device_Serial1 & 0x00FF0000) >> 16);
		CustomHID_StringSerial[16] = (unsigned char)((Device_Serial1 & 0xFF000000) >> 24);

		CustomHID_StringSerial[18] = (unsigned char)(Device_Serial2 & 0x000000FF);
		CustomHID_StringSerial[20] = (unsigned char)((Device_Serial2 & 0x0000FF00) >> 8);
//     CustomHID_StringSerial[22] = (unsigned char)((Device_Serial2 & 0x00FF0000) >> 16);
//     CustomHID_StringSerial[24] = (unsigned char)((Device_Serial2 & 0xFF000000) >> 24);
	}
}
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
