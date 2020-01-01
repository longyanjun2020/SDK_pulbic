/**
* @file    mmi_srv_fmradio.h
* @brief   This service is to provide the interface to manipulate the FM radio, included of area, channel volume, and output audio path. Basically, FM channel can be changed
*          by the APIs provided here, too. The advanced feature is to support the FM radio recording. By this service, it will be much easier to implement the user interface
*          to listent to FM radio and record the channel.
*/

#ifndef __MMI_SRV_FMRADIO_H__
#define __MMI_SRV_FMRADIO_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_fmradiosrv.h"
#include "mmi_mediasrv_common.h"

/** SrvFmradioPlayStatusCb
* @brief         The callback function to notify the changed status. (triggered by FMRADIOSRV_EVT_StatusChangeInd event)
*
* @param[out]    pThis      The pointer of the applet.
* @param[out]    eStatus    The changed status.
*                           FMRADIOSRV_STATUS__IDLE       The idle state.
*                           FMRADIOSRV_STATUS__PLAY       The FM radio playing state.
*                           FMRADIOSRV_STATUS__RECORD     The recording state.
*                           FMRADIOSRV_STATUS__INVALID    The invalid state.
*/
typedef void (*SrvFmradioPlayStatusCb )(void *pThis, u32 nCusData, FmradioSrvPlayInfo_t *pPlayInfo);

typedef void (*SrvFmradioChannelInfoCb)(void *pThis, u32 nCusData, FmradioSrvChannelInfo_t *pChanInfo);

/** SrvFmradioRecStatusNotify
* @brief         The callback function to notify the recording status. (triggered by FMRADIOSRV_EVT_RecStatusChangeInd event)
*
* @param[out]    pThis      The pointer of the applet.
* @param[out]    eStatus    The recording status.
*                           FMRADIOSRV_REC_STATUS__END                   The recording reaches the end which is set by user. In general, the set end might be the expected the duration.
*                           FMRADIOSRV_REC_STATUS__SAPCE_FULL            The space of the target volume is full.
*                           FMRADIOSRV_REC_STATUS__ERROR                 There exists some recoding errors.
*                           FMRADIOSRV_REC_STATUS__POSITION_UPDATE       Every one second to update the current recording duration.
*                           FMRADIOSRV_REC_STATUS__SCH_TIMEOUT           The scheduled timer is expired.
*                           FMRADIOSRV_REC_STATUS__SCH_FILE_NOT_EXIST    NAND space is not available.
* @param[out]    pInfo      The notified recording information. There're three possible informations accordingly.
*                           1. eErrCode:  The detailed reason for errors. (for FMRADIOSRV_REC_STATUS__ERROR)
*                                         MEDIASRV_ERR__OK/MEDIASRV_ERR__FAIL/MEDIASRV_ERR__DENY/MEDIASRV_ERR__FORMAT_NOT_SUPPORT/MEDIASRV_ERR__NO_MEMORY/
*                                         MEDIASRV_ERR__FILE_DATA_FAIL/MEDIASRV_ERR__SDCARD_NOT_DETECTED/MEDIASRV_ERR__FORMAT_NOT_MATCH/MEDIASRV_ERR__ABORT/MEDIASRV_ERR__UNKNOWN
*                           2. nPosition: The current recording duration. (for FMRADIOSRV_REC_STATUS__POSITION_UPDATE)
*                           3. tFileInfo: The recorded file information. (for FMRADIOSRV_REC_STATUS__SAPCE_FULL/FMRADIOSRV_REC_STATUS__SCH_TIMEOUT)
*/
typedef void (*SrvFmradioRecStatusNotify)(void *pThis, u32 nCusData, FmradioSrvRecInfo_t *pRecInfo);

typedef void (*SrvFmradioErrorCb)(void *pThis, u32 nCusData, FmradioSrvErrorInfo_t *pErrorInfo);

/** SrvFmradioSetStatusChangeCb
* @brief        Register/deregister a callback function which will be triggered when the status of FM radio sevice is changed.
*
* @param[in]    pfnEmradioSrvCb          The callback function which will be called to notify the changed status(FMRADIOSRV_STATUS__IDLE/FMRADIOSRV_STATUS__PLAY/FMRADIOSRV_STATUS__RECORD).
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the registering/deregistering request.
* @retval       MAE_RET_BAD_PARAM        If the service data, notifier, or listener is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvFmradioSetPlayStatusCb(u32 nCusData, SrvFmradioPlayStatusCb pfnStatusChange);

/** SrvFmradioSetSearchChannelCb
@brief  Set a call back function to listen search channel event
@
@param[in]      pfnSearchNotify	Search channel notify call back function pointer.
@
*/
MAE_Ret SrvFmradioSetChannelInfoCb(u32 nCusData, SrvFmradioChannelInfoCb pfnSearchNotify);

/** SrvFmradioSetRecStatusCb
* @brief        Register/deregister a callback function which will be triggered when the status of recording is changed.
*
* @param[in]    pfnRecNotify             The callback function which will be called to notify the changed recording status
*                                        FMRADIOSRV_REC_STATUS__END/FMRADIOSRV_REC_STATUS__SAPCE_FULL/FMRADIOSRV_REC_STATUS__ERROR/
*                                        FMRADIOSRV_REC_STATUS__POSITION_UPDATE/FMRADIOSRV_REC_STATUS__SCH_TIMEOUT/FMRADIOSRV_REC_STATUS__SCH_FILE_NOT_EXIST
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the registering/deregistering request.
* @retval       MAE_RET_BAD_PARAM        If the service data, notifier, or listener is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/
MAE_Ret SrvFmradioSetRecStatusCb(u32 nCusData, SrvFmradioRecStatusNotify pfnRecNotify);

MAE_Ret SrvFmradioSetErrorCb(u32 nCusData, SrvFmradioErrorCb pfnError);

/** SrvFmradioGetAreaConfig
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
FmradioSrvAreaConfig_t* SrvFmradioGetAreaConfig(void);

/** SrvFmradioGetStatus
* @brief     Request to get the changed status (idle, playing, recording).
*
* @retval    FMRADIOSRV_STATUS__IDLE       The idle state.
* @retval    FMRADIOSRV_STATUS__PLAY       The FM radio playing state.
* @retval    FMRADIOSRV_STATUS__RECORD     The recording state.
* @retval    FMRADIOSRV_STATUS__INVALID    If there's no enough memory to do allocation for service instance or the service data is NULL.
*/
FmradioSrvStatus_e SrvFmradioGetStatus(void);

/** SrvFmradioGetFrequency
* @brief     Request to get the FM radio frequency (the unit is 0.01MHz).
* @retval    0      If there's no enough memory to do allocation for service instance or the service data is NULL.
* @retval    n>0    The current FM radio frequency (the unit is 0.01MHz).
*/
u32 SrvFmradioGetFrequency(void);

/**  SrvFmradioPlay
* @brief        Request to turn FM radio on.

* @param[in]    pfnFmradioSrvCb          The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for turning FM radio on.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to turn FM radio on.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL.
* @retval       MAE_RET_FAILED           If it fails to get the speaker setting.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvFmradioPlay(void);

/** SrvFmradioStop
* @brief        Request to turn FM radio off.

* @param[in]    pfnFmradioSrvCb          The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for turning FM radio off.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to turn FM radio off.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvFmradioStop(void);

/** SrvFmradioSetFrequency
* @brief        Request to set FM radio frequency (the unit is 0.01MHz). After succeeding to set the frequency, the FM radio will play according to the newly set frequency.
*
* @param[in]    nFrequency               The FM radio frequency (the unit is 0.01MHz).
*                                        The range should be among MMI_FMRADIOSRV_FREQ_MIN and MMI_FMRADIOSRV_FREQ_MAX.
* @param[in]    pfnFmradioSrvCb          The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for setting FM radio frequency.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to set FM radio frequency.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the input frequency is out of range.
* @retval       MAE_RET_FAILED           If the FM radio is interrupted.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvFmradioSetFrequency(u32 nFrequency);

/** SrvFmradioSetVolume
* @brief        Request to set FM radio volume.
*
* @param[in]    nVolume                  The FM Radio volume.
*                                        FMRADIOSRV_VOLUME_LEVEL__LEVEL0/FMRADIOSRV_VOLUME_LEVEL__LEVEL1/FMRADIOSRV_VOLUME_LEVEL__LEVEL2/FMRADIOSRV_VOLUME_LEVEL__LEVEL3/
*                                        FMRADIOSRV_VOLUME_LEVEL__LEVEL4/FMRADIOSRV_VOLUME_LEVEL__LEVEL5/FMRADIOSRV_VOLUME_LEVEL__LEVEL6/FMRADIOSRV_VOLUME_LEVEL__LEVEL7/
*                                        FMRADIOSRV_VOLUME_LEVEL__LEVEL8
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to set FM radio volume.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the input volume is out of range.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvFmradioSetVolume(u8 nVolume);

/** SrvFmradioSearchChannel
* @brief        Request to search the next FM radio channel. The next channel will be found by up (+frequency) or down (-frequency) direction.
*
* @param[in]    eDirection               The searching direction for searching the next FM radio channel.
*                                        FMRADIOSRV_SEARCH_CHAN_DIRECTION__DOWN    The down (-frequency) direction.
*                                        FMRADIOSRV_SEARCH_CHAN_DIRECTION__UP      The up (+frequency) direction.
* @param[in]    pfnFmradioSrvCb          The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for search the next FM radio channel.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to search the next FM radio channel.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the input direction is invalid.
* @retval       MAE_RET_FAILED           If the FM radio is interrupted.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvFmradioSearchChannel(FmradioSrvSearchChannelDirection_e eDirection);

/**
    SrvFmradioAsycSearchChannel
@brief  The interface is used to Search available FM radio channel and can be canceled when start search.

@param[in]  eDirection              FM Radio UP/Down search.
@param[in]  pfnFmradioSrvCb         FM radio call back function pointer.
*/
MAE_Ret SrvFmradioAsycSearchChannel(FmradioSrvSearchChannelDirection_e eDirection);

/**
    SrvFmradioCancelSearch
@brief  The interface is used to Cancel search available FM radio channel.

@param[in]  pfnFmradioSrvCb         FM radio call back function pointer
*/
MAE_Ret SrvFmradioCancelSearch(void);

/** SrvFmradioGetVolume
* @brief        Request to get FM radio volume.
*
* @retval       FMRADIOSRV_VOLUME_LEVEL__INVALID    If there's no enough memory to do allocation for service instance or the service data is NULL.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL0     The level 0 volume.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL1     The level 1 volume.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL2     The level 2 volume.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL3     The level 3 volume.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL4     The level 4 volume.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL5     The level 5 volume.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL6     The level 6 volume.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL7     The level 7 volume.
* @retval       FMRADIOSRV_VOLUME_LEVEL__LEVEL8     The level 8 volume.
*/
FmradioSrvVolumeLevel_e SrvFmradioGetVolume(void);

/** SrvFmradioGetChannelInfo
* @brief        Request to get the information of the current FM radio channel, included of the frequency, signal level and audio mode.
*
* @param[in]    pfnFmradioSrvCb          The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for getting the information of the current FM radio channel.
*                                        If the registered callback function is NULL, this API is meaningless.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to get the information of the current FM radio channel.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL or the registered callback function is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
*/
MAE_Ret SrvFmradioGetChannelInfo(void);

/** SrvFmradioSetArea
* @brief        Request to set FM radio area. The registered callback function will inform whether the setting is successful or not.
*
* @param[in]    eArea                    FM Radio area.
*                                        MEDIASRV_AREA__TAIWAN      To support Taiwan region.
*                                        MEDIASRV_AREA__CHINA       To support China region.
*                                        MEDIASRV_AREA__THAILAND    To support Tailand region.
* @param[in]    pfnEmradioSrvCb          The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for area setting.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the setting request.
* @retval       MAE_RET_BAD_PARAM        If the input area is out of range or the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/
MAE_Ret SrvFmradioSetArea(MediaSrvArea_e eArea);

/** SrvFmradioSetAreaConfig
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
* @param[in]    pfnEmradioSrvCb          The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for area related parameters setting.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the setting request.
* @retval       MAE_RET_BAD_PARAM        If the input area parameter data is NULL or the set data are invalid. Also, if the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/
MAE_Ret SrvFmradioSetAreaConfig(FmradioSrvAreaConfig_t *pAreaConfig);

/** SrvFmradioSetCarrierThreshold
* @brief        Request to set the FM carrier lock/unlock thresholds for channel scanning.
*
* @param[in]    carrierOn                FM radio carrier lock threshold (default: 0x20). carrierOn must be less than carrierOff.
*                                        If setting the value lower, FM module will lock the channel with higher strength.
* @param[in]    carrierOff               FM radio carrier unlock threshold (default: 0x40). carrierOff must be larger than carrierOn.
*                                        If setting the value higher, FM module will unlock the channel with lower quality.
* @param[in]    pfnEmradioSrvCb          The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for carrier threshold setting.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the setting request.
* @retval       MAE_RET_BAD_PARAM        If carrierOn >= carrierOff or the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/
MAE_Ret SrvFmradioSetCarrierThreshold(u8 carrierOn, u8 carrierOff);

/** SrvFmradioStartRec
* @brief        Request to start FM streaming recording.
*
* @param[in]    eCodecType               The recording codec (file format).
*                                        MEDIASRV_AUD_CODEC__AMR_NB    Adaptive Multi-Rate Narrowband
*                                        MEDIASRV_AUD_CODEC__AMR_WB    Adaptive Multi-Rate Wideband
*                                        MEDIASRV_AUD_CODEC__AAC       Advanced Audio Coding
*                                        MEDIASRV_AUD_CODEC__MP3       MPEG-1 or MPEG-2 Audio Layer 3
*                                        MEDIASRV_AUD_CODEC__WAV       Waveform Audio Format
* @param[in]    eRecPath                 The type of recording path. If it would like to append the recorded stream to a file, set this value as MEDIASRV_REC_PATH__ABSOLUTE.
*                                        MEDIASRV_REC_PATH__DIR         The target URL is a directory name.
*                                        MEDIASRV_REC_PATH__ABSOLUTE    The target URL is a file name.
* @param[in]    pUrl                  	 The URL of the appended file or stored directory.
*                                        If eRecPath is MEDIASRV_REC_PATH__DIR, the URL might be L"fs:/PHON/Music/Voicememo/"
*                                        If eRecPath is MEDIASRV_REC_PATH__ABSOLUTE, the URL might be L"fs:/PHON/Music/Voicememo/AUD_001.AMR"
* @param[in]    pfnCb                    The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for starting to record.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the input parameters for starting to record.
* @retval       MAE_RET_BAD_PARAM        If the input parameters are invalid or the service data is NULL.
* @retval       MAE_RET_FAILED           If it can't succeed to check free space or can't create directory.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
* @retval       MAE_RET_FS_FULL          If the target volume is full.
*/

MAE_Ret SrvFmradioSetRecordFormat(MediaSrvAudCodec_e eType);
MAE_Ret SrvFmradioSetRecordPath(MediaSrvRecPath_e ePathType, const MAE_WChar *pPathUrl);
MAE_WChar * SrvFmradioGetRecordFile(void);

MAE_Ret SrvFmradioStartRec(void);

/** SrvAudioRecStopRecord
* @brief        Request to stop recording.
*
* @param[in]    pfnCb                    The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for stopping recording.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to stop recording.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/
MAE_Ret SrvFmradioStopRec(void);

/** SrvFmradioPauseRec
* @brief        Request to pause recording.
*
* @param[in]    pfnCb                    The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for pausing recording.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to pause recording.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
*/
MAE_Ret SrvFmradioPauseRec(void);

/** SrvFmradioResumeRec
* @brief        Request to resume recording from the paused recording.
*
* @param[in]    pfnCb                    The callback function which will be called to notify the success(MEDIASRV_ERR__OK) or failure for resuming recording.
*
* @retval       MAE_RET_SUCCESS          If it succeeds to request to pause recording.
* @retval       MAE_RET_BAD_PARAM        If the service data is NULL.
* @retval       MAE_RET_FAILED           If there doesn't exist any paused recoding information. Also, if it can't succeed to check free space or can't create directory.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
* @retval       MAE_RET_FS_FULL          If the target volume is full.
*/
MAE_Ret SrvFmradioResumeRec(void);

/** SrvFmradioSetAudioPath
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
MAE_Ret SrvFmradioSetAudioPath(FmradioSrvPrefAudPath_e eAudPath);
MAE_Ret SrvFmradioQueryBuiltInAntennaSupport(bool *pAntennaSupported);

/** SrvFmradioSetResMgrNotifyCb
@brief  The interface is use to register a listener for ResMgr interrupt

@param[in]		pfnSrvFmradioCb				interrupt notify call back function pointer.
@retval			MAE_RET_SUCCESS             If successful.
@retval			MAE_RET_FAILED				It is failed.
 */
MAE_Ret SrvFmradioSetResMgrNotifyCb(FmradioSrvResMgrNotifyCb pfnSrvFmradioCb);
MAE_Ret SrvFmradioSetPlugOutHeadsetHookFunc(u32 nCusData, FmradioSrvHookFunc pfnHook);
MAE_Ret SrvFmradioSetPlugInHeadsetHookFunc(u32 nCusData, FmradioSrvHookFunc pfnHook);

#endif //__MMI_SRV_FMRADIO_H__
/*-----------------------------------------------------*/
