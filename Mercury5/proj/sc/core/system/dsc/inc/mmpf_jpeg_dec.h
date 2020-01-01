//==============================================================================
//
//  File        : mmpf_jpeg_dec.h
//  Description : INCLUDE File for the JPEG Decode Driver Function
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_JPEG_DEC_H_
#define _MMPF_JPEG_DEC_H_

#include "mmp_err.h"
#include "mmp_dsc_inc.h"
#include "mmpf_typedef.h"
#include "njpeg_def.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

// For M5 JPD
#define JPEG_MANUFACTURER_SIZE      32UL
#define JPEG_MODEL_SIZE             128UL

#define MIN_READBUFFER_SIZE         128UL
#define MRC_CHECK_COUNT             5000UL
#define MRC_DECODE_TIMEOUT          3000UL

#define JPEG_DEFAULT_EXIF_SIZE      (64*1024UL + 128)

#define JPEG_DEC_MAX_QUEUE_SIZE     (40)
#define JPEG_DEC_MAX_QUEUE_WRAP_CNT (0xFFFFFFFF)
#define JPEG_DEC_INVALID_QUEUE_SIZE (0xFFFFFFFF)

#define JPEG_DEC_PSEUDO_DEC_DONE_FLAG (0xFFFFFFFF)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: MMPF_JPEGD_DEC_EVENT
/// @brief \b Enum \b Description: JPEG decode event
//-----------------------------------------------------------------------------
typedef enum // Map to NJPD_ISR_Handle_Id
{
    MMPF_JPEGD_DEC_EVENT_DEC_DONE = 0,
    MMPF_JPEGD_DEC_EVENT_DEC_ERR,
    MMPF_JPEGD_DEC_EVENT_MRC0_EMPTY,
    MMPF_JPEGD_DEC_EVENT_MRC1_EMPTY,
    MMPF_JPEGD_DEC_EVENT_WRITE_PROTECT,
    MMPF_JPEGD_DEC_EVENT_MAX
} MMPF_JPEGD_DEC_EVENT;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: MMPF_JPEGD_IMG_TYPE
/// @brief \b Enum \b Description: JPEG decode image type
//-----------------------------------------------------------------------------
typedef enum
{
    MMPF_JPEGD_IMG_TYPE_PRIMARY = 0,
    MMPF_JPEGD_IMG_TYPE_THUMB,
#if (DSC_SUPPORT_BASELINE_MP_FILE)
    MMPF_JPEGD_IMG_TYPE_LARGETHUMB,
#endif
    MMPF_JPEGD_IMG_TYPE_NUM
} MMPF_JPEGD_IMG_TYPE;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: MMPF_JPEGD_DEC_SRC
/// @brief \b Enum \b Description: JPEG decode source
//-----------------------------------------------------------------------------
typedef enum
{
    MMPF_JPEGD_DEC_SRC_MJPEG = 0,       ///< JPEG decode MJPEG Data
    MMPF_JPEGD_DEC_SRC_FILE,            ///< JPEG decode files
    MMPF_JPEGD_DEC_SRC_MEMORY,          ///< JPEG decode in memory
    MMPF_JPEGD_DEC_SRC_NONE = 0xFF
} MMPF_JPEGD_DEC_SRC;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: MMPF_JPEGD_DEC_STEP
/// @brief \b Enum \b Description: JPEG decode step
//-----------------------------------------------------------------------------
typedef enum
{
    MMPF_JPEGD_DEC_STEP_IDLE      = 0x01,
    MMPF_JPEGD_DEC_STEP_DEC_ERR   = 0x02,
    MMPF_JPEGD_DEC_STEP_DEC_HDR   = 0x03,
    MMPF_JPEGD_DEC_STEP_DEC_BEGIN = 0x04,
    MMPF_JPEGD_DEC_STEP_DEC_DONE  = 0x05,
    MMPF_JPEGD_DEC_STEP_WAIT_DONE = 0x06,
    MMPF_JPEGD_DEC_STEP_INIT      = 0x07
} MMPF_JPEGD_DEC_STEP;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: MMPF_JPEGD_DEC_STATUS
/// @brief \b Enum \b Description: JPEG decode status
//-----------------------------------------------------------------------------
typedef enum
{
    MMPF_JPEGD_DEC_STATUS_NONE = 0,
    MMPF_JPEGD_DEC_STATUS_DONE,
    MMPF_JPEGD_DEC_STATUS_ING,
    MMPF_JPEGD_DEC_STATUS_ERR,
    MMPF_JPEGD_DEC_STATUS_READ_ERR
} MMPF_JPEGD_DEC_STATUS;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_ERR_CODE
/// @brief \b Enum \b Description: JPEG error code
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_NO_ERROR                     = 0,
    E_JPEG_BAD_DHT_COUNTS               = -200,
    E_JPEG_BAD_DHT_INDEX                = -201,
    E_JPEG_BAD_DHT_MARKER               = -202,
    E_JPEG_BAD_DQT_MARKER               = -203,
    E_JPEG_BAD_DQT_TABLE                = -204,
    E_JPEG_BAD_PRECISION                = -205,
    E_JPEG_BAD_HEIGHT                   = -206,
    E_JPEG_BAD_WIDTH                    = -207,
    E_JPEG_TOO_MANY_COMPONENTS          = -208,
    E_JPEG_BAD_SOF_LENGTH               = -209,
    E_JPEG_BAD_VARIABLE_MARKER          = -210,
    E_JPEG_BAD_DRI_LENGTH               = -211,
    E_JPEG_BAD_SOS_LENGTH               = -212,
    E_JPEG_BAD_SOS_COMP_ID              = -213,
    E_JPEG_W_EXTRA_BYTES_BEFORE_MARKER  = -214,
    E_JPEG_NO_ARITHMETIC_SUPPORT        = -215,
    E_JPEG_UNEXPECTED_MARKER            = -216,
    E_JPEG_NOT_JPEG                     = -217,
    E_JPEG_UNSUPPORTED_MARKER           = -218,
    E_JPEG_BAD_DQT_LENGTH               = -219,
    E_JPEG_TOO_MANY_BLOCKS              = -221,
    E_JPEG_UNDEFINED_QUANT_TABLE        = -222,
    E_JPEG_UNDEFINED_HUFF_TABLE         = -223,
    E_JPEG_NOT_SINGLE_SCAN              = -224,
    E_JPEG_UNSUPPORTED_COLORSPACE       = -225,
    E_JPEG_UNSUPPORTED_SAMP_FACTORS     = -226,
    E_JPEG_DECODE_ERROR                 = -227,
    E_JPEG_BAD_RESTART_MARKER           = -228,
    E_JPEG_ASSERTION_ERROR              = -229,
    E_JPEG_BAD_SOS_SPECTRAL             = -230,
    E_JPEG_BAD_SOS_SUCCESSIVE           = -231,
    E_JPEG_STREAM_READ                  = -232,
    E_JPEG_NOTENOUGHMEM                 = -233,
    E_JPEG_STOP_DECODE                  = -234,
    E_JPEG_BAD_APP1_MARKER              = -235,
    E_JPEG_NO_THUMBNAIL                 = -236,
    E_JPEG_UNSUPPORTED_HUFF_DECODE      = -237,
    E_JPEG_READBUFFER_TOOSMALL          = -238,
    E_JPEG_NOT_ENOUGH_HEADER_INFO       = -240,
    E_JPEG_RE_INIT                      = -241,
    E_JPEG_NOT_INIT                     = -242,
    E_JPEG_BAD_APP0_MARKER              = -243,
    E_JPEG_BAD_APP2_MARKER              = -250,
    E_JPEG_INIT_INTC_FAIL               = -251,
    E_JPEG_JPD_DECODE_ERROR             = 0x5566
} JPEG_ERR_CODE;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_BUF_LOAD_TYPE
/// @brief \b Enum \b Description: JPEG buffer loading mode
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_BUFFER_NONE  = 0,
    E_JPEG_BUFFER_HIGH  = 1,
    E_JPEG_BUFFER_LOW   = 2
} JPEG_BUF_LOAD_TYPE;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_DOWNSCALE_RATIO
/// @brief \b Enum \b Description: JPEG down scale ratio
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_DOWNSCALE_ORG     = 0x00,
    E_JPEG_DOWNSCALE_HALF    = 0x01,
    E_JPEG_DOWNSCALE_FOURTH  = 0x02,
    E_JPEG_DOWNSCALE_EIGHTH  = 0x03
} JPEG_DOWNSCALE_RATIO;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_RESULT
/// @brief \b Enum \b Description: JPEG decode result
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_FAILED   = 0,
    E_JPEG_OKAY     = 1,
    E_JPEG_DONE     = 2,
    E_JPEG_RETRY    = 3
} JPEG_RESULT;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_EVENT
/// @brief \b Enum \b Description: JPEG decode event flag, return from MApi_JPEG_GetJPDEventFlag()
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_EVENT_DEC_NONE       = 0x00,
    E_JPEG_EVENT_DEC_DONE       = 0x01,
    E_JPEG_EVENT_DEC_ECS_ERROR  = 0x02,
    E_JPEG_EVENT_DEC_IS_ERROR   = 0x04,
    E_JPEG_EVENT_DEC_RST_ERROR  = 0x08,
    E_JPEG_EVENT_DEC_MRBL_DONE  = 0x10,
    E_JPEG_EVENT_DEC_MRBH_DONE  = 0x20,
    E_JPEG_EVENT_DEC_MRB_DONE   = 0x30, // (E_JPEG_EVENT_DEC_MRBL_DONE | E_JPEG_EVENT_DEC_MRBH_DONE)
    E_JPEG_EVENT_DEC_MWB_FULL   = 0x40,
    E_JPEG_EVENT_DEC_ERROR_MASK = 0x0E
} JPEG_EVENT;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_DECODE_STATUS
/// @brief \b Enum \b Description: JPEG decoder status, return from MApi_JPEG_WaitDone()
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_DEC_DONE             = 0,
    E_JPEG_DEC_FAILED           = 1,
    E_JPEG_DEC_RST_ERROR        = 2,
    E_JPEG_DEC_BITSTREAM_ERROR  = 3,
    E_JPEG_DEC_MRBL_DONE        = 4,
    E_JPEG_DEC_MRBH_DONE        = 5,
    E_JPEG_DEC_DECODING         = 6
} JPEG_DECODE_STATUS;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_SCAN_TYPE
/// @brief \b Enum \b Description: JPEG scan type
//-----------------------------------------------------------------------------
typedef enum
{
    E_JPEG_GRAYSCALE    = 0,
    E_JPEG_YH1V1        = 1,
    E_JPEG_YH2V1        = 2,
    E_JPEG_YH1V2        = 3,
    E_JPEG_YH2V2        = 4,
    E_JPEG_YH4V1        = 5,
    E_JPEG_CMYK         = 6,
    E_JPEG_RGB          = 7
} JPEG_SCAN_TYPE;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: MMPF_JPEGD_QUEUE_TYPE
/// @brief \b Enum \b Description: JPEG Queue Type
//-----------------------------------------------------------------------------
typedef enum
{
    MMPF_JPEGD_QUEUE_INPUT_Q = 0,
    MMPF_JPEGD_QUEUE_DONE_Q,
    MMPF_JPEGD_QUEUE_TYPE_NUM
} MMPF_JPEGD_QUEUE_TYPE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef void JpegDecCallBackFunc(int);

//-----------------------------------------------------------------------------
///@brief \b Typedef \b Name: *JPEG_FillHdrFunc
///@brief \b Typedef \b Description: the function for fill header information
///@param <IN> \b BufAddr : fill buffer address
///@param <IN> \b BufLength : fill buffer size
///@return The amount of byte read
//-----------------------------------------------------------------------------
typedef MMP_LONG (JPEG_FillHdrFunc)(MMP_BOOL bMemMode, MMP_ULONG ulBufAddr, MMP_ULONG ulBufLength);

//-----------------------------------------------------------------------------
///@brief \b Typedef \b Name: *JPEG_IsrFuncCb
///@brief \b Typedef \b Description: the function handling JPD interrupt
///@param None
///@return None
//-----------------------------------------------------------------------------
typedef void (*JPEG_IsrFuncCb)(int);

typedef struct _APP0_UNIT
{
    MMP_USHORT  usXdensity;     // inch or cm
    MMP_USHORT  usYdensity;     // inch or cm
    MMP_UBYTE   ubXthumbnail;
    MMP_UBYTE   ubYthumbnail;    
    MMP_UBYTE   ubUnit;         // APP0 Mark units : 0 -> no units, X and Y specify the pixel aspect ratio
                                //                   1 -> X and Y are dots per inch
                                //                   2 -> X and Y are dots per cm
} APP0_UNIT;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_HUFF_INFO (Same as JPEG_HuffInfo)
/// @brief \b Struct \b Description: Structure for JPEG huffman information
//-----------------------------------------------------------------------------
typedef struct _JPEG_HUFF_INFO
{
    MMP_UBYTE   ubHuff_num[17];     ///< Number of Huffman codes per bit size
    MMP_UBYTE   ubHuff_val[256];    ///< Huffman codes per bit size
    MMP_UBYTE   ubSymbol[17];       ///< ubHuff_num in reverse order
    MMP_USHORT  usCode[17];         ///< Minimun code word
    MMP_UBYTE   ubValid[17];        ///< Valid bit for NJPD
    MMP_UBYTE   ubSymbolCnt;        ///< Total symbol count
    MMP_BOOL    bValid;             ///< Has huffman table or not
} JPEG_HUFF_INFO;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_QUANT_TBL (Same as JPEG_QuantTbl)
/// @brief \b Struct \b Description: Structure for JPEG Quantization Table
//-----------------------------------------------------------------------------
typedef struct _JPEG_QUANT_TBL
{
    JPEG_QUANT_TYPE sValue[64];     ///< value of Q table
    MMP_BOOL        bValid;         ///< has Q table or not.
} JPEG_QUANT_TBL;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_HDR_CHK
/// @brief \b Struct \b Description: The info of header checking for JPEG decode
//-----------------------------------------------------------------------------
typedef struct _JPEG_HDR_CHK
{
    MMP_BOOL    DQT;                ///< has Quant Table?
    MMP_BOOL    DHT;                ///< has Huffman Table?
//  MMP_BOOL    SOF;
//  MMP_BOOL    SOS;
    MMP_BOOL    result;             ///< wildcard for header check
} JPEG_HDR_CHK;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_INIT_PARAM
/// @brief \b Struct \b Description: JPEG decode parameter setting
//-----------------------------------------------------------------------------
typedef struct _JPEG_INIT_PARAM
{
    MMP_ULONG   u32MRCBufAddr;      ///< MRC buffer address (VA)
    MMP_ULONG   u32MRCBufSize;      ///< MRC buffer size
    MMP_ULONG   u32MWCBufAddr;      ///< MWC buffer address (VA)
    MMP_ULONG   u32MWCBufSize;      ///< MWC buffer size
    MMP_ULONG   u32InternalBufAddr; ///< Internal buffer address (VA)
    MMP_ULONG   u32InternalBufSize; ///< Internal buffer size
    MMP_ULONG   u32DecByteRead;     ///< How many byte read for JPEG decoder initialization
    MMP_BOOL    bEOF;               ///< Has read to the end of file
    MMP_UBYTE   u8DecodeType;       ///< JPEG decode type : JPEG main, thumbnail, or MJPEG
    MMP_BOOL    bInitMem;           ///< Initialize memory pool or not
    JPEG_FillHdrFunc *pFillHdrFunc; ///< The function for fill header information
} JPEG_INIT_PARAM;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_STATUS
/// @brief \b Struct \b Description: JPD driver Status
//-----------------------------------------------------------------------------
typedef struct _JPEG_STATUS
{
    MMP_ULONG   u32CurMRCAddr;      ///< JPD current decoded address
    MMP_USHORT  u16CurRow;          ///< JPD current decoded row
    MMP_USHORT  u16CurCol;          ///< JPD current decoded column
    MMP_BOOL    bDrvBusy;           ///< JPD status
    MMP_BOOL    bIsrEnable;         ///< JPD ISR status
} JPEG_STATUS;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_DrvCap
/// @brief \b Struct \b Description: JPD driver capability
//-----------------------------------------------------------------------------
typedef struct _JPEG_DrvCap
{
    MMP_USHORT  u16MaxWidth;        ///< max decoded width for baseline
    MMP_USHORT  u16MaxHeight;       ///< max decoded height for baseline
    MMP_USHORT  u16MaxProWidth;     ///< max decoded width for progressive
    MMP_USHORT  u16MaxProHeight;    ///< max decoded height for progressive
    MMP_BOOL    bBaseline;          ///< support baseline decode
    MMP_BOOL    bProgressive;       ///< support progressive decode
    MMP_BOOL    bMJPEG;             ///< support motion JPEG
} JPEG_DrvCap;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: JPEG_Info
/// @brief \b Struct \b Description: JPD driver version
//-----------------------------------------------------------------------------
typedef struct _JPEG_Info
{
    MMP_UBYTE*  pu8HalVer;          ///< JPEG HAL version
    MMP_UBYTE*  pu8FwVer;           ///< JPEG FW version
    JPEG_DrvCap stDrvCap;           ///< JPEG driver capability
} JPEG_Info;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: MMPF_JPEGD_INPUT_ATTR
/// @brief \b Struct \b Description:
//-----------------------------------------------------------------------------
typedef struct _MMPF_JPEGD_INPUT_ATTR
{
    MMP_UBYTE               ubCompType;             ///< Decode Component Type
    MMP_UBYTE               ubDecSrc;               ///< Decode Source Type
    MMP_UBYTE               ubDecImgType;           ///< Decode Image Type
    MMP_ULONG               ulSrcBufAddr;           ///< Decode Source Buffer Address (Memory or MJPEG mode)
    MMP_ULONG               ulSrcBufSize;           ///< Decode Source Buffer Size (Memory or MJPEG mode)
    MMP_ULONG               ulInputBufAddr;         ///< Decode Input Buffer Address (MRC)
    MMP_ULONG               ulInputBufSize;         ///< Decode Input Buffer Size
    MMP_ULONG               ulOutputBufAddr;        ///< Decode Output Buffer Address (MWC)
    MMP_ULONG               ulOutputBufSize;        ///< Decode Output Buffer Size
    JpegDecCallBackFunc     *pfDecCBFunc;           ///< Decode Callback Function
    void*                   pDecCBFuncArg;          ///< Decode Callback Function Argument
} MMPF_JPEGD_INPUT_ATTR;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: MMPF_JPEGD_DONE_ATTR
/// @brief \b Struct \b Description:
//-----------------------------------------------------------------------------
typedef struct _MMPF_JPEGD_DONE_ATTR
{
    MMP_UBYTE               ubCompType;             ///< Decode Component Type
    MMP_UBYTE               ubDecSrc;               ///< Decode Source Type
    MMP_UBYTE               ubDecImgType;           ///< Decode Image Type
    MMP_ULONG               ulOutputBufAddr;        ///< Decode Output Buffer Address (MWC)
    MMP_ULONG               ulOutputBufSize;        ///< Decode Output Buffer Size
} MMPF_JPEGD_DONE_ATTR;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: MMPF_JPEGD_INPUT_QUEUE
/// @brief \b Struct \b Description:
//-----------------------------------------------------------------------------
typedef struct _MMPF_JPEGD_INPUT_QUEUE
{
    MMPF_JPEGD_INPUT_ATTR   attr[JPEG_DEC_MAX_QUEUE_SIZE];
    JPG_QUEUE_PTR           stQptr;
} MMPF_JPEGD_INPUT_QUEUE;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: MMPF_JPEGD_DONE_QUEUE
/// @brief \b Struct \b Description:
//-----------------------------------------------------------------------------
typedef struct _MMPF_JPEGD_DONE_QUEUE
{
    MMPF_JPEGD_DONE_ATTR    attr[JPEG_DEC_MAX_QUEUE_SIZE];
    JPG_QUEUE_PTR           stQptr;
} MMPF_JPEGD_DONE_QUEUE;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/* Decode Function */
MMP_ERR MMPF_JPEGD_RegisterDecIntrCallBack(MMPF_JPEGD_DEC_EVENT event, void* pCallBack, void *pArgument);
MMP_ERR MMPF_JPEGD_EnableDecInterrupt(MMPF_JPEGD_DEC_EVENT event, MMP_BOOL bEnable);

MMP_ERR MMPF_JPEGD_GetJpegInfo(MMP_BOOL bMemMode, MMP_UBYTE ubDecType, MMP_DSC_JPEG_INFO *pJpegInfo);
MMP_ERR MMPF_JPEGD_GetJpegResolFmtInfo(MMP_BOOL bMemMode, MMP_UBYTE ubDecType, MMP_DSC_JPEG_INFO *pJpegInfo);
MMP_ERR MMPF_JPEGD_DecodeJpegInFile(MMP_UBYTE ubDecType);
MMP_ERR MMPF_JPEGD_DecodeJpegInMem(MMP_UBYTE ubDecType, MMP_ULONG ulSrcAddr, MMP_ULONG ulSrcSize);

MMP_ERR MMPF_JPEGD_ResetPreSeekPos(void);
MMP_ERR MMPF_JPEGD_SetJpgDecOffset(MMP_ULONG ulStartOffset,  MMP_ULONG ulEndOffset);
MMP_ERR MMPF_JPEGD_SetDecodeSrcType(MMP_UBYTE ubSrc);
MMP_ERR MMPF_JPEGD_OpenFile(void);
MMP_ERR MMPF_JPEGD_CloseFile(void);

MMP_ERR MMPF_JPEGD_SetDecodeInputBuf(MMP_ULONG ulBSBufAddr, MMP_ULONG ulBufSize);
MMP_ERR MMPF_JPEGD_SetDecodeInternalBuf(MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize);
MMP_ERR MMPF_JPEGD_SetDecodeOutBuf(MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize);
MMP_ERR MMPF_JPEGD_SetMemModeSrcAttr(MMP_ULONG ulSrcAddr, MMP_ULONG ulSrcLength);

#endif // _MMPF_JPEG_DEC_H_
