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
///@file       mdl_vdr_mx_movatom.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_MOVATOM_H__
#define __MDL_VDR_MX_MOVATOM_H__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include "mdl_vdr_mx_def.h"


//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------
//#define MP4MUX_MPEG4_EN
#define MP4MUX_ADO_MP3_EN
#define MP4MUX_ADO_PCM_EN

#if defined(MP4MUX_MPEG4_EN)
#define MP4_ATOM_IODS_EN
#define MP4_ATOM_ESDS_EN
#endif

//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------
#define VDO_TIMESCALE	8000

#define AMR_VENDOR          0x4d537472 //MStr //0x4d535452 //MSTR //0x6861726b//hark
#define H263_VENDOR         0x4d537472 //MStr //0x4d535452 //MSTR //0x6861726b//hark
#define H263_VENDOR_MSTR    0x4d537472 //MStr //0x4d535452 //MSTR //0x6861726b//hark
#define H263_VENDOR_FFMP    0x46464d50 //FFMP //0x46464d50

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

struct tagMOVATOMARRAY;
struct tagMOVPropertyArray;
struct tagMOVAtomInfoArray;
struct tagMOVFile;
struct tagMOVProperty;

typedef struct tagMOVATOM {
	struct tagMOVFile*	m_pFile;
	FILE_POS	m_start;
	FILE_POS	m_end;
	FILE_POS	m_size;
	u8		m_type[5];

	struct tagMOVATOM*	m_pParentAtom;
	struct tagMOVAtomInfoArray *m_pChildAtomInfos;
	struct tagMOVATOMARRAY		*m_pChildAtoms;

	void		*m_pProperties;

	struct tagMOVATOM		*m_pNextAtom;	// next atom address in the atom array
} MOVATOM, *PMOVATOM;

typedef struct tagMOVATOMARRAY
{
	u32			m_totalnum;
	MOVATOM		*m_pBegin;
	MOVATOM		*m_pTail;
} MOVATOMARRAY, *PMOVATOMARRAY;

typedef struct tagMOVAtomInfo
{
	u8 m_name[5];
	u8 m_mandatory;
	u8 m_onlyOne;

	struct tagMOVAtomInfo *m_pNextItem;
} MOVATOMINFO, *PMOVATOMINFO;

typedef struct tagMOVAtomInfoArray
{
	u32				m_totalnum;
	MOVATOMINFO		*m_pBegin;
	MOVATOMINFO		*m_pTail;
} MOVATOMINFOARRAY, *PMOVATOMINFOARRAY;


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------
// Atom API
MOVATOM* mxMP4CreateAtom(const char* type);
U8 mxMP4AtomGenerate(MOVATOM *pAtom);
U8 mxMP4AtomFree(MOVATOM *pAtom);
MOVATOM* mxMP4AtomFindAtom(MOVATOM *pAtom, const char* name);
uint32_t mxMP4AtomGetNumberOfChildAtoms(MOVATOM *pAtom);
void mxMP4AtomInsertChildAtom(MOVATOM *pAtom, MOVATOM* pChildAtom, uint32_t index);
U8 mxMP4AtomSetProperty(MOVATOM *pAtom, char *name, void *value);
U8 mxMP4AtomGetProperty(MOVATOM *pAtom, char *name, void *value);
void mxMP4AtomFinishWriteRootAtom(MOVATOM *pRootAtom);

// Atom array
U8 mxMP4AtomArrayAdd(MOVATOMARRAY *pArray, MOVATOM *pAtom);
U8 mxMP4AtomArrayInsert(MOVATOMARRAY *pArray, uint32_t index, MOVATOM *pAtom);
MOVATOM *mxMP4AtomArrayGet(MOVATOMARRAY *pArray, uint32_t index);
#define mxMP4AtomArrayGetTail(pArray) ((pArray)->m_pTail)
#define mxMP4AtomArrayGetSize(pArray) ((pArray)->m_totalnum)
U8 mxMP4AtomArrayFree(MOVATOMARRAY *pArray);
MOVATOMINFO *mxMP4CreateInfo(const char* name, U8 mandatory, U8 onlyOne);
U8 mxMP4AtomInfoArrayAdd(MOVATOMINFOARRAY *pArray, MOVATOMINFO *pAtom);
U8 MP4AtomInfoArrayInsert(MOVATOMINFOARRAY *pArray, uint32_t index, MOVATOMINFO *pAtom);
U8 MP4AtomInfoArrayDelete(MOVATOMINFOARRAY *pArray, uint32_t index);
MOVATOMINFO *mxMP4AtomInfoArrayGet(MOVATOMINFOARRAY *pArray, uint32_t index);
#define mxMP4AtomInfoArrayGetTail(pArray) ((pArray)->m_pTail)
#define mxMP4AtomInfoArrayGetSize(pArray) ((pArray)->m_totalnum)
U8 mxMP4AtomInfoArrayFree(MOVATOMINFOARRAY *pArray);

#endif // __MDL_VDR_MX_MOVATOM_H__

