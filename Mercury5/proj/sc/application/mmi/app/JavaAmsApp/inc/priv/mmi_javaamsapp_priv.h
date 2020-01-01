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
* @file    mmi_javaamsapp_priv.h
* @version
* @brief   javaams applet private header file
*
*/

#ifndef __MMI_JAVAAMSAPP_PRIV_H__
#define __MMI_JAVAAMSAPP_PRIV_H__

#ifdef __JAVA_MMI__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_javasrv.h"
#include "mmi_common_vtm.h"
#include "mmi_baseapplet.h"
#include "mmi_base_util.h"
#include "mmi_common_dialog.h"
#include "mmi_common_mimetype.h"
#include "mmi_vendorapp.h"
#include "mmi_common_window.h"
#ifdef __WAP_MMI_CDWAP__
#include "mmi_cdwapapp.h"
#endif

#include "mmi_srv_header.h"
#include "mmi_javaamsapp_id.h"
#include "javaamsapp_resource.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/
#ifdef __JAVA_OAKMONT__
#define __JAVA_ACTIVE_INSTALL__ // Install procedure is controlled by MMI
#define __JAVA_CACHE_MIDLET_SUITE__ // Cache AMS list information in MMI
//#define __JAVA_NOPREINSTALL_LIST__ // Not shown preinstall midlet on java ams list
#ifdef __ONBOARD_USER_STORAGE_MMI__
//#define __JAVA_INSTALLTO_CARD_ONLY__
#endif
#endif
#if defined (__JAVA_DELTA__) || defined(__NCC_3RD_JAVA_PORTING_LAYER__)
#ifndef __NCC_3RD_JAVA_PORTING_LAYER__
#define __JAVA_PASSIVE_INSTALL__ // Install procedure is controller by VM
#endif
#define __JAVA_CACHE_MIDLET_SUITE__ // Cache AMS list information in MMI
#define GET_DIALOG_LSK(key) ((key >> 16) & 0xF)
#define GET_DIALOG_CSK(key) ((key >> 8)  & 0xF)
#define GET_DIALOG_RSK(key) (key & 0xF)
#define DIALOG_SK_RESUKLT(lsk, csk, rsk) ((lsk << 16) | (csk << 8) | rsk)
#define SET_CANCEL_INFO(info, key) ((info << 24) | key)
#endif
#if defined(__DUAL_CARD__)
#define __JAVA_SUPPORT_DUAL_CARD__
#endif

#define __SD_JAVA__ // If Java is only on SD
#define JAVA_PERMISSION_LEVEL_MAX 9
#define JAVA_INFORMATION_STR L"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s"

#ifdef __NCC_3RD_JAVA_PORTING_LAYER__
#define __NCC_3RD_JPL_SUPPORT_PROFILE_SELECT_OPTION__
#else
#define JAVA_PERMISSION
#define JAVA_MEMORY_STATUS
#endif

/*=============================================================*/
// Data type definition -- enum
/*=============================================================*/
// Show list reason
enum
{
    JAVAAMSAPP_SHOWLIST_NO_ACTION = 0,      // Do nothing
    JAVAAMSAPP_SHOWLIST_REFRESH_ALL,        // Refresh MIDlet suites list
    JAVAAMSAPP_SHOWLIST_DELETE_ONE,         // Refresh MIDlet suites list after uninstall one MIDlet suite
    JAVAAMSAPP_SHOWLIST_MEM_STATUS,         // Launch memory status applet
    JAVAAMSAPP_SHOWLIST_PERMISSIONS,        // Set permissions view
    JAVAAMSAPP_SHOWLIST_INFORMATION,        // Set information view
    JAVAAMSAPP_SHOWLIST_LAUNCH,             // Set launch view
};

// Dialog reason
enum
{
    JAVA_DIALOG_NONE = 0,

    // Waiting reason
    JAVA_DIALOG_INIT_WAITING,            // Init waitng
    JAVA_DIALOG_INIT_FAILED,             // Fail to init AMS
    JAVA_DIALOG_INIT_NO_ENOUGH_SPACE,    // Fail to init AMS due to low space
    JAVA_DIALOG_INIT_BUSY,               // Java is busy now
    JAVA_DIALOG_INIT_NOT_SUPPORT,        // Not support
    JAVA_DIALOG_PROCESS_WAITING,         // Process waiting

    // Exit reason
    JAVA_DIALOG_EXIT_NO_EXT_MEMCARD,       // Exit due to no external memory card
    JAVA_DIALOG_EXIT_DECISION,             // Exit confirmation
    JAVA_DIALOG_EXIT_MEMCARD_EXTRACTED,    // Exit due to external memory card is extracted during Midlet execution
    JAVA_DIALOG_EXIT_OPERATION_NOT_ALLOW,  // Exit due to operation not allowed. eg. Try to launch AMS when USB WebCam/MassStorage is active

    // Launch reason
    JAVA_DIALOG_LAUNCH_FAILED,           // Fail to launch MIDlet
    JAVA_DIALOG_LAUNCH_NOT_ALLOWED,      // Launch not allowed cuz MMS's busy

    // Permission reason
    JAVA_DIALOG_PERMISSIONS_GET_FAILED,  // Failed to get permissions of a given MIDlet suite
    JAVA_DIALOG_PERMISSIONS_SET_FAILED,      // Can't set permission value

    // Install reason
    JAVA_DIALOG_INSTALL_CHECK,                       // Install check progress
    JAVA_DIALOG_INSTALL_CONFIRM,                     // Install confirmation
    JAVA_DIALOG_INSTALL_PROGRESS,                    // Install progress
    JAVA_DIALOG_INSTALL_NEW_VERSION_CFM,             // Install confirmation with new version
    JAVA_DIALOG_INSTALL_OLD_VERSION_CFM,             // Install confirmation with old version
    JAVA_DIALOG_INSTALL_SAME_VERSION_CFM,            // Install confirmation with same version
    JAVA_DIALOG_INSTALL_KEEP_RMS_CFM,                // Install confirmation with keeping RMS data
    JAVA_DIALOG_INSTALL_LAUNCH,                      // Launch after installation
    JAVA_DIALOG_INSTALL_SUCCESS,                     // Install success
    JAVA_DIALOG_INSTALL_ERROR,                       // Install error
    JAVA_DIALOG_INSTALL_CARD_NO_ENOUGH_SPACE,        // Not enough space in memory card
    JAVA_DIALOG_INSTALL_PHONE_NO_ENOUGH_SPACE,       // Not enough space in phone
    JAVA_DIALOG_INSTALL_LOSS_OF_SERVICE,             // Lost of service
    JAVA_DIALOG_INSTALL_USER_CANCEL,                 // User cancel
    JAVA_DIALOG_INSTALL_NOT_DEFINE,                  // Install error
    JAVA_DIALOG_INSTALL_JAR_SIZE_MISMATCH,           // JAR size mismatch
    JAVA_DIALOG_INSTALL_ATTRIBUTE_MISMATCH,          // Attribute mismatch
    JAVA_DIALOG_INSTALL_INVALID_JAD,                 // Invalid JAD
    JAVA_DIALOG_INSTALL_INVALID_JAR,                 // Invalid JAR
    JAVA_DIALOG_INSTALL_CLDC_MIDP_VERSION,           // Wrong MIDP version
    JAVA_DIALOG_INSTALL_AUTHENTICATION_FAILURE,      // Authentication failure
    JAVA_DIALOG_INSTALL_AUTHORIZATION_FAILURE,       // Authorization failure
    JAVA_DIALOG_INSTALL_PUSH_REGISTRATION_FALIURE,   // Push registry failure
    JAVA_DIALOG_INSTALL_DELETION_NOTIFICATION,       // Deletion notification
    JAVA_DIALOG_INSTALL_AMSLIST_FULL,                // ams list full
    JAVA_DIALOG_INSTALL_LARGE_JAR,                   // jar too large
    JAVA_DIALOG_INSTALL_UNTRUSTED,                   // Warning of installing a un-trusted MIDlet
#ifdef __NCC_3RD_JAVA_PORTING_LAYER__
    JAVA_DIALOG_INSTALL_NAME_TOO_LONG,
    JAVA_DIALOG_INSATLL_MMS_BUSY,
    JAVA_DIALOG_INSTALL_BT_BUSY,
    JAVA_DIALOG_INSTALL_IO_CONFLICT,
    JAVA_DIALOG_INSTALL_SUITE_NOT_FOUND,
#ifdef __NCC_3RD_JAVA_WITH_PREINSTALL__
    JAVA_DIALOG_INSTALL_PREINSTALL,
    JAVA_DIALOG_RST_PREINSTALL_SUCCESS,
    JAVA_DIALOG_RST_PREINSTALL_FAILED,
#endif
    JAVA_DIALOG_RST_NETPROFILE_CONFIRM,
#endif
    // Un-install reason
    JAVA_DIALOG_UNINSTALL_CONFIRM,       // Un-install confirmation
    JAVA_DIALOG_UNINSTALL_PROCESS,       // Un-install process
    JAVA_DIALOG_UNINSTALL_SUCCESS,       // Un-install success
    JAVA_DIALOG_UNINSTALL_FAILED,        // Fail to un-install

    // Re-install reason
    JAVA_DIALOG_REINSTALL,
    JAVA_DIALOG_DAMAGED_REINSTALL,      // Fail to Launch AP cuz midlet is not exist

#ifdef __WAP_MMI_CDWAP__
    // Download reason
    JAVA_DIALOG_GET_JAR_CONFIRM,         // Download JAR confirmation
#endif

#ifdef __NCC_3RD_JPL_SUPPORT_PROFILE_SELECT_OPTION__
    JAVA_DIALOG_SIM_CARD_UNPRESENT_ALERT,
    JAVA_DIALOG_SIM_CARD_ERROR,
#endif
    JAVA_DIALOG_ERROR_MMS_BUSY,           // Launch not allowed cuz MMS's busy
#ifdef __NCC_3RD_JAVA_PORTING_LAYER__
    JAVA_DIALOG_ERROR_BT_BUSY,            // Launch not allowed cuz BT's busy
    JAVA_DIALOG_ERROR_SIM_INI_BUSY,
#endif//__NCC_3RD_JAVA_PORTING_LAYER__

    JAVA_DIALOG_MEMORY_INSUFFICIENT,
    JAVA_DIALOG_STORGE_FULL,
    // Add new dialog reason above this line
    JAVA_DIALOG_LAST,
};

// List type in ShowList mode
enum
{
    MIDLET_SUITE_LIST = 0,              // MIDletSuites list
    MIDLET_LIST,                        // MIDlets list of a given MIDlet suite
};

// Install Status
enum
{
    JAVAAMSAPP_INSTALL_NONE = 0,
    JAVAAMSAPP_INSTALL_PROCESSING,
    JAVAAMSAPP_INSTALL_COMPLETE,
};

// Permission Items
enum
{
    JAVA_PERMISSION_NETWORK_ACCESS = 0,
    JAVA_PERMISSION_MULTIMEDIA_RECORDING,
    JAVA_PERMISSION_WIRELESS_MESSAGING,
    JAVA_PERMISSION_APPLICATION_AUTO_INVOCATION,
    JAVA_PERMISSION_LOCAL_CONNECTIVITY,
    JAVA_PERMISSION_USER_DATA_READ,
    JAVA_PERMISSION_USER_DATA_WRITE,
    JAVA_PERMISSION_LAST,
};

// The reason why the Java launch is blocked
enum
{
    JAVA_BLOCKED_NONE,
    JAVA_BLOCKED_BY_MMS_RELOADING,          // Current action is blocked by MMS reloading
#ifdef __NCC_3RD_JAVA_PORTING_LAYER__
    JAVA_BLOCKED_BY_BT_ACTIVE,              // Current action is blocked by Bluttooth busy
    JAVA_BLOCKED_BY_SIM_INI,
#endif//__NCC_3RD_JAVA_PORTING_LAYER__
    JAVA_BLOCKED_BY_BACKGROUND_EXECUTION,   // Current action is blocked due to a existing background Java application
};
typedef u8 JavaAmsApp_BlockReason_t;
enum
{
    JAVA_STORAGE_INVALID = 0x00,
    JAVA_STORAGE_NAND = 0x01,
    JAVA_STORAGE_MEMCARD = 0x02,
    JAVA_STORAGE_MEMCARD2 = 0x04,
    JAVA_STORAGE_NOR = 0x08,
};
typedef u8 Java_Storage_e;

enum
{
    // Mapping to MNU_JAVAAMSAPP_STORAGE enum
    // if install to CARD only, the phone item need to be removed - the enum set to the last one.
#ifdef __JAVA_INSTALLTO_CARD_ONLY__
    JAVAAMSAPP_STORAGE_PHONE = MNU_JAVAAMSAPP_MAX_NUM-1,
    JAVAAMSAPP_STORAGE_CARD = 0, 
#else
    JAVAAMSAPP_STORAGE_PHONE = 0,
    JAVAAMSAPP_STORAGE_CARD, 
#endif
    JAVAAMSAPP_STORAGE_CARD2,
    JAVAAMSAPP_MAX_NUM,
};
/*=============================================================*/
// Data type definition -- typedef
/*=============================================================*/
typedef struct
{
    boolean bValid;
    u32 nMIDletSuiteIdx;
    u32 nMIDletIdx;
} LAUNCH_INFO_t;

#if defined (__JAVA_ACTIVE_INSTALL__) || defined (JAVAAMS_UPDATE)
typedef struct
{
    s32    nUpdate;
    s32    nTrusted;   // 0 means untrusted, 1 means trusted
    boolean bKeepRMS; // TRUE if user wants to keep RMS data
} MIDLET_CHECK_RESULT_t;
#endif // __JAVA_ACTIVE_INSTALL__

#ifdef __JAVA_CACHE_MIDLET_SUITE__
// Structure to store MIDlet Suite item
typedef struct
{
    u32 nIndex;                      // MIDlet Suite index
    MAE_WChar *pName;                // MIDlet Suite name
    u8 *pIconData;                   // Pointer to icon data
    u32 nIconSize;                   // Icon size
    boolean bPreinstall;             // TRUE if MIDlet suite is preinstall
    Java_Storage_e eStorage;          // Storage of MIDlet suite
} MIDLET_SUITE_ITEM_t;
#endif // __JAVA_CACHE_MIDLET_SUITE__

typedef struct
{
    u8 nLevel;
    u32 nTextId;
    u32 nMnuId;
} MIDLET_SUITE_PERMISSION_t;

// Install Wnd structure
typedef struct
{
    IWidget *pProgressWgt;
#ifdef __JAVA_PASSIVE_INSTALL__
    IWidget *pTextWdg;
#endif
} JavaSetInstallView_t;
#ifdef __NCC_3RD_JAVA_PORTING_LAYER__
typedef struct
{
    MenuWdgList_t   tMenuWdgList;
    MenuData_t      tMenuData;
    MenuCB_t        tMenuCB;
    u32             nListHightLightIndex;
    u32             nListFirstIndex;
}JavaAmsWndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
    OptionMenuData_t    tOptionMenuData;
    OptionMenuCB_t      tOptionMenuCB;
}JavaAmsOptionWndData_t;

typedef struct
{
    PopUpSelectWdgList_t tPopUpSelectWdgList;
    PopUpSelectData_t    tPopUpSelectData;
    PopUpSelectCB_t      tPopUpSelectCB;
}JavaAmsPopUpSelectWndData_t;

typedef struct
{
    PopUpInfoWdgList_t   tPopUInfoWdgList;
}JavaAmsPopUpInfoWndData_t;
#endif
typedef struct
{
    APPLET_BASE_ELEMENTS;
    boolean bExtMemCard;                            // TRUE if external memory card is available
#if (defined __JAVA_SUPPORT_DUAL_CARD__ || defined MINIJAVA_SUPPORT_DUAL_CARD)
    boolean bExtMemCard2;                            // TRUE if external memory card2 is available
#endif
    boolean bInit;                                  // TRUE if JAVA VM is initialized
    boolean bAllowLaunch;                           // TRUE if JavaAmsApp is allowed to launch MIDlet
    u32 nInstallState;                              // State of current install
    ArrayClass_t *pMIDletSuiteList;                  // Array model to store MIDlet suites list
    ArrayClass_t *pMIDletList;                       // Array model to store MIDlets list
    u32 nDialogReason;                              // Reason to prompt dialog
    MAE_WChar *pJadURL;                             // Local URL of JAD file for install
    MAE_WChar *pJarURL;                             // Local URL of JAR file for install
    u32 nMIDletSuiteCount;                          // Number of MIDlet suites
    u32 nMIDletCount;                               // Number of MIDlets of a given MIDlet suite
    u32 nEmbeddedReason;                            // Embedded start reason (embedded start for install/launch)
    u32 nListType;                                  // Type of current list(MIDlet suite/MIDlet)
    MenuWdgList_t tCreatePermissionWdgList;
    u32 nMIDletSuiteIdx;                            // Index of Highlighted MIDlet suite
    u32 nMIDletIdx;                                 // Index of Highlighted MIDlet
    u8 aPermission[JAVA_PERMISSION_LAST];           // Level of each permission
    u8 nRadioListPermissionIdx;
    s32 nInstallId;                                 // ID to install
#ifdef __JAVA_PASSIVE_INSTALL__
    IDataModel *pVenDataMdl;                        // Data model for dialog request from 3rd party Java VM
#endif
#if defined (__JAVA_ACTIVE_INSTALL__) || defined(JAVAAMS_UPDATE)
    MIDLET_CHECK_RESULT_t midletCheckResult;       // Result of MIDlet check
#endif
    MAE_WChar *pEmbeddedLaunchName;                 // MIDlet name used when embedded launch
    Java_Storage_e eSupportedStorage;               // Supported storage
    JAVASRV_STORAGE_e eInstallStorage;              // Storage to install
    boolean bExit;
#ifdef __WAP_MMI_CDWAP__
    tWapStartParm *pWapStartParam;                  // WAP start parameter
    boolean bJARDownload;                           // TRUE if downloading JAR
    MAE_Ret tWapDownloadRet;
#endif
#ifdef __ONBOARD_USER_STORAGE_MMI__
    u32 nStorageSelAdaptTxtId[MNU_JAVAAMSAPP_MAX_NUM]; //store text id setting for dynamic get data about ListMenu
#endif
#ifdef __JAVA_NOPREINSTALL_LIST__
    u8 nPreinstallCount;
#endif
} JavaAppData_t;

//Total scen.


/*=============================================================*/
// Handler Function
/*=============================================================*/
/** JavaAmsHomeWndHdl
* @brief        Show list window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsHomeWndHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
/** JavaAmsWndShowListHdl
* @brief        Show list window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsWndShowListHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
/** JavaAmsWndOptionMenuHdl
* @brief        Option menu window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsWndOptionMenuHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
/** JavaAmsWndInstallHdl
* @brief        Install window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsWndInstallHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
/** JavaAmsWndPermissionViewHdl
* @brief        Permission window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsWndPermissionViewHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
/** JavaAmsWndRadioListHdl
* @brief        Radio List window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsWndRadioListHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
/** JavaAmsWndInformationHdl
* @brief        Information window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsWndInformationHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);

#ifdef __APP_MMI_BACKGROUND_EXECUTION__
/** JavaAmsWndPopupRadioSelectionHdl
* @brief        Radio Selection window handle function (For Background Execution)
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsWndBGRadioSelectHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
#endif /* __APP_MMI_BACKGROUND_EXECUTION__*/


/** JavaAmsWndStorageSelectHdl
* @brief        Storage Selection window handle function (For Background Execution)
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
*
*/
#ifdef __ONBOARD_USER_STORAGE_MMI__
MAE_Ret JavaAmsWndStorageSelectHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);
#endif

/*=============================================================*/
// AP Entry Function
/*=============================================================*/
/** JavaAmsConstructor
* @brief        Construct Applet function(when receive MAE_EVT_CONSTRUCT)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsConstructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);
/** JavaAmsDestructor
* @brief        Release Applet function(when receive MAE_EVT_DESTRUCT)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_Ret             Success.
*
*/
MAE_Ret JavaAmsDestructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);
/** JavaAmsStartCB
* @brief        Applet start function(when receive MAE_EVT_APP_START)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter [Paremeter from StartApplet : JavaAmsApp_EmbeddedParam_t]
*
* @retval       TRUE                Event is handled
*
*/
boolean JavaAmsStartCB(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
/** JavaAmsStopCB
* @brief        Applet Stop function(when receive MAE_EVT_APP_STOP)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean JavaAmsStopCB(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
/** JavaAmsKeyPressCB
* @brief        Handle key press function(when receive MAE_EVT_KEY_PRESS)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter [Key Code]
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean JavaAmsKeyPressCB(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
/** JavaAmsSuspendCB
* @brief        Applet Suspend function(when receive MAE_EVT_APP_SUSPEND)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean JavaAmsSuspendCB(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);
/** JavaAmsResumeCB
* @brief        Applet Resume function(when receive MAE_EVT_APP_RESUME)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
*
*/
boolean JavaAmsResumeCB(IApplet* pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);

/*=============================================================*/
//  Call back Functions / Java Service
/*=============================================================*/
/** JavaAmsInitCB
* @brief        Java ams initial function
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Init result]
* @param[in]    nParam2             Second parameter
*
* @retval       None
*
*/
void JavaAmsInitCB(void *ps, u32 param1, u32 param2);
/** JavaAmsGetSuiteInfoCB
* @brief        Get Suite Info function (Show on Information Menu)
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Get info Result]
* @param[in]    nParam2             Second parameter [Get info parameter : mmi_ams_GetSuiteInfoRsp_t]
*
* @retval       None
*
*/
void JavaAmsGetSuiteInfoCB(void *ps, u32 param1, u32 param2);
/** JavaAmsGetSuiteCountCB
* @brief        Get Suite Count function
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [MIDlet suites count]
* @param[in]    nParam2             Second parameter
*
* @retval       None
*
*/
void JavaAmsGetSuiteCountCB(void *ps, u32 param1, u32 param2);
/** JavaAmsCheckMidletCnfCB
* @brief        Check Midlet confirmation function (For installation)
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [check install result]
* @param[in]    nParam2             Second parameter
*
* @retval       None
*
*/
void JavaAmsCheckMidletCnfCB(void *ps, u32 param1, u32 param2);
/** JavaAmsCheckMidletIndCB
* @brief        Check Midlet Information function (For installation progress status checking)(__JAVA_ACTIVE_INSTALL__)
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Check install result parameter : mmi_ams_CheckResult_t]
* @param[in]    nParam2             Second parameter [Check progress]
*
* @retval       None
*
*/
void JavaAmsCheckMidletIndCB(void *ps, u32 param1, u32 param2);
/** JavaAmsInstallMidletCnfCB
* @brief        Install Midlet confirmation function (For finishing installation checking)
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Check install result : MMI_JAVA_OK]
* @param[in]    nParam2             Second parameter [MIDlet Suite Idx]
*
* @retval       None
*
*/
void JavaAmsInstallMidletCnfCB(void *ps, u32 param1, u32 param2);
/** JavaAmsInstallMidletCnfCB
* @brief        Install Midlet Information function (For installation progress status checking)
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Install Result Parameter : mmi_ams_InstallResult_t]
* @param[in]    nParam2             Second parameter [Install progress]
*
* @retval       None
*
*/
void JavaAmsInstallMidletIndCB(void *ps, u32 param1, u32 param2);
/** JavaAmsInstallProgressReqNotifyCB
* @brief        Install Progress Req function (For installation progress status checking)(__JAVA_PASSIVE_INSTALL__)
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Install progress]
* @param[in]    nParam2             Second parameter[softkey]
*
* @retval       None
*
*/
void JavaAmsInstallProgressReqNotifyCB(void *ps, u32 param1, u32 param2);
/** JavaAmsDrawInstallDialogReqNotifyCB
* @brief        Draw Installation Progress bar function (__JAVA_PASSIVE_INSTALL__)
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Date Model parameter : IDataModel]
* @param[in]    nParam2             Second parameter
*
* @retval       None
*
*/
void JavaAmsDrawInstallDialogReqNotifyCB(void *ps, u32 param1, u32 param2);
/** JavaAmsGetMidletCountCB
* @brief        Get Midlet Count in Suite
* (For checking Option menu success or not : if index is wrong, then it'll return Fail)
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Get Count result:MMI_JAVA_OK]
* @param[in]    nParam2             Second parameter [Midlet Count parameter : mmi_ams_GetMidletCntRsp_t]
*
* @retval       None
*
*/
void JavaAmsGetMidletCountCB(void *ps, u32 param1, u32 param2);
/** JavaAmsGetMidletInfoCB
* @brief        Get Midlet Info
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Get Info result:MMI_JAVA_OK]
* @param[in]    nParam2             Second parameter [Midlet Info parameter : mmi_ams_GetMidletInfoRsp_t]
*
* @retval       None
*
*/
void JavaAmsGetMidletInfoCB(void *ps, u32 param1, u32 param2);
/** JavaAmsSetPermissionCB
* @brief        Send Midlet permission RSP
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Get Permission Result]
* @param[in]    nParam2             Second parameter [Permission parameter : mmi_ams_GetPermissionRsp_t]
*
* @retval       None
*
*/
void JavaAmsSetPermissionCB(void *ps, u32 param1, u32 param2);
/** JavaAmsGetPermissionCB
* @brief        Get Midlet permission Info
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Get Permission Result]
* @param[in]    nParam2             Second parameter [Permission parameter : mmi_ams_GetPermissionRsp_t]
*
* @retval       None
*
*/
void JavaAmsGetPermissionCB(void *ps, u32 param1, u32 param2);
/** JavaAmsRemoveSuiteCB
* @brief        uninstall Midlet
*
* @param[in]    ps               The pointer of Applet
* @param[in]    nParam1             First parameter [Remove result:MMI_JAVA_OK]
* @param[in]    nParam2             Second parameter [Midlet index]
*
* @retval       None
*
*/
void JavaAmsRemoveSuiteCB(void *ps, u32 param1, u32 param2);

/*=============================================================*/
// Softkey function
/*=============================================================*/
/** JavaAmsShowListViewSoftkeyActCB
* @brief        Callback function for Show list softkey act event [Menu Widget Active]
*
* @param[in]    pApplet          The pointer of Applet
* @param[in]    pUsrData
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void JavaAmsShowListViewSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
/** JavaAmsPermissionsViewSoftkeyActCB
* @brief        Callback function for Permission View softkey act event [Menu Widget Active]
*
* @param[in]    pApplet          The pointer of Applet
* @param[in]    pUsrData
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void JavaAmsPermissionsViewSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
/** JavaAmsOptionMenuViewSoftkeyActCB
* @brief        Callback function for Option Menu softkey act event [Option Menu Widget Active]
*
* @param[in]    pApplet          The pointer of Applet
* @param[in]    pUsrData
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void JavaAmsOptionMenuViewSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
/** JavaAmsRadioListViewSoftkeyActCB
* @brief        Callback function for Radio List softkey act event [Popup Selection Widget Active]
*
* @param[in]    pApplet          The pointer of Applet
* @param[in]    pUsrData
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void JavaAmsRadioListViewSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
/** JavaAmsBGRadioSelectSoftkeyActCB
* @brief        Callback function for Radio Selection softkey act event [Popup Selection Widget Active] [For Background Execution]
*
* @param[in]    pApplet          The pointer of Applet
* @param[in]    pUsrData
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void JavaAmsBGRadioSelectSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
/** JavaAmsStorageSelectSoftkeyActCB
* @brief        Callback function for Softkey Selection act event [Popup Selection Widget Active] [For Memory/Card Selection]
*
* @param[in]    pCusHandle          The pointer of Applet
* @param[in]    pWndMsg            (CommWindowMsg_t)
* @param[in]    pParam1              Storage Type (VFS_VOL_TYPE)
* @param[in]    pParam2            Event (WidgetEvtCode_t)
*
* @retval       MAE_RET_SUCCESS
*
*/
MAE_Ret JavaAmsStorageSelectSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
/** JavaAmsDialogHandler
* @brief        Callback function when press Key on dialog
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                 Event
* @param[in]    nParam1            First parameter
* @param[in]    nParam2            Second parameter
*
* @retval       MAE_Ret             Success.
* @retval       other                   Failed.
*
*/
MAE_Ret JavaAmsDialogHandler(void *pApplet, MAE_EventId evt, u32 nParm1, u32 nParm2);

#endif // __JAVA_MMI__

#endif /* __MMI_JAVAAMSAPP_PRIV_H__ */
