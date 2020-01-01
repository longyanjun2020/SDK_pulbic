/**
 * @file    mmi_cb_sys.h
 * @brief   The file handles the system messages
 * @author  kenny.wu@mstarsemi.com
 * 
 * @version $Id: mmi_cb_sys.h 29728 2009-04-30 13:15:48Z kenny.wu $
 */
 
 
#ifndef __MMI_CB_SYS_H__
#define __MMI_CB_SYS_H__
#include "esl_sys_itf.h"

void mmi_sys_EMA_Notify_cb(u16 senderID, u32 userValue, esl_SysNotifyInfo_t *pSysNotifyInfo);

#endif /* __MMI_CB_SYS_H__ */
