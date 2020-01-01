/**
 * @file    mae_glmenuwidget.h
 * @brief   This file defines the interface of 3D demo widget
 * @version $Id$
 */

#ifndef __MMI_WDG_GLMENUWIDGET_H__
#define __MMI_WDG_GLMENUWIDGET_H__

#include "mmi_mae_window.h"
#include "mmi_mae_graphic_forward.h" //for Pos_t
#include "mmi_mae_widget.h" //for WidgetSize_t

enum
{
    //For GLGridWidget widget properties
    PROP_GLMENU_WDG_PLAY_START_ANIMATION = 0,
    PROP_GLMENU_WDG_MESSAGE_NUMBER,
    PROP_GLMENU_WDG_MISSCALL_NUMBER,
    PROP_GLMENU_WDG_KEY_INPUT,
	PROP_GLMENU_WDG_FOCUS_CHANGE,
	PROP_GLMENU_WDG_FOCUS_ANIM_PAUSE,
	PROP_GLMENU_WDG_FOCUS_ANIM_RESUME,
	PROP_GLMENU_WDG_SWITCH_TRAN_CHANGE,
	PROP_GLMENU_WDG_CUBE_START_PAGE,
	PROP_GLMENU_WDG_SHOW_BG_MODE,
};

enum
{
    GlMenuWidget_NotifyEvent_Begin = 0,
	GlMenuWidget_NotifyEvent_LaunchAppBefore,
    GlMenuWidget_NotifyEvent_LaunchApp,
	GlMenuWidget_NotifyEvent_LastFrameBeforeLaunchApp,
};
typedef u16 GlMenuWidget_NotifyEvent_e;


IWidget* WdgGlMenuCreate(void);
IWidget* WdgGlMenuCreateForWnd(HWIN hWin,Pos_t *pPos,WidgetSize_t *pSize,u16 nWidgetID);

#endif /* __MAE_GLMENUWIDGET_H__ */
