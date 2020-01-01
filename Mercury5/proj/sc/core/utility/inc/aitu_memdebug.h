//==============================================================================
//
//  File        : aitu_memdebug.h
//  Description : Header File of Generic Memory Debug Utility
//  Author      : Eroy
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AITU_MEM_DEBUG_H_
#define _AITU_MEM_DEBUG_H_

/** @addtogroup AIT_UTILITY
 *  @{
 */

//==============================================================================
//
//                              INCLUDE FILES
//
//==============================================================================

#include "mmpf_typedef.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define MEM_DBG_MAX_STRING_LEN	(32)
#define MEM_DBG_MAX_ITEM_NUM 	(25)

#define MEM_DBG_ERR_NONE		(0)
#define MEM_DBG_ERR_NULL_PTR	(1)
#define MEM_DBG_ERR_PARAM		(2)

#define MEM_MAP_DBG_EN			(0)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/*
 * Memory Debug Usage ID
 */
typedef enum _AUTL_MEMDBG_USAGE_ID {
	AUTL_MEMDBG_USAGE_ID_VR_PREVW = 0,
	AUTL_MEMDBG_USAGE_ID_VR_RECD,
	AUTL_MEMDBG_USAGE_ID_DSC_PREVW,
	AUTL_MEMDBG_USAGE_ID_DSC_CAPTURE,
	AUTL_MEMDBG_USAGE_ID_UNDEF,
	AUTL_MEMDBG_USAGE_ID_NUM
} AUTL_MEMDBG_USAGE_ID;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

/*
 * Memory Debug Item
 */
typedef struct _AUTL_MEMDBG_ITEM {
    MMP_ULONG   ulItemIdx;         					///< Item Index
    MMP_ULONG   ulMemSt;    						///< Buffer Start Address
    MMP_ULONG   ulMemEd;    						///< Buffer End Address
    MMP_ULONG   ulMemSz;							///< Buffer Size
    MMP_UBYTE   ubMemDesc[MEM_DBG_MAX_STRING_LEN];	///< Item Description
} AUTL_MEMDBG_ITEM;

/*
 * Memory Debug Block
 */
typedef struct _AUTL_MEMDBG_BLOCK {
    AUTL_MEMDBG_USAGE_ID	sUsageId;   					///< Memory Usage ID
    AUTL_MEMDBG_ITEM 		sItem[MEM_DBG_MAX_ITEM_NUM];   	///< Memory Debug Items
} AUTL_MEMDBG_BLOCK;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

int AUTL_MemDbg_Init(AUTL_MEMDBG_BLOCK *pBlock, MMP_UBYTE ubUsageId);
int AUTL_MemDbg_PushItem(AUTL_MEMDBG_BLOCK 	*pBlock, 
						 MMP_ULONG 			ulItemIdx, 
						 MMP_ULONG   		ulMemSt,
						 MMP_ULONG   		ulMemEd,
						 MMP_ULONG   		ulMemSz,
						 MMP_UBYTE*   		ubMemDesc);
int AUTL_MemDbg_ShowItem(AUTL_MEMDBG_BLOCK *pBlock, MMP_ULONG ulItemIdx);
int AUTL_MemDbg_ShowAllItems(AUTL_MEMDBG_BLOCK *pBlock, MMP_BOOL bShow);
				 
/// @}

#endif //_AITU_MEM_DEBUG_H_
