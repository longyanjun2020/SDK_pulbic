#ifndef __VEN_MSG_MSGT_H__
#define __VEN_MSG_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_msg.h"
#include "ven_comdef_priv.h"

#ifdef __SDK_API_01_SMS_MMS_CC__
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_common_sim_id_t 	simId;
	u8                      *pFrom;
	u8                      *pTo;
	u8                      *pCc;
	u8                      *pBcc;
	u8                      *pSubject;
	u8    					messageClass;
	u32                     expiry;
	u32                     deliveryTime;
	u8 						priority;
	bool                 	senderVisibility;
	bool                 	deliveryReport;
	bool                 	readReply;
    u32						contentNum;
    ven_msg_editor_mms_content *pContentArray;
} iVen_msg_mms_send_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_ret_t retCode;
	ven_msg_response_t responseStatus;
} iVen_msg_mms_send_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_common_sim_id_t simId;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    u16 *pTotal;    //output: only useful if the ReqBase.bSync is TRUE
    u16 *pUsed;    //output: only useful if the ReqBase.bSync is TRUE
    u16 *pMaxPerMsg;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_get_sim_capacity_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	ven_common_sim_id_t simId;
    ven_msg_ret_t retCode;
    u16 total;
	u16 used;
	u16 maxPerMsg;
} iVen_msg_get_sim_capacity_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_msg_box_t box;
	ven_msg_readstatus_t readStatus;
	ven_msg_sendstatus_t sendStatus;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    u32 *pNum;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_sms_get_num_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_ret_t retCode;
    u32 num;
} iVen_msg_sms_get_num_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_msg_box_t box;
	ven_msg_readstatus_t readStatus;
	ven_msg_sendstatus_t sendStatus;
    ven_msg_ret_t *pRetCode;		//output: only useful if the ReqBase.bSync is TRUE
    u32 *pNum;						//output: only useful if the ReqBase.bSync is TRUE
    ven_msg_header_t **ppHdrList;	//output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_sms_get_header_list_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_ret_t retCode;
	u32 num; 
	ven_msg_header_t *pHdrList;
} iVen_msg_sms_get_header_list_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_msg_id_t msgId;
	ven_msg_box_t srcBox;
	u8 modifyType;
	ven_msg_header_t msgHdr;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_sms_modify_header_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_msg_id_t msgId;
	ven_msg_box_t srcBox;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_delete_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_ret_t retCode;
} iVen_msg_delete_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_msg_type_t msgType;
	u16* pNum;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_get_phone_max_num_req_t;
#endif //#ifdef __SDK_API_01_SMS_MMS_CC__

typedef struct
{
	ven_msg_header_t msgHdr;
	u16 *pMsgCnt;
	ven_msg_sms_type_t encoding;
	u16 receiverNum;
	ven_msg_phone_addr_t *pReceiverList;
	u32 CRCValue;
	u32 Size;
	u16 reference; 	// 16 bit reference to cross check with Message part
	u8 IMSI[10];	//MMI_MMS_FS_MAX_IMSI_LEN
	u8 type; 		// SMI_MsgType_e, Message type for this message
	u8 msgFlag;
	u8 SimModule; 	// record the sim card for sent
	u8 SmsSimMsgBox;
	u8 IsWapVCardMessage; //check if it is VCard message
}iVen_msg_sms_backup_info_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_msg_id_t msgId;
	ven_msg_box_t box;
	iVen_msg_sms_backup_info_t* pBackupInfo; ////output: only useful if the ReqBase.bSync is TRUE
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_sms_backup_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_ret_t retCode;
	iVen_msg_sms_backup_info_t backupInfo;
} iVen_msg_sms_backup_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	iVen_msg_sms_backup_info_t* pRestoreInfo;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_sms_restore_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_ret_t retCode;
} iVen_msg_sms_restore_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_msg_timestamp_t timestamp; 
	ven_msg_box_t box;
	ven_msg_readstatus_t readStatus;
	ven_msg_sendstatus_t sendStatus;
	u16 *pMsgContent;
	u8 *pPhoneNum;		// Sender or Receiver Address
	ven_common_sim_id_t simId;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_msg_id_t *pMsgId;	//output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_sms_add_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_ret_t retCode;
	ven_msg_id_t msgId;
} iVen_msg_sms_add_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_SEND_SMS_REQ                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              send a sms.                                                 */
/*  Structure : iVen_msg_send_sms_req_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16* ptTelNo;
    u8 telNoLen;
    u16* ptData;
    u16 dataLen;
    ven_msg_sms_type_t smsType;
    ven_common_sim_id_t simId;
    ven_msg_save_sent_msg_t saveSentMsg;
    ven_msg_retry_sent_msg_t retrySendMsg;
    u8 bExt;  //0 for default
    struct
    {
        u16            desport;
        u16            senderport; 
        ven_msg_data_t dataType;
    } ext;

} iVen_msg_send_sms_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_SEND_SMS_RSP                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              sending sms.                                                */
/*                                                                          */
/*  Structure : iVen_msg_send_sms_rsp_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u8 nSentPage;
    ven_msg_sms_send_result_t result;
} iVen_msg_send_sms_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_REGISTER_PORT_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              register a port message.                                    */
/*  Structure : iVen_msg_register_port_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    u16 port;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE

    void* pCBFunc;
    u32   UserData;

} iVen_msg_register_port_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_DEREGISTER_PORT_REQ                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              deregister the uninterested port with a given message type. */
/*  Structure : iVen_msg_deregister_port_req_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    u16 port;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_deregister_port_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_DEREGISTER_ALL_PORT_REQ                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              deregister all uninterested ports with a given message type.*/
/*  Structure : iVen_msg_deregister_all_port_req_t                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;

    void *pMsgFilterFunc;
    void *pCBFunc;  //for callback
    u32 UserData;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_register_all_sms_msg_req_t;


/****************************************************************************/
/*  Message :       I_VEN_MSG_DEREGISTER_ALL_PORT_REQ                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              deregister all uninterested ports with a given message type.*/
/*  Structure : iVen_msg_deregister_all_port_req_t                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_deregister_all_port_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_REGISTER_TELNO_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              register a telno message.                                   */
/*  Structure : iVen_msg_register_telno_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    u16 *ptTelNo;
    u8 telNoLen;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE

    void* pCBFunc;
    u32   UserData;

} iVen_msg_register_telno_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_DEREGISTER_TELNO_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              deregister the uninterested telno with a given message type. */
/*  Structure : iVen_msg_deregister_telno_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    u16 *ptTelNo;
    u8 telNoLen;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_deregister_telno_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_DEREGISTER_ALL_TELNO_REQ                      */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              deregister all uninterested telnos with a given message type.*/
/*  Structure : iVen_msg_deregister_all_telno_req_t                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_deregister_all_telno_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_KEEP_TELNO_MSG_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              keep or delete a telno message by msgId.                    */
/*  Structure : iVen_msg_keep_telno_msg_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    u16 msgId;
    u8 keepMsg;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_keep_telno_msg_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_GET_RECEIVED_SMS_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              get the received SMS with the given message id.             */
/*  Structure : iVen_msg_get_received_sms_req_t                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16 msgId;
    ven_msg_sms_struct_t *ptMsg;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_get_received_sms_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_GET_RECEIVED_SMS_RSP                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              sending sms.                                                */
/*                                                                          */
/*  Structure : iVen_msg_send_sms_rsp_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u16 msgId;
    ven_msg_sms_struct_t *ptMsg;
    ven_msg_ret_t retCode;
} iVen_msg_get_received_sms_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_INCOMING_MSG_IND                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the incoming port message.*/
/*                                                                          */
/*  Structure : iVen_msg_incoming_msg_ind_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_notify_t msgNotify;
} iVen_msg_incoming_msg_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_OPEN_EDITOR_REQ                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              get the received SMS with the given message id.             */
/*  Structure : iVen_msg_open_editor_req_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_editor_info_t *pEditorInfo;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_open_editor_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_OPEN_EDITOR_RSP                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              sending sms.                                                */
/*                                                                          */
/*  Structure : iVen_msg_open_editor_rsp_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_ret_t retCode;
} iVen_msg_open_editor_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_REGISTER_SRV_READY_REQ                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              register for SMS service status message.                    */
/*  Structure : iVen_msg_register_srv_ready_req_t                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    void* pCBFunc;
    u32   UserData;

} iVen_msg_register_srv_ready_req_t;


/****************************************************************************/
/*  Message :       I_VEN_MSG_DEREGISTER_SRV_READY_REQ                      */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              deregister the SMS service status                           */
/*  Structure : iVen_msg_deregister_srv_ready_req_t                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_deregister_srv_ready_req_t;


/****************************************************************************/
/*  Message :       I_VEN_MSG_SRV_READY_IND                                 */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the incoming port message.*/
/*                                                                          */
/*  Structure : iVen_msg_srv_ready_ind_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_type_t type;
} iVen_msg_srv_ready_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_GET_SRV_READY_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of get service ready request                  */
/*                                                                          */
/*  Structure : iVen_msg_get_srv_ready_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_msg_type_t type;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    bool *pReady;
} iVen_msg_get_srv_ready_req_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_GET_SRV_READY_RSP                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of get service ready response                 */
/*                                                                          */
/*  Structure : iVen_msg_get_srv_ready_rsp_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_msg_type_t type;
    ven_msg_ret_t nRetCode; //output: only useful if the ReqBase.bSync is TRUE
    bool bReady;
} iVen_msg_get_srv_ready_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_MSG_QUERY_SMS_SRV_CENTER_REQ                      */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              query SMS service center with the SIM id.                   */
/*  Structure : iVen_msg_query_sms_srv_center_req_t                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_common_sim_id_t simId;
    ven_msg_sms_service_center_t *pSMSSrvCenter; //output: only useful if the ReqBase.bSync is TRUE
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_query_sms_srv_center_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_common_sim_id_t simId;
    ven_msg_sms_service_center_t smsSrvCenter;
    ven_msg_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_msg_set_sms_srv_center_req_t;
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif //__VEN_MSG_MSGT_H__
