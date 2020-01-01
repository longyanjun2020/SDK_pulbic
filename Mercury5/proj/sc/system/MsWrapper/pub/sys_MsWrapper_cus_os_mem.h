#ifndef __SYS_MSWRAPPER_CUS_OS_MEM_H__
#define __SYS_MSWRAPPER_CUS_OS_MEM_H__

#include "sys_rtk_mshmem.h"

/** \addtogroup MemMan
 *  @{
 */

/**
 * \def MsAllocateMem(X)
 * \brief It allocates a memory from pool first, or heap if it fails to allocate from pool
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsAllocateMem(X)                          MsAllocateMemLr(X, 0)
/**
 * \def MsAllocateMemLr(X, Y)
 * \brief It allocates a memory from pool first, or heap if it fails to allocate from pool
 * \param[in] X The requested memory size.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsAllocateMemLr(X, Y)                   MsHMEMMalloc(ms_memoryhandle, X, Y)
/**
 * \def MsPMalloc(X)
 * \brief It allocates memory from heap, and the mapping always in 1-1 physical domain which is suitable for DMA operation
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsPMalloc(X)       	                         MsPMallocLr(X, 0)
/**
 * \def MsPMallocLr(X, Y)
 * \brief It allocates memory from heap, and the mapping always in 1-1 physical domain which is suitable for DMA operation
 * \param[in] X The requested memory size.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsPMallocLr(X, Y)	                         MsHMEMPMalloc(ms_memoryhandle, X, Y)
/**
 * \def MsMemoryReAllocate(X, Y)
 * \brief It reallocates a memory from pool first, or heap if it fails to reallocate from pool
 * \param[in] X Pointer to old memory
 * \param[in] Y The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsMemoryReAllocate(X, Y)            MsMemoryReAllocateLr(X, Y, 0)
/**
 * \def MsMemoryReAllocateLr(X, Y, Z)
 * \brief It reallocates a memory from pool first, or heap if it fails to reallocate from pool
 * \param[in] X Pointer to old memory.
 * \param[in] Y The requested memory size.
 * \param[in] Z The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsMemoryReAllocateLr(X, Y, Z)     MsHMEMRealloc(ms_memoryhandle, X, Y, Z)
/**
 * \def MsCallocateMem(X)
 * \brief It allocates a zero-initialization memory from pool first, or heap if it fails to allocate from pool
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsCallocateMem(X)                        MsCallocateMemLr(X, 0)
/**
 * \def MsCallocateMemLr(X, Y)
 * \brief It allocates a zero-initialization memory from pool first, or heap if it fails to allocate from pool
 * \param[in] X The requested memory size.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsCallocateMemLr(X, Y)                 MsHMEMCalloc(ms_memoryhandle, X, Y)
/**
 * \def MsLinkMemory(X)
 * \brief It reuses a given memory in a pool or a heap
 * \param[in] X Pointer to memory.
 * \return Error code.
 */
#define MsLinkMemory(X)                           MsHMEMLinkMemory(X)
/**
 * \def MsGetPoolMemory(X)
 * \brief It allocates a memory from pool
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetPoolMemory(X)                     MsGetPoolMemoryLr(X, 0)
/**
 * \def MsGetPoolMemoryLr(X, Y)
 * \brief It allocates a memory from pool
 * \param[in] X The requested memory size.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetPoolMemoryLr(X, Y)              MsHMEMGetPoolMemory(ms_memoryhandle, X, Y)
/**
 * \def MsGetCPoolMemory(X)
 * \brief It allocates a zero-initialization memory from pool
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetCPoolMemory(X)                    MsGetCPoolMemoryLr(X, 0)
/**
 * \def MsGetCPoolMemoryLr(X, Y)
 * \brief It allocates a zero-initialization memory from pool
 * \param[in] X The requested memory size.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetCPoolMemoryLr(X, Y)             MsHMEMGetCPoolMemory(ms_memoryhandle, X, Y)
/**
 * \def MsGetPoolIdMemory(X)
 * \brief It allocates a memory from pool with a given specific pool id
 * \param[in] X The requested pool id.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetPoolIdMemory(X)                  MsGetPoolIdMemoryLr(X, 0)
/**
 * \def MsGetPoolIdMemoryLr(X, Y)
 * \brief It allocates a memory from pool with a given specific pool id
 * \param[in] X The requested pool id.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetPoolIdMemoryLr(X, Y)          MsHMEMGetPoolIdMemory(ms_memoryhandle, X, Y)
/**
 * \def MsGetCPoolIdMemory(X)
 * \brief It allocates a zero-initialization memory from pool with a given specific pool id
 * \param[in] X The requested pool id.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetCPoolIdMemory(X)                MsGetCPoolIdMemoryLr(X, 0)
/**
 * \def MsGetCPoolIdMemoryLr(X, Y)
 * \brief It allocates a zero-initialization memory from pool with a given specific pool id
 * \param[in] X The requested pool id.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetCPoolIdMemoryLr(X, Y)         MsHMEMGetCPoolIdMemory(ms_memoryhandle, X, Y)
/**
 * \def MsGetHeapMemory(X)
 * \brief It allocates a memory from heap
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetHeapMemory(X)                    MsGetHeapMemoryLr(X, 0)
/**
 * \def MsGetHeapMemoryLr(X, Y)
 * \brief It allocates a memory from heap
 * \param[in] X The requested memory size.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetHeapMemoryLr(X, Y)             MsHMEMGetHeapMemory(ms_memoryhandle, X, Y)
/**
 * \def MsGetCHeapMemory(X)
 * \brief It allocates a zero-initialization memory from heap
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetCHeapMemory(X)                  MsGetCHeapMemoryLr(X, 0)
/**
 * \def MsGetCHeapMemoryLr(X, Y)
 * \brief It allocates a zero-initialization memory from heap
 * \param[in] X The requested memory size.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetCHeapMemoryLr(X, Y)           MsHMEMGetCHeapMemory(ms_memoryhandle, X, Y)
/**
 * \def MsGetHeapMemoryExt(X, Y, Z)
 * \brief It allocates a memory from heap, with head ptr alignment constriant
 * \param[in] X The requested memory size.
 * \param[in] Y The aligned field, for ex, 12 denotes 4KB align in head ptr
 * \param[in] Z The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetHeapMemoryExt(X, Y, Z)       MsHMEMGetHeapMemoryExt(ms_memoryhandle, X, Y, Z)
/**
 * \def MsHeapRealloc(X)
 * \brief It reallocates a memory from heap
 * \param[in] X Pointer to old memory.
 * \param[in] Y The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsHeapRealloc(X, Y)                       MsHeapReallocLr(X, Y, 0)
/**
 * \def MsHeapReallocLr(X, Y, Z)
 * \brief It reallocates a memory from heap
 * \param[in] X Pointer to old memory.
 * \param[in] Y The requested memory size.
 * \param[in] Z The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsHeapReallocLr(X, Y, Z)                MsHMEMHeapRealloc(ms_memoryhandle, X, Y, Z)
/**
 * \def MsReleaseHeapMemory(X)
 * \brief It frees a memory which is allocated from heap
 * \param[in] X Pointer to memory.
 * \return Error code.
 */
#define MsReleaseHeapMemory(X)             MsReleaseHeapMemoryLr(X, 0)
/**
 * \def MsReleaseHeapMemoryLr(X, Y)
 * \brief It frees a memory which is allocated from heap
 * \param[in] X Pointer to memory.
 * \param[in] Y The rcaller address.
 * \return Error code.
 */
#define MsReleaseHeapMemoryLr(X, Y)      MsHMEMReleaseMemoryDiagnose((void**)&(X), Y, MsHMEMReleaseHeapMemory)
/**
 * \def MsReleaseMemory(X)
 * \brief It frees a memory which is allocated from pool or heap
 * \param[in] X Pointer to memory.
 * \return Error code.
 */
#define MsReleaseMemory(X)                     MsReleaseMemoryLr(X, 0)
/**
 * \def MsReleaseMemoryLr(X, Y)
 * \brief
 * \param[in] X Pointer to memory.
 * \param[in] Y The caller address.
 * \return Error code.
 */
#define MsReleaseMemoryLr(X, Y)              MsHMEMReleaseMemoryDiagnose((void**)&(X), Y, MsHMEMFree)
/**
 * \def MsIsPoolMemory(X)
 * \brief It checks whether the memory is from pool or not
 * \param[in] X Pointer to memory.
 * \return If success return TRUE, or FALSE.
 */
#define MsIsPoolMemory(X)                       MsHMEMIsPoolMemory(X)
/**
 * \def MsIsHeapMemory(X)
 * \brief It checks whether the memory is from heap or not
 * \param[in] X Pointer to memory.
 * \return If success return TRUE, or FALSE.
 */
#define MsIsHeapMemory(X)                      MsHMEMIsHeapMemory(X)
/**
 * \def MsQueryMemRealSize(X)
 * \brief It gets the real size of a given memory pointer
 * \param[in] X Pointer to memory.
 * \return Real size.
 */
#define MsQueryMemRealSize(X)               MsHMEMQueryMemoryRealSize(X)
/**
 * \def MsFindBestPool(X, Y)
 * \brief It finds the best pool id according the specified size
 * \param[in] X The requested memory size.
 * \param[in] Y The requested pool id.
 * \return Error code
 */
#define MsFindBestPool(X, Y)                      MsHMEMFindBestPool(ms_memoryhandle, X, Y)
/**
 * \def MsQueryPoolNumber()
 * \brief It queries the number of pools from system handle
 * \return The number of pools
 */
#define MsQueryPoolNumber()                  MsHMEMQueryPoolNumber(ms_memoryhandle)

#if defined(__IRAM_ALLOC__)
/**
 * \def MsGetIramMemory(X)
 * \brief It allocates a memory from internal RAM
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetIramMemory(X)                   MsHMEMGetHeapMemory(ms_iramhandle, X, 0)
/**
 * \def MsGetIramMemoryLr(X,Y)
 * \brief It allocates a memory from internal RAM
 * \param[in] X The requested memory size.
 * \param[in] Y The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetIramMemoryLr(X,Y)               MsHMEMGetHeapMemory(ms_iramhandle,X,Y)
/**
 * \def MsGetIramMemoryExt(X, Y, Z)
 * \brief It allocates a memory from heap, with head ptr alignment constriant
 * \param[in] X The requested memory size.
 * \param[in] Y The aligned field, for ex, 12 denotes 4KB align in head ptr
 * \param[in] Z The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsGetIramMemoryExt(X, Y, Z)       MsHMEMGetHeapMemoryExt(ms_iramhandle, X, Y, Z)
/**
 * \def MsLinkIramMemory(X)
 * \brief It reuses a given memory in internal RAM
 * \param[in] X Pointer to memory.
 * \return Error code
 */
#define MsLinkIramMemory(X)                  MsHMEMLinkHeapMemory(X)
/**
 * \def MsIsIramMemory(X)
 * \brief It checks whether the memory is from internal RAM or not
 * \param[in] X Pointer to memory.
 * \return If success return TRUE, or FALSE
 */
#define MsIsIramMemory(X)                    MsHMEMIsHeapMemory(X)
/**
 * \def MsIramReallocLr(X, Y, Z)
 * \brief It reallocates a memory from internal RAM
 * \param[in] X Pointer to old memory.
 * \param[in] Y The requested memory size.
 * \param[in] Z The caller address.
 * \return If success pointer to memory, or return NULL.
 */
#define MsIramReallocLr(X, Y, Z)             MsHMEMHeapRealloc(ms_iramhandle, X, Y, Z)
/**
 * \def MsReleaseIramMemory(X)
 * \brief It frees a memory which is allocated from internal RAM
 * \param[in] X Pointer to memory.
 * \return Error code.
 */
#define MsReleaseIramMemory(X)            MsHMEMReleaseHeapMemory(X, 0)
/**
 * \def MsIramPeekAlloc(X)
 * \brief It quickly peek the biggest free block in internal RAM
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsIramPeekAlloc(X)            MsHMEMPeekAlloc(ms_iramhandle, X)
/**
 * \def MsIramPeekFree()
 * \brief It quickly free the biggest free block in internal RAM
 * \return If success pointer to memory, or return NULL.
 */
#define MsIramPeekFree()            MsHMEMPeekFree(ms_iramhandle)

#endif //__IRAM_ALLOC__

/**
 * \def MsAllocateNonCacheMem(X)
 * \brief It allocates a non-cached memory from heap
 * \param[in] X The requested memory size.
 * \return If success pointer to memory, or return NULL.
 */
#define MsAllocateNonCacheMem(X)          MsAllocateNonCacheMemLr(X, 0)

/**
 * \def MsAllocateNonCacheMemExt(X, Y)
 * \brief It allocates a memory from heap, with head ptr alignment constriant
 * \param[in] X The requested memory size.
 * \param[in] Y The aligned field, for ex, 12 denotes 4KB align in head ptr
 * \return If success pointer to memory, or return NULL.
 */
#define MsAllocateNonCacheMemExt(X, Y)    MsAllocateNonCacheMemExtLr(X, Y, 0)

/**
 * \fn void* MsAllocateNonCacheMemLr(u32 nMemSize, u32 lr)
 * \brief It allocates a non-cached memory from heap
 * \param[in] nMemSize the requested memory size.
 * \param[in] lr The caller address.
 * @return If success pointer to memory, or return NULL
 */
void* MsAllocateNonCacheMemLr(u32 nMemSize, u32 lr);

/**
 * \fn void* MsAllocateNonCacheMemExtLr(u32 nMemSize, u8 nAligned, u32 lr)
 * \brief It allocates a non-cached aligned memory from heap
 * \param[in] nMemSize the requested memory size.
 * \param[in] nAligned The aligned field, for ex, 12 denotes 4KB align in head ptr
 * \param[in] lr The caller address.
 * @return If success pointer to memory, or return NULL
 */
void* MsAllocateNonCacheMemExtLr(u32 nMemSize, u8 nAligned, u32 lr);

/**
 * \def MsReleaseNonCacheMem(X)
 * \brief It frees a non-cached memory
 * @param [in] X pointer to memory.
 * @return Error code.
 */
#define MsReleaseNonCacheMem(X)          _MsReleaseNonCacheMem((void**)&X)
/** @}*/
s32 _MsReleaseNonCacheMem(void **pMem);

/**
 * \def MsVA2PA(X)
 * \brief It translates virtual address into physical address
 * @param [in] X pointer to memory.
 * @return Pointer to physical memory
 */
#define MsVA2PA(X)                                      MsHMEMVA2PA(X)
/**
 * \def MsPA2VA(X)
 * \brief It translates physical address into virtual address
 * @param [in] X pointer to memory.
 * @return Pointer to virtual  memory
 */
#define MsPA2VA(X)                                      MsHMEMPA2VA(X)
/**
 * \def MsIsInVMA(X)
 * \brief It checks the given ptr is in virtual domain or not
 * @param [in] X pointer to memory.
 * @return If in VMA return TRUE, or FALSE
 */
#define MsIsInVMA(X)                                  MsHMEMIsInVMA(X)


#define MsNonCache2Cache(X)                             MsHMEMVA2PA(X)


#endif

