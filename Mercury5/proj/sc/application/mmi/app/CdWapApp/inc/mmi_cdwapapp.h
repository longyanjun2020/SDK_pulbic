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
* @file    mmi_cdwapapp.h
* @version
* @brief   CdWap header file
*
*/

#ifndef __MMI_CDWAPAPP_H__
#define __MMI_CDWAPAPP_H__


/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_wap.h"

#ifdef __WAP_MMI_CDWAP__
#include "mmi_venappid.h"
#include "mmi_req_vendor.h"
#include "mmi_base_util.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/


/**
 * External Events
 */
#define CDWAPAPP_EVT_ACTIVE_WAP_APP				(CLSID_CDWAPAPP << 16 | 1)
#define CDWAPAPP_EVT_OPEN_OPTMENU				(CLSID_CDWAPAPP << 16 | 2)
#define CDWAPAPP_EVT_OPEN_DIALOG				(CLSID_CDWAPAPP << 16 | 3)
#define CDWAPAPP_EVT_BACK_MAIN_MENU				(CLSID_CDWAPAPP << 16 | 4)
#define CDWAPAPP_EVT_OPT_MENU_OPER				(CLSID_CDWAPAPP << 16 | 5)
#define CDWAPAPP_EVT_OPEN_EXPLORER				(CLSID_CDWAPAPP << 16 | 6)
#define CDWAPAPP_EVT_RETURN_MAIN_PAGE			(CLSID_CDWAPAPP << 16 | 7)
#define CDWAPAPP_EVT_EDIT_CONTENT				(CLSID_CDWAPAPP << 16 | 8)
#define CDWAPAPP_EVT_INPUT_ADDRESS				(CLSID_CDWAPAPP << 16 | 9)
#define CDWAPAPP_EVT_EDIT_BOOKMARK				(CLSID_CDWAPAPP << 16 | 10)
#define CDWAPAPP_EVT_CREATE_FOLDER				(CLSID_CDWAPAPP << 16 | 11)
#define CDWAPAPP_EVT_RENAME_FOLDER				(CLSID_CDWAPAPP << 16 | 12)
#define CDWAPAPP_EVT_ENTER_SETPAGE				(CLSID_CDWAPAPP << 16 | 13)
#define CDWAPAPP_EVT_OPEN_DOWNLOAD_DIR			(CLSID_CDWAPAPP << 16 | 14)
#define CDWAPAPP_EVT_VIEW_PAGE_IMAGE			(CLSID_CDWAPAPP << 16 | 15)
#define CDWAPAPP_EVT_SAVE_MARK_PAGE				(CLSID_CDWAPAPP << 16 | 16)
#define CDWAPAPP_EVT_EXIT_EXPLORER				(CLSID_CDWAPAPP << 16 | 17)
#define CDWAPAPP_EVT_CHANGE_SETTING				(CLSID_CDWAPAPP << 16 | 18)
#define CDWAPAPP_EVT_LIST_FILES				    (CLSID_CDWAPAPP << 16 | 19)
#define CDWAPAPP_EVT_CHANGE_DIR				    (CLSID_CDWAPAPP << 16 | 20)
#define CDWAPAPP_EVT_MOVE_FILES				    (CLSID_CDWAPAPP << 16 | 21)
#define CDWAPAPP_EVT_MARKMODE				    (CLSID_CDWAPAPP << 16 | 22)
#define CDWAPAPP_EVT_OPT_TO_OPER				(CLSID_CDWAPAPP << 16 | 23)
#define CDWAPAPP_EVT_SETTINGS_TO_RADIO			(CLSID_CDWAPAPP << 16 | 24)
#define CDWAPAPP_EVT_SETTINGS_TO_INPUTHOMEPAGE	(CLSID_CDWAPAPP << 16 | 25)
#define CDWAPAPP_EVT_RADIO_TO_SETTINGS			(CLSID_CDWAPAPP << 16 | 26)
#define CDWAPAPP_EVT_INPUTHMPG_TO_SETTINGS		(CLSID_CDWAPAPP << 16 | 27)
#define CDWAPAPP_EVT_GET_SAVE_PATH				(CLSID_CDWAPAPP << 16 | 28)
#define CDWAPAPP_EVT_RE_ENTER_EXPLORER			(CLSID_CDWAPAPP << 16 | 29)
#define CDWAPAPP_EVT_EXPLORPAGE_TO_DOWNLOADING	(CLSID_CDWAPAPP << 16 | 30)
#define CDWAPAPP_EVT_BACK_EXPLORER				(CLSID_CDWAPAPP << 16 | 31)
#define CDWAPAPP_EVT_EDIT_CONTENT_DONE			(CLSID_CDWAPAPP << 16 | 32)
#define CDWAPAPP_EVT_SHOW_DUALSIM_MENU			(CLSID_CDWAPAPP << 16 | 33)
#define CDWAPAPP_EVT_OPEN_WAITING_DLG			(CLSID_CDWAPAPP << 16 | 34)
#define CDWAPAPP_EVT_GOTO_SUSPEND				(CLSID_CDWAPAPP << 16 | 35)

/*=============================================================*/
// Data type definition
/*=============================================================*/

// WAP launch mode defination
typedef enum
{
	CDWap_WAP_MODE = 0,
	CDWap_QQ_MODE,					// URL must unicode
	CDWap_OPEN_URL_MODE,			// URL must unicode
	CDWap_SAVE_BOOKMARK_MODE,		// URL must unicode
	CDWap_DOWNLOAD_URL_MODE,		// Download mode for Java
} CDWapMode_e;

typedef struct
{
	boolean			bSelSim;
	boolean			bStorageAssigned; // Download Launcher storage assignment check
	u8				nSim;
	CDWapMode_e		mode;
	MAE_WChar		*pURL;
    CmnAppLaunchRspCbInfo_t tRspInfo;
}tWapStartParm;

typedef enum
{
	CDWAP_OPEN_WEBSITE = 0,

#ifdef __YOUTUBE_MMI_CDWAP__
	CDWAP_OPEN_YOUTUBE,      //open http://m.youtube.com
#endif

#ifdef __YOUKU_MMI_CDWAP__
    CDWAP_OPEN_YOUKU,        //open http://3g.youku.com
#endif

#ifdef __VUCLIP_MMI_CDWAP__
    CDWAP_OPEN_VUCLIP,        //open http://vuclip.com
#endif

#ifdef __VUCLIP_MMI_CDWAP__
    CDWAP_OPEN_BAIDU,        //open http://m.baidu.com/?from=1359a
#endif

} CDWapOpenPortal_e;
#endif

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret CdWapAppNew(MAE_ClsId id, void **ppObj);
void CdWapAppPreNew(void);

#define CDWAP_EVT_QUEUE_SIZE  100


#endif /* __MMI_CDWAPAPP_H__ */
