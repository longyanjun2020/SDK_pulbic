//==============================================================================
//
//  File        : mmps_audio.h
//  Description : Audio User Application Interface
//  Author      : Hnas Liu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_audio.h
 *  @brief Header File for the Host Audio Player/Recorder API.
 *  @author Hans Liu
 *  @version 1.0
 */

#ifndef _MMPS_AUDIO_H_
#define _MMPS_AUDIO_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpd_audio.h"
#include "mmpd_audiodb.h"
#include "mmpd_id3.h"

/** @addtogroup MMPS_AUDIO
@{
*/

#if (WNR_EN)
/* Wind noise reduction configuration */
typedef MMP_AUDIO_WNR_CFG MMPS_AUDIO_WNR_CFG;
#endif

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define AUDIO_MAX_FILE_NAME_SIZE            (256)

#define MMPS_AUDIO_BANK_SIZE                (0x4000)
#define MMPS_AUDIO_DATA_BUF_SIZE            (MMPS_AUDIO_BANK_SIZE*2)

#define MMPS_AUDIO_MUSICLIST_MAX_OBJECT     (1200)  ///< maxium object num
#define MMPS_AUDIO_OBJ_PROPERTY_STR_LEN     (256)   ///< object property string length
#define MMPS_AUDIO_MAX_OBJ_REFERENCE_NUM    (400)   ///< maxium object reference num
#define MMPS_AUDIO_MAX_FILE_NAME_LEGTH      (260)   ///< maxium file name length
#define MMPS_AUDIO_MAX_OBJ_PROPERTY_NUM     (100)   ///< maxium propty num for artist,genre,albumname

#define MMPS_AUDIO_MUSICLIST_FILENAME       ("SD:\\FileListInfo")
#define MMPS_AUDIO_DRMHDS_FILENAME          ("SD:\\jazz1.hds")

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPS_AUDIO_UNIT_ID {
	MMPS_AUDIO_INTERNAL_CODEC = 0,
	MMPS_AUDIO_EXTERNAL_CODEC,
	MMPS_AUDIO_HDMI
} MMPS_AUDIO_UNIT_ID;

// Audio in path
typedef enum _MMPS_AUDIO_IN_PATH
{
    MMPS_AUDIO_IN_AFE_SING      = MMP_AUD_AFE_IN_SING,
    MMPS_AUDIO_IN_AFE_DIFF      = MMP_AUD_AFE_IN_DIFF,
    //MMPS_AUDIO_IN_AFE_DIFF2SING = MMP_AUD_AFE_IN_DIFF2SING,
    MMPS_AUDIO_IN_AFE_MASK      = MMP_AUD_AFE_IN_MASK,
    MMPS_AUDIO_IN_I2S0          = MMP_AUD_I2S0,
    MMPS_AUDIO_IN_I2S1          = MMP_AUD_I2S1,
    MMPS_AUDIO_IN_I2S2          = MMP_AUD_I2S2,
    MMPS_AUDIO_IN_I2S_MASK      = MMP_AUD_I2S_MASK
} MMPS_AUDIO_IN_PATH;

// Audio line in channel
typedef enum _MMPS_AUDIO_LINEIN_CHANNEL
{
    MMPS_AUDIO_LINEIN_DUAL      = 0x0,  ///< dual channel line in
    MMPS_AUDIO_LINEIN_R         = 0x1,  ///< Right channel line in
    MMPS_AUDIO_LINEIN_L         = 0x2,  ///< Left channel line in
    MMPS_AUDIO_LINEIN_SWAP      = 0x3   ///< dual channel, L and R swap
} MMPS_AUDIO_LINEIN_CHANNEL;

// Audio out path
typedef enum _MMPS_AUDIO_OUT_PATH
{
    //MMPS_AUDIO_OUT_AFE_HP        = MMP_AUD_AFE_OUT_HP,
    //MMPS_AUDIO_OUT_AFE_HP_INVT   = MMP_AUD_AFE_OUT_HP_INVT,
    MMPS_AUDIO_OUT_AFE_LINE      = MMP_AUD_AFE_OUT_LINE,
    MMPS_AUDIO_OUT_AFE_LINE_INVT = MMP_AUD_AFE_OUT_LINE_INVT,
    MMPS_AUDIO_OUT_AFE_MASK      = MMP_AUD_AFE_OUT_MASK,
    MMPS_AUDIO_OUT_I2S0          = MMP_AUD_I2S0,
    MMPS_AUDIO_OUT_I2S1          = MMP_AUD_I2S1,
    MMPS_AUDIO_OUT_I2S2          = MMP_AUD_I2S2,
    MMPS_AUDIO_OUT_I2S_MASK      = MMP_AUD_I2S_MASK
} MMPS_AUDIO_OUT_PATH;

typedef enum _MMPS_AUDIO_ABMODE_SWITCH
{
    MMPS_AUDIO_AB_MODE_DISABLE = 0,     ///< ab mode diable
    MMPS_AUDIO_AB_MODE_ENABLE           ///< ab mode enable
} MMPS_AUDIO_ABMODE_SWITCH;

typedef enum _MMPS_AUDIO_AMR_ENCODEMODE
{
    MMPS_AUDIO_AMR_MR475_ENCODE_MODE = 0,   ///< 4.75K
    MMPS_AUDIO_AMR_MR515_ENCODE_MODE,       ///< 5.15k
    MMPS_AUDIO_AMR_MR590_ENCODE_MODE,       ///< 5.9k
    MMPS_AUDIO_AMR_MR670_ENCODE_MODE,       ///< 6.7k
    MMPS_AUDIO_AMR_MR740_ENCODE_MODE,       ///< 7.4k
    MMPS_AUDIO_AMR_MR795_ENCODE_MODE,       ///< 7.95k
    MMPS_AUDIO_AMR_MR102_ENCODE_MODE,       ///< 10.2k
    MMPS_AUDIO_AMR_MR122_ENCODE_MODE        ///< 12.2k
} MMPS_AUDIO_AMR_ENCODEMODE;

typedef enum _MMPS_AUDIO_SBC_CHANNEL
{
    MMPS_AUDIO_SBC_CHANNEL_MONO = 0,    ///< Mono channel
    MMPS_AUDIO_SBC_CHANNEL_DUAL,		///< Dual channel
    MMPS_AUDIO_SBC_CHANNEL_STEREO,      ///< stereo channel
    MMPS_AUDIO_SBC_CHANNEL_JOINT        ///< joint stereo channel
} MMPS_AUDIO_SBC_CHANNEL;

typedef enum _MMPS_AUDIO_SBC_METHOD
{
    MMPS_AUDIO_SBC_METHOD_LOUDNESS = 1,	///< loudness
    MMPS_AUDIO_SBC_METHOD_SNR	        ///< snr
} MMPS_AUDIO_SBC_METHOD;

typedef enum _MMPS_AUDIO_PLAY_STATUS
{
    MMPS_AUDIO_PLAY_START = 0x0100,     ///< play start
    MMPS_AUDIO_PLAY_PAUSE = 0x0200,     ///< play pause
    MMPS_AUDIO_PLAY_STOP  = 0x0400,     ///< play stop
    MMPS_AUDIO_PLAY_INVALID = 0x0800	///< invalid status
} MMPS_AUDIO_PLAY_STATUS;

typedef enum _MMPS_AUDIO_ABMODE_POS
{
    MMPS_AUDIO_AB_MODE_POINTA = 0x0300,	///< ab mode a point
    MMPS_AUDIO_AB_MODE_POINTB = 0x0400  ///< ab mode b point
} MMPS_AUDIO_ABMODE_POS;

typedef enum _MMPS_AUDIO_EQTYPE
{
    MMPS_AUDIO_PLAY_EQ_NONE =        0x0000, ///< no eq
    MMPS_AUDIO_PLAY_EQ_CLASSIC =     0x0100, ///< eq classic	
    MMPS_AUDIO_PLAY_EQ_JAZZ =        0x0200, ///< eq jazz
    MMPS_AUDIO_PLAY_EQ_POP =         0x0300, ///< eq pop
    MMPS_AUDIO_PLAY_EQ_ROCK =        0x0400, ///< eq rock
    MMPS_AUDIO_PLAY_EQ_BASS3 =       0x0500, ///< eq bass3
    MMPS_AUDIO_PLAY_EQ_BASS9 =       0x0600, ///< eq bass 9
    MMPS_AUDIO_PLAY_EQ_LOUDNESS =    0x0700, ///< eq loudness
    MMPS_AUDIO_PLAY_EQ_SPK =         0x0800, ///< eq speaker
    MMPS_AUDIO_PLAY_EQ_VIRTUALBASS =	0x0900, ///< eq virtual bass
    MMPS_AUDIO_PLAY_HP_SURROUND =    0x1000, ///< eq headphone surround
    MMPS_AUDIO_PLAY_SPK_SURROUND =    	0x2000  ///< eq speaker surround
} MMPS_AUDIO_EQTYPE;

typedef enum _MMPS_AUDIO_G711_ENCODEMODE
{
	MMPS_AUDIO_G711MU_RECORD_8K_64KBIT = 0
} MMPS_AUDIO_G711_ENCODEMODE;

// AAC Record SamplingRate BitRate
typedef enum _MMPS_AUDIO_AAC_ENCODEMODE
{
	MMPS_AUDIO_AAC_RECORD_16K_16K = 0, MMPS_AUDIO_AAC_RECORD_16K_24K, MMPS_AUDIO_AAC_RECORD_16K_32K,
	MMPS_AUDIO_AAC_RECORD_16K_64K, MMPS_AUDIO_AAC_RECORD_16K_96K, MMPS_AUDIO_AAC_RECORD_16K_128K,
	MMPS_AUDIO_AAC_RECORD_16K_160K, MMPS_AUDIO_AAC_RECORD_16K_192K,
	/////////////////////////////////////////////////////////////////////////
	MMPS_AUDIO_AAC_RECORD_22K_16K, MMPS_AUDIO_AAC_RECORD_22K_24K, MMPS_AUDIO_AAC_RECORD_22K_32K,
	MMPS_AUDIO_AAC_RECORD_22K_64K, MMPS_AUDIO_AAC_RECORD_22K_96K, MMPS_AUDIO_AAC_RECORD_22K_128K,
	MMPS_AUDIO_AAC_RECORD_22K_160K, MMPS_AUDIO_AAC_RECORD_22K_192K, MMPS_AUDIO_AAC_RECORD_22K_256K,
	/////////////////////////////////////////////////////////////////////////
	MMPS_AUDIO_AAC_RECORD_24K_16K, MMPS_AUDIO_AAC_RECORD_24K_24K, MMPS_AUDIO_AAC_RECORD_24K_32K,
	MMPS_AUDIO_AAC_RECORD_24K_64K, MMPS_AUDIO_AAC_RECORD_24K_96K, MMPS_AUDIO_AAC_RECORD_24K_128K,
	MMPS_AUDIO_AAC_RECORD_24K_160K, MMPS_AUDIO_AAC_RECORD_24K_192K, MMPS_AUDIO_AAC_RECORD_24K_256K,
	/////////////////////////////////////////////////////////////////////////
	MMPS_AUDIO_AAC_RECORD_32K_16K, MMPS_AUDIO_AAC_RECORD_32K_24K, MMPS_AUDIO_AAC_RECORD_32K_32K,
	MMPS_AUDIO_AAC_RECORD_32K_64K, MMPS_AUDIO_AAC_RECORD_32K_96K, MMPS_AUDIO_AAC_RECORD_32K_128K,
	MMPS_AUDIO_AAC_RECORD_32K_160K, MMPS_AUDIO_AAC_RECORD_32K_192K, MMPS_AUDIO_AAC_RECORD_32K_256K, MMPS_AUDIO_AAC_RECORD_32K_320K,
	/////////////////////////////////////////////////////////////////////////
	MMPS_AUDIO_AAC_RECORD_44K_16K, MMPS_AUDIO_AAC_RECORD_44K_24K, MMPS_AUDIO_AAC_RECORD_44K_32K,
	MMPS_AUDIO_AAC_RECORD_44K_64K, MMPS_AUDIO_AAC_RECORD_44K_96K, MMPS_AUDIO_AAC_RECORD_44K_128K,
	MMPS_AUDIO_AAC_RECORD_44K_160K, MMPS_AUDIO_AAC_RECORD_44K_192K, MMPS_AUDIO_AAC_RECORD_44K_256K, MMPS_AUDIO_AAC_RECORD_44K_320K,
	/////////////////////////////////////////////////////////////////////////
	MMPS_AUDIO_AAC_RECORD_48K_16K, MMPS_AUDIO_AAC_RECORD_48K_24K, MMPS_AUDIO_AAC_RECORD_48K_32K,
	MMPS_AUDIO_AAC_RECORD_48K_64K, MMPS_AUDIO_AAC_RECORD_48K_96K, MMPS_AUDIO_AAC_RECORD_48K_128K,
	MMPS_AUDIO_AAC_RECORD_48K_160K, MMPS_AUDIO_AAC_RECORD_48K_192K, MMPS_AUDIO_AAC_RECORD_48K_256K, MMPS_AUDIO_AAC_RECORD_48K_320K
} MMPS_AUDIO_AAC_ENCODEMODE;

// MP3 Record SamplingRate BitRate
typedef enum _MMPS_AUDIO_MP3_ENCODEMODE
{
    MMPS_AUDIO_MP3_RECORD_32K_160K = 0, ///<sample rate: 32k, bitrate: 160k
    MMPS_AUDIO_MP3_RECORD_32K_128K,     ///<sample rate: 32k, bitrate: 128k
    MMPS_AUDIO_MP3_RECORD_32K_96K,      ///<sample rate: 32k, bitrate: 96k
    MMPS_AUDIO_MP3_RECORD_32K_64K,      ///<sample rate: 32k, bitrate: 64k
    MMPS_AUDIO_MP3_RECORD_44d1K_160K,   ///<sample rate: 44.1k, bitrate: 160k
    MMPS_AUDIO_MP3_RECORD_44d1K_128K,   ///<sample rate: 44.1k, bitrate: 128k
    MMPS_AUDIO_MP3_RECORD_44d1K_96K,    ///<sample rate: 44.1k, bitrate: 96k
    MMPS_AUDIO_MP3_RECORD_44d1K_64K     ///<sample rate: 44.1k, bitrate: 64k
} MMPS_AUDIO_MP3_ENCODEMODE;

// WAV Record SamplingRate BitRate
typedef enum _MMPS_AUDIO_WAV_ENCODEMODE
{
    MMPS_AUDIO_WAV_RECORD_8K = 0,   ///<sample rate: 8k
    MMPS_AUDIO_WAV_RECORD_11d025K,  ///<sample rate: 11.025k
    MMPS_AUDIO_WAV_RECORD_16K,      ///<sample rate: 16k
    MMPS_AUDIO_WAV_RECORD_22d05K,   ///<sample rate: 22.05k
    MMPS_AUDIO_WAV_RECORD_24K,      ///<sample rate: 24k
    MMPS_AUDIO_WAV_RECORD_32K,      ///<sample rate: 32k
    MMPS_AUDIO_WAV_RECORD_44d1K,    ///<sample rate: 44.1k
    MMPS_AUDIO_WAV_RECORD_48K       ///<sample rate: 48k
} MMPS_AUDIO_WAV_ENCODEMODE;

typedef enum _MMPS_AUDIO_OP_MODE
{
    MMPS_AUDIO_AACPLUS_P_CARD_MODE = 0, ///< aacplus play card mode
    MMPS_AUDIO_AACPLUS_P_MEM_MODE,      ///< aacplus play memory mode 
    MMPS_AUDIO_MIDI_P_CARD_MODE,        ///< midi play card mode
    MMPS_AUDIO_MIDI_P_MEM_MODE,         ///< midi play memory mode
    MMPS_AUDIO_MP3_P_CARD_MODE,         ///< mp3 play card mode
    MMPS_AUDIO_MP3_P_MEM_MODE,          ///< mp3 play memory mode
    MMPS_AUDIO_WMA_P_CARD_MODE,         ///< wma play card mode
    MMPS_AUDIO_WMA_P_MEM_MODE,          ///< wma play memory mode
    MMPS_AUDIO_AMR_P_CARD_MODE,         ///< amr play card mode
    MMPS_AUDIO_AMR_P_MEM_MODE,          ///< amr play memory mode
    MMPS_AUDIO_AMR_R_CARD_MODE,         ///< amr record card mode
    MMPS_AUDIO_AMR_R_MEM_MODE,          ///< amr record memory mode
    MMPS_AUDIO_AAC_R_CARD_MODE,         ///< aac record card mode
    MMPS_AUDIO_AAC_R_MEM_MODE,          ///< aac record memory mode
    MMPS_AUDIO_MP3_R_CARD_MODE,         ///< mp3 record card mode
    MMPS_AUDIO_MP3_R_MEM_MODE,          ///< mp3 record memory mode
    MMPS_AUDIO_PCM_P_MEM_MODE,          ///< pcm play memory mode
    MMPS_AUDIO_RA_P_CARD_MODE,          ///< realaudio play card mode
    MMPS_AUDIO_RA_P_MEM_MODE,           ///< realaudio play memory mode
    MMPS_AUDIO_OGG_P_CARD_MODE,         ///< OGG play card mode
    MMPS_AUDIO_OGG_P_MEM_MODE,          ///< OGG play memory mode
    MMPS_AUDIO_WAV_P_CARD_MODE,         ///< WAV play card mode
    MMPS_AUDIO_WAV_P_MEM_MODE,          ///< WAV play memory mode
    MMPS_AUDIO_AC3_P_CARD_MODE,         ///< ac3 play card mode   
    MMPS_AUDIO_AC3_P_MEM_MODE,          ///< ac3 play memory mode 
    MMPS_AUDIO_FLAC_P_CARD_MODE,        ///< FLAC play card mode
    MMPS_AUDIO_FLAC_P_MEM_MODE,         ///< FLAC play memory mode
    MMPS_AUDIO_WAV_R_CARD_MODE,         ///< WAV record card mode
    MMPS_AUI_MP3_P_CARD_MODE,           ///< mp3 AUI play card mode
    MMPS_AUI_WAV_P_CARD_MODE,           ///< wav AUI play card mode
	MMPS_AUI_AMR_P_CARD_MODE,			///< AMR AUI play card mode
    MMPS_AUDIO_MODE_MAX
} MMPS_AUDIO_OP_MODE;           

#define MMPS_AUDIO_MODE_NUM                  (MMPS_AUDIO_MODE_MAX)

//Center frequency of each band (total 10 bands)
typedef enum _MMPS_AUDIO_EQ_BAND
{
    MMPS_AUDIO_BAND_60Hz    = 0x00, ///< 60HZ
    MMPS_AUDIO_BAND_170Hz   = 0x01, ///< 170HZ
    MMPS_AUDIO_BAND_310Hz   = 0x02, ///< 310HZ  
    MMPS_AUDIO_BAND_600Hz   = 0x03, ///< 600HZ
    MMPS_AUDIO_BAND_1000Hz  = 0x04, ///< 1000HZ
    MMPS_AUDIO_BAND_3000Hz  = 0x05, ///< 3000HZ
    MMPS_AUDIO_BAND_6000Hz  = 0x06, ///< 6000HZ
    MMPS_AUDIO_BAND_12000Hz = 0x07, ///< 12000HZ
    MMPS_AUDIO_BAND_14000Hz = 0x08, ///< 14000HZ
    MMPS_AUDIO_BAND_16000Hz = 0x09, ///< 16000HZ
    MMPS_AUDIO_BAND_MAX
} MMPS_AUDIO_EQ_BAND;

//Q range
typedef enum _MMPS_AUDIO_EQ_QRANGE
{
    MMPS_AUDIO_Q_115_4 = 0x01,  ///< Q = 115.4125  , BW = 0.0125 octave
    MMPS_AUDIO_Q_57_7,          ///< Q = 57.70707  , BW = 0.025 octave
    MMPS_AUDIO_Q_28_8,          ///< Q = 28.85245  , BW = 0.05 octave
    MMPS_AUDIO_Q_14_4,          ///< Q = 14.42406  , BW = 0.1 octave
    MMPS_AUDIO_Q_7_20,          ///< Q = 7.207702  , BW = 0.2 octave
    MMPS_AUDIO_Q_4_80,          ///< Q = 4.800330  , BW = 0.3 octave
    MMPS_AUDIO_Q_3_59,          ///< Q = 3.595210  , BW = 0.4 octave
    MMPS_AUDIO_Q_2_87,          ///< Q = 2.870999  , BW = 0.5 octave
    MMPS_AUDIO_Q_2_38,          ///< Q = 2.387250  , BW = 0.6 octave
    MMPS_AUDIO_Q_2_04,          ///< Q = 2.040914  , BW = 0.7 octave
    MMPS_AUDIO_Q_1_78,          ///< Q = 1.780469  , BW = 0.8 octave
    MMPS_AUDIO_Q_1_57,          ///< Q = 1.577293  , BW = 0.9 octave
    MMPS_AUDIO_Q_1_41,          ///< Q = 1.414213  , BW = 1.0 octave
    MMPS_AUDIO_Q_0_66,          ///< Q = 0.666667  , BW = 2.0 octave
    MMPS_AUDIO_Q_0_004,         ///< Q = 0.004040  , BW = 3.0 octave
    MMPS_AUDIO_Q_0_003,         ///< Q = 0.266667  , BW = 4.0 octave
    MMPS_AUDIO_Q_MAX
} MMPS_AUDIO_EQ_QRANGE;

typedef enum _MMPS_AUDIO_MEDIA_PATH {
    MMPS_AUDIO_MEDIA_PATH_MEM = 0x00,   ///< Media operation by full memory mode
    MMPS_AUDIO_MEDIA_PATH_CARD,         ///< Media operation by B/E file mode
    MMPS_AUDIO_MEDIA_PATH_HOST_FILE,    ///< Media operation by B/B file mode
    MMPS_AUDIO_MEDIA_PATH_MMP_MEM       ///< Media operation by MMP memory
} MMPS_AUDIO_MEDIA_PATH;

typedef enum _MMPS_AUDIO_DB_SORT_TYPE {
	MMPS_AUDIO_DB_SORT_TITLE = 0,
	MMPS_AUDIO_DB_SORT_ARTIST,
	MMPS_AUDIO_DB_SORT_ALBUM,
	MMPS_AUDIO_DB_SORT_GENRES,
	MMPS_AUDIO_DB_SORT_RATING,
	MMPS_AUDIO_DB_SORT_PCNT,
	MMPS_AUDIO_DB_SORT_MAX
} MMPS_AUDIO_DB_SORT_TYPE;

typedef enum _MMPS_AUDIO_OBJECT_PROPERTY
{
    MMPS_AUDIO_OBJECT_NAME = 0,	    ///< file name
    MMPS_AUDIO_ALBUM,               ///< album
    MMPS_AUDIO_ARTIST,              ///< artist
    MMPS_AUDIO_GENRE                ///< genre
} MMPS_AUDIO_OBJECT_PROPERTY;

typedef enum _MMPS_AUDIO_OBJECT_FORMAT
{
    MMPS_AUDIO_FORMAT_UNDEFINED                     =0x3000, ///< undefined
    MMPS_AUDIO_FORMAT_ASSOCIATION                   =0x3001, ///< association
    MMPS_AUDIO_FORMAT_MP3                           =0x3009, ///< mp3
    MMPS_AUDIO_FORMAT_ASF                           =0x300C, ///< asf
    MMPS_AUDIO_FORMAT_WMA                           =0xB901, ///< wma
    MMPS_AUDIO_FORMAT_Abstract_Audio_Album          =0xBA03, ///< audio album
    MMPS_AUDIO_FORMAT_Abstract_Audio_Video_Playlist =0xBA05  ///< playlist
} MMPS_AUDIO_OBJECT_FORMAT;

typedef enum _MMPS_AUDIO_STR_CMP_RESULT
{
    MMPS_AUDIO_STR_EXACT=0,  ///< exact string
    MMPS_AUDIO_STR_DIFFERENT ///< different string  
} MMPS_AUDIO_STR_CMP_RESULT;

typedef enum _MMPS_AUDIO_CHK_SUPPORT_FORMAT
{
    MMPS_AUDIO_SUPPORT_FORMAT=0, ///< supported object format
    MMPS_AUDIO_UNSUPPORT_FORMAT  ///< unsupported object format 
} MMPS_AUDIO_CHK_SUPPORT_FORMAT;

typedef enum MMPS_AUDIO_CODEC{
    MMPS_AUDIO_CODEC_MP3,
    MMPS_AUDIO_CODEC_AMR,
    MMPS_AUDIO_CODEC_AAC,
    MMPS_AUDIO_CODEC_WMA,
    MMPS_AUDIO_CODEC_OGG,
    MMPS_AUDIO_CODEC_RA,
    MMPS_AUDIO_CODEC_WAV,
    MMPS_AUDIO_CODEC_MIDI,
    MMPS_AUDIO_CODEC_FLAC,
    MMPS_AUDIO_CODEC_INVALID
} MMPS_AUDIO_CODEC;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct MMPS_AUDIO_FILEINFO {
    MMP_BYTE    bFileName[AUDIO_MAX_FILE_NAME_SIZE * 2];    // file mode play
    MMP_USHORT  usFileNameLength;
    MMP_USHORT  usHostFileNameLength;
    MMP_UBYTE   *ubBuf;									// full memory mode
    MMP_ULONG64 ulBufSize;								// full memory mode buffer size
    MMP_ULONG   ulFileID;
    MMPS_AUDIO_MEDIA_PATH mediaPath;
} MMPS_AUDIO_FILEINFO;

typedef struct _MMPS_AUDIO_WAV_INFO {
	MMP_ULONG   ulBitRate;      //bit rate
	MMP_ULONG   ulTotalTime;    //unit: milli-sec
	MMP_ULONG   ulSampleRate;   //sampling rate
	MMP_ULONG   ulNewSampleRate;//new sampling rate after converting
	MMP_USHORT  usChans;        //channel num
	MMP_USHORT  usNotSupport;   //0 : supported format; 1 : not supported format
} MMPS_AUDIO_WAV_INFO;

typedef struct {
    MMPS_AUDIO_SBC_CHANNEL  ChannelMode;    ///< SBC ChannelMode. MONO/DUAL/STEREO/JOINT.
    MMPS_AUDIO_SBC_METHOD   AllocMethod;    ///< SBC AllocMethod. LOUDNESS/SNR.
    MMP_USHORT  usNrofBlocks;               ///< SBC NrofBlocks. 4/8/12/16.
    MMP_USHORT  usNrofSubbands;             ///< SBC NrofSubbands. 4/8.
    MMP_ULONG   ulBitRate;                  ///< SBC Bit Rate (unit: K bsp)
    MMP_ULONG   ulIntPeriod;                ///< Transfer INT period, in ms
    MMP_ULONG   ulMaxTransferSize;          ///< Max transfer size
} MMPS_AUDIO_SBC_SETTING;   

typedef struct _MMPS_AUDIO_BUFFER {
    MMP_ULONG   ulBufStartAddr; ///< Not used currently 
    MMP_ULONG   ulPlayBufSize;  ///< Auido Play Data Buffer Size 
    MMP_ULONG   ulTagBufSize;   ///< Wma tag Buffer Size
    MMP_ULONG   ulSbcBufSize;   ///< SBC Data Buffer Size 
    MMP_ULONG   ulRecBufSize;   ///< Audio Record Data Buffer Size
    MMP_ULONG   ulWavBufSize;   ///< Wave Data Buffer Size;
    MMP_ULONG   ulParseBufSize; ///< Parsing Buffer Size;
} MMPS_AUDIO_BUFFER;

typedef struct _MMPS_AUDIOMODE_BUFFER_INFO {
    MMP_ULONG               ulNameBufSize;                  ///< FS FileName Buffer Size
    MMP_ULONG               ulParameterBufSize;             ///< FS Parameter Buffer Size
    MMP_ULONG               ulSdBufSize;                    ///< SD DMA Buffer Size
    MMP_ULONG               ulSmBufSize;                    ///< SM DMA Buffer Size
    MMPS_AUDIO_OUT_PATH     AudioOutPath;                   ///< Audio Out Path
    MMPS_AUDIO_IN_PATH      AudioInPath;                    ///< Audio In Path
    MMPS_AUDIO_SBC_SETTING  SBC;                            ///< SBC Setting    
    MMPS_AUDIO_BUFFER       AudioMode[MMPS_AUDIO_MODE_NUM];
    MMP_UBYTE               ubVolumeLevel;
    MMP_UBYTE               ubAudioOutVolHPTable[40][3];    ///< Audio volume control table, setting SW/ DIGITAL/ ANALOG GAIN. 
    MMP_UBYTE               ubAudioOutVolLineTable[40][2];  ///< Audio volume control table, setting SW/ DIGITAL. 
} MMPS_AUDIOMODE_CONFIG_INFO;

typedef struct _MMPS_AUDIO_I2S_CFG {
    MMP_I2S_WORK_MODE           workingMode;                ///< working in master or slave mode
    MMP_I2S_MCLK_MODE           mclkMode;                   ///< N*fs or USB mode
    MMP_I2S_OUT_BITS            outputBitSize;              ///< output data bit size per channel
    MMP_I2S_WS_POLARITY         lrckPolarity;               ///< LRCK polarity
    MMP_I2S_DELAY_MODE          outDataDelayMode;           ///< output data delay mode
    MMP_BOOL                    bOutputBySDI;               ///< MMP_TRUE: set SDI as output mode
    MMP_BOOL                    bInputFromSDO;              ///< MMP_TRUE: data input from SDO
    MMP_UBYTE                   ubInBitAlign;               ///< the bypass bit before start fetch data
    MMP_UBYTE                   ubOutBitAlign;              ///< number of 0's in front of PCM for alignment
} MMPS_AUDIO_I2S_CFG;

typedef struct _MMPS_AUDIO_DB_INDEX {
	MMPS_AUDIO_DB_SORT_TYPE	sortType;
	MMP_USHORT				usIndexId;
	MMP_USHORT				usTrackId;
	MMP_UBYTE				ubIndexCount;
} MMPS_AUDIO_DB_INDEX;

typedef struct _MMPS_AUDIO_DB_ENTRY {
	MMP_USHORT	usAlbumNum;
	MMP_USHORT	usTrackNum;
	MMP_USHORT	usTitleName[TEXT_FRAME_MAX_LEN];
	MMP_USHORT	usArtistName[TEXT_FRAME_MAX_LEN];
	MMP_USHORT	usAlbumName[TEXT_FRAME_MAX_LEN];
	MMP_USHORT	usGenreName[TEXT_FRAME_MAX_LEN];
	MMP_USHORT	usFullPathName[AUDIODB_MAX_FILE_NAME_SIZE];
} MMPS_AUDIO_DB_ENTRY;

typedef struct _MMPS_AUDIO_DB_TRACK {
	MMP_USHORT	usTitleName[TEXT_FRAME_MAX_LEN];
	MMP_USHORT	usFullPathName[AUDIODB_MAX_FILE_NAME_SIZE];
} MMPS_AUDIO_DB_TRACK;

typedef	struct _MMPS_AUDIO_MUSICLIST_CONTENT{
    MMP_USHORT Signature;
    MMP_USHORT FileName[MMPS_AUDIO_MAX_FILE_NAME_LEGTH+1];
    
    MMP_ULONG  UniqueIdentifier[4];     ///< object unique identifier
    MMP_ULONG  StorageID;               ///< storage id
    MMP_ULONG  ObjSize;                 ///< object size
    MMP_ULONG  SampleRate;              ///< sampling rate
    MMP_ULONG  AudioWAVECodec;          ///< audio wave codec
    MMP_ULONG  UseCount;                ///< play count
    MMP_ULONG  Duration;                ///< duration
    MMP_ULONG  AudioBitRate;            ///< bitrate
    MMP_USHORT ParentHandle;            ///< object parent handle
    MMP_USHORT FileFmt;                 ///< file format
    MMP_USHORT NumberOfChannels;        ///< channel
    MMP_USHORT AssociationType;         ///< association type
    MMP_USHORT NonConsumable;           ///< non consumable
    MMP_USHORT ProtectionStatus;        ///< protection status
    MMP_USHORT Track;                   ///< track
    MMP_USHORT Rating;                  ///< rating
    MMP_USHORT ObjReference[MMPS_AUDIO_MAX_OBJ_REFERENCE_NUM+1];///< reference object
    MMP_UBYTE  Flag;                    ///< delete flag
    MMP_UBYTE  RoundTrip;               ///< roundtrip flag
    MMP_USHORT Dummy2[74];
    
    MMP_USHORT Artist[MMPS_AUDIO_OBJ_PROPERTY_STR_LEN];
    MMP_USHORT Genre[MMPS_AUDIO_OBJ_PROPERTY_STR_LEN];
    MMP_USHORT AlbumName[MMPS_AUDIO_OBJ_PROPERTY_STR_LEN];
    MMP_USHORT Name[MMPS_AUDIO_OBJ_PROPERTY_STR_LEN];
} MMPS_AUDIO_MUSICLIST_CONTENT;

typedef	struct _MMPS_AUDIO_FILELIST_HEADER{
    MMP_USHORT ObjCnt;    ///< total object count
    MMP_USHORT Dummy[255];///< dummy char
} MMPS_AUDIO_MUSICLIST_HEADER;

typedef	struct _MMPS_AUDIO_ENUMOBJ_INFO{
    MMP_USHORT CurrentIndex;            ///< index
    MMP_USHORT PropertyId;              ///< property id
    MMPS_AUDIO_OBJECT_PROPERTY Property;///< property
    MMP_USHORT PrptyStr[MMPS_AUDIO_OBJ_PROPERTY_STR_LEN];          ///< property string
} MMPS_AUDIO_ENUMOBJ_INFO;

typedef	struct _MMPS_AUDIO_ENUMOBJPRPTY_INFO{
    MMP_USHORT CurrentIndex;            ///< index
    MMPS_AUDIO_OBJECT_PROPERTY Property;///< property
    MMP_USHORT ArtistCnt;               ///< artist count
    MMP_USHORT GenreCnt;                ///< genre count
    MMP_USHORT AlbumNameCnt;            ///< albumname count
    MMP_USHORT PrptyStr[MMPS_AUDIO_MAX_OBJ_PROPERTY_NUM][MMPS_AUDIO_OBJ_PROPERTY_STR_LEN];
} MMPS_AUDIO_ENUMOBJPRPTY_INFO;

typedef	struct _MMPS_AUDIO_ENUMPLAYLIST_INFO{
    MMP_USHORT CurrentIndex;    ///< index
} MMPS_AUDIO_ENUMPLAYLIST_INFO;

typedef	struct _MMPS_AUDIO_MUSICLIST_INFO{
    MMP_USHORT ObjCnt;                                      ///< total object count           
    MMP_USHORT FileFmt[MMPS_AUDIO_MUSICLIST_MAX_OBJECT];    ///< object format
    MMP_UBYTE  Flag[MMPS_AUDIO_MUSICLIST_MAX_OBJECT];       ///< delete flag
    MMP_USHORT CurrentContentIndex;                         ///< index
    MMPS_AUDIO_MUSICLIST_CONTENT ListContent;               ///< playlist content
    MMPS_AUDIO_ENUMOBJ_INFO EnumObjInfo;                    ///< enum object information
    MMPS_AUDIO_ENUMOBJPRPTY_INFO EnumObjPrptyInfo;          ///< enum object property information
    MMPS_AUDIO_ENUMPLAYLIST_INFO EnumPlayListInfo;          ///< enum playlist information
} MMPS_AUDIO_MUSICLIST_INFO;
/// @end_ait_only

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_ERR MMPS_AUDIO_SetMediaPath(MMPS_AUDIO_MEDIA_PATH mediapath);
MMP_ERR MMPS_AUDIO_InitializeMP3Play(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_MP3_INFO *mp3info);
MMP_ERR MMPS_AUDIO_InitializeAACPlusPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AACPLUS_INFO *aacplusinfo);
MMP_ERR MMPS_AUDIO_InitializeAMRPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AMR_INFO *amrinfo);
MMP_ERR MMPS_AUDIO_InitializeWMAPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WMA_INFO *wmainfo);
MMP_ERR MMPS_AUDIO_InitializeOGGPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_OGG_INFO *ogginfo);
MMP_ERR MMPS_AUDIO_InitializeRAPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_RA_INFO *rainfo);
MMP_ERR MMPS_AUDIO_InitializeWAVPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WAV_INFO *wavinfo);
MMP_ERR MMPS_AUDIO_InitializeFLACPlay(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_FLAC_INFO *flacinfo);

MMP_ERR MMPS_AUDIO_MP3PlayTime2FileOffset(MMP_ULONG ulMilliSec);
MMP_ERR MMPS_AUDIO_AACPlusPlayTime2FileOffset(MMP_ULONG ulMilliSec);
MMP_ERR MMPS_AUDIO_WAVPlayTime2FileOffset(MMP_ULONG ulMilliSec);
MMP_ERR MMPS_AUDIO_AMRPlayTime2FileOffset(MMP_ULONG ulMilliSec);

MMP_ERR MMPS_AUDIO_SetAC3VHPar(MMP_LONG lm3deff, MMP_LONG ldb, MMP_BOOL bSet_m3deff, MMP_BOOL bSet_db);

MMP_ERR	MMPS_AUDIO_InitialInPath(MMPS_AUDIO_IN_PATH audioinpath);
MMP_ERR	MMPS_AUDIO_InitialOutPath(MMPS_AUDIO_OUT_PATH audiooutpath);
MMP_ERR MMPS_AUDIO_SetLineInChannel(MMPS_AUDIO_LINEIN_CHANNEL lineinchannel);
MMPS_AUDIO_IN_PATH  MMPS_AUDIO_GetInPath(void);
MMPS_AUDIO_OUT_PATH	MMPS_AUDIO_GetOutPath(void);
MMP_ERR	MMPS_AUDIO_SetInPath(MMPS_AUDIO_IN_PATH audiopath);
MMP_ERR	MMPS_AUDIO_SetOutPath(MMPS_AUDIO_OUT_PATH audiopath);
MMP_ERR MMPS_AUDIO_InitializeI2SConfig(MMP_UBYTE ch, MMPS_AUDIO_I2S_CFG *I2SConfig);
MMP_ERR MMPS_AUDIO_EnableI2SMclk(MMP_UBYTE ch, MMP_BOOL bEnable, MMP_ULONG ulSamplerate, MMP_ULONG ulFixedMclkFreq);
MMP_ERR MMPS_AUDIO_SetGaplessEnable(MMP_BOOL bEnable, void *nextFileCB, MMP_ULONG param1);
#if (GAPLESS_PLAY_EN == 1)
MMP_ERR MMPS_AUDIO_ChkOperationAllowed(MMP_AUDIO_GAPLESS_OP op, MMP_BOOL *bAllow);
#endif
// ID3 parsing API
#if 0
MMP_ERR MMPS_AUDIO_SetMP3PlayID3CacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize, MMP_ULONG ulMaxCacheSize);
MMP_ERR MMPS_AUDIO_GetMP3PlayID3Tag(MMPS_AUDIO_FILEINFO *fileinfo, MMPD_ID3_INFO *id3info, AllocZeroMemCBFunc *CallBackFunc);
MMP_ERR MMPS_AUDIO_SetMP3PlayID3Tag(MMPS_AUDIO_FILEINFO *fileinfo, MMPD_ID3_FRAME_ID frameType, MMP_UBYTE *payload, MMP_LONG payloadLen);
#endif
// Host Parser API
MMP_ERR MMPS_AUDIO_SetParserCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize);
MMP_ERR MMPS_AUDIO_ParserGetMp3Info(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_MP3_INFO *mp3info);
MMP_ERR MMPS_AUDIO_ParserGetAACPlusInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AACPLUS_INFO *aacplusinfo);
MMP_ERR MMPS_AUDIO_ParserGetWMAInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WMA_INFO *wmainfo);
MMP_ERR MMPS_AUDIO_ParserGetWAVInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_WAV_INFO *wavinfo);
MMP_ERR MMPS_AUDIO_ParserGetOGGInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_OGG_INFO *ogginfo);
MMP_ERR MMPS_AUDIO_ParserGetRAInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_RA_INFO *rainfo);
MMP_ERR MMPS_AUDIO_ParserGetAMRInfo(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_AMR_INFO *amrinfo);


MMP_ERR MMPS_AUDIO_GetAACPlusPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_GetAMRPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_GetMP3PlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_GetWMAPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_GetRAPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_GetOGGPlayTime(MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_GetWAVPlayTime(MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_GetFLACPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_PauseAACPlusPlay(void);
MMP_ERR MMPS_AUDIO_PauseAMRPlay(void);
MMP_ERR MMPS_AUDIO_PauseAMRRecord(void);
MMP_ERR MMPS_AUDIO_PauseAACRecord(void);
MMP_ERR MMPS_AUDIO_PauseMP3Record(void);
MMP_ERR MMPS_AUDIO_PauseWAVRecord(void);
MMP_ERR MMPS_AUDIO_PauseMP3Play(void);
MMP_ERR MMPS_AUDIO_PauseWMAPlay(void);
MMP_ERR MMPS_AUDIO_PauseRAPlay(void);
MMP_ERR MMPS_AUDIO_PauseOGGPlay(void);
MMP_ERR MMPS_AUDIO_PauseWAVPlay(void);
MMP_ERR MMPS_AUDIO_PauseFLACPlay(void);
MMP_ERR MMPS_AUDIO_ResumeAACPlusPlay(void);
MMP_ERR MMPS_AUDIO_ResumeAMRPlay(void);
MMP_ERR MMPS_AUDIO_ResumeAMRRecord(void);
MMP_ERR MMPS_AUDIO_ResumeAACRecord(void);
MMP_ERR MMPS_AUDIO_ResumeMP3Record(void);
MMP_ERR MMPS_AUDIO_ResumeWAVRecord(void);
MMP_ERR MMPS_AUDIO_ResumeMP3Play(void);
MMP_ERR MMPS_AUDIO_ResumeWMAPlay(void);
MMP_ERR MMPS_AUDIO_ResumeRAPlay(void);
MMP_ERR MMPS_AUDIO_ResumeOGGPlay(void);
MMP_ERR MMPS_AUDIO_ResumeWAVPlay(void);
MMP_ERR MMPS_AUDIO_ResumeFLACPlay(void);
MMP_ERR MMPS_AUDIO_SetAACPlusPlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_SetAMRPlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_SetMP3PlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_SetWMAPlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_SetRAPlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_SetOGGPlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_SetWAVPlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_SetFLACPlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_StartAACPlusPlay(void*, void*);
MMP_ERR MMPS_AUDIO_StartAMRPlay(void);
MMP_ERR MMPS_AUDIO_StartAMRRecord(void);
MMP_ERR MMPS_AUDIO_StartAACRecord(void);
MMP_ERR MMPS_AUDIO_StartMP3Record(void);
MMP_ERR MMPS_AUDIO_StartWAVRecord(void);
MMP_ERR MMPS_AUDIO_StartMP3Play(void*, void*);
MMP_ERR MMPS_AUDIO_StartWMAPlay(void*, void*);
MMP_ERR MMPS_AUDIO_StartRAPlay(void*, void*);
MMP_ERR MMPS_AUDIO_StartOGGPlay(void*, void*);
MMP_ERR MMPS_AUDIO_StartWAVPlay(void*, void*);
MMP_ERR MMPS_AUDIO_StartFLACPlay(void*, void*);
MMP_ERR MMPS_AUDIO_StopAACPlusPlay(void);
MMP_ERR MMPS_AUDIO_StopAMRRecord(void);
MMP_ERR MMPS_AUDIO_StopAACRecord(void);
MMP_ERR MMPS_AUDIO_StopMP3Record(void);
MMP_ERR MMPS_AUDIO_StopWAVRecord(void);
MMP_ERR MMPS_AUDIO_StopAMRPlay(void);
MMP_ERR MMPS_AUDIO_StopMP3Play(void);
MMP_ERR MMPS_AUDIO_StopWMAPlay(void);
MMP_ERR MMPS_AUDIO_StopRAPlay(void);
MMP_ERR MMPS_AUDIO_StopOGGPlay(void);
MMP_ERR MMPS_AUDIO_StopWAVPlay(void);
MMP_ERR MMPS_AUDIO_StopFLACPlay(void);
MMP_ERR MMPS_AUDIO_GetPlayStatus(MMPS_AUDIO_PLAY_STATUS *status);
MMP_ERR MMPS_AUDIO_InitAMRRecordToCard(MMPS_AUDIO_FILEINFO *fileinfo, MMPS_AUDIO_AMR_ENCODEMODE usMode,MMP_ULONG ulMaxSize);
MMP_ERR MMPS_AUDIO_InitAACRecordToCard(MMPS_AUDIO_FILEINFO *fileinfo, MMPS_AUDIO_AAC_ENCODEMODE usMode,MMP_ULONG ulMaxSize);
MMP_ERR MMPS_AUDIO_InitMP3RecordToCard(MMPS_AUDIO_FILEINFO *fileinfo, MMPS_AUDIO_MP3_ENCODEMODE usMode,MMP_ULONG ulMaxSize);
MMP_ERR MMPS_AUDIO_InitWAVRecord(MMPS_AUDIO_FILEINFO *fileinfo, MMPS_AUDIO_WAV_ENCODEMODE mode, MMP_ULONG ulMaxSize);
MMP_ERR MMPS_AUDIO_GetAMRRecordSize(MMP_ULONG *ulSize);
MMP_ERR MMPS_AUDIO_GetWriteCardStatus(MMP_USHORT *usStatus);
MMP_ERR MMPS_AUDIO_GetAACRecordSize(MMP_ULONG *ulSize);
MMP_ERR MMPS_AUDIO_GetMP3RecordSize(MMP_ULONG *ulSize);
MMP_ERR MMPS_AUDIO_GetWAVRecordSize(MMP_ULONG *ulSize);

MMP_ERR MMPS_AUDIO_TransferDataToHost(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize, 
			   MMP_ULONG *ulReturnSize);
MMP_ERR MMPS_AUDIO_TransferDataHostToDev(void);
MMP_ERR MMPS_AUDIO_InitAMRRecordToMem(MMPS_AUDIO_AMR_ENCODEMODE usMode,MMP_ULONG ulMaxSize);
MMP_ERR MMPS_AUDIO_InitAACRecordToMem(MMPS_AUDIO_AAC_ENCODEMODE usMode,MMP_ULONG ulMaxSize);
MMP_ERR MMPS_AUDIO_InitMP3RecordToMem(MMPS_AUDIO_MP3_ENCODEMODE usMode,MMP_ULONG ulMaxSize);

MMP_ERR MMPS_AUDIO_SetPlayVolume(MMP_USHORT usLevel, MMP_BOOL bSWGainOnly);
MMP_ERR MMPS_AUDIO_GetPlayVolume(MMP_USHORT *usLevel);
MMP_ERR MMPS_AUDIO_SetRecordVolume(MMP_UBYTE ubDGain, MMP_UBYTE ubAGain);
MMP_ERR MMPS_AUDIO_SetRecordHeadMuteTime(MMP_ULONG ulMilliSec);
MMP_ERR MMPS_AUDIO_SetRecordTailCutTime(MMP_ULONG ulMilliSec);
MMP_ERR MMPS_AUDIO_EnableDummyRecord(MMP_BOOL bEnable);
MMP_ERR MMPS_AUDIO_GetSBCBitPool (MMP_ULONG ulBitRate, MMP_ULONG ulSampleRate, MMP_ULONG *ulBitPool);
MMP_ERR MMPS_AUDIO_SetSBCEncodeEnable(MMP_BOOL bEnable,MMP_ULONG ulStartTime);
MMP_ERR MMPS_AUDIO_InitializeSBCEncode(MMP_ULONG ulBufStartAddr, MMP_ULONG ulBufSize, MMP_ULONG ulBitRate, MMP_ULONG ulBitPool);
MMP_ERR MMPS_AUDIO_GetSBCInfo(MMP_ULONG *ulOutSampleRate, MMP_ULONG *ulOutBitRate,MMP_ULONG *ulOutFrameSize,MMP_ULONG *ulOutBitpool);
MMP_ERR MMPS_AUDIO_GetSBCTime(MMP_ULONG *time);
MMP_ERR MMPS_AUDIO_TransferSBCDataFromDev(void);
MMP_ERR MMPS_AUDIO_GetCurrnetSBCBuf(MMP_UBYTE **pBuf, MMP_ULONG *DataSize);
MMP_ERR MMPS_AUDIO_GetSBCDataDone(MMP_ULONG DataSize);

MMP_ERR MMPS_AUDIO_SetWAVEncodeEnable(MMP_BOOL ubEnable,MMP_ULONG StartTime);
MMP_ERR MMPS_AUDIO_InitializeWAVEncode(MMP_ULONG BufStartAddr,MMP_ULONG BufSize,MMP_ULONG ulSampleRate,MMP_ULONG ulChans);
MMP_ERR MMPS_AUDIO_GetWAVTime(MMP_ULONG *time);
MMP_ERR MMPS_AUDIO_TransferWAVDataFromDev(void);
MMP_ERR MMPS_AUDIO_GetCurrnetWAVBuf(MMP_UBYTE **pBuf, MMP_ULONG *DataSize);
MMP_ERR MMPS_AUDIO_GetWAVDataDone(MMP_ULONG DataSize);

MMP_ERR MMPS_AUDIO_SetABRepeatMode(MMPS_AUDIO_ABMODE_POS usPoint , MMP_ULONG ulPos);
MMP_ERR MMPS_AUDIO_EnableABRepeatMode(MMPS_AUDIO_ABMODE_SWITCH usEnable);
MMP_ERR MMPS_AUDIO_GetAACPlusPlayPosition(MMP_ULONG *ulPos);
MMP_ERR MMPS_AUDIO_GetMP3PlayPosition(MMP_ULONG *ulPos);
MMP_ERR MMPS_AUDIO_GetAMRPlayPosition(MMP_ULONG *ulPos);
MMP_ERR MMPS_AUDIO_GetWMAPlayPosition(MMP_ULONG *ulPos);
MMP_ERR MMPS_AUDIO_GetWAVPlayPosition(MMP_ULONG *ulPos);
MMP_ERR MMPS_AUDIO_SetEQType(MMPS_AUDIO_EQTYPE usType, void* argHandler);
MMP_ERR MMPS_AUDIO_GetMP3PlaySpectrum(MMP_USHORT usSpectrum[]);
MMP_ERR MMPS_AUDIO_GetWMAPlaySpectrum(MMP_USHORT usSpectrum[]);
MMP_ERR MMPS_AUDIO_GetAACPlusPlaySpectrum(MMP_USHORT usSpectrum[]);
MMP_ERR MMPS_AUDIO_GetAACRecordTime(MMP_ULONG *ulMilliSec);
MMP_ERR MMPS_AUDIO_GetMP3RecordTime(MMP_ULONG *ulMilliSec);
MMP_ERR MMPS_AUDIO_GetAMRRecordTime(MMP_ULONG *ulMilliSec);
MMP_ERR MMPS_AUDIO_GetWAVRecordTime(MMP_ULONG *ulMilliSec);

MMP_ERR	MMPS_AUDIO_PlayFadeOutEn(MMP_UBYTE channelID, MMP_BOOL bAFadeOutEn);
// EQ
MMP_ERR MMPS_AUDIO_SetGraphicEQEnable(MMP_BOOL ubEnable);
MMP_ERR MMPS_AUDIO_SetGraphicEQBand(MMPS_AUDIO_EQ_BAND usFreq, MMPS_AUDIO_EQ_QRANGE usQrange, MMP_USHORT usGain);
MMP_ERR MMPS_AUDIO_SetForeignEffectEnable(MMP_BOOL ubEnable);
MMP_ERR MMPS_AUDIO_SetForeignEffectType(MMP_ULONG ulParam1, MMP_ULONG ulParam2, MMP_ULONG ulParam3);
MMPS_AUDIOMODE_CONFIG_INFO *MMPS_Audio_GetConfig(void);
MMP_ERR	MMPS_AUDIO_SetEncodeFileSize(MMP_ULONG ulSize);
MMP_ERR	MMPS_AUDIO_SetPlayFileSize(MMP_ULONG ulFileSize);

/// @ait_only
MMP_ERR MMPS_AUDIO_InitMIDIPlayFromCard(MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_MIDI_INFO *midiinfo);
MMP_ERR MMPS_AUDIO_InitMIDIPlayFromMem(MMP_UBYTE *ubAudioPtr,MMP_ULONG ulFileSize, MMP_AUDIO_MIDI_INFO *fileinfo);
MMP_ERR MMPS_AUDIO_InitializePCMPlay(MMPS_AUDIO_FILEINFO *fileinfo);
MMP_ERR MMPS_AUDIO_StartMIDIPlay(void);
MMP_ERR MMPS_AUDIO_StartMIDINotePlay(void);
MMP_ERR MMPS_AUDIO_StartPCMPlay(void);
MMP_ERR MMPS_AUDIO_PauseMIDIPlay(void);
MMP_ERR MMPS_AUDIO_ResumeMIDIPlay(void);
MMP_ERR MMPS_AUDIO_StopMIDIPlay(void);
MMP_ERR MMPS_AUDIO_StopMIDINotePlay(void);
MMP_ERR MMPS_AUDIO_StopPCMPlay(void);
MMP_ERR MMPS_AUDIO_GetMIDIPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_SetMIDIPlayTime(MMP_ULONG ulPlayTime);
MMP_ERR MMPS_AUDIO_SetPlayIntThreshold(MMP_USHORT usThreshold);
MMP_ERR MMPS_AUDIO_SetRecordIntThreshold(MMP_USHORT usThreshold);
MMP_ERR MMPS_AUDIO_TransferDataToAIT(MMP_UBYTE *ubAudioPtr, MMP_ULONG ulMaxSize, MMP_ULONG *ulReturnSize);

MMP_ERR MMPS_AUDIO_OpenMusicListFile(void);
MMP_ERR MMPS_AUDIO_CloseMusicListFile(void);
MMP_ERR MMPS_AUDIO_EnumObjPrpty(MMP_USHORT *usUniString,MMP_USHORT *usId);
MMP_ERR MMPS_AUDIO_OpenEnumObjPrpty(MMPS_AUDIO_OBJECT_PROPERTY Property);
MMP_ERR MMPS_AUDIO_OpenEnumObjByPrpty(MMPS_AUDIO_OBJECT_PROPERTY Property,MMP_USHORT usId);
MMP_ERR MMPS_AUDIO_EnumObjByPrpty(MMP_USHORT *usUniString,MMP_USHORT *usId);
MMP_ERR MMPS_AUDIO_GetObjFullPath(MMP_USHORT *usUniString,MMP_USHORT usId);
MMP_ERR MMPS_AUDIO_UTF16ToUTF8(MMP_USHORT *usUTF16Str,MMP_UBYTE *ubUTF8Str);
MMP_ERR MMPS_AUDIO_GetObjPrpty(MMPS_AUDIO_OBJECT_PROPERTY Property,MMP_USHORT *usUniString,MMP_USHORT usId);
MMP_ERR MMPS_AUDIO_OpenEnumPlayList(void);
MMP_ERR MMPS_AUDIO_EnumPlayList(MMP_USHORT *usUniString,MMP_USHORT *usId);
MMP_ERR MMPS_AUDIO_OpenEnumObjByPlayList(MMP_USHORT usId);
MMP_ERR MMPS_AUDIO_EnumObjByPlayList(MMP_USHORT *usUniString,MMP_USHORT *usId);
MMP_ERR MMPS_AUDIO_WriteMusicListContent(MMP_ULONG ulIndex);
MMP_ERR MMPS_AUDIO_UpdateObjUseCnt(MMP_USHORT usId);
MMP_ERR MMPS_AUDIO_GetObjRating(MMP_USHORT usId,MMP_USHORT *usRating);
MMP_ERR MMPS_AUDIO_SetObjRating(MMP_USHORT usId,MMP_USHORT usRating);
MMP_ERR MMPS_AUDIO_PreDACPowerOn(MMP_ULONG ulSampleRate);
MMP_BOOL MMPS_Audio_GetDACPowerOnStatus(void);
MMP_BOOL MMPS_Audio_GetADCPowerOnStatus(void);

MMP_ERR MMPS_AUDIO_DBMngrInitialize(void);
MMP_ERR MMPS_AUDIO_DBMngrFinish(void);
MMP_ERR MMPS_AUDIO_CreateDatabase(MMP_BYTE *bDirName, MMP_ULONG ulDirNameSize,
									MMP_BYTE* bDBFileName, MMP_ULONG ulDBFileNameSize,
									MMP_ULONG ulID3CacheAddr, MMP_ULONG ulID3CacheSize,
									MMP_ULONG ulDBWriteCacheAddr, MMP_ULONG ulDBWriteCacheSize);
MMP_ERR MMPS_AUDIO_SetDatabaseCacheBuf(MMP_ULONG ulDBCacheAddr, MMP_ULONG ulDBCacheSize);
MMP_ERR MMPS_AUDIO_GetDBMngrFileList(MMPS_AUDIO_DB_INDEX *sortindex, MMPS_AUDIO_DB_ENTRY* dbentry, MMP_ULONG *ulTotalCount);
MMP_ERR MMPS_AUDIO_GetDBMngrTrackList(MMPS_AUDIO_DB_INDEX *sortindex, MMPS_AUDIO_DB_TRACK* trackentry, MMP_ULONG *ulTotalCount);
MMP_ERR MMPS_AUDIO_SearchDBMngrFileList(MMPS_AUDIO_DB_INDEX *sortindex, MMP_UBYTE *ubFilterString, MMP_ULONG ulStringLength, 
										MMPS_AUDIO_DB_ENTRY* dbentry, MMP_ULONG *ulTotalCount);
MMP_ERR MMPS_AUDIO_SearchDBMngrTrackList(MMPS_AUDIO_DB_INDEX *sortindex, MMP_UBYTE *ubFilterString, MMP_ULONG ulFilterStringLength, 
											MMPS_AUDIO_DB_TRACK* trackentry, MMP_ULONG *ulTotalCount);
MMP_ERR MMPS_AUDIO_DeleteDBMngrTrackList(MMPS_AUDIO_DB_INDEX *deleteindex);

MMP_ERR MMPS_AUDIO_InitializeDatabase(MMP_BYTE *bDirName, MMP_ULONG ulDirNameSize,
									MMP_BYTE* bDBFileName, MMP_ULONG ulDBFileNameSize,
									MMP_ULONG ulID3CacheAddr, MMP_ULONG ulID3CacheSize,
									MMP_ULONG ulDBWriteCacheAddr, MMP_ULONG ulDBWriteCacheSize);
MMP_ERR MMPS_AUDIO_AddDatabasePart(MMP_ULONG ulRequestNum, MMP_ULONG *ulAddNum);
MMP_ERR MMPS_AUDIO_FinishDatabase(void);
MMP_ERR MMPS_AUDIO_SetPlayVolumeDb(MMP_BYTE);

MMP_ERR MMPS_AUDIO_OpenFile(MMPS_AUDIO_FILEINFO	fileinfo, void* ContainerInfo,MMPS_AUDIO_CODEC AudioFormat) ;
MMP_ERR MMPS_AUDIO_StartPlay(void* callBackFunc, void* context);
MMP_ERR MMPS_AUDIO_PausePlay(void);
MMP_ERR MMPS_AUDIO_ResumePlay(void);
MMP_ERR MMPS_AUDIO_StopPlay(void);
MMP_ERR MMPS_AUDIO_GetPlayTime(MMP_USHORT *usTimeRatio, MMP_ULONG *ulPlayTime);
MMP_ERR MMPS_AUDIO_SeekByTime(MMP_LONG TargetTime);

MMP_ERR	MMPS_AUDIO_SetPlayDigitalGain(MMP_UBYTE ubDGain);
MMP_ERR	MMPS_AUDIO_SetPlayAnalogGain(MMP_UBYTE ubAGain);
MMP_ERR	MMPS_AUDIO_SetRecordDigitalGain(MMP_UBYTE ubDGain);
MMP_ERR	MMPS_AUDIO_SetRecordAnalogGain(MMP_UBYTE ubAGain, MMP_BOOL bboostup);

MMP_ERR MMPS_AUDIO_InitRecord(MMPS_AUDIO_MEDIA_PATH MediaPath,MMPS_AUDIO_FILEINFO *fileinfo, MMP_AUDIO_ENCODE_FMT fmt,MMP_ULONG mode, MMP_ULONG ulMaxSize);
MMP_ERR MMPS_AUDIO_StartRecord(void);
MMP_ERR MMPS_AUDIO_PauseRecord(void);
MMP_ERR MMPS_AUDIO_StopRecord(void);
MMP_ERR MMPS_AUDIO_ResumeRecord(void);

MMP_ERR MMPS_AUDIO_InitLiveRecord(  MMP_AUDIO_ENCODE_FMT    fmt,
                                    MMP_USHORT              mode,
                                    MMP_ULONG               ulAdcSampleRate,
                                    MMP_LivePCMCB           LivePCMCB);
MMP_ERR MMPS_LiveAudio_StartRecord(void);
MMP_ERR MMPS_LiveAudio_PauseRecord(void);
MMP_ERR MMPS_LiveAudio_ResumeRecord(void);
MMP_ERR MMPS_LiveAudio_StopRecord(void);

MMP_ERR MMPS_AUDIO_GetRecordTime(MMP_ULONG *recTime);
MMP_ERR MMPS_AUDIO_RecodeAudioByName(MMP_UBYTE* pFileName, MMP_UBYTE* ubAudioFormat, MMP_UBYTE* ubOpType);
MMP_ERR MMPS_AUDIO_GetCurCodec(MMP_UBYTE* ubcurCodec);

#if (AUDIO_PREVIEW_SUPPORT == 1)
MMP_ERR MMPS_AUDIO_StartPreview(MMP_ULONG ulStartTime, MMP_ULONG ulDuration);
MMP_ERR MMPS_AUDIO_GetPreviewStatus(MMP_BOOL *bDataReady, MMP_SHORT **usDataBuf, MMP_ULONG *ulSampleNum);
#endif
MMP_ERR MMPS_AUDIO_GetDecOutBuf(MMP_ULONG *ulBufAddr, MMP_ULONG *ulBufSize);

#if (WNR_EN)
MMP_ERR MMPS_AUDIO_ConfigWNR(MMP_AUDIO_WNR_CFG *cfg);
MMP_ERR MMPS_AUDIO_EnableWNR(void);
MMP_ERR MMPS_AUDIO_DisableWNR(void);
#endif

#if (AGC_SUPPORT)
MMP_ERR MMPS_AUDIO_EnableAGC(void);
MMP_ERR MMPS_AUDIO_DisableAGC(void);
#endif

/// @end_ait_only
/// @}
#endif // _MMPS_AUDIO_H_
