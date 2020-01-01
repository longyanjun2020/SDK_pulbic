#ifndef __MMI_USBAPP_ID_H__
#define __MMI_USBAPP_ID_H__

typedef enum
{
    USB_WND_CONNECT_MENU = WND_ID_APP_BASE,
    USB_WND_DUALSIM,

} UsbAppWndId_e;

typedef enum
{
    USB_VIEW_BEGIN =APP_WDG_START,
    USB_SELECT_MENU_WDG,
    USB_VIEW_END
}UsbView_e;

typedef enum
{
	MNU_USB_MAIN_MAIN = 0,
	MNU_USB_MASS_STORAGE,
	MNU_USB_MODEM,
	MNU_USB_WEBCAM,
	MNU_USB_PC_SYNC_TOOL,
}UsbMenuId_e;

#endif //__MMI_USBAPP_ID_H__

