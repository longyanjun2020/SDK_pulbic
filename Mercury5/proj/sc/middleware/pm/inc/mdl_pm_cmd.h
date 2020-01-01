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
* @file    mdl_pm_cmd.h
* @version
* @brief   Power manager header file for command interface
*
*/

#ifndef __MDL_PM_CMD_H__
#define __MDL_PM_CMD_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "cus_os.hc"
#include "sys_MsWrapper_cus_os_sem.h"
#include "cus_msg.hc"
#include "mdl_pm.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "mdl_pm_message_define__.hi"
};

#define MDL_PM_CMD_BLOCK    MsConsumeSem(MDL_PM_CMD_QUEUE_SEM)
#define MDL_PM_CMD_UNBLOCK  MsProduceSem(MDL_PM_CMD_QUEUE_SEM)
#define MDL_PM_SYNC_BLOCK   MsConsumeSem(MDL_PM_SYNC_CMD_SEM)
#define MDL_PM_SYNC_UNBLOCK MsProduceSem(MDL_PM_SYNC_CMD_SEM)

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct vm_msg MdlPmCmd_t;

typedef struct
{
    MdlPmDevice_e     eDevice;
    MdlPmPowerReq_e   ePowerReq;
    #ifdef __MDL_PM_CB_USERDATA__
    MdlPmCb_t         *ptPmCb;
    #else
    PfnMdlPmCmdCb     pfnCmdCb;
    #endif
    MdlPmReturnCode_e *peReturnCode;
} MdlPmDevPowerCtlCmd_t;

typedef struct
{
    MdlPmPowerDomain_e ePowerDomain;
    MdlPmPowerReq_e    ePowerReq;
    #ifdef __MDL_PM_CB_USERDATA__
    MdlPmCb_t         *ptPmCb;
    #else
    PfnMdlPmCmdCb     pfnCmdCb;
    #endif
    MdlPmReturnCode_e  *peReturnCode;
} MdlPmPadPowerCtlCmd_t;

typedef struct
{
    MdlPmDevice_e     eDevice;
    MdlPmSimVolt_e    eSimVolt;
    #ifdef __MDL_PM_CB_USERDATA__
    MdlPmCb_t         *ptPmCb;
    #else
    PfnMdlPmCmdCb     pfnCmdCb;
    #endif
    MdlPmReturnCode_e *peReturnCode;
} MdlPmSimPowerOnCtlCmd_t;

typedef struct
{
    MdlPmDevice_e     eDevice;
    MdlPmCoreVolt_e   eCoreVolt;
    #ifdef __MDL_PM_CB_USERDATA__
    MdlPmCb_t         *ptPmCb;
    #else
    PfnMdlPmCmdCb     pfnCmdCb;
    #endif
    MdlPmReturnCode_e *peReturnCode;
} MdlPmCoreVoltageCtlCmd_t;

typedef union
{
    MdlPmDevPowerCtlCmd_t    tDevPowerCtlCmd;
    MdlPmPadPowerCtlCmd_t    tPadPowerCtlCmd;
    MdlPmSimPowerOnCtlCmd_t  tSimPowerOnCtlCmd;
    MdlPmCoreVoltageCtlCmd_t tCoreVoltageCtlCmd;
} vm_msgBody_t;

#include "vm_msgt.ht"

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif //__MDL_PM_CMD_H__

