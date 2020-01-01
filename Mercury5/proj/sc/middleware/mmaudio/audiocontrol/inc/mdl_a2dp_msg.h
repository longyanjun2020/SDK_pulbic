////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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
* @file   mdl_a2dp_msg.h
* @version
* @brief
*
*/

#ifndef __MDL_A2DP_MSG_H__
#define __MDL_A2DP_MSG_H__

/*=============================================================*/
// Extern definition
/*=============================================================*/
#include "vm_msgof.hc"
#include "sys_sys_mbx_def.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define A2DP_PLAYCTL_MBX                                VM_MBX_CUS25

#if 0
#define A2DP_THREAD_MESSAGE_BASE                        (u16)(VM_CUS25_BASE)
#define A2DP_CONTROL_MSG                                (u16)(A2DP_THREAD_MESSAGE_BASE + 0x00)
#define A2DP_INTER_MSG                                  (u16)(A2DP_THREAD_MESSAGE_BASE + 0x01)
#define A2DP_HANDSHAKING_CMD_TIMER                      (u16)(A2DP_CONTROL_MSG + 5)
#define A2DP_TESTCMD_TIMER                              (u16)(A2DP_CONTROL_MSG + 6)
#endif

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif

enum{
    VM_MSG_DEF(A2DP_THREAD_MESSAGE_BASE=(VM_CUS25_BASE), void DUMMY)
    VM_MSG_DEF(A2DP_CONTROL_MSG=(A2DP_THREAD_MESSAGE_BASE + 0x00), void DUMMY)
    VM_MSG_DEF(A2DP_INTER_MSG=(A2DP_THREAD_MESSAGE_BASE + 0x01), void DUMMY)
    VM_MSG_DEF(A2DP_HANDSHAKING_CMD_TIMER=(A2DP_CONTROL_MSG + 0x05), void DUMMY)
    VM_MSG_DEF(A2DP_TESTCMD_TIMER=(A2DP_CONTROL_MSG + 0x06), void DUMMY)
};

typedef enum {
    A2DP_THREAD_CMD_NONE,
    A2DP_THREAD_CMD_INIT,
    A2DP_THREAD_CMD_PLAY,
    A2DP_THREAD_CMD_STOP,
    A2DP_THREAD_CMD_PAUSE,
    A2DP_THREAD_CMD_RESUME,
    A2DP_THREAD_CMD_END,
    A2DP_THREAD_CMD_SEEK,
    A2DP_THREAD_CMD_CLOSE,
} MdlA2dpCmd_e;


/**
 *  @brief This enumeration defines the synchronous/asynchronous primtive mechanism
 */
typedef enum {
	MDL_A2DP_SYNC,         /**< Synchronous transaction */
	MDL_A2DP_ASYNC         /**< Asynchronous transaction */
} MdlA2dpTransType_e;

typedef struct
{
    MdlA2dpErrCode_e    *pErrCode;
    MdlA2dpTransType_e   TransType;   /**< Transaction type */
    MdlA2dpCmd_e         ThreadCmd;

    union
    {
        struct
        {
            u32 SampleRate;     /**< sample rate */
            u16 bStereo;         /**< stereo(true) or mono(false) */
        } tPcmParam;
    } tParam;
} MdlA2dpCmd_t;


/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef union
{
    MdlA2dpCmd_t        A2dpCmd;
    vm_osTimerMsgBody_t tTimerMsg;
} vm_msgBody_t;

#include "vm_msgt.ht"


/*=============================================================*/
// Variable definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/


#endif
