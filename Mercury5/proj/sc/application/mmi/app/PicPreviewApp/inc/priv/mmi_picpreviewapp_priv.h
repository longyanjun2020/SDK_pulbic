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
* @file    mmi_picpreviewapp_priv.h
* @version
* @brief   picpreviewapp applet private header file
*
*/

#ifndef __MMI_PICPREVIEWAPP_PRIV_H__
#define __MMI_PICPREVIEWAPP_PRIV_H__


/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_base_util.h"
#include "mmi_layout.h"
#include "mmi_picpreviewapp.h"
#include "mmi_picpreviewapp_id.h"
#include "mmi_picpreviewapp_rs.h"
#include "mmi_log.h"
#include "mmi_wdg_wallpaper.h"
#include "PicPreviewApp_resource.h"

#include "mmi_launcher_picpreviewapp.h"
#include "mmi_launcher_common.h"
#include "mmi_launcher_phb.h"
#include "mmi_launcher_cc.h"
#include "mmi_launcher_em.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_security.h"
#include "mmi_launcher_ussd.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define PICPREVIEW_NO_ITEM_BG_IMAGE_WIDTH 100
#define PICPREVIEW_NO_ITEM_BG_IMAGE_HEIGHT 40
#define PICPREVIEW_LOADING_IMAGE_WIDTH 36
#define PICPREVIEW_LOADING_IMAGE_HEIGHT 36
#define PICPREVIEW_LOADING_TIMER 50
/*=============================================================*/
// Data type definition
/*=============================================================*/


/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;

	u8 nCurFocusIdx;
	u32 nFileNum;
	boolean bIsPlayAnim;
    boolean bCloseAfterResume;
	PicPreviewWndMode aActiveMode;
	PhotoSlideType_e slideType ;
} PicPreviewAppData_t;


typedef struct
{
	IWidget *pBGWidget;
	IWidget *pGlWidget;
	IWidget *pBtnBGWidget;
	IWidget *pGridWidget;
	IWidget *pCAMWidget;
	IWidget *pSlideShowWidget;
	IWidget *pBackWidget;
	IWidget *pInfoTextWidget;
	IWidget *pInfoImgWidget;
    IWidget *ploadImgWidget;
  	IWidget *pFadoutBgImgWidget;
      	IWidget *pFileNameTextWidget;
      	IWidget *pFileNumTextWidget;
} PicPreviewAppWdgList_t;

typedef struct
{
    PicPreviewAppWdgList_t tWdgList;
} PicPreviewAppWndData_t;


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret PicPreviewConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret PicPreviewDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicPreviewStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicPreviewKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PicPreviewResumeCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean PicPreviewSuspendCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
MAE_Ret PicPreviewAppWndHdlMain(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PicPreviewAppWndHdlMainCreate(void* pCusHandle,void* pWndData, u32 nWndInitParam);
static MAE_Ret _PicPreviewAppWndHdlMainDestroy(void* pCusHandle,void* pWndData, u32 nWndInitParam);

#if defined(__3D_UI_IDLE_MULTIPAGE__)
boolean PicPreviewTSCmdCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif //__3D_UI_IDLE_MULTIPAGE__

#endif /* __MMI_MGLDEMOAPP_PRIV_H__ */
