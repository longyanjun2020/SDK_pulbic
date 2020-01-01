/**************************************************************************************
 *
 * coder.h - private, implementation-specific header file
 **************************************************************************************/

#ifndef _CODER_H
#define _CODER_H

#include "mp3common.h"

#if defined(_WIN32) && defined(_M_IX86) && (defined (_DEBUG) || defined (REL_ENABLE_ASSERTS))
#define ASSERT(x) if (!(x)) __asm int 3;
#else
#define ASSERT(x) /* do nothing */
#endif

/* clip to range [-2^n, 2^n - 1] */
#define CLIP_2N(y, n) { \
	int sign = (y) >> 31;  \
	if (sign != (y) >> (n))  { \
		(y) = sign ^ ((1 << (n)) - 1); \
	} \
}

#define SIBYTES_MPEG1_MONO		17
#define SIBYTES_MPEG1_STEREO	32
#define SIBYTES_MPEG2_MONO		 9
#define SIBYTES_MPEG2_STEREO	17

/* number of fraction bits for pow43Tab (see comments there) */
#define POW43_FRACBITS_LOW		22
#define POW43_FRACBITS_HIGH		12

#define DQ_FRACBITS_OUT			25	/* number of fraction bits in output of dequant */
#define	IMDCT_SCALE				2	/* additional scaling (by sqrt(2)) for fast IMDCT36 */

#define	HUFF_PAIRTABS			32
#define BLOCK_SIZE				18
#define	NBANDS					32
#define MAX_REORDER_SAMPS		((192-126)*3)		/* largest critical band for short blocks (see sfBandTable) */
#define VBUF_LENGTH				(17 * 2 * NBANDS)	/* for double-sized vbuf FIFO */

/* additional external symbols to name-mangle for static linking */
#define	SetBitstreamPointer	STATNAME(SetBitstreamPointer)
#define	GetBits				STATNAME(GetBits)
#define	CalcBitsUsed		STATNAME(CalcBitsUsed)
#define	DequantChannel		STATNAME(DequantChannel)
#define	MidSideProc			STATNAME(MidSideProc)
#define	IntensityProcMPEG1	STATNAME(IntensityProcMPEG1)
#define	IntensityProcMPEG2	STATNAME(IntensityProcMPEG2)
#define PolyphaseMono		STATNAME(PolyphaseMono)
#define PolyphaseStereo		STATNAME(PolyphaseStereo)
#define FDCT32				STATNAME(FDCT32)

#define	ISFMpeg1			STATNAME(ISFMpeg1)
#define	ISFMpeg2			STATNAME(ISFMpeg2)
#define	ISFIIP				STATNAME(ISFIIP)
#define uniqueIDTab			STATNAME(uniqueIDTab)
#define	coef32				STATNAME(coef32)
#define	polyCoef			STATNAME(polyCoef)
#define	csa					STATNAME(csa)
#define	imdctWin			STATNAME(imdctWin)

#define	huffTable			STATNAME(huffTable)
#define	huffTabOffset		STATNAME(huffTabOffset)
#define	huffTabLookup		STATNAME(huffTabLookup)
#define	quadTable			STATNAME(quadTable)
#define	quadTabOffset		STATNAME(quadTabOffset)
#define	quadTabMaxBits		STATNAME(quadTabMaxBits)

typedef struct _BitStreamInfo {
	unsigned char *bytePtr;
	unsigned int iCache;
	int cachedBits;
	int nBytes;
} BitStreamInfo;

typedef struct {
    int cbType;		/* pure long = 0, pure short = 1, mixed = 2 */
    int cbEndS[3];	/* number nonzero short cb's, per subbblock */
	int cbEndSMax;	/* max of cbEndS[] */
    int cbEndL;		/* number nonzero long cb's  */
} CriticalBandInfo;

typedef struct _DequantInfo {
	int *workBuf;						/* workbuf for reordering short blocks */
	CriticalBandInfo cbi[MAX_NCHAN];	/* filled in dequantizer, used in joint stereo reconstruction */
} DequantInfo;

typedef enum _HuffTabType {
	noBits,
	oneShot,
	loopNoLinbits,
	loopLinbits,
	quadA,
	quadB,
	invalidTab
} HuffTabType;

typedef struct _HuffTabLookup {
	int	linBits;
	HuffTabType tabType;
} HuffTabLookup;

/* max bits in scalefactors = 5, so use char's to save space */
typedef struct _ScaleFactorInfoSub {
	char l[23];            /* [band] */
	char s[13][3];         /* [band][window] */
} ScaleFactorInfoSub;  

/* used in MPEG 2, 2.5 intensity (joint) stereo only */
typedef struct _ScaleFactorJS {
	int intensityScale;		
	int	slen[4];
	int	nr[4];
} ScaleFactorJS;

typedef struct _ScaleFactorInfo {
	ScaleFactorInfoSub sfis[MAX_NGRAN][MAX_NCHAN];
	ScaleFactorJS sfjs;
} ScaleFactorInfo;

/* bitstream.c */
void SetBitstreamPointer(BitStreamInfo *bsi, int nBytes, unsigned char *buf);
unsigned int GetBits(BitStreamInfo *bsi, int nBits);
int CalcBitsUsed(BitStreamInfo *bsi, unsigned char *startBuf, int startOffset);

/* dequant.c, dqchan.c, stproc.c */
int DequantChannel(int *sampleBuf, int *workBuf, int *nonZeroBound, MP3DecFrameHdr *fh, MP3DecSideInfoSub *sis, 
					ScaleFactorInfoSub *sfis, CriticalBandInfo *cbi);
//void MidSideProc(int x[MAX_NCHAN][MAX_NSAMP], int nSamps, int mOut[2]);
void MidSideProc(int *x[MAX_NCHAN], int nSamps, int mOut[2]);
//void IntensityProcMPEG1(int x[MAX_NCHAN][MAX_NSAMP], int nSamps, MP3DecFrameHdr *fh, ScaleFactorInfoSub *sfis, 
void IntensityProcMPEG1(int *x[MAX_NCHAN], int nSamps, MP3DecFrameHdr *fh, ScaleFactorInfoSub *sfis, 
						CriticalBandInfo *cbi, int midSideFlag, int mixFlag, int mOut[2]);
//void IntensityProcMPEG2(int x[MAX_NCHAN][MAX_NSAMP], int nSamps, MP3DecFrameHdr *fh, ScaleFactorInfoSub *sfis, 
void IntensityProcMPEG2(int *x[MAX_NCHAN], int nSamps, MP3DecFrameHdr *fh, ScaleFactorInfoSub *sfis, 
						CriticalBandInfo *cbi, ScaleFactorJS *sfjs, int midSideFlag, int mixFlag, int mOut[2]);

/* dct32.c */
void FDCT32(int *x, int *d, int offset, int oddBlock, int gb);

/* hufftabs.c */
extern const HuffTabLookup huffTabLookup[HUFF_PAIRTABS];
extern const int huffTabOffset[HUFF_PAIRTABS];
extern const unsigned short huffTable[];
extern const unsigned char quadTable[64+16];
extern const int quadTabOffset[2];
extern const int quadTabMaxBits[2];

#ifdef __cplusplus
extern "C" {
#endif
void PolyphaseMono(short *pcm, int *vbuf, const int *coefBase);
void PolyphaseStereo(short *pcm, int *vbuf, const int *coefBase);
#ifdef __cplusplus
}
#endif

/* trigtabs.c */
extern const int imdctWin[4][36];
extern const int ISFMpeg1[2][7];
extern const int ISFMpeg2[2][2][16];
extern const int ISFIIP[2][2];
extern const int csa[8][2];
extern const int coef32[31];
extern const int polyCoef[264];

#endif	/* _CODER_H */
