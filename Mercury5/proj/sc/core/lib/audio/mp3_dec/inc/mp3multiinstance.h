
/**************************************************************************************
 *
 * multiinstance.h
 **************************************************************************************/

#ifndef _MP3MULTIINSTANCE_H
#define _MP3MULTIINSTANCE_H

#include "stdio.h"
#include "string.h"
#include "mp3coder.h"

#ifndef NULL
	#define NULL 				(0)
#endif
#ifndef MAX_DECODE_INSTANCE
	#define MAX_DECODE_INSTANCE (2) //max decoder instances
#endif

typedef int (*MP3D_IMDCTFuncP)(void *mp3DecInfo_v, int gr, int ch, void *userData);
typedef int (*MP3D_SubbandFuncP)(void *mp3DecInfo_v, short *pcmBuf, void *userData);
typedef int (*MP3D_MP3DecodeFuncP)(void *mp3DecInfo_v, short *pcmBuf, int gr, void *userData);

typedef struct _MP3DataStruct {
	MP3DecInfo          mp3info;
	MP3DecFrameHdr      frhd;
	MP3DecSideInfo      sideinfo;
	ScaleFactorInfo     scaleinfo;
	MP3DecHuffmanInfo   hfminfo;
	DequantInfo         dqinfo;
} MP3DataStruct;

typedef struct _MP3DecHandler {
	/* declare in buffer.c */
	int                 *STAGE_WorkingBuf;
	int                 STAGE_WorkingBuf_Size;
	int                 STAGE_WorkingBuf_Idx;
	MP3DataStruct       mp3data;
    #if (SW_HW_PIPELINE_PINGPONG == 1)
    //alterman@201012223: to remove CPU copy, use ping-pong buffer
    MP3DecHuffmanInfo   STAGE_HuffmanInfoPS[2][MAX_NGRAN];//ping-pong for SW/HW
	MP3DecHuffmanInfo   *STAGE_HuffmanInfoPS_SW[MAX_NGRAN];
	MP3DecHuffmanInfo   *STAGE_HuffmanInfoPS_HW[MAX_NGRAN];
    #else
    MP3DecHuffmanInfo   STAGE_HuffmanInfoPS_SW[MAX_NGRAN];
	MP3DecHuffmanInfo   STAGE_HuffmanInfoPS_HW[MAX_NGRAN];
    #endif
	MP3DecIMDCTInfo     STAGE_IMDCTInfoPS;
	MP3DecSubbandInfo   STAGE_SubbandInfoPS;
	/* declare in mp3dec.c */
	MP3DecHuffmanInfo   OldHuffmanInfo;
    #if (SW_HW_PIPELINE_PINGPONG == 1)
    //alterman@201012223: to remove CPU copy, use ping-pong buffer
    STAGE_MP3DecInfo    stage_mp3decInfo[2];
	STAGE_MP3DecInfo    *stage_mp3decInfo_sw;
	STAGE_MP3DecInfo    *stage_mp3decInfo_hw;
    #else
    STAGE_MP3DecInfo    stage_mp3decInfo_sw;
	STAGE_MP3DecInfo    stage_mp3decInfo_hw;
    #endif
	unsigned int        MP3HWDecS_glMP3TotalFrame;
	unsigned int        MP3HWDecS_glSearchVBRHeader;
	int                 MP3HWDecS_glID3Size;
	int                 glFrameValid;
	int                 MP3D_HW_FUNC_FLAG;  //0: pure-SW, 1: SUBBAND + IMDCT + MP3HWDecS_MP3Decode
	int                 MP3Decode_On_Flag;
	MP3D_IMDCTFuncP     pfMP3D_IMDCT;
	MP3D_SubbandFuncP   pfMP3D_Subband;
	MP3D_MP3DecodeFuncP pfMP3D_MP3Decode;
	unsigned char       MP3HWDecS_glParsingVBRMP3;
	void                *userData;
    unsigned int        pingPongIdx;
} MP3DecHandler;

#endif
