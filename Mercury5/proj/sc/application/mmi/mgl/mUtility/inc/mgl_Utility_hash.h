/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *     mgl_Utility_hash.h
 *
 *
 * HISTORY
 *      2009.09.24       Chunwei Wang         Initial Version
 *
 *-----------------------------------------------------------------------------
 */
#ifndef __M_UTILITY_HASH_H__
#define __M_UTILITY_HASH_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define MGL_GET_OFFSET(Type,Member)          ((u32) &(((Type *) 0)->Member))

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
/*
 *  Define the hash pointer type
 */
typedef mgl_void* pMGL_Hash_st;
typedef mgl_s32 (*MGL_HashValue_pfn)(mgl_void *pvData);
typedef mgl_s32 (*MGL_HashComp_pfn)(mgl_void *pvData1, mgl_void *pvData2);
typedef mgl_void (*MGL_HashTraverse_pfn)(mgl_void *pvClientData, mgl_void *pvUserData);

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif

pMGL_Hash_st mglOpenHash(mgl_s32 iHashSize, mgl_u32 u32HashLinkOffset, MGL_HashValue_pfn pfnHashValue, MGL_HashComp_pfn pfnHashComp);
mgl_void* mglHashFind(pMGL_Hash_st ptHashPtr, mgl_void *pvUserData);
mgl_void mglHashInsert(pMGL_Hash_st ptHashPtr, mgl_void *pvUserData);
mgl_void* mglHashDelete(pMGL_Hash_st ptHashPtr, mgl_void *pvUserData);
mgl_void mglResetHash(pMGL_Hash_st ptHashPtr);
mgl_void mglCloseHash(pMGL_Hash_st ptHashPtr);
mgl_void mglHashTraverse(pMGL_Hash_st ptHashPtr, MGL_HashTraverse_pfn pfnTraverseCB, mgl_void *pvClientData);
mgl_s32 mglStr16HashValue(mgl_u16 *sText);
mgl_s32 mglStr8HashValue(mgl_s8 *sText);


#ifdef  __cplusplus
}
#endif


#endif /* __M_UTILITY_HASH_H__ */
