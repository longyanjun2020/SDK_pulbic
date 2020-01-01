////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
* @file    vt_dbg.h
* @version
* @brief   APIs
*
*/
#ifndef __VT_DBG_H__
#define __VT_DBG_H__

#include "sys_vm_dbg.ho"
#include "vt_api.h"

#define USE_TMT_TRACE
//#define USE_TRM_TRACE

#define DBG_VT_324M     (_CUS1 | LEVEL_28)
#define DBG_VT_324M1    (_CUS1 | LEVEL_29)
#define DBG_VT_VDR      (_CUS1 | LEVEL_30) //VDR
#define DBG_VT_324M2    (_CUS1 | LEVEL_31)

#define DISABLE_VT_DEBUG_ALL_LEVEL             0

#if !DISABLE_VT_DEBUG_ALL_LEVEL
#define ENABLE_VT_DEBUG_LEVEL_NORMAL       1
#define ENABLE_VT_DEBUG_LEVEL_DETAILS       0
#endif

///////////////////////////////stack definitions
#define USE_3G324M_STACK 1
#define VT_SEND_MES_WITH_OLC 0
//#define USE_AUTO_CAPS
//#define VT_ENABLE_MONA
#define USE_MANUAL_HANDLE_REC_H245_MSG 1
#define VT_ENABLE_CH_SEND_DATA_EXT 1
#define VT_INIT_3G324M_PER_VTCALL 1
#define VT_ENABLE_VIDEO_SEGMENTABLE 1
#define VT_ENABLE_DYNAMIC_ALLOCATE_AVBUFFER 1

//option testing
#define VT_ENABLE_HANDLE_STACK_DATA_PENDING 0
#define VT_USE_2TASK 0
#define VT_EMPTY_FRAME_APPEND 0
#define VT_ENABLE_REMOTE_LOOPBACK 0
//#define USE_3G324M_TESTING
//#define USE_TEST_VDRAVP
//#define USE_STATISTICS
//#define CHECK_VT_MEDIA
//#define DEBUG_CHECKSUM
//#define DEBUG_CHECKTIMER

#if ENABLE_VT_DEBUG_LEVEL_NORMAL
#define VT_RVSTACK_STDIO_APIS 1
#define VT_ENABLE_UPDATE_HEAP_INFO 1
#define VT_ENABLE_TOCHECK_LOST_FRAME 1
#define VTUPDATE_INFO_DEPEND_ON_AUDIO_COUNTER 0
#define VT_ENABLE_UPDATE_VT_INFO    1
#define VT_CHECK_SEND_PDU_TIMER 1
#define VT_CHECK_RECV_PDU_TIMER 1
#define VT_ENABLE_TIMER_CALLBACK 0
#define DEBUG_CHECKMBOXCNT 1
#define DEBUG_CHECKAVSQNUMBER 1  
#endif

#if ENABLE_VT_DEBUG_LEVEL_DETAILS
//#define VT_ENABLE_LOG2FILE
#define DEBUG_CHECK3G324M_BS 1
#define DEBUG_CHECKTMTCUS1_LV31 1
#define DEBUG_CHECK3G324M_BS_INOUT 0
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////// Loopback definitions
#define STACK_LOOPBACK_VTLIKE //simulate 64kbps as H324M
//#define USE_LOOPBACK_AUTO_CAPS
//#define USE_LOOPBACK_MANUAL_HANDLE_REC_H245_MSG
//#define VT_LOOPBACK_OPTIONAL //enable all possibel callback function and some are not implemented yet
#define STACK_LOOPBACK_REMOTE2LOCAL //for testing channel on/off feature and enable channel2 send control data to channel1
//#define LOOPBACK_SUPPORT_MONA
//#define VTMUX_LOOPBACK_TEST
#define VT_LOOPBACK_CH_SEND_DATA_EXT
//#define VT_LOOPBACK_LOG2FILE
#define VT_LOOPBACK_SIMULATE_VT_FLOW //simulate Vt call flow
//#define VT_LOOPBACK_INIT_3G324M_PER_VTCALL
#define VT_LOOPBACK_CHECK_LOST_FRAME 1
#define VT_LOOPBACK_CHECK_VT_INFO 1

#if defined( VTMUX_TEST) || defined (VTMUX_LOOPBACK_TEST)
#define VTMUX_CMD_INIT_FRAME_NUM                                 100
#define VTMUX_CMD_START_FRAME_NUM                              VTMUX_CMD_INIT_FRAME_NUM+30
#define VTMUX_CMD_STOP_FRAME_NUM                                800
#define VTMUX_CMD_SAVE_FRAME_NUM                                VTMUX_CMD_STOP_FRAME_NUM+50
#define VTMUX_CMD_SAVE_DONE_FRAME_NUM                      VTMUX_CMD_SAVE_FRAME_NUM+50
#define VTMUX_CMD_WDATA_UPPER_BOUND_FRAME_NUM    VTMUX_CMD_STOP_FRAME_NUM
#define VTMUX_CMD_WDATA_LOWER_BOUND_FRAME_NUM   VTMUX_CMD_START_FRAME_NUM+2

#define VTMUX_DENOMINATOR_VALUE                                    1000//0xFFFFFFFF
#define VTMUX_FILES_NUMBER                                                1*1000//VTMUX_DENOMINATOR_VALUE
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef USE_TMT_TRACE
#define vt_trace(x, y, ...) mdl_vt_stack_printf(1, x, y, ##__VA_ARGS__)
#define vt_error(x, y, ...) mdl_vt_stack_printf(2, x, y, ##__VA_ARGS__)
#define vt_dbg(x, y, ...) mdl_vt_stack_printf(2, x, y, ##__VA_ARGS__)
#elif defined(USE_TRM_TRACE)
#define vt_trace(level, format, args...) UartSendTrace(format, ##args)
#define vt_error(level, format, args...) UartSendTrace(format, ##args)
#else
#define vt_trace(level, format, args...)
#define vt_error(level, format, args...)
#endif

#endif

