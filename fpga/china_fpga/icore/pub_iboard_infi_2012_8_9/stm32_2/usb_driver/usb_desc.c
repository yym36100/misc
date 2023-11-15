


#include "..\usb_include\usb_desc.h"



//设备描述符
const unsigned char CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC] =
{
	0x12,                       //对于主机设备描述符请求回应的字节数：18字节
	USB_DEVICE_DESCRIPTOR_TYPE, //类型是设备描述符，宏定义为01，即DEVICE
	0x00,                   //0x0200，即USB2.0协议
	0x02,
	0x00,                   //类代码
	0x00,                   //子类代码，如类代码为0，子类代码也为0
	0x00,                       //设备所使用协议
	0x40,                       //端点0最大包长（端点0可以理解为存放这些配置信息的一个64字节缓冲区，其首地址要事先定义好）
	0xFE,                   //厂商ID：0xFFE，博兴电子固定ID
	0x0F,
	0x01,                   //产品ID：设置为0x0001，即第一版
	0x00,
	0x01,                   //设备版本号，同样设置为0x0001
	0x00,
	1,                      //描述厂商的字符串索引
	2,                      //描述产品的字符串索引
	3,                      //产品序列号字符串索引
	0x01
};
//配置描述符
const unsigned char CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC] =
{
	/************** 配置描述符 ****************/
	0x09,
	USB_CONFIGURATION_DESCRIPTOR_TYPE,
	CUSTOMHID_SIZ_CONFIG_DESC,

	0x00,
	0x01,      //接口数为1，高位在前
	0x01,      //配置为1
	0x00,      //配置字符串索引，这里没有置0
	0x80,      //总线供电
	0x32,      //最大电流100MA，每单位电流2MA，所以这里设置50（0x32）
	/************** 接口描述符 ****************/
	/* 09 */
	0x09,     /* bLength: Interface Descriptor size */
	USB_INTERFACE_DESCRIPTOR_TYPE, /* bDescriptorType: Interface descriptor type */
	0x00, /* bInterfaceNumber: Number of Interface */    //接口编号，就一个接口，编号为0
	0x00, /* bAlternateSetting: Alternate setting */    //就一个接口，没有交替接口
	0x02, /* bNumEndpoints */    //2个非0端点，1IN与OUT
	0x03, /* bInterfaceClass: HID */    //接口类：HID
	0x00, /* bInterfaceSubClass : 1=BOOT, 0=no boot */    //自定义HID子类
	0x00, /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */    //自定义HID协议
	0, /* iInterface: Index of string descriptor */       //配置字符串索引，这里没有置0
	/******************** Descriptor of Custom HID HID ********************/
	/* 18 */
	0x09,     /* bLength: HID Descriptor size */
	HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
	0x10, /* bcdHID: HID Class Spec release number */    //HID协议1.1
	0x01,
	0x21, /* bCountryCode: Hardware target country */    //设备适用国家代码，美国是0x21，这里是0，未知
	0x01, /* bNumDescriptors: Number of HID class descriptors to follow */    //下级描述符的数目。我们只有一个报告描述符
	0x22, /* bDescriptorType */    //下级描述符的类型，为报告描述符，编号为0x22
	CUSTOMHID_SIZ_REPORT_DESC, /* wItemLength: Total length of Report descriptor */
	0x00,
	/******************** Descriptor of Custom HID endpoints ******************/
	/* 27 */
	0x07,      /* bLength: Endpoint Descriptor size */
	USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: */

	0x81, /* bEndpointAddress: Endpoint Address (IN) */     //IN端点地址
	0x03, /* bmAttributes: Interrupt endpoint */     //端点类型：中断
	0x40, /* wMaxPacketSize: 64 Bytes max */     //端点1IN发送的最大包大小是1字节（与用户程序对应，1字节为请求的灯，2字节为灯的状态）
	0x00,
	0x01,      /* bInterval: Polling Interval (32 ms) */
	/* 34 */

	0x07,   /* bLength: Endpoint Descriptor size */
	USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: */
	/*	Endpoint descriptor type */
	0x01, /* bEndpointAddress: */  //EP1OUT端点地址
	/*	Endpoint Address (OUT) */
	0x03,   /* bmAttributes: Interrupt endpoint */
	0x40, /* wMaxPacketSize: 64 Bytes max  */  //64字节
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

//厂商字符串
const unsigned char CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR] =
{
	CUSTOMHID_SIZ_STRING_VENDOR, /* Size of Vendor string */
	USB_STRING_DESCRIPTOR_TYPE, /* bDescriptorType*/
	/* Manufacturer: "STMicroelectronics" */
	0xc8, 0x54, //哈
	0x14, 0x5c, //尔
	0xe8, 0x6e, //滨
	0x5a, 0x53, //博
	0x74, 0x51, //兴
	0x35, 0x75, //电
	0x50, 0x5b //子
};

//设备字符串
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

//产品序列号
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



