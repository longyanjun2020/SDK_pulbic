/****************************************************************************/
/*  File    : hmem_rtk7mem.h                                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : RTK memory exports                                                   */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/****************************************************************************/

/*!
 *   \file hmem_rtk7mem.h
 *
 *   \brief public rtk memory include file
 *
 *   this file defines the public memory interface of RTK
 *
 */

#ifndef __HMEM_RTK_HO__
#define __HMEM_RTK_HO__


/* ------------------------------------------------------------------------*/
/*              C RTK prototype interface functions                        */
/* ------------------------------------------------------------------------*/


#ifdef __SDK_SIMULATION__
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
#endif   // __SDK_SIMULATION__
  
/* Memory functions */

u32 HMEMRtkInitDiagnoseGeneric (rtk_memoryContext_t *p_mem);

#ifndef __DEBUG_FILL_HOLE__
#define   _HMEMRtkGetHeapMemory(W, X, Y)     _RtkGetHeapMemoryGeneric(X, Y, W, 0)
#define   HMEMRtkGetHeapMemoryLr(W, X, Y)    _RtkGetHeapMemoryGeneric(X, TRUE, W, Y)
#define   HMEMRtkHeapReallocLr(W, X, Y, Z)  _RtkHeapReAllocateGeneric(X, Y, TRUE, W, Z)
#else
#define   _HMEMRtkGetHeapMemory(W, X, Y)     _RtkGetHeapMemoryGeneric(X, Y, W, 0, FALSE)
#define   HMEMRtkGetHeapMemoryLr(W, X, Y)    _RtkGetHeapMemoryGeneric(X, TRUE, W, Y, FALSE)
#define   HMEMRtkHeapReallocLr(W, X, Y, Z)   _RtkHeapReAllocateGeneric(X, Y, TRUE, W, Z, FALSE)
#endif

#define   HMEMRtkGetHeapMemory(W, X)        _HMEMRtkGetHeapMemory(W, X, TRUE)


#define   HMEMRtkLinkMemory(W, X)     _RtkLinkMemoryGeneric(X, W)

#define   HMEMRtkFindBestPool(W, X, Y)     _RtkFindBestPoolGeneric(X, Y, W, RTK_PTR_STACK)

#define   HMEMRtkGetPoolMemory(W, X, Y)      _RtkGetPoolMemoryGeneric(X, W, RTK_PTR_STACK, Y)

#define   HMEMRtkGetMemory(W, X)     _RtkGetMemoryGeneric(X, W, RTK_PTR_STACK, NULL)

#define   HMEMRtkGetMemoryLr(W, X, Y)             _RtkGetMemoryGeneric(X, W, RTK_PTR_STACK, Y)

#define   HMEMRtkIsHeapMemory(W, X)     _RtkIsHeapMemoryGeneric(X, W)

#define   HMEMRtkIsMemory(W, X)     _RtkIsMemoryGeneric(X, W)

#define   HMEMRtkLinkHeapMemory(W, X)     _RtkLinkHeapMemoryGeneric(X, W)

#define	HMEMRtkCheckPoolMemory(W, X)			_RtkCheckPoolMemoryGeneric(X, W)
#define	HMEMRtkCheckHeapMemory(W, X)			_RtkCheckHeapMemoryGeneric(X, W)

#define	HMEMRtkMemoryLink(W, X)				_RtkMemoryLinkGeneric(X, W)

#ifndef __DEBUG_FILL_HOLE__
#define   HMEMRtkGetHeapMemoryTrapOnNull(W, X)      _RtkGetHeapMemoryTrapOnNullGeneric(X, TRUE, W)
#else
#define   HMEMRtkGetHeapMemoryTrapOnNull(W, X)      _RtkGetHeapMemoryTrapOnNullGeneric(X, TRUE, W, FALSE)
#endif


#define   HMEMRtkHeapWalkEx(W, X, Y)           _RtkHeapWalkExGeneric(X, Y, W)

/* Stack context */
#ifndef __RTK_RELEASE__
#define   HMEMRtkReleaseHeapMemory(W, X, Y)    _RtkReleaseHeapMemoryGeneric(X, W, Y)
#define   HMEMRtkReleaseMemory(W, X, Y)        _RtkReleaseMemoryGeneric(X, W, Y)
#define   HMEMRtkReleaseMemoryGlobal(W, X, Y)  _RtkReleaseMemoryGlobalGeneric(X, W, Y)
#else  //__RTK_RELEASE__
#define   HMEMRtkReleaseHeapMemory(W, X, Y)    RtkReleaseMemoryDiagnose ((void**) &( X ), W, _RtkReleaseHeapMemoryGeneric, Y)
#define   HMEMRtkReleaseMemory(W, X, Y)        RtkReleaseMemoryDiagnose ((void**) &( X ), W, _RtkReleaseMemoryGeneric, Y)
#define   HMEMRtkReleaseMemoryGlobal(W, X, Y)  RtkReleaseMemoryDiagnose ((void**) &( X ), W, _RtkReleaseMemoryGlobalGeneric, Y)
#endif //__RTK_RELEASE__


#define HMEMRtkQueryPoolStatus(W, A, B, C, D, E)		_RtkQueryPoolStatus(A, W, RTK_PTR_STACK, B, C, D, E)
#define HMEMRtkQueryPoolNumber(W)					_RtkQueryPoolNumber(W, RTK_PTR_STACK)

#define HMEMRtkQueryMemRealSize(W, A)                  _RtkGetMemoryRealSize(A, W)

#ifdef __SHARE_M2_MEMORY__
#ifndef __DEBUG_FILL_HOLE__
#define   _HMEMRtkGetHeapMemory_m2(W, X, Y)        _RtkGetHeapMemoryGeneric(X, Y, W, 0)
#else
#define   _HMEMRtkGetHeapMemory_m2(W, X, Y)        _RtkGetHeapMemoryGeneric(X, Y, W, 0, FALSE)
#endif /* __DEBUG_FILL_HOLE__ */
#define   _HMEMRtkReleaseHeapMemory_m2(W, X, Y)       _RtkReleaseHeapMemoryGeneric(X, W, Y)

#define   HMEMRtkGetHeapMemory_m2(W, X)            _HMEMRtkGetHeapMemory_m2(W, X, TRUE)
#define   HMEMRtkReleaseHeapMemory_m2(W, x, Y)        _HMEMRtkReleaseHeapMemory_m2(W, x, Y)

#endif


/***For compatibility with last version */
#define   _HMEMRtkReleaseHeapMemory(X)    _RtkReleaseHeapMemoryGeneric(X, W, Y)
#define   _HMEMRtkReleaseMemory(X)        _RtkReleaseMemoryGeneric(X, W, Y)
#define   _HMEMRtkReleaseMemoryGlobal(X)   _RtkReleaseMemoryGlobalGeneric(X, W, Y)
/***/

#define   HMEMRtkReleaseMemoryGlobalExtended(W, x) _HMEMRtkReleaseMemoryGlobalExtended(W, x)

#ifdef __SDK_SIMULATION__
#ifdef __cplusplus
}
#endif //__cplusplus
#endif   // __SDK_SIMULATION__

#endif  /* __HMEM_RTK_HO__ */


