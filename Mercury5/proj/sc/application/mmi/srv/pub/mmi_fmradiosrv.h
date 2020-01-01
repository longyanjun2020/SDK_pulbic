/**
* @file mmi_fmradiosrv.h
* Class Id: CLSID_FMRADIOSRV
* This header file defines the data structure and interface of fm radio service.
*/
#ifndef __MMI_FMRADIOSRV_H__
#define __MMI_FMRADIOSRV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_mediasrv_common.h"
#include "mmi_fmradiosrv_def.h"
#include "mmi_audioenvsrv.h"
/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define    MMI_FMRADIOSRV_FREQ_MAX    10800  // 108MHz
#define    MMI_FMRADIOSRV_FREQ_MIN    8750   //87.5MHz

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* FmrSrvHdl_t;

typedef enum
{
    FMRADIOSRV_CHANNEL_STATUS__GET_COMPLETE,
    FMRADIOSRV_CHANNEL_STATUS__START_SEARCH,
    FMRADIOSRV_CHANNEL_STATUS__SEARCH_COMPLETE,
    FMRADIOSRV_CHANNEL_STATUS__STOP_SEARCH,
    FMRADIOSRV_CHANNEL_STATUS__FREQUENCY_CHANGE,
    FMRADIOSRV_CHANNEL_STATUS__INVALID
} FmradioSrvChannelStatus_e;

typedef enum
{
    FMRADIOSRV_PLAY__OFF,
    FMRADIOSRV_PLAY__ON,
    FMRADIOSRV_PLAY__SUSPEND,
    FMRADIOSRV_PLAY__INVALID
} FmradioSrvPlayStatus_e;

typedef enum
{
    FMRADIOSRV_REC__STOP_REC,
    FMRADIOSRV_REC__START_REC,
    FMRADIOSRV_REC__POSITION_UPDATE,
    FMRADIOSRV_REC__SUSPEND_REC,
    FMRADIOSRV_REC__PAUSE_REC,
    FMRADIOSRV_REC__RESUME_REC,
    FMRADIOSRV_REC__NUM
} FmradioSrvRecStatus_e;

typedef enum
{
    FMRADIOSRV_ERROR__STOP_FAIL,
    FMRADIOSRV_ERROR__PLAY_FAIL,
    FMRADIOSRV_ERROR__GET_CHANNEL_FAIL,
    FMRADIOSRV_ERROR__SEARCH_FAIL,
    FMRADIOSRV_ERROR__REC_FAIL,
    FMRADIOSRV_ERROR__REC_FORMAT_NOT_SUPPORT,
    FMRADIOSRV_ERROR__REC_SPACE_FULL,
    FMRADIOSRV_ERROR__NUM
} FmradioSrvErrorType_e;

typedef enum
{
    FMRADIOSRV_EVT_RESMGR_SUSPEND_IND = 0,
    FMRADIOSRV_EVT_RESMGR_RESUME_IND
} FmradioSrvInterruptEvt_e;

typedef struct
{
    FmradioSrvChannelStatus_e eStatus;
    u32 nFrequency;
    u16 nSignal;
    u8 nStereo;
} FmradioSrvChannelInfo_t;

typedef struct
{
    FmradioSrvPlayStatus_e eStatus;
} FmradioSrvPlayInfo_t;

typedef struct
{
    FmradioSrvRecStatus_e eStatus;
    union
    {
        u32 nPosition;
    } uParam;
} FmradioSrvRecInfo_t;

typedef struct
{
    FmradioSrvErrorType_e eError;
    union
    {
        u32 nFrequency;
        u32 eReqType;   //for debug only, cast to (FmradioSrvEvt_e)
    } uParam;
} FmradioSrvErrorInfo_t;


typedef struct
{
    MediaSrvFileFormat_e eFileFormat;
    u16 *pFileName;
    u16 nFileNameLen;
} FmradioSrvFileInfo_t;

typedef struct
{
	FmradioSrvInterruptEvt_e eInterruptEvt;
} FmradioSrvResMgrNotifyData_t;

typedef void (*FmradioSrvResMgrNotifyCb)(void *pThis, FmradioSrvResMgrNotifyData_t *pCbData);
typedef void (*FmradioSrvChannelInfoCb)(void *pThis, u32 nCusData, FmradioSrvChannelInfo_t *pChanInfo);
typedef void (*FmradioSrvPlayStatusCb)(void *pThis, u32 nCusData, FmradioSrvPlayInfo_t *pPlayInfo);
typedef void (*FmradioSrvRecStatusCb)(void *pThis, u32 nCusData, FmradioSrvRecInfo_t *pRecInfo);
typedef void (*FmradioSrvErrorCb)(void *pThis, u32 nCusData, FmradioSrvErrorInfo_t *pErrorInfo);
typedef void (*FmradioSrvHookFunc)(void *pThis, u32 nCusData);

/*=============================================================*/
// Function Declaration
/*=============================================================*/
/** FmradioSrvCreate
* @brief        Request to create FM radio service handle.
*
* @param[in]    pUserInstance             Instanse of user
*
* @retval       handle structure          If it succeeds to accept the setting request.
* @retval       NULL                      Fail to create FM radio service handle.
*/
FmrSrvHdl_t FmradioSrvCreate(void *pUserInstance);

/** FmradioSrvDestroy
* @brief        Request to destroy FM radio service handle.
*
* @param[in]    pFmrSrvHdl             Handle of user
*
* @retval       MAE_RET_SUCCESS          If it succeeds to destroy service.
* @retval       MAE_RET_BAD_PARAM        Fail to create FM radio service handle.
*/
MAE_Ret FmradioSrvDestroy(FmrSrvHdl_t pFmrSrvHdl);

/** FmradioSrvSetArea
* @brief        Request to set FM radio area. The registered callback function will inform whether the setting is successful or not.
*
* @param[in]    eArea                    FM Radio area.
*                                        MEDIASRV_AREA__TAIWAN      To support Taiwan region.
*                                        MEDIASRV_AREA__CHINA       To support China region.
*                                        MEDIASRV_AREA__THAILAND    To support Tailand region.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the setting request.
* @retval       MAE_RET_BAD_PARAM        If the input area is out of range or the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/
MAE_Ret FmradioSrvSetArea(FmrSrvHdl_t pFmrSrvHdl, MediaSrvArea_e eArea);


/** FmradioSrvSetCarrierThreshold
* @brief        Request to set the FM carrier lock/unlock thresholds for channel scanning.
*
* @param[in]    carrierOn                FM radio carrier lock threshold (default: 0x20). carrierOn must be less than carrierOff.
*                                        If setting the value lower, FM module will lock the channel with higher strength.
* @param[in]    carrierOff               FM radio carrier unlock threshold (default: 0x40). carrierOff must be larger than carrierOn.
*                                        If setting the value higher, FM module will unlock the channel with lower quality.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the setting request.
* @retval       MAE_RET_BAD_PARAM        If carrierOn >= carrierOff or the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/
MAE_Ret FmradioSrvSetCarrierThreshold(FmrSrvHdl_t pFmrSrvHdl, u8 carrierOn, u8 carrierOff);

/** FmradioSrvSetAreaConfig
* @brief        Request to set FM radio area related parameters, like de-emphasis, step space, BPFIR, channel scanning range and carrier lock/unlock threshold.
*
* @param[in]    pAreaConfig              The pointer to FM radio area related parameters.
*                                        De-emphasis(eFmrDeEmphasis)          : FMRADIOSRV_DEEMPHASIS_50US or FMRADIOSRV_DEEMPHASIS_75US.
*                                        Step space(eFmrStepSpace)            : FMRADIOSRV_STEP_50KHZ, FMRADIOSRV_STEP_100KHZ, FMRADIOSRV_STEP_200KHZ, FMRADIOSRV_STEP_30KHZ or FMRADIOSRV_STEP_300KHZ.
*                                        BPFIR(eFmrBpfir)                     : FMRADIOSRV_BPFIR_100KHZ, FMRADIOSRV_BPFIR_120KHZ, FMRADIOSRV_BPFIR_150KHZ or FMRADIOSRV_BPFIR_200KHZ.
*                                        Begin range(eFmrBeginRange)          : FMRADIOSRV_BEGIN_66MHZ, FMRADIOSRV_BEGIN_68MHZ, FMRADIOSRV_BEGIN_73MHZ, FMRADIOSRV_BEGIN_76MHZ,
*                                                                               FMRADIOSRV_BEGIN_87_5MHZ, FMRADIOSRV_BEGIN_87_8MHZ, FMRADIOSRV_BEGIN_88MHZ or FMRADIOSRV_BEGIN_100MHZ
*                                        End range(eFmrEndRange)              : FMRADIOSRV_END_68MHZ, FMRADIOSRV_END_73MHZ, FMRADIOSRV_END_74MHZ, FMRADIOSRV_END_87_5MHZ,
*                                                                               FMRADIOSRV_END_90MHZ, FMRADIOSRV_END_100MHZ or FMRADIOSRV_END_108MHZ
*                                        Carrier lock threshold(nCarrierOn)   : default value is 0x20
*                                        Carrier unlock threshold(nCarrierOff): default value is 0x40
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the setting request.
* @retval       MAE_RET_BAD_PARAM        If the input area parameter data is NULL or the set data are invalid. Also, if the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/

MAE_Ret FmradioSrvSetAreaConfig(FmrSrvHdl_t pFmrSrvHdl, FmradioSrvAreaConfig_t *pAreaConfig);


/** FmradioSrvGetArea
* @brief     Request to get FM radio area related parameters, like de-emphasis, step space, BPFIR, channel scanning range and carrier lock/unlock threshold.
*
* @retval    NULL                    If there's no enough memory to do allocation for service instance or the service data is NULL.
* @retval    Area related pointer    The pointer to FM radio area related parameters. The memory space pointed by this return pointer can't be released because it's kept inside the service.
*                                    De-emphasis(eFmrDeEmphasis)          : FMRADIOSRV_DEEMPHASIS_50US or FMRADIOSRV_DEEMPHASIS_75US.
*                                    Step space(eFmrStepSpace)            : FMRADIOSRV_STEP_50KHZ, FMRADIOSRV_STEP_100KHZ, FMRADIOSRV_STEP_200KHZ, FMRADIOSRV_STEP_30KHZ or FMRADIOSRV_STEP_300KHZ.
*                                    BPFIR(eFmrBpfir)                     : FMRADIOSRV_BPFIR_100KHZ, FMRADIOSRV_BPFIR_120KHZ, FMRADIOSRV_BPFIR_150KHZ or FMRADIOSRV_BPFIR_200KHZ.
*                                    Begin range(eFmrBeginRange)          : FMRADIOSRV_BEGIN_66MHZ, FMRADIOSRV_BEGIN_68MHZ, FMRADIOSRV_BEGIN_73MHZ, FMRADIOSRV_BEGIN_76MHZ,
*                                                                           FMRADIOSRV_BEGIN_87_5MHZ, FMRADIOSRV_BEGIN_87_8MHZ, FMRADIOSRV_BEGIN_88MHZ or FMRADIOSRV_BEGIN_100MHZ
*                                    End range(eFmrEndRange)              : FMRADIOSRV_END_68MHZ, FMRADIOSRV_END_73MHZ, FMRADIOSRV_END_74MHZ, FMRADIOSRV_END_87_5MHZ,
*                                                                           FMRADIOSRV_END_90MHZ, FMRADIOSRV_END_100MHZ or FMRADIOSRV_END_108MHZ
*                                    Carrier lock threshold(nCarrierOn)   : default value is 0x20
*                                    Carrier unlock threshold(nCarrierOff): default value is 0x40
*/
FmradioSrvAreaConfig_t* FmradioSrvGetAreaConfig(FmrSrvHdl_t pFmrSrvHdl);
/** FmradioSrvSetVolume
* @brief        Request to set FM radio volume.
*
* @param[in]    nVolume                  The FM Radio volume(0~8).
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to set FM radio volume.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the input volume is out of range.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret FmradioSrvSetVolume(FmrSrvHdl_t pFmrSrvHdl, AudioEnvSrvVolLevel_e eVolume);

/** FmradioSrvGetVolume
* @brief        Request to get FM radio volume.
*
* @retval       0     The level 0 volume.
* @retval       1     The level 1 volume.
* @retval       2     The level 2 volume.
* @retval       3     The level 3 volume.
* @retval       4     The level 4 volume.
* @retval       5     The level 5 volume.
* @retval       6     The level 6 volume.
* @retval       7     The level 7 volume.
* @retval       8     The level 8 volume.
*/
AudioEnvSrvVolLevel_e FmradioSrvGetVolume(FmrSrvHdl_t pFmrSrvHdl);

/** FmradioSrvSetAudioPath
* @brief        Request to set the audio output path(medium), like handset, headset, speaker, BT headset, etc.
*
* @param[in]    eAudPath             The audio output path(medium).
*                                    FMRADIOSRV_PREF_PATH__HEADSET          The headset.
*                                    FMRADIOSRV_PREF_PATH__SPEAKER          The speaker.
*                                    FMRADIOSRV_PREF_PATH__BT_HEADSET       The bluetooth headset.
*                                    FMRADIOSRV_PREF_PATH__RIGHT_SPEAKER    The right-side speaker.
*                                    FMRADIOSRV_PREF_PATH__LEFT_SPEAKER     The left-side speaker.
* @retval       MAE_RET_SUCCESS      If it succeeds to request to set the audio output path(medium).
* @retval       MAE_RET_BAD_PARAM    If the service data is NULL.
*/
MAE_Ret FmradioSrvSetAudioPath(FmrSrvHdl_t pFmrSrvHdl, FmradioSrvPrefAudPath_e eAudPath);

/** FmradioSrvSetChannel
* @brief        Request to set FM radio frequency (the unit is 0.01MHz). After succeeding to set the frequency, the FM radio will play according to the newly set frequency.
*
* @param[in]    nFrequency               The FM radio frequency (the unit is 0.01MHz).
*                                        The range should be among MMI_FMRADIOSRV_FREQ_MIN and MMI_FMRADIOSRV_FREQ_MAX.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to set FM radio frequency.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the input frequency is out of range.
* @retval       MAE_RET_FAILED           If the FM radio is interrupted.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret FmradioSrvSetChannel(FmrSrvHdl_t pFmrSrvHdl, u32 nFrequency);

/** FmradioSrvGetFrequency
* @brief     Request to get the FM radio frequency (the unit is 0.01MHz).
* @retval    0      If there's no enough memory to do allocation for service instance or the service data is NULL.
* @retval    n>0    The current FM radio frequency (the unit is 0.01MHz).
*/
u32 FmradioSrvGetFrequency(FmrSrvHdl_t pFmrSrvHdl);
MAE_Ret FmradioSrvSearchChannel(FmrSrvHdl_t pFmrSrvHdl, FmradioSrvSearchChannelDirection_e eDirection);
MAE_Ret FmradioSrvCancelSearch(FmrSrvHdl_t pFmrSrvHdl);
MAE_Ret FmradioSrvGetChannelInfo(FmrSrvHdl_t pFmrSrvHdl);

MAE_Ret FmradioSrvPlay(FmrSrvHdl_t pFmrSrvHdl);
MAE_Ret FmradioSrvStop(FmrSrvHdl_t pFmrSrvHdl);
MAE_Ret FmradioSrvSetRecordFormat(FmrSrvHdl_t pFmrSrvHdl, MediaSrvAudCodec_e eType);
MAE_Ret FmradioSrvSetRecordPath(FmrSrvHdl_t pFmrSrvHdl, MediaSrvRecPath_e eType, const MAE_WChar *pPath);
MAE_WChar * FmradioSrvGetRecordFile(FmrSrvHdl_t *pFmrSrvHdl);
MAE_Ret FmradioSrvStartRecord(FmrSrvHdl_t pFmrSrvHdl);
MAE_Ret FmradioSrvStopRecord(FmrSrvHdl_t pFmrSrvHdl);
MAE_Ret FmradioSrvResumeRecord(FmrSrvHdl_t pFmrSrvHdl);
MAE_Ret FmradioSrvPauseRecord(FmrSrvHdl_t pFmrSrvHdl);
FmradioSrvStatus_e FmradioSrvGetStatus(FmrSrvHdl_t pFmrSrvHdl);
MAE_Ret FmradioSrvQueryBuiltInAntennaSupport(bool *pAntennaSupported);
MAE_Ret FmradioSrvSetPlayStatusCb(FmrSrvHdl_t pFmrSrvHdl, u32 nCusData, FmradioSrvPlayStatusCb pfnStatusChange);
MAE_Ret FmradioSrvSetChannelInfoCb(FmrSrvHdl_t pFmrSrvHdl, u32 nCusData, FmradioSrvChannelInfoCb pfnFmradioSrvCb);
MAE_Ret FmradioSrvSetRecStatusCb(FmrSrvHdl_t pFmrSrvHdl, u32 nCusData, FmradioSrvRecStatusCb pfnStatusChange);
MAE_Ret FmradioSrvSetErrorCb(FmrSrvHdl_t pFmrSrvHdl, u32 nCusData, FmradioSrvErrorCb pfnErrorCb);
MAE_Ret FmradioSrvSetPlugOutHeadsetHookFunc(FmrSrvHdl_t pFmrSrvHdl, u32 nCusData, FmradioSrvHookFunc pfnHook);
MAE_Ret FmradioSrvSetPlugInHeadsetHookFunc(FmrSrvHdl_t pFmrSrvHdl, u32 nCusData, FmradioSrvHookFunc pfnHook);
MAE_Ret FmradioSrvSetResMgrNotifyCb(FmrSrvHdl_t pFmrSrvHdl, u32 nServiceClient, FmradioSrvResMgrNotifyCb pfnResMgrNotifyCb);
boolean FmradioSrvIsBusy(FmrSrvHdl_t pFmrSrvHdl);
#endif /* __MMI_FMRADIOSRV_H__ */

