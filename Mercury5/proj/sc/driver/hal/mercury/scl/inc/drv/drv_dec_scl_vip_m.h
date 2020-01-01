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

#ifndef _MDRV_VIP_H
#define _MDRV_VIP_H


//-------------------------------------------------------------------------------------------------
//  Defines & Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    MDRV_DEC_OSDB_LOC_BYPASS_VIP=0,
    MDRV_DEC_OSDB_LOC_PASS_VIP,
}MDRV_DEC_OSDB_LOC;

typedef struct
{
    u16 u16Y2RCoeff11;
    u16 u16Y2RCoeff12;
    u16 u16Y2RCoeff13;
    u16 u16Y2RCoeff21;
    u16 u16Y2RCoeff22;
    u16 u16Y2RCoeff23;
	u16 u16Y2RCoeff31;
    u16 u16Y2RCoeff32;
    u16 u16Y2RCoeff33;	
}VopCSCConfig_t;

//-------------------------------------------------------------------------------------------------
//  Prototype
//-------------------------------------------------------------------------------------------------

#ifndef _MDRV_VIP_C
#define INTERFACE extern
#else
#define INTERFACE
#endif
INTERFACE bool MDrvDecSclVipInit(MDrvSclVipInitConfig_t *pCfg);
INTERFACE void MDrvDecSclVipResume(MDrvSclVipInitConfig_t *pCfg);
INTERFACE void MDrvDecSclVipFreeMemory(void);
INTERFACE MDrvSclVipSetPqConfig_t MDrvDecSclVipFillBasicStructSetPqCfg(MDrvSclVipConfigType_e enVIPtype,void *pPointToCfg);
INTERFACE void MDrvDecSclVipCheckEachIPByCmdqIst(void);
INTERFACE bool MDrvDecSclVipGetIsBlankingRegion(void);
INTERFACE bool MDrvDecSclVipSysInit(MDrvSclVipInitConfig_t *pCfg);
INTERFACE void MDrvDecSclVipDelete(bool bCloseISR);
INTERFACE void MDrvDecSclVipRelease(void);
INTERFACE void MDrvDecSclVipSupend(void);
INTERFACE bool MDrvDecSclVipGetCmdqHwDone(void);
INTERFACE void * MDrvDecSclVipGetWaitQueueHead(void);

INTERFACE bool MDrvDecSclVipSetPollWait(DrvSclOsPollWaitConfig_t stPollWait);

INTERFACE void MDrvDecSclVipResetEachIP(void);
INTERFACE void MDrvDecSclOSDBLocConfig(MDRV_DEC_OSDB_LOC bOsdbLoc);

INTERFACE void MDrvDecSclVipSetAllVipOneShot(MDrvSclVipSuspendConfig_t *stvipCfg);
INTERFACE void MDrvDecSclVipSuspendResetFlagInit(void);
INTERFACE bool MDrvDecSclVipSetPeakingConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetHistogramConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipGetDlcHistogramReport(void *pCfg);
INTERFACE bool MDrvDecSclVipSetDlcConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetLceConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetUvcConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetIhcConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetICEConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetIhcICCADPYConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetIbcConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetFccConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipCmdqWriteConfig(MDrvSclVipCmdqConfig_t *pCfg);
INTERFACE bool MDrvDecSclVipSetLdcConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetLdcmdConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetLdcDmapConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetLdcSramConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetAckConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetNlmConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetVipOtherConfig(void *pCfg);
INTERFACE bool MDrvDecSclVipSetVipBypassConfig(MDrvSclVipConfigType_e enVIPtype);
INTERFACE bool MDrvDecSclVipSetAipBypassConfig(MDrvSclVipAipType_e enAIPtype);
INTERFACE bool MDrvDecSclVipSetNlmSramConfig(MDrvSclVipNlmSramConfig_t stSRAM);
INTERFACE void MDrvDecSclVipPrepareStructToCheckRegister(MDrvSclVipCmdqCheckType_e enCheckType);


#if defined (SCLOS_TYPE_LINUX_KERNEL)
INTERFACE ssize_t MDrvSclVipProcShow(char *buf);
INTERFACE ssize_t MDrvSclVipVipShow(char *buf);
INTERFACE void MDrvSclVipVipStore(const char *buf);
INTERFACE ssize_t MDrvSclVipCmdqShow(char *buf);
INTERFACE ssize_t MDrvSclVipVipSetRuleShow(char *buf);
#endif

#undef INTERFACE


#endif
