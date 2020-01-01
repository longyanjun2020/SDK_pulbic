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
* @file mmi_worldclockapp_priv.h
*
* Class Id: CLSID_WORLDCLOCKAPP
*
* @version $Id$
*/
#ifndef __MMI_JAVAFACTORYAPP_PRIV_H__
#define __MMI_JAVAFACTORYAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_javasrv.h"
#include "mmi_common_dialog.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_custom.h"
#include "mmi_common_vtm.h"


#include "mmi_baseapplet.h"
#include "mmi_javafactoryapp.h"
#include "mmi_launcher_common.h"
#include "mmi_javafactoryapp_custom.h"
#include "mmi_mae_file_util.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifdef __JAVA_DELTA__
#define __JAVA_PASSIVE_INSTALL__ // Install procedure is controller by VM
#else
#define __JAVA_ACTIVE_INSTALL__ // Install procedure is controlled by MMI
#endif
#define DEFAULT_RSP_LSK(key) ((key >> 16) & 0xF)

/*=============================================================*/
// Data type definition
/*=============================================================*/
enum
{
    DIALOG_NONE = 0,
    DIALOG_INIT,
    DIALOG_INSTALLING,
    DIALOG_COMPLETE,
    DIALOG_ERROR,
    DIALOG_INSERT_MEMCARD,
    DIALOG_LAST,
};
typedef u8 JavaFactoryAppDialog_e;

typedef struct
{
    JavaFactoryAppDialog_e  eDialog;
    u32                     nType;
    u32                     nTxtID;
} JavaFactoryAppDialogItem_t;

typedef struct MIDletInfo_Tag
{
    struct MIDletInfo_Tag *pPrev;
    struct MIDletInfo_Tag *pNext;
    MAE_WChar *pBaseName;   // Base name of Java MIDlet
    MAE_WChar *pJadUrl;     // JAD URL
    MAE_WChar *pJarUrl;     // JAR URL
} MIDletInfo_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    boolean bInit;                   // TRUE if JAVA VM is initialized
    MIDletInfo_t *psMIDletList;      // List of MIDlets to install
    MIDletInfo_t *psCurMIDlet;       // Current installing MIDlet
    IWidget *pProgressWdg;           // Progress widget for install progress
    JavaFactoryAppDialog_e eDialog;  // Current dialog
    boolean bTerminate;              // TRUE if being requested for termination
#ifdef __JAVA_ACTIVE_INSTALL__    
    s32 nInstallId;                  // install id for oakmont checking
#endif
} JavaFactoryAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret JavaFactoryAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret JavaFactoryAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean JavaFactoryAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean JavaFactoryAppStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/*=============================================================*/
// Local function definition
/*=============================================================*/
static boolean _JavaFactoryAppLaunch(UrlSrvUrlHdl_t pUrl, void *pUserData, void **ppvLaunchObj, CmnAppLaunchRspCbInfo_t *psRspCbInfo);
static void _JavaFactoryAppInstallProgressReqNotifyCB(void *ps, u32 nParam1, u32 nParam2);
static void _JavaFactoryAppDrawInstallDialogReqNotifyCB(void *ps, u32 nParam1, u32 nParam2);
static void _JavaFactoryAppCheckMidletIndCB(void *ps, u32 nParam1, u32 nParam2);
static void _JavaFactoryAppInstallMidletIndCB(void *ps, u32 nParam1, u32 nParam2);
static void _JavaFactoryAppAmsInitCB(void *ps, u32 nParam1, u32 nParam2);
static MAE_Ret _JavaFactoryAppCheckJar(JavaFactoryAppData_t *pThis);
static MAE_Ret _JavaFactoryAppInstallJar(JavaFactoryAppData_t *pThis);
static MAE_Ret _JavaFactoryAppCreateDialog(JavaFactoryAppData_t *pThis, JavaFactoryAppDialog_e eDialog);
static void _JavaFactoryAppCloseDialog(JavaFactoryAppData_t *pThis);
static void _JavaFactoryAppDialogTimerCb(void *pData);
static void _JavaFactoryAppQueueMIDlet(MIDletInfo_t **ppHead, MIDletInfo_t *psMIDlet);
static void _JavaFactoryAppDeQueueMIDlet(MIDletInfo_t **ppHead);

#endif /* __MMI_JAVAFACTORYAPP_PRIV_H__ */

