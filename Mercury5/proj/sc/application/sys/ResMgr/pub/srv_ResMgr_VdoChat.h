/**
* @file srv_ResMgr_VdoChat.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of VideoChat.
*
*/

#ifndef __SRV_RESMGR_VDOCHAT_H__
#define __SRV_RESMGR_VDOCHAT_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_vc_itf.h"
#include "MediaRspItf.h"
#include "srv_ResMgr_MmlManager.h"
#include "ABL_Cam.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

typedef enum  ABL_VdoChatErrCode_e_
{
    ABL_VDOCHAT_OK,                     //ESL_VC_OK
    ABL_VDOCHAT_FAIL,                   //ESL_VC_FAIL
    ABL_VDOCHAT_PARAM_ERROR,            //ESL_VC_PARAM_ERROR
    ABL_VDOCHAT_MEM_ALLOC_ERROR,        //ESL_VC_MEM_ALLOC_ERROR
    ABL_VDOCHAT_REJECT,                 //ESL_VC_REJECT
    ABL_VDOCHAT_ABORT,                  //ESL_VC_ABORT
    ABL_VDOCHAT_TIMEOUT,                //ESL_VC_TIMEOUT
    ABL_VDOCHAT_DENY,
    ABL_VDOCHAT_MERGE
} ABL_VdoChatErrCode_e;

typedef enum ABL_VdoChatCamId_e_
{
    ABL_VDOCHAT_CAM_ID_MAIN,            //ESL_VC_CAM_ID_MAIN
    ABL_VDOCHAT_CAM_ID_SUB              //ESL_VC_CAM_ID_SUB
}ABL_VdoChatCamId_e;

typedef enum ABL_VdoChatSwitch_e_
{
    ABL_VDOCHAT_OFF,                    //ESL_VC_OFF
    ABL_VDOCHAT_ON                      //ESL_VC_ON
}ABL_VdoChatSwitch_e;

typedef enum ABL_VdoChatControl_e_
{
    ABL_VDOCHAT_STOP,                   //ESL_VC_STOP
    ABL_VDOCHAT_START,                  //ESL_VC_START
    ABL_VDOCHAT_GETFRAME,               //ESL_VC_GETFRAME
}ABL_VdoChatControl_e;

typedef enum ABL_VdoChatIndex_e_
{
    ABL_VDOCHAT_PRIMARY,                //ESL_VC_PRIMARY
    ABL_VDOCHAT_SECONDARY               //ESL_VC_SECONDARY
}ABL_VdoChatIndex_e;

typedef enum ABL_VdoChatColorFormat_e_
{
    ABL_VDOCHAT_YUV420 = 0,             //ESL_VC_YUV420
    ABL_VDOCHAT_RGB565 = 1              //ESL_VC_RGB565
}ABL_VdoChatColorFormat_e;

typedef esl_Vc_Buff_t ABL_VdoChatBuff_t;
typedef esl_Vc_Size_t ABL_VdoChatSize_t;
//typedef esl_Vc_Source_t ABL_VdoChatSource_t;
//typedef esl_Vc_Destination_t ABL_VdoChatDestination_t;
typedef esl_VcInfo_t ABL_VdoChatInfo_t;
typedef void (*ABL_VdoChatCb)(u16 uSenderId, u32 uUserValue, ABL_VdoChatErrCode_e eErrCode, ABL_VdoChatInfo_t *pCamInfo);

typedef struct
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_VdoChatCb pfnCb;
}ABL_VdoChatCb_t;

typedef struct  ABL_VdoChatInit_t_
{
    esl_VcCamID_e eCamId;
}ABL_VdoChatInit_t;

typedef struct ABL_VdoChatExit_t_
{
    esl_VcCamID_e eCamId;
}ABL_VdoChatExit_t;

typedef struct ABL_VdoChatPreview_t_
{
    esl_Vc_Index_e eIndex;
    esl_Vc_Control_e ePreviewControl;
    esl_Vc_Size_t tFrameSize;
    esl_Vc_Colorformat_e eFormat;
    esl_Vc_Buff_t tBufferInfo;
}ABL_VdoChatPreview_t;

typedef struct
{
    ABL_VdoChatSize_t tFrameSize;
    ABL_VdoChatColorFormat_e eFormat;
    ABL_VdoChatBuff_t tBuff;
}ABL_VdoChatSource_t;

typedef struct
{
    ABL_VdoChatSize_t tFrameSize;
    ABL_VdoChatColorFormat_e eFormat;
    ABL_VdoChatBuff_t tBuff;
    u16 uX0;
    u16 uY0;
    u16 uPitch;
}ABL_VdoChatDestination_t;//ABL_VdoChatSource_t;//typedef esl_Vc_Destination_t ABL_VdoChatDestination_t;


typedef struct
{
    esl_Vc_Source_t tSource;
    esl_Vc_Destination_t tDest;
}ABL_VdoChatConvert_t;

typedef MmlCameraGetPreviewFrame_t ABL_CameraGetPreviewFrame_t;
typedef MmlCameraSetFrameBufferSize_t ABL_VdoChatFrameParam_t;

typedef struct VdoChatCmd_t_
{
    ABL_VdoChatCb_t *pCbParams;
    u32 uHandle;
    union
    {
        ABL_CameraStartPreview_t    tCameraStartPreview;
        ABL_CameraGetPreviewFrame_t tCameraGetPreviewFrame;
        ABL_VdoChatInit_t           tVdoChatInitParams;
        ABL_VdoChatExit_t           tVdoChatExitParams;
        ABL_VdoChatPreview_t        tVdoChatPreviewParams;
        ABL_VdoChatConvert_t        tVdoChatConvertParams;
        ABL_VdoChatFrameParam_t     tVdoChatFrameParams;
    } tParams;
} VdoChatCmd_t;

typedef struct ABL_VdoChatRspInfo_t_
{
    ABL_VdoChatErrCode_e eErrCode;
    ABL_VdoChatInfo_t tVdoChatInfo;
    u32 uExtInfo;
}ABL_VdoChatRspInfo_t;

typedef struct DBLVdoChatRemapErrCode_t_
{
    ABL_VdoChatErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLVdoChatRemapErrCode_t;

/*=============================================================*/
// Type Declarations
/*=============================================================*/
void ABL_VdoChatOpenSessionReq(ResMgr_AppId_e eAppId, ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatCloseSessionReq(ResMgr_AppId_e eAppId, ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatInitReq(ResMgr_AppId_e eAppId, ABL_VdoChatCamId_e eCamId, ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatExitReq(ResMgr_AppId_e eAppId, ABL_VdoChatCamId_e eCamId, ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatPreviewStartReq(ResMgr_AppId_e eAppId,
                                ABL_VdoChatIndex_e eIndex,
                                ABL_VdoChatSize_t *pFrameSize,
                                ABL_VdoChatColorFormat_e eFormat,
                                ABL_VdoChatBuff_t *pBufferInfo,
                                ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatPreviewStopReq(ResMgr_AppId_e eAppId,
                               ABL_VdoChatIndex_e eIndex,
                               ABL_VdoChatSize_t *pFrameSize,
                               ABL_VdoChatColorFormat_e eFormat,
                               ABL_VdoChatBuff_t *pBufferInfo,
                               ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatPreviewGetFrameReq(ResMgr_AppId_e eAppId,
                                   ABL_VdoChatIndex_e eIndex,
                                   ABL_VdoChatSize_t *pFrameSize,
                                   ABL_VdoChatColorFormat_e eFormat,
                                   ABL_VdoChatBuff_t *pBufferInfo,
                                   ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatConvertImageReq(ResMgr_AppId_e eAppId,
                                                              ABL_VdoChatSource_t *pSource,
                                                              ABL_VdoChatDestination_t *pDest,
                                                              ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatInitSyncReq(ResMgr_AppId_e eAppId, ABL_VdoChatCamId_e eCamId, ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatExitSyncReq(ResMgr_AppId_e eAppId, ABL_VdoChatCamId_e eCamId, ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatPreviewStartSyncReq(ResMgr_AppId_e eAppId,
                                ABL_VdoChatIndex_e eIndex,
                                ABL_VdoChatSize_t *pFrameSize,
                                ABL_VdoChatColorFormat_e eFormat,
                                ABL_VdoChatBuff_t *pBufferInfo,
                                ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatPreviewStopSyncReq(ResMgr_AppId_e eAppId,
                               ABL_VdoChatIndex_e eIndex,
                               ABL_VdoChatSize_t *pFrameSize,
                               ABL_VdoChatColorFormat_e eFormat,
                               ABL_VdoChatBuff_t *pBufferInfo,
                               ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatPreviewGetFrameSyncReq(ResMgr_AppId_e eAppId,
                                   ABL_VdoChatIndex_e eIndex,
                                   ABL_VdoChatSize_t *pFrameSize,
                                   ABL_VdoChatColorFormat_e eFormat,
                                   ABL_VdoChatBuff_t *pBufferInfo,
                                   ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatConvertImageSyncReq(ResMgr_AppId_e eAppId,
                                                              ABL_VdoChatSource_t *pSource,
                                                              ABL_VdoChatDestination_t *pDest,
                                                              ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatSetFrameBuffSize(ResMgr_AppId_e eAppId,
                                ABL_VdoChatIndex_e eIndex,
                                u16 nWidth,
                                u16 nHeight,
                                ABL_VdoChatColorFormat_e eColorFormat,
                                ABL_VdoChatCb_t *pVdoChatCb,
                                bool bSync);
void ABL_VdoChatSetFrameBuffSizeReq(ResMgr_AppId_e eAppId,
                                ABL_VdoChatIndex_e eIndex,
                                u16 nWidth,
                                u16 nHeight,
                                ABL_VdoChatColorFormat_e eColorFormat,
                                ABL_VdoChatCb_t *pVdoChatCb);
void ABL_VdoChatSetFrameBuffSizeSyncReq(ResMgr_AppId_e eAppId,
                                ABL_VdoChatIndex_e eIndex,
                                u16 nWidth,
                                u16 nHeight,
                                ABL_VdoChatColorFormat_e eColorFormat,
                                ABL_VdoChatCb_t *pVdoChatCb);

#endif

