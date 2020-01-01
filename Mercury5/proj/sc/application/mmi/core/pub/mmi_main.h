/**
 * @file mmi_main.h
 * @version $Id: mmi_main.h 33677 2009-06-17 15:49:36Z mark.yang $
 *
 * @brief The header file defines the prototypes of initializing, terminating, and message parser
 *        functions of MMI task.
 */

#ifndef __MMI_MAIN_H__
#define __MMI_MAIN_H__

#include "sys_sys_bootinit.h"

#ifdef __MMI_POWER_ON_TIME_INF__
#include "mmi_mae_common_def.h"
#include "sys_MsWrapper_cus_os_util.h"

typedef enum
{
    MMI_POWERON_START_TIME,
    MMI_POWERON_KEYPAD_INIT,
    MMI_POWERON_MAE_INIT, // include MMI_POWERON_MAE_CUS_INIT
    MMI_POWERON_MAE_CUS_INIT,
    MMI_POWERON_GLOBAL_VALUE_INIT,
    MMI_POWERON_STATIC_OBJECT_INIT,
    MMI_POWERON_FIRST_APP_ENTRY_TIME,
    MMI_POWERON_PROCESS_EVENT_TIME,
    MMI_POWERON_BACKTRACE_WRITE,
	MMI_POWERON_TASK_INIT_TIME,
    MMI_POWERON_NETWORK_REGIST_TIME1,
    MMI_POWERON_NETWORK_REGIST_TIME2,
    MMI_POWERON_NETWORK_REGIST_TIME3,
    MMI_POWERON_NETWORK_REGIST_TIME4,
    MMI_POWERON_NETWORK_NITZ_TIME1,
    MMI_POWERON_NETWORK_NITZ_TIME2,
    MMI_POWERON_SIM1_ROCK_CLOSE_TIME,
    MMI_POWERON_SIM2_ROCK_CLOSE_TIME,
    MMI_POWERON_SIM1_FUNREQ_TIME,
    MMI_POWERON_SIM2_FUNREQ_TIME,
    MMI_POWERON_SIM1_PRESENT_TIME,
    MMI_POWERON_SIM2_PRESENT_TIME,  
    MMI_POWERON_ONAPP_INIT_TIME,
    MMI_POWERON_ONAPP_LOGO_TIME,
    MMI_POWERON_ONAPP_MENU_TIME,
    MMI_POWERON_ONAPP_ANIM_TIME,
    MMI_POWERON_ONAPP_SEARCH_TIME,
    MMI_POWERON_ONAPP_SECURITY_TIME,
    MMI_POWERON_ONAPP_CHECK_SIM_READY_TIME,
    MMI_POWERON_SIM1_READY_TIME,
    MMI_POWERON_SIM2_READY_TIME,
    MMI_POWERON_ONAPP_SEARCH_WAIT_TIME,   
    MMI_POWERON_IDLE_ENTRY_TIME,
    MMI_POWERON_TIME_MAX
} MMI_PowerOnTimeType_e;

typedef struct
{
    u32 u32LastRecordTime;
    u32 au32Times[MMI_POWERON_TIME_MAX];
} MMI_PowerOnTimeInf_t;

void mmi_SetPowerOnTime(MMI_PowerOnTimeType_e eType, boolean bIsDuration, boolean bIsDiff);
u32 mmi_GetPowerOnTime(MMI_PowerOnTimeType_e eType);

#endif /* __MMI_POWER_ON_TIME_INF__ */

/**
 * The entry function of MMI task.
 */
__ONCE_CALL_ON_BOOT__ void MMI_Task_Init(void);

/**
 * The exit function of MMI task.
 */
void MMI_Task_Terminate(void);

/** 
 * The message parser function for MMI task.
 */
void MMI_Task_ParseMsg(void*);


#endif /* __MMI_MAIN_H__ */
