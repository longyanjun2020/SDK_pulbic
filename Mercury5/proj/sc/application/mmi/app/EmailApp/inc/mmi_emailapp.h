////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

	// User Code Begin:APP:INFO
	// User Code End

#ifndef __MMI_EMAILAPP_H__
#define __MMI_EMAILAPP_H__


/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_common_vtm.h"

	// User Code Begin:APP:INCLUDE
#include "mmi_base_util.h"
//#include "nccemail.h"
#include "mmi_emailapp_id.h"
	// User Code End

/*=============================================================*/
// Extern definition
/*=============================================================*/
	// User Code Begin:APP:EXTERN
	// User Code End

/*=============================================================*/
// Macro definition
/*=============================================================*/
	// User Code Begin:APP:MACRO
#ifndef __NAND__
#define EMAIL_ROOT_CHECK_SDCARD
#endif
	// User Code End

/*=============================================================*/
// Data type definition
/*=============================================================*/


typedef enum
{
	EMAIL_WND_ACCOUNTLIST_BEGIN = APP_WDG_START,
	EMAIL_WND_ACCOUNTLIST_END
}EmailAppEMAIL_WND_ACCOUNTLIST_e;

typedef struct
{
	MenuWdgList_t     tVtmEMAIL_WND_ACCOUNTLISTWdgLst;
}EmailAppEMAIL_WND_ACCOUNTLISTWdgList_t;

typedef enum
{
	EMAIL_WND_ACCOUTLIST_OPTIONMENU_BEGIN = APP_WDG_START,
	EMAIL_WND_ACCOUTLIST_OPTIONMENU_END
}EmailAppEMAIL_WND_ACCOUTLIST_OPTIONMENU_e;

typedef struct
{
	OptionMenuWdgList_t     tVtmEMAIL_WND_ACCOUTLIST_OPTIONMENUWdgLst;
}EmailAppEMAIL_WND_ACCOUTLIST_OPTIONMENUWdgList_t;

typedef enum
{
	EMAIL_WND_NEWACCOUNT_BEGIN = APP_WDG_START,
	EMAIL_WND_NEWACCOUNT_END
}EmailAppEMAIL_WND_NEWACCOUNT_e;

typedef struct
{
	MenuWdgList_t     tVtmEMAIL_WND_NEWACCOUNTWdgLst;
}EmailAppEMAIL_WND_NEWACCOUNTWdgList_t;

typedef enum
{
	EMAIL_WND_PUBLICINPUT_BEGIN = APP_WDG_START,
	EMAIL_WND_PUBLICINPUT_END
}EmailAppEMAIL_WND_PUBLICINPUT_e;

typedef struct
{
	InputVtmWdgList_t     tVtmEMAIL_WND_PUBLICINPUTWdgLst;
}EmailAppEMAIL_WND_PUBLICINPUTWdgList_t;

typedef enum
{
	EMAIL_WND_PUBLICINPUTOPTION_BEGIN = APP_WDG_START,
	EMAIL_WND_PUBLICINPUTOPTION_END
}EmailAppEMAIL_WND_PUBLICINPUTOPTION_e;

typedef struct
{
	OptionMenuWdgList_t     tVtmEMAIL_WND_PUBLICINPUTOPTIONWdgLst;
}EmailAppEMAIL_WND_PUBLICINPUTOPTIONWdgList_t;

typedef enum
{
	EMAIL_WND_EDITACCOUNT_BEGIN = APP_WDG_START,
	EMAIL_WND_EDITACCOUNT_END
}EmailAppEMAIL_WND_EDITACCOUNT_e;

typedef struct
{
	TabMenuWdgList_t     tVtmEMAIL_WND_EDITACCOUNTWdgLst;
}EmailAppEMAIL_WND_EDITACCOUNTWdgList_t;

typedef enum
{
	EMAIL_WND_SETTING_BEGIN = APP_WDG_START,
	EMAIL_WND_SETTING_END
}EmailAppEMAIL_WND_SETTING_e;

typedef struct
{
	TabMenuWdgList_t     tVtmEMAIL_WND_SETTINGWdgLst;
}EmailAppEMAIL_WND_SETTINGWdgList_t;

typedef enum
{
	EMAIL_WND_POPUPSELECT_BEGIN = APP_WDG_START,
	EMAIL_WND_POPUPSELECT_END
}EmailAppEMAIL_WND_POPUPSELECT_e;

typedef struct
{
	PopUpSelectWdgList_t     tVtmEMAIL_WND_POPUPSELECTWdgLst;
}EmailAppEMAIL_WND_POPUPSELECTWdgList_t;

typedef enum
{
	EMAIL_WND_POPUPINPUT_BEGIN = APP_WDG_START,
	EMAIL_WND_POPUPINPUT_END
}EmailAppEMAIL_WND_POPUPINPUT_e;

typedef struct
{
	PopUpInputWdgList_t     tVtmEMAIL_WND_POPUPINPUTWdgLst;
}EmailAppEMAIL_WND_POPUPINPUTWdgList_t;

typedef enum
{
	EMAIL_WND_MAIN_MENU_BEGIN = APP_WDG_START,
	EMAIL_WND_MAIN_MENU_END
}EmailAppEMAIL_WND_MAIN_MENU_e;

typedef struct
{
	MenuWdgList_t     tVtmEMAIL_WND_MAIN_MENUWdgLst;
}EmailAppEMAIL_WND_MAIN_MENUWdgList_t;

typedef enum
{
	EMAIL_WND_EMAIL_EDITOR_BEGIN = APP_WDG_START,
	// User Code Begin
	EMAIL_IMG_WDG_ATTACH_ICON,
	EMAIL_TXT_WDG_SIZE,
	EMAIL_TXT_WDG_CONTAINER,	//not auto genereated by tools
	EMAIL_TXT_WDG_SCROLLBAR,	//not auto genereated by tools
	// User Code End
	EMAIL_TXT_WDG_CONTENT,
	EMAIL_TXT_WDG_SUBJECT,
	EMAIL_TXT_WDG_BCC,
	EMAIL_TXT_WDG_CC,
	EMAIL_TXT_WDG_TO,
	EMAIL_TXT_WDG_FROM,
	EMAIL_EDITOR_VIEW_PORT_WDG,
	EMAIL_WND_EMAIL_EDITOR_END
}EmailAppEMAIL_WND_EMAIL_EDITOR_e;

typedef struct
{

	IWidget         *pIEMAIL_TXT_WDG_CONTENTWdg;
	IWidget         *pIEMAIL_TXT_WDG_SUBJECTWdg;
	IWidget         *pIEMAIL_TXT_WDG_BCCWdg;
	IWidget         *pIEMAIL_TXT_WDG_CCWdg;
	IWidget         *pIEMAIL_TXT_WDG_TOWdg;
	IWidget         *pIEMAIL_TXT_WDG_FROMWdg;
	IWidget         *pIEMAIL_EDITOR_VIEW_PORT_WDGWdg;
}EmailAppEMAIL_WND_EMAIL_EDITORWdgList_t;

typedef enum
{
	EMAIL_WND_EMAIL_EDITOR_OPTION_MENU_BEGIN = APP_WDG_START,
	EMAIL_WND_EMAIL_EDITOR_OPTION_MENU_END
}EmailAppEMAIL_WND_EMAIL_EDITOR_OPTION_MENU_e;

typedef struct
{
	OptionMenuWdgList_t     tVtmEMAIL_WND_EMAIL_EDITOR_OPTION_MENUWdgLst;
}EmailAppEMAIL_WND_EMAIL_EDITOR_OPTION_MENUWdgList_t;

typedef enum
{
	EMAIL_WND_EMAILBOXLIST_BEGIN = APP_WDG_START,
	EMAIL_WND_EMAILBOXLIST_END
}EmailAppEMAIL_WND_EMAILBOXLIST_e;

typedef struct
{
	TabMenuWdgList_t     tVtmEMAIL_WND_EMAILBOXLISTWdgLst;
}EmailAppEMAIL_WND_EMAILBOXLISTWdgList_t;

typedef enum
{
	EMAIL_WND_BOXLISTOPTION_BEGIN = APP_WDG_START,
	EMAIL_WND_BOXLISTOPTION_END
}EmailAppEMAIL_WND_BOXLISTOPTION_e;

typedef struct
{
	OptionMenuWdgList_t     tVtmEMAIL_WND_BOXLISTOPTIONWdgLst;
}EmailAppEMAIL_WND_BOXLISTOPTIONWdgList_t;

typedef enum
{
	EMAIL_WND_MAILBOX_EDITOR_BEGIN = APP_WDG_START,
	// User Code Begin
	EMAIL_MAILBOX_EDITOR_PROPCONTAINER,
	EMAIL_MAILBOX_EDITOR_ABSCONTAINER,
	// User Code End
	EMAIL_MAILBOX_EDITOR_MENU_WDG,
	EMAIL_MAILBOX_EDITOR_BG_IMG_WDG,
	EMAIL_MAILBOX_EDITOR_BUTTON_WDG,
	EMAIL_MAILBOX_EDITOR_INPUT_WDG,
	EMAIL_WND_MAILBOX_EDITOR_END
}EmailAppEMAIL_WND_MAILBOX_EDITOR_e;

typedef struct
{

	IWidget         *pIEMAIL_MAILBOX_EDITOR_MENU_WDGWdg;
	IWidget         *pIEMAIL_MAILBOX_EDITOR_BG_IMG_WDGWdg;
	IWidget         *pIEMAIL_MAILBOX_EDITOR_BUTTON_WDGWdg;
	IWidget         *pIEMAIL_MAILBOX_EDITOR_INPUT_WDGWdg;
}EmailAppEMAIL_WND_MAILBOX_EDITORWdgList_t;

typedef enum
{
	EMAIL_MAILBOX_WND_OPTION_MENU_BEGIN = APP_WDG_START,
	MAILBOX_EDITOR_OPTION_MENU_WDG,
	EMAIL_MAILBOX_WND_OPTION_MENU_END
}EmailAppEMAIL_MAILBOX_WND_OPTION_MENU_e;

typedef struct
{

	IWidget         *pIMAILBOX_EDITOR_OPTION_MENU_WDGWdg;
}EmailAppEMAIL_MAILBOX_WND_OPTION_MENUWdgList_t;

typedef enum
{
	EMAIL_WND_ATTACH_EDITOR_BEGIN = APP_WDG_START,
	EMAIL_WND_ATTACH_EDITOR_MENU_WDG,
	EMAIL_WND_ATTACH_EDITOR_END
}EmailAppEMAIL_WND_ATTACH_EDITOR_e;

typedef struct
{

	IWidget         *pIEMAIL_WND_ATTACH_EDITOR_MENU_WDGWdg;
}EmailAppEMAIL_WND_ATTACH_EDITORWdgList_t;

typedef enum
{
	EMAIL_ATTACH_EDITOR_WND_OPTION_MENU_BEGIN = APP_WDG_START,
	EMAIL_ATTACH_EDITOR_WND_OPTION_MENU_END
}EmailAppEMAIL_ATTACH_EDITOR_WND_OPTION_MENU_e;

typedef struct
{
	OptionMenuWdgList_t     tVtmEMAIL_ATTACH_EDITOR_WND_OPTION_MENUWdgLst;
}EmailAppEMAIL_ATTACH_EDITOR_WND_OPTION_MENUWdgList_t;

typedef struct
{
	APPLET_BASE_ELEMENTS;
	// User Code Begin:APP:DATA

    HistoryInfo_t                   MainMenuHistory;
    VectorClass_t                   *pIMainVectorModel;            //Main Menu Vector, Private Main Menu Vector

    IWidget                         *pProcessWdg;
    //account list
    T_EMAIL_Account_Config          *pAccountCfg;
    T_EMAIL_FS_ACCOUNT_HEAD_LIST    *pAccountHeadList;
    u32                             u32AvailableAccNum;

    u32                             curOpenedEmailAccountID;
    u32                             eCurrentEditorType;
    u32                             eTabViewType;
    u32                             nSelectedID;
    u32                             nHighlight;
    boolean                         isNewAccount;
    T_EMAIL_Account_Setting         *pEmailSetting;
	T_EMAIL_Account_Setting         *pEmailSaveSetting;

    u32                              BoxId;
    HistoryInfo_t                    BoxListHistory;
    VectorClass_t                    *pEmailListVectorModel;            //Email List Vector
    EmailMarkType_e                  MarkModeType;
    COMMON_SIM_CARD_STATUS_e         eSIMCardStatus;
    u32                              publicMaxLen;
    EMAILSRV_ErrCode                 sentErrCode;
    EMAILSRV_ErrCode                 receiveErrCode;
    EMAIL_OPERATE_TYPE               EmailOperation;
    boolean                          bHandleEndKey;
	boolean                          bSuspend;
	boolean                          bCloseAp;
    boolean                          bResetMusicMode;
    boolean                          bPlayMusic;
    EmailStartData_t                 *pEmStartData;
	u8                               u8DefaultAccountId;
    u32                             uPrevTotalMail;

	// User Code End
} EmailAppAppData_t;
	// User Code Begin:APP:DataType


	// User Code End

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** EmailAppNew
* @brief        New function for create EmailApp Applet
*
* @param[in]    nClsId              EmailApp class id
* @param[in]    ppObj               The pointer of pointer of Applet
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       other               Fail
*
*/
MAE_Ret EmailAppNew
(
    MAE_ClsId   nClsId,
    void	**ppObj
);

void EmailAppPreNew(void);

void EmailAppStartApFree(EmailStartData_t **ppInitData);

/** EmailAppConstructorCb
* @brief        Applet constructor function
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_RET_SUCCESS     If success
* @retval       Others              failed
*
*/
MAE_Ret EmailAppConstructorCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** EmailAppDestructorCb
* @brief        Applet destructor function
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_RET_SUCCESS     If success
* @retval       Others              failed
*
*/
MAE_Ret EmailAppDestructorCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** EmailAppStartCb
* @brief        Applet start function(when receive MAE_EVT_APP_START)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean EmailAppStartCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** EmailAppStopCb
* @brief        Applet stop function(when receive MAE_EVT_APP_STOP)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean EmailAppStopCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** EmailAppSuspendCb
* @brief        Applet suspend function(when receive MAE_EVT_APP_SUSPEND)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
MAE_Ret EmailAppSuspendCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** EmailAppResumeCb
* @brief        Applet stop function(when receive MAE_EVT_APP_RESUME)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
MAE_Ret EmailAppResumeCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** EmailAppKeyPressCb
* @brief        Handle key press function(when receive MAE_EVT_KEY_PRESS)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean EmailAppKeyPressCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** EmailAppEMAIL_WND_ACCOUNTLISTWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_ACCOUNTLISTWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_ACCOUTLIST_OPTIONMENUWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_ACCOUTLIST_OPTIONMENUWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_NEWACCOUNTWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_NEWACCOUNTWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_PUBLICINPUTWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_PUBLICINPUTWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_PUBLICINPUTOPTIONWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_PUBLICINPUTOPTIONWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_EDITACCOUNTWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_EDITACCOUNTWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_SETTINGWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_SETTINGWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_POPUPSELECTWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_POPUPSELECTWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_POPUPINPUTWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_POPUPINPUTWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_MAIN_MENUWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_MAIN_MENUWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_EMAIL_EDITORWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_EMAIL_EDITORWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_EMAIL_EDITOR_OPTION_MENUWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_EMAIL_EDITOR_OPTION_MENUWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_EMAILBOXLISTWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_EMAILBOXLISTWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_BOXLISTOPTIONWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_BOXLISTOPTIONWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_MAILBOX_EDITORWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_MAILBOX_EDITORWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_MAILBOX_WND_OPTION_MENUWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_MAILBOX_WND_OPTION_MENUWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_WND_ATTACH_EDITORWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_WND_ATTACH_EDITORWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);
/** EmailAppEMAIL_ATTACH_EDITOR_WND_OPTION_MENUWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret EmailAppEMAIL_ATTACH_EDITOR_WND_OPTION_MENUWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);

	// User Code Begin:APP:UserCb
	// User Code End

#endif /* __MMI_EMAILAPP_H__ */

