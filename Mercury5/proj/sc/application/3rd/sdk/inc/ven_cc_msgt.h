#ifndef __VEN_CC_MSGT_H__
#define __VEN_CC_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_cc.h"
#include "ven_comdef_priv.h"

/****************************************************************************/
/*  Message :       I_VEN_CC_MAKE_CALL_REQ                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to make call. */
/*                                                                          */
/*  Structure : iVen_cc_make_call_req_t                                     */
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
    ven_common_sim_id_t simId;
} iVen_cc_make_call_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CC_MAKE_CALL_RSP                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              making a call.                                              */
/*                                                                          */
/*  Structure : iVen_cc_make_call_rsp_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	ven_cc_ret_t retCode;
} iVen_cc_make_call_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CC_MAKE_CALL_GET_CALL_ID_RSP                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              making a call.                                              */
/*                                                                          */
/*  Structure : iVen_cc_make_call_get_call_id_rsp_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
#ifdef __SDK_API_01_SMS_MMS_CC__
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	ven_cc_ret_t retCode;
	s32 state;
	s32 callID;
} iVen_cc_make_call_get_call_id_rsp_t;
#endif


/****************************************************************************/
/*  Message :       I_VEN_CC_RELEASE_CALL_REQ                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to hang up call. */
/*                                                                          */
/*  Structure : iVen_cc_release_call_req_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
#ifdef __SDK_API_01_SMS_MMS_CC__
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	s32 callID;
	u32 *pResult;	// output param, the address of return code, should be set by mmi/vendorApp/vendorSrv
} iVen_cc_release_call_req_t;
#endif

/****************************************************************************/
/*  Message :       I_VEN_CC_CALL_STATUS_RSP                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting call status.                                        */
/*                                                                          */
/*  Structure : iVen_cc_get_call_status_rsp_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_cc_ret_t RetCode;

} iVen_cc_get_call_status_rsp_t;



/****************************************************************************/
/*  Message :       I_VEN_CC_GET_CALL_STATUS_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting call status.                                        */
/*                                                                          */
/*  Structure : iVen_cc_get_call_status_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    iVen_cc_call_status_t *pCallStatus;
    ven_cc_ret_t *pRetCode;    
} iVen_cc_get_call_status_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	void *pCallFilter;
	void *pCallHandler;
	u32 usrData;
    ven_cc_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_cc_register_incoming_call_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	u8 *pCallNumber;
	u32 callID;
	u8 indType;
} iVen_cc_register_incoming_call_ind_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	void *pCallLogListener;
	u32 usrData;
    ven_cc_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_cc_register_add_call_log_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
	ven_cc_calllog_t *pCallLog;
} iVen_cc_register_call_log_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_CC_SEND_DTMF_REQ                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting call status.                                        */
/*                                                                          */
/*  Structure : iVen_cc_send_DTMF_req_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_cc_ret_t *pRetCode;
    u8 u8KeyCode;
    u8 u8Duration;
    u8 u8OperationMode;
} iVen_cc_send_DTMF_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CC_SEND_DTMF_RSP                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting call status.                                        */
/*                                                                          */
/*  Structure : iVen_cc_send_DTMF_rsp_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_cc_ret_t RetCode;
} iVen_cc_send_DTMF_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CC_ABORT_DTMF_REQ                                  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting call status.                                        */
/*                                                                          */
/*  Structure : iVen_cc_send_DTMF_req_t                                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_cc_ret_t *pRetCode;
} iVen_cc_abort_DTMF_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CC_ENABLE_DL_VOICE_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting call status.                                        */
/*                                                                          */
/*  Structure : iVen_cc_enable_DL_voice_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_cc_ret_t *pRetCode;
    bool bEnable;
} iVen_cc_enable_DL_voice_req_t;

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif //__VEN_CC_MSGT_H__

