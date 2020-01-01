#include "type.h"

typedef struct _USB_DEVICE_DESC {
U8* pDeviceDescriptor;
U16 DeviceDescriptorSize;
U8* pConfigDescriptor;
U16 ConfigDescriptorSize;
U8* pOtherSpeedConfigDescriptor;
U16 OtherSpeedConfigDescriptorSize;
U8* pStrDescriptor0; //Unicode
U16 StrDescriptorSize0;
U8* pStrDescriptor1; //Manufacturer String Descriptor
U16 StrDescriptorSize1;
U8* pStrDescriptor2; //Product String Descriptor
U16 StrDescriptorSize2;
U8* pStrDescriptor3; //
U16 StrDescriptorSize3;
U8* pStrDescriptor4; // UVC Video Control Interface String Descriptor
U16 StrDescriptorSize4;
U8* pStrDescriptor5; //UVC Video Stream Interface String Descriptor
U16 StrDescriptorSize5;
} USB_DEVICE_DESC;


USB_DEVICE_DESC volatile	*USB_Dscr;
void USB_FUNC_INIT(USB_DEVICE_DESC* ep_desc);
