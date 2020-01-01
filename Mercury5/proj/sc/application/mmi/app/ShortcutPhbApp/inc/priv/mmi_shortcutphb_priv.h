////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file		mmi_shortcutphb_priv.h
* @version
* @brief	Shortcut phone book private header file
*
*/

#ifndef __MMI_SHORTCUTPHB_PRIV_H__
#define __MMI_SHORTCUTPHB_PRIV_H__

#if defined(__3D_UI_IDLE_MULTIPAGE__)
/*=============================================================*/
// Include files
/*=============================================================*/

#include "mae_glwidget_common.h"
#include "mmi_baseapplet.h"
#include "mmi_common_rai_id.h"
#include "mmi_phbapp.h"
#include "mmi_phbsrv.h"
#include "mmi_shortcutphb.h"
#include "mmi_shortcutphb_rs.h"
#include "shortcutphbapp_resource.h"
#include "idleapp_resource.h"
#include "mmi_wdg_3dloader.h"
#include "mmi_common_dialog.h"

#include "mmi_launcher_common.h"
#include "mmi_launcher_phb.h"
#include "mmi_launcher_cc.h"
#include "mmi_launcher_em.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_security.h"
#include "mmi_launcher_ussd.h"
#include "mgl_Scene_Environment.h"

/*=============================================================*/
// Enumeration
/*=============================================================*/

enum
{
    SHORTCUTPHB_CALL_TYPE_EMERGENCYCALL = 0,
    SHORTCUTPHB_CALL_TYPE_NORMALCALL,
#ifdef __IP_CALL_MMI__
    SHORTCUTPHB_CALL_TYPE_IPCALL,
#endif
    SHORTCUTPHB_CALL_TYPE_MAX_NUM
};
typedef u8 ShortcutPhbCallType_e;

enum
{
    SHORTCUTPHB_MSG_TYPE_SMS = 0,
    SHORTCUTPHB_MSG_TYPE_MMS,
    SHORTCUTPHB_MSG_TYPE_MAX_NUM
};
typedef u8 ShortcutPhbMsgType_e;

enum
{
    SHORTCUTPHB_CREATE_APP_FIRST = 0,
    SHORTCUTPHB_CREATE_APP_FROM_RESUME,
    SHORTCUTPHB_CREATE_APP_DONE,
    SHORTCUTPHB_CREATE_APP_MAX_NUM
};
typedef u8 ShortcutPhbCreateType_e;

enum
{
    SHORTCUTPHB_SPIN_STATUS_EMPTY = 0,
    SHORTCUTPHB_SPIN_STATUS_STARTANI,
    SHORTCUTPHB_SPIN_STATUS_LAYDOWN,
    SHORTCUTPHB_SPIN_STATUS_ROTATE,
    SHORTCUTPHB_SPIN_STATUS_CLOCKWISE_ROTATE_EXT,    
    SHORTCUTPHB_SPIN_STATUS_COUNTERCLOCKWISE_ROTATE_EXT,    
    SHORTCUTPHB_SPIN_STATUS_STANDUP,
    SHORTCUTPHB_SPIN_STATUS_END
};
typedef u8 ShortcutPhbSpinStatus_e;

/*=============================================================*/
// Application structure
/*=============================================================*/

typedef struct
{
	APPLET_BASE_ELEMENTS;

    boolean                                 bAnimEnd;
    boolean                                 bUserPress;
    boolean                                 bAddBtnPress;    
    u16                                     nCurrentFrame;
    u32                                     nPreIdx;    
    u32                                     nSelectedIdx;
    s32                                     nSpinNum;
    u8                                      nItemObjId[SHORTCUT_PHB_ITEM_MAX_NUM];    
    u16                                     nTsPressYPos;
    u8                                      nUnderDecodingNum;
    IVectorModel                            *pDecodingQueue;
    ShortcutPhbCreateType_e                 eCreateType;
    IBitmap                                 *pEmptyItemPtr;  
    IBitmap                                 *pEmpty1stItemPtr;      
    MmiShortcutPhbData_t	                *tPhbData;
	MmiPhbContactContent_t 	                *tPhbContact;  
	IPHBSRV 				                *pPhbSrv;    
}ShortcutPhbAppData_t;

typedef struct
{
    IWidget     *pBgImgWdg;
    IWidget     *pStatusBarImgWdg;    
    IWidget     *pCallBtnWdg;        
    IWidget     *pDelBtnWdg;        
    IWidget     *pSendBtnWdg;        
    IWidget     *pBackBtnWdg;                
    IWidget     *p3DLoaderWdg;
    //For capturing item bitmap
    IWidget     *pItemAbsCntr;
    IWidget     *pItemBgImg;
    IWidget     *pItemPreImg;
    IWidget     *pItemUpperText;
    IWidget     *pItemLowerText;    
}ShortcutPhbMainWdgList_t;


typedef struct
{
    ShortcutPhbSpinStatus_e                 eSpinStatus;
    IImage                                  *pItemImg[SHORTCUT_PHB_ITEM_MAX_NUM];   
    ShortcutPhbMainWdgList_t                tScPhbMainWdgList;
}ShortcutPhbMainWndData_t;


/*=============================================================*/
// Function definition
/*=============================================================*/
//Window event handler
MAE_Ret _ShortcutPhbConstructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);
MAE_Ret _ShortcutPhbDestructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);
boolean _ShortcutPhbStartCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _ShortcutPhbSuspendCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _ShortcutPhbResumeCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _ShortcutPhbStopCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _ShortcutPhbTSPressCB(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean _ShortcutPhbTSReleaseCB(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean _ShortcutPhbTSMoveCB(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean _ShortcutPhbKeyPressCB(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
//Window listener
MAE_Ret ShortcutPhbMainWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#endif
#endif /* __MMI_SHORTCUTPHB_PRIV_H__ */
