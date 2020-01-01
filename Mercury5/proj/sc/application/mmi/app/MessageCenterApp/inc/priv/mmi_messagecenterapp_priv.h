////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_messagecenterapp_priv.h
* @version
* @brief   MCA applet private header file
*
*/

#ifndef __MMI_MESSAGECENTERAPP_PRIV_H__
#define __MMI_MESSAGECENTERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
// app
#include "mmi_messagecenterapp.h"
// view
#include "mmi_common_vtm.h"
#include "mmi_messagecenterapp_id.h"
#include "messagecenterapp_resource.h"

// service wrapper
#include "mmi_srv_evtcenter.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_phb.h"
#if defined(__MMS_MMI_CDMMS__) && defined(__USER_FILE_DELETER__)
#include "mmi_filemgrapp.h"
#endif
#ifdef __APP_MMI_PRIVATEPROTECT__ 
#include "mmi_srv_privateprotect.h"
#endif
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
#include "mmi_launcher_mca.h"
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MCA_DIALOG_TIMER  1000
#define MCA_WAITINGDIALOG_UPDATE_TIMER 1

#define MCA_BOX_ARRAY_ENSURE_CAPACITY_SMS_TAB   250
#define MCA_BOX_ARRAY_ENSURE_CAPACITY_CB_TAB    CBS_MAX_CBMSG_SIZE
#define MCA_BOX_ARRAY_GROW_NUM                  20

#define MCA_E_SENTBOX_OR_DRAFT   (MCA_E_NOT_PRIVATE_TOTAL+1)

#define MCA_PARAM1_TO_BOX(p)    ((e_MCA_MENU_BOX)(p))
#define MCA_BOX_TO_PARAM1(Box)  ((u32)Box)
#define MAX_SEARCHLIST_INPUT_BYTE				(40)
#define MCA_ISMARKMODETYPE(t)  (t!=MCA_E_MARK_OFF)

#define MCA_MAX_CHAR_SAVED_MSG  3   //Ex: 500
#define MCA_MAX_CHAR_MEMORY     8   //Ex: 99999999 MB (Total Phone Size could be about 95GB)
#define MCA_B_TO_MB(b)  ((b)/(1024*1024))
#define MCA_B_TO_KB(b)  ((b)/(1024))
#define MCA_IS_SHOW_MB(b)  ((b) >= 1024*1024)
#define MCA_IS_SHOW_KB(b)  (((b) >= 1024) && !MCA_IS_SHOW_MB(b))
#define MCA_MIN_CHAR_VOICEMAIL_NUMBER  3    //Ex: voice mail number: 123

#define MCA_IEVT_Active						(CLSID_MCA << 16 | 2)
#define MCA_IEVT_Invisible					(CLSID_MCA << 16 | 3)
#define MCA_IEVT_Suspend					(CLSID_MCA << 16 | 4)
#define MCA_IEVT_Resume						(CLSID_MCA << 16 | 5)
#define MCA_IEVT_DelayWaiting				(CLSID_MCA << 16 | 6)
#define MCA_IEVT_DialVoiceMailNumber		(CLSID_MCA << 16 | 7)
#define MCA_IEVT_GetListDone				(CLSID_MCA << 16 | 8)
#define MCA_IEVT_Reload						(CLSID_MCA << 16 | 9)
#define MCA_IEVT_Back						(CLSID_MCA << 16 | 10)
#define MCA_IEVT_DelConfirm					(CLSID_MCA << 16 | 11)
#define MCA_IEVT_GoToCreateNew				(CLSID_MCA << 16 | 12)
#define MCA_IEVT_GoToMenu					(CLSID_MCA << 16 | 13)
#define MCA_IEVT_GoToBox					(CLSID_MCA << 16 | 14)
#define MCA_IEVT_TabChange					(CLSID_MCA << 16 | 15)
#define MCA_IEVT_Option						(CLSID_MCA << 16 | 16)
#define MCA_IEVT_Select						(CLSID_MCA << 16 | 17)
#define MCA_IEVT_SIM_ERROR					(CLSID_MCA << 16 | 18)
#define MCA_IEVT_MENU_Box					(CLSID_MCA << 16 | 19)
#define MCA_IEVT_MENU_VoiceMail				(CLSID_MCA << 16 | 20)
#define MCA_IEVT_MENU_Template				(CLSID_MCA << 16 | 21)
#define MCA_IEVT_MENU_Setting				(CLSID_MCA << 16 | 22)
#define MCA_IEVT_MENU_MemStatus				(CLSID_MCA << 16 | 23)
#define MCA_IEVT_MENU_Read					(CLSID_MCA << 16 | 24)
#define MCA_IEVT_MENU_Delete				(CLSID_MCA << 16 | 25)
#define MCA_IEVT_MENU_DeleteAll				(CLSID_MCA << 16 | 26)
#define MCA_IEVT_MENU_ViewDetail			(CLSID_MCA << 16 | 27)
#define MCA_IEVT_MENU_CreateNew				(CLSID_MCA << 16 | 28)
#define MCA_IEVT_MENU_VoiceMailSetting		(CLSID_MCA << 16 | 29)
#define MCA_IEVT_MENU_CopyToPhone			(CLSID_MCA << 16 | 30)
#define MCA_IEVT_MENU_CopyToSim				(CLSID_MCA << 16 | 31)
#define MCA_IEVT_GoToOpDenial				(CLSID_MCA << 16 | 32)
#define MCA_IEVT_MENU_Move					(CLSID_MCA << 16 | 33)
#define MCA_IEVT_MENU_Send					(CLSID_MCA << 16 | 34)
#define MCA_IEVT_MENU_Search				(CLSID_MCA << 16 | 35)                 

#define MCA_APP_STATUS_INIT 					0x01 << 6
#define MCA_APP_STATUS_ACTIVE 					0x01 << 5
#define MCA_APP_STATUS_ACTIVE_READ_MSG			(MCA_APP_STATUS_ACTIVE | 0x01)
#define MCA_APP_STATUS_ACTIVE_DEL_MSG			(MCA_APP_STATUS_ACTIVE | 0x02)
#define MCA_APP_STATUS_ACTIVE_COPY2PHONE		(MCA_APP_STATUS_ACTIVE | 0x03)
#define MCA_APP_STATUS_ACTIVE_COPY2SIM			(MCA_APP_STATUS_ACTIVE | 0x04)
#define MCA_APP_STATUS_ACTIVE_MOVE_MSG			(MCA_APP_STATUS_ACTIVE | 0x05)
#define MCA_APP_STATUS_ACTIVE_OPDENIAL			(MCA_APP_STATUS_ACTIVE | 0x06)
#define MCA_APP_STATUS_ACTIVE_CANCELWAITING		(MCA_APP_STATUS_ACTIVE | 0x07)
#define MCA_APP_STATUS_ACTIVE_DIALVOICEMAIL		(MCA_APP_STATUS_ACTIVE | 0x08)
#define MCA_APP_STATUS_ACTIVE_BOX				(MCA_APP_STATUS_ACTIVE | 0x09)
#define MCA_APP_STATUS_ACTIVE_CHAT_DEL_MSG      (MCA_APP_STATUS_ACTIVE | 0x0A)  
#define MCA_APP_STATUS_ACTIVE_CHATITEM_DEL_MSG   (MCA_APP_STATUS_ACTIVE | 0x0B)
#define MCA_APP_STATUS_ACTIVE_CHATITEM_COPY2PHONE  (MCA_APP_STATUS_ACTIVE | 0x0C)
#define MCA_APP_STATUS_ACTIVE_SORTLIST  (MCA_APP_STATUS_ACTIVE | 0x0D)
#define MCA_APP_STATUS_ACTIVE_SEARCH			(MCA_APP_STATUS_ACTIVE | 0x0E)

#ifdef __MMI_SMS_EXPORT__
#define MCA_APP_STATUS_ACTIVE_EXPORTSMS			(MCA_APP_STATUS_ACTIVE | 0x0F)
#endif
#define MCA_APP_STATUS_INVISIBLE				0x01 << 4

#define IS_APP_STATUS_INIT(s) 		s & MCA_APP_STATUS_INIT
#define IS_APP_STATUS_ACTIVE(s) 	s & MCA_APP_STATUS_ACTIVE
#define IS_APP_STATUS_INVISIBLE(s) 	s & MCA_APP_STATUS_INVISIBLE

#define CHAT_ITEM_VIEW_MSG_NUM 5
#define CHAT_ITEM_HIGHLIGHTED_COLOR 0x8064B5E3
#define CHAT_ITEM_UNHIGHLIGHTED_COLOR 0x00FFFFFF

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct McaMemStatusWdgList_t_
{
	IWidget *pTitleWdg;
    IWidget *pScrollbarWdg;
    IWidget *pViewportWdg;
    IWidget *pMainContainer;
    IWidget *pPhoneMsgSmsTextWdg;
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
	IWidget *pPhoneHiddenMsgSmsTextWdg;
#endif
    IWidget *pPhoneMsgMmsTextWdg;
    IWidget *pPhoneMsgCBTextWdg;
    IWidget *pPhoneMsgWAPTextWdg;
    IWidget *pSimMsgTextWdg;
    IWidget *pSimMsgSingleTextWdg;
    IWidget *pSimMsgMasterTextWdg;
    IWidget *pSimMsgSlaveTextWdg;
    IWidget *pMobileMemTextWdg;
    IWidget *pMobileUsedTextWdg;
    IWidget *pMobilleAvailableTextWdg;
    IWidget *pMobileTotalTexWdg;
    IWidget *pMMSTotalTextWdg;
    IWidget *pMMSAvailableTextWdg;
    IWidget *pMMSMemTextWdg;
    IWidget *pMMSUsedTextWdg;
} McaMemStatusWdgList_t;

#ifdef __MMI_SMS_CHAT__
typedef struct McaChatItemWdgList_t_
{
	IWidget *pTitleWdg;
	IWidget *pScrollbarWdg;
	IWidget *pViewportWdg;
	IWidget *pInputWdg;
	IWidget *pMainPropContainer;
	IWidget *pBGImgWdg;
	IWidget *pInputBGImgWdg;
	IWidget *pInputAbsContainer;
	IWidget *pPropContainer;
	IWidget *pOlderBtnAbsContainer;
	IWidget *pOlderButton;
	IWidget *pNewerBtnAbsContainer;
	IWidget *pNewerButton;
} McaChatItemWdgList_t;
#endif

typedef struct
{
	SMI_MsgID_t MsgID;
	SMI_MsgLocation_e  storage;
} McaOperateMsg_t;

typedef struct
{
	u8 Type;
	u8 Status;
	u16 nOpIdx;
	McaOperateMsg_t *pMsgList;
} McaOperate_t;

#ifdef __MMI_SMS_CHAT__
typedef struct MCA_MSG_BOX_SORTDATA_TAG{
    McaMsgBoxItemData_t *pBoxItemData;
    void *pSortData;			// depend on the sortType Subject:WChar*, Sender:index;	
}MCA_Msg_Box_SortData_t;

typedef struct MCA_MSG_BOX_PHBDATA_TAG{
    SMS_MsgRecipAddr	tAddr;
    u16					nPhbSortedIndex;
}MCA_Msg_Box_PhbData_t;

typedef struct MCA_MSG_CHAT_ITEMDATA_TAG{
    SMS_MsgRecipAddr	tAddr;
    u32 SMSCount;
    SMI_TimeStamp_t time;    
    MAE_WChar *pMemoStr;
    boolean bMoreMemo;
    IArrayModel *pChatSMSArrayModel;  //SMS Chat content list Array Model
}MCA_Msg_Chat_ItemData_t;

typedef struct ChatItem_View{
  //u32 nHighlightedRec;  					// the highlight index of list
  WidgetHandler_t inputWdgHandler; 			// input widget handler to check if input widget is focused
  WidgetHandler_t scrollBarWdgHandler; 			// input widget handler to check if input widget is focused
}McaChatItemView_t;
#endif

typedef enum
{
	MCA_MSG_OPERATE_NONE=0x00,
	MCA_MSG_OPERATE_START=0x01,
	MCA_MSG_OPERATE_ONE_MSG,
	MCA_MSG_OPERATE_MULTI_MSG,
	MCA_MSG_OPERATE_MULTI_PHONE_MSG,
	MCA_MSG_OPERATE_MULTI_SIM_MSG,
	MCA_MSG_OPERATE_LOCATION,
#if __MSG_SUPPORT_DEL_LOCATION__
	MCA_MSG_OPERATE_PHONE_LOCATION,
	MCA_MSG_OPERATE_MASTER_SIM_LOCATION,
	MCA_MSG_OPERATE_SLAVE_SIM_LOCATION,
#endif
	MCA_MSG_OPERATE_TOTAL
} McaMsgOperateType_e;

typedef enum
{
	MCA_MSG_OPERATE_STATUS_START=0x00,
	MCA_MSG_OPERATE_STATUS_NONE=0x00,
	MCA_MSG_OPERATE_STATUS_WAIT,
	MCA_MSG_OPERATE_STATUS_SUCCESS,
	MCA_MSG_OPERATE_STATUS_PARTIAL_FAIL,
	MCA_MSG_OPERATE_STATUS_FAIL,
	MCA_MSG_OPERATE_STATUS_TOTAL
} McaMsgOperateStatus_e;

typedef enum
{
	MCA_BOX_UPDATE_SRC_NO_NEED=0x00,
	MCA_BOX_ADDMSG_DES_NO_NEED=0x00,
	MCA_BOX_UPDATE_SRC_SUCCESS,
	MCA_BOX_UPDATE_SRC_DES_SUCCESS,
	MCA_BOX_ADDMSG_DES_SUCCESS,
	MCA_BOX_UPDATE_SRC_FAIL,
	MCA_BOX_ADDMSG_DES_FAIL,
	MCA_BOX_UPDATE_SRC_NO_ITEM,
	MCA_BOX_ADDMSG_DES_NO_ITEM,
	MCA_BOX_UPDATE_SRC_BAD_PARAM,
	MCA_BOX_ADDMSG_DES_BAD_PARAM,
} McaBoxUpdateResult_e;

typedef enum
{
	MCA_E_MARK_START=0x00,
	MCA_E_MARK_OFF=0x00,
	MCA_E_MARK_ON,
	MCA_E_MARK_FOCUS,
	MCA_E_MARK_ALL,
	MCA_E_UNMARK_ALL,
	MCA_E_MARK_TOTAL
} McaMarkType_e;

typedef enum
{
	MCA_E_MASTER_SIM=0x00,
	MCA_E_SLAVE_SIM=0x01,
	MCA_E_SIM_TOTAL,
} McaSettingSim_e;

typedef enum
{
	MCA_E_EMB_AP_START=MCA_E_START_TYPE_TOTAL,
	MCA_E_EMB_BOX_SMS_VIEWER=MCA_E_EMB_AP_START,
} McaEmbApType_e;

typedef enum
{
	MCA_E_MSG_SIM_UNKNOWN = 0,
	MCA_E_MSG_SIM_SINGLE,
	MCA_E_MSG_SIM_MASTER,
	MCA_E_MSG_SIM_SLAVE,
	MCA_E_MSG_SIM_STATUS_TOTAL,
} McaMsgSimStatus_e;

typedef enum
{
	MCA_E_MSG_TYPE_SMS = 0,
	MCA_E_MSG_TYPE_MMS,
#ifdef __MMI_SMS_WAPPUSH__
	MCA_E_MSG_TYPE_WAPPUSH,
#endif
	MCA_E_MSG_TYPE_INBOX_TOTAL,
	MCA_E_MSG_TYPE_CB=MCA_E_MSG_TYPE_INBOX_TOTAL,
	MCA_E_MSG_TYPE_TOTAL,
} McaMsgType_e;

typedef enum
{
	MCA_E_OPTION_MENU_LEVEL1 = 0,
	MCA_E_OPTION_MENU_LEVEL2,
	MCA_E_OPTION_MENU_CSK,
} McaOptionMenuStyle_e;

typedef enum
{
    MCA_E_INIT_NONE             =0x00,
    MCA_E_INIT_EVT_START        =0x01,
    MCA_E_INIT_SIM_SRV_INIT     =0x02,
    MCA_E_INIT_SMS_SRV_READY    =0x04,
    MCA_E_INIT_SMI_SRV_NOTBUSY  =0x08,
    MCA_E_INIT_CB_SRV_READY     =0x10,
#ifdef __MMS_MMI_CDMMS__
    MCA_E_INIT_MMS_SRV_READY=0x20,
    MCA_E_INIT_ALL_READY=0x3F,
#else
    MCA_E_INIT_ALL_READY=0x1F,
#endif
     MCA_E_INIT_EVT_RESUME=0x80
} McaInitFlag_e;

typedef enum
{
    MCA_MENU_ITEM_START=0x00,
    MCA_MENU_CREATE_NEW=0x00,
#ifndef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
    MCA_MENU_BOX_ITEM_START=0x01,
#endif
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
	MCA_MENU_SMS=0x01,
#ifdef __MMS_MMI_CDMMS__
	MCA_MENU_MMS,
#endif
#else
    MCA_MENU_INBOX=0x01,
    MCA_MENU_DRAFT_BOX,
    MCA_MENU_OUTBOX,
    MCA_MENU_SENT_BOX,
#endif
#ifndef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
    MCA_MENU_BOX_ITEM_TOTAL,
    MCA_MENU_TEMPLATE=MCA_MENU_BOX_ITEM_TOTAL,
#else
	MCA_MENU_TEMPLATE,
#endif

#ifdef __MMI_SMS_CHAT__
    MCA_MENU_SMS_CHAT,
#endif

#ifdef __MMI_SMS_SEARCH__	
	MCA_MENU_SMS_SEARCH,
#endif

    MCA_MENU_VOICE_MAIL,
    MCA_MENU_CB,
    MCA_MENU_SETTING,
    MCA_MENU_MEMORY_STATUS,
    MCA_MENU_ITEM_TOTAL
}McaMenuItem_e;

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
typedef enum
{
	MCA_MENU_BOX_ITEM_START=MCA_MENU_ITEM_TOTAL,
	MCA_MENU_INBOX=MCA_MENU_ITEM_TOTAL,
    MCA_MENU_DRAFT_BOX,
    MCA_MENU_OUTBOX,
    MCA_MENU_SENT_BOX,
	MCA_MENU_BOX_ITEM_TOTAL,
}McaMsgBoxMenuItem_e;

typedef enum
{
	MCA_MSG_NONE,
	MCA_MSG_MASTER_SIM,
	MCA_MSG_SLAVE_SIM,
    MCA_MSG_MMS,
}McaMsgBoxTypeItem_e;
#endif

typedef enum McaMsgSortingType_e_
{
	SORTBY_DATE,    // default
	SORTBY_NUMBER,
	SORTBY_SUBJECT,
	SORTBY_MSGTYPE, // SMS/MMS
	SORTBY_LOC, 	// phone/SIM1/SIM2
} McaMsgSortingType_e;

typedef enum McaMsgStorageSizeUnitType_e_
{
    SIZEUNIT_BYTE,
    SIZEUNIT_KB,
    SIZEUNIT_MB,
    SIZEUNIT_ITEM_TOTAL
} McaMsgStorageSizeUnitType_e;

#ifdef __3D_MESSAGE_BOX__
enum
{
    MCA_DESKTOP_BUTTON_OPTION,
    MCA_DESKTOP_BUTTON_REPLY,
    MCA_DESKTOP_BUTTON_DELETE,
    MCA_DESKTOP_BUTTON_BACK,
    MCA_DESKTOP_BUTTON_TOTAL,
};
typedef u16 IdleApp_M303_Desktop_Button_e;
#endif

typedef struct McaMsgBoxSortData_t_
{
	McaMsgBoxItemData_t *pBoxItemData;
	void *pSortData;			// depend on the sortType Subject:WChar*, Sender:index;
} McaMsgBoxSortData_t;

typedef struct
{
    u32 MenuID;
    u32 nTotal;
    u32 nRead;
    u32 nSending;
} McaMsgMainItemData_t;

// window related

typedef struct MainMenuWndData_t_
{
	MenuWdgList_t tWdgList;
} MainMenuWndData_t;

typedef struct NewMsgMenuWndData_t_
{
	MenuWdgList_t tWdgList;
} NewMsgMenuWndData_t;

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
typedef struct SimMsgBoxMenuWndData_t_
{
	MenuWdgList_t tWdgList;
} SimMsgBoxMenuWndData_t;
typedef struct NewMsgBoxSelectMenuWndData_t_
{
	MenuWdgList_t tWdgList;
} NewMsgBoxSelectMenuWndData_t;
#endif

typedef struct ListMenuWndData_t_
{
	u16 nViewID;
	u16 nMenuID;
	TabMenuWdgList_t tWdgList;
	MenuWdgList_t tCbWdgList;
#ifdef __3D_MESSAGE_BOX__
    IWidget *pIGLBoxListWdg;
    IWidget *PIGLTitleWdg;
    boolean bShow;
    boolean bBoxWnd;
#endif
} ListMenuWndData_t;

#ifdef __MMI_SMS_CHAT__
typedef struct ChatListMenuWndData_t_
{
    MenuWdgList_t tWdgList;
}ChatListMenuWndData_t;

typedef struct ChatListOptMenuWndData_t_
{
    OptionMenuWdgList_t tOptionMenuWdgList;
}ChatListOptMenuWndData_t;

typedef struct ChatItemMenuWndData_t_
{
    //MenuWdgList_t tWdgList;
	McaChatItemWdgList_t tWdgList;

}ChatItemMenuWndData_t;

typedef struct ChatItemOptMenuWndData_t_
{
    OptionMenuWdgList_t tOptionMenuWdgList;
}ChatItemOptMenuWndData_t;

typedef struct ChatBubbleWdgList_t_
{
    IWidget *pChatBubbleAbsContainer;
    IWidget *pChatBubbleButtonWdg;
    IWidget *pChatBubbleTextBubble;
    IWidget *pChatBubbleTextWdg;
    //IWidget *pChatBubbleImageWdg;
}ChatBubbleWdgList_t;

typedef struct ChatBubbleDateWdgList_t_
{
    IWidget *pChatBubbleDateAbsContainer;
    IWidget *pChatBubbleDateTextBubble;
}ChatBubbleDateWdgList_t;
#endif

typedef struct OptMenuWndData_t_
{
	OptionMenuWdgList_t tOptionMenuWdgList;
} OptMenuWndData_t;

typedef struct OptMenuWndInitData_t_
{
	u32 nEvt;
	u32 param1;
} OptMenuWndInitData_t;

typedef struct SettingMenuWndData_t_
{
	MenuWdgList_t tWdgList;
} SettingMenuWndData_t;

typedef struct MemStatusWndData_t_
{
	McaMemStatusWdgList_t tWdgList;
} MemStatusWndData_t;

typedef struct DualSimMenuWndData_t_
{
	SimSelectionWdgList_t tWdgList;
} DualSimMenuWndData_t;

typedef struct ViewMsgDetailWndData_t_
{
	McaDetailViewWdgList_t tWdgList;
} ViewMsgDetailWndData_t;

#ifdef __MMI_SMS_SEARCH__	
typedef struct SearchBoxMenuWndData_t_
{
	MenuWdgList_t tWdgList;
} SearchBoxMenuWndData_t;

typedef struct SearchListWdgList_t_
{
    IWidget *pSearchList_PROPCONTAINER;
    IWidget *pSearchList_TITLEWIDGET;
    IWidget *pSearchList_MENUWIDGET;
    IWidget *pSearchList_ABSCONTAINER;
    IWidget *pSearchList_BGIMGWDG;
    IWidget *pSearchList_BUTTONWDG;
    IWidget *pSearchList_INPUTWIDGET;
}SearchListWdgList_t;

typedef struct SearchList_View
{
  WidgetHandler_t inputWdgHandler; 			// input widget handler to check if input widget is focused
}SearchListView_t;
#endif

typedef struct
{
	APPLET_BASE_ELEMENTS;

	e_MCA_START_TYPE StartType;
	e_MCA_MENU_BOX EntryMenu;
	e_MCA_MENU_BOX BoxType;
	McaMarkType_e MarkModeType;
	u8 InitConfirmFlag;
	u8 nAppStatus;

	/* for Main Menu*/
	//View
	HistoryInfo_t MainMenuHistory;
	//Data
	//IVectorModel *pIMainVectorModel;			//Main Menu Vector, Private Main Menu Vector
	VectorClass_t *pIMainVectorModel;			//Main Menu Vector, Private Main Menu Vector
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
	VectorClass_t *pIMainBoxVectorModel;		//Main Box Menu Vector, Private Main Menu Vector
	HistoryInfo_t MainBoxMenuHistory;
#endif

	/* for Box Menu */
	//View
	HistoryInfo_t BoxMenuHistory;
	//IMenuModel *pBoxMenuModel; //for mark mode box using, to keep the selected item

	//Data
	IArrayModel *pBoxArrayModel;		//Box Array Model
	ModelListener_t BoxArrayMdlListener;

	/* for Both Box and Center Menu*/

	/* for Option Menu in Box Mode*/
	//IWidget 		*pOptionMenuWdg; 	//for L2 Option Menu

	/* for send Message Dual SIM Menu*/

	//Box Msg current operation
	McaOperate_t CurrentOperate;
	MCA_Start_t *pOpDelayStart; 		//After operation process the start request
	//u32 nDeleteMsgId;
    McaOperateMsg_t *pTempMsgList;

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
	McaMsgBoxTypeItem_e MsgBoxType;
	boolean bNeedRefresh;
	NewMsgNum_t tNewMessageNum;
	boolean bIsInboxTypeSelectView;
	boolean bIsClass0SMSSaving;
#endif

#ifdef __MMI_SMS_CHAT__
    boolean bDeleteChat;
    boolean bSMSChatMode;
    boolean bHistoryMode;
    boolean bViewerMode;
    boolean bViewerOpen;
    u32 ChatItemIndex;
    u32 ChatItemOldIndex;
    u32 ChatMenuOldIndex;
    u32 ViewerMenuOldIndex;
    u32 ViewerItemOldIndex;    
    IArrayModel *pChatArrayModel;        //SMS Chat list Array Model(MCA_Msg_Chat_ItemData_t)
    IArrayModel *pTmpChatArrayModel;        //SMS Chat list Array Model    
    ModelListener_t ChatArrayMdlListener;    
    //IMenuModel *pChatMenuModel;         
    //IMenuModel *pChatItemModel;    
    HistoryInfo_t ChatMenuHistory;
    HistoryInfo_t ChatItemHistory;

    boolean bSenderRecipientName;
    boolean bNoneChatItem;
    boolean bDeleteSentBox;
    boolean bNeedDeleteSentBox;
    u32 nDeleteSendBoxMsg;

    boolean bReloadSMSChatList;   //Reload the SMSChat list after deleting SMS
    boolean pInitSMSChat;	//Flag if create MCA_WND_CHATLISTMENU after reload SMSChat list
	McaChatItemView_t ChatItemView;
	boolean bChatMarkMode;
	u32 nChatItemFocusedIndex;
	u32 nCurrMsgIndex;
	u32 nCurrDateIndex;
	SMI_TimeStamp_t RefTime;
	boolean bIsChecked[CHAT_ITEM_VIEW_MSG_NUM];
	McaOperate_t TempOperate;
	boolean bChatSendMessage;
	IArrayModel *pChatSMSAbsConArrayModel; //SMS Chat AbsContainer Array Model
	IArrayModel *pChatDateItemWdgArrayModel; //SMS Chat Date Item Wdg Array Model
	u32 nChatItemViewMsgNum;
	boolean bFirstCreateChatItem;
	u32 nNextMsgIndex;
	u32 nChatViewPortWidth;
	SMI_MsgID_t nCurrSendMsgId;
	boolean bSimBusyNeedReload;
#ifndef __FADE_OUT_SCROLLBAR__
	boolean bScrollBarNeedToAdjust;
	ModelListener_t tMainPropViewMdlListener;
#endif
#endif

#ifdef __MMI_SMS_SEARCH__	
    SearchListView_t tSearchListView;
	IArrayModel *pSearchArrayModel;		//Box Array Model
	MAE_WChar *pCmpContent;
	u8 *CmpContent;
	u8 SearchBoxIndex;
	u32 SearchArrayIndex;
	boolean bSearchDone;
	u16 phbSerialNo;
#endif
    boolean bSearchMode;
	boolean bSuspend;
#ifdef __SIM_NO_RSP_HANDLING__
    boolean bHandleSIMNoRspInd;
#endif
	COMMON_SIM_CARD_STATUS_e SIMStatus;
	boolean bShowFullNotice;

	// for sorting
	McaMsgSortingType_e eCurrentSortType; // record current sorting type to sort,

#ifdef __MMI_SMS_EXPORT__
	// for export SMS
	e_MCA_EXPORT_DEST ExportDest;
	MAE_Ret ExportResult;
	u32	ExportAmount;
#endif
	/* for Embedded AP */
	IApplet *pEmbAP;
	void *pEmbApStartData;
	McaEmbApType_e EmbApType;
	//ModelListener_t EmbAPNotifyListen;	  //for embedded voice mail ap notify the ap close
	IDataModel	*pEmbViewerInfoDataMdl;   //The Msg Info

#if defined(__3D_MESSAGE_BOX__)
    IApplet *pQA3D;
    u16 nQAPageIndex, nQAPageTotal;
    u8 bPrompt3DView;
    IWidget *pButtonContainer;
    IWidget *pDesktopButWdg[MCA_DESKTOP_BUTTON_TOTAL];
    boolean bBoxMode;
#endif
#ifdef __SMS_SEND_FROM_BUFFER__
    boolean                         bIsBuffMsg;
#endif /* __SMS_SEND_FROM_BUFFER__ */
	boolean bNeedShowFullNotice;
} McaAppData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/
#if defined(__3D_MESSAGE_BOX__)
const static u32 BoxStringID[]={TXT_LTL_N_INBOX, TXT_LTL_N_DRAFT_BOX, TXT_LTL_N_OUTBOX, TXT_LTL_N_SENT_BOX, TXT_LTL_N_CB};
const static u32 BoxTabImgID[]={MSGBOX3D_IMG_INBOX_ICON, MSGBOX3D_IMG_DRAFT_ICON, MSGBOX3D_IMG_OUTBOX_ICON, MSGBOX3D_IMG_SENTBOX_ICON};
#endif
const static u32 ActiveTabImgID[]={SMS_IMG_TAB_INBOX, SMS_IMG_TAB_DRAFT, SMS_IMG_TAB_OUTBOX, SMS_IMG_TAB_SENTBOX};
const static u32 InActiveTabImgID[]={SMS_IMG_TAB_INBOX_DISABLE, SMS_IMG_TAB_DRAFT_DISABLE, SMS_IMG_TAB_OUTBOX_DISABLE, SMS_IMG_TAB_SENTBOX_DISABLE};
const static u32 MenuItemTextID[]={TXT_LIL_N_CREATE_NEW, 
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
                                   TXT_LIL_N_SMS,
#ifdef __MMS_MMI_CDMMS__
								   TXT_LIL_N_MMS,
#endif
#else
                                   TXT_LIL_P_INBOX_UNREAD, TXT_LIL_P_DRAFT_BOX, TXT_LIL_P_OUTBOX, TXT_LIL_P_SENT_BOX,
#endif
                                   TXT_LIL_N_TEMPLATE, 
#ifdef __MMI_SMS_CHAT__
                                   TXT_LIL_N_SMS_CHAT,
#endif
#ifdef __MMI_SMS_SEARCH__	
                                   TXT_LIL_N_SEARCH_SMS,
#endif

                                   TXT_LIL_N_VOICE_MAIL, TXT_LIL_N_CELL_BROADCAST, TXT_LIL_N_SETTINGS, TXT_LIL_N_MEMORY_STATUS
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
                                   , TXT_LIL_P_INBOX_UNREAD, TXT_LIL_P_DRAFT_BOX, TXT_LIL_P_OUTBOX, TXT_LIL_P_SENT_BOX
#endif
};
#ifdef __MSG_SUPPORT_ICON_MENU__
const static u32 MenuItemImgID[] ={COMMON_IMG_NO_1, COMMON_IMG_NO_2, COMMON_IMG_NO_3, COMMON_IMG_NO_4, COMMON_IMG_NO_5,
							 COMMON_IMG_NO_6, COMMON_IMG_NO_8, COMMON_IMG_NO_9, COMMON_IMG_NO_10, COMMON_IMG_NO_11}; //wait for the icon
#endif	// __MSG_SUPPORT_ICON_MENU__


#ifdef __3D_MESSAGE_BOX__
const static u32 Outbox3DIcon[2/*bIsMMS*/][MCA_E_MSG_SIM_STATUS_TOTAL]=    
{
    /*SMS*/ {MSGSTATUS_3D_SMS_IMG_ICON_OUTBOX_UNKNOW, IMG_NULL_ID, MSGSTATUS_3D_SMS_IMG_DUAL_OUTBOX_MASTER, MSGSTATUS_3D_SMS_IMG_DUAL_OUTBOX_SLAVE},
    /*MMS*/ {MSGSTATUS_3D_MMS_IMG_ICON_OUTBOX_UNKNOW, IMG_NULL_ID, MSGSTATUS_3D_MMS_IMG_DUAL_OUTBOX_MASTER, MSGSTATUS_3D_MMS_IMG_DUAL_OUTBOX_SLAVE}
};

const static u32 Sentbox3DIcon[2/*bIsMMS*/][MCA_E_MSG_SIM_STATUS_TOTAL]=    
{
    /*SMS*/ {MSGSTATUS_3D_SMS_IMG_ICON_SENT_UNKNOW,   IMG_NULL_ID,   MSGSTATUS_3D_SMS_IMG_DUAL_SENT_MASTER,   MSGSTATUS_3D_SMS_IMG_DUAL_SENT_SLAVE},
    /*MMS*/ {MSGSTATUS_3D_MMS_IMG_ICON_SENT_UNKNOW,   IMG_NULL_ID,   MSGSTATUS_3D_MMS_IMG_DUAL_SENT_MASTER,   MSGSTATUS_3D_MMS_IMG_DUAL_SENT_SLAVE}
};

const static u32 Inbox3DIcon[MCA_E_MSG_TYPE_INBOX_TOTAL][2/*bRead*/][2/*bComplete*/][MCA_E_MSG_SIM_STATUS_TOTAL]=
{
    /*SMS*/ 
    {
        /*Unread*/
        {
            /*InComplete*/
            {MSGSTATUS_3D_SMS_IMG_ICON_UNREAD_INCOMPLETE_UNKNOW, IMG_NULL_ID, MSGSTATUS_3D_SMS_IMG_DUAL_UNREAD_INCOMPLETE_MASTER,  MSGSTATUS_3D_SMS_IMG_DUAL_UNREAD_INCOMPLETE_SLAVE},

                /*Complete*/
            {MSGSTATUS_3D_SMS_IMG_ICON_UNREAD_UNKNOW,            IMG_NULL_ID,            MSGSTATUS_3D_SMS_IMG_DUAL_UNREAD_MASTER,             MSGSTATUS_3D_SMS_IMG_DUAL_UNREAD_SLAVE},
        },

        /*Read*/
        {
            /*InComplete*/
            {MSGSTATUS_3D_SMS_IMG_ICON_READ_INCOMPLETE_UNKNOW,   IMG_NULL_ID,   MSGSTATUS_3D_SMS_IMG_DUAL_READ_INCOMPLETE_MASTER,    MSGSTATUS_3D_SMS_IMG_DUAL_READ_INCOMPLETE_SLAVE},

                /*Complete*/
            {MSGSTATUS_3D_SMS_IMG_ICON_READ_UNKNOW,              IMG_NULL_ID,              MSGSTATUS_3D_SMS_IMG_DUAL_READ_MASTER,               MSGSTATUS_3D_SMS_IMG_DUAL_READ_SLAVE},
        },
    },

    /*MMS*/ 
    {
        /*Unread*/
        {
            /*UnRetrieved*/
            {MSGSTATUS_3D_MMS_IMG_ICON_UNREAD_UNRETRIEVED_UNKNOW, IMG_NULL_ID, MSGSTATUS_3D_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_MASTER,  MSGSTATUS_3D_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_SLAVE},

                /*Retrieved*/
            {MSGSTATUS_3D_MMS_IMG_ICON_UNREAD_UNKNOW,            IMG_NULL_ID,            MSGSTATUS_3D_MMS_IMG_DUAL_UNREAD_MASTER,             MSGSTATUS_3D_MMS_IMG_DUAL_UNREAD_SLAVE},
        },

        /*Read*/
        {
            /*UnRetrieved: Won't let user to read the unretrieved MMS, so treat as unread unretrieved*/ 
            {MSGSTATUS_3D_MMS_IMG_ICON_UNREAD_UNRETRIEVED_UNKNOW, IMG_NULL_ID,   MSGSTATUS_3D_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_MASTER, MSGSTATUS_3D_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_SLAVE},

                /*Retrieved*/
            {MSGSTATUS_3D_MMS_IMG_ICON_READ_UNKNOW,              IMG_NULL_ID,              MSGSTATUS_3D_MMS_IMG_DUAL_READ_MASTER,               MSGSTATUS_3D_MMS_IMG_DUAL_READ_SLAVE},
        },
    },
};
#endif


typedef enum
{
/* MMS */
    MCA_E_MMS_IMG_DRAFT,
    MCA_E_MMS_IMG_DRAFT_SEND_FAIL,
    MCA_E_MMS_IMG_DUAL_OUTBOX_MASTER,
    MCA_E_MMS_IMG_DUAL_OUTBOX_SLAVE,
    MCA_E_MMS_IMG_DUAL_READ_MASTER,
    MCA_E_MMS_IMG_DUAL_READ_SLAVE,
    MCA_E_MMS_IMG_DUAL_SENT_MASTER,
    MCA_E_MMS_IMG_DUAL_SENT_SLAVE,
    MCA_E_MMS_IMG_DUAL_UNREAD_MASTER,
    MCA_E_MMS_IMG_DUAL_UNREAD_SLAVE,
    MCA_E_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_MASTER,
    MCA_E_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_SLAVE,
    MCA_E_MMS_IMG_ICON_OUTBOX,
    MCA_E_MMS_IMG_ICON_READ,
    MCA_E_MMS_IMG_ICON_SENT,
    MCA_E_MMS_IMG_ICON_UNREAD,
    MCA_E_MMS_IMG_ICON_UNREAD_UNRETRIEVED,
/* SMS */
    MCA_E_SMS_IMG_DRAFT,
    MCA_E_SMS_IMG_DRAFT_SEND_FAIL,
    MCA_E_SMS_IMG_DUAL_DRAFT_MASTER,
    MCA_E_SMS_IMG_DUAL_DRAFT_SLAVE,
    MCA_E_SMS_IMG_DUAL_OUTBOX_MASTER,
    MCA_E_SMS_IMG_DUAL_OUTBOX_SLAVE,
    MCA_E_SMS_IMG_DUAL_READ_INCOMPLETE_MASTER,
    MCA_E_SMS_IMG_DUAL_READ_INCOMPLETE_SLAVE,
    MCA_E_SMS_IMG_DUAL_READ_MASTER,
    MCA_E_SMS_IMG_DUAL_READ_SLAVE,
    MCA_E_SMS_IMG_DUAL_SENT_MASTER,
    MCA_E_SMS_IMG_DUAL_SENT_SLAVE,
    MCA_E_SMS_IMG_DUAL_UNREAD_INCOMPLETE_MASTER,
    MCA_E_SMS_IMG_DUAL_UNREAD_INCOMPLETE_SLAVE,
    MCA_E_SMS_IMG_DUAL_UNREAD_MASTER,
    MCA_E_SMS_IMG_DUAL_UNREAD_SLAVE,
    MCA_E_SMS_IMG_ICON_DRAFT_SIM,
    MCA_E_SMS_IMG_ICON_OUTBOX,
    MCA_E_SMS_IMG_ICON_READ,
    MCA_E_SMS_IMG_ICON_READ_INCOMPLETE,
    MCA_E_SMS_IMG_ICON_READ_SIM,
    MCA_E_SMS_IMG_ICON_READ_SIM_INCOMPLETE,
    MCA_E_SMS_IMG_ICON_SENT,
    MCA_E_SMS_IMG_ICON_SENT_SIM,
    MCA_E_SMS_IMG_ICON_UNREAD,
    MCA_E_SMS_IMG_ICON_UNREAD_INCOMPLETE,
    MCA_E_SMS_IMG_ICON_UNREAD_SIM,
    MCA_E_SMS_IMG_ICON_UNREAD_SIM_INCOMPLETE,
/* CB */
    MCA_E_SMS_IMG_ICON_CB,
    MCA_E_SMS_IMG_ICON_CB_UNREAD,
/* WAP PUSH */
#ifdef __MMI_SMS_WAPPUSH__
    MCA_E_SMS_IMG_ICON_WAP_PUSH_READ,
    MCA_E_SMS_IMG_ICON_WAP_PUSH_UNREAD,
#endif
/* OTAP */
#ifdef __WAP_MMI_OTA_PROV__
    MCA_E_SMS_IMG_ICON_OTAP_READ,
    MCA_E_SMS_IMG_ICON_OTAP_SIM1_READ,
    MCA_E_SMS_IMG_ICON_OTAP_SIM1_UNREAD,
    MCA_E_SMS_IMG_ICON_OTAP_SIM2_READ,
    MCA_E_SMS_IMG_ICON_OTAP_SIM2_UNREAD,
    MCA_E_SMS_IMG_ICON_OTAP_UNREAD, 
#endif
    MCA_E_OVERLAY_IMAGE_TOTAL
} McaOverlayImage_e;

const static WdgOverlayImageDataID_t McaOverlayImageDataID[MCA_E_OVERLAY_IMAGE_TOTAL] = {
/* MMS */
// MCA_E_MMS_IMG_DRAFT
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), MMS_IMG_DRAFT},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DRAFT_SEND_FAIL
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), MMS_IMG_DRAFT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), SMS_IMG_SEND_FAIL},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_OUTBOX_MASTER
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_MIDDLE), SMS_IMG_OUTBOX_SEND},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_TOP   ), MMS_IMG_MMS},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_OUTBOX_SLAVE
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_MIDDLE), SMS_IMG_OUTBOX_SEND},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_TOP   ), MMS_IMG_MMS},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_READ_MASTER
{ SMS_IMG_ICON_READ, {
  {(WdgAlignment_e)(ALIGN_H_CENTER| ALIGN_V_MIDDLE), MMS_IMG_MMS},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_READ_SLAVE
{ SMS_IMG_ICON_READ, {
  {(WdgAlignment_e)(ALIGN_H_CENTER| ALIGN_V_MIDDLE), MMS_IMG_MMS},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_SENT_MASTER
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_TOP   ), MMS_IMG_SENT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_SENT_SLAVE
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_TOP   ), MMS_IMG_SENT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_UNREAD_MASTER
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_MIDDLE), MMS_IMG_SENT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_UNREAD_SLAVE
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_MIDDLE), MMS_IMG_SENT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_MASTER
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), MMS_IMG_UNRETRIEVED},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_SLAVE
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), MMS_IMG_UNRETRIEVED},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_ICON_OUTBOX
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_OUTBOX},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_TOP   ), MMS_IMG_SENT},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_ICON_READ
{ SMS_IMG_ICON_READ, {
  {(WdgAlignment_e)(ALIGN_H_CENTER| ALIGN_V_MIDDLE), MMS_IMG_MMS},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_ICON_SENT
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_TOP   ), MMS_IMG_SENT},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_ICON_UNREAD
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_MIDDLE), MMS_IMG_SENT},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_MMS_IMG_ICON_UNREAD_UNRETRIEVED
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), MMS_IMG_UNRETRIEVED},
  {(WdgAlignment_e)0, 0},
}},

/* SMS */
// MCA_E_SMS_IMG_DRAFT
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_DRAFT},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DRAFT_SEND_FAIL
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_DRAFT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), SMS_IMG_SEND_FAIL},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_DRAFT_MASTER
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_DRAFT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_DRAFT_SLAVE
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_DRAFT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_OUTBOX_MASTER
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_OUTBOX_SEND},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_OUTBOX_SLAVE
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_OUTBOX_SEND},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_READ_INCOMPLETE_MASTER
{ SMS_IMG_ICON_READ_INCOMPLETE, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_READ_INCOMPLETE_SLAVE
{ SMS_IMG_ICON_READ_INCOMPLETE, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_READ_MASTER
{ SMS_IMG_ICON_READ, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_READ_SLAVE
{ SMS_IMG_ICON_READ, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_SENT_MASTER
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_SENT_SLAVE
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_UNREAD_INCOMPLETE_MASTER
{ SMS_IMG_ICON_UNREAD_INCOMPLETE, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_UNREAD_INCOMPLETE_SLAVE
{ SMS_IMG_ICON_UNREAD_INCOMPLETE, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_UNREAD_MASTER
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_DUAL_UNREAD_SLAVE
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_DRAFT_SIM
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_DRAFT},
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), SMS_IMG_ICON_SIM},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_OUTBOX
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_LEFT  | ALIGN_V_BOTTOM), SMS_IMG_OUTBOX},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_READ
{ SMS_IMG_ICON_READ, {
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_READ_INCOMPLETE
{ SMS_IMG_ICON_READ_INCOMPLETE, {
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_READ_SIM
{ SMS_IMG_ICON_READ, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), SMS_IMG_ICON_SIM},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_READ_SIM_INCOMPLETE
{ SMS_IMG_ICON_READ_INCOMPLETE, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), SMS_IMG_ICON_SIM},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_SENT
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_SENT_SIM
{ SMS_IMG_ICON_SENT, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), SMS_IMG_ICON_SIM},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_UNREAD
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_UNREAD_INCOMPLETE
{ SMS_IMG_ICON_UNREAD_INCOMPLETE, {
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_UNREAD_SIM
{ SMS_IMG_ICON_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), SMS_IMG_ICON_SIM},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_UNREAD_SIM_INCOMPLETE
{ SMS_IMG_ICON_UNREAD_INCOMPLETE, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), SMS_IMG_ICON_SIM},
  {(WdgAlignment_e)0, 0},
}},

/* CB */
// MCA_E_SMS_IMG_ICON_CB
{ SMS_IMG_ICON_CB, {
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_CB_UNREAD
{ SMS_IMG_ICON_CB_UNREAD, {
  {(WdgAlignment_e)0, 0},
}},

/* WAP PUSH */
#ifdef __MMI_SMS_WAPPUSH__
// MCA_E_SMS_IMG_ICON_WAP_PUSH_READ
{ SMS_IMG_ICON_WAP_PUSH_READ, {
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_WAP_PUSH_UNREAD
{ SMS_IMG_ICON_WAP_PUSH_UNREAD, {
  {(WdgAlignment_e)0, 0},
}},
#endif

/* OTAP */
#ifdef __WAP_MMI_OTA_PROV__
// MCA_E_SMS_IMG_ICON_OTAP_READ
{ SMS_IMG_ICON_OTAP_READ, {
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_OTAP_SIM1_READ
{ SMS_IMG_ICON_OTAP_READ, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_OTAP_SIM1_UNREAD
{ SMS_IMG_ICON_OTAP_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_OTAP_SIM2_READ
{ SMS_IMG_ICON_OTAP_READ, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM1},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_OTAP_SIM2_UNREAD
{ SMS_IMG_ICON_OTAP_UNREAD, {
  {(WdgAlignment_e)(ALIGN_H_RIGHT | ALIGN_V_BOTTOM), COMMON_LIST_IMG_SIM2},
  {(WdgAlignment_e)0, 0},
}},
// MCA_E_SMS_IMG_ICON_OTAP_UNREAD
{ SMS_IMG_ICON_OTAP_UNREAD, {
  {(WdgAlignment_e)0, 0},
}},
#endif
};

const static McaOverlayImage_e InboxIcon[MCA_E_MSG_TYPE_INBOX_TOTAL][2/*bRead*/][2/*bComplete*/][MCA_E_MSG_SIM_STATUS_TOTAL] =
{
    /*SMS*/
    {
        /*Unread*/
        {
            /*InComplete*/
            {MCA_E_SMS_IMG_ICON_UNREAD_INCOMPLETE,  MCA_E_SMS_IMG_ICON_UNREAD_INCOMPLETE,   MCA_E_SMS_IMG_DUAL_UNREAD_INCOMPLETE_MASTER,    MCA_E_SMS_IMG_DUAL_UNREAD_INCOMPLETE_SLAVE},

            /*Complete*/
            {MCA_E_SMS_IMG_ICON_UNREAD,             MCA_E_SMS_IMG_ICON_UNREAD,              MCA_E_SMS_IMG_DUAL_UNREAD_MASTER,               MCA_E_SMS_IMG_DUAL_UNREAD_SLAVE},
        },

        /*Read*/
        {
            /*InComplete*/
            {MCA_E_SMS_IMG_ICON_READ_INCOMPLETE,    MCA_E_SMS_IMG_ICON_READ_INCOMPLETE,     MCA_E_SMS_IMG_DUAL_READ_INCOMPLETE_MASTER,      MCA_E_SMS_IMG_DUAL_READ_INCOMPLETE_SLAVE},

            /*Complete*/
            {MCA_E_SMS_IMG_ICON_READ,               MCA_E_SMS_IMG_ICON_READ,                MCA_E_SMS_IMG_DUAL_READ_MASTER,                 MCA_E_SMS_IMG_DUAL_READ_SLAVE},
        },
    },

    /*MMS*/
    {
        /*Unread*/
        {
            /*UnRetrieved*/
            {MCA_E_MMS_IMG_ICON_UNREAD_UNRETRIEVED, MCA_E_MMS_IMG_ICON_UNREAD_UNRETRIEVED,  MCA_E_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_MASTER,   MCA_E_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_SLAVE},

            /*Retrieved*/
            {MCA_E_MMS_IMG_ICON_UNREAD,             MCA_E_MMS_IMG_ICON_UNREAD,              MCA_E_MMS_IMG_DUAL_UNREAD_MASTER,               MCA_E_MMS_IMG_DUAL_UNREAD_SLAVE},
        },

        /*Read*/
        {
            /*UnRetrieved: Won't let user to read the unretrieved MMS, so treat as unread unretrieved*/
            {MCA_E_MMS_IMG_ICON_UNREAD_UNRETRIEVED, MCA_E_MMS_IMG_ICON_UNREAD_UNRETRIEVED,  MCA_E_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_MASTER,   MCA_E_MMS_IMG_DUAL_UNREAD_UNRETRIEVED_SLAVE},

            /*Retrieved*/
            {MCA_E_MMS_IMG_ICON_READ,               MCA_E_MMS_IMG_ICON_READ,                MCA_E_MMS_IMG_DUAL_READ_MASTER,                 MCA_E_MMS_IMG_DUAL_READ_SLAVE},
        },
    },
};


/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/
MAE_Ret _McaInit(McaAppData_t *pThis, MAEEvent_t nEvt, u32 nHighlightedIndex);
void _McaResetStartData(McaAppData_t *pThis, MAE_EventId nEvt, MCA_Start_t *pData, boolean bInitReady, MAE_EventId *pEventID,  u32 *pParam1, u32 *pParam2);
MAE_Ret _McaInitialReady(McaAppData_t *pThis, u8 NewReadyFlag, MAEEvent_t nEvt);
void _McaInitialReadyActiveCheck(McaAppData_t *pThis);	// check which window to open

void _McaRelease(McaAppData_t *pThis);
//////////////////////////////////////////////////////////////////////////////
// [Dialog Related]
MAE_Ret _McaLoadWaitingDialog(McaAppData_t *pThis, MAE_WChar *pTitleText, boolean bRightKeyHandle);
MAE_Ret _McaCloseDialogWithGetBox(void *pThis, MAEEvent_t tEvt, u32 nParam1, u32 nParam2);
#if defined(__MMS_MMI_CDMMS__) && defined(__USER_FILE_DELETER__)
MAE_Ret _McaCloseDialogAndFileManagerDeleteApp(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#endif
void _McaStartEmbAPWithClsID(McaAppData_t *pThis, u32 nParam);
void _McaStartEmbAP(IBase *pObj, u32 Param);
//void _McaEmbAPMdlListener(void *pUsrData, ModelEvent_t *pMdlEvent);
void _McaFreeSVARecipientItem(void *pData, void *pOwner);
SVA_INIT_DATA_t *_McaInitViewerData(McaAppData_t *pThis, McaChangeMessage_t *pChangeAbility, McaMsgBoxItemData_t *pItemData);
void _McaVoicemailSettings(McaAppData_t *pThis);

void _McaSavedMsgTransfer(SMI_MsgHdr_t MsgData, void **ppOutData, void *pUserData);
u32 _McaGetSavedMsgNumFromVectorModel(IVectorModel *pVectorMdl);
void _McaMsgHeaderTransfer(SMI_MsgHdr_t MsgData, void **ppOutData, void *pUserData);
void _McaFreeItemData(void *pData, IBase *pOwner);

MAE_Ret _McaMergeSmsArrayModel(McaAppData_t *pThis, IArrayModel* pSim1ArrayMdl, IArrayModel* pSim2ArrayMdl);
void _McaUpdateMenuBySMINotify(McaAppData_t* pThis, MAE_EventId NotifyEvent, IArrayModel *pUpdateList);
McaBoxUpdateResult_e _McaUpdateSrcBoxMenu(McaAppData_t* pThis, MAE_EventId NotifyEvent, SMI_NotifyInfo_t *pNotifyInfo, IArrayModel *pUpdateArrayModel);
McaBoxUpdateResult_e _McaAddMsgInDesBoxMenu(McaAppData_t* pThis, MAE_EventId NotifyEvent, SMI_NotifyInfo_t *pNotifyInfo);
void _McaUpdateItemInMainMenu(McaAppData_t* pThis, MAE_EventId NotifyEvent, SMI_NotifyInfo_t *pNotifyInfo);

MAE_Ret _McaCopyMessageToPhone(McaAppData_t* pThis);
void _McaResetOperateData(McaAppData_t *pThis);
void _McaRemoveProgressPushResult(void* pData, boolean bDone, u32 TextLabelID);

// Invisible Status
MAE_Ret _McaInvisible(McaAppData_t *pThis);

void _McaUpdateMenuAt(IWidget *pMenuWdg, WdgMenuItemType_e eItemType, u32 nIndex, PfnWdgDynamicMenuGetDataPtr pfnMenuAdapterGet, McaAppData_t *pThis);

// window
//////////////////////////////////////////////////////////////////////////////
// [MainMenu Window]
MAE_Ret _McaCreateMainMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaDestroyMainMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaLoadMainMenuView(McaAppData_t *pThis, MainMenuWndData_t *pData);
//MAE_Ret _McaMainMenuUpdateItemData(McaAppData_t *pThis);
void _McaMainVectorItemFree(void *pData, void *pOwner);
//void _McaMainMenuAdapterGetItem (void **ppDataOut, void *pUserData, u16 nIndex);
void _McaMainMenuAdapterGetItem(WdgDynamicMenuItemPtr_t *pDataOut, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
//void _McaMainMenuItemFree(void *pData, IBase *pOwner);
void _McaMainMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);
MAE_Ret _McaMainMenuGetBoxInfo(McaAppData_t *pThis, u8 BoxMenuIdx, u32 *pTotal, u32* pRead, u32* pSending);
MAE_Ret _McaGetListParamByMenuItem(u8 MenuItem, SMI_LIST_PARAM *pListParam);
MAE_Ret _McaGetListParamByBox(e_MCA_MENU_BOX Box, SMI_LIST_PARAM *pListParam, boolean SearchMode);
MAE_Ret _McaGetMenuItemByBox(e_MCA_MENU_BOX Box, u32 *pMenuItem);
MAE_Ret _McaGetSIMListParamByBox(e_MCA_MENU_BOX Box, u8 SIM_Module, SMI_LIST_PARAM *pListParam);
void _McaDialVoiceMail(McaAppData_t* pThis);
//////////////////////////////////////////////////////////////////////////////
// [NewMsgMenu Window]
MAE_Ret _McaCreateNewMsgMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaDestroyNewMsgMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaLoadNewMsgMenuView(McaAppData_t *pThis, NewMsgMenuWndData_t *pData);
//////////////////////////////////////////////////////////////////////////////
// [BoxListMenu Window]
MAE_Ret _McaCreateBoxListMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaShowBoxListMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaDestroyBoxListMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaSetBoxListMenuView(McaAppData_t *pThis, u32 nViewID, ListMenuWndData_t *pData);
MAE_Ret _McaLoadBoxListMenuView(McaAppData_t *pThis, u32 nViewID, ListMenuWndData_t *pData);
MAE_Ret _McaBoxListMenuGetList(McaAppData_t *pThis, SMI_MsgID_t MsgID, u32 *pHighlightIdx, boolean bSearchMode);
void _McaBoxListMenuGetListAndShowList(McaAppData_t *pThis, MAE_EventId nEvt, u32 nParam);
boolean _HandleKeyPressBoxListMenu(McaAppData_t *pThis, u32 nParam1, u32 nParam2);
void _McaBoxListMenuAdapterGetItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void _McaBoxListMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
void _McaBoxListMenuTabIconFree(void *pData, IBase *pOwner);
void _McaBoxListMenuUpdateTabIcon(McaAppData_t *pThis, IWidget *pTabWdg);
void _McaBoxListMenuBoxArrayMdlListener (void *pUsrData, ModelEvent_t *pMdlEvent);
MAE_Ret _McaBoxListMenuGetTabAndMenuWdg (McaAppData_t *pThis, IWidget **ppMenuWdg, IWidget **ppTabWidget);
void _McaBoxListMenuBoxItemFree (void *pData, IBase *pOwner);
MAE_Ret _McaBoxListMenuSetMarkedNumOnTitle(IWidget *pMenuWdg, IWidget *pTitleWdg);
void _McaBoxListMenuExit(McaAppData_t *pThis);
MAE_Ret _McaGetBoxByLocation(SMI_MsgLocation_e pMsgLocation, e_MCA_MENU_BOX* BoxType);
void _McaGetBoxMenuIdx(IArrayModel* pBoxArrayModel, SMI_MsgID_t MsgID, u32* pHighlightIdx);
void _McaCreateMsgIcon( McaAppData_t *pThis, McaMsgBoxItemData_t *pItemData, u8 *pIMSI, IImage **pImage );
MAE_Ret _McaGetSIMStatusByIMSI(McaAppData_t *pThis, u8 *pIMSI, McaMsgSimStatus_e *pSIMStatus);
MAE_Ret _McaBoxMarkSelectItemList(McaAppData_t *pThis);
#ifdef __MMI_SMS_EXPORT__
MAE_Ret _McaExportMarkSelectItemList(McaAppData_t *pThis);
#endif

#ifdef __MMI_SMS_CHAT__
//////////////////////////////////////////////////////////////////////////////
// [SMSChat Window]
void _McaSMSChatListMenuGetListAndShowList(McaAppData_t *pThis, MAE_EventId nEvt, u32 nParam);
MAE_Ret _McaSMSChatListMenuGetList(McaAppData_t *pThis, SMI_MsgID_t MsgID, u32 *pHighlightIdx);


/************************************************************************/
/* Mca SMS Chat Window Handle                                           */
/************************************************************************/
MAE_Ret McaChatListMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaChatListOptMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaChatItemMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaChatItemOptMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

MAE_Ret _McaCreateChatListMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaShowChatListMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaDestroyChatListMenuWnd(void *pWndHandle, void *pWndData);

MAE_Ret _McaCreateChatListOptMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaShowChatListOptMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaDestroyChatListOptMenuWnd(void *pWndHandle, void *pWndData);

MAE_Ret _McaCreateChatItemMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaShowChatItemMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaDestroyChatItemMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaSetChatItemMenuWnd(void *pWndHandle, void *pWndData);

MAE_Ret _McaCreateChatItemOptMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaShowChatItemOptMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaDestroyChatItemOptMenuWnd(void *pWndHandle, void *pWndData);

/************************************************************************/
/* Mca SMS Chat Adaptget Function                                       */
/************************************************************************/
void _McaChatListMenuAdapterGetItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void _McaChatListMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);

/************************************************************************/
/* Mca SMS Chat Load Window Function                                    */
/************************************************************************/
MAE_Ret _McaLoadChatListMenuView(McaAppData_t *pThis, ChatListMenuWndData_t *pData);
MAE_Ret _McaLoadChatListOptMenuView(McaAppData_t *pThis, ChatListOptMenuWndData_t *pData, u32 nOptMenuID);
MAE_Ret _McaLoadChatItemMenuView(McaAppData_t *pThis, ChatItemMenuWndData_t *pData);
MAE_Ret _McaLoadChatItemOptMenuView(McaAppData_t *pThis, ChatItemOptMenuWndData_t *pData, u32 nOptMenuID);

/************************************************************************/
/* MCA SMS Chat List Menu Callback Function                             */
/************************************************************************/
void McaChatListMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaChatListMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaChatListMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void McaChatListMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaChatListMenuMarkedNumberChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);

/************************************************************************/
/* MCA SMS Chat List Option Menu Callback Function                      */
/************************************************************************/
void McaChatListOptMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaChatListOptMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaChatListOptMenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void McaMarkChatOptMenuSelectCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaMarkChatOptMenuSoftkeyActCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/************************************************************************/
/* MCA SMS Chat Item Menu Callback Function                             */
/************************************************************************/

/************************************************************************/
/* MCA SMS Chat Item Menu Option Menu Callback Function                 */
/************************************************************************/
void McaChatItemOptMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaChatItemOptMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaChatItemOptMenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);


/************************************************************************/
/* MCA SMS Chat Update Option Menu                                      */
/************************************************************************/
void _McaChatListOptUpdateMenu(McaAppData_t* pThis, IWidget *pMenuWdg, McaOptionMenuStyle_e eOptMenuStyle);
void _McaChatItemOptUpdateMenu(McaAppData_t* pThis, IWidget *pMenuWdg, McaOptionMenuStyle_e eOptMenuStyle);

void _McaChatListMenuExit(McaAppData_t *pThis);

void _McaFreeSMSChatItem(void* pData, IBase* pOwner);
void _McaChatArrayMdlListener (void *pUsrData, ModelEvent_t *pMdlEvent);

/************************************************************************/
/* MCA SMS Chat Get Chat List Function                                  */
/************************************************************************/
MAE_Ret _McaMergeSMSChatArrayModel(McaAppData_t *pThis, IArrayModel* pSim1ArrayMdl, IArrayModel* pSim2ArrayMdl);
MAE_Ret _McaSortSMSChatList(McaAppData_t *pThis);
MAE_Ret _McaCreateSMSChatList(McaAppData_t *pThis);
MAE_Ret _McaGetPhbSortedIdx(McaAppData_t *pThis, SMI_MsgID_t MsgID, SMI_MsgLocation_e eLoc, SMS_MsgRecipAddr *pRecipAddr, u16 *pPhySortedIdx);

/************************************************************************/
/* MCA SMS Chat Related Function                                        */
/************************************************************************/
void _McaCall(McaAppData_t *pThis, u32 param1, u32 param2);
void _McaChatItemOptCopyToSim(McaAppData_t* pThis, u32 nParam1);
void _McaChatMarkOptUpdateMenu (McaAppData_t* pThis, IWidget *pMenuWdg);
void _McaUpdateChatBySMINotify(McaAppData_t* pThis, MAE_EventId NotifyEvent, IArrayModel *pUpdateList);
void _McaUpdateChatItemMenu(McaAppData_t* pThis, boolean bNeedGetList);
void _McaChatItemUpdateIncommingItem(McaAppData_t *pThis, ChatItemMenuWndData_t *pData, MAE_WChar* pMsgCnt, SMI_TimeStamp_t time, u32 nIndex, boolean bMarkMode);
void _McaChatItemUpdateSentItem(McaAppData_t *pThis, ChatItemMenuWndData_t *pData, MAE_WChar* pMsgCnt, SMI_TimeStamp_t time, u32 nIndex, boolean bMarkMode);
void _McaChatItemUpdateDateItem(McaAppData_t *pThis, ChatItemMenuWndData_t *pData, MCA_Msg_Chat_ItemData_t *pItemData, MAE_DateTime_t time, u32 nIndex);

MAE_Ret _McaChatItemOptMenuCopyToPhone(McaAppData_t* pThis);
MAE_Ret _McaChatItemOptMenuReadMessage(McaAppData_t *pThis);
MAE_Ret _McaChatResumeStartSEA(McaAppData_t *pThis, SEA_StartType_e StartType, McaMsgBoxItemData_t *pBoxItem);
MAE_Ret _McaChatMenuGetMenuWdg (McaAppData_t *pThis, IWidget **ppMenuWdg);
MAE_Ret _McaChatItemMenuGetMenuWdg (McaAppData_t *pThis, IWidget **ppMenuWdg);
MAE_Ret _McaCopyChatMessageToPhone(McaAppData_t* pThis);

SVA_INIT_DATA_t *_McaInitChatViewerData(McaAppData_t *pThis, McaChangeMessage_t *pChangeAbility, McaMsgBoxItemData_t *pItemData);

u32 TextBubbleGetTextWidth(McaAppData_t *pThis, MAE_WChar* pMsgCnt);
static boolean _McaChatEditorHandleEvent(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
void _McaChatEditorEventHandlerFree( McaAppData_t *pThis);
static boolean _McaChatScrollBarHandleEvent(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
void _McaChatScrollBarEventHandlerFree( McaAppData_t *pThis);
MAE_Ret _McaChatItemFocusOnEditor(McaAppData_t *pThis,MAE_EventId evt, u32 keycode);
void _McaChatItemUnFocusEditor(McaAppData_t *pThis);
void _McaChatItemEditorTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
boolean _HandleKeyPressChatItemView(McaAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);
void _McaChatItemMoveFocusedItem(McaAppData_t *pThis, u32 nFocusedIndex, boolean bIsFocus);
void _McaChatItemGetMsgItem(McaAppData_t *pThis);
void _McaHandlerSmiRetrvMsgDataFromSIMCnf(void *pInstance,SMI_MsgMgrStatus_e eStatus,SMI_SIMData_t *pSIMData);
MAE_Ret _McaChatItemSendMsg(McaAppData_t* pThis, TextInfo tTextInfo);
MAE_Ret _McaChatItemSaveMsg(McaAppData_t *pThis, SMI_MsgLocation_e eLocation, MAE_WChar *pContent, MAE_WChar *pAddr, SMI_MsgID_t *msgID );
void _McaChatItemClickBubbleCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nValue, IWidget *pWidget);
void _McaChatItemTouchBubbleCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nValue, IWidget *pWidget);
void _McaChatItemTouchButtonCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void _McaChatItemMarkItem(McaAppData_t* pThis, u32 nMarkIndex, boolean bMark);
#ifndef __FADE_OUT_SCROLLBAR__
//static void _McaChatViewportScrollChangeCb (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollData_t *pScrollData, IWidget *pIWidget);
MAE_Ret _McaChatItemSetScrollChangeView(McaAppData_t *pThis, u32 nNewViewWidth);
static void _McaChatMainPropContainerViewListener(void *pUserData, ModelEvent_t *pMdlEvent);
#endif
Rect_t _McaChatItemGetFocusedItemPos(McaAppData_t *pThis, u32 nIndex);
MAE_Ret _McaChatItemForward(McaAppData_t* pThis);
void _McaChatItemSetDateItem(ChatItemMenuWndData_t *pData, ChatBubbleDateWdgList_t *ptWdgList);
void _McaChatItemSetIncommingItem(McaAppData_t *pThis, ChatItemMenuWndData_t *pData, MAE_WChar* pMsgCnt, SMI_TimeStamp_t time, u32 nIndex, boolean bMarkMode);
void _McaChatItemSetSentItem(McaAppData_t *pThis, ChatItemMenuWndData_t *pData, MAE_WChar* pMsgCnt, SMI_TimeStamp_t time, u32 nIndex, boolean bMarkMode);
MAE_Ret _McaChatItemSetMarkModeView(McaAppData_t *pThis);
#ifdef __TOUCH_SCREEN_MMI__
void _McaChatItemLoadMsgButtonCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nValue, IWidget *pWidget);
#endif
void _McaChatItemDeleteAllItemView(McaAppData_t *pThis);
u32 _McaChatItemGetUnReadMsgNum(MCA_Msg_Chat_ItemData_t *pChatItem);
u32 _McaGetChatMenuHighlightedIndex(IArrayModel* pChatArrayModel, const MAE_WChar* pContact);

/************************************************************************/
/* Chat Menu Update Function                                            */
/************************************************************************/
McaBoxUpdateResult_e _McaUpdateSrcChatMenu(McaAppData_t* pThis, MAE_EventId NotifyEvent, SMI_NotifyInfo_t *pNotifyInfo);
McaBoxUpdateResult_e _McaAddMsgInDesChatMenu(McaAppData_t* pThis, MAE_EventId NotifyEvent, SMI_NotifyInfo_t *pNotifyInfo);


/************************************************************************/
/* Delete Chat Function                                                 */
/************************************************************************/
MAE_Ret _McaOptMenuDeleteChatMessage(McaAppData_t* pThis);
MAE_Ret _McaOptMenuDeleteChatItemMessage(McaAppData_t* pThis, boolean bIsDeleteAll);

void _McaOptMenuDeleteChatMessageConfirm(McaAppData_t* pThis);
boolean McaDeleteChatMessageConfirmCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void _McaChatOptMenuDeleteProgress(McaAppData_t* pThis);
MAE_Ret _McaDeleteChatMessage(McaAppData_t *pThis);
MAE_Ret _McaChatMarkSelectItemList(McaAppData_t *pThis, SMI_MsgLocation_e eMsgLocation);

void McaMsgMgrSrvDelChatMsgByIdCnfCB(void *pApplet, SMI_MsgMgrStatus_e Result);
u32 _McaGetChatMarkSelectItemNum(McaAppData_t *pThis);
void  _McaChatOperateMsgResult(McaAppData_t* pThis, SMI_MsgMgrStatus_e SMI_Result);

void McaChatMsgMgrSrvCmtUptMsgHdrCnfCB(void *pThis, SMI_MsgMgrStatus_e Result );
MAE_Ret McaSMSChatDialogCancelCB(void *pApplet, MAE_EventId nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _McaChatGetUnknownDateStr(MAE_WChar **ppDateStr);

#endif
////////////////////////

#ifdef __3D_MESSAGE_BOX__                 
static MAE_Ret mmi_MCA_Get3DMsgIcon(McaAppData_t *pThis, McaMsgBoxItemData_t *pItemData, u8 *pIMSI, u32 *pL1ImageID);
static void mmi_MCA_3DBoxMenuAdapterGetItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
static void mmi_MCA_3DBoxMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType);
#endif

#ifdef __3D_MESSAGE_BOX__
static void  mmi_MCA_BoxResumePostSelectCB(IBase *pObj, u32 Param);
static void mmi_MCA_BoxInfoFree(void *pData, IBase *pOwner);
static void mmi_MCA_SetGlBoxData(McaAppData_t *pThis, IWidget *pGlBoxListWdg);
static MAE_Ret MCA_GetContactNameAndImg(McaAppData_t *pThis, SMS_MsgRecipAddr *pAddr, u32 nContactStrLen, MAE_WChar **ppContact, IImage **ppImg);
static void  mmi_MCA_BoxResumePostSelectCB(IBase *pObj, u32 Param);
static void McaBoxListGlBoxListViewModelChangedCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, BoxChangeData_t *ptBoxData, void *pReserve);
#endif
static MAE_Ret MCA_GetContactName(McaAppData_t *pThis, SMS_MsgRecipAddr *pAddr, u32 nContactStrLen, MAE_WChar **ppContact);
static void mmi_MCA_UpdateBoxTitle(McaAppData_t* pThis, IWidget *pTitleWdg);
//////////////////////////////////////////////////////////////////////////////
// [BoxOptMenu Window]
MAE_Ret _McaCreateBoxOptMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaDestroyBoxOptMenuWnd(void *pWndHandle, void *pWndData);
//boolean _HandleKeyPressOptMenu(McaAppData_t *pThis, u32 nParam1, u32 nParam2);
MAE_Ret _McaLoadBoxOptMenuView(McaAppData_t *pThis, OptMenuWndData_t *pData, u32 nOptMenuID);
//void _McaBoxMarkOptUpdateMenu (McaAppData_t* pThis, IMenuModel *pMenuModel);
void _McaBoxMarkOptUpdateMenu (McaAppData_t* pThis, IWidget *pMenuWdg);
//void _McaBoxOptUpdateMenu (McaAppData_t* pThis, IMenuModel *pMenuModel, McaOptionMenuStyle_e eOptMenuStyle);
void _McaBoxOptUpdateMenu (McaAppData_t* pThis, IWidget *pMenuWdg, McaOptionMenuStyle_e eOptMenuStyle);
//void _McaUpdateMenuModelItemFlag (IMenuModel* pModel, u32 MenuID, u32 ItemFlag);
void _McaUpdateMenuItemFlag (IWidget *pMenuWdg, u32 nItemId, u32 ItemFlag);
MAE_Ret _McaBoxResumeStartSEA(McaAppData_t *pThis, SEA_StartType_e StartType, McaMsgBoxItemData_t *pBoxItem);
MAE_Ret _McaOptMenuReadMessage(McaAppData_t *pThis);
MAE_Ret _McaDeleteMessage(McaAppData_t *pThis);
MAE_Ret _McaOptMenuDeleteMessage(McaAppData_t* pThis);
void _McaOptMenuDeleteMessageConfirm(McaAppData_t* pThis);
MAE_Ret _McaOptMenuCopyToPhone(McaAppData_t* pThis);
void _McaOptMenuDeleteProgress(McaAppData_t* pThis);
void _McaOptMenuCopyToSim(McaAppData_t* pThis, u32 nParam1);
void _McaOptMenuSend(McaAppData_t *pThis);
void _McaOptMenuMove(McaAppData_t *pThis);
MAE_Ret _McaMoveMessageToDraft(McaAppData_t *pThis);
#ifdef __MMI_SMS_EXPORT__
MAE_Ret _McaOptExportSMS(McaAppData_t* pThis);
MAE_Ret _McaExportSMS(McaAppData_t *pThis);
static MAE_Ret _McaExportPhoneSMS(McaAppData_t *pThis, McaOperateMsg_t Msg);
static MAE_Ret _McaExportSIMSMS(McaAppData_t *pThis, void *pData, u32 dataLen, MAE_WChar *pFileName);
void _McaExportSMSDoneCB(void *data);
void _McaExportSMSDoneAndShowList(McaAppData_t* pThis);
void  _McaBoxOperateExportResult(McaAppData_t* pThis, SMI_MsgMgrStatus_e SMI_Result);
#endif
void _McaOptMenuOpDenial(McaAppData_t *pThis);
boolean _McaDeleteNextSIMOperation(McaAppData_t *pThis, u32 *pOpFailTextID);
void  _McaBoxOperateMsgResult(McaAppData_t* pThis, SMI_MsgMgrStatus_e SMI_Result);

//////////////////////////////////////////////////////////////////////////////
// [SettingMenu Window]
MAE_Ret _McaCreateSettingMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaDestroySettingMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaLoadSettingMenuView(McaAppData_t *pThis, SettingMenuWndData_t *pData);
//////////////////////////////////////////////////////////////////////////////
// [MemStatus Window]
MAE_Ret _McaCreateMemStatusWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
boolean _HandleKeyPressMemStatus(McaAppData_t *pThis, u32 nParam1, u32 nParam2);
MAE_Ret _McaLoadMemStatusView(McaAppData_t *pThis, MemStatusWndData_t *pData);
MAE_Ret _McaSetMemStatusView(McaAppData_t *pThis, MemStatusWndData_t *pData);
//MAE_Ret _McaUpdateMemStatusView(McaAppData_t *pThis, IView *pView, u16 WidgetID, u32 nData, u32 nTotal, u32 nMaxDataChar, MAE_WChar *pUnit);
MAE_Ret _McaUpdateMemStatusView(McaAppData_t *pThis, McaMemStatusWdgList_t *pWdgList, IWidget *pTextWdg, u32 nData, u32 nTotal, McaMsgStorageSizeUnitType_e eSizeUnitType, u32 nMaxDataChar, MAE_WChar *pUnit);
//////////////////////////////////////////////////////////////////////////////
// [DualSimMenu Window]
MAE_Ret _McaCreateDualSimMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaLoadDualSimMenuView(McaAppData_t *pThis, DualSimMenuWndData_t *pData);
//////////////////////////////////////////////////////////////////////////////
// [TemplateMenu Window]
MAE_Ret _McaCreateTemplateMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);

//////////////////////////////////////////////////////////////////////////////
// [ViewMsgDetail Window]
MAE_Ret _McaCreateViewMsgDetailWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaShowViewMsgDetailWnd(void *pWndHandle, void *pWndData);
boolean _HandleKeyPressViewMsgDetail(McaAppData_t *pThis, u32 nParam1, u32 nParam2);
MAE_Ret _McaLoadViewMsgDetailView(McaAppData_t *pThis, ViewMsgDetailWndData_t *pData, McaMsgBoxItemData_t *pMsgItemData, SMI_MsgHdr_t **ppMsgHd);

//////////////////////////////////////////////////////////////////////////////
// [Sorting]
static void _McaSortList(void* pObj);
static MAE_Ret _McaSortListByDate(McaAppData_t* pThis);
static MAE_Ret _McaSortListBySubject(McaAppData_t* pThis);
//static MAE_Ret _McaSortListByNumber(McaAppData_t* pThis);
static MAE_Ret _McaSortListByType(McaAppData_t *pThis);
static MAE_Ret _McaSortListByStorage(McaAppData_t *pThis);
static MAE_Ret _McaGetMsgIdxBySortMode(McaAppData_t *pThis, IArrayModel *pIBoxListMdl, McaMsgBoxItemData_t *pNewItem, McaMsgSortingType_e eType, u32 *pMsgIdx);
static MAE_Ret _McaGetMsgSubject(McaAppData_t* pThis, SMI_MsgID_t MsgID, SMI_MsgLocation_e eLoc, MAE_WChar** ppSubject);

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret McaConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret McaDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean McaStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean McaStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean McaKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean McaSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean McaResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean McaGetPropertyCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
// Timer callback function
MAE_Ret McaCloseDialogCB(void *pThis, MAEEvent_t tEvt, u32 nParam1, u32 nParam2);
// service callback function
void McaCbsSrvReadyNotifyCB(void *pThis);

void McaMsgMgrSrvOperationNotBusyNotifyCB(void *pThis);
void McaMsgMgrSrvUpdateHeaderNotifyCB(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvModifyMsgParamReqCB(void *pThis, SMI_MsgMgrStatus_e eResult);
void McaMsgMgrSrvDelMsgByIdCnfCB(void *pApplet, SMI_MsgMgrStatus_e Result);
void McaMsgMgrSrvCopySimMsgToPhoneCnfCB(void *pApplet, SMI_MsgMgrStatus_e eResult, SMI_SIMData_t *pSIMData );
void McaMsgMgrSrvCopyPhoneMsgToSimCnfCB(void *pThis, SMI_MsgMgrStatus_e eOpResult, SMI_MsgID_t nMsgID);
void McaMsgMgrSrvAddMsgNotifyCB(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvDelMsgNotifyCB(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvDelLocationNotifyCB(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvMoveMsgNotifyCB(McaAppData_t *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvAddMsgSortByTimeNotifyCB(void *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvCmtUptMsgHdrCnfCB(void *pThis, SMI_MsgMgrStatus_e Result );
void McaMsgMgrSrvUtilCancelCommitUpdateHeaderCB(void *pApplet, SMI_MsgMgrStatus_e Result);
#ifdef __MMI_SMS_EXPORT__
void McaMsgMgrSrvRetrvMsgDataFromSIMNotifyCB(void *pInstance,SMI_MsgMgrStatus_e eStatus,SMI_SIMData_t *pSIMData);
#endif
void McaSmsSrvReadyCB(void *pThis, COMMON_SIM_CARD_STATUS_e eSIMCardStatus);

void McaSimSrvInitAppFinishedIndCB(void *pThis, SIMSRV_INITAPP_TYPE_e eInitAppType );
void McaSimSrvActivateSIMCnfCB(McaAppData_t *pThis, SIMSRV_RESULT_e eResult, SIMSRV_SIM_ID_e eSIMID);

void McaMmsSrvMessageReSyncStartIndCB(void *pThis);
void McaMmsSrvMessageReSyncEndIndCB(void *pThis);
void McaMmsTransSrvGetSubjectReqCB(void *pApplet, MMI_GetMmsSubjectInfoCnf_t *pMmsGetSubjectInfoCnf);

/*
void McaMsgMgrSrvReadStatusNotifyCB(McaAppData_t *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvSentStatusNotifyCB(McaAppData_t *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvCompleteStatusNotifyCB(McaAppData_t *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
void McaMsgMgrSrvUpdateStatusNotifyCB(McaAppData_t *pThis, SMI_LIST_PARAM nListParam, IArrayModel *pArrayModel);
*/

void McaPhonebookReadyCB(void *pApplet);
void McaEvtCenterSrvStartDialogNotifyCB(void *pThis, EvtCenter_Dialog_Type_e eDialogType, u32 nMsgId);
void McaDateTickCB(void *pApplet);
void McaSysTimeChangeCB(void *pThis, MAE_DateTime_t *pLocalTime);
void McaSysTimeZoneChangeCB(void *pThis, MAE_TimeZone_e ePrimaryTimeZone);
static void _McaMarkOff(McaAppData_t *pThis);
// widget callback function
void McaMainMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaMainMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaNewMsgMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaNewMsgMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaBoxListMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaBoxListMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void McaBoxListMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaBoxListMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaBoxListMenuMarkedNumberChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
void McaBoxListMenuTabChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);
void McaMarkBoxOptMenuSelectCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaMarkBoxOptMenuSoftkeyActCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaBoxOptMenuSelectCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaBoxOptMenuSoftkeyActCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaBoxOptMenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __MMI_SMS_EXPORT__
void McaMarkOptMenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
//void McaOptMenuBackToLayer1CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaSettingMenuSelectCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaSettingMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaDualSimMenuSelectCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaDualSimMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#if defined(__MMS_MMI_CDMMS__) && defined(__USER_FILE_DELETER__)
void _McaOptSendDeleteFile(McaAppData_t *pThis);
static void _McaMmsListFilesGetOptionMenuCb(void *pUserData, u32 nFolderLevel, void *pFileInfo, u32 *pOptonMeneuItemNum, const WdgStaticMenuItem_t **pOptionMeneuItemList, PfnFileMgrOptMenuSelectCb *pfnSelectCb);
static void _McaMmsLaunchFileMangerGetVirtualVolumeListCb(void *pUserData, u32 *pNumber, const FileMgrVirtualVolumeItem_t **pVirtualVolumeList);
static void _McaMmsCommonLaunchFileMangerGetL1SoftkeyCb(void *pUserData, u32 nFileNumber, u32 *pnLSKVal, u32 *pnCSKVal, u32 *pnRSKVal, PfnFileMgrL1SoftKeySelectCb *pfnLiselectCb);
MAE_Ret _McaMmsLaunchFileMangerDeleteApp(McaAppData_t *pThis, FileMgrApp_FilterType_e nFilterType);
#endif
#ifdef __APP_MMI_PRIVATEPROTECT__ 
void _McaPrivateProtectStatusCB(void *pIApplet, PrivateProtectAuthResult_e eAuthResult);
#endif
#ifdef __SMS_SEND_FROM_BUFFER__
void McaBuffMessageAddedCB( void *pApplet, SMI_MsgID_t nMsgId );
void McaBuffMessageDeletedCB( void *pApplet, SMI_MsgID_t nMsgId );
void McaBuffMessageMsgFlagUpdatedCB( void *pApplet, SMI_MsgID_t nMsgId, SMI_MsgFlag eMsgFlag );
#endif /* __SMS_SEND_FROM_BUFFER__ */

// other callback function
MAE_Ret McaWaitingDialogCancelCB(void *pApplet, MAE_EventId nEvt, u32 nParm1, u32 nParm2);
boolean McaDeleteMessageConfirmCB(void *pApplet, u32 nEvt, u32 nParm1, u32 nParm2);
void McaOperationDelayCB(void *data);
// window
MAE_Ret McaMainMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaNewMsgMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaBoxListMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaOptMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaSettingMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaMemStatusWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaDualSimMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaTemplateMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaViewMsgDetailWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __MMI_SMS_SEARCH__	
MAE_Ret McaSearchBoxMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret McaSearchBoxListMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaLoadSearchBoxMenuView(McaAppData_t *pThis, SearchBoxMenuWndData_t *pData);
MAE_Ret _McaCreateSearchBoxMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaDestroySearchBoxMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaCreateSearchBoxListMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaLoadSearchBoxListMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _McaDestroySearchBoxListMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaShowSearchBoxListMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaSearchBoxCmpWithCnt(McaAppData_t *pThis);
void _McaSearchArrayDelayCB(void *data);
static MAE_Ret McaInitSearchListMenuData(McaAppData_t *pThis);
static void _McaStartSearch(McaAppData_t* pThis);
static void _McaStopSearch(McaAppData_t* pThis);
void McaSearchBoxMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaSearchBoxMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static boolean McaSearchListHandleEvent(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
void McaSearchListEventHandlerFree( McaAppData_t *pThis);
void _McaSearchListInputWdgTextChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
boolean _HandleKeyPressSearchList(McaAppData_t *pThis, u32 nParam1, u32 nParam2);
void _McaUpdateSearchListBySMINotify(McaAppData_t* pThis, MAE_EventId NotifyEvent, IArrayModel *pUpdateList);
static void _McaSearchSetTitleLayout(McaAppData_t* pThis);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
void _McaSetWdgLayout(HWIN hWin, IWidget *pWdg, Pos_t *pPos,WidgetSize_t *pSize);
#endif
#endif
#ifdef __SIM_NO_RSP_HANDLING__
void McaHandleSIMNoRspIndCB( McaAppData_t *pThis, u8 u8SimModule );
#endif

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
MAE_Ret McaSimMsgBoxMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaCreateSimMsgBoxMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaDestroySimMsgBoxMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaLoadSimMsgBoxMenuView(McaAppData_t *pThis, SimMsgBoxMenuWndData_t *pData);
void McaSimMsgBoxMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaSimMsgBoxMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret McaMainBoxMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaCreateMainBoxMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaShowMainBoxMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaDestroyMainBoxMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaLoadMainBoxMenuView(McaAppData_t *pThis, MainMenuWndData_t *pData);
MAE_Ret McaNewMsgBoxSelectMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaCreateNewMsgBoxSelectMenuWnd(void *pWndHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _McaDestroyNewMsgBoxSelectMenuWnd(void *pWndHandle, void *pWndData);
MAE_Ret _McaLoadNewMsgBoxSelectMenuView(McaAppData_t *pThis, NewMsgBoxSelectMenuWndData_t *pData);
void McaNewMsgBoxSelectMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void McaNewMsgBoxSelectMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _McaNewMsgBoxSelectMenuAdapterGetItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void _McaNewMsgBoxSelectMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);
#endif

#endif /* __MMI_MESSAGECENTERAPP_PRIV_H__ */

