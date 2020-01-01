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
* @file    mdl_pm.h
* @version
* @brief   Power manager header file for public interface
*
*/

#ifndef __MDL_PM_H__
#define __MDL_PM_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "sys_traces.ho"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MDL_PM_TRACE (_IOB|LEVEL_24)
#define MDL_PM_ERROR (_IOB|LEVEL_24)
#define MDL_PM_FATAL (_IOB|LEVEL_24|FATAL)

#define MDL_PM_CORE_VOLT_DEFAULT MDL_PM_CORE_VOLT_1_2


//#define __MDL_PM_CB_USERDATA__
#if !defined(__MDL_PM_CB_USERDATA__) && !defined(__AUTO_CPU_SPEED__)
#define PM_DIRECT_CALL_FOR_CORE_VOLTAGE_CTL_CMD
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    MDL_PM_RET_OK=0,
    MDL_PM_RET_MEM_ALLOC_ERROR,
    MDL_PM_RET_UNSUPPORT_COMMAND,
    MDL_PM_RET_UNSUPPORT_DEVICE,
    MDL_PM_RET_UNSUPPORT_DOMAIN,
    MDL_PM_RET_UNSUPPORT_POWER_REQ,
    MDL_PM_RET_UNSUPPORT_LDO,
    MDL_PM_RET_UNSUPPORT_POWER_STATE,
    MDL_PM_RET_UNSUPPORT_VOLTAGE,
    MDL_PM_RET_REINITIALIZE_LDO,
    MDL_PM_RET_UNINITIALIZE_LDO,
    MDL_PM_RET_NULL_HANDLER,
    MDL_PM_RET_GENERIC_FAILURE,
} MdlPmReturnCode_e;

typedef enum
{
    MDL_PM_DEV_ATV=0,       /* ATV            */
    MDL_PM_DEV_AUDIO,       /* audio          */
    MDL_PM_DEV_BT,          /* Bluetooth      */
    MDL_PM_DEV_CORE,        /* core           */
    MDL_PM_DEV_DISP_ENG,    /* display engine */
    MDL_PM_DEV_DTV,         /* DTV            */
    MDL_PM_DEV_ENG_MODE,    /* engineer mode  */
    MDL_PM_DEV_FM,          /* FM radio       */
    MDL_PM_DEV_G3D_ENG,     /* G3D engine     */
    MDL_PM_DEV_GPS,         /* GPS            */
    MDL_PM_DEV_GSENSOR,     /* G-sensor       */
    MDL_PM_DEV_I2C,         /* I2C            */
    MDL_PM_DEV_I3_ADC,      /* Incense ADC    */
    MDL_PM_DEV_LCD,         /* LCD            */
    MDL_PM_DEV_MONTAGE,     /* MMP            */
    MDL_PM_DEV_NAND,        /* Nand           */
    MDL_PM_DEV_OFN,         /* OFN            */
    MDL_PM_DEV_RF_ABB,      /* flight mode    */
    MDL_PM_DEV_RF_DIG,      /* RF             */
    MDL_PM_DEV_SD,          /* memory card    */
    MDL_PM_DEV_SD2,         /* memory card    */
    MDL_PM_DEV_SENSOR,      /* Camera         */
    MDL_PM_DEV_SIM1,        /* SIM1           */
    MDL_PM_DEV_SIM2,        /* SIM2           */
    MDL_PM_DEV_TOUCHSCREEN, /* touch screen, R-type   */
    MDL_PM_DEV_TOUCHSCREEN_CTYPE, /* touch screen, C-type   */
    MDL_PM_DEV_WIFI,        /* WLAN           */
    MDL_PM_DEV_CALL,        /* CALL           */
    MDL_PM_DEV_ASURA_CLASSD,/* audio Asura class D */    
#ifdef __PROXIMITY_SENSOR_DRV__
    MDL_PM_DEV_PROXIMITY_SENSOR, /* Proximity Sensor */
#endif
#ifdef __BALL_DRV__
    MDL_PM_DEV_BALL,        /* Ball           */
#endif
    MDL_PM_DEV_BACKLIGHT,

#ifdef __RFID__
	MDL_PM_DEV_RFID,		/* 24: RFID 		  */
#endif	//__RFID__

    MDL_PM_DEV_INVALID
} MdlPmDevice_e;

typedef enum
{
    MDL_PM_PWR_REQ_ON=0,
    MDL_PM_PWR_REQ_OFF,
    MDL_PM_PWR_REQ_INVALID
} MdlPmPowerReq_e;

typedef enum
{
    MDL_PM_SIM_VOLT_1_8=0,
    MDL_PM_SIM_VOLT_2_9,
    MDL_PM_SIM_VOLT_INVALID
} MdlPmSimVolt_e;

typedef enum
{
    MDL_PM_CORE_VOLT_1_2=0,
    MDL_PM_CORE_VOLT_1_3,
    MDL_PM_CORE_VOLT_INVALID
} MdlPmCoreVolt_e;

typedef enum
{
    MDL_PM_DOMAIN_0=0,
    MDL_PM_DOMAIN_1,
    MDL_PM_DOMAIN_2,
    MDL_PM_DOMAIN_3,
    MDL_PM_DOMAIN_4,
    MDL_PM_DOMAIN_5,
    MDL_PM_DOMAIN_6,
    MDL_PM_DOMAIN_7,
    MDL_PM_DOMAIN_8,
    MDL_PM_DOMAIN_9,
    MDL_PM_DOMAIN_10,
    MDL_PM_DOMAIN_11,
    MDL_PM_DOMAIN_12,
    MDL_PM_DOMAIN_13,
    MDL_PM_DOMAIN_14,
    MDL_PM_DOMAIN_15,
    MDL_PM_DOMAIN_16,
    MDL_PM_DOMAIN_17,
} MdlPmPowerDomain_e;

#ifdef __MDL_PM_CB_USERDATA__
typedef void (*PfnMdlPmCmdCb)(MdlPmReturnCode_e eReturnCode, void *pnUserData);

typedef struct {
	PfnMdlPmCmdCb  pfnCb;
  void           *pnUserData;
} MdlPmCb_t;
#else
typedef void (*PfnMdlPmCmdCb)(MdlPmReturnCode_e eReturnCode);
#endif

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** MdlPmInit
* @brief        Power manager initialize function
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
extern MdlPmReturnCode_e MdlPmInit(void);

/** MdlPmDevPowerCtl
* @brief        Power control function for a device
*
* @param[in]    eDevice             The device to turn on/off.
* @param[in]    ePowerReq           Request to turn on/off device.
* @param[in]    pfnCmdCb            Callback function for result.
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
#ifdef __MDL_PM_CB_USERDATA__
extern MdlPmReturnCode_e MdlPmDevPowerCtl(MdlPmDevice_e eDevice, MdlPmPowerReq_e ePowerReq, MdlPmCb_t *ptPmCb);
#else
extern MdlPmReturnCode_e MdlPmDevPowerCtl(MdlPmDevice_e eDevice, MdlPmPowerReq_e ePowerReq, PfnMdlPmCmdCb pfnCmdCb);
#endif

/** MdlPmPadPowerCtl
* @brief        Power control function for pad only
*
* @param[in]    ePowerDomain        The power domain to turn on/off.
* @param[in]    ePowerReq           Request to turn on/off device.
* @param[in]    pfnCmdCb            Callback function for result.
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
#ifdef __MDL_PM_CB_USERDATA__
extern MdlPmReturnCode_e MdlPmPadPowerCtl(MdlPmPowerDomain_e ePowerDomain, MdlPmPowerReq_e ePowerReq, MdlPmCb_t *ptPmCb);
#else
extern MdlPmReturnCode_e MdlPmPadPowerCtl(MdlPmPowerDomain_e ePowerDomain, MdlPmPowerReq_e ePowerReq, PfnMdlPmCmdCb pfnCmdCb);
#endif

/** MdlPmSimPowerOnCtl
* @brief        Power control function for device Sim1/Sim2 only
*
* @param[in]    eDevice             The device to turn on.
* @param[in]    eSimVolt            Voltage set to device.
* @param[in]    pfnCmdCb            Callback function for result.
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
#ifdef __MDL_PM_CB_USERDATA__
extern MdlPmReturnCode_e MdlPmSimPowerOnCtl(MdlPmDevice_e eDevice, MdlPmSimVolt_e eSimVolt, MdlPmCb_t *ptPmCb);
#else
extern MdlPmReturnCode_e MdlPmSimPowerOnCtl(MdlPmDevice_e eDevice, MdlPmSimVolt_e eSimVolt, PfnMdlPmCmdCb pfnCmdCb);
#endif

/** MdlPmCoreVoltageCtl
* @brief        Voltage vote function for core power
*
* @param[in]    eDevice             The device to request voltage change.
* @param[in]    eCoreVolt           Voltage set to core.
* @param[in]    pfnCmdCb            Callback function for result.
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
#ifdef __MDL_PM_CB_USERDATA__
extern MdlPmReturnCode_e MdlPmCoreVoltageCtl(MdlPmDevice_e eDevice, MdlPmCoreVolt_e eCoreVolt, MdlPmCb_t *ptPmCb);
#else
extern MdlPmReturnCode_e MdlPmCoreVoltageCtl(MdlPmDevice_e eDevice, MdlPmCoreVolt_e eCoreVolt, PfnMdlPmCmdCb pfnCmdCb);
#endif

#endif //__MDL_PM_H__

