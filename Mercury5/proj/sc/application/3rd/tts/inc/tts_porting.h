/**
*Copyright Statement:
*
*
* @file    tts_porting.h
* @author  mstarsemi.com
* @date    
*
* function declaration & macro definition for 3rd party tts porting
*
*/
#ifndef    __TTS_PORTING_H__ 
#define    __TTS_PORTING_H__
#ifdef     __TTS__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/*=============================================================*/
// Include files
/*=============================================================*/
#include "ven_prim_msg.h"
#include "ven_sdk.h"
#include "ven_dbg.h"
#include "ven_file.h"
#include "ven_handle.h"
#include "vm_msgt.ht"

#include "ivDefine.h"
#include "ivPlatform.h"
#include "ivTTS.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define _TRACE_TTS  (VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_5)

/*=============================================================*/
// Constant define
/*=============================================================*/
// constant for buffer size
#define TEMPBUF_PCMSIZE     (4096*2)
#define WAIT_STREAM_BUFFUER_TIME (20)

// constant for TTS heap size
#define ivTTS_HEAP_SIZE		58000

// constant for alignment
#ifdef	__SHARE_MEM_DRV__
#define	MEMORY_ALIGNMENT					(32)
#else
#define	MEMORY_ALIGNMENT					(2)
#endif //__SHARE_MEM_DRV__

// constant for cache allocation
#define ivTTS_CACHE_SIZE	2048		//1024//512//256
#define ivTTS_CACHE_COUNT	128         //256//512//1024
#define ivTTS_CACHE_EXT		8

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct RIFF_HEADER
{
    s8  szRiffID[4];            // 'R','I','F','F'
    u32 dwRiffSize;
    s8  szRiffFormat[4];        // 'W','A','V','E'
} RIFF_HEADER_t;

typedef struct WAVE_FORMAT
{
    u16 wFormatTag;             // 1
    u16 wChannels;              // 1
    u32 dwSamplesPerSec;
    u32 dwAvgBytesPerSec;
    u16 wBlockAlign;
    u16 wBitsPerSample;
} WAVE_FORMAT_t;

typedef struct FMT_BLOCK
{
    s8  szFmtID[4];       // 'f','m','t',' '
    u32 dwFmtSize;
    WAVE_FORMAT_t wavFormat;
} FMT_BLOCK_t;

typedef struct DATA_BLOCK
{
    s8  szDataID[4];            // 'd','a','t','a'
    u32 dwDataSize;
} DATA_BLOCK_t;

typedef struct
{
    bool                bInitSuccess; 
    ivHTTS              hTtsHandle;
    ivPointer           pTtsHeap;
    u8*                 pPCM;
    u32                 nPCMLen;
    bool                bPcmHead;     
    ven_file_handle_t   pFile;
    s32                 hMediaHandle;
    bool                bExit;
} TtsStruct;

#ifdef __cplusplus
}
#endif //__cplusplus

#endif  //__TTS__
#endif  //__TTS_PORTING_H__
