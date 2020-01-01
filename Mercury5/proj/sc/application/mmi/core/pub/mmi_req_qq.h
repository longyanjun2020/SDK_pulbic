#ifndef __MMI_REQ_QQ_H__
#define __MMI_REQ_QQ_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "mmi_qqsrv.h"
/**
 * Send message to ask  QQ task to init QQ client
 *
 * \param nActiveSimId [in]
 *      The selected SIM card's ID
 *
 * \param bHasCard [in]
 *      If the SD card has been inserted
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_qq_InitQQClientReq(u8 nActiveSimId, boolean bHasCard);

/**
 * Save QQ Config into Local File System
 */
s32 mmi_qq_UpdateQQConfigReq(boolean bHasCard, QQSrvQQConfig_t *pQQConfig);

/**
 * Send message to QQ task to destroy QQ client
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_qq_DestroyQQClientReq(void);

/**
 * Change Group Message Settings For Special Account
 *
 * \param bBlockGroupMsg [in]
 *      If block all group messages
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_qq_SetGroupMsgSettingsReq(u32 accountID, boolean bBlockGroupMsg);

/**
 * login qq.
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_qq_LoginReq(u32 accountID, u8 *pPswStr, boolean bRecvGroupMsg, boolean bHideLogin);

/**
 * load QQ config File
 *
 * \param pVerifyStr [in]
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_qq_VerifyReq(u32 accountID, u8 *pVerifyStr, QQSrvVerifyType_e type);

/**
 * qq logout
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_qq_LogoutReq(u32 accountID);

s32 mmi_qq_SendMsgReq(u32 accountID, u32 type, u32 receiverID, u8 *pMsg);

s32 mmi_qq_ChangeStatusReq(u32 accountID, QQSrvQQStatus_e newStatus);

s32 mmi_qq_DelBuddyByIdReq(u32 accountID, u32 buddyID, u8 isBlock);

s32 mmi_qq_AddBuddyByIdReq(u32 accountID, u32 buddyID, u8 *pReqStr);

s32 mmi_qq_AddBuddyReply(u32 accountID, u32 buddyID, boolean isAccept);

s32 mmi_qq_GetBuddyInfoReq(u32 accountID, u32 type, u32 id);

#ifdef __cplusplus
}
#endif

#endif //__MMI_REQ_QQ_H__
