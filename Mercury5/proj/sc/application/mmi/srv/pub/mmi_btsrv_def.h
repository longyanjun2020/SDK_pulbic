/**
* @file mmi_btsrv_def.h
*
* BTSRV structure definition
*
* $Id: $
*/
#ifndef __MMI_BTSRV_DEF_H__
#define __MMI_BTSRV_DEF_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_langcode.h"
#include "mmi_btsrv_cfg.h"
#include "mmi_mae_helper.h"
#include "mmi_util_fs.h"
#include "mmi_common_custom.h"
#include "mmi_mae_filemgr.h"
#include "drv_bt_api.h"
#include "mmi_audiosrv.h"
#include "mmi_filemgr.h"

#define MMI_LEVEL_BT MMI_LEVEL_27

#define BTSRV_DEVICE_ADDR_SIZE        BD_ADDR_SIZE
#define BTSRV_PINCODE_LEN           (BT_PINCODE_LEN) //16
#define BTSRV_LINKKEY_LEN           (BT_LINKKEY_LEN) //16
#define BTSRV_MAX_AVRCP_QUEUE_SIZE  6
//#define BTSRV_DEVICE_NAME_LEN     (BT_DEVICE_NAME_LEN/2-1) //265/2 -1
//#define BTSRV_DEVICE_MAX_NUM      20 // move to customization
#define BTSRV_40MB (40*1024*1024)
#define BTSRV_AskIfRecvTimer (20000)
#define BTSRV_INVALID_DEVICE_IDX 0xFF //The device index which is invalid
#ifndef MEMCMP
#define MEMCMP(s,t,n) memcmp(s,t,n)
#endif


/* Maximum length of call number */
#define BTSRV_CALLNUM_LEN           BT_HFP_PHONE_NUM_SIZE


/* International Call's Symbol */
#define BTSRV_INTERNATIONAL_CALL_SYMBOL     '+'


/* Call Type */
typedef enum {
    BTSRV_CALL_TYPE_NATIONAL      = 129,
    BTSRV_CALL_TYPE_INTERNATIONAL = 145
}BtSrvCallType_e;


/* BT Current Status */
typedef enum BtSrvConflictStatus_e_
{
    BTSRV_CONFLICT_STATE_INQUERY = 0,        //BT is searching devices
    BTSRV_CONFLICT_STATE_AUDIOLNK_ON,        //Audio/A2DP link is connected
    BTSRV_CONFLICT_STATE_SCO_ON,             //SCO is active
    BTSRV_CONFLICT_STATE_A2DP_ON,            //A2DP is active
    BTSRV_CONFLICT_STATE_OPP_ON,             //OPP is active
    BTSRV_CONFLICT_STATE_NUM,
    BTSRV_CONFLICT_STATE_INVALID
} BtSrvConflictStatus_e;

/* User's Request */
typedef enum BtSrvConflictReq_e_
{
    BTSRV_CONFLICT_REQ_PAIR,
    BTSRV_CONFLICT_REQ_AUDIOLNK,
    BTSRV_CONFLICT_REQ_SCO,
    BTSRV_CONFLICT_REQ_A2DP,
    BTSRV_CONFLICT_REQ_OPP,
    BTSRV_CONFLICT_REQ_INQUERY,
    BTSRV_CONFLICT_REQ_NUM,
    BTSRV_CONFLICT_REQ_INVALID
} BtSrvConflictReq_e;

/* BT Task's Indicator */
typedef enum BtSrvConflictInd_e_
{
    BTSRV_CONFLICT_IND_PAIR = 0, //MAE_EVT_BT_PIN_CODE_IND
    BTSRV_CONFLICT_IND_AUDIOLNK, //MAE_EVT_BT_AUDIO_LINK_IND / MAE_EVT_BT_AUDIO_LINK_CNF
    BTSRV_CONFLICT_IND_SCO,
    BTSRV_CONFLICT_IND_A2DP,     //MAE_EVT_BT_A2DP_LINK_IND / MAE_EVT_BT_A2DP_LINK_CNF
    BTSRV_CONFLICT_IND_OPP,      //MAE_EVT_BT_OBEX_RECEIVE_IND
    BTSRV_CONFLICT_IND_NUM,
    BTSRV_CONFLICT_IND_INVALID
} BtSrvConflictInd_e;

#ifdef __BLUETOOTH_CONCURRENT_LIMIT_MMI__//Only for RDA
static bool gBtSrvConcurrentCaseReq[BTSRV_CONFLICT_STATE_NUM][BTSRV_CONFLICT_REQ_NUM] =
{
    /* User Request */
    /* Pair     AudioLink  SCO     A2DP   OPP    InQuery   */
       {TRUE,   TRUE,      FALSE,  TRUE,  FALSE , FALSE }, //InQuery
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE,  FALSE }, //Audio Link Connected
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE,  FALSE }, //SCO ON
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE,  FALSE }, //A2DP Playing
       {FALSE,  FALSE,     FALSE,  FALSE, FALSE,  FALSE }, //OPP Active
};
static bool gBtSrvConcurrentCaseInd[BTSRV_CONFLICT_STATE_NUM][BTSRV_CONFLICT_IND_NUM] =
{
    /* Driver Ind */
    /* Pair     AudioLink  SCO     A2DP   OPP      */
       {TRUE,   TRUE,      TRUE,   TRUE,  FALSE }, //InQuery
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE }, //Audio Link Connected
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE }, //SCO ON
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE }, //A2DP Playing
       {TRUE,   FALSE,     FALSE,  FALSE, FALSE }, //OPP Active
};
#else

#ifdef __BLUETOOTH_ACRUX2_CONCURRENT_LIMIT_MMI__//Acrux2
static bool gBtSrvConcurrentCaseReq[BTSRV_CONFLICT_STATE_NUM][BTSRV_CONFLICT_REQ_NUM] =
{
    /* User Request */
    /* Pair     AudioLink  SCO     A2DP   OPP     InQuery */
       {TRUE,   TRUE,      FALSE,  FALSE, FALSE,  FALSE },   //InQuery
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE,  FALSE },   //Audio/A2DP Link Connected
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE,  FALSE },   //SCO ON
       {FALSE,  FALSE,     TRUE,   TRUE,  FALSE,  FALSE },   //A2DP Playing
       {FALSE,  FALSE,     FALSE,  FALSE, FALSE,  FALSE },   //OPP Active
};
static bool gBtSrvConcurrentCaseInd[BTSRV_CONFLICT_STATE_NUM][BTSRV_CONFLICT_IND_NUM] =
{
    /* Driver Ind */
    /* Pair     AudioLink  SCO     A2DP   OPP    */
       {TRUE,   TRUE,      TRUE,   TRUE,  FALSE  }, //InQuery
       {TRUE,   TRUE,      TRUE,   TRUE,  FALSE  }, //Audio/A2DP Link Connected
       {FALSE,  TRUE,      TRUE,   TRUE,  FALSE  }, //SCO ON
       {FALSE,  TRUE,      TRUE,   TRUE,  FALSE  }, //A2DP Playing
       {TRUE,   TRUE,      FALSE,  FALSE, FALSE  }, //OPP Active
};
#else //NO Concurrent Limit

static bool gBtSrvConcurrentCaseReq[BTSRV_CONFLICT_STATE_NUM][BTSRV_CONFLICT_REQ_NUM] =
{
    /* User Request */
    /* Pair     AudioLink  SCO     A2DP   OPP     InQuery */
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE,   TRUE }, //InQuery
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE,   TRUE }, //Audio/A2DP Link Connected
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE,   TRUE }, //SCO ON
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE,   TRUE }, //A2DP Playing
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE,   TRUE }, //OPP Active
};
static bool gBtSrvConcurrentCaseInd[BTSRV_CONFLICT_STATE_NUM][BTSRV_CONFLICT_IND_NUM] =
{
    /* Driver Ind */
    /* Pair     AudioLink  SCO     A2DP   OPP      */
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE  }, //InQuery
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE  }, //Audio/A2DP Link Connected
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE  }, //SCO ON
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE  }, //A2DP Playing
       {TRUE,   TRUE,      TRUE,   TRUE,  TRUE  }, //OPP Active
};
#endif

#endif

/*The bit for different BT status*/
typedef enum
{
    BTSRV_NONE              =   0x0000
    ,BTSRV_ENABLED           =   0x0001 //bit 0
    ,BTSRV_INQUERY           =   0x0002 //bit 1
    ,BTSRV_PAIRING           =   0x0004 //bit 2
    ,BTSRV_OPP_TX_START     =   0x0008 //bit 3
	,BTSRV_OPP_RX_START     =   0x0010 //bit 4
    ,BTSRV_XXX1              =   0x0020 //bit 5
    ,BTSRV_XXX2              =   0x0040 //bit 6
    ,BTSRV_SCO               =   0x0080 //bit 7
    ,BTSRV_XXX3              =   0x0100 //bit 8
    ,BTSRV_XXX4              =   0x0200 //bit 9
    ,BTSRV_XXX5              =   0x0400 //bit 10
    ,BTSRV_XXX6              =   0x0800 //bit 11
    ,BTSRV_XXX7              =   0x1000 //bit 12
    ,BTSRV_XXX8              =   0x2000 //bit 13
    ,BTSRV_SNIFF             =   0x4000 //bit 14
    ,BTSRV_A2DP_ON           =   0x8000 //bit 15
} BTSRV_States_e;

typedef enum
{
    BTSRV_POWER_ONOFF_CAUSE_NORMAL = 0
    ,BTSRV_POWER_ONOFF_CAUSE_SEARCHING
    ,BTSRV_POWER_ONOFF_CAUSE_CONNECTING
    ,BTSRV_POWER_ONOFF_CAUSE_NUM
} BTSRV_POWER_ONOFF_CAUSE_e;

/* Bluetooth CoD Definitions */
typedef enum
{
    BTSRV_SRV_CLASS_OBEX_COD        = 0x00100000
    ,BTSRV_SRV_CLASS_AUDIO_COD      = 0x00200000
} BTSRV_CoD_MajorSrvClass_e;

#define BTSRV_COD_MAJOR_SRV_MASK 0x00FF0000

typedef enum
{
    BTSRV_DEV_CLASS_COMPUTER_COD     = 0x00000100
    ,BTSRV_DEV_CLASS_PHONE_COD       = 0x00000200
    ,BTSRV_DEV_CLASS_LAN_AP_COD      = 0x00000300
    ,BTSRV_DEV_CLASS_AUDIO_VIDEO_COD = 0x00000400
    ,BTSRV_DEV_CLASS_PERIPHERAL_COD  = 0x00000500
} BTSRV_CoD_MajorDevClass_e;

#define BTSRV_COD_MAJOR_DEV_MASK 0x0000FF00

typedef enum
{
    BTSRV_DEV_CLASS_AUDIO_COD      = 0x0000000C //BTSRV_HEADSET_COD + BTSRV_HANDSFREE_COD
    ,BTSRV_DEV_CLASS_HEADSET_COD    = 0x00000004
    ,BTSRV_DEV_CLASS_HANDSFREE_COD  = 0x00000008
    ,BTSRV_DEV_CLASS_HIFI_COD       = 0x00000028
} BTSRV_CoD_MinorDevClass_e;

#define BTSRV_COD_MINOR_DEV_MASK 0x000000FF

typedef enum
{
    BTSRV_OBEX_COD        = 0x00100000
    ,BTSRV_COMPUTER_COD   = 0x00000100
    ,BTSRV_PHONE_COD      = 0x00000200
    ,BTSRV_LAN_AP_COD     = 0x00000300
    ,BTSRV_AUDIO_COD      = 0x0020040C //BTSRV_HEADSET_COD + BTSRV_HANDSFREE_COD
    ,BTSRV_HEADSET_COD    = 0x00200404
    ,BTSRV_HANDSFREE_COD  = 0x00200408
    ,BTSRV_HIFI_COD       = 0x00200428
    ,BTSRV_PERIPHERAL_COD = 0x00000500
} BTSRV_CoD_e;

#define BTSRV_COD_MASK 0x00000FFF

typedef enum
{
    BTSRV_HEADSETSTATUS_IDLE = 0
    ,BTSRV_HEADSETSTATUS_CONNECTING
    ,BTSRV_HEADSETSTATUS_CONNECTED
    ,BTSRV_HEADSETSTATUS_DISCONNECTING
    ,BTSRV_HEADSETSTATUS_MAX = BTSRV_HEADSETSTATUS_DISCONNECTING
} BTSRV_HeadsetStatus_e;

typedef enum
{
    BTSRV_PROFILE_NONE = 0
    ,BTSRV_HS_PROFILE
    ,BTSRV_HF_PROFILE
    ,BTSRV_OPUSH_PROFILE
    ,BTSRV_FTP_PROFILE
    ,BTSRV_A2DP_PROFILE
    ,BTSRV_MAX_PROFILE = BTSRV_A2DP_PROFILE
} BTSRV_PROFILE_e;

typedef enum
{
    BTSRV_INQUIRY_STOP = 0
    ,BTSRV_INQUIRY_START
    ,BTSRV_INQUIRY_NUM
} BTSRV_InquiryAction_e;

typedef enum
{
    BTSRV_ACL_CONNECT = 0
    ,BTSRV_ACL_DISCONT
    ,BTSRV_ACL_NUM
} BTSRV_ACLLinkAction_e;

typedef enum
{
    BTSRV_CONNECT = 0
    ,BTSRV_DISCONNECT
    ,BTSRV_CANCEL
    ,BTSRV_CONNECT_AUDIO_CALL
    ,BTSRV_AUDIOLINK_NUM
} BTSRV_AudioLink_e;

typedef enum
{
    BTSRV_AUDIO_DEV_NONE = 0
    ,BTSRV_AUDIO_DEV_CONNECT = BTSRV_AUDIO_DEV_NONE + 1
    ,BTSRV_AUDIO_DEV_DISCONNECT
    ,BTSRV_AUDIO_DEV_END = BTSRV_AUDIO_DEV_DISCONNECT
} BTSRV_AudioDevLinkAction_e;

//Connected Profiles
typedef enum{
    BTSRV_AUDIODEV_PROFILE_NONE  = 0x00000000
    ,BTSRV_AUDIODEV_PROFILE_HFP  = 0x00000001 //bit 1 (Profile: HFP)
#ifdef __BLUETOOTH_A2DP_MMI__
    ,BTSRV_AUDIODEV_PROFILE_A2DP = 0x00000002 //bit 2 (Profile: A2DP)
#endif //__BLUETOOTH_A2DP_MMI__
} BTSRV_AudioDevLinkStatus_e;

typedef enum{
    BTSRV_AUDIODEV_ATTR_NONE                 = 0x00000000
    ,BTSRV_AUDIODEV_ATTR_RESPONSE            = 0x00000001 //bit 1 (The notification is a response to user's request)
    ,BTSRV_AUDIODEV_ATTR_AUTO_DETECT         = 0x00000002 //bit 2 (The request detects the profiles automatically.)
    ,BTSRV_AUDIODEV_ATTR_DISABLE_A2DP_STREAM = 0x00000004 //bit 3 (The connect info about streaming status.)
    ,BTSRV_AUDIODEV_ATTR_FINISHED            = 0x00000008 //bit 4 (The audio link operation is finished)
} BTSRV_AudioDevNotifyAttr_e;

typedef enum
{
    BTSRV_STATUS_CONNECT = 0           // Connect HFP
    ,BTSRV_STATUS_CONNECT_FAIL = 1     // Connect HFP fail
    ,BTSRV_STATUS_DISCONNECT = 2       // 1. Disconnect HFP 2. Disconnect HFP/A2DP
    ,BTSRV_STATUS_DISCONNECT_AUTO = 3
    ,BTSRV_STATUS_DISCONNECT_FAIL = 4  // 1. Disconnect HFP fail 2. Disconnect A2DP fail

#ifdef __BLUETOOTH_A2DP_MMI__
    ,BTSRV_STATUS_DISCONNECT_A2DP = 5   // Disconnect A2DP
    ,BTSRV_STATUS_CONNECT_A2DP = 6      // Connect HFP & A2DP ok
    ,BTSRV_STATUS_CONNECT_A2DP_FAIL = 7 // Connect HFP ok, A2DP fail
    ,BTSRV_STATUS_CONNECT_HF_A2DP = 8
    ,BTSRV_STATUS_CONNECT_A2DP_DISABLE_STREAM = 9 // Connect HFP & A2DP ok, but Disable A2dp streaming
#endif

} BTSRV_Link_Status_e;

typedef enum
{
    BTSRV_SCO_ON = 0
    ,BTSRV_SCO_OFF
    ,BTSRV_RING
    ,BTSRV_KEY
    ,BTSRV_AUDIOCALLTYPE_NUM
} BTSRV_AudioCallType_e;

typedef enum
{
    BTSRV_MUTE_OFF = 0
    ,BTSRV_MUTE_ON
    ,BTSRV_MUTE_NUM
} BTSRV_AudioMuteType_e;

typedef enum
{
    BTSRV_NOCALL = 0
    ,BTSRV_INCOMING
    ,BTSRV_DIALING
    ,BTSRV_ALERTING
    ,BTSRV_WAITING
    ,BTSRV_NO_HOLD
    ,BTSRV_HOLD
    ,BTSRV_HOLD_NO_ACTIVE
    ,BTSRV_NO_CALL_ACTIVE
    ,BTSRV_CALL_ACTIVE
    ,BTSRV_GSM_NOSERVICE
    ,BTSRV_AUDIOCALLSTATUS_NUM
} BTSRV_AudioCallStatus_e;

enum
{
    BTSRV_MASK_Audio_Link = 1 << 0
    ,BTSRV_MASK_Audio_Call = 1 << 1
    ,BTSRV_MASK_Other = 1 << 2
    ,
#ifdef __BLUETOOTH_OBEX_MMI__
    BTSRV_MASK_TRANS_STATUS = 1 << 3
    ,
    // for BTSRV_MASK_TRANS_STATUS
    // BTSRV_EVT_SendFileInd : param1 = BTSRV_TRANS_RESULT_e
    // BTSRV_EVT_RecvFileInd : param1 = BTSRV_TRANS_RESULT_e; param2 = file name
    // BTSRV_EVT_ImportFileInd : param1 = BTSRV_TRANS_RESULT_e
    BTSRV_MASK_TRANS_PROGRESS = 1 << 4
    ,
    // BTSRV_EVT_TransProgressInd : param1 = cur size; param2 = total size
    BTSRV_MASK_TRANS_INTERACTIVE = 1 << 5
    ,
    // BTSRV_EVT_TransInteractiveInd
#endif

#ifdef __BLUETOOTH_A2DP_MMI__
    BTSRV_MASK_A2DP_STATUS = 1 << 6
    ,
#endif

    BTSRV_MASK_CHIP_RESET = 1 << 10
    ,BTSRV_MASK_ALLMask = -1
} ;

typedef s32 BTSRV_NOTIFY_MASK_e;

typedef enum
{
    BTSRV_SUCCESS = BT_SUCCESS,/* Successful and complete = 0 */
    BTSRV_FAILED = BT_FAILED,/* Operation failed = 1 */
    BTSRV_PENDING = BT_PENDING_,/* Successfully started but pending */
    BTSRV_LINK_DISCONNECT = BT_DISCONNECT,/* Link disconnected */
    BTSRV_NO_LINK = BT_NO_LINK,/* No Link layer Connection exists */
    BTSRV_IN_USE = BT_IN_USE,/* Operation failed - already in use. */

    BTSRV_BUSY = BT_BUSY,/* Busy = 6 */
    BTSRV_NO_RESOURCES = BT_NO_RESOURCES,/* No resources */
    BTSRV_NOT_FOUND = BT_NOT_FOUND,/* Not found */
    BTSRV_DEVICE_NOT_FOUND = BT_DEVICE_NOT_FOUND,/* Device not found */
    BTSRV_CONNECTION_FAILED = BT_CONNECTION_FAILED,/* Connect failed */
    BTSRV_TIMEOUT = BT_TIMEOUT_,/* Timeout */
    BTSRV_NO_CONNECTION = BT_NO_CONNECTION,/* No connection */
    BTSRV_INVALID_PARM = BT_INVALID_PARM,/* Invalid parameter */
    BTSRV_IN_PROGRESS = BT_IN_PROGRESS,/* In progress */
    BTSRV_RESTRICTED = BT_RESTRICTED,/* Restricted */
    BTSRV_INVALID_TYPE = BT_INVALID_TYPE,/* Invalid type */
    BTSRV_HCI_INIT_ERR = BT_HCI_INIT_ERR,/* HCI initial error */
    BTSRV_NOT_SUPPORTED = BT_NOT_SUPPORTED,/* No supported */
    BTSRV_CONTINUE = BT_CONTINUE,/* Continue */
    BTSRV_CANCELLED = BT_CANCELLED,/* Cancelled = 20 */
    BTSRV_UNKNOWN_HCI_CMD = BT_UNKNOWN_HCI_CMD,/* Unknown HCI Command = 21 */
    BTSRV_NO_ACL_CONNECTION = BT_NO_ACL_CONNECTION,/* No ACL connection */
    BTSRV_HARDWARE_FAILURE = BT_HARDWARE_FAILURE,/* Hardware Failure */
    BTSRV_PAGE_TIMEOUT = BT_PAGE_TIMEOUT,/* Page timeout */
    BTSRV_AUTHENTICATE_FAILURE = BT_AUTHENTICATE_FAILURE,/* Authentication failure */
    BTSRV_MISSING_KEY = BT_MISSING_KEY,/* Missing key */
    BTSRV_MEMORY_FULL = BT_MEMORY_FULL,/* Memory full */
    BTSRV_CONNECTION_TIMEOUT = BT_CONNECTION_TIMEOUT,/* Connection timeout */
    BTSRV_MAX_CONNECTIONS = BT_MAX_CONNECTIONS,/* Max number of connections */
    BTSRV_MAX_SCO_CONNECTIONS = BT_MAX_SCO_CONNECTIONS,/* Max number of SCO connections to a device */
    BTSRV_ACL_ALREADY_EXISTS = BT_ACL_ALREADY_EXISTS,/* The ACL connection already exists. = 31*/
    BTSRV_COMMAND_DISALLOWED = BT_COMMAND_DISALLOWED,/* Command disallowed */
    BTSRV_LIMITED_RESOURCE = BT_LIMITED_RESOURCE,/* Host rejected due to limited resources */
    BTSRV_SECURITY_ERROR = BT_SECURITY_ERROR,/* Host rejected due to security reasons */
    BTSRV_PERSONAL_DEVICE = BT_PERSONAL_DEVICE,/* Host rejected (remote is personal device) */
    BTSRV_HOST_TIMEOUT = BT_HOST_TIMEOUT,/* Host timeout */
    BTSRV_UNSUPPORTED_FEATURE = BT_UNSUPPORTED_FEATURE,/* Unsupported feature or parameter value */
    BTSRV_INVALID_HCI_PARM = BT_INVALID_HCI_PARM,/* Invalid HCI command parameters */
    BTSRV_USER_TERMINATED = BT_USER_TERMINATED,/* Other end terminated (user) */
    BTSRV_LOW_RESOURCES = BT_LOW_RESOURCES,/* Other end terminated (low resources) */
    BTSRV_POWER_OFF_ERROR = BT_POWER_OFF_ERROR,/* Other end terminated (about to power off) */
    BTSRV_LOCAL_TERMINATED = BT_LOCAL_TERMINATED,/* Terminated by local host */
    BTSRV_REPEATED_ATTEMPTS = BT_REPEATED_ATTEMPTS,/* Repeated attempts */
    BTSRV_PAIRING_NOT_ALLOWED = BT_PAIRING_NOT_ALLOWED,/* Pairing not allowed */
    BTSRV_UNKNOWN_LMP_PDU = BT_UNKNOWN_LMP_PDU,/* Unknown LMP PDU */
    BTSRV_UNSUPPORTED_REMOTE = BT_UNSUPPORTED_REMOTE,/* Unsupported Remote Feature */
    BTSRV_SCO_OFFSET_REJECT = BT_SCO_OFFSET_REJECT,/* SCO Offset Rejected */
    BTSRV_SCO_INTERVAL_REJECT = BT_SCO_INTERVAL_REJECT,/* SCO Interval Rejected */
    BTSRV_SCO_AIR_MODE_REJECT = BT_SCO_AIR_MODE_REJECT,/* SCO Air Mode Rejected */
    BTSRV_INVALID_LMP_PARM = BT_INVALID_LMP_PARM,/* Invalid LMP Parameters */
    BTSRV_UNSPECIFIED_ERR = BT_UNSPECIFIED_ERR,/* Unspecified Error */
    BTSRV_UNSUPPORTED_LMP_PARM = BT_UNSUPPORTED_LMP_PARM,/* Unsupported LMP Parameter Value */
    BTSRV_ROLE_CHG_NOT_ALLOWED = BT_ROLE_CHG_NOT_ALLOWED,/* Role Change Not Allowed */
    BTSRV_LMP_RESPONSE_TIMEOUT = BT_LMP_RESPONSE_TIMEOUT,/* LMP Response Timeout */
    BTSRV_LMP_TRANS_COLLISION = BT_LMP_TRANS_COLLISION,/* LMP Error Transaction Collision */
    BTSRV_LMP_PDU_NOT_ALLOWED = BT_LMP_PDU_NOT_ALLOWED,/* LMP PDU Not Allowed */
    BTSRV_ENCRYP_MODE_NOT_ACC = BT_ENCRYP_MODE_NOT_ACC,/* Encryption Mode Not Acceptable */
    BTSRV_UNIT_KEY_USED = BT_UNIT_KEY_USED,/* Unit Key Used */
    BTSRV_QOS_NOT_SUPPORTED = BT_QOS_NOT_SUPPORTED,/* QoS is Not Supported */
    BTSRV_INSTANT_PASSED = BT_INSTANT_PASSED,/* Instant Passed */
    BTSRV_PAIR_UNITKEY_NO_SUPP = BT_PAIR_UNITKEY_NO_SUPP,/* Pairing with Unit Key Not Supported, 0x3D */

    BTSRV_ITEM_NOT_FOUND = 0xF1,/* Item not found */
    BTSRV_REQUEST_CANCELLED = 0xF2 /* Pending request cancelled */
} BTSRV_StatusCode_e;


typedef enum
{
    BTSRV_SDP_SERVICE_NOE          = 0x00000000,
    BTSRV_SDP_SERVICE_SPP          = 0x00000001,
    BTSRV_SDP_SERVICE_LAP          = 0x00000002,
    BTSRV_SDP_SERVICE_DUN          = 0x00000004,
    BTSRV_SDP_SERVICE_SYNC         = 0x00000008,
    BTSRV_SDP_SERVICE_SYNC_CMD     = 0x00000010,
    BTSRV_SDP_SERVICE_OPP          = 0x00000020,
    BTSRV_SDP_SERVICE_FTP          = 0x00000040,
    BTSRV_SDP_SERVICE_HSP          = 0x00000080,
    BTSRV_SDP_SERVICE_HSP_GW       = 0x00000100,
    BTSRV_SDP_SERVICE_CTP          = 0x00000200,
    BTSRV_SDP_SERVICE_A2DP         = 0x00000400,
    BTSRV_SDP_SERVICE_A2DP_SRC     = 0x00000800,
    BTSRV_SDP_SERVICE_AVRCP        = 0x00001000,
    BTSRV_SDP_SERVICE_AVRCP_TG     = 0x00002000,
    BTSRV_SDP_SERVICE_ICP          = 0x00004000,
    BTSRV_SDP_SERVICE_FAX          = 0x00008000,
    BTSRV_SDP_SERVICE_PANU         = 0x00010000,
    BTSRV_SDP_SERVICE_NAP          = 0x00020000,
    BTSRV_SDP_SERVICE_GN           = 0x00040000,
    BTSRV_SDP_SERVICE_BPP          = 0x00080000,
    BTSRV_SDP_SERVICE_BPP_REF_OBJ  = 0x00100000,
    BTSRV_SDP_SERVICE_BPP_REF_UI   = 0x00200000,
    BTSRV_SDP_SERVICE_BIP          = 0x00400000,
    BTSRV_SDP_SERVICE_HFP          = 0x00800000,
    BTSRV_SDP_SERVICE_HFP_GW       = 0x01000000,
    BTSRV_SDP_SERVICE_SAP          = 0x02000000,
    BTSRV_SDP_SERVICE_PBAP         = 0x04000000,
    BTSRV_SDP_SERVICE_PBAP_SRV     = 0x08000000,
    BTSRV_SDP_SERVICE_HCRP         = 0x10000000,
    BTSRV_SDP_SERVICE_HID          = 0x20000000
} BTSRV_SdpService_e;

typedef enum
{
    BTSRV_OFF = 0,
    BTSRV_INITIALIZING = 1,
    BTSRV_ACTIVE = 2,
    BTSRV_SEARCHING = 3, //Searching other devices
    BTSRV_BONDING = 4, //Pairing with other devices
    BTSRV_SETTING = 5,
    BTSRV_CONNECTING = 6,
    BTSRV_VOICE_CALL = 7, //BT Headset voice call
    BTSRV_A2DP_CONNECTED = 8, //BT Headset A2DP
    BTSRV_UNKOWN = 9

} BTSRV_Mode_e;
typedef struct
{
    u32 CoD;
    //u8	    bUsed;
    u8	    bHandFreeUsed;
    u32	    Sdpdata;
#ifdef __BLUETOOTH_A2DP_MMI__
    u8	    bA2DPUsed;
#endif
    u8 bAuthorized;
    u8 u8Profile;
    u8 Addr[BTSRV_DEVICE_ADDR_SIZE];  // 6bytes
    u16 Name[BTSRV_DEVICE_NAME_LEN + 1]; // 80bytes
    u8 LinkKey[BTSRV_LINKKEY_LEN];  // 16bytes
} BTSRV_DevInfo_t;

typedef struct
{
    u8 Addr[BTSRV_DEVICE_ADDR_SIZE];
} BTSRV_DevAddr_t;

typedef struct
{
    BTSRV_ACLLinkAction_e Connect;    /* Connect/Disconnect */
    u8 Addr[BTSRV_DEVICE_ADDR_SIZE];
} BTSRV_ACLLink_t;

typedef struct
{
    u8 Profile;    /* HS/HF Profile Type */
    BTSRV_AudioLink_e Connect;    /* Connect/Disconnect */
    u8 Addr[BTSRV_DEVICE_ADDR_SIZE];
} BTSRV_AudioLink_t;

/* Save the current status for connecting an audio device*/
typedef struct
{
    boolean bIsAutoDetect; /* TRUE if connect the profiles supported by the device automatically*/
    u8 au8Addr[BTSRV_DEVICE_ADDR_SIZE];
    BTSRV_AudioDevLinkAction_e eLinkAction; /* Connect/Disconnect */
    BTSRV_PROFILE_e eProfile;    /* HS/HF Profile Type */
} BTSRV_AudioDevLinkReq_t;

/* To notify the Apps the result for a link action & the current link status*/
typedef struct
{
    BTSRV_AudioDevLinkAction_e eLinkAction; /* Connect/Disconnect */
    BTSRV_PROFILE_e eLinkProfile;    /* The profile specified in the link action*/
    BTSRV_StatusCode_e eBtStatus; //The result of the link action
    BTSRV_AudioDevNotifyAttr_e eNotifyAttributes; //Allow ap to check some useful attributes of the notification
    BTSRV_AudioDevLinkStatus_e eCurrentLinkStatus; //The current link status for BT audio device
} BTSRV_AudioDevLinkStatus_t;

typedef struct
{
    u8 CurrentAudioAddr[BTSRV_DEVICE_ADDR_SIZE];  // 6bytes
    u8 PairDeviceNum;
    boolean bIsAutoConnect; //Whether or not reconnect the BT device
    BTSRV_DevInfo_t PairDevice[BTSRV_DEVICE_MAX_NUM];
} BTSRV_FileInfo_t;

#define MMI_BTSRV_FILE_INFO_SIZE sizeof(BTSRV_FileInfo_t)

// map to BT_AudioPacketType_e in api_bt_mmi.h
typedef enum
{
    BTSRV_AUDIO_NO_SCO = 0,
    BTSRV_AUDIO_HV3 = 1,
    BTSRV_AUDIO_HV2 = 2,
    BTSRV_AUDIO_HV1 = 3,
    BTSRV_AUDIO_EV3 = 4,
    BTSRV_AUDIO_EV4 = 5,
    BTSRV_AUDIO_EV5 = 6,
    BTSRV_AUDIO_2EV3 = 7,
    BTSRV_AUDIO_2EV5 = 8,
    BTSRV_AUDIO_3EV3 = 9,
    BTSRV_AUDIO_3EV5 = 10,
    BTSRV_AUDIO_INVALID_PKT = 11

} BTSRV_AudioPacketType_e;

typedef enum
{
    BTSRV_ACL_MODE_ACTIVE  = 0, /* ACL active */
    BTSRV_ACL_MODE_HOLD    = 1, /* Hold mode, not used */
    BTSRV_ACL_MODE_SNIFF   = 2, /* Sniff mode */
    BTSRV_ACL_MODE_PARK    = 3, /* Park mode, not used */
    BTSRV_ACL_MODE_INVALID
} BTSRV_AclModeType_e;

typedef struct
{
    MAE_WChar *pFileNameForDialog;
    MAE_WChar *pDevNameForDialog;
    void *pUserData;
} BTSRV_RecvInfoForDialog_t;
#ifdef __BLUETOOTH_OBEX_MMI__

typedef enum
{
    BTSRV_OBEX_RECV_RESUME = 0
    ,BTSRV_OBEX_RECV_PAUSE
} BTSRV_RecvAction_e;

/*
The status code of receiving file from another device.
BTOBEXSRV_EVT_RECV_STATUS_IND event can have following possible types
*/

typedef enum
{
    BTSRV_TRANS_START = 0             //BTSRV can start Send/Receive file
    ,BTSRV_TRANS_SUCCESS              //BTSRV succeeds Sending/Receiving file
    ,BTSRV_IMPORT_VCS_SUCCESS         //BTSRV success importing vcs file
    ,BTSRV_IMPORT_PARTIALLY_SUCCESS   //BTSRV partially success importing vcs file
    ,BTSRV_TRANS_FAIL                 //BTSRV failed Sending/Receiving file

    ,BTSRV_TRANS_RECV_FAIL_EXTCARD    //No card
    ,BTSRV_TRANS_RECV_FAIL_NOSAPCE    //No enough storage space
    ,BTSRV_TRANS_RECV_FAIL_NOSAPCE_PHONE    //No enough phone storage space
    ,BTSRV_TRANS_RECV_FAIL_FILE_NAME_TOO_LONG //File name is too long to receive
    ,BTSRV_TRANS_RECV_CANCEL //The user does not accept the file
} BTSRV_TRANS_RESULT_e;

typedef enum
{
    BTSRV_OBEX_STATUS_CONNECTED = 0
    ,BTSRV_OBEX_STATUS_DISCONTED
    ,BTSRV_OBEX_STATUS_NOSERVICE
    ,BTSRV_OBEX_STATUS_ABORT
    ,BTSRV_OBEX_STATUS_LINK_BUSY
    ,BTSRV_OBEX_STATUS_SENDING
    ,BTSRV_OBEX_STATUS_RECVING
    ,BTSRV_OBEX_STATUS_SUCCESS
    ,BTSRV_OBEX_STATUS_FAILED
} BTSRV_ObexStatus_e ;

typedef enum
{
    BTSRV_OBEX_LINK_CONNECT = 0
    ,BTSRV_OBEX_LINK_DISCONT
} BTSRV_ObexLinkAction_e;

typedef bool (*BTSRV_ObexCallback)(void *FileBuff, u32 FileSize, void *FileInfo);

typedef struct
{
    u16 au16FilePathName[FILEMGR_MAX_FILEPATH_SIZE];
    u32 u32FileSize;
} BTOBEX_FileInfo_t;  // map to BT_FileInfo_t in api_bt_mmi.h

typedef struct
{
    u32 u32WriteSize;
    u32 FileSize;
    void *FileBuff;
}BTOBEX_WriteData_s;

typedef enum
{
	BTOBEX_WRITE_OK = 0,
	BTOBEX_WRITE_FILE_FAIL,
	BTOBEX_WRITE_INFO_FAIL
} BTOBEX_StatusWriteFile_e;

typedef struct
{
	BTOBEX_FileInfo_t tFileInfo;
	u8 *pBuff;
	u32 nWriteLen;
} BTOBEX_WriteFile_t;

typedef struct
{
	u8 *pBuff;
	u32 nWriteLen;
} BTOBEX_WriteReq_s;

#endif //__BLUETOOTH_OBEX_MMI__
#ifdef __BLUETOOTH_DRV_MSTAR_ACRUX2__
// sync to BT_PinPonTestRsp_t
typedef struct
{
    u32     test_result;
    u32     nb_tx_pkt;
    u32     nb_rx_pkt;
    u32     nb_valid_pkt;
    u32     nb_bit_error;
    u32     total_rx_bytes;
} BTSRV_Loopback_Result_t;
#endif
typedef enum
{
    BTSRV_CHIP_OFF = 0
    ,BTSRV_CHIP_ON,
} BTSRV_ChipStatus_e;

typedef enum
{
    BTSRV_UNKNOWN = 0
    ,BTSRV_ACCEPT_PAIRING
    ,BTSRV_CONNECT_INFO
    ,BTSRV_ACCEPT_CONNECT//to be removed
    ,BTSRV_ACCEPT_AUDIO_LNK_CONN
    ,
#ifdef __BLUETOOTH_OBEX_MMI__
    BTSRV_ACCEPT_RECV_FILE
    ,BTSRV_ACCEPT_IMPORT_FILE
    ,BTSRV_OPP_BLOCK_WARNING //OPP is blocked for performance issue
    ,BTSRV_OPP_WARNING_VIDEO_PLAYER //CPU consuming App is running (VideoPlayer /EMU)
    ,BTSRV_OPP_WARNING_EMU_GAME //CPU consuming App is running (VideoPlayer /EMU)
    ,BTSRV_SELECT_STORAGE_LOCATION // Inform btnotify app to pop-up storage selection window if default storage insufficient
#endif
#ifdef __BLUETOOTH_A2DP_MMI__
    ,BTSRV_A2DP_STREAM_STATUS // A2DP_Link exist but disable streaming
#endif
} BTSRV_IndicationType_e;

typedef struct
{
    BTSRV_IndicationType_e IndType;
    BTSRV_DevInfo_t DevInfo;              /* BTSRV_CONNECT_INFO, BTSRV_ACCEPT_PAIRING, BTSRV_ACCEPT_AUDIO_LNK_CONN, BTSRV_ACCEPT_RECV_FILE */
    BTSRV_Link_Status_e ConnectStatus;    /* BTSRV_CONNECT_INFO */
    BTSRV_AudioDevLinkStatus_t tAudioDevLinkStatus;
    boolean bIsConflict;
    boolean bIsDisableA2dpStream;
    u32 u32WarningMsgID;
} BTSRV_IndMsg_t;


/* Bluetooth Test Mode Command */
typedef enum
{
    BTSRV_RF_RSSI = 0
    ,BTSRV_RF_CONT_TX
    ,BTSRV_RF_CONT_RX
    ,BTSRV_RF_POWER
    ,BTSRV_RF_AUTO_TEST
} BTSRV_RfTestAction_e;

#ifdef __BLUETOOTH_A2DP_MMI__

typedef enum
{
    //Sync with BT_A2dpStatus_e
    BTSRV_A2DP_STATUS_SUCCESS = BT_A2DP_STATUS_SUCCESS
    ,BTSRV_A2DP_STATUS_FAILED = BT_A2DP_STATUS_FAILED
    ,BTSRV_A2DP_STATUS_CONNECTED = BT_A2DP_STATUS_CONNECTED
    ,BTSRV_A2DP_STATUS_DISCONTED = BT_A2DP_STATUS_DISCONTED
    ,BTSRV_A2DP_STATUS_NOSERVICE = BT_A2DP_STATUS_NOSERVICE
    ,BTSRV_A2DP_STATUS_ABORT = BT_A2DP_STATUS_ABORT
    ,BTSRV_A2DP_STATUS_TIMEOUT = BT_A2DP_STATUS_TIMEOUT
    ,BTSRV_A2DP_STATUS_LINK_BUSY = BT_A2DP_STATUS_LINK_BUSY
    ,BTSRV_A2DP_STATUS_REJECT = BT_A2DP_STATUS_REJECT
    ,BTSRV_A2DP_STATUS_NO_CHANNEL = BT_A2DP_STATUS_NO_CHANNEL
    ,BTSRV_A2DP_STATUS_CACHE_FULL = BT_A2DP_STATUS_CACHE_FULL
    ,BTSRV_A2DP_STATUS_EMPTY = BT_A2DP_STATUS_EMPTY
     //ResMgr PLAY / STOP event
    ,BTSRV_A2DP_STATUS_CONNECTED_PLAY = BTSRV_A2DP_STATUS_EMPTY + 1
    ,BTSRV_A2DP_STATUS_CONNECTED_STOP
    ,BTSRV_A2DP_STATUS_MAX = BTSRV_A2DP_STATUS_CONNECTED_STOP
} BTSRV_A2dpStatus_e;

typedef enum
{
    //ResMgr PLAY / STOP event
    BTSRV_A2DP_STREAMING_STATUS_PLAY = BTSRV_A2DP_STATUS_CONNECTED_PLAY
    ,BTSRV_A2DP_STREAMING_STATUS_STOP = BTSRV_A2DP_STATUS_CONNECTED_STOP
    ,BTSRV_A2DP_STREAMING_STATUS_MAX = BTSRV_A2DP_STREAMING_STATUS_STOP
} BTSRV_A2dpStreamingStatus_e;

/* A2DP Link Action */
typedef enum
{
    BTSRV_A2DP_LINK_CONNECT = 0
    ,BTSRV_A2DP_LINK_DISCONT
} BTSRV_A2dpLinkAction_e;

/* A2DP Action Type */
typedef enum
{
    BTSRV_A2DP_NONE_ACTION = 0
    ,BTSRV_A2DP_CAPABILITY
    ,BTSRV_A2DP_OPEN_STREAM
    ,BTSRV_A2DP_CLOSE_STREAM
    ,BTSRV_A2DP_PLAY
    ,BTSRV_A2DP_STOP
    ,BTSRV_A2DP_PAUSE
    ,BTSRV_A2DP_RESUME,
} BTSRV_A2dpActionType_e;

typedef struct
{
    BTSRV_A2dpLinkAction_e Connect;    /* Connect/Disconnect */
    u8 Addr[BTSRV_DEVICE_ADDR_SIZE];
} BTSRV_A2dpLink_t;
#endif /* __BLUETOOTH_A2DP_MMI__ */


/* AVRCP Action Type */
typedef enum
{
    BTSRV_AVRCP_NONE_ACTION = 0
    ,BTSRV_AVRCP_PALY
    ,BTSRV_AVRCP_STOP
    ,BTSRV_AVRCP_PAUSE
    ,BTSRV_AVRCP_RESUME
    ,BTSRV_AVRCP_VOLUME_UP
    ,BTSRV_AVRCP_VOLUME_DOWN
    ,BTSRV_AVRCP_REWIND
    ,BTSRV_AVRCP_FAST_FORWARD
    ,BTSRV_AVRCP_FORWARD
    ,BTSRV_AVRCP_BACKWARD
    ,BTSRV_AVRCP_MUTE

    ,BTSRV_AVRCP_PALY_RELEASED = (0x80 | BTSRV_AVRCP_PALY)
    ,BTSRV_AVRCP_STOP_RELEASED = (0x80 | BTSRV_AVRCP_STOP)
    ,BTSRV_AVRCP_PAUSE_RELEASED = (0x80 | BTSRV_AVRCP_PAUSE)
    ,BTSRV_AVRCP_RESUME_RELEASED = (0x80 | BTSRV_AVRCP_RESUME)
    ,BTSRV_AVRCP_VOLUME_UP_RELEASED = (0x80 | BTSRV_AVRCP_VOLUME_UP)
    ,BTSRV_AVRCP_VOLUME_DOWN_RELEASED = (0x80 | BTSRV_AVRCP_VOLUME_DOWN)
    ,BTSRV_AVRCP_REWIND_RELEASED = (0x80 | BTSRV_AVRCP_REWIND)
    ,BTSRV_AVRCP_FAST_FORWARD_RELEASED = (0x80 | BTSRV_AVRCP_FAST_FORWARD)
    ,BTSRV_AVRCP_FORWARD_RELEASED = (0x80 | BTSRV_AVRCP_FORWARD)
    ,BTSRV_AVRCP_BACKWARD_RELEASED = (0x80 | BTSRV_AVRCP_BACKWARD)
    ,BTSRV_AVRCP_MUTE_RELEASED = (0x80 | BTSRV_AVRCP_MUTE)
} BTSRV_AvrcpActionType_e;

typedef struct
{
    BTSRV_AvrcpActionType_e eActionType;
    u8 u8Addr[BTSRV_DEVICE_ADDR_SIZE];
} BTSRV_AvrcpCmd_t;

typedef enum
{
    BTSRV_AVRCP_REG_BACKGROUND = 0
    ,BTSRV_AVRCP_REG_FOREGROUND
    ,BTSRV_AVRCP_REG_TOTAL_NUM
} BTSRV_AvrcpRegType_e;

#endif /* __MMI_BTSRV_DEF_H__ */
