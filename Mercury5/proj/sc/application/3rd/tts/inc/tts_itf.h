/**
*Copyright Statement:
*
*
* @file    tts_itf.h
* @author  mstarsemi.com
* @date
*
* interface declaration for 3rd party tts porting
*
*/
#ifndef    __TTS_ITF_H__
#define    __TTS_ITF_H__

#ifdef     __TTS__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


/*=============================================================*/
// Include files
/*=============================================================*/

#include "ven_prim_msg.h"
#include "ven_sdk.h"
#include "ven_dbg.h"
#include "ven_file.h"
#include "vm_msgt.ht"

#include "ivTTS.h"
#include "ivDefine.h"
#include "ivPlatform.h"


/*=============================================================*/
// Macro definition
/*=============================================================*/
//eventbase between tts & mmi task
//#define TTSEVENTBASE 0x00850000

/*=============================================================*/
// Constant define
/*=============================================================*/
// constant for file path
#define TTS_FILE_PATH_XFSDK  L"/CARD/.system/TTS/Resource.irf"

/*=============================================================*/
// Data type definition
/*=============================================================*/
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum
{
#include "tts_message_define__.hi"
} TTSCmdType_e;

typedef enum
{
    TTS_ERROR_SUCCESS,                      /**< Operation success       */
    TTS_ERROR_UNKNOWN,                      /**< Unkown error            */
    TTS_ERROR_INVALIVERSION,                /**< Invalid version         */
    TTS_ERROR_GETBUFFERSIZE,                /**< Get Buffer size failed  */
    TTS_ERROR_GETMEMORY,                    /**< Get Memory failed       */
    TTS_ERROR_KERNELINIT,                   /**< Kernel init failed      */
    TTS_ERROR_SETCODE,                      /**< set code failed         */
    TTS_ERROR_SETLANGUAGE,                  /**< set language failed     */
    TTS_ERROR_SETFORMAT,                    /**< set format failed       */
    TTS_ERROR_SETVOL,                       /**< set Vol failed          */
    TTS_ERROR_SETSPEAKMAN,                  /**< set speak man failed    */
    TTS_ERROR_SETOUTCALLBACK,               /**< set out callback failed */
    TTS_ERROR_DECODE,                       /**< TTS Decode faild        */
    TTS_ERROR_INPUT_PARAM,                  /**< TTS Input faild         */
    TTS_ERROR_NOT_INIT,                     /**< TTS          */
    TTS_ERROR_INPUT_MODE,
    TTS_ERROR_FILEOPEN,
    TTS_ERROR_GETSEMAPHORE,
    TTS_ERROR_INITSEMAPHORE,
    TTS_ERROR_STOPDECODE,                   /**< TTS stop decode         */
    TTS_ERROR_UNINITIALIZED,                /**< TTS has not inited      */
    TTS_ERROR_FAILED,                       /**< TTS Operation failed    */

}TTSErrorCode;

typedef enum
{
    TTS_STATUS_NONE,

}TTSStatus_e;

typedef enum
{
    TTS_READDIGIT_AUTO      = ivTTS_READDIGIT_AUTO,
    TTS_READDIGIT_AS_NUMBER = ivTTS_READDIGIT_AS_NUMBER,
    TTS_READDIGIT_AS_VALUE  = ivTTS_READDIGIT_AS_VALUE,
}TTSReadDigit_e;

typedef enum
{
    TTS_CHNUM1_READ_YAO     = ivTTS_CHNUM1_READ_YAO,
    TTS_CHNUM1_READ_YI      = ivTTS_CHNUM1_READ_YI,
}TTSChineseNumberOne_e;

typedef enum
{
    TTS_ROLE_YANPING        = ivTTS_ROLE_YANPING,
    TTS_ROLE_YUFENG         = ivTTS_ROLE_YUFENG,
    TTS_ROLE_NANNAN         = ivTTS_ROLE_NANNAN,
    TTS_ROLE_XIAOQIAN       = ivTTS_ROLE_XIAOQIAN,
    TTS_ROLE_XIAORONG       = ivTTS_ROLE_XIAORONG,
    TTS_ROLE_XIAOMEI        = ivTTS_ROLE_XIAOMEI,
    TTS_ROLE_JOHN           = ivTTS_ROLE_JOHN,
    TTS_ROLE_TERRY          = ivTTS_ROLE_TERRY,
    TTS_ROLE_JIUXU          = ivTTS_ROLE_JIUXU,
    TTS_ROLE_DUOXU          = ivTTS_ROLE_DUOXU,
    TTS_ROLE_XIAOPING       = ivTTS_ROLE_XIAOPING,
    TTS_ROLE_DONALDDUCK     = ivTTS_ROLE_DONALDDUCK,
    TTS_ROLE_BABYXU         = ivTTS_ROLE_BABYXU,
    TTS_ROLE_USER           = ivTTS_ROLE_USER,
}TTSRole_e;

typedef enum
{
    TTS_LANGUAGE_CHINESE    = ivTTS_LANGUAGE_CHINESE,
    TTS_LANGUAGE_ENGLISH    = ivTTS_LANGUAGE_ENGLISH,
}TTSLanguage_e;

typedef enum
{
    TTS_STYLE_PLAIN         = ivTTS_STYLE_PLAIN,
    TTS_STYLE_NORMAL        = ivTTS_STYLE_NORMAL,
}TTSStyle_e;

typedef enum
{
    TTS_SPEED_MIN           = ivTTS_SPEED_MIN,
    ///TTS_SPEED_LOW        = (ivTTS_SPEED_MIN/2),
    TTS_SPEED_NORMAL        = ivTTS_SPEED_NORMAL,
    ///TTS_SPEED_HIGH       = (ivTTS_SPEED_MIN/2),
    TTS_SPEED_MAX           = ivTTS_SPEED_MAX,
}TTSSpeed_e;

typedef enum
{
    TTS_PITCH_MIN           = ivTTS_PITCH_MIN,
    ///TTS_PITCH_LOW        = (ivTTS_PITCH_MIN/2),
    TTS_PITCH_NORMAL        = ivTTS_PITCH_NORMAL,
    ///TTS_PITCH_HIGH       = (ivTTS_PITCH_MIN/2),
    TTS_PITCH_MAX           = ivTTS_PITCH_MAX,
}TTSPitch_e;

typedef enum
{
    TTS_VOLUME_MIN          = ivTTS_VOLUME_MIN,
    ///TTS_VOLUME_LOW       = (ivTTS_VOLUME_MIN/2),
    TTS_VOLUME_NORMAL       = ivTTS_VOLUME_NORMAL,
    ///TTS_VOLUME_HIGH      = (ivTTS_VOLUME_MAX/2),
    TTS_VOLUME_MAX          = ivTTS_VOLUME_MAX,
}TTSVolumn_e;

typedef enum
{
    TTS_PLAYVOLUME_DEFAULT = 255,
    TTS_PLAYVOLUME_MIN = 0,
    TTS_PLAYVOLUME_0 = TTS_PLAYVOLUME_MIN,
    TTS_PLAYVOLUME_1,
    TTS_PLAYVOLUME_2,
    TTS_PLAYVOLUME_3,
    TTS_PLAYVOLUME_4,
    TTS_PLAYVOLUME_5,
    TTS_PLAYVOLUME_6,
    TTS_PLAYVOLUME_7,
    TTS_PLAYVOLUME_8,
    TTS_PLAYVOLUME_MAX = TTS_PLAYVOLUME_8
}TTSPlayVolumn_e;

typedef enum
{
    TTS_VEMODE_NONE         = ivTTS_VEMODE_NONE,
    TTS_VEMODE_WANDER       = ivTTS_VEMODE_WANDER,
    TTS_VEMODE_ECHO         = ivTTS_VEMODE_ECHO,
    TTS_VEMODE_ROBERT       = ivTTS_VEMODE_ROBERT,
    TTS_VEMODE_CHROUS       = ivTTS_VEMODE_CHROUS,
    TTS_VEMODE_UNDERWATER   = ivTTS_VEMODE_UNDERWATER,
    TTS_VEMODE_REVERB       = ivTTS_VEMODE_REVERB,
    TTS_VEMODE_ECCENTRIC    = ivTTS_VEMODE_ECCENTRIC,
}TTSVEMODE_e;

typedef void (*TtsRspCB)(TTSErrorCode eResult, void *pvUserData, u32 uRspVenHdl);
typedef void (*TtsIndCB)(TTSStatus_e  eStatus, void *pvUserData, u32 uRspVenHdl);

typedef struct
{
    TTSLanguage_e eLanguage;                // ivTTS_PARAM_LANGUAGE (default: ivTTS_LANGUAGE_CHINESE)
    TTSReadDigit_e eReadDigit;              // ivTTS_PARAM_READ_DIGIT (default: ivTTS_READ_DIGIT_AUTO)
    bool bRecognizePhoneme;                 // ivTTS_PARAM_RECOGNIZE_PHONEME (Default: ivFalse)
    bool bReadPunctuation;                  // ivTTS_PARAM_PUNCTUATION (Default: ivFalse)
    TTSChineseNumberOne_e eChineseNumber1;  // ivTTS_PARAM_CHINESE_NUMBER_1 (default:ivTTS_CHHUM1_READ_YAO)
    TTSRole_e eRole;                        // ivTTS_PARAM_ROLE (default:ivTTS_ROLE_YANPING)
    TTSStyle_e eVoiceStyle;                 // ivTTS_PARAM_SPEAK_STYLE (default:ivTTS_STYLE_NORMAL)
    TTSPitch_e eVoicePitch;                 // ivTTS_PARAM_VOICE_PITCH(default: ivTTS_PITCH_NORMAL)
    TTSSpeed_e eVoiceSpeed;                 // ivTTS_PARAM_VOICE_SPEED(default: ivTTS_SPEED_NORMAL)
    TTSVolumn_e eVoiceVolume;               // ivTTS_PARAM_VOLUME(default: ivTTS_VOLUME_NORMAL)
    TTSVEMODE_e eVeMone;                    // ivTTS_PARAM_VEMODE(default: ivTTS_VEMODE_NONE)
}TTSParam_t;

typedef struct
{
    void     *pvUserData;
    TtsRspCB pfnRspCb;
}TTSInitReq_t;

typedef struct
{
    void     *pvUserData;
    TtsRspCB pfnRspCb;
}TTSReleaseReq_t;

typedef struct
{
    TTSParam_t      tParam;
    u16             *pText;
    u16             nLen;
    TTSPlayVolumn_e ePlayVolume;
    void            *pvUserData;
    TtsRspCB        pfnRspCb;
    u32             uTi; // Trainsition Id
} TTSPlayTextReq_t;

typedef struct
{
    TTSErrorCode   eResult;
    void           *pvUserData;
} TTSInitRsp_t;

typedef struct
{
    TTSErrorCode   eResult;
    void           *pvUserData;
} TTSReleaseRsp_t;

typedef struct
{
    TTSErrorCode   eResult;
    void*          pvUserData;
}TTSPlayTextRsp_t;

typedef struct
{
    TTSErrorCode   eResult;
    void*          pvUserData;
}TTSStopRsp_t;

typedef struct
{
    TTSStatus_e    eStatus;
    void*          pvUserData;
} TTSStopPlayInd_t;

typedef struct
{
    TTSStatus_e    eStatus;
    void*          pvUserData;
} TTSPlayErrInd_t;

typedef struct
{
    TTSStatus_e    eStatus;
    void*          pvUserData;
} TTSPlayEndInd_t;

typedef union
{
   TTSInitReq_t tInitReq;
   TTSReleaseReq_t tReleaseReq;
   TTSPlayTextReq_t tPlayReq;
} TTSReqData_t;

typedef union
{
   TTSInitRsp_t     tInitRsp;
   TTSReleaseRsp_t  tReleaseRsp;
   TTSPlayTextRsp_t tPlayRsp;
   TTSStopRsp_t     tStopRsp;
} TTSRspData_t;

typedef union
{
   TTSStopPlayInd_t  tStopplayInd;
   TTSPlayErrInd_t  tPlayErrInd;
   TTSPlayEndInd_t  tPlayEndInd;
} TTSIndData_t;

typedef union
{
    TTSReqData_t    tReqData;
    TTSRspData_t    tRspData;
    TTSIndData_t    tIndData;
} TTSCmdData_t;

typedef struct
{
    TTSCmdType_e    eCmdType;
    TTSCmdData_t    tCmdData;
} TTSMsg_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
TTSErrorCode TtsEngineAdjustVolume(u32 uTi, TTSPlayVolumn_e eVolume);
bool TtsEngineIsPlaying(void);
TTSErrorCode TtsEngineSetPlaying(bool bPlay);
TTSErrorCode TtsEngineStop(void *pvUserData, u32 uTi, TtsRspCB pfnRspCb);
TTSErrorCode TtsEngineRegPlayEndCB(TtsIndCB pfnIndCb);
TTSErrorCode TtsEngineRegPlayErrCB(TtsIndCB pfnIndCb);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif  //__TTS__
#endif  //__TTS_ITF_H__
