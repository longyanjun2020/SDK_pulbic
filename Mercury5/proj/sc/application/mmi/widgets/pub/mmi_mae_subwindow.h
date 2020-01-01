#ifndef __MMI_MAE_SUBWINDOW_H__
#define __MMI_MAE_SUBWINDOW_H__

/**
 * @file mmi_mae_subwindow.h
 *
 * @brief  The window manager will keep a window stack 
 *         for handling all window switching.
 *         App can use the functions supported by window manager 
 *         to handle the sub window(panel).
 *       This file is inclued by App used for sub window(panel) - dual lCM. 
 *
 * @author jerry-hy.liu@mstarsemi.com
 * @version $Id: mae_subwindow.h 2010-05-16 22:00:00Z jerry-hy.liu $
 * @note This file is a carbon copy of the original mae_subwindow.h.
 *   it is renamed as mmi_mae_subwindow.h for becoming a public header.
 */
#include "mmi_mae_window.h"

//#define WND_ID_APP_SUB_BASE  0x1000
//////////////////////////////////////////////////////////////////////////
/** WndCreateSubWindow
* @brief        To constrcut the sub window handle, then show the sub window on the screen.
*               If App registers pfnWndCB(), pfnWndCB() will receive WND_CREATE then WND_SHOW message.
*
* @param[in]    pApplet(IApplet*)         A pointer of IApplet object.
* @param[in]    nSubWndId(u16)            The specific sub window ID.
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
HWIN WndCreateSubWindow
(
    IApplet         *pApplet,
    MAE_WndId       nSubWndId,
    u32             nWndDataSize,
    u32             nWndType,
    u32             nWndInitParam,
    PFN_WndFunc     pfnWndCB
);

//////////////////////////////////////////////////////////////////////////
/** WndReplaceSubWindow
* @brief        To constrcut the window handle,then If the sub window Id is not existed,
*               replace the current top sub window.
*               Others, remove all the sub windows above this specific sub window then show this window.
*               If App registers pfnWndCB(), pfnWndCB() will receive WND_CREATE then WND_SHOW message.
*
* @param[in]    pApplet(IApplet*)         A pointer of IApplet object.
* @param[in]    nSubWndId(u16)            The specific sub window ID.
* @param[in]    nWndDataSize(u32)         The size of the customized data owned by this window wanted to be created.
* @param[in]    nWndType                  The window type.
* @param[in]    nWndInitParam(u32)        The init param will be transferred to pfnWndFunc():WND_CREATE/WND_SHOW
* @param[in]    pfnWndCB(void*)           The callback function for App to receive WND_XXX message.
*
* @retval       hWin(HWIN)                The handle of this new window.
* @retval       NULL                      Failed.
*
*/
HWIN WndReplaceSubWindow
(
    IApplet         *pApplet,
    MAE_WndId       nSubWndId,
    u32             nWndDataSize,
    u32             nWndType,
    u32             nWndInitParam,
    PFN_WndFunc     pfnWndCB
);

/** WndCloseSubWindow
* @brief        To close the current sub window of the top screen, then destroy the window handle.
*               the window data will be freed.
*               If App registers pfnWndCB(), pfnWndCB() will receive WND_HIDE then WND_DESTROY message.
*
* @param[in]    pApplet(IApplet*)  The pointer of Applet.
*
* @retval       MAE_RET_SUCCESS             Success.
* @retval       others                      Fail.
*
*/
MAE_Ret WndCloseSubWindow(IApplet *pApplet);

/** WndReCreateSubWindow
* @brief        ReCreate the top sub window.
*               The top window will receive WND_HIDE->WND_DESTROY->WND_CREATE->WND_SHOW.
*
* @param[in]    pApplet(IApplet*)         A pointer of IApplet object.
* @param[in]    nWndInitParam(u32)        The init param will be transferred to pfnWndFunc():WND_CREATE/WND_SHOW.
*
* @retval       MAE_RET_SUCCESS             Success.
* @retval       others                      Fail.
*
*/
MAE_Ret WndReCreateSubWindow(IApplet *pApplet, u32 nWndInitParam);

/** WndRemoveSubWindowTo
* @brief                To remove all the sub windows that are on the top of
                        this specific window ID in the window stack.
*                       If this window ID is not existed, return Fail.
*
* @param[in]            pApplet(IApplet*)           A pointer of IApplet object.
* @param[in]            nSubWndId(MAE_WndId)        The sub window ID.
*
* @retval       MAE_RET_SUCCESS             Success.
* @retval       others                      Fail.
*
*/
MAE_Ret WndRemoveSubWindowTo(IApplet *pApplet, MAE_WndId nSubWndId);

/** WndRemoveAllSubWindow
* @brief        To remove all the sub windows in the window stack owned by window manager.
*
* @param[in]    pApplet(IApplet*)         A pointer of Applet object.
*
* @retval       void.
*
*/
void WndRemoveAllSubWindow(IApplet *pApplet);


/** WndGetCurrSubWindowHandle
* @brief        To get the current sub window handle by the ID.
*
* @param[in]        pApplet(IApplet*)           A pointer of IApplet object.
*
* @retval           hWin(HWIN)                  Success.
* @retval           NULL                        Failed.
*
*/
HWIN WndGetCurrSubWindowHandle(IApplet *pApplet);

/** WndGetWindowHandle
* @brief        To get the specific sub window handle by the ID.
*
* @param[in]        pApplet(IApplet*)           A pointer of IApplet object.
* @param[in]        nWndId(MAE_WndId)        The window ID.
*
* @retval           hWin(HWIN)                  Success.
* @retval           NULL                        Failed.
*
*/
//HWIN WndGetWindowHandle(IApplet *pApplet, MAE_WndId nWndId);

/** WndGetCurrSubWindowData
* @brief        To get the current sub window data.
*
* @param[in]        pApplet(IApplet*)       A pointer of IApplet object.
*
* @retval           window data pointer     Success.
* @retval           NULL                    Failed.
*
*/
void *WndGetCurrSubWindowData(IApplet *pApplet);

/** WndGetWindowData
* @brief        To get the specific sub window data by the ID.
*
* @param[in]        pApplet(IApplet*)       A pointer of IApplet object.
* @param[in]        nWndId(MAE_WndId)    The window ID.
*
* @retval           window data pointer     Success.
* @retval           NULL                    Failed.
*
*/
//void *WndGetWindowData(IApplet *pApplet, MAE_WndId nWndId);

/** WndGetWindowDatayByHandle
* @brief            To get the window data by the window handle.
*
* @param[in]        hWin(HWIN)              A pointer of IApplet object.
*
* @retval           window data pointer     Success.
* @retval           NULL                    Failed.
*
*/
//void *WndGetWindowDatayByHandle(HWIN hWin);

/** WndGetCurrSubWindowId
* @brief        To get the current sub window ID on the top screen.
*               If the sub window is not existed, return invalid window Id(oxFFFF).
*
* @param[in]    hWin(HWIN)                  A pointer of window handle object.
*
* @retval       MAE_WndId                   output sub Window ID
* @retval       0xFFFF                      Failed.
*
*/
MAE_WndId WndGetCurrSubWindowId(IApplet *pApplet);


/** WndGetPreSubWindowId
* @brief        To get the previous sub window ID on the screen.(below the top)
*               If the window is not existed, return invalid window Id(oxFFFF).
*
* @param[in]    hWin(HWIN)              A pointer of window handle object.
*
* @retval       MAE_WndId               output sub Window ID
* @retval       0xFFFF                  Failed.
*
*/
MAE_WndId WndGetPreSubWindowId(IApplet *pApplet);

/** WndGetCurrSubDialogId
* @brief        To get the current sub dialog ID on the top screen.
*               If the sub dialog is not existed, return invalid dialog Id(oxFFFF).
*
* @param[in]    hWin(HWIN)                  A pointer of window handle object.
*
* @retval       MAE_WndId                   output sub dialog ID
* @retval       0xFFFF                      Failed.
*
*/
MAE_WndId WndGetCurrSubDialogId(IApplet *pApplet);

/** WndSetCurrSubWndSoftkeyVisible
 * @brief  This function set the softkey visiblity of the current sub window.
 *         The difference between this and WndSetSoftkeyVisible is the softkey
 *         bar region visiblity.  If invisible, WndSetCurrWndSoftkeyVisible will
 *         also cause the softkey bar region invisible, but WndSetSoftkeyVisible not.
 *
 * @param[in]   pApplet(IApplet*)   A pointer of IApplet object
 * @param[in]   eSKVisType          The visible type.
 *
 */
void WndSetCurrSubWndSoftkeyVisible(IApplet *pApplet, ViewSKVisType_t eSKVisType);

/** WndSetCurrSubWndStatusbarVisible
 * @brief  This function set the statusbar visiblity of the current sub window.
 *         The difference between this and WndSetStatusBarVisible is the status
 *         bar region visiblity.  If invisible, WndSetCurrWndStatusbarVisible will
 *         also cause the status bar region invisible, but WndSetStatusBarVisible not.
 *
 * @param[in]   pApplet(IApplet*)   A pointer of IApplet object
 * @param[in]   eSBVisType          The visible type.
 *
 */
void WndSetCurrSubWndStatusbarVisible(IApplet *pApplet, ViewSBVisType_t eSBVisType);


#endif //__MMI_MAE_SUBWINDOW_H__
