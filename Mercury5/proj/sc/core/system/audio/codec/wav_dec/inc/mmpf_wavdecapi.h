#ifndef _WAV_DEC_API_
#define _WAV_DEC_API_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_audio.h"
#include "mmpf_audio_typedef.h"
#include "adpcm_api.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

/* WAV Buffer Size */
#define WAV_OUTFRAMESIZE            (2048)
#define WAV_BUFDEPTH                (10)
#define WAV_READ_SAMPLE             (256)

#define WAV_READBUF_SIZE            (1024*8)
#define WAV_FILLUNIT                (1024*4)
#if (GAPLESS_EN == 1)||(SRC_SUPPORT == 1)
#define WAV_OUTBUF_SIZE             (WAV_OUTFRAMESIZE << 1)
#else
#define WAV_OUTBUF_SIZE             ((WAV_OUTFRAMESIZE * WAV_BUFDEPTH) << 1)
#endif
#define LPCMDEC_BUFFER_SIZE         (WAV_OUTBUF_SIZE + \
                                    ((WAV_OUTFRAMESIZE * WAV_BUFDEPTH) << 2))

/* ADPCM Buffer Size */
#define ADPCMDEC_IN_BUFFER_SIZE     (2048)
#define ADPCMDEC_FRM_SAMPLES        (ADPCMDEC_IN_BUFFER_SIZE*4*2) //(samples per-frame)*(ch)
#define ADPCMDEC_WORKING_BUF_SIZE   (4*1024)
#define DEFAULT_FILL_PCM_SIZE	    (1024)
#if (GAPLESS_EN == 1)||(SRC_SUPPORT == 1)
#define ADPCM_OUTBUF_SIZE           (ADPCMDEC_FRM_SAMPLES)
#else
#define ADPCM_OUTBUF_SIZE           (ADPCMDEC_FRM_SAMPLES * WAV_BUFDEPTH)
#endif
#define ADPCMDEC_BUFFER_SIZE        (ADPCMDEC_WORKING_BUF_SIZE + \
                                    (ADPCMDEC_IN_BUFFER_SIZE * WAV_BUFDEPTH) + \
                                    ADPCM_OUTBUF_SIZE)

#if (ADPCMDEC_BUFFER_SIZE > LPCMDEC_BUFFER_SIZE)
#define WAVDEC_BUFFER_SIZE          ADPCMDEC_BUFFER_SIZE
#else
#define WAVDEC_BUFFER_SIZE          LPCMDEC_BUFFER_SIZE
#endif

/* Misc */
#ifndef MAX_DECODE_INSTANCE
	#define MAX_DECODE_INSTANCE     (2) // Max decoder instances
#endif

#if (VWAV_P_EN)
#ifndef SIZEOF_AUDIO_HEADER
    #define SIZEOF_AUDIO_HEADER     (12)
#endif
#endif

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

#if (VWAV_P_EN)
typedef struct _WAV_TIME_HANDLE {
    unsigned short  sample_rate;
    unsigned int    sample_cnt;
    unsigned int    current_time;
} WAV_TIME_HANDLE;
#endif

typedef struct {    
    Word32u         rd_ind;             // read pointer
    Word32u         wr_ind;             // write pointer
    Word32          SampleLeft;         // remainder samples in buffer (Unit:Bytes)
    Word32u         BufButton;          // 2*2304-1 or 2*1152 (Unit:Short) 
} WavInDataObj;

typedef struct _WAVFileInfo {
    Word32u         bitRate;            // AvgBytesPerSec
    Word32u         totaldataSize;      // total wave data to play.
    Word32u         totaltime;
    Word16u         compressionCode;
    Word16u         nChannels;
    Word32u         sampleRate;
    Word32u         newSampleRate;
    Word16u         blockAlign;
    Word16u         bitsPerSample;
} WAVFileInfo;

typedef struct _WAV_PLAY_HANDLE {
	MMP_ULONG		id;
	WAVFileInfo		wavfileinfo;
	unsigned int 	*pADPCMDecWorkingBuf;
	MMP_SHORT		*pWavInBuf;		    // input bitstream buffer (planar)
	MMP_SHORT		*pWavOutBuf;	    // output pcm buffer
	MMP_LONG		eofReached;		    // record the end of the file
	MMP_ULONG		ulReadPtr;		    // current address of the input bitstream
	MMP_ULONG    	ulFirstFramePos;
	MMP_ULONG		ulDecFrameInByte;
	MMP_ULONG		ulAudioTotalSize;
	WavInDataObj 	wavInData;
	OutDataObj   	wavOutData;		    // output pcm buffer info
	MMP_USHORT		usSmoothDir;
	MMP_SHORT    	sVolTmp;
	MMP_USHORT   	usVolUpLimit;
	MMP_BOOL     	bWavSRCEnable;
	MMP_BOOL     	bCallBackOccurred;
	MMP_BOOL		bDecodeEnd;
	MMP_BOOL		bFirstFrameDecDone; // ADPCM use
	MMP_ULONG		ulOutSample;
	MMP_BOOL		bIsADPCMFormat;
	AVCodecContext	tContext;
} WAV_PLAY_HANDLE;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

Word32 WavInbufTask(WAV_PLAY_HANDLE *wavhandle);
int InitWAVDecoder(WAV_PLAY_HANDLE *wavhandle, int decoder);

MMP_ERR MMPF_StartWAVDec(MMP_ULONG	id);
void MMPF_StopWAVDec(MMP_ULONG	id);
void MMPF_PauseWAVDec(MMP_ULONG	id);
void MMPF_ResumeWAVDec(MMP_ULONG	id);
int MMPF_DecodeWAVFrame(MMP_ULONG	id, int decoder);

MMP_SHORT MMPF_ExtractWAVInfo(MMP_ULONG	id, WAVFileInfo **wavinfo);
void MMPF_GetWAVFileInfo(WAVFileInfo **wavinfo);
int MMPF_PreDecWAVFrame(void);
void MMPF_GetWAVContext(AVCodecContext **context);
void MMPF_SetWAVFormat(MMP_BOOL bIsADPCM);

MMP_ULONG MMPF_GetWAVDecFramesInByte(void);
WAV_PLAY_HANDLE *MMPF_GetWAVDecHandler(MMP_ULONG id);
MMP_ULONG MMPF_GetWAVPlayTime(void);
#if (AUDIO_PREVIEW_SUPPORT == 1)
MMP_ERR MMPF_StartWAVPreview(MMP_ULONG id);
MMP_ERR MMPF_DecodeWAVForPreview(MMP_ULONG id);
#endif

#endif //_WAV_DEC_API_

