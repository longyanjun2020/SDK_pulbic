/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      db_rdgeoNameCache.h
 *
 * DESCRIPTION
 *      This file provides the interfaces to provide the cache for name storage.
 *
 * HISTORY
 *      2009.07.14       Mickey Chiang     Initial Version
 *----------------------------------------------------------------------------- 
 */
#ifndef DB_RDGEONAMECACHE_H
#define DB_RDGEONAMECACHE_H

#if defined(SUPPORT_RETURN_ONE_SCREENDATA)&&defined(SUPPORT_NAMECACHE)
/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 *  Syntax:
 *      MBOOL dbRdGeoNameCacheInitialize(MVOID);
 * 
 *  Purpose:
 *      Initialize the name pool index and the pointer of the used name entries.
 *
 *  Parameters:
 *      None.
 *
 *  Return Values
 *      None.
 */
MVOID dbRdGeoNameCacheInitialize(MVOID);

/*
 *  Syntax:
 *      PU16 dbRdGeoNameCacheHit(U32 u32NameID);
 * 
 *  Purpose:
 *      Get the name pointer by the given name ID.
 *
 *  Parameters:
 *      u32NameID
 *          [in] The name ID.
 *
 *  Return Values
 *      The pointer to the name.
 */
PU16 dbRdGeoNameCacheHit(U32 u32NameID);

/*
 *  Syntax:
 *      MVOID dbRdGeoNameCacheReplace(U32 u32NameID,PU16 pu16Name);
 * 
 *  Purpose:
 *      Replace the name entry with the given name ID and name pointer.
 *
 *  Parameters:
 *      u32NameID
 *          [in] The name ID.
 *      pu16Name
 *          [in] The pointer to the name.
 *
 *  Return Values
 *      None.
 */
MVOID dbRdGeoNameCacheReplace(U32 u32NameID,PU16 pu16Name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* end of #if defined(SUPPORT_RETURN_ONE_SCREENDATA)&&defined(SUPPORT_NAMECACHE) */
#endif    /* end of #ifndef DB_RDGEONAMECACHE_H */
