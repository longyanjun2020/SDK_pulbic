/**
* @file DBL_Cam.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of Camera.
*
*/

#ifndef __DBL_CAM_H__
#define __DBL_CAM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"
#include "ABL_Cam.h"
#include "esl_cam_itf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
// Jeff TODO: needs to check
s16 DBL_CamQueryNoneSavingFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamDeleteTempVideoFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamSaveVideoFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamAbortSavingVideoFile(ResMgr_CmdHdl_t pCurCmdHdl);

void DBL_CamCmnCb(u16 uSenderId, u32 uUserValue, esl_CamErrCode_e eErrCode, esl_CamInfo_t *pCamInfo);
void DBL_MmlCamCmnCb(u16 uSenderId, u32 uUserValue, MmlCameraResult_e eErrCode, MmlCameraResponse_t *pCamInfo);
void DBL_MmlVDRCmnCb(u16 uSenderId, u32 uUserValue, MmlVideoResult_e eErrCode, MmlVideoResponse_t *pCamInfo);
void DBL_MmlImageCmnCb(u16 uSenderId, u32 uUserValue, MmlImageResult_e eErrCode, MmlImageResponse_t *pCamInfo);
s16 DBL_CamOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamSetConfig(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamSetConfig(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamSetAttribution(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamPreview(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamPreviewStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamFocus(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamCapture(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamCapture(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamCaptureStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamCaptureStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamAbortPanoramaCapture(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamRecordStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamRecordStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamGetFileName(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamSetRecordSetting(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamSaveRecordingFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamDiscardRecordingFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamGetImage(ResMgr_CmdHdl_t pCurCmdHdl);
#ifdef __CAMERA_QRCODE_MMI__
s16 DBL_CamGetQRC(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamQRCStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamQRCStop(ResMgr_CmdHdl_t pCurCmdHdl);
#endif
#ifdef __CAMERA_STICKER_MMI__
s16 DBL_MmlCamSetSticker(ResMgr_CmdHdl_t pCurCmdHdl);
#endif
s16 DBL_CamGetStatus(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_CamRegNotify(u16 uEvtType, void *pCusData, DBL_CamNotifyCb CamNotifyCb);
void DBL_CamEvtNotify(u16 uSenderId, u32 uUserValue, DBL_CamNotifyInfo *pNotifyInfo);
void DBL_MmlCamEvtNotify(u16 uSenderId, u32 uUserValue, MmlCameraNotify_t *pNotifyInfo);
void DBL_MmlVDREvtNotify(u16 uSenderId, u32 uUserValue, MmlVideoNotify_t *pNotifyInfo);
ABL_CamErrCode_e DBL_CamRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_CamErrCode_e DBL_MmlCamRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_CamErrCode_e DBL_MmlVDRRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_CamErrCode_e DBL_MmlImageRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
void DBL_MmlCamUpdatePos(ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
void DBL_MmlImageEvtNotify(u16 uSenderId, u32 uUserValue, MmlImageNotify_t *pNotifyInfo);
s16 DBL_MmlCamGetCaptureQuota(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamGetCameraInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamGetCaptureCapability(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamGetRecordingCapability(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamEnableMotionDetect(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlCamDisableMotionDetect(ResMgr_CmdHdl_t pCurCmdHdl);
#endif //__DBL_CAM_H__
