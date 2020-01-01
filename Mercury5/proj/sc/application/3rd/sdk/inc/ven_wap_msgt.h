#ifndef __VEN_WAP_MSGT_H__
#define __VEN_WAP_MSGT_H__

#include "ven_wap.h"
#include "ven_msg.h"
#include "ven_comdef_priv.h"
//@@~~ this might define in other common.h


/****************************************************************************/
/*  Message :       I_VEN_WAP_OPEN_BROWSER_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to launch a   */
/*              pbb browser for user to phone numbers(s) or email(s)        */
/*                                                                          */
/*  Structure : iVen_wap_open_browser_req_t                                       */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16* pURL;
    u16  nURLLen;
    ven_wap_download_storage_t eStorage;
    ven_wap_browser_mode_t eMode;
    ven_wap_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    u8 SimID;         //the SIM ID used to create datalink in browser (possible values are SIM_ONE, SIM_TWO, NO_SIM_SELECT)
    VEN_CB_FUNC_PTR pfnCb;  //for calling back while calling wap dowloading or browser status
} iVen_wap_open_browser_req_t;

/****************************************************************************/
/*  Message :       I_VEN_WAP_OPEN_BROWSER_RSP                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              user select phone numbers(s) or email(s)                    */
/*                                                                          */
/*  Structure : iVen_wap_open_browser_rsp_t                                       */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_wap_ret_t retCode;
} iVen_wap_open_browser_rsp_t;



#endif //__VEN_WAP_MSGT_H__

