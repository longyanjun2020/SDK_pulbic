#ifndef __MMI_EMAILSRV_H__
#define __MMI_EMAILSRV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"
#include "mmi_base_util.h"

#include "nccemail.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EMAILSRV_STATUS_IDLE = 0,

    EMAILSRV_STATUS_CONNECTING,

    EMAILSRV_STATUS_SENDING,
    EMAILSRV_STATUS_SEND_FINISH,    // sent all email message to email server
    EMAILSRV_STATUS_SEND_FAILED, // there are email message send failed

    EMAILSRV_STATUS_RECEIVING,
    EMAILSRV_STATUS_RECEIVE_FINISH, // received all email message from email server
    EMAILSRV_STATUS_RECEIVE_FAILED, // there are some email message can not be received from email server

    EMAILSRV_STATUS_FINISHED
} EMAILSRV_Status;

typedef enum {
    EMAILSRV_State_Idle = 0,
    EMAILSRV_State_Initializing,    // load email setting information or email account info
    EMAILSRV_State_Getting_Network_Profile,
    EMAILSRV_State_Creating_Datalink,
    EMAILSRV_State_Sending,
    EMAILSRV_State_Receiving
} EMAILSRV_State;

typedef enum {
    EMAILSRV_Err_Ok = 0,
    EMAILSRV_Err_Pending,
    EMAILSRV_Err_Failed, // for any unknown reason
    EMAILSRV_Err_InboxFull,
    EMAILSRV_Err_SentboxFull,
    EMAILSRV_Err_UserCancel,
    EMAILSRV_Err_UsbConnected,
    EMAILSRV_Err_DiskFull,
    EMAILSRV_Err_InvalidConfig,
    EMAILSRV_Err_OutOfMemory,
} EMAILSRV_ErrCode;

typedef enum {
    EMAILSRV_ReqType_None = 0x00,
    EMAILSRV_ReqType_SendAll = 0x01,
    EMAILSRV_ReqType_Receive = 0x02,
    EMAILSRV_ReqType_SendOne = 0x04,
    EMAILSRV_ReqType_Cancel = 0x08,
} EMAILSRV_ReqType;

typedef struct _EMAILSRV_AccountStatusInfo_t {
    u32 accountID;    // the email account info

    u32 sentItems;
    u32 totalSendTask;

    u32 receivedItems;
    u32 totalReceiveTask;

    EMAILSRV_Status status;
    EMAILSRV_ErrCode errCode;

    u32 reqType;
} EMAILSRV_AccountStatusInfo_t;

typedef enum {
    EMAILSRV_Notify_Mask_ProgressChangeInd = 0x000001,
    EMAILSRV_Notify_Mask_OpenEmailAccountInd = 0x000002,
    EMAILSRV_Notify_Mask_ReadAccountListInd = 0x000004,
    EMAILSRV_Notify_Mask_ReadAccountCFGInd = 0x000008,
    EMAILSRV_Notify_Mask_ReadSettingInd = 0x000010,
    EMAILSRV_Notify_Mask_ReadEmailInd = 0x000020,
    EMAILSRV_Notify_Mask_ReadEmailListInd = 0x000040,
    EMAILSRV_Notify_Mask_WriteEmailCfgInd = 0x000080,
    EMAILSRV_Notify_Mask_WriteInfoInd = 0x000100,
    EMAILSRV_Notify_Mask_WriteSettingInd = 0x000200,
    EMAILSRV_Notify_Mask_DeleteAccountInd = 0x000400,
    EMAILSRV_Notify_Mask_SaveEmailInd = 0x000800,
    EMAILSRV_Notify_Mask_DeleteEmailInd = 0x001000,
    EMAILSRV_Notify_Mask_UpdateEmailListInd = 0x002000,
    EMAILSRV_Notify_Mask_SendInd = 0x004000,
    EMAILSRV_Notify_Mask_ReceiveInd = 0x008000,
} EMAILSRV_NOTIFY_MASK_TAG;


#ifdef __NAND__
#define EMAIL_SDCARD_DIR    L"fs:/NAND"
#else
#define EMAIL_SDCARD_DIR    L"fs:/CARD"
#endif

/**
 * External Events
 */
#define EMAILSRV_EVT_ProgressChange             (CLSID_EMAILSRV << 16 | 1)
#define EMAILSRV_EVT_DataLinkClosed             (CLSID_EMAILSRV << 16 | 2)
#define EMAILSRV_EVT_OpenEmailAccount           (CLSID_EMAILSRV << 16 | 3)
#define EMAILSRV_EVT_ReadEmailAccountList       (CLSID_EMAILSRV << 16 | 4)
#define EMAILSRV_EVT_ReadEmailAccountCfg        (CLSID_EMAILSRV << 16 | 6)
#define EMAILSRV_EVT_WriteEmailAccountCfg       (CLSID_EMAILSRV << 16 | 7)
#define EMAILSRV_EVT_WriteEmailAccountInfo      (CLSID_EMAILSRV << 16 | 8)
#define EMAILSRV_EVT_ReadEmailSetting           (CLSID_EMAILSRV << 16 | 9)
#define EMAILSRV_EVT_WriteEmailSetting          (CLSID_EMAILSRV << 16 | 10)
#define EMAILSRV_EVT_DeleteEmailAccount         (CLSID_EMAILSRV << 16 | 11)
#define EMAILSRV_EVT_OpenEmail                  (CLSID_EMAILSRV << 16 | 12)
#define EMAILSRV_EVT_SaveEmail                  (CLSID_EMAILSRV << 16 | 13)
#define EMAILSRV_EVT_SortEmailHeaderList        (CLSID_EMAILSRV << 16 | 14)
#define EMAILSRV_EVT_DeleteEmail                (CLSID_EMAILSRV << 16 | 15)
#define EMAILSRV_EVT_UpdateEmailList            (CLSID_EMAILSRV << 16 | 16)
#define EMAILSRV_EVT_SendingStartInd            (CLSID_EMAILSRV << 16 | 17)
#define EMAILSRV_EVT_ReceivingStartInd          (CLSID_EMAILSRV << 16 | 18)
#define EMAILSRV_EVT_SendingDoneInd             (CLSID_EMAILSRV << 16 | 19)
#define EMAILSRV_EVT_ReceivingDoneInd           (CLSID_EMAILSRV << 16 | 20)


#define INHERIT_IEMAILSRV(IName) \
    INHERIT_IHandler(IName);    \
    MAE_Ret (*RegisterNotification)             (IName *, void* pInstance, EMAILSRV_NOTIFY_MASK_TAG mask);    \
    MAE_Ret (*DeRegisterNotification)           (IName *, void* pInstance, EMAILSRV_NOTIFY_MASK_TAG mask);    \
    MAE_Ret (*GetAccountStatus)                 (IName *, u32 accountID, EMAILSRV_AccountStatusInfo_t *pStatus);    \
    MAE_Ret (*SendAll)                          (IName *, u32 emailAccount);    \
    MAE_Ret (*SendOne)                          (IName *, u32 emailAccount, u32 emailID);    \
    MAE_Ret (*ReceiveAll)                       (IName *, u32 emailAccount);    \
    MAE_Ret (*CancelSendReceive)                (IName *, u32 emailAccount);    \
    MAE_Ret (*ReadEmailAccountList)             (IName *); \
    MAE_Ret (*ReadEmailAccountCfg)              (IName *, u32 emailAccount); \
    MAE_Ret (*WriteEmailAccountCfg)             (IName *, u32 emailAccount, T_EMAIL_Account_Config *ppEmailAccountCfg); \
    MAE_Ret (*WriteEmailAccountInfo)            (IName *, boolean NewAccount, u32 emailAccount, T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList, T_EMAIL_Account_Config *pEmailAccountCfg); \
    MAE_Ret (*ReadEmailSetting)                 (IName *); \
    MAE_Ret (*WriteEmailSetting)                (IName *,  T_EMAIL_Account_Setting  *pEmailSetting); \
    MAE_Ret (*DeleteEmailAccount)               (IName *, u32 emailAccount, T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList); \
    MAE_Ret (*OpenEmailAccount)                 (IName *, u32 emailAccount); \
    MAE_Ret (*CloseEmailAccount)                (IName *, u32 emailAccount); \
    MAE_Ret (*GetInboxItemsCount)               (IName *, u32 *pUnreadItems, u32 *pSendingItems, u32 *pTotalItems); \
    MAE_Ret (*GetDraftboxItemsCount)            (IName *, u32 *pUnreadItems, u32 *pSendingItems, u32 *pTotalItems); \
    MAE_Ret (*GetOutboxItemsCount)              (IName *, u32 *pUnreadItems, u32 *pSendingItems, u32 *pTotalItems); \
    MAE_Ret (*GetSentboxItemsCount)             (IName *, u32 *pUnreadItems, u32 *pSendingItems, u32 *pTotalItems); \
    MAE_Ret (*GetInboxHeaderList)               (IName *, VectorClass_t **ppVector);\
    MAE_Ret (*GetDraftboxHeaderList)            (IName *, VectorClass_t **ppVector);\
    MAE_Ret (*GetOutboxHeaderList)              (IName *, VectorClass_t **ppVector);\
    MAE_Ret (*GetSentboxHeaderList)             (IName *, VectorClass_t **ppVector);\
    MAE_Ret (*OpenEmail)                        (IName *, u32 boxID, u32 msgID, u32 isOnlyHeader); \
    MAE_Ret (*SaveEmail)                        (IName *, u32 emailAccountID, u32 boxID, u32 msgID, boolean isNew, u8 *pBuf, u32 bufLen); \
    MAE_Ret (*SortEmailHeaderList)              (IName *, u32 boxId, u32 sortBy);\
    MAE_Ret (*DeleteEmail)                      (IName *, u32 *emailList, u32 emailNum, u32 boxId);\
    MAE_Ret (*MarkEmailAsRead)                  (IName *, u32 boxID, u32 emailID, u8 isRead)\

DEFINE_INTERFACE(IEMAILSRV);


/**
 * Function APIs
 */
MAE_Ret EmailSrvNew(MAE_ClsId id, void **ppObj);

#define IEMAILSRV_QueryInterface(pICntlr, id, pp, po)               GET_FUNCTBL((pICntlr), IEMAILSRV)->QueryInterface(pICntlr, id, pp, po)

#define IEMAILSRV_HandleEvent(pICntlr, e, p1, p2)                   GET_FUNCTBL((pICntlr), IEMAILSRV)->HandleEvent(pICntlr, e, p1, p2)

/**
 This function is used for registering a notify mask.
 */
#define IEMAILSRV_RegisterNotification(pICntlr, p1, p2)             GET_FUNCTBL((pICntlr), IEMAILSRV)->RegisterNotification( pICntlr, p1, p2)

/**
 This function is used for de-registering a notify mask for alarm.
 */
#define IEMAILSRV_DeRegisterNotification(pICntlr, p1, p2)           GET_FUNCTBL((pICntlr), IEMAILSRV)->DeRegisterNotification( pICntlr, p1, p2)

#define IEMAILSRV_GetAccountStatus(pICntlr, accountID, pStatus)     GET_FUNCTBL((pICntlr), IEMAILSRV)->GetAccountStatus(pICntlr, accountID, pStatus)

/**
 * This function is used to request sending specified emails
 */
#define IEMAILSRV_SendAll(pICntlr, p1)                              GET_FUNCTBL((pICntlr), IEMAILSRV)->SendAll(pICntlr, p1)

#define IEMAILSRV_SendOne(pICntlr, p1, p2)                          GET_FUNCTBL((pICntlr), IEMAILSRV)->SendOne(pICntlr, p1, p2)

#define IEMAILSRV_ReceiveAll(pICntlr, p1)                           GET_FUNCTBL((pICntlr), IEMAILSRV)->ReceiveAll(pICntlr, p1)

#define IEMAILSRV_CancelSendReceive(pICntlr, p1)                    GET_FUNCTBL((pICntlr), IEMAILSRV)->CancelSendReceive(pICntlr, p1)

#define IEMAILSRV_ReadEmailAccountList(pICntlr)                     GET_FUNCTBL((pICntlr), IEMAILSRV)->ReadEmailAccountList(pICntlr)

#define IEMAILSRV_ReadEmailAccountCfg(pICntlr, p1)                  GET_FUNCTBL((pICntlr), IEMAILSRV)->ReadEmailAccountCfg(pICntlr, p1)

#define IEMAILSRV_WriteEmailAccountCfg(pICntlr, p1, p2)             GET_FUNCTBL((pICntlr), IEMAILSRV)->WriteEmailAccountCfg(pICntlr, p1, p2)

#define IEMAILSRV_WriteEmailAccountInfo(pICntlr, p1, p2, p3, p4)    GET_FUNCTBL((pICntlr), IEMAILSRV)->WriteEmailAccountInfo(pICntlr, p1, p2, p3, p4)

#define IEMAILSRV_ReadEmailSetting(pICntlr)                         GET_FUNCTBL((pICntlr), IEMAILSRV)->ReadEmailSetting(pICntlr)

#define IEMAILSRV_WriteEmailSetting(pICntlr, p1)                    GET_FUNCTBL((pICntlr), IEMAILSRV)->WriteEmailSetting(pICntlr, p1)

#define IEMAILSRV_DeleteEmailAccount(pICntlr, p1, p2)               GET_FUNCTBL((pICntlr), IEMAILSRV)->DeleteEmailAccount(pICntlr, p1, p2)

#define IEMAILSRV_OpenEmailAccount(pICntlr, p1)                     GET_FUNCTBL((pICntlr), IEMAILSRV)->OpenEmailAccount(pICntlr, p1)

#define IEMAILSRV_CloseEmailAccount(pICntlr, p1)                    GET_FUNCTBL((pICntlr), IEMAILSRV)->CloseEmailAccount(pICntlr, p1)

#define IEMAILSRV_GetInboxItemsCount(pICntlr, p1, p2, p3)           GET_FUNCTBL((pICntlr), IEMAILSRV)->GetInboxItemsCount(pICntlr, p1, p2, p3)

#define IEMAILSRV_GetDraftboxItemsCount(pICntlr, p1, p2, p3)        GET_FUNCTBL((pICntlr), IEMAILSRV)->GetDraftboxItemsCount(pICntlr, p1, p2, p3)

#define IEMAILSRV_GetOutboxItemsCount(pICntlr, p1, p2, p3)          GET_FUNCTBL((pICntlr), IEMAILSRV)->GetOutboxItemsCount(pICntlr, p1, p2, p3)

#define IEMAILSRV_GetSentboxItemsCount(pICntlr, p1, p2, p3)         GET_FUNCTBL((pICntlr), IEMAILSRV)->GetSentboxItemsCount(pICntlr, p1, p2, p3)

#define IEMAILSRV_GetInBoxHeaderList(pICntlr, p1)                    GET_FUNCTBL((pICntlr), IEMAILSRV)->GetInboxHeaderList(pICntlr, p1)

#define IEMAILSRV_GetDraftBoxHeaderList(pICntlr, p1)                GET_FUNCTBL((pICntlr), IEMAILSRV)->GetDraftboxHeaderList(pICntlr, p1)

#define IEMAILSRV_GetOutBoxHeaderList(pICntlr, p1)                    GET_FUNCTBL((pICntlr), IEMAILSRV)->GetOutboxHeaderList(pICntlr, p1)

#define IEMAILSRV_GetSentBoxHeaderList(pICntlr, p1)                    GET_FUNCTBL((pICntlr), IEMAILSRV)->GetSentboxHeaderList(pICntlr, p1)

#define IEMAILSRV_OpenEmail(pICntlr, p1, p2, p3)                        GET_FUNCTBL((pICntlr), IEMAILSRV)->OpenEmail(pICntlr, p1, p2, p3)

#define IEMAILSRV_SaveEmail(pICntlr, p1, p2, p3, p4, p5, p6)        GET_FUNCTBL((pICntlr), IEMAILSRV)->SaveEmail(pICntlr, p1, p2, p3, p4, p5, p6)

#define IEMAILSRV_SortEmailHeaderList(pICntlr, p1, p2)              GET_FUNCTBL((pICntlr), IEMAILSRV)->SortEmailHeaderList(pICntlr, p1, p2)

#define IEMAILSRV_DeleteEmail(pICntlr, p1, p2, p3)                  GET_FUNCTBL((pICntlr), IEMAILSRV)->DeleteEmail(pICntlr, p1, p2, p3)

#define IEMAILSRV_MarkEmailAsRead(pICntlr, p1, p2, p3)              GET_FUNCTBL((pICntlr), IEMAILSRV)->MarkEmailAsRead(pICntlr, p1, p2, p3)



#ifdef __cplusplus
}
#endif


#endif

