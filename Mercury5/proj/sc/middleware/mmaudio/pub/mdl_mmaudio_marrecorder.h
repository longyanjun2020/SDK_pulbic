#ifndef _PUB_AUD_MARRECORDER_H
#define _PUB_AUD_MARRECORDER_H

#if 1
#include "sys_MsWrapper_cus_os_type.h"
#include "srv_resmgr_mmlaudio_types.h"
#include "mdl_vfs_file.ho"

#define __MDL_AUD_REC_RINGBUF__

//move to ms_io.h
//#define MAX_FILE_NAME_LENGTH            (262*2)
//#define FILENAMESIZE                    (2*(MAX_FILE_NAME_LENGTH+4*2))

#define __MDL_AUD_REC_DYN_TASK__

typedef enum
{
    MAR_FILE_RENEW       = 0,
    MAR_FILE_APPEND      = 1,
} MAR_FILE_MODE;

typedef struct _recorder_func_addr
{

    s32(*open)(void *pinst,
               s32 s32dtx_enable,
               u32 *u32samplebuffer,
               u32 *u32bits_per_sample,
               u32 *u32sample_rate,
               u32 *u32frame_length,
               u32 *u32channels,
               u32 *u32para);


    s32(*encode_data)(void *encoder,
                      s32 *out_size,
                      u32 *u32rectotaltime,
                      u32 *u32rectotalsize,
                      s32 s32first_frame);

    /*get continuing audio frame num*/

    //s32(*get_timestamp)(void *pinst, u32 *pu32Pos);

    void (*engine_clock)(void *pinst, u8 onoff);

    s32(*close)(void *pinst);

    s32(*write_close)(void *pinst , s32 *seek_offt, s32 *wsize, u8** wsrcptr);

} recorder_func_addr;


typedef struct _mar_input_setting
{
    u8  u8channels;
    MAR_FILE_MODE  u8append_mode;
    u8  u8sample_convert;
    MmlAudioInputType_e u16inputpath;
    u16 u16outputpath;
    u16 u16format;
    u16 u16samplerate;
    u32 u32bitrate;
} mar_input_setting;

typedef struct _recorder_common_inst
{
    u16 *file_name;
    u16 *path_name;
    s32 file_type;
    s32 audio_only;
    MmlFilenameFormat_e eFilenameFormat;
} recorder_common_inst;

typedef struct _recorder_mem_addr
{
    u8 *codeclayer2addr;
    u32 codeclayer2size;

    u8* heapbuf;
    u32 heapbuflen;

#ifndef __MDL_AUD_REC_RINGBUF__
    u8* storagebuf1;
    u8* storagebuf2;
    u32 storagebuflen;
#endif

    u8* encdatabuf;
    u32 encdatabuflen;
    u32 encheaderlen;

    u8* srcinbuf;
    u32 srcinbufsize;
    u8* srctmpbuf;
    u32 srctmpbufsize;

    u8* pcmbuf;
    u32 pcmbuflen;
    u8* pcmtmpbuf;
    u32 pcmtmpbufsize;

#ifdef __FM_PEQ_ENABLE__
    u8 *ringbuftmpbuf;
    u32 ringbuftmpbufsize;
    u32 ringbuftmpdatasize;
#endif    

    u32 u32FullThreshold;

} recorder_mem_addr;


typedef struct _recorder_storge_buf
{

    u8 u8rec_wbuf_idx;
    u8 u8rec_sbuf_flag;
    u8* u8storagebufptr;
    u8* u8storagebuf;
    u32 u32storagesize;

} recorder_storge_buf;

typedef struct _encoder_info_s_
{
    s32 s32dtx_enable;
    u32 u32sample_buffer;
    u32 u32bits_per_sample;
    u32 u32sample_rate;
    u32 u32frame_length;
    u32 u32channels;
    u32 u32para;
} encoder_info_s;


typedef struct _recorder_codec_para
{
    void  *st;
    u16   *pcm_in;
    s32   frames;
} recorder_codec_para;


typedef struct _marrecorder_s_
{
    recorder_func_addr      *rec_func_addr;

    recorder_func_addr      rec_func;

    mar_input_setting       rec_input_set;

    recorder_common_inst     comm_inst;

    recorder_mem_addr        mem_addr;

    recorder_storge_buf      storge_buf;

    encoder_info_s           encoder_info;

    recorder_codec_para      rec_codec_para;

    void *pthis;
    void *voidsample_ptr;
    u32 u32samplesize;
    s32 s32first_frame;
    u32 *pOutMemBuf;

    u8 u8Pause;
    u8 u8forcestop;
    u8 iStop;
    u8 u8Resume;

    u8 bs_format;

    u8 u8_input_channel;

    MmlAudioResult_e u32mar_stop_type;
    u32 u32mar_status;

    u32 u32enc_timestamp;
    u32 u32enc_timestamp_prev;
    u32 u32enc_size;

    u32 u32TimeLimit;
    u32 u32SizeLimit;

    u32 u32FreeCapicity;

#ifdef __MDL_AUD_REC_RINGBUF__
    u32 rbHandle;
#endif

#ifdef __MDL_AUD_REC_DYN_TASK__
    MsTaskId_e nTaskId;
    u32 *nStackTopAddr;
#endif

    u32 error_notify_send; // record error notify have been send

    MmlAudioNotify_t *pErrorNotify;
    u32 nWaitRespCmd;
    u32 frameSize;	//single frame size    
    u32 oriFileSize;	//original filesize for Write Append
    u32 oriFileTime;	//original file total time for Write Append
    u32 FileSize_accum;
} marrecorder_s;
#endif
#endif
