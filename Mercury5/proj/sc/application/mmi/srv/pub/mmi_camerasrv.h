/**
* @file mmi_camerasrv.h
*
* Class Id: CLSID_CAMERASRV
*
*/
#ifndef __MMI_CAMERASRV_H__
#define __MMI_CAMERASRV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_camerasrv_def.h"
#include "mmi_mae_handler.h"

/*-------------------------------------------------------------------------*/

/**
 * ICAMERASRV Interfaces
 */
#define INHERIT_ICAMERASRV(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(ICAMERASRV);

#define ICAMERASRV_QueryInterface(pICntlr, id, pp, po) GET_FUNCTBL((pICntlr), ICAMERASRV)->QueryInterface(pICntlr, id, pp, po)
#define ICAMERASRV_HandleEvent(pICntlr, e, p1, p2) GET_FUNCTBL((pICntlr), ICAMERASRV)->HandleEvent(pICntlr, e, p1, p2)

/**
 * Functions
 */
typedef struct
{
    DECLARE_FUNCTBL(ICAMERASRV); // function table pointer
    u32                            nRefCnt;     // reference count
    CameraSrvDev_e                 eCamId;
    CameraSrvStorageConfig_t       tStorageConfig;
    CameraSrvStorage_e             eStorageType;
#ifdef __CAMERA_V1_ITF__
    CameraSrvShutterSoundSetting_t *pShutSound;
    CameraSrvCusInfo_t             *pSoundCusInfo;
#endif
    CameraSrvCaptureFile_t         *pCaptureFile;
    CameraSrvAppType_e             eCamAppType;
    CameraSrvCusInfo_t             *pNotifyData;
    CameraSrvCusInfo_t             *pCameraStatus;
    CameraSrvCusInfo_t             *pCamcoderStatus;
    CameraSrvInitInfo_t            *pCameraInitData;
    CameraSrvCaptureAttribute_t    tCaptureAttr;
    u32                            nImageEffectSupported;
    boolean                        bImageEffectSupported;
    boolean                        bSensorImageEffectSupported;
    boolean                        bIsTerminated;
    boolean                        bLockAE;
    boolean                        bLockAWB;

} CameraSrv_t;

MAE_Ret CameraSrvOpenSession(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId);
MAE_Ret CameraSrvCloseSession(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId);
MAE_Ret CameraSrvOpen(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvDev_e eCamId, CameraSrvAppType_e eCamAppType, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvClose(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvStartPreview(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvPreviewMode_e ePreviewMode, CameraSrvPreviewType_e ePreviewType, const CameraSrvRegion_t *pPreviewRegion, const CameraSrvRegion_t *pOsdRegion, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvStopPreview(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvStartFocus(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvFocusPosition_t *pFocusPosition, CameraSrvCnfCb pfnCameraSrvCb);
#ifdef __CAMERA_V1_ITF__
MAE_Ret CameraSrvSetCameraStatusChangeCb(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, boolean bCamera, CameraSrvStatusChangeCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetResMgrNotifyCb(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvResMgrNotifyCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetShutterSound(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvShutterSound_e eShutSound, CameraSrvSoundType_e eSoundType, u8 *pData, u32 nLen, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvStartCapture(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCaptureConfig_t *pConfig, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvStopCapture(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvGetFilename(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, MAE_WChar *pFileName, u16 nLen, CameraSrvGetFileCb pfnCameraSrvCb);
MAE_Ret CameraSrvGetImage(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvImgDataType_e, u8 *pData, u32 nDataSize, CameraSrvGetImageCb pfnCameraSrvCb);
#endif
MAE_Ret CameraSrvSetCameraStatusChangeCbEx(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, boolean bCamera, CameraSrvStatusChangeCbEx pfnCameraSrvCb);
MAE_Ret CameraSrvSetResMgrNotifyCbEx(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvResMgrNotifyCbEx pfnCameraSrvCb);
MAE_Ret CameraSrvSetCaptureAttribute(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCaptureAttribute_t *pCaptureAttribute);
MAE_Ret CameraSrvStartCaptureEx(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCaptureConfig_t *pConfig, CameraSrvShutterSoundSetting_t *pSoundSetting, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvStopCaptureEx(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvStopCaptureCb pfnCameraSrvCb);
MAE_Ret CameraSrvAbortPanoramaCapture(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvStartRecord(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvRecordConfig_t *pConfig, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvStopRecord(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvQueryNoneSavingFile(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvDeleteTempVideoFile(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSaveVideoFile(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvAbortSavingVideoFile(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSaveRecordFile(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvSaveFileCb pfnCameraSrvCb);
void CameraSrvDiscardRecordFile(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvGetCameraInfo(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvGetCameraInfo_t *pGetCameraInfo, CameraSrvGetCameraInfoCb pfnCameraSrvCb);
MAE_Ret CameraSrvConfigStorage(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvStorageConfig_t *pConfig, CameraSrvStorage_e eStorage, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetSticker(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, u8 *pData, boolean bIsEnable, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetWB(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvAWB_e eCamAWB, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetAE(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvAE_e eCamAE, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetAF(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvAF_e eCamAF, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetZoom(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvZoom_e eCamZoom, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetEV(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvEV_e eCamEV, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetAntiFlicker(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvAntiFlicker_e eCamAntiFlicker, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetEffect(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvEffect_e eCamEffect, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetNightMode(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvEnv_e eCamEnv, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetFlashlight(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvFlashlight_e eCamFlashlight, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetFocusMode(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvFocusMode_e eCamFocusMode, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvSetVideoStabilizer(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvVdoStabilizer_e eVideoStabilizer, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvGetCaptureQuota(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvStorage_e eStorage, CameraSrvPicResolution_e eResolution, CameraSrvImgQuality_e eQuality, CameraSrvGetQuotaCb pfnCameraSrvCb);
void CameraSrvEnableMotionDetect(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvDev_e eCamId, CameraSrvCnfCb pfnCameraSrvCb);
void CameraSrvDisableMotionDetect(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvCnfCb pfnCameraSrvCb);
MAE_Ret CameraSrvLockAE(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, boolean bLockAE);
MAE_Ret CameraSrvLockAWB(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, boolean bLockAWB);
MAE_Ret CameraSrvNew(MAE_ClsId nId, void **ppObj);
MAE_Ret CameraSrvInitSetDefConfig(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvSettings_t *pConfig, CameraSrvCnfCb pfnCameraSrvCb);
boolean CameraSrvIsEffectSupport(CameraSrv_t *pICAMERASRV, u32 nSrvClientInstId, CameraSrvEffect_e eCameffectType);

#endif /* __MMI_CAMERASRV_H__ */

