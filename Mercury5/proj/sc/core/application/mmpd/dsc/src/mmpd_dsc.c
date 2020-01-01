/// @ait_only
//==============================================================================
//
//  File        : mmpd_dsc.c
//  Description : Camera Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmpd_dsc.h"
#include "mmph_hif.h"
#include "mmpf_exif.h"
#include "mmpf_jpeg_dec.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MMPD_DSC_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define MMPD_DSC_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

static MMP_ULONG        m_ulJpegFileNameBufAddr = 0;

// For Exif initialization
static MMP_BOOL         m_bExifInited[DSC_MAX_EXIF_NODE_NUM] = {MMP_FALSE, MMP_FALSE};
static MMP_ULONG        m_ulExifEncBufAddr[DSC_MAX_EXIF_NODE_NUM] = {0, 0};
static MMP_ULONG        m_ulExifEncBufSize[DSC_MAX_EXIF_NODE_NUM] = {0, 0};
static MMP_ULONG        m_ulExifDecBufAddr[DSC_MAX_EXIF_NODE_NUM] = {0, 0};
static MMP_ULONG        m_ulExifDecBufSize[DSC_MAX_EXIF_NODE_NUM] = {0, 0};

#if (DSC_SUPPORT_BASELINE_MP_FILE)
// For MPF initialization
static MMP_BOOL         m_bMpfInited = MMP_FALSE;
#endif

//==============================================================================
//
//                              FUNCTIONS PROTOTYPE
//
//==============================================================================

#if 0
void _____Playback_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_GetJpegInfo
//  Description :
//------------------------------------------------------------------------------
/** @brief Get the JPEG information

The function reads an input Jpeg buffer (ulJpegBufAddr) from an input Jpeg information structure and
writes back the required fields in the same structure.

@param[in] pJpegInfo the jpeg information data structure
@param[out] pJpegInfo the jpeg information data structure
@return It reports the status of the operation.
*/
MMP_ERR MMPD_DSC_GetJpegInfo(MMP_DSC_JPEG_INFO *pJpegInfo)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (pJpegInfo->ulJpegBufAddr != 0) {

        MMPF_JPEGD_SetMemModeSrcAttr(pJpegInfo->ulJpegBufAddr, pJpegInfo->ulJpegBufSize);

        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        MMPD_DSC_SetCardModeExifDec(pJpegInfo->bDecodeThumbnail, pJpegInfo->bDecodeLargeThumb);
        #else
        MMPD_DSC_SetCardModeExifDec(pJpegInfo->bDecodeThumbnail, MMP_FALSE);
        #endif
        
        MMPF_JPEGD_SetDecodeSrcType(MMPF_JPEGD_DEC_SRC_MEMORY);
        
        #if (DSC_ENC_THUMBNAIL_OK)
        if (pJpegInfo->bDecodeThumbnail) {
            eRetErr = MMPF_JPEGD_GetJpegResolFmtInfo(MMP_TRUE, MMPF_JPEGD_IMG_TYPE_THUMB, pJpegInfo);
        
            if (eRetErr != MMP_ERR_NONE) {
                pJpegInfo->usThumbWidth   = 0;
                pJpegInfo->usThumbHeight  = 0;
                pJpegInfo->eThumbFormat   = MMP_DSC_JPEG_FMT_NOT_BASELINE;
                return eRetErr;
            }
        }
        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        else if (pJpegInfo->bDecodeLargeThumb) {
            eRetErr = MMPF_JPEGD_GetJpegResolFmtInfo(MMP_TRUE, MMPF_JPD_TYPE_LARGETHUMB, pJpegInfo);
        
            if (eRetErr != MMP_ERR_NONE) {
                pJpegInfo->usLargeThumbWidth   = 0;
                pJpegInfo->usLargeThumbHeight  = 0;
                pJpegInfo->eLargeThumbFormat   = MMP_DSC_JPEG_FMT_NOT_BASELINE;
                return eRetErr;
            }
        }
        #endif
        else
        #endif
        {
            eRetErr = MMPF_JPEGD_GetJpegResolFmtInfo(MMP_TRUE, MMPF_JPEGD_IMG_TYPE_PRIMARY, pJpegInfo);
        
            if (eRetErr != MMP_ERR_NONE) {
                pJpegInfo->usPrimaryWidth   = 0;
                pJpegInfo->usPrimaryHeight  = 0;
                pJpegInfo->ePrimaryFormat   = MMP_DSC_JPEG_FMT_NOT_BASELINE;
                return eRetErr;
            }
        }
        
        pJpegInfo->bValid = MMP_TRUE;
    }
    else if (pJpegInfo->bJpegFileName[0] != NULL) {

        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        MMPD_DSC_SetCardModeExifDec(pJpegInfo->bDecodeThumbnail, pJpegInfo->bDecodeLargeThumb);
        #else
        MMPD_DSC_SetCardModeExifDec(pJpegInfo->bDecodeThumbnail, MMP_FALSE);
        #endif

        MMPF_JPEGD_SetDecodeSrcType(MMPF_JPEGD_DEC_SRC_FILE);
        
        #if (DSC_ENC_THUMBNAIL_OK)
        if (pJpegInfo->bDecodeThumbnail) {
            eRetErr = MMPF_JPEGD_GetJpegResolFmtInfo(MMP_FALSE, MMPF_JPEGD_IMG_TYPE_THUMB, pJpegInfo);

            if (eRetErr != MMP_ERR_NONE) {
                pJpegInfo->usThumbWidth   = 0;
                pJpegInfo->usThumbHeight  = 0;
                pJpegInfo->eThumbFormat   = MMP_DSC_JPEG_FMT_NOT_BASELINE;
                return eRetErr;
            }
        }
        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        else if (pJpegInfo->bDecodeLargeThumb) {
            eRetErr = MMPF_JPEGD_GetJpegResolFmtInfo(MMP_FALSE, MMPF_JPD_TYPE_LARGETHUMB, pJpegInfo);

            if (eRetErr != MMP_ERR_NONE) {
                pJpegInfo->usLargeThumbWidth   = 0;
                pJpegInfo->usLargeThumbHeight  = 0;
                pJpegInfo->eLargeThumbFormat   = MMP_DSC_JPEG_FMT_NOT_BASELINE;
                return eRetErr;
            }
        }
        #endif
        else
        #endif
        {
            eRetErr = MMPF_JPEGD_GetJpegResolFmtInfo(MMP_FALSE, MMPF_JPEGD_IMG_TYPE_PRIMARY, pJpegInfo);

            if (eRetErr != MMP_ERR_NONE) {
                pJpegInfo->usPrimaryWidth   = 0;
                pJpegInfo->usPrimaryHeight  = 0;
                pJpegInfo->ePrimaryFormat   = MMP_DSC_JPEG_FMT_NOT_BASELINE;
                return eRetErr;
            }
        }

        pJpegInfo->bValid = MMP_TRUE;
    }
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_OpenJpegFile
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_OpenJpegFile(MMP_DSC_JPEG_INFO *pJpegInfo)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    
    if (pJpegInfo->bJpegFileName[0] != NULL) {
    
        eRetErr = MMPD_DSC_SetFileName(pJpegInfo->bJpegFileName, pJpegInfo->usJpegFileNameLength);
        if (eRetErr) {
            MMPD_DSC_DBG_ERR(1, "OpenJpegFile => SetFileName ERR [%x]\r\n", eRetErr);
        }
        
        eRetErr = MMPF_JPEGD_OpenFile();
        if (eRetErr) {
            MMPD_DSC_DBG_ERR(1, "OpenJpegFile => JPEGD_OpenFile ERR [%x]\r\n", eRetErr);
        }

        pJpegInfo->ulFileSize = MMPF_JPEGD_GetFileSize();
    }
    
    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_CloseJpegFile
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_CloseJpegFile(MMP_DSC_JPEG_INFO *pJpegInfo)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    
    if (pJpegInfo->bJpegFileName[0] != NULL) {
        eRetErr = MMPF_JPEGD_CloseFile();
    }
    
    return eRetErr;
}

#if 0
void _____MPF_Functions_____(){}
#endif

#if (DSC_SUPPORT_BASELINE_MP_FILE)
//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_UpdateMpfNode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_UpdateMpfNode(MMP_USHORT   usIfd,  MMP_USHORT  usTag,
                               MMP_USHORT   usType, MMP_ULONG   ulCount,
                               MMP_UBYTE    *pData, MMP_ULONG   ulDataSize,
                               MMP_BOOL     bForUpdate)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if ((!bForUpdate) && (!m_bMpfInited)) {
        eRetErr = MMPF_MPF_InitMpfNode();
        m_bMpfInited = MMP_TRUE;
    }

    eRetErr = MMPF_DSC_UpdateMpfInfo(   usIfd,
                                        usTag,
                                        usType,
                                        ulCount,
                                        pData,
                                        ulDataSize,
                                        bForUpdate);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_UpdateMpfEntry
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_UpdateMpfEntry(MMP_USHORT  usIfd,
                                MMP_USHORT  usEntryID,
                                MMP_ULONG   ulImgAttr,
                                MMP_ULONG   ulImgSize,
                                MMP_ULONG   ulImgOffset,
                                MMP_USHORT  usImg1EntryNum,
                                MMP_USHORT  usImg2EntryNum,
                                MMP_BOOL    bForUpdate)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if ((!bForUpdate) && (!m_bMpfInited)) {
        eRetErr = MMPF_MPF_InitMpfNode();
        m_bMpfInited = MMP_TRUE;
    }

    eRetErr = MMPF_DSC_UpdateMpfEntry(  usIfd,
                                        usEntryID,
                                        ulImgAttr,
                                        ulImgSize,
                                        ulImgOffset,
                                        usImg1EntryNum,
                                        usImg2EntryNum,
                                        bForUpdate);

    return eRetErr;
}
#endif

#if 0
void _____Exif_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_GetExifWorkingBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_GetExifWorkingBuffer(MMP_USHORT usExifNodeId, MMP_ULONG *pulBufAddr, MMP_ULONG *pulBufSize, MMP_BOOL bForUpdate)
{
    if (bForUpdate) {
        *pulBufAddr = m_ulExifDecBufAddr[usExifNodeId];
        *pulBufSize = m_ulExifDecBufSize[usExifNodeId];
    }
    else {
        *pulBufAddr = m_ulExifEncBufAddr[usExifNodeId];
        *pulBufSize = m_ulExifEncBufSize[usExifNodeId];
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_SetExifWorkingBuffer
//  Description : Allocation the buffer for EXIF working.
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_SetExifWorkingBuffer(MMP_USHORT usExifNodeId, MMP_UBYTE *pBuf, MMP_ULONG ulBufSize, MMP_BOOL bForUpdate)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (bForUpdate) {
        m_ulExifDecBufAddr[usExifNodeId] = (MMP_ULONG)pBuf;
        m_ulExifDecBufSize[usExifNodeId] = ulBufSize;
    }
    else {
        m_ulExifEncBufAddr[usExifNodeId] = (MMP_ULONG)pBuf;
        m_ulExifEncBufSize[usExifNodeId] = ulBufSize;
    }

    if ((MMP_ULONG)pBuf == 0 || ulBufSize == 0) {
        return MMP_ERR_NONE;
    }

    if (usExifNodeId >= DSC_MAX_EXIF_NODE_NUM) {
        return MMP_ERR_NONE;
    }

    // Restart the initialization of EXIF.
    m_bExifInited[usExifNodeId] = MMP_FALSE;
    
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    // Restart the initialization of MPF.
    if (usExifNodeId == EXIF_NODE_ID_PRIMARY) {
        m_bMpfInited = MMP_FALSE;
    }
    #endif
    
    eRetErr = MMPF_DSC_SetEXIFWorkingBuffer(usExifNodeId, pBuf, ulBufSize, bForUpdate);

    return eRetErr;
}
 
//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_SetCardModeExifEnc
//  Description :
//------------------------------------------------------------------------------
/** @brief Configure the Exif setting for card mode encode
@param[in] bEncodeExif support Exif encode or not
@param[in] bEncodeThumbnail support Exif-Thumbnail encode or not
@param[in] usThumbnailW the width of thumbnail
@param[in] usThumbnailH the height of thumbnail
@return It reports the status of the operation.
*/
MMP_ERR MMPD_DSC_SetCardModeExifEnc(MMP_USHORT  usExifNodeId,
                                    MMP_BOOL    bEncodeExif,
                                    MMP_BOOL    bEncodeThumbnail,
                                    MMP_USHORT  usPrimaryJpegW,
                                    MMP_USHORT  usPrimaryJpegH,
                                    MMP_USHORT  usThumbnailW,
                                    MMP_USHORT  usThumbnailH)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    
    m_bExifInited[usExifNodeId] = MMP_TRUE;
    
    if (!bEncodeThumbnail) {
        usThumbnailW = 0;
        usThumbnailH = 0;
    }

    eRetErr = MMPF_DSC_SetCardModeExifEnc(  usExifNodeId,
                                            bEncodeExif,
                                            bEncodeThumbnail,
                                            usPrimaryJpegW,
                                            usPrimaryJpegH,
                                            usThumbnailW,
                                            usThumbnailH);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_SetCardModeExifDec
//  Description :
//------------------------------------------------------------------------------
/** @brief Configure the Exif setting for card mode decode
@param[in] bDecodeThumbnail support Exif decode or not
@return It reports the status of the operation.
*/
MMP_ERR MMPD_DSC_SetCardModeExifDec(MMP_BOOL bDecodeThumb, MMP_BOOL bDecodeLargeThumb)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    if (bDecodeLargeThumb) {
        MMPD_DSC_EnableMultiPicFormat(MMP_TRUE);
    }
    #else
    bDecodeLargeThumb = MMP_FALSE;
    #endif

    eRetErr = MMPF_DSC_SetCardModeExifDec(bDecodeThumb, bDecodeLargeThumb);

    return eRetErr;
} 

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_OpenEXIFFile
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_OpenEXIFFile(MMP_UBYTE *pubFileName, MMP_ULONG ulFileNameLen, MMP_USHORT usExifNodeId)
{
     MMP_ERR eRetErr = MMP_ERR_NONE;
     
     if (pubFileName == NULL) {
        return MMP_DSC_ERR_PARAMETER;
     }

     MMPD_DSC_SetFileName((MMP_BYTE *)pubFileName, (MMP_USHORT)ulFileNameLen);

     eRetErr = MMPF_DSC_OpenEXIFFile(usExifNodeId);

     return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_UpdateExifNode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_UpdateExifNode(MMP_USHORT  usExifNodeId,
                                MMP_USHORT  usIfd,  MMP_USHORT  usTag,
                                MMP_USHORT  usType, MMP_ULONG   ulCount,
                                MMP_UBYTE   *pData, MMP_ULONG   ulDataSize,
                                MMP_BOOL    bForUpdate)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;
    
    if ((!bForUpdate) && (!m_bExifInited[usExifNodeId])) {
        eRetErr = MMPF_EXIF_InitExifNode(usExifNodeId);
        m_bExifInited[usExifNodeId] = MMP_TRUE;
    }

    eRetErr = MMPF_DSC_UpdateExifInfo(  usExifNodeId,
                                        usIfd,
                                        usTag,
                                        usType,
                                        ulCount,
                                        pData,
                                        ulDataSize,
                                        bForUpdate);

    return eRetErr;
}

#if 0
void _____Storage_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_SetFileName
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_SetFileName(MMP_BYTE ubFilename[], MMP_USHORT usLength)
{
    MMP_UBYTE null = 0;

    if (!m_ulJpegFileNameBufAddr) {
        MMPD_DSC_DBG_ERR(1, "DSC_SetFileName Addr need to be initialized\r\n");
        return MMP_DSC_ERR_PARAMETER;
    }

    if ((ubFilename == NULL) || (usLength == 0)) {
        MMPD_DSC_DBG_ERR(1, "DSC_SetFileName need to be given parameters\r\n");
        return MMP_DSC_ERR_FILE_ERROR;
    }

    MMPH_HIF_MemCopyHostToDev(m_ulJpegFileNameBufAddr, (MMP_UBYTE *)ubFilename, usLength);
    MMPH_HIF_MemCopyHostToDev(m_ulJpegFileNameBufAddr + usLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulJpegFileNameBufAddr + usLength  + 1, (MMP_UBYTE*)&null, 1);

    return MMPF_DSC_SetFileName(m_ulJpegFileNameBufAddr);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_SetThumbFileName
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_SetThumbFileName(MMP_BYTE ubFilename[], MMP_USHORT usLength)
{
    MMP_UBYTE null = 0;

    if (!m_ulJpegFileNameBufAddr) {
        RTNA_DBG_Str0("DSC_SetFileNameAddr need to be initialized\r\n");
        return MMP_DSC_ERR_PARAMETER;
    }

    if ((ubFilename == NULL) || (usLength == 0)) {
        RTNA_DBG_Str0("DSC_SetThumbFileName need to be given parameters\r\n");
        return MMP_DSC_ERR_FILE_ERROR;
    }

    MMPH_HIF_MemCopyHostToDev(m_ulJpegFileNameBufAddr, (MMP_UBYTE *)ubFilename, usLength);
    MMPH_HIF_MemCopyHostToDev(m_ulJpegFileNameBufAddr + usLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulJpegFileNameBufAddr + usLength  + 1, (MMP_UBYTE*)&null, 1);
    
    return MMPF_DSC_SetThumbFileName(m_ulJpegFileNameBufAddr);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_SetFileNameAddr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_SetFileNameAddr(MMP_ULONG ulFilenameAddr)
{
    m_ulJpegFileNameBufAddr = ulFilenameAddr;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_DSC_GetFileNameAddr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_DSC_GetFileNameAddr(MMP_ULONG *pulFilenameAddr)
{
    *pulFilenameAddr = m_ulJpegFileNameBufAddr;

    return MMP_ERR_NONE;
}

#if 0
void _____Streaming_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_Streaming_Init
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Streaming_Init(MMP_USHORT usEncID)
{
    MMP_USHORT usType = MMP_MJPEG_CMD_NEW_ONE;

    MMPH_HIF_WaitSem(GRP_IDX_DSC, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 0, usEncID);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 2, usType);
    
    MMPH_HIF_SendCmd(GRP_IDX_DSC, HIF_DSC_MJPEG_OPERATION | STREAM_JPEG_INFO);
    MMPH_HIF_ReleaseSem(GRP_IDX_DSC);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Streaming_SetModeID
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Streaming_SetModeID(MMP_USHORT usEncID, MMP_USHORT usModeID)
{
    MMP_USHORT usType = MMP_MJPEG_CMD_SET_MODE;

    MMPH_HIF_WaitSem(GRP_IDX_DSC, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 0, usEncID);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 2, usType);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 4, usModeID);

    MMPH_HIF_SendCmd(GRP_IDX_DSC, HIF_DSC_MJPEG_OPERATION | STREAM_JPEG_INFO);
    MMPH_HIF_ReleaseSem(GRP_IDX_DSC);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Streaming_SetCompBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Streaming_SetCompBuf(MMP_USHORT usEncID, MMP_USHORT usModeID, MMP_ULONG ulAddr, MMP_ULONG ulSize, MMP_M_STREAMCB_CODEC codec, MMP_ULONG ulThresholdCB)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_USHORT  usType = MMP_MJPEG_CMD_SET_COMPBUF;

    // Set EncID and ModeID before set compress buffer.
    eRetErr = MMPD_Streaming_SetModeID(usEncID, usModeID);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, 0, "", 0); return eRetErr;}
    
    MMPH_HIF_WaitSem(GRP_IDX_DSC, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 0, usEncID);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 2, usType);
    MMPH_HIF_SetParameterL(GRP_IDX_DSC, 4, ulAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_DSC, 8, ulSize);
    MMPH_HIF_SetParameterL(GRP_IDX_DSC, 12, codec);
    MMPH_HIF_SetParameterL(GRP_IDX_DSC, 16, ulThresholdCB);

    eRetErr = MMPH_HIF_SendCmd(GRP_IDX_DSC, HIF_DSC_MJPEG_OPERATION | STREAM_JPEG_INFO);
    MMPH_HIF_ReleaseSem(GRP_IDX_DSC);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Streaming_Enable
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Streaming_Enable(MMP_USHORT usEncID, MMP_BOOL bEnable, MMP_BOOL bWaitForSync)
{
    MMP_USHORT usType = MMP_MJPEG_CMD_STREAM_EN;

    MMPH_HIF_WaitSem(GRP_IDX_DSC, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 0, usEncID);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 2, usType);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 4, bEnable);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 6, bWaitForSync);
    
    MMPH_HIF_SendCmd(GRP_IDX_DSC, HIF_DSC_MJPEG_OPERATION | STREAM_JPEG_INFO);
    MMPH_HIF_ReleaseSem(GRP_IDX_DSC);

    return MMP_ERR_NONE;
}

#if 0
void _____MJPEG_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_MJPEG_CheckEncodeDone
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_MJPEG_CheckEncodeDone(MMP_USHORT usEncID)
{
    MMP_USHORT usType = MMP_MJPEG_CMD_CHECK_ENC_DONE;

    MMPH_HIF_WaitSem(GRP_IDX_DSC, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 0, usEncID);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 2, usType);

    MMPH_HIF_SendCmd(GRP_IDX_DSC, HIF_DSC_MJPEG_OPERATION | STREAM_JPEG_INFO);
    MMPH_HIF_ReleaseSem(GRP_IDX_DSC);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_MJPEG_SetFPS
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_MJPEG_SetFPS(MMP_USHORT usEncID, MMP_ULONG ulIncrReso, MMP_ULONG ulIncrement)
{
    MMP_USHORT usType = MMP_MJPEG_CMD_SET_FPS;

    MMPH_HIF_WaitSem(GRP_IDX_DSC, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 0, usEncID);
    MMPH_HIF_SetParameterW(GRP_IDX_DSC, 2, usType);
    MMPH_HIF_SetParameterL(GRP_IDX_DSC, 4, ulIncrReso);
    MMPH_HIF_SetParameterL(GRP_IDX_DSC, 8, ulIncrement);
    
    MMPH_HIF_SendCmd(GRP_IDX_DSC, HIF_DSC_MJPEG_OPERATION | STREAM_JPEG_INFO);
    MMPH_HIF_ReleaseSem(GRP_IDX_DSC);

    return MMP_ERR_NONE;
}

/// @}
/// @end_ait_only
