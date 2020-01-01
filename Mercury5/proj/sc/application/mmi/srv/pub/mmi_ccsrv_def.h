/**
 * @file    mmi_ccsrv_def.h
 * @brief   xxxx
 * @version $Id: mmi_ccsrv_def.h 40101 2009-09-12 07:05:56Z collin.chiang $
 */

#ifndef __MMI_CCSRV_DEF_H__
#define __MMI_CCSRV_DEF_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define CCSRV_MAX_CALL_NUMBER   40      /* Maximum call number length */
#define CCSRV_MAX_IP_NUMBER     5
#define CCSRV_SHORT_CALL_NUMBER 41      /* For display only */
#define CCSRV_MAX_CALL_NAME     41      /* Maximum call name length */
#define CCSRV_SHORT_CALL_NAME   CCSRV_SHORT_CALL_NUMBER     /* For display only */
#define CCSRV_MAX_CALL_TABLE    7       /* Maximum call entries numbers */
#define CCSRV_MAX_CLCC_ENTRY_NUM    8

#define CCSRV_NORMAL_CALL_CLEARING            16  //Cause No.16 "normal call clearing"
#define CCSRV_NORMAL_NON_SELECTED_CLEARING    26  //Cause No.26 "non-selected user clearing". Not supported. Treated as cause no. 31
#define CCSRV_NORMAL_UNSPECIFIED              31  //Cause No.31 "normal, unspecified"

#define CCSRV_SYS_LIMIT_TIME_IN_SEC           2208988740u  // time in seconds of 12/31/2039 23:59:00 

#define CCSRV_MAKE_CALL_HOLD_CALL_FAIL  998

/*=============================================================*/
// Data type definition
/*=============================================================*/

enum
{
    CC_AP_FID_UNKNOWN = 0
   ,CC_AP_FID_MAKECALL = 1
   ,CC_AP_FID_INCOMINCALL = 2
   ,CC_AP_FID_WAITINGCALL = 3
#ifdef __IP_CALL_MMI__
   ,CC_AP_FID_IPCALL = 4  // after finish all ip number selection, this fid will tranfers to makeCall
#endif
   ,CC_AP_FID_ENDCALL = 5
   ,CC_AP_FID_HOOK_ENDCALL = 6
   ,CC_AP_FID_ENDSPECIFICCALL = 7
};
typedef s32 MMI_CC_AP_FID_E;


typedef enum
{
    CCSRV_MO_NO_ERROR = 0
    // Reserve 1~127 to GSM04.08 specific cause value (Annex H)
    // Reserve 240~255 for MStar ATI  +CEER failure cause

   ,CCSRV_MO_FAILED = 999
   ,CCSRV_MO_CALL_NO_SIM_CARD = 1000
} CCSRV_MO_ERROR_CODE;

/* The status of one call in the call table */
typedef enum
{
    MMI_CALL_ACTIVE
   ,MMI_CALL_HELD
   ,MMI_CALL_DAILING
   ,MMI_CALL_ALERTING
   ,MMI_CALL_INCOMING
   ,MMI_CALL_WAITING
   ,MMI_CALL_UNKNOWN
} MMI_CCSRV_Status_e;

typedef struct
{
    u8 CallRefID;
} CCSRV_CallRefInd_t;

typedef struct
{
    boolean Result;
    u8 Cause;
} CCSRV_DialingCnf_t;

typedef struct
{
    u8 CallRefID;
    u8 CPHSLine;
    u8 TonNpi;
    u8 CallerNumber[CCSRV_MAX_CALL_NUMBER + 1];
} CCSRV_RingInd_t;

typedef struct
{
    u8 CallRefID;
    u8 Cause;
} CCSRV_RelInd_t;

typedef struct
{
    boolean Status;
} CCSRV_HangUpCnf_t;

typedef struct
{
    boolean Result;
    u8 Cause;
} CCSRV_AcceptCnf_t;

typedef struct
{
    u8 Code;  
    s8 Index;
} CCSRV_CallSetupNotifyInd_t;

typedef struct
{
    u8 Code;  
    s8 Index;  
    u8 TonNpi;
    u8 CalledNb[CCSRV_MAX_CALL_NUMBER + 1];
} CCSRV_InCallNotifyInd_t;

typedef struct
{
    u8 CallId;  
    MMI_CCSRV_Status_e Status;
} CCSRV_Clcc_Entry_t;

typedef struct
{
    boolean Status;
    u8 NbCalls;
    CCSRV_Clcc_Entry_t CallTable[CCSRV_MAX_CLCC_ENTRY_NUM];
} CCSRV_ClccCnf_t;

typedef union
{
    CCSRV_CallRefInd_t CallRefInd;  
    CCSRV_DialingCnf_t DialingCnf;  
    CCSRV_RingInd_t RingInd;
    CCSRV_HangUpCnf_t HangUpCnf;
    CCSRV_RelInd_t ReleaseInd;
    CCSRV_AcceptCnf_t AcceptCnf;
    CCSRV_CallSetupNotifyInd_t CallSetupNotifyInd;
    CCSRV_InCallNotifyInd_t InCallNotifyInd;
    CCSRV_ClccCnf_t CallClccCnf;
} CCSRV_unMsg_t;

/* The call direction in the call table */
typedef enum
{
    MMI_CALL_DIR_MO
   ,MMI_CALL_DIR_MT
} MMI_CCSRV_Direction_e; 

/* The mode of one call in the call table */
typedef enum
{
    MMI_CALL_MODE_VOICE
   ,MMI_CALL_MODE_DATA
   ,MMI_CALL_MODE_FAX
   ,MMI_CALL_MODE_UNKNOWN = 9
} MMI_CCSRV_Mode_e;

typedef enum
{
    MMI_CALL_DTMF_STOP
   ,MMI_CALL_DTMF_START
   ,MMI_CALL_DTMF_NONE
} MMI_CCSRV_DTMF_OP_e;

typedef enum
{
    CLIR_INFO_INVOKE_CLIR = 0
   ,CLIR_INFO_SUPPRESS_CLIR = 1
   ,CLIR_INFO_NOT_SPECIFIC = 2
} MMI_CLIR_INFO_e;

/* The attribute is used to distinguish the call manipulation. 
The attribute will be used with VM_MRL_CC_CHLD_REQ to RIL. */
/* The operation of CHLD */
typedef enum
{
    CCSRV_NO_OPERATION
   ,/* SEND 0 Category */
    CCSRV_REL_HELD_CALLS_ONLY
   ,CCSRV_REJECT_WAITING_CALL
   ,CCSRV_REJECT_WAITING_CALL_WHEN_MAKE_CALL
   ,CCSRV_WAITING_CALL_IN_BLACKLIST
   ,/* SEND 1 Category */
    CCSRV_REL_ACT_CALLS_ANSWER_CALL
   ,CCSRV_REL_ACT_CALLS_RETRIEVE_CALLS
   ,/* SEND 1X Category */
    CCSRV_REL_SPECIFIC_CALLS
   ,/* SEND 2 Category */
    CCSRV_HOLD_CALLS
   ,CCSRV_RETRIEVE_CALLS
   ,CCSRV_SWAP_CALLS
   ,CCSRV_HOLD_ACT_CALLS_ANSWER_CALL
   ,/* SEND 2X Category */
    CCSRV_SPLIT_CALL
   ,/* SEND 3 Category */
    CCSRV_JOIN_MPTY_CALL
   ,/* SEND 4 Category */
    CCSRV_TRANSFER_CALLS
   ,/* Extend Category*/
    CCSRV_REPLCAE_HELD_CALL
   ,/* Use in 1A1H1W only*/
    CCSRV_RELEASE_ALL_HELD_CALL_ONLY
   ,/* Use in 1AW, 1AHW to release all held call*/
    CCSRV_RELEASE_ALL_ACTIVE_CALL_ONLY
   ,/* Use in 1AH, 1AHW, 1AW only*/
} MMI_Call_Chld_Type_e;

/* The attribute of one call in the call table */
typedef enum
{
    /* To indicate the MO/MT call is normal call. MMI have to display the call record by call number or call name. */
    MMI_CALL_ATTR_NORMAL = 0 
    /* To indicate the CLIR of the MT call is enable */
   ,MMI_CALL_ATTR_ANONYMOUS
    /* To indicate the MO call is an emergency call */
   ,MMI_CALL_ATTR_EMERGENCY
    /* To indicate the MO call is an STK call */
   ,MMI_CALL_ATTR_STK
} MMI_CCSRV_Attr_e;


typedef enum
{
    CCSRV_OVERWRITE_MODE = 0
   ,CCSRV_UPDATE_MODE
} CCSRV_UpdateMode_e;

/* The enum is used for APP to check the CC Service status */
typedef enum
{
    CCSRV_IDLE = 0
   ,CCSRV_1A
,                   // 1 active call (or 1 MPTY call)
    CCSRV_1H
,                   // 1 hold call
    CCSRV_1A1H
,               // 1 active and 1 hold call
    CCSRV_1AW
,               // 1 active and 1 waiting call
    CCSRV_1HW
,               // 1 hold call and 1 waiting call
    CCSRV_1AHW
,               // 1 active, 1 hold and 1 waiting call
    CCSRV_MAKE2NDCALL
,   // 1 hold call and dial another call
    CCSRV_INCOMING
,       // 1 incoming call
    CCSRV_OUTGOING
,       // 1 outgoing call  
    CCSRV_UNKNOWN
} CCSRV_Mode_e;

typedef enum
{
    CCSRV_MASTER_CALL_EXISTED = 0
   ,CCSRV_SLAVE_CALL_EXISTED
   ,CCSRV_NO_CALL
   ,CCSRV_STATUS_UNKNOW
} CCSRV_DUO_STATUS_e;

enum
{
    CCSRV_MT_TYPE_RING = 0
   ,CCSRV_MT_TYPE_WAITING = 1
 ,  // For 1A1W or 1H1W
    CCSRV_MT_TYPE_WAITING_FULL = 2      // For 1A1H1W
};

typedef s32 CCSRV_MT_TYPE_E;

enum
{
    CCSRV_NUMBER_NATIONAL = 129
   ,CCSRV_NUMBER_INTERNATIONAL = 145
};
typedef u8 CCSRV_NUMBER_Type_e;

enum
{
    CCSRV_DURATION_CURRENT
   ,CCSRV_DURATION_FINAL
};
typedef u8 CCSRV_DURATION_Type_e;

enum
{
    CCSRV_CLCC_NONE,
    CCSRV_CLCC_HANGUP,
    CCSRV_CLCC_CHLD,
    CCSRV_CLCC_ATA
};
typedef u8 CCSRV_CLCC_Type_e;

enum
{
	ANSWERING_MACHINE_NONE = 0, 
	ANSWERING_MACHINE_INSUFFICIENT_STORAGE, 
	ANSWERING_MACHINE_MASS_STORAGE,
	ANSWERING_MACHINE_WEBCAM,
	ANSWERING_MACHINE_CARD_ABSENT,
	ANSWERING_MACHINE_CHECK_DISK,
	ANSWERING_MACHINE_DISK_FORMAT,
	ANSWERING_MACHINE_THIRD_PARTY_AP_RUNNING,
	ANSWERING_MACHINE_VOICEBOX_FULL
};
typedef u8 ANSWERING_MACHINE_FAILED_TYPE_e;

enum
{
    CCSRV_CAUSE_USER_BUSY = 17
   ,CCSRV_CAUSE_NO_USER_RESPONDING = 18		
   ,CCSRV_CAUSE_SUBSCRIBER_ABSENT = 20
   ,CCSRV_CAUSE_NUMBER_CHANGED = 22
};

/* The structure describes the general information of a call */
typedef struct
{
    u8 u8CallID;                                    //Used to identify the call, range is from 1 to 7 only
    MMI_CCSRV_Direction_e CallDir;              //Used to show call direction (MO or MT call)
    MMI_CCSRV_Status_e CallStatus;                  //Used to show the current status (active, held, dialing, alerting...)
    MMI_CCSRV_Mode_e CallMode;                  //Used to show current call is voice or data call (voice, data, fax...)
    boolean bMPTY;                                  //Used to show this call is belonged to MPTY call or not
    u8 CallNumber[CCSRV_MAX_CALL_NUMBER + 1];       //Record the call number
    MAE_WChar CallName[CCSRV_MAX_CALL_NAME + 1];    //Name of the call number
    MMI_CCSRV_Attr_e CallNumberAttr;             //Indicate the call attribute (NORMAL, ANONYMOUS, EMERGENCY, STK)
    u32 u32StartTime;
    u32 u32MinuteTick;                              //The counter of minute tick after 2039:12:31 23:59:00
    u32 u32ImageID;                                 //The image ID stored in Phonebook
    u32 u32RingtoneID;                              //The ringer ID stored in Phonebook
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
	u32 u32VideoID;									//The video ID stored in Phonebook
#endif
    u32 u32PhbCheckValue;                           // Make sure the search name confirm (to Phonebook) belong to this call entry
#ifdef __CALLER_LOCATION__
    MAE_WChar *pstrCallCL;							// store caller location
#endif // __CALLER_LOCATION__
#ifdef __3G_RIL_MMI__
    boolean    bIsHangUpFromLocal;
#endif //__3G_RIL_MMI__
} CallEntry_t;

/* The structure will store the necessary information during in-call session */
typedef struct
{
    CallEntry_t CallTable[CCSRV_MAX_CALL_TABLE];
} CallTable_t;


/* This structure is call table flag. 
Update the corresponding field only if the flag is TRUE */
typedef struct
{
    boolean bCallID;
    boolean bCallDir;
    boolean bCallStatus;
    boolean bCallMode;
    boolean bMpty;
    boolean bCallNumber;
    boolean bCallName;
    boolean bCallNumberAttr;
    boolean bImageID;
} CallEntryFlag_t;

/* User has to fill the fields he want to update(UpdateFlag) and provides the data(UpdateEntry) */
typedef struct
{
    CallEntryFlag_t EntryFlag;
    CallEntry_t EntryData;
} CallTableEntry_t;

typedef struct
{
    u8 CallNumber[CCSRV_MAX_CALL_NUMBER + 1];
    u8 CallNum2CallLog[CCSRV_MAX_CALL_NUMBER + 1];
    u8 IPNumber[CCSRV_MAX_IP_NUMBER + 1];
    MAE_WChar CallName[CCSRV_MAX_CALL_NAME + 1];    
    u32 u32ImageID;                                 
    u32 u32RingtoneID;              
    boolean bSTKMakeCall;       // STK will request: Release call existed calls first, them make STK call
} MmiMakeCallReq_t;

typedef struct
{
    CCSRV_MT_TYPE_E type;
    u8 u8DualID;
} MmiMTCallInd_t;

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/

#endif /* __MMI_CCSRV_DEF_H__ */
