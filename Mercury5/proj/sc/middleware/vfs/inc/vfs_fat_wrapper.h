/**
 *
 * @file    vfs_fat_wrapper.h
 *
 * @brief
 *
 * @author  YF Lin
 * @version $Id: vfs_fat_parser.c 15206 2011-04-25 06:52:18Z yf.lin $
 *
 */
 
#include "cus_msg.hc"
#include "vfs_struct.h"

#ifndef __SDK_SIMULATION__
#include "mdl_efat_pub.h"
#endif

int fat_register_notify (VFS_NotifyType_e notifyType, VFS_NotifyCb_t* pNotifyCb);
void fat_unregister_notify (VFS_NotifyType_e notifyType);


