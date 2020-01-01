/**
* @file mmi_cb_bt.h
*
*
* @version $Id: 
*
*/
#ifndef __MMI_CB_BT_H__
#define __MMI_CB_BT_H__

#include "MediaTaskClientMgrItf.h"
#include "drv_bt_api.h"

static boolean bA2DPUnblockMsgHandled = TRUE;

#ifdef _MSIM_
void mmi_sim_cb_set_BTSRVPTR(void * ptr);
void mmi_sim_cb_set_BTOBEXSRVPTR(void * ptr);
#endif

#ifdef __BLUETOOTH_OBEX_MMI__
void mmi_bt_ObexTransStatus_cb(u32 u32CurBytes, u32 u32TotalBytes);
void mmi_bt_ObexWrite_cb(u32 u32WriteSize, void *FileBuff, u32 FileSize);
#endif

#ifdef __BLUETOOTH_A2DP_MMI__
/* Setter & Getter for shared variable between MMI & BT Tasks */
boolean _mmi_bt_isUnblockMsgHandled(void);
void _mmi_bt_setUnblockMsgHandled(boolean bIsHandled);

boolean mmi_bt_a2dp_MMIUIUpdate_cb(BT_A2dpUIUpdateInfo_t* pInfo);
void mmi_bt_a2dp_StatusChanged_cb(BtStatus_e eStatus, u32 uNotifyInfo);
#endif//__BLUETOOTH_A2DP_MMI__



#endif /* __MMI_CB_BT_H__ */
