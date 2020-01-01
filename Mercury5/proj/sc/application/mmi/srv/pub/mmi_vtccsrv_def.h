/**
 * @file    mmi_vtccsrv_def.h
 * @brief   xxxx
 * @version $Id: mmi_vtccsrv_def.h 40101 2009-09-12 07:05:56Z collin.chiang $
 */

#ifndef __MMI_VTCCSRV_DEF_H__
#define __MMI_VTCCSRV_DEF_H__

#ifdef __VT_3G324M__

#include "mmi_ccsrv_def.h"

#define VTCCSRV_MAX_CALL_NUMBER   40
#define VTCCSRV_MAX_IP_NUMBER     5
#define VTCCSRV_SHORT_CALL_NUMBER 41      /* For display only */
#define VTCCSRV_MAX_CALL_NAME     41
#define VTCCSRV_SHORT_CALL_NAME   VTCCSRV_SHORT_CALL_NUMBER     /* For display only */
#define VTCCSRV_MAX_CALL_TABLE    7
#define VTCCSRV_MAX_CLCC_ENTRY_NUM    8

#define VTCCSRV_NORMAL_CALL_CLEARING            16  //Cause No.16 "normal call clearing"
#define VTCCSRV_NORMAL_NON_SELECTED_CLEARING    26  //Cause No.26 "non-selected user clearing". Not supported. Treated as cause no. 31
#define VTCCSRV_NORMAL_UNSPECIFIED              31  //Cause No.31 "normal, unspecified"

//Fallback Cause Definition
#define VTCCSRV_RESOURCE_UNAVAILABLE 47  ///Cause No. 47 "resource unavailable, unspecified"
#define VTCCSRV_BEARER_NOT_AUTHORIZED 57  ///Cause No. 57 "bearer capability not authorized"
#define VTCCSRV_BEARER_NOT_AVAILABLE 58  ///Cause No. 58 "bearer capability not presently available"
#define VTCCSRV_INCOMPATIABLE_DEST 88  ///Cause No. 88 "incompatible destination"

//Network Release Cause Definition
#define VTCCSRV_SERVICE_OPTION_UNAV   63  ///Cause No. 63 "service or option not available, unspecified"
#define VTCCSRV_BEARER_SRV_NOT_IMPL   65  ///Cause No. 65 "bearer service not implemented"

#define VTCCSRV_SYS_LIMIT_TIME_IN_SEC           2208988740u  // time in seconds of 12/31/2039 23:59:00

#define VTCCSRV_MAKE_CALL_HOLD_CALL_FAIL  998

#define VTCCSRV_CHANNEL_NUMBER 7

enum
{
    VTCC_AP_FID_UNKNOWN = 0
   ,VTCC_AP_FID_MAKECALL = 1
   ,VTCC_AP_FID_INCOMINCALL = 2
   ,VTCC_AP_FID_WAITINGCALL = 3
   ,
#ifdef __IP_CALL_MMI__
    VTCC_AP_FID_IPCALL = 4
  , // after finish all ip number selection, this fid will tranfers to makeCall
#endif
    VTCC_AP_FID_ENDCALL = 5,
};
typedef s32 MMI_VTCC_AP_FID_E;


typedef enum
{
    VTCCSRV_MO_NO_ERROR = 0
,
    // Reserve 1~127 to GSM04.08 specific cause value (Annex H)
    // Reserve 240~255 for MStar ATI  +CEER failure cause

    VTCCSRV_MO_FAILED = 999
   ,VTCCSRV_MO_CALL_NO_SIM_CARD = 1000
} VTCCSRV_MO_ERROR_CODE;

///
#define MMI_VTCCSRV_Status_e MMI_CCSRV_Status_e

typedef struct
{
    u8 CallRefID;
} VTCCSRV_CallRefInd_t;

typedef struct
{
    boolean Result;
    u8 Cause;
} VTCCSRV_DialingCnf_t;

typedef struct
{
    u8 CallRefID;
    u8 CPHSLine;
    u8 TonNpi;
    u8 CallerNumber[VTCCSRV_MAX_CALL_NUMBER + 1];
} VTCCSRV_RingInd_t;

typedef struct
{
    u8 CallRefID;
    u16 Cause;
} VTCCSRV_RelInd_t;


typedef enum
{
    VTCC_MRL_HANGUP_NONE = 0,
    VTCC_MRL_HANGUP_MODEM_ERROR = 1,
    VTCC_MRL_HANGUP_CONNECTED,
}VtCcHangupErrCause_e;

typedef struct
{
    boolean Status;
    VtCcHangupErrCause_e eCause;
} VTCCSRV_HangUpCnf_t;

typedef struct
{
    boolean Result;
    u8 Cause;
} VTCCSRV_AcceptCnf_t;

typedef struct
{
    u8 Code;
    s8 Index;
} VTCCSRV_CallSetupNotifyInd_t;

typedef struct
{
    u8 Code;
    s8 Index;
    u8 TonNpi;
    u8 CalledNb[VTCCSRV_MAX_CALL_NUMBER + 1];
} VTCCSRV_InCallNotifyInd_t;

typedef struct
{
    u8 CallId;
    MMI_VTCCSRV_Status_e Status;
} VTCCSRV_Clcc_Entry_t;

typedef struct
{
    boolean Status;
    u8 NbCalls;
    VTCCSRV_Clcc_Entry_t CallTable[VTCCSRV_MAX_CLCC_ENTRY_NUM];
} VTCCSRV_ClccCnf_t;

typedef enum
{
    VTCC_3G324M_CHANNEL_ON = 0,
    VTCC_3G324M_CHANNEL_OFF
} VtCc3G324MOnOffState_e;

typedef enum
{
    VTCC_3G324M_CHANNEL_AUDIO = 0,
    VTCC_3G324M_CHANNEL_VIDEO,
    VTCC_3G324M_CHANNEL_DATA,
    VTCC_3G324M_REMOTE_CHANNEL_AUDIO,
    VTCC_3G324M_REMOTE_CHANNEL_VIDEO,
    VTCC_3G324M_REMOTE_CHANNEL_DATA
} VtCc3G324MChannelType_e;

typedef enum
{
    VTCC_3G324M_CHANNEL_NOTIFY_OFF = 0,
    VTCC_3G324M_CHANNEL_NOTIFY_ON
} VtCc3G324MChannelNotify_e;

typedef enum
{
    VTCC_3G324M_CALL_STATE_INIT = 0,
    VTCC_3G324M_CALL_STATE_SYNCHRONIZED = 1,
    VTCC_3G324M_CALL_STATE_CONNECTED = 2,
    VTCC_3G324M_CALL_STATE_CONNECTED_CHANNELS = 3,
    VTCC_3G324M_CALL_STATE_DISCONNECTED = 4,
    VTCC_3G324M_CALL_STATE_IDLE = 5,
    VTCC_3G324M_CALL_STATE_RESETTING = 6,
    VTCC_3G324M_CALL_STATE_LOST_SYNCH = 7,
    VTCC_3G324M_CALL_STATE_NUM
} VtCc3G324MCallState_e;

typedef enum
{
    VTCC_3G324M_RESULT_OK = 0,
    VTCC_3G324M_RESULT_CONSTRUCT_FAIL,
    VTCC_3G324M_RESULT_CHANNEL_SETUP_FAIL,
    VTCC_3G324M_RESULT_LOOPBACK_START_FAIL,
    VTCC_3G324M_RESULT_LOOPBACK_STOP_FAIL,
    VTCC_3G324M_ALREADY_IN_DISABLED
} VtCc3G324MResultCode_e;

typedef struct
{
    VtCc3G324MCallState_e eCallState;
    VtCc3G324MResultCode_e eResult;
} VTCCSRV_3G324MCallStateInd_t;

typedef struct
{
    u8* pData;
    u32 nLength;
    VtCc3G324MResultCode_e eResult;
} VTCCSRV_3G324MUserInputInd_t;

typedef struct
{
    boolean bResult;
} VTCCSRV_3G324MUserInputDTMFCnf_t;

typedef struct
{
    u32 nIndex;
    boolean bStatus;
    u32 nChannelNumber;
} VTCCSRV_CmGetChannelNumberCnf_t;

typedef struct
{
    boolean bStatus;
} VTCCSRV_CmDisconnectCnf_t;

typedef struct
{
    boolean bStatus;
} VTCCSRV_CmDisconnectInd_t;

typedef struct
{
    VtCc3G324MOnOffState_e eVtCc3G324MOnOffState;
	VtCc3G324MChannelType_e eVtCc3G324MChannelType;
} VTCCSRV_3G324MChannelOnOffInd_t;

typedef union
{
    ///RIL
    VTCCSRV_CallRefInd_t CallRefInd;
    VTCCSRV_DialingCnf_t DialingCnf;
    VTCCSRV_RingInd_t RingInd;
    VTCCSRV_HangUpCnf_t HangUpCnf;
    VTCCSRV_RelInd_t ReleaseInd;
    VTCCSRV_AcceptCnf_t AcceptCnf;
    VTCCSRV_CallSetupNotifyInd_t CallSetupNotifyInd;
    VTCCSRV_InCallNotifyInd_t InCallNotifyInd;
    VTCCSRV_ClccCnf_t CallClccCnf;
    ///3G324M
    VTCCSRV_3G324MCallStateInd_t t3G324MCallStateInd;
    VTCCSRV_3G324MUserInputInd_t t3G324MUserInputInd;
    VTCCSRV_3G324MUserInputDTMFCnf_t t3G324MUserInputDTMFCnf;
    ///CM
    VTCCSRV_CmGetChannelNumberCnf_t tCmGetChannelNumberCnf;
    VTCCSRV_CmDisconnectCnf_t tCmDisconnectCnf;
    VTCCSRV_CmDisconnectInd_t tCmDisconnectInd;
	VTCCSRV_3G324MChannelOnOffInd_t t3G324MChannelOnOffInd;
} VTCCSRV_unMsg_t;

///
#define MMI_VTCCSRV_Direction_e MMI_CCSRV_Direction_e
///
#define MMI_VTCCSRV_Mode_e MMI_CCSRV_Mode_e
///
#define MMI_VTCCSRV_DTMF_OP_e MMI_CCSRV_DTMF_OP_e

/* The attribute is used to distinguish the call manipulation.
The attribute will be used with VM_MRL_VTCC_CHLD_REQ to RIL. */
typedef enum
{
    VTCCSRV_NO_OPERATION
   ,/* SEND 0 Category */
    VTCCSRV_REL_HELD_CALLS_ONLY
   ,VTCCSRV_REJECT_WAITING_CALL
   ,VTCCSRV_REJECT_WAITING_CALL_WHEN_MAKE_CALL
   ,VTCCSRV_WAITING_CALL_IN_BLACKLIST
   ,/* SEND 1 Category */
    VTCCSRV_REL_ACT_CALLS_ANSWER_CALL
   ,VTCCSRV_REL_ACT_CALLS_RETRIEVE_CALLS
   ,/* SEND 1X Category */
    VTCCSRV_REL_SPECIFIC_CALLS
   ,/* SEND 2 Category */
    VTCCSRV_HOLD_CALLS
   ,VTCCSRV_RETRIEVE_CALLS
   ,VTCCSRV_SWAP_CALLS
   ,VTCCSRV_HOLD_ACT_CALLS_ANSWER_CALL
   ,/* SEND 2X Category */
    VTCCSRV_SPLIT_CALL
   ,/* SEND 3 Category */
    VTCCSRV_JOIN_MPTY_CALL
   ,/* SEND 4 Category */
    VTCCSRV_TRANSFER_CALLS
   ,/* Extend Category*/
    VTCCSRV_REPLCAE_HELD_CALL
   ,/* Use in 1A1H1W only*/
    VTCCSRV_RELEASE_ALL_HELD_CALL_ONLY
   ,/*Use in 1AW, 1AHW to releaae all held call*/
    VTCCSRV_RELEASE_ALL_ACTIVE_CALL_ONLY
   ,/* Use in 1AH, 1AHW, 1AW only*/
} MMI_VtCcCall_Chld_Type_e;

/* The attribute of one call in the call table */
///
#define MMI_VTCCSRV_Attr_e MMI_CCSRV_Attr_e

typedef enum
{
    VTCCSRV_OVERWRITE_MODE = 0
   ,VTCCSRV_UPDATE_MODE
} VTCCSRV_UpdateMode_e;

/* The enum is used for APP to check the VTCC Service status */
typedef enum
{
    VTCCSRV_IDLE = 0
   ,VTCCSRV_1A
,                   // 1 active call (or 1 MPTY call)
    VTCCSRV_1H
,                   // 1 hold call
    VTCCSRV_1A1H
,               // 1 active and 1 hold call
    VTCCSRV_1AW
,               // 1 active and 1 waiting call
    VTCCSRV_1HW
,               // 1 hold call and 1 waiting call
    VTCCSRV_1AHW
,               // 1 active, 1 hold and 1 waiting call
    VTCCSRV_MAKE2NDCALL
,   // 1 hold call and dial another call
    VTCCSRV_INCOMING
,       // 1 incoming call
    VTCCSRV_OUTGOING
,       // 1 outgoing call
    VTCCSRV_UNKNOWN
} VTCCSRV_Mode_e;

typedef enum
{
    VTCCSRV_MASTER_CALL_EXISTED = 0
   ,VTCCSRV_SLAVE_CALL_EXISTED
   ,VTCCSRV_NO_CALL
   ,VTCCSRV_STATUS_UNKNOW
} VTCCSRV_DUO_STATUS_e;

enum
{
    VTCCSRV_MT_TYPE_RING = 0
   ,VTCCSRV_MT_TYPE_WAITING = 1
 ,  // For 1A1W or 1H1W
    VTCCSRV_MT_TYPE_WAITING_FULL = 2      // For 1A1H1W
};

typedef s32 VTCCSRV_MT_TYPE_E;

enum
{
    VTCCSRV_NUMBER_NATIONAL = 129
   ,VTCCSRV_NUMBER_INTERNATIONAL = 145
};
typedef u8 VTCCSRV_NUMBER_Type_e;

enum
{
    VTCCSRV_DURATION_CURRENT
   ,VTCCSRV_DURATION_FINAL
};
typedef u8 VTCCSRV_DURATION_Type_e;

typedef struct
{
    VTCCSRV_MT_TYPE_E type;
    u8 u8DualID;
} MmiVtCcMTCallInd_t;

#endif//__VT_3G324M__
#endif /* __MMI_VTCCSRV_DEF_H__ */

