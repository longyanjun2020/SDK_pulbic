/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description : Jpeg Decoder Container
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: jpegdeccontainer.h,v $
--  $Revision: 1.4 $
--  $Date: 2008/02/04 12:46:38 $
--
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------

    Table of contents 
   
    1. Include headers
    2. Module defines
    3. Data types
    4. Function prototypes

------------------------------------------------------------------------------*/

#ifndef JPEGDECCONT_H
#define JPEGDECCONT_H

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/
#include "drv_mfd_basetype.h"
#include "drv_mfd_jpegdecapi.h"
#include "drv_mfd_dwl.h"
#include "drv_mfd_deccfg.h"
#include "drv_mfd_decppif.h"

/*------------------------------------------------------------------------------
    2. Module defines
------------------------------------------------------------------------------*/
#ifdef _ASSERT_USED
#include <assert.h>
#endif

/* macro for assertion, used only if compiler flag _ASSERT_USED is defined */
#ifdef _ASSERT_USED
#define ASSERT(expr) assert(expr)
#else
//#define ASSERT(expr) //move to mstar_fpga.h
#endif

#define MAX_NUMBER_OF_COMPONENTS 3

#define JPEG_DWL_TIME_OUT -1

#define JPEGDEC_X170_REGISTERS          38

#ifndef NULL
#define NULL 0
#endif

#ifdef JPEGDEC_ASIC_TRACE
#define JPEG_REGS 38
#endif /* #ifdef JPEGDEC_ASIC_TRACE */

#define JPEGDEC_X170_MIN_BUFFER 5120
#define JPEGDEC_X170_MAX_BUFFER 16776960
#define JPEGDEC_MAX_SLICE_SIZE 4096
#define JPEGDEC_TABLE_SIZE 544
#define JPEGDEC_MIN_WIDTH 48
#define JPEGDEC_MIN_HEIGHT 48
#define JPEGDEC_MAX_WIDTH 4672
#define JPEGDEC_MAX_HEIGHT 4672
#define JPEGDEC_MAX_PIXEL_AMOUNT 16370688
#define JPEGDEC_MAX_WIDTH_TN 256
#define JPEGDEC_MAX_HEIGHT_TN 256
#define JPEGDEC_YUV400 0
#define JPEGDEC_YUV420 2
#define JPEGDEC_YUV422 3
#define JPEGDEC_YUV444 4
#define JPEGDEC_YUV440 5

/*------------------------------------------------------------------------------
    3. Data types
------------------------------------------------------------------------------*/

typedef struct
{
    u32 C;  /* Component id */
    u32 H;  /* Horizontal sampling factor */
    u32 V;  /* Vertical sampling factor */
    u32 Tq; /* Quantization table destination selector */
} Components;

typedef struct
{
    u8 *pStartOfStream;
    u8 *pCurrPos;
    u32 streamBus;
    u32 bitPosInByte;
    u32 streamLength;
    u32 readBits;
    u32 appnFlag;
    u32 thumbnail;
    u32 returnSosMarker;
} StreamStorage;

typedef struct
{
    u8 *pStartOfImage;
    u8 *pLum;
    u8 *pCr;
    u8 *pCb;
    u32 imageReady;
    u32 headerReady;
    u32 size;
    u32 sizeLuma;
    u32 sizeChroma;
    u32 ready;
    u32 columns[MAX_NUMBER_OF_COMPONENTS];
    u32 pixelsPerRow[MAX_NUMBER_OF_COMPONENTS];
} ImageData;

typedef struct
{
    u32 Lf;
    u32 P;
    u32 Y;
    u32 hwY;
    u32 X;
    u32 hwX;
    u32 Nf; /* Number of components in frame */
    u32 codingType;
    u32 numMcuInFrame;
    u32 numMcuInRow;
    u32 numMcuInFrameInput;
    u32 numMcuInRowInput;
    u32 mcuNumber;
    u32 nextRstNumber;
    u32 Ri;
    u32 driPeriod;
    u32 block;
    u32 row;
    u32 col;
    u32 cIndex;
    u32 *pBuffer;
    u32 bufferBus;
    i32 *pBufferCb;
    i32 *pBufferCr;
    MEMMAP_t pTableBase;
    u32 numBlocks[MAX_NUMBER_OF_COMPONENTS];
    u32 blocksPerRow[MAX_NUMBER_OF_COMPONENTS];
    u32 useAcOffset[MAX_NUMBER_OF_COMPONENTS];
    Components component[MAX_NUMBER_OF_COMPONENTS];
} FrameInfo;

typedef struct
{
    u32 Ls;
    u32 Ns;
    u32 Cs[MAX_NUMBER_OF_COMPONENTS];   /* Scan component selector */
    u32 Td[MAX_NUMBER_OF_COMPONENTS];   /* Selects table for DC */
    u32 Ta[MAX_NUMBER_OF_COMPONENTS];   /* Selects table for AC */
    u32 Ss;
    u32 Se;
    u32 Ah;
    u32 Al;
    u32 index;
    i32 numIdctRows;
    i32 pred[MAX_NUMBER_OF_COMPONENTS];
} ScanInfo;

typedef struct
{
    u32 sliceHeight;
    u32 amountOfQTables;
    u32 yCbCrMode;
    u32 yCbCr422;
    u32 column;
    u32 X;
    u32 Y;
    u32 memSize;
    u32 SliceCount;
    u32 verPadNeeded;
    u32 horPadNeeded;
    u32 SliceReadyForPause;
    u32 SliceMBCutValue;
    u32 pipeline;
    u32 userAllocMem;
    u32 sliceMbSetValue;
    u32 timeout;
    u32 rlcMode;
    u32 lumaPos;
    u32 chromaPos;
    u32 sliceStartCount;
    u32 amountOfSlices;
    u32 noSliceIrqForUser;
    u32 sliceLimitReached;
    u32 inputBufferEmpty;
    u32 fill;
    u32 streamEnd;
    u32 inputBufferLen;
    u32 inputStreaming;
    u32 decodedStreamLen;
    u32 init;
    u32 initThumb;
    u32 initBufferSize;
    i32 dcRes[MAX_NUMBER_OF_COMPONENTS];
    MEMMAP_t outLuma;
    MEMMAP_t outChroma;
    MEMMAP_t givenOutLuma;
    MEMMAP_t givenOutChroma;
    i32 pred[MAX_NUMBER_OF_COMPONENTS];
} DecInfo;

typedef struct
{

    MEMMAP_t outLumaBuffer;
    MEMMAP_t outChromaBuffer;

} JpegAsicBuffers;

typedef struct
{
    u32 bits[16];
    u32 *vals;
    u32 tableLength;
    u32 start;
    u32 last;
} VlcTable;

typedef struct
{
    u32 Lh;
    VlcTable acTable0;
    VlcTable acTable1;
    VlcTable dcTable0;
    VlcTable dcTable1;
    VlcTable *table;
} HuffmanTables;

typedef struct
{
    u32 Lq; /* Quantization table definition length */
    u32 table0[64];
    u32 table1[64];
    u32 table2[64];
    u32 table3[64];
    u32 *table;
} QuantTables;

typedef struct
{
    u32 jpegRegs[DEC_X170_REGISTERS];
    u32 asicRunning;
    StreamStorage stream;
    FrameInfo frame;
    ImageData image;
    ScanInfo scan;
    DecInfo info;
    HuffmanTables vlc;
    QuantTables quant;
    u32 tmpData[64];
    JpegAsicBuffers asicBuff;
    DecPpInterface ppControl;
    DecPpQuery ppConfigQuery;   /* Decoder asks pp info about setup, info stored here */
    u32 ppStatus;
    const void *dwl;    /* DWL instance */

    const void *ppInstance;
    void (*PPRun) (const void *, DecPpInterface *);
    void (*PPEndCallback) (const void *);
    void (*PPConfigQuery) (const void *, DecPpQuery *);

} JpegDecContainer;

/*------------------------------------------------------------------------------
    4. Function prototypes
------------------------------------------------------------------------------*/

#endif /* #endif JPEGDECDATA_H */
