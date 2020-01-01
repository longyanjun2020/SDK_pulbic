
#ifndef __MDL_AUD_INT_TYPES_H__
#define __MDL_AUD_INT_TYPES_H__

#include "mdl_aud_forward.h"
#include "mdl_aud_pub_types.h"
#include "mdl_aud_pub_api.h"

/**
 * @brief The structure defines Audio DTMF tone setting
 */
typedef struct
{
  MdlAudDTMF_e   eToneId;        /**< DTMF tone id */
  u8             nVolRange;      /**< DTMF tone volume range */
  u8             nVolLevel;      /**< DTMF tone volume level */
} MdlAudDtmfParam_t;

/**
 *  @brief The structure defines the music playing mode
 */
typedef struct {
  MdlAudMusicMode_e  eMode;
} MdlAudSetMusicModeParam_t;

typedef struct{
    MdlAudDistortedVoice_e eMode;
}MdlAudSetDistortedVoiceParam_t;

/**
 *  @brief The structure defines the switch speaker command
 */
typedef struct {
  MdlAudChannel_e    eChannel;
  bool               bOn;
  u32                nDelay;
  u32                nExtInfo;
} MdlAudSwitchSpeakerAmp_t;

/**
 *  @brief The structure defines the open command
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    MdlAudType_e       eAudioType;
} MdlAudOpen_t;


/**
 *  @brief The structure defines the close command
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    MdlAudType_e       eAudioType;
} MdlAudClose_t;


/**
 *  @brief The structure defines the set in gain command
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    MdlAudGain_t       tInputGain;
} MdlAudSetInGain_t;


/**
 *  @brief The structure defines the set input command
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    MdlAudInput_e      eInput;
} MdlAudSetInput_t;


/**
 *  @brief The structure defines the get output command
 */
typedef struct
{
    MdlAudChannel_e     eChannel;
    MdlAudOutput_e     *peOutput;
} MdlAudGetOutput_t;


/**
 *  @brief The structure defines the set output command
 */
typedef struct
{
    MdlAudChannel_e     eChannel;
    MdlAudOutput_e      eOutput;
} MdlAudSetOutput_t;


/**
 *  @brief The structure defines the get output gain command
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    MdlAudType_e       eAudioType;
    MdlAudGain_t      *ptOutputGain;
} MdlAudGetOutputGain_t;


/**
 *  @brief The structure defines the set frequency command
 */
typedef struct
{
    MdlAudChannel_e       eChannel;
    MdlAudSamplingRate_e  eSamplingRate;
} MdlAudSetFrequency_t;


/**
 *  @brief The structure defines the set record frequency command
 */
typedef struct {
  MdlAudSamplingRate_e    eSamplingRate;
} MdlAudSetRecFrequency_t;


/**
 *  @brief The structure defines the switch TCH status command
 */
typedef struct {
  bool                    bEnable;
}MdlAudSwitchTchStatus_t;

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct
{
    MdlAudNotifyType_e eNotifyType;  /**< Notification type */
    MdlAudNotifyCb_t   tNotifyCb;    /**< Notification callback */
} MdlAudRegNotify_t;

/**
 *  @brief The sturcture defines the audio set mute parameter
 */
typedef struct
{
    bool            bMute;  /**< Mute */
} MdlAudSetMute_t;

/**
 *  @brief The sturcture defines the audio set path parameter
 */
typedef struct {
    MdlAudChannel_e eChanId;   /**< Channel id */
    MdlAudPath_e    eAudPath;  /**< Audio path */
} MdlAudSetPath_t;

/**
 *  @brief The sturcture defines the audio set volume parameter
 */
typedef struct {
    MdlAudChannel_e eChanId;   /**< Channel id */
    u8              nRange;    /**< Volume range */
    u8              nVolume;   /**< Volume level */
} MdlAudSetVol_t;

/**
 *  @brief The sturcture defines the audio set balance parameter
 */
typedef struct
{
    MdlAudChannel_e eChanId;   /**< Channel id */
    s8              nRange;    /**< Balance range */
    s8              nLevel;    /**< Balance level */
} MdlAudSetBalance_t;

/**
 *  @brief The sturcture defines the audio enable local tone parameter
 */
typedef struct
{
    bool            bEnable;  /**< Enable */
} MdlAudEnableLocalTone_t;

/**
 *  @brief The sturcture defines the audio enable speech parameter
 */
typedef struct
{
    bool            bEnable;  /**< Enable */
} MdlAudEnableSpeech_t;

/**
 *  @brief The structure defines the PCM recording parameter
 */
typedef struct {
  MdlAudPcmRecordCb  *pfnCb;
  u32                 nUserData;
} MdlAudRegPcmRecordCb_t;


/**
 *  @brief The structure defines the set frequency command
 */
typedef struct
{
    MdlAudConfig_t *ptAudConfig;
    MdlAudType_e   *peAudState;
} MdlAudGetInfo_t;


/**
 *  @brief The structure defines the speaker enable command
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    bool               bEnable;
} MdlAudSpeakerEnable_t;


/**
 *  @brief The structure defines the gain fade out command
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    MdlAudGain_t       tGain;
} MdlAudGainFadeOut_t;


/**
 *  @brief The structure defines the gain fade in command
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    MdlAudGain_t       tGain;
} MdlAudGainFadeIn_t;

/**
 *  @brief The structure defines the get output path
 */
typedef struct
{
    MdlAudChannel_e    eChannel;
    MdlAudPath_e      *pePath;
} MdlAudGetPath_t;

//Yi-Lung:
typedef struct{
	bool			bOn;
	MdlAudChannel_e eChannel; 
	MdlAudInput_e eInput; 
	MdlAudOutput_e eOutput;
	MdlAudGain_t tInputGain;
	MdlAudGain_t tOutputGain;
} MdlAudEmTest_t;

#endif //__MDL_AUD_INT_TYPES_H__


