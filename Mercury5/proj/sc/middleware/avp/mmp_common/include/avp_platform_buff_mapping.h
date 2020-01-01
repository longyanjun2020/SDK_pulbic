////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef PLATFORM_BUFF_MAPPING_H
#define PLATFORM_BUFF_MAPPING_H

// ***********************************************************
//               PLATFORM_DEPENDENT_DYNAMIC_DRAM
// ***********************************************************
#if defined(_SUPPORT_D1_) || defined(_SUPPORT_720P_)
#ifdef __NAND__
#define AUDIO_RINBUF_SIZE               (144*1024) //For 600Kb/s RM with COOK
#define VIDEO_RINBUF_SIZE               (512*1024) //For 600Kb/s RM with COOK
#else
#define AUDIO_RINBUF_SIZE               (72*1024)
#define VIDEO_RINBUF_SIZE               (200*1024)
#endif

#define MAX_RINGBUF_SIZE                (10*1024+16)
#define SRAM_DRAM_VIDEC_HBUF_SIZE       (60*1024)

#ifndef SRAM_DRAM_VIDEC_FRAME_BUF_SIZE
#define SRAM_DRAM_VIDEC_FRAME_BUF_SIZE  (2250*1024)
#endif
#define SRAM_DRAM_VIDEC_QCIF_FRAME_BUF_SIZE     (218*1024*3)
#define SRAM_DRAM_VIDEC_CIF_FRAME_BUF_SIZE      (218*1024*3)
#define SRAM_DRAM_VIDEC_nHD_FRAME_BUF_SIZE      (830*1024)
#define SRAM_DRAM_VIDEC_D1_FRAME_BUF_SIZE       SRAM_DRAM_VIDEC_FRAME_BUF_SIZE

#else // _SUPPORT_CIF_
#define AUDIO_RINBUF_SIZE               (72*1024) //For 600Kb/s RM with 44.1K sampling rate COOK
#define VIDEO_RINBUF_SIZE               (200*1024) //For 600Kb/s RM with COOK

#define SRAM_DRAM_VIDEC_HBUF_SIZE       (80*1024)
#define SRAM_DRAM_VIDEC_FRAME_BUF_SIZE  (218*1024*3) //288x352 and CIF 3 frames, QVGA 4 frames
#define MAX_RINGBUF_SIZE                (10*1024 + 16) // Ernie + 16 to workaround for sys_ringbuffer full case (pwrite != pread)
#endif

#define QCIF_AUDIO_RINBUF_SIZE          (60*1024)
#define QCIF_VIDEO_RINBUF_SIZE          (100*1024)
#define MJPG_VIDEO_RINBUF_SIZE          (400*1024)
#define HD1080_ROW_VIDEO_RINGBUF_SIZE   (400*1024)

// ---------- dmx_heap_buffer_size ------------------
#define MP4DMX_HEAP_BUFFER_SIZE         (25*1024)    // it should be 25k for PR174686
#define RMDMX_HEAP_BUFFER_SIZE          (8*1024)
#define CMMBDMX_HEAP_BUFFER_SIZE        (0)
#define MP2PSDMX_HEAP_BUFFER_SIZE       (0)
#ifdef TS_DEMUX
#define TSDMX_HEAP_BUFFER_SIZE          (36*1024)
#else
#define TSDMX_HEAP_BUFFER_SIZE          (0)
#endif
#define AVIDMX_HEAP_BUFFER_SIZE         (20*1024)
#define FLVDMX_HEAP_BUFFER_SIZE         (20*1024)
#define MKVDMX_HEAP_BUFFER_SIZE         (20*1024)
#define ASFDMX_HEAP_BUFFER_SIZE         (20*1024)

#define MAX_DMX_HEAP_BUFFER_SIZE        MAX(MP4DMX_HEAP_BUFFER_SIZE, \
                                        MAX(RMDMX_HEAP_BUFFER_SIZE, \
                                        MAX(CMMBDMX_HEAP_BUFFER_SIZE, \
                                        MAX(MP2PSDMX_HEAP_BUFFER_SIZE, \
                                        MAX(FLVDMX_HEAP_BUFFER_SIZE, \
                                        MAX(TSDMX_HEAP_BUFFER_SIZE, \
                                        MAX(AVIDMX_HEAP_BUFFER_SIZE, MKVDMX_HEAP_BUFFER_SIZE)))))))

#define MP3_DRAM_HEAP_SIZE              (30*1024)
#define HEAAC_SRAM_HEAP_SIZE            0

#ifdef SUPPORT_LCAAC_ONLY
#define HEAAC_DRAM_HEAP_SIZE            (30*1024)
#else
#define HEAAC_DRAM_HEAP_SIZE            (130*1024)
#endif

#define COOK_DECBUF_SIZE                (30*1024)

#ifdef AC3_PLAYER
#define AC3_DECBUF_SIZE                 (24*1024)
#else
#define AC3_DECBUF_SIZE                 0
#endif

#ifdef WMA_PLAYER
#define WMA_DRAM_HEAP_SIZE              (69*1024)
#else
#define WMA_DRAM_HEAP_SIZE              0
#endif

#define AMR_DECORDER_HEAP               (5*1024)
#define SW_MIXER_BUFFER_SIZE            0
#define AUD_DMA_BUF_SIZE                (32 * 1024)

#define MAX_AUDIO_HEAP_BUFFER_SIZE      MAX(MP3_DRAM_HEAP_SIZE, \
                                        MAX((HEAAC_DRAM_HEAP_SIZE), \
                                        MAX(WMA_DRAM_HEAP_SIZE, \
                                        MAX(COOK_DECBUF_SIZE, \
                                        MAX(AC3_DECBUF_SIZE, AMR_DECORDER_HEAP)))))

#ifdef SUPPORT_ASYNCIO
#define STREAM_READ_BUF_SIZE            (1024)
#else
#ifndef STREAM_READ_BUF_SIZE
#define STREAM_READ_BUF_SIZE            (512)
#endif
#endif

#define VO_OUTPUT_BUF_CNTS              4

#define PLATFORM_DEPENDENT_DYNAMIC_DRAM  (AUDIO_RINBUF_SIZE + \
                                          VIDEO_RINBUF_SIZE + \
                                          SRAM_DRAM_VIDEC_HBUF_SIZE + \
                                          SRAM_DRAM_VIDEC_FRAME_BUF_SIZE + \
                                          MAX_RINGBUF_SIZE + \
                                          MAX_DMX_HEAP_BUFFER_SIZE + \
                                          STREAM_READ_BUF_SIZE + \
                                          AUD_DMA_BUF_SIZE)
#endif // PLATFORM_BUFF_MAPPING_H
