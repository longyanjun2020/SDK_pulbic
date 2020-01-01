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
* @file    drv_clkgen_cmu_forward.h
* @version
* @brief   Clock Management Unit driver
*
*/

#ifndef __DRV_CLKGEN_CMU_API_H__
#define __DRV_CLKGEN_CMU_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "vm_types.ht"
#include "sys_sys_vm_sys.h"
#include "drv_clkgen_cmu_forward.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 * @defgroup Clkgen_Drv
 *
 **/

/** \addtogroup Clkgen_Drv
 *  @{
 */

/**
 * \fn ClkgenResult_e DrvClkgenInit(ClkgenClkSpeed_e eC0CoreClkSpeed)
 * \brief Initial platform clock data structure. Initial CPU clock by given clock speed, and bbtop clock initial.
 * \param[in] ClkgenClkSpeed_e eC0CoreClkSpeed - Initial CPU speed.
 * \return Always CLKGEN_SUCCESS.
 */
extern ClkgenResult_e DrvClkgenInit(ClkgenClkSpeed_e eC0CoreClkSpeed);

/**
 * \fn ClkgenClkSpeed_e DrvClkgenGetCpuStallSpeed(vm_sys_SpeedProfile_e eSpeedProfile, u8 nE2pIndex)
 * \brief Get CPU speed mapping by given speed profile or e2p index.
 * \param[in] vm_sys_SpeedProfile_e eSpeedProfile.
 * \param[in] u8 nE2pIndex.
 * \return CPU speed.
 */
extern ClkgenClkSpeed_e DrvClkgenGetCpuStallSpeed(vm_sys_SpeedProfile_e eSpeedProfile, u8 nE2pIndex);

/**
 * \fn ClkgenResult_e DrvClkgenDrvSetMaxMiuSpeed(ClkgenClkSpeed_e eClkSpeed)
 * \brief Save the maximum MIU speed level of the platform to the clkgen data structure, this is not used to set MIU speed.
 * \param[in] ClkgenClkSpeed_e eClkSpeed - Maximum MIU speed.
 * \return Always CLKGEN_SUCCESS.
 */
extern ClkgenResult_e DrvClkgenDrvSetMaxMiuSpeed(ClkgenClkSpeed_e eClkSpeed);

/**
 * \fn ClkgenResult_e DrvClkgenDrvClockCtl(ClkgenModule_e eModule, ClkgenClkReq_e eClkReq)
 * \brief Device/Task request relative clock On/Off.
 * \param[in] ClkgenModule_e eModule - request device/task.
 * \param[in] ClkgenClkReq_e eClkReq - On/Off.
 * \return CLKGEN_SUCCESS - On/Off ok.
 * \return CLKGEN_INVALID_PARAMETER - Module invalid, or redudant request.
 */
extern ClkgenResult_e DrvClkgenDrvClockCtl(ClkgenModule_e eModule, ClkgenClkReq_e eClkReq);

/**
 * \fn ClkgenResult_e DrvClkgenDrvClockUpdate(ClkgenModule_e eModule, ClkgenClkUpdate_e eClk, ClkgenClkSpeed_e eClkSpeed)
 * \brief Device/Task update specific clock speed.
 * \param[in] ClkgenModule_e eModule - request device/task.
 * \param[in] ClkgenClkUpdate_e eClk - specific clock.
 * \param[in] ClkgenClkReq_e eClkReq - On/Off.
 * \return CLKGEN_SUCCESS - On/Off ok.
 * \return CLKGEN_INVALID_PARAMETER - Module invalid, or module did not request On first.
 */
extern ClkgenResult_e DrvClkgenDrvClockUpdate(ClkgenModule_e eModule, ClkgenClkUpdate_e eClk, ClkgenClkSpeed_e eClkSpeed);

/**
 * \fn ClkgenResult_e DrvClkgenDrvClockSelectSrc(ClkgenModule_e eModule, ClkgenClkUpdate_e eClk, U16 nClkSrc)
 * \brief Device/Task update specific clock speed.
 * \param[in] ClkgenModule_e eModule - request device/task.
 * \param[in] ClkgenClkUpdate_e eClk - specific clock.
 * \param[in] U16 nClkSrc - specify clock source.
 * \return CLKGEN_SUCCESS - On/Off ok.
 * \return CLKGEN_INVALID_PARAMETER - Module invalid, or module did not request On first.
 */
extern ClkgenResult_e DrvClkgenDrvClockSelectSrc(ClkgenModule_e eModule, ClkgenClkUpdate_e eClk, U16 nClkSrc);

/**
 * \fn bool DrvClkgenModIsEnable(ClkgenModule_e eModule)
 * \brief Check Device/Task has requested on or not.
 * \param[in] ClkgenModule_e eModule - request device/task.
 * \return TRUE - Module is On.
 * \return FALSE - Module is Off or did not request before.
 */
extern bool DrvClkgenModIsEnable(ClkgenModule_e eModule);

/**
 * \fn ClkgenResult_e DrvClkgenChangeCpuClock(ClkgenClkSpeed_e eNewSpeed)
 * \brief Change CPU speed by given speed.
 * \param[in] ClkgenClkSpeed_e eNewSpeed - request speed.
 * \return CLKGEN_SUCCESS - Setting speed success.
 * \return CLKGEN_INTERNAL_ERROR - Should not happen, happen when CPU clock did not initial.
 */
extern ClkgenResult_e DrvClkgenChangeCpuClock(ClkgenClkSpeed_e eNewSpeed);

/**
 * \fn ClkgenResult_e DrvClkgenFixedCpuClock(ClkgenClkSpeed_e eNewSpeed)
 * \brief Change CPU speed by given speed and fix at this speed.
 * \param[in] ClkgenClkSpeed_e eNewSpeed - request speed.
 * \return CLKGEN_SUCCESS - Setting speed success.
 */
extern ClkgenResult_e DrvClkgenFixedCpuClock(ClkgenClkSpeed_e eNewSpeed);

/**
 * \fn ClkgenResult_e DrvClkgenChangeDspClock(ClkgenClkSpeed_e eNewSpeed)
 * \brief Change DSP speed by given speed.
 * \param[in] ClkgenClkSpeed_e eNewSpeed - request speed.
 * \return CLKGEN_SUCCESS - Setting speed success.
 * \return CLKGEN_INTERNAL_ERROR - Should not happen, happen when DSP clock did not initial.
 */
extern ClkgenResult_e DrvClkgenChangeDspClock(ClkgenClkSpeed_e eNewSpeed);

/**
 * \fn ClkgenResult_e DrvClkgenGetCpuClock(ClkgenClkSpeed_e *peCpuSpeed)
 * \brief Get CPU clock frequency.
 * \param[out] ClkgenClkSpeed_e *peCpuSpeed - CPU speed.
 * \return CLKGEN_SUCCESS - Get speed success.
 * \return CLKGEN_INTERNAL_ERROR - Should not happen, happen when CPU clock did not initial.
 * \return CLKGEN_INVALID_PARAMETER - peCpuSpeed = NULL.
 */
extern ClkgenResult_e DrvClkgenGetCpuClock(ClkgenClkSpeed_e *peCpuSpeed);

/**
 * \fn ClkgenResult_e DrvClkgenGetDspClock(ClkgenClkSpeed_e *peDspSpeed)
 * \brief Get CPU clock frequency.
 * \param[out] ClkgenClkSpeed_e *peDspSpeed - DSP speed.
 * \return CLKGEN_SUCCESS - Get speed success.
 * \return CLKGEN_INTERNAL_ERROR - Should not happen, happen when DSP clock did not initial.
 * \return CLKGEN_INVALID_PARAMETER - peDspSpeed = NULL.
 */
extern ClkgenResult_e DrvClkgenGetDspClock(ClkgenClkSpeed_e *peDspSpeed);

extern ClkgenResult_e DrvClkgenEnableClock(PeriphType_e eHWIP, bool bEnable);

/**
 * \fn ClkgenResult_e DrvClkgenEnableReset(PeriphType_e eHWIP, bool bEnable)
 * \brief Enable reset of CMU peripheral by given HWIP.
 * \param[in] PeriphType_e eHWIP - request IP.
 * \param[in] bool bEnable - On/Off.
 * \return CLKGEN_SUCCESS - Reset success.
 * \return CLKGEN_INTERNAL_ERROR - Invalid IP.
 */
extern ClkgenResult_e DrvClkgenEnableReset(PeriphType_e eHWIP, bool bEnable);

/**
 * \fn ClkgenResult_e DrvClkgenEnablePower(PeriphType_e eHWIP, bool bEnable)
 * \brief Enable power of CMU peripheral by given HWIP.
 * \param[in] PeriphType_e eHWIP - request IP.
 * \param[in] bool bEnable - On/Off.
 * \return CLKGEN_SUCCESS - Reset success.
 * \return CLKGEN_INTERNAL_ERROR - Invalid IP.
 */
extern ClkgenResult_e DrvClkgenEnablePower(PeriphType_e eHWIP, bool bEnable);

/**
 * \fn ClkgenResult_e DrvClkgenCheckCpuClock(ClkgenClkSpeed_e eSpeed)
 * \brief Check speed profile mapping with the given speed of CPU is support or not.
 * \param[in] ClkgenClkSpeed_e eSpeed.
 * \return CLKGEN_SUCCESS - Given speed is spport in current speed profile.
 * \return CLKGEN_SPEED_NOT_SUPPORT - Given speed is not spport in current speed profile.
 */
extern ClkgenResult_e DrvClkgenCheckCpuClock(ClkgenClkSpeed_e eSpeed);
extern ClkgenClkSpeed_e DrvClkgenGetC0CoreOCSpeed(void);
extern void DrvClkgenMdcgDma2dEn(void);

/**
 * \fn bool DrvClkgenIsForceOn26MHz(void)
 * \brief Check if 26M is force On or not.
 * \return TRUE - 26M is force On.
 * \return FALSE - 26M is not force On.
 */
//extern bool DrvClkgenIsForceOn26MHz(void);
/** @}*/

extern ClkgenResult_e DrvClkgenAutoCpuSpeed(ClkgenClkSpeed_e eSpeed);
extern ClkgenResult_e DrvClkgenutoCpuGetSpeedInfo(void **eppSpeedTab, u8 *pTblSize);
extern u32 DrvClkgenGetPllSwitchTable(void);
extern u32 DrvClkgenModuleGetClkSwitchBitmap(void);
extern u32 DrvClkgenBbtopGetClkSwitchBitmap(void);
extern void DrvClkgenModuleSetMemClock(void);
extern ClkgenResult_e DrvClkgenInitSec(void);

/**
 * \fn  u32 DrvClkgenTopGetClkEnableCount((ClkgenTopClk_e eTopClk)
 * \brief Get clk enable count.
 * \param[in] ClkgenTopClk_e eTopClk - requested clock.
 * \return clock enable count.
 */
extern u32 DrvClkgenTopGetClkEnableCount(ClkgenTopClk_e eTopClk);

/**
 * \fn  ClkgenClkSpeed_e DrvClkgenTopGetClkRate(ClkgenTopClk_e eTopClk)
 * \brief Get clk speed.
 * \param[in] ClkgenTopClk_e eTopClk - requested clock.
 * \return ClkgenClkSpeed_e eSpeed, CLKGEN_INVALID for no clock rate information.
 */
extern ClkgenClkSpeed_e DrvClkgenTopGetClkRate(ClkgenTopClk_e eTopClk);

#endif //__DRV_CLKGEN_CMU_API_H__

