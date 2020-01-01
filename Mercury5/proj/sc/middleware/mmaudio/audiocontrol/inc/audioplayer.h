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
#ifndef _AUDPLAYER_H
#define _AUDPLAYER_H

//-----------------------------------------------------------------------------
//Include Files
//-----------------------------------------------------------------------------
#ifndef PIONEER_PLAYER
//#include <sys/bsdtypes.h>
//#include <cyg/kernel/kapi.h>
//#include <cyg/infra/diag.h>
//#include <cyg/hal/plf_intr.h>
#endif

#include "ms_io.h"
#include "srv_resmgr_mmlaudio_types.h" // Lib release stage1's workaround

//-----------------------------------------------------------------------------
//Global Variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Global definition
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Structure PRE Declaration
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Global Function Prototype
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Function Declaration
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Structure Declaration
//-----------------------------------------------------------------------------


#define __MDL_AUD_PLAY_RINGBUF__

//#define MAX_FILE_NAME_LENGTH            (262*2)
//#define FILENAMESIZE                    (2*(MAX_FILE_NAME_LENGTH+4*2))

typedef enum AUDIO_DOUBLE_BUFFER_ID
{
    AUDIO_DOUBLE_BUF_A = 0x1,
    AUDIO_DOUBLE_BUF_B = 0x2,
} AUDIO_DOUBLE_BUFFER;

typedef enum
{
    AUDIO_DOUBLE_BUF_FLAG = 0x01
}AUDIOPLAY_FLAG;

typedef enum
{
    AUDIO_PLAY_END = 0x0,
    AUDIO_PLAYING = 0x1,
}AUDIOPLAY_STATUS;

#if 0
typedef enum
{
    AUDIO_INPUT_SD          = 0x0,
    AUDIO_INPUT_NOR         = 0x1,
    //AUDIO_INPUT_STREAMING   = 0x2,
}AUDIOPLAY_INPUT_PATH;
#endif
typedef struct _audio_rbuffer{
    #ifndef __MDL_AUD_PLAY_RINGBUF__
    s32 bytes_into_buffer_a;
    s32 bytes_into_buffer_b;
    u8 *buf_read_offset_a;
    u8 *buf_read_offset_b;
    u8  buf_reading;
    u8 *buffer_a;
    u8 *buffer_b;
    s32 bufsize;
    s32 readsize;
    #endif
    int at_eof;
    u32 filesize;
    MSFILE infile;
    u32 audmem_remainsize;
    u32 audmem_consumsize;
    u8 *audmem_streamadr;
    u32 audmem_streamsize;
    u8 validdata_end;
    u8 memmode;
    u8 u8inputpath;
} audio_rbuffer;

#ifndef PIONEER_PLAYER
typedef struct _player_common_inst {
    ms_fnchar *file_name;
    int file_type;
    int audio_only;
} player_common_inst;

typedef enum
{
    MMP_FILE_UNKNOWN = 0,
    MMP_FILE_MP3     = 1,
    MMP_FILE_3GP     = 2,
    MMP_FILE_JPEG    = 3,
    MMP_FILE_AMR     = 4,
    MMP_FILE_AAC     = 5,
    MMP_FILE_BMP     = 6,
    MMP_FILE_GIF     = 7,
    MMP_FILE_PNG     = 8,
    MMP_PCM_STREAM   = 9,
#if defined(CYGCFG_T_TIVC_ENABLE)
    MMP_FILE_TMP4    = 10,
#endif
    MMP_FILE_MIDI    = 11,
    MMP_FILE_264     = 12,
    MMP_FILE_263     = 13,
    MMP_FILE_FLV1    = 14,
    MMP_FILE_M4V     = 15,
    MMP_FILE_MP4     = 16,
    MMP_FILE_WAV     = 17,
    MMP_FILE_PCM     = 18,
    MMP_FILE_RM      = 19,
    MMP_FILE_RVC     = 20,
    MMP_FILE_QRCODE  = 21,
    MMP_CMMB_STREAM  = 22,
    MMP_FILE_AVI     = 23,
    MMP_FILE_MPG     = 24,
    MMP_FILE_AMRWB     = 25,
    MMP_FILE_WMA   = 26,
    MMP_FILE_COOK   = 27,
    MMP_FILE_APE   = 29,
} MMP_FILE_TYPE;
#endif



typedef struct _player_mem_addr {
    u8 *codeclayer2addr;
    u32 codeclayer2size;
    unsigned char* iisaddr;
    unsigned int iislen;
    unsigned char* sourcebuf1;
    unsigned char* sourcebuf2;
    unsigned int sourcebuflen;

    unsigned char* playreadstack;
    unsigned int playreadstacksize;
    unsigned char* playalarmstack;
    unsigned int playalarmstacksize;

	unsigned char* outputpcm;
    unsigned int outputpcmsize;

 	unsigned char* copybuf;
	unsigned int copybufsize;

	unsigned char* dcacheaddr;

    u32 parserbufsize;
    u32 codecbuf1size;
    u32 codecbuf2size;
    u32 codecbuf3size;
    u8 *parserbuf;
    u8 *parsertmpbuf;
    u8 *codecbuf1;
    u8 *codecbuf2;
    u8 *codecbuf3;
} player_mem_addr;

typedef struct _player_audiofun_addr {

    void (*func_init)(void *pinst);

    s32 (*open)( void *pinst,
                u32 *bits_per_sample,
                u32 *sample_rate,
                u16 *frame_length,
                u8 *channels,
                u32 *para);

    s32 (*seek_data) (void *pinst,
                    u32 *seektime);

    s32 (*decode_data) (void *pinst,
                     u8 **out_buf, u32 *out_size, u32 *IISthreshold, u32 *u32consume_size);

    u32 (*close)(void *pinst);

    /*get continuing audio frame num*/

    s32 (*get_timestamp)(void *pinst, u32 *pu32Pos);

    void (*engine_clock)(void *pinst, u8 onoff);

}player_audiofunc_addr;

typedef struct _player_raw_stream_media_info{

    MmlAudioSamplingRate_e    eSamplingRate;
    MmlAudioBitsPerSample_e   eBitsPerSample;
    MmlAudioChannelMode_e    eChannelMode;

}player_raw_stream_media_info;

typedef struct _audioplayer_s_
{
    player_common_inst     comm_inst;

    player_audiofunc_addr  *audio_func_addr;

    player_mem_addr        mem_addr;

    player_raw_stream_media_info    raw_stream_media_info;

    void *pthis;

    u8 u8sd_error;
	MSFILE file_handle;

    u8 u8sbcenable;
    u8 u8dmareset;
    u8 u8Pause;
    u8 u8pcmforcestop;
    u8 iStop;

    u8 iPlayend;
    u8 iPlayend_mode;
    u8 memmode;
    MmlAudioInputType_e u8inputpath;
    u8 *audmem_sharebuf;
    u32 audmem_sharebufsize;
    u32 audmem_consumsize;
    s32 gain_setting;

    s32 EQMode;
    s32 downmix_en;

    u32 sample_rate;
    u32 bit_rate;
    u32 nCopySize;
    u32 Spec_handle;
    u32 streamThreshold;
    u32 total_time_ex;
    u32 total_time;
    s32 codec_mem_addr1;
    s32 codec_mem_addr2;
    s32 codec_sram_size;
    s32 codec_dram_size;

}audioplayer_s;


extern s32 init_audio_codec(void *player, s32 data_fmt);


#ifdef PIONEER_PLAYER
int _Audio_copy_rbuffer(audio_rbuffer *b, u8 *dest_buf, s32 bytes);
s32 _Audio_fill_rbuffer(audio_rbuffer *b);
s32 _Audio_advance_rbuffer(audio_rbuffer *b, s32 bytes);
s32 _Audio_rbuffer_reset_buf(audio_rbuffer *b,u8 *bufa, u8 *bufb, u32 bufsize);
s32 _Audio_rbuffer_init(audio_rbuffer *b, MSFILE rfile,void *pinst);
#endif

#endif //_AUDPLAYER_H
