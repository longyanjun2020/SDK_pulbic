/**
 *
 * @file    ven_clipboard_stmsg.h
 * @brief   This file defines the structures for the clipboard module message
 * @author  Jorena.Ku
 * @version $Id: ven_clipboard_stmsg.h 15797 2008-11-02 14:35:33Z jorena.lee $
 *
 */

#ifndef __VEN_CLIPBOARD_STMSG_H__
#define __VEN_CLIPBOARD_STMSG_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_clipboard.h"


/****************************************************************************/
/*  Message :       I_VEN_CLIPBOARD_GET_SETTING_REQ                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : Get the clipboard setting                                   */
/*                                                                          */
/*  Structure : iVen_clipboard_getSetting_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_clipboard_ret_t *pRetCode;      //output
    ven_clipboard_setting_t *pSet;      //output
} iVen_clipboard_getSetting_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CLIPBOARD_COPY_TEXT_REQ                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : Copy the text into the clipboard                            */
/*                                                                          */
/*  Structure : iVen_clipboard_copyText_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u16 *pStr;
    u32 nStrLen;
    ven_clipboard_ret_t *pRetCode;      //output
} iVen_clipboard_copyText_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CLIPBOARD_GET_COPY_TEXT_REQ                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : Get the copied string from the clipboard                    */
/*                                                                          */
/*  Structure : iVen_clipboard_getCopyText_req_t                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_clipboard_ret_t *pRetCode;  //output
    u16 **ppStr;                    //output
    u32 *pnStrLen;                  //output
} iVen_clipboard_getCopyText_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_clipboard_ret_t *pRetCode;  //output
	bool* pHasCopyText;
} iVen_clipboard_hasCopyText_req_t;


#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif //__VEN_CLIPBOARD_STMSG_H__

