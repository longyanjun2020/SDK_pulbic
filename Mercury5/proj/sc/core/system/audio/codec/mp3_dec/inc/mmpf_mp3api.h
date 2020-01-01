#ifndef MP3_API
#define MP3_API

#include "mp3dec_include.h"
#include "mmpf_audio_typedef.h"
#if (MP12DEC_EN == 1)
#include "mmpf_mp12decapi.h"
#endif

#if (HW_MP3D_EN == 1)
#define MP3DEC_SIZEOF_WORKING_BUF   (61440) //for MP3 HW lib
#else
#define MP3DEC_SIZEOF_WORKING_BUF   (48440) //for MP3 SW lib
#endif
#define MP3_MAXFRAMESIZE            2304 // max frame output samples
#define MP3_OUTFRAMESIZE	        2304 // 2304 or 1152
#define MP3_BUFDEPTH                3	 //10 mp3 low power mode
#if (GAPLESS_EN == 1)||(SRC_SUPPORT == 1)
#define MP3_OUTBUF_SIZE             (MP3_OUTFRAMESIZE << 1)
#else
#define MP3_OUTBUF_SIZE             ((MP3_OUTFRAMESIZE * MP3_BUFDEPTH) << 1)
#endif
#define MP3DEC_BUFFER_SIZE          (MP3DEC_SIZEOF_WORKING_BUF + \
                                    READBUF_SIZE + \
                                    MP3_OUTBUF_SIZE)

#define	STAGE_HUFFMAN               (1)
#define	STAGE_GRAN_0_CHAN_0_IMDCT   (5)
#define	STAGE_GRAN_0_CHAN_1_IMDCT   (6)
#define	STAGE_GRAN_0_Subband        (7)
#define	STAGE_GRAN_1_CHAN_0_IMDCT   (8)
#define	STAGE_GRAN_1_CHAN_1_IMDCT   (9)
#define	STAGE_GRAN_1_Subband        (10)
#define	STAGE_IDLE                  (11)
#define	STAGE_WAIT                  (12)
#define	STAGE_MP3DECODE_GR0         (13)
#define	STAGE_MP3DECODE_GR1         (14)

#define MP3_RETRY_NUM       10
#define MP3_PARTIAL_SEARCH  0       //fast parsing
#define MP3_FULL_SEARCH		1		//precise parsing

#ifndef MAX_DECODE_INSTANCE
	#define MAX_DECODE_INSTANCE (2) //max decoder instances
#endif

#define MMPF_ID3_FRAME_XHD3 ('X' << 24 | 'H' << 16 | 'D' << 8 | '3')    //MP3HD info

#if (VMP3_P_EN)
#define MP3_AUDIO_OUTPUT_FRAME_NUM  3
#define MP3_TIME_BUFFER_NUM         (MP3_AUDIO_OUTPUT_FRAME_NUM+2)
#define PROCESS_MP3_HEADER          1
#ifndef SIZEOF_AUDIO_HEADER
    #define SIZEOF_AUDIO_HEADER     12
#endif

typedef struct {
    unsigned char InitSRC;
    unsigned short sample_rate;
    unsigned int sample_cnt;
    unsigned int current_time;
    unsigned int bitrate;
    unsigned int SkipSize;
} MP3_TIME_HANDLE;
#endif

typedef struct {
    Word32  byteLeft;			// remainder bytes in buffer
} InDataObj;

#if (MP12DEC_EN == 1)
typedef struct _MMPF_MP12DEC_DATA {
    AIT_MPEGAud12DecContext tContext;
} MMPF_MP12DEC_DATA;
#endif

typedef struct _MP3_PLAY_HANDLE {
    MP3DecInstance  hMP3Decoder;
    MP3DecFrameInfo glmp3FrameInfo;
    MMP_LONG        eofReached;
    MMP_ULONG       glFirstFramePos;
    MMP_ULONG       glID3SizeInBytes;
    MMP_ULONG       glAudioPlayWaitBufFlush;
    MMP_ULONG       glDecFrameInByte;

    InDataObj       mp3InBuf;
    InDataObj       *pInData;
    OutDataObj      mp3OutBuf;
    OutDataObj      *pOutData;
    
    MMP_SHORT       *pOutBuf;
    MMP_UBYTE       *readPtr;
    
    MMP_LONG        *mp3decWorkingBuf;
    MMP_UBYTE       *pInBuf;
    MMP_SHORT       *Mp3OutBuf;
    MMP_LONG        lLayer;
    MMP_SHORT       *mp3pcmBuf;
    MMP_LONG        STAGE_MP3_DECODE_HW_Start;
    MMP_SHORT       *pTmpMP3OutBuf;
    volatile MMP_LONG   mp3dec_stage;
    volatile MMP_LONG   mp3dec_previous_stage;
    volatile MMP_LONG   next_stage;

    MMP_SHORT       fSmoothing;
    MMP_USHORT      gsSmoothDir;
    MMP_SHORT       gsVolTmp;
    MMP_USHORT      gsVolUpLimit;
    MMP_USHORT      gsBufEmpty;
    MMP_BOOL        bSamplingRateChange;
    MMP_BOOL        bActive;
    MMP_BOOL     	bCallBackOccurred;
    MMP_UBYTE       instanceID;
    MMP_BOOL        bResync;

    #if (MP12DEC_EN == 1)
    MMPF_MP12DEC_DATA   mpa12;
    #endif
} MP3_PLAY_HANDLE;

typedef struct _MMPF_MP3_PARSEINFO {
    MMP_ULONG       ulID3TagSize;
    MMP_ULONG       ulFirstFramePos;
    MMP_ULONG       ulParsedBytes;
    MP3DecFrameInfo mp3Info;
    MMP_BOOL        bIsMP3HD;
} MMPF_MP3_PARSEINFO;

//ID3v2 Tag Header
typedef struct _MMPF_MP3_ID3V2_TAGHDR {
    MMP_BYTE        header[3];
    MMP_BYTE        ver;
    MMP_BYTE        rev;
    MMP_BYTE        flag;
    MMP_BYTE        size[4];
} MMPF_MP3_ID3V2_TAGHDR;

extern Word32 Mp3Init(MP3_PLAY_HANDLE *handler);
extern Word32 Mp3InbufTask(MP3_PLAY_HANDLE *handler);
extern Word32 Mp3Start(MP3_PLAY_HANDLE *handler, MP3DecFrameInfo *mp3info, Word8u *readBuf, Word16 *outbuf, int *err);
extern void MMPF_PreStartMp3Dec(MMP_ULONG id);
extern MMP_ERR MMPF_StartMp3Dec(MMP_ULONG id);
extern void MMPF_StopMp3Dec(MMP_ULONG id);
extern void MMPF_PauseMp3Dec(MMP_ULONG id);
extern void MMPF_ResumeMp3Dec(MMP_ULONG id);
extern void MMPF_DecodeMp3Frame(MMP_ULONG id, int decoder);
extern MMP_LONG MMPF_ExtractMP3Info(MMP_ULONG id, MP3DecFrameInfo **mp3info);
extern MMP_ULONG MMPF_GetMP3DecFramesInByte(void);
extern void MMPF_GetMp3Spectrum(void);
extern void MMPF_SetMP3Layer(MMP_UBYTE Layer);
extern void MMPF_PreDecMP3Frame(MP3DecFrameInfo *mp3info);
extern MP3_PLAY_HANDLE *MMPF_GetMP3DecHandler(MMP_ULONG id);
extern MMPF_MP3_PARSEINFO *MMPF_GetMP3DecParseInfo(MMP_ULONG id);
extern MMP_ULONG MMPF_GetMP3PlayTime(void);
#if (AUDIO_PREVIEW_SUPPORT == 1)
extern MMP_ERR MMPF_StartMP3Preview(MMP_ULONG id);
extern MMP_ERR MMPF_DecodeMP3ForPreview(MMP_ULONG id);
#endif
#endif
