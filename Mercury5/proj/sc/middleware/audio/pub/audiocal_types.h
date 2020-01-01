#ifndef __AUDIOCAL_TYPES_H__
#define __AUDIOCAL_TYPES_H__

#include "mdl_aud_forward.h"
#include "audiocal_api.h"

// audiocal_api.h
struct tACAECParams_
{
    u16 AP_AEC_Config;
    u16 AP_AEC_NLP_MIN;
    u8 AP_AEC_DT_THR;
    u8 AP_AEC_NLP_SHIFT;
    u16 AP_AEC_MAX_CNG_MAG;
    u16 AP_AEC_TONEDET_THR;
    u16 AP_AEC_NS_MIN_WEIGHT;
    u16 AP_AEC_REFSMOOTHING_MAG;
    u16 AP_AEC_DT_SENS_THR;
    u16 AP_AEC_FREQ_DT;
    u8 AP_AEC_LPF_CUT_OFF;
    u8 AP_AEC_FIXED_DELAY;

    /* AGC related parameters are not implemented */
    /* They keep the values defined in hwlaud_aec.c */
    /* Same for RapidDTThr */
};

struct tACParams_
{
    u8 AP_Config;
    s16 AP_PreDist[AC_PREDIST_LENGTH];
    s16 AP_DspUl[AC_DSPUL_LENGTH];
    s16 AP_GSMDL[AC_GSMDL_LENGTH];
    s16 AP_GSMUL[AC_GSMUL_LENGTH];
    s8 AP_ST1Vol;
    s8 AP_ST2Vol;
    s8 AP_DLVolMax;
    s8 AP_ULVolMax;
    u8 AP_MicVol;
    tACAECParams AEC;
};

/* parameters stored in E2P */
struct tACParams_E2P_
{
    u16 AP_AEC_Config;
    u16 AP_AEC_NLP_MIN;
    u16 AP_AEC_MAX_CNG_MAG;
    u16 AP_AEC_TONEDET_THR;
    u16 AP_AEC_NS_MIN_WEIGHT;
    u16 AP_AEC_REFSMOOTHING_MAG;
    u16 AP_AEC_DT_SENS_THR;

    u8 AP_Config;
    s8 AP_ST1Vol_MicVol; /* packed 4MSB + 4LSB */
    s8 AP_ST2Vol;
    s8 AP_DLVolMax;
    s8 AP_ULVolMax;

    u8 AP_AEC_DT_THR_NLP_SHIFT; /* packed 4MSB + 4LSB */
    u8 AP_AEC_FIXED_DELAY;
};
// end audiocal_api.h

#endif // __AUDIOCAL_TYPES_H__

