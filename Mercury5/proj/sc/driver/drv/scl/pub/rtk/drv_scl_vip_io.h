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
#ifndef __DRV_SCL_VIP_IO_H__
#define __DRV_SCL_VIP_IO_H__


#ifndef __DRV_SCL_VIP_IO_C__
#define INTERFACE extern
#else
#define INTERFACE
#endif

//[Daniel]
#include "drv_scl_vip_io_st.h"

INTERFACE DrvSclVipIoErrType_e DrvSclVipIoInit(void);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoExit(void);
INTERFACE s32                  DrvSclVipIoOpen(DrvSclVipIoIdType_e enSlcVipId);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoRelease(s32 s32Handler);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoPoll(s32 s32Handler, DrvSclVipIoPollConfig_t *pstIoPollCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSuspend(s32 s32Handler);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoResume(s32 s32Handler);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetPeakingConfig(s32 s32Handler, DrvSclVipIoPeakingConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetDlcHistogramConfig(s32 s32Handler, DrvSclVipIoDlcHistogramConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoGetDlcHistogramConfig(s32 s32Handler, DrvSclVipIoDlcHistogramReport_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetDlcConfig(s32 s32Handler, DrvSclVipIoDlcConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetLceConfig(s32 s32Handler, DrvSclVipIoLceConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetUvcConfig(s32 s32Handler, DrvSclVipIoUvcConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetIhcConfig(s32 s32Handler, DrvSclVipIoIhcConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetIccConfig(s32 s32Handler, DrvSclVipIoIccConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetIhcIceAdpYConfig(s32 s32Handler, DrvSclVipIoIhcIccConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetIbcConfig(s32 s32Handler, DrvSclVipIoIbcConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetFccConfig(s32 s32Handler, DrvSclVipIoFccConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetNlmConfig(s32 s32Handler, DrvSclVipIoNlmConfig_t *pstIoCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetAckConfig(s32 s32Handler, DrvSclVipIoAckConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetMcnrConfig(s32 s32Handler, DrvSclVipIoMcnrConfig_t *pstIoCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetAipConfig(s32 s32Handler, DrvSclVipIoAipConfig_t *pstIoConfig);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetAipSramConfig(s32 s32Handler, DrvSclVipIoAipSramConfig_t *pstIoCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoCmdqWriteConfig(s32 s32Handler, DrvSclVipIoCmdqConfig_t *pstIoCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetLdcConfig(s32 s32Handler, DrvSclVipIoLdcConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetVipConfig(s32 s32Handler, DrvSclVipIoConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetLdcMdConfig(s32 s32Handler, DrvSclVipIoLdcMdConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetLdcDmapConfig(s32 s32Handler, DrvSclVipIoLdcDmapConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetLdcSramConfig(s32 s32Handler, DrvSclVipIoLdcSramConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetVtrackConfig(s32 s32Handler, DrvSclVipIoVtrackConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetVtrackOnOffConfig(s32 s32Handler, DrvSclVipIoVtrackOnOffConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoGetVersion(s32 s32Handler, DrvSclVipIoVersionConfig_t *pstCfg);
INTERFACE DrvSclVipIoErrType_e DrvSclVipIoSetAllVip(s32 s32Handler, DrvSclVipIoAllSetConfig_t *pstIoCfg);


#undef INTERFACE
#endif
