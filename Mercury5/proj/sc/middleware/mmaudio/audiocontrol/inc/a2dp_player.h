////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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

/**
* @file   a2dp_player.h
* @version
* @brief
*
*/

#ifndef __A2DP_PLAYER_H__
#define __A2DP_PLAYER_H__

#include "mma_thread_mapping.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
//#define __A2DP_TEST__
#define A2DP_PCM_RETRY_CNT  2000
#define A2DP_RETRY_CNT  40000
#define A2DP_YIELD_TIME 30      //ms

#define A2DP_THREAD_STACKSIZE   (20 * 1024)
#define A2DP_THREAD_PRIORITY    68

#define A2DP_PCM_RING_BUFSIZE   (1024*32)
#define A2DP_SBC_RING_BUFSIZE   (1024*10)


#ifndef __SDK_SIMULATION__
#ifdef __A2DP_USE_BACH_PATH__
#define A2DP_USE_BACH_PATH
#endif
#endif

#ifdef A2DP_USE_BACH_PATH
    #define A2DP_START_THRESHOLD    77//(A2DP_SBC_RING_BUFSIZE-1024*9)
#else
    #define A2DP_START_THRESHOLD    77
#endif

#define A2DP_SRC_MIN_SAMPLERATE     0
#define A2DP_SRC_MAX_SAMPLERATE     1

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct _a2dpplayer_s_ a2dpplayer_t;

typedef enum {
    A2DP_CMD_NONE,
    A2DP_CMD_INIT,
    A2DP_CMD_PLAY,
    A2DP_CMD_STOP,
    A2DP_CMD_PAUSE,
    A2DP_CMD_RESUME,
    A2DP_CMD_END,
    A2DP_CMD_SEEK,
    A2DP_CMD_CLOSE,
}a2dp_command_e;

typedef enum {
    A2DP_STATE_NONE = 0,
    A2DP_STATE_INITIALIZED,
    A2DP_STATE_CONFIGURING,
    A2DP_STATE_CONFIGURED,
    A2DP_STATE_STARTING,
    A2DP_STATE_STARTED,
    A2DP_STATE_STOPPING,
} a2dp_state_e;

typedef struct
{
    u32 sample_rate;
    u16 channels;
    u16 length;
}a2dp_setting_t;

typedef struct
{
	u8 channel_mode;
	u8 frequency;
	u8 allocation_method;
	u8 subbands;
	u8 block_length;
	u8 bitpool;
}sbc_t;

typedef struct _recorder_mem_addr
{
    //u8* heapbuf;
    //u32 heapbuflen;

    u8* srcinbuf;
    u32 srcinbufsize;
    u8* srcoutbuf;
    u32 srcoutbufsize;

    u8* pcmbuf;
    u32 pcmbuflen;
    u8* encdatabuf;                 /* sbc output buffer address */
    u32 encdatabuflen;              /* sbc output buffer size */
} recorder_mem_addr;

typedef struct player_thread_s {
    map_thread_inst     handle;
    void               *stack;
    int                 existed;
} thread_st;

struct _a2dpplayer_s_
{
    a2dp_state_e state;             /* Current state for a2dp thread */
    a2dp_command_e command;         /* Current command for a2dp thread */

    sbc_t sbc;                      /* Codec data */
    recorder_mem_addr mem_addr;

    u32 pcmring_handle;             /* input pcm ring buffer handle */
    u32 sbcring_handle;             /* output sbc ring buffer handle */

    s32 channels;                   /* src output ch, sbc encode ch */
    s32 sample_rate;                /* src input sample rate */
    s32 sbc_bitrate;                /* sbc bitrate */
    s32 sbc_samplerate;             /* sbc sampling rate */
    s32 open_success;               /* audio io open status */

    u8 u8Stop;
    u8 u8Pause;
    u8 u8Playend;
    u8 started;
    u8 wait;

    thread_st a2dp_thread;

    map_mutex_t mutex;
    map_sem_t pause_sem;

    map_cond_t thread_start;       /* Lock for communication with a2dp player thread */
    map_cond_t thread_wait;
    u32 task_exist;
};

/*=============================================================*/
// Variable definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/
s32 fnA2dPlayer_Open(void **pInst, a2dp_setting_t *pSetting);
s32 fnA2dPlayer_Play(void *pInst);
s32 fnA2dPlayer_Stop(void *pInst);
s32 fnA2dPlayer_Pause(void *pInst);
s32 fnA2dPlayer_Continue(void *pInst);
s32 fnA2dPlayer_PlayEnd(void *pInst);
s32 fnA2dPlayer_Close(void *pInst);

s32 AudioA2dpPcmWrite(u8 *pBuffer, u32 u32Len);
s32 AudioA2dpPcmRead(void *pInst, u8 *pBuffer, u32 u32Len);
void AudioA2dpChkSampleFinish(u8 *u8stopflag);
void AudioA2dpGetPlayAvailBufsize(u32 *pnDataSize);
void AudioA2dpGetRecAvailBufsize(u32 *pnDataSize);
void AudioA2dpResetBuf(void);

int fnCreateA2DPThread(void *pInst);
void fnDestroyA2DPThread(void *pInst);
void fnCheckSBCend(u8* u8Stopflag);
void fnGetSBCRingBufferInfo(u32 *pnTime);

int wait_for_start(void *pInst, int timeout);
#endif
