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
#ifndef __DRV_SCL_HVSP_IO_H__
#define __DRV_SCL_HVSP_IO_H__


//=============================================================================
#ifndef __DRV_SCL_HVSP_IO_C__
#define INTERFACE extern
#else
#define INTERFACE
#endif
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoInit(void);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoExit(void);
INTERFACE s32                   DrvSclHvspIoOpen(DrvSclHvspIoIdType_e enSclHvspId);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoRelease(s32 s32Handler);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoPoll(s32 s32Handler, DrvSclHvspIoPollConfig_t *pstIoPollCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSuspend(s32 s32Handler);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoResume(s32 s32Handler);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSetInputConfig(s32 s32Handler, DrvSclHvspIoInputConfig_t *pstIoInCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSetOutputConfig(s32 s32Handler, DrvSclHvspIoOutputConfig_t *pstIoOutCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSetScalingConfig(s32 s32Handler, DrvSclHvspIoScalingConfig_t *pstIOSclCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoReqmemConfig(s32 s32Handler, DrvSclHvspIoReqMemConfig_t*pstReqMemCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSetMiscConfig(s32 s32Handler, DrvSclHvspIoMiscConfig_t *pstIOMiscCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSetPostCropConfig(s32 s32Handler, DrvSclHvspIoPostCropConfig_t *pstIOPostCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoGetPrivateIdConfig(s32 s32Handler, DrvSclHvspIoPrivateIdConfig_t *pstIOCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoGetInformConfig(s32 s32Handler, DrvSclHvspIoScInformConfig_t *pstIOInfoCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoReleaseMemConfig(s32 s32Handler, u32 ulchannel);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSetOsdConfig(s32 s32Handler, DrvSclHvspIoOsdConfig_t *pstIOOSDCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSetPriMaskConfig(s32 s32Handler, DrvSclHvspIoPriMaskConfig_t *pstIOPriMaskCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoPirMaskTrigerConfig(s32 s32Handler, DrvSclHvspIoPriMaskTriggerConfig_t *pstIOPriMaskTrigCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoSetFbConfig(s32 s32Handler, DrvSclHvspIoSetFbManageConfig_t *pstIOFbMgCfg);
INTERFACE DrvSclHvspIoErrType_e DrvSclHvspIoGetVersion(s32 s32Hander, DrvSclHvspIoVersionConfig_t *pstIOVersionCfg);

#undef INTERFACE

#endif
