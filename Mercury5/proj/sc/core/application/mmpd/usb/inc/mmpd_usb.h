/// @ait_only
//==============================================================================
//
//  File        : mmpd_usb.h
//  Description : USB Control Driver Function
//  Author      : Hnas Liu
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_USB_H_
#define _MMPD_USB_H_

#include "mmp_usb_inc.h"

/** @addtogroup MMPD_USB
 *  @{
 */

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define MMPD_USB_PCSYNC_OUTFLAG_OFFSET_B             (0)
#define MMPD_USB_PCSYNC_INFLAG_OFFSET_B              (1)
#define MMPD_USB_PCSYNC_INSIZE_OFFSET_W              (2)
#define MMPD_USB_PCSYNC_OUTSIZE_OFFSET_W             (4)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

extern MMP_ERR  MMPD_USB_GetWriteFlag(MMP_UBYTE *USBIsWriting);
extern MMP_ERR  MMPD_USB_GetReadFlag(MMP_UBYTE *USBIsReading);

extern MMP_ERR  MMPD_USB_AdjustVref(MMP_ULONG Vref);
extern MMP_ERR  MMPD_USB_AdjustBiasCurrent(MMP_ULONG BiasCurrent);
extern MMP_ERR  MMPD_USB_AdjustSignal(MMP_ULONG TxCur, MMP_ULONG TxCurPlus,
                                      MMP_ULONG SqLevel);
extern MMP_ERR  MMPD_USB_RegisterCallback(MMP_USB_EVENT event,
                                          MMP_USB_Callback *callback);
extern MMP_ERR  MMPD_USB_GetMode(MMP_UBYTE *UsbCurMode);
extern MMP_ERR	MMPD_USB_SetMode(MMP_UBYTE ubMode);
extern MMP_ERR	MMPD_USB_StopDevice(void);
extern MMP_ERR	MMPD_USB_ConnectDevice(void);
extern MMP_ERR	MMPD_USB_SetMSDCBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize);
extern MMP_ERR  MMPD_USB_SetMSDCMaxUnits(MMP_UBYTE ubMaxUnitCnt);
extern MMP_ERR	MMPD_USB_SetCtlBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize);
extern MMP_ERR	MMPD_USB_SetPCSYNC_InBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize);
extern MMP_ERR	MMPD_USB_SetPCSYNC_OutBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize);
extern MMP_ERR	MMPD_USB_SetPCSYNC_HandShakeBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize);
extern MMP_ERR	MMPD_USB_GetPCSYNCInFlag(MMP_ULONG *ulFlag);
extern MMP_ERR	MMPD_USB_SetPCSYNCInFlag(MMP_ULONG ulFlag);
extern MMP_ERR	MMPD_USB_GetPCSYNCOutFlag(MMP_ULONG *ulFlag);
extern MMP_ERR	MMPD_USB_SetPCSYNCOutFlag(MMP_ULONG ulFlag);
extern MMP_ERR	MMPD_USB_GetPCSYNCInSize(MMP_ULONG *ulSize);
extern MMP_ERR	MMPD_USB_ReadPCSYNCInData(MMP_UBYTE *ubMemStart,MMP_ULONG ulSize);
extern MMP_ERR	MMPD_USB_WritePCSYNCOutData(MMP_UBYTE *ubMemStart,MMP_ULONG ulSize);
extern MMP_ERR	MMPD_USB_SetPCSYNCOutSize(MMP_ULONG ulSize);
extern MMP_ERR	MMPD_USB_SetPCamCompressBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize);
extern MMP_ERR	MMPD_USB_SetPCCamLineBuf(MMP_ULONG ulBufAddr,MMP_ULONG ulBufSize);
extern MMP_ERR	MMPD_USB_SetMTPEPBuf(MMP_ULONG ulRxBufAddr,MMP_ULONG ulTxBufAddr,
                                     MMP_ULONG ulBufSize,MMP_ULONG ulMBufAddr,
                                     MMP_ULONG ulMBufSize);
extern MMP_ERR  MMPD_USB_GetDpsBufAddr(MMP_UBYTE ubBufType, MMP_ULONG *ulAddr);
extern MMP_ERR	MMPD_DPS_AbortPrint(void);
extern MMP_ERR	MMPD_DPS_ContinuePrint(void);
extern MMP_ERR	MMPD_DPS_GetPrinterStatus(MMP_USHORT *usStatus);

extern MMP_ERR  MMPD_USB_SetDBGBuffer(MMP_ULONG uldbg_buf, MMP_ULONG uldbg_size);

extern MMP_ERR MMPD_USB_RegPollingCallBack(void *pReadUSBIDTimeoutCallback, void *pOtgSessionTimeoutCallback, void *pDevConnCallback, void *pDevDisconnCallback);
extern MMP_ERR MMPD_USB_TriggerReadUSBID(MMP_ULONG *pulTimerId);
extern MMP_ERR MMPD_USB_ReadUSBID(MMP_UBYTE *pubDevType);
extern MMP_ERR MMPD_USB_StartOTGSession(MMP_ULONG *pulTimerId);
extern MMP_ERR MMPD_USB_StopOTGSession(void);
extern MMP_ERR MMPD_USB_GetDevConnSts(MMP_BOOL *pbStatus);
extern MMP_ERR MMPD_USB_SetDevConnSts(MMP_BOOL pbStatus);
extern MMP_ERR MMPD_USB_EnumUVC(void);
extern MMP_ERR MMPD_USB_GetUVCStreamSts(MMP_BOOL *pbStatus);
extern MMP_ERR MMPD_USB_RegUVCMDCallBack(void *pDevTriggerMDCallback);
extern MMP_ERR MMPD_USB_EnableUVCMD(void);
extern MMP_ERR MMPD_USB_DisableUVCMD(void);
extern MMP_ERR MMPD_USB_SetCheckDevAliveCFG(MMP_ULONG pulCheckDevAliveInterval, void *pDevNoResponseCallback);
extern MMP_ERR MMPD_USB_SetTranTimeoutCFG(MMP_ULONG pulTranTimeoutInterval, void *pDevTranTimeoutCallback);
extern MMP_ERR MMPD_USB_SetFrmRxTimeoutCFG(MMP_ULONG pulFrmRxLostTH, MMP_ULONG pulFrmRxFirstAddGap, void *pDevFrmRxLostTHCallback);
extern MMP_ERR MMPD_USB_SetFrmRxTimeout2CFG(MMP_ULONG pulFrmRxLostTH2, void *pDevFrmRxLostTH2Callback);
extern MMP_ERR MMPD_USB_SetFrmSeqNoLostCFG(MMP_ULONG pulSeqNoLostTH, void *pDevSeqNoLostTHCallback);
extern MMP_ERR MMPD_USB_StopFrmRxClrFIFO(void);
extern MMP_ERR MMPD_USB_SetDropRxFrmCFG(MMP_ULONG ulTotalCnt, MMP_ULONG ulContinCnt, void *pDropRxFrmCallback);

/// @}
#endif // _MMPD_USB_H_

/// @end_ait_only
