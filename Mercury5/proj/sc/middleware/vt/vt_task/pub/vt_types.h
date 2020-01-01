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
* @file    vt_types.h
* @version
* @brief   video telephony definitions
*
*/
#ifndef __VT_TYPES_H__
#define __VT_TYPES_H__

#include "vm_msgof.hc"
#include "osdefs.hc"

#if defined( __VT_3G324M__)
//3G324M headers
#include "Rv3G324m.h"
#endif

#define VT_GET_LOWBYTE(a)   (u32)(((u64)a)&0xFFFFFFFF)
#define VT_GET_HIGHBYTE(a)  (u32)(((u64)(a)>>32)&0xFFFFFFFF)

typedef enum
{
    VT_TEST_STACK_TO_MODEM_DISABLE = 0,
    VT_TEST_STACK_TO_MODEM_ENABLE = 1,
}VTestStackType_e;

typedef enum
{
    VT_TEST_STACK_DUMP_BITSTREAM_DISABLE = 0,
    VT_TEST_STACK_DUMP_BITSTREAM_ENABLE = 1,
}VTestStackDumpBitStream_e;

/* Signal Interface Definitions */
typedef enum
{
    //324M-MMI
    SIG_MMI_3G324M_CALL_DROP_REQ = VM_3G324M_BASE,
    SIG_3G324M_MMI_CALL_STATE_IND,
    SIG_3G324M_MMI_CHANNEL_STATE_IND, // to be obsoleted
    SIG_MMI_3G324M_USER_INPUT_DTMF_REQ,
    SIG_3G324M_MMI_USER_INPUT_DTMF_CNF,
    SIG_MMI_3G324M_USER_INPUT_IND,
    SIG_MMI_3G324M_LOOPBACK_REQ,
    SIG_3G324M_MMI_LOOPBACK_CNF,
    SIG_3G324M_MMI_CHANNEL_ONOFF_IND,
    SIG_MMI_3G324M_CHANNEL_ONOFF_REQ,

    //internal
    SIG_TIMER_3G324M_SEND_MUXPDU,
    SIG_TIMER_3G324M_FOR_LOOPBACK,
    SIG_TIMER_3G324M_FOR_UPDATE_INFO,
    SIG_TIMER_3G324M_FOR_LOOPBACKUPDATE_INFO,
    SIG_TIMER_3G324M_TEST_SEND_MUXPDU,
    SIG_TIMER_3G324M_EVENT
} VtMsgType_e;

typedef enum
{
    VT_TIMERID_PROCESS_EVENT = (VM_3G324M_BASE+0x10),
    VT_TIMERID_PROCESS_EVENT_TASK2 = (VT_TIMERID_PROCESS_EVENT+0x1)
} VtTimerId_e;

typedef enum
{
    VT_RESULT_OK = 0,
    VT_RESULT_CONSTRUCT_FAIL,
    VT_RESULT_CHANNEL_SETUP_FAIL,
    VT_RESULT_LOOPBACK_START_FAIL,
    VT_RESULT_LOOPBACK_STOP_FAIL,
    VT_RESULT_DTMF_FAIL,
    VT_RESULT_ALREADY_IN_DISABLED
} VtResultCode_e;

typedef enum
{
    VT_CALL_STATE_INIT                  = Rv3G324mCallStateInit,//-1
    VT_CALL_STATE_SYNCHRONIZED          = Rv3G324mCallStateSynchronized,
    VT_CALL_STATE_CONNECTED             = Rv3G324mCallStateConnected,
    VT_CALL_STATE_CONNECTED_CHANNELS    = Rv3G324mCallStateConnectedChannels,
    VT_CALL_STATE_DISCONNECTED          = Rv3G324mCallStateDisconnected,
    VT_CALL_STATE_IDLE                  = Rv3G324mCallStateIdle,
    VT_CALL_STATE_RESETTING             = Rv3G324mCallStateResetting,
    VT_CALL_STATE_LOST_SYNCH            = Rv3G324mCallStateLostSynch
} VtCallState_e;

typedef enum
{
    VT_CHANNEL_STATE_DIALTONE           = cmChannelStateDialtone,
    VT_CHANNEL_STATE_RINGBACK           = cmChannelStateRingBack,
    VT_CHANNEL_STATE_CONNECTED          = cmChannelStateConnected,
    VT_CHANNEL_STATE_DISCONNECTED       = cmChannelStateDisconnected,
    VT_CHANNEL_STATE_IDLE               = cmChannelStateIdle,
    VT_CHANNEL_STATE_OFFERING           = cmChannelStateOffering
} VtChannelState_e;

typedef enum
{
    VT_Channel_On = 0,
    VT_Channel_Off
} VtChannelOnOffState_e;

typedef enum
{
    VT_Channel_Local_Audio = 0,
    VT_Channel_Local_Video,
    VT_Channel_Local_Data,
    VT_Channel_Remote_Audio,
    VT_Channel_Remote_Video,
    VT_Channel_Remote_Data
} VtChannelType_e;

typedef enum
{
    VT_Channel_Without_Notify_Remote = 0,
    VT_Channel_Notify_Remote,
} VtChannelNotifyRemote_e;

typedef enum
{
    VT_LOOPBACK_DISABLED = 0,
    VT_LOOPBACK_MEDIA,
    VT_LOOPBACK_STACK
} VtLoopbackState_e;

typedef enum
{
    VT_FCM_STATE_CLOSED = 0,
    VT_FCM_STATE_OPENED,
    VT_FCM_STATE_STALLED
} VtFcmState_e;

typedef enum
{
    VT_STACK_DUMP_INCOMING_BS = 0,
    VT_STACK_DUMP_OUTGOING_BS,
    VT_STACK_DUMP_MEDIA_VIDEO,
    VT_STACK_DUMP_MEDIA_AUDIO,
    VT_STACK_DUMP_NUMBER
} VtStackDumpType_e;

typedef struct
{
    VTestStackType_e VtTestType;
    VTestStackDumpBitStream_e VtTestDumpBSFlag;    
} VtTestStatus_t;

typedef struct
{
    VtCallState_e CallState;
} VtCallStateInd_t;

typedef struct
{
    VtChannelState_e ChannelState;
} VtChannelStateInd_t;

typedef struct
{
    u32 pad;
} VtCallDropReq_t;

typedef struct
{
    char digit;
    u8 pad[3];
} VtUserInputDtmfReq_t;

typedef struct
{
    VtResultCode_e result;
} VtUserInputDtmfCnf_t;

typedef struct
{
    VtChannelOnOffState_e ind_state;
    VtChannelType_e ind_type;
} VtChannelOnOffInd_t;

typedef struct
{
    VtChannelOnOffState_e req_state;
    VtChannelType_e req_type;
    VtChannelNotifyRemote_e req_notify;
} VtChannelOnOffReq_t;

typedef struct
{
    VtLoopbackState_e state;
} VtLoopbackReq_t;

typedef struct
{
    VtResultCode_e result;
} VtLoopbackCnf_t;

typedef struct
{
    u32 pad;
} VtTimerSend_t;

typedef struct {
    RvUint32 vt_local_video_on;
    RvUint32 vt_local_audio_on;
    RvUint32 vt_remote_video_on;
    RvUint32 vt_remote_audio_on;
} VtMediaCtrl_t;


typedef struct {
    VtTestStatus_t vt_test_stack_status;	
} VtTestStackCtrl_t;

typedef struct
{
    u32 vpre_sqn;
    u32 vcur_sqn;
    u32 vpre_size;
    u32 vcur_size;
    u16 vlost_frame;
    u32 vtotal_size;
    u32 vframe_cnt;
    u32 vpending_cnt;

    u32 apre_sqn;
    u32 acur_sqn;
    u32 apre_size;
    u32 acur_size;
    u16 alost_frame;
    u32 atotal_size;
    u32 aframe_cnt;
    u32 apending_cnt;

    u64 v_time;
    u64 vtotal_time;
    u64 a_time;
    u64 atotal_time;
    u64 sys_time;
    u64 sys_vt_initial_time;
}vtframe_basic_info_t;

typedef struct
{
    vtframe_basic_info_t vt_incoming_t;
    vtframe_basic_info_t vt_outgoing_t;

    void *optional_data;
}vt_info_t;

typedef enum _VT_Call_Statement_e_
{
    INCOMING,
    OUTGOING,
}VT_Call_Statement_e;

typedef struct
{
    int tm_sec;     /* seconds after the minute - [0,59] */
    int tm_min;     /* minutes after the hour - [0,59] */
    int tm_hour;    /* hours since midnight - [0,23] */
    int tm_mday;    /* day of the month - [1,31] */
    int tm_mon;     /* months since January - [0,11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday - [0,6] */
    int tm_yday;    /* days since January 1 - [0,365] */
    int tm_isdst;   /* daylight savings time flag */
}vt_tm;

typedef void (* VT_VIDEO_FAST_UPDATE_CALLBACK) (u16);

typedef int (* VT_REQ_VIDEO_FAST_UPDATE_CALLBACK) (HCHAN);
typedef int (* VT_TSTO_CMD_CALLBACK) (HCHAN, int);

typedef enum
{
     VT_VIDEO_FAST_UPDATE_NO_CALLBACK=0,
     VT_VIDEO_FAST_UPDATE_WITH_CALLBACK,
}VT_VIDEO_FAST_UPDATE_CALLBACK_STATUS_e;

typedef enum
{
     VT_TSTO_CMD_NO_CALLBACK=0,
     VT_TSTO_CMD_WITH_CALLBACK,
}VT_TSTO_CMD_CALLBACK_STATUS_e;


#endif

