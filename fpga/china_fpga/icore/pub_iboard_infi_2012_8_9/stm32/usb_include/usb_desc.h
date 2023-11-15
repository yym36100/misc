
#ifndef __USB_DESC_H
#define __USB_DESC_H


#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define HID_DESCRIPTOR_TYPE                     0x21
#define CUSTOMHID_SIZ_HID_DESC                  0x09
#define CUSTOMHID_OFF_HID_DESC                  0x12

#define CUSTOMHID_SIZ_DEVICE_DESC               18
#define CUSTOMHID_SIZ_CONFIG_DESC               41
#define CUSTOMHID_SIZ_REPORT_DESC               23
#define CUSTOMHID_SIZ_STRING_LANGID             4
#define CUSTOMHID_SIZ_STRING_VENDOR             16
#define CUSTOMHID_SIZ_STRING_PRODUCT            34
#define CUSTOMHID_SIZ_STRING_SERIAL             22

#define STANDARD_ENDPOINT_DESC_SIZE             0x09


extern const unsigned char CustomHID_DeviceDescriptor[CUSTOMHID_SIZ_DEVICE_DESC];
extern const unsigned char CustomHID_ConfigDescriptor[CUSTOMHID_SIZ_CONFIG_DESC];
extern const unsigned char CustomHID_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC];
extern const unsigned char CustomHID_StringLangID[CUSTOMHID_SIZ_STRING_LANGID];
extern const unsigned char CustomHID_StringVendor[CUSTOMHID_SIZ_STRING_VENDOR];
extern const unsigned char CustomHID_StringProduct[CUSTOMHID_SIZ_STRING_PRODUCT];
extern unsigned char CustomHID_StringSerial[CUSTOMHID_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */

