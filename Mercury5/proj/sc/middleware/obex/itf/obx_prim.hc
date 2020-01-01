/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 2001
*/



/***************************************************************************/
/*  File       : obx_prim.hc												            */
/*-------------------------------------------------------------------------*/
/*  Object     : OBEX stack Interface : define messages offsets used in    */
/*				     RTK message exchanges							          		   */
/*                                                                         */
/*  Change     :                                                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/*   Date   | Author    | Modification                                     */
/*----------+-----------+--------------------------------------------------*/
/***************************************************************************/





#ifndef __OBX_PRIM_HC__
#define __OBX_PRIM_HC__

#include "msgofs.hc"

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "obx_message_define__.hi"
};

#endif /* __OBX_PRIM_HC__*/
