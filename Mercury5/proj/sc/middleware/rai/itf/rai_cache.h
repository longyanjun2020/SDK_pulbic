/**
 *
 * @file		rai_cache.h
 *
 * @brief		This module is RAI cache mechanism
 *
 * @author	Xavier.Fan
 * @version $Id: $
 *
 */
//#if	!defined(__RAI_CACHE_H__)
//#define	__RAI_CACHE_H__



#if 1
#include "mdl_rai_cache_pub.h"
#else
/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include	"vm_types.ht"
#include	"vm_rai.hi"




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
typedef void (*pFuncToFlush)(void);




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION PROTOTYPE                                                */
/*--------------------------------------------------------------------------*/
s32	rai_cacheMemoryInit(pFuncToFlush * pFunc);
s32	rai_cacheMemoryGetInfo(vm_raiId_t id, vm_raiInfo_t * pInfo);
s32	rai_cacheMemoryRead(vm_raiId_t id, vm_raiSize_t offset, vm_raiSize_t size, void * pBuffer);
s32	rai_cacheMemoryWrite(vm_raiId_t id, vm_raiSize_t size, void * pData, bool isDirectWrite);
s32	rai_cacheMemoryDelete(vm_raiId_t id);
#if defined(__NAND__)
vm_raiId_t * rai_cacheMemoryGroupDeleteInit(vm_raiId_t * identGroup, u32 number);
s32	rai_cacheMemoryGroupDelete(vm_raiId_t * identGroup, u32 number);
#endif
s32	rai_cacheMemoryFlush(void);


#endif
//#endif	/*	!defined(__RAI_CACHE_H__)	*/

