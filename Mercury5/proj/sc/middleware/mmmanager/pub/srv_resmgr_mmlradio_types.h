// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    srv_resmgr_mmlradio_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLRADIO_TYPES_H__
#define __SRV_RESMGR_MMLRADIO_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerRadio
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseRadioId_e_)
{
    /* Radio Init */
    MML_UCID_RADIO_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_RADIO),
    MML_UCID_RADIO_REG_NOTIFY_CALLBACK = MML_UCID_RADIO_INIT_BASE,            ///< 00090000 = Reg notify callback
    MML_UCID_RADIO_UNREG_NOTIFY_CALLBACK,                                     ///< 00090001 = Unreg notify callback
    MML_UCID_RADIO_INIT_CATEGORY,

    /* Radio Get */
    MML_UCID_RADIO_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_RADIO),
    MML_UCID_RADIO_GET_RADIO_CONFIGURATION = MML_UCID_RADIO_GET_BASE,         ///< 00090100 = Get radio configuration
    MML_UCID_RADIO_GET_CURRENT_FREQUENCY,                                     ///< 00090101 = Get current frequency
    MML_UCID_RADIO_GET_SIGNAL_STRENGTH,                                       ///< 00090102 = Get signal strength
    MML_UCID_RADIO_GET_CHANNEL_INFO,                                          ///< 00090103 = Get channel info
    MML_UCID_RADIO_GET_RADIO_CAPABILITY,                                      ///< 00090104 = Get radio capability
    MML_UCID_RADIO_GET_CATEGORY,

    /* Radio Set */
    MML_UCID_RADIO_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_RADIO),
    MML_UCID_RADIO_SET_RADIO_CONFIGURATION = MML_UCID_RADIO_SET_BASE,         ///< 00090200 = Set radio configuration
    MML_UCID_RADIO_SET_FREQUENCY,                                             ///< 00090201 = Set frequency
    MML_UCID_RADIO_SET_MUTE,                                                  ///< 00090202 = Set mute
    MML_UCID_RADIO_SET_CATEGORY,

    /* Radio Execute */
    MML_UCID_RADIO_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_RADIO),
    MML_UCID_RADIO_START_PLAYBACK = MML_UCID_RADIO_EXECUTE_BASE,              ///< 00090300 = Start playback
    MML_UCID_RADIO_STOP_PLAYBACK,                                             ///< 00090301 = Start playback
    MML_UCID_RADIO_SEEK,                                                      ///< 00090302 = Start playback
    MML_UCID_RADIO_CANCEL_SEEK,                                               ///< 00090303 = Start playback
    MML_UCID_RADIO_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_RADIO_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerRadio
    @brief      Response results
*/
typedef enum
{
    /* Common */
    RADIO_ERROR_SUCCESS = 0,
    RADIO_ERROR_FAIL,
    RADIO_ERROR_PARAMETER_INVALID,
    RADIO_ERROR_STATE_CHANGE,
    RADIO_ERROR_ACCEPT,
    RADIO_ERROR_IGNORE,
    RADIO_ERROR_REJECT,
    RADIO_ERROR_MEMORY_FAILURE,
    /* */
    RADIO_ERROR_NUM
} MmlRadioResult_e;

/** @ingroup    MMLayerRadio
    @brief      States
*/
typedef enum
{
    RADIO_STATE_STOPPED = 0,
    RADIO_STATE_PLAYING,
    RADIO_STATE_MUTED,
    RADIO_STATE_SEEKING,
    RADIO_STATE_STOP_TRAN,
    RADIO_STATE_PLAY_TRAN,
    RADIO_STATE_SEEK_TRAN,
    RADIO_STATE_MUTE_TRAN,
    RADIO_STATE_SEEKCANCEL_TRAN,

    /* */
    RADIO_STATE_DONTCARE,
    RADIO_STATE_NUM
} MmlRadioState_e;

/** @ingroup    MMLayerRadio
    @brief      Events
*/
typedef enum
{
    /* Common */
    RADIO_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_RADIO),
    RADIO_EVENT_RUNTIME_ERROR,
    RADIO_EVENT_SEEK_COMPLETE,
    RADIO_EVENT_SEEK_CANCELED,
    /* */
    RADIO_EVENT_DONTCARE,
    RADIO_EVENT_ALL,
    RADIO_EVENT_NUM
} MmlRadioEvent_e;

/** @ingroup    MMLayerRadio
    @brief      Stereo modes
*/
typedef enum
{
    RADIO_STEREOMODE_MONO = 0,    ///< Force monaural mode
    RADIO_STEREOMODE_STEREO,      ///< Force stereo mode
    RADIO_STEREOMODE_AUTO,        ///< Automatic stereo mode
    RADIO_STEREOMODE_NUM,
} MmlRadioStereoMode_e;

/** @ingroup    MMLayerRadio
    @brief      Frequency areas
*/
typedef enum
{
    RADIO_FREQUENCYAREA_FMAMERICA = 0,    ///< American FM frequency range
    RADIO_FREQUENCYAREA_FMJAPAN,          ///< Japanese FM frequency range
    RADIO_FREQUENCYAREA_FMTAIWAN,         ///< Taiwanese FM frequency range
    RADIO_FREQUENCYAREA_FMCHINA,          ///< Chinese FM frequency range
    RADIO_FREQUENCYAREA_NUM,
} MmlRadioFrequencyArea_e;

/** @ingroup    MMLayerRadio
    @brief      Maximum frequency of range band (MHz)
*/
typedef enum
{
    RADIO_RANGEBAND_MAXFREQUENCY_68 = 0,    ///< 68 MHz
    RADIO_RANGEBAND_MAXFREQUENCY_73,        ///< 73 MHz
    RADIO_RANGEBAND_MAXFREQUENCY_74,        ///< 74 MHz
    RADIO_RANGEBAND_MAXFREQUENCY_87_5,      ///< 87.5 MHz
    RADIO_RANGEBAND_MAXFREQUENCY_90,        ///< 90 MHz
    RADIO_RANGEBAND_MAXFREQUENCY_100,       ///< 100 MHz
    RADIO_RANGEBAND_MAXFREQUENCY_108,       ///< 108 MHz
} MmlRadioRangeBandMaxFrequency_e;

/** @ingroup    MMLayerRadio
    @brief      Minimum frequency of range band (MHz)
*/
typedef enum
{
    RADIO_RANGEBAND_MINFREQUENCY_66 = 0,    ///< 66 MHz
    RADIO_RANGEBAND_MINFREQUENCY_68,        ///< 68 MHz
    RADIO_RANGEBAND_MINFREQUENCY_73,        ///< 73 MHz
    RADIO_RANGEBAND_MINFREQUENCY_76,        ///< 76 MHz
    RADIO_RANGEBAND_MINFREQUENCY_87_5,      ///< 87.5 MHz
    RADIO_RANGEBAND_MINFREQUENCY_87_8,      ///< 87.8 MHz
    RADIO_RANGEBAND_MINFREQUENCY_88,        ///< 88 MHz
    RADIO_RANGEBAND_MINFREQUENCY_100,       ///< 100 MHz
} MmlRadioRangeBandMinFrequency_e;

/** @ingroup    MMLayerRadio
    @brief      BPFIR frequency (KHz)
*/
typedef enum
{
    RADIO_BPFIRFREQUENCY_100 = 0,    ///< 100 KHz
    RADIO_BPFIRFREQUENCY_120,        ///< 120 KHz
    RADIO_BPFIRFREQUENCY_150,        ///< 150 KHz
    RADIO_BPFIRFREQUENCY_200,        ///< 200 KHz
} MmlRadioBpfirFrequency_e;

/** @ingroup    MMLayerRadio
    @brief      Step space (KHz)
*/
typedef enum
{
    RADIO_STEPSPACE_50 = 0,    ///< 50 KHz
    RADIO_STEPSPACE_100,       ///< 100 KHz
    RADIO_STEPSPACE_200,       ///< 200 KHz
    RADIO_STEPSPACE_30,        ///< 30 KHz
    RADIO_STEPSPACE_300,       ///< 300 KHz
} MmlRadioStepSpace_e;

/** @ingroup    MMLayerRadio
    @brief      De emphasis (US)
*/
typedef enum
{
    RADIO_DEEMPHASIS_50 = 0,    ///< 50
    RADIO_DEEMPHASIS_75,        ///< 75
} MmlRadioDeEmphasis_e;

/** @ingroup    MMLayerRadio
    @brief      Configuration types
*/
typedef enum
{
    RADIO_CONFIGURATIONTYPE_FREQUENCYAREA = 0,    ///< Frequency area
    RADIO_CONFIGURATIONTYPE_STEREOMODE,           ///< Stereo mode
    RADIO_CONFIGURATIONTYPE_FREQUENCYRANGE,       ///< Frequency range
    RADIO_CONFIGURATIONTYPE_CARRYLOCKTHRESHOLD,   ///< Carry lock threshold
} MmlRadioConfigurationType_e;

/** @ingroup    MMLayerRadio
    @brief      Frequency range
*/
typedef struct
{
    MmlRadioRangeBandMaxFrequency_e     eMaxFrequency;
    MmlRadioRangeBandMinFrequency_e     eMinFrequency;
    MmlRadioBpfirFrequency_e            eBpfirFrequency;
    MmlRadioStepSpace_e                 eStepSpace;
    MmlRadioDeEmphasis_e                eDeEmphasis;
} MmlRadioFrequencyRange_t;

/** @ingroup    MMLayerRadio
    @brief      Carry lock threshold
*/
typedef struct
{
    u8    nCarryLockOnThreshold;    ///< Carrier off NSR threshold (default is 0x40)
    u8    nCarryLockOffThreshold;   ///< Carrier on NSR threshold (default is 0x20)
} MmlRadioCarryLockThreshold_t;

/** @ingroup    MMLayerRadio
    @brief      Channel info
*/
typedef struct
{
    u32                     nFrequency;     ///< Current frequency in 1/1000 MHz
    MmlRadioStereoMode_e    eStereoMode;    ///< Stereo mode
    u16                     nRssi;          ///< 16-bit RSSI value in units of -dBm
} MmlRadioChannelInfo_t;

/** @ingroup    MMLayerRadio
    @brief      State change info
*/
typedef	struct
{
    MmlRadioState_e               eState;          ///< The new state after the transition
    MmlRadioEvent_e	              eCause;          ///< The cause of state change, if any

    /// union of MmlRadioStateChange_t parameters
    union
    {
   	     MmlRadioChannelInfo_t    tChannelInfo;    ///< The found channel info
    } uParam;
} MmlRadioStateChange_t;

/** @ingroup    MMLayerRadio
    @brief      Notification payload
*/
typedef struct
{
    MmlRadioEvent_e	            eEvent;        ///< Specify the event you want to notify
    u32                         nHandle;       ///< 32-bit playback handle

    /// union of MmlRadioNotify_t parameters
    union
    {
        MmlRadioStateChange_t    tStateChange;    ///< Used with RADIO_EVENT_STATE_CHANGE event
        MmlRadioResult_e         eErrCode;        ///< Used with RADIO_EVENT_RUNTIME_ERROR event
        MmlRadioChannelInfo_t    tChannelInfo;    ///< Used with RADIO_EVENT_SEEK_COMPLETE event
	} uParam;
} MmlRadioNotify_t;

/** @ingroup    MMLayerRadio
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      pRadioNotify      Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlRadioNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlRadioNotify_t *pRadioNotify);

/** @ingroup    MMLayerRadio
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                             nSenderID;           ///< Sender's mailbox ID
    u32                             nUserValue;          ///< Interface self-reference
    PfnMmlRadioNotifyCallback       pfnNotifyCallback;   ///< Callback function your want to register
} MmlRadioNotifyCallback_t;

/** @ingroup    MMLayerRadio
    @brief      Response callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      eErrCode          Returned result (error code)
    @param      pRadioResponse    Pointer to the returned response payload
*/
struct MmlRadioResponse_t_;
typedef void (*PfnMmlRadioResponseCallback)(u16 nSenderID, u32 nUserValue, MmlRadioResult_e eErrCode, struct MmlRadioResponse_t_ *pRadioResponse);

/** @ingroup    MMLayerRadio
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlRadioResponseCallback     pfnResponseCallback;    ///< Callback function your want to register
} MmlRadioResponseCallback_t;

/** @ingroup    MMLayerRadio
    @brief      Register notification callback
*/
typedef struct
{
    MmlRadioEvent_e                 eEvent;             ///< Specify which event you want to handle
    MmlRadioNotifyCallback_t        tNotifyCallback;    ///< Registration data specifying the callback function' address
} MmlRadioRegNotifyCallback_t;

/** @ingroup    MMLayerRadio
    @brief      Radio configuration
*/
typedef struct
{
    MmlRadioFrequencyArea_e         eFrequencyArea;         ///< Specify the frequency area
    MmlRadioStereoMode_e            eStereoMode;            ///< Specify the stereo mode
    MmlRadioFrequencyRange_t        tFrequencyRange;        ///< Specify the frequency range
    MmlRadioCarryLockThreshold_t    tCarryLockThreshold;    ///< Specify the carry lock threshold
} MmlRadioRadioConfiguration_t;

/** @ingroup    MMLayerRadio
    @brief      Set radio configuration
*/
typedef struct
{
    MmlRadioConfigurationType_e    eConfigurationType;    ///< Specify which type of setting to be configured

    /// union of MmlRadioSetRadioConfiguration_t parameters
    union
    {
        MmlRadioFrequencyArea_e         eFrequencyArea;         ///< Specify the frequency area
        MmlRadioStereoMode_e            eStereoMode;            ///< Specify the stereo mode
        MmlRadioFrequencyRange_t        tFrequencyRange;        ///< Specify the frequency range
        MmlRadioCarryLockThreshold_t    tCarryLockThreshold;    ///< Specify the carry lock threshold
    } uParam;
} MmlRadioSetRadioConfiguration_t;

/** @ingroup    MMLayerRadio
    @brief      Set frequency\n
                1. The new frequency of the tuner is to round the given value to the nearest supported one.
*/
typedef struct
{
    u32    nHandle;        ///< 32-bit playback handle, used to indicate which playback to be set
    u32    nFrequency;     ///< 32-bit frequency in 1/1000 MHz
} MmlRadioSetFrequency_t;

/** @ingroup    MMLayerRadio
    @brief      Set mute
*/
typedef struct
{
    u32    nHandle;        ///< 32-bit playback handle, used to indicate which playback to be set
    u16    bMuteEnable;    ///< If TRUE, the radio is muted. If FALSE, the radio is unmuted
} MmlRadioSetMute_t;

/** @ingroup    MMLayerRadio
    @brief      Seek\n
                1. The found vaild frequency is returned from "seek completed" notification, indicating
                   that the seek is completed and the frequency of the tuner is the one that is given as
                   event parameter, or if nothing was found, the starting frequency.
*/
typedef struct
{
    u32    nHandle;        ///< 32-bit playback handle, used to indicate which playback to seek
    u16    bUpward;        ///< If TRUE, the seek progresses towards higher frequencies. If FALSE,
                           ///< the seek progresses towards lower frequencies.
} MmlRadioSeek_t;

#define MML_RADIO_ENCODER_BITMASK_AMR_NB               ((u32) 0x00000001)
#define MML_RADIO_ENCODER_BITMASK_AMR_WB               ((u32) 0x00000002)
#define MML_RADIO_ENCODER_BITMASK_WAV_IMAADPCM_4BIT    ((u32) 0x00000004)
#define MML_RADIO_ENCODER_BITMASK_WAV_IMAADPCM_3BIT    ((u32) 0x00000008)
#define MML_RADIO_ENCODER_BITMASK_WAV_MSADPCM4BIT      ((u32) 0x00000010)
#define MML_RADIO_ENCODER_BITMASK_MP3_LAYERII          ((u32) 0x00000020)
#define MML_RADIO_ENCODER_BITMASK_PCM                  ((u32) 0x00000040)
#define MML_RADIO_CHANNELMODE_BITMASK_MONO             ((u32) 0x00000001)
#define MML_RADIO_CHANNELMODE_BITMASK_STEREO           ((u32) 0x00000002)

/** @ingroup    MMLayerRadio
    @brief      Radio capability
*/
typedef struct
{
    u32     nEncoderSupported;    ///< Encoders supported
    u32     nMaxSamplingRate;     ///< Maximum sampling rate supported (Hz)
    u32     nMinSamplingRate;     ///< Minimum sampling rate supported (Hz)
    u32     nMaxBitRate;          ///< Maximum bitrate supported (bps)
    u32     nMinBitRate;          ///< Minimum bitrate supported (bps)
    u32     nChannelMode;         ///< Channel modes supported
    u16     bAntennaSupported;    ///< Antenna supported
    u16     bRecordingSupported;  ///< Encoding supported
} MmlRadioCapability_t;

/** @ingroup    MMLayerRadio
    @brief      Get radio capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;             ///< Used for backward compatible (Current version = 0x0000, 2010/08/26)
} MmlImageGetRadioCapability_t;

/** @ingroup    MMLayerRadio
    @brief      Response payload
*/
typedef struct MmlRadioResponse_t_
{
    MmlRadioState_e                     eState;            ///< Current state
    u32                                 nHandle;           ///< 32-bit playback handle

    /// union of MmlRadioResponse_t parameters
	union
	{
        u32                             nFrequency;        ///< Used with 'Get current frequency, Set frequency'
        u16                             nRssi;             ///< 16-bit RSSI value in units of -dBm, used with 'Get signal strength'
        MmlRadioStateChange_t           tStateChange;      ///< Used with 'RADIO_ERROR_STATE_CHANGE' result
        MmlRadioRadioConfiguration_t    tConfiguration;    ///< Used with 'Get radio configuration'
        MmlRadioChannelInfo_t           tChannelInfo;      ///< Used with 'Get channel info'
        MmlRadioCapability_t            tCapability;       ///< Used with 'Get radio capability'
    } uParam;
} MmlRadioResponse_t;

/** @ingroup    MMLayerRadio
    @brief      Radio use case parameters\n
                1. Cancel seek is to cancel an outstanding seek request. After cancellation,
                   the frequency is the one where seeking stopped.
*/
typedef struct
{
	u32                                 nUseCaseID;             ///< Use case ID
	MmlRadioResponseCallback_t          *pResponseCallback;     ///< Pointer to the response callback registration data
	MmlRadioResponse_t                  *pResponse;             ///< Pointer to the response payload

    /// union of MmlRadioUCParam_t parameters
	union
	{
	    /* No parameter: 'Get radio configuration, Start playback' */

        u32                                nHandle;                   ///< Used with 'Get current frequency, Get signal strength, Stop playback,
                                                                      ///< Cancel seek, Get channel info'
	    MmlRadioRegNotifyCallback_t        tRegNotifyCallback;        ///< Used with 'Register notification callback'
	    MmlRadioSetRadioConfiguration_t    tSetRadioConfiguration;    ///< Used with 'Set radio configuration'
	    MmlRadioSetFrequency_t             tSetFrequency;             ///< Used with 'Set frequency'
	    MmlRadioSetMute_t                  tSetMute;                  ///< Used with 'Set mute'
	    MmlRadioSeek_t                     tSeek;                     ///< Used with 'Seek'
	    MmlImageGetRadioCapability_t       tGetRadioCapability;       ///< Used with 'Get radio capability'

	} uParam;
} MmlRadioUCParam_t;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLRADIO_TYPES_H__
