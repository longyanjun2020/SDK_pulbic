/**
 *  @file   mmi_common_sms_master.h
 *  @brief  it is used for communination within different Applications/Services in sms utility functions.
 *
 * @version $Id: mmi_common_sms_master.h 39985 2009-09-11 07:24:33Z miya.chien $
 * @author	joe.hsu
 */
#ifndef __MMI_COMMON_SMS_MASTER_H__
#define __MMI_COMMON_SMS_MASTER_H__

#include "mmi_common_custom.h"
#include "mmi_common_mms.h"
#include "mmi_mae_helper.h"

extern const MAE_WChar MFINBOX[];             //L"fs:/PHON/SMS/mfinbox"
extern const MAE_WChar MFOUTBOX[];            //L"fs:/PHON/SMS/mfoutbox"
extern const MAE_WChar MFSENT[];              //L"fs:/PHON/SMS/mfsent"
extern const MAE_WChar MFDRAFT[];             //L"fs:/PHON/SMS/mfdraft"
extern const MAE_WChar MSGIDFILE[];           //L"fs:/PHON/SMS/MsgID"
extern const MAE_WChar MFMSGPATH[];           //L"fs:/PHON/SMS/"
extern const MAE_WChar TEMP_FILE_POSTFIX[];   //L"_temp"
extern const MAE_WChar MFRAWDATA_TEMP_FILE[]; //L"fs:/PHON/SMS/_temp"
extern const MAE_WChar MFINBOXTEMP[];         //L"fs:/PHON/SMS/mfinbox_temp"
extern const MAE_WChar MFOUTBOXTEMP[];        //L"fs:/PHON/SMS/mfoutbox_temp"
extern const MAE_WChar MFSENTTEMP[];          //L"fs:/PHON/SMS/mfsent_temp"
extern const MAE_WChar MFDRAFTTEMP[];         //L"fs:/PHON/SMS/mfdraft_temp"
extern const MAE_WChar MSGIDFILETEMP[];       //L"fs:/PHON/SMS/MsgID_temp"
extern const MAE_WChar MFPMBOX[];             //L"fs:/PHON/SMS/mfpmbox"	  for port message
extern const MAE_WChar MFPMBOXTEMP[];         //L"fs:/PHON/SMS/mfpmbox_temp" for port message
extern const MAE_WChar MFTNBOX[];             //L"fs:/PHON/SMS/mftnbox"	  for telno message
extern const MAE_WChar MFTNBOXTEMP[];         //L"fs:/PHON/SMS/mftnbox_temp" for telno message

#ifdef __MMI_SMS_TRASHBOX__
#define MAX_PHONE_MSG_AMOUNT 	(MAX_PHONE_SMS_AMOUNT+MMI_MMS_MAX_AMOUNT+CBS_MAX_CBMSG_SIZE+MAX_PM_MSG_NUM+MAX_TRA_MSG_NUM)
#else
#define MAX_PHONE_MSG_AMOUNT 	(MAX_PHONE_SMS_AMOUNT+MMI_MMS_MAX_AMOUNT+CBS_MAX_CBMSG_SIZE+MAX_PM_MSG_NUM)
#endif

#define MIN_PHONE_MSG_ID        1
#define MAX_PHONE_MSG_ID 		(MIN_PHONE_MSG_ID + MAX_PHONE_MSG_AMOUNT -1)
#define MIN_MSG_ID 				MIN_PHONE_MSG_ID
#define NULL_MSG_ID             0

// sms ID
#ifdef __MMI_SMS_TRASHBOX__
#define MAX_PHONE_SMS_ID 		(NULL_MSG_ID + MAX_PHONE_SMS_AMOUNT + MAX_TRA_MSG_NUM)
#else
#define MAX_PHONE_SMS_ID 		(NULL_MSG_ID + MAX_PHONE_SMS_AMOUNT)
#endif

// mms ID
#define MIN_MMS_MSG_ID			(MAX_PHONE_SMS_ID + 1)
#define MAX_MMS_MSG_ID			(MAX_PHONE_SMS_ID + MMI_MMS_MAX_AMOUNT)


// cb ID
#define CBS_MAX_CBMSG_SIZE   	25   // number of CB message at phone for iphone style new flow
#define MIN_CB_MSG_ID			(MAX_MMS_MSG_ID + 1)
#define MAX_CB_MSG_ID			(MAX_MMS_MSG_ID + CBS_MAX_CBMSG_SIZE)


// wap push/port msg ID
#define MAX_PM_MSG_NUM			10
#define MIN_PM_MSG_ID			(MAX_CB_MSG_ID + 1)
#define MAX_PM_MSG_ID			(MAX_CB_MSG_ID + MAX_PM_MSG_NUM)

#ifdef __MMI_SMS_TRASHBOX__
// trash sms ID
#define MAX_TRA_MSG_NUM			20
#endif

// sim ID
#define MAX_SIM_MSG_NUM         300
#define MAX_SIM_MSG_ID          (MAX_PHONE_MSG_ID+2*MAX_SIM_MSG_NUM) //for 2 SIM card, 600 SMS
#define MIN_SIM_MSG_ID          (MAX_PHONE_MSG_ID+1)
#define MAX_MASTER_SIM_MSG_ID   (MAX_PHONE_MSG_ID+MAX_SIM_MSG_NUM)
#define MIN_MASTER_SIM_MSG_ID   (MAX_PHONE_MSG_ID+1)
#define MAX_SLAVE_SIM_MSG_ID    MAX_SIM_MSG_ID
#define MIN_SLAVE_SIM_MSG_ID    (MAX_MASTER_SIM_MSG_ID+1)

#define MAX_MSG_FILE_BYTE_LEN	10
#define MAX_FILE_FULL_PATH_LEN  30

#ifdef __SMS_SEND_FROM_BUFFER__
#define BUFF_MSG_ID_BASE        0xB000
#define IS_BUFF_MSG(msgId)      ((msgId & BUFF_MSG_ID_BASE) == BUFF_MSG_ID_BASE)
#define MAX_BUFF_MSG_NUM        8
#endif /* __SMS_SEND_FROM_BUFFER__ */

enum
{
	SMI_MAX_VP_LEN	   =  7,
	SMI_RECP_LST_NUM   =  1,
	SMI_MAX_ADDR_LEN   =  20,
	SMI_SCA_LEN_MAX    =  21,
	SMI_MEMO_BYTE_LEN   =  30,
    SMI_PHONE_SMS_MEMO_BYTE_LEN   =  50,
#ifdef __MMI_SMS_WAPPUSH__
	SMI_MAX_WapPush_URL_LEN= 256, 
#endif
};

enum  {
	SMI_SUCCESS	= 0,
    SMI_PARTIAL_FAIL,
    SMI_FAIL,
    SMI_SIM_FULL,
    SMI_SIM_RESET_ABORT,
    SMI_PHONE_FULL,
	SMI_MsHeaderNotFound,			/* Header not found in header list */
	SMI_MsInitialiseFailed,				/* Message manager initialisation failed */
	SMI_MsFileOpFailed,					/* File operation failed */
	SMI_MsDeleteFailed,					/* Delete of a message failed */
	SMI_MsHeaderUpdateFailed,			/* Updating a message header failed */
	SMI_MsInvalidMessageId,				/* Id not recognised */
    SMI_SEND_FAILED,
    SMI_EXPORT_SMS
} ;
typedef u8 SMI_MsgMgrStatus_e;

enum  {
	SMI_SMS_NONE = 0,
	SMI_SMS_SIM_MASTER_BOX,
    SMI_SMS_SIM_SLAVE_BOX,
} ;
typedef u8 SMI_SmsSimMsgBox_e;

enum {
    MtSms = 0,                  /*GSM SMS or EMS message.*/
    MtSmscb,                    /*GSM cell broadcast message. */
#ifdef __MMI_SMS_TRASHBOX__
    MtSmstrash,
#endif
#ifdef __MMI_SMS_WAPPUSH__
    MtWapPushSms, 
#endif
    MtWemt,                     /*CDMA SMS message.*/
    MT_MMS_START,
    MtMms = MT_MMS_START,       /*MMS message no scripting.*/
    MtMmsSmil,                  /*MMS message SMIL encoded.*/
    MtMmsXhtml,                 /*MMS message XHTML encoded.*/
    MtMmsMixed,                 /*MMS message SMIL + XHTML.*/
    MtMmsNotSet,
    MtMmsNotMarkUp,
    MtOTAProvision,             /*OTA provision. */
    MT_MMS_END = MtOTAProvision,
    MT_NUM_MESSAGE_TYPES        /*Number supported message types.*/
};
typedef u8 SMI_MsgType_e;

typedef enum {
	TimeStampNull = 0,
	TimeStampRelative,
	TimeStampAbsolute,
} SMI_TimeStampVar_e;

enum {
//    MlMsgInPhoneStart=0,
	MlInbox = 0,	/*!< Message is in the inbox */
  MlDraft,						/*!< Message is a dradft message */
	MlOutbox,						/*!< Message has been sent (UI) but not yet dispatched */
	MlSent,							/*!< Message has been sent to MMS proxy-relay */
	MlPmbox,       //incoming Port SMS
#ifdef __MMI_SMS_TRASHBOX__
	MlTrabox,      // incoming Trash SMS
#endif
	MlPvInbox,
	MlPvDraft,
	MlPvOutbox,
	MlPvSent,
	MLCblInbox,
	MlMsgInPhoneEnd=MLCblInbox,
	MlSim1InBox,    //incoming SMS in Master SIM
	MlSim2InBox,    //incoming SMS in Slave SIM
	MlSim1Sent,    //incoming SMS in Master SIM
	MlSim2Sent,    //incoming SMS in Master SIM
	MlUserBox1,
	MlUserBox2,
	MlUserBox3,
	MlTempBox,
	MlTnbox,        // incoming TelNo SMS
	MlUnknown
};
typedef u8 SMI_MsgLocation_e;

typedef enum {
	EncodingGSM7Bit=0,		/*!< Comment */
	Encoding8BitASCII,		/*!< Comment */
	EncodingUCS2,			/*!< Comment */
	Encoding7BitASCII,		/*!< Comment */
	EncodingGSM8Bit,		/*!< Comment */
	EncodingIS91,			/*!< Comment */
	EncodingUNICODE,		/*!< Comment */
	EncodingIA5,			/* ITU-T T.50 */
	EncodingHebrew,		/* ISO 8859-8 */
	EncodingLatin,			/* ISO 8859-1 */
    SE_NUM_ENCODINGS,
} SMI_SmEncoding_t;

enum
{
	sentunknown = 0,
	sentfail,
	sent,
	unsent,
	sending
};
typedef u8 SMI_SentStatus_e;

#define SMI_AVAILABLE_ID_HEADER_SIZE (sizeof(boolean)+2*sizeof(u32))

typedef u32  SMI_Available_MsgId_t;

typedef struct {
	u16				year;
	u8				month;
	u8				day;
	u8				hour;
	u8				min;
	u8				sec;
} SMI_TimeStamp_t;



enum{
    SMI_FLAG_READ_MASK=0x01,
    SMI_FLAG_COMPLETE_MASK=0x02,
    SMI_FLAG_REPLACE_MASK=0x04,
    SMI_FLAG_MULTI_RECIPIENT_MASK=0x08,
    SMI_FLAG_SEND_MASK=0x70, // 3 bit
    SMI_FLAG_UNSEND_STATUS =0x00,
    SMI_FLAG_SENDING_STATUS =0x10,
    SMI_FLAG_SENT_SUCCESS_STATUS =0x20,
    SMI_FLAG_SENT_FAIL_STATUS =0x30,
    SMI_FLAG_SENT_RETRY_STATUS =0x40,
    SMI_FLAG_SUSPEND_OPERATION_MASK =0x80, // current message is deleting or moving
};
typedef u8 SMI_MsgFlag;

enum{
    SMI_MSGID_PHONE_SMS_MSG,
    SMI_MSGID_CB_MSG,
    SMI_MSGID_MMS_MSG,
    SMI_MSGID_SIM1_SMS,
    SMI_MSGID_SIM2_SMS,
    SMI_MSGID_PM_MSG,
};
typedef u8  SMI_MsgID_Type_e;

typedef u16 SMI_MsgID_t;

typedef struct {
    SMI_TimeStamp_t timestamp; // SMS Service Center TimeStamp for MT message, handset TimeStamp for MO message
    SMI_MsgID_t u16MsgId;  // bit message id - generated by message center
    u16 reference; // 16 bit reference to cross check with Message part
    SMI_MsgType_e type; // SMI_MsgType_e, Message type for this message
    SMI_MsgLocation_e location; // SMI_MsgLocation_e, Current location of this message
    SMI_MsgFlag msgFlag;
    u8 SimModule; // record the sim card for sent
    u8 addr[SMI_MAX_ADDR_LEN*2+1];	// Sender Address
	SMI_SmsSimMsgBox_e SmsSimMsgBox;
	u8 IsWapVCardMessage; //check if it is VCard message
} SMI_MsgHdr_t;

typedef struct {
    u8 SimModule;
    u16 lAddress[SMI_MAX_ADDR_LEN+1]; //sender address for MT message
    SMI_TimeStamp_t timestamp; // SMS Service Center TimeStamp for MT message, handset TimeStamp for MO message
} SMI_MsgSrHdr_t;

typedef struct {
    u8                  cntMemo[SMI_MEMO_BYTE_LEN+1]; //message content highlight part
    u8                  bMoreCnt;
    u8					lAddress[SMI_MAX_ADDR_LEN+1]; //sender address for MT message
	u8					simIndex[MAX_CONCATENATE_PACKAGE];			// 8 bit array of SIM message index
	SMI_MsgID_t u16MsgId;  // bit message id - generated by message center
	u8					nMaxPartNum;
	u8 IsWapVCardMessage; //check if it is VCard message
} SMI_SimMsgHdr_t;


//#define SMI_MSG_HDR_LIST_HEADER_SIZE (2*sizeof(u32)+2*sizeof(u16))

typedef struct {
	u32					size;						// Number of headers in the _MsgHdr_t
	u32					privateSize;				// Number of private msg in the _MsgHdr_t
	u16					readNum;					// Number of read msg in the _MsgHdr_t
	u16					prvReadNum;					// Number of read private msg in the _MsgHdr_t
	u16					sendingNum;					// Number of sending msg in the _MsgHdr_t
	u16					prvSendingNum;				// Number of private sending msg in the _MsgHdr_t
} SMI_MsgHdrLstHdr_t;


typedef struct {
    SMI_MsgHdrLstHdr_t   ListHdr;
    SMI_MsgHdr_t		*pList;					// Pointer to an array of SMI_MsgHdr_t structures
} SMI_MsgHdrLst_t;

typedef struct {
    u32					size;
    SMI_SimMsgHdr_t		*pList;					// Pointer to an array of SMI_SimMsgHdrLst_t structures
} SMI_SimMsgHdrLst_t;

typedef struct {
	u8					cSMSCAddress[SMI_SCA_LEN_MAX];	// ascii < SMSC Address Field in  ascii  characters
	u8					iSMSCAddressSize;
	u8					iSMSCAddrType;

} SMI_MsgSmscInfo_t;

typedef struct {
	SMI_SmEncoding_t	encoding;
	u16 mid;
} SMI_CBHdr_t;


/*!
\brief		Search flags for mmi_SMI_ListMessageByParam() reporter function.
 */
#define SMI_LIST_NON_PRIVATE_SHIFT_TO_PRIVATE  4
#define SMI_LIST_ALL					( (u32) 0xFFFFFFFF )
/*Msg Box*/
#define SMI_LIST_INBOX					( (u32) 0x00000001 )
#define SMI_LIST_OUTBOX					( (u32) 0x00000002 )
#define SMI_LIST_SENTBOX				( (u32) 0x00000004 )
#define SMI_LIST_DRAFT					( (u32) 0x00000008 )
#define SMI_LIST_NON_PRIVATE_BOX_MASK   ( (u32) 0x0000000F )
#define SMI_LIST_PRVINBOX				( (u32) 0x00000010 )
#define SMI_LIST_PRVOUTBOX				( (u32) 0x00000020 )
#define SMI_LIST_PRVSENTBOX				( (u32) 0x00000040 )
#define SMI_LIST_PRVDRAFT				( (u32) 0x00000080 )
#define SMI_LIST_PRIVATE_BOX_MASK  		( (u32) 0x000000F0 )
#define SMI_LIST_BOX_MASK			    ( (u32) 0x000000FF )

/*Msg Storage*/
#define SMI_LIST_REMOTE					( (u32) 0x00000100 )
#define SMI_LIST_MASTER_SIM				( (u32) 0x00000200 )
#define SMI_LIST_SLAVE_SIM				( (u32) 0x00000400 )
#define SMI_LIST_PHONE					( (u32) 0x00000800 )
#define SMI_LIST_STORAGE_MASK           ( (u32) 0x00000F00 )

/*Sent Status*/
#define SMI_LIST_SENT				    ( (u32) 0x00001000 )
#define SMI_LIST_NOT_SENT				( (u32) 0x00002000 )
#define SMI_LIST_RESENT			    	( (u32) 0x00004000 )
#define SMI_LIST_SENT_FAIL		    	( (u32) 0x00008000 )
#define SMI_LIST_SENT_MASK              ( (u32) 0x0000F000 )



#define SMI_LIST_READ					( (u32) 0x00010000 )
#define SMI_LIST_UNREAD					( (u32) 0x00020000 )
#define SMI_LIST_READ_MASK				( (u32) 0x00030000 )

#define SMI_LIST_COMPLETE				( (u32) 0x00040000 )
#define SMI_LIST_INCOMPLETE				( (u32) 0x00080000 )
#define SMI_LIST_COMPLETE_MASK			( (u32) 0x000c0000 )

#define SMI_LIST_REMOTE_DELIVERED		( (u32) 0x00100000 )
#define SMI_LIST_REMOTE_NOT_DELIVERED	( (u32) 0x00200000 )
#define SMI_LIST_DELIVERED_READ			( (u32) 0x00400000 )
#define SMI_LIST_DELIVERED_NOT_READ		( (u32) 0x00800000 )
#define SMI_LIST_DELIVERED_MASK 		( (u32) 0x00F00000 )

#define SMI_LIST_DELETING				( (u32) 0x01000000 )
#define SMI_LIST_NON_DELETING			( (u32) 0x02000000 )
#define SMI_LIST_DELETING_MASK 			( (u32) 0x03000000 )

/*Remote MMS Retrievable*/
#define SMI_LIST_RETRIEVABLE			( (u32) 0x04000000 )
#define SMI_LIST_NOT_RETRIEVABLE		( (u32) 0x08000000 )
#define SMI_LIST_RETRIEVABLE_MASK       ( (u32) 0x0c000000 )

/*Message Type*/
#define SMI_LIST_SMS                    ( (u32) 0x10000000 )
#define SMI_LIST_CB                     ( (u32) 0x20000000 )
#define SMI_LIST_MMS			        ( (u32) 0x40000000 )
#ifdef __MMI_SMS_TRASHBOX__
#define SMI_LIST_TRASMS			        ( (u32) 0x80000000 )
#endif
#define SMI_LIST_MSG_TYPE_MASK          ( (u32) 0xF0000000 )


/*
\brief		Status flags for message contains all control information
 */
#define SMI_FLAGS_INBOX					( (u32) 0x00000001)	/*!< */
#define SMI_FLAGS_OUTBOX				( (u32) 0x00000002)	/*!< */
#define SMI_FLAGS_SENT					( (u32) 0x00000004)	/*!< */
#define SMI_FLAGS_DRAFTS				( (u32) 0x00000008)	/*!< */
#define SMI_FLAGS_REMOTE				( (u32) 0x00000010)	/*!< */

/*!
\brief		Status flags for messages in the message manager
 */
#define		SMI_FLAGS_MESSAGE_COMPLETE	( (u32) 0x00000001 )		/*!< */
#define		SMI_FLAGS_MESSAGE_CLEANUP	( (u32) 0x00000100 )		/*!< */

/*!
\var	MM_INVALID_MESSAGE_ID
\brief
*/
#define		SMI_INVALID_MESSAGE_ID		((u32)0xFFFFFFFF)			/*!< */
#define		EMM1Read 1
#define		EMM1Deleted 0

typedef		u32	SMI_LIST_PARAM;



#endif /*__MMI_COMMON_SMS_MASTER_H__*/
