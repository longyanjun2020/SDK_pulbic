/**
 * \file    mmi_cfgsrv_mitem_info_itemid.h"
 * \brief   The document describes the mutiple items mapping table and these items no need to be configuredby user.
 * \author  eric.chen@mstarsemi.com
 *
 * \page    Configuration Service
 * @version $Id:$
 *  
 */

#ifndef __MMI_CFGSRV_MITEM_INFO_ITEMID_H__
#define __MMI_CFGSRV_MITEM_INFO_ITEMID_H__

#include "mmi_cfgsrv_common_table.h"

/*****************************************
*  Step  1  Add CFG Item 
*****************************************/
enum
{
    CFGIT_MULTIPLE_ITEMS_INFO_START = INFO_ITEM_START
,
    //Item list as below              

    /*Calendar AP*/
    CFGIT_CALENDAR_LAST_USED_UID
,                               //Data type:u32

    /*Setting*/
    CFGIT_CFG_MASTER_RESET_FLAG
,                                //Data type:SET_MASTER_RESET_FLAG_e

    /*Unit Convert*/
    CFGIT_UNITCONVERTER_SELECTION
   ,CFGIT_UNITCONVERTER_DATASTORE
   /*ONOFFAPP*/
#ifdef __EMAPP_SHOW_PROFILING_DATA__
   ,CFGIT_ONOFFAPP_POOL_STATUS
#endif //__EMAPP_SHOW_PROFILING_DATA__
   ,CFGIT_ONOFF_ON_PROCESS_CHECK_POINT
,                             //Data type:ONOFFAPP_OnProcessCheckPoint_e

    /*System*/
    CFGIT_SYS_DEBUG_USB_MENU_FLAG
,                              //SYS_USB_MENU_FLAG_e   
#ifdef __EMAPP_SHOW_PROFILING_DATA__
    CFGIT_SYS_DEBUG_ENABLE_UPDATE_INDICATION
,                   //SYS_DEBUG_FLAG_e
    CFGIT_SYS_DEBUG_ENABLE_MEMORY_SATAUS
,                       //SYS_DEBUG_FLAG_e
    CFGIT_SYS_DEBUG_ENABLE_UPDATE_TIME
,                       //SYS_DEBUG_FLAG_e
#endif // __EMAPP_SHOW_PROFILING_DATA__
    CFGIT_SYS_DEBUG_POWER_ON_OFF_CAUSE
#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
   ,CFGIT_SYS_DEBUG_HIGH_CPU_SPEED_TASK
#endif // __CHECK_CPU_STATUS_BEFORE_SLEEP__
   ,CFGIT_SYS_DEBUG_STACK_PROFILE_INFO
   ,CFGIT_SYS_LANG_PACKED_ID
,                                   //u8 nLangPackedID[RESOURCEID_SIZE]


#ifdef  __FEATURE_POWER_CONSUMPTION_LOG__
    CFGIT_SYS_DEBUG_POWER_CONSUMPTION_LOG_FLAG
   ,
#endif //__FEATURE_POWER_CONSUMPTION_LOG__ 
    CFGIT_SYS_DEBUG_ENABLE_STK_GCF
   ,CFGIT_SYS_HANDSET_BOOT_FIRST_TIME
   ,/*SIMSRV*/
    CFGIT_SIMSRV_SIM_CARD_STATUS
,   //COMMON_SIM_CARD_STATUS_e


    CFGIT_MULTIPLE_ITEMS_INFO_END
};

#endif//__MMI_CFGSRV_MITEM_INFO_ITEMID_H__
