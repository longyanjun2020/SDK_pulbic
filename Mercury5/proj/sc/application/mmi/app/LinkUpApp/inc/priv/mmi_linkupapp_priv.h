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
* @file    linkup_bmiapp_priv.h
* @version
* @brief   LINKUP applet private header file
*
*/
#ifndef __MMI_LINKUPAPP_PRIV_H__
#define __MMI_LINKUPAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_srv_clock.h"
#include "mmi_common_vtm.h"
#include "mmi_common_dialog.h"
#include "mmi_common_rai_id.h"
#include "linkupapp_resource.h"
#include "mmi_srv_audio.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define LU_GAME_TIME_LIMIT 166
#define LU_DIALOG_AUTOCLOSE_TIME 800
#define LU_BLANK_STATE (100)
#define LU_INVAILD_ELEMENT (12)
#define LU_INVAILD_ELEMENT_ONE (-1)
#define LU_GAME_MAGIC_REMOVE_TOTAL_COUNT  3
#define LU_GAME_MAGIC_SHUFFLES_TOTAL_COUNT  3
#define LU_GAME_MAGIC_TWINS_TOTAL_COUNT  3
#define LU_GAME_TIME_COUNTDOWN_START 40
#define LU_GAME_TIME_INTERVEL 500




/*=============================================================*/
// Data type definition
/*=============================================================*/
enum
{
     LU_LINETYPE_HORIZONTAL = 0,
     LU_LINETYPE_STRAIGHT,
     LU_LINETYPE_ONE_CORNER,
     LU_LINETYPE_TWO_CORNER,
};

typedef struct
{
    s32            *pdata;
} LinkUpSaveGameData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    u8                  nDisNodeNum;
	boolean				bIsSound;
} LinkUpAppData_t;

typedef struct
{
    IWidget         *pIValueBgImageWdg;
    IWidget         *pIImageWdg;
    IWidget         *pMChessboardMenuWdg;
    IWidget         *pIHLineOneImageWdg;
    IWidget         *pIHLineTwoImageWdg;
    IWidget         *pIVLineOneImageWdg;
    IWidget         *pIVLineTwoImageWdg;
    IWidget         *pIRedRectangleImageOneWdg;
    IWidget         *pIRedRectangleImageTwoWdg;
    IWidget         *pIShufflesMagicNuberImageWdg;
    IWidget         *pIFindTwinsMagicNuberImageWdg;
    IWidget         *pIRemoveTwinsMagicNuberImageWdg;
    IWidget         *pBReturnButtonWdg;
    IWidget         *pBShufflesButtonWdg;
    IWidget         *pBRemoveTwinsButtonWdg;
    IWidget         *pBFindTwinsButtonWdg;
    IWidget         *pPTimeProgressWdg;
}LinkUpGameWdgList_t;


typedef struct
{
    IWidget         *pIValueBgImageWdg;
    IWidget         *pILogoImageWdg;
    IWidget         *pBPlayButtonWdg;
    IWidget         *pBOptionsButtonWdg;
    IWidget         *pBHelpButtonWdg;
    IWidget         *pBQuitButtonWdg;
}LinkUpContentWdgList_t;

typedef struct
{
    IWidget         *pIOptionsSoundButtonWdg;
    IWidget         *pIBgWdg;
    IWidget         *pBCloseButtonWdg;
}LinkUpOptionsWdgList_t;

typedef struct
{
    IWidget         *pIHelpImage1Wdg;
    IWidget         *pIHelpImage2Wdg;
    IWidget         *pIHelpImage3Wdg;
    IWidget         *pIBgWdg;
    IWidget         *pBNextButtonWdg;
    IWidget         *pBPreviousButtonWdg;
    IWidget         *pBCloseButtonWdg;
}LinkUpHelpWdgList_t;

typedef struct
{
    u32             nIsSound;
}LinkUpOptionsData_t;

typedef struct
{
    IImage          *pAUnpressImage[14];
    IImage          *pApressImage[14];
}LinkUpGameIImage_t;
typedef struct
{
    Pos_t       PosCornerOne;
    Pos_t       PosCornerTwo;
    u32         nLinkType;
}LinkUpLinkLineData_t;

typedef struct
{
    u32         nRemoveTwinsNum;
    u32         nShufflesNum;
    u32         nFindTwinsNum;
}LinkUpMagicData_t;


typedef struct
{
    LinkUpContentWdgList_t     tContentWdgList;
    LinkUpOptionsData_t        *pOptions;
    u32                     nFocuseWdg;
}ContentWndData_t;

typedef struct
{
     LinkUpGameWdgList_t           tGameWdgList;
     LinkUpSaveGameData_t          pSaveGame;
     s32                        nGameSelectPosition;
     LinkUpGameIImage_t            tGameIImage;
     LinkUpLinkLineData_t          tLinkLineData;
     LinkUpMagicData_t             tMagicData;
}GameWndData_t;


typedef struct
{
    LinkUpHelpWdgList_t    tHelpWdgList;
    u32                 nHelpImagePage;
}HelpWndData_t;

typedef struct
{
    LinkUpOptionsWdgList_t    tOptionsWdgList;
}OptionsWndData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret LinkUpAppNew(MAE_ClsId nClsId, void **ppObj);

/** LinkUpStartCB
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
boolean LinkUpStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/** LinkUpStopCB
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
MAE_Ret LlkDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/** LinkUpKeyPressCB
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
boolean LinkUpKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/** LinkUpSuspendCb
* @brief        Cancel all timer;
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
boolean LinkUpSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/** LinkUpResumeCb
* @brief        close the window,and recreate a defualt content window.
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
boolean LinkUpResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/** LinkUpContentWndHdl
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

MAE_Ret LinkUpContentWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

MAE_Ret LinkUpOptionsWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);
/** LinkUpGameWndHdl
* @brief        Game window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc()
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret LinkUpGameWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

/** LinkUpHelpWndHdl
* @brief        Help window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc()
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret LinkUpHelpWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

MAE_Ret _LinkUpCreateOptionsWnd
(
    void    *pCusHandle,
    void    *pWndData,
    u32     nWndInitParam
);

boolean _HandleKeyPressContent
(
    LinkUpAppData_t    *pThis,
    u32             nParam
);

boolean _HandleKeyPressHelp
(
    LinkUpAppData_t    *pThis,
    u32             nParam
);

MAE_Ret _LinkUpCreateContentWnd
(
    void    *pCusHandle,
    void    *pWndData,
    u32     nWndInitParam
);

void _LinkUpLoadContentView
(
		LinkUpAppData_t 		        	*pThis,
		ContentWndData_t	            *pWndData,
		u32 							nWndId
 );

MAE_Ret _LinkUpCreateGameWnd
(
    void    *pCusHandle,
    void    *pWndData,
    u32     nWndInitParam
);

void _LinkUpLoadGameView
(
		LinkUpAppData_t 		*pThis,
		GameWndData_t 		*pWndData,
		u32 				nWndId
);

/** _LinkUpMapInit
* @brief        load all image to the window data GameWndData_t.tGameIImage.
*               init the window data(pdata array),and through random get
*               item from a defined vector class ,put random index value to pdata array.
*
* @param[in]    hWin             Window handle
* @param[in]    pWndData            Game Window data
*
* @retval       None
*/
void _LinkUpMapInit(HWIN hWin, GameWndData_t *pWndData);

/** _PfnGameMenuWdgGetItemData
* @brief        Callback function throngh the Game window data(pdata array),
*               to init the menu item data.
* @param[in]    pItemDataPtr        Pointer to Data
* @param[in]    hWin                Window handle
* @param[in]    eItemType           Item type
* @param[in]    pMenu               Pointer to Menu widget
* @param[in]    u32Index            Index of menu
*
* @retval       None
*
*/
void _PfnGameMenuWdgGetItemData
(
		WdgDynamicMenuItemPtr_t 	*pItemDataPtr,
		HWIN 						hWin,
		WdgMenuItemType_e 		    eItemType,
		IWidget 					*pMenu,
		u32 						u32Index
);




/** _PfnWdgMenuSelect
* @brief        Callback function select menu
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void _PfnWdgMenuSelect
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 				nEvtCode,
		HistoryInfo_t 					*pHistoryInfo,
		IWidget 						*pReserve
);

/** _PfnWdgMenuSelect
* @brief        Callback function of timer,make Lines invisible
*
* @param[in]    pApplet        The pointer of Applet
* @param[in]    pUserData      Game window data
*
* @retval       None
*
*/
void _PfnTimerCBDisableLines(void * pApplet,void *pUserData);

/** _PfnTimerCBDisableRedRectangle
* @brief        Callback function of timer,make RedRectangle invisible
*
* @param[in]    pApplet        The pointer of Applet
* @param[in]    pUserData      Game window data
*
* @retval       None
*
*/
void _PfnTimerCBDisableRedRectangle(void * pApplet,void *pUserData);

void _PfnTimerCBDisableRedRectangleTwo(void * pApplet,void *pUserData);

/** _PfnTimerCBProgress
* @brief        Callback function of timer,control the progress timer
*               and judge if game is over or win.
*
* @param[in]    pApplet        The pointer of Applet
* @param[in]    pUserData      Game window data
*
* @retval       None
*
*/
void _PfnTimerCBProgress(void * pApplet,void *pUserData);


/** _LinkUpConfirmDalogGameWinCB
* @brief        Callback function of confirm dialog when game was win.
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret _LinkUpConfirmDailogGameWinCB
(
		void 								*pApplet,
		MAEEvent_t 					        nEvt,
		u32 								nParam1,
		u32 								nParam2
);

void _CreateGameView(
		HWIN 				hWin,
		GameWndData_t 		*pWndData
);

void _CreateHelpView
(
		HWIN						hWin,
		HelpWndData_t 	            *pWndData
);

void _LinkUpShowGameWnd
(
    void    *pCusHandle,
    GameWndData_t    *pWndData
);

void _LinkUpHideGameWnd
(
    void    *pCusHandle,
    void    *pWndData
);

void _LinkUpDestroyGameWnd
(
    void    *pCusHandle,
    void    *pWndData
);

MAE_Ret _LinkUpCreateHelpWnd
(
    void    *pCusHandle,
    void    *pWndData,
    u32     nWndInitParam
);

void _LinkUpLoadHelpView
(
		LinkUpAppData_t 		*pThis,
		HelpWndData_t		*pWndData,
		u32 				nWndId
);

/** _ContentWndHelpButtonClickCb
* @brief        Callback function of Help button
*               close content window,and open help window.
*
*/
void _ContentWndHelpButtonClickCb
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 	            nEvtCode,
		u32 							dwParam,
		IWidget 					    *pWidget
);

/** _ContentWndPlayButtonClickCb
* @brief        Callback function of Play button
*               close content window,and open Play window.
*
*/
void _ContentWndPlayButtonClickCb
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 	            nEvtCode,
		u32 							dwParam,
		IWidget 					    *pWidget
);

/** _ContentWndQuitButtonClickCb
* @brief        Callback function of Quit button
*               close current applet;
*
*/
void _ContentWndQuitButtonClickCb
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 	            nEvtCode,
		u32 							dwParam,
		IWidget 					    *pWidget
);

/** _GameWndRemoveTwinsButtonClickCb
* @brief        Callback function of Magic tools button
*               find two vaild element and set them invalid.
*
*/
void _GameWndRemoveTwinsButtonClickCb
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 	            nEvtCode,
		u32 							dwParam,
		IWidget 					    *pWidget
);

/** _GameWndShufflesButtonClickCb
* @brief        Callback function of Magic tools button
*               random switch the positon of vaild element in chessborad
*
*/
void _GameWndShufflesButtonClickCb
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 	            nEvtCode,
		u32 							dwParam,
		IWidget 					    *pWidget
);

/** _GameWndFindTwinsButtonClickCb
* @brief        Callback function of Magic tools button
*               find two element which can linked ,
*               and set redRectangle visible.
*/
void _GameWndFindTwinsButtonClickCb
(
		void 						*pApplet,
		void 						*pUsrData,
		WidgetEvtCode_t 	        nEvtCode,
		u32 						dwParam,
		IWidget 					*pWidget
);

/** _HelpWndPreviousButtonClickCb
* @brief        Callback function of help window previous button
*               set some image visible.set some image invisible.
*
*/
void _HelpWndPreviousButtonClickCb
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 	            nEvtCode,
		u32 							dwParam,
		IWidget 					    *pWidget
);

/** _HelpWndNextButtonClickCb
* @brief        Callback function of help window next button
*               set some image visible.set some image invisible.
*
*/
void _HelpWndNextButtonClickCb
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 	            nEvtCode,
		u32 							dwParam,
		IWidget 					    *pWidget
);

/** _HelpWndCloseButtonClickCb
* @brief        Callback function of close button,
*               close current window.
*
*/
void _HelpWndCloseButtonClickCb
(
		void 							*pApplet,
		void 							*pUsrData,
		WidgetEvtCode_t 	            nEvtCode,
		u32 							dwParam,
		IWidget						    *pWidget
);

/** _LinkUpFailInfoDialogCB
* @brief        Callback function of info dialog when game was failed.
*               close current window,open content window.
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret _LinkUpFailInfoDialogCB(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);

void _LinkUpShowHelpWnd
(
    void    *pCusHandle,
    HelpWndData_t    *pWndData
);

/** _PlaySounds
* @brief                Through the Melody Id Play the melody file.
*
*
* @param[in]    nMelodyID             the ID of Melody
* @param[in]    nIsSound              options of sound set
*
* @retval       none
*
*/
void _PlaySounds(u32 nMelodyID,u32 nIsSound);

/** _DrawLinkLines
* @brief                Through the game window data(LinkUpLinkLineData_t),
*                       calculate the coordinate and draw 1/2/3 lines
*
* @param[in]    pWndData             pointer of game window data
* @param[in]    x1              the x coordinate of first element
* @param[in]    x2              the x coordinate of second element
* @param[in]    y1              the y coordinate of first element
* @param[in]    y2              the y coordinate of second element
*
* @retval       none
*
*/
void _DrawLinkLines(GameWndData_t *pWndData,u32 x1,u32 x2,u32 y1,u32 y2,HWIN hwin);


/** IsLink
* @brief                Through the LINKUP Algorithms to judge
*                       if two elements are linked,and save the
*                       linked type and corners info for drawline func.
*
* @param[in]    x1              the x coordinate of first element
* @param[in]    x2              the x coordinate of second element
* @param[in]    y1              the y coordinate of first element
* @param[in]    y2              the y coordinate of second element
* @param[in]    pData           The pointer of game menu data array
* @param[in]    tLineData       save the linked type and corners info to game window data
*
* @retval       TRUE            two elements can link
* @retval       FALSE           two elements can not link
*/
boolean IsLink(s32 x1, s32 y1, s32 x2, s32 y2,s32 *pdata, LinkUpLinkLineData_t *tLineData);

#endif /* __LINKUP_BMIAPP_PRIV_H__ */
