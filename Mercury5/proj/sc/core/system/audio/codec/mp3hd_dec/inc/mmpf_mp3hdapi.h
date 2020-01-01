#include "mmpf_audio_ctl.h"
#include "mmpf_audio_typedef.h"

#ifndef MP3HD_API
#define MP3HD_API

#define MP3HDDEC_SIZEOF_WORKING_BUF   (240*1024)

#define MP3HD_FILLUNIT          (1024*4)
#define MP3HD_READINSIZE        (1024*8)

#define MP3HD_MAXFRAMESIZE      (2304)  //max frame output samples
#define MP3HD_OUTFRAMESIZE	    (2304)  //2304 or 1152
#define MP3HD_BUFDEPTH          (3)     //15 for capture and playback mp3 at the same time
#if (GAPLESS_EN == 1)||(SRC_SUPPORT == 1)
#define MP3HD_OUTBUFSIZE        (MP3HD_OUTFRAMESIZE << 1)
#else
#define MP3HD_OUTBUFSIZE        ((MP3HD_BUFDEPTH * MP3HD_OUTFRAMESIZE) << 1)
#endif
#define MP3HDDEC_BUFFER_SIZE    (MP3HDDEC_SIZEOF_WORKING_BUF + \
                                MP3HD_READINSIZE +\
                                MP3HD_OUTBUFSIZE)

#ifndef FILLUNIT
    #define FILLUNIT        MP3HD_FILLUNIT
#endif

#define MP3HD_MAX_LAYER     (2)

typedef struct {	
    MMP_LONG byteLeft;              //remainder bytes in buffer
} MP3HdInDataObj;

extern OutDataObj *pOutData;

typedef struct _MP3HdFrameInfo {
	int bitrate;
	int nChans;
	int samprate;
	int bitsPerSample;
	int outputSamps;
	int layer;
	int version;
	int vbr;
	int	avgbr;
} MP3HdFrameInfo;

typedef struct _MP3HD_LAYER_DATA {
    MMP_UBYTE pbBuf[MP3HD_READINSIZE];
    MMP_ULONG ulBufSize;
    MMP_ULONG ulFileID;
    MMP_ULONG ulTotalRead;
    MMP_ULONG ulFileOffset;
} MP3HD_LAYER_DATA;

MMP_ERR     MMPF_MP3HDDec_Start(void);
void        MMPF_MP3HDDec_Stop(void);
void        MMPF_MP3HDDec_Pause(void);
void        MMPF_MP3HDDec_Resume(void);
void        MMPF_MP3HDDec_Exit(void);
void        MMPF_MP3HDDec_DecodeFrame(int decoder);
MMP_LONG    MMPF_MP3HDDec_ExtractInfo(MP3HdFrameInfo *mp3info);
MMP_ULONG   MMPF_MP3HDDec_GetFramesInByte(void);
MMP_ULONG   MMPF_MP3HDDec_GetTime(void);
void        MMPF_MP3HDDec_SetTime(MMP_ULONG ulTime);
#endif
