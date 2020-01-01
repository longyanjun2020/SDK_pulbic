////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_pm_res.h
* @version
* @brief   Power manager source file for LDO resource management
*          functions
*
*/

#ifndef __MDL_PM_RES_H__
#define __MDL_PM_RES_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_pm_ldo.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    bool bPowerStatusMap[DRV_PM_LDO_INVALID];
    u16 nClockStatusPllSet3;
    u16 nClockStatusFreeRunTst;
} MdlPmResStatusMap_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** MdlPmResInit
* @brief        Initialize PM RES module
*
* @param[in]
*
* @retval
*
*/
extern void MdlPmResInit(void);

/** MdlPmResLdoInit
* @brief        Initialize LDO setting
*
* @param[in]    ptLdoSetting        LDO setting.
*
* @retval       MDL_PM_RET_OK                           Success.
* @retval       MDL_PM_RET_MEM_ALLOC_ERROR              Fail to allocate memory.
* @retval       MDL_PM_RET_UNSUPPORT_DEVICE             Unsupport device.
* @retval       MDL_PM_RET_UNSUPPORT_POWER_REQ          Unsupport power request.
* @retval       MDL_PM_RET_UNSUPPORT_LDO                Unsupport LDO.
* @retval       MDL_PM_RET_UNSUPPORT_VOLTAGE            Unsupport voltage.
* @retval       MDL_PM_RET_REINITIALIZE_LDO             Ldo is initialized already.
* @retval       MDL_PM_RET_UNINITIALIZE_LDO             Ldo is not initialized.
* @retval       MDL_PM_RET_NULL_HANDLER                 No handler for customer LDO.
*
*/
extern MdlPmReturnCode_e MdlPmResLdoInit(DrvPmLdoSetting_t *ptLdoSetting);

/** MdlPmResDevPowerCtl
* @brief        Update LDO setting
*
* @param[in]    ptDeviceSetting     Device setting.
* @param[out]   ptLdoSetting        LDO setting.
*
* @retval       MDL_PM_RET_OK                           Success.
* @retval       MDL_PM_RET_MEM_ALLOC_ERROR              Fail to allocate memory.
* @retval       MDL_PM_RET_UNSUPPORT_DEVICE             Unsupport device.
* @retval       MDL_PM_RET_UNSUPPORT_POWER_REQ          Unsupport power request.
* @retval       MDL_PM_RET_UNSUPPORT_LDO                Unsupport LDO.
* @retval       MDL_PM_RET_UNSUPPORT_VOLTAGE            Unsupport voltage.
* @retval       MDL_PM_RET_REINITIALIZE_LDO             Ldo is initialized already.
* @retval       MDL_PM_RET_UNINITIALIZE_LDO             Ldo is not initialized.
* @retval       MDL_PM_RET_NULL_HANDLER                 No handler for customer LDO.
*
*/
extern MdlPmReturnCode_e MdlPmResDevPowerCtl(DrvPmDeviceSetting_t *ptDeviceSetting, DrvPmLdoSetting_t *ptLdoSetting);

/** MdlPmResPadPowerCtl
* @brief        Update pad domain setting
*
* @param[in]    ptDomainSetting     Pad domain setting.
* @param[out]   ptLdoSetting        LDO setting.
*
* @retval       MDL_PM_RET_OK                           Success.
* @retval       MDL_PM_RET_MEM_ALLOC_ERROR              Fail to allocate memory.
* @retval       MDL_PM_RET_UNSUPPORT_DEVICE             Unsupport device.
* @retval       MDL_PM_RET_UNSUPPORT_POWER_REQ          Unsupport power request.
* @retval       MDL_PM_RET_UNSUPPORT_LDO                Unsupport LDO.
* @retval       MDL_PM_RET_UNSUPPORT_VOLTAGE            Unsupport voltage.
* @retval       MDL_PM_RET_REINITIALIZE_LDO             Ldo is initialized already.
* @retval       MDL_PM_RET_UNINITIALIZE_LDO             Ldo is not initialized.
* @retval       MDL_PM_RET_NULL_HANDLER                 No handler for customer LDO.
*
*/
extern MdlPmReturnCode_e MdlPmResPadPowerCtl(DrvPmPowerDomainSetting_t *ptDomainSetting, DrvPmLdoSetting_t *ptLdoSetting);

/** MdlPmResPowerClockStatusReport
* @brief        report power and clock status
*
* @param[in]    ptMap                           power / clock status mapping.
*
* @retval          TRUE                           Success.
* @retval          FALSE                          Fail.
*
*/
extern bool MdlPmResPowerClockStatusReport(MdlPmResStatusMap_t *ptMap);

/** MdlPmResResetSleepModeCounter
* @brief        reset nSleepModeCount
*
* @param[in]    None
*
* @retval          None
*
*/
extern void MdlPmResResetSleepModeCounter(void);

/** MdlPmResIncreaseSleepModeCount
* @brief        Increase nSleepModeCount
*
* @param[in]    None
*
* @retval          None
*
*/
extern void MdlPmResIncreaseSleepModeCount(void);

/** MdlPmResSleepModeReport
* @brief        report nSleepModeCount
*
* @param[in]    None
*
* @retval          nSleepModeCount      sleep mode counter
*
*/
extern u32 MdlPmResSleepModeReport(void);

#endif //__MDL_PM_RES_H__

