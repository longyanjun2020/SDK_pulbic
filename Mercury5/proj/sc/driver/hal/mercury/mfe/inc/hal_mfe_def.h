
#ifndef _MFE_DEF_H_
#define _MFE_DEF_H_

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;
typedef   signed char       int8;
typedef   signed short      int16;
typedef   signed int        int32;
typedef   signed long long  int64;

//#define MMFE_REGS_TRACE

/* macros */
#define MIN(a,b)        ((a)>(b)?(b):(a))
#define MAX(a,b)        ((a)<(b)?(b):(a))

/* debug msg */
#if !defined(DEBUG_LEVEL)
#define DEBUG_LEVEL     0
#endif

#define MFE_MSG_ERR     3
#define MFE_MSG_WARNING 4
#define MFE_MSG_DEBUG   5
#define MFE_MSG_LEVEL   MFE_MSG_ERR //JPE_MSG_WARNING

#define MFE_MSG_ENABLE

#ifdef  MFE_MSG_ENABLE
#define MFE_MSG_FUNC_ENABLE
#define MFE_STRINGIFY(x) #x
#define MFE_TOSTRING(x) MFE_STRINGIFY(x)
#ifdef MFE_MSG_FUNC_ENABLE
#define MFE_MSG_TITLE   "[MFE, %s] "
#define MFE_MSG_FUNC    __func__
#else
#define MFE_MSG_TITLE   "[MFE] %s"
#define MFE_MSG_FUNC    ""
#endif
#endif

//////////// Define for Linux pletform ////////////
#if defined(__KERNEL__) || defined(CAM_OS_LINUX_USER)
//#include <stdio.h>
//#include <stdarg.h>
//#include <string.h> // for memset
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <asm/types.h>
#include "ms_platform.h"
#include "cam_os_wrapper.h"

//////////// Define for RTK pletform ////////////
#elif defined(__I_SW__)
#include <stdio.h>
#include <stdarg.h>
#include <string.h> // for memset
#include "kernel.h"
#include "vm_types.ht"
#include "cam_os_wrapper.h"
#include "sys_sys_isw_uart.h"
#include "hal_drv_util.h"

#define ENOMEM      12              // Cannot allocate memory
#define EFAULT      14              // Bad address
#define EINVAL      22              // Invalid argument
#define ENODATA     61              // No data available

#endif  //#if defined(__KERNEL__)

#define REGW(base,idx)          (*(((volatile unsigned short*)(base))+2*(idx)))
#if defined(MMFE_REGS_TRACE)
#define PRINT(s,idx,v)          CamOsDebug(#s":bank%d[%02x]=%04x\n",(idx&0x80)?1:0,idx&0x7F,v)
#define REGWR(base,idx,v,cmt)   do{REGW(base,idx)=(v);PRINT(w,idx,v);}while(0)
#define REGRD(base,idx,cmt)     ({ushort v=REGW(base,idx);PRINT(r,idx,v); v;})
#else
#define REGWR(base,idx,val,cmt) REGW(base,idx)=(val)
#define REGRD(base,idx,cmt)     REGW(base,idx)
#endif

#define MFE_MSG(dbglv, _fmt, _args...)                          \
    do if (dbglv <= MFE_MSG_LEVEL) {                            \
        CamOsDebug(MFE_TOSTRING(dbglv) MFE_MSG_TITLE  _fmt, MFE_MSG_FUNC, ## _args);   \
    } while(0)

#define MEM_ALLC(l)         CamOsMemCalloc(1, l)
#define MEM_FREE(p)         CamOsMemRelease(p)
#define MEM_SETV(p,v,l)     memset(p,v,l)
#define MEM_COPY(p,q,l)     memcpy(p,q,l)

typedef enum
{
    MFE_DEV_INIT = 0,
    MFE_DEV_BUSY,
    MFE_DEV_ENC_DONE,
    MFE_DEV_OUTBUF_FULL,
    MFE_DEV_INBUF_FULL
} MfeDevStatus_e;

typedef enum
{
    MFE_IOC_RET_SUCCESS             = 0,
    MFE_IOC_RET_BAD_QTABLE          = 1,
    MFE_IOC_RET_BAD_QP              = 2,
    MFE_IOC_RET_BAD_BITSOFFSET      = 3,
    MFE_IOC_RET_BAD_BANKNUM         = 4,
    MFE_IOC_RET_BAD_INBUF           = 5,
    MFE_IOC_RET_BAD_OUTBUF          = 6,
    MFE_IOC_RET_BAD_NULLPTR         = 7,
    MFE_IOC_RET_BAD_BANKCNT         = 8,
    MFE_IOC_RET_BAD_LASTZZ          = 9,
    MFE_IOC_RET_UNKOWN_COMMAND      = 10,
    MFE_IOC_RET_BAD_VIRTUAL_MEM     = 11,
    MFE_IOC_RET_NEED_DRIVER_INIT    = 12,
    MFE_IOC_RET_FMT_NOT_SUPPORT     = 13,
    MFE_IOC_RET_HW_IS_RUNNING       = 14,
    MFE_IOC_RET_FAIL                = 15
} MFE_IOC_RET_STATUS_e;

#define MMFE_RCTL_PATCH
#define MMFE_IMI_DBF_ADDR  0x00000 /* From 0x00000 to 0x03FFF */
#define MMFE_IMI_LBW_ADDR  0x04000 /* From 0x04000 to 0x13FFF */

#endif /*_MFE_DEF_H_*/
