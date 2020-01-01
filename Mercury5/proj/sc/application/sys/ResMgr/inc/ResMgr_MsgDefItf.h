/**
* @file ResMgr_MsgDefItf.h
*
* This header file defines the message declation for Resource Manager.
*
*/

#ifndef __RESMGR_MSGDEFITF_H__
#define __RESMGR_MSGDEFITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"

#if !defined(RES_MGR_STANDALONE_DEBUG)
#include "cus_msg.hc"
#endif

#if defined(__SDK_SIMULATION__) && !defined(RES_MGR_STANDALONE_DEBUG)
#include "sys_rtk_vmoshi.h"
#endif

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*================ Audio =====================*/
#if defined(RES_MGR_STANDALONE_DEBUG)
#define RES_MGR_CMD_IND					    1
#define RES_MGR_RSP_IND					    2
#define RES_MGR_CTRL_IND				    3
#define RES_MGR_EVT_IND					    4
#else
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "ResMgr_message_define__.hi"
};
#endif

typedef void* ResMgr_MsgBody_t;
typedef union
{
#if defined(__SDK_SIMULATION__) && !defined(RES_MGR_STANDALONE_DEBUG)
    vm_osTimerMsgBody_t tTimerMsgBody;
#endif
    ResMgr_MsgBody_t pResMgrMsgBody;
} vm_msgBody_t;

#if defined(RES_MGR_STANDALONE_DEBUG)

typedef struct vm_msgHeader_t_
{
    u32 MbxSrc;
    u32 MbxDst;
    u32 TypMsg;
    u32 Length;
} vm_msgHeader_t;

typedef struct vm_msg_t_
{
    vm_msgHeader_t Header;
    vm_msgBody_t Body;
} vm_msg_t;

#else ////#if defined(RES_MGR_STANDALONE_DEBUG)

#include "vm_msgt.ht"

#endif //#if defined(RES_MGR_STANDALONE_DEBUG)

/*=============================================================*/
// Function Declarations
/*=============================================================*/
#endif
