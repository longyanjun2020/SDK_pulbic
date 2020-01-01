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

#ifndef __MMI_QQAPP_PRIV_H__
#define __MMI_QQAPP_PRIV_H__

#ifdef __cplusplus
extern "C" {

#endif
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_common_vtm.h"
#include "mmi_mae_textmodel.h"
#include "mmi_rs_macro_struct.h"
#include "mmi_qqapp.h"
#include "mmi_qqapp_id.h"
#include "mmi_qqapp.rs"
#include "mmi_qqapp_util.h"
#include "mmi_event.h"
#include "UsbApp_textlabel.h"
#include "QQApp_resource.h"

// User Code Begin:APP:INCLUDE
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
// User Code End

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    IWidget         *pIQQLoadingImageWdg;
}QQAppQQ_WND_LOADINGWdgList_t;

typedef struct
{
    IWidget         *pIQQIDTxtWdg;
    IWidget         *pIQQIDInputTxtWdg;
    IWidget         *pIQQPswTxtWdg;
    IWidget         *pIQQPswInputTxtWdg;
    IWidget         *pIQQIDHistoryButtonWdg;
    IWidget         *pIQQRemPswTxtWdg;
    IWidget         *pIQQRemPswSwitchIconWdg;
    IWidget         *pIQQRecvGroupMsgTxtWdg;
    IWidget         *pIQQRecvGroupMsgSwitchIconWdg;
    IWidget         *pIQQHideLoginTxtWdg;
    IWidget         *pIQQHideLoginSwitchIconWdg;
    IWidget         *pIQQVibrateOnTxtWdg;
    IWidget         *pIQQVibrateOnSwitchIconWdg;
    IWidget         *pIQQSoundOnTxtWdg;
    IWidget         *pIQQSoundOnSwitchIconWdg;
}QQAppQQ_WND_LOGINWdgList_t;

typedef struct
{
    VectorClass_t           *pQQFocusWdgList;
    WidgetHandler_t         IDInputWdgHandler;
    WidgetHandler_t         IDHistoryButtonHandler;
    WidgetHandler_t         pswInputWdgHandler;
    WidgetHandler_t         remPswTxtWdgMdLsn;
    WidgetHandler_t         remPswSwitchIconHandler;
    WidgetHandler_t         recvGroupMsgTxtWdgMdLsn;
    WidgetHandler_t         recvGroupMsgSwitchIconHandler;
    WidgetHandler_t         hideLoginTxtWdgMdLsn;
    WidgetHandler_t         hideLoginSwitchIconHandler;
    WidgetHandler_t         vibrateOnTxtWdgMdLsn;
    WidgetHandler_t         vibrateOnSwitchIconHandler;
    WidgetHandler_t         soundOnTxtWdgMdLsn;
    WidgetHandler_t         soundOnSwitchIconHandler;
    u32                     selectedWdg;
    QQAppQQ_WND_LOGINWdgList_t         tQQWdgList;
}QQWndLoginData_t;

typedef struct
{
    OptionMenuWdgList_t       tVtmQQ_WND_LOGIN_OPTIONMENUWdgList;
}QQAppQQ_WND_LOGIN_OPTIONMENUWdgList_t;

typedef struct
{
    IWidget         *pIQQOperateInstructInputTextWdg;
}QQAppQQ_WND_OPERATE_CMDWdgList_t;

typedef struct
{
    IWidget         *pIShowInfoTextWdg;
    IWidget         *pICodesImageWdg;
    IWidget         *pICodesInputWdg;
    void            *pImageData;
}QQAppQQ_WND_VERIFYWdgList_t;

typedef struct
{
    IWidget         *pILoginingImageWdg;
}QQAppQQ_WND_LOGININGWdgList_t;


typedef struct
{
    TabMenuWdgList_t    tVtmQQ_WND_SHOWLISTWdgLst;
	IWidget         	*pMsgImageWdg;
}QQAppQQ_WND_SHOWLISTData_t;

typedef struct
{
    IWidget         *pIShowReceivedMessageInputWdg;
    u32             uUserId;
    u32             uMsgType;
    MAE_WChar       *pInitStr;
    u8              *pNickName;
}QQAppQQ_WND_READMESSAGEWdgList_t;

typedef struct
{
    u32             userId;
    u32             msgType;
    u8              *pNickName;
} QQApp_WND_SendMsgInitData_t;

typedef struct
{
    IWidget         *pTitleWdg;
    IWidget         *pIQQSendMessageInputWdg;
    MAE_WChar       *pNickName;
    u32             uUserId;
    u32             uMsgType;
}QQAppQQ_WND_SENDMESSAGEData_t;

typedef struct
{
    OptionMenuWdgList_t       tVtmQQ_WND_SEND_MESSAGE_OPTIONMENUWdgList;
}QQAppQQ_WND_SENDMESSAGE_OPTIONMENUWdgList_t;

typedef struct
{
    MenuWdgList_t   tVtmQQ_WND_PresetMessageWdgList;
}QQAppQQ_WND_PRESET_MESSAGEData_t;

typedef struct
{
    IWidget         *pIShowUserInfoInputWdg;
}QQAppQQ_WND_USER_INFOWdgList_t;

typedef struct
{
    IWidget         *pIMessageHistoryInputWdg;
    VectorClass_t   *pVector;
	u8              *pBuffer;
	u32				 uLen;
    u32              nCurPage;
    u32              nTotalPage;
}QQAppQQ_WND_MESSAGE_HISTORYData_t;

typedef struct
{
    OptionMenuWdgList_t        tVtmQQ_WND_MESSAGE_HISTORY_OPTIONMENUWdgList;
}QQAppQQ_WND_MESSAGE_HISTORY_OPTIONMENUWdgList_t;

typedef struct
{
    MenuWdgList_t   tVtmQQ_WND_FriendsAdminWdgLst;
}QQAppQQ_WND_FRIENDS_ADMINData_t;

typedef struct
{
    IWidget         *pIQQIDInputWdg;
    IWidget         *pIQQIDTxtWdg;
}QQAppQQ_WND_ADD_BUDDYData_t;

typedef struct
{
    IWidget         *pIQQSearchResultTextWdg;
}QQAppQQ_WND_SEARCH_RESULTWdgList_t;

typedef struct
{
    OptionMenuWdgList_t       tVtmQQ_WND_SEARCH_RESULT_OPTIONMENUWdgList;
}QQAppQQ_WND_SEARCH_RESULT_OPTIONMENUWdgList_t;

typedef struct
{
    PopUpSelectWdgList_t    tVtmQQ_WND_POPUPSELECT_WdgLst;
}QQAppQQ_WND_POPUPSELECTData_t;

typedef struct
{
    MenuWdgList_t   tVtmQQ_WND_BasicSettingWdgLst;
}QQAppQQ_WND_BASIC_SETTINGData_t;

typedef enum
{
    QQAPP_OPT_NONE = 0,
    QQAPP_OPT_LOGIN,
    QQAPP_OPT_DEL_BUDDY,
    QQAPP_OPT_BLOCK_BUDDY,
    QQAPP_OPT_ADD_BUDDY,
} QQAppOperationType_e;

typedef struct
{
    IWidget         *pINumberTextWdg;
    IWidget         *pIQuestionTextWdg;
    IWidget         *pIAnswerInputWdg;
}QQAppQQ_WND_ANSWER_QUESTIONWdgList_t;

typedef struct
{
    // User Code Begin:APP:DATA
    APPLET_BASE_ELEMENTS;

//    u32                         venHandle;
    u32                         nBuddyHighlight;
    u32                         eTabViewType;
    u32                         nPopUpSelectType;
    u32                         nCurOperationNumber;

    QQAppOperationType_e        nCurOperation;
    COMMON_SIM_CARD_STATUS_e    eSimStatus;                // check sim status

    u8                          isClose;
    u8                          nActiveSimId;
    u8                          nFocusItemId;   // focus item in menu widget
    boolean                     bBlinkFlag;
    boolean                     bHandleEndKey;
	boolean                     bSelectedQQLogout;
	boolean                     bExit;
    // User Code End
} QQAppAppData_t;

// User Code Begin:APP:DataType
// User Code End

/** QQAppConstructorCb
* @brief        Applet constructor function

* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter

* @retval       MAE_RET_SUCCESS     If success
* @retval       Others              failed

*/
MAE_Ret QQAppConstructorCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** QQAppDestructorCb
* @brief        Applet destructor function

* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter

* @retval       MAE_RET_SUCCESS     If success
* @retval       Others              failed

*/
MAE_Ret QQAppDestructorCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** QQAppStartCb
* @brief        Applet start function(when receive MAE_EVT_APP_START)

* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter

* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function

*/
boolean QQAppStartCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** QQAppStopCb
* @brief        Applet stop function(when receive MAE_EVT_APP_STOP)

* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter

* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function

*/
boolean QQAppStopCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** QQAppSuspendCb
* @brief        Applet suspend function(when receive MAE_EVT_APP_SUSPEND)

* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter

* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function

*/
MAE_Ret QQAppSuspendCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

boolean QQAppPreHookCB(IApplet * pApplet,u32 evt,u32 param1,u32 param2);

/** QQAppResumeCb
* @brief        Applet stop function(when receive MAE_EVT_APP_RESUME)

* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter

* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function

*/
MAE_Ret QQAppResumeCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** QQAppKeyPressCb
* @brief        Handle key press function(when receive MAE_EVT_KEY_PRESS)

* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter

* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function

*/
boolean QQAppKeyPressCb
(
    IApplet	*pApplet,
    u32		nEvt,
    u32		nParam1,
    u32		nParam2
);

/** QQAppQQ_WND_LOADINGWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_LOADINGWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_LOGINWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_LOGINWndHdl
(
    void	*pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void	*pWndData,
    u32	nWndInitParam
);

/** QQAppQQ_WND_VERIFYWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_VERIFYWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_LOGINWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_LOGINWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_LOGIN_OPTIONMENUWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_LOGIN_OPTIONMENUWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_OPERATE_CMDWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_OPERATE_CMDWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_VERIFYWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_VERIFYWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_LOGININGWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_LOGININGWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQApp_QQ_WND_SHOWLISTWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQApp_QQ_WND_SHOWLISTWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQApp_QQ_WND_READMESSAGEWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQApp_QQ_WND_READMESSAGEWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_MAINMENUWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_MAINMENUWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_AddBuddyReqOptionMenuWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_AddBuddyReqOptionMenuWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );


/** QQAppQQ_WND_SENDMESSAGEWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_SENDMESSAGEWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_SENDMESSAGELOGIN_OPTIONMENUWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_SENDMESSAGE_OPTIONMENUWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_WORDS_COMMON_USEWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_PRESET_MESSAGEWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_USER_INFOWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_USER_INFOWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_MESSAGE_HISTORYWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_MESSAGE_HISTORYWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_SENDMESSAGELOGIN_OPTIONMENUWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_MESSAGE_HISTORY_OPTIONMENUWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_SEARCH_AND_APPENDWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_ADD_BUDDYWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_SEARCH_RESULTWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_SEARCH_RESULTWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_SEARCH_RESULT_OPTIONMENUWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_SEARCH_RESULT_OPTIONMENUWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_POPUPSELECTWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_POPUPSELECTWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

/** QQAppQQ_WND_SETTINGWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_SETTINGWndHdl
(
 void	*pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void	*pWndData,
 u32	nWndInitParam
 );

// User Code Begin:APP:UserCb

/** QQAppQQ_WND_DualSimHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_DualSimHdl
(void *pCusHandle,
 const WindowMsg_t *pWndMsg,
 void *pWndData,
 u32 nWndInitParam);

/** QQAppQQ_WND_ANSWER_QUESTIONWndHdl
* @brief        Calculator window handle function

* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE

* @retval       MAE_Ret             Success.
* @retval       other               Failed.

*/
MAE_Ret QQAppQQ_WND_ANSWER_QUESTIONWndHdl
(
 void                *pCusHandle,
 const WindowMsg_t   *pWndMsg,
 void                *pWndData,
 u32                 nWndInitParam
 );

// User Code End

#ifdef __cplusplus
}
#endif

#endif /* __MMI_QQAPP_PRIV_H__ */

