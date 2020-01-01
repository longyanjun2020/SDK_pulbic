/**
* @file    mmi_srv_usb.h
* @brief  This describes the service wrapper interface of USB
*             You can get USB status / register a CB to listen the USB event     
*
*/

#ifndef __MMI_SRV_USB_H__
#define __MMI_SRV_USB_H__


/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_usbsrv.h"

/*=============================================================*/
// Specific Service ListenerCallBack API
/*=============================================================*/
/** SrvUsbStoppedCB
@brief  The interface is the CB for USB stop indication.
           The event is USBSRV_EVT_SRV_STOP_IND

@param[out]     pThis             The pointer of Applet
*/
typedef void (*SrvUsbStoppedCB)(void *pThis);
/** SrvUsbBackToIdleCB
@brief  The interface is the CB for USB back to Idle indication(USB service state is idle state) . 
           The event is USBSRV_EVT_SRV_BACK_TO_IDLE

@param[out]     pThis             The pointer of Applet
*/
typedef void (*SrvUsbBackToIdleCB)(void *pThis);
/** SrvUsbPullOutCB
@brief  The interface is the CB for USB pull out indication when USB cable is not inserted.
           The event is USBSRV_EVT_USB_OUT

@param[out]     pThis             The pointer of Applet
*/
typedef void (*SrvUsbPullOutCB)(void *pThis);
/** SrvUsbStatusChangedCB
@brief  The interface is the CB for USB status changes indication when USB status is changed.
@         The event is USBSRV_EVT_USB_STATUS

@param[out]     pThis             The pointer of Applet
@param[out]     eUsbStatus    The USB status
                            MMI_USB_STATUS_NONE : USB cable is not connected.
                            MMI_USB_STATUS_UNKNOWN : USB cable is not checked yet (but connected). 
                            MMI_USB_STATUS_PCHOST : USB cable is attached for PC host 
                            MMI_USB_STATUS_CHARGING : USB cable is for charging only
                            MMI_USB_STATUS_PCHOST_CDC_MODEM : USB cable is for Communication Modem Device
                            MMI_USB_STATUS_PCHOST_CDC_SYNCTOOL : USB cable is for Communication Sync tool Device
                            MMI_USB_STATUS_PCHOST_CDC_TRACE : USB cable is for Communication Trace Device
                            MMI_USB_STATUS_PCHOST_MSC : USB cable is for Mass Storage
                            MMI_USB_STATUS_PCHOST_VDC :  USB cable is for Webcam
                            MMI_USB_STATUS_VBUS_USB_IN : For dual charger, to notify USB IN
                            MMI_USB_STATUS_VBUS_USB_OUT : For dual charger, to notify USB OUT
*/
typedef void (*SrvUsbStatusChangedCB)(void *pThis, MMI_USB_STATUS_E eUsbStatus); // usbmodel lisnter notify

/*=============================================================*/
// USB API - register a CB function
/*=============================================================*/
/**
SrvUsbSetStoppedCB
@brief  The interface of Service is to set CB to listen the USB Stop Ind. 
           When user safety removes USB device from PC(device) but cable is still connected to target(phone), this indication will be triggered.

@param[in]      pfnStatusCB         SrvUsbStoppedCB Call back function point is to info owner when USB is stopped.

@retval MAE_RET_SUCCESS       If successful.
@retval MAE_RET_FAILED        If an error happen.
@retval MAE_RET_OUT_OF_MEMORY       If malloc fail.
*/
MAE_Ret SrvUsbSetStoppedCB(SrvUsbStoppedCB pfnStatusCB);

/**
SrvUsbSetBackToIdleIndCB
@brief  The interface of Service is to set CB to listen the USB back to Idle Ind.

@param[in]      pfnStatusCB         SrvUsbBackToIdleCB Call back function point is to info owner when USB is closed (USB service state is idle state).

@retval MAE_RET_SUCCESS       If successful.
@retval MAE_RET_FAILED        If an error happen.
@retval MAE_RET_OUT_OF_MEMORY       If malloc fail.
*/
MAE_Ret SrvUsbSetBackToIdleIndCB(SrvUsbBackToIdleCB pfnStatusCB);

/**
SrvUsbSetPullOutCB
@brief  The interface of Service is to set CB to listen the USB plugged out Ind.
           It will be triggered when USB cable is not inserted.

@param[in]      pfnStatusCB         SrvUsbPullOutCB Call back function point is to info owner when USB is plugged out.

@retval MAE_RET_SUCCESS       If successful.
@retval MAE_RET_FAILED        If an error happen.
@retval MAE_RET_OUT_OF_MEMORY       If malloc fail.
*/
MAE_Ret SrvUsbSetPullOutCB(SrvUsbPullOutCB pfnStatusCB);

/**
SrvUsbSetStatusIndCB
@brief  The interface of Service is to set CB to listen the USB status changes Ind. (MMI_USB_STATUS_E)

@param[in]      pfnStatusCB         SrvUsbSetStatusIndCB Call back function point is to info owner when USB status is changed.

@retval MAE_RET_SUCCESS       If successful.
@retval MAE_RET_FAILED        If an error happen.
@retval MAE_RET_OUT_OF_MEMORY       If malloc fail.
*/
__SLDPM_FREE__ MAE_Ret SrvUsbSetStatusChangedCB(SrvUsbStatusChangedCB pfnStatusCB);

/*=============================================================*/
// USB API - get/set USB status function
/*=============================================================*/
/**
SrvUsbOpenSession
@brief  The interface of Service is to open session to USB Service.
           Pair with SrvUsbCloseSession()

@param[in]      eUsbDev    The USB device you want to open
                              MMI_USB_NONE : No USB function
                              MMI_USB_CDC : Communication Device Class (Modem virtual COM port)
                              MMI_USB_MSC : Mass Storage Device Class
                              MMI_USB_MTP : Media Transfer Protocol
                              MMI_USB_PBD : Picture Bridge Device
                              MMI_USB_VDC : Video Class used for PC camera service. It's for single camera
                              MMI_USB_VDC_MAIN : Video Class used for main PC camera service. It's for dual camera
                              MMI_USB_VDC_SUB : Video Class used for SUB PC camera service It's for dual camera
                              MMI_USB_OTG : OTG Host

@param[out]     pfnResultCB		SrvUsbResultCB is the CB for USB service return value. (TRUE means ok, FALSE is failed)

@retval MAE_RET_SUCCESS       If successful.
@retval MAE_RET_FAILED        If an error happen.
*/
MAE_Ret SrvUsbOpenSession(MMI_USB_DEVICE_E eUsbDev, SrvUsbResultCB pfnResultCB);

/**
SrvUsbCloseSession
@brief  The interface of Service is to close session to USB Service.
           Pair with SrvUsbOpenSession()

@param[in]      pfnResultCB         SrvUsbResultCB is the CB for USB service return value. (TRUE means ok, FALSE is failed)

@retval MAE_RET_SUCCESS       If successful.
@retval MAE_RET_FAILED        If an error happen.
*/
MAE_Ret SrvUsbCloseSession(SrvUsbResultCB pfnResultCB);

/**
SrvUsbOpen
@brief  The interface of Service is to send USB open request with DeviceType to USB Service.

@param[in]      eUsbDev    The USB device you want to open
                              MMI_USB_NONE : No USB function
                              MMI_USB_CDC : Communication Device Class (Modem virtual COM port)
                              MMI_USB_MSC : Mass Storage Device Class
                              MMI_USB_MTP : Media Transfer Protocol
                              MMI_USB_PBD : Picture Bridge Device
                              MMI_USB_VDC : Video Class used for PC camera service. It's for single camera
                              MMI_USB_VDC_MAIN : Video Class used for main PC camera service. It's for dual camera
                              MMI_USB_VDC_SUB : Video Class used for SUB PC camera service It's for dual camera
                              MMI_USB_OTG : OTG Host

@param[out]     peUsbSrvRetVal		  point to USB service return vaule
                              MMI_USB_OK : Complete successfully
                              MMI_USB_FAIL : Common failed
                              MMI_USB_PARAM_ERROR : The input parameter is invalid
                              MMI_USB_MEM_ALLOC_ERROR : Can not allocate memory from OS
                              MMI_USB_REJECT : Request rejected because of other function's confliction.
                              MMI_USB_ABORT : Request aborted because of incorrect sequence.
                              MMI_USB_TIMEOUT : Request no response timeout, this error is returned by call back function.

@param[in]      pfnResultCB      SrvUsbResultCB is the CB for USB service return value. (TRUE means ok, FALSE is failed)

@retval MAE_RET_SUCCESS       If successful.
@retval MAE_RET_FAILED        If an error happen.
@retval MAE_RET_OUT_OF_MEMORY       If malloc fail.
@retval MAE_RET_BAD_PARAM   If parameter fail.
*/
MAE_Ret SrvUsbOpen(MMI_USB_DEVICE_E eUsbDev, MMI_USB_RESULT_E *peUsbSrvRetVal, SrvUsbResultCB pfnResultCB);

/**
SrvUsbClose
@brief  The interface of Service is to send all devices close request to USB Service.

@param[out]     peUsbSrvRetVal  point to USB service return value
                              MMI_USB_OK : Complete successfully
                              MMI_USB_FAIL : Common failed
                              MMI_USB_PARAM_ERROR : The input parameter is invalid
                              MMI_USB_MEM_ALLOC_ERROR : Can not allocate memory from OS
                              MMI_USB_REJECT : Request rejected because of other function's confliction.
                              MMI_USB_ABORT : Request aborted because of incorrect sequence.
                              MMI_USB_TIMEOUT : Request no response timeout, this error is returned by call back function.

@param[in]       pfnResultCB		SrvUsbResultCB is the CB for USB service return value. (TRUE means ok, FALSE is failed)

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_FAILED          If an error happen. (USB Srv is already terminated.)
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
@retval MAE_RET_BAD_PARAM   If parameter fail.
*/
MAE_Ret SrvUsbClose(MMI_USB_RESULT_E *peUsbSrvRetVal, SrvUsbResultCB pfnResultCB);

/**
SrvUsbSetSimPath
@brief  The interface of Service is to set which SIM to use. (Only for modem mode)

@param[in]      eSimPath        Set the SIM to SIM1 or SIM2 (USBSRV_SIM_PATH_SIM1 / USBSRV_SIM_PATH_SIM2)
@param[out]    pfnUsbSrvCb   SrvUsbResultCB is the CB for USB service return value. (TRUE means ok, FALSE is failed)

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
@retval MAE_RET_BAD_PARAM   If parameter fail.
*/
MAE_Ret SrvUsbSetSimPath(UsbSrvSimPath_e eSimPath, SrvUsbResultCB pfnUsbSrvCb);

/**
SrvUsbGetStatus
@brief  The interface of Service is to get USB cable connection status.

@param[out]     peUsbStatus         pointer to USB status get from Service
                              MMI_USB_STATUS_NONE : USB cable is not connected.
                              MMI_USB_STATUS_UNKNOWN : USB cable is not checked yet (but connected). 
                              MMI_USB_STATUS_PCHOST : USB cable is attached for PC host 
                              MMI_USB_STATUS_CHARGING : USB cable is for charging only
                              MMI_USB_STATUS_PCHOST_CDC_MODEM : USB cable is for Communication Modem Device
                              MMI_USB_STATUS_PCHOST_CDC_SYNCTOOL : USB cable is for Communication Sync tool Device
                              MMI_USB_STATUS_PCHOST_CDC_TRACE : USB cable is for Communication Trace Device
                              MMI_USB_STATUS_PCHOST_MSC : USB cable is for Mass Storage
                              MMI_USB_STATUS_PCHOST_VDC :  USB cable is for Webcam
                              MMI_USB_STATUS_VBUS_USB_IN : For dual charger, to notify USB IN
                              MMI_USB_STATUS_VBUS_USB_OUT : For dual charger, to notify USB OUT

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
@retval MAE_RET_BAD_PARAM   If parameter fail.
*/
MAE_Ret SrvUsbGetStatus(MMI_USB_STATUS_E *peUsbStatus);

/**
SrvUsbEnableReq
@brief  The interface of Service is to enable or disable USB service.

@param[in]      bIsEnabled          Enable or disable USB service. (TRUE is for enabled and FALSE is disabled)

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_FAILED          If an error happen. (IUSBSRV is NULL)
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvUsbEnableReq(boolean bIsEnabled);

/**
SrvUsbEnableReqInCharging
@brief  The interface of Service is to enable USB service in charging mode .

@param[in]      bIsEnabledInCharging        This flag can be set for enable USB service in charging mode or not. (TRUE is for enabled and FALSE is disabled)

@retval MAE_RET_SUCCESS          If successful.
@retval MAE_RET_FAILED           If an error happen. (IUSBSRV is NULL)
@retval MAE_RET_OUT_OF_MEMORY    If malloc fail.
*/
MAE_Ret SrvUsbEnableReqInCharging(boolean bIsEnabledInCharging);

/**
SrvUsbFlushAppletStack
@brief  The interface of Service is to set the selected menu ID and flush the APP stack.
           Notify USBSrv to flush all launched applet before establishing USB connection.(Only use for USB APP)

@param[in]      nUSBFuncID      The selected menu ID of the USB connection menu
@param[out]    pusb_ret           pointer to USB result get from Service
                              MMI_USB_OK : Complete successfully
                              MMI_USB_FAIL : Common failed
                              MMI_USB_PARAM_ERROR : The input parameter is invalid
                              MMI_USB_MEM_ALLOC_ERROR : Can not allocate memory from OS
                              MMI_USB_REJECT : Request rejected because of other function's confliction.
                              MMI_USB_ABORT : Request aborted because of incorrect sequence.
                              MMI_USB_TIMEOUT : Request no response timeout, this error is returned by call back function.

@retval MAE_RET_SUCCESS         If successful.(checked by pusb_ret)
@retval MAE_RET_FAILED          If an error happen.(checked by pusb_ret)
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
@retval MAE_RET_BAD_PARAM   If parameter fail.
*/
MAE_Ret SrvUsbFlushAppletStack(u32 nUSBFuncID, MMI_USB_RESULT_E *pusb_ret);

#endif //__MMI_SRV_USB_H__
