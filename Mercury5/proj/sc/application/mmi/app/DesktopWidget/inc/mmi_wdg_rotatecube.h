/**
 * @file    mmi_wdg_rotatecube.h
 * @brief   This file defines the interface of rotatecube widget
 * @version $Id: mmi_wdg_rotatecube.h $
 */
 
#ifndef __MMI_WDG_ROTATECUBE_H__
#define __MMI_WDG_ROTATECUBE_H__

#ifdef __3D_UI_IDLE_SIMPLE__

/*=============================================================*/
// include
/*=============================================================*/

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_interfacemodel.h"
#include "mmi_mae_window.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum
{
    ROTATECUBE_WDG_ANIM_NONE,
    ROTATECUBE_WDG_ANIM_FADEOUT,
    ROTATECUBE_WDG_ANIM_FADEIN,
    ROTATECUBE_WDG_ANIM_FLIPNEXT,
    ROTATECUBE_WDG_ANIM_FLIPPRE,
}RotateCubeWdg_Anim_Phase_e;

enum
{
    ROTATECUBE_FLIPWDG_DTIME,
    ROTATECUBE_FLIPWDG_ACLOCK,
    ROTATECUBE_FLIPWDG_CALENDAR,
    ROTATECUBE_FLIPWDG_TOTAL,    
};
typedef u8 RotateCubeFlipWdg_e;

typedef void (*PfnRotateCubeWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/////////////////////////////////////////////////////////////

MAE_Ret WdgRotateCubeRegisterEventCb
(
    IWidget                         *pRotateCubeWdg,
    PfnRotateCubeWdgCallBack         pfn,
    void                            *pUserData
);

MAE_Ret WdgRotateCubeDeregisterEventCb
(
    IWidget                         *pRotateCubeWdg,
    PfnRotateCubeWdgCallBack         pfn,
    void                            *pUserData
);

IWidget* WdgRotateCubeCntCreate
(
    void
);

IWidget* WdgRotateCubeCntCreateForWnd
(
    HWIN                hWin,
    Pos_t               *pPos,
    WidgetSize_t        *pSize,
    u16                 nWidgetID
);

#endif  //__3D_UI_IDLE_SIMPLE__
#endif /* __MMI_WDG_ROTATECUBE_H__ */
/*=============================================================*/
// end of file
