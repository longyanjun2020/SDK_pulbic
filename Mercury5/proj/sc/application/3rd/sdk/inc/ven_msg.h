#ifndef __VEN_MSG_H_
#define __VEN_MSG_H_
/***************************************************************************/
/*  File : ven_mag.h                                                       */
/*-------------------------------------------------------------------------*/
/*  Scope: This file defines the msg related vendor request API,           */
/*         and MMI response API.                                           */
/*                                                                         */
/***************************************************************************/

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Preprocessor Macro Definition                                            */
/*--------------------------------------------------------------------------*/
#define VEN_MSG_SMS_SERVICE_CENTER_MAX_CHAR 21 // Max character length of SMS service center number

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

enum
{
    VEN_MSG_RET_SUCCESS             = 0, ///< operation completed successfully
    VEN_MSG_RET_FAILED              = 1, ///< WHAT? every code here is failed
    VEN_MSG_RET_NOT_SUPPORT         = 2, ///< not support
    VEN_MSG_RET_BAD_PARAM           = 3, ///< invalid input parameters
    VEN_MSG_RET_OUT_OF_MEMORY       = 4, ///< memory is not enough to complete the operation
};
typedef u32 ven_msg_ret_t;

enum
{
    VEN_MSG_SMS_TYPE_UNSPECIFIC = 0,
    VEN_MSG_SMS_TYPE_7BIT = 1,
    VEN_MSG_SMS_TYPE_8BIT = 2,
    VEN_MSG_SMS_TYPE_UCS2 = 3,
	VEN_MSG_SMS_TYPE_7BitASCII,		/*!< Comment */
	VEN_MSG_SMS_TYPE_GSM8Bit,		/*!< Comment */
	VEN_MSG_SMS_TYPE_IS91,			/*!< Comment */
	VEN_MSG_SMS_TYPE_UNICODE,		/*!< Comment */
	VEN_MSG_SMS_TYPE_IA5,			/* ITU-T T.50 */
	VEN_MSG_SMS_TYPE_Hebrew,		/* ISO 8859-8 */
	VEN_MSG_SMS_TYPE_Latin,			/* ISO 8859-1 */     
};
typedef u8 ven_msg_sms_type_t;

enum
{
    VEN_MSG_SMS_SEND_RESULT_SUCCESS  = 0,
    VEN_MSG_SMS_SEND_RESULT_FAIL = 1,
    VEN_MSG_SMS_SEND_RESULT_SAVETOOUTBOX_FAIL = 2,
};
typedef u8 ven_msg_sms_send_result_t;

enum
{
    VEN_MSG_SMS = 0,
    VEN_MSG_CBS = 1,
    VEN_MSG_MMS = 2,

	VEN_MSG_INVALID = 0xff,	//no meaning
};
typedef u8 ven_msg_type_t;

enum
{
    VEN_MMS_HEADER_FROM = 0,
    VEN_MMS_HEADER_TO,
    VEN_MMS_HEADER_CC,
    VEN_MMS_HEADER_BCC,
    VEN_MMS_HEADER_SUBJECT,
    VEN_MMS_HEADER_SENDER_VISIBILITY,
    VEN_MMS_HEADER_DELIVERY_REPORT,
    VEN_MMS_HEADER_READ_REPLY,
};
typedef u8 ven_msg_mms_header_param_t;

typedef u32 ven_msg_mms_handle_t;

enum {
	//--- single box ---
	VEN_MSG_PH_Inbox = 0,		//phone public
	VEN_MSG_PH_Draft,					
	VEN_MSG_PH_Outbox,		
	VEN_MSG_PH_Sent,				
	VEN_MSG_PH_PvInbox,			//phone private
	VEN_MSG_PH_PvDraft,			
	VEN_MSG_PH_PvOutbox,		
	VEN_MSG_PH_PvSent,		
	VEN_MSG_SIM1_InBox,			//sim1
	VEN_MSG_SIM1_Draft, 
	VEN_MSG_SIM1_Sent, 
	VEN_MSG_SIM2_InBox,  		//sim2
	VEN_MSG_SIM2_Draft,
	VEN_MSG_SIM2_Sent,   
	
	//--- multiple boxes --- 
	VEN_MSG_PH_PUBLIC_ALL = 0x80, 
	VEN_MSG_PH_PRIVATE_ALL,				
	VEN_MSG_PH_ALL,								
	VEN_MSG_SIM1_ALL,
	VEN_MSG_SIM2_ALL,

	VEN_MSG_BOX_INVALID = 0xff,	//no meaning
};
typedef u8 ven_msg_box_t; 

enum {
	VEN_MSG_READ = 0,	
	VEN_MSG_UNREAD,	

	VEN_MSG_READ_INVALID = 0xff,	//no meaning							
};
typedef u8 ven_msg_readstatus_t; 

enum {
	VEN_MSG_TO_SEND = 0,	
	VEN_MSG_SENT_FAIL,
	VEN_MSG_SENT_SUCCESS,	//only in sentbox
	//--- internal status ---
	VEN_MSG_SENDING,							
	VEN_MSG_SENT_RETRY,
	
	VEN_MSG_SEND_INVALID = 0xff,	//no meaning
};
typedef u8 ven_msg_sendstatus_t;

enum
{
    VEN_MSG_DATA_BYTEDATA = 0,
    VEN_MSG_DATA_TEXTDATA = 1,
};
typedef u8 ven_msg_data_t;

enum
{
    VEN_MSG_NOT_SAVE_SENT_MSG = 0,  ///< do not save sent message in sent box
    VEN_MSG_SAVE_SENT_MSG           ///< save sent message in sent box
};
typedef u8 ven_msg_save_sent_msg_t;

enum
{
    VEN_MSG_NOT_RETRY_SEND_MSG = 0,  ///< do not retry to send message when we fail to send the message
    VEN_MSG_RETRY_SEND_MSG           ///< retry to send message till the message is succesfully sent
};
typedef u8 ven_msg_retry_sent_msg_t;

enum
{
    VEN_MSG_PORT_DISABLE = 0,       ///< message without port
    VEN_MSG_PORT_ENABLE             ///< message with port
};
typedef u8 ven_msg_msg_port_porp_t;

enum
{
    VEN_MSG_EDITOR_SMS = 0,
    VEN_MSG_EDITOR_MMS,
    VEN_MSG_EDITOR_NUM,
};
typedef u8 ven_msg_editor_type_t;

enum
{
    VEN_MMS_OBJECT_NONE = 0,
    VEN_MMS_OBJECT_IMAGE,
    VEN_MMS_OBJECT_AUDIO,
    VEN_MMS_OBJECT_VIDEO,
    VEN_MMS_OBJECT_VCS,
    VEN_MMS_OBJECT_TEXT,
    VEN_MMS_OBJECT_ATTACHMENT,
    VEN_MMS_OBJECT_NUM,
};
typedef u8 ven_msg_mms_object_t;

#ifdef __SDK_API_01_SMS_MMS_CC__
enum
{
	VEN_MSG_RESPONSE_OK = 0,
	VEN_MSG_RESPONSE_TRANSIENT_FAILURE,
	VEN_MSG_RESPONSE_STORAGEFULL,
	VEN_MSG_RESPONSE_PARAMERROR,
	VEN_MSG_RESPONSE_NETWORKPROBLEM,
	VEN_MSG_RESPONSE_SERVICESUSPENDED,
	VEN_MSG_RESPONSE_UNKNOWNERROR,

	VEN_MSG_RESPONSE_INVALID = 0xff,
};
typedef u8 ven_msg_response_t;
#endif //#ifdef __SDK_API_01_SMS_MMS_CC__

typedef struct {
	u16				year;
	u8				month;
	u8				day;
	u8				hour;
	u8				min;
	u8				sec;
} ven_msg_timestamp_t; //the same as SMI_TimeStamp_t from mmi

typedef u16 ven_msg_id_t;
typedef u32 ven_msg_sms_handle_t;

typedef struct {
    ven_msg_timestamp_t timestamp; 
    ven_msg_id_t msgId;  
    ven_msg_box_t box; 
    ven_msg_readstatus_t readStatus;
    ven_msg_sendstatus_t sendStatus;
    u8 addr[20*2+1];	// Sender Address
} ven_msg_header_t; 

typedef struct
{
    u8 addr[20*2+1];	//SMI_MAX_ADDR_LEN*2+1
} ven_msg_phone_addr_t;

typedef struct
{
	ven_msg_timestamp_t timestamp; 
	ven_msg_box_t box;
	ven_msg_readstatus_t readStatus;
	ven_msg_sendstatus_t sendStatus;
	u16 msgContent[9*175+1];
	u8 phoneNum[20*2+1];		// Sender or Receiver Address
	ven_common_sim_id_t simId;
}ven_msg_sms_add_t;

typedef struct
{
    ven_msg_sms_handle_t hSms;
    ven_msg_ret_t retCode;
} ven_msg_sms_open_rsp_t;

typedef struct
{
    u8 nSentPage;
    ven_msg_sms_send_result_t result;
} ven_msg_send_sms_rsp_t;

typedef struct
{
    u16 *ptTelNo;
    u8 telNoLen;
    u16 *pData;                            ///< do type casting if type= VEN_MSG_DATA_BYTEDATA
    u16 dataLen;                           ///< equal to bytelen if type= VEN_MSG_DATA_BYTEDATA
    u32 timeStamp;                         ///< only for receive SMS. Time in seconds since 1979/01/01
    ven_common_sim_id_t simId;             ///< Sim ID
    ven_msg_sms_type_t smsType;            ///< encoding type
    ven_msg_save_sent_msg_t saveSentMsg;   ///< if save sent message in sent box, if port property is enabled, this will be ignored.
    ven_msg_msg_port_porp_t msgPortProp;   ///< if message with port property
    u16 port;                              ///< for port message
    ven_msg_data_t type;                   ///< for port message
    ven_msg_retry_sent_msg_t retrySendMsg; ///< if retry to send message when we fail to send the message
} ven_msg_sms_struct_t;

typedef struct
{
    u16 *pData;                      ///< Pointer to unicode string
    u16 dataLen;                     ///< Number of unicode characters
} ven_msg_cbs_struct_t;

typedef struct
{
    u32 userData;
    ven_msg_type_t msgType;
    union
    {
        u32 nSmsId;
        ven_msg_cbs_struct_t cbsMsg;
    } msgData;
} ven_msg_notify_t;

typedef struct
{
    u16 msgId;
    ven_msg_sms_struct_t* ptMsg;
    ven_msg_ret_t retCode;
} ven_msg_sms_received_rsp_t;

typedef struct
{
    u8 *pPhoneNum;                  ///< Phone number
    u8 len;                         ///< Length in bytes, without null terminate
} ven_msg_recipient_type_t;

typedef struct
{
    ven_msg_mms_object_t mmsObjType;
    u16 *pText;      ///< MMS text, used with VEN_MMS_OBJECT_TEXT
    u16 *pFilePath; ///< MMS embedded file path, used with VEN_MMS_OBJECT_IMAGE, VEN_MMS_OBJECT_AUDIO, VEN_MMS_OBJECT_VIDEO,
} ven_msg_editor_mms_content;

typedef struct
{
    ven_msg_type_t msgType;                         ///< VEN_MSG_SMS / VEN_MSG_MMS
    u8 numOfRecipients;                             ///< Number of recipients
    ven_msg_recipient_type_t *pRecipientList;       ///< List of recipients
    union
    {
        u16 *pSMSText;                              ///< SMS text, used with VEN_MSG_SMS
        ven_msg_editor_mms_content *pMMSContent;    ///< MMS content, used with VEN_MSG_MMS
    } content;
} ven_msg_editor_info_t;

typedef struct
{
	ven_msg_ret_t retCode;
} ven_msg_open_editor_rsp_t;

typedef struct
{
    ven_msg_type_t msgType;
} ven_msg_srv_ready_ind_t;

typedef struct
{
    ven_msg_type_t msgType;
    bool bReady;
} ven_msg_get_srv_ready_rsp_t;

typedef struct
{
    u8 addr[VEN_MSG_SMS_SERVICE_CENTER_MAX_CHAR];   ///< SMS service center number without NULL terminate
    u8 addrLen;                                     ///< Character length of SMS service center number
} ven_msg_sms_service_center_t;

#ifdef __SDK_API_01_SMS_MMS_CC__
typedef struct
{
	ven_msg_ret_t retCode;
	ven_common_sim_id_t simId;
	u16 total;
	u16 used;
	u16 maxPerMsg;
} ven_msg_get_sim_capacity_rsp_t;

typedef struct
{
	ven_msg_ret_t retCode;
	u32 num;
} ven_msg_sms_get_num_rsp_t;

typedef struct
{
	ven_msg_ret_t retCode;
	u32 num;
	ven_msg_header_t *pHdrList;
} ven_msg_sms_get_header_list_rsp_t;

typedef struct
{
	ven_msg_ret_t retCode;
	ven_msg_response_t responseStatus;
} ven_msg_mms_send_rsp_t;
#endif //#ifdef __SDK_API_01_SMS_MMS_CC__

typedef struct
{
	ven_msg_ret_t retCode;
	ven_msg_id_t msgId;
} ven_msg_sms_add_rsp_t;

/**
    This function is used in ven_msg_registerAllSMSMsg,
    3rd will filter sms msg by this function.
*/
typedef bool (*VEN_MSG_FILTER_FUNC)(ven_msg_header_t *pVenMsgHead, u32 MsgContent, u32 UserData);
/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/
#ifdef __SDK_API_01_SMS_MMS_CC__
/**
 *  ven_msg_mms_createHandle
 *
 *  @brief  This function will create a handle to prepare memory space for sending mms.
 *
 *  @param  venHandle  	[in]vendor handle.
 *  @param  phMms        	[out]pointer to the handle.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_mms_createHandle(u32 venHandle, ven_msg_mms_handle_t *phMms);

/**
 *  ven_msg_mms_setHeaderByParam
 *
 *  @brief  This function will help to set the parameters of the header.
 *
 *  @param  hMms  		[in]mms handle.
 *  @param  param        	[in]parameter type of the header.
 *  @param  value        		[in]the value to set if parameter is a value.
 *  @param  pStr        		[in]the string pointer to set if parameter is a string.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 *
 *  @note Please set 0 or NULL if value or pStr not used.
 */
ven_msg_ret_t ven_msg_mms_setHeaderByParam(ven_msg_mms_handle_t hMms, ven_msg_mms_header_param_t param, u32 value, u8 *pStr);

/**
 *  ven_msg_mms_setContent
 *
 *  @brief  This function will help to attach object with the mms.
 *
 *  @param  hMms  		[in]mms handle.
 *  @param  content        	[in]the object to attach with the mms.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_mms_setContent(ven_msg_mms_handle_t hMms, ven_msg_editor_mms_content content);

/**
 *  ven_msg_mms_send
 *
 *  @brief  This function will help to send mms under background without ui.
 *
 *  @param  hMms  		[in]mms handle.
 *  @param  simId  	[in]sim card.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 *
 *  @note support async only, if sync = TRUE, return  VEN_MSG_RET_BAD_PARAMETERS
 */
ven_msg_ret_t ven_msg_mms_send(ven_msg_mms_handle_t hMms, ven_common_sim_id_t simId, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_mms_releaseHandle
 *
 *  @brief  This function will release handle.
 *
 *  @param  hMms  		[in]mms handle.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_mms_releaseHandle(ven_msg_mms_handle_t hMms);
/**
 *  ven_msg_getSimCapacity
 *
 *  @brief  This function will help to get the capacity of sim card.
 *
 *  @param  simId  	[in]sim card.
 *  @param  pTotal        [out]pointer to the num of total PDUs of capacity.
 *  @param  pUsed        [out]pointer to the num of used PDUs currently.
 *  @param  pMaxPerMsg        [out]pointer to the max num of PDUs per message.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 *
 *  @note PDU is the unit of sim card capacity.
 */
ven_msg_ret_t ven_msg_getSimCapacity(ven_common_sim_id_t simId, u16 *pTotal, u16 *pUsed, u16 *pMaxPerMsg, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_getPhoneMaxNum
 *
 *  @brief  This function will help to get max num of messages by msg type.
 *
 *  @param  msgType  		[in]message type.
 *  @param  pNum		 	[out]pointer to the num of messagees with given msg type.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 *
 *  @note support sync only, if sync = FALSE, return  VEN_MSG_RET_BAD_PARAMETERS
 */
ven_msg_ret_t ven_msg_getPhoneMaxNum(ven_msg_type_t msgType, u16 *pNum, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_sms_getNum
 *
 *  @brief  This function will help to get the msg num of a given box or mutliple boxes.
 *
 *  @param  box  		[in]message box.
 *  @param  pNum        [out]pointer to the num of messagees in the given message box(es).
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_getNum(ven_msg_box_t box, u32 *pNum, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sms_getNumFromInbox
 *
 *  @brief  This function will help to get the msg num with given read status of a given inbox.
 *
 *  @param  inbox  		[in]message inbox.
 *  @param  readStatus  	[in]read or unread
 *  @param  pNum        		[out]pointer to the num of messagees in the given message box(es).
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_getNumFromInbox(ven_msg_box_t inbox, ven_msg_readstatus_t readStatus, u32 *pNum, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sms_getNumFromPhoneOutbox
 *
 *  @brief  This function will help to get the msg num with given send status of a given phone outbox(private or public or both).
 *
 *  @param  phOutbox  		[in]message phone outbox.
 *  @param  sendStatus  	[in]send status
 *  @param  pNum        		[out]pointer to the num of messagees in the given message box(es).
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_getNumFromPhoneOutbox(ven_msg_box_t phOutbox, ven_msg_sendstatus_t sendStatus, u32 *pNum, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sms_getHdrList
 *
 *  @brief  This function will help to get the msg num and headr list of a given box or mutliple boxes.
 *
 *  @param  box  		[in]message box.
 *  @param  pNum        [out]pointer to the num of messagees in the given message box(es).
 *  @param  ppHdrList   [out]pointer to the message header list in the given message box(es).
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_getHdrList(ven_msg_box_t box, u32 *pNum, ven_msg_header_t **ppHdrList, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sms_getHdrListFromInbox
 *
 *  @brief  This function will help to get the msg num and headr list with given read status of a given inbox.
 *
 *  @param  inbox  		[in]message inbox.
 *  @param  readStatus  	[in]read or unread
 *  @param  pNum        		[out]pointer to the num of messagees in the given message box(es).
 *  @param  ppHdrList   		[out]pointer to the message header list in the given message box(es).
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_getHdrListFromInbox(ven_msg_box_t inbox, ven_msg_readstatus_t readStatus, u32 *pNum, ven_msg_header_t **ppHdrList, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sms_getHdrListFromPhoneOutbox
 *
 *  @brief  This function will help to get the msg num and headr list with given send status of a given phone outbox(private or public or both).
 *
 *  @param  phOutbox  		[in]message phone outbox.
 *  @param  sendStatus  	[in]send status
 *  @param  pNum        		[out]pointer to the num of messagees in the given message box(es).
 *  @param  ppHdrList   		[out]pointer to the message header list in the given message box(es).
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_getHdrListFromPhoneOutbox(ven_msg_box_t phOutbox, ven_msg_sendstatus_t sendStatus, u32 *pNum, ven_msg_header_t **ppHdrList, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sms_setInboxReadStatus
 *
 *  @brief  This function will help to set the read status of a message in inbox.
 *
 *  @param  msgId  		[in]message ID.
 *  @param  inbox  		[in]message inbox.
 *  @param  readStatus  	[in]read or unread
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 *
 *  @note support sync only, if sync = FALSE, return  VEN_MSG_RET_BAD_PARAMETERS
 */
ven_msg_ret_t ven_msg_sms_setInboxReadStatus(ven_msg_id_t msgId, ven_msg_box_t inbox, ven_msg_readstatus_t readStatus, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sms_setPhoneOutboxSendStatus
 *
 *  @brief  This function will help to set the send status of a message in phone outbox.
 *
 *  @param  msgId  		[in]message ID.
 *  @param  phOutbox  		[in]message phone outbox.
 *  @param  readStatus  	[in]read or unread
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 *
 *  @note support sync only, if sync = FALSE, return  VEN_MSG_RET_BAD_PARAMETERS
 */
ven_msg_ret_t ven_msg_sms_setPhoneOutboxSendStatus(ven_msg_id_t msgId, ven_msg_box_t phOutbox, ven_msg_sendstatus_t sendStatus, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sms_moveBetweenPairPhoneBox
 *
 *  @brief  This function will help to move a message between phone boxes by pair(private <--> public).
 *
 *  @param  msgId  		[in]message ID.
 *  @param  srcPhBox  		[in]original message phone box.
 *  @param  dstPhBox  		[in]destination message phone box.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 *
 *  @note support sync only, if sync = FALSE, return  VEN_MSG_RET_BAD_PARAMETERS
 */
ven_msg_ret_t ven_msg_sms_moveBetweenPairPhoneBox(ven_msg_id_t msgId, ven_msg_box_t srcPhBox, ven_msg_box_t dstPhBox, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_delete
 *
 *  @brief  This function will help to delete a message by msgId and box.
 *
 *  @param  msgId  		[in]message ID.
 *  @param  srcPhBox  		[in]original message phone box.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_delete(ven_msg_id_t msgId, ven_msg_box_t srcBox, ven_req_data_t *ptVenReq);
#endif //#ifdef __SDK_API_01_SMS_MMS_CC__

ven_msg_ret_t ven_msg_sendSMS(u16 *ptTelNo, u8 telNoLen, u16 *ptData, u16 dataLen, ven_msg_sms_type_t smsType, ven_common_sim_id_t simId, ven_req_data_t* ptVenReq);
ven_msg_ret_t ven_msg_getSMSContentPageNumber(ven_msg_sms_type_t reqSmsType, u16* ptSmsContent, u16 nSmsContentLen, ven_msg_sms_type_t* ptOutSmsType, u8* ptOutSmsPageCount);

/**
 *  ven_msg_registerAllSMSMsg
 *
 *  @brief  This function will help to register all msg with a given message type.
 *          This function only support sync mode!
 *
 *  @param  venHandle       [in]Vendor handle.
 *  @param  pMsgFilterFunc  [in]Msg filter function
 *  @param  ptVenReq        [in]Vendor req data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_registerAllSMSMsg(s32 venHandle, VEN_MSG_FILTER_FUNC pMsgFilterFunc, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_registerPort
 *
 *  @brief  This function will help to register the user interested port with a given message type.
 *
 *  @param  venHandle   [in]Vendor handle.
 *  @param  type        [in]Message type.
 *  @param  port        [in]Port to register.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_registerPort(s32 venHandle, ven_msg_type_t type, u16 port, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_deregisterPort
 *
 *  @brief  This function will help to deregister the uninterested port with a given message type.
 *
 *  @param  venHandle       [in]Vendor handle.
 *  @param  type            [in]Message type.
 *  @param  port             [in]Port to deregister.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_deregisterPort(s32 venHandle, ven_msg_type_t type, u16 port);

/**
 *  ven_msg_deregisterAllPort
 *
 *  @brief  This function will help to deregister all uninterested ports with a given message type.
 *
 *  @param  venHandle       [in]Vendor handle.
 *  @param  type            [in]Message type.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_deregisterAllPort(s32 venHandle, ven_msg_type_t type);

/**
 *  ven_msg_registerTelNo
 *
 *  @brief  This function will help to register the user interested telno with a given message type.
 *
 *  @param  venHandle   [in]Vendor handle.
 *  @param  type        [in]Message type.
 *  @param  port        [in]Port to register.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_registerTelNo(s32 venHandle, ven_msg_type_t type, u16 *ptTelNo, u8 telNoLen, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_deregisterTelNo
 *
 *  @brief  This function will help to deregister the uninterested telno with a given message type.
 *
 *  @param  venHandle       [in]Vendor handle.
 *  @param  type            [in]Message type.
 *  @param  port             [in]Port to deregister.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_deregisterTelNo(s32 venHandle, ven_msg_type_t type, u16 *ptTelNo, u8 telNoLen);

/**
 *  ven_msg_deregisterAllTelNo
 *
 *  @brief  This function will help to deregister all uninterested telnos with a given message type.
 *
 *  @param  venHandle       [in]Vendor handle.
 *  @param  type            [in]Message type.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_deregisterAllTelNo(s32 venHandle, ven_msg_type_t type);

ven_msg_ret_t ven_msg_keepTelNoMsg(s32 venHandle, u16 msgId, u8 keepMsg, ven_msg_type_t type);

/**
 *  ven_msg_sendSMSEx
 *
 *  @brief  This function will help to send SMS with the data you want.
 *
 *  @param  ptMsg       [in]The pointer of input message.
 *  @param  ptVenReq    [in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sendSMSEx(ven_msg_sms_struct_t *ptMsg, ven_req_data_t *ptVenReq);
/**
 *  ven_msg_sendSMSEx2
 *
 *  @brief  This function will help to send SMS with the data you want and sender Port .
 *
 *  @param  ptMsg           [in]The pointer of input message.
 *  @param  nSenderPort  [in]The sender port.
 *  @param  ptVenReq      [in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */

ven_msg_ret_t ven_msg_sendSMSWithSenderPort(ven_msg_sms_struct_t *ptMsg, u16 nSenderPort, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_getSMSContentPageNumberEx
 *
 *  @brief  This function will help to count SMS page size.
 *
 *  @param  ptMsg           [in]The pointer of input message.
 *  @param  pSmsPageCount   [out]SMS page count.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_getSMSContentPageNumberEx(ven_msg_sms_struct_t *ptMsg, u8 *pSmsPageCount);

/**
 *  ven_msg_getReceivedSMS
 *
 *  @brief  This function will help to get the received SMS with the given message id.
 *
 *  @param  msgId           [in]The pointer of input message.
 *  @param  ptMsg           [out]Pointer to the message.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_getReceivedSMS(u16 msgId, ven_msg_sms_struct_t *ptMsg, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_openEditor
 *
 *  @brief  This function will help to open MMS/SMS editor
 *
 *  @param  pEditorInfo     [in]The pointer of editor information.
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_openEditor(ven_msg_editor_info_t *pEditorInfo, ven_req_data_t* ptVenReq);

/**
 *  ven_msg_registerSrvReadyInd
 *
 *  @brief  This function allows user to register a call back for srv ready indication
 *
 *  @param  venHandle       [in]Vendor handle
 *  @param  type            [in]Message Type
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_registerSrvReadyInd(s32 venHandle, ven_msg_type_t type, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_deregisterSrvReadyInd
 *
 *  @brief  This function allows user to deregister a call back for srv ready indication
 *
 *  @param  venHandle       [in]Vendor handle
 *  @param  type            [in]Message Type
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_deregisterSrvReadyInd(s32 venHandle, ven_msg_type_t type);

/**
 *  ven_msg_getSrvReadyInd
 *
 *  @brief  This function allows user to get srv ready indication synchronously or asynchronously
 *
 *  @param  venHandle       [in]Vendor handle
 *  @param  type            [in]Message Type
 *  @param  pReady         [out]Pointer to result in bool (u8)
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_getSrvReadyInd(s32 venHandle, ven_msg_type_t type, bool *pReady, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_querySMSServiceCenter
 *
 *  @brief  This function will help to query SMS service center
 *
 *  @param  simId           [in]SIM id
 *  @param  pSmsSrvCenter   [out]The number and length of SMS service center
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_querySMSServiceCenter(ven_common_sim_id_t simId, ven_msg_sms_service_center_t *pSmsSrvCenter, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_setSMSServiceCenter
 *
 *  @brief  This function will help to set SMS service center
 *
 *  @param  simId           [in]SIM id
 *  @param  pSmsSrvCenter   [out]The number and length of SMS service center
 *  @param  ptVenReq        [in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_setSMSServiceCenter(ven_common_sim_id_t simId, ven_msg_sms_service_center_t smsSrvCenter, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_sms_open
 *
 *  @brief  This function will help to open a sms and get a handle for other operations.
 *
 *  @param  msgId           	[in]msg id
 *  @param  box   			[in]msg box
 *  @param  phSms        	[out]the pointer to handle for sync, please fill with NULL for async.
 *  @param  ptVenReq        	[in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_open(u16 msgId, ven_msg_box_t box, ven_msg_sms_handle_t *phSms, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_sms_backup
 *
 *  @brief  This function will help to open a sms and get a handle for other operations.
 *
 *  @param  hSms           	[in] sms handle
 *  @param  ppData   		[out] the pointer to the pointer to the complete sms raw data for backup.
 *  @param  pLength        	[out] the pointer to length of the complete sms raw data.
 *  @note 	Please copy the complete sms raw data from *ppData to save, don't modify the content and don't free *ppData.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_backup(ven_msg_sms_handle_t hSms, u8 **ppData, u16 *pLength);

/**
 *  ven_msg_sms_close
 *
 *  @brief  This function will help to close sms handle.
 *
 *  @param  hSms           	[in] sms handle
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_close(ven_msg_sms_handle_t hSms);

/**
 *  ven_msg_sms_restore
 *
 *  @brief  This function will help to restore a sms by the complete sms raw data from ven_msg_sms_backup.
 *
 *  @param  pData   		[in] the pointer to the complete sms raw data from ven_msg_sms_backup.
 *  @param  length        	[in] the length of the complete sms raw data.
 *  @param  ptVenReq        	[in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_restore(u8 *pData, u16 length, ven_req_data_t *ptVenReq);

/**
 *  ven_msg_sms_add
 *
 *  @brief  This function will help to add a sms made by self into boxes.
 *
 *  @param  pSmsMsg   	[in] the pointer to the sms data.
 *  @param  pMsgId        	[out] the pointer to the msgId, only useful in sync mode.
 *  @param  ptVenReq        	[in]Request data.
 *
 *  @retval VEN_MSG_RET_SUCCESS if success
 *          VEN_MSG_RET_ERROR if failed
 *          VEN_MSG_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_msg_ret_t ven_msg_sms_add(ven_msg_sms_add_t *pSmsMsg, ven_msg_id_t *pMsgId, ven_req_data_t *ptVenReq);


#endif //__VEN_MSG_H_
