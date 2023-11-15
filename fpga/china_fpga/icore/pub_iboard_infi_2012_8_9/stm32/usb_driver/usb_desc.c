


#include "..\usb_include\usb_desc.h"



//�豸������
const unsigned char CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC] =
{
	0x12,                       //���������豸�����������Ӧ���ֽ�����18�ֽ�
	USB_DEVICE_DESCRIPTOR_TYPE, //�������豸���������궨��Ϊ01����DEVICE
	0x00,                   //0x0200����USB2.0Э��
	0x02,
	0x00,                   //�����
	0x00,                   //������룬�������Ϊ0���������ҲΪ0
	0x00,                       //�豸��ʹ��Э��
	0x40,                       //�˵�0���������˵�0�������Ϊ�����Щ������Ϣ��һ��64�ֽڻ����������׵�ַҪ���ȶ���ã�
	0xFE,                   //����ID��0xFFE�����˵��ӹ̶�ID
	0x0F,
	0x01,                   //��ƷID������Ϊ0x0001������һ��
	0x00,
	0x01,                   //�豸�汾�ţ�ͬ������Ϊ0x0001
	0x00,
	1,                      //�������̵��ַ�������
	2,                      //������Ʒ���ַ�������
	3,                      //��Ʒ���к��ַ�������
	0x01
};
//����������
const unsigned char CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC] =
{
	/************** ���������� ****************/
	0x09,
	USB_CONFIGURATION_DESCRIPTOR_TYPE,
	CUSTOMHID_SIZ_CONFIG_DESC,

	0x00,
	0x01,      //�ӿ���Ϊ1����λ��ǰ
	0x01,      //����Ϊ1
	0x00,      //�����ַ�������������û����0
	0x80,      //���߹���
	0x32,      //������100MA��ÿ��λ����2MA��������������50��0x32��
	/************** �ӿ������� ****************/
	/* 09 */
	0x09,     /* bLength: Interface Descriptor size */
	USB_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType: Interface descriptor type */
	0x00, /* bInterfaceNumber: Number of Interface */    //�ӿڱ�ţ���һ���ӿڣ����Ϊ0
	0x00, /* bAlternateSetting: Alternate setting */    //��һ���ӿڣ�û�н���ӿ�
	0x02, /* bNumEndpoints */    //2����0�˵㣬1IN��OUT
	0x03, /* bInterfaceClass: HID */    //�ӿ��ࣺHID
	0x00, /* bInterfaceSubClass : 1=BOOT, 0=no boot */    //�Զ���HID����
	0x00, /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */    //�Զ���HIDЭ��
	0, /* iInterface: Index of string descriptor */       //�����ַ�������������û����0
	/******************** Descriptor of Custom HID HID ********************/
	/* 18 */
	0x09,     /* bLength: HID Descriptor size */
	HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
	0x10, /* bcdHID: HID Class Spec release number */    //HIDЭ��1.1
	0x01,
	0x21, /* bCountryCode: Hardware target country */    //�豸���ù��Ҵ��룬������0x21��������0��δ֪
	0x01, /* bNumDescriptors: Number of HID class descriptors to follow */    //�¼�����������Ŀ������ֻ��һ������������
	0x22, /* bDescriptorType */    //�¼������������ͣ�Ϊ���������������Ϊ0x22
	CUSTOMHID_SIZ_REPORT_DESC, /* wItemLength: Total length of Report descriptor */
	0x00,
	/******************** Descriptor of Custom HID endpoints ******************/
	/* 27 */
	0x07,      /* bLength: Endpoint Descriptor size */
	USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */

	0x81, /* bEndpointAddress: Endpoint Address (IN) */     //IN�˵��ַ
	0x03, /* bmAttributes: Interrupt endpoint */     //�˵����ͣ��ж�
	0x40, /* wMaxPacketSize: 64 Bytes max */     //�˵�1IN���͵�������С��1�ֽڣ����û������Ӧ��1�ֽ�Ϊ����ĵƣ�2�ֽ�Ϊ�Ƶ�״̬��
	0x00,
	0x01,      /* bInterval: Polling Interval (32 ms) */
	/* 34 */

	0x07,   /* bLength: Endpoint Descriptor size */
	USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: */
	/*	Endpoint descriptor type */
	0x01, /* bEndpointAddress: */  //EP1OUT�˵��ַ
	/*	Endpoint Address (OUT) */
	0x03,   /* bmAttributes: Interrupt endpoint */
	0x40, /* wMaxPacketSize: 64 Bytes max  */  //64�ֽ�
	0x00,
	0x01,   /* bInterval: Polling Interval (32 ms) */
	/* 41 */
};

const unsigned char CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] =
{
	0x05, 0x00,                                        // USAGE_PAGE(User define)
	0x09, 0x00,                // USAGE(User define)
	0xa1, 0x01,                // COLLECTION (Application)




	0x75, 0x08,                //   REPORT_SIZE (8)
	0x95, 0x40,                //   REPORT_COUNT (64)
	0x15, 0x00,                //   LOGICAL_MINIMUM (0)
	0x25, 0xFF,                //   LOGICAL_MAXIMUM (255)
	0x09, 0x00,                                        //   USAGE(User define)
	0x81, 0x02,                //   INPUT (Data,Var,Abs)


	0x09, 0x00,                                        //   USAGE(User define)
	0x91, 0x02,                //   OUTPUT (Data,Var,Abs)

	0xc0                           // END_COLLECTION
	//23
};


const unsigned char CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID] =
{
	CUSTOMHID_SIZ_STRING_LANGID,
	USB_STRING_DESCRIPTOR_TYPE,
	0x09,
	0x04
};

//�����ַ���
const unsigned char CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =
{
	CUSTOMHID_SIZ_STRING_VENDOR, /* Size of Vendor string */
	USB_STRING_DESCRIPTOR_TYPE, /* bDescriptorType*/
	/* Manufacturer: "STMicroelectronics" */
	0xc8, 0x54, //��
	0x14, 0x5c, //��
	0xe8, 0x6e, //��
	0x5a, 0x53, //��
	0x74, 0x51, //��
	0x35, 0x75, //��
	0x50, 0x5b //��
};

//�豸�ַ���
const unsigned char CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT] =
{
	CUSTOMHID_SIZ_STRING_PRODUCT,      /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,    /* bDescriptorType */
	'i', 0x00,
	'B', 0x00,
	'o', 0x00,
	'a', 0x00,
	'r', 0x00,
	'd', 0x00,
	' ', 0x00,
	'X', 0x00,
	'i', 0x00,
	'a', 0x00,
	'o', 0x00,
	'm', 0x00,
	'a', 0x00,
	'G', 0x00,
	'e', 0x00,
	'e', 0x00
};

//��Ʒ���к�
unsigned char CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL] =
{
	CUSTOMHID_SIZ_STRING_SERIAL,       /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,    /* bDescriptorType */

	0x32, 0x00, //2
	0x30, 0x00, //0
	0x31, 0x00, //1
	0x31, 0x00, //1
	0x2d, 0x00, //-
	0x30, 0x00, //0
	0x34, 0x00, //4
	0x2d, 0x00, //-
	0x31, 0x00, //1
	0x39, 0x00, //9
};



