//==============================================================================
//
//  File        : mmpf_usbh_uvc.h
//  Description : Header file for the USB HOST UVC function
//  Author      : Bruce_Chien
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBH_UVC_H_
#define _MMPF_USBH_UVC_H_

#if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)
#include "mmpf_usbh_core.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define MMPF_USBH_UVC_CHIP_STR_LEN  (8)
#define MMPF_USBH_DEV_CFG_MAX_NUM   (10)

/* Default UVC Parameters */
#define DEFAULT_PREVW_W             (320)
#define DEFAULT_PREVW_H             (180)
#define DEFAULT_PREVW_TIMERESO      (200)
#define DEFAULT_PREVW_TIMEINCR      (6000)

#define DEFAULT_RECD_RES            (VIDRECD_RESOL_1920x1088)
#define DEFAULT_RECD_W              (1920)
#define DEFAULT_RECD_H              (1080)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURES AND TYPEDEF
//
//==============================================================================

typedef void (MMPF_USBH_Callback) (void);

typedef struct __attribute__((packed)) _MMP_USBH_UVC_RECD_CFG 
{
    MMP_UBYTE                   usResol;
    MMP_USHORT                  usWidth;
    MMP_USHORT                  usHeight;
    MMP_ULONG                   ulBitrate;
    MMP_USHORT                  usTimeIncrement;
    MMP_USHORT                  usTimeIncrResol;
    MMP_USHORT                  usPFrame;
} MMPF_USBH_UVC_RECD_CFG;

typedef struct __attribute__((packed)) _MMPF_USBH_UVC_PREVW_CFG 
{
    MMP_USHORT                  usWidth;
    MMP_USHORT                  usHeight;
    MMP_UBYTE                   ubFps;
    MMP_UBYTE                   ubStrmTyp;
    MMP_BOOL                    ubSet;
} MMPF_USBH_UVC_PREVW_CFG;

typedef struct __attribute__((packed)) _MMPF_USBH_UVC_STREAM_CFG 
{
    MMPF_USBH_UVC_RECD_CFG      mRecd;
    MMPF_USBH_UVC_PREVW_CFG     mPrevw;
} MMPF_USBH_UVC_STREAM_CFG;

typedef struct __attribute__((packed)) _MMPF_USBH_DEV_CFG 
{
    MMP_UBYTE                   ubDevStrInfo[MMPF_USBH_UVC_CHIP_STR_LEN];
    MMPF_USBH_Callback          *OpenUVCCallback;
    MMPF_USBH_Callback          *StartUVCCallback;
    USBH_UVC_H264_NALU_CFG      mNalu;
    MMP_ULONG                   ulGuidEu[CS_INTERFACE_DESCR_GUID_SZ/(sizeof(MMP_ULONG))];
} MMPF_USBH_DEV_CFG;

typedef struct __attribute__((packed)) _MMPF_USBH_DEV_GRP_CFG 
{
    MMP_UBYTE                   ubTotalCount;
    MMP_UBYTE                   ubFreeCount;
    MMP_UBYTE                   ubDevIdx;                            // Current index that match chip info
    MMPF_USBH_DEV_CFG           mDev[(MMPF_USBH_DEV_CFG_MAX_NUM+1)]; // Reserve last one NULL if no match dev
} MMPF_USBH_DEV_GRP_CFG;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_USBH_StartOTGSession(MMP_ULONG *pulTimerId);
MMP_ERR MMPF_USBH_OpenUVC(USBH_DEVICE *dev);
MMP_ERR MMPF_USBH_StartUVCPrevw(void);
MMP_ERR MMPF_USBH_StopUVCPrevw(void);
MMP_ERR MMPF_USBH_SetUVCStreamOn(void);
MMP_ERR MMPF_USBH_SetUVCStreamOff(void);
MMP_ERR MMPF_USBH_GetUVCStreamSts(MMP_BOOL *pbEnable);
MMP_ERR MMPF_USBH_SetUVCPrevwOn(void);
MMP_ERR MMPF_USBH_SetUVCPrevwOff(void);
MMP_ERR MMPF_USBH_GetUVCPrevwSts(MMP_BOOL *pbEnable);
MMP_ERR MMPF_USBH_SetStartFrameofUVCRecd(void);
MMP_ERR MMPF_USBH_SetEndFrameofUVCRecd(void);
MMP_ERR MMPF_USBH_GetUVCRecdSts(MMP_BOOL *pbEnable);
MMP_ERR MMPF_USBH_SetUVCPrevwWinID(MMP_UBYTE pbWinID);
MMP_ERR MMPF_USBH_SetUVCIDR(void);
MMPF_USBH_UVC_STREAM_CFG* MMPF_USBH_GetUVCCFG(void);
MMP_ERR MMPF_USBH_FindDevInfo(MMP_UBYTE *pubStr);
MMP_ERR MMPF_USBH_SetUVCRecdResol(MMP_UBYTE ubResol, MMP_USHORT usWidth, MMP_USHORT usHeight);
MMP_ERR MMPF_USBH_SetUVCRecdBitrate(MMP_ULONG ulBitrate);
MMP_ERR MMPF_USBH_SetUVCRecdFrameRate(MMP_USHORT usTimeIncrement, MMP_USHORT usTimeIncrResol);
MMP_ERR MMPF_USBH_SetUVCRecdFrameCount(MMP_USHORT usPFrameCount);
MMP_ERR MMPF_USBH_SetUVCPrevwResol(MMP_USHORT usWidth, MMP_USHORT usHeight);
MMP_ERR MMPF_USBH_SetUVCPrevwStrmTyp(MMP_UBYTE ubPrevwStrmTyp);
MMP_ERR MMPF_USBH_IsUVCDecMjpeg2Prevw(MMP_BOOL *pbIsDecMjpeg2Prevw);
MMP_ERR MMPF_USBH_SetUVCPrevwFrameRate(MMP_UBYTE ubFps);
MMPF_USBH_DEV_GRP_CFG* MMPF_USBH_GetDevCFG(void);
MMP_ERR MMPF_USBH_ClrDevCFG(void);
MMP_ERR MMPF_USBH_AddDevCFG(MMP_UBYTE *pubStr, void *pOpenDevCallback, void *pStartDevCallback, void *pNaluInfo);
MMP_ERR MMPF_USBH_UpdDevCFG(MMP_ULONG ulEvent, MMP_UBYTE *pubStr, void *pParm);
MMP_ERR MMPF_USBH_RegDevAddiCFG(MMP_ULONG ulRegTyp, MMP_UBYTE *pubStr, MMP_ULONG ulParm0, MMP_ULONG ulParm1, MMP_ULONG ulParm2, MMP_ULONG ulParm3);
MMP_ERR MMPF_USBH_ExeCB(void *pCBFunc);
MMP_ERR MMPF_USBH_SetUVCDevTotalCount(MMP_UBYTE ubCount);

#endif // #if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)

#endif // _MMPF_USBH_UVC_H_
