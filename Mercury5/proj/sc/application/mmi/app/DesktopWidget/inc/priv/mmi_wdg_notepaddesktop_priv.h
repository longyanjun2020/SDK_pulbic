/**
 * @file    mmi_wdg_notepaddesktop_priv.h
 * @brief   The internal structure of the notepad desktopwidget

 */

#ifndef __MMI_WDG_NOTEPADDESKTOP_PRIV_H__
#define __MMI_WDG_NOTEPADDESKTOP_PRIV_H__

#if defined(__3D_UI_IDLE_MULTIPAGE__) && defined(__APP_MMI_NOTEPAD__)

/*=============================================================*/
// include
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mae_glwidget_common.h"
#include "mae_glflipeffectwidget.h"
#include "mgl_Effect_BezierSurface.h"
#include "mmi_wdg_desktop.h"
#include "mmi_settingapp.h"
#include "mmi_common_util.h"
#include "mmi_common_cfg.h"
#include "rs_layout_id.h"
#include "mmi_wdg_notepaddesktop.h"
#include "mmi_coresrv.h"

#include "mmi_srv_phb.h"
#include "mmi_sssrv.h"
#include "mmi_srv_sim.h"
#include "mmi_srv_cc.h"
#include "mmi_srv_cfg.h"
#include "mmi_ccsrv_def.h"

#include "mmi_notepadapp_priv.h"

/*************************************************************************/
/*   For Definition                                                      */
/*************************************************************************/
/*************************************************************************/
/*   For Enumeration                                                     */
/*************************************************************************/

/*************************************************************************/
/*   For Structure                                                       */
/*************************************************************************/

typedef struct
{
    IWidget *pBgImgWdg;
    IWidget *pContentTextWdg;
    IWidget *pDelButtonWdg;
    IWidget *pFlipWdg;
    IWidget *pUpImgWidget;
    IWidget *pDownImgWidget;
} WdgList_t;

typedef struct
{
    DECLARE_BASECLASS_DESKTOPWIDGET
    WdgList_t tWdgList;
    Mmi_NotepadIdxTblBuf_t *pIdxTblBuf;
    u8 nNoteIdx;
    boolean bAnimationStart;
    boolean bNoData;
} NotepadDesktopWdg_t;

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
static MAE_Ret NotepadDesktopWidget_Ctor(NotepadDesktopWdg_t*);
static void NotepadDesktopWidget_Dtor(NotepadDesktopWdg_t*);

static boolean NotepadDesktopWidget_DefHandleEvent(IAbsContainer*, MAEEvent_t, u32, u32);
static boolean NotepadDesktopWidget_SetProperty(NotepadDesktopWdg_t*, u32, u32);
static boolean NotepadDesktopWidget_GetProperty(NotepadDesktopWdg_t*, u32, u32);


#endif //__3D_UI_IDLE_MULTIPAGE__ && __APP_MMI_NOTEPAD__
#endif //__MMI_WDG_NOTEPADDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
