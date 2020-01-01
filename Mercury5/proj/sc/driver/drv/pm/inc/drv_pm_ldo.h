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
* @file    drv_pm_ldo.h
* @version
* @brief   Power manager header file for LDO support functions
*
*/

#ifndef __DRV_PM_LDO_H__
#define __DRV_PM_LDO_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "mdl_pm.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifdef PM_SUPPORT_CUSTOMER_PMIC
#define DRV_PM_FIRST_CUST_LDO     DRV_PM_LDO_CUST_1
#define DRV_PM_LAST_CUST_LDO      DRV_PM_LDO_CUST_8
#endif

#define DRV_PM_VOLT_NONE          DRV_PM_VOLT_INVALID  /* this ldo has no voltage setting */

#define DRV_PM_NULL_LDO_SETTING    {DRV_PM_LDO_INVALID, DRV_PM_STATE_INVALID, DRV_PM_VOLT_INVALID, DRV_PM_STATE_INVALID, DRV_PM_VOLT_INVALID, 0}
#define DRV_PM_NULL_DEVICE_SETTING {MDL_PM_DEV_INVALID, DRV_PM_NULL_LDO_SETTING}
#define DRV_PM_NULL_DOMAIN_SETTING {MDL_PM_DOMAIN_INVALID, DRV_PM_NULL_LDO_SETTING}

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    DRV_PM_LDO_0,
    DRV_PM_LDO_1,
    DRV_PM_LDO_2,
    DRV_PM_LDO_3,
    DRV_PM_LDO_4,
    DRV_PM_LDO_5,
    DRV_PM_LDO_6,
    DRV_PM_LDO_7,
    DRV_PM_LDO_8,
    DRV_PM_LDO_9,
    DRV_PM_LDO_10,
    DRV_PM_LDO_11,
    DRV_PM_LDO_12,
    DRV_PM_LDO_13,
    DRV_PM_LDO_14,
    DRV_PM_LDO_15,
    DRV_PM_LDO_16,
    DRV_PM_LDO_17,
    DRV_PM_LDO_18,
    DRV_PM_LDO_19,
    DRV_PM_LDO_20,
    DRV_PM_LDO_21,
    DRV_PM_LDO_22,
    DRV_PM_LDO_23,
    DRV_PM_LDO_24,
    DRV_PM_LDO_25,
    DRV_PM_LDO_26,
    DRV_PM_LDO_27,
    DRV_PM_LDO_28,
    DRV_PM_LDO_29,
    DRV_PM_LDO_30,
    DRV_PM_LDO_31,
    DRV_PM_LDO_32,
    DRV_PM_LDO_33,
    DRV_PM_LDO_34,
    DRV_PM_LDO_35,
    DRV_PM_LDO_36,
    DRV_PM_LDO_37,
} DrvPmLdo_e;

typedef enum
{
    /* states supported by MStar PMIC */
    DRV_PM_STATE_ON=0,
    DRV_PM_STATE_LQ,
    DRV_PM_STATE_OFF,

#ifdef PM_SUPPORT_CUSTOMER_PMIC
    /* states supported by customer PMIC */
    DRV_PM_STATE_CUST_1,
    DRV_PM_STATE_CUST_2,
    DRV_PM_STATE_CUST_3,
    DRV_PM_STATE_CUST_4,
    DRV_PM_STATE_CUST_5,
    DRV_PM_STATE_CUST_6,
    DRV_PM_STATE_CUST_7,
    DRV_PM_STATE_CUST_8,
#endif

    DRV_PM_STATE_INVALID
} DrvPmPowerState_e;

typedef enum
{
    DRV_PM_VOLT_PASS=0, /*  0: don't change voltage setting */

    /* voltages supported by MStar PMIC */
    DRV_PM_VOLT_1_05,   /*  1 */
    DRV_PM_VOLT_1_1,    /*  2 */
    DRV_PM_VOLT_1_15,   /*  3 */
    DRV_PM_VOLT_1_2,    /*  4 */
    DRV_PM_VOLT_1_25,   /*  5 */
    DRV_PM_VOLT_1_3,    /*  6 */
    DRV_PM_VOLT_1_35,   /*  7 */
    DRV_PM_VOLT_1_5,    /*  8 */
    DRV_PM_VOLT_1_65,   /*  9 */
    DRV_PM_VOLT_1_7,    /* 10 */
    DRV_PM_VOLT_1_75,   /* 11 */
    DRV_PM_VOLT_1_8,    /* 12 */
    DRV_PM_VOLT_1_85,   /* 13 */
    DRV_PM_VOLT_1_9,    /* 14 */
    DRV_PM_VOLT_1_95,   /* 15 */
    DRV_PM_VOLT_2_28,   /* 16 */
    DRV_PM_VOLT_2_5,    /* 17 */
    DRV_PM_VOLT_2_6,    /* 18 */
    DRV_PM_VOLT_2_7,    /* 19 */
    DRV_PM_VOLT_2_8,    /* 20 */
    DRV_PM_VOLT_2_9,    /* 21 */
    DRV_PM_VOLT_3_0,    /* 22 */
    DRV_PM_VOLT_3_1,    /* 23 */
    DRV_PM_VOLT_3_2,    /* 24 */
    DRV_PM_VOLT_3_3,    /* 25 */

    DRV_PM_VOLT_DIFF_600, /* 26 */
    DRV_PM_VOLT_DIFF_550, /* 27 */
    DRV_PM_VOLT_DIFF_500, /* 28 */
    DRV_PM_VOLT_DIFF_450, /* 29 */
    DRV_PM_VOLT_DIFF_400, /* 30 */
    DRV_PM_VOLT_DIFF_350, /* 31 */
    DRV_PM_VOLT_DIFF_300, /* 32 */
    DRV_PM_VOLT_DIFF_250, /* 33 */
    DRV_PM_VOLT_DIFF_200, /* 34 */
    DRV_PM_VOLT_DIFF_150, /* 35 */
    DRV_PM_VOLT_DIFF_100, /* 36 */

#ifdef PM_SUPPORT_CUSTOMER_PMIC
    /* voltages supported by customer PMIC */
    DRV_PM_VOLT_CUST_1, /* 37 */
    DRV_PM_VOLT_CUST_2, /* 38 */
    DRV_PM_VOLT_CUST_3, /* 39 */
    DRV_PM_VOLT_CUST_4, /* 40 */
    DRV_PM_VOLT_CUST_5, /* 41 */
    DRV_PM_VOLT_CUST_6, /* 42 */
    DRV_PM_VOLT_CUST_7, /* 43 */
    DRV_PM_VOLT_CUST_8, /* 44 */
#endif

    DRV_PM_VOLT_INVALID
} DrvPmVolt_e;

typedef struct
{
    DrvPmLdo_e        eLdo;
    DrvPmPowerState_e eActiveState;
    DrvPmVolt_e       eActiveVolt;
    DrvPmPowerState_e eStandbyState;
    DrvPmVolt_e       eStandbyVolt;
    u32               nDelayUs; /* micro second, must > 30 */
} DrvPmLdoSetting_t;

typedef struct
{
    MdlPmDevice_e     eDevice;
    DrvPmLdoSetting_t eLdoSetting;
} DrvPmDeviceSetting_t;

typedef struct
{
    MdlPmPowerDomain_e ePowerDomain;
    DrvPmLdoSetting_t  eLdoSetting;
} DrvPmPowerDomainSetting_t;

typedef MdlPmReturnCode_e (*PfnDrvPmLdoHandler)(DrvPmLdoSetting_t *ptPmLdoSetting);

/*=============================================================*/
// Variable definition
/*=============================================================*/

#include "hal_pm_ldo.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** DrvPmInit
* @brief        Initialize PM DRV layer
*
* @param[in]
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
extern MdlPmReturnCode_e DrvPmInit(void);

/** DrvPmCheckDeviceBitmap
* @brief        Check against device support bitmap
*
* @param[in]    eDevice             The device to check.
*
* @retval       TRUE                                    Device is support.
*
*/
extern bool DrvPmCheckDeviceBitmap(MdlPmDevice_e eDevice);

/** DrvPmCheckPadDomainBitmap
* @brief        Check against pad power domain support bitmap
*
* @param[in]    ePowerDomain        The pad power domain to check.
*
* @retval       TRUE                                    Pad power domain is support.
*
*/
extern bool DrvPmCheckPadDomainBitmap(MdlPmPowerDomain_e ePowerDomain);

/** DrvPmRunDevPowerTable
* @brief        Power manager Power control function
*
* @param[in]    eDevice             The device to turn on/off.
* @param[in]    ePowerReq           Request to turn on/off device.
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
extern MdlPmReturnCode_e DrvPmRunDevPowerTable(MdlPmDevice_e eDevice, MdlPmPowerReq_e ePowerReq);

/** DrvPmRunPadPowerTable
* @brief        Power control function for pad only
*
* @param[in]    ePowerDomain        The power domain to turn on/off.
* @param[in]    ePowerReq           Request to turn on/off device.
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
extern MdlPmReturnCode_e DrvPmRunPadPowerTable(MdlPmPowerDomain_e ePowerDomain, MdlPmPowerReq_e ePowerReq);

/** DrvPmSetSimVoltage
* @brief        Modify power on table for Sim1/Sim2
*
* @param[in]    eDevice             The device to update.
* @param[in]    eSimVolt            New voltage for this device.
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
extern MdlPmReturnCode_e DrvPmSetSimVoltage(MdlPmDevice_e eDevice, MdlPmSimVolt_e eSimVolt);

/** DrvPmSetCoreVoltage
* @brief        Modify power on table for core power
*
* @param[in]    eDevice             The device to update.
* @param[in]    eCoreVolt           New voltage for this device.
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
extern MdlPmReturnCode_e DrvPmSetCoreVoltage(MdlPmDevice_e eDevice, MdlPmCoreVolt_e eCoreVolt);

/** DrvPmSetCoreVoltageDirect
* @brief        Modify modify core voltage directly
*
* @param[in]    eDevice             The device to update.
* @param[in]    eCoreVolt           New voltage for this device.
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
extern MdlPmReturnCode_e DrvPmSetCoreVoltageDirect(MdlPmDevice_e eDevice, MdlPmCoreVolt_e eCoreVolt);

/** DrvPmLdoPrint
* @brief        Print LDO setting
*
* @param[in]    pcPrev              String to print first.
* @param[in]    ptLdoSetting        LDO setting to print.
*
* @retval
*
*/
extern void DrvPmLdoPrint(char *pcPrev, DrvPmLdoSetting_t *ptLdoSetting);

/** _DrvPmFindCustPmIdx
* @brief        Get power manager device index from power manager table
*
* @param[in]    ptDevice                Pointer to power manager device table.
* @param[in]    Device                  Power manager device enum.
*
* @retval       DrvPmDeviceSetting_t *  Pointer to power manager device structure.
*
*/
extern DrvPmDeviceSetting_t * _DrvPmFindCustPmIdx(DrvPmDeviceSetting_t * ptDevice, MdlPmDevice_e Device);

#endif //__DRV_PM_LDO_H__

