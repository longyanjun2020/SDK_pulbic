
#ifndef __WSP_OSAPI_H__
#define __WSP_OSAPI_H__

#include <ncc_types.h>
#include <wsp_conf.h>

/*common*/
#include <nccport_time.h>
#include <nccport_browser_mem.h>

#define OS_MALLOC   CRTL_malloc
#define OS_FREE        CRTL_free

/*system time related*/
#define OS_CLOCK    NCCPort_time_getElapsedSecondsFrom1970
#define OS_SLEEP    NCCPort_time_sleep
#define OS_TIME     NCCPort_time_getElapsedSecondsFrom1970

/*network*/
#include <nccport_wsp_netPorting.h>

/*debug*/
#ifdef DEBUG

#ifdef NCC_KERNEL_ASSERT
#define WAP_DEBUG_ASSERT NCC_KERNEL_ASSERT
#else
#define WAP_DEBUG_ASSERT
#endif

#else
#define WAP_DEBUG_PRINTF
#define WAP_DEBUG_ASSERT
#endif

#endif /* __WSP_OSAPI_H__ */

