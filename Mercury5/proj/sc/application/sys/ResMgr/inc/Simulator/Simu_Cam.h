/**
* @file Simu_Cam.h
*
* This header file defines the interface of lower layer device simulation for camera
*
*/
#ifndef __SIMU_CAM_H__
#define __SIMU_CAM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"
#include "ABL_Cam.h"
// for WB test
#include "srv_resmgr_mmlimage_types.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct SimuImgCapWBUserData_t_
{
    u32 ImgWBId;
    u32 nData;
    MmlImageUCParam_t ImgCapUCParam;
}SimuImgCapWBUserData_t;


/**
 * @brief Indicate image-capture unit testing scenerio
 */
typedef enum
{
  SIMU_IMG_CAP_ALL_SUCESS = 0x00,       /* all encode success                                 */
  SIMU_IMG_CAP_FOLDER_NOT_EXIST, /* encode happen the designed path is not exist error */
  SIMU_IMG_CAP_STOP_ERROR,       /* stop encoding fail                                 */
  SIMU_IMG_CAP_NO_FREE_SPACE,    /* encode happen no free space error in Nth capture   */
  SIMU_IMG_CAP_UNKNOWN_ERROR,    /* encode happen unknown error in Nth capture         */
} SimuImgCapWbErr_e;


/**
 * @brief Indicate the value of Nth capture if SIMU_IMG_CAP_NO_FREE_SPACE,
 *        or SIMU_IMG_CAP_UNKNOWN_ERROR happened.
 */
typedef struct
{
  u8  nCaptureIndex;  /* indicate which capture will happen error */
} SimuImgCapWbErrNoFreeSpace_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void DBL_CamCmnMMWBCb(u16 uSenderId, u32 uUserValue, esl_CamErrCode_e eErrCode, esl_CamInfo_t *pCamInfo);
void Simu_CamOpenCb(void *pUserData);
void Simu_CamCloseCb(void *pUserData);
void Simu_CamSetConfigCb(void *pUserData);
void Simu_CamSetAttrCb(void *pUserData);
void Simu_CamPreviewCb(void *pUserData);
void Simu_CamPreviewStopCb(void *pUserData);
void Simu_CamFocusCb(void *pUserData);
void Simu_CamCaptureCb(void *pUserData, u8 nPicNum);
void Simu_CamCaptureStopCb(void *pUserData);
void Simu_CamAbortPanoramaCaptureCb(void *pUserData);
void Simu_CamQRCStartCb(void *pUserData);
void Simu_CamQRCStopCb(void *pUserData);
void Simu_CamRecordStartCb(void *pUserData);
void Simu_CamRecordStopCb(void *pUserData);
void Simu_CamQueryNoneSavingFile(void *pUserData);
void Simu_CamDeleteTempVideoFile(void *pUserData);
void Simu_CamSaveVideoFile(void *pUserData);
void Simu_CamAbortSavingVideoFileAction(void *pUserData);
void Simu_CamGetFileNameCb(void *pUserData, ABL_CamGetFile_t *pFileInfo);
void Simu_CamGetImageCb(void *pUserData, ABL_CamImg_t *pImageInfo);
void Simu_CamGetQRCCb(void *pUserData);
void Simu_CamSetStickerCb(void *pUserData);
void Simu_CamGetStatusCb(void *pUserData);
void Simu_CamGetCaptureQuotaCb(void *pUserData);
void Simu_CamEnableMotionDetectCb(void *pUserData);
void Simu_CamDisableMotionDetectCb(void *pUserData);
void Simu_CamGetCameraInfoCb(void *pUserData, ABL_CameraGetCameraInfo_t *pGetCameraInfo);
void Simu_CamGetCaptureCapabilityCb(void *pUserData, void *pParam);
void Simu_CamGetRecordingCapabilityCb(void *pUserData, void *pParam);
void Simu_CamWBTc1(void *pUserData);
void Simu_CamWBTc2(void *pUserData);
void Simu_CamWBTc3(void *pUserData);
void Simu_CamWBTc4(void *pUserData);
void Simu_CamWBTc5(void *pUserData);
void Simu_CamWBTc6(void *pUserData);
void Simu_CamWBTc7(void *pUserData);
#endif //__SIMU_CAM_H__
