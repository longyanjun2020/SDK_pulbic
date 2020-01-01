/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description :  dwl common part header file
--
------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: dwl_linux.h,v $
--  $Revision: 1.3 $
--  $Date: 2007/06/27 12:48:22 $
--
------------------------------------------------------------------------------*/

#include "drv_mfd_basetype.h"
#include "drv_mfd_dwl.h"

#include "drv_mfd_memalloc.h"
#include "drv_mfd_dwl_linux_lock.h"

#include <sys/types.h>
#include <sys/stat.h>
#ifdef _LINUX_
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/timeb.h>
#endif

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_EFENCE
#include "drv_mfd_efence.h"
#endif

#ifdef _DWL_DEBUG
#error !
#define DWL_DEBUG(fmt, args...) printf(__FILE__ ":%d: " fmt, __LINE__ , ## args)
#define REG_DUMP_FILE "swregdump.log"
#else
//#define DWL_DEBUG(fmt, args...) /* not debugging: nothing */
#endif

#ifndef HX170DEC_IO_BASE
#define HX170DEC_IO_BASE   0xC0000000U
#endif

#define HX170PP_REG_START       0xF0
#define HX170DEC_REG_START      0x4
#define HX170DEC_REG_AMOUNT     100

#define HX170DEC_REG_SIZE       ((HX170DEC_REG_AMOUNT+1)*4)
#define HX170PP_SYNTH_CFG       100
#define HX170DEC_SYNTH_CFG       50

#define DWL_DECODER_INT ((DWLReadReg(dec_dwl, HX170DEC_REG_START) >> 12) & 0xFFU)
#define DWL_PP_INT      ((DWLReadReg(dec_dwl, HX170PP_REG_START) >> 12) & 0xFFU)

#define DWL_STREAM_ERROR_BIT    0x010000    /* 16th bit */
#define DWL_HW_TIMEOUT_BIT      0x040000    /* 18th bit */
#define DWL_HW_ENABLE_BIT       0x000001    /* 0th bit */
#define DWL_HW_PIC_RDY_BIT      0x001000    /* 12th bit */

#ifdef _DWL_HW_PERFORMANCE
/* signal that decoder/pp is enabled */
void DwlDecoderEnable(void);
void DwlPpEnable(void);
#endif
/* Function prototypes */

/* wrapper information */
typedef struct hX170dwl
{
    u32 clientType;
    int fd;                  /* decoder device file */
    int fd_mem;              /* /dev/mem for mapping */
    int fd_memalloc;         /* linear memory allocator */
#if defined(_SOC_) || defined(_FPGA_)
    volatile u32 pRegBase;  /* IO mem base */
#else
    volatile u32 *pRegBase;  /* IO mem base */
#endif
    u32 regSize;             /* IO mem size */
    u32 freeLinMem;          /* Start address of free linear memory */
    u32 freeRefFrmMem;       /* Start address of free reference frame memory */
    int semid;
#ifdef _DWL_DEBUG
    MY_FILE regDump;
#endif
} hX170dwl_t;

i32 DWLWaitPpHwReady(const void *instance, u32 timeout);
i32 DWLWaitDecHwReady(const void *instance, u32 timeout);
void *DWLmemcpy(void *d, const void *s, u32 n);
