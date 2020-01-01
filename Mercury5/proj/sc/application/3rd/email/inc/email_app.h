#ifndef __MS_EMAIL_H__
#define __MS_EMAIL_H__

#include "nccemail.h"
#include "mmi_base_util.h"
#include "mmi_emailsrv.h"
#include "cus_msg.hc"

#include "ven_setting.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "email_message_define__.hi"
};
#define EMAIL_TRANS_MGR_TIMER_INTERVAL    100    // milliseconds
//#define EMAIL_WATCHDOG_TIMER_INTERVAL     2000 // milliseconds

#define EMAIL_MAX_FILENAME_LEN  265

#ifdef __NAND__
#define EMAIL_ROOT_FULL_PATH    "/NAND/.system/EMail"
#define EMAIL_WAP_BROWSER_PATH  "/NAND/.system/WapExplorer/Browser/"
#else
#define EMAIL_ROOT_FULL_PATH    "/CARD/.system/EMail"
#define EMAIL_WAP_BROWSER_PATH  "/NOR0/.system/WapExplorer/Browser/"
#endif

#define EMAIL_WAP_BROWSER_PATH_TCARD "/CARD/.system/WapExplorer/Browser/"


typedef struct {
    u32 totalItems;
    u32 unreadItems;
    u32 sortBy;

    VectorClass_t *pEmailHeaderList;    // T_EMAIL_FS_HEADER NOTE: don't care next pointer
} MMI_EMAIL_MailboxInfo;

typedef struct {
    u32 accountID;

    MMI_EMAIL_MailboxInfo inboxInfo;
    MMI_EMAIL_MailboxInfo draftboxInfo;
    MMI_EMAIL_MailboxInfo outboxInfo;
    MMI_EMAIL_MailboxInfo sentboxInfo;
} MMI_EMAIL_EmailAccountInfo;

typedef struct {
    u32 accountID;
} MMI_EMAIL_OpenEmailAccount_Req;

typedef struct {
    u32 accountID;
} MMI_EMAIL_CloseEmailAccount_Req;

typedef struct {
    u32 accountID;
}MMI_EMAIL_ReadEmailAccountCfg_Req;

typedef struct {
    u32 accountID;
    T_EMAIL_Account_Config *pEmailAccountCfg;
}MMI_EMAIL_WriteEmailAccountCfg_Req;

typedef struct {
    u32 NewAccount;
    u32 accountID;
    T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList;
    T_EMAIL_Account_Config *pEmailAccountCfg;
}MMI_EMAIL_WriteEmailAccountInfo_Req;

typedef struct {
    T_EMAIL_Account_Setting *pEmailSetting;
}MMI_EMAIL_WriteEmailSetting_Req;

typedef struct {
    u32 accountID;
    T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList;
}MMI_EMAIL_DeleteEmailAccount_Req;

typedef struct {
    u32 accountID;
    u32 boxID;
    u32 msgID;
    u32 isOnlyHeader;
} MMI_EMAIL_OpenEmail_Req;

typedef struct {
    u32 accountID;
    u32 boxID;
    u32 msgID;

    u8 *pEmailBuf;
    u32 bufLen;

    boolean isNew;
} MMI_EMAIL_SaveEmail_Req;

typedef struct {
    MMI_EMAIL_EmailAccountInfo *pEmailAccountInfo;

    u32 status; // TRUE or FALSE
} MMI_EMAIL_OpenEmailAccount_Cnf;

typedef struct {
    u32 accountID;
    u32 boxId;
    u32 sortBy;
}MMI_EMAIL_SortEmailHeaderList_Req;

typedef struct {
    u32 accountID;
    u32 *emailList;
    u32 emailNum;
    u32 boxId;
}MMI_EMAIL_DeleteEmail_Req ;

typedef struct {
    u32 accountID;
    u32 boxID;
    u32 emailID;
    u8  isRead;
}MMI_EMAIL_MarkEmailAsRead_Req;

typedef struct
{
    u32 accountID;
    u32 emailID; // for reqType is EMAILSRV_ReqType_SendOne

    EMAILSRV_ReqType reqType;
} MMI_EMAIL_SendReceive_Req;

typedef struct {
    T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList;
    u32 status; // MAE_RET_FAILED or MAE_RET_SUCCESS
}MMI_EMAIL_GetEmailAccountList_Cnf;

typedef struct {
    T_EMAIL_Account_Config *pEmailAccountCfg;
    u32 status; // MAE_RET_FAILED or MAE_RET_SUCCESS
}MMI_EMAIL_ReadEmailAccountCfg_Cnf;

typedef struct {
    u32 status; // MAE_RET_FAILED or MAE_RET_SUCCESS
}MMI_EMAIL_WriteEmailAccountCfg_Cnf;

typedef struct {
    u32 status; // MAE_RET_FAILED or MAE_RET_SUCCESS
}MMI_EMAIL_WriteEmailAccountInfo_Cnf;

typedef struct {
    T_EMAIL_Account_Setting *pEmailSetting;
    u32 status; // MAE_RET_FAILED or MAE_RET_SUCCESS
}MMI_EMAIL_ReadEmailSetting_Cnf;

typedef struct {
    u32 status; // MAE_RET_FAILED or MAE_RET_SUCCESS
}MMI_EMAIL_WriteEmailSetting_Cnf;

typedef struct {
    u32 status; // MAE_RET_FAILED or MAE_RET_SUCCESS
}MMI_EMAIL_DeleteEmailAccount_Cnf;

typedef struct {
    u32 status;    // MAE_RET_FAILED or MAE_RET_SUCCESS

    u32 accountID;
    u32 boxID;
    u32 msgID;

    EMAIL_HANDLE emailHandle;
} MMI_EMAIL_OpenEmail_Cnf;

typedef struct {
    u32 status;

    MMI_EMAIL_MailboxInfo inboxInfo;
    MMI_EMAIL_MailboxInfo draftboxInfo;
    MMI_EMAIL_MailboxInfo outboxInfo;
    MMI_EMAIL_MailboxInfo sentboxInfo;
} MMI_EMAIL_SaveEmail_Cnf;

typedef struct
{
    u32 boxID;
    u32 status;

    MMI_EMAIL_MailboxInfo boxInfo;
}MMI_EMAIL_SortEmailHeaderList_Cnf;

typedef struct
{
    u32 status;
    u32 boxID;

    MMI_EMAIL_MailboxInfo boxInfo;
}MMI_EMAIL_DeleteEmail_Cnf;

typedef struct
{
    u32 status;
    u32 boxID;
    u32 emailID;
    u32 newStatus;
}MMI_EMAIL_MarkEmailAsRead_Cnf;

typedef struct
{
    EMAILSRV_AccountStatusInfo_t *pAccountStatus;

    MMI_EMAIL_EmailAccountInfo *pBoxInfo;
} MMI_EMAIL_AccountStatusChange_Cnf;

typedef enum
{
    EMAIL_SORT_BY_DATE,
    EMAIL_SORT_BY_SUBJECT,
    EMAIL_SORT_BY_SENDER,
}EmailSortType_t;

typedef struct _EmailTransMgr_t
{
    VectorClass_t *pSendTaskQueue; // used to save EmailTransMgrTaskItemInfo list

    u32 curOpenedEmailAccountID;
    u32 curEmailAccountID;
    u32 totalSendItems;
    u32 sentItems;    // field to save how many items have been sent to email server in current session
    u32 totalReceiveItems;
    u32 receivedItems;
    u32 curMsgID;

    ESMTP_HANDLE esmtpSession;
    POP3_HANDLE pop3Session;

    T_EMAIL_Account_Config *pEmailAccountConfig;
    T_EMAIL_Account_Setting *pEmailSetting;

    u32 reqType;

    // network begin ....
    ven_setting_network_profile_t *pEmailNetworkProfile;
#ifdef __WLAN_MMI__
    ven_setting_network_connectset_t connSet;
#endif
    ven_common_sim_id_t simID;
    // network end .....

    EMAILSRV_State state;
    EMAILSRV_ErrCode errCode;
    u32     sortBy;
    boolean isDataLinkReady; // Flag to check whether or not data link has been initialized
    boolean receivingTask;
    boolean sendingTask;
    boolean isUserCancelled;
} EmailTransMgr_t;

typedef struct _EMAILSRV_WorkItemInfo {
    u32 msgID;
} EmailTransMgrTaskItemInfo;

void EmailApp_FreeEmailHeaderItem(void *pItemData, void *pUseData);

//void EMAIL_CallBack(void *pMessage);

#ifdef __cplusplus
}
#endif

#endif //__MS_EMAIL_H__
