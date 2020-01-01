/**
 * @file mmi_mae_windowmgr.h
 *
 * @brief  The window manager will keep a window stack for handling all window switching.
 *         App can use the functions supported by window manager to handle the window.
 *         This file is inclued by system used, not for App used.
 *
 * @version $Id: mmi_mae_windowmgr.h 2009-10-16 12:00:00z jerry-hy.liu $
 */
#ifndef __MMI_MAE_WINDOWMGR_H__
#define __MMI_MAE_WINDOWMGR_H__
//////////////////////////////////////////////////////////////////////////
//==========Includes=======================
#include "mmi_mae_interface_def.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_retcode.h"
#include "mmi_mae_window.h"
#include "mmi_mae_handler.h"
#include "mmi_mae_softkey.h"
#include "mmi_common_vtmdialog.h"
#include "mmi_mae_thmmgr.h"
//////////////////////////////////////////////////////////////////////////
//==========Types&Data=====================
#define WNDMGR_EVT_TRIGGER_CODE_TRACE   0x57E40000//The same definition at MkernelWin32.cpp
#define WNDMGR_EVT_ASYNC_FREE_WNDHANDLE (CLSID_WNDMGR << 16 | 1)
#define WNDMGR_EVT_ASYNC_FREE_VIEW      (CLSID_WNDMGR << 16 | 2)
#define WNDMGR_EVT_TRIGGER_ORIENTATION  (CLSID_WNDMGR << 16 | 3)
#ifdef __MULTI_THEMES_ENABLED__
#define WNDMGR_EVT_TRIGGER_CHANGE_THEME  (CLSID_WNDMGR << 16 | 4)
#endif

//Only for BaseApplet init used.
void WndMgrSetAppletData(IWndMgr *pIWndMgr, IApplet *pIApplet);

typedef MAE_Ret (*PFN_DlgHandlerCB)(void *,...);

typedef struct DialogKeyInfo_t_
{
	SoftkeyID_e nLSK;
	SoftkeyID_e nCSK;
	SoftkeyID_e nRSK;
} DialogKeyInfo_t;

typedef struct ConfirmDlgData_t_
{
    DialogKeyInfo_t tKeyInfo;
    u16 u16DialogViewID;
    u8 bIsAcceptedAnyKey;
    NormalDialogWdgList_t tWdgList;
    PFN_DlgHandlerCB pfnCB;
} ConfirmDlgData_t;

typedef struct WaitingDlgData_t_
{
    DialogKeyInfo_t tKeyInfo;
    u16 u16DialogViewID;
    u8 bIsAcceptedAnyKey;
    WaitingDialogWdgList_t tWdgList;
    PFN_DlgHandlerCB pfnCB;
} WaitingDlgData_t;

typedef struct ProgressDlgData_t_
{
    DialogKeyInfo_t tKeyInfo;
    //IWidget *pWidget;
    u8 bIsAcceptedAnyKey;
    ProcessDialogWdgList_t tWdgList;
    PFN_DlgHandlerCB pfnCB;
} ProgressDlgData_t;

typedef struct RedialDlgData_t_t
{
    DialogKeyInfo_t tKeyInfo;
    //IWidget *pWidget;
    u8 bIsAcceptedAnyKey;
    RedialDialogWdgList_t tWdgList;
    PFN_DlgHandlerCB pfnCB;
} RedialDlgData_t;

typedef struct RecordingDlgData_t_
{
    DialogKeyInfo_t tKeyInfo;
    //IWidget *pWidget;
    u8 bIsAcceptedAnyKey;
    RecordingDialogWdgList_t tWdgList;
    PFN_DlgHandlerCB pfnCB;
} RecordingDlgData_t;

typedef struct InfoDlgData_t_
{
    u8 bIsAcceptedAnyKey;
    NormalDialogWdgList_t tWdgList;
    PFN_DlgHandlerCB pfnCB;
}InfoDlgData_t;

typedef struct VolumeDlgData_t_
{
    //IWidget *pWidget;
    u8 bIsAcceptedAnyKey;
    VolumeSetDialogWdgList_t tWdgList;
    ModelListener_t tVolumeMdlListener;
    PFN_DlgHandlerCB pfnCB;
}VolumeDlgData_t;

typedef struct WndEventData_t_
{
    IApplet         *pApplet;
    MAE_WndId       nWndId;
    u32             nWndDataSize;
    u32             nWndType;
    u32             nWndInitParam;
    PFN_WndFunc     pfnWndCB;
}WndEventData_t;
//////////////////////////////////////////////////////////////////////////
#define IWNDMGR_QueryInterface(pMgr,iid,ppObj,pOwner)    GET_FUNCTBL(pMgr,IWndMgr)->QueryInterface(pMgr,iid,ppObj,pOwner)

/** WndGetCurrView
* @brief        To get the current pointer of view.
*
* @param[in]    hWin(HWIN)                  A pointer of window handle object.
* @retval       pApplet(IApplet*)           Success.
* @retval       NULL                        Fail.
*
*/
IView *WndGetCurrView(HWIN hWin);

/** WndSetCurrView
* @brief        To set the current pointer of view.
*
* @param[in]    hWin(HWIN)                  A pointer of window handle object.
*
* @retval       MAE_RET_SUCCESS             Success.
* @retval       others                      Fail.
*
*/
MAE_Ret WndSetCurrView(HWIN hWin, IView *pIView);

/** WndCreateDialog
* @brief        To constrcut the window handle, then return for App.
*
* @param[in]    nDispId(MAE_DispId_t)     the main display or sub display.
* @param[in]    pApplet(IApplet*)         A pointer of IApplet object.
* @param[in]    nWndId(u16)               The specific window ID.
* @param[in]    nWndDataSize(u32)         The size of the customized data owned by this window wanted to be created.
* @param[in]    nLeftSoftkeyInfo          The left soft key customization of this window.
* @param[in]    nWndType                  The window type.
* @param[in]    pfnWndCB(void*)           The callback function for App to receive WND_XXX message.
*
* @retval       hWin(HWIN)                The handle of this new window.
* @retval       NULL                      Failed.
*
*/
HWIN WndCreateDialog
(
    MAE_DispId_t nDispId,
    IApplet         *pApplet,
    MAE_WndId       nWndId,
    u32             nWndDataSize,
    u32             nWndType,
    PFN_WndFunc     pfnWndCB
);

/** WndShowDialog
* @brief        To show the dialog.This function is only called by dialog mechanism.
*
* @param[in]    nDispId(MAE_DispId_t)           the main display or sub display.
* @param[in]    hDialogWnd(HWIN)                A pointer of window handle object.
* @retval       MAE_RET_SUCCESS                 Success.
* @retval       others                          Failed.
*
*/
MAE_Ret WndShowDialog(MAE_DispId_t nDispId, HWIN hDialogWnd);

/** WndRemoveDialogbyId
* @brief        To remove the dialog according to the window Id if existed.
*               This function is only called by dialog mechanism.
*
* @param[in]    nDispId(MAE_DispId_t) the main display or sub display.
* @param[in]    pWndMgr(WndMgr_t*)    A pointer of window manager.
* @param[in]    nWndId(u16)           The specific window ID.
* @param[in]    nEvt(MAEEvent_t)      The event transferred into the CB function.
* @param[in]    param1(u32)           The param1 transferred into the CB function.
* @param[in]    param2(u32)           The param2 transferred into the CB function.

* @retval       void.
*
*/
void WndRemoveDialogbyId
(
    MAE_DispId_t nDispId,
    IWndMgr *pIWndMgr,
    MAE_WndId nWndId,
    MAEEvent_t nEvt,
    u32 param1,
    u32 param2
);

/** WndRemoveTopDialog
* @brief        To remove the top dialog.This function is only called by dialog mechanism.
*
* @param[in]    nDispId               The main display or sub display.
* @param[in]    pWndMgr(WndMgr_t*)      A pointer of window manager.
* @param[in]    nEvt(MAEEvent_t)      The event transferred into the CB function.
* @param[in]    param1(u32)           The param1 transferred into the CB function.
* @param[in]    param2(u32)           The param2 transferred into the CB function.

* @retval       void.
*
*/
void WndRemoveTopDialog
(
    MAE_DispId_t nDispId,
    IWndMgr *pIWndMgr,
    MAEEvent_t nEvt,
    u32 param1,
    u32 param2
);

/** WndFreeWndHandleObj
* @brief        To free the window handle object if show window fail.
*
* @param[in]    hWin(HWIN)    A pointer of window handle object.
*
* @retval       void
*
*/
void WndFreeWndHandleObj(HWIN hWin);

/** WndRemoveAllWindowByApplet
* @brief        To remove all the windows in the window stack owned by window manager.
*
* @param[in]    nDispId                   The main display or sub display.
* @param[in]    pApplet(IApplet*)         A pointer of Applet object.
* @param[in]    bIsAsyncFree(boolean)     Async free the object or not.
*
* @retval       void.
*
*/
void WndRemoveAllWindowByApplet(MAE_DispId_t nDispId, IApplet *pApplet, boolean bIsAsyncFree);

//3Dswitch
/** WndIsFullScreenWindowExisted
* @brief        check if the first full screen window is 3d window
*
* @param[in]    pApplet(IApplet*)         A pointer of Applet object.
* @param[out]   pWndId(u32*)              full screen window Id
*
* @retval       TRUE                      The first full screen window is 3d window.
*               FALSE                     The first full screen window is not 3d window.
*
*/
boolean WndIsFullScreenWindowExisted(IApplet *pApplet, u32* pWndId);

/** WndIs3DOptionMenuExisted
* @brief        check if there is any 3d option menu window
*
* @param[in]    pApplet(IApplet*)         A pointer of Applet object.
* @param[out]   pWndId(u32*)              full screen window Id
*
* @retval       TRUE                      There is a 3d option menu window.
*               FALSE                     There is not any 3d option menu window.
*
*/
boolean WndIs3DOptionMenuExisted(IApplet *pApplet, u32* pWndId);

#ifdef __AP_USE_ML__
/** WndSetLayerOffset
* @brief		Set the offset of specified layer, only works if the Top View of Mgr use ML and ML buffer created, and will cause Screen Update
*
* @param[in]	hWin                A pointer of window handle object.
* @param[in]	nLayer				the specified layer
* @param[in]   (x, y)				the offset
*
* @retval	MAE_RET_SUCCESS       successfully set offset and update screen
* @retval	MAE_RET_BAD_PARAM		pMgr is NULL or nLayer is illegal
* @retval  MAE_RET_FAILED			if top view isn't ML or buffer not created
*/
MAE_Ret WndSetLayerOffset(HWIN hWin, DisplayLayer_e nLayer, u32 x, u32 y);

/** WndSetLayerVisible
* @brief		Set the visibility of specified layer, only works if the Top View of Mgr use ML and ML buffer created, and will cause Screen Update
*
* @param[in]    hWin                A pointer of window handle object.
* @param[in]    nLayer				the specified layer
* @param[in]    bvisible            the layer visibility
*
* @retval	MAE_RET_SUCCESS         successfully set offset and update screen
* @retval	MAE_RET_BAD_PARAM       pMgr is NULL or nLayer is illegal
* @retval   MAE_RET_FAILED          if top view isn't ML or buffer not created
*/
MAE_Ret WndSetLayerVisible(HWIN hWin, DisplayLayer_e nLayer, boolean bVisible);
#endif

//only test in BaseApplet interface
void WndMgrResetRotation(void *pWndMgr, void* pApplet);
u16 WndMgrGetCurrOrientation(void *pWndMgr);
void WndMgrSetCurrOrientation(IWndMgr *pIWndMgr, s32 nMotionValue);
void WndMgrHandleOrientation(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#ifdef __MULTI_THEMES_ENABLED__
void WndMgrHandleChangeTheme(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#endif

boolean WndMgrGetOrientation(IApplet *pApplet, u32 *pOrientation);

/** WndGetDisplayID
* @brief		To distinguish the main display or sub display.
*
* @param[in]    hWin       A pointer of window handle object.
*
* @retval	    DispID     The main display or sub display.
*/
MAE_DispId_t WndGetDisplayID(HWIN hWin);

/** WndGetSubWindowData
* @brief        To get the specific sub window data by the ID.
*
* @param[in]        pApplet(IApplet*)       A pointer of IApplet object.
* @param[in]        nWndId(MAE_WndId)       The window ID.
*
* @retval           window data pointer     Success.
* @retval           NULL                    Failed.
*
*/
void *WndGetSubWindowData(IApplet *pApplet, MAE_WndId nWndId);
#endif // __MAE_WINDOWMGR_H__

