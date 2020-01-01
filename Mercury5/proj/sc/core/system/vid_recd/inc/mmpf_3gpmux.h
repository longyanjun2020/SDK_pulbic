#ifndef _MMPF_3GPMUX_H_
#define _MMPF_3GPMUX_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define PANA_FORMAT  (0)

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_ERR MMPF_3GPMUX_AddChunkPrefix(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_AddChunkSuffix(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pContainer);
MMP_ULONG MMPF_3GPMUX_CalcChunkPrefixSize(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pContainer);
MMP_ULONG MMPF_3GPMUX_CalcChunkSuffixSize(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_KeepIndexEntry(MMP_UBYTE chunktype, MMP_ULONG framesize, VIDENC_FRAME_TYPE frametype, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_AddIndexChunk(MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_GetRecordingSize(MMP_ULONG *ulSize, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_PreProcessFile(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_PostProcessFile(MMP_UBYTE storagemode, MMP_UBYTE * tmp_buf, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_GetSavedSize(MMP_ULONG AVSize, MMP_ULONG VideoCount, MMP_ULONG AudioSampleCount, MMP_ULONG AudioChunkCount, MMP_ULONG64 *total_size, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_FillTail(MMPF_VID_MGR_INFO* pContainer);
MMP_ERR MMPF_3GPMUX_InsertDupFrame(MMPF_VID_MGR_INFO* pContainer);

MMP_BOOL MMPF_3GPMUX_IsTimeInfoNeeded(void);
MMP_BOOL MMPF_3GPMUX_IsSizeInfoNeeded(void);

#endif // _MMPF_3GPMUX_H_
