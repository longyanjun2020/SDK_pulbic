/**
 * @file    mmi_if_vfs.h
 * @brief   The file handles the VFS messages to IFStream interface
 * @author  kenny.wu@mstarsemi.com
 *
 * @version $Id $
 */

#ifndef __MMI_IF_VFS_H__
#define __MMI_IF_VFS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

void mmi_vfs_msg_parser(IBase *pRecipient, struct vm_msg *pData);
void mmi_vfs_resmgr_notify_if(u32 uCusData, void *pNotifyInfo);

#endif /* __MMI_IF_VFS_H__ */
