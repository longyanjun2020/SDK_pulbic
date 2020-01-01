///////////////////////////////////////////////////////////////////////////////
// File   : ima_adpcm_enc.h
// Author : MStar Semiconductor Inc. (CA.Wang)
// Brief  : IMA ADPCM Encoder
///////////////////////////////////////////////////////////////////////////////
#ifndef __IMA_ADPCM_ENC__
#define __IMA_ADPCM_ENC__


//=============================================================================
// Include Files
//=============================================================================
#include "wavenc_mgr_datatype.h"
#include <stdio.h>



//=============================================================================
// Function Define
//=============================================================================

//======== Print Message Switch========
#define ENABLE_IMAADPCMENC_DBG_PRINTF




//=============================================================================
// Define
//=============================================================================

//============ print message ==========
#ifdef ENABLE_IMAADPCMENC_DBG_PRINTF
#ifndef ON_MONTAGE
#define IMAADPCMENC_DBG_MSG       printf
#else
#define IMAADPCMENC_DBG_MSG       diag_printf
#endif
#else
#ifndef ON_MONTAGE
#define IMAADPCMENC_DBG_MSG
#else
#define IMAADPCMENC_DBG_MSG(fmt, args...)
#endif
#endif


#ifdef ENABLE_IMAADPCMENC_DBG_PRINTF
#ifndef ON_MONTAGE
#define IMAADPCMENC_PARSER_MSG       printf
#else
#define IMAADPCMENC_PARSER_MSG       diag_printf
#endif
#else
#ifndef ON_MONTAGE
#define IMAADPCMENC_PARSER_MSG
#else
#define IMAADPCMENC_PARSER_MSG(fmt, args...)
#endif
#endif




//=============================================================================
// IMA ADPCM ENC Limiter Structure/Paramater
//=============================================================================

//=====================================
//        EXTEND WAVE FORMAT
//=====================================

// WAVFORNATEX => size = 18
typedef struct
{
	U16 u16FormatTag;
	U16 u16Channel;
	U32 u32SamplesPerSec;
	U32 u32AvgBytesPerSec;
	U16 u16BlockAlign;
	U16 u16BitsPerSample;
    U16 u16CbSize;
}WaveFmtExt;
#define WAVEFORMATEX_SIZE 18




//=====================================
//       IMA-ADPCM WAVE FORMAT
//=====================================

// IMA-ADPCM WAVE FORMAT => size = 18 +2 = 20
typedef struct
{
    WaveFmtExt wf_ext;
    U16 u16SamplesPerBlock;
}IMAADPCM_WaveFmt;
#define IMAADPCM_WAVEFORMAT_SIZE (WAVEFORMATEX_SIZE + 2)




//=====================================
//              Chunk
//=====================================

// RIFF Chunk : Wave Master-Chunk = > size = 12 bytes
typedef struct
{
	ADPCM_S8   Tag_RIFF[4];               // "riff"                   => 4 bytes
	U32  TotalSize;                 // ...                      => 4 bytes
	ADPCM_S8   Tag_WAVE[4];               // "wave"                   => 4 bytes
}IMAADPCM_RIFFChunk;
#define IMAADPCM_RIFFCHUNK_SIZE 12


// FORMAT Chunk : Wave Sub-Chunk => size = 28 bytes
typedef struct
{
	ADPCM_S8   Tag_fmt[4];               // " fmt"
	U32  FmtSize;                  // 20
	IMAADPCM_WaveFmt imaadpcm_wf;
}IMAADPCM_FmtExtChunk;
#define IMAADPCM_FORMATCHUNK_SIZE (IMAADPCM_WAVEFORMAT_SIZE + 4 + 4)


// FACT Chunk : Wave Sub-Chunk = > size = 12 bytes
typedef struct
{
    ADPCM_S8   Tag_Fact[4];               // "fact"
    U32  chunksize;
    U32  datafactsize;
}IMAADPCM_FactChunk;
#define IMAADPCM_FACTCHUNK_SIZE 12


// DATA Chunk : Wave Sub-Chunk = > size = 8 bytes
typedef struct
{
	ADPCM_S8   Tag_Data[4];               // "data"
	U32  DataSize;                  // ...
}IMAADPCM_DataChunk;
#define IMAADPCM_DATACHUNK_SIZE 8




//=====================================
//      Wave Header of IMA-ADPCM
//=====================================

// IMAADPCM HEADER
typedef struct {
    IMAADPCM_RIFFChunk    RIFFChk;  // Master-Chunk : RIFF Chunk   => 12 bytes
	IMAADPCM_FmtExtChunk  FmtChk;   // Sub-Chunk    : FORMAT Chunk => 28 bytes
	IMAADPCM_FactChunk    FactChk;  // Sub-Chunk    : FACT Chunk   => 12 bytes
    IMAADPCM_DataChunk    DataChk;  // Sub-Chunk    : DATA Chunk   => 8 bytes
}IMAADPCM_WaveHeader;
#define IMAADPCM_HEADER_SIZE (IMAADPCM_RIFFCHUNK_SIZE + IMAADPCM_FORMATCHUNK_SIZE + IMAADPCM_FACTCHUNK_SIZE + IMAADPCM_DATACHUNK_SIZE)




//=====================================
//      Block Header of IMA-ADPCM
//=====================================

// IMAADPCM BLOCK HEADER
typedef struct {
    // size = 4
    S16 iSamp0;
    U8  bStepTableIndex;
    U8  bReserved;
}IMAADPCM_BlockHeader;
#define IMAADPCM_BLOCK_HEADER_SIZE 4




//=====================================
//    IMA-ADPCM Data Control Manager
//=====================================

typedef struct {
    IMAADPCM_WaveHeader   sFileHeader;
    IMAADPCM_BlockHeader  sBlockHeader[2];
    U32 u32BlockCount;
    U32 u32totaltime_ex;
}IMAADPCM_EncCtrStrc;




//=============================================================================
// Extern Function Declare
//=============================================================================

#ifdef __cplusplus
extern "C"
{
#endif

BOOL IMA_ADPCM_Read_CurTotalTime( IMAADPCM_EncCtrStrc * psIMAADPCM_EncCtr, U32* pu32CurTotalTime );

BOOL IMA_ADPCM_Read_CurTotalSize( IMAADPCM_EncCtrStrc * psIMAADPCM_EncCtr, U32* pu32CurTotalTime );

BOOL IMA_ADPCM_Read_FileHeader( IMAADPCM_EncCtrStrc * psIMAADPCM_EncCtr,
                                              U8*  pu8OutBuf,
                                              S32  s32OutBufSize,
                                              S32* ps32OutBufUsedCount );
BOOL IMA_ADPCM_Retrieve_FileHeader( IMAADPCM_EncCtrStrc * psIMAADPCM_EncCtr,
                                              U8*  pu8InBuf,
                                              S32  s32InBufSize);


BOOL IMA_ADPCM_Read_SamplesPerChPerBlk( IMAADPCM_EncCtrStrc * psIMAADPCM_EncCtr,
                                                           S32* ps32SampleSizePerChn);

BOOL IMA_ADPCM_Encoder_Init( IMAADPCM_EncCtrStrc * psIMAADPCM_EncCtr,
						                U32 u32SampleRate,
						                U16 u16Channel,
						                U16 u16BitsPerSample );

BOOL IMA_ADPCM_Update_BlockHeader( IMAADPCM_EncCtrStrc*  psIMAADPCM_EncCtr,
                                                  U8 * pu8InBuf,
                                                  S32  s32InBufDataSize,
                                                  S32* ps32InBufUsedCount,
                                                  U8*  pu8OutBuf,
                                                  S32  s32OutBufSize,
                                                  S32* ps32OutBufUsedCount );

BOOL IMA_ADPCM_Encoder_BlockEnc( IMAADPCM_EncCtrStrc * psIMAADPCM_EncCtr,
                                                U8*  pu8InBuf,
                                                S32  s32InBufDataSize,
                                                S32* ps32InBufUsedCount,
                                                U8*  pu8OutBuf,
                                                S32  s32OutBufSize,
                                                S32* ps32OutBufUsedCount );

BOOL IMA_ADPCM_Encoder_Close( IMAADPCM_EncCtrStrc * psIMAADPCM_EncCtr);

#ifdef __cplusplus
}
#endif


#endif

