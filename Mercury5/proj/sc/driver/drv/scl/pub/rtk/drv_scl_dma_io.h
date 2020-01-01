///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
#ifndef __DRV_SCL_DMA_IO_H__
#define __DRV_SCL_DMA_IO_H__


//=============================================================================
#ifndef __DRV_SCL_DMA_IO_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE s32                  DrvSclDmaIoOpen(DrvSclDmaIoIdType_e enSclDmaId);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoInit(void);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoExit(void);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoRelease(s32 s32Handler);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoPoll(s32 s32Handler ,DrvSclDmaIoPollConfig_t *pstCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoSuspend(s32 s32Handler);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoResume(s32 s32Handler);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoSetInBufferConfig(s32 s32Handler, DrvSclDmaIoBufferConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoSetInTriggerConfig(s32 s32Handler, DrvSclDmaIoTriggerConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoSetOutBufferConfig(s32 s32Handler, DrvSclDmaIoBufferConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoSetOutTriggerConfig(s32 s32Handler, DrvSclDmaIoTriggerConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoGetInformationConfig(s32 s32Handler, DrvSclDmaIoGetInformationConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoGetInActiveBufferConfig(s32 s32Handler, DrvSclDmaIoActiveBufferConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoGetOutActiveBufferConfig(s32 s32Handler, DrvSclDmaIoActiveBufferConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoBufferQueueHandleConfig(s32 s32Handler, DrvSclDmaIoBufferQueueConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoGetPrivateIdConfig(s32 s32Handler, DrvSclDmaIoPrivateIdConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoSetLockConfig(s32 s32Handler, DrvSclDmaIoLockConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoSetUnlockConfig(s32 s32Handler, DrvSclDmaIoLockConfig_t *pstIoInCfg);
INTERFACE DrvSclDmaIoErrType_e DrvSclDmaIoGetVersion(s32 s32Handler, DrvSclDmaIoVersionConfig_t*pstIoInCfg);

#undef INTERFACE

#endif

