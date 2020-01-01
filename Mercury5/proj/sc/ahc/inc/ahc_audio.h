/**
 @file ahc_audio.h
 @brief Header File for the AHC audio API.
 @author 
 @version 1.0
*/

#ifndef _AHC_AUDIO_H_
#define _AHC_AUDIO_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gpio.h"
#include "ahc_rtc.h"
#include "Config_SDK.h"
//#ifndef _MMPS_3GPRECD_H_
//#include "mmps_3gprecd_inc.h"
//#endif
#include "mmps_3gprecd.h"
#include "ahc_audio_inc.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define AUDIO_PLAYBACK_MUTE (1)

#if VR_AUDIO_TYPE == VR_AUDIO_TYPE_AAC
    #define AHC_AUDIO_OPTION AHC_AAC_AUDIO_OPTION
#elif VR_AUDIO_TYPE == VR_AUDIO_TYPE_MP3
    #define AHC_AUDIO_OPTION AHC_MP3_AUDIO_OPTION
#elif VR_AUDIO_TYPE == VR_AUDIO_TYPE_ADPCM
    #define AHC_AUDIO_OPTION AHC_ADPCM_AUDIO_OPTION
#elif VR_AUDIO_TYPE == VR_AUDIO_TYPE_PCM
    #define AHC_AUDIO_OPTION AHC_PCM_AUDIO_OPTION
#endif

#define AHC_AUDIO_STREAM_ID 0 //should be 0 or 1.
#define AHC_AUDIO_STREAM_2_ID 1 //should be 0 or 1.

/*===========================================================================
 * Enum define
 *===========================================================================*/ 
 
typedef enum _AHC_AUDIO_RECORD_CMD_TYPE {
	AHC_AUDIO_RECORD_START = 0,
	AHC_AUDIO_RECORD_PAUSE,
	AHC_AUDIO_RECORD_RESUME,
	AHC_AUDIO_RECORD_STOP
} AHC_AUDIO_RECORD_CMD_TYPE;

typedef enum _AHC_AUDIO_PLAY_CMD_LIST{
    AHC_AUDIO_PLAY_START = 0,
    AHC_AUDIO_PLAY_PAUSE,
    AHC_AUDIO_PLAY_STOP,
    AHC_AUDIO_PLAY_STOP_AUTO,
    AHC_AUDIO_PLAY_RESUME,
    AHC_AUDIO_PLAY_SEEK_BY_TIME,
    AHC_AUDIO_PLAY_FAST_FORWARD,
    AHC_AUDIO_PLAY_FAST_FORWARD_RATE,
    AHC_AUDIO_PLAY_SET_VOLUME,
    AHC_AUDIO_PLAY_2ND_START,
    AHC_AUDIO_PLAY_2ND_PAUSE,
    AHC_AUDIO_PLAY_2ND_STOP_AUTO,
    AHC_AUDIO_PLAY_2ND_RESUME,
    AHC_AUDIO_PLAY_2ND_SEEK_BY_TIME,
    AHC_AUDIO_PLAY_2ND_FAST_FORWARD,
    AHC_AUDIO_PLAY_2ND_FAST_FORWARD_RATE
} AHC_AUDIO_PLAY_CMD_LIST;

typedef enum _AHC_AUDIO_LINEIN_CHANNEL
{
    AHC_AUDIO_LINEIN_DUAL 		= 0x0,  ///< dual channel line in
    AHC_AUDIO_LINEIN_R 			= 0x1,  ///< Right channel line in
    AHC_AUDIO_LINEIN_L 			= 0x2   ///< Left channel line in
} AHC_AUDIO_LINEIN_CHANNEL;

typedef enum _AHC_AUDIO_UINT_ID {
	AHC_AUDIO_INTERNAL_CODEC = 0,
	AHC_AUDIO_EXTERNAL_CODEC,
	AHC_AUDIO_HDMI
} AHC_AUDIO_UINT_ID;

typedef enum _AHC_AUDIO_CHANNEL_CONFIG{
    AHC_AUDIO_CHANNEL_STEREO = 0,
    AHC_AUDIO_CHANNEL_MONO_R,
    AHC_AUDIO_CHANNEL_MONO_L,
    AHC_AUDIO_CHANNEL_MAX
} AHC_AUDIO_CHANNEL_CONFI;

#if 0
_EXTERNAL_CODEC_SETTING_(){}
#endif

typedef enum _AHC_AUDIO_I2S_WORK_MODE {
    AHC_AUDIO_I2S_WORK_MODE_NONE = 0,
    AHC_AUDIO_I2S_MASTER_MODE,                             ///< BCK & LRCK is outputed by AIT
    AHC_AUDIO_I2S_SLAVE_MODE,                              ///< BCK & LRCK is outputed by external codec
    AHC_AUDIO_I2S_MAX_WORK_MODE
} AHC_AUDIO_I2S_WORK_MODE;

typedef enum _AHC_AUDIO_I2S_MCLK_MODE {
    AHC_AUDIO_I2S_MCLK_MODE_NONE = 0,
    AHC_AUDIO_I2S_256FS_MODE,                              ///< 256*fs clock output
    AHC_AUDIO_I2S_USB_MODE,                                ///< fixed clock output
    AHC_AUDIO_I2S_MAX_MCLK_MODE
} AHC_AUDIO_I2S_MCLK_MODE;

typedef enum _AHC_AUDIO_I2S_OUT_BITS {
    AHC_AUDIO_I2S_OUT_BITS_NONE = 0,
    AHC_AUDIO_I2S_OUT_16BIT,                               ///< 16 bits for each channel
    AHC_AUDIO_I2S_OUT_24BIT,                               ///< 24 bits for each channel
    AHC_AUDIO_I2S_OUT_32BIT,                               ///< 32 bits for each channel
    AHC_AUDIO_I2S_MAX_OUT_BIT_MODE
} AHC_AUDIO_I2S_OUT_BITS;

typedef enum _AHC_AUDIO_I2S_WS_POLARITY {                  ///< word select polarity
    AHC_AUDIO_I2S_LRCK_POLARITY_NONE = 0,
    AHC_AUDIO_I2S_LRCK_L_LOW,                              ///< L channel is low, R channel is high
    AHC_AUDIO_I2S_LRCK_L_HIGH,                             ///< L channel is high, R channel is low
    AHC_AUDIO_I2S_MAX_WS_POLARITY
} AHC_AUDIO_I2S_WS_POLARITY;

typedef enum _AHC_AUDIO_PLAY_FORMAT {
    AHC_AUDIO_PLAY_FMT_MP3 = 0,
    AHC_AUDIO_PLAY_FMT_AAC,
    AHC_AUDIO_PLAY_FMT_ADPCM,
    AHC_AUDIO_PLAY_FMT_WMA,
    AHC_AUDIO_PLAY_FMT_MULAW,
    AHC_AUDIO_PLAY_FMT_WAVE,
    AHC_AUDIO_PLAY_FMT_PCM16,
    AHC_AUDIO_PLAY_FMT_OGG
} AHC_AUDIO_PLAY_FORMAT;



/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef struct _AHC_AUDIO_I2S_CFG {
    AHC_AUDIO_I2S_WORK_MODE    	workingMode;                ///< working in master or slave mode
    AHC_AUDIO_I2S_MCLK_MODE    	mclkMode;                   ///< N*fs or USB mode
    AHC_AUDIO_I2S_OUT_BITS     	outputBitSize;              ///< bit size per channel
    AHC_AUDIO_I2S_WS_POLARITY  	lrckPolarity;               ///< LRCK polarity
    /*
    AHC_AUDIO_I2S_DELAY_MODE   	outDataDelayMode;           ///< output data delay mode
    AHC_BOOL                   	bOutputBySDI;               ///< MMP_TRUE: set SDI as output mode
    AHC_BOOL                   	bInputFromSDO;              ///< MMP_TRUE: data input from SDO
    UINT8                   	ubInBitAlign;               ///< the bypass bit before start fetch data
    UINT8                   	ubOutBitAlign;              ///< number of 0's in front of PCM for alignment
    */
} AHC_AUDIO_I2S_CFG;

typedef struct _AUDIO_ATTR {
	UINT8  wave_format;
	UINT16 sample_rate;
	UINT8  channels;  
	UINT16 avg_bitrate;
	UINT32 data_size;
	UINT32 total_time;
} AUDIO_ATTR;

typedef struct _AHC_SOUND_FILE_QUEUE_
{
	AHC_SOUNDEFFECT_TYPE soundtype;
	AHC_RTC_TIME		 soundInitTime;
	AHC_MSOUND_TYPE      mstype;
} AHC_SOUND_FILE_QUEUE;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

/** @addtogroup AHC_AUDIO
@{
*/
AHC_BOOL AIHC_InitAudioExtDACIn(void);
AHC_BOOL AIHC_InitAudioExtDACOut(void);

AHC_BOOL AHC_RecordAudioByName(UINT8* pFileName) ;
AHC_BOOL AHC_ConfigAudioExtDevice(AHC_AUDIO_I2S_CFG* byPortCFG, UINT16 uwSampleRate);
AHC_BOOL AHC_GetAudioFileAttr(AUDIO_ATTR *pAudioAttr);
AHC_BOOL AHC_CaptureAudioMessage(void);
AHC_BOOL AHC_StopRecording(UINT32 *plTotalTime);
AHC_BOOL AHC_PlayAudioMessage(void);
AHC_BOOL AHC_ConfigAudioRecFormat(UINT8 byAudioFormat, UINT32 uiAudioSampleRate, UINT8 bySelChannel , UINT32 uiBitRate);
AHC_BOOL AHC_RecordAudioCmd(UINT8 byAudioFormat, UINT8 byOpType);
AHC_BOOL AHC_GetAudioCurRecTime(UINT32 *pulTime);
AHC_BOOL AHC_PlayAudioByName(UINT8 *pFileName, UINT8 byOpType);
AHC_BOOL AHC_PlayAudioCmd(UINT8 byOpType, UINT32 byParam);
AHC_BOOL AHC_ConfigAudioAnnotation(AHC_BOOL bValue, UINT16 uwPre, UINT16 uwAfter);
AHC_BOOL AHC_AudioAnnotationStop(void);
AHC_BOOL AHC_SelectAudioUnit(AHC_AUDIO_UINT_ID eAudId);
AHC_BOOL AHC_GetCurrentAudioUnit(AHC_AUDIO_UINT_ID *peAudId);
AHC_BOOL AHC_GetAudioCurrentTime(UINT32 *pulTime);
AHC_BOOL AHC_AudioSetRecMultiplier(float fMultiplier );
AHC_BOOL AHC_Audio_ParseOptions(MMPS_3GPRECD_AUDIO_OPTION option, MMPS_3GPRECD_AUDIO_FORMAT *format,
        MMP_ULONG *samplingRate, MMP_ULONG *bitRate);
/// @}

//Sound Effect Function
AHC_BOOL 	AHC_IsSpeakerEnable(void);
AHC_BOOL 	AHC_SpeakerEnable(MMP_GPIO_PIN piopin, AHC_BOOL enable);
AHC_BOOL 	AHC_GetSoundEffectStatus(UINT8 *ubSoundEffectStatus);
AHC_BOOL    AHC_PlaySoundEffectEx(AHC_SOUNDEFFECT_TYPE soundtype, AHC_MSOUND_TYPE MSType, AHC_SOUND_IMPORTANCE SImportance);
AHC_BOOL 	AHC_PlaySoundEffect(AHC_SOUNDEFFECT_TYPE soundtype);
AHC_BOOL 	AHC_SetSoundEffectExist(AHC_BOOL bExist);
UINT8 		AHC_GetSoundEffectExist(void);
AHC_BOOL 	AHC_LoadSoundEffect(void);

#endif // _AHC_AUDIO_H_
