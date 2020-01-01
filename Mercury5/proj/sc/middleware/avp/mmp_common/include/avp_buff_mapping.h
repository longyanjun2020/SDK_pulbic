////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
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


#ifndef BUFFERR_MAPPING_H
#define BUFFERR_MAPPING_H

#include <stdint.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))


/*
*  platform dependent include headers
*/
#include "avp_platform_buff_mapping.h"

// ******************************************************************
//                  common part of mmp memory usage
// ******************************************************************
#define DMX_THREAD_STACK_SIZE           (6*1024)
#define AUDIO_THREAD_STACKSIZE          (10*1024)           //notification thread
#define VO_THREAD_STACK                 (4*1024)
#define VD_THREAD_STACK                 (20*1024)
#define OPEN_THREAD_STACK_SIZE          (10*1024)
#define VO_DISPLAY_BUF_CNTS              2


#ifdef SUPPORT_KMV
#define KMV_RECONSTRUCT_FRAME           (384*360)
#define KMV_UPSAMPLE_FRMAE              (320*360)
#define KMV_MAPPBUFF                    (396)
#define SRAM_DRAM_KING_FRAME_BUF_SIZE   (160*1024*3) //QVGA 3 frames (384*280)+(384*136)
#define SRAM_DRAM_KING_SPEED_BUF_SIZE   (640*1024)   //QVGA 4 frames (384*280)+(384*136)
#define SRAM_DRAM_KING_HVGA_FRAME_SIZE  (600*1024)   //HVGA 2 frames (512*352)
#define SRAM_DRAM_KING_3DLR_FRAME_SIZE  (1024*1024)  //960x320 2 frames (992*352)
#else
#define KMV_RECONSTRUCT_FRAME           (0)
#define KMV_UPSAMPLE_FRMAE              (0)
#define KMV_MAPPBUFF                    (0)
#endif


#ifdef SUPPORT_SUBTITLE
#define SRAM_DRAM_SUBTITLE_BUFSIZE      (8192+720*576*4)
#define SUBTITLE_RINBUF_SIZE            (256)
#else
#define SRAM_DRAM_SUBTITLE_BUFSIZE      (0)
#define SUBTITLE_RINBUF_SIZE            (0)
#endif

#ifdef SUPPORT_KMV
#define PLAYER_CTXT_SIZE                (6*1024)
#else
#define PLAYER_CTXT_SIZE                (5*1024)
#endif

#define PCM_BUFFER_SIZE                 (8*1024)
#define VIDEC_RV_TABLE_SIZE             (100*1024)

#define MAX_VO_QUEUE_BUF_SIZE           (3*1024)

#define COMMON_DYNAMIC_DRAM             (DMX_THREAD_STACK_SIZE+ \
                                        AUDIO_THREAD_STACKSIZE+ \
                                        VO_THREAD_STACK+ \
                                        VD_THREAD_STACK+ \
                                        SRAM_DRAM_SUBTITLE_BUFSIZE+ \
                                        SUBTITLE_RINBUF_SIZE+ \
                                        PLAYER_CTXT_SIZE+ \
                                        PCM_BUFFER_SIZE+ \
                                        VIDEC_RV_TABLE_SIZE+ \
                                        MAX_VO_QUEUE_BUF_SIZE+ \
                                        KMV_RECONSTRUCT_FRAME+ \
                                        KMV_UPSAMPLE_FRMAE+ \
                                        KMV_MAPPBUFF)

#define TOTAL_DYNAMIC_DRAM              (PLATFORM_DEPENDENT_DYNAMIC_DRAM + COMMON_DYNAMIC_DRAM) //ms_malloc

#define TOTAL_PLAYER_DRAM               TOTAL_DYNAMIC_DRAM


// ******************************************************************************
//                      MAP memory usage
// ******************************************************************************
#define AUDPLAY_BUF_SIZE                (180*1024)
#define AUDIO_INFO_BUF_SIZE             (40*1024)

#define AMR_IIS_BUFSIZE                 (16*1024)
#define AMR_THREAD_STACK_SIZE           (26*1024)
#define AMRPLAY_HEAPSIZE                (30500)
#define AMRPLAY_READSIZE                (1548)
#define AMRPLAY_DATABUFSIZE             (2048)
#define AMRPLAY_SOURCEBUFSIZE           (4*1024)
#define AMRPLAY_ALRAM_STACK_SIZE        (2048)
#define AMRPLAY_SURROUND_BUFSIZE        (1152)
#define AMRPLAY_READ_STACK_SIZE         (2048)
#define AMRPLAY_PCM_OUTPUT_SIZE         (640)
#define AMRPLAY_DATA_COPY_SIZE          (32+6)

#define AMRWBDEC_IIS_BUFSIZE            (16*1024)
#define AMRWBDEC_SRAM_HEAP_SIZE         (4*1024)
#define AMRWBDEC_SDRAM_HEAP_SIZE        (4*1024)
#define AMRWBDEC_SOURCEBUFSIZE          (1024*4)

#define AMRWBDEC_ALRAM_STACK_SIZE       2048
#define AMRWBDEC_READ_STACK_SIZE        2048
#define AMRWBDEC_SURROUND_BUFSIZE       1152
#define AMRWBDEC_PCM_OUTPUT_SIZE        (320*2*2)

#define AAC_IIS_BUFSIZE                 (32*1024)
#define AAC_THREAD_STACK_SIZE           (20*1024)
#define AACPLAY_HEAPSIZE                (25*1024)
#define AACPLAY_READSIZE                (1548)
#define AACPLAY_DATABUFSIZE             (2048)
#define AACPLAY_SOURCEBUFSIZE           (4*1024)
#define AACPLAY_ALRAM_STACK_SIZE        (2048)
#define AACPLAY_SURROUND_BUFSIZE        (1152)
#define AACPLAY_READ_STACK_SIZE         (2048)
#define AACPLAY_PCM_OUTPUT_SIZE         (4096)
#define AACPLAY_DATA_COPY_SIZE          (0)

#define AAC_GETINFBUFSIZE               (1548)
#define AAC_GETINFREADSIZE              (1548)



#define WAV_IIS_BUFSIZE                 (30*1024)
#define WAV_PLAYSTACKSIZE               (10*1024)
#define WAV_ALRAM_STACK_SIZE            (2048)
#define WAV_PLAYTHREADSTACKSIZE         (2100)
#define WAV_READSTACKSIZE               (2100)
#define WAV_STREAMBUFSIZE               (4080)
#define WAV_CONVERTBUFSIZE              (10884)
#define WAV_SURROUND_BUFSIZE            (1152)
#define WAV_READSTREAMBUFSIZE           (36*1024) //should be multiple of WAVFILE_READBYTES
#define WAV_PARSERSTREAMBUFSIZE         (1024)
#define WAVPLAY_DATA_COPY_SIZE          (4080)
//MP3

#define MP3PLAY_IIS_BUFSIZE             (24*1024)
#define MP3PLAY_THREAD_STACK_SIZE       (26*1024)
#define MP3PLAY_HEAPSIZE                (30500)
#define MP3PLAY_READSIZE                (1548)
#define MP3PLAY_DATABUFSIZE             (2048)
#define MP3PLAY_SOURCEBUFSIZE           (4*1024)
#define MP3PLAY_ALRAM_STACK_SIZE        (2048)
#define MP3PLAY_SURROUND_BUFSIZE        (1152)
#define MP3PLAY_READ_STACK_SIZE         (2048)
#define MP3PLAY_DATA_COPY_SIZE          0  //MP3PLAY_INPUT_BUFSIZE, 0



//#define MP3PLAY_IIS_BUFSIZE           (1152*4*8)     //(1024*30) // (5120+1024)
#define MP3PLAY_MAINDATA_BUFSIZE        (1024*3)
#define MP3PLAY_READDATA_BUFSIZE        (1024*6) /*read how many data from SD card each time*/
#define MP3PLAY_PLAYINST_BUFSIZE        (512)   //128
#define MP3DECODER_OVERLAY_BUFSIZE      (1152*4)
#define MP3DECODER_THREADSTACKSIZE      (10*1024)
#define MP3DECODER_INTERNALBUFSIZE      (24728)  /// 22680
#define MPWAIT_TIMER_THREADSIZE         (1600)
#define MP3PLAY_PCM_BUFSIZE             (1024*9) //4608   //(1024*3)
#define MP3PLAY_SURROUND_BUFSIZE        (1152)
//#define MP3PLAY_READ_SD_STACK_SIZE    (2*1024)
#define MP3PLAY_READDATA_BUFSIZE_CONCURRENT       (1024 * 4) /*read how many data from SD card each time*/
#define MP3PLAY_INPUT_BUFSIZE           (1024*2)
#define MP3PLAY_INPUT_DECPCM_BUFSIZE    (1024*3)
#define mp3playReadDataBufConcurrentSize          (8*1024)
#define MP3DECODER_INTERNALBUFSIZE_CONCURRENT_NEW (2*1024)
#define MP3PLAY_INPUT_BUFSIZE_NEW                 (1024*2)
#define MP3PLAY_INPUT_DECPCM_BUFSIZE_NEW          (1024*3)
#define MP3PLAY_READ_SD_STACK_SIZE      (2*1024)
#define MP3_SD_BUFFER_SIZE              (1024*20)    //(1024 * 4)



#define WMA_PARSERSTREAMBUFSIZE         (8*1024)
// ************************* END OF MAP memory usage ********************

#endif // BUFFERR_MAPPING_H

