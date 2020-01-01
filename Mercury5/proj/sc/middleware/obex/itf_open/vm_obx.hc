/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 2001
*/



/***************************************************************************/
/*  File       : vm_obx.hc								         		            */
/*-------------------------------------------------------------------------*/
/*  Object     : OBEX Open stack Interface : define messages offsets used  */
/*				     in RTK message exchanges				   	          		   */
/*                                                                         */
/*  Change     :                                                           */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/*   Date   | Author    | Modification                                     */
/*----------+-----------+--------------------------------------------------*/
/***************************************************************************/







#ifndef __VM_OBX_HC__
#define __VM_OBX_HC__

#include "vm_msgof.hc"


/*Messages exchanged between OBEX and  MMI (CUS) */



#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "vm_obx_message_define__.hi"
};


#endif /* __VM_OBX_HC__*/
