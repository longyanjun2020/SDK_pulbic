/**
 * @file ven_ui.h
 *
 * @brief  This file defines the UI related request vendor API and SDK reponse API
 *
 * @author  steve.lee
 *
 * @version $Id: ven_ui.h 47127 2009-12-10 14:30:38Z steve.lee $
 *
 */

#ifndef __VEN_UI_H_
#define __VEN_UI_H_

#include "ven_sdk.h"
#include "ven_setting.h"
#include "ven_socket.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

typedef u32 ven_menu_handle_t;
typedef u32 ven_dialog_handle_t;
typedef u32 ven_textviewer_handle_t;
typedef u32 ven_softkey_handle_t;

//Has to be a number smaller than u8 for now
#define VEN_STATUSBAR_NUM_OF_SLOT 5
enum
{
    VEN_UI_RET_SUCCESS,                 ///< operation completed successfully
    VEN_UI_RET_BAD_PARAM,               ///< invalid input parameters
    VEN_UI_RET_OUT_OF_MEMORY,           ///< memory is not enough to complete the operation
    VEN_UI_RET_OPERATION_CANCELED,      ///< operation is canceled due to interruption
    VEN_UI_RET_TIMEOUT,                 ///< for dialog with duration assigned
    VEN_UI_RET_ALL_SLOT_OCCUPIED,       ///< All statusbar icon slot occupied and not available
    VEN_UI_RET_FAILED,                  ///< unknown error
    VEN_UI_RET_NOT_SUPPORT,             ///< Not support now
    VEN_UI_RET_NOT_ALLOWED              ///Operation not allowed
};
typedef u32 ven_ui_ret_t;

enum
{
    // Response of menu, dialog, text viewer
    VEN_UI_USR_RSP_OK,      ///< user selects OK
    VEN_UI_USR_RSP_CANCEL,  ///< user selects cancel
};
typedef u32 ven_ui_usr_rsp_t;

enum
{
    // Softkey type of dialog/menu/text viewer
    VEN_UI_SK_X_X_X,
    VEN_UI_SK_X_X_CANCEL,
    VEN_UI_SK_X_OK_CANCEL,
    VEN_UI_SK_X_X_BACK,
    VEN_UI_SK_X_OK_BACK,
    VEN_UI_SK_X_OK_X,
    VEN_UI_SK_OK_OK_CANCEL,

    // Softkey type of customized softkey
    VEN_UI_SK_X_OK_CUS,    ///<  Customized RSK with CSK, the text/image of RSK is decided by vendor
    VEN_UI_SK_CUS_OK_X,    ///<  Customized LSK with CSK, the text/image of LSK is decided by vendor
    VEN_UI_SK_CUS_OK_CUS,  ///<  Customized LSK/RSK with CSK, the text/image of LSK/RSK is decided by vendor
    VEN_UI_SK_X_X_CUS,     ///<  Customized RSK without CSK, the text/image of RSK is decided by vendor
    VEN_UI_SK_CUS_X_X,     ///<  Customized LSK without CSK, the text/image of LSK is decided by vendor
    VEN_UI_SK_CUS_X_CUS,   ///<  Customized LSK/RSK without CSK, the text/image of LSK/RSK is decided by vendor

    VEN_UI_SK_TYPE_SUM
};
typedef u8 ven_ui_softkey_type_t;

enum
{
    VEN_UI_SK_ALL_RELEASED = 0x00,     ///< All softkeys are not pressed
    VEN_UI_SK_LSK_PRESSED  = 0x01,     ///< Left softkey is pressed
    VEN_UI_SK_CSK_PRESSED  = 0x02,     ///< Center softkey is pressed
    VEN_UI_SK_RSK_PRESSED  = 0x04,     ///< Right softkey is pressed

    VEN_UI_SK_STATUS_SUM
};
typedef u8 ven_ui_softkey_status_t;

enum
{
    VEN_UI_SK_NATIVE = 0,               ///< Specified attribute for CSK with VEN_UI_SK_X_OK_CUS / VEN_UI_SK_CUS_OK_X / VEN_UI_SK_CUS_OK_CUS
    VEN_UI_SK_IMG,                      ///< Specified attribute LSK/CSK/RSK
    VEN_UI_SK_TEXT,                     ///< Specified attribute LSK/RSK
};
typedef u8 ven_ui_softkey_attribute_t;

enum
{
    VEN_UI_INT_NORMAL           = 0x00,     ///< Allow all interruptions
    VEN_UI_INT_DENY_DIALOG      = 0x01,     ///< Refuse dialog interruptions ex.SMS/MMS dialog
    VEN_UI_INT_DENY_USB         = 0x02,     ///< Refuse USB screen when data cable is inserted
    VEN_UI_INT_DENY_BT_OBEX     = 0x04,     ///< Refuse Bluetooth OBEX, no Bluetooth file transfer is allowed
    VEN_UI_INT_DENY_MT          = 0x08,     ///< Refuse MT call
    VEN_UI_INT_DENY_ALL         = 0x10,     ///< Refuse all interruptions

    VEN_UI_INT_SUM
};
typedef u8 ven_ui_interrupt_level_t;

enum
{
    VEN_UI_BACKLIGHT_ON         = 0,    ///< LCD backlight is always on
    VEN_UI_BACKLIGHT_AUTO,              ///< LCD backlight will load the last setting, if the last setting is forever ON, then it will be set to forever ON.
    VEN_UI_BACKLIGHT_OFF,               ///< LCD backlight is always off
    VEN_UI_BACKLIGHT_FORCE_AUTO,        ///< LCD backlight is automaitc on/off by the default timer
    VEN_UI_BACKLIGHT_SUM,
};
typedef u8 ven_ui_backlight_behavior_t;

enum
{
	VEN_UI_BACKLIGHT_LEVEL_0 = 0,
	VEN_UI_BACKLIGHT_LEVEL_1,
	VEN_UI_BACKLIGHT_LEVEL_2,
	VEN_UI_BACKLIGHT_LEVEL_3,
	VEN_UI_BACKLIGHT_LEVEL_4,
	VEN_UI_BACKLIGHT_LEVEL_5,
	VEN_UI_BACKLIGHT_LEVEL_6,
	VEN_UI_BACKLIGHT_LEVEL_MAX = VEN_UI_BACKLIGHT_LEVEL_6,
	VEN_UI_BACKLIGHT_LEVEL_DEFAULT,
};
typedef u16 ven_ui_backlight_level_t;

enum
{
    VEN_UI_BACKLIGHT_DURATION_DEFAULT = 0xEEEE,
   	VEN_UI_BACKLIGHT_DURATION_FOREVER = 0xFFFF   //match with BKL_DURATION_ALWAYS_ON
};
typedef u16 ven_ui_backlight_duration_t;

typedef struct
{
    bool bIsBacklightOn;
    ven_ui_backlight_level_t nActiveBKLLevel;
    u16 nActiveBKLDuration;
}ven_ui_backlight_info;

typedef enum
{
	VEN_UI_DATALINK_SELECTSIM           = 0, ///< Draw select SIM wnd
	VEN_UI_DATALINK_SHARELINK           = 1, ///< Share datalink with others (OK)
	VEN_UI_DATALINK_DENYSHARELINK       = 2, ///< Deny to share datalink (cancel)
	VEN_UI_DATALINK_NOTAVAILABLE        = 3, ///< No datalink to use
	VEN_UI_DATALINK_WIFI                = 4, ///< Reserve for WIFI
	VEN_UI_DATALINK_FAILED              ,	 ///< FAILED

}ven_ui_datalink_ret_t;

typedef enum
{
	VEN_UI_DATALINK_DEFAULTALLOW          = 0,  ///< Not show confirm dialog¡ADefault Yes
	VEN_UI_DATALINK_DEFAULTDENY           = 1,   ///< Not show confirm dialog¡ADefault Cancel
	VEN_UI_DATALINK_CONFIRM               = 2, ///< display confirm dialog to choose

}ven_ui_datalink_confirm_t;

typedef enum
{
    VEN_UI_STATUSBAR_IMAGE_NULL = 0,
    VEN_UI_STATUSBAR_IMAGE_JAVA = 1,   
    VEN_UI_STATUSBAR_IMAGE_QQ  = 2, 
    VEN_UI_STATUSBAR_IMAGE_NUM
} ven_ui_statusbar_image_t;

typedef struct
{
    u16 *pText;           ///< UCS2 string pointer
    u16 nTextLen;         ///< character length of pText, not including end of string
} ven_ui_title_t;

typedef struct
{
    u16 *pText;           ///< UCS2 string pointer
    u16 nTextLen;         ///< character length of pText, not including end of string
} ven_ui_menu_item_t;

enum
{
	VEN_UI_MENU_TEXT,
	VEN_UI_MENU_NUMERIC_TEXT,

	VEN_UI_MENU_TYPE_SUM
};
typedef u8 ven_ui_menu_type_t;


typedef struct
{
	ven_ui_title_t tTitle;
	ven_ui_menu_type_t nMenuType;
	u32  nSize;          ///< total number of menu items
	u32	 nHLIndex;		 ///< high index of menu items
	ven_ui_menu_item_t *pItems;   ///< array of menu items
	ven_ui_softkey_type_t nSoftkeyType;
}ven_ui_menu_content_t;

enum
{
    VEN_UI_DLG_INFORMATION,    ///< i
    VEN_UI_DLG_CONFIRMATION,   ///< ?
    VEN_UI_DLG_WARNING,        ///< !

    VEN_UI_DLG_TYPE_SUM
};
typedef u8 ven_ui_dialog_type_t;

typedef struct
{
    ven_ui_title_t tTitle;
    u16 *pText;          ///< UCS2 string pointer
    u16 nTextLen;        ///< character length of pText, not including end of string
    u16 nDuration;       ///< Duration of the dialog in seconds. use 0 to disable auto closing.
    ven_ui_dialog_type_t  nDialogType;
    ven_ui_softkey_type_t nSoftkeyType;
} ven_ui_dialog_content_t;

typedef struct
{
    ven_ui_softkey_attribute_t nAttr;   ///< Softkey attribute
    u8 nTextLen;                        ///< Character length of text, not including end of string
    union
    {
        u8 *pImg;                       ///< Pointer to the image raw data
        u16 *pText;                     ///< UCS2 string pointer
    } data;
} ven_ui_softkey_t;

typedef struct
{
    ven_ui_softkey_type_t nSoftkeyType;     ///< VEN_UI_SK_CUS_X_CUS or VEN_UI_SK_CUS_OK_CUS
    ven_ui_softkey_status_t nSoftkeyStatus; ///< Softkey status. Pressed or Released
    ven_ui_softkey_t lsk;                   ///< Left softkey
    ven_ui_softkey_t csk;                   ///< Center softkey
    ven_ui_softkey_t rsk;                   ///< Right softkey
} ven_ui_softkey_content_t;

typedef struct
{
    ven_ui_title_t tTitle;
    u16 *pText;           ///< UCS2 string pointer
    u16 nTextLen;         ///< character length of pText, not including end of string
    ven_ui_softkey_type_t nSoftkeyType;
} ven_ui_textviewer_content_t;

typedef struct
{
    ven_ui_usr_rsp_t nUsrRet;    ///< user return code, valid when nRetCode is success
    u32 index;                   ///< user select index, valid when nRetCode is success
} ven_ui_show_menu_sync_ret_t;

typedef struct
{
    ven_ui_usr_rsp_t nUsrRet;    ///< user return code, valid when nRetCode is success
} ven_ui_show_dialog_sync_ret_t;

typedef struct
{
    ven_ui_usr_rsp_t nUsrRet;    ///< user return code, valid when nRetCode is success
} ven_ui_show_textviewer_sync_ret_t;

typedef struct
{
    ven_ui_ret_t nRetCode;       ///< operation return code
    ven_ui_usr_rsp_t nUsrRet;    ///< user return code, valid when nRetCode is success
    u32 index;                   ///< user select index, valid when nRetCode is success
} ven_ui_show_menu_rsp_t;

typedef struct
{
    ven_ui_ret_t nRetCode;       ///< operation return code
    ven_ui_usr_rsp_t nUsrRet;    ///< user return code, valid when nRetCode is success
} ven_ui_show_dialog_rsp_t;

typedef struct
{
    ven_ui_ret_t nRetCode;       ///< operation return code
    ven_ui_usr_rsp_t nUsrRet;    ///< user return code, valid when nRetCode is success
} ven_ui_show_textviewer_rsp_t;


typedef struct
{
    u8 *pRawData;
    u32 nDataSize;
} ven_ui_statusbar_draw_icon_req_t;

typedef struct
{
	u32 nHandle ;                                  ///< handle
	ven_ui_datalink_confirm_t tConfirmDatalink;    ///< Reserve
	ven_setting_network_profile_type_t tType;      ///< Network profile
	ven_setting_lang_t tLang;              		   ///< Language

} ven_ui_datalink_t;


enum
{
    IVEN_UI_CLSID_APP_IDLE = 0,                               ///< idle applet
    IVEN_UI_CLSID_APP_VENDOR,                                 ///< vendor applet
#ifdef __UI_STYLE_MMI_ANDROID_KEYGUARD__
    IVEN_UI_CLSID_APP_ANDROID_KEYGUARD,                       ///< android key guard applet
#else
    IVEN_UI_CLSID_APP_KEYGUARD,                               ///< key guard applet
#endif
};
typedef u32 iVen_ui_applet_id;

enum
{
    IVEN_UI_APP_EXIST_STATUS_UNKNOW = 0,          ///< status of applet : unknow
    IVEN_UI_APP_EXIST_STATUS_FOCUSED = 1,         ///< status of applet : actived
    IVEN_UI_APP_EXIST_STATUS_FOREGROUND = 2,      ///< status of applet : in foreground
    IVEN_UI_APP_EXIST_STATUS_BACKGROUND = 4,      ///< status of applet : in background
    IVEN_UI_APP_EXIST_STATUS_IN_STACK = 8,        ///< status of applet : in stack
};


typedef u32 iVen_ui_applet_exist_status;
typedef struct iVen_ui_applet_status
{
    iVen_ui_applet_exist_status nAppletExistStatus;     ///< the status of applet 
    void *pData;                                        
}iVen_ui_applet_status_t;


/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 *  ven_ui_createMenu
 *
 *  @brief  Create menu handle
 *
 *  @param  phMenu   [out] Popinter to store created menu handle
 *
 *  @retval VEN_UI_RET_SUCCESS   Create successfully
 *          VEN_UI_RET_BAD_PARAM    Given phMenu is NULL
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_createMenu(ven_menu_handle_t *phMenu);

/**
 *  ven_ui_releaseMenu
 *
 *  @brief  Release menu handle
 *
 *  @param  hMenu   [in] Menu handle to be released
 *
 *  @retval VEN_UI_RET_SUCCESS   Release successfully
 *          VEN_UI_RET_BAD_PARAM    Invalid menu handle
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_releaseMenu(ven_menu_handle_t hMenu);

/**
 *  ven_ui_setMenuContent
 *
 *  @brief  Set menu data to the given menu handle
 *
 *  @param  hMenu   [in] Menu handle to be set data
 *  @param  pMenuContent   [in] Menu data to be set to the given menu handle
 *
 *  @retval VEN_UI_RET_SUCCESS   Set data successfully
 *          VEN_UI_RET_BAD_PARAM    Given hMenu is invalid or pMenuContent is NULL
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 *  @note pItems in pMenuContent must contain nSize items or be NULL. NULL means menu
 *        items will be set in the future by ven_ui_setMenuItem()
 */
ven_ui_ret_t ven_ui_setMenuContent(ven_menu_handle_t hMenu, ven_ui_menu_content_t *pMenuContent);

/**
 *  ven_ui_setMenuItem
 *
 *  @brief  Set single menu item data to the given menu handle
 *
 *  @param  hMenu   [in] Menu handle to be set data
 *  @param  index   [in] Item index of the menu item
 *  @param  pItem   [in] Menu item data to be set to the given menu handle
 *
 *  @retval VEN_UI_RET_SUCCESS   Set data successfully
 *          VEN_UI_RET_BAD_PARAM    Given hMenu is invalid, pItem is NULL, or index is invalid
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_setMenuItem(ven_menu_handle_t hMenu, u32 index, ven_ui_menu_item_t *pItem);

/**
 *  ven_ui_showMenu
 *
 *  @brief  Show menu on screen
 *
 *  @param  hMenu   [in] Menu handle to be shown
 *  @param  pSyncRet   [out]  Pointer to the structure to store user return value in synchronous mode.
 *  @param  ptVenReq   [in] Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given hMenu is invalid, ptVenReq is NULL, or data in ptVenReq is invalid
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note For asynchronous using, call back function in ptVenReq will be called after user interaction and pSyncRet will be ignore.
 */
ven_ui_ret_t ven_ui_showMenu(ven_menu_handle_t hMenu, ven_ui_show_menu_sync_ret_t *pSyncRet, ven_req_data_t *ptVenReq);

/**
 *  ven_ui_createDialog
 *
 *  @brief  Create dialog handle
 *
 *  @param  phDialog   [out] Popinter to store created dialog handle
 *
 *  @retval VEN_UI_RET_SUCCESS   Create successfully
 *          VEN_UI_RET_BAD_PARAM    Given phDialog is NULL
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_createDialog(ven_dialog_handle_t *phDialog);

/**
 *  ven_ui_releaseDialog
 *
 *  @brief  Release dialog handle
 *
 *  @param  hDialog   [in] Dialog handle to be released
 *
 *  @retval VEN_UI_RET_SUCCESS   Release successfully
 *          VEN_UI_RET_BAD_PARAM    Invalid menu handle
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_releaseDialog(ven_dialog_handle_t hDialog);

/**
 *  ven_ui_setDialogContent
 *
 *  @brief  Set dialog data to the given dialog handle
 *
 *  @param  hDialog   [in] Dialog handle to be set data
 *  @param  pDialogContent   [in] Dialog data to be set to the given dialog handle
 *
 *  @retval VEN_UI_RET_SUCCESS   Set data successfully
 *          VEN_UI_RET_BAD_PARAM    Given hDialog is invalid or pDialogContent is NULL
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_setDialogContent(ven_dialog_handle_t hDialog, ven_ui_dialog_content_t *pDialogContent);

/**
 *  ven_ui_showDialog
 *
 *  @brief  Show dialog on screen
 *
 *  @param  hDialog   [in] Dialog handle to be shown
 *  @param  pSyncRet   [out]  Pointer to the structure to store user return value in synchronous mode.
 *  @param  ptVenReq   [in] Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given hDialog is invalid, ptVenReq is NULL, or data in ptVenReq is invalid
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note For asynchronous using, call back function in ptVenReq will be called after user interaction and pSyncRet will be ignore.
 */
ven_ui_ret_t ven_ui_showDialog(ven_dialog_handle_t hDialog, ven_ui_show_dialog_sync_ret_t *pSyncRet, ven_req_data_t *ptVenReq);

/**
 *  ven_ui_updateDialogContentSync
 *
 *  @brief  Update asynchronous dialog content on screen (A dialog has to be shown prior to use this API)
 *
 *  @param  hDialog   [in] Dialog handle previously used to show dialog
 *  @param  pDialogContent   [in]  Pointer to the new dialog content
 *  @param  ptVenReq   [in] Request data structure, currently only supports synchronous way to update content
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given hDialog is invalid, ptVenReq is NULL, or data in ptVenReq is invalid
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note This update function can only be used with synchronous method. However, the dialog created and shown before
 *		  update happens has to be used in asynchronous method.
 */
ven_ui_ret_t ven_ui_updateDialogContentSync(ven_dialog_handle_t hDialog, ven_ui_dialog_content_t *pDialogContent, ven_req_data_t *ptVenReq);

/**
 *  ven_ui_createTextViewer
 *
 *  @brief  Create text viewer handle
 *
 *  @param  phTextViewer   [out] Popinter to store created text viewer handle
 *
 *  @retval VEN_UI_RET_SUCCESS   Create successfully
 *          VEN_UI_RET_BAD_PARAM    Given phTextViewer is NULL
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_createTextViewer(ven_textviewer_handle_t *phTextViewer);

/**
 *  ven_ui_releaseTextViewer
 *
 *  @brief  Release text viewer handle
 *
 *  @param  hTextViewer   [in] Text viewer handle to be released
 *
 *  @retval VEN_UI_RET_SUCCESS   Release successfully
 *          VEN_UI_RET_BAD_PARAM    Invalid text viewer handle
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_releaseTextViewer(ven_textviewer_handle_t hTextViewer);

/**
 *  ven_ui_setTextViewerContent
 *
 *  @brief  Set text viewer data to the given text viewer handle
 *
 *  @param  hTextViewer   [in] Text viewer handle to be set data
 *  @param  pTextViewerContent   [in] Text viewer data to be set to the given text viewer handle
 *
 *  @retval VEN_UI_RET_SUCCESS   Set data successfully
 *          VEN_UI_RET_BAD_PARAM    Given hTextViewer is invalid or pTextViewerContent is NULL
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_setTextViewerContent(ven_textviewer_handle_t hTextViewer, ven_ui_textviewer_content_t *pTextViewerContent);

/**
 *  ven_ui_showTextViewer
 *
 *  @brief  Show text viewer on screen
 *
 *  @param  hTextViewer   [in] Text viewer handle to be shown
 *  @param  pSyncRet   [out]  Pointer to the structure to store user return value in synchronous mode.
 *  @param  ptVenReq   [in] Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given hTextViewer is invalid, ptVenReq is NULL, or data in ptVenReq is invalid
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note For asynchronous using, call back function in ptVenReq will be called after user interaction and pSyncRet will be ignore.
 */
ven_ui_ret_t ven_ui_showTextViewer(ven_textviewer_handle_t hTextViewer, ven_ui_show_textviewer_sync_ret_t *pSyncRet, ven_req_data_t *ptVenReq);

/**
 *  ven_ui_updateTextViewerSync
 *
 *  @brief  Update asynchronous textviewer content on screen (A textviewer has to be shown prior to use this API)
 *
 *  @param  hTextViewer   [in] textviewer handle previously used to show textviewer
 *  @param  pTextViewerContent   [in]  Pointer to the new textviewer content
 *  @param  ptVenReq   [in] Request data structure, currently only supports synchronous way to update content
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given textviewer is invalid, ptVenReq is NULL, or data in ptVenReq is invalid
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note This update function can only be used with synchronous method. However, the textviewer created and shown before
 *		  update happens has to be used in asynchronous method.
 */
ven_ui_ret_t ven_ui_updateTextViewerSync(ven_textviewer_handle_t hTextViewer, ven_ui_textviewer_content_t *pTextViewerContent, ven_req_data_t *ptVenReq);

/**
 *  ven_ui_setInterruptLevel
 *
 *  @brief  Show UI interrupt level
 *
 *  @param  SdkHandle  [in]   The handle of SDK get from ven_handle_open()
 *  @param  intLevel   [out]  Interrupt level
 *  @param  ptVenReq     [in] The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                            It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given handle or interrupt level is wrong
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note For asynchronous using, call back function in ptVenReq will be called after user interaction and pSyncRet will be ignore.
 */
ven_ui_ret_t ven_ui_setInterruptLevel(ven_ui_interrupt_level_t intLevel, ven_req_data_t *ptVenReq);

/**
 *  ven_ui_getStatusBarIconSlot
 *
 *  @brief  Get a statusbar display icon free slot
 *
 *  @param  ptVenReq   [in] Request data structure, only SDK handle is required in this structure for now
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM   Invalid request data structure or SDK handle
 *          VEN_UI_RET_ALL_SLOT_OCCUPIED  All statusbar icon slot are occupied.
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_getStatusBarIconSlot(ven_req_data_t *ptVenReq);

/**
 *  ven_ui_releaseStatusBarIconSlot
 *
 *  @brief  Free up the statusbar display icon slot occupied by this task
 *
 *  @param  ptVenReq   [in] Request data structure, only SDK handle is required in this structure for now
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM   Invalid request data structure or SDK handle
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_releaseStatusBarIconSlot(ven_req_data_t *ptVenReq);

/**
 *  ven_ui_drawStatusBarIcon
 *
 *  @brief  Draw image raw data to the open statusbar icon slot aquired
 *
 *  @param  ptVenReq   [in] Request data structure, only SDK handle is required in this structure for now
 *  @param  pDrawIconInfo   [in] Draw icon request data structure. Please feed with 12x12 image raw data.
 *                               (supports animated GIF for animation usage)
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM   Invalid request data structure or SDK handle
 *          VEN_UI_RET_NOT_ALLOWED Current SDK handle did not get an open statusbar icon slot
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_drawStatusBarIcon(ven_ui_statusbar_draw_icon_req_t *pDrawIconInfo, ven_req_data_t *ptVenReq);
/**
 *  ven_ui_drawStatusBarImage
 *
 *  @brief  Draw image (by file) to the open statusbar icon slot aquired
 *
 *  @param  ptVenReq   [in] Request data structure, only SDK handle is required in this structure for now
 *  @param  ven_ui_statusbar_image_t [in] the image ID , Now the supported ID are
 *                        VEN_UI_STATUSBAR_IMAGE_JAVA = 1,   
 *                        VEN_UI_STATUSBAR_IMAGE_SKYENGINE  = 2, 
 *                          And the invalid ID will be
 *                        VEN_UI_STATUSBAR_IMAGE_NULL = 0,
 *                        VEN_UI_STATUSBAR_IMAGE_NUM
 * 
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM   Invalid request data structure or SDK handle
 *          VEN_UI_RET_NOT_ALLOWED Current SDK handle did not get an open statusbar icon slot
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_drawStatusBarImage(ven_ui_statusbar_image_t tStatusBarImage, ven_req_data_t *ptVenReq);
/**
 *  ven_ui_drawSoftkey
 *
 *  @brief  Draw softkey on screen
 *
 *  @param  SdkHandle       [in] The handle of SDK get from ven_handle_open()
 *  @param  pSoftkeyContent [in] Softkey data to be set to softkey
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given hSoftkey is invalid, ptVenReq is NULL, or data in ptVenReq is invalid
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_ui_ret_t ven_ui_drawSoftkey(u32 SdkHandle, ven_ui_softkey_content_t *pSoftkeyContent);

/**
 *  ven_ui_setBacklightBehavior
 *
 *  @brief  Show UI LCD backlight behavior
 *
 *  @param  blkBehavior  [in] LCD backlight behavior
 *  @param  ptVenReq     [in] The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                            It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given handle or interrupt level is wrong
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note For asynchronous using, call back function in ptVenReq will be called after user interaction and pSyncRet will be ignore.
 */
ven_ui_ret_t ven_ui_setBacklightBehavior(ven_ui_backlight_behavior_t blkBehavior, ven_req_data_t *ptVenReq);

/**
 *  ven_ui_setBacklight
 *
 *  @brief  Set UI LCD backlight
 *
 *  @param  blkLevel  [in] LCD backlight level
 *  @param  blkDuration  [in] LCD backlight duration
 *  @param  ptVenReq     [in] The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                            It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_UI_RET_SUCCESS   Send request successfully
 *          VEN_UI_RET_BAD_PARAM    Given handle or interrupt level is wrong
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note For asynchronous using, call back function in ptVenReq will be called after user interaction and pSyncRet will be ignore.
 */
ven_ui_ret_t ven_ui_setBacklight(ven_ui_backlight_level_t blkLevel, ven_ui_backlight_duration_t blkDuration, ven_req_data_t *ptVenReq);

ven_ui_ret_t ven_ui_getBacklightInfo(ven_ui_backlight_info *bklInfo, ven_req_data_t *ptVenReq);

ven_ui_ret_t ven_ui_EnableLaunchKeyguard(bool bEnableLaunch, ven_req_data_t* ptVenReq);

typedef struct
{
    ven_ui_backlight_info bklInfo;
    ven_ui_ret_t RetCode;
} ven_ui_get_backlight_info_rsp_t;

ven_ui_datalink_ret_t ven_ui_checkDataLinkstatus(ven_ui_datalink_t tSelectSim, ven_common_sim_id_t *tSelectSimID);


/**
 *  ven_ui_getAppletStatus
 *
 *  @brief  get status of given applet
 *
 *  @param  iVen_ui_applet_id  [in] Applet id
 *  @param  pAppletInfo        [in] The pointer of applet status of given applet id
 *
 *  @retval VEN_UI_RET_SUCCESS        Successfully
 *          VEN_UI_RET_BAD_PARAM      Given applet id or pAppletInfo is null
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note For asynchronous using, call back function in ptVenReq will be called after user interaction and pSyncRet will be ignore.
 */
ven_ui_ret_t ven_ui_getAppletStatus(iVen_ui_applet_id AppId, iVen_ui_applet_status_t *pAppletInfo, ven_req_data_t *ptVenReq);

/**
 *  ven_ui_queryAppletExistStatus
 *
 *  @brief  check the iVen_ui_applet_exist_status queried from ven_ui_getAppletStatus
 *
 *  @param  iVen_ui_applet_status_t  [in] Queried applet status from ven_ui_getAppletStatus(...)
 *  @param  eStatus                  [in] The target status that wants to be confirmed
 *  @param  pAnswer                  [out] Answer of the status, true : the applet contains the given status. false : otherwise
 *
 *  @retval VEN_UI_RET_SUCCESS        Successfully
 *          VEN_UI_RET_BAD_PARAM      Given null parameter(s)
 *
 */
ven_ui_ret_t ven_ui_queryAppletExistStatus( iVen_ui_applet_status_t *pAppletInfo, iVen_ui_applet_exist_status eStatus , bool *pAnswer);

#endif /* __VEN_UI_H_ */

