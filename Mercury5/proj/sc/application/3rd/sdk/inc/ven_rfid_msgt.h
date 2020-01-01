/**
 * @file ven_rfid_msgt.h
 *
 * This file defines the MMI image and media related request vendor API and
 * MMI response API
 *
 * @version $Id: ven_rfid_msgt.h  $
 *
 */

#ifndef __VEN_RFID_MSGT_H__
#define __VEN_RFID_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_rfid.h"
#include "ven_comdef_priv.h"

#ifdef __RFID_SDK_SUPPORT__

//#include "ema_parse.ht"
//#include "ema_prim.hc"


/****************************************************************************/
/*  Message :       I_VEN_RFID_CMD_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Rfid to caller task (Vendor task)                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              Rfid cmd response                                               */
/*                                                                          */
/*  Structure : iVen_rfid_cmd_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_rfid_ret_e retCode;

    ven_RFID_Info_t *pRFIDInfo;

} iVen_rfid_cmd_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_RFID_LISTENER_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Rfid to caller task (Vendor task)                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              Rfid cmd response                                               */
/*                                                                          */
/*  Structure : iVen_rfid_listener_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
//typedef iVen_rfid_cmd_rsp_t iVen_rfid_listener_rsp_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    //ven_rfid_ret_e retCode;

    ven_RFID_Info_t *pRFIDInfo;

} iVen_rfid_listener_rsp_t;


/****************************************************************************/
/*  Message :       RFID_API_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : caller task (Vendor task)  to Rfid                                       */
/*                                                                          */
/*  Scope     : The structure of the message with the parameter of Rfid cmd */
/*                                                        */
/*                                                                          */
/*  Structure : iVen_rfid_cmd_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

// TODO: Refine code Here , Wait ResMgr Interface  Ready

//typedef ema_RfidCmdReq_t iVen_rfid_cmd_req_t;
//{
//	ema_RfidCmdReq_t	RfidReq;
//} iVen_rfid_cmd_rsp_t;


#endif //__RFID_SDK_SUPPORT__
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__
#endif //__VEN_CODEC_MSGT_H__
