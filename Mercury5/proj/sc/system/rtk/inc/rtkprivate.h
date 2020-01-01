/****************************************************************************/
/*  File    : rtkprivate.h                                                  */
/*--------------------------------------------------------------------------*/
/*  Scope   : RTK private functions                                         */
/*                                                                          */
/*  Contents:    This header file is only included         */
/*                    in rtk internal files.                           */
/*                    Please do not directly include them.   */
/*  Historical :                                                            */
/****************************************************************************/

/*!
 *   \file rtkprivate.h
 *
 *   \brief private rtk include file
 *
 *   this file defines the private interface of RTK
 *
 */


#ifndef __RTKPRIVATE_H__
#define __RTKPRIVATE_H__

#include "rtk.ho"

#define RTK_FATAL FATAL

#ifdef __SDK_SIMULATION__
bool AddMemBlock(rtk_memoryContext_t *p_ctx, void *memAdd, u32 size);
bool RemoveMemBlock(rtk_memoryContext_t *p_ctx, void *memAdd);
#endif

/* Memory functions */

#ifndef __DEBUG_FILL_HOLE__
void      *_RtkGetHeapMemoryGeneric (u32 RequestedSize, bool Walk, rtk_memoryContext_t *ptr_memoryContext, u32 lr);
void      *_RtkHeapReAllocateGeneric(void *MemoryPtr, u32 RequestedSize, bool Walk, rtk_memoryContext_t *p_ctx, u32 lr);

#define   _RtkGetHeapMemory(X, Y)     _RtkGetHeapMemoryGeneric(X, Y, &rtk_memoryStk, 0)
#define   RtkGetHeapMemoryLr(X, Y)    _RtkGetHeapMemoryGeneric(X, TRUE, &rtk_memoryStk, Y)
#define   RtkHeapReallocLr(X, Y, Z)  _RtkHeapReAllocateGeneric(X, Y, TRUE, &rtk_memoryStk, Z)
#else
void      *_RtkGetHeapMemoryGeneric (u32 RequestedSize, bool Walk, rtk_memoryContext_t *ptr_memoryContext, u32 lr, bool fillHole);
void      *_RtkHeapReAllocateGeneric(void *MemoryPtr, u32 RequestedSize, bool Walk, rtk_memoryContext_t *p_ctx, u32 lr, bool fillHole);

#define   _RtkGetHeapMemory(X, Y)     _RtkGetHeapMemoryGeneric(X, Y, &rtk_memoryStk, 0, FALSE)
#define   RtkGetHeapMemoryLr(X, Y)    _RtkGetHeapMemoryGeneric(X, TRUE, &rtk_memoryStk, Y, FALSE)
#define   RtkHeapReallocLr(X, Y, Z)   _RtkHeapReAllocateGeneric(X, Y, TRUE, &rtk_memoryStk, Z, FALSE)
#endif

#define   RtkGetHeapMemory(X)        _RtkGetHeapMemory(X, TRUE)

u8        _RtkLinkMemoryGeneric (void *rtkMemoryPtr, rtk_memoryContext_t *rtk_memoryContext);
#define   RtkLinkMemory(X)     _RtkLinkMemoryGeneric(X, &rtk_memoryStk)

u8        _RtkFindBestPoolGeneric( u16 MessageLength, u8 *PtrPoolID , rtk_memoryContext_t *p_ctx, rtk_PtrRegion_e ptr_region);
//u8        _RtkFindBestPoolGeneric( u16 MessageLength, u8 *PtrPoolID , rtk_memoryContext_t *rtk_memoryContext);
#define   RtkFindBestPool(X, Y)     _RtkFindBestPoolGeneric(X, Y, &rtk_memoryStk, RTK_PTR_STACK)
#define   RtkFindBestCusPool(X, Y)    _RtkFindBestPoolGeneric(X, Y, &rtk_memoryStk, RTK_PTR_STACK)


void      *_RtkGetPoolMemoryGeneric (u8 PoolId, rtk_memoryContext_t *p_ctx, rtk_PtrRegion_e ptr_region, u32 Lr);
//void      *_RtkGetPoolMemoryGeneric (u8 PoolId, rtk_memoryContext_t *rtk_memoryContext);
//void      *_RtkGetPoolMemoryGenericWithLR (u8 PoolId, rtk_memoryContext_t *rtk_memoryContext, u32 lr);
#define   RtkGetPoolMemory(X)      _RtkGetPoolMemoryGeneric(X, &rtk_memoryStk, RTK_PTR_STACK, NULL)

#define   RtkGetCusPoolMemory(X, Y)      _RtkGetPoolMemoryGeneric(X, &rtk_memoryStk,RTK_PTR_STACK, Y)

void      *_RtkGetMemoryGeneric (u16 MemorySize, rtk_memoryContext_t *p_ctx, rtk_PtrRegion_e ptr_region, u32 Lr);
//void      *_RtkGetMemoryGeneric (u16 MemorySize, rtk_memoryContext_t *rtk_memoryContext);
//void      *_RtkGetMemoryGenericWithLR (u16 MemorySize, rtk_memoryContext_t *rtk_memoryContext, u32 lr);
#define   RtkGetMemory(X)     _RtkGetMemoryGeneric(X, &rtk_memoryStk, RTK_PTR_STACK, NULL)

#define   RtkGetMemoryLr(X, Y)             _RtkGetMemoryGeneric(X, &rtk_memoryStk, RTK_PTR_STACK, Y)
#define   RtkGetCustoMemory(X,Y)        _RtkGetMemoryGeneric(X, &rtk_memoryStk, RTK_PTR_STACK, Y)

#ifdef __MEM_CHECK_TOOL___
s32 _RtkMemCheck(u32* pMem, rtk_memoryContext_t *pCtx, rtk_mem_check_info_t* nMemInfo);
#define RtkMemCheck(x, Y) _RtkMemCheck(x, &rtk_memoryStk, Y)
#endif
bool      _RtkIsHeapMemoryGeneric(void *p, rtk_memoryContext_t *rtk_memoryContext);
#define   RtkIsHeapMemory(X)     _RtkIsHeapMemoryGeneric(X, &rtk_memoryStk)

u8        _RtkIsMemoryGeneric (void *rtkMemoryPtr, rtk_memoryContext_t *rtk_memoryContext);
#define   RtkIsMemory(X)     _RtkIsMemoryGeneric(X, &rtk_memoryStk)

u8        _RtkLinkHeapMemoryGeneric (void *rtkMemoryPtr, rtk_memoryContext_t *rtk_memoryContext);
#define   RtkLinkHeapMemory(X)     _RtkLinkHeapMemoryGeneric(X, &rtk_memoryStk)

bool			_RtkCheckPoolMemoryGeneric(void *pMem, rtk_memoryContext_t *pCtx);
bool			_RtkCheckHeapMemoryGeneric(void *pMem, rtk_memoryContext_t *pCtx);
#define		RtkCheckPoolMemory(X)			_RtkCheckPoolMemoryGeneric(X, &rtk_memoryStk)
#define		RtkCheckHeapMemory(X)			_RtkCheckHeapMemoryGeneric(X, &rtk_memoryStk)

void*     _RtkMemoryAllocateGeneric(u32 requestedSize, rtk_memoryContext_t *pCtx, rtk_PtrRegion_e ptr_region, u32 lr);
void*     _RtkMemoryReAllocateGeneric(void *MemoryPtr, u32 requestedSize, rtk_memoryContext_t *pCtx, rtk_PtrRegion_e ptr_region, u32 lr);
#define		RtkMemoryReAllocateLr(X, Y, Z)		 _RtkMemoryReAllocateGeneric(X, Y, &rtk_memoryStk, RTK_PTR_STACK, Z)
#define		RtkMemoryReAllocate(X, Y)		       _RtkMemoryReAllocateGeneric(X, Y, &rtk_memoryStk, RTK_PTR_STACK, 0)
#define		RtkMemoryAllocate(X)		           _RtkMemoryAllocateGeneric(X, &rtk_memoryStk, RTK_PTR_STACK, 0)
#define   RtkCustoMemoryAllocate(X,Y)        _RtkMemoryAllocateGeneric(X, &rtk_memoryStk, RTK_PTR_STACK, Y)

#define   RtkMemoryAllocate_stack(X)         _RtkMemoryAllocateGeneric(X, &rtk_memoryStk, RTK_PTR_STACK, 0)
#define   RtkMemoryAllocateLr_stack(X,Y)     _RtkMemoryAllocateGeneric(X, &rtk_memoryStk, RTK_PTR_STACK, Y)

u8 				_RtkMemoryLinkGeneric(void *pMem, rtk_memoryContext_t *p_ctx);
#define		RtkMemoryLink(X)				_RtkMemoryLinkGeneric(X, &rtk_memoryStk)

#ifndef __DEBUG_FILL_HOLE__
void      *_RtkGetHeapMemoryTrapOnNullGeneric(u32 RequestedSize, bool Walk, rtk_memoryContext_t *rtk_memoryContext);
#define   RtkGetHeapMemoryTrapOnNull(X)      _RtkGetHeapMemoryTrapOnNullGeneric(X, TRUE, &rtk_memoryStk)
#else
void      *_RtkGetHeapMemoryTrapOnNullGeneric(u32 RequestedSize, bool Walk, rtk_memoryContext_t *rtk_memoryContext, bool fillHole);
#define   RtkGetHeapMemoryTrapOnNull(X)      _RtkGetHeapMemoryTrapOnNullGeneric(X, TRUE, &rtk_memoryStk, FALSE)
#endif

void *_RtkGetPMemory(u32 RequestedSize, rtk_memoryContext_t *p_ctx, u8 nAlignedHead, u32 lr);
void *_RtkGetPMemoryAtEnd(u32 RequestedSize, rtk_memoryContext_t *p_ctx, u32 lr);
void *_RtkGetVMemory(u32 RequestedSize, rtk_memoryContext_t *p_ctx, u32 *AcutalSize, u8 nAlignedHead, u8 nAlignedEnd, bool bCanTruncate, u32 lr);
void _RtkSetVMemoryBlock(void *pMem, vmb_struct_t *pVmb);
void _RtkGetVMemoryBlock(void *pMem, vmb_struct_t *pVmb);
u32 _RtkGetHeapRealSize(void *MemoryPtr , rtk_memoryContext_t *p_ctx);

u8        _RtkReleaseHeapMemoryGeneric(void *MemoryPtr , rtk_memoryContext_t *rtk_memoryContext, void *pre_LR);
u8        _RtkReleaseMemoryGeneric (void *rtkMemoryPtr, rtk_memoryContext_t *rtk_memoryContext, void *pre_LR);
u8        _RtkReleaseMemoryGlobalGeneric(void *p, rtk_memoryContext_t *rtk_memoryContext, void *pre_LR);

/* Stack context */
#ifndef __RTK_RELEASE__
#define   RtkReleaseHeapMemory(X)    _RtkReleaseHeapMemoryGeneric(X, &rtk_memoryStk, 0)
#define   RtkReleaseMemory(X)        _RtkReleaseMemoryGeneric(X, &rtk_memoryStk, 0)
#define   RtkReleaseMemoryGlobal(X)  _RtkReleaseMemoryGlobalGeneric(X, &rtk_memoryStk, 0)
#else  //__RTK_RELEASE__
u8 RtkReleaseMemoryDiagnose (void **p, rtk_memoryContext_t * p_ctx, u8 (*f)(void *, rtk_memoryContext_t *, void *), void *pre_LR);
#define   RtkReleaseHeapMemory(X)    RtkReleaseMemoryDiagnose ((void**) &( X ), &rtk_memoryStk, _RtkReleaseHeapMemoryGeneric, 0)
#define   RtkReleaseMemory(X)        RtkReleaseMemoryDiagnose ((void**) &( X ), &rtk_memoryStk, _RtkReleaseMemoryGeneric, 0)
#define   RtkReleaseMemoryGlobal(X)  RtkReleaseMemoryDiagnose ((void**) &( X ), &rtk_memoryStk, _RtkReleaseMemoryGlobalGeneric, 0)
#endif //__RTK_RELEASE__

u8    _RtkQueryPoolStatus(u8 poolId, rtk_memoryContext_t *p_ctx, rtk_PtrRegion_e ptr_region, u16 *pClusterSize, u16 *pTotalClusters, u16 *pCurrUsedClusters, u16 *pMaxUsedClusters);
u8    _RtkQueryPoolNumber(rtk_memoryContext_t *p_ctx, rtk_PtrRegion_e ptr_region);
#define RtkQueryCusPoolStatus(A, B, C, D, E)		_RtkQueryPoolStatus(A, &rtk_memoryStk, RTK_PTR_STACK, B, C, D, E)
#define RtkQueryCusPoolNumber()									_RtkQueryPoolNumber(&rtk_memoryStk, RTK_PTR_STACK)
#define RtkQueryPoolStatus(A, B, C, D, E)				_RtkQueryPoolStatus(A, &rtk_memoryStk, RTK_PTR_STACK, B, C, D, E)
#define RtkQueryPoolNumber()										_RtkQueryPoolNumber(&rtk_memoryStk, RTK_PTR_STACK)

u32   _RtkGetMemoryRealSize(void *p, rtk_memoryContext_t *p_ctx);
#define RtkQueryMemRealSize(A)                  _RtkGetMemoryRealSize(A, &rtk_memoryStk)

/***For compatibility with last version */
#define   _RtkReleaseHeapMemory(X)    _RtkReleaseHeapMemoryGeneric(X, &rtk_memoryStk, 0)
#define   _RtkReleaseMemory(X)        _RtkReleaseMemoryGeneric(X, &rtk_memoryStk, 0)
#define   _RtkReleaseMemoryGlobal(X)  _RtkReleaseMemoryGlobalGeneric(X, &rtk_memoryStk, 0)
/***/

u8 _RtkReleaseMemoryGlobalExtended(void *p);
#define   RtkReleaseMemoryGlobalExtended(x) _RtkReleaseMemoryGlobalExtended(x )

#ifdef __DEBUG_FILL_HOLE__
void *RtkGetHeapMemoryAtEnd(u32 RequestedSize);
u32   RtkReleaseHeapMemoryAtEnd(void *MemoryPtr);
#endif
 
#endif //__RTKPRIVATE_H__

