///////////////////////////////////////////////////////////////////////////////////////////////////
// mdl_stg2gpd.h storage monitor to notify gpd task func prototype
// create by jeffrey.chen@mstarsemi.com on 2010.03.19
// to define notify mail box structure
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MDL_STG_MSG_H__
#define __MDL_STG_MSG_H__

#include "vm_types.ht"
#include "sys_rtk_vmrtkho.h"
#include "sys_rtk_ho.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "vm_msgof.hc"
#include "sys_sys_mbx_def.h"

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "mdl_stg2gpd_message_define__.hi"
};

typedef enum
{
    MDL_STG_IP_FCIE,
    MDL_STG_IP_SDIO,
    MDL_STG_IP_NMBR,

} MDL_STG_IP;


typedef enum
{
    MDL_STG_TYPE_SDMMC,
    MDL_STG_TYPE_MSPRO,
    MDL_STG_TYPE_NUM,

} MDL_STG_TYPE;

typedef enum
{
    MDL_STG_INSERT,
    MDL_STG_REMOVE,
    MDL_STG_UNKNOW,

} MDL_STG_EVENT;

typedef struct
{
    MDL_STG_IP      StorageIp;
    MsMailbox_e     MailboxId;

} MDL_STG_SUBSCRIBE;


typedef struct
{
    vm_osTimerMsgBody_t     TimerMsg;

    MDL_STG_IP              StorageIp;
    MDL_STG_TYPE            StorageType;
    MDL_STG_EVENT           StorageEvent;
    MDL_STG_SUBSCRIBE       StorageSubscribe;

} MdlStgMsgBody_t;


void MdlStorageMonitorSubscribe(MDL_STG_SUBSCRIBE * Subscribe);
u8 MdlStorageSubscribeBody(MDL_STG_SUBSCRIBE * Subscribe);
void MDrvStorageStatusCallback(MDL_STG_IP StorageIp, MDL_STG_TYPE StorageType, MDL_STG_EVENT StorageEvent);

#endif

