/***********************************************************************
Filename   : rvpoolmem.h
Description: rvpoolmem header file
************************************************************************
      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/
/*$
{package:
	{name: PoolMem}
	{superpackage: Memory}
	{include: rvmemory.h}
	{description:	
		{p: This module is a driver for the Memory module and provides
			block pool memory management.}
		{p: There are three types of pools:}
		{bulletlist:
			{item:  FIXED: This creates a fixed size pool with all blocks
					pre-allocated. The number of starting blocks (or pages)
					can never be changed.}
			{item:  EXPANDING: This creates a pool which expands (by adding
					pages) as needed. The pages are not released until the
					region is destructed.}
			{item:  DYNAMIC: This creates a pool which expands exactly like
					and EXPANDING pool but also has the ability to removed
					unused pages. The freelevel value in the RvPoolMemAttr
					determines when a page should be released.}
		}
	}
	{notes:
		{note:  When calling RvMemoryConstruct, set the drivernum parameter to
				RV_MEMORY_DRIVER_POOLMEM to create a region using this driver.}
		{note:  When calling RvMemoryConstruct, the start parameter is ignored
				and the size parameter indicates the block size of the pool.}
		{note:  When calling RvMemoryConstruct, pass a structure of type RvPoolMemAttr
				as the attr parameter. This structure contains the information
				required to create a block pool and must be completely filled out.}
		{note:  All blocks must be returned to a pool before destructing it or
				an error will be reported and the pool will not be destructed.}
	}
}
$*/

/* Due to type dependencies, rvmemory.h requires that it include driver */
/* headers and not the reverse, so force it to happen. */
#ifndef RV_MEMORY_H
#include "rvmemory.h"
#endif

#ifndef RV_POOLMEM_H
#define RV_POOLMEM_H

#include "rvobjpool.h"
#include "rvlock.h"

/* Module specific error codes (-512..-1023). See rverror.h dor more details */

/* Pool Types: Not all attribute parameters used by all types */
/*   FIXED: Fixed pool with number of blocks set by startblocks or startpages attribute */
/*   EXPANDING: Pages (and thus blocks) added as needed, starting amount set by startblocks or startpages */
/*   DYNAMIC: Pages added as needed and removed automatically. The freelevel attribute should */
/*             be set to blocks free per 100 which should be maintained (freelevel == 0 indicates */
/*             to always remove free pages). */
#define RV_POOLMEM_TYPE_FIXED RV_OBJPOOL_TYPE_FIXED
#define RV_POOLMEM_TYPE_EXPANDING RV_OBJPOOL_TYPE_EXPANDING
#define RV_POOLMEM_TYPE_DYNAMIC RV_OBJPOOL_TYPE_DYNAMIC

#if defined(__cplusplus)
extern "C" {
#endif 

/*$
{type:
	{name: RvPoolMemAttr}
	{superpackage: PoolMem}
	{include: rvmemory.h}
	{description:	
		{p: A structure containing the information required to construct a block pool
			memory region. This structure is passed in via the attr parameter of the
			RvMemoryConstruct function.}
	}
	{attributes scope="public":
		{attribute: {t: RvInt }    {n: pooltype}    {d: The type of block pool: RV_POOLMEM_TYPE_FIXED, RV_POOLMEM_TYPE_EXPANDING, or RV_POOLMEM_TYPE_DYNAMIC.}}
		{attribute: {t: RvSize_t } {n: pageblocks}  {d: The number of blocks per page (0 = calculate from pagesize).}}
		{attribute: {t: RvSize_t } {n: pagesize}    {d: The size of each page (0 = calculate from pageblocks).}}
		{attribute: {t: RvSize_t } {n: maxblocks}   {d: Never exceed this number of blocks (0 = no limit).}}
		{attribute: {t: RvSize_t } {n: minblocks}   {d: Never go below this number of blocks.}}
		{attribute: {t: RvSize_t } {n: freelevel}   {d: The minimum number of free blocks per 100 to maintain when shrinking a DYNAMIC pool (0 to 100).
														A value of 0 always releases empty pages and a value of 100 never releases empty pages
														(which is the same as an EXPANDING pool).}}
		{attribute: {t: RvSize_t } {n: startblocks} {d: The number of blocks to start with. }}
		{attribute: {t: RvSize_t } {n: startpages}  {d: The number of pages to start with (used if startblocks = 0).}}
	}
}
$*/
/* Attribute struct to be filled out by user and passed into RvMemoryConstruct. */
typedef struct {
	RvInt pooltype;       /* Type of pool */
	RvSize_t pageblocks;  /* number of blocks per page (0 = calculate) */
	RvSize_t pagesize;    /* size of each page (0 = calculate) */
	RvSize_t maxblocks;   /* never exceed this number of blocks (0 = no limit) */
	RvSize_t minblocks;   /* never go below this number of blocks */
	RvSize_t freelevel;   /* free level option for dynamic pools (0..100) */
	RvSize_t startblocks; /* number of blocks to start with */
	RvSize_t startpages;  /* number of pages to start with (used if startblocks = 0) */
} RvPoolMemAttr;

/* Driver specific region data definition */
typedef struct {
	RvLock lock;        /* Lock for pool region */
	RvSize_t blocksize; /* Size needed for each block in pool */
	RvSize_t usersize;  /* Size of block user requested */
	RvSize_t overhead;  /* Overhead that rvmemory asked for */
	RvInt pooltype;     /* Type of pool (see rvobjpool) */
	RvMemory *moremem;  /* Where to allocated pages from */
	RvObjPool objpool;  /* Pool itself (see rvobjpool) */
} RvPoolMemData;

/* Prototypes and macros */

/********************************************************************************************
 * RvPoolMemInit - Initializes the PoolMem module.
 *
 * Must be called once (and only once) before any other functions in the module are called.
 *
 * INPUT   : none
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvPoolMemInit(void);

/********************************************************************************************
 * RvPoolMemEnd - Shuts down the PoolMem module.
 *
 * Must be called once (and only once) when no further calls to this module will be made.
 *
 * INPUT   : none
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvPoolMemEnd(void);


#if (RV_MEMORY_TYPE == RV_MEMORY_POOL)

/********************************************************************************************
 * RvPoolMemConstruct - Creates a pool driver memory region. 
 *
 * A "pool" memory region is managed by RvObjPool module.
 * This function constructs a ObjPool object which will satisfies alloc requests.
 *
 * INPUT   : start	   	  - Starting address of region (ignored).
 *			 size		  - Block size.
 *           overhead     - RvMemory overhead.
 *			 moremem	  - Memory region to get additional memory from.
 *			 attr		  - Pool configuration.
 * OUTPUT  : driverRegion - Pointer to object where region information will be stored.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvPoolMemConstruct(
    IN  void*        start,
    IN  RvSize_t     size,
    IN  RvSize_t     overhead,
    IN  RvMemory*    moremem,
    IN  void*        attr,
    OUT void*        driverRegion);
    
/********************************************************************************************
 * RvPoolMemDestruct - Destroys a pool driver memory region.
 *
 * Destructs the ObjPool object that has been created by RvPoolMemConstruct().
 *
 * INPUT   : driverRegion - Pointer to the region object to be destroyed.
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvPoolMemDestruct(
    IN void*        driverRegion);

/********************************************************************************************
 * RvPoolMemAlloc - Allocates memory from a pool driver region.
 *
 * Use the ObjPool facilities to allocate a block of memory from the ObjPool object.
 *
 * INPUT   : driverRegion - Pointer to the region object.
 *			 size		  - Number of bytes of memory needed (used only to verify that the size
 *                          of the requested block is not bigger than the region block size).
 * OUTPUT  : result       - Pointer to where the resulting memory pointer will be stored.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvPoolMemAlloc(
    IN  void*       driverRegion,
    IN  RvSize_t    size,
    OUT void**      result);

/********************************************************************************************
 * RvPoolMemFree - Frees a memory which was allocated from a pool driver region.
 *
 * Use the ObjPool facilities to release a block of memory back to the ObjPool object.
 *
 * INPUT   : driverRegion - Pointer to the region object.
 *           ptr          - Pointer to the allocated memory to be released.
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvPoolMemFree(
    IN  void*       driverRegion,
    IN  void*       ptr);

/********************************************************************************************
 * RvPoolMemGetInfo - Returns the collected statistic information about a memory region.
 *
 * Since there's no run-time additional overhead we can always return statistics regardless
 * of the RV_MEMORY_KEEPSTATS flag except for those that depend on other memory regions 
 * (which may not be keeping them).
 *
 * INPUT   : driverRegion - Pointer to the region object where statistic data is stored.
 * OUTPUT  : result       - Pointer to RvMemoryInfo structure where the statistic data
 *                          will be copied into.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvPoolMemGetInfo(
    IN  void*           driverRegion,
    OUT RvMemoryInfo*   meminfo);
#endif

#if defined(__cplusplus)
}
#endif 

#endif
