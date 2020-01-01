//==============================================================================
//
//  File        : mp3dec_include.h
//  Description : MP3 Decoder Interface
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#ifndef _MP3DEC_INCLUDE_H_
#define _MP3DEC_INCLUDE_H_

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
#if defined(MP3D_RAM_INTERLEAVE)
#define FILLUNIT		    (4096)
#define READBUF_SIZE		(8192)
#else
#define FILLUNIT		    (2048)
#define READBUF_SIZE		(1024*4)
#endif

#define	SYNCWORDH		    (0xFF)
#define	SYNCWORDL		    (0xE0)

#define MAX_SCFBD       4   //max scalefactor bands per channel
#define MAX_NGRAN       2   //max granules
#define MAX_NCHAN       2   //max channels
#define MAX_NSAMP       576 //max samples per channel per granule
//==============================================================================
//
//                              MACRO
//
//==============================================================================
#define MIN(a, b)           (((a) < (b)) ? (a) : (b))
#define MAX(a, b)           (((a) > (b)) ? (a) : (b))


//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================
typedef enum _MP3DecErrorCode {
	ERR_MP3DEC_NONE                 = 0,
	ERR_MP3DEC_INDATA_UNDERFLOW     = 1,
	ERR_MP3DEC_DATA_UNDERFLOW       = 2,
	ERR_MP3DEC_FREE_BITRATE_SYNC    = 3,
	ERR_MP3DEC_OUT_OF_MEMORY        = 4,
	ERR_MP3DEC_NULL_POINTER         = 5,
	ERR_MP3DEC_INVALID_FRAMEHEADER  = 6,
	ERR_MP3DEC_INVALID_SIDEINFO     = 7,
	ERR_MP3DEC_INVALID_SCALEFACT    = 8,
	ERR_MP3DEC_INVALID_HUFFCODES    = 9,
	ERR_MP3DEC_INVALID_HANDLER      = 10,
	ERR_MP3DEC_UNKNOWN              = 9999
} MP3DecErrorCode;

typedef enum _MPAVersion {
    MPEG_VER1 =  0,
    MPEG_VER2 =  1,
    MPEG_VER25 = 2
} MPAVersion;

typedef enum _MPAChMode {
    MPA_STEREO = 0x00,
    MPA_JOINT = 0x01,
    MPA_DUAL = 0x02,
    MPA_MONO = 0x03
} MPAChMode;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
typedef struct _MP3DecSFBandTable {
	MMP_SHORT layer[23];
	MMP_SHORT srIdx[14];
} MP3DecSFBandTable;

typedef struct _MP3DecSideInfoSub {
    MMP_LONG part23Length;
    MMP_LONG nBigvals;
    MMP_LONG globalGain;
    MMP_LONG sfCompress;
    MMP_LONG winSwitchFlag;
    MMP_LONG lBlkType;
    MMP_LONG lMixingBlk;
    MMP_LONG tableSelect[3];
    MMP_LONG subBlockGain[3];
    MMP_LONG region0Count;
    MMP_LONG region1Count;
    MMP_LONG preFlag;
    MMP_LONG sfactScale;
    MMP_LONG count1TableSelect;
} MP3DecSideInfoSub;

typedef struct _MP3DecFrameHdr {
    MPAVersion verion;      // MPEG audio version
    MMP_LONG layer;         // MPEG audio layer (1/2/3)
    MMP_LONG crc;
    MMP_LONG brIdx;         // MPEG audio bitrate index
    MMP_LONG srIdx;         // MPEG audio sample rate index
    MMP_LONG paddingBit;    // Padding bit
    MMP_LONG privateBit;    // Private bit
    MPAChMode sMode;        // Channel mode
    MMP_LONG modeExt;
    MMP_LONG copyFlag;      // Copyright
    MMP_LONG origFlag;
    MMP_LONG emphasis;
    MMP_LONG crcWord;       // CRC code
    const MP3DecSFBandTable *sfBand;
} MP3DecFrameHdr;

typedef struct _MP3DecSideInfo {
	MMP_LONG mainDataBegin;
	MMP_LONG privateBits;
	MMP_LONG scfsi[MAX_NCHAN][MAX_SCFBD];
	MP3DecSideInfoSub sideInfoSub[MAX_NGRAN][MAX_NCHAN];
} MP3DecSideInfo;

typedef struct _MP3DecHuffmanInfo {
	MMP_LONG *huffmanBuf[MAX_NCHAN];
	MMP_LONG lNonZeroB[MAX_NCHAN];
	MMP_LONG lGranB[MAX_NCHAN];
} MP3DecHuffmanInfo;

typedef struct _MP3DecSubbandInfo {
	MMP_LONG *lVBuf;
	MMP_LONG lVIdx;
} MP3DecSubbandInfo;

typedef struct _MP3DecIMDCTInfo {
	MMP_LONG *outBuf;
	MMP_LONG *overBuf[MAX_NCHAN];
	MMP_LONG numPrevIMDCT[MAX_NCHAN];
	MMP_LONG prevType[MAX_NCHAN];
	MMP_LONG prevWinSwitch[MAX_NCHAN];
	MMP_LONG lGranB[MAX_NCHAN];
} MP3DecIMDCTInfo;

typedef struct _STAGE_MP3DecInfo {
	MP3DecFrameHdr FrameHeaderPS;
	MP3DecSideInfo SideInfoPS;
	MP3DecHuffmanInfo *HuffmanInfoPS;
	MP3DecIMDCTInfo *IMDCTInfoPS;
	MP3DecSubbandInfo *SubbandInfoPS;
	int nGrans;
	int channles;
	int nGranSamps;
    #if 1 //(HW_MP3D_EN == 1)
	short MP3HWDecS_mp3decSp[32];
	short *MP3HWDecS_Spectrum;
    #endif
} STAGE_MP3DecInfo;

typedef struct _MP3DecBlockCount {
	MMP_LONG nBlocksLong;
	MMP_LONG nBlocksTotal;
	MMP_LONG nBlocksPrev; 
	MMP_LONG prevType;
	MMP_LONG prevWinSwitch;
	MMP_LONG currWinSwitch;
	MMP_LONG gbIn;
	MMP_LONG gbOut;
} MP3DecBlockCount;

typedef struct _MP3DecFrameInfo {
	MMP_LONG bitrate;
	MMP_LONG channles;
	MMP_LONG samprate;
	MMP_LONG bitsPerSample;
	MMP_LONG outSamples;
	MMP_LONG layer;
	MMP_LONG version;
	MMP_LONG vbr;
	MMP_LONG avgbr;
	MMP_LONG totaltime;
} MP3DecFrameInfo;

typedef void *MP3DecInstance;
//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================
extern const int    samplerateTab[3][3];
extern const short  bitrateTab[3][3][15];
extern const short  samplesPerFrameTab[3][3];

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================
#if 0 //(HW_MP3D_EN == 0)
int             MP3Dec_SetWorkingBuf(int *workingBuf);
MP3DecInstance  MP3InitDecoder(void);
int             MP3Decode(MP3DecInstance hMP3Decoder, unsigned char **inbuf, int *bytesLeft, short *outbuf, int useSize);
void            MP3GetLastFrameInfo(MP3DecInstance hMP3Decoder, MP3DecFrameInfo *mp3FrameInfo);
int             MP3FindSyncWord(unsigned char *buf, int nBytes);
void            mp3Copy(unsigned char *tar, unsigned char *src, unsigned int len);
#else
MP3DecInstance  MP3HWDecS_MP3Dec_SetWorkingBuf(int *buf, int bufsize, int *size);
int             MP3HWDecS_MP3InitDecoder(MP3DecInstance hMP3Decoder, void *userData);
int             MP3Decode_STAGE_HW(MP3DecInstance hMP3Decoder, int stage, short *outbuf);
int             MP3Decode_SWHW_Config(MP3DecInstance hMP3Decoder, int config);
int             MP3HWDecS_MP3FindSyncWord(MP3DecInstance hMP3Decoder, unsigned char *buf, int nBytes, unsigned int decodedbytes);
int             MP3HWDecS_MP3Decode(MP3DecInstance hMP3Decoder, unsigned char **inbuf, int *bytesLeft, short *outbuf, unsigned int decodedbytes);
int             MP3HWDecS_MP3GetLastFrameInfo(MP3DecInstance hMP3Decoder, MP3DecFrameInfo *mp3FrameInfo);
int             MP3HWDecS_MP3GetTotalFrameCount(MP3DecInstance hMP3Decoder, unsigned int *totalframe);
int             MP3HWDecS_MP3SetParsingVBREnable(MP3DecInstance hMP3Decoder, unsigned char enable);
int             MP3HWDecS_MP3SetSearchVBREnable(MP3DecInstance hMP3Decoder, unsigned int enable);
int             MP3HWDecS_MP3GetSpectrum(MP3DecInstance hMP3Decoder, short *sp);
unsigned int    MP3HWDecS_MP3GetID3Size(MP3DecInstance hMP3Decoder);
int             MP3HWDecS_MP3SetID3Size(MP3DecInstance hMP3Decoder, unsigned int size);
void            MP3HWDecS_mp3Copy(unsigned char *tar, unsigned char *src, unsigned int len);
#endif

#endif //_MP3DEC_INCLUDE_H_