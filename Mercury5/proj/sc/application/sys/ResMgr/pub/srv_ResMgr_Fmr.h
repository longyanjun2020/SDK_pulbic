/**
* @file srv_ResMgr_Fmr.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*   drivers and Resource Manager
*  This header file defines the declaration of operations of FM Radio.
*
*/

#ifndef __SRV_RESMGR_FMR_H__
#define __SRV_RESMGR_FMR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_fmr_itf.h"
#include "MediaRspItf.h"
//#include "MML_Manager.h"
#include "srv_resmgr_mmlradio_types.h"
#include "srv_resmgr_mmlaudio_types.h"
#include "ABL_Aud.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef esl_FmrBand_e ABL_FmrBand_e;
typedef esl_FmrInfo_t ABL_FmrInfo_t;
typedef MmlImageGetRadioCapability_t ABL_FmrGetCapabilityParam_t;



typedef esl_FmrAreaConfig_t ABL_FmrAreaConfig_t;

typedef struct ABL_FmrCarrier_t_
{
    u8 uThresholdOn;
    u8 uThresholdOff;
} ABL_FmrCarrier_t;

typedef esl_FmrRecParam_t ABL_FmrRecParam_t;

typedef struct ABL_FmrRecSetting_t_
{
    esl_FmrRecParam_t tRecSetting;
} ABL_FmrRecSetting_t;

typedef esl_FmrFileParam_t ABL_FmrFileName_t;

typedef struct ABL_FmrGetFile_t_
{
    esl_FmrFileParam_t tFmrFileName;
} ABL_FmrGetFile_t;

typedef enum ABL_FmrDeEmphasis_e_
{
    ABL_FMR_DEEMPHASIS_50US = 0,
    ABL_FMR_DEEMPHASIS_75US
} ABL_FmrDeEmphasis_e;

typedef enum ABL_FmrStepSpace_e_
{
    ABL_FMR_STEP_50KHZ = 0,
    ABL_FMR_STEP_100KHZ,
    ABL_FMR_STEP_200KHZ,
    ABL_FMR_STEP_30KHZ,     /* M3 not support yet */
    ABL_FMR_STEP_300KHZ     /* M3 not support yet */
} ABL_FmrStepSpace_e;

typedef enum ABL_FmrBpfir_e_
{
    ABL_FMR_BPFIR_100KHZ = 0,
    ABL_FMR_BPFIR_120KHZ,
    ABL_FMR_BPFIR_150KHZ,
    ABL_FMR_BPFIR_200KHZ
} ABL_FmrBpfir_e;

typedef enum ABL_FmrBeginRange_e_
{
    ABL_FMR_BEGIN_66MHZ = 0,  /* M3 not support yet */
    ABL_FMR_BEGIN_68MHZ,      /* M3 not support yet */
    ABL_FMR_BEGIN_73MHZ,      /* M3 not support yet */
    ABL_FMR_BEGIN_76MHZ,
    ABL_FMR_BEGIN_87_5MHZ,
    ABL_FMR_BEGIN_87_8MHZ,
    ABL_FMR_BEGIN_88MHZ,
    ABL_FMR_BEGIN_100MHZ
} ABL_FmrBeginRange_e;

typedef enum ABL_FmrEndRange_e_
{
    ABL_FMR_END_68MHZ = 0,  /* M3 not support yet */
    ABL_FMR_END_73MHZ,      /* M3 not support yet */
    ABL_FMR_END_74MHZ,      /* M3 not support yet */
    ABL_FMR_END_87_5MHZ,
    ABL_FMR_END_90MHZ,
    ABL_FMR_END_100MHZ,
    ABL_FMR_END_108MHZ
} ABL_FmrEndRange_e;

typedef enum ABL_FmrFrequency_e_
{
    ABL_FMR_FREQ__8_KHZ,        //ESL_FMRIO_8_KHZ
    ABL_FMR_FREQ__11_025_KHZ,   //ESL_FMRIO_11_025_KHZ
    ABL_FMR_FREQ__12_KHZ,       //ESL_FMRIO_12_KHZ
    ABL_FMR_FREQ__16_KHZ,       //ESL_FMRIO_16_KHZ
    ABL_FMR_FREQ__22_050_KHZ,   //ESL_FMRIO_22_050_KHZ
    ABL_FMR_FREQ__24_KHZ,       //ESL_FMRIO_24_KHZ
    ABL_FMR_FREQ__32_KHZ,       //ESL_FMRIO_32_KHZ
    ABL_FMR_FREQ__44_1_KHZ,     //ESL_FMRIO_44_1_KHZ
    ABL_FMR_FREQ__48_KHZ,       //ESL_FMRIO_48_KHZ
    ABL_FMR_FREQ__64_KHZ,       //ESL_FMRIO_64_KHZ
    ABL_FMR_FREQ__96_KHZ        //ESL_FMRIO_96_KHZ
} ABL_FmrFrequency_e;

typedef enum ABL_FmrChannelMode_e_
{
    ABL_FMR_CHANNEL_MODE__MONO,     //AUDIO_CHANNEL_MODE_MONO
    ABL_FMR_CHANNEL_MODE__STEREO    //AUDIO_CHANNEL_MODE_STEREO
} ABL_FmrChannelMode_e;

typedef enum ABL_FmrRecType_e_
{
    ABL_FMR_REC_CODEC__AMR,             //ESL_FMR_REC_CODEC_AMR
    ABL_FMR_REC_CODEC__AWB,             //ESL_FMR_REC_CODEC_AWB
    ABL_FMR_REC_CODEC__WAV_IMAADPCM4BIT,//ESL_FMR_REC_CODEC_WAV_IMAADPCM4BIT
    ABL_FMR_REC_CODEC__WAV_IMAADPCM3BIT,//ESL_FMR_REC_CODEC_WAV_IMAADPCM3BIT
    ABL_FMR_REC_CODEC__WAV_MSADPCM4BIT, //ESL_FMR_REC_CODEC_WAV_MSADPCM4BIT
    ABL_FMR_REC_CODEC__MP3,             //ESL_FMR_REC_CODEC_MP3
    ABL_FMR_REC_CODEC__AAC              //ESL_FMR_REC_CODEC_AAC
} ABL_FmrRecType_e;

typedef enum ABL_FmrRecStorage_e_
{
    ABL_FMR_REC_STORAGE__SD,      //ESL_FMR_REC_STORAGE_SD
    ABL_FMR_REC_STORAGE__MEMORY   //ESL_FMR_REC_STORAGE_MEMORY
} ABL_FmrRecStorage_e;

typedef enum ABL_FmrRecPath_e_
{
    ABL_FMR_REC_PATH__DIR,      //ESL_FMR_REC_PATH_DIR
    ABL_FMR_REC_PATH__PREFIX,   //ESL_FMR_REC_PATH_PREFIX
    ABL_FMR_REC_PATH__ABSOLUTE  //ESL_FMR_REC_PATH_ABSOLUTE
} ABL_FmrRecPath_e;

typedef enum ABL_FmrRecAppendTime_e_
{
    ABL_FMR_REC_APPEND_TIME__FIRST,     //ESL_FMR_REC_APPEND_FIRST
    ABL_FMR_REC_APPEND_TIME__LAST_TIME  //ESL_FMR_REC_APPEND_LAST_TIME
} ABL_FmrRecAppendTime_e;

typedef enum ABL_FmrRecLimitType_e_
{
    ABL_FMR_REC_LIMIT_SPACE,    //ESL_FMR_REC_LIMIT_SPACE
    ABL_FMR_REC_LIMIT_TIME      //ESL_FMR_REC_LIMIT_TIME
} ABL_FmrRecLimitType_e;

typedef enum {
    ABL_FMR_NOTIFY_ERR_UNKNOWN,
    ABL_FMR_NOTIFY_ERR_OUT_MEMORY,
    ABL_FMR_NOTIFY_ERR_FILE_DATA_FAIL,
    ABL_FMR_NOTIFY_ERR_FORMAT_NOT_SUPPORT,
    ABL_FMR_NOTIFY_ERR_SDCARD_NOT_DETECTED,
    ABL_FMR_NOTIFY_ERR_FORMAT_NOT_MATCH,
} ABL_FmrNotifyErr_e;

typedef enum ABL_FmrArea_e_
{
    ABL_FMR_AREA__TAIWAN,
    ABL_FMR_AREA__CHINA,
    ABL_FMR_AREA__THAILAND,
    ABL_FMR_AREA_NUM
} ABL_FmrArea_e;

typedef MmlRadioChannelInfo_t ABL_FmrChanInfo_t;

typedef esl_FmrCapability_t ABL_FmrCapability_t;

typedef enum ABL_FmrErrCode_e_
{
    ABL_FMR_OK,               //ESL_FMR_OK
    ABL_FMR_FAIL,             //ESL_FMR_FAIL
    ABL_FMR_PARAM_ERROR,      //ESL_FMR_PARAM_ERROR
    ABL_FMR_MEM_ALLOC_ERROR,  //ESL_FMR_MEM_ALLOC_ERROR
    ABL_FMR_REJECT,            //ESL_FMR_REJECT,
    ABL_FMR_ABORT,              //ESL_FMR_ABORT
    ABL_FMR_SKIP,            //ESL_FMR_SKIP
    ABL_FMR_PATH_ERROR,         //ESL_FMR_PATH_ERROR
    ABL_FMR_TIMEOUT,                  //ESL_FMR_TIMEOUT
    ABL_FMR_FORMAT_NOT_SUPPORT,    //ESL_FMR_FORMAT_NOT_SUPPORT
    ABL_FMR_DENY,
    ABL_FMR_MERGE,
    ABL_FMR_WAIT_APPSTOP_DROP
} ABL_FmrErrCode_e;


typedef struct DBLFmrRemapErrCode_t_
{
    ABL_FmrErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLFmrRemapErrCode_t;

typedef struct ABL_FmrRspInfo_t_
{
    ABL_FmrErrCode_e eErrCode;
    ABL_FmrInfo_t tFmrInfo;
    u32 uExtInfo;
} ABL_FmrRspInfo_t;

typedef struct ABL_FmrNotifyInfo_t_
{
    MediaRspId_e eNotifyType;    /**< Type of audio notification */
    union
    {
        ABL_FmrNotifyErr_e eNotifyErr;      /**< Fmr error code for "ESL_FMR_NOTIFY_PLAY_ERROR" */
        u32 nPosition;                      /**< Fmr playback position for "ESL_FMR_NOTIFY_PLAY_POSITION_UPDATE"*/
        u32 nBitrate;                       /**< Fmr decode bitrate for "ESL_FMR_NOTIFY_PLAY_STREAM_DECODE_COMPLETE"*/
        u32 nDataSize;                      /**< Fmr record data length for "ESL_FMR_NOTIFY_REC_END" and "ESL_AUD_NOTIFY_REC_SAPCE_FULL"*/
        ABL_FmrChanInfo_t tChanInfo;                      /**< Fmr search found frequency */
    } uNotify;
} ABL_FmrNotifyInfo_t;

typedef void (*ABL_FmrCb)(u16 uSenderId, u32 uUserValue, ABL_FmrErrCode_e eErrCode, ABL_FmrInfo_t *pFmrInfo);

typedef struct
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_FmrCb pfnCb;
} ABL_FmrCb_t;

typedef struct ABL_FMRSeek_t_
{
    u8 uOnOff;
    u8 uDirection;
} ABL_FMRSeek_t;

typedef MmlRadioSetRadioConfiguration_t ABL_RadioSetRadioConfiguration_t;
typedef MmlAudioSetRecordingSetting_t ABL_RadioSetRecordSetting_t;
typedef struct ABL_FMRSetRecordSetting_t_
{
    ABL_FmrRecType_e eFmrRecordType;
    ABL_FmrFrequency_e eFmrRecordFrequency;
    u32 uFmrRecordBitRate; //bitrate
    ABL_FmrChannelMode_e eChanMode;
} ABL_FMRSetRecordSettin_t;

typedef struct FmrCmd_t_
{
    ABL_FmrCb_t *pCbParams;
    u32 uHandle;
    union
    {
        ABL_RadioSetRadioConfiguration_t tRadioSetRadioConfiguration;
        ABL_AudioStartRecordParam_t tAudioStartRecordParam;
        ABL_RadioSetRecordSetting_t tRadioSetRecordSetting;
        ABL_FmrGetCapabilityParam_t         tFmrGetCapabilityParam;
        ABL_FmrBand_e eFmrBandParams;
        bool bMuteOnOff;
        ABL_FMRSeek_t tFmrSeekParams;
        u16 uFrequency;
        u8 uStereoOnOff;
        ABL_FmrAreaConfig_t tFmrAreaConfig;
        ABL_FmrCarrier_t tFmrCarrier;
        ABL_FmrRecSetting_t tRecParams;
        ABL_FmrGetFile_t tRecGetFileParams;
    } tParams;
} FmrCmd_t;
typedef struct
{
    ABL_FmrErrCode_e eErrCode;
    ABL_FmrCapability_t tFmrCapabilityCap;
}ABL_FmrGetCapabilityCapInfo_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

esl_FmrAudioRecFrequency_e ABL_FmrRemapFrequency(ABL_FmrFrequency_e eFrequency);
esl_FmrRecType_e ABL_FmrRemapRecType(ABL_FmrRecType_e eRecType);
esl_FmrRecStorage_e ABL_FmrRemapRecStorage(ABL_FmrRecStorage_e eRecStorage);
esl_FmrRecPath_e ABL_FmrRemapRecPath(ABL_FmrRecPath_e eRecPath);
esl_FmrRecAppendTimeMode_e ABL_FmrRemapRecAppendTime(ABL_FmrRecAppendTime_e eAppendTimeMode);
esl_FmrRecLimitType_e ABL_FmrRemapRecLimitType(ABL_FmrRecLimitType_e eLimitType);
ABL_CmnErrCode_e ABL_FmrPowerOn(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrPowerOff(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
void ABL_FmrSetBand(ResMgr_AppId_e eAppId, ABL_FmrBand_e bBand, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrSetFrequency(ResMgr_AppId_e eAppId, u32 uFreq, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrSetArea(ResMgr_AppId_e eAppId, ABL_FmrArea_e eArea, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrSetCarrierThreshold(ResMgr_AppId_e eAppId, u8 carrierOn, u8 carrierOff, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrSetAreaConfig(ResMgr_AppId_e eAppId, ABL_FmrAreaConfig_t *pAreaConfig, ABL_FmrCb_t *pFmrCb);
void ABL_FmrSetMute(ResMgr_AppId_e eAppId, bool bMute, ABL_FmrCb_t *pFmrCb);
void ABL_FmrSetStereo(ResMgr_AppId_e eAppId, bool bStereo, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrSearchChannel(ResMgr_AppId_e eAppId, bool bDirection, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrCancelSearch(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrGetChanInfo(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
void ABL_FmrGetChipInfo(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
void ABL_FmrGetCapability(ResMgr_AppId_e eAppId, ABL_FmrGetCapabilityParam_t *pCapabilityParam,ABL_FmrCb_t *pFmrCb);
#ifdef __APP_MMI_FM_RADIO_REC__
ABL_CmnErrCode_e ABL_FmrRecStartReq(ResMgr_AppId_e eAppId, ABL_FmrRecParam_t *pRecParam, ABL_FmrCb_t *pAudCb);
ABL_CmnErrCode_e ABL_FmrRecStopReq(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pAudCb);
#endif
void ABL_FmrGetRecFileNameReq(ResMgr_AppId_e eAppId, ABL_FmrFileName_t *pFileParam, ABL_FmrCb_t *pAudCb);
ABL_CmnErrCode_e ABL_FmrOpenSessionReq(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
ABL_CmnErrCode_e ABL_FmrCloseSessionReq(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
#ifdef __APP_MMI_FM_RADIO_REC__
void ABL_FmrRecSaveFileReq(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
void ABL_FmrRecDiscardFileReq(ResMgr_AppId_e eAppId, ABL_FmrCb_t *pFmrCb);
#endif
void ABL_FmrSetRecordSettingReq(ResMgr_AppId_e eAppId, ABL_FMRSetRecordSettin_t *pFMRSetRecordSetting, ABL_FmrCb_t *pFmrCb);
MmlRadioBpfirFrequency_e ABL_MmlFmrRemapBpfirFrequency(esl_FmrBpfir_e eBpfirFrequency);
MmlRadioStepSpace_e ABL_MmlFmrRemapStepSpace(esl_FmrStepSpace_e eStepSpace);
MmlRadioDeEmphasis_e ABL_MmlFmrRemapDeEmphasis(esl_FmrDeEmphasis_e eDeEmphasis);
MmlRadioFrequencyArea_e ABL_FmrRemapFrequencyArea(ABL_FmrArea_e eFrequencyArea);
esl_FmrBeginRange_e ABL_FmrRemapRangeBandMinFrequency(ABL_FmrBeginRange_e eRangeBandMinFrequency);
esl_FmrEndRange_e ABL_FmrRemapRangeBandMaxFrequency(ABL_FmrEndRange_e eRangeBandMaxFrequency);
esl_FmrBeginRange_e ABL_FmrRemapRangeBandMinFrequency(ABL_FmrBeginRange_e eRangeBandMinFrequency);
esl_FmrEndRange_e ABL_FmrRemapRangeBandMaxFrequency(ABL_FmrEndRange_e eRangeBandMaxFrequency);
esl_FmrBpfir_e ABL_FmrRemapBpfirFrequency(ABL_FmrBpfir_e eBpfirFrequency);
esl_FmrStepSpace_e ABL_FmrRemapStepSpace(ABL_FmrStepSpace_e eStepSpace);
esl_FmrDeEmphasis_e ABL_FmrRemapDeEmphasis(ABL_FmrDeEmphasis_e eDeEmphasis);

#endif //__SRV_RESMGR_FMR_H__

