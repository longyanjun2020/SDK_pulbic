/**
* @file mmi_bt_msgdef.h
*
*
* @version $Id: 
*
*/
#ifndef __MMI_BT_MSGDEF_H__
#define __MMI_BT_MSGDEF_H__
#include "MediaTaskClientMgrItf.h"

typedef struct 
{
	u32		u32CurTransBytes;
	u32		u32TotalBytes;
} BT_TransStatusInd_t ;

typedef struct 
{
	u32 u32WriteSize;
	void *FileBuff;
	u32 FileSize;
} BT_FileWriteInd_t ;

#ifdef __BLUETOOTH_A2DP_MMI__
typedef struct 
{
    BtStatus_e eStatus;
    u32 uNotifyInfo;
} BT_StatusChangedInd_t ;

typedef struct 
{
    u32 uTimeout;
} BT_UnblockBTInd_t ;

#endif /* __BLUETOOTH_A2DP_MMI__ */

#endif /* __MMI_BT_MSGDEF_H__ */
