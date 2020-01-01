/**
 *  @file   mmi_common_sms_util.h
 *  @brief  it is used for communination within different Applications in sms utility functions.
 *
 * @version $Id: mmi_common_sms_util.h 40987 2009-09-22 03:06:47Z sata.yeh $
 * @author	joe.hsu
 */
#ifndef MMI_COMMON_SMS_UTIL_H
#define MMI_COMMON_SMS_UTIL_H

#include "mmi_common_sms_master.h"
#include "mmi_mae_view.h"

MAE_Ret MessageGetDetailView(SMI_MsgID_t MsgID, SMI_MsgLocation_e location,SMI_MsgHdr_t **pMsgHeader, HWIN hWin, McaDetailViewWdgList_t *pWdgList, MAE_WChar *pDetail, IBase * pOwner);

MAE_Ret MessageUpdateDetailViewTitle(McaDetailViewWdgList_t *pWdgList, MAE_WChar *pDetail, IBase *pOwner, boolean bMultiNumber);

#ifdef __MMI_SMS_CHAT__
MAE_WChar *MessageGetChatRoomNumber( void );
void MessageSetChatRoomNumber( MAE_WChar *pChatRoomNumber );
#endif /* __MMI_SMS_CHAT__ */

#endif /* MMI_COMMON_SMS_UTIL_H */

