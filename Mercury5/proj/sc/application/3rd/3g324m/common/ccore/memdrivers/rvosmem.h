/***********************************************************************
Filename   : rvosmem.h
Description: rvosmem header file
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
	{name: OSMem}
	{superpackage: Memory}
	{include: rvmemory.h}
	{description:
		{p: This module is a driver for the Memory module and provides
			standard dynamic memory management using standard OS calls.}
	}
	{notes:
		{note:  When calling RvMemoryConstruct, set the drivernum parameter to
				RV_MEMORY_DRIVER_OSMEM to create a region using this driver.}
		{note:  When calling RvMemoryConstruct, the start, size, moremem, and
				attr parameters are ignored and have no effect when creating
				this type of region.}
		{note:  Destructing a region of this type will not release memory that
				has not been deallocated and will not report an error on most
				operating systems.}
		{note:  Not all operating systems provide complete memory statistics.}
		{note:  Memory statistics do not account for the overhead that may be
				caused by the underlying operating system memory allocation
				mechanism.}
		{note:  This driver is set up as the default driver and is used for
				the default region created by the Memory module.}
	}
}
$*/

/* Due to type dependencies, rvmemory.h requires that it include driver */
/* headers and not the reverse, so force it to happen. */
#ifndef RV_MEMORY_H
#include "rvmemory.h"
#endif

#ifndef RV_OSMEM_H
#define RV_OSMEM_H

#include "rvlock.h"

/* Error checks to make sure configuration has been done properly */
#if !defined(RV_OSMEM_TYPE) || ((RV_OSMEM_TYPE != RV_OSMEM_MALLOC) && \
(RV_OSMEM_TYPE != RV_OSMEM_OSE) && (RV_OSMEM_TYPE != RV_OSMEM_NUCLEUS) && \
(RV_OSMEM_TYPE != RV_OSMEM_PSOS) && (RV_OSMEM_TYPE != RV_OSMEM_VXWORKS) && \
(RV_OSMEM_TYPE != RV_OSMEM_SYMBIAN) && (RV_OSMEM_TYPE != RV_OSMEM_RTK) && (RV_OSMEM_TYPE != RV_OSMEM_OSA))
#error RV_OSMEM_TYPE not set properly
#endif
/* End of configuration error checks */

/* Module specific error codes (-512..-1023). See rverror.h dor more details */

#if defined(__cplusplus)
extern "C" {
#endif

#if (RV_OSMEM_TYPE == RV_OSMEM_PSOS)
/* Forward declaration needed in RvOsMemData */
typedef struct RvOsMemPsosPool_s RvOsMemPsosPool;
#endif

/* Driver specific region data definition */
typedef struct {
#if (RV_MEMORY_KEEPSTATS != RV_YES) && (RV_OSMEM_TYPE != RV_OSMEM_PSOS)
	RvInt dummy; /* make sure structure isn't empty even if its not being used */
#endif
#if (RV_MEMORY_KEEPSTATS == RV_YES)
	/* These fields are only used for collecting statistics */
	RvLock lock;                 /* Lock on statistics data */
	RvSize_t overhead;           /* Overhead that rvmemory asked for */
	RvSize_t allocs_requested;   /* Number allocs not yet free'd */
	RvSize_t bytes_requested;    /* Requested bytes alloc'd but not free'd */
	RvSize_t bytes_used;         /* Total bytes currently in use */
#endif
#if (RV_OSMEM_TYPE == RV_OSMEM_PSOS)
	RvOsMemPsosPool *mempools;   /* Array of memory pools */
	int numpools;                /* Number of memory pools */
	unsigned long segment_size;  /* Segment size of pSOS region (power of 2 >= 16) */
	unsigned long psos_region;   /* pSOS region ID to get segments from */
#if (RV_MEMORY_KEEPSTATS == RV_YES)
	RvSize_t region_bytes_used;  /* bytes allocated directly from the region */
#endif
#endif
} RvOsMemData;

/* Prototypes and macros */

/********************************************************************************************
 * RvOsMemInit - Initializes the OsMem module.
 *
 * Must be called once (and only once) before any other functions in the module are called.
 *
 * INPUT   : none
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvOsMemInit(void);

/********************************************************************************************
 * RvOsMemEnd - Shuts down the OsMem module.
 *
 * Must be called once (and only once) when no further calls to this module will be made.
 *
 * INPUT   : none
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvOsMemEnd(void);

/********************************************************************************************
 * RvOsMemConstruct - Creates a driver memory region. 
 *
 * If statistic information is required - initializes the statistics area and constructs
 * a lock to protect this area.
 *
 * INPUT   : start	   	  - Starting address of region (ignored).
 *			 size		  - Size to use for region (ignored).
 *           overhead     - RvMemory overhead (used only when statistics is on).
 *			 moremem	  - Memory region to get additional memory from (ignored).
 *			 attr		  - Region attributes (ignored).
 * OUTPUT  : region		  - Pointer to object where region information will be stored.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvOsMemConstruct(
    IN  void*        start,
    IN  RvSize_t     size,
    IN  RvSize_t     overhead,
    IN  RvMemory*    moremem,
    IN  void*        attr,
    OUT void*        driverRegion);

/********************************************************************************************
 * RvOsMemDestruct - Destroys a system driver memory region.
 *
 * If statistic information is required - destructs the statistics area and its lock.
 *
 * INPUT   : driverRegion - Pointer to the region object to be destroyed.
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvOsMemDestruct(
    IN void*        driverRegion);

/********************************************************************************************
 * RvOsMemAlloc - Allocates memory from a system driver region.
 *
 * Use the underlying OS services to allocate a block of memory from the system heap.
 *
 * INPUT   : driverRegion - Pointer to the region object.
 *			 size		  - Number of bytes of memory needed.
 * OUTPUT  : result       - Pointer to where the resulting memory pointer will be stored.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvOsMemAlloc(
    IN  void*       driverRegion,
    IN  RvSize_t    size,
    OUT void**      result);

/********************************************************************************************
 * RvOsMemFree - Frees a memory which was allocated from a system driver region.
 *
 * Use the underlying OS services to free a block of memory back to the system heap.
 *
 * INPUT   : driverRegion - Pointer to the region object.
 *           ptr          - Pointer to the allocated memory to be released.
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvOsMemFree(
    IN  void*       driverRegion,
    IN  void*       ptr);

/********************************************************************************************
 * RvOsMemGetInfo - Returns the collected statistic information about a memory region.
 *
 * INPUT   : driverRegion - Pointer to the region object where statistic data is stored.
 * OUTPUT  : result       - Pointer to RvMemoryInfo structure where the statistic data
 *                          will be copied into.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvOsMemGetInfo(
    IN  void*           driverRegion,
    OUT RvMemoryInfo*   meminfo);

#if defined(__cplusplus)
}
#endif

#endif
