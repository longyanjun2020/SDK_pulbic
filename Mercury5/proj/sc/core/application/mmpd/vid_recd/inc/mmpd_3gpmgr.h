/// @ait_only
/**
 @file mmpd_3gpmgr.h
 @brief Header File for the Host 3GP MERGER Driver.
 @author Will Tseng
 @version 1.0
*/

#ifndef _MMPD_3GPMGR_H_
#define _MMPD_3GPMGR_H_

//==============================================================================
//
//                              INCLUDE FILES
//
//==============================================================================

#include "mmp_vidrec_inc.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef struct _MMPD_H264ENC_HEADER_BUF {
    MMP_ULONG ulSPSStart;
    MMP_ULONG ulSPSSize;
    MMP_ULONG ulTmpSPSStart;
    MMP_ULONG ulTmpSPSSize;
    MMP_ULONG ulPPSStart;
    MMP_ULONG ulPPSSize;
} MMPD_H264ENC_HEADER_BUF;

// AV operation mode. This is for recorder only, used in Initialization
typedef enum _MMPD_3GPMGR_AUDIO_FORMAT {
    MMPD_3GPMGR_AUDIO_FORMAT_AAC = 0x00,    ///< Video encode with AAC audio
    MMPD_3GPMGR_AUDIO_FORMAT_AMR,           ///< Video encode with AMR audio
    MMPD_3GPMGR_AUDIO_FORMAT_ADPCM,         ///< Video encode with ADPCM audio
    MMPD_3GPMGR_AUDIO_FORMAT_MP3,           ///< Video encode with MP3 audio
    MMPD_3GPMGR_AUDIO_FORMAT_PCM            ///< Video encode with raw PCM audio
} MMPD_3GPMGR_AUDIO_FORMAT;

// Aux table index
typedef enum _MMPD_3GPMGR_AUX_TABLE {
    MMPD_3GPMGR_AUX_FRAME_TABLE = 0,        ///< Video encode aux frame table
    MMPD_3GPMGR_AUX_TIME_TABLE  = 1,        ///< Video encode aux time table
    MMPD_3GPMGR_AUX_TABLE_NUM
} MMPD_3GPMGR_AUX_TABLE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMPD_3GPMGR_REPACKBUF {
    MMP_ULONG ulAvRepackStartAddr;              ///< AV repack buffer start address for 3gp encoder
    MMP_ULONG ulAvRepackSize;                   ///< AV repack buffer size for 3gp encoder
    MMP_ULONG ulVideoSizeTableAddr;             ///< Video encode frame table buffer start address
    MMP_ULONG ulVideoSizeTableSize;             ///< Video encode frame table buffer size
    MMP_ULONG ulVideoTimeTableAddr;             ///< Video encode time table buffer start address
    MMP_ULONG ulVideoTimeTableSize;             ///< Video encode time table buffer size
} MMPD_3GPMGR_REPACKBUF;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/** @addtogroup MMPD_3GPMGR
 *  @{
 */

MMP_ERR MMPD_H264ENC_GetBitstreamBuf(MMP_ULONG ulEncId, MMP_ULONG* pulBufStart, MMP_ULONG* pulBufSize);
MMP_ERR MMPD_H264ENC_SetBitstreamBuf(MMP_ULONG ulEncId, MMP_ULONG ulBufStart, MMP_ULONG ulBufSize);
MMP_ERR MMPD_H264ENC_GetHeaderBuf(MMP_ULONG ubEncId, MMPD_H264ENC_HEADER_BUF *hdrbuf);
MMP_ERR MMPD_H264ENC_SetHeaderBuf(MMP_ULONG ulEncId, MMPD_H264ENC_HEADER_BUF *hdrbuf);

MMP_ERR MMPD_3GPMGR_PreCapture(MMP_ULONG ulEncId, MMP_USHORT usStreamType, MMP_ULONG ulPreEncMs);
MMP_ERR MMPD_3GPMGR_StartAllCapture(MMP_UBYTE ubTotalEncCnt, MMP_ULONG *pEncID);
MMP_ERR MMPD_3GPMGR_StartCapture(MMP_ULONG ulEncId, MMP_USHORT usStreamType);
MMP_ERR MMPD_3GPMGR_StopCapture(MMP_ULONG ulEncId, MMP_USHORT usStreamType);

MMP_ERR MMPD_3GPMGR_GetTempFileNameAddr(MMP_ULONG* pulAddr, MMP_ULONG* pulSize);
MMP_ERR MMPD_3GPMGR_SetTempFileNameAddr(MMP_ULONG addr, MMP_ULONG size);
MMP_ERR MMPD_3GPMGR_SetFileName(MMP_USHORT usStreamType, MMP_BYTE bFileName[], MMP_USHORT usLength);
MMP_ERR MMPD_3GPMGR_SetUserDataAtom(MMP_USHORT usStreamType, MMP_BYTE AtomName[], MMP_BYTE UserDataBuf[], MMP_USHORT UserDataLength);
MMP_ERR MMPD_3GPMGR_ModifyAVIListAtom(MMP_BOOL bEnable, MMP_BYTE *pStr);
MMP_ERR MMPD_3GPMGR_SetAudioParam(  MMP_ULONG                   param,
                                    MMPD_3GPMGR_AUDIO_FORMAT    AudioMode);
MMP_ERR MMPD_3GPMGR_SetTimeDynamicLimit(MMP_ULONG ulTimeMax);
MMP_ERR MMPD_3GPMGR_GetRepackMiscBuf(MMP_USHORT             usStreamType,
                                     MMPD_3GPMGR_REPACKBUF  *pRepackBuf);
MMP_ERR MMPD_3GPMGR_SetRepackMiscBuf(MMP_USHORT usStreamType, MMPD_3GPMGR_REPACKBUF *repackbuf);
MMP_ERR MMPD_3GPMGR_GetRecordTailBuf(   MMP_USHORT          usStreamType,
                                        MMP_ULONG*          pulTailInfoAddress,
                                        MMP_ULONG*          pulTailInfoSize);
MMP_ERR MMPD_3GPMGR_SetRecordTailSpeed( MMP_USHORT              usStreamType,
                                        MMP_BOOL                ubHighSpeedEn,
                                        MMP_ULONG               ulTailInfoAddress,
                                        MMP_ULONG               ulTailInfoSize);
MMP_ERR MMPD_3GPMGR_MakeRoom(MMP_ULONG ulEncId, MMP_ULONG ulRequiredSize);

// Emergency Record Function
MMP_ERR MMPD_3GPMGR_StartEmergentRecd(MMP_BOOL bStopVidRecd);
MMP_ERR MMPD_3GPMGR_StopEmergentRecd(void);

#endif // _MMPD_3GPMGR_H_

/// @end_ait_only
