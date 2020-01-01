#ifndef _MS_DRV_USB_PUB_API_H
#define _MS_DRV_USB_PUB_API_H

#include "vm_types.ht"

void DrvUsbUtilitySelClass(U8 nDevMode);
void DrvUsbUtilitySetSensorId(U8 nSensorId);
S32 DrvUsbUtilitySwitchOffUSB(void);
void DrvUsbUtilityCloseUtmi(void);
S32 DrvUsbUtilitySwitchOnUSB(U8 nDevMode);
void DrvUsbUtilityReadCdcRxBuffer(U8* pRBuffer, U16* pwAmount, U16 nMax);
S32 DrvUsbUtilityWriteCdcTxBuffer(U8 *pWbuffer, U16 nLen);
S32 DrvUsbUtilityWriteCdcSerialStateNotify(U16 nNotification);
void DrvUsbUtilityResetUsbConnectStatus(void);
u8 DrvUsbUtilityGetUsbConnectStatus(void);
u8 DrvUsbUtilityGetUsbClassMode(void);
void DrvUsbUtilityGetCdcLineCoding(void* pLineCoding);
U8 DrvUsbUtilityGetCdcLineState(void);
S32 DrvUsbUtilityDetUsbCallbackRegister(void *pfUsbFun);
void DrvUsbUtilityDetUsbCallbackUnRegister(void);
S32 DrvUsbUtilityCommUsbCallbackRegister(U8 nUsbEvent, void *pfUsbFun);
S32 DrvUsbUtilityCommUsbCallbackUnRegister(U8 nUsbEvent);
S32 DrvUsbUtilityCdcMuxUsbCallbackRegister(U8 nUsbEvent, void *pfUsbFun);
S32 DrvUsbUtilityCdcMuxUsbCallbackUnRegister(U8 nUsbEvent);
S32 DrvUsbUtilityCdcUsbCallbackRegister(U8 nUsbEvent, void *pfUsbFun);
S32 DrvUsbUtilityCdcUsbCallbackUnRegister(U8 nUsbEvent);
void DrvUsbUtilityCheckCdcOpenEvent(void);
s32 DrvUsbUtilityBufferAlloc(u8 nDevMode);
void DrvUsbUtilityBufferDealloc(u8 nDevMode);
void DrvUsbUtilityFlagDestroy(void);
#ifdef ENABLE_PictBridge
S32 DrvUsbUtilityPbUsbCallbackRegister(U8 nUsbEvent, void *pfUsbFun);
#endif
void usb_cdc_read(void);
void cdcConnPortAvailableRsp(vm_msg_t *Msg);
void cdcMuxConnOpenReq(vm_msg_t *Msg);
void dcdon_data_receive(vm_msg_t  *Msg);
void cdcReceiveFcmDataBlockReq(vm_msg_t  *Msg);
void cdcReceiveFcmResumeFlowInd(void);
void cdcReceiveFcmCloseFlowInd(vm_msg_t  *Msg);
void cdcReceiveFcmOpenFlowInd(vm_msg_t  *Msg);
S32  DrvUsbUtilityGenieUsbCallbackRegister(U8 nUsbEvent, void *pfUsbFun);
S32  DrvUsbUtilityGenieUsbCallbackUnRegister(U8 nUsbEvent);
void DrvUsbUtilityReadGenieRxBuffer(U8* pRBuffer, U16* pwAmount, U16 nMax);
S32  DrvUsbUtilityWriteGenieTxBuffer(U8 *pWbuffer, U16 nLen);
void DrvUSbSetDebugPort(U8 option);
void Drv_usb_enable_composite(void);
void Drv_usb_disable_composite(void);
void DrvUsbUtilityPauseUsb(void);
void DrvUsbUtilityResumeUsb(void);
void DrvUsbUtilityCheckGenieOpenEvent(void);
#endif  //_MS_DRV_USB_PUB_API_H
