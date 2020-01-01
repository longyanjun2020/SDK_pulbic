//==============================================================================
//
//  File        : mmpf_pcmencapi.h
//  Description : INCLUDE File for Live PCM encoder
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_PCMENCAPI_H_
#define _MMPF_PCMENCAPI_H_

//==============================================================================
//
//                              OPTIONS
//
//==============================================================================

#define DEBUG_LIVE_PCM          (0) // 1: dump PCM output frames for debug

#if (DEBUG_LIVE_PCM)
    #define DUMP_LIVE_PCM_SIZE  (320000*2)
#endif

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

/* Config live input ring buffer that convey RawPCM sample,
so use sample as unit*/
#define LIVE_PCM_FRAME_SAMPLE   (512)  // 256 samples per channel
#define LIVE_PCM_INBUF_FRM_CNT  (20)    // 20 frames
#define LIVE_PCM_INBUF_SIZE     (LIVE_PCM_FRAME_SAMPLE * LIVE_PCM_INBUF_FRM_CNT)

/* Config live output ring buffer that may convey compressed audio format like G.711/AAC or RawPCM,
so use byte as unit*/
#define LIVE_PCM_OUT_FRAME_SAMPLE       LIVE_PCM_FRAME_SAMPLE//(512)
#define LIVE_PCM_OUT_INBUF_FRM_CNT      (20)    // 20 frames
#define LIVE_PCM_OUTBUF_SIZE            (LIVE_PCM_OUT_FRAME_SAMPLE * LIVE_PCM_OUT_INBUF_FRM_CNT * 2)
#define LIVE_PCM_CB_OVER_THRESHOLD      (1024)

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

extern void MMPF_LivePCM_Init(void);
extern AUTL_RINGBUF *MMPF_LivePCM_OutRingBufHandle(void);
extern MMP_ULONG MMPF_LivePCM_Enc(void);
extern MMP_ULONG MMPF_LivePCM_GetFrameSize(void);

#endif //_MMPF_PCMENCAPI_H_