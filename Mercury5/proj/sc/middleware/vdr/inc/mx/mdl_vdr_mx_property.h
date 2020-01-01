////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_mx_property.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_PROPERTY_H__
#define __MDL_VDR_MX_PROPERTY_H__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include "mdl_vdr_mx_atom.h"
#include "mdl_vdr_mx_movatom.h"

//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------
struct tagMOVATOM;

//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// for muxer
//-----------------------------------------------------------------------------
void mxMP4FTYPPropBrandsFree(FTYPPROP *ftypprop);
U8 mxMP4DrefGetValue(struct tagMOVATOM *pAtom, char *property, void *pvalue);
U8 mxMP4StsdGetValue(struct tagMOVATOM *pAtom, char *property, void *pvalue);
U8 mxMP4TkhdGetValue(struct tagMOVATOM *pAtom, char *property, void *pvalue);
U8 mxMP4MdhdGetValue(struct tagMOVATOM *pAtom, char *property, void *pvalue);
void mxMP4IodsSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4TkhdSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4MstrSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4HdlrSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4MdhdSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4DrefSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4StsdSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4SounSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4DamrSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4MvhdSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4VideSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4D263SetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4BitrSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4EsdsSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4SttsSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4StszSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4StscSetValue(struct tagMOVATOM *pAtom, char *property, void *value);
void mxMP4StcoAddEntry(void *pmuxobj, STCOPROP *pstcoprop, uint32_t chunkOffset);
void mxMP4StszAddEntry(void *pmuxobj, STSZPROP *pstszprop, uint32_t entry_size);
void mxMP4SttsAddEntry(void *pmuxobj, STTSPROP *psttsprop, uint32_t sample_delta);
void mxMP4StssAddEntry(void *pmuxobj, STSSPROP *pstssprop, uint32_t sample_number);
void mxMP4StscAddChunk(void *pmuxobj, STSCPROP *pstscprop, uint32_t chunkId, uint32_t samplesperchunk, uint32_t samplesdescrindex);
void mxMP4StscAddEntry(void *pmuxobj, STSCPROP *pstscprop);

#endif // __MDL_VDR_MX_PROPERTY_H__

