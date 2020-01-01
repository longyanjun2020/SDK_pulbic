////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2017 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_MFE_CTX_H__
#define __DRV_MFE_CTX_H__

#include "drv_mfe_kernel.h"

mmfe_ctx* MfeCtxAcquire(mmfe_dev*, int strm_id);
long MfeCtxActions(mmfe_ctx*, unsigned int, void*);

#if defined(__KERNEL__) || defined(CAM_OS_LINUX_USER)
long   MfeRqcIoctls(void*, unsigned int, void*);
size_t MfeRqcPrint(void*, char*, size_t);
#endif

#endif // __DRV_MFE_CTX_H__