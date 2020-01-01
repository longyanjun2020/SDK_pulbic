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

#ifndef __DRV_MFE_DEV_H__
#define __DRV_MFE_DEV_H__

#include "drv_mfe_kernel.h"

int MfeDevRegister(mmfe_dev*, mmfe_ctx*);
int MfeDevUnregister(mmfe_dev*, mmfe_ctx*);
int MfeDevPowerOn(mmfe_dev*, int);
int MfeDevSuspend(mmfe_dev*);
int MfeDevResume(mmfe_dev*);
int MfeDevPushjob(mmfe_dev*, mmfe_ctx*);
int MfeDevIsrFnx(mmfe_dev*);
int DevClkRate(mmfe_dev*, int);
int DevPowerOn(mmfe_dev*, int);

#endif // __DRV_MFE_DEV_H__
