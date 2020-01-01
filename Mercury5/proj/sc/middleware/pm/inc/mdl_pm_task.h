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
* @file    mdl_pm_task.h
* @version
* @brief   Power manager source file for task
*
*/

#ifndef __MDL_PM_TASK_H__
#define __MDL_PM_TASK_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "mdl_pm_cmd.h"

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
/** MdlPmTaskInit
* @brief        Initialize PM task data before task creation
*
* @param[in]
*
* @retval
*
*/
extern void MdlPmTaskInit(void);

/** MdlPmTaskReady
* @brief        Is PM task ready to work
*
* @param[in]
*
* @retval       TRUE                                    Task is ready.
* @retval       FALSE                                   Task is not ready.
*
*/
extern bool MdlPmTaskReady(void);

/** MdlPmInExcep
* @brief        Exception happens; disable pm task and use direct function call to handle commands
*
* @param[in]
*
* @retval
*
*/
extern void MdlPmInExcep(void);

/** MdlPmNonOsHandleCmd
* @brief        PM command handler in non-os mode
*
* @param[in]    ptCmd               Pointer to command buffer.
*
* @retval
*
*/
void MdlPmNonOsHandleCmd(MdlPmCmd_t *ptCmd);

#endif //__MDL_PM_RES_H__

