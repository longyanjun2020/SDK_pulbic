/**
*  @file:   mmiextmsg.h
*
*  @revision: $Id$
*
*  @brief:
*           define Msgs sent from Other task to MMI Ext task 
*/
#ifndef __MMIEXTMSG_H__
#define __MMIEXTMSG_H__

#include "vm_msgof.hc"

//******************************************************************************
//	C O N S T A N T S  A N D  E N U M S
//******************************************************************************

/**
* VM_CUS3_BASE OS message (number of enum should be less than 256)
*/
enum
{
	MMI_MMIEXTMSG_CONTENTDB								= VM_CUS3_BASE,
	MMI_MMIEXTMSG_CONTENTDB_SYNC_REQ					= MMI_MMIEXTMSG_CONTENTDB,
	MMI_MMIEXTMSG_CONTENTDB_SYNC_ABORT_REQ
};


#endif//__MMIEXTMSG_H__

