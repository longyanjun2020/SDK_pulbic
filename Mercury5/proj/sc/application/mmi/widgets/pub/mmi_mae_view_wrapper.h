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
* @file    mmi_mae_view_wrapper.h
* @version
* @brief   View wrapper header file
*
*/

#ifndef __MMI_MAE_VIEW_WRAPPER_H__
#define __MMI_MAE_VIEW_WRAPPER_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_retcode.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_view_defines.h"
#include "mmi_wdg_abscontainer.h"
#include "mmi_mae_window.h"
#include "mmi_mae_softkeymodel.h"
#include "mmi_wdg_group.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define USR_APP_WDG_START 0x1
#define SYSTEM_WDG_START 0x1000
#define VTM_WDG_START    0x1100
#define APP_WDG_START    0x1200

#define BASE_WDG_ID  SYSTEM_WDG_START //0x1000
#ifdef __AP_USE_ML__
enum{
	IME_WDG_ID = SYSTEM_WDG_START+MMI_DISP_LAYER_TOTAL,
	TITLE_WDG_ID,
	STATICMENU_WDG_ID,
	DYNAMICMENU_WDG_ID,
};
#else
#define IME_WDG_ID   0x1001
#define TITLE_WDG_ID 0x1002
#define STATICMENU_WDG_ID 0x1003
#define DYNAMICMENU_WDG_ID 0x1004
#endif


/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef void (*PfnWndSoftkey) (HWIN hWin, void *pUsrData, WidgetEvtCode_t nEvtCode, MaeSoftkeyEventInf_t *psEventInf, void *pReserve);

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** ViewCreate
* @brief        Create a view and widget, follow by nViewType to generate widgets and add to view, set view ID
*
* @param[in]    hWin		point to a window handle
* @param[in]    nViewType 		indicate the view type. Refer to the sturct ViewType_t
* @param[in]    nViewID			set the view ID
*
* @retval       MAE_RET_SUCCESS Success
* @retval       others          Failed
*/
__SLDPM_FREE__ MAE_Ret ViewCreate(HWIN hWin, u32 nViewType, u32 nViewID);

/** WndAddWdg
* @brief        input a widget, add it to window by nWDGId and put it on base container at pPos
*
* @param[in]    hWin     	point to a window handle
* @param[in]    pWDG 			input a widget, add it to window by nWDGId and put it on base container at pPos
* @param[in]    nWDGId			set the widget id in window 
* @param[in]    pPos			indicate position on view base container
*
*/
__SLDPM_FREE__ void WndAddWdg(HWIN hWin, IWidget *pWDG, u16 nWDGId, Pos_t *pPos);


/** WndRemoveWdg
* @brief        input a widget, remove it from window
*
* @param[in]    hWin     	point to a window handle
* @param[in]    pWDG 		pointer to a widget to be removed
*
*/
void WndRemoveWdg(HWIN hWin, IWidget *pWDG);

/** WndSetMLInfo
* @brief        Set the used layer info (position, size, format, transpBG), this should be done before other ML operation, e.g. WndAddWdgML
*
* @param[in]    hWin     	point to a window handle
* @param[in]    pInfo 			the pointer to a layer info structure
* @param[in]	 nLayer			specify the layer
*
*/
void WndSetMLInfo(HWIN hWin, LayerCreateInfo_t *pInfo, DisplayLayer_e nLayer);

/** WndAddWdgML
* @brief        input a widget, add it to view by nWDGId and put it on base container (specify layer) at pPos
*
* @param[in]    hWin     	point to a window handle
* @param[in]    pWDG 			input a widget, add it to view by nWDGId and put it on base container at pPos
* @param[in]    nWDGId			set the widget id in view 
* @param[in]    pPos			indicate position on view base container
* @param[in]	 nLayer			specify the layer
*
*/
void WndAddWdgML(HWIN hWin, IWidget *pWDG, u16 nWDGId, Pos_t *pPos, DisplayLayer_e nLayer);

/** WndMoveWdg
* @brief        move a widget's position on it parent container
*
* @param[in]    hWin     	point to a window handle
* @param[in]    pWDG 			indicate which widget on this view
* @param[in]    pWPos			new position 
*
*/
void WndMoveWdg(HWIN hWin, IWidget *pWDG, WPos_t *pWPos);

/** WndChangeWdgLayer
* @brief        move a widget's layer on it parent container
*
* @param[in]    hWin     	point to a window handle
* @param[in]    pWDG 			indicate which widget on this view
* @param[in]    pRefWDG 		indicate which widget want to refer; NULL means to most top/bottom
* @param[in]    bUpper			move to top or bottom
*
*/
void WndChangeWdgLayer(HWIN hWin, IWidget *pWDG, IWidget *pRefWDG, boolean bUpper);

/** WndSetWindowSize
* @brief        set windows size
*
* @param[in]    hWin     	point to a window handle
* @param[in]    pWndSize 		new size
*
*/
void WndSetWindowSize(HWIN hWin, WidgetSize_t *pWndSize);

/** WndGetWindowSize
* @brief        Get windows size
*
* @param[in]    hWin     	point to a window handle
* @param[out]   pWndSize 		current windows size
*
*/
void WndGetWindowSize(HWIN hWin, WidgetSize_t *pWndSize);

/** WndCheckWdg
* @brief        check a widget is in the window or not
*
* @param[in]    hWin	point to a window handle
* @param[in]    nId 		widget ID
*
* @retval       TRUE		the widget in the window
* @retval       FALSE       the widget do not contain in the window
*/
boolean WndCheckWdg(HWIN hWin, u16 nId);

/** WndGetWdg
* @brief        get a widget by  input widget id
*
* @param[in]    hWin	point to a window handle
* @param[in]    nId 		widget ID
*
* @retval       NULL		the widget do not contain in the window
* @retval       other       a pointer to the widget       
*/
IWidget* WndGetWdg(HWIN hWin, u16 nId);

/** WndSetWdgPos
* @brief        set a widget's position on window base container
*
* @param[in]    hWin	point to a window handle
* @param[in]    pWDG 		pointer to a widget
* @param[in]    pWPos 		new position
*
*/
void WndSetWdgPos(HWIN hWin, IWidget *pWDG, WPos_t *pWPos);

/** WndGetWdgPos
* @brief        Get a widget's position on base container(Please use WndSetWdgPosition)
*
* @param[in]    hWin	point to a window handle
* @param[in]    pWDG 		pointer to a widget
* @param[out]   pWPos 		widget's current position on base container
*
*/
void WndGetWdgPos(HWIN hWin, IWidget *pWDG, WPos_t *pWPos);

/** WndSetWdgPosition
* @brief        set a widget's position on window base container
*
* @param[in]    hWin	point to a window handle
* @param[in]    pWDG 		pointer to a widget
* @param[in]    pPos 		new position
*
*/
void WndSetWdgPosition(HWIN hWin, IWidget *pWDG, Pos_t *pPos);

/** WndGetWdgPosition
* @brief        Get a widget's position on base container
*
* @param[in]    hWin	point to a window handle
* @param[in]    pWDG 		pointer to a widget
* @param[out]   pPos 		widget's current position on base container
*
*/
void WndGetWdgPosition(HWIN hWin, IWidget *pWDG, Pos_t *pPos);

/** WndGetTitle
* @brief        Get title widget
*
* @param[in]    hWin	point to a window handle
*
* @retval       NULL		the widget do not contain in the window
* @retval       other       a pointer to the widget       
*/
IWidget * WndGetTitle(HWIN hWin);

/*Internal use function*/
void WndAddTitle(HWIN hWin, IView *pView);

/** WndSetTitle
* @brief        Set title widget's text, icon and style
*
* @param[in]    hWin		point to a window handle
* @param[in]    nTitleImageID	indicate the title's icon
* @param[in]    nTitleTextID	indicate the title's text
*
*/
__SLDPM_FREE__ void WndSetTitle(HWIN hWin, u32 nTitleImageID, u32 nTitleTextID);

/** WndSetTitleVisiable
* @brief        Set title widget is visible or not
*
* @param[in]    hWin	 point to a window handle
* @param[in]    bVisiable	 indicate visible or invisible
*
*/
void WndSetTitleVisiable(HWIN hWin, boolean bVisiable);

/** WndGetTitleVisiable
* @brief        get title widget is visible or not
*
* @param[in]    hWin	point to a window handle
*
* @retval       TRUE		title widget is visible
* @retval       FALSE       title widget is invisible
*/
boolean WndGetTitleVisiable(HWIN hWin);

/** WndSetBgImage
* @brief        set window background image
*
* @param[in]    hWin	point to a window handle
* @param[in]    pBgImg      point a background image
*
*/

void WndSetBgImage(HWIN hWin, IBase* pBgImg);

/** WndSetBgPos
* @brief        
*
* @param[in]    hWin	point to a window handle.
* @param[in]    tBgPos      set background image's property, refer to struct WdgBackgroundPos_t
*
*/
void WndSetBgPos(HWIN hWin, WdgBackgroundPos_t tBgPos);

/** WndSetBgColor
* @brief        set window background image's color
*
* @param[in]    hWin	point to a window handle
* @param[in]    tBgColor    background image color, refer to RGBColor_t
*
*/
void WndSetBgColor(HWIN hWin, RGBColor_t tBgColor);

/*Internal use function*/
IWidget* _WndAddIme(HWIN hWin);

/* Internal use function, Set IME widget to input widget*/
void _WndSetImeModel(HWIN hWin, IWidget *pTargetWidget, IBase *pThis);

void WndCreateIme(HWIN hWin, IWidget *pTargetWidget, IBase *pOwner);
void WndActiveIme(HWIN hWin, IWidget* pWdg);

/** WndGetIme
* @brief        Get IMEAssist widget
*
* @param[in]    hWin	point to a window handle
*
* @retval       NULL		the widget do not contain in the window
* @retval       other       a pointer to the widget       
*/
IWidget* WndGetIme(HWIN hWin);

/** WndSetSoftKeyData
* @brief        Set view softkey control/model to the target widget, set PROP_WDG_SK_DATA property
*
* @param[in]    hWin point to a window handle
* @param[in]    pWdg       point to target widget
*
*/
void WndSetSoftKeyData(HWIN hWin, IWidget *pTargetWdg);

/** WndGetBaseContainer
* @brief        Get base container
*
* @param[in]    hWin	point to a window handle
*
* @retval       NULL		the widget do not contain in the window
* @retval       other       a pointer to the widget
*/
__SLDPM_FREE__ IWidget* WndGetBaseContainer(HWIN hWin);

/** WndGetBaseContainerML
* @brief        Specify the layer to get base container
*
* @param[in]    hWin	point to a window handle
* @param[in]	nLayer  specify the layer
*
* @retval       NULL		the widget do not contain in the window
* @retval       other       a pointer to the widget
*/
IWidget* WndGetBaseContainerML(HWIN hWin, DisplayLayer_e nLayer);

/** WndChangeContainer
* @brief        change widget's container. if pWDG is locate on pContainer, do nothing
*
* @param[in]    hWin point to a window handle
* @param[in]    pContainer point to a container
* @param[in]    pWDG       point to a widget
*
*/
void WndChangeContainer(HWIN hWin, IWidget *pContainer, IWidget *pWDG);

/** WndSetAllSoftkey
* @brief        set view's all softkey
*
* @param[in]    hWin  point to a window handle
* @param[in]    nLeftSKID   left softkey ID
* @param[in]    nMiddleSKID middle softkey ID
* @param[in]    nRightSKID  right softkey ID
*
*/
void WndSetAllSoftkey(HWIN hWin, u32 nLeftSKID, u32 nMiddleSKID, u32 nRightSKID);

/** WndGetAllSoftkey
* @brief        get view's all softkey
*
* @param[in]     hWin  point to a window handle
* @param[out]    nLeftSKID   point of left softkey ID
* @param[out]    nMiddleSKID point of middle softkey ID
* @param[out]    nRightSKID  point of right softkey ID
*
*/
void WndGetAllSoftkey(HWIN hWin, u32 *pLeftSKID, u32 *pMiddleSKID, u32 *pRightSKID);

/** WndSetSoftkey
* @brief        set view's single softkey
*
* @param[in]    hWin  point to a window handle
* @param[in]    nSkType     indicate which softkey you want to set
* @param[in]    nSKID       softkey ID
*
*/
void WndSetSoftkey(HWIN hWin, u32 nSkType, u32 nSKID);

/** WndGetSoftkey
* @brief        get view's single softkey
*
* @param[in]     hWin point to a window handle
* @param[out]    nSkType    indicate which softkey you want to get
* @param[out]    pSKID      point of softkey ID
*
*/
void WndGetSoftkey(HWIN hWin, u32 nSkType, u32 *pSKID);

/** WndSetSoftkeyVisible
* @brief        set view softkey visible or not
*
* @param[in]     hWin point to a window handle
* @param[in]     bVisible    indicate softkey visible or not
*
*/
void WndSetSoftkeyVisible(HWIN hWin, boolean bVisible);

/** WndGetSoftkeyVisible
* @brief        get view softkey visible or not
*
* @param[in]    hWin point to a window handle
*
* @retval       TRUE	   softkey is visible
* @retval       FALSE      softkey is not visible
*/
boolean WndGetSoftkeyVisible(HWIN hWin);

/** WndSetSoftkeyTransparency
* @brief        set view softkey transparency or not
*
* @param[in]     hWin point to a window handle
* @param[in]     bTransparency    indicate softkey transparency or not
*
*/
void WndSetSoftkeyTransparency(HWIN hWin, boolean bTransparency);

/** WndGetSoftkeyTransparency
* @brief        get view softkey transparency or not
*
* @param[in]    hWin point to a window handle
*
* @retval       TRUE	   transparency
* @retval       FALSE      not transparency
*/
boolean WndGetSoftkeyTransparency(HWIN hWin);

/** WndSetStatusBarVisible
* @brief        set view status bar visible or not
*
* @param[in]     hWin point to a window handle
* @param[in]     bVisible    indicate status bar visible or not
*
*/
__SLDPM_FREE__ void WndSetStatusBarVisible(HWIN hWin, boolean bVisible);

/** WndGetStatusBarVisible
* @brief        get view status bar visible or not
*
* @param[in]    hWin point to a window handle
*
* @retval       TRUE	   status bar is visible
* @retval       FALSE      status bar is not visible
*/
boolean WndGetStatusBarVisible(HWIN hWin);

/** WndSetStatusBarTransparency
* @brief        set view status bar transparency or not
*
* @param[in]     hWin point to a window handle
* @param[in]     bTransparency    indicate status bar transparency or not
*
*/
void WndSetStatusBarTransparency(HWIN hWin, boolean bTransparency);

/** WndGetStatusBarTransparency
* @brief        get view status bar transparency or not
*
* @param[in]    hWin point to a window handle
*
* @retval       TRUE	   transparency
* @retval       FALSE      not transparency
*/
boolean WndGetStatusBarTransparency(HWIN hWin);

#ifdef __APP_MMI_GROUP_APP__
/** WndSetGroupVisible
* @brief        set view's group visible or not
*
* @param[in]     hWin point to a window handle
* @param[in]     bVisible    indicate group visible or not
*
*/
void WndSetGroupVisible(HWIN hWin, boolean bVisible);

/** WndGetGroupVisible
* @brief        get view's group visible or not
*
* @param[in]    hWin point to a window handle
*
* @retval       TRUE	 group is visible
* @retval       FALSE      group is not visible
*/
boolean WndGetGroupVisible(HWIN hWin);

/** WndSetGroupAP
* @brief        set current AP of group 
*
* @param[in]    hWin                 point to a window handle
* @param[in]    nCurrAppType   current AP type
*
*/
void WndSetGroupAP(HWIN hWin, GROUP_APPLET_TYPE nCurrAppType);

/** WndSetGroupTransparency
* @brief        set view group transparency or not
*
* @param[in]     hWin point to a window handle
* @param[in]     bTransparency    indicate group transparency or not
*
*/
void WndSetGroupTransparency(HWIN hWin, boolean bTransparency);

/** WndGetGroupTransparency
* @brief        get view group transparency or not
*
* @param[in]    hWin point to a window handle
*
* @retval       TRUE	   transparency
* @retval       FALSE      not transparency
*/
boolean WndGetGroupTransparency(HWIN hWin);
#endif

/** WndRegisterSoftkeyCb
* @brief        Register callback : CB will be triggered when softkey is pressed ex, OK, Stop, Save...
*
* @param[in]    hWin    hWin point to a window handle
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WndRegisterSoftkeyCb(HWIN hWin, PfnWndSoftkey pfn, void *pUserData);
#ifdef __UI_STYLE_MMI_IFONE__
void WndSetTitleSoftkey(HWIN hWin, u32 nSkType, u32 nSKID);
#endif

#endif /* __MMI_VIEW_WRAPPER_H__ */
