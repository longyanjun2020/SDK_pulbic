/**
* @file srv_ResMgr_Aud.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of audio.
*
*/

#ifndef __SRV_RESMGR_AUD_H__
#define __SRV_RESMGR_AUD_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_aud_itf.h"
#include "Esl_vdo_itf.h"
#include "MediaCtrlItf.h"
#include "HAL_AudResCtrlItf.h"
#include "MediaRspItf.h"
#include "MML_Manager.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef enum ABL_AudErrCode_e_
{
    ABL_AUD_OK,                 //ESL_AUD_OK
    ABL_AUD_FAIL,               //ESL_AUD_FAIL
    ABL_AUD_SKIP,               //ESL_AUD_SKIP
    ABL_AUD_PARAM_ERROR,        //ESL_AUD_PARAM_ERROR
    ABL_AUD_MEM_ALLOC_ERROR,    //ESL_AUD_MEM_ALLOC_ERROR
    ABL_AUD_REJECT,             //ESL_AUD_REJECT
    ABL_AUD_ABORT,              //ESL_AUD_ABORT,
    ABL_AUD_PATH_ERROR,         //ESL_AUD_PATH_ERROR
    ABL_AUD_TIMEOUT,            //ESL_AUD_TIMEOUT
    ABL_AUD_FORMAT_NOT_SUPPORT, //ESL_AUD_FORMAT_NOT_SUPPORT
    ABL_AUD_DENY,
    ABL_AUD_MERGE
} ABL_AudErrCode_e;

typedef struct DBLMmlAudRemapErrCode_t_
{
    MmlAudioResult_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLMmlAudRemapErrCode_t;

typedef struct DBLAudRemapErrCode_t_
{
    ABL_AudErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLAudRemapErrCode_t;

typedef enum ABL_AudNotifyErr_e_
{
    ABL_AUD_NOTIFY_ERR_UNKNOWN,             //ESL_AUD_NOTIFY_ERR_UNKNOWN
    ABL_AUD_NOTIFY_ERR_OUT_MEMORY,          //ESL_AUD_NOTIFY_ERR_OUT_MEMORY
    ABL_AUD_NOTIFY_ERR_FILE_DATA_FAIL,      //ESL_AUD_NOTIFY_ERR_FILE_DATA_FAIL
    ABL_AUD_NOTIFY_ERR_FORMAT_NOT_SUPPORT,  //ESL_AUD_NOTIFY_ERR_FORMAT_NOT_SUPPORT
    ABL_AUD_NOTIFY_ERR_SDCARD_NOT_DETECTED, //ESL_AUD_NOTIFY_ERR_SDCARD_NOT_DETECTED
    ABL_AUD_NOTIFY_ERR_STREAMING_UNDERRUN
} ABL_AudNotifyErr_e;

typedef enum ABL_AudAcceptCall_e_
{
    ABL_AUD_ACCEPT_CALL__BY_BT,
    ABL_AUD_ACCEPT_CALL__BY_PHONE,
    ABL_AUD_ACCEPT_CALL__NUM
} ABL_AudAcceptCall_e;

typedef esl_AudDTMF_e ABL_ToneId_e;
typedef esl_AudChannel_e ABL_AudChannel_e;
typedef esl_AudEQ_e ABL_AudEQ_e;
typedef esl_AudUserPEQConfig_t ABL_AudUserPEQConfig_t;

typedef enum ABL_AudConfigItem_e_
{
    ABL_AUD_EQ_TYPE,        //ESL_AUD_EQ_TYPE
    ABL_AUD_3D_EFFECT,      //ESL_AUD_3D_EFFECT
    ABL_AUD_PEQ_SETTING     //ESL_AUD_PEQ_SETTING
} ABL_AudConfigItem_e;

typedef enum ABL_AudEncodeScheme_e_
{
    ABL_AUD_ISO_8859_1,     //ESL_AUD_ISO_8859_1
	ABL_AUD_UTF16,          //ESL_AUD_UTF16
	ABL_AUD_UTF16BE,        //ESL_AUD_UTF16BE
	ABL_AUD_UTF8            //ESL_AUD_UTF8
} ABL_AudEncodeScheme_e;

typedef enum ABL_AudGetMode_e_
{
    ABL_AUD_GET_INFOLEN,    //ESL_AUD_GET_INFOLEN
    ABL_AUD_GET_INFODATA    //ESL_AUD_GET_INFODATA
} ABL_AudGetMode_e;

typedef enum ABL_AudFrequency_e_
{
  	ABL_AUD_FREQ__8_KHZ,		//ESL_AUDIO_8_KHZ
	ABL_AUD_FREQ__11_025_KHZ,	//ESL_AUDIO_11_025_KHZ
	ABL_AUD_FREQ__12_KHZ,		//ESL_AUDIO_12_KHZ
	ABL_AUD_FREQ__16_KHZ,		//ESL_AUDIO_16_KHZ
	ABL_AUD_FREQ__22_050_KHZ,	//ESL_AUDIO_22_050_KHZ
	ABL_AUD_FREQ__24_KHZ,		//ESL_AUDIO_24_KHZ
	ABL_AUD_FREQ__32_KHZ,		//ESL_AUDIO_32_KHZ
	ABL_AUD_FREQ__44_1_KHZ,		//ESL_AUDIO_44_1_KHZ
	ABL_AUD_FREQ__48_KHZ,		//ESL_AUDIO_48_KHZ
	ABL_AUD_FREQ__64_KHZ,		//ESL_AUDIO_64_KHZ
	ABL_AUD_FREQ__96_KHZ		//ESL_AUDIO_96_KHZ
} ABL_AudFrequency_e;

typedef enum ABL_AudVolume_e_
{
    ABL_AUD_VOLLEVEL__DEFAULT = 4,
    ABL_AUD_VOLLEVEL__OFF = 0,
    ABL_AUD_VOLLEVEL__MIN = 0,
    ABL_AUD_VOLLEVEL__0 = ABL_AUD_VOLLEVEL__MIN,
    ABL_AUD_VOLLEVEL__1 = 1,
    ABL_AUD_VOLLEVEL__2 = 2,
    ABL_AUD_VOLLEVEL__3 = 3,
    ABL_AUD_VOLLEVEL__4 = 4,
    ABL_AUD_VOLLEVEL__5 = 5,
    ABL_AUD_VOLLEVEL__6 = 6,
    ABL_AUD_VOLLEVEL__7 = 7,
    ABL_AUD_VOLLEVEL__8 = 8,
    ABL_AUD_VOLLEVEL__MAX = ABL_AUD_VOLLEVEL__8,
    ABL_AUD_VOLLEVEL__NUM
} ABL_AudVolume_e;

typedef enum ABL_AudRecType_e_
{
	ABL_AUD_REC_CODEC__AMR,				    //ESL_AUD_REC_CODEC_AMR
	ABL_AUD_REC_CODEC__AWB,				    //ESL_AUD_REC_CODEC_AWB
	ABL_AUD_REC_CODEC__WAV_IMAADPCM4BIT,    //ESL_AUD_REC_CODEC_WAV_IMAADPCM4BIT
	ABL_AUD_REC_CODEC__WAV_IMAADPCM3BIT,    //ESL_AUD_REC_CODEC_WAV_IMAADPCM3BIT
	ABL_AUD_REC_CODEC__WAV_MSADPCM4BIT,	    //ESL_AUD_REC_CODEC_WAV_MSADPCM4BIT
	ABL_AUD_REC_CODEC__MP3,				    //ESL_AUD_REC_CODEC_MP3
	ABL_AUD_REC_CODEC__AAC,				    //ESL_AUD_REC_CODEC_AAC
	ABL_AUD_REC_CODEC__PCM,                 //ESL_AUD_REC_CODEC_PCM
} ABL_AudRecType_e;

typedef enum ABL_AudRecStorage_e_
{
	ABL_AUD_REC_STORAGE__SD,	  //ESL_AUD_REC_STORAGE_SD
	ABL_AUD_REC_STORAGE__MEMORY	  //ESL_AUD_REC_STORAGE_MEMORY
} ABL_AudRecStorage_e;

typedef enum ABL_AudRecPath_e_
{
	ABL_AUD_REC_PATH__DIR,	  	//ESL_AUD_REC_PATH_DIR
	ABL_AUD_REC_PATH__PREFIX,	//ESL_AUD_REC_PATH_PREFIX
	ABL_AUD_REC_PATH__ABSOLUTE	//ESL_AUD_REC_PATH_ABSOLUTE
} ABL_AudRecPath_e;

typedef enum ABL_AudRecAppendTime_e_
{
	ABL_AUD_REC_APPEND_TIME__FIRST,		//ESL_AUD_REC_APPEND_FIRST
	ABL_AUD_REC_APPEND_TIME__LAST_TIME	//ESL_AUD_REC_APPEND_LAST_TIME
} ABL_AudRecAppendTime_e;

typedef enum ABL_AudRecLimitType_e_
{
    ABL_AUD_REC_LIMIT_SPACE,    //ESL_AUD_REC_LIMIT_SPACE
    ABL_AUD_REC_LIMIT_TIME      //ESL_AUD_REC_LIMIT_TIME
} ABL_AudRecLimitType_e;

typedef enum ABL_AudRecRemainStorageType_e_
{
    ABL_AUD_REC_REMAIN_STORAGE__SD,
    ABL_AUD_REC_REMAIN_STORAGE__SD2,
    ABL_AUD_REC_REMAIN_STORAGE__NOR,
    ABL_AUD_REC_REMAIN_STORAGE__NAND
} ABL_AudRecRemainStorageType_e;

typedef enum ABL_AudEncoderId_e_
{
    ABL_AUD_ENCODERID__AMR_NB,              //AUDIO_ENCODERID_AMR_NB
    ABL_AUD_ENCODERID__AMR_WB,              //AUDIO_ENCODERID_AMR_WB
    ABL_AUD_ENCODERID__WAV_IMAADPCM_4BIT,   //AUDIO_ENCODERID_WAV_IMAADPCM_4BIT
    ABL_AUD_ENCODERID__WAV_IMAADPCM_3BIT,   //AUDIO_ENCODERID_WAV_IMAADPCM_3BIT
    ABL_AUD_ENCODERID__WAV_MSADPCM4BIT,     //AUDIO_ENCODERID_WAV_MSADPCM4BIT
    ABL_AUD_ENCODERID__MP3_LAYERII,         //AUDIO_ENCODERID_MP3_LAYERII
    ABL_AUD_ENCODERID__PCM,                 //AUDIO_ENCODERID_PCM
    ABL_AUD_ENCODERID__MP3_LAYERIII,        //AUDIO_ENCODERID_MP3_LAYERIII
    ABL_AUD_ENCODERID__NUM
} ABL_AudEncoderId_e;

typedef enum ABL_AudSamplingRate_e_
{
    ABL_AUD_SAMPLING_RATE__8000,    //AUDIO_SAMPLING_RATE_8000
    ABL_AUD_SAMPLING_RATE__11025,   //AUDIO_SAMPLING_RATE_11025
    ABL_AUD_SAMPLING_RATE__12000,   //AUDIO_SAMPLING_RATE_12000
    ABL_AUD_SAMPLING_RATE__16000,   //AUDIO_SAMPLING_RATE_16000
    ABL_AUD_SAMPLING_RATE__22025,   //AUDIO_SAMPLING_RATE_22050
    ABL_AUD_SAMPLING_RATE__24000,   //AUDIO_SAMPLING_RATE_24000
    ABL_AUD_SAMPLING_RATE__32000,   //AUDIO_SAMPLING_RATE_32000
    ABL_AUD_SAMPLING_RATE__44100,   //AUDIO_SAMPLING_RATE_44100
    ABL_AUD_SAMPLING_RATE__48000,   //AUDIO_SAMPLING_RATE_48000
    ABL_AUD_SAMPLING_RATE__UNSUPPORT//AUDIO_SAMPLING_RATE_UNSUPPORT
} ABL_AudSamplingRate_e;

typedef enum ABL_AudChannelMode_e_
{
    ABL_AUD_CHANNEL_MODE__MONO,     //AUDIO_CHANNEL_MODE_MONO
    ABL_AUD_CHANNEL_MODE__STEREO    //AUDIO_CHANNEL_MODE_STEREO
} ABL_AudChannelMode_e;

typedef enum ABL_AudMusicMode_e_
{
    ABL_AUD_MUSIC_MODE__TO_NE_WITHOUT_GSM_DL,           //ESL_AUD_MUSIC_MODE__TO_NE_WITHOUT_GSM_DL
    ABL_AUD_MUSIC_MODE__TO_NE_WITH_GSM_DL,              //ESL_AUD_MUSIC_MODE__TO_NE_WITH_GSM_DL
    ABL_AUD_MUSIC_MODE__TO_FE_WITHOUT_ADC_UL,           //ESL_AUD_MUSIC_MODE__TO_FE_WITHOUT_ADC_UL
    ABL_AUD_MUSIC_MODE__TO_FE_WITH_ADC_UL,              //ESL_AUD_MUSIC_MODE__TO_FE_WITH_ADC_UL
    ABL_AUD_MUSIC_MODE__TO_NE_FE_WITH_GSM_UL_ADC_DL     //ESL_AUD_MUSIC_MODE__TO_NE_FE_WITH_GSM_UL_ADC_DL
} ABL_AudMusicMode_e;

typedef enum ABL_AudDistortedVoice_e_
{
    ABL_AUD_DISTORTED_VOICE__NORMAL = 0, //MDL_AUD_DISTORTED_VOICE_NORMAL
    ABL_AUD_DISTORTED_VOICE__KID,        //MDL_AUD_DISTORTED_VOICE_KID
    ABL_AUD_DISTORTED_VOICE__GIRL,       //MDL_AUD_DISTORTED_VOICE_GIRL
    ABL_AUD_DISTORTED_VOICE__WOMAN,      //MDL_AUD_DISTORTED_VOICE_WOMAN
    ABL_AUD_DISTORTED_VOICE__MALE,       //MDL_AUD_DISTORTED_VOICE_MALE
    ABL_AUD_DISTORTED_VOICE__MAN,        //MDL_AUD_DISTORTED_VOICE_MAN
    ABL_AUD_DISTORTED_VOICE__BASS,       //MDL_AUD_DISTORTED_VOICE_BASS
} ABL_AudDistortedVoice_e;

typedef esl_AudInfo_t ABL_AudInfo_t;

typedef struct ABL_AudRspInfo_t_
{
    ABL_AudErrCode_e eErrCode;
    ABL_AudInfo_t tAudInfo;
    u32 uExtInfo;
} ABL_AudRspInfo_t;

/**
 *  @brief The structure defines the notification value for application layer.
 *			should sync. with esl_AudNotifyInfo_t
 */
typedef struct ABL_AudNotifyInfo_t_
{
    MediaRspId_e	  notifyType;		/**< Type of audio notification */
    union
    {
        ABL_AudNotifyErr_e notifyErr;   /**< audio error code for "ESL_AUD_NOTIFY_PLAY_ERROR" */
        u32 position;	                /**< audio playback position for "ESL_AUD_NOTIFY_PLAY_POSITION_UPDATE"*/
        u32 bitrate;                    /**< audio decode bitrate for "ESL_AUD_NOTIFY_PLAY_STREAM_DECODE_COMPLETE"*/
        u32 dataSize;                   /**< audio record data length for "ESL_AUD_NOTIFY_REC_END" and "ESL_AUD_NOTIFY_REC_SAPCE_FULL"*/
        u32 userData[2];                /**< audio user data for "ESL_AUD_NOTIFY_GENERAL_UPDATE"*/
		u32 pcmData;		            /**< pcm data for "MEDIA_RSP_ID__AUDIO_REC_PCM_DATA"*/
		u32 updatetotaltime;            /**< audio playback updated total time for position for "AUDIO_EVENT_PLAYBACK_TOTALPLAYTIME_UPDATE" */
        u32 nAvailableStreamTime;       /**< Used with AUDIO_EVENT_PLAYBACK_STREAM_UNDERRUN, expressed in milliseconds */
    } notify;
} ABL_AudNotifyInfo_t;

typedef void (*ABL_AudCb)(u16 uSenderId, u32 uUserValue, ABL_AudErrCode_e eErrCode, ABL_AudInfo_t *pAudInfo);

typedef struct ABL_AudCb_t_
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_AudCb pfnCb;
} ABL_AudCb_t;

typedef esl_AudSetMute_t ABL_AudSetMute_t;
typedef esl_AudEnableSpeech_t ABL_AudEnableSpeech_t;
typedef esl_AudDtmfParam_t ABL_AudDtmfParam_t;
typedef esl_AudStreamParam_t ABL_AudStreamParam_t;
typedef esl_AudMemoryParam_t ABL_AudMemoryParam_t;
typedef esl_AudFileParam_t ABL_AudFileParam_t;

typedef struct ABL_AudPlayMemoryParam_t_
{
    ABL_AudMemoryParam_t tMemoryParam;
    MmlAudioMediaParam_t tMediaParam;    ///< Media parameters (current for PCM usage only)
} ABL_AudPlayMemoryParam_t;

typedef struct ABL_AudPlayFileParam_t_
{
    ABL_AudFileParam_t tFileParam;
    u32 uPosition;
    MmlAudioMediaParam_t tMediaParam;    ///< Media parameters (current for PCM usage only)
} ABL_AudPlayFileParam_t;

typedef esl_AudID3V1Info_t ABL_AudID3V1Info_t;

typedef struct ABL_AudGetID3_t_
{
    ABL_AudFileParam_t tFileParam;
    ABL_AudID3V1Info_t *pID3Info;
} ABL_AudGetID3_t;

typedef esl_AudAdvancedInfo_t ABL_AudAdvancedInfo_t;

typedef struct ABL_AudGetAdvInfo_t_
{
    u8 uMode;
    ABL_AudFileParam_t tFileParam;
    ABL_AudAdvancedInfo_t *pAdvancedInfo;
} ABL_AudGetAdvInfo_t;

typedef struct ABL_AudGetFileInfo_t_
{
    ABL_AudFileParam_t tFileParam;
} ABL_AudGetFileInfo_t;

typedef struct ABL_AudGetStreamInfo_t_
{
    ABL_AudStreamParam_t tStreamParam;
} ABL_AudGetStreamInfo_t;

typedef struct ABL_AudGetMemoryInfo_t_
{
    ABL_AudMemoryParam_t tMemoryParam;
} ABL_AudGetMemoryInfo_t;

typedef esl_AudRecTimeParam_t ABL_AudRecTimeParam_t;

typedef struct ABL_AudGetRecRemainTime_t_
{
    ABL_AudRecRemainStorageType_e eStorage;
    ABL_AudRecType_e eRecType;
    ABL_AudFrequency_e eFreq;
    ABL_AudChannelMode_e eChanMode;
    u32 uBitRate;
} ABL_AudGetRecRemainTime_t;

typedef struct ABL_AudSetUserPEQConfig_t_
{
    ABL_AudEQ_e eType;
    ABL_AudUserPEQConfig_t tConfig;
} ABL_AudSetUserPEQConfig_t;

typedef esl_AudRecParam_t ABL_AudRecParam_t;

typedef struct ABL_AudRecGetMedium_t_
{
    esl_AudFileParam_t fileParam;
} ABL_AudRecGetMedium_t;

typedef esl_AudMediaConfig_t ABL_AudSetMediaConfig_t;
typedef esl_AudMediaConfig_t ABL_AudMediaConfig_t;

typedef MmlAudioStartPlayback_t ABL_AudioStartPlayback_t;
typedef MmlAudioStartRecording_t ABL_AudioStartRecordParam_t;
typedef MmlAudioGetMP3ID3Tag_t ABL_AudioGetMP3ID3Tag_t;
typedef MmlAudioGetMusicLyrics_t ABL_AudioGetMusicLyrics_t;
typedef MmlAudioFileParam_t ABL_AUDIOFileParam_t;
typedef MmlAudioMemoryParam_t ABL_AudioMemoryparam_t;
typedef MmlAudioFormat_e ABL_AudioFormate_e;
typedef MmlAudioSetPlaybackPosition_t ABL_AudioSetPlaybackPosition_t;
typedef MmlAudioGetAudioInfo_t ABL_AUDIOGetAudioInfo_t;
typedef MmlAudioGetRecordingInfo_t ABL_AudioGetRecordInfo_t;
typedef MmlAudioSetRecordingSetting_t ABL_AudioSetRecordSetting_t;
typedef MmlAudioSetConfiguration_t ABL_AudioSetConfiguration_t;
typedef MmlAudioGetConfiguration_t ABL_AudioGetConfiguration_t;
typedef MmlAudioPlayTone_t ABL_AudioPlayTone_t;
typedef MmlAudioGetPlaybackCapability_t     ABL_AudioGetPlaybackCapability_t;
typedef MmlAudioPlaybackCapability_t        ABL_AudioPlaybackCapability_t;
typedef MmlAudioGetRecordingCapability_t    ABL_AudioGetRecordingCapability_t;
typedef MmlAudioRecordingCapability_t       ABL_AudioRecordingCapability_t;
typedef struct ABL_AudioStreamParam_t_
{
    esl_AudFormat_e         format;                     /**< Audio streaming data format */
    ResMgr_RingBuffHdl_t    pRingBuffHdl;               /**< Ring buffer handle */
    u32                     nAvailableStreamThreshold;  /**< Available stream threshold expressed in milliseconds */
} ABL_AudioStreamParam_t;

typedef struct ABL_AudPlayStreamParam_t_
{
    ABL_AudioStreamParam_t tStreamParam;
    MmlAudioMediaParam_t tMediaParam;    ///< Media parameters (current for PCM usage only)
} ABL_AudPlayStreamParam_t;

typedef struct
{
    ABL_AudErrCode_e eErrCode;
    ABL_AudioPlaybackCapability_t tAudPlaybackCap;
} ABL_AudGetPlaybackCapInfo_t;

typedef struct
{
    ABL_AudErrCode_e eErrCode;
    ABL_AudioRecordingCapability_t tAudRecCap;
} ABL_AudGetRecCapInfo_t;

typedef struct ABL_AudioRecordConfig_t_
{
    ABL_AudRecType_e eAudioRecordType;
    ABL_AudSamplingRate_e eAudioRecordFrequency;
    u32 uAudioRecordBitRate;
    ABL_AudChannelMode_e eChanMode;
} ABL_AudioSetRecordConfig_t;

typedef esl_AudPcmRecordCb ABL_AudPcmRecordCb;

typedef struct ABL_AudPcmRecData_t_
{
    u16 *pData;
    u32 uDataLen;
} ABL_AudPcmRecData_t;

typedef struct AudioCmd_t_
{
    ABL_AudCb_t *pCbParams;
    u32 uHandle;
    u32 uBitRate;
    union
    {
        ABL_AudioStartRecordParam_t tAudioStartRecordParam;
        ABL_AudioStartPlayback_t tAudioStartPlayback;
        MmlAudioGetMP3ID3Tag_t tAudioGetMP3ID3Tag;
        ABL_AudioGetMusicLyrics_t tAudioGetMusicLyrics;
        ABL_AUDIOFileParam_t tAudioFileParam;
        ABL_AudioMemoryparam_t tAudioMemoryParam;
        ABL_AudioSetPlaybackPosition_t tAudioSetPlaybackPosition;
        ABL_AUDIOGetAudioInfo_t tAudioGetAudioInfo;
        ABL_AudioGetRecordInfo_t tAudioGetRecordInfo;
        ABL_AudioSetRecordSetting_t tAudioSetRecordSetting;
        ABL_AudioSetConfiguration_t tAudioSetConfiguration;
        ABL_AudioGetConfiguration_t tAudioGetConfiguration;
        ABL_AudioPlayTone_t tAudioPlayTone;
        ABL_AudioGetPlaybackCapability_t    tAudioGetPlaybackCapability;
        ABL_AudioGetRecordingCapability_t   tAudioGetrecordingCapability;
        ABL_AudSetMute_t tMuteParams;
        ABL_ToneId_e eToneId;
        ABL_AudDtmfParam_t tDtmfParams;
        ABL_AudStreamParam_t tAudStmParams;
        ABL_AudMemoryParam_t tAudMmrParams;
        ABL_AudPlayFileParam_t tPlayFileParams;
        ABL_AudGetID3_t tGetID3Params;
        ABL_AudGetAdvInfo_t tGetAdvInfoParams;
        ABL_AudGetFileInfo_t tGetFileInfoParams;
        ABL_AudGetStreamInfo_t tGetStmInfoParams;
        ABL_AudGetMemoryInfo_t tGetMmrInfoParams;
        u32 uPEQTableAddress;
        ABL_AudSetUserPEQConfig_t tSetUserPEQParams;
        u32 uPosition;
        ABL_AudRecParam_t tRecParams;
        ABL_AudRecGetMedium_t tRecGetFileParams;
        ABL_AudSetMediaConfig_t tSetMediaConfigParams;
        ABL_AudRecTimeParam_t tRecTimeParams;
        ABL_AudMusicMode_e eMusicMode;
        ABL_AudDistortedVoice_e eDistortedVoice;
    } tParams;
} AudioCmd_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void ABL_AudioStartRecording(ResMgr_AppId_e eAppId,ABL_AudioStartRecordParam_t *pRecParam,ABL_AudCb_t *pAudCb);
void ABL_AudioStopRecording(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudioPauseRecording(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudioResumeRecording(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_DiscardRecordingFile(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_SaveRecordingFile(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudRecSaveFileReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudRecDiscardFileReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudSetPreProcessTableAddressReq(ResMgr_AppId_e eAppId, u32 uPreProcessTableAddress, u32 uMemSize, ABL_AudCb_t *pAudCb);
void ABL_AudGetPreProcessTableAddressReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudSetRecordSettingReq(ResMgr_AppId_e eAppId, ABL_AudioSetRecordConfig_t *pAudioSetRecordConfig, ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ void ABL_AudGetPlaybackCapabilityReq(ResMgr_AppId_e eAppId,ABL_AudioGetPlaybackCapability_t* pGetPlaybackCapability,ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ void ABL_AudGetRecordingCapabilityReq(ResMgr_AppId_e eAppId,ABL_AudioGetRecordingCapability_t *pGetRecordingCapability,ABL_AudCb_t *pAudCb);
ABL_AudErrCode_e ABL_AudGetSpectrumData(ResMgr_AppId_e eAppId, void *pSpectrumData, u32 uDataSize);
void ABL_AudSetSpectrumMode(ResMgr_AppId_e eAppId, bool bSpectrumOn);
ABL_AudErrCode_e ABL_AudSetMicLoopBack(ResMgr_AppId_e eAppId, bool bMicLoopBack);
ABL_CmnErrCode_e ABL_AudSetMute(ResMgr_AppId_e eAppId, bool bMute);
ABL_CmnErrCode_e ABL_AudEnableSpeech(ResMgr_AppId_e eAppId, ABL_AudAcceptCall_e eAcceptCall);
ABL_CmnErrCode_e ABL_AudDisableSpeech(ResMgr_AppId_e eAppId);
ABL_CmnErrCode_e ABL_AudPlayKeypadToneReq(ResMgr_AppId_e eAppId, ABL_ToneId_e eToneId, u8 uVolRange, u8 uVolLevel, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudPlayToneReq(ResMgr_AppId_e eAppId, ABL_ToneId_e eToneId, u8 uVolRange, u8 uVolLevel, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudPlayStreamReq
(
    ResMgr_AppId_e eAppId,
    ABL_AudPlayStreamParam_t *pStreamParam,
    ABL_AudCb_t *pAudCb,
    bool bLoopPlay
);
ABL_CmnErrCode_e ABL_AudPlayStreamAddBufferReq(ResMgr_AppId_e eAppId, ABL_AudStreamParam_t *pStreamParam, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudPlayMemoryReq(ResMgr_AppId_e eAppId, ABL_AudPlayMemoryParam_t *pMemoryParam, ABL_AudCb_t *pAudCb, bool bLoopPlay);
ABL_CmnErrCode_e ABL_AudPlayFileReq(ResMgr_AppId_e eAppId, ABL_AudPlayFileParam_t *pFileParam, ABL_AudCb_t *pAudCb, bool bLoopPlay);
ABL_CmnErrCode_e ABL_AudGetID3V1InfoReq(ResMgr_AppId_e eAppId, ABL_AudFileParam_t *pFileParam, ABL_AudID3V1Info_t *pID3Info, ABL_AudCb_t *pAudCb);
void ABL_AudGetAdvancedInfoReq(ResMgr_AppId_e eAppId, ABL_AudGetMode_e eMode, ABL_AudFileParam_t *pFileParam, ABL_AudAdvancedInfo_t *pAdvancedInfo, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudGetFileInfoReq(ResMgr_AppId_e eAppId, ABL_AudFileParam_t *pFileParam, ABL_AudCb_t *pAudCb);
void ABL_AudGetStreamInfoReq(ResMgr_AppId_e eAppId, ABL_AudStreamParam_t *pStreamParam, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudGetMemoryInfoReq(ResMgr_AppId_e eAppId, ABL_AudMemoryParam_t *pMemoryParam, ABL_AudCb_t *pAudCb);
ABL_AudErrCode_e ABL_AudGetRecRemainTimeReq(ResMgr_AppId_e eAppId, ABL_AudGetRecRemainTime_t *pRemainTimeParam, u32 *pRecRemainTime);
void ABL_AudSetPEQTableAddressReq(ResMgr_AppId_e eAppId, u32 uPEQTableAddress, u32 uMemSize, ABL_AudCb_t *pAudCb);
void ABL_AudSetPEQTableAddressSyncReq(ResMgr_AppId_e eAppId, u32 uPEQTableAddress, u32 uMemSize, ABL_AudCb_t *pAudCb);
void ABL_AudGetPEQTableAddressReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudSetUserPEQConfigReq(ResMgr_AppId_e eAppId, ABL_AudEQ_e eType, ABL_AudUserPEQConfig_t *ptConfig, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudSetPositionReq(ResMgr_AppId_e eAppId, u32 uPosition, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudSeekCancelReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudGetPositionReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudRecStartReq(ResMgr_AppId_e eAppId, ABL_AudRecParam_t *pRecParam, ABL_AudCb_t *pAudCb);
void ABL_AudStreamRecStartReq(ResMgr_AppId_e eAppId, ABL_AudioStreamParam_t *pStreamRecParam, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudRecStopReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudRecGetFileReq(ResMgr_AppId_e eAppId, ABL_AudFileParam_t *pFileParam, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudStopPlayReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudPausePlayReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudResumePlayReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudOpenSessionReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudOpenSessionReqEx(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb, MediaResInfo_e eResInfo);
ABL_CmnErrCode_e ABL_AudCloseSessionReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudCloseSessionReqEx(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb, MediaResInfo_e eResInfo);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudOpenSpeechSessionReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudOpenSpeechSessionReqEx(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb, MediaResInfo_e eResInfo);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudCloseSpeechSessionReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudCloseSpeechSessionReqEx(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb, MediaResInfo_e eResInfo);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudOpenRecSessionReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudCloseRecSessionReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudInitRecorderReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudInitPcmRecorderReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudUninitRecorderReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ void ABL_InitDefVol(ResMgr_TaskId_e eTaskId, MediaVolUserId_e eVolUserId, u8 uDefVol, u8 uVolRange);
__SLDPM_FREE__ void ABL_RegVolUser(ResMgr_TaskId_e eTaskId, ResMgr_AppId_e eAppId, MediaVolUserId_e eVolUserId);
__SLDPM_FREE__ void ABL_DeregVolUser(ResMgr_TaskId_e eTaskId, ResMgr_AppId_e eAppId);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_EnableDtmf(ResMgr_AppId_e eAppId);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_DisableDtmf(ResMgr_AppId_e eAppId);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudSetVol(ResMgr_AppId_e eAppId, u8 uVolCtrlID, u8 uVolume);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudSetChannelVol(ResMgr_AppId_e eAppId, u8 uVolCtrlID, AudChannel_e eChannel, u8 uVolume);
ABL_CmnErrCode_e ABL_AudSetBalance(ResMgr_AppId_e eAppId, u8 uVolCtrlID, AudChannel_e eChannel, s8 sBalance);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudGetVol(ResMgr_AppId_e eAppId, u8 *pVolume, u8 *pVolRange);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudGetPath(ResMgr_AppId_e eAppId, AudPath_e *pPath);
__SLDPM_FREE__ void ABL_InitDefProfileVol(ResMgr_TaskId_e eTaskId, MediaVolUserId_e eVolUserId, MediaProfileVol_t *pProfileVol);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudSetActiveProfile(ResMgr_AppId_e eAppId, MediaProfileType_e eProfileType);
ABL_CmnErrCode_e ABL_AudGetActiveProfile(ResMgr_AppId_e eAppId, MediaProfileType_e *pProfileType);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_AudSetTmpVol(ResMgr_AppId_e eAppId, u8 uVolume, u8 uVolRange);
__SLDPM_FREE__ ABL_CmnErrCode_e ABL_SetMediaConfig(ResMgr_AppId_e eAppId, MediaSetConfigParm_t *pMediaConfig);
__SLDPM_FREE__ void ABL_UpdateMediaConfig(ResMgr_AppId_e eAppId);
ABL_CmnErrCode_e ABL_AudPcmRecStartReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
ABL_CmnErrCode_e ABL_AudPcmRecStopReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);

ABL_CmnErrCode_e ABL_AudPlayToneSyncReq
(
    ResMgr_AppId_e eAppId,
    ABL_ToneId_e eToneId,
    u8 uVolRange,
    u8 uVolLevel
);
void ABL_AudPlayMemorySyncReq(ResMgr_AppId_e eAppId, ABL_AudPlayMemoryParam_t *pMemoryParam, ABL_AudCb_t *pAudCb, bool bLoopPlay);
void ABL_AudPlayFileSyncReq(ResMgr_AppId_e eAppId, ABL_AudPlayFileParam_t *pFileParam, ABL_AudCb_t *pAudCb, bool bLoopPlay);
void ABL_AudStopPlaySyncReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudPlayStreamSyncReq
(
    ResMgr_AppId_e eAppId,
    ABL_AudPlayStreamParam_t *pStreamParam,
    ABL_AudCb_t *pAudCb,
    bool bLoopPlay
);
void ABL_AudPlayStreamAddBufferSyncReq(ResMgr_AppId_e eAppId, ABL_AudStreamParam_t *pStreamParam, ABL_AudCb_t *pAudCb);
void ABL_AudGetFileInfoSyncReq(ResMgr_AppId_e eAppId, ABL_AudFileParam_t *pFileParam, ABL_AudCb_t *pAudCb);
void ABL_AudGetMemoryInfoSyncReq(ResMgr_AppId_e eAppId, ABL_AudMemoryParam_t *pMemoryParam, ABL_AudCb_t *pAudCb);
void ABL_AudPausePlaySyncReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudResumePlaySyncReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudSetPositionSyncReq(ResMgr_AppId_e eAppId, u32 uPosition, ABL_AudCb_t *pAudCb);
void ABL_AudRecStarSyncReq(ResMgr_AppId_e eAppId, ABL_AudRecParam_t *pRecParam, ABL_AudCb_t *pAudCb);
void ABL_AudStreamRecStartSyncReq(ResMgr_AppId_e eAppId, ABL_AudioStreamParam_t *pStreamRecParam, ABL_AudCb_t *pAudCb);
void  ABL_AudRecSaveFileSyncReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
__SLDPM_FREE__ void ABL_AudRecStopSyncReq(ResMgr_AppId_e eAppId, ABL_AudCb_t *pAudCb);
void ABL_AudRecGetFileSyncReq(ResMgr_AppId_e eAppId, ABL_AudFileParam_t *pFileParam, ABL_AudCb_t *pAudCb);
void ABL_AudGetApPathSetting(ResMgr_AppId_e eAppId, ABL_AudFormat_e eFormat, AudPath_e *pPath);
__SLDPM_FREE__ ABL_AudErrCode_e ABL_AudSetMusicMode(ResMgr_AppId_e eAppId, ABL_AudMusicMode_e eMode);
ABL_AudErrCode_e ABL_AudSetDistortedVoice(ResMgr_AppId_e eAppId, ABL_AudDistortedVoice_e eDistortedVoice);

__SLDPM_FREE__ esl_AudioFrequency_e ABL_AudRemapFrequency(ABL_AudFrequency_e eFrequency);
__SLDPM_FREE__ esl_AudRecType_e ABL_AudRemapRecType(ABL_AudRecType_e eRecType);
__SLDPM_FREE__ esl_AudRecStorage_e ABL_AudRemapRecStorage(ABL_AudRecStorage_e eRecStorage);
__SLDPM_FREE__ esl_AudRecPath_e ABL_AudRemapRecPath(ABL_AudRecPath_e eRecPath);
__SLDPM_FREE__ esl_AudRecAppendTimeMode_e ABL_AudRemapRecAppendTime(ABL_AudRecAppendTime_e eAppendTimeMode);
__SLDPM_FREE__ esl_AudRecLimitType_e ABL_AudRemapRecLimitType(ABL_AudRecLimitType_e eLimitType);
__SLDPM_FREE__ esl_AudRecRemainStorage_e ABL_AudRemapRecRemainStorage(ABL_AudRecRemainStorageType_e eStorageType);
__SLDPM_FREE__ MmlAudioEncoderId_e ABL_AudRemapEncoderId(ABL_AudEncoderId_e eEncoderId);
__SLDPM_FREE__ MmlAudioSamplingRate_e ABL_AudRemapSamplingRate(ABL_AudSamplingRate_e eSamplingRate);
__SLDPM_FREE__ MmlAudioChannelMode_e ABL_AudRemapChannelMode(ABL_AudChannelMode_e eChannelMode);
__SLDPM_FREE__ ABL_AudErrCode_e ABL_AudEnableLocalTone(ResMgr_AppId_e eAppId, bool bEnable);

#endif //__SRV_RESMGR_AUD_H__

