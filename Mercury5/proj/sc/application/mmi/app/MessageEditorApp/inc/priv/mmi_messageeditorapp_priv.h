/**
* @file mmi_messageeditorapp_priv.h
*
*/
#ifndef __MMI_MESSAGEEDITORAPP_PRIV_H__
#define __MMI_MESSAGEEDITORAPP_PRIV_H__

#include "mmi_baseapplet.h"
#include "mmi_messageeditorapp.h"
#include "mmi_messageeditorapp_custom.h"

#include "mmi_common_sms.h"
#include "mmi_common_sim.h"
#include "mmi_common_storage_mgr.h"

#include "mmi_phbapp.h"
#include "mmi_calendarapp.h"

#include "mmi_srv_header.h"

#include "mmi_common_vtm.h"
#include "mmi_messageeditorapp_id.h"
#include "messageeditorapp_resource.h"

#include "mmi_mae_common_def.h"
#include "mmi_mae_helper.h"
#include "mmi_mae_input_common.h"

#define SEA_RECIPIENT_MULTI_FROM_PHONEBOOK
#define SEA_DIALOG_TIMER                            2000

enum
{
    SEA_Operation_None =0x0000,
    SEA_Operation_Init,
    SEA_Operation_CreatEditorForm,
    SEA_Operation_SaveConfirm,
    SEA_Operation_GetDrmRightsConfirm,    
    SEA_Operation_Convert,
    SEA_Operation_CreateMMSTextContentEditor,
    SEA_Operation_CreateMMSSubjectEditor,
    SEA_Operation_FullEditorSave,
    SEA_Operation_Send,
    SEA_Operation_SendConfirm, // to check if send without content
    SEA_Operation_Preview,
    SEA_Operation_Save,
    SEA_Operation_InsertTemplate,
    SEA_Operation_InsertVCard,
    SEA_Operation_InsertVCalendar,
    SEA_Operation_InsertImage,
    SEA_Operation_InsertAudio,
#ifdef __MMS_SUPPORT_PLAY_VIDEO__
    SEA_Operation_InsertVideo,
#endif
    SEA_Operation_InsertFile,
    SEA_Operation_InsertSlide,

    SEA_Operation_CreateRecipientDisplay,
    SEA_Operation_AddFromPhonebook,
    SEA_Operation_DeleteOneRecipient,
    SEA_Operation_DeleteConfirm,
    SEA_Operation_DeleteAllRecipients,
    SEA_Operation_EnterOneNumber,

    SEA_Operation_CreateObjectListDisplay,
    SEA_Operation_ObjectOperation_Open,
    SEA_Operation_ObjectOperation_Remove,
    SEA_Operation_ObjectListPlayMusic,
    SEA_Operation_ObjectListStopMusic,

    SEA_Operation_CreateSlideListDisplay,
    SEA_Operation_CreateSlideListOption,
    SEA_Operation_ChangeOrder,
    SEA_Operation_JumpTo,
    SEA_Operation_DeleteFile,
#ifdef __SMS_SEND_FROM_BUFFER__
    SEA_Operation_SendFromBufferConfirm,
#endif /* __SMS_SEND_FROM_BUFFER__ */
};
typedef u32 SEA_Operation_e;

/**************COMMON************************/

/* recipient list, number */
typedef struct SEA_Recipient_Info{
    u32 oldSize;                 //record the size of recipient before launching PB to check if recipients change after add from phonebook
    u32 RecipientLen;	         //must less then MMI_MMS_MAX_RECEIVE_LIST
    VectorClass_t* pIRecipients; //SEA_Recipient_t
}SEA_RecipientInfo_t;


typedef struct Recipient_View
{
  u32 nHighlightedRec;  					// the highlight index of list
  WidgetHandler_t inputWdgHandler; 			// input widget handler to check if input widget is focused
}SEA_RecipientView_t;

typedef struct  
{
	SEA_Operation_e eSlideListOperation;// used to distinguish jump to/change order
}SEA_SlideList_t;


typedef enum
{
   Unknow = 0,
   Send_Master,
   Send_Slave,
}SEA_SendMode_e;


enum
{
    SEA_SIMSTATUS_e_Active,
    SEA_SIMSTATUS_e_NoSIM,
    SEA_SIMSTATUS_e_InActive,
    SEA_SIMSTATUS_e_AirplaneMode
};
typedef u8 SEA_SIMStatus_e;


enum
{
    Disable_SK = 0,
    Enable_SK
};
typedef u8 SEA_UpdateSK_e;

enum
{
    SEA_EDITOR_TYPE_NONE,
    SEA_EDITOR_TYPE_SMS,
    SEA_EDITOR_TYPE_MMS_SUBJECT,
    SEA_EDITOR_TYPE_MMS_CONTENT,
};

typedef u8 SEA_InputType_e;

typedef struct MMSEditorWdgList
{
    IWidget *pMMS_TITLEAREA_TITLEWIDGET;
    IWidget *pMMS_TITLEAREA_SIZE_TEXTWIDGET;
    IWidget *pMMS_TITLEAREA_PAGESWITCH_PICKCONTAINER;
    IWidget *pMMS_PAGESWITCH_LEFT_ARROW_BUTTONWDG;
    IWidget *pMMS_PAGESWITCH_PAGE_TEXTWDG;
    IWidget *pMMS_PAGESWITCH_RIGHT_ARROW_BUTTONWDG;
    IWidget *pMMS_TITLEAREA_ATTACHMENT_ICON_IMAGEWDG;
    IWidget *pMMS_EDITORAREA_SCROLLBARWDG;
    IWidget *pMMS_EDITORAREA_VIEWPOINTWDG;
    IWidget *pMMS_EDITORAREA_PROPCONTAINER;
    IWidget *pMMS_EDITORAREA_TO_DISPLAY_WDG;
    IWidget *pMMS_EDITORAREA_CC_DISPLAY_WDG;
    IWidget *pMMS_EDITORAREA_BCC_DISPLAY_WDG;
    IWidget *pMMS_EDITORAREA_SUBJECT_DISPLAY_WDG;
    IWidget *pMMS_EDITORAREA_ICONLIST_PROPCONTAINER;
    IWidget *pMMS_EDITORAREA_AUDIO_ICON_IMAGEWDG;
    IWidget *pMMS_EDITORAREA_VIDEO_ICON_IMAGEWDG;
    IWidget *pMMS_EDITORAREA_INPUTWIDGET;
    IWidget *pMMS_EDITORAREA_IMAGE_CONTNR;
    IWidget *pMMS_EDITORAREA_IMAGE_IMGWDG;
}SEA_MmsEditorWdgList_t;

typedef struct MSA_RECIPIENTWDGList
{
    IWidget *pRECIPIENT_PROPCONTAINER;
    IWidget *pRECIPIENT_TITLEWIDGET;
    IWidget *pRECIPIENT_MENUWIDGET;
    IWidget *pRECIPIENT_EDITOR_ABSCONTAINER;
    IWidget *pRECIPIENT_EDITOR_BGIMGWDG;
    IWidget *pRECIPIENT_EDITOR_BUTTONWDG;
    IWidget *pRECIPIENT_INPUTWIDGET;
}SEA_RecipientWdgList_t;

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
typedef struct SmsSelectSimMsgMenuWndData_t_
{
	MenuWdgList_t tWdgList;
} SmsSelectSimMsgMenuWndData_t;
#endif

typedef struct Editor_View
{
   u32 currentPage; // sms : page; mms:slide
}SEA_EditorView_t;


enum
{
   SEA_SAVE_NONE         =   0,
   SEA_SAVE_SUCCESS      =0x01,
   SEA_SAVE_STORAGE_FULL =0x02,
   SEA_SAVE_UNKNOW_ERROR =0x04,
};
typedef u8 SEA_SaveResult_e;

typedef struct
{
    MAE_WChar *pReturnStr;
    MAE_Ret eResult;

} SEA_CalendarReturnData_t;
typedef struct
{
    MAE_WChar wStrName  [PHB_NAME_LEN+1];       /// Name
    MAE_WChar wStrNumber[PHB_EMAIL_LEN+1];     /// Number or Email

}SEA_PHBRecipientContent_t;
typedef struct
{
	PhoneBookContactFieldMask_e eMask;
	u32 uContactNum;
    SEA_PHBRecipientContent_t *pDetail;

}SEA_PHBRecipientData_t;

/*********************MMS*********************************/
enum
{
    SEA_MMS_GETDATA_READY_NONE      =0x00,
    SEA_MMS_GETDATA_READY_SLIDE     =0x01,
    SEA_MMS_GETDATA_READY_SUBJECT   =0x02,
    SEA_MMS_GETDATA_READY_ATTACHMENT=0x04,
    SEA_MMS_GETDATA_READY_RECIPIENT =0x08,

    SEA_MMS_GETDATA_READY =0x0F,
};

typedef u8 SEA_MmsGetDataReady_e;

#ifdef __MMS_MMI_CDMMS__

typedef struct SEA_MMS_FILEMANAGER_TAG
{
    MAE_WChar   tURL[FILEMGR_MAX_FILEPATH_SIZE];
    MAE_Ret     RspCode;
} SEA_MmsFileManager_t;


typedef struct SEA_MMS_Attach_Tag
{
	MMI_MMS_Composer_Attach_t tAttachData; // for interface saving, must at first
    MAE_WChar tURL[FILEMGR_MAX_FILEPATH_SIZE];
} SEA_MmsAttachItem_t;

/* Object List Index */
#define SEA_MMS_OLIDX_IMAGE             0x80
#define SEA_MMS_OLIDX_AUDIO             0x40
#ifdef __MMS_SUPPORT_PLAY_VIDEO__
#define SEA_MMS_OLIDX_VIDEO             0x20
#endif

#endif //__MMS_MMI_CDMMS__
/**
 * Application structure
 */
typedef struct MMI_SEA_TAG {

    APPLET_BASE_ELEMENTS;

    SEA_Operation_e eCurrentOperation;
    boolean bInitSuccss;
    boolean bFirstEntry;
	boolean bHandleEndKey;      //APM handle end key stop, and wait confirm
	boolean bParentAskClose;    //Parent ask embedded close
	boolean bIsScaleDone;
	boolean bResetMusicMode;
    UrlSrvUrlRspInfo_t tRspData;
/**********COMMON********/
    /* start type*/
    SEA_MmsGetDataReady_e eReady;
    SEA_StartType_e eMsgType;

    /*editor view*/
    SEA_EditorView_t tEditorView;

     /*recipients list */
    SEA_RecipientType_e eRecipientType;
    SEA_RecipientView_t tCommonRecipientView;
    SEA_RecipientInfo_t tCommonRecipientInfo;
    COMMON_SIM_CARD_STATUS_e eSIMCardStatus;    //SIM card status get from SIM Service

    /*sending */
    SEA_SIMStatus_e SIMStatus;                  //check if No SIM insert or Both SIM inactive or airplane mode
	SEA_SendMode_e eSendMode;                  //The Naster/Slave send key user pressed
	SEA_InputType_e eCurrentEditorType;
    u32 nEmbApID;
    SMI_MsgID_t MsgID;

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
	SMI_SmsSimMsgBox_e SmsSimMsgBox;
#endif
#ifdef __MMI_SMS_CHAT__
	boolean bIsForwardLengthTooLong;
#endif

/**********import data*********/
    SEA_PHBRecipientData_t *pPhbAPRecipientData;
#ifdef __MMS_MMI_CDMMS__
    SEA_MmsFileManager_t *pMmsFileMangerData; // for launch file manager
#endif

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
    MmiPhbApFidSelectContactDetails_t *pPhbAPvCardText;

	MmiPhbApFidSelectContactAsvCard_t *pPhbAPDataAsVcard;
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

#ifdef __APP_MMI_CALENDAR__
    SEA_CalendarReturnData_t *pCalAPData;
#endif
    SMI_MsgLocation_e location;
	boolean bShowNotice;

/************SMS*********/
    SEA_SaveResult_e nSaveResult;        //Save before sending , sms could be mutil sending
    SMI_SmEncoding_t nEncoding;
#ifdef __SMS_3GPP_R8_SUPPORT__
  	mmiGsmLockShiftTable_e eLockShift;
	mmiGsmSingleShiftTable_e eSingleShift;
#endif
    MAE_WChar       *pContent;           // record the start up data
    SEA_EDITOR_Info_t *pReloadData;      // recode SIM draft SMS init data. It will be free after finishing retrieving SIM data
    ModelListener_t MSANotifyListen;     //Model listener to MSA: Send options
#ifdef __SMS_SEND_FROM_BUFFER__
    boolean                         bIsBuffMsg;
#endif /* __SMS_SEND_FROM_BUFFER__ */
/************MMS*********/
#ifdef __MMS_MMI_CDMMS__
    u8    eSendOptionMode;                   //dual_master, dual_slave
    u32   nCurrentSize;
    u32   nMessageSize;
    u32   nHighlightIdx;                     // for object list
    u32   nFocusedWdgID;                     // record the focuseID;
    bool  bScreenDirty;
	bool  bRecipientOverLen;
    MMI_MMS_FS_MAILBOX_e eMMSLocation;
    MMI_MMS_Composer_Cntx *pMMSData;        // IVectorModel *pMal;SEA_MmsAttachItem_t    	IVectorModel *pMsl; SEA_MMS_SLIDE_t

    VectorClass_t *pFocusList;               // record current widget ID at the view

    WidgetHandler_t scrollWdgHandler;
    WidgetHandler_t TextContainWdgMdLsn;
    WidgetHandler_t SubjectWdgMdLsn;
    WidgetHandler_t BccWdgMdLsn;
    WidgetHandler_t CCWdgMdLsn;
    WidgetHandler_t ToWdgMdLsn;

	u32 vCarNum;
	u32 vCalNum;

    IImage         *pCurrentSlideImage;
    MAE_WChar       TempURL[FILEMGR_MAX_FILEPATH_SIZE];
	StorageInfo_t	tStorageInfo;
    IImage                          *pScaleImage;
    IIMAGEMAKER                     *pScaleImageMaker;
    u8                              *pScaleImageData;
    u32                             ScaleImageDataSize;
#ifdef __MMS_MMI_CDMMS_TEMPLATE__
    boolean                         PreviewOnly;
    boolean                         IsTemplateEditorMode;
    u8                              TempalteIdx;
    MSG_MMS_TEXT_LOCATION_e         OldTextLoc;
    MSG_MMS_IMAGE_SIZE_e            OldImageSize; 
#endif	
    MSG_MMS_TEXT_LOCATION_e         DefTextLoc;
    MSG_MMS_IMAGE_SIZE_e            DefImageSize;

#ifdef __MMI_OMA_DRM_V1__
    u8* pDrmAudioBuffer;
#endif
#endif //__MMS_MMI_CDMMS__
} MMI_SEA;


//event Callback
static boolean SeaAppStartCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean SeaAppSuspendCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean SeaAppResumeCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean SeaKeyPressCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean SeaAppEmbeddedCloseCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);


MAE_Ret SeaConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret SeaDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);


MAE_Ret _SEAWndSmsEditorViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndSmsEditorOptionViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndRecipientViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndRecipientOptionViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndDualSimMenuViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#ifdef __MMS_MMI_CDMMS__
MAE_Ret _SEAWndMmsEditorViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndMmsEditorOptionViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndMmsSlideListViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndMmsObjectListViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndMmsObjectListOptionViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndMmsFullEditorViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _SEAWndMmsFullEditorOptionViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret SEA_WndCreateSmsEditorView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroySmsEditorView(void* pCusHandle,void* pWndData);
MAE_Ret SEA_WndShowSmsEditorView (void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateSmsEditorOptionView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroySmsEditorOptionView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateRecipientView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndSetRecipientView(void* pCusHandle,void* pWndData, u32 nWndInitParam);//becky.wu
MAE_Ret SEA_WndDestroyRecipientView(void* pCusHandle,void* pWndData);
MAE_Ret SEA_WndShowRecipientView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateRecipientOptionView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyRecipientOptionView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateDualSimMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyDualSimMenuView(void* pCusHandle,void* pWndData);

#ifdef __MMS_MMI_CDMMS__
MAE_Ret SEA_WndSetMmsEditorView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndCreateMmsEditorView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyMmsEditorView(void* pCusHandle,void* pWndData);
MAE_Ret SEA_WndShowMmsEditorView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateMmsEditorOptionView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyMmsEditorOptionView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateMmsSlideListView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyMmsSlideListView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateMmsObjectListView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyMmsObjectListView(void* pCusHandle,void* pWndData);
MAE_Ret SEA_WndShowMmsObjectListView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateMmsObjectListOptionView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyMmsObjectListOptionView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateMmsFullEditorView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyMmsFullEditorView(void* pCusHandle,void* pWndData);
MAE_Ret SEA_WndShowMmsFullEditorView(void* pCusHandle,void* pWndData);

MAE_Ret SEA_WndCreateMmsFullEditorOptionView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroyMmsFullEditorOptionView(void* pCusHandle,void* pWndData);
#endif

void _SEA_HandleAppResumeStoppingCB( MMI_SEA *pThis );

void _SEA_HandleKeyPressSmsEditorView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressSmsEditorOptionView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressMmsEditorView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressMmsEditorOptionView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressRecipientView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressRecipientOptionView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressMmsSlideListView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressMmsObjectListView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressMmsObjectListOptionView(MMI_SEA* pThis, u32 keycode);
void _SEA_HandleKeyPressDualSimMenuView(MMI_SEA* pThis, u32 keycode);

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
MAE_Ret _SEAWndSmsSelectSimMsgMenuViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndCreateSmsSelectSimMsgMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret SEA_WndDestroySmsSelectSimMsgMenuView(void* pCusHandle,void* pWndData);
#endif


#endif /* __MMI_MESSAGEEDITORAPP_PRIV_H__ */
