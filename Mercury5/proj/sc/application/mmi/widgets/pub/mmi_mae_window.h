/**
 * @file mmi_mae_window.h
 *
 * @brief  The window manager will keep a window stack for handling all window switching.
 *         App can use the functions supported by window manager to handle the window.
 *         This file is inclued by App used.
 *
 * @author jerry-hy.liu@mstarsemi.com
 * @version $Id: mmi_mae_window.h 2009-10-15 22:00:00Z jerry-hy.liu $
 */
#ifndef __MMI_MAE_WINDOW_H__
#define __MMI_MAE_WINDOW_H__
//////////////////////////////////////////////////////////////////////////
#include "mmi_mae_common_def.h"
#include "mmi_mae_view_defines.h"
#include "mmi_mae_view.h"//This need to be removed.
#include "mmi_mae_applet.h"
#include "mmi_common_transition.h"
//////////////////////////////////////////////////////////////////////////
typedef u16 MAE_WndId;
typedef u32 MAE_WndDataSize;
typedef void* HWIN;
//////////////////////////////////////////////////////////////////////////
//[Window ID definition]
#define WND_ID_INVALID       0xFFFF
#define WND_ID_BASE_MASK     0xF000
//[main display window]
#define WND_ID_APP_BASE      0x0
#define WND_ID_APP_BASE_MAX     0x0FFF
//[Sub display window]
#define WND_ID_APP_SUB_BASE     0x1000
#define WND_ID_APP_SUB_BASE_MAX 0x1FFF
//[3D main display window]
#define WND_ID_3D_BASE       0x3000
#define WND_ID_3D_MAX        0x3FFF
//App do not use the following ID:Range[0x4000~0xFFFE]
#define WND_ID_COMMON_BASE   0x4000
#define WND_ID_DIALOG_BASE   0x5000
#define WND_ID_COMMON_WND_BASE  0x6000
enum{
    WND_ID_DIALOG_CONFIRM = WND_ID_DIALOG_BASE,//0x5000
    WND_ID_DIALOG_INFO,
    WND_ID_DIALOG_WAITING,
    WND_ID_DIALOG_VOLUME,
    WND_ID_DIALOG_PROGRESS,
    WND_ID_DIALOG_REDIAL,
    WND_ID_DIALOG_RECORDING
};

enum
{
    WND_ID_COMMWND_SELECT_STORAGE_POPUP = WND_ID_COMMON_WND_BASE,
    WND_ID_COMMWND_SELECT_STORAGE_FULLSCREEN,

    WND_ID_COMMWND_INTERNAL_WND,
    WND_ID_COMMWND_SELECT_STORAGE_FULLSCREEN_OPTMENU
};

//support multiple confirm dialog created simultaneously
#define MULTIPLE_CONFIRM_DIALOG_NUM 10
//////////////////////////////////////////////////////////////////////////

typedef enum WndAction_e_
{
	WND_READY,
	WND_CREATE,//Entry,
	WND_DESTROY,//EXIT,
	WND_SHOW,//ACTIVE,
	WND_HIDE,//INACTIVE
	WND_CONVERT //CONVERT
}WndAction_e;

enum
{
	WND_ORIENTATION_PORTRAIT,
	WND_ORIENTATION_LANDSCAPE,
	WND_ORIENTATION_REVERSE_PORTRAIT,
	WND_ORIENTATION_REVERSE_LANDSCAPE,
	WND_ORIENTATION_DONT_CARE = 0xFFFF,
};
typedef u16 WndOrientation_e;

typedef struct WndOrientation_t_
{
	WndOrientation_e eOrgOrientation;
	WndOrientation_e eNewOrientation;
	WndOrientation_e ePrevWndOrientation;
}WndOrientation_t;

typedef struct WindowMsg_t_
{
    WndAction_e eWndAction;
    MAE_WndId nWndId;
}WindowMsg_t;

typedef MAE_Ret (*PFN_WndFunc)(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);

//////////////////////////////////////////////////////////////////////////
//==========Interface&Function=============
///
/// IWndMgr interface
///
#define INHERIT_IWndMgr(IName) \
	INHERIT_IHandler(IName)

DEFINE_INTERFACE(IWndMgr);

//////////////////////////////////////////////////////////////////////////
/** WndCreateWindow
* @brief        To constrcut the window handle, then show the window on the screen.
*               If App registers pfnWndCB(), pfnWndCB() will receive WND_CREATE then WND_SHOW message.
*
* @param[in]    pApplet(IApplet*)         A pointer of IApplet object.
* @param[in]    nWndId(u16)               The specific window ID.
* @param[in]    nWndDataSize(u32)         The size of the customized data owned by this window wanted to be created.
* @param[in]    nLeftSoftkeyInfo          The left soft key customization of this window.
* @param[in]    nWndType                  The window type.
* @param[in]    nWndInitParam(u32)        The init param will be transferred to pfnWndFunc():WND_CREATE/WND_SHOW
* @param[in]    pfnWndCB(void*)           The callback function for App to receive WND_XXX message.
*
* @retval       hWin(HWIN)                The handle of this new window.
* @retval       NULL                      Failed.
*
*/
HWIN WndCreateWindow
(
    IApplet         *pApplet,
    MAE_WndId       nWndId,
    u32             nWndDataSize,
    u32             nWndType,
    u32             nWndInitParam,
    PFN_WndFunc     pfnWndCB
);

//3D switch
/** WndCreate3DWindow
* @brief        To constrcut the window handle, then show the window on the screen.
*               If App registers pfnWndCB(), pfnWndCB() will receive WND_CREATE then WND_SHOW message.
*
* @param[in]    pApplet(IApplet*)         A pointer of IApplet object.
* @param[in]    nWndId(u16)               The specific window ID (0x3000 ~ 0x4000).
* @param[in]    nWndDataSize(u32)         The size of the customized data owned by this window wanted to be created.
* @param[in]    nLeftSoftkeyInfo          The left soft key customization of this window.
* @param[in]    nWndType                  The window type.
* @param[in]    nWndInitParam(u32)        The init param will be transferred to pfnWndFunc():WND_CREATE/WND_SHOW
* @param[in]    pfnWndCB(void*)           The callback function for App to receive WND_XXX message.
*
* @retval       hWin(HWIN)                The handle of this new window.
* @retval       NULL                      Failed.
*
*/
HWIN WndCreate3DWindow
(
    IApplet         *pApplet,
    MAE_WndId       nWndId,
    u32             nWndDataSize,
    u32             nWndType,
    u32             nWndInitParam,
    PFN_WndFunc     pfnWndCB
);

//////////////////////////////////////////////////////////////////////////
/** WndReplaceWindow
* @brief        To constrcut the window handle,then If the window Id is not existed,
*               replace the current top window.
*               Others, remove all the windows above this specific window then show this window.
*               If App registers pfnWndCB(), pfnWndCB() will receive WND_CREATE then WND_SHOW message.
*
* @param[in]    pApplet(IApplet*)         A pointer of IApplet object.
* @param[in]    nWndId(u16)               The specific window ID.
* @param[in]    nWndDataSize(u32)         The size of the customized data owned by this window wanted to be created.
* @param[in]    nWndType                  The window type.
* @param[in]    nWndInitParam(u32)        The init param will be transferred to pfnWndFunc():WND_CREATE/WND_SHOW
* @param[in]    pfnWndCB(void*)           The callback function for App to receive WND_XXX message.
*
* @retval       hWin(HWIN)                The handle of this new window.
* @retval       NULL                      Failed.
*
*/
HWIN WndReplaceWindow
(
    IApplet         *pApplet,
    MAE_WndId       nWndId,
    u32             nWndDataSize,
    u32             nWndType,
    u32             nWndInitParam,
    PFN_WndFunc     pfnWndCB
);

/** WndCloseWindow
* @brief        To close the current window of the top screen, then destroy the window handle.
*               the window data will be freed.
*               If App registers pfnWndCB(), pfnWndCB() will receive WND_HIDE then WND_DESTROY message.
*
* @param[in]    pApplet(IApplet*)  The pointer of Applet.
*
* @retval       MAE_RET_SUCCESS             Success.
* @retval       others                      Fail.
*
*/
MAE_Ret WndCloseWindow(IApplet *pApplet);

/** WndReCreateWindow
* @brief        ReCreate the top window.
*               The top window will receive WND_HIDE->WND_DESTROY->WND_CREATE->WND_SHOW.
*
* @param[in]    pApplet(IApplet*)         A pointer of IApplet object.
* @param[in]    nWndInitParam(u32)        The init param will be transferred to pfnWndFunc():WND_CREATE/WND_SHOW.
*
* @retval       MAE_RET_SUCCESS             Success.
* @retval       others                      Fail.
*
*/
MAE_Ret WndReCreateWindow(IApplet *pApplet, u32 nWndInitParam);

/** WndRemoveWindowTo
* @brief                To remove all the windows that are on the top of
                        this specific window ID in the window stack.
*                       If this window ID is not existed, return Fail.
*
* @param[in]            pApplet(IApplet*)           A pointer of IApplet object.
* @param[in]            nWndId(MAE_WndId)           The window ID.
*
* @retval       MAE_RET_SUCCESS             Success.
* @retval       others                      Fail.
*
*/
MAE_Ret WndRemoveWindowTo(IApplet *pApplet, MAE_WndId nWndId);

/** WndRemoveAllWindow
* @brief        To remove all the windows in the window stack owned by window manager.
*
* @param[in]    pApplet(IApplet*)         A pointer of Applet object.
*
* @retval       void.
*
*/
void WndRemoveAllWindow(IApplet *pApplet);


/** WndGetCurrWindowHandle
* @brief        To get the current window handle by the ID.
*
* @param[in]        pApplet(IApplet*)           A pointer of IApplet object.
*
* @retval           hWin(HWIN)                  Success.
* @retval           NULL                        Failed.
*
*/
HWIN WndGetCurrWindowHandle(IApplet *pApplet);

/** WndGetWindowHandle
* @brief        To get the specific window handle by the ID.
*
* @param[in]        pApplet(IApplet*)           A pointer of IApplet object.
* @param[in]        nWndId(MAE_WndId)           The window ID.
*
* @retval           hWin(HWIN)                  Success.
* @retval           NULL                        Failed.
*
*/
HWIN WndGetWindowHandle(IApplet *pApplet, MAE_WndId nWndId);

/** WndGetCurrWindowData
* @brief        To get the current window data.
*
* @param[in]        pApplet(IApplet*)       A pointer of IApplet object.
*
* @retval           window data pointer     Success.
* @retval           NULL                    Failed.
*
*/
void *WndGetCurrWindowData(IApplet *pApplet);

/** WndGetWindowData
* @brief        To get the specific window data by the ID.
*
* @param[in]        pApplet(IApplet*)       A pointer of IApplet object.
* @param[in]        nWndId(MAE_WndId)       The window ID.
*
* @retval           window data pointer     Success.
* @retval           NULL                    Failed.
*
*/
void *WndGetWindowData(IApplet *pApplet, MAE_WndId nWndId);

/** WndGetWindowDatayByHandle
* @brief            To get the window data by the window handle.
*
* @param[in]        hWin(HWIN)              A pointer of IApplet object.
*
* @retval           window data pointer     Success.
* @retval           NULL                    Failed.
*
*/
void *WndGetWindowDatayByHandle(HWIN hWin);

/** WndGetCurrWindowId
* @brief        To get the current window ID on the top screen.
*               If the window is not existed, return invalid window Id(oxFFFF).
*
* @param[in]    hWin(HWIN)                  A pointer of window handle object.
*
* @retval       MAE_WndId                   output Window ID
* @retval       0xFFFF                      Failed.
*
*/
MAE_WndId WndGetCurrWindowId(IApplet *pApplet);


/** WndGetPreWindowId
* @brief        To get the previous window ID on the screen.(below the top)
*               If the window ID is not existed, return invalid window Id(oxFFFF).
*
* @param[in]    hWin(HWIN)              A pointer of window handle object.
*
* @retval       MAE_WndId               output Window ID
* @retval       0xFFFF                  Failed.
*
*/
MAE_WndId WndGetPreWindowId(IApplet *pApplet);

/** WndGetCurrDialogId
* @brief        To get the current dialog ID on the top screen.
*               If the dialog ID is not existed, return invalid dialog Id(oxFFFF).
*
* @param[in]    hWin(HWIN)                  A pointer of window handle object.
*
* @retval       MAE_WndId                   output Window ID
* @retval       0xFFFF                      Failed.
*
*/
MAE_WndId WndGetCurrDialogId(IApplet *pApplet);

/** WndGetCurrApplet
* @brief        To get the current pointer of applet.
*
* @param[in]    hWin(HWIN)                  A pointer of window handle object.
*
* @retval       pApplet(IApplet*)           Success.
* @retval       NULL                        Fail.
*
*/
IApplet *WndGetCurrApplet(HWIN hWin);

/** WndSetSyncFree
* @brief        To free the objects using by window directly or not. Default is Async free.
*               Some special app needs sync free action to save the memory by sudden use.
*
* @param[in]   pApplet(IApplet*)       A pointer of IApplet object.
* @param[in]   bIsSyncFree(boolean)    Sync Free or not.
* @retval       void.
*
*/
void WndSetSyncFree(IApplet *pApplet, boolean bIsSyncFree);


/** WndPlayTransitionById
 * @brief  This function play the transition by the Id for the current window.
 *
 * @param[in]   pApplet(IApplet*)       A pointer of IApplet object.
 * @param[in]   nTransitionId           Pre-defined transition ID
 *
 */
void WndPlayTransitionById(IApplet *pApplet, WndTransitionType_e eTransitionId);

/** WndSetAppDisplayMode
 * @brief  This function set the display mode property defined in mae_viewmgr.h.
 *
 * @param[in]   pApplet(IApplet*)      A pointer of IApplet object
 * @param[in]   eDisplayMode           The display mode
 *
 */
void WndSetAppDisplayMode(IApplet *pApplet, DisplayMode_e eDisplayMode);

/** WndGetAppDisplayMode
 * @brief  This function get the display mode property defined in mae_viewmgr.h.
 *
 * @param[in]   pApplet(IApplet*)      A pointer of IApplet object
 * @retval      DisplayMode_e          The display mode
 *
 */
DisplayMode_e WndGetAppDisplayMode(IApplet *pApplet);

/** WndSetAppSKUserIcon
 * @brief  This function set the softkey style as user defined icon
 *
 * @param[in]   pApplet(IApplet*)   A pointer of IApplet object
 * @param[in]   nSkType		The softkey to be set, LEFT_SK / MIDDLE_SK / RIGHT_SK
 * @param[in]   pImg			The user defined icon
 *
 */
void WndSetAppSKUserIcon(IApplet *pApplet, u32 nSkType, IImage* pImg);

/** WndSetAppBgVisible
 * @brief  This function set the background visibility defined in mae_viewmgr.h.
 *
 * @param[in]   pApplet(IApplet*)   A pointer of IApplet object
 * @param[in]   eBgVisible          The background visibility.
 *
 */
void WndSetAppBgVisible(IApplet *pApplet, ViewMgrBGVis_e eBgVisible);

/** WndSetAppBgType
 * @brief  This function set the background type defined in mae_viewmgr.h.
 *
 * @param[in]   pApplet(IApplet*)   A pointer of IApplet object
 * @param[in]   eBgType             The background type.
 *
 */
void WndSetAppBgType(IApplet *pApplet, ViewMgrBGTpye_e eBgType);

/** WndSetAppBgColor
 * @brief  This function set the background color.
 *
 * @param[in]   pApplet(IApplet*)   A pointer of IApplet object
 * @param[in]   nBgColor            The background color.
 *
 */
void WndSetAppBgColor(IApplet *pApplet, RGBColor_e nBgColor);

/** WndSetCurrWndSoftkeyVisible
 * @brief  This function set the softkey visiblity of the current window.
 *         The difference between this and WndSetSoftkeyVisible is the softkey
 *         bar region visiblity.  If invisible, WndSetCurrWndSoftkeyVisible will
 *         also cause the softkey bar region invisible, but WndSetSoftkeyVisible not.
 *
 * @param[in]   pApplet(IApplet*)   A pointer of IApplet object
 * @param[in]   eSKVisType          The visible type.
 *
 */
void WndSetCurrWndSoftkeyVisible(IApplet *pApplet, ViewSKVisType_t eSKVisType);

/** WndSetCurrWndStatusbarVisible
 * @brief  This function set the statusbar visiblity of the current window.
 *         The difference between this and WndSetStatusBarVisible is the status
 *         bar region visiblity.  If invisible, WndSetCurrWndStatusbarVisible will
 *         also cause the status bar region invisible, but WndSetStatusBarVisible not.
 *
 * @param[in]   pApplet(IApplet*)   A pointer of IApplet object
 * @param[in]   eSBVisType          The visible type.
 *
 */
void WndSetCurrWndStatusbarVisible(IApplet *pApplet, ViewSBVisType_t eSBVisType);

#endif // __MAE_WINDOW_H__
