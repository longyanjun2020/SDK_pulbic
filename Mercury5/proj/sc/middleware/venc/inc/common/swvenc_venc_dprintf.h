#ifndef venc_dprintf_H
#define venc_dprintf_H

// Switch for different debug messages
#define DBGLVL_APP_USAGE    (1 << 0)
#define DGBLVL_APP_ERRMSG   (1 << 1)
#define DBGLVL_APP_INFO     (1 << 2)
#define DBGLVL_LIB_CRC      (1 << 8)
#define DBGLVL_LIB_ME       (1 << 9)
#define DBGLVL_LIB_RUNLEVEL (1 << 10)
#define DBGLVL_LIB_MALLOC   (1 << 11)
#define DBGLVL_LIB_FLOW     (1 << 12)
#define DBGLVL_LIB_RC       (1 << 13) // Rate control
#define DBGLVL_LIB_RCDFR    (1 << 14) // Rate control: Dynamic-Frame-Rate
#define DBGLVL_LIB_VLC      (1 << 15) // For DEBUG_RUNLEVEL
#define DBGLVL_LIB_CODING      (1 << 16) // For DEBUG_Coding
// Marked out below line to disable all debug messages!
//#define VENC_DEBUG_LEVEL (DBGLVL_LIB_MALLOC|DBGLVL_APP_INFO|DBGLVL_LIB_MALLOC|DBGLVL_APP_USAGE|DGBLVL_APP_ERRMSG|DBGLVL_APP_INFO|DBGLVL_LIB_CRC|DBGLVL_LIB_FLOW)


#if !defined(VENC_DEBUG_LEVEL)
#define VENC_DEBUG_LEVEL 0
#endif

#ifdef _MSC_VER

#if VENC_DEBUG_LEVEL == 0

static __inline void venc_dprintf(int level, const char *fmt, ...) {}

#else /* VENC_DEBUG_LEVEL */

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

static __inline void venc_dprintf(int level, const char *fmt, ...)
{
    va_list ap;
    char msg[2048];

    if (!(level & VENC_DEBUG_LEVEL))
        return;

    va_start(ap, fmt);
    vsprintf(msg, fmt, ap);
#ifdef WINCE
    fprintf(stderr, "%s", msg);
#else
  #if 0
    printf(msg);
  #else
    OutputDebugStringA(msg);
  #endif
#endif
    va_end(ap);
}

#endif /* VENC_DEBUG_LEVEL */

#else /* _MSC_VER */

#if VENC_DEBUG_LEVEL == 0

#define venc_dprintf(arg...) ((void) 0)

#else /* VENC_DEBUG_LEVEL */

#ifdef MIPSDEV

#include <cyg/infra/diag.h>

#define venc_dprintf(level, fmt, arg...) \
    do { \
        if (level & VENC_DEBUG_LEVEL) diag_printf(fmt, ##arg); \
    } while (0)
#elif defined(__I_SW__)
#include <stdio.h>
#include <stdarg.h>
#include "sys_sys_isw_uart.h"
//#define VENC_DEBUG_LEVEL 1
//#include "sys_sys_isw_uart.h" // UartSendTrace
static __inline void venc_dprintf(int level, const char *fmt, ...)
{
    va_list ap;
    char msg[2048];

    if (!(level & VENC_DEBUG_LEVEL))
        return;

    va_start(ap, fmt);
    vsprintf(msg, fmt, ap);
    UartSendTrace(msg);
    va_end(ap);
}
#elif defined(AEON_SIM)

#define venc_dprintf(level, fmt, arg...) \
    do { \
        if (level & VENC_DEBUG_LEVEL) printf(fmt, ##arg); \
    } while (0)

#elif 0//defined(__RTK_OS__)&&defined(__AEON__)
//#define VENC_DEBUG_LEVEL 1
//#include "sys_sys_isw_uart.h" // UartSendTrace
#include "drv_uart_api.h"
#include <string.h>
#include <stdarg.h>
#include "kernel.h"
#include "hal_fuart.h"
#include "hal_r2_uart.h"
static __inline void venc_dprintf(int level, const char *fmt, ...)
{

static char dbg_trace_buf[512];
    if (!(level & VENC_DEBUG_LEVEL))
        return;

	va_list  args = {0};

	va_start(args, fmt);

	vsprintf(dbg_trace_buf, fmt, args);

    DrvUartSendMsg(dbg_trace_buf);
}
#elif defined(ARM9)
#define venc_dprintf(level, fmt, arg...) \
    do { \
        if (level & VENC_DEBUG_LEVEL) printf(fmt, ##arg); \
    } while (0)

#elif defined(__RTK_OS__)
#include "sys_vm_dbg.ho"
#include "sys_traces.ho"
//vm_dbgTrace(_CUSAVP, fmt, ##__VA_ARGS__)
#define venc_dprintf(level, fmt, arg...) \
    do { \
       if ((level & VENC_DEBUG_LEVEL) != 0) \
        vm_dbgTrace(_CUS1 | LEVEL_30,fmt, ##arg); \
    } while(0)

#else /* MIPSDEV */

#if 1
#define venc_dprintf(level, fmt, arg...)
#else
#define venc_dprintf(level, fmt, arg...) \
    do { \
        if (level & VENC_DEBUG_LEVEL) printf(fmt, ##arg); \
    } while (0)
#endif

#endif /* MIPSDEV */

#endif /* DEBUG_LEVEL */

#endif /* _MSC_VER */

#endif /* venc_dprintf_H */
