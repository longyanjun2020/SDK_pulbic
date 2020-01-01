/**
* @file MediaCtrlItf.h
*
* This header file defines the interface of media related
* control request
*/

#ifndef __MEDIACTRLITF_H__
#define __MEDIACTRLITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
#define MEDIA_CONFIG__AUD_SRS_PARAM_LEVEL_DEFAULT   (0)
#define MEDIA_CONFIG__AUD_SRS_PARAM_LEVEL_MAX       (10)

typedef enum MediaProfileType_e_
{
    MEDIA_PROFILE_TYPE__NORMAL,
    MEDIA_PROFILE_TYPE__MEETING,
    MEDIA_PROFILE_TYPE__OUTDOOR,
    MEDIA_PROFILE_TYPE__SILENT,
    MEDIA_PROFILE_TYPE__USER_DEFINE,
    MEDIA_PROFILE_TYPE__HEADSET,
    MEDIA_PROFILE_TYPE__BLUETOOTH,
    MEDIA_PROFILE_TYPE__POWER_SAVING,
    MEDIA_PROFILE_TYPE__NUM,
    MEDIA_PROFILE_TYPE__INVALID = 0xFF,
} MediaProfileType_e;

typedef enum MediaAudChannel_e_
{                                                     /*Sync. HAL_AudResCtrlItf.h */
    MEDIA_AUD_CHAN__VOICE = 0,                        //AUD_CHAN__VOICE
    MEDIA_AUD_CHAN__STEREO,                           //AUD_CHAN__STEREO
    MEDIA_AUD_CHAN__AUX,                              //AUD_CHAN__AUX
    MEDIA_AUD_CHAN__VOICE_SLAVE,                      //AUD_CHAN__VOICE_SLAVEL
    MEDIA_AUD_CHAN__NUM,                              //AUD_CHAN__NUM
    MEDIA_AUD_CHAN__ALL = MEDIA_AUD_CHAN__NUM,        //AUD_CHAN__ALL
    MEDIA_AUD_CHAN__INVALID                           //AUD_CHAN__INVALID
} MediaAudChannel_e;

typedef enum MediaVolUserId_e_
{
    MEDIA_VOL_USER_ID__PROFILE,
    MEDIA_VOL_USER_ID__GAME,
    MEDIA_VOL_USER_ID__CC,
    MEDIA_VOL_USER_ID__MPLAYER,
    MEDIA_VOL_USER_ID__VIDEOPLAYER,
    MEDIA_VOL_USER_ID__EMU_GAME,
    MEDIA_VOL_USER_ID__VOICEMEMO,
    MEDIA_VOL_USER_ID__FILEMGR,
    MEDIA_VOL_USER_ID__FMRADIO,
    MEDIA_VOL_USER_ID__ATV,
    MEDIA_VOL_USER_ID__VENDOR_1,
    MEDIA_VOL_USER_ID__VENDOR_2,
    MEDIA_VOL_USER_ID__VENDOR_3,
	MEDIA_VOL_USER_ID__OTHERAPP,
    MEDIA_VOL_USER_ID__NUM
} MediaVolUserId_e;

typedef enum MediaConfigId_e_
{
    MEDIA_CONFIG_ID__HANDSET,
    MEDIA_CONFIG_ID__HEADSET,
    MEDIA_CONFIG_ID__A2DP,
    MEDIA_CONFIG_ID__NUM
} MediaConfigId_e;

typedef enum MediaConfigUserId_e_
{
    MEDIA_CONFIG_USER_ID__COMMON,
    MEDIA_CONFIG_USER_ID__MPLAYER,
    MEDIA_CONFIG_USER_ID__NUM
} MediaConfigUserId_e;

typedef enum MediaConfig_Aud3D_e_
{
    MEDIA_CONFIG__AUD_3D_DISABLE,
    MEDIA_CONFIG__AUD_3D_NORMAL,
    MEDIA_CONFIG__AUD_3D_HIGH
} MediaConfig_Aud3D_e;

typedef enum MediaConfig_AudPitchShift_e_
{
    MEDIA_CONFIG__AUD_PITCH_SHIFT_DISABLE,
    MEDIA_CONFIG__AUD_PITCH_SHIFT_LEVEL_1,
    MEDIA_CONFIG__AUD_PITCH_SHIFT_LEVEL_2,
    MEDIA_CONFIG__AUD_PITCH_SHIFT_LEVEL_3,
    MEDIA_CONFIG__AUD_PITCH_SHIFT_LEVEL_4,
    MEDIA_CONFIG__AUD_PITCH_SHIFT_LEVEL_5,
    MEDIA_CONFIG__AUD_PITCH_SHIFT_LEVEL_6,
} MediaConfig_AudPitchShift_e;

typedef enum MediaCondifg_AudEQ_e_
{
    MEDIA_CONFIG__AUD_EQ_0,
    MEDIA_CONFIG__AUD_EQ_1,
    MEDIA_CONFIG__AUD_EQ_2,
    MEDIA_CONFIG__AUD_EQ_3,
    MEDIA_CONFIG__AUD_EQ_4,
    MEDIA_CONFIG__AUD_EQ_5,
    MEDIA_CONFIG__AUD_EQ_6,
    MEDIA_CONFIG__AUD_EQ_MAX
} MediaConfig_AudEQ_e;

typedef enum MediaCondifg_AudTS_e_
{
    MEDIA_CONFIG__AUD_TS_x1,
    MEDIA_CONFIG__AUD_TS_x2,
    MEDIA_CONFIG__AUD_TS_x15,
    MEDIA_CONFIG__AUD_TS_x075,
    MEDIA_CONFIG__AUD_TS_x05,
    MEDIA_CONFIG__AUD_TS_MAX
} MediaConfig_AudTS_e;

typedef enum MediaCondifg_AudReverb_e_
{
    MEDIA_CONFIG__AUD_Reverb_NONE,
    MEDIA_CONFIG__AUD_Reverb_CHURCH,
    MEDIA_CONFIG__AUD_Reverb_BATHROOM,
    MEDIA_CONFIG__AUD_Reverb_MEDIUMCONCERT,
    MEDIA_CONFIG__AUD_Reverb_SMALLCLUB,
    MEDIA_CONFIG__AUD_Reverb_CAVE
} MediaConfig_AudReverb_e;

typedef enum MediaCondifg_AudDolby_e_
{
    MEDIA_CONFIG__AUD_DOLBY_DISABLE,
    MEDIA_CONFIG__AUD_DOLBY_NORMAL,
    MEDIA_CONFIG__AUD_DOLBY_MAX
} MediaConfig_AudDolby_e;

typedef enum MediaConfig_AudVirtualBass_e_
{
    MEDIA_CONFIG__AUD_VIRTUAL_BASS_DISABLE,
    MEDIA_CONFIG__AUD_VIRTUAL_BASS_ENABLE,
    MEDIA_CONFIG__AUD_VIRTUAL_BASS_MAX
} MediaConfig_AudVirtualBass_e;

typedef enum MediaCondifg_AudSRS_e_
{
    MEDIA_CONFIG__AUD_SRS_DISABLE,
    MEDIA_CONFIG__AUD_SRS_ENABLE,
    MEDIA_CONFIG__AUD_SRS_MAX
} MediaConfig_AudSRS_e;

typedef enum MediaCondifg_AudDRCLimiter_e_
{
    MEDIA_CONFIG__AUD_DRC_LIMITER_0,
    MEDIA_CONFIG__AUD_DRC_LIMITER_1,
    MEDIA_CONFIG__AUD_DRC_LIMITER_2,
    MEDIA_CONFIG__AUD_DRC_LIMITER_3
} MediaCondifg_AudDRCLimiter_e;

typedef enum MediaCondifg_AudSpeakerPEQ_e_
{
    MEDIA_CONFIG__AUD_SPEAKER_PEQ_0,
    MEDIA_CONFIG__AUD_SPEAKER_PEQ_1,
    MEDIA_CONFIG__AUD_SPEAKER_PEQ_2,
    MEDIA_CONFIG__AUD_SPEAKER_PEQ_3
} MediaCondifg_AudSpeakerPEQ_e;

typedef enum MediaCondifg_AudARPDevType_e_
{
    MEDIA_CONFIG__AUD_DEVICETYPE_NONE = 0,          ///< No device is selected
    MEDIA_CONFIG__AUD_DEVICETYPE_MICROPHONE,        ///< Microphone
    MEDIA_CONFIG__AUD_DEVICETYPE_FM,                ///< FMRadio
} MediaCondifg_AudARPDevType_e;             /// should be same index value as MmlAudioDeviceType_e

typedef enum MediaConfig_MediaType_e_
{
    MEDIA_CONFIG_MEDIA__NONE,
    MEDIA_CONFIG_MEDIA__AUDIO,
    MEDIA_CONFIG_MEDIA__VIDEO,
} MediaConfig_MediaType_e;

typedef enum MediaConfig_PlatformMemType_e_
{
    PLATFORM_MEMORYTYPE_TYPE1,          ///< Type1: Nor(Page)+Psram(Page)/Nor(Burst)+Psram(Page)
    PLATFORM_MEMORYTYPE_TYPE2,          ///< Type2: Nor(Page)+Psram(Burst)/Nor(Burst)+Psram(Burst)
    PLATFORM_MEMORYTYPE_TYPE3,          ///< Type3: Nand+Sdram
    PLATFORM_MEMORYTYPE_TYPE4           ///< Type4: SPI+Psram(Burst)
}MediaConfig_PlatformMemType_e;

typedef struct MediaSrsWowhdParam_t_
{
    u8 bSrsEnable;         ///< Is SRS enabled
    u8 nTruBassLevel;      ///< Tru bass level
    u8 n3DCenterLevel;     ///< 3D center level
    u8 n3DSpaceLevel;      ///< 3D space level
    u8 nFocusLevel;        ///< Focus level
    u8 nDefinitionLevel;   ///< Definition level
} MediaSrsWowhdParam_t;

typedef struct MediaPeqConfig_t_
{
    u8 uAudEqType;
    u8 uAud3dSetting;
    u8 uAudTsSetting;
    u8 uAudReverbSetting;
    u8 uDolbyType;
    u8 uPitchShiftValue;
    MediaSrsWowhdParam_t tAudSrsWowhdParam;
    u8 uAudVirtualBassMode;
} MediaPeqConfig_t;

typedef struct MediaPreProcessConfig_t_
{
    MediaCondifg_AudARPDevType_e eDeviceType;
} MediaPreProcessConfig_t;

typedef struct MediaAPPConfigParm_t_
{
    MediaConfigId_e eConfigId;
    MediaPeqConfig_t tPeqParms;
    MediaConfig_MediaType_e eMediaType;
} MediaConfigParm_t;

typedef struct MediaARPConfigParm_t_
{
    MediaPreProcessConfig_t tARPParms;
    MediaConfig_MediaType_e eMediaType;
} MediaARPConfigParm_t;

typedef struct MediaAPPConfig_t_
{
    MediaPeqConfig_t aPeqConfig[MEDIA_CONFIG_ID__NUM];
    MediaConfig_MediaType_e eMediaType;
} MediaConfig_t;

typedef struct MediaARPConfig_t_
{
    MediaPreProcessConfig_t aConfigParms[MEDIA_CONFIG_ID__NUM];
    MediaConfig_MediaType_e eMediaType;
} MediaARPConfig_t;

typedef struct MediaSetConfigParm_t_
{
    u8 uAudEqType;
    u8 uAud3dSetting;
    u8 uAudTsSetting;
    u8 uAudReverbSetting;
    u8 uAudDolbyType;
    u8 uAudPitchShiftValue;
    MediaSrsWowhdParam_t tAudSrsWowhdParam;
    u8 uAudVirtualBassMode;
} MediaSetConfigParm_t;

typedef enum MediaPrefPath_e_
{
    MEDIA_PREF_PATH__HANDSET,
    MEDIA_PREF_PATH__HEADSET,
    MEDIA_PREF_PATH__SPEAKER,
    MEDIA_PREF_PATH__BT_HEADSET,
    /*
    Only used for EM testing
    */
    MEDIA_PREF_PATH__RIGHT_SPEAKER,
    MEDIA_PREF_PATH__LEFT_SPEAKER,
    MEDIA_PREF_PATH__NUM
} MediaPrefPath_e;

typedef struct MediaProfileVol_t_
{
    u8 aDefVol[MEDIA_PROFILE_TYPE__NUM];
    u8 aDefChannelVol[MEDIA_PROFILE_TYPE__NUM][MEDIA_AUD_CHAN__NUM];
    u8 aDefVolRange[MEDIA_PROFILE_TYPE__NUM];
    s8 aDefChannelBalance[MEDIA_PROFILE_TYPE__NUM][MEDIA_AUD_CHAN__NUM];
} MediaProfileVol_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__MEDIACTRLITF_H__

