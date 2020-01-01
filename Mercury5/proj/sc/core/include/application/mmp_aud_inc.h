//==============================================================================
//
//  File        : mmp_aud_inc.h
//  Description : INCLUDE File for Audio Function
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_AUD_INC_H_
#define _MMP_AUD_INC_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

// Audio Play Memory Mode Handshake Buffer
#define AUDIO_PLAY_R_HPTR_OFST                  (0)
#define AUDIO_PLAY_R_PTR_OFST                   (4)
#define AUDIO_PLAY_FINISH_SEEK_W                (8)
#define AUDIO_PLAY_START_SEEK_W                 (10)
#define AUDIO_PLAY_FILE_SEEK_OFFSET_L_W         (12)
#define AUDIO_PLAY_FILE_SEEK_OFFSET_H_W         (14)
#define AUDIO_PLAY_W_HPTR_OFST                  (16)
#define AUDIO_PLAY_W_PTR_OFST                   (20)

// Audio Record Memory Mode Handshake Buffer
#define AUDIO_REC_WRITE_HIGH_PTR_OFFSET_D       (0)
#define AUDIO_REC_WRITE_PTR_OFFSET_D            (4)
#define AUDIO_REC_READ_HIGH_PTR_OFFSET_D        (8)
#define AUDIO_REC_READ_PTR_OFFSET_D             (12)

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================

typedef void (*MMP_LivePCMCB) (void*, MMP_ULONG);

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

// Audio codec type
typedef enum MMP_AUDIO_CODEC{
    MMP_AUDIO_CODEC_MP3,
    MMP_AUDIO_CODEC_AMR,
    MMP_AUDIO_CODEC_AAC,
    MMP_AUDIO_CODEC_WMA,
    MMP_AUDIO_CODEC_OGG,
    MMP_AUDIO_CODEC_RA,
    MMP_AUDIO_CODEC_WAV,
    MMP_AUDIO_CODEC_MIDI,
    MMP_AUDIO_CODEC_RAWPCM,
    MMP_AUDIO_CODEC_G711,
    MMP_AUDIO_CODEC_INVALID
} MMP_AUDIO_CODEC;

// Audio input channel, it depends on the board schematic
typedef enum _MMP_AUD_LINEIN_CH {
    MMP_AUD_LINEIN_DUAL = 0x0,  ///< Dual channel line in
    MMP_AUD_LINEIN_R    = 0x1,  ///< Right channel line in
    MMP_AUD_LINEIN_L    = 0x2,  ///< Left channel line in
    MMP_AUD_LINEIN_SWAP = 0x3   ///< Dual channel, L and R swap
} MMP_AUD_LINEIN_CH;

// Audio input/output path
typedef enum _MMP_AUD_INOUT_PATH {
    /* AFE input path */
    MMP_AUD_AFE_IN              = 0x000001,
    MMP_AUD_AFE_IN_SING         = 0x000002, ///< AUXL/AUXR
    MMP_AUD_AFE_IN_DIFF         = 0x000004, ///< LIP/LIN/RIP/RIN
    //MMP_AUD_AFE_IN_DIFF2SING    = 0x000008, ///< LIP/RIP
    MMP_AUD_AFE_IN_MASK         = 0x00000F,
    /* AFE output path */
    //MMP_AUD_AFE_OUT             = 0x000100,
    //MMP_AUD_AFE_OUT_HP          = 0x000200, ///< HP_OUT (LOUT/ROUT)
    //MMP_AUD_AFE_OUT_HP_INVT     = 0x000400, ///< HP_OUT Inverter (LOUT/ROUT)
    MMP_AUD_AFE_OUT_LINE        = 0x000800, ///< LINE_OUT (LOUT2/ROUT2)
    MMP_AUD_AFE_OUT_LINE_INVT   = 0x001000, ///< LINE_OUT Inverter (LOUT2/ROUT2)
    MMP_AUD_AFE_OUT_MASK        = 0x001F00,
    /* I2S path */
    MMP_AUD_I2S_INOUT           = 0x010000,
    MMP_AUD_I2S0                = 0x020000, ///< I2S channel 0
    MMP_AUD_I2S1                = 0x040000, ///< I2S channel 1
    MMP_AUD_I2S2                = 0x080000, ///< I2S channel 2
    MMP_AUD_I2S_MASK            = 0x0F0000,
        #define I2S_PATH(ch)    (1 << (ch + 4))
    MMP_AUD_DMIC_PAD0			= 0x100000,
    MMP_AUD_DMIC_PAD1           = 0x200000,
    MMP_AUD_DMIC_PAD2           = 0x400000,
    MMP_AUD_DMIC_MASK           = 0xF00000
} MMP_AUD_INOUT_PATH;

// Audio high pass filter mode
typedef enum _MMP_AUD_HPF_MODE {
    MMP_AUD_HPF_AUD_2HZ=0,
    MMP_AUD_HPF_AUD_4HZ,
    MMP_AUD_HPF_AUD_8HZ,
    MMP_AUD_HPF_AUD_16HZ,
    MMP_AUD_HPF_VOC_2D5HZ,
    MMP_AUD_HPF_VOC_25HZ,
    MMP_AUD_HPF_VOC_50HZ,
    MMP_AUD_HPF_VOC_100HZ,
    MMP_AUD_HPF_VOC_200HZ,
    MMP_AUD_HPF_VOC_300HZ,
    MMP_AUD_HPF_VOC_400HZ,
    MMP_AUD_HPF_BYPASS 
} MMP_AUD_HPF_MODE;

// Gapless Operation
typedef enum _MMP_AUDIO_GAPLESS_OP
{
    MMP_AUDIO_GAPLESS_SEEK     = 0x0001,
    MMP_AUDIO_GAPLESS_PAUSE    = 0x0002,
    MMP_AUDIO_GAPLESS_STOP     = 0x0004,
    MMP_AUDIO_GAPLESS_OP_ALL   = 0x0007
} MMP_AUDIO_GAPLESS_OP;

// Encode Format
typedef enum _MMP_AUDIO_ENCODE_FMT
{
    MMP_AUDIO_VAMR_ENCODE   = 0,    ///< video + amr encode mode
    MMP_AUDIO_VAAC_ENCODE   = 1,    ///< video + aac encode mode
    MMP_AUDIO_AMR_ENCODE    = 2,    ///< pure amr encode mode
    MMP_AUDIO_AAC_ENCODE    = 3,    ///< pure aac encode mode
    MMP_AUDIO_MP3_ENCODE    = 4,    ///< pure mp3 encode mode
    MMP_AUDIO_WAV_ENCODE    = 5,    ///< pure wav encode mode
    MMP_AUDIO_VADPCM_ENCODE = 6,    ///< video + adpcm encode mode
    MMP_AUDIO_VMP3_ENCODE   = 7,    ///< video + mp3 encode mode
    MMP_AUDIO_G711_ENCODE   = 8,    ///< G711 mu law encode mode
    MMP_AUDIO_VPCM_ENCODE   = 9,    ///< video + raw PCM encode mode
    MMP_AUDIO_PCM_ENCODE    = 10,   ///< pure pcm encode mode
    MMP_AUDIO_UAC_ENCODE    = 0xE0, ///< UAC mode
    MMP_AUDIO_ENCODE_NONE   = 0xFF
} MMP_AUDIO_ENCODE_FMT;

// Decode Format
typedef enum _MMP_AUDIO_DECODE_FMT
{
    MMP_AUDIO_MP3_PLAY      = 0,    ///< mp3 play mmode
    MMP_AUDIO_MIDI_PLAY     = 1,    ///< midi play mode
    MMP_AUDIO_AMR_PLAY      = 2,    ///< amr play mode
    MMP_AUDIO_WMA_PLAY      = 3,    ///< wma play mode
    MMP_AUDIO_AAC_PLAY      = 4,    ///< aac play mode
    MMP_AUDIO_PCM_PLAY      = 5,    ///< pcm play mode
    
    MMP_AUDIO_AACPLUS_PLAY  = 7,    ///< aac+ play mode
    
	MMP_AUDIO_OGG_PLAY      = 9,    ///< ogg play mode
    MMP_AUDIO_VAMR_PLAY     = 10,   ///< video + amr play mode
    MMP_AUDIO_VAAC_PLAY     = 11,   ///< video + aac play mode
	MMP_AUDIO_RA_PLAY       = 12,   ///< ra play mode
	MMP_AUDIO_WAV_PLAY      = 13,   ///< wav play mode
	MMP_AUDIO_VMP3_PLAY     = 14,   ///< video + mp3 play mode
    MMP_AUDIO_AC3_PLAY      = 15,   ///< ac3 play mmode	
	MMP_AUDIO_VAC3_PLAY     = 16,   ///< video + ac3 play mode
	MMP_AUDIO_VRA_PLAY      = 17,   ///< video + ra play mode
	MMP_AUDIO_VWMA_PLAY     = 18,   ///< video + wma play mode
	MMP_AUDIO_VWAV_PLAY     = 19,   ///< video + wav play mode
	MMP_AUDIO_FLAC_PLAY     = 20,    ///< flac play mode
	MMP_AUDIO_ERR_PLAY_FMT	= 21  ///
} MMP_AUDIO_DECODE_FMT;

// Gain Change Mode
typedef enum _MMP_AUD_GAIN_CHANGE_MODE {
    MMP_AUD_GAIN_UPDATE_DIRECT,
    MMP_AUD_GAIN_UPDATE_SMOOTH    
} MMP_AUD_GAIN_CHANGE_MODE;

// Audio Player Type
typedef enum _MMP_AUD_PLAYER_TYPE {
    MMP_AUD_PLAYER_TYPE_AUDIO = 0,
    MMP_AUD_PLAYER_TYPE_AUI,
    MMP_AUD_PLAYER_TYPE_NUM
} MMP_AUD_PLAYER_TYPE;
//==============================================================================
//
//                              ENUMERATION (Gain settings)
//
//==============================================================================
typedef enum _MMP_AUD_GAIN_MIC_PREGAIN {
    MMP_AUD_GAIN_MIC_PREGAIN_0dB = 0,
	MMP_AUD_GAIN_MIC_PREGAIN_6dB,
	MMP_AUD_GAIN_MIC_PREGAIN_13dB,
	MMP_AUD_GAIN_MIC_PREGAIN_23dB,
	MMP_AUD_GAIN_MIC_PREGAIN_30dB,
	MMP_AUD_GAIN_MIC_PREGAIN_36dB,
	MMP_AUD_GAIN_MIC_PREGAIN_MAX
} MMP_AUD_GAIN_MIC_PREGAIN;

typedef enum _MMP_AUD_GAIN_ADC_ANALOG {
    MMP_AUD_GAIN_MIC_ADC_ANALOG_M6dB = 0,  //Minus 6 dB
	MMP_AUD_GAIN_MIC_ADC_ANALOG_M3dB,
	MMP_AUD_GAIN_MIC_ADC_ANALOG_0dB,
	MMP_AUD_GAIN_MIC_ADC_ANALOG_P3dB,	   //Positive 6dB
	MMP_AUD_GAIN_MIC_ADC_ANALOG_P6dB,
	MMP_AUD_GAIN_MIC_ADC_ANALOG_P9dB,
	MMP_AUD_GAIN_MIC_ADC_ANALOG_P12dB,
	MMP_AUD_GAIN_MIC_ADC_ANALOG_P15dB,
	MMP_AUD_GAIN_MIC_ADC_ANALOG_MAX
} MMP_AUD_GAIN_ADC_ANALOG;

//==============================================================================
//
//                              ENUMERATION (I2S)
//
//==============================================================================

// I2S Channel ID
typedef enum _MMP_I2S_CH {
    MMP_I2S_CH0 = 0,
    MMP_I2S_CH1,
    MMP_I2S_CH2,
	MMP_I2S_CH_NUM,
	MMP_I2S_CH_DEFAULT = MMP_I2S_CH0
} MMP_I2S_CH;

// I2S Working Mode
typedef enum _MMP_I2S_WORK_MODE {
    MMP_I2S_WORK_MODE_NONE = 0,
    MMP_I2S_MASTER_MODE,             ///< BCK & LRCK is outputed by AIT
    MMP_I2S_SLAVE_MODE,              ///< BCK & LRCK is outputed by external codec
    MMP_I2S_MAX_WORK_MODE
} MMP_I2S_WORK_MODE;

// I2S Mclk Mode
typedef enum _MMP_I2S_MCLK_MODE {
    MMP_I2S_MCLK_MODE_NONE = 0,
    MMP_I2S_128FS_MODE,              ///< 128*fs clock output
    MMP_I2S_192FS_MODE,              ///< 192*fs clock output
    MMP_I2S_256FS_MODE,              ///< 256*fs clock output
    MMP_I2S_384FS_MODE,              ///< 384*fs clock output
    MMP_I2S_512FS_MODE,              ///< 512*fs clock output
    MMP_I2S_768FS_MODE,              ///< 768*fs clock output
    MMP_I2S_1024FS_MODE,             ///< 1024*fs clock output
    MMP_I2S_1536FS_MODE,             ///< 1536*fs clock output
    MMP_I2S_FIX_256FS_MODE,          ///< fixed 256*fs clock output
    MMP_I2S_USB_MODE,                ///< fixed clock output
    MMP_I2S_MAX_MCLK_MODE
} MMP_I2S_MCLK_MODE;

// I2S Output Bit Size
typedef enum _MMP_I2S_OUT_BITS {
    MMP_I2S_OUT_BITS_NONE = 0,
    MMP_I2S_OUT_16BIT,               ///< 16 bits for each channel
    MMP_I2S_OUT_24BIT,               ///< 24 bits for each channel
    MMP_I2S_OUT_32BIT,               ///< 32 bits for each channel
    MMP_I2S_MAX_OUT_BIT_MODE
} MMP_I2S_OUT_BITS;

// I2S WS Clock Polarity
typedef enum _MMP_I2S_WS_POLARITY {  ///< word select polarity
    MMP_I2S_LRCK_POLARITY_NONE = 0,
    MMP_I2S_LRCK_L_LOW,              ///< L channel is low, R channel is high
    MMP_I2S_LRCK_L_HIGH,             ///< L channel is high, R channel is low
    MMP_I2S_MAX_WS_POLARITY
} MMP_I2S_WS_POLARITY;

// I2S Output Delay Mode
typedef enum _MMP_I2S_DELAY_MODE {
    MMP_I2S_OUT_DELAY_NONE = 0,
    MMP_I2S_OUT_DELAY_I2S,           ///< I2S mode output data delay
    MMP_I2S_OUT_DELAY_STD,           ///< standard mode output data delay
    MMP_I2S_MAX_OUT_DELAY_MODE
} MMP_I2S_DELAY_MODE;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMP_AUDIO_AACPLUS_INFO {
    MMP_ULONG   ulBitRate;      // bit rate
    MMP_USHORT  usSampleRate;   // sampling rate
    MMP_USHORT  usHeaderType;   // header type : 0->unknown, 1->ADIF, 2->ADTS
    MMP_USHORT  usChans;        // channel num
    MMP_ULONG	ulTotalTime;    // file total time(unit: sec)
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
} MMP_AUDIO_AACPLUS_INFO;

typedef struct _MMP_AUDIO_FLAC_INFO {
    MMP_ULONG   ulBitRate;      // bit rate
    MMP_ULONG64 ulTotalSamples; // total samples
    MMP_USHORT  usSampleRate;   // sampling rate
    MMP_USHORT  usChans;        // channel num
    MMP_ULONG	ulTotalTime;    // file total time(unit: sec)
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
} MMP_AUDIO_FLAC_INFO;

typedef struct _MMP_AUDIO_MIDI_INFO {
    MMP_USHORT  usSampleRate;   // sampleing rate
    MMP_ULONG   ulTotalTime;    // total time(unit: milli-sec)
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
} MMP_AUDIO_MIDI_INFO;

typedef struct _MMP_AUDIO_MP3_INFO {
    MMP_ULONG 	ulBitRate;      // unit: bps
    MMP_USHORT  usSampleRate;   // unit: Hz
    MMP_USHORT  usChans;        // 1->mono, 2->stereo
    MMP_USHORT  usLayer;        // 3->layer 3
    MMP_USHORT  usVersion;      // 0->MPEG1, 1->MPEG2, 2->MPEG2.5
    MMP_ULONG	ulTotalTime;    // unit: milli-sec
	MMP_USHORT	usVbr;          // 0 : CBR, 1 : VBR
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
    MMP_BOOL    bIsMp3HdFile;   // MMP_TRUE: mp3HD file
} MMP_AUDIO_MP3_INFO;

typedef struct _MMP_AUDIO_AMR_INFO {
    MMP_ULONG   ulBitRate;      // bit rate
    MMP_USHORT	usMode;         // 0 : 4.75k, 7 : 12.2k
    MMP_USHORT	usSampleSize;   // frame size
    MMP_USHORT  usSampleRate;   // sample rate
    MMP_ULONG	ulTotalTime;    // unit: milli-sec
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
} MMP_AUDIO_AMR_INFO;

typedef struct _MMP_AUDIO_WMA_INFO {
    MMP_ULONG   ulBitRate;      // bit rate
    MMP_ULONG   ulSampleRate;   // sampling rate
    MMP_USHORT  usChans;        // channel num
    MMP_USHORT  usBitsPerSample;// bit per sample
    MMP_ULONG	ulTotalTime;    // unit: milli-sec
    MMP_USHORT  usTagInfo;      // 0 : no tag, 1 : tag exist
    MMP_USHORT  usVbrInfo;      // 0 : CBR, 1 : VBR
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
    MMP_USHORT  usVersion;      // 0, 1, 2: WMA Std Bitstream, 3: WMA Pro Bitstream
} MMP_AUDIO_WMA_INFO;

typedef struct _MMP_AUDIO_RA_INFO {
    MMP_ULONG   ulBitRate;      // bit rate
    MMP_USHORT  usSampleRate;   // sampling rate
    MMP_USHORT  usChans;        // channel num
    MMP_ULONG	ulTotalTime;    // unit: milli-sec
    MMP_USHORT  usVbrInfo;      // 0 : CBR, 1 : VBR
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
    MMP_BOOL    bSeekable;      // 0 : non-seekable; 1 : seekable
} MMP_AUDIO_RA_INFO;

typedef struct MMP_AUDIO_OGG_INFO {
    MMP_ULONG   ulBitRate;      // bit rate
    MMP_USHORT  usSampleRate;   // sampling rate
    MMP_USHORT  usChans;        // channel num
    MMP_ULONG	ulTotalTime;    // unit: milli-sec
    MMP_USHORT  usTagInfo;      // 0 : no tag, 1 : tag exist
    MMP_USHORT  usVbrInfo;      // 0 : CBR, 1 : VBR
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
} MMP_AUDIO_OGG_INFO;

typedef struct _MMP_AUDIO_OGG_TAG_INFO {
    MMP_ULONG	title_len;
    MMP_ULONG   version_len;
    MMP_ULONG	album_len;
    MMP_ULONG	artist_len;
    MMP_ULONG   copyright_len;
    MMP_ULONG   description_len;
} MMP_AUDIO_OGG_TAG_INFO;

typedef struct _MMP_AUDIO_WAV_INFO {
    MMP_ULONG   ulBitRate;      // bit rate
    MMP_ULONG   ulTotalTime;    // unit: milli-sec
    MMP_ULONG   ulSampleRate;   // sampling rate
    MMP_ULONG   ulNewSampleRate;// new sampling rate after converting
    MMP_USHORT  usChans;        // channel num
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
} MMP_AUDIO_WAV_INFO;

typedef struct _MMP_AUDIO_AAC_INFO {
    MMP_ULONG   ulBitRate;      // bit rate
    MMP_USHORT  usSampleRate;   // sampling rate
    MMP_USHORT  usHeaderType;   // header type:0->unknown, 1->ADIF, 2->ADTS
    MMP_USHORT  usChans;        // channel num
    MMP_ULONG	ulTotalTime;    // file total time(unit: sec)
    MMP_USHORT  usNotSupport;   // 0 : supported format; 1 : not supported format
} MMP_AUDIO_AAC_INFO;

/* Wind noise reduction configuration */
typedef struct _MMP_AUDIO_WNR_CFG {
    MMP_BOOL    bEnWNR;         ///< Noise filter enable
    MMP_BOOL    bEnNR;          ///< Noise reduction enable
} MMP_AUDIO_WNR_CFG;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

#endif //_MMP_AUD_INC_H_
