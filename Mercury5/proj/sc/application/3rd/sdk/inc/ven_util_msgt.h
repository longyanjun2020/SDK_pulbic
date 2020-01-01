/**
 *
 * @file    ven_setting_stmsg.h
 * @brief   This file defines the structures for the setting module message
 * @author  randy.Wu
 * @version $Id: ven_util_msgt.h 36962 2010-11-24 13:59:22Z randy.wu $
 *
 */

#ifndef __VEN_UTIL_MSGT_H__
#define __VEN_UTIL_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__ 

#include "ven_util.h"
#include "ven_comdef_priv.h"


/****************************************************************************/
/*  Message :       I_VEN_UTIL_GET_CELLINFO_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_util_get_cellinfo_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_util_get_cell_info_t *pCellInfoReq;
    ven_util_CellInfoRsp_t *pCellInfoData;
    ven_util_ret_t *pRetCode;            //output: only useful if the ReqBase.bSync is TRUE
} iVen_util_get_cellinfo_req_t;


/****************************************************************************/
/*  Message :       I_VEN_UTIL_GET_CELLINFO_RSP                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   :  MMI to Vendor task                                         */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_util_get_cellinfo_rsp_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_util_ret_t *pRetCode;    //output: only useful if the ReqBase.bSync is TRUE
} iVen_util_get_cellinfo_rsp_t;

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__
#endif //__VEN_UTIL_MSGT_H__

