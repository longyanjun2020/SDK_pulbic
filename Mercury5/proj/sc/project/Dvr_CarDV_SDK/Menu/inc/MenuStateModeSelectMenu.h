
#ifndef _MENU_STATE_MODE_SELECT_MENU_H_
#define _MENU_STATE_MODE_SELECT_MENU_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
//#include "ahc_gui.h"

/*===========================================================================
 * Enum define 
 *===========================================================================*/ 

#if (USB_MODE_SELECT_EN)
typedef enum {
    ITEMID_USB_MSDC_MODE = 1,
    ITEMID_USB_PCAM_MODE,
    ITEMID_USB_DSC_MODE,
    ITEMID_USB_DV_MODE
}USBMODEITEMID;

typedef enum {
    AHC_USB_MSDC_MODE = 1,
    AHC_USB_PCAM_MODE,
    AHC_USB_DSC_MODE,
    AHC_USB_DV_MODE,
    AHC_USB_MAX_MODE
}USBMODE;

#endif

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 
AHC_BOOL USBFunctionHandler(USBMODE selection);
AHC_BOOL StateSelectFuncUSBSelectMenuMode(void);
#endif //_MENU_STATE_MODE_SELECT_MENU_H_


