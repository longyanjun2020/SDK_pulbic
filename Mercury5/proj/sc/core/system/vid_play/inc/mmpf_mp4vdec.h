/**
 @file mmpf_mp4vdec.h
 @brief Header function of mpeg 4 simple profile decoder
 @author Truman Yang
 @version 1.0 Original Version
*/

#include "includes_fw.h"
#ifndef _MMPF_M_MP4V_DEC_H_
#define _MMPF_M_MP4V_DEC_H_
#include "mmpf_viddec_def.h"
//==============================================================================
//                                IPC SECTION
//==============================================================================
/** @addtogroup MMPF_MP4VDEC
@{
*/
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
/** @brief The config required in MP4V and H.263 decoder
*/
typedef struct MMPF_M_MP4V_CONFIG{
	MMP_USHORT	usHMB; ///< The number of horizontal macro blocks
	MMP_USHORT	usVMB; ///< The number of vertical macro blocks
	MMP_USHORT  usHWConfig;///< The attribute of VLD, including H263/MPEG4 format. RVLC and data partition.
	MMP_USHORT  usTimeIncRes;///< The video time increament resolution
	MMP_UBYTE   ubQType;     ///< 1 is MP4 Q type, 0 is 263 Q type
	MMP_UBYTE   ubQDownload; ///< 1 is needed download Q table
}MMPF_M_MP4V_CONFIG;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
void MMPF_MP4V_Debug(const MMPF_3GPP_DEBUG sCase);

// Will Add
MMP_ERR MMPF_MP4VDEC_SetFrameAddr(MMP_MEDIA_FRAME input_frame, MMP_UBYTE ubType);
MMP_ERR MMPF_MP4VDEC_SetBakFrame(MMP_MEDIA_FRAME bak_frame);
MMP_ERR MMPF_MP4VDEC_GetFrameSize(MMP_ULONG *ulYsize);
MMP_ERR MMPF_MP4VDEC_GetFrameType(MMP_UBYTE *ubType, MMP_ULONG ulAddr);
MMP_ERR MMPF_MP4VDEC_SetScale( MMP_ULONG ulAddr, MMP_BOOL *bCoded);
MMP_ERR MMPF_MP4VDEC_GetDecSize(MMP_ULONG *ulBSAddr, MMP_ULONG *ulSize);
// End Will Add
MMP_HANDLE MMPF_M4VDEC_Open(MMPF_VIDEO_FUNC *func);

/** @} */ // end of group MMPF_M
#endif