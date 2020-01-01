////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------------------------------
// Modification History
//---------------------------------------------------------------------------------------------
//  Date     | Author       | Description
//-----------+--------------+------------------------------------------------------------------
//27/10/2009 | Vincent.chen | Creation
//12/11/2009 | Vincent.chen | fix bug that error occur while selecting NG's Att/Rel coefficnet
//01/03/2011 | Wendy.Lin    | Re-organize and support stereo channel, 3 sampling rate: 8000, 16000, 32000

#ifndef __ARP_SW_AGC_H__
#define __ARP_SW_AGC_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "arp_datatype.h"

/*============================================================================*/
// Extern definition
/*============================================================================*/
//...

/*============================================================================*/
// Macro definition
/*============================================================================*/
/*------------------ Process Data Type ------------------*/
//...

/*----------------- Print Message Switch ----------------*/
#define ENABLE_ARP_SWAGC_PARSER_PRINTF

/*--------------------- Channel size --------------------*/
#define ARP_SWAGC_MAX_CH_NUM 2

/*------------------ AGC Coeff Boundary -----------------*/

// Target level dB : -24~-2 dB
#define AGC_MIN_TARGET_DB        (-24)
#define AGC_MAX_TARGET_DB        (-2)
#define AGC_TARGET_DB_OFFSET     (-AGC_MIN_TARGET_DB)
#define AGC_TARGET_DB_SIZE       (AGC_MAX_TARGET_DB - AGC_MIN_TARGET_DB + 1)

// Maximum gain can adjust dB : 0~24 dB
#define AGC_MIN_MAXGAIN_DB       (0)
#define AGC_MAX_MAXGAIN_DB       (24)
#define AGC_MAXGAIN_DB_OFFSET    (-AGC_MIN_MAXGAIN_DB)
#define AGC_MAXGAIN_DB_SIZE      (AGC_MAX_MAXGAIN_DB - AGC_MIN_MAXGAIN_DB + 1)

// Minimum gain can adjust dB : -24~-3 dB
#define AGC_MIN_MINGAIN_DB       (-24)
#define AGC_MAX_MINGAIN_DB       (-3)
#define AGC_MINGAIN_DB_OFFSET    (-AGC_MIN_MINGAIN_DB)
#define AGC_MINGAIN_DB_SIZE      (AGC_MAX_MINGAIN_DB - AGC_MIN_MINGAIN_DB + 1)

// Attack rate step : 1~10*(50dB/s)  or (30ms/6dB)
#define AGC_MIN_ATTTACK_IDX      (1)
#define AGC_MAX_ATTTACK_IDX      (10)
#define AGC_ATTTACK_IDX_OFFSET   (-AGC_MIN_ATTTACK_IDX)
#define AGC_ATTTACK_IDX_SIZE     (AGC_MAX_ATTTACK_IDX - AGC_MIN_ATTTACK_IDX + 1)

// Decay rate step : 1~10*(3.65dB/s) or (1.64s/6dB)
#define AGC_MIN_DECAY_IDX        (1)
#define AGC_MAX_DECAY_IDX        (10)
#define AGC_DECAY_IDX_OFFSET     (-AGC_MIN_DECAY_IDX)
#define AGC_DECAY_IDX_SIZE       (AGC_MAX_DECAY_IDX - AGC_MIN_DECAY_IDX + 1)

// 0~2000 ms
#define AGC_MIN_HOLDTIME_MS      (0)
#define AGC_MAX_HOLDTIME_MS      (2000)
#define AGC_HOLDTIME_MS_OFFSET   (-AGC_MIN_HOLDTIME_MS)
#define AGC_HOLDTIME_MS_SIZE     (AGC_MAX_HOLDTIME_MS - AGC_MIN_HOLDTIME_MS + 1)

// Length of the lookahead used by AGC : 0~20 ms
#define AGC_MIN_LOOKAHEAD_MS     (0)
#define AGC_MAX_LOOKAHEAD_MS     (20)
#define AGC_LOOKAHEAD_MS_OFFSET  (-AGC_MIN_LOOKAHEAD_MS)
#define AGC_LOOKAHEAD_MS_SIZE    (AGC_MAX_LOOKAHEAD_MS - AGC_MIN_LOOKAHEAD_MS + 1)
#define AGC_LOOKAHEAD_BUF_SIZE   (ARP_SWAGC_MAX_CH_NUM*((AGC_LOOKAHEAD_MS_SIZE*ARP_FS_32K)/1000))

// Noise gate threshold : -64~-36 dB, -6dB/step
#define AGC_MIN_NGTHRESH_DB      (-64)
#define AGC_MAX_NGTHRESH_DB      (-36)
#define AGC_NGTHRESH_DB_OFFSET   (-AGC_MIN_NGTHRESH_DB)
#define AGC_NGTHRESH_DB_SIZE     (AGC_MAX_NGTHRESH_DB - AGC_MIN_NGTHRESH_DB + 1)

// Noise gate attenuate level when fading mode : -24~-0 dB
#define AGC_MIN_NGATTGAIN_DB     (-24)
#define AGC_MAX_NGATTGAIN_DB     (0)
#define AGC_NGATTGAIN_DB_OFFSET  (-AGC_MIN_NGATTGAIN_DB)
#define AGC_NGATTGAIN_DB_SIZE     (AGC_MAX_NGATTGAIN_DB - AGC_MIN_NGATTGAIN_DB + 1)

// Hysteresis holding samples : 0~2000 ms
#define AGC_MIN_NGHOLDTIME_MS    (0)
#define AGC_MAX_NGHOLDTIME_MS    (2000)
#define AGC_NGHOLDTIME_MS_OFFSET (-AGC_MIN_NGHOLDTIME_MS)
#define AGC_NGHOLDTIME_MS_SIZE   (AGC_MAX_NGHOLDTIME_MS - AGC_MIN_NGHOLDTIME_MS + 1)

// Noise gate release coef : (2^-k) k= 5~10
#define AGC_MIN_NGATT_IDX        (5)
#define AGC_MAX_NGATT_IDX        (10)
#define AGC_NGATT_IDX_OFFSET     (-AGC_MIN_NGATT_IDX)
#define AGC_NGATT_IDX_SIZE       (AGC_MAX_NGATT_IDX - AGC_MIN_NGATT_IDX + 1)

// Noise gate attack coef : (2^-k) k= 5~10
#define AGC_MIN_NGREL_IDX        (5)
#define AGC_MAX_NGREL_IDX        (10)
#define AGC_NGREL_IDX_OFFSET     (-AGC_MIN_NGREL_IDX)
#define AGC_NGREL_IDX_SIZE       (AGC_MAX_NGREL_IDX - AGC_MIN_NGREL_IDX + 1)

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
//...

/*------------------- Noise Gate Type -------------------*/
typedef enum
{
    NGATE_HOLDING = 0,
    NGATE_FADING
}ARP_SWAGC_NGATE_TYPE;

/*----------------------- Interface ---------------------*/
// Gain control
typedef struct
{
    tS16 Target;      // [r/w]desired target level
    tS16 MaxGain;     // [r/w]maximum boost gain
    tS16 MinGain;     // [r/w]maximum attenuate gain
    tS16 AtkRate;     // [r/w]attack rate
    tS16 DcyRate;     // [r/w]release rate
    tS16 HoldTime;    // [r/w]adjustable hold time
    tS16 HoldCnt;     // [r]hold time counter
}ARP_SWAGC_GAINCONTROL_s;

// Noise Gate, (static VAD)
typedef struct
{
    tS16 En;
    tS16 lThd;
    tS16 uThd;
    tS16 hTime;
    tS16 lThcnt;
    tS16 uThcnt;
    tS16 Rel;
    tS16 Att;
    tS16 Activate;
    tS16 Type;
    tS16 Attgain;
}ARP_SWAGC_NOISEGATE_s;

typedef struct
{
    tS16 bufsize;
    tS16 bufidx;
    tS16 buf[AGC_LOOKAHEAD_BUF_SIZE];
}ARP_SWAGC_DELAYBUF_s;

typedef struct
{
    tBOOL bEn;

    tS16  tAGC_TARGET;        // Target level dB
    tS16  tAGC_MAXGAIN;
    tS16  tAGC_MINGAIN;
    tS16  tAGC_ATTACK;        // Attack rate step  1~10*(50dB/s)  or (30ms/6dB)
    tS16  tAGC_DECAY;         // Decay rate step   1~10*(3.65dB/s) or (1.64s/6dB)
    tS16  tAGC_HOLDTIME;      // msec (maxmum 16382 samples, minimum and dufault 0 sample)
    tS16  tAGC_LOOKAHEAD;     // Length of the lookahead used by AGC (0~160samples)

    tBOOL tAGC_NG_TURNON ;    // Noise gate on/off
    tS16  tAGC_NG_THRESH  ;   // Noise gate threshold (-36dB~-72dB, -6dB/step)
    tS16  tAGC_NG_ATTGAIN ;   // Noise gate attenuate level when fading mode (0dB,-3dB)
    tS16  tAGC_NG_HOLDTIME ;  // Hysteresis holding samples (0~16384 /FS )
    tS16  tAGC_NG_REL;        // Noise gate release coef (2^-k) k= 5~10
    tS16  tAGC_NG_ATT  ;      // Noise gate attack coef  (2^-k) k= 5~10
    tS16  tAGC_NG_TYPE ;      // Noise gate type 'fade=1', 'hold=0'
}ARP_SWAGC_PAR_s;
#define ARP_SIZEOF_SWAGC_DATA ((sizeof(tS16)*13) + (sizeof(tBOOL)*2))

typedef struct
{
    // public variable:
    ARP_SWAGC_PAR_s sSWAGC_Ctr;
    tU8 bUpdateFlag;

    // IP specific controls
    tS16 *frmbuf;
    tS32 nchans;
    tS16 smpfreq;

    // IP specific variable:
    tS16 FastDet[ARP_SWAGC_MAX_CH_NUM];
    tS16 PeakDet[ARP_SWAGC_MAX_CH_NUM];
    tS32 gain[ARP_SWAGC_MAX_CH_NUM];
    tS16 gain_out[ARP_SWAGC_MAX_CH_NUM];
    tS16 step[ARP_SWAGC_MAX_CH_NUM];

    ARP_SWAGC_GAINCONTROL_s sGainCtl;
    ARP_SWAGC_NOISEGATE_s   sNGate;
    ARP_SWAGC_DELAYBUF_s    sLookahead;
}ARP_SWAGC_MAIN_s;

/*============================================================================*/
// Variable definition
/*============================================================================*/
//...

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif
// Parser
tS32 ARP_ATTR_16BITS ARP_SWAGCPar_CopyParFromCalbTable(tU8* ps8ModeData, const tU8* ps8CalibTab);
tS32 ARP_ATTR_16BITS ARP_SWAGCPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);

// Par.
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_GetPower(void* void_pSet, tU8 *enb);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetPower(void* void_pSet, tU8 enb);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetTarget(void* void_pSet,tS16 tAGC_TARGET);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetMaxGain(void* void_pSet, tS16 tAGC_MAXGAIN);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetMinGain(void* void_pSet, tS16 tAGC_MINGAIN);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetAtkRate(void* void_pSet,tS16 tAGC_ATTACK);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetDcyRate(void* void_pSet,tS16 tAGC_DECAY);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetHoldTime(void* void_pSet,tS16 tAGC_HOLDTIME);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetLookAheadLength(void* void_pSet,tS16 tAGC_LOOKAHEAD);

tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetNoiseGatePower(void* void_pSet, tS16 tAGC_NG_TURNON);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetNoiseGateThreshold(void* void_pSet, tS16 tAGC_NG_THRESH);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetNoiseGateAtGain(void* void_pSet, tS16 tAGC_NG_ATTGAIN);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetNoiseGateHoldTime(void* void_pSet, tS16 tAGC_NG_HOLDTIME);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetNoiseGateRtAtCoef(void* void_pSet, tS16 tAGC_NG_REL,tS16 tAGC_NG_ATT);
tBOOL ARP_ATTR_16BITS ARP_SWAGCPar_SetNoiseGateType(void* void_pSet, tS16 tAGC_NG_TYPE);

// Main
tBOOL ARP_SWAGCMain_Init(void* void_pIP,void* void_pSet, tS32 s32ChannelNum, tS32 s32Samplerate);
tBOOL ARP_SWAGCMain_Check(void* void_pIP,void* void_pSet, tU8* pbUpdateFlag);
tBOOL ARP_SWAGCMain_Update(void* void_pIP,void* void_pSet);
tBOOL ARP_SWAGCMain_Proc(void* void_pIP,tS16* procBuf, tS32 procSamplePerCh);
tBOOL ARP_SWAGCMain_Close(void* void_pIP,void* void_pSet);


#ifdef __cplusplus
}
#endif

#endif



