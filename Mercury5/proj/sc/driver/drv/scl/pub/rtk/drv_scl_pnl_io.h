////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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
#ifndef __DRV_SCL_PNL_IO_H__
#define __DRV_SCL_PNL_IO_H__


#ifndef __DRV_SCL_PNL_IO_C__
#define INTERFACE extern
#else
#define INTERFACE
#endif

INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoInit(void);
INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoExit(void);
INTERFACE s32                  DrvSclPnlIoOpen(DrvSclPnlIoIdType_e enSclPnlId);
INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoRelease(s32 s32Handler);
INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoPoll(s32 s32Handler);
INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoSuspend(s32 s32Handler);
INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoResume(s32 s32Handler);
INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoSetTimingConfig(s32 s32Handler, DrvSclPnlIoTimingConfig_t *pstIOPnlTimingCfg);
INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoSetLpllConfig(s32 s32Handler, DrvSclPnlIoTimingConfig_t *pstIOPnlTimingCfg);
INTERFACE DrvSclPnlIoErrType_e DrvSclPnlIoGetVersionConfig(s32 s32Handler, DrvSclPnlIoVersionConfig_t *psIOVersionCfg);

#undef INTERFACE

#endif

