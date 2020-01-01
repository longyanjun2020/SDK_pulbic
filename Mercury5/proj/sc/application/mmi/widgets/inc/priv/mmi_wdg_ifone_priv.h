/**
* @file    mmi_wdg_ifone_priv.h
* @version $Id: mmi_wdg_ifone_priv.h 2009-09-01 ken.zhou $
* @brief   This is the private header file for mmi_wdg_ifone.c
*/
#ifndef MMI_WDG_IFONE_PRIV_H
#define MMI_WDG_IFONE_PRIV_H

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_abscontainer.h"
#include "mmi_wdg_abscontainer_priv.h"
#include "mmi_wdg_image.h"
#include "mmi_wdg_text.h"
#include "mmi_wdg_snapshot.h"
#include "mmi_layout.h"
#include "mmi_mae_touchsrv.h"
#include "mmi_wdg_ifone.h"
#include "mmi_mae_clock.h"
#include "mmi_mae_clock_types.h"
#include "mmi_evtcentersrv.h"
/*=============================================================*/
// type and define
/*=============================================================*/

#define IFONEWDG_SETDRAGMODE_TIMER 1
#define IFONEWDG_SETDRAGMODE_PHASE	1
#define IFONEWDG_TRANS_COLOR_RGB16 0x83F0
#define IFONEWDG_FLODER_ICONMENU_ROWNUM 3
#define IFONEWDG_FLODER_ICONMENU_COLNUM 3
#define IFONEWIDGET_RGB16TO24(nTransColor_16)  ((((nTransColor_16) & 0xF800) << 8) +(((nTransColor_16) & 0x7E0) << 5) +(((nTransColor_16) & 0x1F) << 3))
#define IFONEWDG_ANIM_MOVE_PIXEL 3

///structure for a ImageText
typedef struct {
    AbsContainerBase_t AbsCntrBase;

    IWidget * pImageWdg;
    IWidget * pTextWdg;
    IWidget * pSnapshotTextWdg;
    IWidget * pITopImageWdg;
    IWidget * pIMissEvtTextWdg;
    IWidget * pIContainer;
    IWidget * pIWeekDayWdg;
    IWidget * pIMonthDayWdg;
    IWidget * pIFolderGridMenu;
    IWidget * pIShadowImgWdg;

    IModel *	pITextModel;
    IVectorModel * pIChildWdgModel;
    IImage *	pIMainImage;
    IBitmap *	pFocusImage;
    IBitmap *	pDragImage;
    IBitmap* pIOrigBmp;
    IBitmap* pLeftBmp;
    IBitmap* pRightBmp;
    IEVTCENTERSRV* pIEvtCenterSrv;
    IClock* pIClock;
	u32 nMissEvtCount;
    ClockListener_t     ClockLsn;
    ModelListener_t    pIChildWdgMdlListener;

    IFONEWDG_ANIMSTYLE_e eAnimstyle;
    IFONEWDG_ANIM_DIRECTION_e	eCurrentAnimDir;
    IFONEWDG_DESPLAY_STYLE_e	eCurrentStyle;

    IfoneMenuItemData_p pIfoneMenuData;
    s8	nSetDragModePhase;
    boolean bAinamation:1;
    boolean bShowText :1;
    boolean bDragTimerActive:1;
    boolean bDisableAnim:1;
    boolean bShowShadow:1;
} _IFoneWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/
MAE_Ret IFoneWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean IFoneWidget_HandleEvent(IAbsContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);
static boolean _IFoneWdg_SetProperty(_IFoneWdg_t *pThis, u32 P1, u32 P2);
static boolean _IFoneWdg_GetProperty(_IFoneWdg_t *pThis, u32 P1, u32 P2);
static void _IFoneWdg_SetAnimation(_IFoneWdg_t *pThis, boolean bEnableAnim, IFONEWDG_ANIMSTYLE_e eAnimstyle);
static void _IFoneWdg_ModelChanged(_IFoneWdg_t *pThis,ModelEvent_t *pEvent);
static void _IFoneWidget_SetData(_IFoneWdg_t *pWdg, IfoneMenuItemData_p pMenuData);
static void _IFoneWidget_UpdateMissEvtCount(_IFoneWdg_t *pWdg);
static boolean _IfoneWidget_AddChildWdg(_IFoneWdg_t *pWdg, IWidget *pChildWdg);
static void IFoneWdg_SetDragMode(_IFoneWdg_t *pThis, boolean bDragMode);
static void IFoneWdg_SetDragMode_TimerCB(void* pUser);
static IBitmap * _IFoneWidget_RotateBitmap(_IFoneWdg_t *pThis,IBitmap * pISrcBitmap, IFONEWDG_ANIM_DIRECTION_e eAnimation);
static IBitmap* _IFoneWidget_GetFocusImage(_IFoneWdg_t *pThis);
static void  _IFoneWidget_GetDragImage(_IFoneWdg_t *pThis);
static void _IFoneWidget_GetAnimationBmp(_IFoneWdg_t *pThis);
static void _IFoneWidget_GetOriginalImage(_IFoneWdg_t *pThis);
static void _IfoneWidget_ClockLsn(void *pUsrData, MAEClkItemId_t id, void *pItemData);
static void _IfoneWidget_UpdateDate( _IFoneWdg_t *pThis);
static void _IFoneWidget_ChildModelListener(void *pUsrData, ListModelEvent_t *pVectorMdlEvent);
static void _IFoneWidget_ChildMenuWidgetFree (u32 u32UserData);
static IBitmap* _IFoneWidget_GetShadowBmp(_IFoneWdg_t *pThis);
static void _IFoneWidget_CFGSrvListener(void *pUserData, ModelEvent_t *pMdlEvt);
static IBitmap* _IFoneWidget_GetWidgetRawData(IWidget* WidgetPtr, IBase* pThis, boolean bSetAlpha);

#endif //MMI_WDG_IFONE_PRIV_H
/*=============================================================*/
// end of file
