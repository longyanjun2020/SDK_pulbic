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

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_system.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


#ifndef __MDL_VDR_SYSTEM_H__
#define __MDL_VDR_SYSTEM_H__


#if defined(__cplusplus)
extern "C" {
#endif


//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"

#include "sys_vm_dbg.ho"

#if defined(__I_SW__)
#include "sys_sys_isw_cli.h"
#endif
//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Macro Definition
//-----------------------------------------------------------------------------
#if defined(VDR_SLDLM)
#include "sys_sys_dlm_mgr.h"
#endif

#define ENABLE_DYNAMIC_PRIORITY                         0

#if !defined(__I_SW__)
#define ENABLE_MDLVDR_DYNAMIC_VIDEO_THREAD               1
#define ENABLE_MDLVDR_DYNAMIC_AUDIO_THREAD               1
#define ENABLE_MDLVDR_DYNAMIC_WRITE_THREAD               1
#endif

#define MDLVDR_MBX_MMRMGR       0xFFFF

#if defined(__I_SW__)
#define MDLVDR_MBX_BASE         3   // order in init.c/cus_InitTask[]
#else
#define MDLVDR_MBX_BASE         VM_MBX_CUS27
#endif

#define MDLVDR_MBX_MAIN         (MDLVDR_MBX_BASE)
#if ENABLE_MDLVDR_DYNAMIC_VIDEO_THREAD
extern MsTaskId_e               g_nMdlVdrVideoTaskId;
#define MDLVDR_MBX_VIDEO        g_nMdlVdrVideoTaskId
#else
#define MDLVDR_MBX_VIDEO        (MDLVDR_MBX_BASE + 1)
#endif // ENABLE_MDLVDR_DYNAMIC_VIDEO_THREAD
#if ENABLE_MDLVDR_DYNAMIC_AUDIO_THREAD
extern MsTaskId_e               g_nMdlVdrAudioTaskId;
#define MDLVDR_MBX_AUDIO        g_nMdlVdrAudioTaskId
#else
#define MDLVDR_MBX_AUDIO        (MDLVDR_MBX_BASE + 2)
#endif // ENABLE_MDLVDR_DYNAMIC_AUDIO_THREAD
#if ENABLE_MDLVDR_DYNAMIC_WRITE_THREAD
extern MsTaskId_e               g_nMdlVdrWriteTaskId;
#define MDLVDR_MBX_WRITE        g_nMdlVdrWriteTaskId
#else
#define MDLVDR_MBX_WRITE        (MDLVDR_MBX_BASE + 3)
#endif // ENABLE_MDLVDR_DYNAMIC_WRITE_THREAD
#define MDLVDR_MBX_WHITE_BOX    VM_MBX_CUS57

// Message Type
#define MDLVDR_MSG_TYPE_TIMEOUT    0
#define MDLVDR_MSG_TYPE_INTERNAL   1
#define MDLVDR_MSG_TYPE_EXTERNAL   2

// Thread Priority
#define MDLVDR_VIDEO_THREAD_PRIORITY                36
#define MDLVDR_VIDEO_THREAD_LOW_PRIORITY             7
#define MDLVDR_AUDIO_THREAD_PRIORITY                35
#define MDLVDR_AUDIO_THREAD_LOW_PRIORITY             7
#define MDLVDR_WRITE_THREAD_PRIORITY                34
#define MDLVDR_WRITE_THREAD_LOW_PRIORITY             7


//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum MdlVdrCmd
{
#include "mdl_vdr_message_define__.hi"
} MdlVdrCmd_e;


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------
#define VdrMsg_t                                vm_msg_t
#define VDR_TMT_LV1     (_CUS1|LEVEL_30)

extern u32 _MdlVdrSendMsg(u16 MbxSrc, u16 MbxDst, u32 u32Msg);

#if !defined(__I_SW__)
#if defined(__SDK_SIMULATION__)
#define VDR_TMT_DBG
#else
#define VDR_TMT_DBG
#endif
#endif

#ifdef VDR_TMT_DBG
#include "sys_traces.ho"
// Marcos
// vm_dbgTrace
// _TRACE
//vm_dbgError

// Example:
// vm_dbgTrace(VDR_TMT_LV1, "SD space full: RecTotalSize: 0x%x, u32ThresholdSize: 0x%x, cached: 0x%x, FreeCapicity: 0x%x\n",
//            u32rectotalsize, u32ThresholdSize, u32reccacedsize, pmenc->storageFree);
// _TRACE((VDR_TMT_LV1, "..."));
// vm_dbgTrace((VDR_TMT_LV1, "Func=<SYMBOL> (0x%08x)\n", __LINE__));

// NOTICE:
// (1) %s is not allowed
// (2) _TRACE must use double brackets
#else
// for the case TMT is not available

#ifndef __SDK_SIMULATION__
#include "sys_sys_tools.h"

#define send_trace_vdr sys_UartPrintf
#else
#define send_trace_vdr
#endif

#ifdef  vm_dbgTrace
#undef  vm_dbgTrace
#endif

#ifdef _TRACE
#undef _TRACE
#endif

#ifdef vm_dbgError
#undef vm_dbgError
#endif

#define vm_dbgTrace(_level_, _format_, ...) send_trace_vdr(_format_, ##__VA_ARGS__)

#define _TRACE(_level_, _format_, ...) send_trace_vdr(_format_, ##__VA_ARGS__)

#define vm_dbgError(_level_, _format_, ...) send_trace_vdr(_format_, ##__VA_ARGS__)

#endif


#if defined(__cplusplus)
}
#endif


#endif // __MDL_VDR_SYSTEM_H__

