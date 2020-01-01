/**
 *
 * @file    ema_usb_msg.h
 *
 * @brief   This module defines the EMA USB message struct type for USB interface using.
 *
 * @author  Kevin Chang
 * @version $Id: ema_usb_msg.h 14361 2008-09-24 10:56:18Z kevin.chang $
 * 
 */
#ifndef __EMA_USB_MSG_H__
#define __EMA_USB_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_usb_itf.h"
#include "usb_cdc_api.h"
#include "usb_cdc_fl.h"




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef struct
{
  esl_UsbDev_e usbDev;
  esl_UsbDevConfig_t usbDevConfig;
}ema_UsbOpen_t;

typedef struct{
  bool              usbCdcNotifyType;
	psSignalCb_t      usbCdcSigHandler;
}ema_UsbCdcRegNotify_t;

typedef struct{
  u32 usbPipeType;
	u8* usbDataIn;
  u16 usbDataSize;
}ema_UsbCdcWriteData_t;

typedef struct{
	u8* usbDataOut;
  u16 usbDataSize;
}ema_UsbCdcReadData_t;

typedef struct{
  esl_UsbNotifyType_e usbNotifyType;
	esl_UsbNotifyCb_t  usbNotifyCb;
}ema_UsbRegNotify_t;

typedef struct
{
	ema_TransType_t     TransType;
	esl_UsbCb_t         *pUsbDoneCB;
	union
	{
		ema_UsbOpen_t         usbOpenCmd;
    ema_UsbRegNotify_t         usbRegNotifyCmd;
    ema_UsbCdcRegNotify_t      usbCdcRegNotifyCmd;
    ema_UsbCdcWriteData_t      usbCdcWriteDataCmd;
    ema_UsbCdcReadData_t       usbCdcReadDataCmd;
	} cmdType;
} ema_UsbCmd_t;

typedef struct
{
	u16                 prim;
	u16                 sender;
	ema_TransType_t     TransType;
	ema_ErrCode_e        errorStatus;
} ema_UsbRsp_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_USB_MSG_H__ */




