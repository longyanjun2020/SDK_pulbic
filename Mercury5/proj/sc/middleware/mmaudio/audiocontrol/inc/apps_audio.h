///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   apps_audio.h
/// @author MStar Semiconductor Inc.
/// @brief  audio application header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _APPS_AUDIO_H
#define _APPS_AUDIO_H

//-------------------------------------------------------------------------------------------------
// General Include Files
//-------------------------------------------------------------------------------------------------
//#include <cyg/infra/dyn_module.h>

//#include "msmComm.h"
#include "vm_stdio.ho"
#include "sys_vm_dbg.ho"
#include "ms_io.h"
#include "mdl_mmaudio_msmerror.h"
//#include "vm_types.ht"
//-------------------------------------------------------------------------------------------------
// Audio Header Files
//-------------------------------------------------------------------------------------------------
//#include "dma_ring.h"

#define AUD_RING_SIZE_OLD
#define AUD_RING_SIZE_New

#define BIG3
#define _CUSAUD _CUS2 | LEVEL_30

#define  fnMPAmpNotify(a,b,c,d)
#define fpShellWriteNotifyResult(a,b,c,d,e,f)
#define fnMPPlayNotify(a,b,c)
//#define CYGARC_PHYSICAL_ADDRESS(a)
//#define CYGARC_UNCACHED_ADDRESS(a)

#define ARM_SDRAM_ENABLE

//#define WAV_PLAYER
//#define MIDI_PLAYER
#define ENABLE_PCMSTREAM
#define ENABLE_LYRICS
#define ENABLE_ID3


//#define ENABLE_AUD_SPECTRUM

#define MAXDMABUFSIZE 75*1024


#define __NEW_MARRECORDER__




#ifdef MP3_DEC
#include "mp3d_lib2.h"
#endif

#ifdef AMRNB_DEC
#include "and_lib2.h"
#endif

#ifdef AAC_DEC
#include "aacd_lib2.h"
#endif


#ifdef WMA_DEC
#include "wma_lib.h"
#include "wma_lib2.h"
#endif

#if defined(COOK_DEC)
#include "cook_lib.h"
#include "cook_lib2.h"
#endif

#if defined(APE_DEC)
#include "aped_lib.h"
#include "aped_lib2.h"
#endif

#if 0//defined(MP3_DEC) //SelyLan 20100225
#include "mp3d_lib.h"
#include "mp3d_lib2.h"
#endif

#ifdef AMRWB_ENC
#include "awe_lib.h"
#endif

#ifdef AMRWB_DEC
#include "awd_lib.h"
#include "awd_lib2.h"
#endif

#ifdef AAC_PLAYER
#include "aacdec_lib.h"
#endif

#ifdef WAV_PLAYER
#include "wavdec.h"
#endif

#ifdef __AMR_REC__
//#include "amrenc_lib.h"
#endif

#ifdef ENABLE_ID3
#include "ID3.h"
#endif

#ifdef  ENABLE_AES
#include "aes.h"
#endif

#ifdef FM_RX_PLAYER
#include "fmrxplayer.h"
#endif


#ifdef ENABLE_AUD_SPECTRUM
#include"aud_spectrum.h"
#endif

enum audio_rec_mode {
   AUD_REC_NORMAL_MODE,
   AUD_REC_FXRX_MODE
};
typedef enum audio_rec_mode AudioRecMode;



typedef char                C8;
// merge from audiodrv.h end

#if 0
// merge from sharebuffer.c
#ifndef AUD_STACK_DRAM
#ifdef NEW_AUDPLAYER
#define AUD_STACK_DRAM_SIZE 20 * 1024
#define AUD_STACK_DRAM      u8 _AUDPLAYER[AUD_STACK_DRAM_SIZE];
#define AUD_STACK_SRAM_SIZE 20 * 1024
#define AUD_STACK_SRAM      u8 _AUDPLAYER[AUD_STACK_SRAM_SIZE];
#else
#define AUD_STACK_SRAM
#define AUD_STACK_DRAM
#endif
#endif
// merge from sharebuffer.c end
#endif
/* AMR record */

typedef u16  fntabRecordAMR(char *filename, u16 cmdid);
typedef void fntabStopRecordAMR(void);
typedef u8* fntabRecAMR_GetStack(void);
typedef int fntabRecAMR_GetStackSize(void);

typedef struct AMRRec_FuncTable{
    fntabRecordAMR              *RecordAMR;
    fntabStopRecordAMR          *StopRecordAMR;
    fntabRecAMR_GetStack        *RecAMR_GetStack;
    fntabRecAMR_GetStackSize    *RecAMR_GetStackSize;
}AMRREC_FUNCTABLE;

#ifndef __NEW_MARRECORDER__
extern u16  _MApp_RECDev_RecordAMR(char *filename, u16 cmdid);
extern void  _MApp_RECDev_StopRecordAMR(void);
#endif

extern u8* _MApp_RecAMR_GetStack(void);
extern int _MApp_RecAMR_GetStackSize(void);

#ifdef  CYGCFG_COMMON_PACKAGE
#define AMRREC_FP           ((AMRREC_FUNCTABLE *)&__audio_functab_start)
#else
extern AMRREC_FUNCTABLE     AMRRecTable;
#define AMRREC_FP           (&AMRRecTable)
#endif

#define fnRecordAMR             AMRREC_FP->RecordAMR
#define fnStopRecordAMR         AMRREC_FP->StopRecordAMR

#define fnRecAMR_GetStack       AMRREC_FP->RecAMR_GetStack
#define fnRecAMR_GetStackSize   AMRREC_FP->RecAMR_GetStackSize


typedef void (*fntabAMREnc_Init)(void **pInst, void *amrheapaddr);
typedef void (*fntabAMREnc_Open)(void *pInst, int dtx);
typedef int (*fntabAMREnc_Dec)(void *pInst, unsigned char *poutstream, int *outbufsize, int *pactualoutsize, int first_frame);


typedef struct AMREnc_FuncTable{
    fntabAMREnc_Init AMREnc_Init;
    fntabAMREnc_Open AMREnc_Open;
    fntabAMREnc_Dec  AMREnc_Dec;
}AMRENC_FUNCTABLE;

extern void fpAMREnc_Init(void **pInst, void *amrheapaddr);
extern void fpAMREnc_Open(void *pInst, int dtx);
extern int fpAMREnc_Dec(void *pInst, unsigned char *poutstream, int *outbufsize, int *pactualoutsize, int first_frame);

#ifdef  CYGCFG_COMMON_PACKAGE
#define AMRENC_FP               ((AMRENC_FUNCTABLE *)((int)&__audio_functab_start + sizeof(AMRREC_FUNCTABLE)))
#else
extern struct AMREnc_FuncTable  AMREncTable;
#define AMRENC_FP               (&AMREncTable)
#endif

#define fnAMREnc_Init           AMRENC_FP->AMREnc_Init
#define fnAMREnc_Open           AMRENC_FP->AMREnc_Open
#define fnAMREnc_Dec            AMRENC_FP->AMREnc_Dec

typedef int fntabAMRDec_GetBitRate(const char *filename, int *bitrate);
typedef int fntabAMRDec_GetTotalTime(const char *filename,unsigned int filesize, unsigned int *pu32TotalTime);

// FM player
#ifndef FM_RX_PLAYER
typedef s32 FmrxArea_e;
#endif

#ifdef  CYGCFG_COMMON_PACKAGE
#define FMRXPlayer                  ((FMRXPLAYER_FUNCTABLE *)&__audio_functab_start)
#else
extern struct FMRXPLAYER_FuncTable FMRXPlayerTable;
#define FMRXPlayer                  (&FMRXPlayerTable)
#endif

#define fnfmrx_PwOnOff     FMRXPlayer->p_fmrx_PwOnOff
#define fnfmrx_SchChl      FMRXPlayer->p_fmrx_SchChl
#define fnfmrx_SetArea     FMRXPlayer->p_fmrx_SetArea
#define fnfmrx_SetFreq     FMRXPlayer->p_fmrx_SetFreq
#define fnfmrx_GetFreq     FMRXPlayer->p_fmrx_GetFreq
#define fnfmrx_SetMute     FMRXPlayer->p_fmrx_SetMute
#define fnfmrx_SetForceMono FMRXPlayer->p_fmrx_SetForceMono
#define fnfmrx_GetStro     FMRXPlayer->p_fmrx_GetStro
#define fnfmrx_GetRSSI     FMRXPlayer->p_fmrx_GetRSSI
#define fnfmrx_FlushDcache FMRXPlayer->p_fmrx_FlushDcache
#define fnfmrx_CrtTast     FMRXPlayer->p_fmrx_CrtTast
#define fnfmrx_Play        FMRXPlayer->p_fmrx_Play





/* PCM streaming */
typedef s32 fntabPlayPCM(void*, s8 s8streamingChannel);
typedef u8* fntabPCMstream_GetBuf(void);
typedef int fntabPCMstream_GetBufSize(void);
typedef u8* fntabPCMstream_GetStack(void);
typedef int fntabPCMstream_GetStackSize(void);
typedef u8* fntabPCMstream_GettmpBuf(void);
typedef void fntabPCMstream_BufFlush(void);

typedef struct PCMStream_FuncTable{
    fntabPlayPCM                    *PlayPCM;
    fntabPCMstream_GetBuf           *PlayPCM_GetBuf;
    fntabPCMstream_GetBufSize       *PlayPCM_GetBufSize;
    fntabPCMstream_GetStack         *PlayPCM_GetStack;
    fntabPCMstream_GetStackSize     *PlayPCM_GetStackSize;
    fntabPCMstream_GettmpBuf        *PlayPCM_GettmpBuf;
    fntabPCMstream_BufFlush         *PlayPCM_BufFlush;
}PCMStream_FUNCTABLE;

extern s32  fpPlayPCM(void *pcmtask, s8 s8streamingChannel);
extern u8* fpPCMstream_GetBuf(void);
extern int fpPCMstream_GetBufSize(void);
extern u8* fpPCMstream_GetStack(void);
extern int fpPCMstream_GetStackSize(void);
extern u8* fpPCMstream_GettmpBuf(void);
extern void fpPCMstream_BufFlush(void);



#ifdef  CYGCFG_COMMON_PACKAGE
#define PCMSTREAM_FP               ((PCMStream_FUNCTABLE *)&__audio_functab_start)
#else
extern PCMStream_FUNCTABLE         PCMStreamTable;
#define PCMSTREAM_FP               (&PCMStreamTable)
#endif

#define fnPlayPCM                   PCMSTREAM_FP->PlayPCM
#define fnPCMStream_GetBuf          PCMSTREAM_FP->PlayPCM_GetBuf
#define fnPCMStream_GetBufSize      PCMSTREAM_FP->PlayPCM_GetBufSize
#define fnPCMStream_GettmpBuf       PCMSTREAM_FP->PlayPCM_GettmpBuf
#define fnPCMStream_GetStack          PCMSTREAM_FP->PlayPCM_GetStack
#define fnPCMStream_GetStackSize      PCMSTREAM_FP->PlayPCM_GetStackSize
#define fnPCMStream_BufFlush         PCMSTREAM_FP->PlayPCM_BufFlush



typedef void fntabMStarID3Parser(s16 s16Cmdid, u32 u32Setting);
extern s32 fpMStarID3Parser(const ms_fnchar *pFilename, u32 u32Setting, void *pBuf);

typedef u32 fntab_WAVHeaderParser(void *pInst, u32 *data_pos, void *aPCMWaveHeader, void *aIMAADPCMHeader, void *aMSADPCMHeader);



//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// audio_spectrum
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

typedef int FP_AUD_Config_AudSpectrum(void* pUserConfig, void* pSelfConfig,int FFTSize,int SmpRate,short Channel,char* pGlobalBuf);
typedef int FP_AUD_Proc_AudSpectrum(void* pSelfConfig,short* p16data,int SzInByte, u32 pts);
typedef int FP_Alloc_Shared_Memory_AudSpectrum(void*, char* pbuf, int size);
typedef int FP_Close_AudSpectrum(void* pSelfConfig);
typedef int FP_Update_Settings_AudSpectrum(void* pSelfConfig, void* pUserConfig);
typedef void FP_Set_Enable_AudSpectrum(void* pUserConfig, int EnableDisp);


extern int Config_AudSpectrum(void* pUserConfig, void* pSelfConfig,int FFTSize,int SmpRate,short Channel,char* pGlobalBuf);
//extern int Proc_AudSpectrum(void* pSelfConfig,short* p16data,int SzInByte, short* p16OutLevel);
extern int Proc_AudSpectrum(void* pSelfConfig,short* p16data,int SzInByte,u32 pts);
extern int Alloc_Shared_Memory_AudSpectrum(void*, char* pbuf, int size);
extern int Close_AudSpectrum(void* pSelfConfig);
extern int Update_Settings_AudSpectrum(void* pSelfConfig, void* pUserConfig);
extern void Set_Enable_AudSpectrum(void* pUserConfig, int EnableDisp);


typedef struct  AUD_SpecTable
{
	FP_AUD_Config_AudSpectrum  *fnConfig_AudSpectrum;
	FP_AUD_Proc_AudSpectrum  *fnProc_AudSpectrum;
	FP_Alloc_Shared_Memory_AudSpectrum *fnAlloc_Shared_Memory_AudSpectrum;
	FP_Close_AudSpectrum *fnClose_AudSpectrum;
	FP_Update_Settings_AudSpectrum *fnUpdate_Settings_AudSpectrum;
	FP_Set_Enable_AudSpectrum *fnSet_Enable_AudSpectrum;

}AUD_SPECTABLE;

#ifdef  CYGCFG_COMMON_PACKAGE
#define AUD_Spec_FP                  ((AUD_SPECTABLE *)&__audio_functab_start)
#else
extern AUD_SPECTABLE    AUDSpecTable;
#define AUD_Spec_FP                  (&AUDSpecTable)
#endif


#define fpConfig_AudSpectrum      AUD_Spec_FP->fnConfig_AudSpectrum
#define fpProc_AudSpectrum		  AUD_Spec_FP->fnProc_AudSpectrum
#define fpAlloc_Shared_Memory_AudSpectrum AUD_Spec_FP->fnAlloc_Shared_Memory_AudSpectrum
#define fpClose_AudSpectrum  AUD_Spec_FP->fnClose_AudSpectrum
#define fpUpdate_Settings_AudSpectrum AUD_Spec_FP->fnUpdate_Settings_AudSpectrum
#define fpSet_Enable_AudSpectrum AUD_Spec_FP->fnSet_Enable_AudSpectrum


//----------------------------------------------------------------------
//For Audio Getinfo functions
//----------------------------------------------------------------------
typedef u32 fntabWAVHeaderParser(void *pInst, u32 *data_pos, void *aPCMWaveHeader, void *aIMAADPCMHeader, void *aMSADPCMHeader);

typedef s32 fntabmidic_GetTotalTime(s32 *fmidi,s32 filesize, void *Inst);
extern s32 midic_GetTotalTime_New(MSFILE fmidi,s32 filesize, void *Inst);


typedef s32 fntabAACDec_getInfo(const ms_fnchar* filename, u32 *u32aacSamplRate,u32 *u32aacBitRate
                         , u8 *u8aacBitRateType, u8 *u8aacChannel_info, u32 *u32aacTotalTime);

extern s32 fpAACDec_getInfo(const ms_fnchar* filename, u32 *u32aacSamplRate,u32 *u32aacBitRate
                         , u8 *u8aacBitRateType, u8 *u8aacChannel_info, u32 *u32aacTotalTime);

extern int fpAMRDec_GetTotalTime(const ms_fnchar *filename, unsigned int filesize, unsigned int *pu32TotalTime, u32* u32Bitrate);

extern int fpAMRDec_GetBitRate(const ms_fnchar *filename, int *bitrate);

extern u32 WAVHeaderParser(void *pInst, u32 *data_pos, void *aPCMWaveHeader, void *aIMAADPCMHeader, void *aMSADPCMHeader);

typedef u32 fntabMP3GetInfoConcurrent(void *pInst, const ms_fnchar* filename, u32 *SamplRate,u32 *BitRate,u8 *BitRateType,u8 *Channel_info,u32 *tmptime,void *t_mp3info);
extern u32 fpMP3GetInfoConcurrent(void *pInst, const ms_fnchar* filename, u32 *SamplRate,u32 *BitRate,u8 *BitRateType,u8 *Channel_info,u32 *tmptime,void *t_mp3info);

typedef struct AUDGETINFO_FuncTable
{
    fntabWAVHeaderParser        *WAVHeaderParser;
    fntabmidic_GetTotalTime     *midic_GetTotalTime;

    fntabAACDec_getInfo         *AACDec_getInfo;

    fntabAMRDec_GetTotalTime    *AMRDec_GetTotalTime;
    fntabAMRDec_GetBitRate      *AMRDec_GetBitRate;

    fntabMStarID3Parser             *MStarID3Parser;

    fntabMP3GetInfoConcurrent      *MP3GetInfoConcurrent;

}AUDGETINFO_FUNCTABLE;

#ifdef  CYGCFG_COMMON_PACKAGE
#define AUDGETINFO_FP           ((AUDGETINFO_FUNCTABLE *)&__audio_functab_start)
#else
extern AUDGETINFO_FUNCTABLE     AUDGETINFOFuncTable;
#define AUDGETINFO_FP           (&AUDGETINFOFuncTable)
#endif

#define fnGetInfoWAVHeaderParser        AUDGETINFO_FP->WAVHeaderParser
#define fnGetInfo_getAACInfo            AUDGETINFO_FP->AACDec_getInfo
#define fnGetInfo_GetAMRTotalTime       AUDGETINFO_FP->AMRDec_GetTotalTime
#define fnGetInfo_GetAMRBitRate         AUDGETINFO_FP->AMRDec_GetBitRate

#define fnMStarID3Parser                         AUDGETINFO_FP->MStarID3Parser

#define fnMP3GetInfoConcurrent              AUDGETINFO_FP->MP3GetInfoConcurrent

//
// AMR recorder
//
#ifdef  __AMR_REC__
#define AMRREC_MAX_FRAME_LEN            160
#define AMRREC_IISBUFSIZE               (640*15)
#define AMRREC_STACKSIZE                (6*1024)
#define AMRREC_HEAPSIZE                 (7516+1280) //6148 //0x00001d5c=7516
#define AMRREC_ALRAM_STACK_SIZE         2048
#define AMRREC_STORAGE_BUF_SIZE         1024
#define AMRREC_ENCDATA_BUF_SIZE         32
#define AMRREC_WHANDLE_STACK_SIZE       (1024*4)
#define AMRREC_PCM_TMP_SIZE             (640*6) //Max 48Khz->8kHZ , MAX DMA data size per fetch // George
#define AMRREC_RING_BUF_SIZE            (1024*10)
#define AMRREC_RING_HIGH_WATER      (30)
#define AMRREC_RING_LOW_WATER       AMRREC_STORAGE_BUF_SIZE
#define AMRREC_WRITE_SIZE_LIMIT       ((AMRREC_STORAGE_BUF_SIZE/1024) * 2)


#define amrrecIISBufSize                AMRREC_IISBUFSIZE   //extern U16 amrrecIISBufSize;
#define amrrecStackSize                 AMRREC_STACKSIZE    //extern U16 amrrecStackSize;
#define amrrecAlarmStackSize            AMRREC_ALRAM_STACK_SIZE

#define amrrecLayer2Buf                 (AMRRecoderDRAM_uncached)
#define amrrecIISBuf                    (AMRRecoderSRAM_uncached->_amrrecIISBuf)
#define amrrecStack                     (AMRRecoderSRAM_cached->_amrrecStack)
#define amrrecheap                      (AMRRecoderSRAM_cached->_amrrecheap)
#define amrrecAlarmStack                (AMRRecoderDRAM_cached->_amrrecalarmstack)
#define amrrecWhandleStack              (AMRRecoderDRAM_cached->_amrrecwhandlestack)
#define amrrecStorageBuf1               (AMRRecoderDRAM_cached->_amrrecstoragebuf1)
#define amrrecStorageBuf2               (AMRRecoderDRAM_cached->_amrrecstoragebuf2)
#define amrrecEncdataBuf                (AMRRecoderDRAM_cached->_amrrecencdatabuf)

#define amrplayheap2                    ((u8 *)_sharemem)           //share mem only 6k(0xA0026800--0xA0027fff)


#endif  // __AMR_REC__


//------------------------------------------------------------
//------------------------------------------------------------


#ifdef __NEW_MARRECORDER__
#define MAR_STACK_DRAM_SIZE 10 * 1024
#define MAR_STACK_DRAM      u8 _MARENCODER[MAR_STACK_DRAM_SIZE];
#define MAR_STACK_SRAM_SIZE 10 * 1024
#define MAR_STACK_SRAM      u8 _MARENCODER[MAR_STACK_SRAM_SIZE];

#define MAR_CTRL_DRAM_SIZE  4 * 1024
#else
#define MAR_STACK_SRAM
#define MAR_STACK_DRAM
#endif //

#ifndef __SDK_SIMULATION__
#define CACHE_LINE_ALIGNMENT //__attribute__((aligned(16)))
#else
#define CACHE_LINE_ALIGNMENT
#endif
// merge from sharebuffer.h end

//
// Wave Encorder
//
#ifdef  ENABLE_WAVENC_MGR
#ifdef  ARM_SDRAM_ENABLE
#define WAVENCMGR_MAX_FRAME_LEN         673
#define WAVENCMGR_HEAP_BUFSIZE          ((4*1024)  + 32)
#define WAVENCMGR_ENCDATA_BUFSIZE       ((1*1024)  + 32)
#define WAVENCMGR_STORAGE_BUFSIZE   (32*1024)
#define WAVENCMGR_PCM_TMP_SIZE             (4*1024) //673*6  Max 48Khz->8kHZ , MAX DMA data size per fetch // George
#define WAVENCMGR_RING_BUF_SIZE            (1024*96)
#define WAVENCMGR_RING_HIGH_WATER      (1024*1)
#define WAVENCMGR_RING_LOW_WATER       WAVENCMGR_STORAGE_BUFSIZE
#define WAVENCMGR_WRITE_SIZE_LIMIT       ((WAVENCMGR_STORAGE_BUFSIZE/1024) * 2)


#define WavEncMgrHeapBufSize            WAVENCMGR_HEAP_BUFSIZE
#define WavEncMgrStorageBufSize         WAVENCMGR_STORAGE_BUFSIZE
#define WavEncMgrEncdataBufSize         WAVENCMGR_ENCDATA_BUFSIZE
#define WavEncMgrWritedataLimitSize      ((WAVENCMGR_STORAGE_BUFSIZE/1024) * 2)

#define WavEncMgrLayer2Buf              (WAVENCMGRDRAM_uncached)
#define WavEncMgrHeapBuf                (WAVENCMGRDRAM_cached->_WaveEncMgrHeap)
#define WavEncMgrEncdataBuf             (WAVENCMGRDRAM_cached->_WaveEncMgrEncDataBuf)


typedef struct wavencmgr_sdram
{    // 32*1024 + 4*1024 + 2*1024 + 2*1024 + 32*1024 + 32*1024 + 1*1024 = 105*1024
    CACHE_LINE_ALIGNMENT U8 _WaveEncMgrHeap[WAVENCMGR_HEAP_BUFSIZE];
    U8 _WaveEncMgrEncDataBuf[WAVENCMGR_ENCDATA_BUFSIZE];
}WAVENC_MGR_SDRAM;

#endif  // ARM_SDRAM_ENABLE
#endif



//#ifdef  PCM_ENC
#ifdef  ARM_SDRAM_ENABLE
#define PCMENC_MAX_FRAME_LEN            1024
#define PCMENC_ENCDATA_BUFSIZE       640//(2*1024)  // frame length :1024
#define PCMENC_HEAP_BUFSIZE              (PCMENC_ENCDATA_BUFSIZE*2)
#define PCMENC_STORAGE_BUFSIZE       (20*1024)
#define PCMENC_PCM_TMP_SIZE             (4*6*1024) //1024*6  Max 48Khz->8kHZ , MAX DMA data size per fetch // George
#define PCMENC_RING_BUF_SIZE            (1024*40)
#define PCMENC_RING_HIGH_WATER      (1024*1)
#define PCMENC_RING_LOW_WATER       PCMENC_STORAGE_BUFSIZE
#define PCMENC_WRITE_SIZE_LIMIT       ((PCMENC_STORAGE_BUFSIZE/1024) * 2)


#define PcmEncHeapBufSize             PCMENC_HEAP_BUFSIZE
#define PcmEncStorageBufSize         PCMENC_STORAGE_BUFSIZE
#define PcmEncEncdataBufSize         PCMENC_ENCDATA_BUFSIZE
#define PcmEncWritedataLimitSize      ((PCMENC_STORAGE_BUFSIZE/1024) * 2)

#define PcmEncLayer2Buf              (PCMENCDRAM_uncached)
#define PcmEncHeapBuf                (PCMENCDRAM_cached->_PcmEncrHeap)
#define PcmEncEncdataBuf             (PCMENCDRAM_cached->_PcmEncEncDataBuf)


typedef struct pcmencmgr_sdram
{    // 32*1024 + 4*1024 + 2*1024 + 2*1024 + 32*1024 + 32*1024 + 1*1024 = 105*1024
    CACHE_LINE_ALIGNMENT U8 _PcmEncHeap[PCMENC_HEAP_BUFSIZE];
    U8 _PcmEncEncDataBuf[PCMENC_ENCDATA_BUFSIZE];
}PCMENC_MGR_SDRAM;

#endif  // ARM_SDRAM_ENABLE
//#endif


#ifdef ENABLE_LYRICS
//Lyrics
#define LYRICS_BUFSIZE      10240
#define LYRICSPARSER_TIMEBUFSIZE  128 //128 * u32
#define LYRICSPARSER_TIMEPOSBUFSIZE 128 //128 * u32
#define LYRICSPARSER_TEXTLENBUFSIZE 128 //128 * u32
#define LYRICSPARSER_TEXTPOSBUFSIZE 128 //128 * u32
//#define LYRICS_TIMENOTIFIEDBUFSIZE  128

typedef struct lyricparser_sdram
{
    u32 _LyricsParserTimeBuf[LYRICSPARSER_TIMEBUFSIZE];
    u32 _LyricsParserTimePosBuf[LYRICSPARSER_TIMEPOSBUFSIZE];
    u32 _LyricsParserTextLenBuf[LYRICSPARSER_TEXTLENBUFSIZE];
    u32 _LyricsParserTextPosBuf[LYRICSPARSER_TEXTPOSBUFSIZE];
    u16 _LyricsTimeSortBuf[1024];
    u8 _LyricsBuf[LYRICS_BUFSIZE];
    u8 _LyricsDesiredBuf[LYRICS_BUFSIZE];
} LYRICPARSER_SDRAM;

#define AudLyricsBuf      (LyricDRAM_cached->_LyricsBuf)
#define AudLyricsDesiredBuf   (LyricDRAM_cached->_LyricsDesiredBuf)
#define AudLyricsTimeSortBuf            (LyricDRAM_cached->_LyricsTimeSortBuf)
#define AudLyricsParserTimeBuf          (LyricDRAM_cached->_LyricsParserTimeBuf)
#define AudLyricsParserTimePosBuf (LyricDRAM_cached->_LyricsParserTimePosBuf)
#define AudLyricsParserTextLenBuf (LyricDRAM_cached->_LyricsParserTextLenBuf)
#define AudLyricsParserTextPosBuf (LyricDRAM_cached->_LyricsParserTextPosBuf)

#endif

//WAV playback
#define WAV_PARSERSTREAMBUFSIZE 1024
#define WAV_PARSER_TEMP_BUFSIZE 1024
#define wavparserstreambuf (WAVPaserDRAM_cached->_wavparserstreambuf)
#define wavparser_temp_buf (WAVPaserDRAM_cached->_wavparser_temp_buf)

#ifdef  WAV_PLAYER  //ccc temporary mark
#define WAV_IIS_BUFSIZE            40*1024
#define WAV_STREAMBUFSIZE 4080
#define WAV_CONVERTBUFSIZE 10884
#define WAVPLAY_DATA_COPY_SIZE  4080
#define WAV_PARSERSTREAMBUFSIZE 1024

typedef struct wavplayer_sdram
{
     u8 _wavconvbuf[WAV_CONVERTBUFSIZE];
     u8 _wavplaycopybuf[WAVPLAY_DATA_COPY_SIZE];
} WAVPLAYER_SDRAM;

typedef struct wavparser_sdram
{
    u8 _wavparserstreambuf[WAV_PARSERSTREAMBUFSIZE];
    u8 _wavparser_temp_buf[WAV_PARSER_TEMP_BUFSIZE];    
} WAVPARSER_SDRAM;

#define wavconvbuf         (WAVPlayerDRAM_cached->_wavconvbuf)
#define wavplaycopybuf      (WAVPlayerDRAM_cached->_wavplaycopybuf)
#endif

// ID3 Parser
#ifdef ENABLE_ID3
#define ID3_STRING_LIMIT_SIZE 128

#if defined(ARM_SDRAM_ENABLE)
#define id3v1AllTagBuf        (ID3ParserDRAM_cached->_id3TagContent)
#define id3TagBuf           (ID3ParserDRAM_cached->_id3TagBuf)
#else
#define id3v1AllTagBuf          (ID3PaserSRAM_cached->_id3TagContent)
#define id3TagBuf           (ID3PaserSRAM_cached->_id3TagBuf)
#endif
#endif //ENABLE_ID3

#ifdef ENABLE_AUD_SPECTRUM
#define SPEC_BUF_DRAM_SIZE 3072
#define Aud_spec_BUF        AUD_SpecDRAM_uncached
#endif

// FM Player
#if defined(FM_RX_PLAYER)

#if defined(ARM_SDRAM_ENABLE)

#define FMRX_IISRX_BUFSIZE               (16*1024)
#define FMRX_IISTX_BUFSIZE               FMRX_IISRX_BUFSIZE  // 500ms/per channel
#define FMRX_TMP_BUFSIZE                 FMRX_IISRX_BUFSIZE  // 500ms/per channel
#define FMRX_THREAD_STACKSIZE            1024*6               // 10K stack size

#define fmrxplayerLayer2Buf             (FMRXPlayerDRAM_uncached)
#define fmrx_iisrx_audbuf               (FMRXPlayerSRAM_uncached->_fmrx_iisrx_audbuf)
#define fmrx_iistx_audbuf               (FMRXPlayerSRAM_uncached->_fmrx_iistx_audbuf)
#define fmrx_player_stackbuf            (FMRXPlayerDRAM_cached->_fmrx_player_stackbuf)
#define fmrx_tempbuf                    (FMRXPlayerDRAM_cached->_fmrx_tempbuf)

#else

#define FMRX_IISRX_BUFSIZE               (16*1024)
#define FMRX_IISTX_BUFSIZE               FMRX_IISRX_BUFSIZE  // 500ms/per channel
#define FMRX_TMP_BUFSIZE                 FMRX_IISRX_BUFSIZE  // 500ms/per channel
#define FMRX_THREAD_STACKSIZE            1024*6               // 10K stack size


#define fmrxplayerLayer2Buf             (FMRXPlayerSRAM_uncached)
#define fmrx_iisrx_audbuf               (FMRXPlayerSRAM_uncached->_fmrx_iisrx_audbuf)
#define fmrx_iistx_audbuf               (FMRXPlayerSRAM_uncached->_fmrx_iistx_audbuf)
#define fmrx_player_stackbuf            (FMRXPlayerSRAM_cached->_fmrx_player_stackbuf)
#define fmrx_tempbuf                    (FMRXPlayerSRAM_cached->_fmrx_tempbuf)

#endif

#define fmrx_iisrx_bufsize              FMRX_IISRX_BUFSIZE
#define fmrx_iistx_bufsize              FMRX_IISTX_BUFSIZE
#define fmrx_player_stacksize           FMRX_THREAD_STACKSIZE
#define fmrx_tempbufsize                FMRX_TMP_BUFSIZE

#endif // FM Player

#if 0
#ifdef  __AMR_REC__
typedef struct amrrecoder
{
    // AMR recorder
    u8 _amrrecIISBuf[AMRREC_IISBUFSIZE];
    CACHE_LINE_ALIGNMENT u8 _amrrecStack[AMRREC_STACKSIZE];
    u8 _amrrecheap[AMRREC_HEAPSIZE];
//    u8 _amrrecalarmstack[AMRREC_ALRAM_STACK_SIZE];
//    u8 _amrrecwhandlestack[AMRREC_ALRAM_STACK_SIZE];
//    u8 _amrrecstoragebuf1[AMRREC_STORAGE_BUF_SIZE];
//    u8 _amrrecstoragebuf2[AMRREC_STORAGE_BUF_SIZE];
}AMRRECODER;

typedef struct amrrecoder_sdram
{
    // AMR recorder
//    u8 _amrrecIISBuf[AMRREC_IISBUFSIZE];
//    CACHE_LINE_ALIGNMENT u8 _amrrecStack[AMRREC_STACKSIZE];
//    u8 _amrrecheap[AMRREC_HEAPSIZE];
    CACHE_LINE_ALIGNMENT u8 _amrrecalarmstack[AMRREC_ALRAM_STACK_SIZE]; // alarm thread stack 2K
    u8 _amrrecwhandlestack[AMRREC_ALRAM_STACK_SIZE]; // write thread stack 2K
    u8 _amrrecstoragebuf1[AMRREC_STORAGE_BUF_SIZE]; // write buffer A 1K
    u8 _amrrecstoragebuf2[AMRREC_STORAGE_BUF_SIZE]; // write buffer B 1K
    u8 _amrrecencdatabuf[AMRREC_ENCDATA_BUF_SIZE]; // encoder buffer 32bytes
}AMRRECODER_SDRAM;
#endif
#endif



//------------------------------------------------------------
//------------------------------------------------------------



#ifdef ENABLE_PCMSTREAM
#define PCMNEW_PCM_OUTPUT_SIZE          4080
#if defined(ARM_SDRAM_ENABLE)
#define pcmnewplaycopybuf                  (PCMNEWPlayerDRAM_cached->_pcmnewplaycopybuf)
#define pcmnewplayoutbuf                  (PCMNEWPlayerDRAM_cached->_pcmnewplayoutbuf)

typedef struct pcmnewplayer_sdram
{
    u8 _pcmnewplaycopybuf[PCMNEW_PCM_OUTPUT_SIZE];
    u8 _pcmnewplayoutbuf[PCMNEW_PCM_OUTPUT_SIZE];
}PCMNEWPLAYER_SDRAM;
#endif
#endif //#ENABLE_PCMSTREAM

#ifdef ENABLE_ID3
#ifdef  ARM_SDRAM_ENABLE
typedef struct id3parser_sdram
{
    CACHE_LINE_ALIGNMENT U8 _id3TagContent[256];
    char _id3TagBuf[ID3_STRING_LIMIT_SIZE];
} ID3PARSER_SDRAM;
#else
typedef struct id3parser
{
    char _id3TagContent[256];
    char _id3TagBuf[ID3_STRING_LIMIT_SIZE];
}ID3PARSER;
#endif
#endif


#ifdef ENABLE_AUD_SPECTRUM
typedef struct aud_spectrum
{
	U8 _AUD_SpecDRAM_buf[SPEC_BUF_DRAM_SIZE];
}Aud_Spectrum;

extern Aud_Spectrum* AUD_SpecDRAM_uncached;
#endif

// FM RX Player
#if defined(FM_RX_PLAYER)

#if defined(ARM_SDRAM_ENABLE)

// for dram
typedef struct fmrxplayer_dram
{
    CACHE_LINE_ALIGNMENT u8 _fmrx_player_stackbuf[FMRX_THREAD_STACKSIZE];
    u8 _fmrx_tempbuf[FMRX_TMP_BUFSIZE];
}FMRXPLAYER_SDRAM;

// for sram
typedef struct fmrxplayer
{
    u8 _fmrx_iisrx_audbuf[FMRX_IISRX_BUFSIZE];
    u8 _fmrx_iistx_audbuf[FMRX_IISTX_BUFSIZE];

}FMRXPLAYER;

#else

typedef struct fmrxplayer
{
    u8 _fmrx_player_stackbuf[FMRX_THREAD_STACKSIZE];
    u8 _fmrx_tempbuf[FMRX_TMP_BUFSIZE];
    u8 _fmrx_iisrx_audbuf[FMRX_IISRX_BUFSIZE];
    u8 _fmrx_iistx_audbuf[FMRX_IISTX_BUFSIZE];

}FMRXPLAYER;

#endif

#endif // FM Player


#ifdef ENABLE_LYRICS
extern LYRICPARSER_SDRAM *LyricDRAM_cached;
#endif

#if 0
#ifdef __AMR_REC__
#ifdef ARM_SDRAM_ENABLE
//#define AMR_REC_BUF     AMRRECODER_SDRAM  _AMRRECODER;
extern AMRRECODER_SDRAM *AMRRecoderDRAM_cached;
extern AMRRECODER_SDRAM *AMRRecoderDRAM_uncached;
#endif //ARM_SDRAM_ENABLE
//#define AMR_REC_SRAM    AMRRECODER  _AMRRECODER;
extern AMRRECODER *AMRRecoderSRAM_cached;
extern AMRRECODER *AMRRecoderSRAM_uncached;
#endif //__AMR_REC__
#endif

#ifdef ENABLE_WAVENC_MGR
extern WAVENC_MGR_SDRAM *WAVENCMGRDRAM_cached;
extern WAVENC_MGR_SDRAM *WAVENCMGRDRAM_uncached;
#endif //ENABLE_WAVENC_MGR

//------------------------------------------------------------
//------------------------------------------------------------

#ifdef ENABLE_ID3
#if defined(ARM_SDRAM_ENABLE)
extern ID3PARSER_SDRAM *ID3ParserDRAM_cached;
#else
extern ID3PARSER *ID3PaserSRAM_cached;
#endif
#endif //ENABLE_ID3


#ifdef ENABLE_PCMSTREAM
extern PCMNEWPLAYER_SDRAM *PCMNEWPlayerDRAM_cached;
#endif //ENABLE_PCMSTREAM


#ifdef FM_RX_PLAYER
#if defined(ARM_SDRAM_ENABLE)
extern FMRXPLAYER_SDRAM *FMRXPlayerDRAM_cached;
extern FMRXPLAYER_SDRAM *FMRXPlayerDRAM_uncached;
extern FMRXPLAYER       *FMRXPlayerSRAM_uncached;
#else
extern FMRXPLAYER       *FMRXPlayerSRAM_cached;
extern FMRXPLAYER       *FMRXPlayerSRAM_uncached;
#endif
#endif


//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Audio RAM define
//----------------------------------------------------------------------
//----------------------------------------------------------------------

#if defined(MP3_DEC)
#ifdef  ARM_SDRAM_ENABLE
#define MP3DEC_DRAM_HEAP_SIZE          (31*1024+4)// max sdam size 26112 + 1152*4 + 4
#define MP3DEC_SRAM_HEAP_SIZE          (26*1024)    // max sram size orig:24064
#define MP3DEC_SRAM_HEAP_SIZE_1        (20*1024)
#define MP3DEC_SRAM_HEAP_SIZE_2        (15*1024)
#define MP3DEC_SRAM_HEAP_SIZE_3        (10*1024)
#define MP3_PARSERSBUFSIZE             (7*1024) 
#define mp3dec_dram_heap               (MP3DecDRAM_cached->_mp3dec_dram_heap)
#define mp3dec_sram_heap               (MP3DecSRAM_cached->_mp3dec_sram_heap)
#define mp3parserbuf                   (MP3ParserDRAM_cached->_mp3parserbuf)

typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _mp3dec_sram_heap[MP3DEC_DRAM_HEAP_SIZE];
}MP3DEC_MEM_SRAM;

typedef struct
{ 
   u8 _mp3dec_dram_heap[MP3DEC_SRAM_HEAP_SIZE];
}MP3DEC_MEM_DRAM;

typedef struct MP3parser_sdram
{
    u8 _mp3parserbuf[MP3_PARSERSBUFSIZE];   
} MP3PARSER_SDRAM;

extern MP3DEC_MEM_SRAM *MP3DecSRAM_cached;
extern MP3DEC_MEM_DRAM *MP3DecDRAM_cached;
extern MP3PARSER_SDRAM *MP3ParserDRAM_cached;

#else
#define mp3decLayer2Buf                (MP3DecSRAM_uncached)
#define mp3decaudbuf                   (MP3DecSRAM_uncached->_mp3decaudbuf)
#define mp3dec_sram_heap               (MP3DecSRAM_cached->_mp3dec_sram_heap)
#define mp3dec_sdram_heap              (MP3DecSRAM_cached->_mp3dec_sdram_heap)
#define mp3dec_sdram_heap2             (MP3DecSRAM_cached->_mp3dec_sdram_heap2)
#define mp3decsourcebuf                (MP3DecSRAM_cached->_mp3decsourcebuf)
#define mp3decalarmstack               (MP3DecSRAM_cached->_mp3decalarmstack)
#define mp3decSurroundBuf              (MP3DecSRAM_cached->_mp3decsurroundbuf)
#define mp3decgetinfobuf               (MP3DecPaserSRAM_cached->_mp3decgetinfobuf)

typedef struct
{
    u8 _mp3decaudbuf[MP3DEC_IIS_BUFSIZE];
    u8 _mp3dec_sram_heap[MP3DEC_SRAM_HEAP_SIZE];
    u8 _mp3dec_sdram_heap[MP3DEC_SDRAM_HEAP_SIZE];

    u8 _mp3decalarmstack[MP3DEC_ALRAM_STACK_SIZE];
    u8 _mp3decsourcebuf[MP3DEC_SOURCESIZE];
    u8 _mp3decsurroundbuf[MP3DEC_SURROUND_BUFSIZE];
}MP3DEC_MEM;
typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _mp3decgetinfobuf[8*1024];
}MP3DECPARSER_MEM;
#endif //
#endif// MP3_DEC
//----------------------------------------------------------------------
#if defined(AMRNB_DEC)
#define AMRNBDEC_SDRAM_HEAP_SIZE         (30*1024) //7504
#ifdef  ARM_SDRAM_ENABLE
#define amrnbdec_sdram_heap              (AMRNBDecDRAM_cached->_amrnbdec_sdram_heap)

typedef struct
{
    u8 _amrnbdec_sdram_heap[AMRNBDEC_SDRAM_HEAP_SIZE];
}AMRNBDEC_MEM_SDRAM;

extern AMRNBDEC_MEM_SDRAM *AMRNBDecDRAM_cached;
#else
#define amrnbdecLayer2Buf                (AMRNBDecSRAM_uncached)
#define amrnbdecaudbuf                   (AMRNBDecSRAM_uncached->_amrnbdecaudbuf)
#define amrnbdec_sram_heap               (AMRNBDecSRAM_cached->_amrnbdec_sram_heap)
#define amrnbdec_sdram_heap              (AMRNBDecSRAM_cached->_amrnbdec_sdram_heap)
#define amrnbdec_sdram_heap2             (AMRNBDecSRAM_cached->_amrnbdec_sdram_heap2)
#define amrnbdecsourcebuf                (AMRNBDecSRAM_cached->_amrnbdecsourcebuf)
#define amrnbdecalarmstack               (AMRNBDecSRAM_cached->_amrnbdecalarmstack)
#define amrnbdecSurroundBuf              (AMRNBDecSRAM_cached->_amrnbdecsurroundbuf)
#define amrnbdecgetinfobuf               (AMRNBDecPaserSRAM_cached->_amrnbdecgetinfobuf)

typedef struct
{
    u8 _amrnbdecaudbuf[AMRNBDEC_IIS_BUFSIZE];
    u8 _amrnbdec_sram_heap[AMRNBDEC_SRAM_HEAP_SIZE];
    u8 _amrnbdec_sdram_heap[AMRNBDEC_SDRAM_HEAP_SIZE];

    u8 _amrnbdecalarmstack[AMRNBDEC_ALRAM_STACK_SIZE];
    u8 _amrnbdecsourcebuf[AMRNBDEC_SOURCESIZE];
    u8 _amrnbdecsurroundbuf[AMRNBDEC_SURROUND_BUFSIZE];
}AMRNBDEC_MEM;
typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _amrnbdecgetinfobuf[8*1024];
}AMRNBDECPARSER_MEM;
#endif //
#endif// AMRNB_DEC
//----------------------------------------------------------------------
#if defined(AAC_DEC)
// aac variable sram
#ifdef HEAAC_V2_DEC
#define AACDEC_DRAM_HEAP_SIZE         (129120+4) // max sdam size, varible
#else
#define AACDEC_DRAM_HEAP_SIZE         (37*1024+4)  // (32864+4)max sdam size, varible //35840  //0x000004a8*2
#endif
#define AACDEC_SRAM_HEAP_SIZE          (27136) //26.5k(24064)  // max sram size, HEACC not support this mode
#define AACDEC_SRAM_HEAP_SIZE_1        (20*1024)
#define AACDEC_SRAM_HEAP_SIZE_2        (16*1024)
#define AACDEC_SRAM_HEAP_SIZE_3        (12*1024)
#define AAC_PARSERSBUFSIZE             (10*1024) 
#define aacdec_dram_heap              (AACDecDRAM_cached->_aacdec_dram_heap)
#define aacdec_sram_heap               (AACDecSRAM_cached->_aacdec_sram_heap)
#define aacparserbuf                  (AACParserDRAM_cached->_aacparserbuf)
typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _aacdec_sram_heap[AACDEC_DRAM_HEAP_SIZE];
}AACDEC_MEM_SRAM;

typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _aacdec_dram_heap[AACDEC_SRAM_HEAP_SIZE];
}AACDEC_MEM_DRAM;

typedef struct AACparser_sdram
{
    u8 _aacparserbuf[AAC_PARSERSBUFSIZE];   
} AACPARSER_SDRAM;

extern AACDEC_MEM_SRAM *AACDecSRAM_cached;
extern AACDEC_MEM_DRAM *AACDecDRAM_cached;
extern AACPARSER_SDRAM *AACParserDRAM_cached;
#endif// AAC_DEC

//------------------------------------------------------------
//------------------------------------------------------------
#if defined(COOK_DEC)
#define COOKDEC_SDRAM_HEAP_SIZE         (120*1024)
#define COOKDEC_PARSER_BUF_DRAM_SIZE 8*1024

#ifdef  ARM_SDRAM_ENABLE
#define cookdec_sdram_heap              (COOKDecDRAM_cached->_cookdec_sdram_heap)
#define cookdecgetinfobuf               (COOKDecPaserDRAM_cached->_cookdecgetinfobuf)

typedef struct
{
    u8 _cookdec_sdram_heap[COOKDEC_SDRAM_HEAP_SIZE];
}COOKDEC_MEM_SDRAM;

typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _cookdecgetinfobuf[8*1024];
}COOKDECPARSER_MEM_SDRAM;
#else

typedef struct
{
    u8 _cookdecaudbuf[COOKDEC_IIS_BUFSIZE];
    u8 _cookdec_sram_heap[COOKDEC_SRAM_HEAP_SIZE];
    u8 _cookdec_sdram_heap[COOKDEC_SDRAM_HEAP_SIZE];

    u8 _cookdecalarmstack[COOKDEC_ALRAM_STACK_SIZE];
    u8 _cookdecsourcebuf[COOKDEC_SOURCESIZE];
}COOKDEC_MEM;
typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _cookdecgetinfobuf[8*1024];
}COOKDECPARSER_MEM;
#endif  // ARM_SDRAM_ENABLE

#ifdef ARM_SDRAM_ENABLE
extern COOKDEC_MEM_SDRAM *COOKDecDRAM_cached;
extern COOKDECPARSER_MEM_SDRAM *COOKDecPaserDRAM_cached;
#endif
#endif //endif defined(COOK_DEC)
//------------------------------------------------------------
//------------------------------------------------------------
#ifdef MP3L2ENC
#define MP3L2ENC_MAX_FRAME_LEN          1152
#define MP3L2ENC_IISDramBUFSIZE           (1024*32)
#define MP3L2ENC_INBUF_SIZE               4608  //6148+1280 // 1280 for input PCM
#define MP3L2ENC_HEAPSIZE                 (16520+4608) // 4608 is MP3L2ENC_INBUF_SIZE
#define MP3L2ENC_ALRAM_STACK_SIZE         2048
#define MP3L2ENC_STORAGE_BUF_SIZE         1024*16 //2048
#define MP3L2ENC_PCM_TMP_SIZE             (5*1024) //1152*4  MAX DMA data size per fetch // George
#define MP3L2ENC_DATA_BUF_SIZE            (720+80) //61*2       // for mode 8 two channel ; 80 is reserved
#define MP3L2ENC_RING_BUF_SIZE            (1024*48)
#define MP3L2ENC_RING_HIGH_WATER      (1024*1)
#define MP3L2ENC_RING_LOW_WATER       MP3L2ENC_STORAGE_BUF_SIZE
#define MP3L2ENC_WRITE_SIZE_LIMIT       ((MP3L2ENC_STORAGE_BUF_SIZE/1024) * 2)


#define mp3l2encIISDramBufSize            MP3L2ENC_IISDramBUFSIZE   //extern U16 amrrecIISBufSize;
#define mp3l2encAlarmStackSize            MP3L2ENC_ALRAM_STACK_SIZE
#define mp3l2encLayer2Buf                 (MP3L2EncDRAM_uncached)
#define mp3l2encIISDramBuf                (MP3L2EncDRAM_uncached->_mp3l2encIISDramBuf)
#define mp3l2encinbuf                      (MP3L2EncSRAM_cached->_mp3l2encinbuf)
#define mp3l2encheap                      (MP3L2EncDRAM_cached->_mp3l2encheap)

#define mp3l2encAlarmStack                (MP3L2EncDRAM_cached->_mp3l2encalarmstack)
#define mp3l2encWhandleStack              (MP3L2EncDRAM_cached->_mp3l2encwhandlestack)
#define mp3l2encStorageBuf1               (MP3L2EncDRAM_cached->_mp3l2encstoragebuf1)
#define mp3l2encStorageBuf2               (MP3L2EncDRAM_cached->_mp3l2encstoragebuf2)
#define mp3l2encdataBuf                   (MP3L2EncDRAM_cached->_mp3l2encdatabuf)


typedef struct
{
    U8 _mp3l2encdatabuf[MP3L2ENC_DATA_BUF_SIZE];
}MP3L2ENC_MEM; //SRAM => MP3L2ENC_BUF_SRAM_SIZE

typedef struct
{
    U8 _mp3l2encdatabuf[MP3L2ENC_DATA_BUF_SIZE];
    CACHE_LINE_ALIGNMENT U8 _mp3l2encheap[MP3L2ENC_HEAPSIZE];
}MP3L2ENC_MEM_SDRAM; //DRAM => MP3L2ENC_BUF_DRAM_SIZE

#define MP3L2ENC_BUF_DRAM_SIZE 90 * 1024
#define MP3L2ENC_BUF_DRAM      U8 _MP3L2ENC_MEM[MP3L2ENC_BUF_DRAM_SIZE];
#define MP3L2ENC_BUF_SRAM_SIZE 9 * 1024
#define MP3L2ENC_BUF_SRAM      U8 _MP3L2ENC_MEM[MP3L2ENC_BUF_SRAM_SIZE];

extern MP3L2ENC_MEM_SDRAM *MP3L2EncDRAM_cached;
extern MP3L2ENC_MEM_SDRAM *MP3L2EncDRAM_uncached;
#endif  //MP3L2ENC
//----------------------------------------------------------------------
//----------------------------------------------------------------------
#ifdef MP3L3ENC
#define MP3L3ENC_MAX_FRAME_LEN          1152
#define MP3L3ENC_HEAPSIZE                 (26*1024+5*1024) //5k is reserved for 4608
#define MP3L3ENC_SRAMSIZE                 (0*1024) //follow  MP3L3SRAM_ENABLE
#define MP3L3ENC_PCM_TMP_SIZE             (5*1024) //1152*4
#define MP3L3ENC_DATA_BUF_SIZE            (2880)
#define MP3L3ENC_STORAGE_BUF_SIZE         1024*16
#define MP3L3ENC_RING_BUF_SIZE            (1024*48)
#define MP3L3ENC_RING_HIGH_WATER          (1024*1)
#define MP3L3ENC_RING_LOW_WATER           MP3L3ENC_STORAGE_BUF_SIZE
#define MP3L3ENC_WRITE_SIZE_LIMIT         ((MP3L3ENC_STORAGE_BUF_SIZE/1024) * 2)
#endif //MP3L3ENC
//----------------------------------------------------------------------
//----------------------------------------------------------------------
#ifdef  AMRWB_ENC
#define AMRWBENC_MAX_FRAME_LEN          320
#define AMRWBENC_HEAPSIZE                 14*1024+2560 // 2560 for input PCM ; actually, we need 4800 bytes for amrwb encoder //  0x00003564=13668
#define AMRWBENC_DATA_BUF_SIZE            64*2       // for mode 8 two channel; 477bits are produced for 23.85 kbit/s (bitrate); max is 61(mode = 8)+9(magic number)
#define AMRWBENC_PCM_TMP_SIZE             (640*6)
#define AMRWBENC_STORAGE_BUF_SIZE         2048
#define AMRWBENC_RING_BUF_SIZE            (1024*20)
#define AMRWBENC_RING_HIGH_WATER         (30)
#define AMRWBENC_RING_LOW_WATER         AMRWBENC_STORAGE_BUF_SIZE
#define AMRWBENC_WRITE_SIZE_LIMIT       ((AMRWBENC_STORAGE_BUF_SIZE/1024) * 2)
#endif

//------------------------------------------------------------
//------------------------------------------------------------
#ifdef AMRWB_DEC
#define AMRWBDEC_SRAM_HEAP_SIZE          (20*1024)
#define AMRWBDEC_PCM_OUTPUT_SIZE         (320*2*2)
#define AMRWBDEC_BUF_SRAM_SIZE 24 * 1024  // 20 + 1.25k   //   0x000012c8=4808

#define amrwbdec_sram_heap               (AMRWBDecSRAM_cached->_amrwbdec_sram_heap)
#define amrwbdec_pcm_output              (AMRWBDecSRAM_cached->_amrwbdec_pcm_output)

typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _amrwbdec_sram_heap[AMRWBDEC_SRAM_HEAP_SIZE];
    CACHE_LINE_ALIGNMENT u8 _amrwbdec_pcm_output[AMRWBDEC_PCM_OUTPUT_SIZE];
}AMRWBDEC_MEM;

extern AMRWBDEC_MEM *AMRWBDecSRAM_cached;
#endif  // AMRWB_DEC
//------------------------------------------------------------
//------------------------------------------------------------
#ifdef WMA_DEC
#define WMADEC_SDRAM_HEAP_SIZE         ((56+12+2)*1024)
#define WMADEC_GETINFO_HEAP_SIZE       (8*1024)
#define wmadec_sdram_heap              (WMADecDRAM_cached->_wmadec_sdram_heap)
#define wmadecgetinfobuf               (WMADecPaserDRAM_cached->_wmadecgetinfobuf)

typedef struct
{
    u8 _wmadec_sdram_heap[WMADEC_SDRAM_HEAP_SIZE];
}WMADEC_MEM_SDRAM;
typedef struct
{
    CACHE_LINE_ALIGNMENT u8 _wmadecgetinfobuf[WMADEC_GETINFO_HEAP_SIZE];
}WMADECPARSER_MEM_SDRAM;

extern WMADEC_MEM_SDRAM *WMADecDRAM_cached;
extern WMADECPARSER_MEM_SDRAM *WMADecPaserDRAM_cached;

#endif  // WMA_DEC
//------------------------------------------------------------
//------------------------------------------------------------
// End of Audio RAM define
//----------------------------------------------------------------------
//----------------------------------------------------------------------
#endif // _APPS_AUDIO_H
