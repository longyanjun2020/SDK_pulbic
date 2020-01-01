/**
 *
 * @file    ema_aud_msg.h
 *
 * @brief   This module defines the EMA audio message struct type for camera interface using.
 *
 * @author  Roger Lai
 * @version $Id: ema_aud_msg.h 10532 2008-05-14 13:39:26Z roger.lai $
 *
 */
#ifndef __EMA_AUD_MSG_H__
#define __EMA_AUD_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "ema.h"


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

typedef struct              /*Get sample rate*/
{
  esl_AudFileParam_t fileParam;
} ema_AudRecGetMedium_t;

typedef struct              /*Get sample rate*/
{
  esl_AudFileParam_t fileParam;
} ema_AudGetFileInfo_t;


typedef struct              /*Get sample rate*/
{
  esl_AudFileParam_t fileParam;
} ema_AudSampleRate_t;

typedef struct              /*Get total time*/
{
  esl_AudFileParam_t fileParam;
} ema_AudGetTotalTime_t;

typedef struct
{
  esl_AudRecParam_t recParam;
} ema_AudRecParam_t;

typedef struct
{
  esl_AudRecTimeParam_t recTimeParam;
} ema_AudRecTimeParam_t;

typedef struct
{
  esl_AudFileParam_t  fileParam;
  u32                 position;
} ema_AudPlayFileParam_t;

typedef struct
{
  esl_AudStreamParam_t  streamParam;

} ema_AudPlayStreamParam_t;

typedef struct
{
  esl_AudMemoryParam_t  memoryParam;

} ema_AudPlayMemoryParam_t;

typedef struct
{
  esl_AudStreamParam_t  streamParam;

} ema_AudGetStreamInfo_t;

typedef struct
{
  esl_AudMemoryParam_t  memoryParam;

} ema_AudGetMemoryInfo_t;

typedef struct              /*Read ID3 Tag*/
{
  esl_AudFileParam_t    fileParam;
  esl_AudID3V1Info_t    *pID3Info;
} ema_AudGetID3_t;

typedef struct
{
  u8                      mode;
  esl_AudFileParam_t      fileParam;
  esl_AudAdvancedInfo_t    *pAdvancedInfo;
} ema_AudGetAdvancedInfo_t;

typedef struct{
	esl_AudNotifyType_e  notifyType;
	esl_AudNotifyErr_e   notifyErr;
}ema_AudSendNotifyCmd_t;

typedef struct{
  esl_AudNotifyType_e notifyType;
  esl_AudNotifyCb_t  notifyCb;
}ema_AudRegNotify_t;

typedef struct{
    esl_AudPEQ_t PEQSetting;
}ema_PEQSettings_t;

#ifdef __BLUETOOTH_A2DP_DRV__
typedef struct{
  esl_AudA2dpCb_t a2dpCb;
}ema_AudRegA2dp_t;
#endif

typedef struct{
  esl_AudEQ_e               userPEQType;
  esl_AudUserPEQConfig_t    userPEQConfig;
}ema_UserPEQConfigs_t;

typedef struct
{
  //Primitive       prim;

  //ema_TransType_e TransType;

  esl_AudCb_t  *pAudDoneCB;

  esl_AudInfo_t *pAudGetRsp;

  union
  {

    bool        onoff;
    u8          EQ;
    u8          thrD_Effect;
    u32  position;
    u16  PlaySpeed;
    s8          VolDPGA_val;
    u32         btCapability;
    u32         PEQTableAddress;

    ema_AudPlayFileParam_t    playFile;
    ema_AudPlayMemoryParam_t  playMemory;
    ema_AudPlayStreamParam_t  playStream;
    ema_AudRecParam_t         recFile;
    ema_AudRecTimeParam_t     recTime;
    ema_AudRecGetMedium_t     recMedium;
    ema_AudGetID3_t           ID3Tag;
    ema_AudGetFileInfo_t      getFileInfoParam;
    ema_AudGetStreamInfo_t    getStreamInfoParam;
    ema_AudGetMemoryInfo_t    getMemoryInfoParam;
    ema_AudGetAdvancedInfo_t  advancedInfoParam;
    ema_AudSendNotifyCmd_t    notifyCmdParam;
    ema_AudRegNotify_t        audRegNotifyParam;
    ema_PEQSettings_t   peqSettings;
    ema_UserPEQConfigs_t      userPEQParam;
#ifdef __BLUETOOTH_A2DP_DRV__
    ema_AudRegA2dp_t          a2dpRegCbParam;
#endif

  } param;

} ema_AudCmd_t;

typedef struct {
  //u16             prim;
  u16             sender;
  //ema_TransType_e TransType;
  ema_ErrCode_e errorStatus;
} ema_AudRsp_t;



/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_AUD_MSG_H__ */

