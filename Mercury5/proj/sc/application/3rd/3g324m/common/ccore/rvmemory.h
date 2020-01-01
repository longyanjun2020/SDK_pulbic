/***********************************************************************
Filename   : rvmemory.h
Description: rvmemory header file
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

/***********************************************************************
 *	DESCRIPTION:
 *		This module provides memory management functions with plug-in
 *		drivers to supports various memory management schemes.
 ***********************************************************************/
#ifndef RV_MEMORY_H
#define RV_MEMORY_H

#include "rvccore.h"
#include "rvobjlist.h"

#if (RV_MEMORY_DEBUGINFO == RV_YES)
#include "rvlock.h"
#endif

/* Forward declarations so it can be used by memory driver headers */
typedef struct RvMemory_s RvMemory;
typedef struct RvMemoryInfo_s RvMemoryInfo;
typedef struct RvMemoryDriverFuncs_s RvMemoryDriverFuncs; /* Currently used internally only. */

/* Memory driver header includes. Driver headers should insure that */
/* their headers are completely read in before this header is parsed. */
#include "rvosmem.h"
#include "rvpoolmem.h"

/* Error checks to make sure configuration has been done properly */
#if !defined(RV_MEMORY_TYPE) || ((RV_MEMORY_TYPE != RV_MEMORY_STANDARD) && (RV_MEMORY_TYPE != RV_MEMORY_POOL))
#error RV_MEMORY_TYPE not set properly
#endif

#if !defined(RV_MEMORY_MAX_NAMESIZE) || (RV_MEMORY_MAX_NAMESIZE < 1)
#error RV_MEMORY_MAX_NAMESIZE not set properly
#endif

#if !defined(RV_MEMORY_KEEPSTATS) || ((RV_MEMORY_KEEPSTATS != RV_NO) && (RV_MEMORY_KEEPSTATS != RV_YES))
#error RV_MEMORY_KEEPSTATS not set properly
#endif

#if !defined(RV_MEMORY_DEBUGINFO) || ((RV_MEMORY_DEBUGINFO != RV_NO) && (RV_MEMORY_DEBUGINFO != RV_YES))
#error RV_MEMORY_DEBUGINFO not set properly
#endif

#if !defined(RV_MEMORY_DEBUGCHECK) || ((RV_MEMORY_DEBUGCHECK != RV_NO) && (RV_MEMORY_DEBUGCHECK != RV_YES))
#error RV_MEMORY_DEBUGCHECK not set properly
#endif
/* End of configuration error checks */

/* Module specific error codes (-512..-1023). See rverror.h for more details */
#define RV_MEMORY_ERROR_DRIVERFAILED -512 /* requested driver not available due to failure */
#define RV_MEMORY_ERROR_OVERRUN -513 /* memory allocation boundry has been overrun */

/* *************IMPORTANT*******************                                           */
/* To add a new driver (other than writing and testing the module itself):                                                                */
/*    1. add header file to include list at the top of this file                       */
/*    2. Increment RV_MEMORY_NUMDRIVERS                                                */
/*    3. Add a RV_MEMORY_DRIVER_XXX constant to the ID list                            */
/*    4. Add a new type to the driverData union in RvMemory_s structure                */
/*    5. In the rvmemory.c file, add the driver functions to the RvMemoryDrivers array */
/*    6. In the rvmemory.c file, add a new item to the switch in RvMemoryConstruct     */
/* *****************************************                                           */

/* Max number of memory drivers */
#define RV_MEMORY_NUMDRIVERS 2

/* Memory Driver ID numbers */
#define RV_MEMORY_DRIVER_OSMEM 0   /* ID 0 is used for the default driver (OS mem) */
#define RV_MEMORY_DRIVER_POOLMEM 1

#if defined(__cplusplus)
extern "C" {
#endif

/********************************************************************************************
 * RvMemoryFunc - Out of memory callback.
 *
 * This callback is called when a memory region can not allocate the memory needed
 * for a memory allocation.
 *
 * INPUT   : n		-	The number of bytes needed.
 * OUTPUT  : None.
 * RETURN  : Return RV_OK if allocation attempt should be tried again. Returning
 *			an any error code will abort the memory allocation and return an
 *			error to the caller.
 */

typedef RvStatus (*RvMemoryFunc)(RvSize_t n);


/********************************************************************************************
 *	A structure containing information about a memory region. This structure is
 *	returned by the RvMemoryInfo command. Not all fields may be filled in (will
 *	show a value of 0) if the OS doesn't support it or the RV_MEMORY_STATISTICS
 *	option is not enabled. Most field are filled in by the driver itself. The actual typedef
 *	is above for forward declarations.
 *********************************************************************************************/
struct RvMemoryInfo_s {
	RvChar name[RV_MEMORY_MAX_NAMESIZE]; /* name of region (filled in by rvmemory) */
	RvInt drivernum;                     /* driver number of region (filled in by rvmemory) */
	RvSize_t bytes_requested_byuser;     /* # of bytes used, per user request */
	RvSize_t bytes_requested_bymem;      /* # of bytes used, including rvmemory layer overhead */
	RvSize_t bytes_requested_total;      /* # of bytes used, including all per allocation overhead */
	RvSize_t bytes_total_inuse;          /* Total number of bytes in use */
	RvSize_t allocs_requested;           /* number of actual allocations still in use */
	RvSize_t bytes_free_now;             /* # of bytes immediately available without asking for more */
	RvSize_t bytes_free_total;           /* Total number of bytes available */
	RvSize_t allocs_free_now;            /* # of actual allocations available */
	RvSize_t allocs_free_total;          /* Total number of actual allocations available */
};

/********************************************************************************************
 *
 *	RvMemory - A memory region object. Actual typedef is above for forward declarations.
 *
 *********************************************************************************************/
struct RvMemory_s {
	RvInt drivernum;                      /* driver number */
	RvChar name[RV_MEMORY_MAX_NAMESIZE];  /* Name of region */
	const RvMemoryDriverFuncs *drivercalls;/* pointer to driver functions (faster than indexing) */
	RvObjListElement listElem;            /* used to maintain list of current regions */
	void *start;                          /* starting address of region (if needed) */
	RvSize_t size;                        /* size of region (if needed) */
	RvMemory *moremem;                    /* region to request addional memory from (if needed) */
	RvMemoryFunc nomem;                   /* function to call when no additional memory available */
	void *driverRegion;                   /* pointer to driver specific region data in union (for speed) */
	union {                               /* driver specific data, MUST have one entry for each driver */
		RvOsMemData osMemData;
#if (RV_MEMORY_TYPE == RV_MEMORY_POOL)
		RvPoolMemData poolMemData;
#endif
	} driverData;
#if (RV_MEMORY_DEBUGINFO == RV_YES)
	RvObjList alloclist;                  /* List of blocks allocated from region */
	RvLock listlock;                      /* Lock use for alloclist. */
#endif
};


/********************************************************************************************
 *
 *									PROTOTYPES
 *
 *********************************************************************************************/

/********************************************************************************************
 * RvMemoryInit - inits Initializes the Memory module.
 *
 * Must be called once (and only once) before any other functions in the module are called.
 * A default region is created with the default driver.
 *
 * INPUT   : none
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvMemoryInit(void);

/********************************************************************************************
 * RvMemoryEnd - Shuts down the Memory module.
 *
 * Must be called once (and only once) when no further calls to this module will be made.
 * The default region is destroyed.
 *
 * INPUT   : none
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvMemoryEnd(void);


/********************************************************************************************
 * RvMemorySourceConstruct -Constructs memory module log source
 *
 * Constructs memory module log source for printing log per specific
 * log manager instance
 *
 * INPUT   : logMgr	- log manager instance
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvMemorySourceConstruct(
	IN RvLogMgr* logMgr);


/********************************************************************************************
 * RvMemoryConstruct - Creates a memory region.
 *
 * Different drivers may interpret some of the parameters
 * in different ways. Refer to those drivers for further information.
 * note:  A copy of the name string passed in is made. The maximum size of the
 *  	the string is RV_MEMORY_MAX_NAMESIZE and names that are too long
 *		will be truncated.
 *
 * INPUT   : drivernum	- Driver ID of memory allocation driver to use.
 *						See rvmemory.h for current list.
 *			 name		- Pointer to string name to use for this region (a copy will be made).
 *			 start		- Starting address of region (not used by all drivers).
 *			 size		- Size to use for region (driver specific).
 *			 moremem	- Memory region to get additional memory from (not used by all drivers).
 *			 nomem		- Callback function that will be called if no more memory can be
 *						aquired (NULL is allowed).
 *			 attr		- Driver specific parameters.
 *			 logMgr		- log manager instance
 * OUTPUT  : region		- Pointer to object where region information will be stored.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvMemoryConstruct(
	IN  RvInt			drivernum,
	IN  RvChar			*name,
	IN  void			*start,
	IN  RvSize_t		size,
	IN  RvMemory		*moremem,
	IN  RvMemoryFunc	nomem,
	IN  void			*attr,
	IN  RvLogMgr		*logMgr,
	OUT RvMemory		*region);


/********************************************************************************************
 * RvMemoryDestruct - Destroys a memory region.
 *
 *	note:  Some drivers allow destroying regions with outstanding allocations
 *		and some do not.
 *
 * INPUT   : region	-Pointer to the region object to be destroyed.
 *			 logMgr	- log manager instance
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvMemoryDestruct(
	IN RvMemory *region,
	IN RvLogMgr	*logMgr);


/********************************************************************************************
 * RvMemoryFree - Returns allocated memory back to region it came from.
 *
 * INPUT   : ptr			- Pointer to allocated memory. Must be the same pointer returned
 *							by rvMemoryAlloc.
 *			 logMgrParam	- log manager instance
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvMemoryFree(
	IN void		*ptr,
	IN RvLogMgr	*logMgrParam);


/********************************************************************************************
 * RvMemoryGetInfo - Returns statistics about a memory region.
 *
 * INPUT   : reqregion	- Pointer to the region to request information from
 *						(NULL = default region).
 * OUTPUT  : memory		- Pointer to a structure which will be filled in with the statistics.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RVCOREAPI
RvStatus RVCALLCONV RvMemoryGetInfo(
	IN  RvMemory		*reqregion,
	IN  RvLogMgr	    *logMgr,
	OUT RvMemoryInfo	*meminfo);


/********************************************************************************************
 * RvMemorySetDefaultMemCB - Sets an out of memory callback for the default region.
 *
 * INPUT   : func	- Out of memory callback (NULL = none).
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvMemorySetDefaultMemCB(
	IN RvMemoryFunc func);


/********************************************************************************************
 * RvMemoryGetDefaultMemCB - Gets the current out of memory callback for the default region.
 *
 * INPUT   : none
 * OUTPUT  : func	- Function pointer where the callback pointer is stored
 *					(result can be NULL).
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvMemoryGetDefaultMemCB(
	OUT RvMemoryFunc *func);


/********************************************************************************************
 * RvMemoryAlloc - Allocates memory from a region.
 *
 * INPUT   : reqregion	- Pointer to the region to request the memory from (NULL =
 *						default region).
 *			 size		- Number of bytes of memory needed.
 *			 logMgr		- log manager instance
 * OUTPUT  : resultptr	- Pointer to where the resulting memory pointer will be stored.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
#if (RV_MEMORY_DEBUGINFO == RV_NO)
RVCOREAPI
RvStatus RVCALLCONV RvMemoryAlloc(
	IN  RvMemory		*reqregion,
	IN  RvSize_t		size,
	IN  RvLogMgr		*logMgr,
	OUT void			**resultptr);
#else
/* Special Alloc for debugging */
#define RvMemoryAlloc(_r, _s, _l, _p) RvMemoryAllocDbg((_r), (_s), __LINE__, __FILE__, (_l), (_p))
RVCOREAPI
RvStatus RVCALLCONV RvMemoryAllocDbg(
	IN  RvMemory	*reqregion,
	IN  RvSize_t	size,
	IN  RvInt		line,
	IN  const RvChar *filename,
	IN  RvLogMgr	*logMgr,
	OUT void		**resultptr);
#endif

#if RV_MEMORY_DEBUGINFO == RV_YES

RVCOREAPI
RvStatus RVCALLCONV RvMemoryPrintDbg(
	IN  RvMemory	*reqregion,
    IN  RvLogMgr    *logMgr);

#else

/* We don't want to make using RvMemoryPrintDbg illegal even if RV_MEMORY_DEBUGINFO != RV_YES
 *  - it may demand changing code that uses RvMemoryPrintDbg.
 * So, if RV_MEMORY_DEBUGINFO != RV_YES - just return RV_ERROR_NOTSUPPORTED
 */
#define RvMemoryPrintDbg(reqregion, logMgr) ((void)(reqregion), (void)(logMgr), RV_ERROR_NOTSUPPORTED)

#endif

#if RV_MEMORY_DEBUGCHECK == RV_YES

RVCOREAPI
RvStatus RVCALLCONV RvMemoryCheckOverrun(
	IN void		*ptr,
	IN RvLogMgr	*logMgrParam);

#else

/* We don't want to make using RvMemoryPrintDbg illegal even if RV_MEMORY_DEBUGCHECK != RV_YES
 *  - it may demand changing code that uses RvMemoryPrintDbg.
 * So, if RV_MEMORY_DEBUGCHECK != RV_YES - just return RV_ERROR_NOTSUPPORTED
 */
#define RvMemoryCheckOverrun(ptr, logMgr) ((void)(ptr), (void)(logMgr), RV_ERROR_NOTSUPPORTED)

#endif


#if defined(__cplusplus)
}
#endif

#endif
