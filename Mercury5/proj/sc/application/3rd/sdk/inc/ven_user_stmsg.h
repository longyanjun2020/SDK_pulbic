/**
 *
 * @file    ven_user_stmsg.h
 * @brief   This file defines the structures for the user extend message
 * @author  Christine.tai
 * @version $Id: ven_user_stmsg.h 15633 2008-10-28 03:55:31Z steve.lee $
 *
 */

#ifndef __VEN_USER_STMSG_H__
#define __VEN_USER_STMSG_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_user.h"
#include "ven_comdef_priv.h"

/****************************************************************************/
/*  Message :       I_VEN_USER_EXTEND_OUT_MSG/I_VEN_USER_EXTEND_IN_MSG            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vender, Vender to MMI           */
/*                                                                          */
/*  Scope     : gethostbyname                                               */
/*                                                                          */
/*  Structure : iVen_user_extend_msg_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

typedef struct
{
    iVen_App_ID VenAppId;
    void *pData;
    u32 u32DataLen;
} iVen_user_extend_msg_t;
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif //__VEN_USER_STMSG_H__

