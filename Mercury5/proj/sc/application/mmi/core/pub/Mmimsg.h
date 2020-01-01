/**
*  @file:   Mmimsg.h
*
*  @revision: $Id: Mmimsg.h 39944 2009-09-10 18:01:37Z sho.ding $
*
*  @brief:
*           define Msgs sent from MMI to MMI
*/
#ifndef __MMIMSG_H__
#define __MMIMSG_H__

#include "vm_msgof.hc"
#include "cus_msg.hc"

//******************************************************************************
//	C O N S T A N T S  A N D  E N U M S
//******************************************************************************

/**
* VM_CUS3_BASE OS message (number of enum should be less than 256)
*/
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "mmi_message_define__.hi"
};


#endif//__MMIMSG_H__

