/**
 * @file    mae_gltransformwidget.h
 * @brief   This file defines the interface of 3D transforms for 2D widget
 *<Class Description>
 *   =
 *<Class ID>
 *    CLSID_GLTRANSFORMWIDGET.
 *
 *<Supported Interface>
 *    IWidget, IDecorator
 *
 *<Events Handle> The widget handles following events:
 *<pre>
 *    =======================
 *    EVT_WIDGET_SET_PROPERTY:    The widget handles this event by attempting to set the following properties.
 *        -----------------------
 *        PROP_GLTRANSFORM_WDG_TRANSFORM_TYPE_ID
 *        PROP_GLTRANSFORM_WDG_FRAME_INDEX
 *        PROP_GLTRANSFORM_WDG_FRAME_CNT
 *        PROP_GLTRANSFORM_WDG_TRANSFORM_STATE
 *        -----------------------
 
 *</pre>
 *
 *<View Model Event>
 *<pre>
 *    =======================
 *</pre>
 *
 *<Supported Model>
 *
 *<Model Data>
 * 
 **/


#ifndef __MMI_WDG_GLTRANSFORMWIDGET_H__
#define __MMI_WDG_GLTRANSFORMWIDGET_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_interfacemodel.h"
#include "mmi_wdg_common_interface.h"

typedef enum
{
	GLTRANSFORM_ROTATE_UP,
	GLTRANSFORM_ROTATE_DOWN,
	GLTRANSFORM_FADE_IN,
	GLTRANSFORM_FADE_OUT,
	GLTRANSFORM_SLIDE_UP,
	GLTRANSFORM_SLIDE_DOWN,
	GLTRANSFORM_ROTATE_LEFT_FROM_DEGREE_0,	
	GLTRANSFORM_ROTATE_LEFT_FROM_DEGREE_90,	
    GLTRANSFORM_ROTATE_RIGHT_FROM_DEGREE_0,
    GLTRANSFORM_ROTATE_RIGHT_FROM_DEGREE_90,      
	GLTRANSFORM_ROTATE_NONE,	
}GLTRANSFORM_TYPE_e;

typedef enum
{
	GLTRANSFORM_STATE_START,
	GLTRANSFORM_STATE_END,
}GLTRANSFORM_STATE_e;


typedef void (*PfnGlTransformWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

IWidget* WdgGlTransformCreate(void);
IWidget* WdgGlTransformCreateForWnd(HWIN hWin, Pos_t *pPos, WidgetSize_t *pSize, u16 nWidgetID);

MAE_Ret WdgGlTransformRegisterEventCb
(
    IWidget                         *pGlFlipEffectWdg,
    PfnGlTransformWdgCallBack       pfn,
    void                            *pUserData
);

MAE_Ret WdgGlTransformDeregisterEventCb
(
    IWidget                         *pGlFlipEffectWdg,
    PfnGlTransformWdgCallBack       pfn,
    void                            *pUserData
);

#endif /* __MMI_WDG_GLTRANSFORMWIDGET_H__ */
