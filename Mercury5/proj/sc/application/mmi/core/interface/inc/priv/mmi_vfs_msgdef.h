/**
* @file mmi_vfs_msgdef.h
*
*
* @version $Id: mmi_vfs_msgdef.h 15190 2008-10-16 03:22:39Z christine.tai $
*
*/

#ifndef __MMI_VFS_MSGDEF_H__
#define __MMI_VFS_MSGDEF_H__

#include "vm_types.ht"
#include "mdl_vfs_fat.ho"

typedef struct 
{
	s32 retCode;
	u32         userData;
	VFS_NotifyInfo_t *pNotifyInfo;
} mmi_VfsMsgBody_t;
#endif /* __MMI_VFS_MSGDEF_H__ */

