#ifndef _MS_MDL_USB_PUB_H
#define _MS_MDL_USB_PUB_H

typedef enum
{
    /* Virtual COM */
    EVENT_USBCDC_READ_DONE=0,             ///< Reading data from PC is completed
    EVENT_USBCDC_WRITE_DONE,            ///< Writing data to PC is completed
    EVENT_USBCDC_CONNECTED,             ///< Virtual COM port is connected to PC
    EVENT_USBCDC_DISCONNECTED,
    EVENT_USBCDC_SET_LINESTATE,
    EVENT_USBCDC_SET_LINECODING,

} USBFUNCDCEVENT_e;

s32 MdlUsbMainCdcCallbackRegister(u8 nUsbEvent, void *pfUsbFun);
s32 MdlUsbMainCdcCallbackUnRegister(u8 nUsbEvent);
void MdlUsbMainCdcRead(u8* pRbuffer, u16* pwAmount, u16 nMax);
s32 MdlUsbMainCdcWrite(u8 *pWbuffer, u16 nLen);
s32 MdlUsbMainCdcSerialStateNotifify(u16 nCdcNotification);
void MdlUsbMainCdcGetLineCoding(void* pLineCoding);
void MdlUsbMainTaskInit(void);
void MdlUsbMainTaskParseMsg(void *pMessage);
void MdlUsbMainPauseUsb(void);
void MdlUsbMainResumeUsb(void);
#endif  //_MS_MDL_USB_PUB_H
