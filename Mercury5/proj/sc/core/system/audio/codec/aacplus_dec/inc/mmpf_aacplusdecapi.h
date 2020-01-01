
#ifndef AACPLUSAPI_H
#define AACPLUSAPI_H

//#include "includes_fw.h"
//#include "lib_retina.h"
#include "mmpf_typedef.h"

typedef unsigned int Word32u;
typedef unsigned short Word16u;
typedef unsigned char Word8u;

//#define AACPLUS_SIZEOF_WORKING_BUF  0x11800  //0x11800 = 70k (aac main profile)  //0xA800 = 42k (aac lc profile)
#define AACPLUS_SIZEOF_WORKING_BUF  0x16C00  //0x16C00 = 91k (aac main profile + 6CH)  //0xA800 = 42k (aac lc profile)

#define AACPLUS_INBUF_SIZE          (5000) //(6144*2/8) /*!< Size of Input buffer in bytes*/
#define AACPLUS_OUTFRAMESIZE        4096
#define AACPLUS_OUTFRAMECOUNT       3
#define AACPLUS_TIMEDATASIZE        (5 * AACPLUS_OUTFRAMESIZE)
#if (SEC_DNSE_VH_ON == 1)
#define AACPLUS_VHLRDATASIZE        (2 * AACPLUS_OUTFRAMESIZE)
#else
#define AACPLUS_VHLRDATASIZE        (0)
#endif
#if (VAAC_P_EN)
#define A8_AUDIO_OUTPUT_FRAME_NUM   3           // eric add
#define AAC_SAMPLES_PER_FRAME       1024
#define AAC_TIME_BUFFER_NUM         (A8_AUDIO_OUTPUT_FRAME_NUM*2+2)
#define PROCESS_AAC_HEADER          1
#ifndef SIZEOF_AUDIO_HEADER
    #define SIZEOF_AUDIO_HEADER     12
#endif
#endif

#if (GAPLESS_EN == 1)||(SRC_SUPPORT == 1)
#define AACPLUS_OUTBUF_SIZE         (AACPLUS_OUTFRAMESIZE << 1)
#else
#define AACPLUS_OUTBUF_SIZE         ((AACPLUS_OUTFRAMESIZE * AACPLUS_OUTFRAMECOUNT) << 1)
#endif
#if (SEC_DNSE_VH_ON == 1)
#define AACPLUS_EXTRA_BUF_SIZE      (AACPLUS_VHLRDATASIZE)
#else
#define AACPLUS_EXTRA_BUF_SIZE      (0)
#endif
#define AACPLUSDEC_BUFFER_SIZE      (AACPLUS_SIZEOF_WORKING_BUF + \
                                    AACPLUS_TIMEDATASIZE + \
                                    AACPLUS_OUTBUF_SIZE + \
                                    AACPLUS_EXTRA_BUF_SIZE + \
                                    AACPLUS_INBUF_SIZE)

enum {
    UNKNOWN_FORMAT=0,
    ADIF_FORMAT,
    ADTS_FORMAT
};

typedef struct {
    unsigned int BitRate;
    unsigned short SampleRate;
    unsigned short HeaderType;
    unsigned short nChannel;
    unsigned int   OutSamples;
    unsigned int   NotSupport;
} AACPLUSFileInfo;

MMP_ERR MMPF_PreDecAacPlusFrame(void);
extern void MMPF_StopAacPlusDec(void);
extern void MMPF_StartAacPlusDec(void);
extern void MMPF_ResumeAacPlusDec(void);
extern void MMPF_PauseAacPlusDec(void);
extern void MMPF_GetAacPlusInfo(AACPLUSFileInfo* info);
extern unsigned int MMPF_GetAACPLUSDecFramesInByte(void);
extern void MMPF_DecodeAacplusFrame(int decoder);
extern void MMPF_GetAacplusSpectrum(void);
extern MMP_ULONG MMPF_GetAACPLUSPlayTime(void);
#if (AUDIO_PREVIEW_SUPPORT == 1)
extern MMP_ERR MMPF_StartAacplusPreview(void);
extern MMP_ERR MMPF_DecodeAacplusForPreview(void);
#endif

typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned char u_char;

#if (VAAC_P_EN)
typedef struct {
    unsigned short rd_index;
    unsigned short wr_index;
    unsigned int sample_cnt;
    unsigned int sample_rate;
    unsigned int current_time;
    unsigned int frame_time;
    unsigned int dummy_wr_cnt;
    unsigned int dummy_rd_cnt;
    unsigned int InitSRC;
    unsigned int time[AAC_TIME_BUFFER_NUM];
} AAC_TIME_HANDLE;
#endif

#ifdef MDTV_FW
typedef struct {
    short rd_index;
    short wr_index;
    short int_cnt;
    MMP_ULONG64 time[6];
    MMP_ULONG64 time_scale;
    MMP_ULONG64 current_time;
} AACPLUS_TIME_HANDLE;
#endif /* MDTV_FW */

#endif
