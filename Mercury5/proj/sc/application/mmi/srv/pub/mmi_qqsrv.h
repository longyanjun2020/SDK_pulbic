#ifndef __MMI_QQSRV_H__
#define __MMI_QQSRV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"
#include "mmi_base_util.h"
#include "Filemgr_fstream.h"


#ifdef __cplusplus
extern "C" {
#endif

#define QQSRV_MAX_MESSAGE_LENGTH        1024   //
#define QQSRV_NICKNAME_LEN              64     //12
#define QQSRV_SESSION_KEY_LEN           20
#define QQSRV_HISTORY_MSG_NUM           10
#define QQSRV_MESSAGE_HEADER_LENGTH  128
#define QQSRV_CHAT_HISTORY_FILE_SIZE    50*1024 //50K
#define QQSRV_CHAT_LOG_DIR              L"fs:/CARD/.system/QQ/user/"

#ifndef QQ_NO_BUDDY_DETAIL_INFO
#define QQSRV_SIGNATURE_LEN             256
#define QQSRV_EMAIL_ACCOUNT_LEN         64
#define QQSRV_ALIAS_LEN                 32
#define QQSRV_POST_CODE_LEN             32
#define QQSRV_ADDRESS_LEN               64
#define QQSRV_HOME_PHONE_LEN            32
#define QQSRV_MOBILE_PHONE_LEN          32
#define QQSRV_EMAIL_LEN                 32
#define QQSRV_OCCUPATION_LEN            32
#define QQSRV_HOMEPAGE_LEN              64
#define QQSRV_BRIEF_LEN                 256
#define QQSRV_SCHOOL_LEN                32
#define QQSRV_BIRTH_LEN                 32
#define QQSRV_PROVINCE_LEN              16
#define QQSRV_CITY_LEN                  16
#define QQSRV_COUNTRY_LEN               16
#endif

#define QQSRV_CONFIG_PASSWORD_MAX_LEN   32
#define QQSRV_MAX_SERVER_ADDR           16


typedef enum
{
    QQSRV_Notify_Mask_InitQQClientInd       = 0x000001,
    QQSRV_Notify_Mask_DestroyQQClientInd    = 0x000002,
    QQSRV_Notify_Mask_QQLoginInd            = 0x000004,
    QQSRV_Notify_Mask_QQVerifyInd           = 0x000008,
    QQSRV_Notify_Mask_QQLogoutInd           = 0x000010,
    QQSRV_Notify_Mask_QQEvtUpdateInd     = 0x000020,
    QQSRV_Notify_Mask_QQDelBuddyByIdInd     = 0x000040,
    QQSRV_Notify_Mask_QQAddBuddyByIdInd     = 0x000080,
    QQSRV_Notify_Mask_QQLoadChatHistoryInd  = 0x000100,
    QQSRV_Notify_Mask_QQGetBuddyInfoInd     = 0x000200,
    QQSRV_Notify_Mask_QQSrvStatusChangeInd  = 0x000400,
} QQSRV_NOTIFY_MASK_TAG_e;

typedef enum
{
    QQSRV_QQ_STATUS_NONE = 0x00,
    QQSRV_QQ_STATUS_LOGINING = 0x01,

    // QQ protocol status begin ......
    QQSRV_QQ_STATUS_ONLINE = 0x0a,
    QQSRV_QQ_STATUS_OFFLINE = 0x14,
    QQSRV_QQ_STATUS_AWAY = 0x1e,
    QQSRV_QQ_STATUS_HIDDEN = 0x28,
    QQSRV_QQ_STATUS_BUSY = 0x32,
    QQSRV_QQ_STATUS_KILLME = 0x3C,
    QQSRV_QQ_STATUS_QUIET = 0x46,

    QQSRV_QQ_STATUS_LOGOUTING,
    // QQ protocol status end ......
} QQSrvQQStatus_e;

typedef enum _QQSrvErrCode_e
{
    QQSRV_OK = 0,
    QQSRV_ERR_PENDING = -1,
    QQSRV_ERR_VERIFY_REQUIRED = -2,
    QQSRV_ERR_DENIED = -3,
    QQSRV_ERR_WRONG_PASSWORD = -4,
    QQSRV_ERR_GET_NETWORK_PROFILE = -5,
    QQSRV_ERR_ESTABLISH_NETWORK_CONNECTION = -6,
    QQSRV_ERR_NETWORK_FAILED = -7,
    QQSRV_ERR_OUT_OF_MEMORY = -8,
    QQSRV_ERR_PROTOCOL_ERROR = -9,
    QQSRV_ERR_FILE_ERROR = -10,
    QQSRV_ERR_UNKNOWN = -11,
    QQSRV_ERR_REFUSED = -12,
    QQSRV_ERR_WAIT_FOR_REPLY = -13,// for add buddy, when the adding buddy
                                    //set privacy to be "Require identity verification to add me as a contact"
    QQSRV_ERR_NEED_ANSWER_QUESTION = -14,
    QQSRV_ERR_ERROR_ANSWER = -15,
    QQSRV_ERR_BLOCK_BUDDY = -16,
    QQSRV_ERR_QQ_ACCOUNT_NOT_FOUND = -17,
    QQSRV_ERR_BUSY = -18, // QQ account has been logined in another place
} QQSrvErrCode_e;

typedef enum _QQSrvMsgType_e
{
    QQSRV_MSG_TYPE_BUDDY,
    QQSRV_MSG_TYPE_QUN,
    QQSRV_MSG_TYPE_SYS_NORMAL,
    QQSRV_MSG_TYPE_SYS_ADD_BUDDY_REQ,
} QQSrvMsgType_e;

typedef enum _QQSrvEvent_e
{
    QQSRV_EVT_STATUS_CHANGED,

    // message event begin ......
    QQSRV_EVT_IM_MSG_ARRIVED,
    QQSRV_EVT_QUN_MSG_ARRIVED,
    QQSRV_EVT_SYS_MSG_ARRIVED,
    QQSRV_EVT_AGREED_TO_ADD_BUDDY,
    QQSRV_EVT_REFUSED_TO_ADD_BUDDY,
    QQSRV_EVT_ADD_BUDDY_REQ,
    // message event end ......

    QQSRV_EVT_BUDDY_UPDATED,
    QQSRV_EVT_QUN_UPDATED,
    QQSRV_EVT_GROUP_UPDATED,
} QQSrvEvent_e;

typedef enum _QQSrvStatus_e
{
    QQSRV_STATUS_NONE = 0, // means QQ client hasn't been initialized. Must call SrvQQInitQQClient when launch QQ AP.
    QQSRV_STATUS_INITIALIZING,
    QQSRV_STATUS_READY, // means QQ client has been initialized, but QQ account is offline and need to login again.

    QQSRV_STATUS_ONLINE,
    QQSRV_STATUS_RECV_NEW_MSG,

} QQSrvStatus_e;

typedef struct _QQSrvEvtUpdateItem_t{
    u32 accountId;

	u32 param; /*
       			For #QQSRV_EVT_IM_MSG_ARRIVED, param stands for the id number of message sender
       			For #QQSRV_EVT_QUN_MSG_ARRIVED, param stands for the id number of qun message
 	 			For #QQSRV_EVT_STATUS_CHANGED,param stands for new status
 	 		     */
    QQSrvEvent_e event;
    QQSrvErrCode_e errCode;
} QQSrvEvtUpdateItem_t;

typedef struct _QQSrvHistoryBufferItem_t{
	u8 *pBuffer;
	u32 uLen;
} QQSrvHistoryBufferItem_t;


typedef struct _QQSrvQQAccountInfo_t {
    u32    id;
    u8     password[QQSRV_CONFIG_PASSWORD_MAX_LEN];

    u8     bRemPsw;
    u8     bHideLogin;
    u8     bRecvQunMsg;
} QQSrvQQAccountInfo_t;

typedef struct _QQSrvQQConfig_t {
    u8              bSoundOn;
    u8              bVibrateOn;

    VectorClass_t   *pAccountInfoVector;  // QQSrvQQAccountInfo_t
} QQSrvQQConfig_t;

typedef struct _QQSrvMsgPacket_t
{
    u32 userId;
    u32 qunId;
    u32 time;
    u32 len;
    u8  *pNickName;
    u8  *pMsg;
    QQSrvMsgType_e type;
} QQSrvMsgPacket_t;

typedef struct _QQVerifyPngPacket_t
{
    u8  *pMsg;
} QQVerifyPngPacket_t;

typedef enum
{
    QQSRV_VERIFY_IDENTITY = 0,
    QQSRV_VERIFY_ANSWER
} QQSrvVerifyType_e;

typedef struct _QQSrvQQBuddy_t
{
    u32        number;
    u8         *pNickName;
    u32        ip;
    u16        port;
    u16        face;
    u8         age;
    u8         sex;
    u8         gid;
    u8         qqshow;
    u8         flag;
    QQSrvQQStatus_e status;
    u8         verify_flag;    //00 permit 01 verify 02 reject 03 question
    u8         account_flag;
    u8         session_key[QQSRV_SESSION_KEY_LEN];
    u32        sign_time;

#ifndef QQ_NO_BUDDY_DETAIL_INFO
    u8      *pSignature;
    u8      *pAccount;
    u8      *pAlias;
    u8      *pPostCode;
    u8      *pAddress;
    u8      *pHomePhone;
    u8      *pMobilePhone;
    u8      *pEmail;
    u8      *pOccupation;
    u8      *pHomePage;
    u8      *pBrief;
    u8      *pSchool;
    u8      *pBirth;
    u8      *pProvince;
    u8      *pCity;
    u8      *pCountry;
#else
    s8         signiture[1];
    s8         account[1];
    s8         alias[1];
    s8         post_code[1];
    s8         address[1];
    s8         homephone[1];
    s8         mobilephone[1];
    s8         email[1];
    s8         occupation[1];
    s8         homepage[1];
    s8         brief[1];
    s8         school[1];
    s8         birth[1];
    s8         province[1];
    s8         city[1];
    s8         country[1];
#endif
    u16        version;

    VectorClass_t       *pUnreadMsgList; //QQSrvMsgPacket_t
    VectorClass_t       *pHistoryMsgList;
 } QQSrvQQBuddy_t;

typedef struct _QQSrvQunMemberInfo_t
{
    u32     number;
    u8      *pNickname;
    u16     face;
    u8      age;
    u8      sex;
    u8      qqshow;
    u8      flag;
    u8      status;
    u8      accountFlag;
    u8      *pAccount;
    u8      role;
    u8      org;
} QQSrvQunMemberInfo_t;

typedef struct _QQSrvQQQun_t
{
    u32             number;     //internal number
    u32             ext_number; //external number
    u32             owner;
    u8              *pNickname;
    u8              *pAnnouncement;
    u8              *pIntroduction;

    VectorClass_t   *pQunMemberList;  // QQSrvQunMemberInfo_t
    VectorClass_t   *pUnreadMsgList; //QQSrvMsgPacket_t
    VectorClass_t   *pHistoryMsgList;
}QQSrvQQQun_t;

typedef struct _QQSrvQQGroup_t
{
    u32             number;
    u8              *pName;
    u32             bExpand;
    u32             onlineCount;
    u32             order;

    VectorClass_t   *pBuddyList;
} QQSrvQQGroup_t;

typedef enum
{
    QQSRV_CONTACTS_LIST_ITEM_BUDDY,
    QQSRV_CONTACTS_LIST_ITEM_GROUP
} QQSrvBuddyListItemType_e;

typedef struct _QQSrvQQContactsListItem_t
{
    QQSrvBuddyListItemType_e  type;

    void *pData; // if type is QQSRV_BUDDY_LIST_ITEM_GROUP, pData is QQSrvQQGroup_t, otherwise pData is QQSrvQQBuddy_t
} QQSrvQQContactsListItem_t;

typedef struct _QQSrvQQClient_t
{
    u32                 id;
    u8                  password[QQSRV_CONFIG_PASSWORD_MAX_LEN];
    QQSrvQQBuddy_t      *pSelf;

    //buddy qun group
    VectorClass_t       *pQunList;
    VectorClass_t       *pGroupList; // QQSrvQQGroup_t
    VectorClass_t       *pSysMsgList; // QQSrvMsgPacket_t
    VectorClass_t       *pBuddyHasMsgList; //QQSrvQQBuddy_t
    VectorClass_t       *pQunHasMsgList; //_QQSrvQQQun_t
    VectorClass_t       *pContactsList;

    u32                 unReadMsgAmount;

    QQSrvQQStatus_e     status;
    QQSrvErrCode_e      errCode;
    u8                  bOnlyShowOnlineBuddy;

    // login info
    u8                  bRemPsw;
    u8                  bRecvGroupMsg;
    u8                  bHideLogin;
} QQSrvQQClient_t;

typedef struct
{
    u8 *pPduData;
    u32 dataLen;
} QQSrvPduData_t;


/**
 * External Events
 */
#define QQSRV_EVT_InitQQClient           (CLSID_QQSRV << 16 | 1)
#define QQSRV_EVT_DestroyQQClient       (CLSID_QQSRV << 16 | 2)
#define QQSRV_EVT_QQLogin                (CLSID_QQSRV << 16 | 3)
#define QQSRV_EVT_QQVerify               (CLSID_QQSRV << 16 | 4)
#define QQSRV_EVT_QQLogout               (CLSID_QQSRV << 16 | 5)
#define QQSRV_EVT_QQEvtUpdate        (CLSID_QQSRV << 16 | 6)
#define QQSRV_EVT_DelBuddyById           (CLSID_QQSRV << 16 | 7)
#define QQSRV_EVT_AddBuddyById          (CLSID_QQSRV << 16 | 8)
#define QQSRV_EVT_LoadChatHistory        (CLSID_QQSRV << 16 | 9)
#define QQSRV_EVT_GetBuddyInfo           (CLSID_QQSRV << 16 | 10)
#define QQSRV_Evt_QQSrvStatusChange     (CLSID_QQSRV << 16 | 11)



#define INHERIT_IQQSRV(IName) \
    INHERIT_IHandler(IName);    \
    MAE_Ret (*RegisterNotification)             (IName *, void* pInstance, QQSRV_NOTIFY_MASK_TAG_e mask);    \
    MAE_Ret (*DeRegisterNotification)           (IName *, void* pInstance, QQSRV_NOTIFY_MASK_TAG_e mask);    \
    MAE_Ret (*InitQQClient)                     (IName *, u8 nActiveSimId); \
    MAE_Ret (*DestroyQQClient)                  (IName *); \
    MAE_Ret (*GetQQSrvStatus)                   (IName *, QQSrvStatus_e *pStatus);\
    MAE_Ret (*Login)                            (IName *, u32 accountID, u8 *pPswStr, boolean bRemPsw, boolean bRecvGroupMsg, boolean bHideLogin); \
    MAE_Ret (*Verify)                           (IName *, u8 *pVerifyStr, QQSrvVerifyType_e type); \
    MAE_Ret (*Logout)                           (IName *, u32 accountID); \
    MAE_Ret (*GetQQConfig)                      (IName *, QQSrvQQConfig_t **ppConfig); \
    MAE_Ret (*GetActiveQQClient)                (IName *, QQSrvQQClient_t **ppQQClient); \
    MAE_Ret (*SendMsg)                          (IName *, u32 type, u32 receiverID, u8 *pMsg); \
    MAE_Ret (*ChangeStatus)                     (IName *, QQSrvQQStatus_e newStatus); \
    MAE_Ret (*SetGroupMsgSettings)              (IName *, boolean bBlockGroupMsg);\
    MAE_Ret (*DelBuddyById)                     (IName *, u32 buddyID, u8 isBlock); \
    MAE_Ret (*AddBuddyById)                     (IName *, u32 buddyID, u8 *pReqStr); \
    MAE_Ret (*AddBuddyReply)                    (IName *, u32 buddyID, boolean isAccept); \
    MAE_Ret (*LoadChatHistory)                  (IName *, u32 msgType, u32 id);\
    MAE_Ret (*CleanChatHistory)                 (IName *, u32 msgType, u32 id);\
    MAE_Ret (*GetBuddyInfo)                     (IName *, u32 type, u32 uId);\
    MAE_Ret (*ExpandGroupById)                  (IName *, u32 groupId);\
    MAE_Ret (*CloseGroupById)                   (IName *, u32 groupId);\
    MAE_Ret (*GetContactsList)                  (IName *, VectorClass_t **ppContactsList);\
    MAE_Ret (*GetBuddyItemByNumber)             (IName *, u32 buddyID, QQSrvQQBuddy_t **ppBuddy);\
    MAE_Ret (*GetGroupItemById)                 (IName *, u32 groupID, QQSrvQQGroup_t **ppGroup);\
    MAE_Ret (*GetQunList)                       (IName *, VectorClass_t **ppQunList);\
    MAE_Ret (*GetQunItemById)                   (IName *, u32 qunID, QQSrvQQQun_t **ppQun);\
    MAE_Ret (*SetShowOnlineBuddyOnly)           (IName *, u8 bShowOnlineBuddyOnly);\
    MAE_Ret (*SetActiveQQAccount)               (IName *, u32 accountID);\
    MAE_Ret (*GetQQClientVector)                (IName *, VectorClass_t **ppQQClientVector);\
    MAE_Ret (*UpdateQQConfig)                   (IName *)

DEFINE_INTERFACE(IQQSRV);


/**
 * Function APIs
 */
MAE_Ret QQSrvNew(MAE_ClsId id, void **ppObj);

#define IQQSRV_QueryInterface(pICntlr, id, pp, po) \
    GET_FUNCTBL((pICntlr), IQQSRV)->QueryInterface(pICntlr, id, pp, po)

#define IQQSRV_HandleEvent(pICntlr, e, p1, p2) \
    GET_FUNCTBL((pICntlr), IQQSRV)->HandleEvent(pICntlr, e, p1, p2)

/**
 This function is used for registering a notify mask.
 */
#define IQQSRV_RegisterNotification(pICntlr, p1, p2) \
    GET_FUNCTBL((pICntlr), IQQSRV)->RegisterNotification( pICntlr, p1, p2)

/**
 This function is used for de-registering a notify mask for alarm.
 */
#define IQQSRV_DeRegisterNotification(pICntlr, p1, p2) \
    GET_FUNCTBL((pICntlr), IQQSRV)->DeRegisterNotification( pICntlr, p1, p2)

/**
This function is used for init QQ client.
*/
#define IQQSRV_InitQQClient(pICntlr, p1) \
    GET_FUNCTBL((pICntlr), IQQSRV)->InitQQClient(pICntlr, p1)

/**
This function is used for destroy QQ client.
*/
#define IQQSRV_DestroyQQClient(pICntlr) \
    GET_FUNCTBL((pICntlr), IQQSRV)->DestroyQQClient(pICntlr)

/**
This function is used for Update QQ Config into local file system.
*/
#define IQQSRV_UpdateQQConfig(pICntlr) \
    GET_FUNCTBL((pICntlr), IQQSRV)->UpdateQQConfig(pICntlr)


#define IQQSRV_GetQQSrvStatus(pICntlr, pStatus) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetQQSrvStatus(pICntlr, pStatus)

/**
This function is used for qq login.
*/
#define IQQSRV_Login(pICntlr, accountID, pPswStr, bRemPsw, bRecvGroupMsg, bHideLogin) \
    GET_FUNCTBL((pICntlr), IQQSRV)->Login(pICntlr, accountID, pPswStr, bRemPsw, bRecvGroupMsg, bHideLogin)

/**
This function is used for qq verify.
*/
#define IQQSRV_Verify(pICntlr, p1, p2) \
    GET_FUNCTBL((pICntlr), IQQSRV)->Verify(pICntlr, p1, p2)

/**
This function is used for qq logout.
*/
#define IQQSRV_Logout(pICntlr, accountID) \
    GET_FUNCTBL((pICntlr), IQQSRV)->Logout(pICntlr, accountID)

/**
This function is used for get qq config.
*/
#define IQQSRV_GetQQConfig(pICntlr, p1) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetQQConfig(pICntlr, p1)

/**
This function is used for get qq client.
*/
#define IQQSRV_GetActiveQQClient(pICntlr, ppClient) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetActiveQQClient(pICntlr, ppClient)

#define IQQSRV_SendMsg(pICntlr, type, receiverID, pMsg) \
    GET_FUNCTBL((pICntlr), IQQSRV)->SendMsg(pICntlr, type, receiverID, pMsg)

#define IQQSRV_ChangeStatus(pICntlr, newStatus) \
    GET_FUNCTBL((pICntlr), IQQSRV)->ChangeStatus(pICntlr, newStatus)

#define IQQSRV_SetGroupMsgSettings(pICntlr, bBlockGroupMsg) \
    GET_FUNCTBL((pICntlr), IQQSRV)->SetGroupMsgSettings(pICntlr, bBlockGroupMsg)

#define IQQSRV_DelBuddyById(pICntlr, buddyID, isBlock) \
    GET_FUNCTBL((pICntlr), IQQSRV)->DelBuddyById(pICntlr, buddyID, isBlock)

#define IQQSRV_AddBuddyById(pICntlr, buddyID, pReqStr) \
    GET_FUNCTBL((pICntlr), IQQSRV)->AddBuddyById(pICntlr, buddyID, pReqStr)

#define IQQSRV_AddBuddyReply(pICntlr, buddyID, isAccept)    \
    GET_FUNCTBL((pICntlr), IQQSRV)->AddBuddyReply(pICntlr, buddyID, isAccept)

#define IQQSRV_GetBuddyInfo(pICntlr, type, id) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetBuddyInfo(pICntlr, type, id)

/**
 * Load the chat history for specified QQ buddy or QQ qun.
 *
 * \param accountID [in]
 *      The account ID of QQ client.
 *
 * \param type [in]
 *      #QQSRV_MSG_TYPE_BUDDY or #QQSRV_MSG_TYPE_QUN
 *
 * \param id [in]
 *      Represent the id of QQ buddy if type is #QQSRV_MSG_TYPE_BUDDY.
 *      Represent the id of QQ qun if type is #QQSRV_MSG_TYPE_QUN
 */
#define IQQSRV_LoadChatHistory(pICntlr, type, id) \
    GET_FUNCTBL((pICntlr), IQQSRV)->LoadChatHistory(pICntlr, type, id)

/**
 * Clean up chat history for specified QQ buddy or QQ qun
 *
 * \param accountID [in]
 *      The account ID of QQ client
 *
 * \param msgType [in]
 *      #QQSRV_MSG_TYPE_BUDDY or #QQSRV_MSG_TYPE_QUN
 *
 * \param id [in]
 *      Represent the id of QQ buddy if type is #QQSRV_MSG_TYPE_BUDDY.
 *      Represent the id of QQ qun if type is #QQSRV_MSG_TYPE_QUN
 */
#define IQQSRV_CleanChatHistory(pICntlr, msgType, id) \
    GET_FUNCTBL((pICntlr), IQQSRV)->CleanChatHistory(pICntlr, msgType, id)

#define IQQSRV_ExpandGroupById(pICntlr, groupID) \
    GET_FUNCTBL((pICntlr), IQQSRV)->ExpandGroupById(pICntlr, groupID)

#define IQQSRV_CloseGroupById(pICntlr, groupID) \
    GET_FUNCTBL((pICntlr), IQQSRV)->CloseGroupById(pICntlr, groupID)

#define IQQSRV_GetContactsList(pICntlr, ppContactsList) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetContactsList(pICntlr, ppContactsList)

#define IQQSRV_GetBuddyItemByNumber(pICntlr, buddyID, ppBuddy) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetBuddyItemByNumber(pICntlr, buddyID, ppBuddy)

#define IQQSRV_GetGroupItemById(pICntlr, groupID, ppGroup) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetGroupItemById(pICntlr, groupID, ppGroup)

#define IQQSRV_GetQunList(pICntlr, ppQunList) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetQunList(pICntlr, ppQunList)

#define IQQSRV_GetQunItemById(pICntlr, qunID, ppQun) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetQunItemById(pICntlr, qunID, ppQun)

#define IQQSRV_SetShowOnlineBuddyOnly(pICntlr, bShowOnlineBuddyOnly) \
    GET_FUNCTBL((pICntlr), IQQSRV)->SetShowOnlineBuddyOnly(pICntlr, bShowOnlineBuddyOnly)

#define IQQSRV_SetActiveQQAccount(pICntlr, accountID) \
    GET_FUNCTBL((pICntlr), IQQSRV)->SetActiveQQAccount(pICntlr, accountID)

#define IQQSRV_GetQQClientVector(pICntlr,p1) \
    GET_FUNCTBL((pICntlr), IQQSRV)->GetQQClientVector(pICntlr, p1)


void mmi_QQSRV_FreeBuddyItem(void *pItemData, void *pUserData);

void mmi_QQSRV_FreeQunItem(void *pItemData, void *pUserData);

void mmi_QQSRV_FreeGroupItem(void *pItemData, void *pUserData);

void mmi_QQSRV_FreeMsgPacketItem(void *pItemData, void *pUserData);

void mmi_QQSRV_FreeQunMemberInfoItem(void *pItemData, void *pUserData);

void mmi_QQSRV_FreeQQClient(void *pItemData, void *pUserData);

void mmi_QQSRV_FreeQQAccountInfo(void *pItemData, void *pUserData);

void mmi_QQSRV_FreeContactsListItem(void *pItemData, void *pUserData);

#ifdef __cplusplus
}
#endif


#endif

