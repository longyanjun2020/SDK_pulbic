/**
 *
 * @file    ven_editor_stmsg.h
 * @brief   This file defines the structures for the editor related message
 * @author  Alison.Chen
 * @version $Id: ven_editor_msgt.h 44566 2009-10-30 14:47:24Z code.lin $
 *
 */

#ifndef __VEN_EDITOR_MSGT_H__
#define __VEN_EDITOR_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_editor.h"
#include "ven_comdef_priv.h"

/****************************************************************************/
/*  Message :       I_VEN_EDITOR_EDIT_REQ                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : Launch a editor to get user's input.                        */
/*                                                                          */
/*  Structure : iVen_editor_edit_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16 *ptTitle;
    u8 titleLen;
    ven_editor_type_t type;
    ven_editor_style_t style;
    ven_editor_encoding_t encoding;
    u16 maxContentLen;
    u16 *ptInitContent;
    u16 initContentLen;
    u16 *pFormatStr;
    u8 formatStrLen;
    ven_editor_result_t *ptOutResult;
    u16 **pptOutContent;
    u16 *ptOutContentLen;
} iVen_editor_edit_req_t;

typedef struct
{
	iVen_AsyncReq_BodyBase_t ReqBase;
	bool bDate;			
	u16 year;           ///< Year value after 1900, value range is 1900~2038
	u8  month;          ///< Month, value range is 1~12
	u8  day;            ///< Day, value range is 1~31
	u8  hour;           ///< Hour, value range is 0~23
	u8  minute;         ///< Minute, value range is 0~59
	u8  second;         ///< Second, value range is 0~59
} iVen_editor_datetime_req_t;
/****************************************************************************/
/*  Message :       I_VEN_EDITOR_EDIT_RSP                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_editor_edit_rsp_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_editor_result_t rspType;
    u16 *ptContent;
    u16 contentLen;
} iVen_editor_edit_rsp_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	ven_editor_ret_t *pRetCode;    ///< Sync only, command return code
} iVen_editor_close_req_t;

typedef struct
{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_editor_result_t rspType;
	bool bDate;			
	u16 year;           ///< Year value after 1900, value range is 1900~2038
	u8  month;          ///< Month, value range is 1~12
	u8  day;            ///< Day, value range is 1~31
	u8  hour;           ///< Hour, value range is 0~23
	u8  minute;         ///< Minute, value range is 0~59
	u8  second;         ///< Second, value range is 0~59
} iVen_editor_datetime_rsp_t;
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__
#endif //__VEN_EDITOR_MSGT_H__

