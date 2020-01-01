#ifndef __EM_AUDIO_ITF_PUB_H__
#define __EM_AUDIO_ITF_PUB_H__

#include "vm_types.ht"
#include "vm_msgof.hc"
#include "mdl_aud_core_forward.h"
//#include "vm_audio.h"
//#include "hal_audio.h"

//#ifndef _AEC_H
//#include "hwlaud_aec-fd.h"
//#endif // _AEC_H


/**
 *  @brief The structure defines the EM audio calibration error code
 */
typedef enum {
  EM_AUD_OK,              /**< Function complete successfully */
  EM_AUD_FAIL             /**< Function fail */
} em_AudCalErrCode_e;


/**
 *  @brief The enumeration defines the EM audio calibration profile
 */
typedef enum
{
  EM_PROFILE_DEFAULT = 0,                   /**< Audio Default Profile  */
  EM_PROFILE_HANDSET = EM_PROFILE_DEFAULT,  /**< Audio Handset Profile  */
  EM_PROFILE_HEADSET,                       /**< Audio Headset Profile  */
  EM_PROFILE_HANDSFREE,                     /**< Audio Handsfree Profile  */
  EM_PROFILE_BLUETOOTH,                     /**< Audio Bluetooth Profile  */
  EM_PROFILE_MAX,
}em_ProfileType_e;


/**
 *  @brief The enumeration defines the EM audio Test Sequence Type
 */
typedef enum
{
  EM_TEST_SEQUENCE_DEFAULT = 0,  
  EM_TEST_SEQUENCE_500HZ = EM_TEST_SEQUENCE_DEFAULT,  
  EM_TEST_SEQUENCE_1KHZ,
  EM_TEST_SEQUENCE_2KHZ, 
  EM_TEST_SEQUENCE_MLS,   
  EM_TEST_SEQUENCE_PINK,
  EM_TEST_SEQUENCE_MAX,
}em_TestSequenceType_e;
/**
 *  @brief The enumeration defines the EM audio calibration stereo format
 */
typedef enum
{
  EM_STEREO_MP3,              /**< Music */
  EM_STEREO_MIDI,
  EM_STEREO_AMR,
  EM_STEREO_AAC,
  EM_STEREO_3GP,              /**< Video */
  EM_STEREO_WAV,
  EM_STEREO_IPTV,
  EM_STEREO_FM,
  EM_STEREO_DTMF,
  EM_STEREO_ATV,
  EM_STEREO_MAX
}em_StereoFormat_e;


/**
 *  @brief The structure defines the EM audio calibration stereo parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
  em_StereoFormat_e     Type;             /**< 0:mp3  1:midi  2:amr  3:aac  4:3gp  5:wave  6:m2 pcm  7:fm  8:dtmf  9:atv  */
  AudioGain_t           Gain[32];
} em_AudSetStereoGainTable_t, em_AudGetStereoGainTable_t;


/**
 *  @brief The structure defines the EM audio calibration keypad parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
  AudioGain_t           Gain;
} em_AudSetKeypadToneGain_t, em_AudGetKeypadToneGain_t;


/**
 *  @brief The structure defines the EM audio calibration keypad parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
  AudioGain_t           DLGain[8];
} em_SetAudioDLGainTable_t, em_GetAudioDLGainTable_t;


/**
 *  @brief The enumeration defines the EM audio calibration recording mic type
 */
typedef enum
{
  EM_REC_VOICE_MEMO,        /**< Voice Memo */
  EM_REC_CAMCORDER,         /**< Camera Record */
  EM_REC_PCM_RECORDING      /**< PCM Record */
}em_RecMicType_e;


/**
 *  @brief The structure defines the EM audio calibration recording mic parameter
 */
typedef struct
{
  em_RecMicType_e       Type;             /**< 0:handset  1:headset  2:handsfree  3:bt */
  AudioGain_t           Gain;
} em_SetRecMicGain_t, em_GetRecMicGain_t;


/**
 *  @brief The structure defines the EM audio calibration uplink mic gain parameter
 */
//typedef struct
//{
//  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
//  vm_AudioGain_t        DPGA;             /**< ADCAGC_DPGAGAIN */
//  u8                    MicVol;           /**< enum(Preamp + Boost) */
//} em_SetULGains_t, em_GetULGains_t;


/**
 *  @brief The structure defines the EM audio calibration uplink DPGA gain parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
  AudioGain_t           DPGA;             /**< ADCAGC_DPGAGAIN */
}em_SetULDPGAGain_t, em_GetULDPGAGain_t;


/**
 *  @brief The structure defines the EM audio calibration uplink mic gain parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
  u8                    MicVol;           /**< enum(Preamp + Boost), bt is (0~11) */
}em_SetULMicGain_t, em_GetULMicGain_t;

/**
 *  @brief The structure defines the EM audio calibration comfort noise shift parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
  u8                    GainShrBit;       /**< comfort noise gain shift bit */
}em_SetComfortNoiseGain_t, em_GetComfortNoiseGain_t;

/**
 *  @brief The structure defines the EM audio calibration sidetone gain parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
  AudioGain_t           STVol;            /**< db */
}em_SetSTGains_t, em_GetSTGains_t;


/**
 *  @brief The enumeration defines the EM audio calibration FIR type
 */
typedef enum
{
  EM_FIR_TYPE_PREDIST,
  EM_FIR_TYPE_INCENSE_DL,
  EM_FIR_TYPE_INCENSE_UL,
  EM_FIR_TYPE_MAX
}em_FirType_e;


/**
 *  @brief The enumeration defines the EM audio calibration FIR set
 */
typedef enum
{
  //EM_FIR_SET_E2P = -1,
  EM_FIR_SET_1,
  EM_FIR_SET_2,
  EM_FIR_SET_3,
  EM_FIR_SET_4,
  EM_FIR_SET_5,
  EM_FIR_SET_MAX,
}em_FirSet_e;


/**
 *  @brief The enumeration defines the EM audio sine generateor which supports frequency
 */
typedef enum
{
  EM_AUD_250_HZ,
  EM_AUD_500_HZ,
  EM_AUD_1000_HZ,
  EM_AUD_1500_HZ,
  EM_AUD_2000_HZ,
  EM_AUD_3000_HZ,
  EM_AUD_4000_HZ,
  EM_AUD_6000_HZ,
  EM_AUD_8000_HZ,
  EM_AUD_12000_HZ,
  EM_AUD_16000_HZ,
}em_ToneFrequency_e;


/**
 *  @brief The enumeration defines the EM audio sine generateor which cae use gain
 */
typedef enum
{
  EM_AUD_0_DB,          /**< 0db */
  EM_AUD_MINUS_6_DB,    /**< -6db */
  EM_AUD_MINUS_12_DB,   /**< -12db */
  EM_AUD_MINUS_18_DB,   /**< -18db */
  EM_AUD_MINUS_24_DB,   /**< -24db */
  EM_AUD_MINUS_30_DB,   /**< -30db */
  EM_AUD_MINUS_36_DB,   /**< -36db */
  EM_AUD_MINUS_42_DB,   /**< -42db */
  EM_AUD_MINUS_48_DB,   /**< -48db */
  EM_AUD_MINUS_54_DB,   /**< -54db */
  EM_AUD_MINUS_60_DB,   /**< -60db */
  EM_AUD_MINUS_66_DB,   /**< -66db */
  EM_AUD_MINUS_72_DB,   /**< -72db */
  EM_AUD_MINUS_78_DB,   /**< -78db */
  EM_AUD_MINUS_84_DB,   /**< -84db */
  EM_AUD_MINUS_90_DB,   /**< -90db */
}em_AudioGain_e;


/**
 *  @brief The structure defines the EM audio calibration sidetone FIR parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;  /**< 0:handset  1:headset  2:handsfree  3:bt */
  em_FirType_e          Type;     /**< DSP DL PreDist:0, Incense DL :1, Incense UL :2 */
  em_FirSet_e           Set;      /**< E2P or hotcode parameter */
} em_SetFIR_t, em_GetFIR_t;


/**
 *  @brief The enumeration defines the EM audio calibration output driver type
 */
typedef enum
{
  EM_OUTPUT_DRV_HEADSET,
  EM_OUTPUT_DRV_HANDSET,
  EM_OUTPUT_DRV_LINEOUT,
  EM_OUTPUT_DRV_CLASSD
}em_OutputDrvType;


/**
 *  @brief The structure defines the EM audio calibration output driver boost parameter
 */
typedef struct
{
  em_OutputDrvType      Type;     /**< 0:Headset driver, 1:Handset driver, 2:Lineout driver, 3:ClassD*/
  u8                    mode;     /**< 0:voice, 1:multimedia */
  AudioGain_t           Gain;     /**< B2<0:1x GAIN, 1:2x GAIN>, B3<gain db>*/
}em_SetOutputDriverGain_t, em_GetOutputDriverGain_t;


/**
 *  @brief The structure defines the EM audio calibration CTA path parameter
 */
typedef struct
{
  u16                   Enable;    /**< 0:disable CTA path  1:enable CTA path */
} em_SetGsmCtaPath_t, em_GetGsmCtaPath_t;


/**
 *  @brief The structure defines the EM Downlink Fixed FIR parameter
 */
typedef struct
{
  u16                   Enable;    /**< 0:disable DL Fixed FIR  1:enable DL Fixed FIR */
} em_SetGsmDLfixedFIR_t, em_GetGsmDLfixedFIR_t;
/**
 *  @brief The structure defines the EM audio Test Sequence parameter
 */
typedef struct
{
  u16                   Enable;    /**< 0:disable Test Sequence   1:enable Test Sequence*/
  u16                   Type;
} em_SetGsmTestSequence_t, em_GetGsmTestSequence_t;

/**
 *  @brief The structure defines the EM audio calibration path control parameter
 */
typedef struct
{
  u8                    outputOn;  /**< 0:close current output   1:enable current output */
  u8                    micOn;     /**< 0:mute mic               1:unmute mic */
} em_SetPathCtrl_t, em_GetPathCtrl_t;


/**
 *  @brief The structure defines the AGC parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;          /**< 0:handset  1:headset  2:handsfree  3:bt */
  bool                  IsAGCOn;          /**< False:off  True:on */
  // output AGC params
  unsigned short        TargeLevel;       /**< OutAGCMaxMicLevel       */
  unsigned short        ClippingLevel;    /**< OutAGCMicClippingLevel  */
  unsigned short        MaxGain;          /**< OutAGCMaxMicGain        */
  unsigned short        MinGain;          /**< OutAGCMaxMicGain        */
  unsigned short        AttackRate;       /**< OutAGCAgcPeriod         */
  unsigned short        ReleaseRate;      /**< OutAGCAgcPeriod         */
}em_SetAGCParams_t, em_GetAGCParams_t;


/**
 *  @brief The structure defines the AEC parameter
 */
typedef struct
{
  em_ProfileType_e      Profile;        /**< 0:handset  1:headset  2:handsfree  3:bt */

  unsigned short  isNLPOn;              /**< TRUE/FALSE   IAEC_NLPENABLE            */
  unsigned short  nlpMin;               /**< NLP minimal gain (max NLP attenuation) */
  unsigned short  nlpShift;             /**< NLP smoothness                         */
  unsigned short  maxCNGMagn;           /**< Maximal CNG magnitude                  */

  unsigned short  isNSOn;               /**< TRUE/FALSE Turns noise suppressor      */
  unsigned short  nsMINWeight;          /**< Noise suppressor maximum suppression   */

  unsigned short  isRefSmoothingOn;     /**< TRUE/FALSE Reference smooth            */
  unsigned short  refSmoothingMag;      /**< Reference smooth Max magnitude         */

  unsigned short  isStartInHalfDuplex;  /**< TRUE/FALSE   Start Half Duplex     	  */
  unsigned short  isHalfDuplex;         /**< TRUE/FALSE   IAEC_HALFDUPLEXENABLE     */

}em_SetAECParams_t, em_GetAECParams_t;


typedef struct
{
  bool                  Enable;           /**< False:Stop  True:Start */
  u8                    Freq;             /**< enum 250Hz~16KHz */
  AudioGain_t           Gain;             /**< enum -90dB~0dB, 6dB stepsize */
}em_PlayTone_t, em_StopTone_t;


typedef struct
{
  bool                  Enable;           /**< False:Stop  True:Start */
  em_ToneFrequency_e    Freq;             /**< enum 250Hz~16KHz */
  em_AudioGain_e        Gain;             /**< enum -90dB~0dB, 6dB stepsize */
}em_PlaySineWave_t, em_StopSineWave_t;

/**
 * @brief EM audio calibration set stereo gain
 *
 * @param  stereoGainTblParam			    : Stereo gain table setting parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudSetStereoGainTable(em_AudSetStereoGainTable_t stereoGainTblParam);


/**
 * @brief EM audio calibration get stereo gain
 *
 * @param  stereoGainTblParam			    : Stereo gain table setting parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudGetStereoGainTable(em_AudGetStereoGainTable_t *stereoGainTblParam);


/**
 * @brief EM audio calibration set keypad tone gain
 *
 * @param  keypadGainParam			      : Keypadtone gain parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetKeypadToneGain (em_AudSetKeypadToneGain_t keypadGainParam);


/**
 * @brief EM audio calibration get keypad tone gain
 *
 * @param  keypadGainParam			      : Keypadtone gain parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetKeypadToneGain (em_AudGetKeypadToneGain_t *keypadGainParam);


/**
 * @brief EM audio calibration set downlink gain table
 *
 * @param  dlGainTblParam			        : Downlink gain table parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetAudioDLGainTable(em_SetAudioDLGainTable_t dlGainTblParam);


/**
 * @brief EM audio calibration get downlink gain table
 *
 * @param  dlGainTblParam			        : Downlink gain table parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetAudioDLGainTable(em_GetAudioDLGainTable_t *dlGainTblParam);


/**
 * @brief EM audio calibration set record mic gain
 *
 * @param  recMicGainParam			      : Recording mic gain parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetRecMicGain(em_SetRecMicGain_t recMicGainParam);


/**
 * @brief EM audio calibration get record mic gain
 *
 * @param  recMicGainParam			      : Recording mic gain parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetRecMicGain(em_GetRecMicGain_t *recMicGainParam);


/**
 * @brief EM audio calibration set uplink gain
 *
 * @param  gainParam			            : Uplink gain parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
//em_AudCalErrCode_e em_AudCalSetULGains(em_SetULGains_t gainParam);


/**
 * @brief EM audio calibration get uplink gain
 *
 * @param  gainParam			            : Uplink gain parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
//em_AudCalErrCode_e em_AudCalGetULGains(em_GetULGains_t *gainParam);


/**
 * @brief EM audio calibration set DPGA uplink gain
 *
 * @param  dpgaGainParam			        : Uplink gain parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetULDPGAGains(em_SetULDPGAGain_t dpgaGainParam);


/**
 * @brief EM audio calibration get DPGA uplink gain
 *
 * @param  dpgaGainParam			        : Uplink gain parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetULDPGAGains(em_GetULDPGAGain_t *dpgaGainParam);


/**
 * @brief EM audio calibration set mic uplink gain
 *
 * @param  micGainParam			          : Uplink mic gain parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetULMicGains(em_SetULMicGain_t micGainParam);


/**
 * @brief EM audio calibration get mic uplink gain
 *
 * @param  micGainParam			          : Uplink mic gain parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetULMicGains(em_GetULMicGain_t *micGainParam);

/**
 * @brief EM audio calibration set comfort noise gain
 *
 * @param  cnGainParam	              : Comfort gain parameter
 *
 * @return ESL_AUD_OK       		  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetComfortNoiseGain(em_SetComfortNoiseGain_t cnGainParam);

/**
 * @brief EM audio calibration get comfort noise gain
 *
 * @param  *pcnGainParam	          : Comfort noise gain parameter pointer
 *
 * @return ESL_AUD_OK       		  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetComfortNoiseGain(em_GetComfortNoiseGain_t *pcnGainParam);


/**
 * @brief EM audio calibration set sidetone gain
 *
 * @param  stGainParam			          : Sidetone gain parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetSTGains(em_SetSTGains_t stGainParam);


/**
 * @brief EM audio calibration get sidetone gain
 *
 * @param  stGainParam			          : Sidetone gain parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetSTGains(em_GetSTGains_t *stGainParam);


/**
 * @brief EM audio calibration set FIR
 *
 * @param  firParam			              : FIR parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetFir(em_SetFIR_t firParam);


/**
 * @brief EM audio calibration get FIR
 *
 * @param  firParam			              : FIR parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetFir(em_GetFIR_t *firParam);


/**
 * @brief EM audio calibration set GSM CTA path
 *
 * @param  gsmCtaPathParam			      : GSM CTA path parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetGsmCtaPath (em_SetGsmCtaPath_t gsmCtaPathParam);


/**
 * @brief EM audio calibration get GSM CTA path
 *
 * @param  gsmCtaPathParam			      : GSM CTA path parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetGsmCtaPath (em_GetGsmCtaPath_t *gsmCtaPathParam);

/**
 * @brief EM audio calibration get the enable flag of GSM Downlink Fixed FIR
 *
 * @param  gsmDLfixedFIRParam			      : GSM Downlink Fixed FIR parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetGsmDLfixedFIR (em_GetGsmDLfixedFIR_t *gsmDLfixedFIRParam);

/**
 * @brief EM audio calibration set the enable flag of GSM Downlink Fixed FIR
 *
 * @param  gsmDLfixedFIRParam			      : GSM Downlink Fixed FIR parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetGsmDLfixedFIR (em_SetGsmDLfixedFIR_t *gsmDLfixedFIRParam);

/**
 * @brief EM audio test sequence get the enable flag of GSM Downlink Test Sequence
 *
 * @param  gsmDLTestSequenceParam			      : GSM Downlink Test Sequence parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudGetGsmTestSequence (em_GetGsmTestSequence_t *gsmDLTestSequenceParam);

/**
 * @brief EM audio calibration set the enable flag of GSM Downlink Test Sequence
 *
 * @param  gsmDLTestSequenceParam			      : GSM Downlink Test Sequence parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudSetGsmTestSequence (em_GetGsmTestSequence_t *gsmDLTestSequenceParam);

/**
 * @brief EM audio calibration set Output driver gain boost
 *
 * @param  outputDrvGainParam			    : Output dirver gain parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetOutputDriverGain(em_SetOutputDriverGain_t outputDrvGainParam);


/**
 * @brief EM audio calibration get Output driver gain boost
 *
 * @param  outputDrvGainParam			    : Output dirver gain parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetOutputDriverGain(em_GetOutputDriverGain_t *outputDrvGainParam);


/**
 * @brief EM audio calibration set Path control
 *
 * @param  pathCtrlParam			        : Path control parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetPathCtrl(em_SetPathCtrl_t pathCtrlParam);


/**
 * @brief EM audio calibration get Path control
 *
 * @param  pathCtrlParam			        : Path control parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetPathCtrl(em_GetPathCtrl_t *pathCtrlParam);


/**
 * @brief EM audio calibration set AGC
 *
 * @param  agcParam			              : AGC setting parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetAGCParams(em_SetAGCParams_t agcParam);


/**
 * @brief EM audio calibration get AGC
 *
 * @param  agcParam			              : AGC setting parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetAGCParams(em_GetAGCParams_t *agcParam);


/**
 * @brief EM audio calibration set AEC
 *
 * @param  aecParam			              : AEC setting parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalSetAECParams(em_SetAECParams_t aecParam);


/**
 * @brief EM audio calibration get AEC
 *
 * @param  aecParam			              : AEC setting parameter pointer
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalGetAECParams(em_GetAECParams_t *aecParam);


/**
 * @brief EM audio calibration play tone
 *
 * @param  toneParam			            : Tonepaly parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalPlayTone(em_PlayTone_t toneParam);


/**
 * @brief EM audio calibration stop tone
 *
 * @param  toneParam			            : Tonepaly parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalStopTone(em_StopTone_t toneParam);


/**
 * @brief EM audio calibration play sine wave
 *
 * @param  toneParam			            : Sine wave parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */

em_AudCalErrCode_e em_AudCalPlaySineWave(em_PlaySineWave_t sineWaveParam);


/**
 * @brief EM audio calibration stop sine wave
 *
 * @param  toneParam			            : Sine wave parameter
 *
 * @return ESL_AUD_OK       				  : Audio set success
 * @return ESL_AUD_FAIL               : Audio set fail
 */
em_AudCalErrCode_e em_AudCalStopSineWave(em_PlaySineWave_t sineWaveParam);

#endif /*__EM_AUDIO_ITF_PUB_H__*/

