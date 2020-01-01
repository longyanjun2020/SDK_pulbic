/// @ait_only
//==============================================================================
//
//  File        : mmpd_dsc.h
//  Description : INCLUDE File for the Host DSC Driver.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPD_DSC_H_
#define _MMPD_DSC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_dsc_inc.h"
#include "mmp_media_def.h"

/** @addtogroup MMPD_DSC
 *  @{
 */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

// Decode Function
MMP_ERR MMPD_DSC_GetJpegInfo(MMP_DSC_JPEG_INFO *pJpegInfo);
MMP_ERR MMPD_DSC_OpenJpegFile(MMP_DSC_JPEG_INFO *pJpegInfo);
MMP_ERR MMPD_DSC_CloseJpegFile(MMP_DSC_JPEG_INFO *pJpegInfo);

// MPF Function
MMP_ERR MMPD_DSC_UpdateMpfNode(MMP_USHORT   usIfd,  MMP_USHORT  usTag,
                               MMP_USHORT   usType, MMP_ULONG   ulCount,
                               MMP_UBYTE    *pData, MMP_ULONG   ulDataSize,
                               MMP_BOOL     bForUpdate);
MMP_ERR MMPD_DSC_UpdateMpfEntry(MMP_USHORT      usIfd,          MMP_USHORT  usEntryID,
                                MMP_ULONG       ulImgAttr,      MMP_ULONG   ulImgSize,
                                MMP_ULONG       ulImgOffset,
                                MMP_USHORT      usImg1EntryNum, MMP_USHORT  usImg2EntryNum,
                                MMP_BOOL        bForUpdate);

// EXIF Function
MMP_ERR MMPD_DSC_SetExifWorkingBuffer(MMP_USHORT usExifNodeId, MMP_UBYTE *pBuf, MMP_ULONG ulBufSize, MMP_BOOL bForUpdate);
MMP_ERR MMPD_DSC_SetCardModeExifEnc(MMP_USHORT  usExifNodeId,
                                    MMP_BOOL    bEncodeExif,
                                    MMP_BOOL    bEncodeThumbnail,
                                    MMP_USHORT  usPrimaryJpegW,
                                    MMP_USHORT  usPrimaryJpegH,
                                    MMP_USHORT  usThumbnailW,
                                    MMP_USHORT  usThumbnailH);
MMP_ERR MMPD_DSC_SetCardModeExifDec(MMP_BOOL bDecodeThumb, MMP_BOOL bDecodeLargeThumb);
MMP_ERR MMPD_DSC_OpenEXIFFile(MMP_UBYTE *pubFileName, MMP_ULONG ulFileNameLen, MMP_USHORT usExifNodeId);
MMP_ERR MMPD_DSC_UpdateExifNode(MMP_USHORT  usExifNodeId,
                                MMP_USHORT  usIfd,  MMP_USHORT  usTag,
                                MMP_USHORT  usType, MMP_ULONG   ulCount,
                                MMP_UBYTE   *pData, MMP_ULONG   ulDataSize,
                                MMP_BOOL    bForUpdate);

// Storage Function
MMP_ERR MMPD_DSC_SetFileName(MMP_BYTE ubFilename[], MMP_USHORT usLength);
MMP_ERR MMPD_DSC_SetThumbFileName(MMP_BYTE ubFilename[], MMP_USHORT usLength);
MMP_ERR MMPD_DSC_SetFileNameAddr(MMP_ULONG ulFilenameAddr);
MMP_ERR MMPD_DSC_GetFileNameAddr(MMP_ULONG *pulFilenameAddr);

// Streaming Function
MMP_ERR MMPD_Streaming_Init(MMP_USHORT usEncID);
MMP_ERR MMPD_Streaming_SetModeID(MMP_USHORT usEncID, MMP_USHORT usModeID);
MMP_ERR MMPD_Streaming_SetCompBuf(MMP_USHORT usEncID, MMP_USHORT usModeID, MMP_ULONG ulAddr, MMP_ULONG ulSize, MMP_M_STREAMCB_CODEC eCodec, MMP_ULONG ulThresholdCB);
MMP_ERR MMPD_Streaming_Enable(MMP_USHORT usEncID, MMP_BOOL bEnable, MMP_BOOL bWaitForSync);

// MJPEG Function
MMP_ERR MMPD_MJPEG_CheckEncodeDone(MMP_USHORT usEncID);
MMP_ERR MMPD_MJPEG_SetFPS(MMP_USHORT usEncID, MMP_ULONG ulIncrReso, MMP_ULONG ulIncrement);

/// @}

#endif // _MMPD_DSC_H_

/// @end_ait_only
