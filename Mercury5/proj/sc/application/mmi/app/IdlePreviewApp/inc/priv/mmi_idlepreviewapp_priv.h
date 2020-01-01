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
* @file    mmi_idlepreviewapp_priv.h
* @version
* @brief   idlepreviewapp applet private header file
*
*/

#ifndef __MMI_IDLEPREVIEWAPP_PRIV_H__
#define __MMI_IDLEPREVIEWAPP_PRIV_H__

#if defined(__FEATURE_MGL__) && defined(__3D_UI_IDLE_MULTIPAGE__)
/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_base_util.h"
#include "mmi_layout.h"
#include "mmi_idlepreviewapp.h"
#include "mmi_idlepreviewapp_id.h"
#include "mmi_idlepreviewapp_rs.h"
#include "mmi_log.h"
#include "mmi_wdg_wallpaper.h"
#include "IdlePreviewApp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/ 


#define IDLE_ANIM_NEXT_FRAME 5
#define IDLE_NUM_OF_PAGE 5
#define IDLE_PER_PAGE_ACTVIE_RANGE MAIN_LCD_WIDTH/IDLE_NUM_OF_PAGE
#define IDLE_ANIM_INDEX_STEP 15
#define IDLE_ANIM_MOVE_START_FRAME 75
#define IDLE_ANIM_MOVE_END_FRAME 95
#define IDLE_CLOSE_APPLET_TIMER 10
#define IDLE_PLAEN_WIDTH 60
/*=============================================================*/
// Data type definition
/*=============================================================*/


/**
 * Application structure
 */
enum
{
	ANIM_FLY_OUT = -1,//DIR_LEFT
	ANIM_DIR_NONE,
	ANIM_FLY_IN = 1,//DIR_RIGHT
	ANIM_DIR_RIGHT,
	ANIM_DIR_LEFT,
	ANIM_DIR_CLICK,
	ANIM_READY
};
typedef s8 AnimDir_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;

	u8 nCurFocusIdx;
	u8 nloaderFocusIdx;
	u32 nFileHandle;
	u32 nFileNum;
	u32 nCurrentFrame;
	AnimDir_t eCureAnim;
	boolean bIsAnim;
	Pos_t  LastPos;
} IdlePreviewAppData_t;


typedef struct
{
	IWidget *pBGWidget; 
	IWidget *pMultiIdlePageWdg; 
} IdlePreviewAppWdgList_t;

typedef struct
{
    IdlePreviewAppWdgList_t tWdgList;
} IdlePreviewAppWndData_t;


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret IdlePreviewConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret IdlePreviewDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean IdlePreviewStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean IdlePreviewKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean IdlePreviewTSEventCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);

boolean IdlePreviewResumeCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdlePreviewSuspendCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);

MAE_Ret IdlePreviewAppWndHdlMain(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _IdlePreviewAppWndHdlMainCreate(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret _IdlePreviewAppWndHdlMainDestroy(void* pCusHandle,void* pWndData, u32 nWndInitParam);


#endif //__FEATURE_MGL__ && __3D_UI_IDLE_MULTIPAGE__
#endif /* __MMI_MGLDEMOAPP_PRIV_H__ */
