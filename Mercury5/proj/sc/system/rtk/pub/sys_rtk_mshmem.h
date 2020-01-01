/** @file sys_rtk_mshmem.h
 * @author Piazza.Lo
 * @date 04/24/2009
 *
 * Handle based OS memory interface.
 */

#ifndef __SYS_RTK_MSHMEM_H__
#define __SYS_RTK_MSHMEM_H__

#include "sys_rtk_ho.h"

/************************************************************************/
/*                                                   Macros                                                              */
/************************************************************************/
#define SIZE_OF_MAGICBEG		4
#define SIZE_OF_MAGICEND		4

#define MSHMEM_CACHE_DEFAULT        0
#define MSHMEM_CACHE_WRITEBACK      1
#define MSHMEM_CACHE_WRITETHROUGH   2
#define MSHMEM_CACHE_NONCACHED      3

/************************************************************************/
/*                                                   Types                                                               */
/************************************************************************/
typedef struct MemHandle_t_
{
	u32 MagicBegin;	//Identifier, used to protect hangle structure
	u32 Flag;
	void *pBody;	//pointer to the begining position of heap
	void *pEnd;	//point to buffer end
	struct MemHandle_t_ *pPrev;	//point to previous handle
	struct MemHandle_t_ *pNext;	//point to next handle
	u32 owner;	//the handle's owner
	u32 freeer;	//freeer
	void *pVMA;
	rtk_memoryContext_t rtkCtxt;	//RTK memory APIs' specific structure
	u32 MagicEnd;	//Identifier, used to protect hangle structure
} MemHandle_t, *pMemHandle_t;

typedef struct
{
    u16 ClusterNum;	//the number of clusters
    u16 ClusterSize;	//the cluster size
} gpDesc_t, *pgpDesc_t;

typedef struct
{
    u16 ClusterSize;
    u16 ClusterNum;
    u16 CurrUsedClusters;	//the current used number of clusters
    u16 MaxUsedClusters;	//the maximum used number of clusters
} gpStatus_t, *pgpStatus_t;

typedef struct
{
    u32 TotalFreeSize;
    u32 TotalFreeBlks;
    u32 MaxFreeSize;
    u32 TotalAllocSize;
    u32 MaxTotalAllocSize;
    u32 TotalAllocBlks;
    u32 TopFreeSize;
    u32 MemOverhead;
} ghStatus_t, *pghStatus_t;

typedef enum
{
    VMA_PAGE_1K = 0,
    VMA_PAGE_4K,
    VMA_PAGE_64K,
    VMA_PAGE_NUM
} HMVMAPageSize_e;

typedef struct
{
    u32 size;
    void *next;
} HMVMB_t;

/************************************************************************/
/*                                                  Functions                                                           */
/************************************************************************/

/**
 * @brief Runtime library initialize.
 * @param None.
 * @return None.
 */
extern void MsHMEMRtInit(void);


/**
 * @brief Runtime library deinitialize.
 * @param None.
 * @return None.
 */
extern void MsHMEMRtDeinit(void);


/**
 * @brief Profile memory usage of all handles in handle table.
 * @param None.
 * @return u32 the number of toal handles.
 */
extern u32 MsHMEMProfiling(void);


/**
 * @brief Create handle with a fully heap.
 * @param[in] pBuf pointer to buffer.
 * @param[in] nBufSize buffer size.
 * @return int a handle if success or 0 once failed.
 */
extern u32 MsHMEMCreate(void* pBuf, u32 nBufSize);


/**
 * @brief Close a handle.
 * @param[in] Handle the memory handle.
 * @return None.
 */
extern void MsHMEMClose(u32 Handle);


/** @defgroup PoolMgt Pool management
 * @{
 */

/**
 * @brief Initialize a pool.
 * @param[in] Handle the memory handle.
 * @param[in] pDesc pointer to a desction table.
 * @param[in] nPoolNum the number of pool clusters.
 * @return s32 status.
 */
extern s32 MsHMEMInitializePool(u32 Handle, pgpDesc_t pDesc, u32 nPoolNum);


/**
 * @brief Get a pool memory with a given return address.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMGetPoolMemory(u32 Handle, u32 nMemSize, u32 lr);


/**
 * @brief Get a zero-initialization pool memory with a given return address.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMGetCPoolMemory(u32 Handle, u32 nMemSize, u32 lr);


/**
 * @brief Get a pool id memory with a given return address.
 * @param[in] Handle the memory handle.
 * @param[in] nPoolId the PoolId.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMGetPoolIdMemory(u32 Handle, u8 nPoolId, u32 lr);


/**
 * @brief Get a zero-initialization pool id memory with a given return address.
 * @param[in] Handle the memory handle.
 * @param[in] nPoolId the PoolId.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMGetPoolIdMemory(u32 Handle, u8 nPoolId, u32 lr);


/**
 * @brief Release the stack pool memory.
 * @param[in] pMem pointer to memory.
 * @param[in] lr return address.
 * @return s32 status.
 */
extern s32 MsHMEMReleasePoolMemory(void *pMem, u32 lr);


/**
 * @brief Release the pool memory.
 * @param[in] pMem pointer to memory.
 * @param[in] lr return address.
 * @return s32 status.
 */
extern s32 MsHMEMReleasePoolMemoryLr(void *pMem, u32 lr);


/**
 * @brief Find the best pool id according the specified size.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[out] pPoolId pointer to pool id.
 * @return s32 status.
 */
extern s32 MsHMEMFindBestPool(u32 Handle, u32 nMemSize, u8 *pPoolId);


/**
 * @brief Reuse a given memory in the pool.
 * @param[in] pMem pointer to memory.
 * @return s32 status.
 */
extern s32 MsHMEMLinkPoolMemory(void *pMem);


/**
 * @brief Check whether the memory is from pool or not.
 * @param[in] pMem pointer to memory.
 * @return bool true if yes, or false.
 */
extern bool MsHMEMIsPoolMemory(void *pMem);


/**
 * @brief Check whether the memory from pool is valid or not.
 * @param[in] pMem pointer to memory.
 * @return bool true if yes, or false.
 */
extern bool MsHMEMCheckPoolMemory(void *pMem);


/**
 * @brief Query the number of pool.
 * @param[in] Handle the memory handle.
 * @return s32 status.
 */
extern s32 MsHMEMQueryPoolNumber(u32 Handle);


/**
 * @brief Query the pool status.
 * @param[in] Handle the memory handle.
 * @param[in] nPoolId the PoolId.
 * @param[in] pStatus pointer to query status.
 * @return s32 status.
 */
extern s32 MsHMEMQueryPoolStatus(u32 Handle, u8 nPoolId, pgpStatus_t pStatus);


/**
 * @brief Report the pool status.
 * @param[in] Handle the memory handle.
 * @return s32 status.
 */
extern s32 MsHMEMReportPoolStatus(u32 Handle);


/* @} */


/** @defgroup HeapMgt Heap management
 * @{
 */


/**
 * @brief Get a heap memory with a given return address.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMGetHeapMemory(u32 Handle, u32 nMemSize, u32 lr);


/**
 * @brief Get a zero-initialization heap memory with a given return address.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMGetCHeapMemory(u32 Handle, u32 nMemSize, u32 lr);


/**
 * @brief Get a heap memory with a given return address.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] nAligned the aligned byte from 0 ~ 15 (means 2^0 ~ 2^15).
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMGetHeapMemoryExt(u32 Handle, u32 nMemSize, u8 nAligned, u32 lr);


/**
 * @brief Get a heap memory with a given return address or trap once failed.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMGetHeapMemoryTrapOnNull(u32 Handle, u32 nMemSize, u32 lr);


/**
 * @brief Reuse a given memory in the heap.
 * @param[in] pMem pointer to memory.
 * @return s32 status.
 */
extern s32 MsHMEMLinkHeapMemory(void *pMem);


/**
 * @brief Release the heap memory.
 * @param[in] pMem pointer to memory.
 * @param[in] lr return address.
 * @return s32 status.
 */
extern s32 MsHMEMReleaseHeapMemory(void *pMem, u32 lr);


/**
 * @brief Check whether the memory is from heap or not.
 * @param[in] pMem pointer to memory.
 * @return bool true if yes, or false.
 */
extern bool MsHMEMIsHeapMemory(void *pMem);



/**
 * @brief Check whether the memory from heap is valid or not.
 * @param[in] pMem pointer to memory.
 * @return bool true if yes, or false.
 */
extern bool MsHMEMCheckHeapMemory(void *pMem);


/**
 * @brief Reallocate a heap memory.
 * @param[in] Handle the memory handle.
 * @param[in] pMem pointer to memory.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMHeapRealloc(u32 Handle, void *pMem, u32 nMemSize, u32 lr);


/**
 * @brief Allocate a memory from heap.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMMalloc(u32 Handle, u32 nMemSize, u32 lr);


/**
 * @brief Allocate a physical memory from pool or heap.
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMPMalloc(u32 Handle, u32 nMemSize, u32 lr);


/**
 * @brief Reallocate a memory from pool or heap.
 * @param[in] Handle the memory handle.
 * @param[in] pMem pointer to old memory.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMRealloc(u32 Handle, void* pMem, u32 nMemSize, u32 lr);


/**
 * @brief Allocate a zero-initialization memory from pool or heap
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @param[in] lr return address.
 * @return void* pointer to memory.
 */
extern void* MsHMEMCalloc(u32 Handle, u32 nMemSize, u32 lr);


/**
 * @brief Free the memory of pool or heap.
 * @param[in] pMem pointer to memory.
 * @param[in] lr return address.
 * @return s32 status.
 */
extern s32 MsHMEMFree(void *pMem, u32 lr);


/**
 * @brief Reuse a given memory in a pool or a heap.
 * @param[in] pMem pointer to memory.
 * @return s32 status.
 */
extern s32 MsHMEMLinkMemory(void *pMem);


/**
 * @brief Query the heap status.
 * @param[in] Handle the memory handle.
 * @param[in] pStatus pointer to query status.
 * @return s32 status.
 */
extern s32 MsHMEMQueryHeapStatus(u32 Handle, pghStatus_t pStatus);


/**
 * @brief Report the heap status.
 * @param[in] Handle the memory handle.
 * @return s32 status.
 */
extern s32 MsHMEMReportHeapStatus(u32 Handle);

/**
 * \brief Translate virtual address into physical address
 * @param[in] pMem pointer to virtual memory.
 * @return void* pointer to physical memory.
 */
void* MsHMEMVA2PA(void *pMem);


/**
 * \brief Translate physical address into virtual address
 * @param[in] pMem pointer to physical memory.
 * @return void* pointer to virtual memory.
 */
void* MsHMEMPA2VA(void *pMem);


/**
 * \brief Check whether memory is in VMA range
 * @param[in] pMem pointer to physical memory.
 * @return bool TRUE or FALSE
 */
bool MsHMEMIsInVMA(void *pMem);


/**
 * @brief Create a vma manager.
 * @param[in] Handle the memory handle.
 * @param[in] nVstart virtual start address.
 * @param[in] nSize the range of virtual address.
 * @param[in] nPageSize the page size using on mmu.
 * @return bool success or fail.
 */
extern bool MsHMEMVMACreate(u32 Handle, u32 nVstart, u32 nSize, HMVMAPageSize_e nPageSize);


/**
 * @brief Destroy the vma manager.
 * @param[in] Handle the memory handle.
 * @return void.
 */
extern void MsHMEMVMADestroy(u32 Handle);


/**
 * @brief Get vma related info.
 * @param[in] Handle the memory handle.
 * @param[out] *nSucc the success count.
 * @param[out] *nFail the fail count.
 * @return void.
 */
extern void MsHMEMVMAGetInfo(u32 Handle, u32 *nSucc, u32 *nFail);

/* @} */


/**
 * @brief Release the memory and return a zero memory pointer.
 * @param[in|out] pMem pointer to memory.
 * @param[in] lr return address.
 * @param[in] f Release function pointer.
 * @return s32 status.
 */
extern s32 MsHMEMReleaseMemoryDiagnose(void **pMem, u32 lr, s32 (*f)(void *, u32));


/**
 * @brief Get the real size of a given memory pointer.
 * @param[in] pMem pointer to memory.
 * @return u32 Real size.
 */
extern u32 MsHMEMQueryMemoryRealSize(void* pMem);

#ifdef __SDK_SIMULATION__
extern void *MEMCPY_S(void *s1, const void *s2, u32  n);
#endif

/**
 * @brief Reset memory monitor data.
 */
extern void MsHMEMResetMemoryStatus(void);

/**
 * @brief Print out log for memory status (Peak).
 */
extern void MsHMEMShowMemoryStatus(void);

/**
 * @brief Walk the vmalloc'd pointer to get detail information of each block.
 * @param[in] pMem pointer to a virtual memory.
 * @param[in|out] pVmb detail information.
 * @return void* The corresponding physical address of the pMem.
 */
extern void *MsHMEMVMAWalk(void *pMem, HMVMB_t *pVmb);

/**
 * @brief Get the number of blocks of vmalloc'd pointer.
 * @param[in] pMem pointer to a virtual memory.
 * @return u32 The number of blocks.
 */
extern u32 MsHMEMVMAGetBlockCount(void *pMem);

/**
 * @brief Quickly peek the biggest free block in handle
 * @param[in] Handle the memory handle.
 * @param[in] nMemSize the requested memory size.
 * @return None* pointer to memory.
 */
extern void *MsHMEMPeekAlloc(u32 Handle, u32 nMemSize);

/**
 * @brief Quickly free the biggest peeked free block in handle
 * @param[in] Handle the memory handle.
 * @return None.
 */
extern void MsHMEMPeekFree(u32 Handle);

#endif //__SYS_RTK_MSHMEM_H__

