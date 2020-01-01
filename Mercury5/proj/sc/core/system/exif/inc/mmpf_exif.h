/// @ait_only
//==============================================================================
//
//  File        : mmpf_exif.h
//  Description : INCLUDE File for the EXIF Driver.
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_EXIF_H_
#define _MMPF_EXIF_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_dsc_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

// Exif marker
#define EXIF_ID                         0x45786966

// Tiff format
#define TIF_II_FORMAT                   0x4949
#define TIF_MM_FORMAT                   0x4d4d

// JPEG marker size
#define JPEG_MARKER_NAME_SZ             2
#define JPEG_MARKER_LENG_SZ             2

#define EXIF_SOI_MARKER_SZ              2
#define EXIF_APP_MARKER_SZ              2
#define EXIF_APP_LEN_SZ                 2
#define EXIF_EOI_MARKER_SZ              2

// Exif header size
#define EXIF_HEADER_SZ                  4
#define EXIF_PAD_SZ                     2

// Tiff header size
#define TIF_FORMAT_SZ                   2
#define TIF_FIXED_SZ                    2
#define TIF_IFD_OFFSET_SZ               4
#define TIF_HEADER_TOTAL_SZ             8

// IFD structure size
#define EXIF_IFD_TAG_NUM_SZ             2
#define EXIF_IFD_NEXT_OFST_SZ           4

// TAG structure size
#define EXIF_TAG_ID_SZ                  2
#define EXIF_TAG_TYPE_SZ                2
#define EXIF_TAG_COMPNENT_NUM_SZ        4
#define EXIF_TAG_DATA_SZ                4
#define EXIF_TAG_VAL_OFFSET             8   //EXIF_TAG_ID_SZ + EXIF_TAG_TYPE_SZ + EXIF_TAG_COMPNENT_NUM_SZ
#define EXIF_TAG_TOTAL_SZ               12  //EXIF_TAG_ID_SZ + EXIF_TAG_TYPE_SZ + EXIF_TAG_COMPNENT_NUM_SZ + EXIF_TAG_DATA_SZ

// JPEG Exif header size
#define JPEG_EXIF_HEADER_SZ             (EXIF_SOI_MARKER_SZ + EXIF_APP_MARKER_SZ + EXIF_APP_LEN_SZ + \
                                         EXIF_HEADER_SZ + EXIF_PAD_SZ + TIF_HEADER_TOTAL_SZ)

// Others
#define EXIF_NULL_NEXT_OFST             0x00000000

#if (DSC_SUPPORT_BASELINE_MP_FILE)
// MPF marker
#define MPF_ID                          0x4D504600

// MPF header size
#define MPF_HEADER_SZ                   4

// JPEG MPF header size
#define JPEG_MPF_HEADER_SZ              (EXIF_APP_MARKER_SZ + EXIF_APP_LEN_SZ + MPF_HEADER_SZ + TIF_HEADER_TOTAL_SZ)

// MPF entry structure size
#define MPF_MP_ENTRY_IMG_ATTR_SZ        4
#define MPF_MP_ENTRY_IMG_SIZE_SZ        4
#define MPF_MP_ENTRY_IMG_OFST_SZ        4
#define MPF_MP_ENTRY_IMG_ENTRYNUM_SZ    2
#define MPF_MP_ENTRY_TOTAL_SZ           16

// MPF unique ID entry size
#define MPF_IND_IMG_UNIQUE_ID_SZ        33

// MPF attribute flag
#define MPF_ATTR_FLAG_DEP_PARENT_IMG        0x80000000
#define MPF_ATTR_FLAG_DEP_CHILD_IMG         0x40000000
#define MPF_ATTR_FLAG_REPRESENT_IMG         0x20000000
#define MPF_ATTR_FLAG_DATA_FMT_JPEG         0x00000000
#define MPF_ATTR_FLAG_TYPE_BASELINE_PRI_IMG 0x00030000
#define MPF_ATTR_FLAG_TYPE_LARGE_THUMB_VGA  0x00010001
#define MPF_ATTR_FLAG_TYPE_LARGE_THUMB_FHD  0x00010002
#define MPF_ATTR_FLAG_TYPE_PANORAMA_IMG     0x00020001
#define MPF_ATTR_FLAG_TYPE_DISPARITY_IMG    0x00020002
#define MPF_ATTR_FLAG_TYPE_MULTI_ANGLE_IMG  0x00020003
#define MPF_ATTR_FLAG_TYPE_UNDEF            0x00000000
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: JPEG_EXIF_ORIENTATION
/// @brief \b Enum \b Description: The orientation of JPEG EXIF
//-----------------------------------------------------------------------------
typedef enum _JPEG_EXIF_ORIENTATION
{
    JPEG_EXIF_ORIENT_NOT_FOUND              = 0,
    JPEG_EXIF_ORIENT_ROTATE_0               = 1,
    JPEG_EXIF_ORIENT_MIRROR_LR              = 2,
    JPEG_EXIF_ORIENT_ROTATE_180             = 3,
    JPEG_EXIF_ORIENT_MIRROR_TB              = 4,
    JPEG_EXIF_ORIENT_ROTATE_90_MIRROR_LR    = 5,
    JPEG_EXIF_ORIENT_ROTATE_90              = 6,
    JPEG_EXIF_ORIENT_ROTATE_90_MIRROR_TB    = 7,
    JPEG_EXIF_ORIENT_ROTATE_270             = 8,
    JPEG_EXIF_ORIENT_RESERVED               = 9
} JPEG_EXIF_ORIENTATION;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _JPEG_RATIONAL {
    MMP_USHORT              usNumerator;
    MMP_USHORT              usDenominator;
} JPEG_RATIONAL;

typedef struct _MMPF_EXIF_DATETIME {
    MMP_ULONG               ulYear;         ///< The year info of JPEG EXIF DataTime
    MMP_ULONG               ulMonth;        ///< The month info of JPEG EXIF DataTime
    MMP_ULONG               ulDay;          ///< The day info of JPEG EXIF DataTime
    MMP_ULONG               ulHour;         ///< The hour info of JPEG EXIF DataTime
    MMP_ULONG               ulMinute;       ///< The minute info of JPEG EXIF DataTime
    MMP_ULONG               ulSecond;       ///< The second info of JPEG EXIF DataTime
} MMPF_EXIF_DATETIME;

typedef struct _MMPF_EXIF_INFO {
    MMP_UBYTE               ubMaker[32];
    MMP_UBYTE               ubModel[32];
    JPEG_EXIF_ORIENTATION   eOrientation;
    MMPF_EXIF_DATETIME      tDateTime;
    MMP_ULONG               ulIsoSpeedRating;
    JPEG_RATIONAL           tExposureTime;
    JPEG_RATIONAL           tExposureBias;
    MMP_USHORT              usExposureProg;
    JPEG_RATIONAL           tFNumber;
    JPEG_RATIONAL           tShutterSpeed;
    JPEG_RATIONAL           tAperture;
    JPEG_RATIONAL           tFocalLength;
    MMP_USHORT              usFlash;
    MMP_ULONG               ulExifImgWidth;
    MMP_ULONG               ulExifImgHeight;
} MMPF_EXIF_INFO;

typedef struct _MMPF_EXIF_TIF_HEADER {
    MMP_USHORT              usByteOrder;
    MMP_USHORT              usFixed002a;
    MMP_ULONG               ulIfd0Offset;
} MMPF_EXIF_TIF_HEADER;

typedef struct _MMPF_EXIF_HEADER {
    MMP_USHORT              usSOI;
    MMP_USHORT              usApp1Marker;
    MMP_USHORT              usApp1Len;
    MMP_ULONG               ulExifID;
    MMP_USHORT              usPad;
} MMPF_EXIF_HEADER;

typedef struct _MMPF_EXIF_TagNode {
    MMP_USHORT              usTag;              // Tag name / ID
    MMP_USHORT              usType;             // Data type
    MMP_ULONG               ulCount;            // Data count
    MMP_ULONG               ulValue;            // Data value or offset value
    MMP_UBYTE               *pData;             // Data buffer address(while data size > 4)
    MMP_ULONG               ulDataSize;         // Real Data Size
    void                    *pNextTag;          // Pointer to next tag
} MMPF_EXIF_TagNode;

typedef struct _MMPF_EXIF_IfdNode {
    MMP_USHORT              usIfdID;
    MMP_USHORT              usByteOrder;        // The byte order of this IFD
    MMP_USHORT              usTagNum;           // The total tag number within this IFD
    MMPF_EXIF_TagNode       *pTag;              // First tag node
    /* The GPS/EXIF IFD is the sub-IFD of IFD0 */
    MMP_USHORT              usGpsIfdTagNum;     // GPS IFD total tag number
    MMP_ULONG               ulGpsIfdOffset;     // GPS IFD address offset
    MMPF_EXIF_TagNode       *pGpsIfdTag;        // GPS IFD first tag node
    MMP_USHORT              usExifIfdTagNum;    // EXIF IFD total tag number
    MMP_ULONG               ulExifIfdOffset;    // EXIF IFD address offset
    MMPF_EXIF_TagNode       *pExifIfdTag;       // EXIF IFD first tag node
    /* The InterOperability IFD is the sub-IFD of EXIF IFD */
    MMP_USHORT              usInteropIfdTagNum; // InterOperability IFD total tag number
    MMP_ULONG               ulInteropIfdOffset; // InterOperability IFD address offset
    MMPF_EXIF_TagNode       *pInteropIfdTag;    // InterOperability IFD first tag node
    MMP_ULONG               ulNextIfdOffset;    // Next IFD node offset
    void*                   pNextIfd;           // Next IFD node
} MMPF_EXIF_IfdNode;

typedef struct _MMPF_EXIF_DATA {
    MMPF_EXIF_TIF_HEADER    TifHeader;
    MMP_ULONG               ulTifHeaderOffset;
    MMP_LONG                lIfdNodeNum;
    MMP_ULONG               ulThumbnailOffset;
    MMP_ULONG               ulThumbnailSize;
} MMPF_EXIF_DATA;

typedef struct _MMPF_EXIF_CONTEXT {
    MMP_USHORT              usPrimaryW;         // Jpeg W
    MMP_USHORT              usPrimaryH;         // Jpeg H
    MMP_USHORT              usThumbnailW;       // Thumbnail W
    MMP_USHORT              usThumbnailH;       // Thumbnail H
    MMP_BOOL                bEncExif;
    MMP_BOOL                bEncThumbnail;
} MMPF_EXIF_CONTEXT;

#if 1//(DSC_SUPPORT_BASELINE_MP_FILE)
typedef struct _MMPF_MPF_HEADER {
    MMP_USHORT              usApp2Marker;
    MMP_USHORT              usApp2Len;
    MMP_ULONG               ulMPFID;
} MMPF_MPF_HEADER;

typedef struct _MMPF_MPF_MPEntryNode {
    MMP_ULONG               ulIndImgAttr;       // Individual Image Attribute.
    MMP_ULONG               ulIndImgSize;       // Individual Image Size.
    MMP_ULONG               ulIndImgOffset;     // Individual Image Data Offset.
    MMP_USHORT              usDepImg1EntryNum;  // Dependent Image 1 Entry Num.
    MMP_USHORT              usDepImg2EntryNum;  // Dependent Image 2 Entry Num.
    void                    *pNextEntry;        // Pointer to next tag
} MMPF_MPF_MPEntryNode;

typedef struct _MMPF_MPF_IfdNode {
    MMP_USHORT              usIfdID;
    MMP_USHORT              usByteOrder;        // The byte order of this IFD
    MMP_USHORT              usImageNum;         // The total image number within this MPF.
    MMP_USHORT              usTagNum;           // The total tag number within this IFD
    MMPF_EXIF_TagNode       *pTag;              // First tag node
    MMP_ULONG               ulNextIfdOffset;    // Next IFD node offset
    void*                   pNextIfd;           // Next IFD node
    MMP_USHORT              usEntryNum;         // The total enrty number within this IFD
    MMPF_MPF_MPEntryNode    *pEntry;            // First entry node.
} MMPF_MPF_IfdNode;

typedef struct _MMPF_MPF_DATA {
    MMPF_EXIF_TIF_HEADER    TifHeader;
    MMP_ULONG               ulTifHeaderOffset;
    MMP_USHORT              usImageNum;
    MMP_ULONG               ulPrimaryImageOffset;
    MMP_ULONG               ulPrimaryImageSize;
    MMP_ULONG               ulLargeThumb1Offset;
    MMP_ULONG               ulLargeThumb1Size;
    MMP_ULONG               ulLargeThumb2Offset;
    MMP_ULONG               ulLargeThumb2Size;
    MMP_ULONG               ulThumbnailOffset;
    MMP_ULONG               ulThumbnailSize;
} MMPF_MPF_DATA;
#endif

typedef MMP_ERR     JpegFileReadCBFunc(MMP_UBYTE *ubTarget, MMP_ULONG ulSeekpos, MMP_ULONG ulReadsize);
typedef MMP_UBYTE*  JpegMemAllocCBFunc(MMP_USHORT usExifNodeId, MMP_ULONG ulSize, MMP_BOOL ForUpdate);
typedef MMP_ERR     JpegMemFreeCBFunc(void *pBuf);

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

#if (DSC_SUPPORT_BASELINE_MP_FILE)
extern MMP_BOOL m_bMpfEnable;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

/* Exif Common Function */
MMP_ERR MMPF_EXIF_SetMemCBFunc(JpegMemAllocCBFunc *FpMalloc, JpegMemFreeCBFunc *FpFree);
MMP_ERR MMPF_EXIF_SetTifHeader(MMP_USHORT usByteOrder);
MMP_ERR MMPF_EXIF_FillDataToBuf(MMP_USHORT usByteOrder, MMP_UBYTE *pBuf, MMP_ULONG ulData, MMP_ULONG ulSize);

/* Exif Encode Function */
MMP_ERR MMPF_EXIF_InitExifNode(MMP_USHORT usExifNodeId);
MMP_ERR MMPF_EXIF_UpdateExifNodeOffset(MMPF_EXIF_IfdNode *pExifBuf);  
MMP_ERR MMPF_EXIF_UpdateExifNode( MMP_USHORT    usExifNodeId,
                                  MMPF_EXIF_IfdNode *pExifNode,
                                  MMP_USHORT    usIfd,          MMP_USHORT  usTagID,
                                  MMP_USHORT    usTagType,      MMP_ULONG   ulTagCount,
                                  MMP_UBYTE     *pTagData,      MMP_ULONG   ulDataSize,
                                  MMP_ULONG     *ulExifSize,    MMP_BOOL    ForUpdate);
MMP_ERR MMPF_EXIF_WriteExifHeader(MMP_USHORT usExifNodeId, MMP_UBYTE *ExifStartAddr, MMP_ULONG ulThumbnailSize);
MMP_ERR MMPF_EXIF_WriteExifData(MMP_UBYTE *ExifStartAddr, MMPF_EXIF_IfdNode *pIfdBuf, MMP_UBYTE *ubWriteBuf);
MMP_ERR MMPF_EXIF_FinishExif(MMP_USHORT usExifNodeId, MMP_ULONG ExifStartAddr, MMP_ULONG *ExifSize, MMP_ULONG ulThumbnailSize);
MMP_ERR MMPF_EXIF_Encode(MMP_USHORT usExifNodeId, MMPF_EXIF_CONTEXT *pExifCtx);
MMP_ERR MMPF_EXIF_KillExifForMS(MMP_USHORT usExifNodeId);
MMP_ERR MMPF_EXIF_KillIFD(MMP_USHORT usExifNodeId, MMPF_EXIF_IfdNode *pExifBuf, MMP_USHORT IfdID);

#if (DSC_SUPPORT_BASELINE_MP_FILE)
/* MPF Encode Function */
MMP_ERR MMPF_MPF_EnableMpf(MMP_BOOL bEnable);
MMP_ERR MMPF_MPF_InitMpfNode(void);
MMP_ERR MMPF_MPF_UpdateMpfNode(MMPF_MPF_IfdNode *pMpfBuf,
                               MMP_USHORT   usIfd,      MMP_USHORT  usTagID,
                               MMP_USHORT   usTagType,  MMP_ULONG   ulTagCount,
                               MMP_UBYTE    *pTagData,  MMP_ULONG   ulDataSize,
                               MMP_ULONG    *ulMpfSize, MMP_BOOL    ForUpdate);
MMP_ERR MMPF_MPF_UpdateMpfEntry(MMPF_MPF_IfdNode *pMpfBuf, 
                                MMP_USHORT      usIfd,          MMP_USHORT  usEntryID,
                                MMP_ULONG       ulImgAttr,      MMP_ULONG   ulImgSize,
                                MMP_ULONG       ulImgOffset,
                                MMP_USHORT      usImg1EntryNum, MMP_USHORT  usImg2EntryNum,
                                MMP_ULONG       *pulMpfSize,    MMP_BOOL    ForUpdate);
MMP_ERR MMPF_MPF_WriteMpfHeader(MMP_UBYTE *MpfStartAddr);
MMP_ERR MMPF_MPF_WriteMpfData(MMP_UBYTE *MpfStartAddr, MMPF_MPF_IfdNode *pIfdBuf, MMP_UBYTE *ubWriteBuf);
MMP_ERR MMPF_MPF_FinishMpf(MMP_ULONG MpfStartAddr, MMP_ULONG *pMpfSize);
MMP_ERR MMPF_MPF_EncodeMpf(void);                                
#endif   

/* Exif Decode Function */
MMP_ERR MMPF_EXIF_ParseExifInfo(JpegFileReadCBFunc  *pCallBackFunc, 
                                MMP_ULONG           ulJpegSize,
                                MMP_USHORT          usExifNodeId,
                                MMPF_EXIF_IfdNode   **ppIfd,
                                MMP_ULONG           *pulExifSize,
                                MMP_ULONG           *pulExifOffset,
                                MMPF_MPF_IfdNode    **ppMpfIfd,
                                MMP_ULONG           *pulMpfSize,
                                MMP_ULONG           *pulMpfOffset);
MMP_ERR MMPF_EXIF_GetTagDataOffset(MMPF_EXIF_IfdNode *pIfd0, MMP_USHORT usIfd, MMP_USHORT usTag, MMP_ULONG *pulOffset);                         
MMP_ERR MMPF_EXIF_GetTagData(MMP_USHORT usIfd, MMP_USHORT usTag, MMP_ULONG ulDataAddr, MMP_ULONG *ulSize, MMPF_EXIF_IfdNode *pIfd0);
MMP_ERR MMPF_EXIF_GetThumbInfo(MMP_DSC_JPEG_INFO *pJpegInfo, JpegFileReadCBFunc *CallBackFunc);

/* Exif Public Function */
MMP_ERR MMPF_DSC_ResetEXIFWorkingBufPtr(MMP_USHORT usExifNodeId, MMP_BOOL bForUpdate);
MMP_ERR MMPF_DSC_GetEXIFInfo(MMP_USHORT usExifNodeId, MMP_USHORT usIfd, MMP_USHORT usTag, MMP_ULONG ulDataAddr, MMP_ULONG *ulSize);
MMP_ERR MMPF_DSC_OpenEXIFFile(MMP_USHORT usExifNodeId);
MMP_ERR MMPF_DSC_CloseEXIFFile(MMP_USHORT usExifNodeId);
MMP_ERR MMPF_DSC_SetEXIFWorkingBuffer(MMP_USHORT usExifNodeId, MMP_UBYTE *pBuf, MMP_ULONG ulBufSize, MMP_BOOL bForUpdate);
MMP_ERR MMPF_DSC_UpdateExifInfo(MMP_USHORT  usExifNodeId,
                                MMP_USHORT  usIfd,      MMP_USHORT  usTag,
                                MMP_USHORT  usType,     MMP_ULONG   ulCount,
                                MMP_UBYTE   *pData,     MMP_ULONG   ulDataSize,
                                MMP_BOOL    bForUpdate);
MMP_ERR MMPF_DSC_UpdateMpfInfo( MMP_USHORT  usIfd,      MMP_USHORT  usTag,
                                MMP_USHORT  usType,     MMP_ULONG   ulCount,
                                MMP_UBYTE   *pData,     MMP_ULONG   ulDataSize,
                                MMP_BOOL    bForUpdate);
MMP_ERR MMPF_DSC_UpdateMpfEntry(MMP_USHORT      usIfd,          MMP_USHORT  usEntryID,
                                MMP_ULONG       ulImgAttr,      MMP_ULONG   ulImgSize,
                                MMP_ULONG       ulImgOffset,
                                MMP_USHORT      usImg1EntryNum, MMP_USHORT  usImg2EntryNum,
                                MMP_BOOL        bForUpdate);
MMP_ERR MMPF_DSC_SetCardModeExifDec(MMP_BOOL bDecodeThumb, MMP_BOOL bDecodeLargeThumb);
MMP_ERR MMPF_DSC_SetCardModeExifEnc(MMP_USHORT  usExifNodeId,
                                    MMP_BOOL    bEncodeExif,
                                    MMP_BOOL    bEncodeThumbnail,
                                    MMP_USHORT  usPrimaryJpegW,
                                    MMP_USHORT  usPrimaryJpegH,
                                    MMP_USHORT  usThumbnailW,
                                    MMP_USHORT  usThumbnailH);

/// @}

#endif // _MMPF_EXIF_H_

/// @end_ait_only
