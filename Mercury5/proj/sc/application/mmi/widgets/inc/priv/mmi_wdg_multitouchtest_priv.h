/**
* @file mmi_wdg_multitouchtest_priv.h
*/
#ifndef __MMI_WDG_MULTITOUCHTEST_PRIV_H__
#define __MMI_WDG_MULTITOUCHTEST_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#ifdef __MULTI_TOUCH__
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"

#include "mmi_wdg_multitouchtest.h"
#include "mae_widget_common.h"

#include "mmi_mae_touchsrv_types.h"
#include "mae_abscontainerbase.h"
#include "mmi_base_util.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
    s32 PosX;
    s32 PosY;
    u8 nPointId;
    boolean bValid;
} MultiTouchWdgPoint_t;

typedef struct
{
    IWidget *pWidget;
    Rect_t tRect;
} MultiTouchWdgHookWdg_t;

#define MULTITOUCHTEST_DEMO_NUM 3
typedef struct
{
    Rect_t tRect;
    RGBColor_t tColor;
    u32 nFingerNum;
    u8 aPointId[MAE_TS_MAX_TOUCH];
    Point_t aPoint[MAE_TS_MAX_TOUCH];
    s32 nAngle;
    Rect_t tRotateRect;
    IBitmap *pBitmap;
    boolean bChanged;
} MultiTouchTestWdgDemo_t;

#define MULTITOUCHTEST_EM_NUM 2
typedef struct
{
    IWidget *pButtonWdg;
    WidgetHandler_t tButtonWdgHandler;
    Rect_t tRect;
    u32 nFingerNum;
    u8 aPointId[MAE_TS_MAX_TOUCH];
    Point_t aPoint[MAE_TS_MAX_TOUCH];
    boolean aHook[MAE_TS_MAX_TOUCH];
    boolean aPress[MAE_TS_MAX_TOUCH];
} MultiTouchTestWdgEm_t;

typedef struct
{
    u32 nTestIndex;
    IWidget *pButtonWdg1;
    IWidget *pButtonWdg2;
#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
    IWidget *pCutWdg1;
    IWidget *pCutWdg2;
#endif
    boolean bTimer;
    WidgetHandler_t tButtonWdg1Handler;
    WidgetHandler_t tButtonWdg2Handler;
#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
    WidgetHandler_t tCutWdg1Handler;
    WidgetHandler_t tCutWdg2Handler;
#endif
} MultiTouchTestCaseWdg;

typedef struct 
{
    AbsContainerBase_t  AbsCntrBase;
    ITouchSrv *pITouchSrv;
    IWidget *pFingerTextWdg;
    IWidget *pInfoTextWdg;
    IWidget *pExtraTextWdg;
    IWidget *pEmTextWdg;
    u32 nFinger;
    VectorClass_t *pVector;
    MultiTouchWdgPoint_t tPoint[MAE_TS_MAX_TOUCH];
    /// test case
    MultiTouchTestCaseWdg tCase;
    MultiTouchTestWdgDemo_t tDemo[MULTITOUCHTEST_DEMO_NUM];
    MultiTouchTestEmType_e eEmType;
    MultiTouchTestWdgEm_t tEm[MULTITOUCHTEST_EM_NUM];
    MultiTouchTestType_e eType;
} MultiTouchTestWidget_t;

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret MultiTouchTestWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean MultiTouchTestWidget_DefHandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/

#endif //__MULTI_TOUCH__
#endif //__MMI_WDG_MULTITOUCHTEST_PRIV_H__
/*=============================================================*/
// end of file
