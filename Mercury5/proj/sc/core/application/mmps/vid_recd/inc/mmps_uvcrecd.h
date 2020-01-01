#ifndef _MMPS_HUVC_H_
#define _MMPS_HUVC_H_

//===============================================================================
//
//                               INCLUDE FILE
//
//===============================================================================

#include "config_fw.h"
#include "mmp_usb_inc.h"
#include "mmp_graphics_inc.h"
#include "mmp_scal_inc.h"
#include "mmp_display_inc.h"

//===============================================================================
//
//                               MACRO DEFINE
//
//===============================================================================

#if (SUPPORT_USB_HOST_FUNC)
#define MMPS_3GPRECD_UVC_CHIP_STR_LEN   (8) // Sync (MMPF_USBH_UVC_CHIP_STR_LEN)
#define MMPS_3GPRECD_UVC_CFG_MAX_NUM    (10) // Sync (MMPF_USBH_DEV_CFG_MAX_NUM)
#endif

//===============================================================================
//
//                               ENUMERATION
//
//===============================================================================

typedef enum _MMPS_HUVC_FILE_TYPE {
    MMPS_HUVC_MULFILE,
    MMPS_HUVC_MULTRACK
} MMPS_HUVC_FILE_TYPE;

typedef enum _MMPS_HUVC_UI_MODE {
    MMPS_HUVC_UI_MODE_VR,
    MMPS_HUVC_UI_MODE_DSC,
    MMPS_HUVC_UI_MODE_NUM
} MMPS_HUVC_UI_MODE;

//===============================================================================
//
//                               STRUCTURES
//
//===============================================================================

typedef struct _MMPS_HUVC_CONTAINER_INFO {
    MMP_USHORT      usVidEncFormat;     ///< video encode format
    MMP_ULONG       ulFrameWidth;       ///< video frame width
    MMP_ULONG       ulFrameHeight;      ///< video frame height
    MMP_ULONG       ulTimeIncrement;    ///< video time increment
    MMP_ULONG       ulTimeResolution;   ///< video time resolution   
    MMP_USHORT      usPFrameCount;      ///< P frames count in one GOP
    MMP_USHORT      usBFrameCount;      ///< # consecutive B frames
    
    MMP_ULONG       ulSPSAddr;
    MMP_ULONG       ulPPSAddr;
    MMP_USHORT      ulSPSSize;
    MMP_USHORT      ulPPSSize;
    MMP_USHORT      ulProfileIDC;
    MMP_USHORT      ulLevelIDC;
} MMPS_HUVC_CONTAINER_INFO;

typedef struct _MMPS_HUVC_AHC_PREVIEW_INFO {
    MMP_BOOL                bUserDefine;
    MMP_BOOL                bPreviewMirror;
    MMP_SCAL_FIT_MODE       sFitMode;
    MMP_ULONG               ulPreviewBufW;
    MMP_ULONG               ulPreviewBufH;
    MMP_ULONG               ulDispStartX;
    MMP_ULONG               ulDispStartY;
    MMP_ULONG               ulDispWidth;
    MMP_ULONG               ulDispHeight;
    MMP_DISPLAY_COLORMODE   sDispColor;
} MMPS_HUVC_AHC_PREVIEW_INFO;

//===============================================================================
//
//                               FUNCTION PROTOTYPES
//
//===============================================================================

/* Decode MJPEG to Preview Function */
MMP_ERR MMPS_HUVC_GetDecMjpegToPreviewSrcAttr(MMP_USHORT *pusW, MMP_USHORT *pusH);
MMP_ERR MMPS_HUVC_SetDecMjpegToPreviewSrcAttr(MMP_USHORT usSrcW, MMP_USHORT usSrcH);
MMP_ERR MMPS_HUVC_InitVRDecMjpegToPreview(MMP_USHORT usJpegSrcW, MMP_USHORT usJpegSrcH);
MMP_ERR MMPS_HUVC_VRDecMjpegPreviewStart(void);
MMP_ERR MMPS_HUVC_VRDecMjpegPreviewStop(void);
MMP_ERR MMPS_HUVC_InitDscDecMjpegToPreview(MMP_USHORT usJpegSrcW, MMP_USHORT usJpegSrcH);
MMP_ERR MMPS_HUVC_DscDecMjpegPreviewStart(void);
MMP_ERR MMPS_HUVC_DscDecMjpegPreviewStop(void);

#if (SUPPORT_USB_HOST_FUNC)
MMP_ERR MMPS_HUVC_SetCustomedPrevwAttr( MMP_BOOL      bUserConfig,
                                        MMP_BOOL      bMirror,
                                        MMP_UBYTE     sFitMode,
                                        MMP_USHORT    usBufWidth, MMP_USHORT usBufHeight,
                                        MMP_USHORT    usStartX,   MMP_USHORT usStartY,
                                        MMP_USHORT    usWinWidth, MMP_USHORT usWinHeight);
MMP_ERR MMPS_HUVC_GetCustomedPrevwAttr( MMP_BOOL      *pbUserConfig,
                                        MMP_BOOL      *pbMirror,
                                        MMP_UBYTE     *psFitMode,
                                        MMP_USHORT    *pusBufWidth,   MMP_USHORT *pusBufHeight,
                                        MMP_USHORT    *pusStartX,     MMP_USHORT *pusStartY,
                                        MMP_USHORT    *pusWinWidth,   MMP_USHORT *pusWinHeight);

MMP_ERR MMPS_HUVC_StartPreview(void);
MMP_ERR MMPS_HUVC_StopPreview(void);
MMP_ERR MMPS_HUVC_SetPrevwWinID(MMP_UBYTE ubWinID);
MMP_ERR MMPS_HUVC_SetUVCRecdResol(MMP_UBYTE ubResol);
MMP_ERR MMPS_HUVC_SetRecdBitrate(MMP_ULONG ulBitrate);
MMP_ERR MMPS_HUVC_SetRecdFrameRate(MMP_USHORT usTimeIncrement, MMP_USHORT usTimeIncrResol);
MMP_ERR MMPS_HUVC_SetRecdPFrameCount(MMP_USHORT usFrameCount);
MMP_ERR MMPS_HUVC_SetPrevwResol(MMP_USHORT usWidth, MMP_USHORT usHeight);
MMP_ERR MMPS_HUVC_SetUVCPrevwRote(MMP_GRAPHICS_ROTATE_TYPE ubRoteType);
MMP_ERR MMPS_HUVC_SetPrevwStrmTyp(MMP_UBYTE ubPrevwStrmTyp);
MMP_ERR MMPS_HUVC_SetPrevwFrameRate(MMP_UBYTE ubFps);
MMP_ERR MMPS_HUVC_AddDevCFG(MMP_UBYTE *pubStr, void *pOpenDevCallback, void *pStartDevCallback, void *pNaluInfo);
MMP_ERR MMPS_HUVC_UpdDevCFG(MMP_USBH_UPD_UVC_CFG_OP Event, MMP_UBYTE *pubStr, void *pParm);
MMP_ERR MMPS_HUVC_RegDevAddiCFG(MMP_ULONG ulRegTyp, MMP_UBYTE *pubStr, MMP_ULONG ulParm0, MMP_ULONG ulParm1, MMP_ULONG ulParm2, MMP_ULONG ulParm3);
MMP_ERR MMPS_HUVC_SetClassIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPS_HUVC_GetClassIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_ULONG *UVCDataLength, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPS_HUVC_SetStdIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPS_HUVC_GetStdDevCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_ULONG *UVCDataLength, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPS_HUVC_SetDevTotalCount(MMP_UBYTE ubCount);
#endif

#if (UVC_VIDRECD_SUPPORT)
MMP_ERR MMPS_HUVC_SetUVCRecdSupport(MMP_BOOL bSupport);
MMP_ERR MMPS_HUVC_GetUVCRecdSupport(MMP_BOOL *bSupport);
MMP_ERR MMPS_HUVC_StartRecd(MMP_UBYTE type);
MMP_ERR MMPS_HUVC_OpenRecdFile(void);
MMP_ERR MMPS_HUVC_EnableRecd(void);
MMP_ERR MMPS_HUVC_StopRecd(void);
MMP_ERR MMPS_HUVC_RecdInputFrame(MMP_ULONG bufaddr, MMP_ULONG size, MMP_ULONG timestamp,
                                    MMP_USHORT frametype, MMP_USHORT vidaudtype);
MMP_ERR MMPS_HUVC_SetRecdInfo(MMPS_HUVC_CONTAINER_INFO *pInfo);
#endif

#endif // _MMPS_HUVC_H_
