/**
 *
 * @file    ven_time_msgt.h
 * @brief   This file defines the MMI time related request vendor API and
 *          MMI response API
 *
 * @author  Code.Lin
 * @version $Id: ven_time_msgt.h 40108 2009-09-12 12:04:25Z code.lin $
 *
 */

#ifndef __VEN_TIME_MSGT_H__
#define __VEN_TIME_MSGT_H__

#include "ven_time.h"

/****************************************************************************/
/*  Message :       I_VEN_TIME_SET_TIME_ZONE_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to set        */
/*              timezone                                                    */
/*                                                                          */
/*  Structure : iVen_time_set_timezone_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u32 ven_time_zone_id;
    ven_time_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_time_set_timezone_req_t;

/****************************************************************************/
/*  Message :       I_VEN_TIME_SET_TIME_ZONE_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_time_set_timezone_rsp_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_time_ret_t RetCode;
    u32 ven_time_zone_id;
} iVen_time_set_timezone_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_TIME_SET_TIME_REQ                                 */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to set time   */
/*                                                                          */
/*  Structure : iVen_time_set_time_req_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_time_format_t localTime;
    ven_time_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_time_set_time_req_t;

/****************************************************************************/
/*  Message :       I_VEN_TIME_SET_TIME_RSP                                 */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to set time   */
/*                                                                          */
/*  Structure : iVen_time_set_time_rsp_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_time_ret_t RetCode;
} iVen_time_set_time_rsp_t;

#endif //__VEN_TIME_MSGT_H__
