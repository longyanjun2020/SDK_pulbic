
//==============================================================================
/**
 @file ahc_mempoolfixedsize.h
 @brief AHC Memory Pool with fixed chunk size
 @author Caesar Chang
 @version 1.0
*/

#ifndef __AHC_MEMORY_POOL_WITH_FIXED_SIZE_H__
#define __AHC_MEMORY_POOL_WITH_FIXED_SIZE_H__
#include "ahc_common.h"
#include "ahc_os.h"

/*******************************************************************************
 *
 *   DEFINITIONS
 *
*******************************************************************************/
#define MEMPOOLFIXEDSIZE_ALIGN_SIZE		4
#define MEMPOOLFIXEDSIZE_TAG			0x5346504D

#ifndef NULL
#define NULL 0
#endif

/*******************************************************************************
 *
 *   TYPE DEFINITIONS
 *
*******************************************************************************/

typedef struct tagSMEMPOOLFIXEDSIZE
{
	UINT uiTag;
	UINT uiTotalChunks;
	int  nUsedChunks;

	UINT uiLastAllocPos;

	UINT uiChunkSize;
	UINT uiChunkBitmapSize;	

	PULONG pulChunkBitmap;
	PBYTE  pbyChunkStart;
    AHC_OS_SEMID smLock;

}SMEMPOOLFIXEDSIZE,*PSMEMPOOLFIXEDSIZE;

/*******************************************************************************
 *
 *   FUNCTIONS
 *
*******************************************************************************/

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_LockInit
 *
 *   DESCRIPTION
 *
 *      Init the locker of the memory pool
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_LockInit(PSMEMPOOLFIXEDSIZE hPool);

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_LockUninit
 *
 *   DESCRIPTION
 *
 *      Uninitialize the memory pool.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_LockUninit(PSMEMPOOLFIXEDSIZE hPool);
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_LockEx
 *
 *   DESCRIPTION
 *
 *      Lock pool for finite time waiting
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_LockEx(PSMEMPOOLFIXEDSIZE hPool, UINT32 uiTimeOutTick );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Lock
 *
 *   DESCRIPTION
 *
 *      Lock pool
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_Lock(PSMEMPOOLFIXEDSIZE hPool );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Unlock
 *
 *   DESCRIPTION
 *
 *      Unlock the pool.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_Unlock(PSMEMPOOLFIXEDSIZE hPool);

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_InitPool
 *
 *   DESCRIPTION
 *
 *      Initialize memory pool with fixed chunk size.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
PSMEMPOOLFIXEDSIZE AHC_MemPoolFS_InitPool(PBYTE pbyBuffer, UINT uiPoolSize, UINT uiChunkSize );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_UninitPool
 *
 *   DESCRIPTION
 *
 *      Unitialize memory pool with fixed chunk size.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_UninitPool(PSMEMPOOLFIXEDSIZE hPool );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Alloc
 *
 *   DESCRIPTION
 *
 *      Allocate a memory chunk.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
void* AHC_MemPoolFS_Alloc(PSMEMPOOLFIXEDSIZE hPool);

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Calloc
 *
 *   DESCRIPTION
 *
 *      Allocate a chunk and set the all data in buffer to zero.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
void* AHC_MemPoolFS_Calloc(PSMEMPOOLFIXEDSIZE hPool);
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Free
 *
 *   DESCRIPTION
 *
 *      Free an allocated chunk
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_Free(PSMEMPOOLFIXEDSIZE hPool, void* pbyBuffer );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Dump
 *
 *   DESCRIPTION
 *
 *      Dump the memory pool.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_Dump(PSMEMPOOLFIXEDSIZE hPool);

#endif // __AHC_MEMORY_POOL_WITH_FIXED_SIZE_H__
