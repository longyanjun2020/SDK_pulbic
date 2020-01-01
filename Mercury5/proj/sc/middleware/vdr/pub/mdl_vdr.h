////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_H__
#define __MDL_VDR_H__

#define MDLVDR_HANDLE                       0xFDB97531

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

//#include "mm_types.h"
#include "vm_types.ht"
#include "mdl_vdr_api.h"

//#include "mdl_vdr_system.h"



//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Macro Definition
//-----------------------------------------------------------------------------

// REC_DRAM_STACK
#define MP4REC_DRAM_TASK_TOTAL   (MP4REC_MAIN_STACKSIZE+MP4REC_VDO_STACKSIZE+MP4REC_ADO_STACKSIZE+MP4REC_Wrt_STACKSIZE)
    #define MP4REC_MAIN_STACKSIZE       (5<<10)
    #define MP4REC_VDO_STACKSIZE         (7<<10) //(10<<10)
    #define MP4REC_ADO_STACKSIZE         (11<<10) //AMR-WB:(11<<10) AMR-NB:(7<<10)
    #define MP4REC_NOTIFY_STACKSIZE    0    // compatible to mp4rec_api.c
    #define MP4REC_Wrt_STACKSIZE          (7<<10) //(10<<10)
//    #define mp4recStackMainBuf                (Recordbuf_map->buffer[REC_DRAM_STACK]) // must at start positon
//    #define mp4recStackVBuf                     (mp4recStackMainBuf+MP4REC_MAIN_STACKSIZE)
//    #define mp4recStackABuf                     (mp4recStackVBuf+MP4REC_VDO_STACKSIZE)
//    #define mp4recStackMuxBuf                 (mp4recStackABuf+MP4REC_ADO_STACKSIZE)

// REC_DRAM_HEAP
#define MP4REC_DRAM_HEAP_TOTAL   MP4REC_HEAP_BUFSIZE
    #define MP4REC_HEAP_BUFSIZE         (50<<10)
//    #define mp4recHeapBuf                   (Recordbuf_map->buffer[REC_DRAM_HEAP])

//Use VT and VTMUX feature with more reliable memory size
#define MP4REC_VT_HEAP_BUFSIZE         (20<<10)
#define MP4REC_VTMUX_HEAP_BUFSIZE         (32<<10)

// REC_DRAM_VIDEO_ENC
#define MP4REC_DRAM_VIDEO_ENC_JPEIP_TOTAL       (MP4REC_DRAM_VIDEO_ENC_JPEIP_SHARED+MP4REC_DRAM_VIDEO_ENC_JPEIP_EXTEND)
    #define MP4REC_DRAM_VIDEO_ENC_JPEIP_SHARED  (MP4REC_LBC_BUFSIZE+MP4REC_VDO_BUFSIZE+MP4REC_VDO_BUFSIZE)
    #define MP4REC_DRAM_VIDEO_ENC_JPEIP_EXTEND   (0)
    #define MP4REC_VDO_BUFSIZE             (20*1024)
//    #define mp4recLBCBuf                            (Recordbuf_map->buffer[REC_DRAM_VIDEO_ENC_SHARED])
//    #define h263recFrameBuf                     (mp4recLBCBuf+MP4REC_LBC_BUFSIZE)

// REC_DRAM_AUDIO_ENC
#define MP4REC_DRAM_AUDIO_ENC_AMRNB_TOTAL (MP4REC_AMR_HEAP_BUFSIZE)
    #define MP4REC_AMR_HEAP_BUFSIZE  7680 //AMR-WB: (7680) AMR-NB: (6160)//(6148)
    #define MP4REC_MP3_HEAP_BUFSIZE  22000
    #define MP4REC_MP3L3_HEAP_BUFSIZE  (34*1024+512)
    #define MP4REC_WAV_HEAP_BUFSIZE   (6*1024)

// REC_DRAM_MUX_POOL_V
#define MP4REC_DRAM_MUX_MP4_POOL_V_JPEIP    (400<<10)

// REC_DRAM_MUX_POOL_A
#define MP4REC_DRAM_MUX_MP4_POOL_A_AMR      (6<<10) //AMR-WB (2<<10)
//    #define MP4REC_ADO_POOLSIZE             (Recordbuf_map->size[REC_DRAM_MUX_POOL_A])
//    #define ADO_BUF_START_PTR               (Recordbuf_map->buffer[REC_DRAM_MUX_POOL_A])
//    #define ADO_BUF_END_PTR                 (ADO_BUF_START_PTR + MP4REC_ADO_POOLSIZE)

// REC_DRAM_MUX_POOL_ATM
#define MP4REC_DRAM_MUX_MP4_POOL_ATM    (MP4REC_ATM_POOLSIZE+MP4REC_MUX_PACKSIZE_DRAM)
    #define MP4REC_ATM_POOLSIZE            (ATOM_CLUSTER_PAGE_SIZE*ATOM_CLUSTER_MAX_NUM)
#if defined(VIDEO_REC_D1_EN)
    #define MP4REC_MUX_PACKSIZE_DRAM    (256*1024)
#elif defined(CYGHWR_BIG2_TYPE_A)
    #define MP4REC_MUX_PACKSIZE_DRAM    (128*1024)
#else
    #define MP4REC_MUX_PACKSIZE_DRAM    (64*1024)
#endif
//    #define ATOM_BUF_START_PTR              (Recordbuf_map->buffer[REC_DRAM_MUX_POOL_ATM])
//    #define MUX_BUF_START_PTR               (ATOM_BUF_START_PTR+MP4REC_ATM_POOLSIZE)

// REC_SRAM_VIDEO_ENC
#define MP4REC_SRAM_VIDEO_ENC_JPEIP_TOTAL   (MP4REC_LBC_BUFSIZE+MP4REC_RLC_BUFSIZE)
    #define MP4REC_LBC_BUFSIZE              (352 * 2 * 16 * 2 )
    #define MP4REC_RLC_BUFSIZE              (2048 * 2)
//    #define mp4recLBCBuf_sram               (Recordbuf_map->buffer[REC_SRAM_VIDEO_ENC])
//    #define H263encRLCBuf                           (mp4recLBCBuf_sram+MP4REC_LBC_BUFSIZE)

// REC_SRAM_AUDIO_ENC
#define MP4REC_SRAM_AUDIO_ENC_MP3_IIS         MP4REC_MP3_IIS_BUFSIZE
    #define MP4REC_MP3_IIS_BUFSIZE                (32*1024*4)

#define MP4REC_SRAM_AUDIO_ENC_AMRNB_IIS         MP4REC_AMR_IIS_BUFSIZE
    #define MP4REC_AMR_IIS_BUFSIZE                (640*46)//, use released MP4REC_MUX_PACKSIZE//(320*72)
//    #define mp4recIISBuf                    (Recordbuf_map->buffer[REC_SRAM_AUDIO_ENC])

#define MP4REC_WAV_IIS_BUFSIZE                (16*1024*4)      ///< size of I2S if audio format is AMR-NB

// REC_SRAM_MUX
#define MP4REC_SRAM_MUX_FS                                  (MP4REC_MUX_BUFSIZE+MP4REC_MUX_PACKSIZE)
    #define MP4REC_MUX_BUFSIZE            (ATOM_CLUSTER_PAGE_SIZE)  // (20 * 1024) /* 8k+8k+9k */
    #define MP4REC_MUX_PACKSIZE         0 //(20 << 10), use DRAM instead
//    #define mp4recmuxBuf                    (Recordbuf_map->buffer[REC_SRAM_MUX])
//    #define mp4recpackBuf                    (mp4recmuxBuf+MP4REC_MUX_BUFSIZE)


// from sharebuffer.h
#if defined(MP4_RECORDER) || defined(H263_DRIVER)
#define MP4REC_SRAM_HEAP_SIZE           80*1024
#if defined(CYGHWR_BIG2_TYPE_A)
#define MP4REC_DRAM_HEAP_SIZE           900*1024
#else
#define MP4REC_DRAM_HEAP_SIZE           635*1024//820*1024
#endif
#if 0 // put back
#define MP4_REC_SDRAM  U8 _mp4recBuf_dram[MP4REC_DRAM_HEAP_SIZE]; //MP4RECODER_SDRAM    _mp4Recoder_sdram;
#define MP4_REC_SRAM   U8 _mp4recBuf_sram[MP4REC_SRAM_HEAP_SIZE];//MP4RECODER          _MP4RECODER;
#endif
#else
#define MP4_REC_SRAM
#define MP4_REC_SDRAM
#endif//defined(MP4_RECORDER)

#define REC_MEM_TYPE_M3_UNDEFINED       0
#define REC_MEM_TYPE_M3_SRAM            1
#define REC_MEM_TYPE_M3_SHARE           2
#define REC_MEM_TYPE_BB_SHARE           3
#define REC_MEM_TYPE_TEST               4

//REC Pause Resume Enable
#if defined(__SDK_SIMULATION__) || (!defined(__SMALL_ROM_32__) && !defined(__SMALL_ROM__))
#define MDL_VDR_PAUSE_EN
#endif

#define EN_PAUSE_RESUME  0  //FIXJASON, del later

#define WRITE_APPEND_SIZE 300 //Cluster Appended size limit

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

enum _recorder_buffer_mapping_ {
    REC_SRAM_VIDEO_ENC=0,
    REC_SRAM_AUDIO_ENC,
    REC_SRAM_MUX,

    RECORDER_MAX_SRAM_INDEX,

    REC_DRAM_STACK = RECORDER_MAX_SRAM_INDEX,
    REC_DRAM_HEAP,
    REC_DRAM_VIDEO_ENC_SHARED,
    REC_DRAM_AUDIO_ENC,
    REC_DRAM_MUX_POOL_V,
    REC_DRAM_MUX_POOL_A,
    REC_DRAM_MUX_POOL_ATM,
    REC_DRAM_VIDEO_ENC_EXTEND,

    RECORDER_MAX_BUFFER_INDEX
};

struct _recorder_buffer_mapping_table_ {
    U32 type[RECORDER_MAX_BUFFER_INDEX];
    U8 *buffer[RECORDER_MAX_BUFFER_INDEX];
    U32 size[RECORDER_MAX_BUFFER_INDEX];
} ;
typedef struct _recorder_buffer_mapping_table_ recorder_buffer_mapping_table;

typedef volatile struct _mp4rec_
{
    void *pmuxer;           /* mp4 muxer instance */
    void *pvenc;            /* video encoder instance */
    void *paenc;            /* audio encoder instance */
    U8   bStop;          /* stop or not? */
    U8   bNAND;     /* is reorded at SD card or NAND */
    U32 u32totaltime;   /* total duration of 3GP */
    U32 vframes;        /* encoded video frames number */
    U32 aframes;        /* encoded audio frames number */
    U16 u16RecCurAudioSize; /* the size of current encoded audio */
    U32 u32RecCurVidoeSize; /* the size of current encoded video */
    U32 u32RecTmpAtoms; /* sum the total atoms(stts/stsc/stsz/stco) size in SD */
    U32 u32RecNotWAudioSize; /* the not write size yet of recorded audio data */
    U32 u32RecAudioSize; /* total size of recorded audio data */
    U32 u32RecVidoeSize;  /* total size of recorded video data */
    U32 u32RecTotalSize; /* total size of recorded video + audio + atoms */
    U8 *u8VDORecBuf;          /* buffer address for encoded video data */
    U8   u8VdoFrmRate; /*the not write frame num of video data */
    U32 u32VErrRtl;  /* keep the error return code */
    U32 u32AErrRtl;  /* keep the error return code */

#if defined(CYGHWR_HAL_MIPS_MSTAR_SDRAM_ENABLE)
    U32 u32RecNotWVideoSize; /* the not write size yet of recorded video data */
    U8 *pVDOBufWptr; /* the next can write ptr (video data to get to write) in the ring buffer */
    U8 *pstszBuf; /* the ATOM (v_stsz) buffer ptr to save data */
    U8 *pstszWptr; /* the next can write ptr (atom data to get to write) in the ring buffer */
    U8 *pstcoBuf; /* the ATOM (v_stco) buffer ptr to save data */
    U32 u32NotWATMSize; /* the not write size yet of recorded video data */
    U32 u32PrevFrmSize;
    U32 u32PrevFrmOfst;
    U32 u32WrtSize; /* the write size of each write*/
#endif

#if 0 // Modify
    //write thread
    cyg_handle_t write_thread_hdl; /* write thread handle */
    cyg_thread write_thread_obj;/* write thread handle */
    cyg_sem_t  write_sem; /* can write semaphore */
#endif

    U8 write_done; /* indicate the audio is written done or not */
    U8 notify_end; /* indicate the ended or not */

//#if defined(XMR_REC)
#if 0 // Modify
    cyg_handle_t audio_thread_hdl; /* audio encode thread handle */
    cyg_thread audio_thread_obj; /* audio encode thread object */
#endif

    U8 *pAmrRecBuf; /* the next can enc ptr (AMR data to put and wait to write) in the ring buffer */
    U8 *pAmrBufWptr; /* the next can write ptr (AMR data to get to write) in the ring buffer */
    U8 bAudioStart; /* to sync the audio and video start point */
    U8 u8ado_edone; /* indicate the audio is encoded done or not */
//#endif
}mp4rec;

typedef struct avwrite_s
{
    U32 state;

#if 0 // Modify
    //write thread
    cyg_handle_t write_thread_hdl; /* write thread handle */
    cyg_thread write_thread_obj;/* write thread handle */
    //cyg_sem_t  write_sem; /* can write semaphore */
    //cyg_sem_t start_sem;     /* start semaphore */
    //cyg_sem_t stop_sem; /* stop semaphore */

    cyg_handle_t write_mbox_hdl;
    cyg_mbox    write_mbox;
#endif

    U32 u32WrtSize; /* the write size of each write*/
}avwrite_st;

typedef volatile struct rec_av_s
{
    U8   stop_flag;          /* stop or not? */
    U8   audio_on;  /* a flag to encode audio or not */
    U32 u32totaltime;   /* total duration of 3GP */
    U32 u32RecMaxSize;  /* maximal recording size */
    U32 u32RecMaxTime; /* maximal recording time */

    U32 err_v_flag;  /* keep the video_enc error return code */
    U32 err_a_flag;  /* keep the audio_enc error return code */
    U32 err_w_flag;  /* keep the write (muxer) error return code */

    void *pav_info;     /* information instance ptr */
    void *pvenc_inst; /* venc_st (video) instant ptr */
    void *paenc_inst; /* aenc_st (audio) instant ptr */
    void *pmux_inst; /* avmux_st instant ptr */
    void *pwrite_inst; /* avwrite_st instant ptr */

    u8  is_a_finished;
    u8  is_v_finished;
    u8  is_w_finished;

#if 0 // Modify
    //notify variables
    cyg_sem_t notify_timer_sem;
    cyg_handle_t alarm_hdl;  /* alarm thread handle */
    cyg_alarm alarm_obj;  /* alarm thread object */

    // message to main thread
    cyg_handle_t rec_mbox_hdl;
    cyg_mbox    rec_mbox;
#endif
}rec_av_st;

typedef enum
{
    FILE_UNKNOWN = 0,
    FILE_MP3 = 1,
    FILE_3GP = 2,
    FILE_JPEG = 3,
    FILE_AMR = 4,
    FILE_AAC = 5,
    FILE_BMP = 6,
    FILE_GIF = 7,
    FILE_PNG = 8,
    PCM_STREAM = 9,
    FILE_AMRWB = 10,
    FILE_MIDI = 11,
    FILE_264  = 12,
    FILE_263  = 13,
    FILE_FLV1 = 14,
    FILE_M4V  = 15,
    FILE_MP4  = 16,
    FILE_WAV  = 17,
    FILE_PCM  = 18,
    FILE_RM   = 19,
    FILE_RVC   = 20,
    FILE_QRCODE  = 21,
    CMMB_STREAM = 22,
    FILE_MFS  = 23,
    TS_STREAM = 24,
    FILE_TS   = 25,
    FILE_FMRX    = 26,
    FILE_WMA   =27,
    FILE_COOK   =28,
    FILE_FLV    =29,
    FILE_APE = 30,
    FILE_IMAADPCM3BIT = 31,
    FILE_IMAADPCM4BIT = 32,
    FILE_MSADPCM4BIT  = 33,
    FILE_AVI        = 34,
    PCM_STREAM_MONO = 35,
}FILE_TYPE;


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------

extern mp4rec *g_pMp4RecInst;
#if 0 // put back
extern MP4MuxerInst *g_pMp4MuxInst;
#endif
#if 0 // Modify
extern cyg_sem_t gMp4recAbortSem;
#endif

// for MP4 Muxer Demuxer
//extern u16 mdx_byteused;
//extern u16 mdx_maxbyte;
//extern u8 *mdx_ptr;
#if 0 // put back
extern MP4DMXInst mp4dmxInst;
extern MP4FILE mp4fileInst;
#endif


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------

U32 mp4rec_master_clock(U8 mode, void *data);
#endif // __MDL_VDR_H__


