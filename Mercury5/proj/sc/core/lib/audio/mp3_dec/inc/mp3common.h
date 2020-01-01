
/**************************************************************************************
 *
 * mp3common.h - implementation-independent API's, datatypes, and definitions
 **************************************************************************************/

#ifndef _MP3COMMON_H
#define _MP3COMMON_H

#include "mp3typedef.h"
#include "mp3dec.h"
#include "mp3dec_include.h"
#include "statname.h"	/* do name-mangling for static linking */

#define NGRANS_MPEG1	2
#define NGRANS_MPEG2	1

typedef struct _MP3DecInfo {
	/* pointers to platform-specific data structures */
	void *FrameHeaderPS;
	void *SideInfoPS;
	void *ScaleFactorInfoPS;
	void *HuffmanInfoPS;
	void *DequantInfoPS;
//	void *IMDCTInfoPS;
//	void *SubbandInfoPS;

	/* buffer which must be large enough to hold largest possible main_data section */
//	unsigned char mainBuf[MAINBUF_SIZE];
	unsigned char *mainBuf;

	/* special info for "free" bitrate files */
	int freeBitrateFlag;
	int freeBitrateSlots;

	/* user-accessible info */
	int bitrate;
	int channles;
	int samprate;
	int nGrans;				/* granules per frame */
	int nGranSamps;			/* samples per granule */
	int nSlots;
	int layer;
	MPAVersion version;

	int mainDataBegin;
	int mainDataBytes;

	int part23Length[MAX_NGRAN][MAX_NCHAN];

} MP3DecInfo;



/* decoder functions which must be implemented for each platform */
//void FreeBuffers(MP3DecInfo *mp3DecInfo);
int CheckPadBit(MP3DecInfo *mp3DecInfo);
int UnpackFrameHeader(MP3DecInfo *mp3DecInfo, unsigned char *buf);
int UnpackSideInfo(MP3DecInfo *mp3DecInfo, unsigned char *buf);
int Dequantize(MP3DecInfo *mp3DecInfo, int gr);
//int IMDCT(MP3DecInfo *mp3DecInfo, int gr, int ch, void *userData);
int IMDCT(void *mp3DecInfo, int gr, int ch, void *userData);

int UnpackScaleFactors(MP3DecInfo *mp3DecInfo, unsigned char *buf, int *bitOffset, int bitsAvail, int gr, int ch);
//int Subband(MP3DecInfo *mp3DecInfo, short *pcmBuf);
int Subband(void *mp3DecInfo, short *pcmBuf, void *userData);

void MP3HWDecS_mp3Copy(unsigned char *tar, unsigned char *src, unsigned int len);
#if (SW_IMDCT_SUBBAND_DIS == 0) //alterman@20110308: for reducing code size
void mp3Zero(unsigned char *tar, unsigned char c, unsigned int len);
#endif

/* mp3tabs.c - global ROM tables */
extern const int samplerateTab[3][3];
extern const short bitrateTab[3][3][15];
extern const short samplesPerFrameTab[3][3];
extern const short bitsPerSlotTab[3];
extern const short sideBytesTab[3][2];
extern const short slotTab[3][3][15];
extern const MP3DecSFBandTable sfBandTable[3][3];
#endif	/* _MP3COMMON_H */