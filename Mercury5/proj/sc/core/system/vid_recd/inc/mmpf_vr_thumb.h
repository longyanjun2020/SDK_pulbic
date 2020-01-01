//==============================================================================
//
//  File        : mmpf_vr_thumb.h
//  Description : INCLUDE File for the Thumbnail encode Function
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_VR_THUMB_H_
#define _MMPF_VR_THUMB_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_vidrec_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define VR_THUMB_DISABLE            (0)
#define VR_THUMB_SKIP_ATOM          (0x1)
#define VR_THUMB_PANA_ATOM          (0x2)

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern VIDENC_THUMB_ATTR        gstVRThumbAttr[VIDENC_THUMB_MAX_TYPE][VR_THUMB_MAX_BUF_NUM];
extern VIDENC_THUMB_TARGET_CTL  gstVRThumbKeepQIdx[VIDENC_THUMB_MAX_TYPE];
extern MMP_ULONG                gulVRThumbWrIdx[VIDENC_THUMB_MAX_TYPE];
extern MMP_ULONG                gulVRThumbRdIdx[VIDENC_THUMB_MAX_TYPE];
extern MMP_USHORT               gusVRThumbBufNum[VIDENC_THUMB_MAX_TYPE];

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_UBYTE   MMPF_VIDENC_IsVRThumbCreateFile(void);
MMP_UBYTE   MMPF_VIDENC_IsVRThumbInsert2PanaAtom(void);
MMP_ULONG   MMPF_VIDENC_GetVRThumbSkipAtomLen(void);
MMP_UBYTE   MMPF_VIDENC_GetVRThumbEn(void);
MMP_ERR     MMPF_VIDENC_SetVRThumbEn(MMP_UBYTE ubThumbEn, MMP_UBYTE ubIsCreatJpgFile);
MMP_ERR     MMPF_VIDENC_SetVRThumbRingBufNum(MMP_UBYTE ubRingBufNum);
MMP_USHORT  MMPF_VIDENC_GetVRThumbRingBufNum(MMP_UBYTE ubRingType);
MMP_USHORT  MMPF_VIDENC_GetVRThumbStreamBufNum(MMP_UBYTE ubStreamType);
MMP_ERR     MMPF_VIDENC_SetVRThumbMaxBufSize(MMP_ULONG ulMaxSize);
MMP_ULONG   MMPF_VIDENC_GetVRThumbMaxBufSize(void);
MMP_ERR     MMPF_VIDENC_SetVRThumbResol(MMP_ULONG ulJpegW, MMP_ULONG ulJpegH);
MMP_ERR     MMPF_VIDENC_GetVRThumbResol(MMP_ULONG *pulJpegW, MMP_ULONG *pulJpegH);

MMP_ERR     MMPF_VIDENC_SwapThumbFromRing(MMP_ULONG ulRingType, MMP_ULONG ulThumbType, VIDENC_THUMB_ATTR* pTargetThumb, VIDENC_THUMB_TARGET_CTL* pTarIdxCtl);
MMP_ERR     MMPF_VIDENC_CaptureThumb2Ring(MMP_ULONG ulRingType, MMP_ULONG ulWrap, MMP_ULONG ulIdx);
MMP_ERR     MMPF_VIDENC_StoreVRThumbToCard(MMP_USHORT usStreamType);
MMP_ERR     MMPF_VIDENC_UpdateVRThumbInfo(MMP_UBYTE eRingBufType, MMP_ULONG ulSrcAddr, MMP_ULONG ulSize);

#endif // _MMPF_VR_THUMB_H_
