/**
 *
 * @file    ema_tv_msg.h
 *
 * @brief   This module defines the EMA tvera message struct type for tvera interface using.
 *
 * @author  Gary Lu
 * @version $Id: ema_tv_msg.h 14276 2008-09-22 06:27:36Z gary.lu $
 *
 */
#ifndef __EMA_TV_MSG_H__
#define __EMA_TV_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_tv_itf.h"




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define DefExtern
#else
#define DefExtern extern
#endif




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

typedef struct{
  esl_TvType_e type;
}ema_TvOpen_t;

typedef struct{
  esl_TvType_e type;
}ema_TvCloset_t;

typedef struct{
  esl_TvPreview_t    tvPreview;  
  esl_TvDispRegion_t tvDispRegion;
}ema_TvPreview_t;

typedef struct{
  esl_TvRegion_t        region;
  esl_TvRotate_e        rotateAngle;
} ema_TvResetWindow_t;

typedef struct{
  esl_TvJpegSetting_t  tvJPEGSetting;
}ema_TvCapture_t;

typedef struct{
  esl_TvRecSetting_t  tvRecordSet;
}ema_TvRecordCmd_t;

typedef struct{
  esl_TvType_e   type;
  esl_TvConfig_t config;
}ema_TvSetConfig_t;


typedef struct{
  u8            isEnable;
  esl_TvSound_t sound;
}ema_TvSetSoundCmd_t;

typedef struct{
  esl_TvNotifyCb_t    notifyCb;
  esl_TvNotifyType_e  notifyType;
} ema_TvRegNotify_t;

typedef struct{
  u8            *pBuffer;
  u32           bufferLens;
  u32           userDefData;
  u32           payLoadData;  
  u8            mode;
}ema_TvStreamDataCmd_t;

typedef struct{
  u16           frequency;
}ema_TvGetEmInfoCmd_t;

typedef struct{
  ema_TransType_t TransType;
  esl_TvCb_t     *pTvDoneCB;
  union
  {
    ema_TvOpen_t           tvOpenCmd;
    ema_TvCloset_t         tvCloseCmd;
    ema_TvPreview_t        tvPreviewCmd;
    ema_TvCapture_t        tvCaptureCmd;
    esl_TvFileName_t       tvGetFileCmd;
    ema_TvSetConfig_t      tvSetConfigCmd;
    esl_TvScanConfig_t     tvScanCmd;
    esl_TvType_e           tvGetInfoCmd;
    ema_TvRegNotify_t      tvRegNotifyCmd;
    ema_TvSetSoundCmd_t    tvSetSoundCmd;
    ema_TvResetWindow_t    tvResetWinCmd;
    u32                    tvSwitchChCmd;
    esl_TvNotifyInfo_t     tvNotifyEMACmd;
    ema_TvStreamDataCmd_t  tvStreamDataCmd;
    ema_TvRecordCmd_t      tvRecordCmd;
    esl_TvSetFreq_t        tvSetFreqCmd;
    esl_TvCancelType_e     tvCancelCmd;
    esl_TvSoundChannel_e   tvMultiLanguageCmd;
    ema_TvGetEmInfoCmd_t   tvGetEmCmd;
  } cmdType;
} ema_TvCmd_t;





/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __EMA_TV_MSG_H__ */

