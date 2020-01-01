/**
* @file srv_ResMgr_Tv.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of analog TV.
*
*/

#ifndef __SRV_RESMGR_TV_H__
#define __SRV_RESMGR_TV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_tv_itf.h"
#include "MediaRspItf.h"
//#include "MML_Tv.h"
#include "ABL_Cam.h"
#include "srv_resmgr_mmlimage_types.h"
#include "srv_resmgr_mmltv_types.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
#define ABL_TV_STORAGE_PATH     ESL_TV_STORAGE_PATH
typedef enum ABL_TvErrCode_e_
{
    ABL_TV_OK,               //ESL_TV_OK
    ABL_TV_FAIL,             //ESL_TV_FAIL
    ABL_TV_PARAM_ERROR,      //ESL_TV_PARAM_ERROR
    ABL_TV_MEM_ALLOC_ERROR,  //ESL_TV_MEM_ALLOC_ERROR
    ABL_TV_REJECT,           //ESL_TV_REJECT
    ABL_TV_ABORT,            //ESL_TV_ABORT,
    ABL_TV_TIMEOUT,          //ESL_TV_TIMEOUT
    ABL_TV_DENY,
    ABL_TV_MERGE,
    ABL_TV_WAIT_APPSTOP_DROP
} ABL_TvErrCode_e;

typedef struct DBLTvRemapErrCode_t_
{
    ABL_TvErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLTvRemapErrCode_t;

typedef enum ABL_TvType_e_
{
    ABL_TV_ATV,     //ESL_TV_ATV
    ABL_TV_DTV,     //ESL_TV_DTV
    ABL_TV_AUDIO,   //ESL_TV_AUDIO
    ABL_TV_LC_TEST, //ESL_TV_LC_TEST
    ABL_TV_MAX      //ESL_TV_MAX
} ABL_TvType_e;

typedef enum ABL_TvPreview_e_
{
    ABL_TV_PREVIEW_OFF,   //ESL_TV_PREVIEW_OFF
    ABL_TV_PREVIEW_ON     //ESL_TV_PREVIEW_ON
} ABL_TvPreview_e;

typedef enum ABL_TvCaptureRes_e_
{
    ABL_TV_1600_1200,     //ESL_TV_1600_1200
    ABL_TV_1280_1024,     //ESL_TV_1280_1024
    ABL_TV_1024_768,      //ESL_TV_1024_768
    ABL_TV_800_600,       //ESL_TV_800_600
    ABL_TV_640_480,       //ESL_TV_640_480
    ABL_TV_480_320,       //ESL_TV_480_320
    ABL_TV_400_240,       //ESL_TV_400_240
    ABL_TV_320_240,       //ESL_TV_320_240
    ABL_TV_240_320,       //ESL_TV_240_320
    ABL_TV_220_176,       //ESL_TV_220_176
    ABL_TV_176_220,       //ESL_TV_176_220
    ABL_TV_176_144,       //ESL_TV_176_144
    ABL_TV_160_120,       //ESL_TV_160_120
    ABL_TV_96_96,         //ESL_TV_96_96
} ABL_TvCaptureRes_e;

typedef enum ABL_TvQuality_e_
{
    ABL_TV_QUALITY_LOW,     //ESL_TV_QUALITY_LOW
    ABL_TV_QUALITY_NORMAL,  //ESL_TV_QUALITY_NORMAL
    ABL_TV_QUALITY_HIGH     //ESL_TV_QUALITY_HIGH
} ABL_TvQuality_e;

typedef enum{
  ABL_TV_LEFTCHANNEL,
  ABL_TV_RIGHTCHANNEL,
}ABL_TvSoundChannel_e;

/**
 *  @brief The enumeration defines the tv capture recording quality.
 */
typedef enum {
  ABL_TV_ESG_TYP_NORMAL,       /* Normal ESG data */
  ABL_TV_ESG_TYP_INFO_UPDATE,  /* ESG Information update */
  ABL_TV_ESG_TYP_BROADCAST     /* ESG Broadcasting */
} ABL_TvEsgType_e;

/**
 *  @brief The enumeration defines for tv set frequency.
 */
typedef enum {
  ABL_TV_SET_FREQ_GET_INFO,    /* Notify Normal ESG data after setting frequency */
  ABL_TV_SET_FREQ_NO_INFO,     /* no ESG Information update  after setting frequency*/
} ABL_TvSetFreqType_e;


typedef enum ABL_TvShotMode_e_
{
    ABL_TV_SINGLE,          //ESL_TV_SINGLE
    ABL_TV_CONSSINGLE,      //ESL_TV_CONSSINGLE
    ABL_TV_SINGLE_DTV       //ESL_TV_SINGLE_DTV
} ABL_TvShotMode_e;

typedef enum ABL_TvSoundPath_e_
{
    ABL_TV_SOUND_DEFAULT,   //ESL_TV_SOUND_DEFAULT
    ABL_TV_SOUND_DOWNLOAD,  //ESL_TV_SOUND_DOWNLOAD
    ABL_TV_SOUND_CARD       //ESL_TV_SOUND_CARD
} ABL_TvSoundPath_e;

typedef enum ABL_TvRotate_e_
{
    ABL_TV_ROTATE_NONE,       //ESL_TV_ROTATE_NONE
    ABL_TV_ROTATE_90,         //ESL_TV_ROTATE_90
    ABL_TV_ROTATE_180,        //ESL_TV_ROTATE_180
    ABL_TV_ROTATE_270         //ESL_TV_ROTATE_270
} ABL_TvRotate_e;

typedef enum ABL_TvCmd_e_
{
    ABL_TV_CMD_TSP_START,             //ESL_TV_CMD_TSP_START
    ABL_TV_CMD_TSP_PAUSE,             //ESL_TV_CMD_TSP_PAUSE
    ABL_TV_CMD_TSP_RESUME,            //ESL_TV_CMD_TSP_RESUME
    ABL_TV_CMD_TSP_STOP,              //ESL_TV_CMD_TSP_STOP
    ABL_TV_CMD_COMMAND_CANCEL,        //ESL_TV_CMD_COMMAND_CANCEL
} ABL_TvCmd_e;

/**
 *  @brief The enumeration defines the canel
 */
typedef enum {
  ABL_TV_CANCEL_SCAN,         //ESL_TV_CANCEL_SCAN,
  ABL_TV_CANCEL_SET_FREQ,     //ESL_TV_CANCEL_SET_FREQ,
} ABL_TvCancelType_e;

typedef enum ABL_TvLimitType_e_
{
    ABL_TV_LIMIT_SIZE,      //ESL_TV_LIMIT_SIZE
    ABL_TV_LIMIT_TIME       //ESL_TV_LIMIT_TIME
} ABL_TvLimitType_e;

typedef esl_TvConfig_t ABL_TvConfig_t;
typedef esl_TvScanConfig_t ABL_TvScanConfig_t;
typedef esl_TvPreview_t ABL_TvPrev_t;
typedef esl_TvDispRegion_t ABL_TvDispRegion_t;
typedef esl_TvJpegSetting_t ABL_TvJpegSetting_t;
typedef esl_TvRegion_t ABL_TvRegion_t;
typedef esl_TvSound_t ABL_TvSound_t;
typedef esl_TvFileName_t ABL_TvFileName_t;
typedef esl_TvInfo_t ABL_TvInfo_t;
typedef esl_TvPathSetting_t ABL_TvPathSetting_t;
typedef esl_TvRecLimit_t ABL_TvRecLimit_t;
typedef esl_TvSize_t ABL_TvSize_t;
typedef esl_TvCapture_t ABL_TvCapture_t;
typedef esl_TvRecSetting_t ABL_TvRecSetting_t;
typedef esl_TvData_t ABL_TvData_t;
typedef esl_TvEmData_t ABL_TvEmData_t;
typedef MmlTvSetTvConfiguration_t   ABL_TvSetTvConfiguratioin_t;
typedef MmlTvGetTvInfo_t            ABL_TvGetTVInfo_t;
typedef MmlTvSwitchChannel_t        ABL_TvSwitchingChannel_t;
typedef MmlTvScanChannel_t          ABL_TvScanningChannel_t;
typedef MmlTvScanFrequency_t        ABL_TvScanningFrequency_t;
typedef MmlTvStartPreview_t         ABL_TvStartPreview_t;
typedef MmlTvResetWindow_t          ABL_TvResettingWindow_t;
typedef MmlImageEncodeCompleteInfo_t ABL_TvEncodeComplete_t;
typedef	struct ABL_TvShutterSound_t_
{
	u8 bIsEnable;
	u8 *pBuffer;
	u32 nBufferSize;
} ABL_TvShutterSound_t;

typedef struct ABL_TvRspInfo_t_
{
    ABL_TvErrCode_e eErrCode;
    ABL_TvInfo_t tTvInfo;
} ABL_TvRspInfo_t;

typedef enum ABL_TvNotifyErr_e_
{
    ABL_TV_NOTIFY_ERROR_CAPTURE = 0,       //ESL_TV_ERROR_CAPTURE
    ABL_TV_NOTIFY_ERROR_SPACE_FULL,        //ESL_TV_ERROR_SPACE_FULL
    ABL_TV_NOTIFY_ERROR_UNKNOWN,           //ESL_TV_ERROR_UNKNOWN
    ABL_TV_NOTIFY_ERROR_SETFREQ,           //ESL_TV_ERROR_SETFREQ
    ABL_TV_NOTIFY_ERROR_NONE,              //ESL_TV_ERROR_NONE
    ABL_TV_NOTIFY_ERROR_MEMORY_INSUFFICIENT
} ABL_TvNotifyErr_e;

typedef enum ABL_TvRegion_e_
{
    ABL_TV_REGION_USA,          //ESL_TV_REGION_USA
    ABL_TV_REGION_CANADA,       //ESL_TV_REGION_CANADA
    ABL_TV_REGION_KOREA,        //ESL_TV_REGION_KOREA
    ABL_TV_REGION_TAIWAN,       //ESL_TV_REGION_TAIWAN
    ABL_TV_REGION_MEXICO,       //ESL_TV_REGION_MEXICO
    ABL_TV_REGION_CHILE,        //ESL_TV_REGION_CHILE
    ABL_TV_REGION_VENEZUELA,    //ESL_TV_REGION_VENEZUELA
    ABL_TV_REGION_PHILIPPINES,  //ESL_TV_REGION_PHILIPPINES
    ABL_TV_REGION_JAMAICA,      //ESL_TV_REGION_JAMAICA
    ABL_TV_REGION_CHINA,        //ESL_TV_REGION_CHINA
    ABL_TV_REGION_SHENZHEN,     //ESL_TV_REGION_SHENZHEN
    ABL_TV_REGION_VIETNAM,      //ESL_TV_REGION_VIETNAM
    ABL_TV_REGION_WESTERNEUROPE,//ESL_TV_REGION_WESTERNEUROPE
    ABL_TV_REGION_TURKEY,       //ESL_TV_REGION_TURKEY
    ABL_TV_REGION_UAE,          //ESL_TV_REGION_UAE
    ABL_TV_REGION_AFGHANISTAN,  //ESL_TV_REGION_AFGHANISTAN
    ABL_TV_REGION_SINGAPORE,    //ESL_TV_REGION_SINGAPORE
    ABL_TV_REGION_THAILAND,     //ESL_TV_REGION_THAILAND
    ABL_TV_REGION_CAMBODIA,     //ESL_TV_REGION_CAMBODIA
    ABL_TV_REGION_INDONESIA,    //ESL_TV_REGION_INDONESIA
    ABL_TV_REGION_MALAYSIA,     //ESL_TV_REGION_MALAYSIA
    ABL_TV_REGION_LAOS,         //ESL_TV_REGION_LAOS
    ABL_TV_REGION_PORTUGAL,     //ESL_TV_REGION_PORTUGAL
    ABL_TV_REGION_SWEDEN,       //ESL_TV_REGION_SWEDEN
    ABL_TV_REGION_PAKISTAN,     //ESL_TV_REGION_PAKISTAN
    ABL_TV_REGION_SPAIN,        //ESL_TV_REGION_SPAIN
    ABL_TV_REGION_JAPAN,        //ESL_TV_REGION_JAPAN
    ABL_TV_REGION_UK,           //ESL_TV_REGION_UK
    ABL_TV_REGION_HONGKONG,     //ESL_TV_REGION_HONGKONG
    ABL_TV_REGION_SOUTHAFRICA,  //ESL_TV_REGION_SOUTHAFRICA
    ABL_TV_REGION_BRAZIL,       //ESL_TV_REGION_BRAZIL
    ABL_TV_REGION_ARGENTINA,    //ESL_TV_REGION_ARGENTINA
    ABL_TV_REGION_INDIA,        //ESL_TV_REGION_INDIA
    ABL_TV_REGION_BURMA,        //ESL_TV_REGION_BURMA
    ABL_TV_REGION_SUDAN,        //ESL_TV_REGION_SUDAN
    ABL_TV_REGION_YEMEN,        //ESL_TV_REGION_YEMEN
    ABL_TV_REGION_PERU,         //ESL_TV_REGION_PERU
    ABL_TV_REGION_BOLIVIA,      //ESL_TV_REGION_BOLIVIA
    ABL_TV_REGION_ECUADOR,      //ESL_TV_REGION_ECUADOR
    ABL_TV_REGION_SURINAME,     //ESL_TV_REGION_SURINAME
    ABL_TV_REGION_AUSTRALIA,    //ESL_TV_REGION_AUSTRALIA
    ABL_TV_REGION_NEWZEALAND,   //ESL_TV_REGION_NEWZEALAND
    ABL_TV_REGION_COLUMBIA,     //ESL_TV_REGION_COLUMBIA
    ABL_TV_REGION_COSTARICA,    //ESL_TV_REGION_COSTARICA
    ABL_TV_REGION_HONDURAS,     //ESL_TV_REGION_HONDURAS
    ABL_TV_REGION_GERMAN,       //ESL_TV_REGION_GERMAN
    ABL_TV_REGION_ITALY,        //ESL_TV_REGION_ITALY
    ABL_TV_REGION_TOTAL         //ESL_TV_REGION_TOTAL
} ABL_TvRegion_e;

typedef enum ABL_TvPath_e_
{
    ABL_TV_PATH_DIR,            //ESL_TV_PATH_DIR
    ABL_TV_PATH_PREFIX,         //ESL_TV_PATH_PREFIX
    ABL_TV_PATH_ABSOLUTE        //ESL_TV_PATH_ABSOLUTE
} ABL_TvPath_e;

typedef enum ABL_TvSignalLv_e_
{
    ABL_TV_SIGNAL_LV_NONE = 0,    //ESL_TV_SIGNAL_LV_NONE
    ABL_TV_SIGNAL_LV_1,           //ESL_TV_SIGNAL_LV_1
    ABL_TV_SIGNAL_LV_2,           //ESL_TV_SIGNAL_LV_2
    ABL_TV_SIGNAL_LV_3,           //ESL_TV_SIGNAL_LV_3
    ABL_TV_SIGNAL_LV_4,           //ESL_TV_SIGNAL_LV_4
    ABL_TV_SIGNAL_LV_5,           //ESL_TV_SIGNAL_LV_5
    ABL_TV_SIGNAL_LV_6,           //ESL_TV_SIGNAL_LV_6
    ABL_TV_SIGNAL_LV_7,           //ESL_TV_SIGNAL_LV_7
    ABL_TV_SIGNAL_LV_8,           //ESL_TV_SIGNAL_LV_8
    ABL_TV_SIGNAL_LV_MAX          //ESL_TV_SIGNAL_LV_MAX
} ABL_TvSignalLv_e;

/**
 *  @brief The sturcture defines the notificaiton value for application layer.
 *			should sync. with esl_TvNotifyInfo_t
 */
typedef struct ABL_TvNotifyInfo_t_
{
    MediaRspId_e notifyTyp;
    ABL_TvNotifyErr_e errorTyp;
    union
    {
        u32             position;
        esl_TvData_t    esgData;
        esl_TvEmData_t  emData;
        ABL_TvEncodeComplete_t tEncodeCompleteInfo;
    } param;
} ABL_TvNotifyInfo_t;

typedef void (*ABL_TvCb)(u16 uSenderId, u32 uUserValue, ABL_TvErrCode_e eErrCode, ABL_TvInfo_t *pTvInfo);

typedef struct ABL_TvCb_t_
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_TvCb pfnCb;
} ABL_TvCb_t;

typedef struct ABL_TvSetConfig_t_
{
    //ABL_TvType_e eTvType;
    ABL_TvConfig_t tTvConfig;
} ABL_TvSetConfig_t;

typedef struct ABL_TvSwitchChannel_t_
{
    u32 uCh;
} ABL_TvSwitchChannel_t;

typedef struct ABL_TvScanChannel_t_
{
    ABL_TvScanConfig_t tTvScanConfig;
} ABL_TvScanChannel_t;

typedef struct ABL_TvPreview_t_
{
    ABL_TvPrev_t tTvPreview;
    ABL_TvDispRegion_t tTvDispRegion;
} ABL_TvPreview_t;

typedef struct ABL_TvCapturePic_t_
{
    ABL_TvJpegSetting_t tTvJpegSetting;
} ABL_TvCapturePic_t;

typedef struct ABL_TvResetWindow_t_
{
    ABL_TvRegion_t tTvRegion;
    ABL_TvRotate_e eTvRotateAngle;
} ABL_TvResetWindow_t;

typedef struct ABL_TvSetShutterSound_t_
{
    u8 uEnable;
    ABL_TvSound_t tSound;
} ABL_TvSetShutterSound_t;

typedef struct ABL_TvGetFileName_t_
{
    ABL_TvFileName_t tFileName;
} ABL_TvGetFileName_t;

typedef struct ABL_TvGetEmInfoReq_t_
{
    u32 uFrequence;
} ABL_TvGetEmInfoReq_t;


typedef struct
{
  ABL_TvSetFreqType_e tTvFreqType;
  u32 ufreq;
} ABL_TvSetFreq_t;

typedef struct TvCmd_t_
{
    ABL_TvCb_t *pCbParams;
    ABL_TvType_e eTvType;
    union
    {
        ABL_TvSetTvConfiguratioin_t     tTvSetTvConfiguration;
        ABL_TvGetTVInfo_t               tTvGetTvInfo;
        ABL_TvSwitchingChannel_t        tTvSwitchingChannel;
        ABL_TvScanningChannel_t         tTvScanningChannel;
        ABL_TvScanningFrequency_t       tTvScanningFrequency;
        ABL_TvStartPreview_t            tTvStartPreview;
        ABL_ImageEncodeImage_t          tEncodeImage;
        ABL_TvResettingWindow_t         tTvResettingWindow;
        ABL_TvSetConfig_t tTvSetConfigParams;//ABL_TvSetConfig_t tTvSetConfigParams;
        ABL_TvSwitchChannel_t tTvSwitchChanParams;
        ABL_TvScanChannel_t tTvScanChanParams;
        ABL_TvPreview_t tTvPreviewParams;
        ABL_TvCapturePic_t tTvCaptureParams;
        ABL_TvResetWindow_t tTvResetWindowParams;
        ABL_TvSetShutterSound_t tTvSetShutterSoundParams;
        ABL_TvGetFileName_t tTvGetFileNameParams;
        ABL_TvGetEmInfoReq_t tTvGetEmInfoReq;
    } tParams;
} TvCmd_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ABL_CmnErrCode_e ABL_TvOpenSessionReq(ResMgr_AppId_e eAppId, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvCloseSessionReq(ResMgr_AppId_e eAppId, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvOpenReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvCloseReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvSetConfigReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvSetTvConfiguratioin_t *pTvConfig, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvGetInfoReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType,  ABL_TvGetTVInfo_t *pTvInfo, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvGetEmInfoReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, u32 uFrequence, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvSwitchChannelReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvSwitchingChannel_t *pTvSwitchingChannel, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvScanChannelReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, u32 nChannel, u16 *pChannelName, u32 nChannelNameLen, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvPreviewReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvPreview_e eTvPreview, ABL_TvStartPreview_t *pTvStartPreview, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvPreviewSyncReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvPreview_e eTvPreview, ABL_TvStartPreview_t *pTvStartPreview, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvCaptureReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvJpegSetting_t *pTvJpegSetting, ABL_TvShutterSound_t *pTvShutSound,ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvResetWindowReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvRegion_t *pRegion, ABL_TvRotate_e eRotateAngle, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvSetShutterSoundReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, u8 uEnable, ABL_TvSound_t *pSound, ABL_TvCb_t *pTvCb);
ABL_CmnErrCode_e ABL_TvGetFileNameReq(ResMgr_AppId_e eAppId, ABL_TvType_e eTvType, ABL_TvFileName_t *pFileName, ABL_TvCb_t *pTvCb);
esl_TvPath_e ABL_TvRemapPath(ABL_TvPath_e eTvPath);
esl_TvType_e ABL_TvRemapTvType(ABL_TvType_e eTvType);
esl_TvPreview_e ABL_TvRemapPreviewType(ABL_TvPreview_e ePrevType);
esl_TvRotate_e ABL_TvRemapRotate(ABL_TvRotate_e eRotate);
esl_TvSoundPath_e ABL_TvRemapSoundPath(ABL_TvSoundPath_e eSoundPath);
esl_TvCaptureRes_e ABL_TvRemapCaptureRes(ABL_TvCaptureRes_e eCaptureRes);
esl_TvQuality_e ABL_TvRemapQuality(ABL_TvQuality_e eQuality);
esl_TvShotMode_e ABL_TvRemapShotMode(ABL_TvShotMode_e eShotMode);
MmlTvRegion_e ABL_TvRemapRegion(ABL_TvRegion_e eRegion);
esl_TvSignalLv_e ABL_TvRemapSignalLevel(ABL_TvSignalLv_e eSignalLevel);
#endif //__ABL_TV_H__

