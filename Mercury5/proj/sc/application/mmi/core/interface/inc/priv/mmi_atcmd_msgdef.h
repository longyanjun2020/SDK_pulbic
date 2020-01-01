/**
* @file mmi_atcmd_msgdef.h
*
*
* @version $Id: mmi_atcmd_msgdef.h 38442 2009-08-24 09:24:24Z steve.lee $
*
*/
#ifndef __MMI_ATCMD_MSGDEF_HJ__
#define __MMI_ATCMD_MSGDEF_HJ__

#include "vm_types.ht"

typedef struct
{
	u32 type;
	void *pData;
}mmi_AtCmdWtest_t;

typedef struct 
{
	union
	{
		mmi_AtCmdWtest_t tWtest;
	}tData;
} mmi_AtCmdIndMsgBody_t;

#endif /*__MMI_ATCMD_MSGDEF_HJ__*/
