/**
* @file    mmi_srv_touchshortcut.h
* @brief
*
*/

#ifndef __MMI_SRV_TOUCHSHORTCUT_H__
#define __MMI_SRV_TOUCHSHORTCUT_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_touchshortcutsrv.h"


/*=============================================================*/
// Public Function Implementations
/*=============================================================*/

//Specific Service ListenerCallBack API

typedef void (*SrvTouchShortcutCB)(void *pThis);

/** SrvTouchShortcutSetShortCut1TouchedCB
* @brief  Set the callback function for the shortcut1 shortcut is touched.
*
* @param[in]      pfnCallBack                     TOUCHSHORTCUTSRV_EVT_SHORTCUT1 Callback function point
*/
void SrvTouchShortcutSetShortCut1TouchedCB(SrvTouchShortcutCB pfnCallBack);

/** SrvTouchShortcutSetShortCut2TouchedCB
* @brief   Set the callback function for the shortcut2 shortcut is touched.
* 
* @param[in]      pfnCallBack                     TOUCHSHORTCUTSRV_EVT_SHORTCUT2 Callback function point
*/
void SrvTouchShortcutSetShortCut2TouchedCB(SrvTouchShortcutCB pfnCallBack);

/** SrvTouchShortcutSetShortCut3TouchedCB
* @brief    Set the callback function for the shortcut3 shortcut is touched.
* 
* @param[in]      pfnCallBack                     TOUCHSHORTCUTSRV_EVT_SHORTCUT3 Callback function point
*/
void SrvTouchShortcutSetShortCut3TouchedCB(SrvTouchShortcutCB pfnCallBack);

/** SrvTouchShortcutSetShortCut4TouchedCB
* @brief   Set the callback function for the shortcut4 shortcut is touched.
* 
* @param[in]      pfnCallBack                     TOUCHSHORTCUTSRV_EVT_SHORTCUT4 Callback function point
*/
void SrvTouchShortcutSetShortCut4TouchedCB(SrvTouchShortcutCB pfnCallBack);

/** SrvTouchShortcutSetShortCut5TouchedCB
* @brief   Set the callback function for the shortcut5 shortcut is touched.
* 
* @param[in]      pfnCallBack                     TOUCHSHORTCUTSRV_EVT_SHORTCUT5 Callback function point
*/
void SrvTouchShortcutSetShortCut5TouchedCB(SrvTouchShortcutCB pfnCallBack);

/** SrvTouchShortcutSetShortCut6TouchedCB
* @brief    Set the callback function for the shortcut6 shortcut is touched.
* 
* @param[in]      pfnCallBack                     TOUCHSHORTCUTSRV_EVT_SHORTCUT6 Callback function point
*/
void SrvTouchShortcutSetShortCut6TouchedCB(SrvTouchShortcutCB pfnCallBack);

/** SrvTouchShortcutDisableShortcut
* @brief		  disable some shurtcut by TOUCHSHORTCUTSRV_NOTIFY_MASK_e enum
* 
* @param[in]      eShortcutMask		Shortcut mask to choose which shortcuts
*/
void SrvTouchShortcutDisableShortcut(TOUCHSHORTCUTSRV_NOTIFY_MASK_e eShortcutMask);


/** SrvTouchShortcutEnableShortcut
* @brief		  enable some shurtcut by TOUCHSHORTCUTSRV_NOTIFY_MASK_e enum
* 
* @param[in]      eShortcutMask    Shortcut mask to choose which shortcuts
*/
void SrvTouchShortcutEnableShortcut(TOUCHSHORTCUTSRV_NOTIFY_MASK_e eShortcutMask);

#endif /*__MMI_SRV_TOUCHSHORTCUT_H__*/
