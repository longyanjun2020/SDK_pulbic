//==============================================================================
//
//  File        : mmpf_pll.h
//  Description : INCLUDE File for the Firmware PLL Driver.
//  Author      : Rogers Chen
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_PLL_H_
#define _MMPF_PLL_H_

#include "config_fw.h"
#include "mmp_err.h"
#include "mmpf_typedef.h"
#include "mmp_clk_inc.h"
#if (AUD_DUPLEX_CAN_USE_DIF_FS)
//#include "mmp_aud_inc.h"
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

#if (VR_AVSYNC_METHOD == VR_AVSYNC_REF_VID)
/* The following values should be sync with audio PLL M/N settings */
#define FRACT_STEP_PER_SAMPLE_48K       (89)  //(112)
#define FRACT_STEP_PER_SAMPLE_32K       (134) //(168)
#define FRACT_STEP_PER_SAMPLE_24K       (179) //(224)
#define FRACT_STEP_PER_SAMPLE_16K       (268) //(336)
#define FRACT_STEP_PER_SAMPLE_8K        (537) //(447)
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_PLL_MODE
{
    //For PLL3 to Audio(G5)
    MMPF_PLL_AUDIO_192K,
    MMPF_PLL_AUDIO_128K,
    MMPF_PLL_AUDIO_96K,
    MMPF_PLL_AUDIO_64K,
    MMPF_PLL_AUDIO_48K,
    MMPF_PLL_AUDIO_44d1K,
    MMPF_PLL_AUDIO_32K,
    MMPF_PLL_AUDIO_24K,
    MMPF_PLL_AUDIO_22d05K,
    MMPF_PLL_AUDIO_16K,
    MMPF_PLL_AUDIO_12K,
    MMPF_PLL_AUDIO_11d025K,
    MMPF_PLL_AUDIO_8K,

    MMPF_PLL_ExtClkOutput,
    MMPF_PLL_MODE_NUMBER
} MMPF_PLL_MODE;

typedef enum _MMPF_AUDSRC {
	MMPF_AUDSRC_MCLK = 0,
	MMPF_AUDSRC_I2S
} MMPF_AUDSRC;

typedef struct _MMPF_PLL_SETTINGS {
    MMP_UBYTE M;
    MMP_UBYTE N;
    MMP_UBYTE K;
    MMP_ULONG frac;
    MMP_UBYTE VCO;
    MMP_ULONG freq;
} MMPF_PLL_SETTINGS;

typedef enum _MMPF_PLL_HDMI_MODE
{
	MMPF_PLL_HDMI_27MHZ = 0,
	MMPF_PLL_HDMI_74_25MHZ,
	MMPF_PLL_HDMI_SYNC_DISPLAY
} MMPF_PLL_HDMI_MODE;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void MMPF_PLL_WaitCount(MMP_ULONG count);
MMP_ERR MMPF_PLL_PowerUp(GRP_CLK_SRC PLLNo, MMP_BOOL PLLPowerUp);
MMP_ERR MMPF_PLL_GetGroupFreq(CLK_GRP ubGroupNum, MMP_ULONG *ulGroupFreq);
MMP_ERR MMPF_PLL_GetGroupSrcAndDiv(CLK_GRP ubGroupNum, GRP_CLK_SRC *clkSrc, MMP_UBYTE* pubPllDiv);
MMP_ERR MMPF_PLL_Initialize(void);
#if (AUD_DUPLEX_CAN_USE_DIF_FS)
MMP_ERR MMPF_PLL_SetAudioPLL(MMPF_AUDSRC AudPath, MMPF_PLL_MODE ulSampleRate, MMP_AUD_INOUT_PATH ubPath);
#else
MMP_ERR MMPF_PLL_SetAudioPLL(MMPF_AUDSRC AudPath, MMPF_PLL_MODE ulSampleRate);
#endif
void MMPF_PLL_SetAudioPLLFract(MMP_LONG fract);
MMP_ERR MMPF_PLL_SetTVCLK(void);
MMP_ERR MMPF_PLL_ChangeVIFClock(GRP_CLK_SRC PLLSrc, MMP_ULONG ulDivNum);
MMP_ERR MMPF_PLL_ChangeISPClock(GRP_CLK_SRC PLLSrc, MMP_ULONG ulDivNum);
MMP_ERR MMPF_PLL_ChangeBayerClock(GRP_CLK_SRC PLLSrc, MMP_ULONG ulDivNum);

#if (VR_AVSYNC_METHOD == VR_AVSYNC_REF_VID)
void MMPF_PLL_UpdateAudPLLFract(MMP_BOOL bSpeedUp, MMP_LONG ulAdjFract);
#endif
#endif // _MMPF_PLL_H_
