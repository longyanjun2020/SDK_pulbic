/// @ait_only
/**
 @file mmpd_3gpmgr.c
 @brief Retina 3GP Merger Control Driver Function
 @author Will Tseng
 @version 1.0
*/

/** @addtogroup MMPD_3GPMGR
 *  @{
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmpd_3gpmgr.h"
#include "mmph_hif.h"
#include "mmpf_3gpmgr.h"
#include "mmpf_mp4venc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_RECORD_TIME_LIMIT (0x7FFFFFFF)

//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

static MMP_ULONG    m_ulH264EncBSBufAddr[VIDENC_MAX_STREAM_NUM];
static MMP_ULONG    m_ulH264EncBSBufSize[VIDENC_MAX_STREAM_NUM];
static MMP_ULONG    m_ulH264EncSPSBufAddr[VIDENC_MAX_STREAM_NUM];
static MMP_ULONG    m_ulH264EncPPSBufAddr[VIDENC_MAX_STREAM_NUM];

static MMP_ULONG    m_ulTempFileNameBufAddr = 0;
static MMP_ULONG    m_ulTempFileNameBufSize = 0;

static MMP_ULONG    m_ulAuxTableBufStart[VIDENC_STREAM_MAX][MMPD_3GPMGR_AUX_TABLE_NUM] = {0}; // Size:0, Time:1
static MMP_ULONG    m_ulAuxTableBufSize[VIDENC_STREAM_MAX][MMPD_3GPMGR_AUX_TABLE_NUM] = {0};
static MMP_ULONG    m_ulTailBufStart[VIDENC_STREAM_MAX] = {0};
static MMP_ULONG    m_ulTailBufSize[VIDENC_STREAM_MAX] = {0};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____H264E_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_H264ENC_GetBitstreamBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_H264ENC_GetBitstreamBuf(MMP_ULONG ulEncId, MMP_ULONG* pulBufStart, MMP_ULONG* pulBufSize)
{
    if (pulBufStart)
        *pulBufStart = m_ulH264EncBSBufAddr[ulEncId];
    if (pulBufSize)
        *pulBufSize = m_ulH264EncBSBufSize[ulEncId];

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_H264ENC_SetBitstreamBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_H264ENC_SetBitstreamBuf(MMP_ULONG ulEncId, MMP_ULONG ulBufStart, MMP_ULONG ulBufSize)
{
    m_ulH264EncBSBufAddr[ulEncId] = ulBufStart;
    m_ulH264EncBSBufSize[ulEncId] = ulBufSize;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_H264ENC_GetHeaderBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_H264ENC_GetHeaderBuf(MMP_ULONG ulEncId, MMPD_H264ENC_HEADER_BUF *pHdrBuf)
{
    if (pHdrBuf) {
        pHdrBuf->ulSPSStart = m_ulH264EncSPSBufAddr[ulEncId];
        pHdrBuf->ulPPSStart = m_ulH264EncPPSBufAddr[ulEncId];
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_H264ENC_SetHeaderBuf
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set buffer for SPS, PPS
 @param[in] hdrbuf Buffer address
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_H264ENC_SetHeaderBuf(MMP_ULONG ulEncId, MMPD_H264ENC_HEADER_BUF *pHdrBuf)
{
    m_ulH264EncSPSBufAddr[ulEncId] = pHdrBuf->ulSPSStart;
    m_ulH264EncPPSBufAddr[ulEncId] = pHdrBuf->ulPPSStart;

    if (pHdrBuf->ulSPSStart &&
        pHdrBuf->ulPPSStart) {
        return MMPF_H264ENC_SetHeaderBuf(   MMPF_H264ENC_GetHandle(ulEncId),
                                            pHdrBuf->ulSPSStart,
                                            pHdrBuf->ulPPSStart,
                                            pHdrBuf->ulTmpSPSStart);
    }

    return MMP_ERR_NONE;
}

#if 0
void ____Record_Operation_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_StartCapture
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start capture audio/video
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_PreCapture(MMP_ULONG ulEncId, MMP_USHORT usStreamType, MMP_ULONG ulPreEncMs)
{
    MMP_ERR eEncStatus = MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, ulEncId);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, usStreamType);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8, ulPreEncMs);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_OPERATION | MERGER_PRE_ENCODE);
    eEncStatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 12);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return eEncStatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_StartAllCapture
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start all encoder audio/video together.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_StartAllCapture(MMP_UBYTE ubTotalEncCnt, MMP_ULONG *pulEncID)
{
    MMP_ERR ePrmStatus = MMP_ERR_NONE;
    MMP_ERR eScdStatus = MMP_ERR_NONE;
    MMP_ERR eTrdStatus = MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0,  ubTotalEncCnt);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4,  pulEncID[0]);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8,  pulEncID[1]);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 12, pulEncID[2]);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_OPERATION | MERGER_ALL_START);

    if (ubTotalEncCnt > 0) {
        ePrmStatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
    }
    if (ubTotalEncCnt > 1) {
        eScdStatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 8);
    }
    if (ubTotalEncCnt > 2) {
        eTrdStatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 12);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    if (ePrmStatus != MMP_ERR_NONE)
        return ePrmStatus;
    if (eScdStatus != MMP_ERR_NONE)
        return eScdStatus;
    if (eTrdStatus != MMP_ERR_NONE)
        return eTrdStatus;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_StartCapture
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start capture audio/video
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_StartCapture(MMP_ULONG ulEncId, MMP_USHORT usStreamType)
{
    MMP_ERR eEncStatus = MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, ulEncId);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, usStreamType);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_OPERATION | MERGER_START);
    eEncStatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 8);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return eEncStatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_StopCapture
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop capture audio/video
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_StopCapture(MMP_ULONG ulEncId, MMP_USHORT usStreamType)
{
    MMP_ERR eEncStatus = MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, ulEncId);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, usStreamType);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_OPERATION | MERGER_STOP);
    eEncStatus = MMPH_HIF_GetParameterL(GRP_IDX_VID, 8);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return eEncStatus;
}

#if 0
void ____Set_Record_Config_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_GetTempFileNameAddr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set temp address for filename buffer
 @param[in] addr address
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_GetTempFileNameAddr(MMP_ULONG* pulAddr, MMP_ULONG* pulSize)
{
    if (pulAddr)
        *pulAddr = m_ulTempFileNameBufAddr;
    if (pulSize)
        *pulSize = m_ulTempFileNameBufSize;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_SetTempFileNameAddr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set temp address for filename buffer
 @param[in] addr address
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_SetTempFileNameAddr(MMP_ULONG ulAddr, MMP_ULONG ulSize)
{
    m_ulTempFileNameBufAddr = ulAddr;
    m_ulTempFileNameBufSize = ulSize;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_SetFileName
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Send encoded 3GP file name to firmware for card mode.
 @param[in] bFileName File name.
 @param[in] usLength Length of file name in unit of byte.
 @retval MMP_ERR_NONE Success.
 @note It just use video compressed buffer to store file name. Then it should be set after MMPD_3GPMGR_SetEncodeCompBuf.
*/
MMP_ERR MMPD_3GPMGR_SetFileName(MMP_USHORT usStreamType, MMP_BYTE bFileName[], MMP_USHORT ulFileNameLength)
{
    MMP_UBYTE null = 0;

    if (ulFileNameLength > m_ulTempFileNameBufSize) {
        return MMP_3GPMGR_ERR_UNSUPPORT;
    }

#if 0
    MMPH_HIF_MemCopyHostToDev(m_ulTempFileNameBufAddr, (MMP_UBYTE *)bFileName, ulFileNameLength);
    MMPH_HIF_MemCopyHostToDev(m_ulTempFileNameBufAddr + ulFileNameLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulTempFileNameBufAddr + ulFileNameLength + 1, (MMP_UBYTE*)&null, 1);

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, m_ulTempFileNameBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, ulFileNameLength);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8, usStreamType);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_PARAMETER | ENCODE_FILE_NAME);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
#else
    MMPF_VIDMGR_SetFileName(usStreamType, (MMP_ULONG)bFileName, ulFileNameLength);
#endif

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_SetUserDataAtom
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Send user data atom to firmware for card mode.
 @param[in] UserDataBuf user data atom buffer.
 @param[in] UserDataLength Length of user data atom.
 @param[in] usStreamType file type.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_SetUserDataAtom(MMP_USHORT usStreamType, MMP_BYTE AtomName[], MMP_BYTE UserDataBuf[], MMP_USHORT UserDataLength)
{
    MMP_UBYTE   null = 0;
    MMP_UBYTE   *ptr;
    MMP_ULONG   AtomLen;
    MMP_LONG    i;

    AtomLen = UserDataLength + 8;
    if (AtomLen > m_ulTempFileNameBufSize) {
        return MMP_3GPMGR_ERR_UNSUPPORT;
    }

    ptr = (MMP_UBYTE *)m_ulTempFileNameBufAddr;
    for (i = (4-1); i >= 0; i--) {
        *ptr++ = (MMP_UBYTE)((AtomLen >> (i << 3)) & 0xFF);
    }

    MMPH_HIF_MemCopyHostToDev(m_ulTempFileNameBufAddr + 4, (MMP_UBYTE *)AtomName, 4);
    MMPH_HIF_MemCopyHostToDev(m_ulTempFileNameBufAddr + 8, (MMP_UBYTE *)UserDataBuf, UserDataLength);

    UserDataLength += 8;
    MMPH_HIF_MemCopyHostToDev(m_ulTempFileNameBufAddr + UserDataLength, (MMP_UBYTE*)&null, 1);
    MMPH_HIF_MemCopyHostToDev(m_ulTempFileNameBufAddr + UserDataLength + 1, (MMP_UBYTE*)&null, 1);

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, m_ulTempFileNameBufAddr);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, UserDataLength);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8, usStreamType);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_PARAMETER | SET_USER_DATA_ATOM);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_SetAudioParam
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set audio parameter.
 @param[in] param Audio parameter.
 @param[in] AudioMode Audio operation mode.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_SetAudioParam(  MMP_ULONG                   param,
                                    MMPD_3GPMGR_AUDIO_FORMAT    AudioMode)
{
    MMP_ULONG   ulParam, ret, mode;
    MMP_ERR     err = MMP_ERR_NONE;

    ulParam = param;

    switch(AudioMode) {
    case MMPD_3GPMGR_AUDIO_FORMAT_AMR:
        mode = AUDIO_AMR_MODE;
        break;
    case MMPD_3GPMGR_AUDIO_FORMAT_AAC:
        mode = AUDIO_AAC_MODE;
        break;
    case MMPD_3GPMGR_AUDIO_FORMAT_ADPCM:
        mode = AUDIO_ADPCM_MODE;
        break;
    case MMPD_3GPMGR_AUDIO_FORMAT_MP3:
        mode = AUDIO_MP3_MODE;
        break;
    case MMPD_3GPMGR_AUDIO_FORMAT_PCM:
        mode = AUDIO_PCM_MODE;
        break;
    default:
        return MMP_3GPMGR_ERR_PARAMETER;
    }

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, ulParam);
    err = MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_PARAMETER | mode);
    ret = MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    if (err)
        return err;
    else if (ret)
        return MMP_3GPMGR_ERR_PARAMETER;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_ModifyAVIListAtom
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Modify LIST Atom for AVI format.

 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_ModifyAVIListAtom(MMP_BOOL bEnable, MMP_BYTE *pStr)
{
    MMP_ULONG  ultmp;

    ultmp = (MMP_ULONG)*pStr |
            ((MMP_ULONG)*(pStr+1) << 8)  |
            ((MMP_ULONG)*(pStr+2) << 16) |
            ((MMP_ULONG)*(pStr+3) << 24);

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, bEnable);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, ultmp);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_PARAMETER | MODIFY_AVI_LIST_ATOM);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_GetRepackMiscBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_3GPMGR_GetRepackMiscBuf(MMP_USHORT             usStreamType,
                                     MMPD_3GPMGR_REPACKBUF  *pRepackBuf)
{
    if (pRepackBuf) {
        pRepackBuf->ulAvRepackStartAddr     = 0;
        pRepackBuf->ulAvRepackSize          = 0;
        pRepackBuf->ulVideoSizeTableAddr    = m_ulAuxTableBufStart[usStreamType][0];
        pRepackBuf->ulVideoSizeTableSize    = m_ulAuxTableBufSize[usStreamType][0];
        pRepackBuf->ulVideoTimeTableAddr    = m_ulAuxTableBufStart[usStreamType][1];
        pRepackBuf->ulVideoTimeTableSize    = m_ulAuxTableBufSize[usStreamType][1];
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_SetRepackMiscBuf
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set start address and size of firmware AV repack buffer.

 This buffer is for packing video and audio bitstream sequentially.
 @param[in] repackbuf information of AV repack buffer, such as start address/size,
 sync buffer address, buffer address/size for frame size, and buffer address/size for frame time.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_SetRepackMiscBuf(MMP_USHORT usStreamType, MMPD_3GPMGR_REPACKBUF *pRepackBuf)
{
    if (pRepackBuf == NULL) {
        return MMP_ERR_NONE;
    }

    if (pRepackBuf->ulAvRepackStartAddr &&
        pRepackBuf->ulAvRepackSize) {
        MMPF_VIDMGR_SetAVRepackBufferEx(usStreamType,
                                        pRepackBuf->ulAvRepackStartAddr,
                                        pRepackBuf->ulAvRepackSize);
    }

    m_ulAuxTableBufStart[usStreamType][0] = pRepackBuf->ulVideoSizeTableAddr;
    m_ulAuxTableBufSize[usStreamType][0]  = pRepackBuf->ulVideoSizeTableSize;

    if (pRepackBuf->ulVideoSizeTableAddr &&
        pRepackBuf->ulVideoSizeTableSize) {

        MMPF_VIDMGR_SetAuxTableBufferEx(usStreamType,
                                        MMPD_3GPMGR_AUX_FRAME_TABLE,
                                        pRepackBuf->ulVideoSizeTableAddr,
                                        pRepackBuf->ulVideoSizeTableSize);
    }

    m_ulAuxTableBufStart[usStreamType][1] = pRepackBuf->ulVideoTimeTableAddr;
    m_ulAuxTableBufSize[usStreamType][1]  = pRepackBuf->ulVideoTimeTableSize;

    if (pRepackBuf->ulVideoTimeTableAddr &&
        pRepackBuf->ulVideoTimeTableSize) {

        MMPF_VIDMGR_SetAuxTableBufferEx(usStreamType,
                                        MMPD_3GPMGR_AUX_TIME_TABLE,
                                        pRepackBuf->ulVideoTimeTableAddr,
                                        pRepackBuf->ulVideoTimeTableSize);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_SetTimeDynamicLimit
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Change the maximum 3GP file time for current video encoding.
 @param[in] ulTimeMax Maximum file time.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_SetTimeDynamicLimit(MMP_ULONG ulTimeMax)
{
    MMP_BOOL bCheck = MMP_FALSE;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);

    if (ulTimeMax > MAX_RECORD_TIME_LIMIT) {
        MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, MAX_RECORD_TIME_LIMIT);
    }
    else {
        MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, ulTimeMax);
    }
    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_PARAMETER | AV_TIME_DYNALIMIT);

    bCheck = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);

    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    if (bCheck == MMP_TRUE)
        return MMP_ERR_NONE;
    else
        return MMP_HIF_ERR_PARAMETER;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_GetRecordTailBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_3GPMGR_GetRecordTailBuf(   MMP_USHORT          usStreamType,
                                        MMP_ULONG*          pulTailBufAddr,
                                        MMP_ULONG*          pulTailBufSize)
{
    if (pulTailBufAddr)
        *pulTailBufAddr = m_ulTailBufStart[usStreamType];
    if (pulTailBufSize)
        *pulTailBufSize = m_ulTailBufSize[usStreamType];

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_SetRecordTailSpeed
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set video record with high speed to make tail mode.
 @param[in] ubHighSpeedEn Enable high speed mode or not.
 @param[in] ulTailInfoAddress Tail information address.
 @param[in] ulTailInfoSize Tail information size.
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_SetRecordTailSpeed( MMP_USHORT  usStreamType,
                                        MMP_BOOL    ubHighSpeedEn,
                                        MMP_ULONG   ulTailInfoAddr,
                                        MMP_ULONG   ulTailInfoSize)
{
    m_ulTailBufStart[usStreamType] = ulTailInfoAddr;
    m_ulTailBufSize[usStreamType]  = ulTailInfoSize;

    if (ulTailInfoAddr && ulTailInfoSize) {
        MMPF_VIDMGR_SetTailBufferEx(usStreamType, ubHighSpeedEn, ulTailInfoAddr, ulTailInfoSize);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_MakeRoom
//  Description :
//------------------------------------------------------------------------------
/** @brief The function make extra room from record storage space for other usage
@param[in] ulRequiredSize specify the size to ask recorder system make room for
@retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPD_3GPMGR_MakeRoom(MMP_ULONG ulEncId, MMP_ULONG ulRequiredSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, ulEncId);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, ulRequiredSize);

    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_PARAMETER | MAKE_EXTRA_ROOM);
    MMPH_HIF_GetParameterL(GRP_IDX_VID, 4);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return MMP_ERR_NONE;
}

#if 0
void ____Emergent_Record_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_StartEmergentRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Start emergent video recording.

 Start to save the 3GP file.
 @param[in] bStopVidRecd: stop normal record, keep emergent record
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPD_3GPMGR_StartEmergentRecd(MMP_BOOL bStopVidRecd)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_VID, 0, bStopVidRecd);
    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_OPERATION | MERGER_EMERGSTART);
    status = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_3GPMGR_StopEmergentRecd
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Stop emergent video recording.

 Stop to save the 3GP file.
 @retval MMP_ERR_NONE Success.
 @retval MMP_3GPRECD_ERR_GENERAL_ERROR Not allowed procedure.
*/
MMP_ERR MMPD_3GPMGR_StopEmergentRecd(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SendCmd(GRP_IDX_VID, HIF_VID_CMD_MERGER_OPERATION | MERGER_EMERGSTOP);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    return MMP_ERR_NONE;
}

/// @}

/// @end_ait_only
