/**
 *
 * @file    ema_cam_msg.h
 *
 * @brief   This module defines the EMA camera message struct type for camera interface using.
 *
 * @author  Gary Lu
 * @version $Id: ema_cam_msg.h 14276 2008-09-22 06:27:36Z gary.lu $
 *
 */
#ifndef __EMA_CAM_MSG_H__
#define __EMA_CAM_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_cam_itf.h"




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef enum{
	EMA_MEDIUM_AUD,
	EMA_MEDIUM_CAM,
	EMA_MEDIUM_AUDCAM
}EmaRecMedium_e;

typedef struct{
	esl_CamID_e camID;
}ema_CamInit_t;

typedef struct{
	esl_CamID_e camID;
}ema_CamExit_t;

typedef struct{
	esl_CamPreview_e    camPreview;  
	esl_CamDispRegion_t camDispRegion;
}ema_CamPreview_t;

typedef struct{
  esl_CamMedium_t camMedium;
}ema_CamSetMdeium_t;

typedef struct{
	esl_CamAWB_e camAWB;
}ema_CamSetAWB_t;

typedef struct{
	esl_CamAE_e camAE;
}ema_CamSetAE_t;

typedef struct{
	esl_CamZoom_e camZoom;
}ema_CamSetZoom_t;

typedef struct{
	esl_CamEV_e camEV;
}ema_CamSetEV_t;

typedef struct{
	esl_CamAntiFlicker_e  camAntiFlicker;
}ema_CamSetAntiFlicker_t;

typedef struct{
	esl_CamImgEffect_e  camImgEffect;
}ema_CamSetImgEffect_t;

typedef struct{
	esl_CamNightMode_e  camNightMode;
}ema_CamSetNightMode_t;

typedef struct{
	esl_CamJpegSetting_t  camJPEGSetting;
}ema_CamCapture_t;

typedef struct{
	esl_CamFileName_t  camFileName;
}ema_CamGetFile_t;

typedef struct{
	esl_CamImg_t  camImg;
}ema_CamGetImg_t;

typedef struct{
	esl_CamStatus_e  camStatus;
}ema_CamGetStatus_t;

typedef struct{
	esl_CamVdoSetting_t  camVideoSetting;
}ema_CamRecord_t;

typedef struct{
  esl_CamNotifyType_e camNotifyType;
	esl_CamNotifyCb_t  camNotifyCb;
}ema_CamRegNotify_t;

typedef struct{
	esl_CamNotifyType_e  notifyType;
	esl_CamRecError_e    recErr;
}ema_CamSendNotifyCmd_t;

typedef struct{
	u8             isEnable;
	esl_CamSound_t camSound;
}ema_CamSetSoundCmd_t;

typedef struct{
  u8             isEnable;
	u8             *pSticker;
}ema_CamSetStickerCmd_t;

typedef struct{
	esl_CamQRCSetting_t  camQRCSetting;
}ema_CamQRCCmd_t;

typedef struct{
	esl_CamGetQRC_t  camGetQRC;
}ema_CamGetQRCCmd_t;

typedef struct{
    esl_CamRecSaveInfo_t camRecSaveInfo;
} ema_CamRecSaveCmd_t;

typedef struct{
	esl_CamGetZoomInfo_t  camGetZoomInfo;
}ema_CamGetZoomInfoCmd_t;

typedef struct{
  esl_CamGetQuota_t    camSettings;
}ema_CamGetCaptureQuota_t;


typedef struct{
	ema_TransType_t	TransType;
	esl_CamCb_t     *pCamDoneCB;
	union
	{
        ema_CamInit_t			camInitCmd;
        ema_CamExit_t			camExitCmd;
        ema_CamPreview_t        camPreviewCmd;
        ema_CamSetMdeium_t	    camSetMdeiumCmd;
        ema_CamSetAWB_t         camSetAWBCmd;
        ema_CamSetAE_t          camSetAECmd;
        ema_CamSetZoom_t        camSetZoomCmd;
        ema_CamSetEV_t          camSetEVCmd;
        ema_CamSetAntiFlicker_t camSetAntiFlickerCmd;
        ema_CamSetImgEffect_t   camSetImgEffectCmd;
        ema_CamSetNightMode_t   camSetNightModeCmd;
        ema_CamCapture_t        camCaptureCmd;
        ema_CamRecord_t         camVideoRecCmd;
        ema_CamGetFile_t        camGetFileCmd;
        ema_CamGetImg_t         camGetImgCmd;
        ema_CamGetStatus_t      camGetStatusCmd;
        ema_CamRegNotify_t      camRegNotifyCmd;
        ema_CamSendNotifyCmd_t  camSendNotifyCmd;
        ema_CamSetSoundCmd_t    camSetSoundCmd;
        ema_CamSetStickerCmd_t  camSetStickerCmd;
        ema_CamQRCCmd_t         camQRCCmd;
        ema_CamGetQRCCmd_t      camGetQRCCmd;
        ema_CamRecSaveCmd_t     camRecSaveCmd;
        ema_CamGetZoomInfoCmd_t camGetZoomInfoCmd;
        ema_CamGetCaptureQuota_t camGetCaptureQuotaCmd;
	} cmdType;
} ema_CamCmd_t;

typedef struct{
	u16             sender;
	ema_TransType_t	  TransType;
	ema_ErrCode_e errorStatus;
} ema_CamRsp_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __EMA_CAM_MSG_H__ */

