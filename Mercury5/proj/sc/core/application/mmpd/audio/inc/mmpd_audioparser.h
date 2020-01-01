/// @ait_only
//==============================================================================
//
//  File        : mmpd_audioparser.h
//  Description : INCLUDE File for the Host get audio media spec.
//  Author      : CZLee
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmpd_audioparser.h
 *  @brief The header File for ost get audio media spec functions
 *  @author CZLee
 *  @version 1.0
 */

#ifndef _MMPD_AUDIOPARSER_H_
#define _MMPD_AUDIOPARSER_H_

#include "mmp_lib.h"
#include "mmpd_audio.h"
//#include "ait_utility.h"

#include "mmpd_id3.h"

#if (RA_HOST_PARSER_EN == 1)
#include "radec_helix_result.h"

#include "ra_depack.h"
#include "ra_decode.h"
#include "rm_parse.h"
#include "rm_memory_default.h"

#include "ra8lbr_decode.h"
#include "raac_aac_decode.h"

#endif

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
//++ Start of mp3 parser
#define MP3PARSER_MIN_DATA_REQ      (18)   //byte
#define MAX_SCFBD		4		/* max scalefactor bands per channel */
#define NGRANS_MPEG1	2
#define NGRANS_MPEG2	1

#define MAX_NGRAN		2		/* max granules */
#define MAX_NCHAN		2		/* max channels */
#define MAX_NSAMP		576		/* max samples per channel, per granule */

/* 12-bit syncword if MPEG 1,2 only are supported 
 *#define	SYNCWORDH		0xff
 *#define	SYNCWORDL		0xf0
 */

/* 11-bit syncword if MPEG 2.5 extensions are enabled */
#define	SYNCWORDH		0xff
#define	SYNCWORDL		0xe0

#define MP3_IN_BUF_SIZE					 (4096)
#define	MP3_VALID_FRAME_NO	             (300)
#define MP3_MAX_RESYNC_NO				 (300)
#define MP3_PAR_NEW_SIZE                 (300)            

//samyu@091124, for improving CBR parsing speed.    
#define MP3_CBR_CHK_FRM_NO               (60) 
    
//-- End of mp3 parser

//++ Start of wma parser
#define ASF_CODEC_ID_WMAV1      (0x0160)  //Windows Media Audio v1  (WMA Std.)
#define ASF_CODEC_ID_WMAV2      (0x0161)  //Windows Media Audio v2  (WMA Std.)
#define ASF_CODEC_ID_WMAV3      (0x0162)  //Windows Media Audio v3  (WMA Pro.) 
#define ASF_CODEC_ID_WMAVL      (0x0163)  //Unsupported: Windows Media Audio v3  (WMA Lossless.) 
#define ASF_CODEC_ID_WMASPDIF   (0x0164)  //Unsupported: WMAPro over SPDIF
#define ASF_CODEC_ID_WMAVOICE   (0x000A)  //Unsupported: WMA Voice
#define ASF_CODEC_ID_WMAV2_ES   (0x0165)  //Unsupported: WMA Std.-UES
#define ASF_CODEC_ID_WMAV3_ES   (0x0166)  //Unsupported: WMA Pro.-UES
#define ASF_CODEC_ID_WMAVL_ES   (0x0167)  //Unsupported: WMA Lossless-UES

#ifndef WP_MIN
#define WP_MIN(a, b) (((a)<(b))?(a):(b))
#endif

#ifndef WP_ABS
#define WP_ABS(x) ((x)<0?-(x):(x))
#endif

#define WP_GIUD_SZ      (16)    //byte
#define WP_OBJHDR_SZ    (24)    //byte
//-- End of wma parser

//++ start of aacplus definition
#define	AACPLUS_MIN_STREAMSIZE		(768) /* 6144 bits/channel */

#define AACPLUS_MAX_CHANNELS        (2)
#define AACPLUS_MAX_SYNTAX_ELEMENTS (2)
#define AACPLUS_MAX_WINDOW_GROUPS   (8)
#define AACPLUS_MAX_SFB             (51)

#define AACPLUS_READBUF_SIZE		(512*8)
#define AAC_PRE_DECODE_FRAMES       (2)

#define SBR_DEC

#define MAIN       1
#define LC         2
#define SSR        3
#define LTP        4
#define AACPLUS_V1 5
#define AACPLUS_V2 6
#define ER_LC     17
#define ER_LTP    19
#define LD        23
#define DRM_ER_LC 27 /* special object type for DRM */
//-- end of aacplus definition

//++ start of ogg definition
#define OGGP_MAX_PATH (260)
//-- end of ogg definition

//++ start of ra definition
#define	RADEC_PARSER_WORKING_BUF_SIZE	(8*1024)
#define RM2WAV_INITIAL_READ_SIZE 		(16)

#define	RA_BACKEND_COOK		0x01
#define	RA_BACKEND_RAAC		0x02
//-- end of ra definition
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
/* map to 0,1,2 to make table indexing easier */
//++ start of mp3 definition
typedef enum _MMPD_AUDPSR_MP3MPEGVERSION {
	MPEG1 =  0,
	MPEG2 =  1,
	MPEG25 = 2
} MMPD_AUDPSR_MP3MPEGVERSION;

typedef struct _MMPD_AUDPSR_MP3DECINFO {
	/* user-accessible info */
    MMP_ULONG ulSamplePerFrame;
    /* private */
    MMP_ULONG ulCurrentReSyncFileOffset;
    MMP_ULONG ulNextSyncWordFileOffset;    
} MMPD_AUDPSR_MP3DECINFO;

typedef enum _MMPD_AUDPSR_MP3STEREOMODE{
	Stereo = 0x00,	/* two independent channels, but L and R frames might have different # of bits */
	Joint = 0x01,	/* coupled channels - layer III: mix of M-S and intensity, Layers I/II: intensity and direct coding only */
	Dual = 0x02,	/* two independent channels, L and R always have exactly 1/2 the total bitrate */
	Mono = 0x03		/* one channel */
} MMPD_AUDPSR_MP3STEREOMODE;

typedef struct _MMPD_AUDPSR_MP3FRAMEHEADER {
    MMPD_AUDPSR_MP3MPEGVERSION ver;	/* version ID */
    MMP_UBYTE ubLayer;			/* layer index (1, 2, or 3) */
    MMP_UBYTE ubCRC;			/* CRC flag: 0 = disabled, 1 = enabled */
    MMP_UBYTE ubBrIdx;			/* bitrate index (0 - 15) */
    MMP_UBYTE ubSrIdx;			/* sample rate index (0 - 2) */
    MMP_UBYTE ubPaddingBit;		/* padding flag: 0 = no padding, 1 = single pad byte */
    MMP_UBYTE ubPrivateBit;		/* unused */
    MMPD_AUDPSR_MP3STEREOMODE stereomode;	/* mono/stereo mode */
    MMP_UBYTE ubModeExt;		/* used to decipher joint stereo mode */
    MMP_UBYTE ubCopyFlag;		/* copyright flag: 0 = no, 1 = yes */
    MMP_UBYTE ubOrigFlag;		/* original flag: 0 = copy, 1 = original */
    MMP_UBYTE ubEmphasis;		/* deemphasis mode */
    MMP_USHORT usCRCWord;		/* CRC word (16 bits, 0 if crc not enabled) */
} MMPD_AUDPSR_MP3FRAMEHEADER;
//-- end of mp3 definition

//++ start of wma definition
typedef enum  _MMPD_AUDPSR_ASFERROR {
    ASF_ERROR_INTERNAL       = -1,  /* incorrect input to API calls */
    ASF_ERROR_OUTOFMEM       = -2,  /* some malloc inside program failed */
    ASF_ERROR_EOF            = -3,  /* unexpected end of file */
    ASF_ERROR_IO             = -4,  /* error reading or writing to file */
    ASF_ERROR_INVALID_LENGTH = -5,  /* length value conflict in input data */
    ASF_ERROR_INVALID_VALUE  = -6,  /* other value conflict in input data */
    ASF_ERROR_INVALID_OBJECT = -7,  /* ASF object missing or in wrong place */
    ASF_ERROR_OBJECT_SIZE    = -8,  /* invalid ASF object size (too small) */
    ASF_ERROR_SEEKABLE       = -9,  /* file not seekable */
    ASF_ERROR_SEEK           = -10, /* file is seekable but seeking failed */
    ASF_ERROR_ENCRYPTED      = -11  /* file is encrypted */
} MMPD_AUDPSR_ASFERROR;

typedef struct  _MMPD_AUDPSR_ASFGUID {
    MMP_ULONG   ulv1;
    MMP_USHORT  usv2;
    MMP_USHORT  usv3;
    MMP_UBYTE   ubv4[8];
} MMPD_AUDPSR_ASFGUID;

typedef struct _MMPD_AUDPSR_ASFOBJECT {
    MMPD_AUDPSR_ASFGUID     guid;
    MMP_ULONG64             ullSize;
    MMP_ULONG64             ullDataLen;
} MMPD_AUDPSR_ASFOBJECT;
//-- end of wma definition

//++ start of aacplus definition

typedef struct _MMPD_AUDPSR_AACPLUS_BUFFER {	//aac_buffer
    MMP_LONG bytes_into_buffer;
    MMP_LONG bytes_consumed;
    MMP_LONG file_offset;
    MMP_UBYTE *buffer;
    MMP_LONG at_eof;
} MMPD_AUDPSR_AACPLUS_BUFFER;

typedef enum _MMPD_AUDPSR_AACPLUS_HEADER_TYPE{
	MMPD_AUDPSR_AACPLUS_RAW_FORMAT = 0,
	MMPD_AUDPSR_AACPLUS_ADIF_FORMAT,
	MMPD_AUDPSR_AACPLUS_ADTS_FORMAT
} MMPD_AUDPSR_AACPLUS_HEADER_TYPE;

//-- end of aacplus definition

//++ start of wav definition
typedef struct _MMPD_AUDPSR_WAV_CHUNK_HDR {
    MMP_ULONG ulChunkID;  // should be "RIFF"
    MMP_ULONG ulChunkSize;
    MMP_ULONG ulFormat;   // should be "WAVE"
} MMPD_AUDPSR_WAV_CHUNK_HDR;

typedef struct _MMPD_AUDPSR_WAV_SUBCHUNK_HDR {    //wav sub-chunk header
    MMP_ULONG  ulSubChunkID;
    MMP_ULONG  ulSubChunkSize;
} MMPD_AUDPSR_WAV_SUBCHUNK_HDR;

typedef struct _MMPD_AUDPSR_WAV_FMT_HDR {    //wav fmt sub-chunk
    MMP_USHORT usAudioFmt;
    MMP_USHORT usChans;
    MMP_ULONG  ulSampleRate;
    MMP_ULONG  ulByteRate;
    MMP_USHORT usBlockAlign;
    MMP_USHORT usBitPerSample;
} MMPD_AUDPSR_WAV_FMT_HDR;

//-- end of wav definition

//++ start of ogg definition
enum OGGP_CODEC_ID 
{
    OGGPFMT_UNKNOWN = 0,  /* Unknown file format */
    OGGPFMT_OGG_VORBIS   /* Ogg Vorbis */
};


enum oggp_error_e {
    ASF_ERROR_FILEIO            = -1,  /* file read/seek error */
    ASF_ERROR_FILEHDR           = -2,  /* file not start with "OggS" */
    ASF_ERROR_UNKNW_FMT         = -3,  /* file is not OGG Vorbis, may be it's FLAC or Speex */
    ASF_ERROR_PKTHDR            = -4,
    ASF_ERROR_CMTHDR            = -5,
    ASF_ERROR_MULTISTREAM       = -6,  /* Multiple vorbis streams is not supported */
    ASF_ERROR_INVALID_TOTALTIME = -7  /* Invalid total time */
};
//-- end of ogg definition

//++ start of ra definition
#if (RA_HOST_PARSER_EN == 1)
typedef struct
{
    ra_depack     *pDepack;
    ra_decode     *pDecode;
    MMP_BYTE*  	  pPcmOutBuf;
    MMP_ULONG     ulOutBufSize;
    MMP_ULONG     ulDataBytesWritten;

    MMP_ULONG     raBackendCodec;
    MMP_ULONG     avg_bit_rate;
    MMP_ULONG     max_bit_rate;
    MMP_ULONG     max_packet_size;
    MMP_ULONG     avg_packet_size;
    MMP_ULONG     duration;
    MMP_ULONG     Channels;
    MMP_ULONG     SampleRate;

    MMP_USHORT    usStreamNum;// 0 for realaudio, 1 for realvideo for example.
    MMP_ULONG     MaxSamples;// = superblock size

	MMP_ULONG     PcmOutMaxSamples; //used to indicate i2s_isr to trigger ra decoder.
} radec_info;
#endif
//-- end of ra definition
//==============================================================================
//
//                               FUNCTION PROTOTYPES
//
//==============================================================================
// Parser general API
MMP_ERR MMPD_AUDPSR_SetCacheBuf(MMP_ULONG ulCacheAddr, MMP_ULONG ulCacheSize);
MMP_ERR MMPD_AUDPSR_SetMediaPath(MMPD_AUDIO_PLAY_DATAPATH mediapath);
MMP_ERR MMPD_AUDPSR_Initialize(MMP_BYTE *bFileName, MMP_ULONG ulNameLen, MMP_ULONG ulFileID);
MMP_ERR MMPD_AUDPSR_Finish(MMP_BOOL bCloseFile);

MMP_ERR MMPD_AUDPSR_ReadFile(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize);

MMP_ERR MMPD_AUDPSR_GetRACurFileOffset(MMP_ULONG *ulFileOffset);
MMP_ERR MMPD_AUDPSR_SetRACurFileOffset(MMP_ULONG ulFileOffset);

MMP_ERR MMPD_AUDPSR_GetMp3Info(MMP_AUDIO_MP3_INFO *mp3info);
MMP_ERR MMPD_AUDPSR_GetWMAInfo(MMP_AUDIO_WMA_INFO *wmainfo);
MMP_ERR MMPD_AUDPSR_GetWMAMetaData(MMPD_ID3_INFO *id3info);
MMP_ERR MMPD_AUDPSR_GetAACPlusInfo(MMP_AUDIO_AACPLUS_INFO *aacplusinfo);
MMP_ERR MMPD_AUDPSR_GetOGGInfo(MMP_AUDIO_OGG_INFO *ogginfo);
MMP_ERR MMPD_AUDPSR_GetRAInfo(MMP_AUDIO_RA_INFO *rainfo);
MMP_ERR MMPD_AUDPSR_GetWAVInfo(MMP_AUDIO_WAV_INFO *wavinfo);
MMP_ERR MMPD_AUDPSR_GetAMRInfo(MMP_AUDIO_AMR_INFO *amrinfo);
/// @}
#endif // _MMPD_AUDIOPARSER_H_
/// @end_ait_only

