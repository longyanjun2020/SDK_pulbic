//bass.h
#include "app_datatype.h"
#define __POSTPROC_MGR_DATATYPE_H__
#define ENABLE_BASS_PARSER_PRINTF
//#define HEADPHONE_HALF_HPASS

#ifdef ENABLE_BASS_PARSER_PRINTF
#define BASS_DBG_MSG vm_dbgTrace
#else
#define BASS_DBG_MSG
#endif
#define BASS_FRAME_SIZE 4096 //bytes (512*4*2)
#define BASS_MEM_TOTAL_SIZE  (BASS_FRAME_SIZE<<1) // HPout+LPout
#define SIZEOF_BASS_DATA      ( (sizeof(tS32)*3) + sizeof(tU8) +sizeof(tS16)+ sizeof(eSpkSize) +sizeof(eBPType)+ sizeof(eDRC_ReleaseRate) +sizeof(eDRC_AttackRate) + sizeof(eDevice))
typedef enum
{
    eSpeakerCutFreq60Hz = 0,
	eSpeakerCutFreq100Hz ,
       eSpeakerCutFreq200Hz,
       eSpeakerCutFreq300Hz,
       eSpeakerCutFreq400Hz,
       eSpeakerCutFreq600Hz,
       eSpeakerCutFreq800Hz,
    eSpeakerCutFreqEnum32Bit = 0x10000000	// To make enum take 4 bytes
} eSpkSize;

typedef enum
{
	eSpeaker = 0,
	eHeadphone,
	eTiny_Speaker,
    kDeviceEnum32Bit = 0x10000000	 // To make enum take 4 bytes
} eDevice;

typedef enum
{
	eRT40 = 0,
	eRT60,
	eRT100,
    kDRCRTEnum32Bit = 0x10000000	 // To make enum take 4 bytes
} eDRC_ReleaseRate;

typedef enum
{
	eAT3 = 0,
	eAT5,
	eAT10,
    kDRCATEnum32Bit = 0x10000000	 // To make enum take 4 bytes
} eDRC_AttackRate;


typedef enum
{
    eLevelN6dB = 0,
    eLevelN7dB,
    eLevelN8dB,
    eLevelN9dB,
    eLevelN10dB,
    eLevelN11dB,
    kLeveldBEnum32Bit = 0x10000000	 // To make enum take 4 bytes
} eLeveldB;

typedef enum
{
	eBPFreq180Hz =0,
       eBPFreq240Hz,
       eBPFreq360Hz,
       eBPFreq600Hz,
       eBPFreq800Hz,
       //eBPFreq1200Hz,
       //eBPFreq100_1600Hz,
       eBPFreq200_800Hz,
       //eBPFreq200_1600Hz,
       eBPFreq300_800Hz,
       eBPFreq400_800Hz,
    eBPFreq32Bit = 0x10000000	// To make enum take 4 bytes
} eBPType;

typedef struct
{
	tU8 bEn;
	tU8 u8mode;
       tS32 s32samplerate;
       tS16 s32ChNum;
       eSpkSize eSpeakerSize;
       eDevice eDeviceType;
       tS16 s16LowPassGain;
       eBPType eBPFreq;
       eDRC_ReleaseRate eReleaseRate;
       eDRC_AttackRate eAttackRate;
       tS32 s32limiterLevel;
       tS32 s32NoiseLevel;
       tS32 s32BasicGainShift;
}STR_SETBASS;

typedef struct
{
    tS32 s32DetectLevel;
    tS32 s32LimitLevel;
    tS32 s32NoiseLevel;
    tU16 u16RTIdx;
    tU16 u16ATIdx;
    tS32 s32RTCoef;
    tS32 s32ATCoef;
    tS32 s32MaxGain; // constant gain between limiter level and noise level
}STR_DRC;

typedef struct
{
       tU8 updateflag;
       tU16 u16SmpRtIdx;
       tS32* ps32_cmpHPfilterCoef;
       tS32* ps32_cmpLPfilterCoef;
       tS32* ps32_BPFilterCoef;
       tS32 ps32hpbuf[8];
       tS32 ps32lpbuf[8];
       tS32 ps32bpbuf[16];
       tS32* ps32HPout;
       tS32* ps32LPout;
       tU8* u8AllocBuf;
       tS32 s32Q15_LGain;
       tS32 s32finalShift; // LGainshift + shift 6 bit(29-23) + gainshfit bit
       //#ifdef  HEADPHONE_HALF_HPASS
       tS16 HeadPHone_HPShift;
       //#endif
       STR_DRC strDRC;
       STR_SETBASS strSetBass;
}STR_BASS;
tBOOL Bass_Allocate(void* void_str_bass, tU8* u8addr);
tBOOL Bass_process(void* void_str_bass,tS32* ps32InBuf, tS32 s32in_size_perCh, tS32 s32ch_num);
tBOOL Bass_Init(void* void_str_bass, void*void_set_bass,tS16 s16ch_num, tS32 sample_rate);
tBOOL Bass_Close(void* void_str_bass, void*void_set_bass);
tBOOL BASS_Update(void* void_str_bass, void* void_set_bass);
tBOOL BASS_Check(void* void_str_bass, void* void_set_bass, tU8* checkflag);
tBOOL BASS_SetPower(void* void_set_bass, tU8 bEn);
tBOOL BASS_GetPower(void* void_set_bass, tU8* bEn);
tBOOL Bass_GetSPKSize(void* void_set_bass, eSpkSize* speakerSize);
tBOOL Bass_SetSPKSize(void* void_set_bass, eSpkSize speakerSize);
tBOOL Bass_GetDeviceType(void* void_set_bass, eDevice *devicetype);
tBOOL Bass_SetDeviceType(void* void_set_bass, eDevice devicetype);
tBOOL Bass_SetBasicGainShift(void* void_set_bass, tS32 s32basicGainShfit);
tBOOL Bass_SetDRCAttackRate(void* void_set_bass, eDRC_AttackRate eAttackRate);
tBOOL Bass_SetDRCReleaseRate(void* void_set_bass, eDRC_ReleaseRate eReleaseRate);
tBOOL Bass_SetLimiterLevel(void* void_set_bass, tS32 s32LimiterLevel);
tBOOL Bass_SetBPFreq(void* void_set_bass, eBPType eBPFreq);
tBOOL Bass_SetNoiseLevel(void* void_set_bass, tS32 s32NoiseLevel);

tS32  AUD_BassPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);
tS32  AUD_BassPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32  AUD_BassPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tBOOL BASS_SetGain(void* void_set_bass, tS16 s8Gain);
tBOOL BASS_GetGain(void* void_set_bass, tS16* s8Gain);

