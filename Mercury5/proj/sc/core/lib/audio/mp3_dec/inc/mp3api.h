#include "mp3typedef.h"
#if defined (AIT_PLATFORM)
#include "fs_fat.h"
#include "audio_ctl.h"
#endif
#ifndef MP3_API
#define MP3_API

#define MAXFRAMESIZE	2304	// max frame output samples
#define OUTFRAMESIZE	2304	// 2304 or 1152

#define MP3_BUFDEPTH	3
#define MP3_RETRY_NUM   100
#define MP3_PARTIAL_SEARCH	0		//fast parsing
#define MP3_FULL_SEARCH		1		//precise parsing

#define	STAGE_HUFFMAN					(1)
//#define	STAGE_GRAN_0_CHAN_0_HUFFMAN		(1)
//#define	STAGE_GRAN_0_CHAN_1_HUFFMAN		(2)
//#define	STAGE_GRAN_1_CHAN_0_HUFFMAN		(3)
//#define	STAGE_GRAN_1_CHAN_1_HUFFMAN		(4)
#define	STAGE_GRAN_0_CHAN_0_IMDCT		(5)
#define	STAGE_GRAN_0_CHAN_1_IMDCT		(6)
#define	STAGE_GRAN_0_Subband			(7)
#define	STAGE_GRAN_1_CHAN_0_IMDCT		(8)
#define	STAGE_GRAN_1_CHAN_1_IMDCT		(9)
#define	STAGE_GRAN_1_Subband			(10)
#define	STAGE_IDLE						(11)
#define	STAGE_WAIT						(12)
#define	STAGE_MP3DECODE_GR0             (13)
#define	STAGE_MP3DECODE_GR1             (14)

#endif

typedef struct {	
	Word32	byteLeft;			// remainder bytes in buffer
} InDataObj;

typedef struct {
	Word32u	rd_ind;				// read pointer
	Word32u	wr_ind;				// write pointer
	Word32 	SampleLeft;			// remainder samples in buffer
	Word32u BufButton;			// 2*2304-1 or 2*1152	
} OutDataObj;

extern Word32 Mp3Init(void);
