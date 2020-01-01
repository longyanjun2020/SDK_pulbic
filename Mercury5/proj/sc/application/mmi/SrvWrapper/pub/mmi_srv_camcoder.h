/**
* @file    mmi_srv_camcoder.h
* @brief
*
*/

#ifndef __MMI_SRV_CAMCODER_H__
#define __MMI_SRV_CAMCODER_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_camerasrv.h"
#include "ABL_Cam.h"


/*=============================================================*/
// Variable Declarations
/*=============================================================*/


/*=============================================================*/
// Private Function Implementations
/*=============================================================*/


/*=============================================================*/
// Public Function Implementations
/*=============================================================*/

typedef void(*SrvCamcoderCommonCB)(void *pThis, CameraSrvRetCode_e eRetCode);
typedef void(*SrvCamcoderInterruptNotifyCb)(void *pThis, CameraSrvInterruptNotify_t *pCbData);
typedef void(*SrvCamcoderStatusChangeCb)(void *pThis, CameraSrvCamStatusChange_t *pCbData);
typedef void(*SrvCamcoderGetVideoFileCB)(void *pThis, CameraSrvRetCode_e eRetCode, CameraSrvFileName_t *pGetFileName);
typedef void(*SrvCamcoderSaveFileCB)(void *pThis, CameraSrvRetCode_e eRetCode, CameraSrvFileName_t *pGetFileName);
typedef void(*SrvCamcoderInterruptNotifyCbEx)(void *pThis, CameraSrvInterruptNotifyEx_t *pCbData);
typedef void(*SrvCamcoderStatusChangeCbEx)(void *pThis, CameraSrvCamStatusChangeEx_t *pCbData);

/**
 SrvCameraOpenSession
@brief  The interface is use to open camcoder session
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderOpenSession(void);

/**
 SrvCamcoderCloseSession
@brief  The interface is use to close camcoder session
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderCloseSession(void);

/**
 SrvCamcoderOpen
@brief  The interface is use to open camcoder

@param[in]    eDevID                Device ID
@param[in]    eAppType              Application type, such as camera, recorder or engineering mode.
									(CAMERASRV_APP__PIC/CAMERASRV_APP__VDO/CAMERASRV_APP__EM)
@param[in]    pfnSrvCameraCb        SrvCamcoderCommonCB call back function point to response the Open request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderOpen(CameraSrvDev_e eDevID, CameraSrvAppType_e eAppType, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
SrvCamcoderClose
@brief  The interface is use to close camcoder

@param[in]    pfnSrvCameraCb   SrvCamcoderCommonCB call back function point to response the close request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
*/
MAE_Ret SrvCamcoderClose(SrvCamcoderCommonCB pfnSrvCameraCb);

/**
SrvCamcoderConfigStorage
@brief  The interface is use to set camcoder configurations such as address and

@param[in]    pConfig               The storage configuration information, if stored in sd card or NAND flash, the buffer address must be assign.
@param[in]    eCamStorage           The storage location -- SD Card, BB and NAND flash
									(CAMERASRV_STORAGE__CARD/CAMERASRV_STORAGE__CARD2/CAMERASRV_STORAGE__PHONE_EXTERNAL/CAMERASRV_STORAGE__PHONE_INTERNAL)
@param[in]    pfnSrvCameraCb        SrvCameraCommonCb call back function point to response the configuration request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderConfigStorage(CameraSrvStorageConfig_t *pConfig, CameraSrvStorage_e eCamStorage, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeAE
@brief          Set auto estimate light attribute

@param[in]      eVal                white balance type.
									(CAMERASRV_AWB__ON/CAMERASRV_AWB__CLOUDY/CAMERASRV_AWB__DAYLIGHT/CAMERASRV_AWB__FLUORESCENT/CAMERASRV_AWB__INCANDESCENCE)
@param[in]      pfnSrvCameraCb      SrvCameraCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetWB(CameraSrvAWB_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeAE
@brief          Set auto estimate light attribute

@param[in]      eVal                whole image, central win, ......
									(CAMERASRV_AE__WHOLE_IMAGE/CAMERASRV_AE__CENTRALWIN/CAMERASRV_AE__WEIGHTED_CENTRALWIN/CAMERASRV_AE__CENTRAL_POINT)
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetAE(CameraSrvAE_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeAF
@brief          Set auto focus attribute

@param[in]      eVal                auto focus on/off. (CAMERASRV_AF__OFF/CAMERASRV_AF__ON)
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetAF(CameraSrvAF_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeZoom
@brief          Set Zoom attribute

@param[in]      eVal                zoom in attribute (CAMERASRV_ZOOM__DEFAULT/CAMERASRV_ZOOM__1/CAMERASRV_ZOOM__2/CAMERASRV_ZOOM__3/CAMERASRV_ZOOM__4/CAMERASRV_ZOOM__5
									CAMERASRV_ZOOM__MAX/CAMERASRV_ZOOM__MIN/CAMERASRV_ZOOM__IN/CAMERASRV_ZOOM__OUT).
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetZoom(CameraSrvZoom_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeEV
@brief          Set EV value attribute

@param[in]      eVal                EV values (CAMERASRV_EV__MIN/CAMERASRV_EV__MINUS_1/CAMERASRV_EV__DEFAULT/CAMERASRV_EV__PLUS_1/
									CAMERASRV_EV__MAX/CAMERASRV_EV__ADD/CAMERASRV_EV__MINUS).
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetEV(CameraSrvEV_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeAntiFlicker
@brief          Set Anit Filcker attribute

@param[in]      eVal                Anti flicker value (CAMERASRV_ANTI_FLICKER__50HZ/CAMERASRV_ANTI_FLICKER__60HZ)
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetAntiFlicker(CameraSrvAntiFlicker_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeEffect
@brief          Set image effect attribute

@param[in]      eVal                The effect type (CAMERASRV_EFFECT__NORMAL/CAMERASRV_EFFECT__MONO/CAMERASRV_EFFECT__SEPIA/
									CAMERASRV_EFFECT__NEGATIVE/CAMERASRV_EFFECT__SKETCH/CAMERASRV_EFFECT__OIL_PAINTING/
									CAMERASRV_EFFECT__EMBOSS/CAMERASRV_EFFECT__MOSAIC/CAMERASRV_EFFECT__ZIPPER/CAMERASRV_EFFECT__BLUR).
@param[in]     pfnSrvCameraCb       SrvCamcoderCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetEffect(CameraSrvEffect_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeEnv
@brief          Set nightmode attribute

@param[in]      eVal                The night mode value (CAMERASRV_NIGHT_MODE__OFF/CAMERASRV_NIGHT_MODE__ON).
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetNightMode(CameraSrvEnv_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetAttributeVdoStabilizer
@brief          Set Video Stabilizer attribute

@param[in]      eVal                The video stabilizer value (CAMERASRV_VDO_STABILIZER__OFF/CAMERASRV_VDO_STABILIZER__ON).
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the setting request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSetVdoStabilizer(CameraSrvVdoStabilizer_e eVal, SrvCamcoderCommonCB pfnSrvCameraCb);


/**
 SrvCamcoderStartPreview
@brief  The interface is use to start camera/camcorder previewing

@param[in]      ePreviewType        the type of preview. (CAMERASRV_PREVIEW_TYPE__PORTRAIT/CAMERASRV_PREVIEW_TYPE__LANDSCAPE)
@param[in]      pPreviewRegion      the Region of preview
@param[in]      pOSDRegion          the Region of OSD
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the start preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderStartPreview(CameraSrvPreviewType_e ePreviewType,
                                 const CameraSrvRegion_t *pPreviewRegion,
                                 const CameraSrvRegion_t *pOSDRegion,
                                 SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderStopPreview
@brief  The interface is use to stop camera/camcorder previewing

@param[in]      pfnSrvCameraCb   SrvCamcoderCommonCb call back function point to response the stop preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderStopPreview(SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderStartRecord
@brief  The interface is use to start camcorder recording

@param[in]      pConfig             Camcoder configurations information (Resolution, Quality, Sound recording, Size limit, Time limit)
@param[in]      pfnSrvCameraCb      SrvCamcoderCommonCb call back function point to response the start record request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderStartRecord(CameraSrvRecordConfig_t *pConfig, SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderStopRecord
@brief  The interface is use to stop camcorder recording

@param[in]     pfnSrvCameraCb       SrvCamcoderCommonCb call back function point to response the stop record request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderStopRecord(SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderQueryNoneSavingFile
@brief  The interface is use to query if there are any none saving video file;

@param[in]      pfnSrvCameraCb   SrvCamcoderCommonCb call back function point to response the stop preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderQueryNoneSavingFile(SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderDeleteTempVideoFile
@brief  The interface is use to delete none saving video file;

@param[in]      pfnSrvCameraCb   SrvCamcoderCommonCb call back function point to response the stop preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderDeleteTempVideoFile(SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSaveVideoFile
@brief  The interface is use to save video file;

@param[in]      pfnSrvCameraCb   SrvCamcoderCommonCb call back function point to response the stop preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderSaveVideoFile(SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderAbortSavingVideoFile
@brief  The interface is use to abort saving video file;

@param[in]      pfnSrvCameraCb   SrvCamcoderCommonCb call back function point to response the stop preview request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
MAE_Ret SrvCamcoderAbortSavingVideoFile(SrvCamcoderCommonCB pfnSrvCameraCb);

/**
 SrvCamcoderSetInterruptCb
@brief          Register the camcoder callback function to listen the event such as suspend or resume.
@brief          P.S. deregister the camcoder callback function by pass NULL callback function.

@param[out]    pfnSrvCameraCb        SrvCamcoderStatusChangeCb call back function point to handle these event
 */
MAE_Ret SrvCamcoderSetInterruptNotifyCb(SrvCamcoderInterruptNotifyCb pfnSrvCameraCb);

/**
 SrvCamcoderSetInterruptCb
@brief          Register the camcoder callback function to listen status of camcoder such as
@brief          updating time position, recording error, stoping record, record space full.
@brief          P.S. Deregister the camcoder callback function by pass NULL callback function

@param[out]    pfnSrvCameraCb        SrvCamcoderStatusChangeCb call back function point to handle these change
 */
MAE_Ret SrvCamcoderSetCameraStatusChangeCb(SrvCamcoderStatusChangeCb pfnSrvCameraCb);

/**
 SrvCamcoderSetInterruptCb
@brief          Register the camcoder callback function to listen the event such as suspend or resume.
@brief          P.S. deregister the camcoder callback function by pass NULL callback function.

@param[out]    pfnSrvCameraCb        SrvCamcoderStatusChangeCb call back function point to handle these event
 */
MAE_Ret SrvCamcoderSetInterruptNotifyCbEx(SrvCamcoderInterruptNotifyCbEx pfnSrvCameraCb);

/**
 SrvCamcoderSetInterruptCb
@brief          Register the camcoder callback function to listen status of camcoder such as
@brief          updating time position, recording error, stoping record, record space full.
@brief          P.S. Deregister the camcoder callback function by pass NULL callback function

@param[out]    pfnSrvCameraCb        SrvCamcoderStatusChangeCb call back function point to handle these change
 */
MAE_Ret SrvCamcoderSetCameraStatusChangeCbEx(SrvCamcoderStatusChangeCbEx pfnSrvCameraCb);

/**
 SrvCamcoderGetFilename
@brief  The interface is use to get filename(s)

@param[out]   pFileName        filename
@param[out]   nLen               the length of filename
@param[out]    pfnSrvCameraCb   SrvCamcoderCommonCb call back function point to response the get video request
@retval		MAE_RET_SUCCESS             If successful.
@retval		MAE_RET_FAILED				It is not supported or failed.
 */
//v2.01 API
MAE_Ret SrvCamcoderGetVideoFile(MAE_WChar *pFileName, u16 nLen, SrvCamcoderGetVideoFileCB pfnSrvCameraCb);
//v2.02 API
MAE_Ret SrvCamcoderSaveFile(SrvCamcoderSaveFileCB pfnSrvCameraCb);

#endif //__MMI_SrvCamcoderH__

