#ifndef _MMPF_AUDIO_CTL_H_
#define _MMPF_AUDIO_CTL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "config_fw.h"
#include "mmp_aud_inc.h"

#if (AUDIO_AMR_R_EN)
#include "mmpf_amrencapi.h"
#endif
#if (AUDIO_AAC_R_EN)
#include "mmpf_aacencapi.h"
#endif
#if (VADPCM_R_EN)
#include "mmpf_adpcmencapi.h"
#endif
#if (WAV_R_EN)||(VPCM_R_EN)
#include "mmpf_wavencapi.h"
#endif
#if (AUDIO_MP3_R_EN)
#include "mmpf_mp3encapi.h"
#endif
#if (AUDIO_AMR_P_EN)
//#include "mmpf_amrdecapi.h"
#endif
#if (WAV_P_EN)||(VWAV_P_EN)
#include "mmpf_wavdecapi.h"
#endif
#if (AUDIO_MP3_P_EN)
#include "mmpf_mp3api.h"
#endif
#if (AUDIO_AAC_P_EN)
#include "mmpf_aacplusdecapi.h"
#endif
#if (RA_EN)||(VRA_P_EN)
//#include "mmpf_radecapi.h"
#endif
#if (OGG_EN)
//#include "mmpf_oggdecapi.h"
#endif
#if (WMAPRO10_EN)||(VWMA_P_EN)
//#include "mmpf_wmaprodecapi.h"
#endif
#if (FLAC_P_EN)
//#include "mmpf_flacdecapi.h"
#endif
#if (MP3HD_P_EN)
//#include "mmpf_mp3hdapi.h"
#endif
#if (WNR_EN||NR_EN)&&((AUDIO_R_EN)||(VIDEO_R_EN))
#include "mmpf_wnr.h"
#include "mmpf_nr.h"
#endif
#if (G711_MU_R_EN)
#include "mmpf_g711encapi.h"
#endif
#if (LIVE_PCM_R_EN)
#include "mmpf_pcmencapi.h"
#endif

//==============================================================================
//
//                              MACRO DEFINE (BUFFER SIZE)
//
//==============================================================================

/* Audio encode buffer size */
#if (AUDIO_AMR_R_EN)
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  AMRENC_BUFFER_SIZE
#endif

#if (VADPCM_R_EN)
#ifdef AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF
    #if (ADPCMENC_BUFFER_SIZE > AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  ADPCMENC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  ADPCMENC_BUFFER_SIZE
#endif
#endif

#if (WAV_R_EN)
#ifdef AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF
    #if (WAVENC_BUFFER_SIZE > AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  WAVENC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  WAVENC_BUFFER_SIZE
#endif
#endif

#if (AUDIO_MP3_R_EN)
#ifdef AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF
    #if (MP3ENC_BUFFER_SIZE > AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  MP3ENC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  MP3ENC_BUFFER_SIZE
#endif
#endif

#if (AUDIO_AAC_R_EN)
#ifdef AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF
    #if (AACENC_BUFFER_SIZE > AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  AACENC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF  AACENC_BUFFER_SIZE
#endif
#endif

/* Audio decode buffer size */
#if (AUDIO_AMR_P_EN)
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  AMRDEC_BUFFER_SIZE
#endif

#if (WAV_P_EN)||(VWAV_P_EN)
#ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (WAVDEC_BUFFER_SIZE > AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  WAVDEC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  WAVDEC_BUFFER_SIZE
#endif
#endif

#if (AUDIO_MP3_P_EN)
#ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (MP3DEC_BUFFER_SIZE > AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  MP3DEC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  MP3DEC_BUFFER_SIZE
#endif
#endif

#if (AUDIO_AAC_P_EN)
#ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (AACPLUSDEC_BUFFER_SIZE > AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  AACPLUSDEC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  AACPLUSDEC_BUFFER_SIZE
#endif
#endif

#if (RA_EN)||(VRA_P_EN)
#ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (RADEC_BUFFER_SIZE > AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  RADEC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  RADEC_BUFFER_SIZE
#endif
#endif

#if (OGG_EN)
#ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (OGGDEC_BUFFER_SIZE > AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  OGGDEC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  OGGDEC_BUFFER_SIZE
#endif
#endif

#if (WMAPRO10_EN)||(VWMA_P_EN)
#ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (WMAPRODEC_BUFFER_SIZE > AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  WMAPRODEC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  WMAPRODEC_BUFFER_SIZE
#endif
#endif

#if (FLAC_P_EN)
#ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (FLACDEC_BUFFER_SIZE > AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  FLACDEC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  FLACDEC_BUFFER_SIZE
#endif
#endif

#if (MP3HD_P_EN)
#ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #if (MP3HDDEC_BUFFER_SIZE > AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF)
    #undef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  MP3HDDEC_BUFFER_SIZE
    #endif
#else
    #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF  MP3HDDEC_BUFFER_SIZE
#endif
#endif

/* Audio record effect buffer size */
#if ((AUDIO_R_EN)||(VIDEO_R_EN))
    #if (WNR_EN == 0)
        #ifdef WNR_WORKBUF_SIZE
            #undef WNR_WORKBUF_SIZE
            #define WNR_WORKBUF_SIZE (0)
        #else
            #define WNR_WORKBUF_SIZE (0)
        #endif
    #endif
    #if (NR_EN == 0)
        #ifdef NR_WORKBUF_SIZE
            #undef NR_WORKBUF_SIZE
            #define NR_WORKBUF_SIZE (0)
        #else
            #define NR_WORKBUF_SIZE (0)
        #endif
    #endif
    #define AUDIO_ENC_TOTAL_WORKBUF_SIZE             (AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF + WNR_WORKBUF_SIZE + NR_WORKBUF_SIZE) //       (AUDIO_ENC_SIZEOF_TOTAL_WORKING_BUF + WNR_WORKBUF_SIZE + NR_WORKBUF_SIZE)
#endif //((AUDIO_R_EN)||(VIDEO_R_EN))
#if (AUDIO_DEC_ENC_SHARE_WB)
    #ifdef AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
        #if (AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF < AUDIO_ENC_TOTAL_WORKBUF_SIZE)
        #define AUDIO_ENC_SIZEOF_TOTAL_FINAL_WORKING_BUF    AUDIO_ENC_TOTAL_WORKBUF_SIZE
        #else
        #define AUDIO_ENC_SIZEOF_TOTAL_FINAL_WORKING_BUF    AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF
        #endif
    #else
          #define AUDIO_DEC_SIZEOF_TOTAL_WORKING_BUF 0
          #define AUDIO_ENC_SIZEOF_TOTAL_FINAL_WORKING_BUF    AUDIO_ENC_TOTAL_WORKBUF_SIZE
    #endif
#else
    #define AUDIO_ENC_SIZEOF_TOTAL_FINAL_WORKING_BUF        AUDIO_ENC_TOTAL_WORKBUF_SIZE
#endif

/* Audio live streaming buffer size */
#if (G711_MU_R_EN)
#ifdef AUDIO_LIVE_SIZEOF_IN_BUF
    #if ((G711_INBUF_SIZE << 1) > AUDIO_LIVE_SIZEOF_IN_BUF)
    #undef AUDIO_LIVE_SIZEOF_IN_BUF
    #define AUDIO_LIVE_SIZEOF_IN_BUF    (G711_INBUF_SIZE << 1)
    #endif
#else
    #define AUDIO_LIVE_SIZEOF_IN_BUF    (G711_INBUF_SIZE << 1)
#endif
#ifdef AUDIO_LIVE_SIZEOF_OUT_BUF
    #if (G711_OUTBUF_SIZE > AUDIO_LIVE_SIZEOF_OUT_BUF)
    #undef AUDIO_LIVE_SIZEOF_OUT_BUF
    #define AUDIO_LIVE_SIZEOF_OUT_BUF   G711_OUTBUF_SIZE
    #endif
#else
    #define AUDIO_LIVE_SIZEOF_OUT_BUF   G711_OUTBUF_SIZE
#endif
#endif

#if (LIVE_PCM_R_EN)
#ifdef AUDIO_LIVE_SIZEOF_IN_BUF
    #if (LIVE_PCM_INBUF_SIZE > AUDIO_LIVE_SIZEOF_IN_BUF)
    #undef AUDIO_LIVE_SIZEOF_IN_BUF
    #define AUDIO_LIVE_SIZEOF_IN_BUF    (LIVE_PCM_INBUF_SIZE << 1)
    #endif
#else
    #define AUDIO_LIVE_SIZEOF_IN_BUF    (LIVE_PCM_INBUF_SIZE << 1)
#endif
#ifdef AUDIO_LIVE_SIZEOF_OUT_BUF
    #if (LIVE_PCM_OUTBUF_SIZE > AUDIO_LIVE_SIZEOF_OUT_BUF)
    #undef AUDIO_LIVE_SIZEOF_OUT_BUF
    #define AUDIO_LIVE_SIZEOF_OUT_BUF   LIVE_PCM_OUTBUF_SIZE
    #endif
#else
    #define AUDIO_LIVE_SIZEOF_OUT_BUF   LIVE_PCM_OUTBUF_SIZE
#endif
#endif

#if (LIVE_AAC_R_EN)
#ifdef AUDIO_LIVE_SIZEOF_IN_BUF
#else
    #define AUDIO_LIVE_SIZEOF_IN_BUF    (0)
#endif
#ifdef AUDIO_LIVE_SIZEOF_OUT_BUF
    #if (LIVE_AAC_OUTBUF_SIZE > AUDIO_LIVE_SIZEOF_OUT_BUF)
    #undef AUDIO_LIVE_SIZEOF_OUT_BUF
    #define AUDIO_LIVE_SIZEOF_OUT_BUF   LIVE_AAC_OUTBUF_SIZE
    #endif
#else
    #define AUDIO_LIVE_SIZEOF_OUT_BUF   LIVE_AAC_OUTBUF_SIZE
#endif
#endif

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

// Decoder Type
#define AMR                             (0x0)
#define MP3                             (0x1)
#define AAC                             (0x2)
#define MIDI                            (0x3)
#define AACPLUS                         (0x4)
#define WMA                             (0x5)
#define WMAPRO                          (0x7)
#define OGG                             (0x8)
#define RA                              (0x9)
#define FLAC                            (0xA)
#define MP12                            (0xB)
#define WAVE                            (0x10)

// Audio Volume Smooth
#define AUDIO_NO_SMOOTH_OP              (0x00)
#define AUDIO_SMOOTH_UP                 (0x01)
#define AUDIO_SMOOTH_DOWN               (0x02)

// MIDI Play Mode
#define MIDI_FILE_MODE                  (0)
#define MIDI_STREAM_MODE                (1)

// Audio Record Event
#define EVENT_FIFO_OVER_THRESHOLD       (0x0002)
#define EVENT_STOP_ENCODER              (0x0004)
#define EVENT_STREAM_OVER_THRESHOLD     (0x0008)
#define EVENT_TRANSCODE_OVER_THRESHOLD  (0x0020)

// Audio Play Event
#define EVENT_DECODE_AACPLUS            (0x0001)
#define EVENT_DECODE_WMA                (0x0002)
#define EVENT_DECODE_WAV                (0x0008)
#define EVENT_DECODE_AMR                (0x0010)
#define EVENT_DECODE_MP3                (0x0020)
#define EVENT_DECODE_AAC                (0x0040)
#define EVENT_DECODE_MIDI               (0x0080)
#define EVENT_DECODE_OGG                (0x0400)
#define EVENT_DECODE_RA                 (0x0800)
#define EVENT_SBC_TRIGGER_INT           (0x1000)
#define EVENT_WAV_TRIGGER_INT           (0x2000)
#define EVENT_SBC_FILLBUF_INT           (0x4000)
#define EVENT_DECODE_AC3                (0x8000)
#define EVENT_DECODE_FLAC               (0x0100)

// FIFO Trigger Threshold
//#define MIXER_FIFO_WRITE_THRESHOLD    (4096)
#define MP3_I2S_FIFO_WRITE_THRESHOLD    (128)
#define WMA_I2S_FIFO_WRITE_THRESHOLD    (128)
#define OGG_I2S_FIFO_WRITE_THRESHOLD    (128)
#define AAC_I2S_FIFO_WRITE_THRESHOLD    (128)
#define AC3_I2S_FIFO_WRITE_THRESHOLD    (128)
#define AMR_I2S_FIFO_WRITE_THRESHOLD    (80)
#define RA_I2S_FIFO_WRITE_THRESHOLD     (128)
#define WAV_I2S_FIFO_WRITE_THRESHOLD    (64)
#define FLAC_I2S_FIFO_WRITE_THRESHOLD   (128)

// Audio Common Event
#define AUDIO_EVENT_EOF                 (0x00000001)

#define AUDIO_DMA_WORKING_BUF_SIZE      (1024 * 48 * 2 * 4)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_AUDIO_DATA_FLOW
{
    AFE_FIFO_TO_DAC = 0x1,  ///< AFE FIFO to AFE DAC
    ADC_TO_AFE_FIFO,        ///< AFE ADC to AFE FIFO
    ADC_TO_I2S0_FIFO,       ///< AFE ADC to I2S0 FIFO
    I2S0_FIFO_TO_SDO,       ///< I2S0 FIFO to I2S output
    SDI0_TO_AFE_FIFO,       ///< I2S0 input to AFE FIFO
    SDI_TO_I2S0_FIFO,       ///< I2S input to I2S0 FIFO
    ADC_TO_I2S1_FIFO,       ///< AFE ADC to I2S1 FIFO
    I2S1_FIFO_TO_SDO,       ///< I2S1 FIFO to I2S output
    I2S2_FIFO_TO_SDO,       ///< I2S2 FIFO to I2S output
    SDI1_TO_AFE_FIFO,       ///< I2S1 input to AFE FIFO
    SDI_TO_I2S1_FIFO,       ///< I2S input to I2S1 FIFO
    I2S2_FULL_DUPLEX,       ///< I2S input to I2S2 FIFO
    I2S1_FULL_DUPLEX,       ///< I2S input to I2S2 FIFO
    I2S0_FULL_DUPLEX,       ///< I2S input to I2S2 FIFO
    AFE_FULL_DUPLEX,        ///< I2S input to I2S2 FIFO
    SDI_TO_I2S2_RX_FIFO,    ///< I2S input to I2S2 FIFO
    SDI_TO_I2S1_RX_FIFO,    ///< I2S input to I2S1 FIFO
    SDI_TO_I2S0_RX_FIFO,    ///< I2S input to I2S0 FIFO
    I2S2_TX_FIFO_TO_SDO,    ///< I2S output to I2S2 FIFO
    I2S1_TX_FIFO_TO_SDO,    ///< I2S output to I2S1 FIFO
    I2S0_TX_FIFO_TO_SDO,    ///< I2S output to I2S0 FIFO
    ADC_TO_AFE_RX_FIFO,     ///< ADC input to Rx FIFO
    AFE_TX_FIFO_TO_DAC,     ///< DAC output to Tx FIFO
    MMPF_AUDIO_MAX_FLOW
} MMPF_AUDIO_DATA_FLOW;

//==============================================================================
//
//                              TYPE DEFINE
//
//==============================================================================

typedef void AudioPlayerCallBackFunc(void *VidContext, MMP_ULONG flag1, MMP_ULONG flag2);
#if (GAPLESS_EN == 1)
typedef void GaplessNextFileCallBackFunc(MMP_ULONG handle);
#endif

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _AudioCallBackInfo {
    AudioPlayerCallBackFunc *callBackFunction;
    void            *context;
} AudioCallBackInfo;

typedef struct mp4AudioSpecificConfig {
    /* Audio Specific Info */
    unsigned char   objectTypeIndex;
    unsigned char   samplingFrequencyIndex;
    unsigned long   samplingFrequency;
    unsigned char   channelsConfiguration;

    /* GA Specific Info */
    unsigned char   frameLengthFlag;
    unsigned short  sample256_time;
} mp4AudioSpecificConfig;

typedef struct _AUDIO_DEC_OUTBUF_HANDLE {
    short           rd_index;
    short           wr_index;
    unsigned int    total_rd;
    unsigned int    total_wr;
} AUDIO_DEC_OUTBUF_HANDLE;

typedef struct _MMPF_AUDIO_RINGBUF {
    MMP_ULONG       ulBufStart;
    MMP_ULONG       ulBufSize;
    MMP_ULONG       ulReadPtr;
    MMP_ULONG       ulWritePtr;
    MMP_ULONG       ulReadPtrHigh;
    MMP_ULONG       ulWritePtrHigh;
} MMPF_AUDIO_RINGBUF;

typedef struct _MMPF_AUDIO_INTIME_HANDLE {
    MMP_ULONG ulTimeCnt;           // in ms
    MMP_ULONG ulSampleCnt;         // modular samplerate
} MMPF_AUDIO_INTIME_HANDLE;


//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern int *glAudioEncWorkingBuf;
extern int *glAudioDecWorkingBuf;

#if (LIVE_AAC_R_EN)||(G711_MU_R_EN)||(LIVE_PCM_R_EN)
extern int glAudioLiveInBuf[AUDIO_LIVE_SIZEOF_IN_BUF >> 2];
extern int glAudioLiveOutBuf[AUDIO_LIVE_SIZEOF_OUT_BUF >> 2];
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_ERR     MMPF_Audio_EncAudFrame(MMP_USHORT usAudEncFormat);
MMP_ERR     MMPF_Audio_SetAmrEncodeMode(unsigned short mode);
MMP_ERR     MMPF_Audio_SetStreamLength(unsigned int stream_length);
MMP_ERR     MMPF_SetAudioPlayReadPtr(void);
MMP_ERR     MMPF_Audio_SetupRender(MMP_USHORT usFifoThreshold, MMP_ULONG ulSamplerate);
MMP_ERR     MMPF_Audio_EnableRender(void);
MMP_ERR     MMPF_Audio_DisableRender(void);
MMP_ERR     MMPF_Audio_EnableCapture(MMP_USHORT usFifoThreshold, MMP_ULONG ulSamplerate);
MMP_ERR     MMPF_Audio_DisableCapture(void);
MMP_ERR     MMPF_Audio_InitializeCodec(MMPF_AUDIO_DATA_FLOW path, MMP_ULONG samprate);
MMP_ERR     MMPF_SetAudioRecWritePtr(void);
MMP_ERR     MMPF_Audio_SetSpectrumBuf(MMP_ULONG buf_addr);
MMP_ERR     MMPF_UpdateAudioPlayReadPtr(void);
MMP_ERR     MMPF_UpdateAudioPlayWritePtr(void);
MMP_ERR     MMPF_UpdateAudioRecReadPtr(void);
MMP_ERR     MMPF_Audio_SetRecIntThreshold(MMP_USHORT threshold);
MMP_ERR     MMPF_Audio_SetPlayIntThreshold(MMP_USHORT threshold);
MMP_ERR     MMPF_Audio_SetVoiceInPath(MMP_ULONG path);
MMP_ERR     MMPF_Audio_SetVoiceOutPath(MMP_ULONG path);
MMP_BOOL    MMPF_Audio_GetDACPowerOnStatus(void);
MMP_BOOL    MMPF_Audio_GetADCPowerOnStatus(void);
MMP_ERR     MMPF_Audio_PowerOnDAC(MMP_ULONG samplerate);
MMP_ERR     MMPF_Audio_PowerOnADC(MMP_ULONG samplerate);
MMP_ERR     MMPF_Audio_SetPLL(MMP_AUD_INOUT_PATH ubPath, MMP_ULONG ulSamplerate);
MMP_ERR     MMPF_Audio_SetDACFreq(MMP_ULONG samplerate);
MMP_ERR     MMPF_Audio_SetADCFreq(MMP_ULONG samplerate);
MMP_ERR     MMPF_Audio_PowerDownDAC(MMP_BOOL bPowerDownNow);
MMP_ERR     MMPF_Audio_PowerDownADC(void);
MMP_ERR     MMPF_Audio_PowerDownCodec(void);
MMP_ERR     MMPF_PostPlayAudioOp(void);
#if (VMP3_P_EN)
MMP_ERR     MMPF_Audio_UpdateVMP3Time(MMP_ULONG ulTime);
#endif
#if (VAC3_P_EN)
MMP_ERR     MMPF_Audio_UpdateVAC3Time(MMP_ULONG ulTime);
#endif

void        MMPF_AUDIO_WaitForSync(void);
MMP_ERR     MMPF_AUDIO_GetRecWrPtrEx(MMP_ULONG *ulWrPtr, MMP_ULONG *ulWrWrap, MMP_ULONG *ulRdPtr, MMP_ULONG *ulRdWrap);

MMP_ERR     MMPF_Audio_SetMux(MMPF_AUDIO_DATA_FLOW path, MMP_BOOL bEnable);
MMP_ERR     MMPF_Audio_SetDuplexPath(MMPF_AUDIO_DATA_FLOW path, MMP_BOOL bEnable);
MMP_ERR     MMPF_Audio_SetLineInChannel(MMP_AUD_LINEIN_CH lineinchannel);
MMP_ERR     MMPF_Audio_SetPlayFormat(MMP_USHORT usFormat);
MMP_ERR     MMPF_Audio_SetEncodeFormat(MMP_USHORT usFormat);
MMP_ERR     MMPF_Audio_SetLiveEncodeParam(MMP_USHORT  usFormat,
                                          MMP_ULONG   ulInSamplerate,
                                          MMP_ULONG   ulOutSamplerate,
                                          MMP_UBYTE   ulInCh,
                                          MMP_UBYTE   ulOutCh);
MMP_ERR     MMPF_Audio_SetPlayFileName(MMP_ULONG address);
MMP_ERR     MMPF_Audio_SetPlayBuffer(MMP_ULONG ulBufStart, MMP_ULONG ulBufSize);
MMP_ERR     MMPF_Audio_SetPlayPath(MMP_UBYTE path);
MMP_ERR     MMPF_Audio_SetPlayHandshakeBuf(MMP_ULONG ulBufStart);
MMP_ERR     MMPF_Audio_GetPlayState(MMP_USHORT* usState);
MMP_ERR     MMPF_Audio_GetRecState(MMP_USHORT *usState);
MMP_ERR     MMPF_Audio_GetLiveRecState(MMP_USHORT *usState);
MMP_ERR     MMPF_Audio_SetDACDigitalGain(MMP_UBYTE gain);
MMP_ERR     MMPF_Audio_SetDACAnalogGain(MMP_UBYTE gain);
MMP_ERR     MMPF_Audio_SetADCDigitalGain(MMP_UBYTE gain, MMP_BOOL bRecordSetting);
MMP_ERR     MMPF_Audio_SetADCAnalogGain(MMP_UBYTE gain, MMP_BOOL bRecordSetting);
MMP_ERR     MMPF_Audio_SetADCMute(MMP_BOOL bMute);
MMP_ERR     MMPF_Audio_InitializePlayFIFO(MMP_USHORT usPath, MMP_USHORT usThresholdMs);
MMP_ERR     MMPF_Audio_SetRecordHeadMuteTime(MMP_ULONG ulMilliSec);
MMP_ERR     MMPF_Audio_SetRecordTailCutTime(MMP_ULONG ulMilliSec);
MMP_ERR     MMPF_Audio_EnableDummyRecord(MMP_BOOL bEnable, MMP_UBYTE ubFlag);
MMP_ERR     MMPF_Audio_SetRecordSilence(MMP_BOOL bSilence);
MMP_BOOL    MMPF_Audio_IsRecordSilence(void);
#if (VIDEO_R_EN)
MMP_ERR     MMPF_Audio_SetRecordTimeHandler(MMP_ULONG ulTime, MMP_ULONG ulSampleCnt);
#endif
MMP_ERR     MMPF_Audio_SetEncodeFormat(MMP_USHORT mode);
MMP_ERR     MMPF_Audio_SetEncodeFileName(MMP_ULONG address);
MMP_ERR     MMPF_Audio_SetEncodeBuffer(MMP_ULONG ulBufStart, MMP_ULONG ulBufSize);
MMP_ERR     MMPF_Audio_SetEncodePath(MMP_UBYTE path);
MMP_ERR     MMPF_Audio_SetEncodeHandshakeBuf(MMP_ULONG ulBufStart);
MMP_ERR     MMPF_Audio_SetEncodeLength(MMP_ULONG ulFileLimit);
MMP_ERR     MMPF_Audio_InitializeEncodeFIFO(MMP_USHORT usPath, MMP_USHORT usThresholdMs);
MMP_ERR     MMPF_Audio_GetRecordTime(MMP_ULONG *ulMilliSec);

MMP_ERR     MMPF_Audio_SetADCVolume(MMP_SHORT gain, MMP_SHORT* RealDB_INT, MMP_SHORT* RealDB_FRAC);
MMP_ERR     MMPF_AUDIO_UpdateRecWrPtr(MMP_ULONG ulSize);
MMP_ERR     MMPF_AUDIO_SetRecWrPtrWrap(MMP_ULONG ulWrap);
void        MMPF_AUDIO_SetRecWrPtrWrapWoProt(MMP_ULONG ulWrap);
MMP_ERR     MMPF_AUDIO_GetRecWrPtr(MMP_ULONG *ulPtr, MMP_ULONG *ulWrap);

#if (GAPLESS_EN == 1)
MMP_ERR     MMPF_Audio_SetGaplessEnable(MMP_BOOL bEnable, GaplessNextFileCallBackFunc *cb, MMP_ULONG param);
#endif
MMP_ERR     MMPF_Audio_GaplessTriggerCB(void);
MMP_ERR     MMPF_Audio_SetGraphicEQEnable(MMP_BOOL enable);
MMP_ERR     MMPF_Audio_SetGraphicEQBand(MMP_SHORT usFreq, MMP_SHORT usQrange, MMP_SHORT usGain);

#if (AUDIO_PREVIEW_SUPPORT == 1)
MMP_ERR     MMPF_Audio_InitializePreview(MMP_ULONG ulSampleRate);
void        MMPF_Audio_StorePreviewData(MMP_SHORT *sInbuf, MMP_ULONG ulInSamples, MMP_ULONG ulCh);
void        MMPF_Audio_SetPreviewDone(MMP_LONG lTotalSamples);
MMP_BOOL    MMPF_Audio_GetPreviewDone(void);
#endif

#endif //_MMPF_AUDIO_CTL_H_
