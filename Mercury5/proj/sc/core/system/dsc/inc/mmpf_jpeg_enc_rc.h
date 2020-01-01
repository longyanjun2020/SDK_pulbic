#ifndef _MMPF_JPEG_ENC_RC_H_
#define _MMPF_JPEG_ENC_RC_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define JPEG_ENC_QTBL_SIZE          (64)

// TBD
#define JPEG_SCALE_FACTOR_HQ        (1)
#define JPEG_SCALE_FACTOR_LQ        (100)
#define JPEG_SCALE_FACTOR_CUR       (20)
#define JPEG_SCALE_FACTOR_MIN       (1)
#define JPEG_SCALE_FACTOR_MAX       (100)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    MMP_JPGENC_RC_SIZECTL_DISABLE = 0,
    MMP_JPGENC_RC_SIZECTL_NORMAL
} MMP_JPGENC_RC_SIZECTL_MODE;

// Rate Control Index
typedef enum
{
    MMP_JPGENC_RC_ID_PRM_CAPTURE = 0,
    MMP_JPGENC_RC_ID_SCD_CAPTURE,
    MMP_JPGENC_RC_ID_TRD_CAPTURE,
    MMP_JPGENC_RC_ID_PRM_MJPEG_STREAM,
    MMP_JPGENC_RC_ID_SCD_MJPEG_STREAM,
    MMP_JPGENC_RC_ID_TRD_MJPEG_STREAM,
    MMP_JPGENC_RC_ID_VR_THUMB_PRM_RECD,
    MMP_JPGENC_RC_ID_VR_THUMB_SCD_RECD,
    MMP_JPGENC_RC_ID_VR_THUMB_TRD_RECD,
    MMP_JPGENC_RC_ID_NONE,
    MMP_JPGENC_RC_ID_NUM
} MMP_JPGENC_RC_ID;

typedef enum
{
    MMP_JPGENC_RC_QTBL_HIGH = 0,
    MMP_JPGENC_RC_QTBL_NORMAL,
    MMP_JPGENC_RC_QTBL_LOW,
    MMP_JPGENC_RC_QTBL_CUSTOMER,
    MMP_JPGENC_RC_QTBL_NUM
} MMP_JPGENC_RC_QTBL_SEL;

typedef enum
{
    MMP_JPGENC_RC_QUALITY_SEL_HIGH = 0,
    MMP_JPGENC_RC_QUALITY_SEL_NORMAL,
    MMP_JPGENC_RC_QUALITY_SEL_LOW
} MMP_JPGENC_RC_QUALITY_SEL;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMP_JPGENC_RC_QUALITY_CTL
{
    MMP_BOOL    bTargetCtl;
    MMP_BOOL    bLimitCtl;
    MMP_ULONG   ulTargetSize;
    MMP_ULONG   ulLimitSize;
    MMP_USHORT  usMaxTrialCnt;
    MMP_UBYTE   ubQualitySel;
} MMP_JPGENC_RC_QUALITY_CTL;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

/* Rate Control Function */
MMP_ERR MMPF_JPGENC_RC_Init(MMP_USHORT usJpegW, MMP_USHORT usJpegH, MMP_UBYTE ubRcIdx);
MMP_ERR MMPF_JPGENC_RC_SetQualityCtl(MMP_UBYTE   ubRcIdx,
                                     MMP_BOOL    bTargetCtlEnable,
                                     MMP_BOOL    bLimitCtlEnable,
                                     MMP_ULONG   ulTargetSize,
                                     MMP_ULONG   ulLimitSize,
                                     MMP_USHORT  usMaxCount);

MMP_ERR MMPF_JPGENC_RC_SetQTableLow(void);
MMP_ERR MMPF_JPGENC_RC_SetQTableIntoOpr(MMP_UBYTE ubRcIdx);
MMP_ERR MMPF_JPGENC_RC_SetQTableInfo(MMP_UBYTE ubRcIdx, MMP_UBYTE *ubYQtable, MMP_UBYTE *ubUQtable, MMP_UBYTE *ubVQtable, MMP_JPGENC_RC_QTBL_SEL QTSet);
MMP_ERR MMPF_JPGENC_RC_GetQTableInfo(MMP_UBYTE ubRcIdx, MMP_UBYTE **ppubQY, MMP_UBYTE **ppubQU, MMP_UBYTE **ppubQV);
MMP_ERR MMPF_JPGENC_RC_UpdateCurSize(MMP_UBYTE ubRcIdx, MMP_ULONG ulJpegSizeKB);
MMP_ERR MMPF_JPGENC_RC_DoScale(MMP_UBYTE ubInstId, MMP_UBYTE ubRcIdx);
MMP_USHORT MMPF_JPGENC_RC_GetCurQFactor(MMP_UBYTE ubRcIdx);

#endif // _MMPF_JPEG_ENC_RC_H_
