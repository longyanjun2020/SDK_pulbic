/**
*   Viewport widget is a decorator widget, to provide an area to display an object
*   that may be large. For example, a 1024x1024 picture, usually in a small screen
*   device can not show completely, AP needs to use Viewport widget to view this
*   picture in this time. It is only a part area of picture that Viewport display, and
*   User can use the arrow keys to move the Viewport to show other areas.The
*   default distance of each moving is 10 pixels, AP can modify by setting the
*   property. AP can also set the alignment to let the location of the start Viewport
*   to be in the map left/right/upper/lower/center. AP can even decide whether or
*   not to close the horizontal/vertical movement.
*
*   ex: Viewport widget
*     ------------------------------------
*     |   A large image in               |
*     |  image   ---------------------   |
*     |  widget  |     Viewport      |   |
*     |          |       widget      |   | <-- Viewport widget is the area we can see the image.
*     |          ---------------------   |
*     -----------------------------------
*
*/

#ifndef __MMI_WDG_VIEWPORT_H__
#define __MMI_WDG_VIEWPORT_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_mae_decorator.h"
/*=============================================================*/
// type and define
/*=============================================================*/

/** WdgViewportCfgData_t
*
* @brief    nStep:          Distance (pixels) of each time to move.
*           pDecoratorWdg:  The widget be decorator.
*           eWdgAlignment:  left, right or center alignment; refer to WdgAlignment_e.
*
*/
typedef struct
{
    u16                     nStep;
    IWidget                 *pDecoratorWdg;
    WdgAlignment_e          eWdgAlignment;
}WdgViewportCfgData_t;

/** Animation set
*
* @brief    nStep:          Distance (pixels) of each time to move.
*           pDecoratorWdg:  The widget be decorator.
*           eWdgAlignment:  left, right or center alignment; refer to WdgAlignment_e.
*
*/

typedef void ViewportAnimUserData_t; // user specified animation data
typedef void ViewportAnimStyleData_t; // local style animation data

typedef void (*PfnViewportAnimStartCb)(IWidget *pViewportWdg, void *pUserData);
typedef void (*PfnViewportAnimDoneCb)(IWidget *pViewportWdg, void *pUserData);

// viewport common animation data
typedef struct
{
    Point_t tStartPos;
    Point_t tEndPos;
    Point_t tOffsetMax;
} ViewportAnimCommonData_t;

// viewport init animation data
typedef struct
{
    PfnViewportAnimStartCb pfnAnimStartCb;
    PfnViewportAnimDoneCb pfnAnimDoneCb;
} ViewportAnimInitData_t;

typedef ViewportAnimStyleData_t *(*PfnViewportAnimCreate)(IWidget *pViewportWdg, ViewportAnimInitData_t *AnimInitData, ViewportAnimUserData_t *pAnimUserData);
typedef MAE_Ret (*PfnViewportAnimSet)(ViewportAnimStyleData_t *pAnimData, ViewportAnimCommonData_t *pAnimCommonData);
typedef MAE_Ret (*PfnViewportAnimStart)(ViewportAnimStyleData_t *pAnimData);
typedef MAE_Ret (*PfnViewportAnimStop)(ViewportAnimStyleData_t *pAnimData);
typedef MAE_Ret (*PfnViewportAnimDestroy)(ViewportAnimStyleData_t *pAnimData);

typedef struct
{
    PfnViewportAnimCreate pfnAnimCreate;
    PfnViewportAnimSet pfnAnimSet;
    PfnViewportAnimStart pfnAnimStart;
    PfnViewportAnimStop pfnAnimStop;
    PfnViewportAnimDestroy pfnAnimDestroy;
} ViewportAnimCb_t;

// api used
typedef struct
{
    ViewportAnimUserData_t *pAnimUserData;
    ViewportAnimCb_t tAnimCb;
} ViewportAnimParam_t;

typedef enum
{
    VIEWPORT_LOCKMOVE_KEYPRESS,
    VIEWPORT_LOCKMOVE_TOUCH,
    VIEWPORT_LOCKMOVE_NUM
} ViewportLockMove_e;

typedef struct
{
    ViewportLockMove_e eLockMoveType;
    boolean bLock;
} ViewportLockMoveParam_t;

/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgViewportScrollChange
* @brief      CB register by "WdgViewportRegisterScrollChangeCb"
*             and will be trigger when touch move viewport or WdgViewportSetScrollData.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pScrollData       Info of scroll when viewport change
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgViewportScrollChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollData_t *pScrollData, IWidget *pIWidget);

/** PfnWdgViewportScrollStepChange
* @brief      CB register by "WdgViewportRegisterScrollStepChangeCb"
*             and will be trigger when viewport changed by pressed hotkey.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pScrollStep       Info of scroll when viewport change by step
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgViewportScrollStepChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollStep_t *pScrollStep, IWidget *pIWidget);

typedef void (*PfnWdgViewportScrollStart) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);

typedef void (*PfnWdgViewportScrollFinished) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);

/*=============================================================*/
//Common Function

/** WdgViewportCreateForWnd
* @brief        Viewport widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    pData               Widget Common Data, refer to WdgViewportCfgData_t.
*                                   If set pSize = NULL : means you want Default Value;
*
* @retval       The pointer of Viewport             Success.
* @retval       NULL                                Failed.
*
*/
IWidget* WdgViewportCreateForWnd
(
    HWIN                     hWin,
    Pos_t                          *pPos,
    WidgetSize_t                    *pSize,
    u16                             nWidgetID,
    WdgViewportCfgData_t            *pData
);
/*=============================================================*/
/** WdgViewportCreate
* @brief        Create Viewport widget
*
* @retval       The pointer of Viewport     Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgViewportCreate
(
    void
);

/** WdgViewportSetPanStep
* @brief         Set Viewport widget's pixels per moving
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     nStep             The pixels per moving which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetPanStep
(
    IWidget                 *pWDGViewport,
    u16                     nStep
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_PANSTEP, (u32)nStep);
}

/** WdgViewportSetCurrentXOffset
* @brief         Set Viewport widget's current X offset
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     nCurrentXOffset   The current X offset which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetCurrentXOffset
(
    IWidget                 *pWDGViewport,
    s32                     nCurrentXOffset
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_XOFFSET, (u32)nCurrentXOffset);
}

/** WdgViewportSetCurrentYOffset
* @brief         Set Viewport widget's current Y offset
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     nCurrentYOffset   The current Y offset which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetCurrentYOffset
(
 IWidget                 *pWDGViewport,
 s32                     nCurrentYOffset
 )
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_YOFFSET, (u32)nCurrentYOffset);
}

__INLINE MAE_Ret WdgViewportReset
(
 IWidget                 *pWDGViewport
 )
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_RESET, (u32)0);
}

/** WdgViewportSetKeepCenter
* @brief         Set Viewport widget to keep in center
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     bKeepCenter       The keep center status which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetKeepCenter
(
    IWidget                 *pWDGViewport,
    boolean                 bKeepCenter
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_KEEP_CENTER, (u32)bKeepCenter);
}

/** WdgViewportSetLockHorzMoveEx
* @brief         Set Viewport widget to lock horizontal move by HardKey or Touch 
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     eLockMoveType     Lock Keypress or Touch
* @param[in]     bLock             The lock horizontal move status which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetLockHorzMoveEx
(
 IWidget                 *pWDGViewport,
 ViewportLockMove_e      eLockMoveType,
 boolean                 bLock
 )
{
    ViewportLockMoveParam_t tLockMoveParam;

    tLockMoveParam.eLockMoveType = eLockMoveType;
    tLockMoveParam.bLock = bLock;
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_LOCK_HORZ_MOVE_EX, (u32)&tLockMoveParam);
}

/** WdgViewportSetLockVertMoveEx
* @brief         Set Viewport widget to lock vertical move by HardKey or Touch
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     eLockMoveType     Lock Keypress or Touch
* @param[in]     bLock             The lock vertical move status which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetLockVertMoveEx
(
 IWidget                 *pWDGViewport,
 ViewportLockMove_e      eLockMoveType,
 boolean                 bLock
 )
{
    ViewportLockMoveParam_t tLockMoveParam;

    tLockMoveParam.eLockMoveType = eLockMoveType;
    tLockMoveParam.bLock = bLock;
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_LOCK_VERT_MOVE_EX, (u32)&tLockMoveParam);
}

// the following API is deprecated, keep it for the purpose of compatibility
// use WdgViewportSetLockHorzMoveEx to set Horizontal move status
/** WdgViewportSetLockHoriMove
* @brief         Set Viewport widget to lock horizontal move by HardKey KEY_RIGHT, KEY_LEFT...
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     bLock             The lock horizontal move status which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetLockHoriMove
(
    IWidget                 *pWDGViewport,
    boolean                 bLock
)
{
    return WdgViewportSetLockHorzMoveEx(pWDGViewport, VIEWPORT_LOCKMOVE_KEYPRESS, bLock);
}

// the following API is deprecated, keep it for the purpose of compatibility
// use WdgViewportSetLockVertMoveEx to set Vertical move status
/** WdgViewportSetLockVerMove
* @brief         Set Viewport widget to lock vertical move by HardKey KEY_UP, KEY_DOWN...
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     bLock             The lock vertical move status which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetLockVerMove
(
    IWidget                 *pWDGViewport,
    boolean                 bLock
)
{
    return WdgViewportSetLockVertMoveEx(pWDGViewport, VIEWPORT_LOCKMOVE_KEYPRESS, bLock);
}

/** WdgViewportSetScrollData
* @brief         Set Viewport widget's scroll data; it works only enable scrollbar
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     pScrollData       The widget scroll data which will be set to the viewport widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgViewportSetScrollData
(
    IWidget                 *pWDGViewport,
    ScrollData_t            *pScrollData
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_WDG_SCROLL_DATA, (u32)pScrollData);
}

/** WdgViewportSetEnableVScrollAnim
* @brief         Enable Viewport widget's Vertical Animation;
*
* @param[in]     pWDGViewport        The viewport widget which want to be set
* @param[in]     bEnableVScrollAnim  TRUE : enable animation, FALSE : disable animation
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgViewportSetEnableVScrollAnim
(
    IWidget                 *pWDGViewport,
    boolean					bEnableVScrollAnim
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_ENABLE_V_SCROLL_ANIM, (u32)bEnableVScrollAnim);
}

/** WdgViewportSetEnableHScrollAnim
* @brief         Enable Viewport widget's Horizontal Animation;
*
* @param[in]     pWDGViewport        The viewport widget which want to be set
* @param[in]     bEnableHScrollAnim  TRUE : enable animation, FALSE : disable animation
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgViewportSetEnableHScrollAnim
(
    IWidget                 *pWDGViewport,
    boolean			        bEnableVScrollAnim
 )
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_ENABLE_H_SCROLL_ANIM, (u32)bEnableVScrollAnim);
}

/** WdgViewportSetAnimParam
* @brief         Set Viewport widget's Animation Param, destroy old animation, create new animation
*
* @param[in]     pWDGViewport        The viewport widget which want to be set
* @param[in]     pAnimParam          Animation param, including animation CB and User dat
*
* @retval        MAE_RET_SUCCESS     Success
* @retval        others              Failed
*
*/
__INLINE MAE_Ret WdgViewportSetAnimParam
(
    IWidget                 *pWDGViewport,
    ViewportAnimParam_t     *pAnimParam
 )
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_ANIMATION_PARAM, (u32)pAnimParam);
}

/** WdgViewportStopAnim
* @brief         Stop current Viewport widget's Animation
*
* @param[in]     pWDGViewport        The viewport widget which want to be set
*
* @retval        MAE_RET_SUCCESS     Success
* @retval        others              Failed
*
*/
__INLINE MAE_Ret WdgViewportStopAnim
(
    IWidget                 *pWDGViewport
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_ANIMATION_STOP, 0);
}

/** WdgViewportSetLayoutStyle
* @brief         Set Viewport widget's layout style
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     eWdgLayoutStyle   The widget layout style which will be set to the viewport widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgViewportSetLayoutStyle
(
    IWidget                 *pWDGViewport,
    WdgLayoutStyle_e        eWdgLayoutStyle
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_LAYOUT_STYLE, (u32)eWdgLayoutStyle);
}

/** WdgViewportSetAlignment
* @brief         Set Viewport widget's alignment flag
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     eWdgAlignment     The widget alignment flag which will be set to the viewport widget
*
* @retval        None
*
*/
__INLINE MAE_Ret WdgViewportSetAlignment
(
    IWidget                 *pWDGViewport,
    WdgAlignment_e          eWdgAlignment
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_WDG_ALIGNMENT, (u32)eWdgAlignment);
}

/** WdgViewportSetViewWidget
* @brief         Set the widget which want to be viewed/displayed by viewport widget
*                To set a widget that size is bigger than region we can use viewport to browse it.
*                Ex, A view of picture is large than cell phone screen.
*                Ex, To decorate image widget with viewport when you want to browse partial of the image.
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     pViewWidget       The widget which want to be viewed/displayed by viewport widget.
*
* @retval        None.
*
*/
void WdgViewportSetViewWidget
(
    IWidget                 *pWDGViewport,
    IWidget                 *pViewWidget
 );

/** WdgViewportSetEnableHookPoint
* @brief         Enable Viewport widget's hook point ability, default is enabled
*
* @param[in]     pWDGViewport        The viewport widget which want to be set
* @param[in]     bEnableHookPoint   TRUE : enable hook point, FALSE : disable hook point
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgViewportSetEnableHookPoint
(
 IWidget                 *pWDGViewport,
 boolean			     bEnableHookPoint
 )
{
#ifdef __TOUCH_SCREEN_MMI__
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_ENABLE_HOOK_POINT, (u32)bEnableHookPoint);
#else
    return MAE_RET_NOT_SUPPORTED;
#endif
}

/** WdgViewportGetPanStep
* @brief         Get Viewport widget's pixels per moving
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @retval        Step              The pixels per moving which will be gotten from the viewport widget
*
*/
u16 WdgViewportGetPanStep
(
    IWidget                 *pWDGViewport
);

/** WdgViewportGetCurrentXOffset
* @brief         Get Viewport widget's current X offset
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @retval        CurrentXOffset    The current X offset which will be gotten from the viewport widget
*
*/
s32 WdgViewportGetCurrentXOffset
(
    IWidget                 *pWDGViewport
);

/** WdgViewportGetCurrentYOffset
* @brief         Get Viewport widget's current Y offset
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @retval        CurrentYOffset    The current Y offset which will be gotten from the viewport widget
*
*/
s32 WdgViewportGetCurrentYOffset
(
    IWidget                 *pWDGViewport
);

/** WdgViewportGetKeepCenter
* @brief         Get Viewport widget's keep center status
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @retval        KeepCenter        The keep center status which will be gotten from the viewport widget
*
*/
boolean WdgViewportGetKeepCenter
(
    IWidget                 *pWDGViewport
);

// the following API is deprecated, keep it for the purpose of compatibility
// use WdgViewportGetLockHorzMoveEx to get Horizontal move status
/** WdgViewportGetLockHoriMove
* @brief         Get Viewport widget's lock horizontal move status
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @retval        Lock              The lock horizontal move status which will be gotten from the viewport widget
*
*/
boolean WdgViewportGetLockHoriMove
(
    IWidget                 *pWDGViewport
);

// the following API is deprecated, keep it for the purpose of compatibility
// use WdgViewportGetLockVertMoveEx to get Vertical move status
/** WdgViewportGetLockVerMove
* @brief         Get Viewport widget's lock vertical move status
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @retval        Lock              The lock vertical move status which will be gotten from the viewport widget
*
*/
boolean WdgViewportGetLockVerMove
(
    IWidget                 *pWDGViewport
);

/** WdgViewportGetLockHorzMoveEx
* @brief         Get Viewport widget's lock horizontal move status
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
* @param[in]     eLockMoveType     Lock Keypress or Touch
*
* @retval        Lock              The lock horizontal move status which will be gotten from the viewport widget
*
*/
boolean WdgViewportGetLockHorzMoveEx
(
 IWidget                 *pWDGViewport,
 ViewportLockMove_e      eLockMoveType
 );

/** WdgViewportGetLockVertMoveEx
* @brief         Get Viewport widget's lock vertical move status
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
* @param[in]     eLockMoveType     Lock Keypress or Touch
*
* @retval        Lock              The lock vertical move status which will be gotten from the viewport widget
*
*/
boolean WdgViewportGetLockVertMoveEx
(
 IWidget                 *pWDGViewport,
 ViewportLockMove_e      eLockMoveType
 );

/** WdgViewportGetScrollData
* @brief         Get Viewport widget's scroll data; it works only enable scrollbar
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
* @param[out]    pScrollData       The widget scroll data which will be gotten from the viewport widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgViewportGetScrollData
(
    IWidget                 *pWDGViewport,
    ScrollData_t            *pScrollData
)
{
    return WdgCommonGetProperty(pWDGViewport, PROP_WDG_SCROLL_DATA, (u32 *)pScrollData);
}

/** WdgViewportGetAlignment
* @brief         Get Viewport widget's alignment flag
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @return        The widget alignment flag which will be gotten from the viewport widget
*
*/
WdgAlignment_e WdgViewportGetAlignment
(
    IWidget                 *pWDGViewport
);

/** WdgViewportGetViewWidget
* @brief         Get the widget which be viewed/displayed by viewport widget.
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
*
* @retval        pViewWidget       The widget which be viewed/displayed by viewport widget
*
*/
IWidget* WdgViewportGetViewWidget
(
    IWidget                 *pWDGViewport
);

/** WdgViewportGetVertOverBound
* @brief         Get Viewport widget's Vertical Overbound param
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @retval        bVertOverBound    The vertical overbound status which will be gotten from the viewport widget
*
*/
__INLINE boolean WdgViewportGetVertOverBound
(
 IWidget                 *pWDGViewport
)
{
    boolean bVertOverBound;

    WdgCommonGetProperty(pWDGViewport, PROP_VIEWPORT_WDG_VERT_OVER_BOUNDARY, (u32 *)&bVertOverBound);

    return bVertOverBound;
}

/** WdgViewportGetHorzOverBound
* @brief         Get Viewport widget's Horizontal Overbound param
*
* @param[in]     pWDGViewport      The viewport widget which want to be gotten
*
* @retval        bHorzOverBound    The Horizontal overbound status which will be gotten from the viewport widget
*
*/
__INLINE boolean WdgViewportGetHorzOverBound
(
 IWidget                 *pWDGViewport
 )
{
    boolean bHorzOverBound;

    WdgCommonGetProperty(pWDGViewport, PROP_VIEWPORT_WDG_HORZ_OVER_BOUNDARY, (u32 *)&bHorzOverBound);

    return bHorzOverBound;
}

/** WdgViewportGetEnableVScrollAnim
* @brief         Get Viewport widget's Vertical Animation is enable or disable
*
* @param[in]     pWDGViewport        The viewport widget which want to be set
*
* @retval        bVScrollAnim        TURE : Vertical Animation is enable, FALSE : disable
*
*/
__INLINE boolean WdgViewportGetEnableVScrollAnim
(
 IWidget                 *pWDGViewport
 )
{
    boolean bVScrollAnim;

    WdgCommonGetProperty(pWDGViewport, PROP_VIEWPORT_ENABLE_V_SCROLL_ANIM, (u32 *)&bVScrollAnim);

    return !bVScrollAnim;
}

/** WdgViewportGetEnableHScrollAnim
* @brief         Get Viewport widget's Horizontal Animation is enable or disable
*
* @param[in]     pWDGViewport        The viewport widget which want to be set
*
* @retval        bHScrollAnim        TURE : Horizontal Animation is enable, FALSE : disable
*
*/
__INLINE boolean WdgViewportGetEnableHScrollAnim
(
 IWidget                 *pWDGViewport
 )
{
    boolean bHScrollAnim;

    WdgCommonGetProperty(pWDGViewport, PROP_VIEWPORT_ENABLE_H_SCROLL_ANIM, (u32 *)&bHScrollAnim);

    return !bHScrollAnim;
}

/** WdgViewportGetEnableHookPoint
* @brief         Get Viewport widget's hook point ability is enable or disable
*
* @param[in]     pWDGViewport        The viewport widget which want to be set
*
* @retval        bHookPoint          TURE : enable hook point, FALSE : disable hook point
*
*/
__INLINE boolean WdgViewportGetEnableHookPoint
(
 IWidget                 *pWDGViewport
 )
{
#ifdef __TOUCH_SCREEN_MMI__
    boolean bHookPoint;

    WdgCommonGetProperty(pWDGViewport, PROP_VIEWPORT_WDG_ENABLE_HOOK_POINT, (u32 *)&bHookPoint);

    return bHookPoint;
#else
    return FALSE;
#endif
}

/** WdgViewportRegisterScrollChangeCb
* @brief         Register callback for handling scroll visible range change;
*                CB will be triggered if scroll visible range changed
*
* @param[in]     pWDGViewport      The viewport widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgViewportRegisterScrollChangeCb
(
    IWidget                     *pWDGViewport,
    PfnWdgViewportScrollChange  pfn,
    void                        *pUserData
);

/** WdgViewportRegisterScrollStepChangeCb
* @brief         Register callback for handling the scroll step change;
*                CB will be triggered if scroll step changed
*
* @param[in]     pWDGViewport      The viewport widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgViewportRegisterScrollStepChangeCb
(
    IWidget                         *pWDGViewport,
    PfnWdgViewportScrollStepChange  pfn,
    void                            *pUserData
);

MAE_Ret WdgViewportRegisterScrollStartCb
(
    IWidget                         *pWDGViewport,
    PfnWdgViewportScrollStart  pfn,
    void                            *pUserData
);

MAE_Ret WdgViewportRegisterScrollFinishedCb
(
    IWidget                         *pWDGViewport,
    PfnWdgViewportScrollFinished  pfn,
    void                            *pUserData
);

/** WdgViewportDeregisterScrollChangeCb
* @brief         Deregister callback for handling scroll visible range change.
*
* @param[in]     pWDGViewport      The viewport widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgViewportDeregisterScrollChangeCb
(
    IWidget                     *pWDGViewport,
    PfnWdgViewportScrollChange  pfn,
    void                        *pUserData
);

/** WdgViewportDeregisterScrollStepChangeCb
* @brief         Deregister callback for handling the scroll step change.
*
* @param[in]     pWDGViewport      The viewport widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgViewportDeregisterScrollStepChangeCb
(
    IWidget                         *pWDGViewport,
    PfnWdgViewportScrollStepChange  pfn,
    void                            *pUserData
);

MAE_Ret WdgViewportDeregisterScrollStartCb
(
    IWidget                         *pWDGViewport,
    PfnWdgViewportScrollStart  pfn,
    void                            *pUserData
);

MAE_Ret WdgViewportDeregisterScrollFinishedCb
(
    IWidget                         *pWDGViewport,
    PfnWdgViewportScrollFinished  pfn,
    void                            *pUserData
);

/** WdgViewportSetEnableTouchChild
* @brief         Set Viewport widget to send touch event to child
*
* @param[in]     pWDGViewport      The viewport widget which want to be set
* @param[in]     bFlag             Enable or disable to send touch event to child
*
* @retval        None
*
*/
#ifdef __TOUCH_SCREEN_MMI__
__INLINE MAE_Ret WdgViewportSetEnableTouchChild
(
    IWidget                 *pWDGViewport,
    boolean                 bFlag
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_WDG_ENABLE_TOUCH_CHILD, (u32)bFlag);
}
// the following APIs are deprecated, keep it for the purpose of compatibility
// use MMI_Common_SetViewportAnim to call View port Android animation
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__
__INLINE MAE_Ret WdgViewportEnableSnapToGrid
(
    IWidget                 *pWDGViewport,
    boolean                 bEnable
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_TOUCH_SNAP_TO_GRID, (u32)bEnable);
}

__INLINE MAE_Ret WdgViewportSetGridYSize
(
    IWidget                 *pWDGViewport,
    u32                     nGridYSize
)
{
    return WdgCommonSetProperty(pWDGViewport, PROP_VIEWPORT_TOUCH_GRID_Y_SIZE, (u32)nGridYSize);
}
//end of deprecated
#endif // __UI_STYLE_MMI_ANDROID_MAIN_MENU__

#endif //__TOUCH_SCREEN_MMI__

#endif /* __MMI_WDG_VIEWPORT_H__ */
