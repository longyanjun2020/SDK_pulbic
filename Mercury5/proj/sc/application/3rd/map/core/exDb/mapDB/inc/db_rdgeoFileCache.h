/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      db_rdgeoFileCache.h
 *
 * DESCRIPTION
 *      This file provides the interfaces to provide the cache for file access.
 *
 * HISTORY
 *      2009.04.21       Mickey Chiang     Initial Version
 *----------------------------------------------------------------------------- 
 */
#ifndef DB_RDGEOFILECACHE_H
#define DB_RDGEOFILECACHE_H

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef SUPPORT_INPUT_MEMSPACE
/*
 *  Syntax:
 *      MBOOL dbRdGeoFCInitialize(PMVOID pvMemAddr,S32 s32MaxSize,PS32 ps32Idx);
 * 
 *  Purpose:
 *      Initialize the cache to assign the space to every cache banks from the given
 *      memory space.
 *
 *  Parameters:
 *      pvMemAddr
 *          [in] The address of the given memory space.
 *      s32MaxSize
 *          [in] The size of the given memory space.
 *      ps32Idx
 *          [out] The starting index of the memory space for the next module.
 *
 *  Return Values
 *      MBOOL_TRUE:  success.
 *      MBOOL_FALSE: fail.
 */
MBOOL dbRdGeoFCInitialize(PMVOID pvMemAddr,S32 s32MaxSize,PS32 ps32Idx);

#else    /* !defined(SUPPORT_INPUT_MEMSPACE) */
/*
 *  Syntax:
 *      MBOOL dbRdGeoFCInitialize(MVOID);
 * 
 *  Purpose:
 *      Initialize the cache to assign the space to every cache banks. The whole memory
 *      space is declared in static mode.
 *
 *  Parameters:
 *      None.
 *
 *  Return Values
 *      MBOOL_TRUE:  success.
 *      MBOOL_FALSE: fail.
 */
MBOOL dbRdGeoFCInitialize(MVOID);

#endif    /* end of #ifdef SUPPORT_INPUT_MEMSPACE */
/*
 *  Syntax:
 *      MVOID dbRdGeoFCFinalize(MVOID);
 * 
 *  Purpose:
 *      Finalize the cache.
 *
 *  Parameters:
 *      None.
 *
 *  Return Values
 *      None.
 */
MVOID dbRdGeoFCFinalize(MVOID);

/*
 *  Syntax:
 *      pGrid_st dbRdGeoFCMalloc(S32 s32Size,U32 u32GridID,PMBOOL pbNeedFileAccess);
 * 
 *  Purpose:
 *      Allocate one memory space for the caller.
 *
 *  Parameters:
 *      s32Size
 *          [in] The size of the required memory space.
 *      u32GridID
 *          [in] The absolute grid ID to identify the required memory space.
 *      pbNeedFileAccess
 *          [out] Depict whether it's necessary to do file access.
 *
 *  Return Values
 *      The memory space which is casted in grid data structure.
 */
pGrid_st dbRdGeoFCMalloc(S32 s32Size,U32 u32GridID,PMBOOL pbNeedFileAccess);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* end of #ifndef DB_RDGEOFILECACHE_H */
