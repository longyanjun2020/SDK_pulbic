////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
/**
* @file    mmi_srv_camera.h
* @brief
*
*/

#ifndef __MMI_SRV_CAMERA_H__
#define __MMI_SRV_CAMERA_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_camerasrv.h"

typedef void(*SrvCameraCommonCb)(void *pThis, CameraSrvRetCode_e retCode);
typedef void(*SrvCameraStopCaptureCb)(void *pThis, CameraSrvRetCode_e eRetCode, CameraSrvCaptureFile_t *pCaptureFile);
typedef void(*SrvCameraGetQuotaCb)(void *pThis, u32 nQuota, CameraSrvRetCode_e eRetCode);
typedef void(*SrvCameraInterruptNotifyCb)(void *pThis, CameraSrvInterruptNotify_t *pCbData);
typedef void(*SrvCameraStatusChangeCb)(void *pThis, CameraSrvCamStatusChange_t *pCbData);
typedef void(*SrvCameraGetImageFileCb)(void *pThis, CameraSrvRetCode_e retCode, CameraSrvFileName_t *pGetFileName);
typedef void(*SrvCameraGetImageBufferDataCb)(void *pThis, CameraSrvRetCode_e retCode, CameraSrvImage_t *pGetImage);
typedef void(*SrvCameraGetCameraInfoCb)(void *pThis, CameraSrvRetCode_e retCode, CameraSrvCameraInfo_t *pCameraInfo);
typedef void(*SrvCameraInterruptNotifyCbEx)(void *pThis, CameraSrvInterruptNotifyEx_t *pCbData);
typedef void(*SrvCameraStatusChangeCbEx)(void *pThis, CameraSrvCamStatusChangeEx_t *pCbData);

/**
 SrvCameraOpenSession
@brief  The interface is use to open camera session
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraOpenSession(void);

/**
 SrvCameraCloseSession
@brief  The interface is use to close camera session
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraCloseSession(void);

/**
 SrvCameraOpen
@brief  The interface is use to open camera

@param[in]  eDevID						Device ID
@param[in]  eAppType					Application type, such as camera, recorder or engineering mode.
@param[in]  pfnSrvCameraCb				SrvCameraCommonCb call back function point to response the Open request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraOpen(CameraSrvDev_e eDevID, CameraSrvAppType_e eAppType, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraClose
@brief  The interface is use to close camera

@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the close request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraClose(SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraConfigStorage
@brief  The interface is use to set camera configurations such as address and

@param[in]    pConfig					The storage configuration information, if stored in sd card or NAND flash, the buffer address must be assign.
@param[in]    eCamStorage				The storage location -- SD Card, BB and NAND flash
@param[in]    pfnSrvCameraCb			SrvCameraCommonCb call back function point to response the configuration request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraConfigStorage(CameraSrvStorageConfig_t *pConfig, CameraSrvStorage_e eCamStorage, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraStartPreview
@brief  The interface is use to start camera/camcorder previewing

@param[in]    ePreviewMode       the mode of preview (camera preview, camcoder preview, ratial preview, wallpaper size preview)
@param[in]    ePreviewType       the type of preview (portrait or landscape)
@param[in]    pPreviewRegion     the Region of preview
@param[in]    pOSDRegion          the Region of OSD
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the start preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraStartPreview(CameraSrvPreviewMode_e ePreviewMode,
                                 CameraSrvPreviewType_e ePreviewType,
                                 const CameraSrvRegion_t *pPreviewRegion,
                                 const CameraSrvRegion_t *pOSDRegion,
                                 SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraStopPreview
@brief  The interface is use to stop camera/camcorder previewing

@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the stop preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraStopPreview(SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraStartFocus
@brief  The interface is use to start camera focus function
@param[in]    CameraSrvFocusPosition_t   Focus position
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the start preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraStartFocus(CameraSrvFocusPosition_t *pFocusPosition, SrvCameraCommonCb pfnSrvCameraCb);

MAE_Ret SrvCameraSetCaptureAttribute(CameraSrvCaptureAttribute_t *pCaptureAttribute);
MAE_Ret SrvCameraStartCaptureEx(CameraSrvCaptureConfig_t *pConfig, CameraSrvShutterSoundSetting_t *pSoundSetting, SrvCameraCommonCb pfnSrvCameraCb);
MAE_Ret SrvCameraStopCaptureEx(SrvCameraStopCaptureCb pfnSrvCameraCb);
MAE_Ret SrvCameraAbortPanoramaCapture(SrvCameraCommonCb pfnSrvCameraCb);
MAE_Ret SrvCameraSetInterruptNotifyCbEx(SrvCameraInterruptNotifyCbEx pfnSrvCameraCb);
MAE_Ret SrvCameraSetCameraStatusChangeCbEx(SrvCameraStatusChangeCbEx pfnSrvCameraCb);

/**
 SrvCameraStartCapture
@brief  The interface is use to get camera information

@param[in]    pGetCameraInfo   Input parameters to specify the camera id and capture/record resolution
@param[in]    pfnSrvCameraCb   SrvCameraGetCameraInfoCb call back function point to response the get camera info request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraGetCameraInfo(CameraSrvGetCameraInfo_t *pGetCameraInfo, SrvCameraGetCameraInfoCb pfnSrvCameraCb);

/**
 SrvCameraTurnOnSticker
@brief  The interface is use to turn on photo frame

@param[in]    pRawData          Pointer to the rawdata of sticker frame
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the turn on Sticker request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraTurnOnSticker(u8 *pRawData, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraTurnOffSticker
@brief  The interface is use to turn off photo frame
(The disable action can only be executed when camera is going to close under the sticker is enable but not ready to get into preview stage.)

@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the turn off Sticker request
 */
MAE_Ret SrvCameraTurnOffSticker(SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetAttributeAWB
@brief           Set white balance attribute

@param[in]    eVal (white balance type)
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */

MAE_Ret SrvCameraSetWB(CameraSrvAWB_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetAttributeAE
@brief          Set auto estimate light attribute

@param[in]    eVal (whole image, central win, ......)
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetAE(CameraSrvAE_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetAttributeAF
@brief          Set auto focus attribute

@param[in]    eVal (on, off)
@param[in]    pfnSrvCameraCb			SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetAF(CameraSrvAF_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetAttributeZoom
@brief          Set Zoom attribute

@param[in]    eVal (In, out, default)
@param[in]    pfnSrvCameraCb			SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetZoom(CameraSrvZoom_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetAttributeEV
@brief          Set EV value attribute

@param[in]    eVal (default, -1, +1, ......)
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetEV(CameraSrvEV_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetAttributeAntiFlicker
@brief          Set Anit Filcker attribute

@param[in]    eVal (50\60Hz)
@param[in]    pfnSrvCameraCb			SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetAntiFlicker(CameraSrvAntiFlicker_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetAttributeEffect
@brief          Set image effect attribute

@param[in]    eVal (effect type:MONO, SEPIA, ......)
@param[in]    pfnSrvCameraCb			SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetEffect(CameraSrvEffect_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetAttributeEnv
@brief          Set nightmode attribute

@param[in]    eVal (on\off)
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetNightMode(CameraSrvEnv_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetFlashlight
@brief          Set flash light

@param[in]    eVal (on\off)
@param[in]    pfnSrvCameraCb			SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
*/
MAE_Ret SrvCameraSetFlashlight(CameraSrvFlashlight_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraSetFocusMode
@brief          Set focus mode

@param[in]    eVal (CAMERASRV_FOCUS_MODE__AUTO_FOCUS\CAMERASRV_FOCUS_MODE__TOUCH_TO_FOCUS)
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetFocusMode(CameraSrvFocusMode_e eVal, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraGetCaptureQuota
@brief  The interface is use to get how many pictures could take in the storage.

@param[in]    eResolution   set resolution of pictures for estimation.
@param[in]    eQuality   set quality of pictures for estimation.
@param[in]    pfnSrvCameraCb   SrvCameraGetImageBufferDataCb call back function point to response the geting ImageBuffer request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraGetCaptureQuota(CameraSrvStorage_e eStorage, CameraSrvPicResolution_e eResolution, CameraSrvImgQuality_e eQuality, SrvCameraGetQuotaCb pfnSrvCameraCb);

/**
 SrvCameraEnableMotionDetect
@brief  The interface is used to enable motion detection by camera.

@param[in]    eDevID    Device ID
@param[in]    pfnSrvCameraCb   callback
*/
MAE_Ret SrvCameraEnableMotionDetect(CameraSrvDev_e eDevID, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraDisableMotionDetect
@brief  The interface is used to disable motion detection by camera.

@param[in]    pfnSrvCameraCb   callback
*/
MAE_Ret SrvCameraDisableMotionDetect(SrvCameraCommonCb pfnSrvCameraCb);

/*-----------------------------------------------------*/

/**
 SrvCameraSetInitConfigure
@brief  The interface is use to set default driver setting

@param[in]    CameraSrvSettings_t   set configure of pictures for default setting.
@param[in]    SrvCameraCommonCb   SrvCameraGetImageBufferDataCb call back function point to response the geting ImageBuffer request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraSetInitConfigure(CameraSrvSettings_t *pConfig, SrvCameraCommonCb pfnCameraSrvCb);

/*The following APIs are v2.01 only*/
/**
 SrvCameraStartCapture
@brief  The interface is use to take pictures

@param[in]    pConfig            camera configurations information (Resolution, Quality, ORIENTATION, MultiShot, Sticker)
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the start capture request
 */
MAE_Ret SrvCameraStartCapture(CameraSrvCaptureConfig_t *pConfig, SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraStopCapture
@brief  The interface is use to stop capture

@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the stop capture request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraStopCapture(SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraGetFilename
@brief  The interface is use to get filename(s)

@param[out]   pFileName        filename
@param[out]   nLen               the length of filename
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the get image request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraGetImageFile(MAE_WChar *pFileName, u16 nLen, SrvCameraGetImageFileCb pfnSrvCameraCb);

/**
 SrvCameraGetImage
@brief  The interface is use to get image data

@param[in]    eCamImageType    indicate what kind of rawdata (RGB565 or jpeg format)
@param[out]   pRawData           Pointer to the rawdata of taking picture
@param[out]   nDataSize           the length of rawdata
@param[in]    pfnSrvCameraCb   SrvCameraGetImageBufferDataCb call back function point to response the geting ImageBuffer request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraGetImageBufferData(CameraSrvImgDataType_e eCamImageType, u8 *pRawData, u32 nDataSize, SrvCameraGetImageBufferDataCb pfnSrvCameraCb);

/**
 SrvCameraSetInterruptCb
@brief          Register the camera callback function to listen the event such as suspend or resume.
@brief          deregister the camera callback function by pass NULL callback function

@param[in]    pfnSrvCameraCb        SrvCameraStatusChangeCb call back function point to handle these event
 */
MAE_Ret SrvCameraSetInterruptNotifyCb(SrvCameraInterruptNotifyCb pfnSrvCameraCb);

/**
 SrvCameraSetCameraStatusChangeCb
@brief          Register the camera callback function to listen status of camera such as playing shutter sound, capturing picture,
@brief          deregister the camera callback function by pass NULL callback function

@param[in]    pfnSrvCameraCb        SrvCameraStatusChangeCb call back function point to handle these change
 */
MAE_Ret SrvCameraSetCameraStatusChangeCb(SrvCameraStatusChangeCb pfnSrvCameraCb);

/**
 SrvCameraTurnOnShutterSound
@brief  The interface is use to set camera shutter sound

@param[in]    eSoundLocation    the location of sound data source (phone, card, mmp, bb)
@param[in]    pSoundData         the sound's raw data
@param[in]    nLen                   the length of raw data
@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the turn on shutter sound request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraTurnOnShutterSound(CameraSrvSoundType_e eSoundLocation,
                                   u8 *pSoundData,
                                    u32 nLen,
                                    SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraTurnOffShutterSound
@brief  The interface is use to turn off camera shutter sound

@param[in]    pfnSrvCameraCb   SrvCameraCommonCb call back function point to response the turn off shutter sound request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraTurnOffShutterSound(SrvCameraCommonCb pfnSrvCameraCb);

/**
 SrvCameraLockAE
@brief  The interface is use to turn on/off AE

@param[in]    IsEnabled                          to indicate the LOCK AE mode is enable or disable
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraLockAE(boolean bEnable);

/**
 SrvCameraLockAWB
@brief  The interface is use to turn on/off AWB

@param[in]    IsEnabled                          to indicate the LOCK AWB mode is enable or disable
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCameraLockAWB(boolean bEnable);

/**
 SrvCameraIsEffectSupport
@brief  The interface is use to check the effect is supported or not

@param[in]    eCameffectType                      camera effect type.
@retval		TRUE                        If the effect is supported.
@retval		FALSE                       If the effect isn't supported.
 */
boolean SrvCameraIsEffectSupport(CameraSrvEffect_e eCameffectType);

#endif //__MMI_SRV_CAMERA_H__

