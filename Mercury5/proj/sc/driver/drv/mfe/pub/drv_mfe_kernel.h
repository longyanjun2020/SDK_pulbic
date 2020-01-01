
#ifndef _MFE_KERNEL_H_
#define _MFE_KERNEL_H_

#if defined(__KERNEL__) || defined(CAM_OS_LINUX_USER)
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/clk-provider.h>
#include <linux/interrupt.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/semaphore.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/clk.h>
#include <ms_platform.h>
#include <ms_msys.h>

#elif defined(__I_SW__)
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "kernel.h"
#include "vm_types.ht"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_int_ctrl.h"
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "sys_MsWrapper_cus_os_flag.h"
#include "sys_rtk_vmrtkho.h"
#include "sys_sys_isw_uart.h"
#include "sys_MsWrapper_cus_os_flag.h"
#include "hal_drv_util.h"
#include "hal_int_ctrl_pub.h"
#include "cpu_mem_map_mercury5.h"
#include "drv_clkgen_cmu.h"
#include "drv_clkgen_cmu_types.h"

#endif // if defined(__KERNEL__)

#include "mhve_ios.h"
#include "mhve_ops.h"
#include "mhve_rqct_ops.h"
#include "mhve_pmbr_ops.h"
#include "cam_os_wrapper.h"

#if defined(__KERNEL__) || defined(CAM_OS_LINUX_USER)
#define MMFE_TIMER_SIZE 2048
typedef MSYS_DMEM_INFO  msys_mem;
#else
typedef struct
{
    ClkgenModule_e      eModule;
    ClkgenClkReq_e      eClkReq;
    ClkgenClkUpdate_e   eClk;
    ClkgenClkSpeed_e    eClkSpeed;
    U16                 nClkSrc;
} DrvMfeClk_t;
#endif

typedef struct MfeCtx_t mmfe_ctx;
typedef struct MfeRqc_t mmfe_rqc;
typedef struct MfeDev_t mmfe_dev;

struct MfeCtx_t
{
#if defined(__KERNEL__) || defined(CAM_OS_LINUX_USER)
    atomic_t        i_refcnt;
#else
    int             i_refcnt;
#endif
    void (*release) (void* );
    void (*adduser) (void* );
    CamOsMutex_t    m_stream;       /* OS Mutex */
    mmfe_dev*       p_device;       /* Pointer to DRV mmfe_dev structure */
    void*           p_handle;       /* Pointer to HAL mhve_ops structure */
#define MMFE_CTX_STATE_NULL  -1
#define MMFE_CTX_STATE_IDLE   0
#define MMFE_CTX_STATE_BUSY   1
    int             i_state;        /* Context State */
    int             i_score;        /* Equal to MB_num x FPS */
    int             i_index;        /* Stream Context ID */
    /* direct memory resource */
    short           i_max_w;        /* Aligned Picture Width */
    short           i_max_h;        /* Aligned Picture Height */
    /* user data buffer */
#define MMFE_USER_DATA_SIZE  (4*1024)
    unsigned char*  p_usrdt;        /* User Data Buffer Address */
    short           i_usrsz;        /* User Data Buffer Free Size */
    short           i_usrcn;        /* User Data Count */
    /* user mode output */
    unsigned char*  p_ovptr;        /* Output Bitstream Buffer Address (Virtual) */
    unsigned int    u_ophys;        /* Output Bitstream Buffer Address (Physical Across MIU) */
    int             i_osize;        /* Output Bitstream Buffer Size */
    int             i_ormdr;        /* Output Bitstream Buffer Remain Data Size */
    /* output cpbs */
#define MMFE_CPBS_NR          1
    mhve_cpb        m_mcpbs[MMFE_CPBS_NR];
#define MMFE_OMODE_MMAP       0
#define MMFE_OMODE_USER       1
#define MMFE_OMODE_PIPE       2
    short           i_omode;
#define MMFE_IMODE_PURE       0
#define MMFE_IMODE_PLUS       1
    short           i_imode;
    /* direct memory resource */
#define MMFE_DMEM_NR          5
    int             i_dmems;        /* Direct Memory Buffer Count (Output bitstream, Ref/Reconstruct...) */
    char*           m_dmems[MMFE_DMEM_NR];  /* Direct Memory Buffer pointer */
    int             s_dmems[MMFE_DMEM_NR];  /* Direct Memory Buffer Size */
#if MMFE_TIMER_SIZE
    int             i_numbr;
    struct {
    unsigned char   tm_dur[4];
    unsigned int    tm_cycles;
    } *p_timer;
#endif
};

struct MfeRqc_t
{
#if defined(__KERNEL__) || defined(CAM_OS_LINUX_USER)
    CamOsMutex_t*   p_mutex;
    struct cdev     m_cdev;
#endif
    mmfe_ctx*       p_mctx;         /* Context of RQCT */
};

struct MfeDev_t
{
#if defined(__KERNEL__) || defined(CAM_OS_LINUX_USER)
    int             i_major;
    int             i_minor;
    struct cdev     m_cdev; // character device
    struct device   m_dev;  // device node
    struct device*  p_dev;  // platform device
    int             i_irq;
#define MMFE_CLOCKS_NR        4
    struct clk*     p_clocks[MMFE_CLOCKS_NR];
#else
#define MMFE_CLOCKS_NR        4
    DrvMfeClk_t*    p_clocks[MMFE_CLOCKS_NR]; /* Clock Attribute */
#endif
    CamOsMutex_t    m_mutex;        /* OS Mutex */
    CamOsTsem_t     m_wqh;          /* OS Flag */
    CamOsTsem_t     tGetBitsSem;
#define MMFE_STREAM_NR        4
    mmfe_rqc        m_regrqc[MMFE_STREAM_NR]; /* RQCT (Stream) Context */
    /* asic */
    void*           p_asicip;       /* Pointer to HAL mhve_ios structure */
#define MMFE_DEV_STATE_NULL  -1
#define MMFE_DEV_STATE_IDLE   0
#define MMFE_DEV_STATE_BUSY   1
    int             i_state;        /* Device State */
    int             i_users;        /* Active Stream Count */
    int             i_score;        /* Accumulated MB rate (Active Stream) */
    /* statistic */
    int             i_counts[MMFE_STREAM_NR][5]; /* Time Statistic Data */
    int             i_thresh;       /* Not Used */
    /* clock */
    int             i_clkidx;       /* Clock Select ID */
    int             i_ratehz;       /* Clock Speed */
    /* rate-controller */
    int             i_rctidx;       /* RQCT Factory ID */
};

#endif //_MFE_KERNEL_H_
