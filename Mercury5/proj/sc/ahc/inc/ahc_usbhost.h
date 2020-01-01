//==============================================================================
//
//  File        : ahc_usbhost.h
//  Description : INCLUDE File for the AHC USB function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_USB_HOST_H_
#define _AHC_USB_HOST_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "Customer_config.h"
#include "AHC_Config_SDK.h"
#include "ahc_display.h"
#include "mmps_3gprecd.h"
#include "mmps_uvcrecd.h"
#include "mmp_usb_inc.h"

#if (UVC_HOST_VIDEO_ENABLE)

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define USB_STRM_TYP_H264                   (1)
#define USB_STRM_TYP_MJPEG                  (2)
#define USB_STRM_TYP_YUY2                   (3)
#define USB_STRM_TYP_NV12                   (4)

#define BM_USB_STRM_UNEDF                   (0)
#define BM_USB_STRM_H264                    (1 << (USB_STRM_TYP_H264 - 1))
#define BM_USB_STRM_MJPEG                   (1 << (USB_STRM_TYP_MJPEG - 1))
#define BM_USB_STRM_NV12                    (1 << (USB_STRM_TYP_NV12 - 1))

#define USB_STRM_ID_H264                    (0x00)
#define USB_STRM_ID_MJPEG                   (0x02)
#define USB_STRM_ID_YUV                     (0x40)

/* Commit 720p to transcoding H264 WiFi */
#define CUR_DEV_8437_MJPEG_W                (1280)
#define CUR_DEV_8437_MJPEG_H                (720)
#define INIT_DEV_MJPEG_BITRATE              (12000000)
#define INIT_DEV_MJPEG_FPS                  (30)

#define GUID_EC_AIT_0                       (0x23E49ED0)
#define GUID_EC_AIT_1                       (0x4F311178)
#define GUID_EC_AIT_2                       (0xFBD252AE)
#define GUID_EC_AIT_3                       (0x483B8D8A)

#define GUID_EC_SONIX_0                     (0x28F03370)
#define GUID_EC_SONIX_1                     (0x4A2E6311)
#define GUID_EC_SONIX_2                     (0x90682CBA)
#define GUID_EC_SONIX_3                     (0x164033EB)

#define GUID_JX_SONIX_0                     (0x0fb885c3)
#define GUID_JX_SONIX_1                     (0x454768c2)
#define GUID_JX_SONIX_2                     (0x478ff790)
#define GUID_JX_SONIX_3                     (0xfc959d57)

#define CHECK_EP0_TIMEOUT_INTERVAL          (500)       // Check Ep0 timeout interval
#define CHECK_TRAN_TIMEOUT_INTERVAL         (100)       // Check transaction timeout interval after 1st packet received. Unit: micro sec.
#define CHECK_FRM_RX_LOST_TH                (10)        // Check frame lost threshold
#define CHECK_FRM_RX_FIRST_ADD_GAP          (500)       // First frame gap of check frame lost threshold in ms
#define CHECK_FRM_RX_LOST_TH_2              (30)        // Check frame lost threshold 2
#define CHECK_FRM_SEQ_NO_LOST_TH            (1)         // Check frame seq no lost threshold
#define CHECK_FRM_RX_DROP_TOTAL_CNT         (6000)      //How many frames are dropped in total
#define CHECK_FRM_RX_DROP_CONTI_CNT         (1000)     //How many frames are dropped sequentially

#define UVC_HOST_ERROR_EP0_TIMEOUT          (0x00000001)
#define UVC_HOST_ERROR_TRAN_TIMEOUT         (0x00000002)
#define UVC_HOST_ERROR_FRM_RX_LOST          (0x00000004)
#define UVC_HOST_ERROR_FRM_RX_LOST_TH_2     (0x00000008)
#define UVC_HOST_ERROR_SEQ_NO_LOST          (0x00000010)
#define UVC_HOST_ERROR_DISCONNECTED         (0x00000020)

#define UVC_MAX_OSD_STRING_LEN              (32)

#if 1 // For ISO mode
// ----------------------------- XU Control Selector ------------------------------------
#define XU_SONIX_EU1_ID                     (0x03)

#define XU_SONIX_ASIC_CTRL                  (0x01) 
#define XU_SONIX_I2C_CTRL                   (0x02)
#define XU_SONIX_SF_READ                    (0x03)

#define CUR_DEV_64AB_RES_IDX                (1)	//VIDRECD_RESOL_1280x720
#define CUR_DEV_64AB_H264_FPS               (VIDRECD_FRAMERATE_25FPS)
#define CUR_DEV_64AB_VOP_TIME_INCRM         (100)
#define CUR_DEV_64AB_VOP_TIME_RESOL         (2500)
#define CUR_DEV_64AB_BITRATE                (12000000)
#define CUR_DEV_64AB_PFRM_CNT               (25)
#define CUR_DEV_64AB_W                      (1280)
#define CUR_DEV_64AB_H                      (720)
#endif

#define HUVCSetStdIfCmd(ubReq,usVal,usInd,usLen,pubDataBuf)      MMPS_HUVC_SetStdIfCmd(ubReq, (usVal), (usInd), usLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCGetStdDevCmd(ubReq,usVal,usInd,usLen,pulDataLen,pubDataBuf) MMPS_HUVC_GetStdDevCmd(ubReq, (usVal), (usInd), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCSetVCCmd(ubReq,usVal,usLen,pubDataBuf)               MMPS_HUVC_SetClassIfCmd(ubReq, (usVal<<8), (gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCGetVCCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)    MMPS_HUVC_GetClassIfCmd(ubReq, (usVal<<8), (gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCSetVSCmd(ubReq,usVal,usLen,pubDataBuf)               MMPS_HUVC_SetClassIfCmd(ubReq, (usVal<<8), (gUsbh_UvcDevInfo.bIfNoVS), usLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCGetVSCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)    MMPS_HUVC_GetClassIfCmd(ubReq, (usVal<<8), (gUsbh_UvcDevInfo.bIfNoVS), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCSetCTCmd(ubReq,usVal,usLen,pubDataBuf)               MMPS_HUVC_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdIT<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCGetCTCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)    MMPS_HUVC_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdIT<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCSetPUCmd(ubReq,usVal,usLen,pubDataBuf)               MMPS_HUVC_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdPU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCGetPUCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)    MMPS_HUVC_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdPU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCSetEU1Cmd(ubReq,usVal,usLen,pubDataBuf)              MMPS_HUVC_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCGetEU1Cmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)   MMPS_HUVC_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCSetEU3Cmd(ubReq,usVal,usLen,pubDataBuf)              MMPS_HUVC_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCGetEU3Cmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)   MMPS_HUVC_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCSetFUCmd(ubReq,usVal,usLen,pubDataBuf)               MMPS_HUVC_SetClassIfCmd(ubReq, (usVal<<8), ((UAC_FU_ID<<8)|UAC_AC_AS_EP), usLen, (MMP_UBYTE *)pubDataBuf)
#define HUVCGetFUCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)    MMPS_HUVC_GetClassIfCmd(ubReq, (usVal<<8), ((UAC_FU_ID<<8)|UAC_AC_AS_EP), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

typedef enum _UVC_DEVICE_NAME_INDEX {
    UVC_DEVICE_NAME_8437            = 0, 
    UVC_DEVICE_NAME_8451            = 1, 
    UVC_DEVICE_NAME_PID_0210        = 2,
    UVC_DEVICE_NAME_PID_64AB        = 3,
    UVC_DEVICE_NAME_PID_6300        = 4,
    UVC_DEVICE_NAME_PID_9230        = 5,
    UVC_DEVICE_NAME_PID_2B95        = 6,
    UVC_DEVICE_NAME_PID_8301        = 7,
    UVC_DEVICE_NAME_PID_8328        = 8,
    UVC_DEVICE_NAME_PID_6366        = 9,
    UVC_DEVICE_NAME_PID_8339        = 10,
    UVC_DEVICE_NAME_MAX_SUPPORT_NUM = 11,
    UVC_DEVICE_NAME_NONE            = UVC_DEVICE_NAME_MAX_SUPPORT_NUM
} UVC_DEVICE_NAME_INDEX ;

/* MUST mapping to m_usResolTable[] because of using CreateRecordFileName */
typedef enum _UVC_H264_RES_IDX {
    UVC_H264_RES_360P               = 0,    /* ==> VIDRECD_RESOL_640x360 */
    UVC_H264_RES_480P               = 1,    /* ==> VIDRECD_RESOL_720x480 */
    UVC_H264_RES_720P               = 2,    /* ==> VIDRECD_RESOL_1280x720 */
    UVC_H264_RES_1080P              = 3,    /* ==> VIDRECD_RESOL_1920x1088 */
    UVC_H264_RES_1440P              = 4,    /* ==> VIDRECD_RESOL_2560x1440 */
    UVC_H264_RES_MAX_SUPPORT_NUM    = 5
} UVC_H264_RES_IDX;

typedef enum _UVC_H264_QUALITY_INDEX {
    UVC_H264_QUALITY_HIGH = 0, 
    UVC_H264_QUALITY_MID, 
    UVC_H264_QUALITY_LOW, 
    UVC_H264_QUALITY_MAX_SUPPORT_NUM
} UVC_H264_QUALITY_INDEX ;

typedef enum _UVC_YUV_RESOL_INDEX {
    UVC_YUV_RESOL_90P = 0,  // 160x90, 16:9
    UVC_YUV_RESOL_180P,     // 320x180, 16:9
    UVC_YUV_RESOL_240P,     // 320x240, 4:3
    UVC_YUV_RESOL_360P,     // 640x360, 16:9
    UVC_YUV_RESOL_480P,     // 640x480, 4:3
    UVC_YUV_RESOL_MAX_SUPPORT_NUM
} UVC_YUV_RESOL_INDEX;

typedef enum _UVC_FRAMERATE_INDEX {
    UVC_FRAMERATE_10FPS = 0, 
    UVC_FRAMERATE_15FPS, 
    UVC_FRAMERATE_20FPS,
    UVC_FRAMERATE_25FPS,
    UVC_FRAMERATE_30FPS,
    UVC_FRAMERATE_MAX_SUPPORT_NUM
} UVC_FRAMERATE_INDEX ;

typedef enum _UVC_MJPEG_RESOL_INDEX {
    UVC_MJPEG_RESOL_90P = 0,  // 160x90, 16:9
    UVC_MJPEG_RESOL_180P,     // 320x180, 16:9
    UVC_MJPEG_RESOL_360P,     // 640x360, 16:9
    UVC_MJPEG_RESOL_720P,     // 1280x720, 16:9
    UVC_MJPEG_RESOL_MAX_SUPPORT_NUM
} UVC_MJPEG_RES_INDEX;

typedef enum _UVC_XU_OSD_INDEX {
    UVC_XU_OSD_TIME_DISABLE = 0,
    UVC_XU_OSD_TIME_ENABLE,
    UVC_XU_OSD_TEXT_DISABLE,
    UVC_XU_OSD_TEXT_ENABLE,
    UVC_XU_OSD_MAX_SUPPORT_NUM
} UVC_XU_OSD_INDEX;

typedef enum _UVC_XU_OSD_COLOR {
    UVC_XU_OSD_COLOR_WHITE = 1,
    UVC_XU_OSD_COLOR_YELLOW,
    UVC_XU_OSD_COLOR_BLACK,
    UVC_XU_OSD_COLOR_NUM
} UVC_XU_OSD_COLOR;

typedef enum _UVC_IMAGE_FLIP {
    UVC_IMAGE_FLIP_NONE = 0,
    UVC_IMAGE_FLIP_UPSIDE_DOWN,
    UVC_IMAGE_FLIP_MIRROR,
    UVC_IMAGE_FLIP_BLACK_IMAGE,
    UVC_IMAGE_FLIP_MAX_SUPPORT_NUM
} UVC_IMAGE_FLIP;

typedef enum _UVC_FLICKER_INDEX {
    UVC_FLICKER_NONE = 0,
    UVC_FLICKER_60HZ,
    UVC_FLICKER_50HZ,
    UVC_FLICKER_AUTO,
    UVC_FLICKER_MAX
} UVC_FLICKER_INDEX;

typedef enum _AHC_HUVC_UI_MODE { // Sync with MMPS_HUVC_UI_MODE
    AHC_HUVC_UI_MODE_VR,
    AHC_HUVC_UI_MODE_DSC,
    AHC_HUVC_UI_MODE_NUM
} AHC_HUVC_UI_MODE;

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef struct __attribute__((packed)) _UVC_NALU_CFG
{
    MMP_UBYTE               ubDevStrInfo[MMPS_3GPRECD_UVC_CHIP_STR_LEN];
    USBH_UVC_H264_NALU_CFG  mNalu[UVC_H264_RES_MAX_SUPPORT_NUM];
} UVC_NALU_CFG ;

typedef struct _UVC_HOST_CFG 
{
    UINT8                   ubCmitUVCStrmTyp;
    UVC_H264_RES_IDX        sH264Resol;
    UVC_FRAMERATE_INDEX     sFrameRate;
    UVC_H264_QUALITY_INDEX  sH264Quality;
    UINT16                  usPFrameCnt;
    UVC_YUV_RESOL_INDEX     sYUVResol;
    UVC_MJPEG_RES_INDEX     sMjpegResol;
    UINT16                  usMjpegFps;
    UINT32                  ulMjpegkbps;
} UVC_HOST_CFG ;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void AHC_HostUVCVideoReadErrorType(UINT32 *pErrorType);
void AHC_HostUVCVideoClearError(UINT32 ulErrorType);
void AHC_HostUVCVideoSetEp0TimeoutCB(void);
void AHC_HostUVCVideoSetTranTimeoutCB(void);
void AHC_HostUVCVideoSetFrmRxTimeoutCB(void);
void AHC_HostUVCVideoSetFrmRxTimeout2CB(void);
void AHC_HostUVCVideoSetFrmSeqNoLostCB(void);
void AHC_HostUVCVideoSetFrmRxDropCB(void);
void AHC_HostUVCVideoDevDisconnectedCB(void);

AHC_BOOL AHC_HostUVC_ResetFBMemory(void);
AHC_BOOL AHC_HostUVC_EnumDevice(AHC_BOOL busb_device_in);
AHC_BOOL AHC_HostUVC_SetIdleStates(void);
AHC_BOOL AHC_HostUVC_SonixReverseGearDetection(void);
AHC_BOOL AHC_HostUVC_GetReversingGearStatus(void);

AHC_BOOL AHC_HostUVC_IsDevEnabled(void);
AHC_BOOL AHC_HostUVC_RecordStart(void);
AHC_BOOL AHC_HostUVC_RecordStop(void);
AHC_BOOL AHC_HostUVC_SetScdRecdSetting(void);
AHC_BOOL AHC_HostUVC_PreviewStart(UINT8 u8UiMode, UINT32 ulFlickerMode);
AHC_BOOL AHC_HostUVC_PreviewStop(UINT8 u8UiMode);

#if (MOTION_DETECTION_EN)
AHC_BOOL AHC_HostUVC_SetMDSensitivity(MMP_UBYTE ubSensitivity);
#endif
AHC_BOOL AHC_HostUVC_ForceIFrame(void);
AHC_BOOL AHC_HostUVC_SetOSD(const char *pstring, UINT16 usoffset_x, UINT16 usoffset_y, UVC_XU_OSD_INDEX usdisplay_mode);
AHC_BOOL AHC_HostUVC_SetImageFlip(UVC_IMAGE_FLIP eFlipOption);
AHC_BOOL AHC_HostUVC_GetDevFwVersion(UINT16* puwMajor, UINT16* puwMinor, UINT16* puwBuild);
AHC_BOOL AHC_HostUVC_ResetDevTime(void);
AHC_BOOL AHC_HostUVC_SetFlicker(UVC_FLICKER_INDEX eFlickerIndex);
AHC_BOOL AHC_HostUVC_SetLedFlicker(UINT8 u8Flag);
AHC_BOOL AHC_HostUVC_SetPUBackLightCompensation(UINT16 ulBackLightCompensationLevel);
AHC_BOOL AHC_HostUVC_SetPUBrightness(UINT16 ulBrightnessLevel);
AHC_BOOL AHC_HostUVC_SetPUContrast(UINT16 ulContrastLevel);
AHC_BOOL AHC_HostUVC_SetPUGain(UINT16 ulGainLevel);
AHC_BOOL AHC_HostUVC_SetPUPowerLineFrequency(UINT8 ulPowerLineFrequency);
AHC_BOOL AHC_HostUVC_SetPUHue(UINT16 ulHueLevel);
AHC_BOOL AHC_HostUVC_SetPUSaturation(UINT16 ulSaturationLevel);
AHC_BOOL AHC_HostUVC_SetPUSharpness(UINT16 ulSharpnessLevel);
AHC_BOOL AHC_HostUVC_SetPUGamma(UINT16 ulGammaLevel);
AHC_BOOL AHC_HostUVC_SetPUWhiteBalanceTemperature(UINT16 ulWhiteBalanceTemperature);
AHC_BOOL AHC_HostUVC_SetPUWhiteBalanceTemperatureAuto(UINT8 ulWhiteBalanceTemperatureAuto);
AHC_BOOL AHC_HostUVC_SetMjpegBitrate(UINT32 ulkbps);
AHC_BOOL AHC_HostUVC_SetMjpegFrmSz(UINT32 ulKBytes);

#else
AHC_BOOL AHC_HostUVC_IsDevEnabled(void);
AHC_BOOL AHC_HostUVC_SetScdRecdSetting(void);
AHC_BOOL AHC_HostUVC_SetIdleStates(void);
#endif // UVC_HOST_VIDEO_ENABLE

#endif // _AHC_USB_HOST_H_
