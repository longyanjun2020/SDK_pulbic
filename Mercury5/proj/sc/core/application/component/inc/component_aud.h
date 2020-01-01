//------------------------------------------------------------------------------
//
//  File        : component_aud.h
//  Description : Header file of audio configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_AUDSYS_H_
#define _COMPONENT_AUDSYS_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"
#include "mmp_aud_inc.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    AUDENC_COMPONENT_FRONT = 0,
    AUDENC_COMPONENT_MAX
};

typedef enum
{
    AUDDEC_COMPONENT_PLAYBACK = 0,
    AUDDEC_COMPONENT_MAX
};

typedef enum
{
    COMPONENT_AUD_DIRECTION_RECORD = 0x00,
    COMPONENT_AUD_DIRECTION_PLAYBACK,
    COMPONENT_AUD_DIRECTION_MAX
} MMP_COMPONENT_HANDLER_AUD_DIRECTION;

typedef enum
{
    // Input Path
    COMPONENT_AUD_RECORD_PATH_DIFF_STERO_MIC = 0x00,
    COMPONENT_AUD_RECORD_PATH_SINGLE_LINEIN,
    COMPONENT_AUD_RECORD_PATH_DMIC,
    COMPONENT_AUD_RECORD_PATH_I2S_RX,
    COMPONENT_AUD_RECORD_PATH_MAX,

    // Output Path
    COMPONENT_AUD_PLAYBACK_PATH_SINGLE_LINEOUT = 0x10,
    COMPONENT_AUD_PLAYBACK_PATH_I2S_TX,
    COMPONENT_AUD_PLAYBACK_PATH_SRC_I2STX,
    COMPONENT_AUD_PLAYBACK_PATH_MAX
} MMP_COMPONENT_HANDLER_AUD_PATH;

typedef enum
{
    COMPONENT_AUD_FORMAT_AAC = 0x00,               ///< Video encode with AAC audio
    COMPONENT_AUD_FORMAT_AMR,                      ///< Video encode with AMR audio
    COMPONENT_AUD_FORMAT_ADPCM,                     ///< Video encode with ADPCM audio
    COMPONENT_AUD_FORMAT_MP3,                      ///< video encode with MP3 audio
    COMPONENT_AUD_FORMAT_PCM                       ///< video encode with raw PCM audio
} MMP_COMPONENT_HANDLER_AUD_FORMAT;

typedef enum
{
    COMPONENT_AUD_AAC_BASE      = 0x00,         ///< Audio AAC format
    COMPONENT_AUD_AAC_16K_32K       = 0x02,         ///< AAC    16KHz with 32kbps
    COMPONENT_AUD_AAC_16K_64K,                      ///< AAC    16KHz with 64kbps
    COMPONENT_AUD_AAC_22d05K_64K,                   ///< AAC 22.05KHz with 64kbps
    COMPONENT_AUD_AAC_22d05K_128K,                  ///< AAC 22.05KHz with 128kbps
    COMPONENT_AUD_AAC_32K_64K,                      ///< AAC 32KHz with 64kbps
    COMPONENT_AUD_AAC_32K_128K,                     ///< AAC 32KHz with 128kbps
    COMPONENT_AUD_AAC_48K_128K,                     ///< AAC 48KHz with 128kbps
    COMPONENT_AUD_AAC_44d1K_64K,                    ///< AAC 44.1KHz with 64kbps
    COMPONENT_AUD_AAC_44d1K_128K,                   ///< AAC 44.1KHz with 128kbps

    COMPONENT_AUD_AMR_BASE      = 0x10,         ///< Audio AMR format
    COMPONENT_AUD_AMR_4d75K,                        ///< AMR 4.75KHz with 8kbps
    COMPONENT_AUD_AMR_5d15K,                        ///< AMR 5.15KHz with 8kbps
    COMPONENT_AUD_AMR_12d2K,                        ///< AMR 12.2KHz with 8kbps

    //ADPCM section, need to sync with MMPF_SetADPCMEncMode
    COMPONENT_AUD_ADPCM_16K_22K,                    ///< ADPCM 16KHz with 22kbps
    COMPONENT_AUD_ADPCM_32K_22K,                    ///< ADPCM 32KHz with 22kbps
    COMPONENT_AUD_ADPCM_44d1K_22K,                  ///< ADPCM 44.1KHz with 22kbps
    COMPONENT_AUD_ADPCM_48K_22K,                    ///< ADPCM 48KHz with 22kbps

    COMPONENT_AUD_MP3_32K_128K,                    ///< MP3 32KHz with 128kbps
    COMPONENT_AUD_MP3_44d1K_128K,                  ///< MP3 44.1KHz with 128kbps

    COMPONENT_AUD_PCM_16K,                         ///< Raw PCM 16KHz
    COMPONENT_AUD_PCM_32K                          ///< Raw PCM 32KHz
} MMP_COMPONENT_HANDLER_AUD_OPTION;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_COMPONENT_HANDLER_AUD_GAIN
{
    MMP_UBYTE    ubMicPreGainLevel;  // Level maps to dB value(MMP_AUD_GAIN_MIC_PREGAIN)
    MMP_UBYTE    ubADCGainLevel;     // Level maps to dB value(MMP_AUD_GAIN_ADC_ANALOG)
    signed short sDpgaGain;          // Direct dB value -64 to 64 dB
}MMP_COMPONENT_HANDLER_AUD_GAIN;

typedef struct _MMP_COMPONENT_HANDLER_AUD
{
    MMP_COMPONENT_HANDLER_AUD_PATH   AudPath;
    MMP_COMPONENT_HANDLER_AUD_FORMAT AudFormat;
    MMP_COMPONENT_HANDLER_AUD_OPTION AudOption;
    MMP_COMPONENT_HANDLER_AUD_GAIN   *pAudGain;
    MMP_ULONG   ulSampleRate;
    MMP_ULONG   ulBitRate;
} MMP_COMPONENT_HANDLER_AUD;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_AUD_Encode[];
extern MMP_COMPONENT_BASE Component_AUD_Decode[];

extern MMP_COMPONENT_MEMORY_INFO Component_AudEnc_Memory[];
extern MMP_COMPONENT_MEMORY_INFO Component_AudDec_Memory[];
extern MMP_COMPONENT_HANDLER_AUD Component_AudEnc_Handler[];
extern MMP_COMPONENT_HANDLER_AUD Component_AudDec_Handler[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

#endif // _COMPONENT_AUD_H_

