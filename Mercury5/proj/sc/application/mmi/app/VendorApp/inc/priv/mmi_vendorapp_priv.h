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
* @file    mmi_vendorapp_priv.h
* @version
* @brief   VendorApp applet private header file
*
*/

#ifndef __MMI_VENDORAPP_PRIV_H__
#define __MMI_VENDORAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_vendorapp.h"
#include "mmi_venappid.h"
#include "mmi_phbapp.h"
#include "mmi_vendorsrv_req_st.h"
#include "mmi_class.h"
#ifdef __BLUETOOTH_OBEX_MMI__
#include "mmi_btsrv.h"
#endif // __BLUETOOTH_OBEX_MMI__
#ifdef __WAP_MMI_CDWAP__
#include "mmi_cdwapapp.h"
#endif
#include "mmi_common_vtm.h"
#include "mmi_common_storage_mgr.h"
#include "mmi_vendorapp_id.h"
#include "vendorapp_resource.h"
#include "mmi_req_cdmms.h"
#include "ven_sdk.h"

//Pre define macro
#if defined(__TOUCH_SCREEN_MMI__) && !defined(__WIDGET_DISABLE_FINGERCOMMAND__)
#define __VENDOR_FIGURE_COMMAND_COMMAND_DATE_TIME__
#endif

/**
* Internal Events
*/
enum
{
    VENDORAPP_IEVT_START = (CLSID_VENDORAPP << 16 | 1),
    VENDORAPP_IEVT_DUMMY = (CLSID_VENDORAPP << 16),

    /* Add event after this line */
    VENDORAPP_IEVT_VENSTART_RSP,
    VENDORAPP_IEVT_VENEXIT_RSP,
    VENDORAPP_IEVT_VENSUSPEND_RSP,
    VENDORAPP_IEVT_VENRESUME_RSP,
    VENDORAPP_IEVT_VENBACKGROUND_RSP,
    VENDORAPP_IEVT_VENFOREGROUND_RSP,
    VENDORAPP_IEVT_EXIT_IND,
    VENDORAPP_IEVT_EXIT,
    VENDORAPP_IEVT_KILL_IND,
    VENDORAPP_IEVT_VENBACKGROUND_IND,
    VENDORAPP_IEVT_VENFOREGROUND_IND,
    VENDORAPP_IEVT_VIDEO_PLAY,
    VENDORAPP_IEVT_VIDEOSTREAM_PLAY,
    VENDORAPP_IEVT_VIDEOSTREAM_STOP,
    VENDORAPP_IEVT_VIDEOSEEK_ONOFF,
    VENDORAPP_IEVT_FILE_BROWSE,
    VENDORAPP_IEVT_FILE_BROWSE_EX,
    VENDORAPP_IEVT_FILE_SELECT_FOLDER,
    VENDORAPP_IEVT_SEN_BTAPP_SEND_FILE,    
    VENDORAPP_IEVT_CAM_LAUNCH_APP,
    VENDORAPP_IEVT_CC_MAKECALL,
	VENDORAPP_IEVT_CC_MAKECALL_GET_CALL_ID,
    VENDORAPP_IEVT_CC_RELEASECALL,
    VENDORAPP_IEVT_EDITOR_EDIT,
	VENDORAPP_IEVT_EDITOR_DATE,
	VENDORAPP_IEVT_EDITOR_TIME,
    VENDORAPP_IEVT_GET_SELECT_SIM,
    VENDORAPP_IEVT_SELECT_SIM,
    VENDORAPP_IEVT_TIME_SET_TIMEZONE,
    VENDORAPP_IEVT_PHB_BROWSE,
    VENDORAPP_IEVT_SET_ITEM_VIS,
    VENDORAPP_IEVT_GET_ITEM_VIS,
    VENDORAPP_IEVT_SHOW_UI,
    VENDORAPP_IEVT_SHOW_UI_SELECTED,
    VENDORAPP_IEVT_CLOSE_UI,
    VENDORAPP_IEVT_START_VENDOR,
    VENDORAPP_IEVT_SET_UI_INT_LEVEL,
    VENDORAPP_IEVT_SET_UI_BLK,
    VENDORAPP_IEVT_RESET_UI_BLK,
    VENDORAPP_IEVT_MSG_EDITOR_EDIT,
    VENDORAPP_IEVT_OPEN_BROWSER,
    VENDORAPP_IEVT_UPDATE_UI,
    VENDORAPP_IEVT_ENABLE_LAUNCH_KEYGUARD,
    VENDORAPP_IEVT_EDITOR_CLOSE,
    VENDORAPP_IEVT_SET_DISPLAY_MODE,
    /* Add event before this line */

    VENDORAPP_IEVT_SUM,
    VENDORAPP_IEVT_END = VENDORAPP_IEVT_SUM -1
};

/**
* VendorApp attribute
* Set attribute according to the requirement of different Vendors
*/
#define VENDORAPP_ATTR_NONE                 0x0000
#define VENDORAPP_ATTR_EXTERNAL_MEM_CARD    0x0001 // Set this attribute if external memory card is necessary for execution
#define VENDORAPP_ATTR_INTERACTIVE_STOP     0x0002 // Vendor needs user's confirmation for an external close request
#define VENDORAPP_ATTR_EXIT_WITH_COMFIRM    0x0004 // Vendor needs user's confirmation before exit
#define VENDORAPP_ATTR_DATA_LINK            0x0008 // Vendor needs data link
#define VENDORAPP_ATTR_START_WITH_WATING    0x0010 // Vendor needs a waiting dialog when starting
#define VENDORAPP_ATTR_DELAY_START          0x0020 // Vendor needs to be started after some other comfirmation
#define VENDORAPP_ATTR_INTERACTIVE_BACKGROUND   0x0040 // Vendor could execute in background
#define VENDORAPP_ATTR_INSERT_SIM_CARD    	0x0080 // Set this attribute if sim card is necessary for execution
#define VENDORAPP_ATTR_USB_INUSED    		0x0100 // Set this attribute if USB is inused
#define VENDORAPP_ATTR_USE_ENDKEY           0x0200 // Set this attribute to Use Endkey
#define VENDERAPP_ATTR_NON_SUSPEND_BACKGROUND_MUSIC	0x0400 // Set this attribute for support non stop background music (non session, background mp3/fm will not suspend)
#define VENDORAPP_ATTR_USB_PHB              0x0800 // Set this attribute to Use Phb Sorting Table

/**
* VendorApp check/confirmation mask
* Set mask according to the check/confirmation of different Vendors
*/
#define VENDORAPP_CHECK_NONE                0x00
#define VENDORAPP_CHECK_SUSPEND_MMS         0x01 // Confirm with user to suspend MMS
#define VENDORAPP_CHECK_ABORT_BT_OBEX      0x02 // Confirm with user to abort BT obex transfer
#define VENDORAPP_CHECK_TURNOFF_BT      0x04 // Confirm with user to turn off BT

enum vendor_state_tag
{
    VENDOR_INIT = 0,            // Not ask 3rd party to start yet
    VENDOR_PRE_CHECK,           // Perform some check/confirm before asking 3rd party to start
    VENDOR_ACTIVE,              // ask 3rd party to start, or 3rd party already confirm start_rsp
    VENDOR_SUSPEND,             // 3rd party is suspend and not automatically suspend for editor, select SIM, embedded AP or show UI
    VENDOR_TERMINATE,           // ask 3rd party termintated or 3rd party already notify the stop_ind
	VENDOR_BACKGROUND,			// 3rd party is in background
    VENDOR_EDITOR,              // handled 3rd party editor request.
	VENDOR_EDITOR_DATE,	//handle 3rd party datetime editor
	VENDOR_EDITOR_TIME,			//hadnle 3rd party time editor
    VENDOR_SELECT_SIM,          // handled 3rd party select SIM request.
    VENDOR_EMBEDDED,            // handled 3rd party embedded AP (CC, file browser, phb browser, video player) request.
    VENDOR_SHOW_UI,             // handled 3rd party UI request ( menu, dialog, text viewer)
    VENDOR_WAIT_STOP,           // wait for 3rd party send STOP RSP to exit vendorapp [only for pressing End key->choose "Exit" case]
    VENDOR_NO_CHANGE    = 0xFF
};
#define VENDOR_STATE_MASK               0x0F
#define VENDOR_INTERACTIVE_STOP_MASK    0x10    ///< Interactive with user for exit confirm
#define VENDOR_DELAYED_ACTION_MASK      0x20    ///< Perform next action after got the last confirm from 3rd party
#define VENDOR_AP_SUSPEND_MASK          0x40    ///< got the suspend in TERMINATE, EDITOR, SELECT_SIM, EMBEDDED, or SHOW_UI state.
#define VENDOR_DELAY_CLOSE_UI_MASK      0x80    ///< after got the APM resume, reutn the cancel UI result
///  If 3rd party request close UI in SHOW_UI state and in AP_SUSPEND, service should delay the close UI request

typedef u8 vendor_state_t;

enum vendor_delayed_action_tag
{
    VENDOR_DELAYED_NONE = 0,
    VENDOR_DELAYED_SUSPEND,     ///< Suspend vendor after receiving the response of previous command
    VENDOR_DELAYED_STOP,        ///< Stop vendor after receiving the response of previous command
    VENDOR_DELAYED_START,        ///< interruptive launch but failed and need to wait for other ap finished
};
typedef u8 vendor_delayed_action_t;

enum vendor_sub_state_tag
{
    VENDOR_SUBSTAT_DONE,
    VENDOR_SUBSTAT_WAIT_START_RSP,       //Wait for 3rd party response
    VENDOR_SUBSTAT_WAIT_SUSPEND_RSP,     //Wait for 3rd party response
    VENDOR_SUBSTAT_WAIT_RESUME_RSP,      //Wait for 3rd party response
    VENDOR_SUBSTAT_WAIT_EXIT_RSP,        //Wait for 3rd party response
    VENDOR_SUBSTAT_WAIT_BACKGROUND_RSP,	 //Wait for 3rd party response
    VENDOR_SUBSTAT_DIALOG_WAITING,       //Terminate state:Show error dialog, Wait for dialog pop out
    VENDOR_SUBSTAT_WAIT_DELAY_START_IND, //Wait for external indications for delay start

    VENDOR_SUBSTAT_NO_CHANGE = 0xFF,
};
typedef u8 vendor_substat_t;

enum
{
    VEN_EMBEDDED_ACTION_MAKECALL			= 0,
    VEN_EMBEDDED_ACTION_PHBBROWSE	  		= 1,
    VEN_EMBEDDED_ACTION_FILEBROWSE			= 2,
    VEN_EMBEDDED_ACTION_PLAYVIDEO           = 3,
    VEN_EMBEDDED_ACTION_MSGEDITOR           = 4,
    VEN_EMBEDDED_ACTION_OPENBROWSER         = 5,
    VEN_EMBEDDED_ACTION_PLAYVIDEOSTREAM     = 6,
    VEN_EMBEDDED_ACTION_CAMLAUNCHAPP        = 7,
    VEN_EMBEDDED_ACTION_FILESELECTFOLDER    = 8,
    VEN_EMBEDDED_ACTION_FILEBROWSE_EX	    = 9,
    VEN_EMBEDDED_ACTION_SENBTTAPPSENDFILE   = 10,  
};
typedef u8 ven_embedded_action_t;

// Dialog type for those dialogs prompted by VendorApp
enum
{
    VENDOR_DIALOG_NONE = 0,         // No dialog was prompted by VendorApp
    VENDOR_DIALOG_ERROR,            // Dialog for error prompt
    VENDOR_DIALOG_INTERACTIVE_STOP, // Dialog for interactive stop with user
    VENDOR_DIALOG_ABORT_BT_OBEX,    // Dialog for abort BT OBEX transfer
    VENDOR_DIALOG_TURNOFF_BT,    // Dialog for turn off BT
    VENDOR_DIALOG_NO_MEM_CARD,      // Dialog for absent memory card
    VENDOR_DIALOG_NO_SIM,           // Dialog for absent SIM
    VENDOR_DIALOG_USB_INUSED,       // Dialog for abort USB
    VENDOR_DIALOG_CARD_FOLDER_INVALID, // Dialog for abort Memory card craeting folder invalid
    VENDOR_DIALOG_MMS_NOT_READY,    // MMSSrv is not ready or reloading
    VENDOR_DIALOG_PHB_NOT_READY,    // PHBSrv is not ready or reloading
    VENDOR_DIALOG_MEM_INSUFFICIENT, //for memory subject use
    VENDOR_DIALOG_AIRPLANE_MODE,    // Dialog for airplane mode, network is not allowed. 
};
typedef u8 vendor_dialog_t;

enum
{
	VENDOR_DATE_VIEW_BEGIN = APP_WDG_START,
	VENDOR_DATE_MFLCONTAINER,
	VENDOR_DATE_TEXT_DATE_WIDGET,
};

enum
{
	VENDOR_TIME_VIEW_BEGIN = APP_WDG_START,
	VENDOR_TIME_MFLCONTAINER,
	VENDOR_TIME_TEXT_TIME_WIDGET,
};

typedef struct _vendorBrowseExCfg_t
{
    VFS_ExtensionFilter_t tExtList;
    FileMgrVirtualVolumeItem_t tVirtualVolItem;
}vendorFileBrowseExCfg_t;

/**
* Application structure
*/
typedef struct VendorAppData_t_
{
    APPLET_BASE_ELEMENTS;

    const struct VenAppData_tag *pApData;
    IWidget *pISKWidget;  // Softkey widget
    u32                    venHandle;
    u32                    curEvt;
    u32                    newEvt;
    vendor_state_t         state;        //ap state
    vendor_substat_t       sub_state;
    vendor_delayed_action_t delayedActon;   //Delayed action after receiving response of previous command
    u32			session;
    void* pData;            //data retrieved from embedded ap
    void* pDelayCloseData;  //close data retrieved from embedded ap
    ven_embedded_action_t  embeddedApAction;
    u8                     bSbVis;  // Status bar visibility
    u8                     bSkVis;  // Softkey visibility
    u16 nAttribute; // Applet attribute
    mmi_ui_interrupt_level_t nIntLevel;	 //interrupt level.
    mmi_ui_backlight_behavior_t nBlkBehavior; // LCD backlight behavior
    u8 nPreCheckMask; // Mask for pre-check/confirmation before starting 3rd party
    u8 nCheckResult; // Mask for pre-check/confirmation before starting 3rd party
    boolean bExtMemCard;            // TRUE if external memory card is inserted
    vendor_dialog_t dialogType; // Dialog types for those dialogs prompted by VendorApp
    BKLInfo OriginalBKLInfo;    // Original backlight info before VendorApp is activated

    MAE_WChar *pDisplayName; // Vendor's display name
    MAE_ClsId clsId; // Vendor's class id
    boolean bStatusChangedByVendor; // TRUE if the background/foreground reuqest is issued by 3rd party
    void *pVenParam;    // Pointer to vendor paramater
    u32 nVenParamSize;  // Size of vendor param in bytes
#ifdef __SDK_MMI_DISPLAY_MANAGER__
    IWidget *pActiveBitmapWidget;  // Bitmap Widget to get vendor display buffer
#endif
#ifdef __WAP_MMI_CDWAP__
	bool bWapSync;
    tWapStartParm tWapStartParam; // Parameter to start WAP browser
    mmi_wap_browser_mode_t nWapBrowserMode;
    mmi_wap_browser_download_storage_t nWapStorage;
    SimID_e eSimID;             //the SIM ID used to create datalink in browser

    VEN_CB_FUNC_PTR pWapDLCbFunc;   //callback function for 3rd party to get the error code recorded for later response in 3rd task while cdwap processing
    boolean bCdWapExitByEndKey;   //for indicating cdwap close by END_KEY
#endif

    SetDefaultSIM_e eCurrSimID;     //For saving current select sim value => default value is getting the value of "CFGIT_SETTING_PHONE_DEFAULT_SIM"

    vendorFileBrowseExCfg_t tVendorFileBrowseExCfg;
} VendorAppData_t;

typedef struct VenMainViewData_tag
{
    VendorAppData_t *pThis;
    u8           bStatusbarVis;
    u8           bSoftkeyVis;
} VenMainViewData_t;

typedef MAE_Ret (*VENAP_PFN_INIT)(VendorAppData_t *pThis);
typedef MAE_Ret (*VENAP_PFN_DISPMAINVIEW)(VenMainViewData_t *pData);
typedef MAE_Ret (*VENAP_PFN_TERMINATE)(VendorAppData_t *pThis);

typedef struct VenFnTbl_tag
{
    VENAP_PFN_INIT          pfnInit;
    VENAP_PFN_DISPMAINVIEW  pfnDispMainView;
    VENAP_PFN_TERMINATE     pfnTerminate;
} VenFnTbl_t;

typedef struct VenAppData_tag
{
    Mmi_VenAppID_t	AppId;
    MAE_ClsId      	clsId;
    ResMgr_AppId_e 	mediaAppId;
    VenFnTbl_t     	fnTbl;
    u8              bStatusbarVis;
    u8              bSoftkeyVis;
	u16				nAttribute;
} VenAppData_t;

typedef struct
{
    //u32 PhbApSelect;
    PhoneBookGetContactRecord_t *psContactData;
    u16 nMaxSelectSize;
    phb_browser_type_t browserType;
} PHBBrowserInfo_t;

typedef struct
{
    IWidget *pInputWidget;
    IWidget *pOptionMenuWidget;
    boolean			bShowingOptionMenu;
    u32 nMinLengthForCommit;
    u16 nMaxContentLen;
} InputModeInfo_t;

typedef struct
{
    mmi_ven_select_sim_function_t type;
} SelectSIMInfo_t;

#ifdef __VENDOR_FIGURE_COMMAND_COMMAND_DATE_TIME__          //Figure Command __TOUCH_SCREEN_MMI__
//Figure Command
typedef struct
{
	IWidget     *pITimeWdg;
	TimeInputWdgList_t tInputWdg;
} VendorAppTime_t;
#else//__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__
typedef struct
{
	IWidget         *pITimeWdg;
} VendorAppTime_t;
#endif //__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__

#ifdef __VENDOR_FIGURE_COMMAND_COMMAND_DATE_TIME__          //Figure Command __TOUCH_SCREEN_MMI__
typedef struct
{
	IWidget     *pIDateWdg;
	DateInputWdgList_t tInputWdg;
} VendorAppDate_t;
#else                                                           //__VENDOR_FIGURE_COMMAND_COMMAND_DATE_TIME__
typedef struct
{
	IWidget         *pIDateWdg;
} VendorAppDate_t;
#endif                                                          

typedef struct
{
    mmi_ven_ui_type_t contentType;
    u8          bSync;
    void               *pData;        ///< mmi_ven_ui_xxxx_t
    u32			index;        ///< for response
    mmi_ven_ui_usr_rsp_t  usrRsp;    ///< for response

    union
    {
        struct
        {
            u32 SemID;
            u32 *pRetCode;
            void *pRspData;
        } tSyncData;
        struct
        {
            u32			transID;      ///< transition ID
            void			*pContent;       ///< Pointer to content of menu/dialog/textviewer
            mmi_ven_Callback_Info_t tCBInfo;
        } tAsyncData;
    } tRspData;
} VenApp_ShowUIData_t;

typedef struct
{
    mmi_ven_ui_type_t contentType;
    void               *pRetCode;
    u32			transID;
    u32               SemID;
} VenApp_CloseUIData_t;

typedef struct
{
    mmi_ui_interrupt_level_t intLevel;
    void               *pRetCode;
    u32               SemID;
} VenApp_SetUIIntLevel_t;

typedef union
{
    VenApp_ShowUIData_t tShowUIData;
    VenApp_CloseUIData_t tCloseUIData;
} VenApp_ReqData_t;

typedef void (*VENAP_PFN_CANCEL_REQ)(VendorAppData_t *pThis, void *pData, boolean bCurEvt);
typedef void (*VENAP_PFN_GEN_EVT_DATA)(VendorAppData_t *pThis, u32 param1, u32 param2, void **ppData);
typedef void (*VENAP_PFN_FREE_EVE_DATA)(VendorAppData_t* pThis, void *pData);

typedef struct
{
    u32   evtCode;
    u8   priority;             ///< larger is higher
    u8   DstState;
    VENAP_PFN_CANCEL_REQ  pFnCancel;
    VENAP_PFN_GEN_EVT_DATA pFnGetData;
    VENAP_PFN_FREE_EVE_DATA pFnFreeData;
} VenApp_ReqItem_t;

typedef struct
{
    IModel *pModel;
} VenApp_ShowUiMenuExtData_t;

// ---- Window Data --------
typedef struct VendorMenuWndData_t_
{
    mmi_ven_ui_menu_t *pMenuData;

} VendorMenuWndData_t;

typedef struct VendorTextViewerWndData_t_
{
    mmi_ven_ui_textviewer_t *pTextViewerData;

} VendorTextViewerWndData_t;


// ---- Widget List --------
// VendorActiveViewRC

typedef struct
{
    IWidget *pDummyWdg;
#ifdef __SDK_MMI_DISPLAY_MANAGER__
    IWidget *pBmpWdg;
#endif
    IWidget *pSkWdg;
} VendorActiveWdgList_t;


// VendorSuspendViewRC

typedef struct
{
    IWidget *pBmpWdg;
} VendorSuspendWdgList_t;


// VendorTextViewerRc

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pScrollBar;
    IWidget *pVPWdg;
    IWidget *pTextWdg;
} VendorTextViewerWdgList_t;

typedef struct
{
#if !defined(__VENDOR_FIGURE_COMMAND_COMMAND_DATE_TIME__)
	IWidget *pMflContainer;
#endif
	IWidget *pTextDateWidget;
} VendorDateViewWdgList_t;

typedef struct
{
#if !defined(__SETTINGAPP_FIGURE_COMMAND_COMMAND_DATE_TIME__)
	IWidget *pMflContainer;
#endif
	IWidget *pTextTimeWidget;
} VendorTimeViewWdgList_t;

// used for callback function of CC with get ID
typedef struct{

	u32		venHandle;
	u32		session;

}VenApp_CC_CallbackUserData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
/*=============================================================*/
// AP Entry Function
/*=============================================================*/
/** VendorConstructor
* @brief        Construct Applet function(when receive MAE_EVT_CONSTRUCT)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/** VendorDestructor
* @brief        Release Applet function(when receive MAE_EVT_DESTRUCT)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/** VendorStartCB
* @brief        Applet start function(when receive MAE_EVT_APP_START)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean VendorStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/** VendorStopCB
* @brief        Applet Stop function(when receive MAE_EVT_APP_STOP)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean VendorStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/** VendorResumeCB
* @brief        Applet Resume function(when receive MAE_EVT_APP_RESUME)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean VendorResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/** VendorSuspendCB
* @brief        Applet Suspend function(when receive MAE_EVT_APP_SUSPEND)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean VendorSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/*=============================================================*/
// Handler Function
/*=============================================================*/
/** VendorWndBaseHdl
* @brief        Show Base window handle function (Create Dummy window)
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndBaseHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndSuspendHdl
* @brief        Show suspend window handle function (For Dialog or other interrupt needed to suspend Java AP first)
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndSuspendHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndMenuHdl
* @brief        Show Menu window handle function
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndMenuHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndTextViewerHdl
* @brief        Show Text window handle function
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndTextViewerHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndEditorHdl
* @brief        Show Editor window handle function (Text input)
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndEditorHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndDateEditorHdl
* @brief        Show Date Editor window handle function (Text input)
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndDateEditorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndTimeEditorHdl
* @brief        Show Time Editor window handle function
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndTimeEditorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndEditorOptionHdl
* @brief        Show Editor's Option window handle function (It can have 2 layers of Option)
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndEditorOptionHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndSelectSimHdl
* @brief        Show Selecting Sim Card window handle function (If there is more than one Sim card to choose)
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndSelectSimHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
/** VendorWndBGExitSelectHdl
* @brief        Show BG exit Selection window handle function (For Background execution--Exit/Minimize)
*
* @param[in]    pWndHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorWndBGExitSelectHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);

/*=============================================================*/
// Global Function
/*=============================================================*/
/** VendorGetProperty
* @brief        Get Vendor app property function (By MAE_EVT_GET_PROPERTY event)
*
* @param[in]    pApplet            The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    key                  APM queries applets about these properties by sending MAE_EVT_GET_PROPERTY event
* @param[in]    outVal              For getting class id here to notify interrupting AP ID
*
* @retval       TRUE             For APM_PROP_INTERRUPTIBLE event (From other ap's interrupt)
*			 FALSE		 For other events
*
*/
boolean VendorGetProperty(IApplet *pApplet, u32 nEvt, u32 key, u32 outVal);
/** VendorTsCb
* @brief        For pressing touch panel CB function (Create Dummy window)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean VendorTsCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/** _VendorAppPreHookCB
* @brief        For Hook Key for specail Wnd
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean VendorAppPreHookCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/** VendorTsCb
* @brief        For pressing touch panel CB function
*
* @param[in]    hWin  Window handle
* @param[in]    pWdgList      Widget list structure
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorCreateActiveView(HWIN hWin, VendorActiveWdgList_t *pWdgList);
/** VendorTsCb
* @brief        Create Suspend view (Create BMP widget for copy APview)
*
* @param[in]    hWin  Window handle
* @param[in]    pWdgList      Widget list structure
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret VendorCreateSuspendView(HWIN hWin, VendorSuspendWdgList_t *pWdgList);

#endif /* __MMI_VENDORAPP_PRIV_H__ */
