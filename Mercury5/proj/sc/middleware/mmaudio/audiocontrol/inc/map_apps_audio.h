#ifndef _MAP_APPS_AUDIO_H_
#define _MAP_APPS_AUDIO_H_

#include <assert.h>
#include "vm_types.ht"
#include "sys_vm_dbg.ho"

#define BIG3

//#ifdef __BLUETOOTH_A2DP__
#define ENABLE_SBCENC
#define ENABLE_SRCCONVERT
//#endif

#if defined(ENABLE_SBCENC) || defined(ENABLE_SRCCONVERT)
#include "sbce_lib.h"
#include "srcconvert.h"
#endif

#define _CUSAUD _CUS2 | LEVEL_30
#define BSIN_LEN   2 //195296 //1200//136480 //16832 //80352   //8192  //192960

#if !defined(__SDK_SIMULATION__)
#define AUD_ASSERT                          CUS_ASSERT
#else
#define AUD_ASSERT                          assert
#endif

#ifndef __SDK_SIMULATION__
#define CACHE_LINE_ALIGNMENT //__attribute__((aligned(16)))
#else
#define CACHE_LINE_ALIGNMENT
#endif


// SBC buf
#if defined(ENABLE_SBCENC)
#define A2DPPLAY_SBC_OUTBUFSIZE          1024*1  //(1002+12)
#define A2DPPLAY_SBC_HEAPSIZE            1024*3
#define A2DPPLAY_SBC_HEAPDATASIZE        (A2DPPLAY_SBC_HEAPSIZE+A2DPPLAY_SBC_OUTBUFSIZE)
#define A2DPPLAY_SBC_DATASIZE            4//1024*10 M3 sbc output ringbuffer

#define a2dpsbcheapbuf                   (SBCEncDRAM_cached->_a2dpsbcheap)
#define a2dpsbcdatabuf                   (SBCEncDRAM_cached->_a2dpsbcdata)
#endif

#if defined(ENABLE_SRCCONVERT)
#define SRC_INPUT_SAMPLE_SIZE            (128)
#define SRC_INPUT_BUF_SIZE               (SRC_INPUT_SAMPLE_SIZE * 4)
#define SRC_TMP_BUF_SIZE                 ((SRC_INPUT_SAMPLE_SIZE*4)*2*2)    // tmp 320 samples
#define SRC_OUTPUT_BUF_SIZE              ((SRC_INPUT_SAMPLE_SIZE*(6*2))*2*2) // output 10 * 320 samples

#define SRCTmpBuf                        (AudSrcDRAM_cached->_src_tmpbuf)
#define SRCInputBuf                      (AudSrcDRAM_cached->_src_inbuf)
#define SRCOutputBuf                     (AudSrcDRAM_cached->_src_outbuf)
#endif

typedef struct _player_sbc_attr {
    u8 sbc_samplerate;
    u8 sbc_channel;
    u8 sbc_block;
    u8 sbc_subband;
    u8 sbc_allocation;
    u8 sbc_bitpool;
}player_sbc_attr;

typedef struct _sbc_stream{
    u8 *u32RingBaseAddr;
    u8 *u32RingBtmAddr;
    u8 *u32rpcmaddr;
    u8 *u32wpcmaddr;
    u32 pcmplaybufsize;
    u32 sbcringbufsize;
    u32 u32sbcinit;
} sbc_stream;


#ifdef ENABLE_SBCENC
typedef struct sbcencbuf_sdram
{
    CACHE_LINE_ALIGNMENT u8 _a2dpsbcheap[A2DPPLAY_SBC_HEAPDATASIZE];
    u8 _a2dpsbcdata[A2DPPLAY_SBC_DATASIZE];
}SBCENCBUF_SDRAM;
#endif


#ifdef ENABLE_SRCCONVERT
typedef struct audiosrc_sdram
{
    CACHE_LINE_ALIGNMENT u8 _src_tmpbuf[SRC_TMP_BUF_SIZE];
    u8 _src_inbuf[SRC_INPUT_BUF_SIZE];
    u8 _src_outbuf[SRC_OUTPUT_BUF_SIZE];
}AUDIOSRC_SDRAM;
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SBC encoder
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
typedef s32 fntabMstar_sbce_init(int channel_mode,int alloc_method,int nrof_blocks,int nrof_subbands,
                    int ch,int sample_freq,int bitrate,int br_flag);

typedef void fntabMstar_sbce_open(unsigned char *sram_ptr,unsigned char *sdram_ptr);

typedef s32 fntabMstar_sbce_encode(short *input_buf, unsigned char *output_buf, unsigned short *output_len);

#if 0
typedef s32 fntabMpAudio_SBCPushBuf(u16 *inputptr,
                        u8 *sbcoutptr,
                        s32 s32samplesize,
                        u8 u8channel,
                        s8 *u8bplay,
                        s8 *alarm_enable,
                        s32 sbcbitrate);

typedef void fntabSBCBufInit(u8 *baseaddr, u32 buflen);
typedef u32 fntabPushSBCBuf(u8* PBuffer, u32 u32Len);
typedef u32 fntabPopSBCBuf(u8* PBuffer, u32 u32Len);
typedef u32 fntabGetAvailSBCBufsize(void);
typedef void fntabCheckSBCend(u8 *u8stopflag);
#endif


typedef struct SBCENC_FuncTable{
    fntabMstar_sbce_init        *sbce_init;
    fntabMstar_sbce_open        *sbce_open;
    fntabMstar_sbce_encode      *sbce_encode;
    //fntabMpAudio_SBCPushBuf     *Audio_SBCPushBuf;
    //fntabSBCBufInit             *SBCBufInit;
    //fntabPushSBCBuf             *PushSBCBuf;
    //fntabPopSBCBuf              *PopSBCBuf;
    //fntabGetAvailSBCBufsize     *GetAvailSBCBufsize;
    //fntabCheckSBCend            *CheckSBCend;
}SBCENC_FUNCTABLE;


//extern int Mstar_sbce_encode(short *input_buf, unsigned char *output_buf, unsigned short *output_len);
//extern int Mstar_sbce_init(int channel_mode,int alloc_method,int nrof_blocks,int nrof_subbands,
//                    int ch,int sample_freq,int bitrate,int br_flag);

//extern void Mstar_sbce_open(unsigned char *sram_ptr,unsigned char *sdram_ptr);

//extern s32 fpMpAudio_SBCPushBuf(u16 *inputptr,
//                        u8 *sbcoutptr,
//                        s32 s32samplesize,
//                        u8 u8channel,
//                        s8 *u8bplay,
//                        s8 *alarm_enable,
//                        s32 sbcbitrate);

//extern void fpSBCBufInit(u8 *baseaddr, u32 buflen);
//extern u32 fpPushSBCBuf(u8* PBuffer, u32 u32Len);
//extern u32 fpPopSBCBuf(u8* PBuffer, u32 u32Len);
//extern u32 fpGetAvailSBCBufsize(void);
//extern void fpCheckSBCend(u8 *u8stopflag);
//extern void fpSBCBufclose(void);


#ifdef  CYGCFG_COMMON_PACKAGE
#define SBCENC_FP               ((SBCENC_FUNCTABLE *)&__audio_functab_start)
#else
extern SBCENC_FUNCTABLE         SBCENCTable;
#define SBCENC_FP               (&SBCENCTable)
#endif

#define fnSBC_open                  SBCENC_FP->sbce_open
#define fnSBC_init                  SBCENC_FP->sbce_init
#define fnSBC_encode                SBCENC_FP->sbce_encode
//#define fnMpAudio_SBCPushBuf        SBCENC_FP->Audio_SBCPushBuf
//#define fnSBCBufInit                SBCENC_FP->SBCBufInit
//#define fnPushSBCBuf                SBCENC_FP->PushSBCBuf
//#define fnPopSBCBuf                 SBCENC_FP->PopSBCBuf
//#define fnGetAvailSBCBufsize        SBCENC_FP->GetAvailSBCBufsize
//#define fnCheckSBCend               SBCENC_FP->CheckSBCend



//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SRC
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#ifndef ENABLE_SRCCONVERT
#define SRC_ATTR_MIPs16
typedef s32 SRC_SAMPLERATE_SELECTOR_FLAG;
#else
#define SRC_ATTR_MIPs16
#endif

typedef bool SRC_ATTR_MIPs16 FP_AUD_SRCContInterface_SetPower(void * void_set_stc, bool bEn );
typedef bool SRC_ATTR_MIPs16 FP_AUD_SRCContInterface_SetSampleingRate(void * void_set_stc, s32 *s32ValidOutSamplRateArray, s32 s32ValidOutSamplRateArraySize);
typedef bool SRC_ATTR_MIPs16 FP_AUD_SRCContInterface_SetSelectRule(void * void_set_stc, SRC_SAMPLERATE_SELECTOR_FLAG Rule);
typedef bool SRC_ATTR_MIPs16 FP_AUD_SRCMainIP_GetOutputSamplingRate( void * void_src_ip , s32* s32SamplingRate);
typedef bool SRC_ATTR_MIPs16 FP_AUD_SRCMainIP_GetOutputSampleSize( void * void_src_ip , s32 proc_input_size_per_ch, s32* proc_out_size_per_ch);
typedef bool SRC_ATTR_MIPs16 FP_AUD_SRCMainIP_Init(void * void_src_ip, void * void_set_stc ,
                        s32  s32ChNum ,
                        s32  s32InSamplRate);
typedef bool FP_AUD_SRCMainIP_Proc(void * void_src_ip,
                          s16* ps16Insample_buffer , s32  proc_input_size_per_ch,
                          s16* ps16Tmpsample_buffer, s32  proc_tmp_size_per_ch,
                          s16* ps16Outsample_buffer, s32  proc_output_size_per_ch,
						  s32* real_output_size_per_ch);
typedef bool FP_AUD_SRCMainIP_CheckAndUpdate( void *void_src_ip , void * void_set_stc );
typedef bool SRC_ATTR_MIPs16 FP_AUD_SRCMainIP_Close(void * void_src_ip, void * void_set_stc );

/*
extern bool SRC_ATTR_MIPs16 AUD_SRCContInterface_SetPower(void * void_set_stc, bool bEn );
extern bool SRC_ATTR_MIPs16 AUD_SRCContInterface_SetSamplingRate(void * void_set_stc, s32 *s32ValidOutSamplRateArray, s32 s32ValidOutSamplRateArraySize);
extern bool SRC_ATTR_MIPs16 AUD_SRCContInterface_SetSelectRule(void * void_set_stc, SRC_SAMPLERATE_SELECTOR_FLAG Rule);
extern bool SRC_ATTR_MIPs16 AUD_SRCMainIP_GetOutputSamplingRate( void * void_src_ip , s32* s32SamplingRate);
extern bool SRC_ATTR_MIPs16 AUD_SRCMainIP_GetOutputSampleSize( void * void_src_ip , s32 proc_input_size_per_ch, s32* proc_out_size_per_ch);
extern bool SRC_ATTR_MIPs16 AUD_SRCMainIP_Init(void * void_src_ip, void * void_set_stc ,
                        s32  s32ChNum ,
                        s32  s32InSamplRate);
extern bool AUD_SRCMainIP_Proc(void * void_src_ip,
                          s16* ps16Insample_buffer , s32  proc_input_size_per_ch,
                          s16* ps16Tmpsample_buffer, s32  proc_tmp_size_per_ch,
                          s16* ps16Outsample_buffer, s32  proc_output_size_per_ch,
						  s32* real_output_size_per_ch);
extern bool AUD_SRCMainIP_CheckAndUpdate( void *void_src_ip , void * void_set_stc );
extern bool SRC_ATTR_MIPs16 AUD_SRCMainIP_Close(void * void_src_ip, void * void_set_stc );
*/


typedef struct SRCCONVERT_FuncTable
{
    FP_AUD_SRCContInterface_SetPower*            fnSRC_SetPower;
    FP_AUD_SRCContInterface_SetSampleingRate*    fnSRC_SetSampRate;
    FP_AUD_SRCContInterface_SetSelectRule*       fnSRC_SetRule;
    FP_AUD_SRCMainIP_GetOutputSamplingRate*      fnSRC_GetTarOutSampRate;
    FP_AUD_SRCMainIP_GetOutputSampleSize*        fnSRC_GetTarOutSampSize;
    FP_AUD_SRCMainIP_Init*                       fnSRC_Init;
    FP_AUD_SRCMainIP_Proc*                       fnSRC_Proc;
    FP_AUD_SRCMainIP_CheckAndUpdate*             fnSRC_CheckAndUpdate;
    FP_AUD_SRCMainIP_Close*                      fnSRC_Close;
}SRCCONVERT_FUNCTABLE;

#ifdef  CYGCFG_COMMON_PACKAGE
#define SRCCONVERT_FP               ((SRCCONVERT_FUNCTABLE *)&__audio_functab_start)
#else
extern SRCCONVERT_FUNCTABLE         SRCCONVERTTable;
#define SRCCONVERT_FP               (&SRCCONVERTTable)
#endif

#define fnPCM_SRC_SetPower                SRCCONVERT_FP->fnSRC_SetPower
#define fnPCM_SRC_SetSampRate             SRCCONVERT_FP->fnSRC_SetSampRate
#define fnPCM_SRC_SetRule                 SRCCONVERT_FP->fnSRC_SetRule
#define fnPCM_SRC_GetTarOutSampRate       SRCCONVERT_FP->fnSRC_GetTarOutSampRate
#define fnPCM_SRC_GetTarOutSampSize       SRCCONVERT_FP->fnSRC_GetTarOutSampSize
#define fnPCM_SRC_Init                    SRCCONVERT_FP->fnSRC_Init
#define fnPCM_SRC_CheckAndUpdate          SRCCONVERT_FP->fnSRC_CheckAndUpdate
#define fnPCM_SRC_Proc                    SRCCONVERT_FP->fnSRC_Proc
#define fnPCM_SRC_Close                   SRCCONVERT_FP->fnSRC_Close


#ifdef ENABLE_SBCENC
extern SBCENCBUF_SDRAM *SBCEncDRAM_cached;
#endif
//------------------------------------------------------------
//------------------------------------------------------------
#ifdef ENABLE_SRCCONVERT
extern AUDIOSRC_SDRAM *AudSrcDRAM_cached;
#endif


#endif
