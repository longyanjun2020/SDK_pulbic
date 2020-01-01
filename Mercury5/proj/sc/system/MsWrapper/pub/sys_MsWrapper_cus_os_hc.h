/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 2001
*/

/****************************************************************************/
/*  File    : wm_osdef.hc                                                   */
/*--------------------------------------------------------------------------*/
/*  Description:  OS ressource definition                                   */
/*                                                                          */
/*                                                                          */
/*  History :                                                               */
/*--------------------------------------------------------------------------*/
/*   Date   | Author     | Err  |  Modification                             */
/*----------+------------+------+-------------------------------------------*/
/*----------+------------+------+-------------------------------------------*/
/****************************************************************************/

#ifndef __SYS_MSWRAPPER_CUS_OS_HC__
#define __SYS_MSWRAPPER_CUS_OS_HC__

#include "vm_types.ht"
#include "vm_osdef.hc"
#include "sys_rtk_vmrtkho.h"
#include "sys_rtk_ho.h"
#include "sys_MsWrapper_cus_os_mem.h"

#if defined(__SDK_SIMULATION__)
  // Java Delta is not supported in simulator
  #if defined(__JAVA_DELTA__)
    #undef __JAVA__
	#undef __JAVA_DELTA__
  #endif /* defined(__JAVA_DELTA__) */
#endif /* defined(__SDK_SIMULATION__) */

typedef enum { // Sync to _rtk_ErrCode_e
    CUS_OS_OK                     = 10,   ///< No error - the function call was successfull
    CUS_OS_NOT_RELEASED           = 11,   ///< The bloc was not released
    CUS_OS_UNIT_NOAVAIL           = 21,   ///< Not available
    CUS_OS_NO_MESSAGE             = 33,   ///< No message found
    CUS_OS_NON_SATISFACTORY_POOL  = 40,   ///< No memory pool found (-deprecated-)
    CUS_OS_NO_MEMORY_AVAIL        = 41,   ///< Not enough memory
    CUS_OS_CLUSTER_OUT_OF_RANGE   = 42,   ///<
    CUS_OS_TIMER_NOT_FOUND        = 43,   ///< Invalid timer id
    CUS_OS_MEM_OVERFLOW           = 44,   ///<
    CUS_OS_NULL_RELEASE           = 45,   ///< Try to release a NULL pointer
    CUS_OS_NOT_HEAP_RELEASE       = 46,   ///< Memory zone is not in heap
    CUS_OS_NOT_MEMORY_RELEASE     = 47,   ///< Memory zone is not in pool memory (-deprecated-)
    CUS_OS_MAILBOX_FULL           = 48,   ///< Mailbox is full (-deprecated-)
    CUS_OS_TIMER_EXHAUSTED        = 49,   ///< Timer is unavailable (-deprecated-)
    CUS_OS_MAILBOX_NOT_EXIST      = 50,
    CUS_OS_IN_INTERRUPT           = 51
} cus_ErrCode_e;

#ifdef __SDK_SIMULATION__
#define CUS_ASSERT(_X_)
#define CUS_FAILED(_X_)
#define CUS_ASSERT_EX(_X_, _INFOSTR_)
#define CUS_ASSERT_P1(_X_, _INT1_)
#define CUS_ASSERT_P2(_X_, _INT1_, _INT2_)
#define CUS_ASSERT_P3(_X_, _INT1_, _INT2_, _INT3_)
#else
#define CUS_ASSERT(_X_) \
	if(!(_X_)) \
	{ \
		extern void ker_assert_func(u8 * str, u8 * file, u32 line); \
		ker_assert_func( (u8*)#_X_, (u8*)__FILE__, __LINE__); \
	}
#define CUS_ASSERT_EX(_X_, _INFOSTR_) \
	if(!(_X_)) \
	{ \
		extern void ker_assert_func2(u8 * str, u8 * str2, u8 * file, u32 line); \
		ker_assert_func2( (u8*)#_X_, (u8*)#_INFOSTR_, (u8*)__FILE__, __LINE__); \
	}
#define CUS_ASSERT_P1(_X_, _INT1_) \
	if(!(_X_)) \
	{ \
		extern void ker_assert_func_p1(u8 * str, u32 n1, u8 * file, u32 line); \
		ker_assert_func_p1( (u8*)#_X_, _INT1_, (u8*)__FILE__, __LINE__); \
	}
#define CUS_ASSERT_P2(_X_, _INT1_, _INT2_) \
	if(!(_X_)) \
	{ \
		extern void ker_assert_func_p2(u8 * str, u32 n1, u32 n2, u8 * file, u32 line); \
		ker_assert_func_p2( (u8*)#_X_, _INT1_, _INT2_, (u8*)__FILE__, __LINE__); \
	}
#define CUS_ASSERT_P3(_X_, _INT1_, _INT2_, _INT3_) \
	if(!(_X_)) \
	{ \
		extern void ker_assert_func_p3(u8 * str, u32 n1, u32 n2, u32 n3, u8 * file, u32 line); \
		ker_assert_func_p3( (u8*)#_X_, _INT1_, _INT2_, _INT3_, (u8*)__FILE__, __LINE__); \
	}
#define CUS_ERROR(_X_) \
	if(!(_X_)) \
	{ \
		extern void ker_assert_func(u8 * str, u8 * file, u32 line); \
		ker_assert_func( (u8*)#_X_, (u8*)__FILE__, __LINE__); \
	}
#define CUS_FAILED(_X_) \
	{ \
		extern void ker_failed_func(u8 * str, u8 * file, u32 line); \
		ker_failed_func( (u8*)_X_, (u8*)__FILE__, __LINE__); \
	}
#endif

#endif  /* __SYS_MSWRAPPER_CUS_OS_HC__ */

