/// @ait_only
//==============================================================================
//
//  File        : mmpd_fctl.h
//  Description : INCLUDE File for the Host Flow Control Driver.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmpd_fctl.h
 *  @brief The header File for the Host Flow Control Driver
 *  @author Penguin Torng
 *  @version 1.0
 */

#ifndef _MMPD_FCTL_H_
#define _MMPD_FCTL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"

/** @addtogroup MMPD_FCtl
 *  @{
 */

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPD_Fctl_EnablePreview(MMP_UBYTE       ubSnrSel,
                                MMP_BOOL        bEnable,
                                MMP_BOOL        bCheckFrameEnd);

MMP_ERR MMPD_Fctl_SetDIPCompAttr(MMP_UBYTE ubDipType,
                                 MMP_UBYTE ubDipUseIdx,
                                 MMP_ULONG ulInX,   MMP_ULONG ulInY,    MMP_ULONG ulInW,    MMP_ULONG ulInH,
                                 MMP_ULONG ulCropX, MMP_ULONG ulCropY,  MMP_ULONG ulCropW,  MMP_ULONG ulCropH,
                                 MMP_ULONG ulOutX,  MMP_ULONG ulOutY,   MMP_ULONG ulOutW,   MMP_ULONG ulOutH,
                                 MMP_UBYTE ubInColor, MMP_UBYTE ubOutColor,
                                 MMP_UBYTE ubMirrorType,
                                 MMP_USHORT usLineBias,
                                 MMP_UBYTE ubBufCnt);

MMP_ERR MMPD_Fctl_SetDIPCompAttr_LineOffset(MMP_UBYTE ubDipType,
                                MMP_UBYTE ubDipUseIdx, MMP_UBYTE ubDipOutCompIdx,
                                MMP_ULONG ulInX,   MMP_ULONG ulInY,    MMP_ULONG ulInW,    MMP_ULONG ulInH,  MMP_ULONG ulInLineOffset,
                                MMP_ULONG ulCropX, MMP_ULONG ulCropY,  MMP_ULONG ulCropW,  MMP_ULONG ulCropH,
                                MMP_ULONG ulOutX,  MMP_ULONG ulOutY,   MMP_ULONG ulOutW,   MMP_ULONG ulOutH, MMP_ULONG ulOutLineOffset,
                                MMP_UBYTE ubInColor, MMP_UBYTE ubOutColor,
                                MMP_UBYTE ubMirrorType,
                                MMP_USHORT usLineBias,
                                MMP_UBYTE ubBufCnt);

MMP_ERR MMPD_Fctl_SetDIPCompCropWin( MMP_UBYTE ubDipType,
                                     MMP_UBYTE ubDipUseIdx,
                                     MMP_ULONG ulCropX, MMP_ULONG ulCropY,  MMP_ULONG ulCropW,  MMP_ULONG ulCropH);

MMP_ERR MMPD_Fctl_GetDIPCompWin( MMP_UBYTE ubDipType,
                                 MMP_UBYTE ubDipUseIdx,
                                 MMP_ULONG *pulInX,   MMP_ULONG *pulInY,   MMP_ULONG *pulInW,   MMP_ULONG *pulInH,
                                 MMP_ULONG *pulCropX, MMP_ULONG *pulCropY, MMP_ULONG *pulCropW, MMP_ULONG *pulCropH);

MMP_ERR MMPD_Fctl_SetSCLCompAttr(MMP_UBYTE ubSclType,
                                 MMP_UBYTE ubSclUseIdx,
                                 MMP_ULONG ulInX,   MMP_ULONG ulInY,    MMP_ULONG ulInW,    MMP_ULONG ulInH,
                                 MMP_ULONG ulOutX,  MMP_ULONG ulOutY,   MMP_ULONG ulOutW,   MMP_ULONG ulOutH,
                                 MMP_UBYTE ubBufCnt);

/// @}

#endif // _MMPD_FCTL_H_

/// @end_ait_only
