/**
* @file mmi_srv_shortcut.h
*/
#ifndef __MMI_SRV_SHORTCUT_H__
#define __MMI_SRV_SHORTCUT_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_shortcutssrv.h"


/** SrvShortcutReadKeyInfo
* @brief        The interface is used to read the detail settings of IDLE navigation, soft, or numeric keys
*
* @param[in]    eKey                    SHORTCUTS_KEYTYPE_NAVIKEY_UP, SHORTCUTS_KEYTYPE_NAVIKEY_DOWN, SHORTCUTS_KEYTYPE_NAVIKEY_LEFT, SHORTCUTS_KEYTYPE_NAVIKEY_RIGHT,
*                                       SHORTCUTS_KEYTYPE_SOFTKEY_LEFT, SHORTCUTS_KEYTYPE_SOFTKEY_MIDDLE, SHORTCUTS_KEYTYPE_SOFTKEY_RIGHT,
*                                       SHORTCUTS_KEYTYPE_NUMKEY_1, SHORTCUTS_KEYTYPE_NUMKEY_2, ..., or SHORTCUTS_KEYTYPE_NUMKEY_9.
* @param[out]   pKeyInfo                Pointer of detail setting of IDLE navigation, soft, or numeric key.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutReadKeyInfo(ShortcutsKeyType_e eKey, ShortcutsKeyInfo_t *pKeyInfo);

/** SrvShortcutReadNaviKeyInfo
* @brief        The interface is used to read the detail settings of IDLE navigation key
*
* @param[in]    eKey                    SHORTCUTS_KEYTYPE_NAVIKEY_UP, SHORTCUTS_KEYTYPE_NAVIKEY_DOWN, SHORTCUTS_KEYTYPE_NAVIKEY_LEFT, or SHORTCUTS_KEYTYPE_NAVIKEY_RIGHT.
* @param[out]   pKeyInfo                Pointer of detail setting of IDLE navigation key.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutReadNaviKeyInfo(ShortcutsKeyType_e eKey, ShortcutsKeyInfo_t *pKeyInfo);

/** SrvShortcutReadSoftKeyInfo
* @brief        The interface is used to read the detail shortcut settings of IDLE soft key
*
* @param[in]    eKey                    SHORTCUTS_KEYTYPE_SOFTKEY_LEFT, SHORTCUTS_KEYTYPE_SOFTKEY_MIDDLE, or SHORTCUTS_KEYTYPE_SOFTKEY_RIGHT.
* @param[out]   pKeyInfo                Pointer of detail shortcut settings of IDLE soft key.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutReadSoftKeyInfo(ShortcutsKeyType_e eKey, ShortcutsKeyInfo_t *pKeyInfo);

/** SrvShortcutReadNumKeyInfo
* @brief        The interface is used to read the detail shortcut settings of IDLE numeric key
*
* @param[in]    eKey                    SHORTCUTS_KEYTYPE_NUMKEY_1, SHORTCUTS_KEYTYPE_NUMKEY_2, ..., or  SHORTCUTS_KEYTYPE_NUMKEY_9.
* @param[out]   pKeyInfo                Pointer of detail shortcut settings of IDLE numeric key.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutReadNumKeyInfo(ShortcutsKeyType_e eKey, ShortcutsKeyInfo_t *pKeyInfo);

/** SrvShortcutReadListInfo
* @brief        The interface is used to read the detail settings of whole Shortcuts List
*
* @param[out]   pListInfo               Pointer of detail shortcut settings of whole Shortcuts List.
*
* @retval   total item number of Shortcuts List
*/
u16 SrvShortcutReadListInfo(ShortcutsListInfo_t *pListInfo);

/** SrvShortcutWriteNaviKeyInfo
* @brief        The interface is used to write the detail settings of IDLE navigation key

* @param[in]    eKey                    SHORTCUTS_KEYTYPE_NAVIKEY_UP, SHORTCUTS_KEYTYPE_NAVIKEY_DOWN, SHORTCUTS_KEYTYPE_NAVIKEY_LEFT, or SHORTCUTS_KEYTYPE_NAVIKEY_RIGHT.
* @param[in]    pKeyInfo                Pointer of detail shortcut settings of IDLE navigation key.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutWriteNaviKeyInfo(ShortcutsKeyType_e eKey, ShortcutsNaviKeyInfo_t *pKeyInfo);

/** SrvShortcutWriteSoftKeyInfo
* @brief        The interface is used to write the detail shortcut settings of IDLE soft key

* @param[in]    eKey                    SHORTCUTS_KEYTYPE_SOFTKEY_LEFT, SHORTCUTS_KEYTYPE_SOFTKEY_MIDDLE, or SHORTCUTS_KEYTYPE_SOFTKEY_RIGHT.
* @param[in]    pKeyInfo                Pointer of detail shortcut settings of IDLE soft key.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutWriteSoftKeyInfo(ShortcutsKeyType_e eKey, ShortcutsSoftKeyInfo_t *pKeyInfo);

/** SrvShortcutWriteNumKeyInfo
* @brief        The interface is used to write the detail shortcut settings of IDLE numeric key

* @param[in]    eKey                    SHORTCUTS_KEYTYPE_NUMKEY_1, SHORTCUTS_KEYTYPE_NUMKEY_2, ..., or  SHORTCUTS_KEYTYPE_NUMKEY_9.
* @param[in]    pKeyInfo                Pointer of detail shortcut settings of IDLE numeric key.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutWriteNumKeyInfo(ShortcutsKeyType_e eKey, ShortcutsNumKeyInfo_t *pKeyInfo);

/** SrvShortcutWriteListInfo
* @brief        The interface is used to write the detail shortcut settings of Shortcuts List
*
* @param[in]    pListInfo               Pointer of detail shortcut settings of Shortcuts List.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutWriteListInfo(ShortcutsListInfo_t *pListInfo);

/** SrvShortcutGetKeyString
* @brief        The interface is used to get the display string of given shortcut key code
*
* @param[in]    u32KeyCode              MAE_KEY_UP, MAE_KEY_DOWN, MAE_KEY_LEFT, MAE_KEY_RIGHT, 
*                                       MAE_KEY_SKLEFT, MAE_KEY_SKRIGHT, MAE_KEY_1, ..., or MAE_KEY_9.
* @param[out]   pDispString             Pointer of MAE_WChar for display string.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutGetKeyString(u32 u32KeyCode, MAE_WChar *pDispString);

/** SrvShortcutLaunchKeyShortcut
* @brief        The interface is used to launch the assigned application of given shortcut key type
*
* @param[in]    u32KeyCode              MAE_KEY_UP, MAE_KEY_DOWN, MAE_KEY_LEFT, MAE_KEY_RIGHT, 
*                                       MAE_KEY_SKLEFT, MAE_KEY_SKRIGHT, MAE_KEY_1, ..., or MAE_KEY_9.
* @param[in]    u32LaunchByKeyCode      MAE_KEY_ACTION, MAE_KEY_SEND, or MAE_KEY_SEND2.
* @param[in]    nEventId                MAE_EVT_KEY_PRESS, or MAE_EVT_KEY_LONGPRESS.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchKeyShortcut(u32                     u32KeyCode,
                                     u32                     u32LaunchByKeyCode,
                                     MAE_EventId             nEventId);

/** SrvShortcutLaunchNaviKey
* @brief        The interface is used to launch the assigned application of given navigation key type
*
* @param[in]    u32KeyCode              MAE_KEY_UP, MAE_KEY_DOWN, MAE_KEY_LEFT, or MAE_KEY_RIGHT.
* @param[in]    u32LaunchByKeyCode      MAE_KEY_ACTION, MAE_KEY_SEND, or MAE_KEY_SEND2.
* @param[in]    nEventId                MAE_EVT_KEY_PRESS, or MAE_EVT_KEY_LONGPRESS.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchNaviKey(u32                     u32KeyCode,
                                 u32                     u32LaunchByKeyCode,
                                 MAE_EventId             nEventId);

/** SrvShortcutLaunchSoftKey
* @brief        The interface is used to launch the assigned application of given soft key type

* @param[in]    u32KeyCode              MAE_KEY_SKLEFT, MAE_KEY_ACTION, or MAE_KEY_SKRIGHT.
* @param[in]    u32LaunchByKeyCode      MAE_KEY_ACTION, MAE_KEY_SEND, or MAE_KEY_SEND2.
* @param[in]    nEventId                MAE_EVT_KEY_PRESS, or MAE_EVT_KEY_LONGPRESS.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchSoftKey(u32                     u32KeyCode,
                                 u32                     u32LaunchByKeyCode,
                                 MAE_EventId             nEventId);

/** SrvShortcutLaunchNumKey
* @brief        The interface is used to launch the assigned application of given numeric key type
*
* @param[in]    u32KeyCode              MAE_KEY_1, MAE_KEY_2, ..., MAE_KEY_9, MAE_KEY_0, MAE_KEY_STAR, or MAE_KEY_HASH.
* @param[in]    u32LaunchByKeyCode      MAE_KEY_ACTION, MAE_KEY_SEND, or MAE_KEY_SEND2.
* @param[in]    nEventId                MAE_EVT_KEY_PRESS, or MAE_EVT_KEY_LONGPRESS.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchNumKey(u32         u32KeyCode,
                                u32         u32LaunchByKeyCode,
                                MAE_EventId nEventId);

/** SrvShortcutLaunchListShortcut
* @brief        The interface is used to launch the assigned application of given shortcut list index
*
* @param[in]    u8ListIdx               The index (0-base) in shortcuts list.
* @param[in]    pListInfo               Pointer of detail shortcut settings of whole Shortcuts List.
* @param[in]    n32LaunchByKeyCode      MAE_KEY_ACTION, MAE_KEY_SEND, or MAE_KEY_SEND2.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchListShortcut(u8                  u8ListIdx,
                                      ShortcutsListInfo_t *pKeyInfo,
                                      u32                 u32LaunchByKeyCode);

/** SrvShortcutLaunchAP
* @brief        The interface is used to launch the AP by given class Id and parameter
*
* @param[in]    nClsId                  Class Id of AP.
* @param[in]    u32Param                Parameter for launch specific AP.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchAP(MAE_ClsId nClsId, u32 u32Param);

/** SrvShortcutLaunchFunc
* @brief        The interface is used to launch the AP by given shortcut function Id and parameter
*
* @param[in]    eFuncId                 Shortcut function Id.
* @param[in]    u32Param                Parameter for launch specific AP.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchFunc(ShortcutsFuncId_e eFuncId, u32 u32Param);

/** SrvShortcutConvertListItemString
* @brief        The interface is used to convert stored shortcuts list item info into display string
*
* @param[in]    pListInfo               Pointer of detail shortcut settings of Shortcuts List.
* @param[out]   pDispString             Pointer of MAE_WChar to get converted display string.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutConvertListItemString(ShortcutsListInfo_t *pListInfo, MAE_WChar *pDispString);

/** SrvShortcutGetKeyAssignStatus
* @brief        The interface is used to get key assign status
*
* @param[in]    u32KeyCode              MAE_KEY_UP, MAE_KEY_DOWN, MAE_KEY_LEFT, MAE_KEY_RIGHT,
*                                       MAE_KEY_SKLEFT, MAE_KEY_ACTION, MAE_KEY_SKRIGHT,
*                                       MAE_KEY_1, MAE_KEY_2, ..., MAE_KEY_9, MAE_KEY_0, MAE_KEY_STAR, or MAE_KEY_HASH.
* @param[in]    nEventId                MAE_EVT_KEY_PRESS, or MAE_EVT_KEY_LONGPRESS.
* @param[out]   pFuncId                 Pointer of ShortcutsFuncId_e to get assigned shortcut function id.
*
* @retval   ShortcutsKeyAssignStatus_e to get assign status
*/
ShortcutsKeyAssignStatus_e SrvShortcutGetKeyAssignStatus(u32 u32KeyCode,
                                                         MAE_EventId    nEventId,
                                                         ShortcutsFuncId_e *pFuncId);

/** SrvShortcutGetNumKeyTextId
* @brief        The interface is used to get text id of assigned numeric key
*
* @param[in]    u32KeyCode              MAE_KEY_1, MAE_KEY_2, ..., MAE_KEY_9, MAE_KEY_0, MAE_KEY_STAR, or MAE_KEY_HASH.
* @param[out]   pTextId                 Pointer of u16 to get text id of assigned numeric key.
*
* @retval   SRVCLIENT_RET_SUCCESS       If successful.
* @retval   SRVCLIENT_RET_FAILED        If an error happen.
* @retval   SRVCLIENT_RET_BAD_PARAM     If input parameter error.
*/
MAE_Ret SrvShortcutGetNumKeyTextId(u32 u32KeyCode, u16 *pTextId);

/** SrvShortcutGetFuncInfoById
* @brief        The interface is used to get id of assigned function id
*
* @param[in]    eFuncId                 Shortcut function Id.
* @param[in]    eType                   ShortcutFuncInfo_e of info type.
* @param[out]   pInfo                   Pointer of u32 to get value of given shortcut function id & info type.
*/
MAE_Ret SrvShortcutGetFuncInfoById(ShortcutsFuncId_e eFuncId, ShortcutFuncInfo_e eType, u32 *pInfo);

/** SrvShortcutGetSoftKeyImageId
* @brief        The interface is used to get image id of assigned soft key
*
* @param[in]    u32KeyCode              MAE_KEY_SKLEFT, MAE_KEY_ACTION, MAE_KEY_SKRIGHT
* @param[out]   pImgId                  Pointer of u32 to get image id of given soft key.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutGetSoftKeyImageId(u32 u32KeyCode, u32 *pImgId);

/** SrvShortcutLaunchAPwTransId
* @brief  The interface is used to launch the AP with transition by given class Id and parameter
*
* @param[in]    nClsId                  Class Id of AP.
* @param[in]    u32Param                Parameter for launch specific AP.
* @param[in]    u32EntryTransId         Transition Id for entering AP.
* @param[in]    u32ExitTransId          Transition Id for exiting AP.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchAPwTransId(MAE_ClsId   nClsId,
                                    u32         u32Param,
                                    u32         u32EntryTransId,
                                    u32         u32ExitTransId);

/** SrvShortcutLaunchFuncwTransId
* @brief        The interface is used to launch the AP by given shortcut function Id and parameter
*
* @param[in]    eFuncId                 Shortcut function Id.
* @param[in]    u32Param                Parameter for launch specific AP.
* @param[in]    u32EntryTransId         Transition Id for entering AP.
* @param[in]    u32ExitTransId          Transition Id for exiting AP.
*
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvShortcutLaunchFuncwTransId(ShortcutsFuncId_e eFuncId,
                                      u32               u32Param,
                                      u32               u32EntryTransId,
                                      u32               u32ExitTransId);

/*-------------------------------------------------------------------------*/
#endif /* __MMI_SRV_SHORTCUT_H__ */
