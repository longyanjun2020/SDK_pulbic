#ifndef __MCA_APP_H__
#define __MCA_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_common_sms_master.h"
/// 1. CallLog App,      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_SMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_MMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
/// 2. Cc App,           APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_MENU_AND_CLOSE_CURRENT_FUNCTION,         e_MCA_MENU_BOX = NULL,            pStartData = NULL
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_SMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
/// 3. Dialer App,       APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_SMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t 
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_MMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t 
/// 4. Event Center App, APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_SMS_VIEWER,                              e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = SVA_INIT_DATA_t
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = NULL
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_MMS_VIEWER,                              e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = SVA_INIT_DATA_t
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_CB_BOX,    pStartData = NULL
/// 5. Idle App,         APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_MMS_VIEWER,                              e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = SVA_INIT_DATA_t     (num == 1, SMS)
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_SMS_VIEWER,                              e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = SVA_INIT_DATA_t     (num == 1, MMS)
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = NULL                (num > 1)
/// 6. Phb App,          APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_SMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = NULL
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_MMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = NULL
/// 7. SendVia App,      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_MMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
///                      APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_SMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
/// 8. Sva App,          APM_Mode = APML_AUTO_RELEASE,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_REPLY_FORWARD_SMS_EDITOR,                e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
///                      APM_Mode = APML_AUTO_RELEASE,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_REPLY_FORWARD_MMS_EDITOR,                e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
///                      APM_Mode = APML_AUTO_RELEASE,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = NULL
/// 9. Todolist App,     APM_Mode = APM_LAUNCH_NORMAL,       param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_SMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
/// 10.Vendor App,       APM_Mode = APM_LAUNCH_EMBEDDED,     param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_SMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_MMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = SEA_EDITOR_Info_t
/// 11.Shortcut Srv,     APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_MENU,                                    e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = NULL 
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_DRAFT,     pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_OUTBOX,    pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_NEW_SMS_EDITOR,                          e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_DIAL_VOICE_MAIL_NUMBER_WITH_MASTER_SIM,  e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_DIAL_VOICE_MAIL_NUMBER_WITH_SLAVE_SIM,   e_MCA_MENU_BOX = MCA_E_MAIN_MENU, pStartData = NULL
/// 12.EventCenter Srv,  APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_SMS_VIEWER,                              e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_SMS_VIEWER,                              e_MCA_MENU_BOX = MCA_E_CB_BOX,    pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_MMS_VIEWER,                              e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_MMS_VIEWER,                              e_MCA_MENU_BOX = MCA_E_CB_BOX,    pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_INBOX,     pStartData = NULL
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MCA_Start_t, e_MCA_START_TYPE = MCA_E_START_BOX_MENU,                                e_MCA_MENU_BOX = MCA_E_CB_BOX,    pStartData = NULL


/// Message Cenetr 
/// 1. Edit New SMS
/// 2. Edit New MMS
/// 3. View Latest SMS
/// 4. View Latest MMS
/// 5. View Cell Broadcast
/// 6. View Voice Mail
/// 7. List all messages


typedef enum
{
    MSG_TYPE_MIN = 0,
    MSG_TYPE_SMS_PHONE = MSG_TYPE_MIN,
    MSG_TYPE_SMS_SIM1,
    MSG_TYPE_SMS_SIM2,
	MSG_TYPE_MMS,
	MSG_TYPE_CELL_BROADCAST,
    MSG_TYPE_MAX = MSG_TYPE_CELL_BROADCAST,
	MSG_TYPE_INVALID,
}MsgType_e;

typedef enum
{
	MSG_RECIPIENT_TYPE_MIN= 0,
    MSG_RECIPIENT_TYPE_TO = MSG_RECIPIENT_TYPE_MIN,
    MSG_RECIPIENT_TYPE_CC,
	MSG_RECIPIENT_TYPE_BCC,
    MSG_RECIPIENT_TYPE_MAX = MSG_RECIPIENT_TYPE_BCC,
    MSG_RECIPIENT_TYPE_NUM,
    MSG_RECIPIENT_TYPE_INVALID,
}MsgRecipientType_e;
enum 
{
    MMS_INSERT_OBJECT_NONE = 0x00,
    MMS_INSERT_OBJECT_IMAGE =0x01,
    MMS_INSERT_OBJECT_AUDIO =0x02,
    MMS_INSERT_OBJECT_VIDEO =0x04,
    MMS_INSERT_OBJECT_VCS   =0x08,    
    MMS_INSERT_OBJECT_TEXT  =0x10,
    MMS_INSERT_OBJECT_ATTACHMENT  =0x20,
};
typedef u8 MmsInsertObjectType_e;

typedef enum
{
	MSG_MAIN_MENU=0x00,
	MSG_BOX_START=0x01,
	MSG_INBOX=0x01,
	MSG_DRAFT=0x02,
	MSG_OUTBOX=0x03,
	MSG_SENTBOX=0x04,
	MSG_CBBOX = 0x05,
	MSG_NOT_PRIVATE_TOTAL,
	MSG_BOX_MASK=0xFF
} MsgListtype_e;

enum 
{
    VoiceMailType_All =0,
    VoiceMailType_SIM1,
    VoiceMailType_SIM2,
};
typedef u8 VoiceMailType_e;

typedef struct
{
    MAE_WChar* wStrName;
    MAE_WChar* wStrPhbNum;
    MsgRecipientType_e eRecipientTypes;
}MsgRecipient_t;

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
typedef struct 
{
	u16 MasterSimMsgNum;
	u16 SlaveSimMsgNum;
	u16 MMSMsgNum;
}NewMsgNum_t;
#endif

typedef struct
{
#ifdef __SMART_MESSAGING_MMI_SUPPORT__
	boolean bIsWapVCardMessage;
#endif
	u32 uRecipientNum;
    MsgRecipient_t *psRecipients;
    MAE_WChar *pwStrContent;
}MsgSmsData_t;

typedef struct
{
	u32 uRecipientNum;
    MsgRecipient_t *psRecipients;
	boolean bNeedToDeleteFile;
	MAE_WChar *pwStrUrl; // for object url full path  and  if object is text type, this means text content
    MmsInsertObjectType_e eObjType;
}MsgMmsData_t;

/// "Sms://Edit?APM_Mode=%d&RecipientNum=%d&RecipientName[0]=%d&RecipientPhbNum[0]=%d&...&Content=%s"
void LaunchAppToCreateNewSmsMsg // for phb, template, 
(
  AppLaunchMode_e eAppLaunchMode,
  MsgSmsData_t *psEditData, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
void LaunchAppToEditDraftSmsMsg
(
    AppLaunchMode_e eAppLaunchMode,
    u32 msgID,    
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
// msgID : MIN_MSG_ID ~MAX_PHONE_MSG_ID
void LaunchAppToReplySmsMsg
(
    AppLaunchMode_e eAppLaunchMode,
    u32 msgID,   
    SMI_MsgLocation_e eLocation,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

// msgID : MIN_MSG_ID ~MAX_PHONE_MSG_ID
void LaunchAppToForwardSmsMsg
(
    AppLaunchMode_e eAppLaunchMode,
    u32 msgID,    
    SMI_MsgLocation_e eLocation,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#ifdef __MMS_MMI_CDMMS__
/// "Mms://Edit?APM_Mode=%d&RecipientNum=%d&RecipientType[0]=%s&RecipientName[0]=%d&RecipientPhbNum[0]=%d&...&Content=%s"
void LaunchAppToCreateNewMmsMsg
(
  AppLaunchMode_e eAppLaunchMode,
  MsgMmsData_t *psEditData, 
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
void LaunchAppToEditDraftMmsMsg
(
    AppLaunchMode_e eAppLaunchMode,
    u32 msgID,    
	SMI_MsgLocation_e eLocation,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

// msgID : MIN_MSG_ID ~MAX_PHONE_MSG_ID
void LaunchAppToReplyMmsMsg
(
    AppLaunchMode_e eAppLaunchMode,
    u32 msgID,   
    SMI_MsgLocation_e eLocation,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

// msgID : MIN_MSG_ID ~MAX_PHONE_MSG_ID
void LaunchAppToForwardMmsMsg
(
    AppLaunchMode_e eAppLaunchMode,
    u32 msgID,  
    SMI_MsgLocation_e eLocation,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif //__MMS_MMI_CDMMS__
// msgID : MIN_MSG_ID ~MAX_PHONE_MSG_ID
void LaunchAppToViewLatestMsg
(
  AppLaunchMode_e eAppLaunchMode,  
  u32 msgID,      
  SMI_MsgLocation_e elocation,  
  MsgType_e eMsgType,    
  boolean bComplete,  
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// "MessageViewer://ListAll?APM_Mode=%d"
void LaunchAppToListMsg
(
  AppLaunchMode_e eAppLaunchMode,
  MsgListtype_e eBoxType,
  boolean bCloseCurMsgFunc,
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
  NewMsgNum_t tNewMessageNum,
#endif
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
void LaunchAppToVoiceMail
(
    AppLaunchMode_e eAppLaunchMode,
    VoiceMailType_e eType,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#ifdef __SMS_REJECT_CALL__
void LaunchAppToTemplate
(
  AppLaunchMode_e eAppLaunchMode,
  MAE_WChar *phoneNumber,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif

void LaunchAppToInboxAndShowFullNotice
(
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif
