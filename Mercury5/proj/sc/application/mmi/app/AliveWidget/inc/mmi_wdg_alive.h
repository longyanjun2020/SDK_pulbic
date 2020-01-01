/**
 * @file    mmi_wdg_alive.h
 * @brief   This file defines the interface of alivewidget.

 */
 
#ifndef __MMI_WDG_ALIVE_H__
#define __MMI_WDG_ALIVE_H__

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_common_alivewidget.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

//**********
typedef struct
{
    AliveWidgetID_e         eWidgetID;
}WdgAliveConfigData_t;

typedef struct
{
	Pos_t tPos;
	WidgetSize_t tSize;
	WdgAliveConfigData_t tCfg;
}AliveVar_t;

/*=============================================================*/
// functions
/*=============================================================*/
typedef void (*PfnWdgAliveTouchReleaseIn) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pShortMoveData, IWidget *pIWidget);
typedef void (*PfnWdgAliveTouchReleaseOut) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pShortMoveData, IWidget *pIWidget);
typedef void (*PfnWdgAliveTouchMoveToTop) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pShortMoveData, IWidget *pIWidget);
typedef void (*PfnWdgAliveLaunchSMSInbox) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
typedef void (*PfnWdgAliveLaunchCallLog) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
typedef void (*PfnWdgAliveLaunchMediaPlayer) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
typedef void (*PfnWdgAliveLaunchFMRadio) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
typedef void (*PfnWdgAliveLaunchTime) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);

/*=============================================================*/
/** WdgAliveCreateForWnd
* @brief        Alive widget create function for Window
*
* @param[in]    hWin                The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    pData               Alive widget Common Data, refer to WdgAliveConfigData_t.
*                                   If set pSize = NULL : means you want Default Value;
*
* @retval       The pointer of Alive pointer            Success.
* @retval       NULL                                    Failed.
*
*/
IWidget* WdgAliveCreateForWnd
(
    HWIN                    hWin,
    Pos_t                  *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    WdgAliveConfigData_t  *pData
);

/*=============================================================*/
/** WdgAliveCreate
* @brief        Create Alive widget
*
* @retval       The pointer of Alive widget Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgAliveCreate
(
    void
);

/** WdgAliveSetAliveWidgetID
* @brief        Set Alive widget's alive widget ID
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    eWidgetID         The alive widget ID which will be set to the alive widget;
*                                 display liveWidgetID_Singleton_Dog or liveWidgetID_Singleton_Clock...
*
*
*/
__INLINE void WdgAliveSetAliveWidgetID
(
    IWidget                 *pWDGAlive,
    AliveWidgetID_e         eWidgetID
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_ID, (u32)eWidgetID);
}

/** WdgAliveSetVisible
* @brief        Set Alive widget's visible status
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    bVisible          The visible status which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetVisible
(
    IWidget                 *pWDGAlive,
    boolean                 bVisible
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_VISABLE, (u32)bVisible);
}

/** WdgAliveSetAliveWidgetSize
* @brief        Set Alive widget's alive widget size
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    pWidgetSize       The alive widget size which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetAliveWidgetSize
(
    IWidget                 *pWDGAlive,
    WidgetSize_t            *pWidgetSize
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_ALIVEWIDGET_SIZE, (u32)pWidgetSize);
}

/** WdgAliveSetAliveWidgetPosition
* @brief        Set Alive widget's alive widget position
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    pPosition         The alive widget position which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetAliveWidgetPosition
(
    IWidget                 *pWDGAlive,
    WPos_t                  *pPosition
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_ALIVEWIDGET_POS, (u32)pPosition);
}

/** WdgAliveSetImagePosition
* @brief        Set Alive widget's image position
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    pPosition         The image position which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetImagePosition
(
    IWidget                 *pWDGAlive,
    WPos_t                  *pPosition
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_IMAGE_POS, (u32)pPosition);
}

/** WdgAliveSetTextPosition
* @brief        Set Alive widget's text position
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    pPosition         The text position which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetTextPosition
(
    IWidget                 *pWDGAlive,
    WPos_t                  *pPosition
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_TEXT_POS, (u32)pPosition);
}

/** WdgAliveSetCurrentState
* @brief        Set Alive widget's current state
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    eCurrentState     The current state which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetCurrentState
(
    IWidget                 *pWDGAlive,
    AliveWidget_State_e     eCurrentState
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_CURRENT_STATE, (u32)eCurrentState);
}

/** WdgAliveSetClockMinuteLength
* @brief        Set Alive widget's clock minute length
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    nMinuteLength     The clock minute length which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetClockMinuteLength
(
    IWidget                 *pWDGAlive,
    u8                      nMinuteLength
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_CLOCK_MIN_LENGTH, (u32)nMinuteLength);
}

/** WdgAliveSetClockHourLength
* @brief        Set Alive widget's clock hour length
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    nHourLength       The clock hour length which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetClockHourLength
(
    IWidget                 *pWDGAlive,
    u8                      nHourLength
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_CLOCK_HOUR_LENGTH, (u32)nHourLength);
}

/** WdgAliveSetClockBrushSize
* @brief        Set Alive widget's clock brush size
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    nBrushSize        The clock brush size which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetClockBrushSize
(
    IWidget                 *pWDGAlive,
    u8                      nBrushSize
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_CLOCK_BRUSH_SIZE, (u32)nBrushSize);
}

/** WdgAliveSetClockHandColor
* @brief        Set Alive widget's clock hand color
*
* @param[in]    pWDGAlive         The alive widget which want to be set
* @param[in]    tHandColor        The clock hand color which will be set to the alive widget
*
*
*/
__INLINE void WdgAliveSetClockHandColor
(
    IWidget                 *pWDGAlive,
    RGBColor_t              tHandColor
)
{
    WdgCommonSetProperty(pWDGAlive, PROP_ALIVE_WDG_CLOCK_HAND_COLOR, (u32)tHandColor);
}

/** WdgAliveGetAliveWidgetID
* @brief        Get Alive widget's alive widget ID
*
* @param[in]    pWDGAlive         The alive widget which want to be gotten
*
* @retval       AliveWidgetID_e   The alive widget ID which will be gotten from the alive widget
*
*/
AliveWidgetID_e WdgAliveGetAliveWidgetID
(
    IWidget                 *pWDGAlive
);

/** WdgAliveGetVisible
* @brief        Get Alive widget's visible status
*
* @param[in]    pWDGAlive         The alive widget which want to be gotten
*
* @retval       boolean             The visible status which will be gotten from the alive widget
*
*/
boolean WdgAliveGetVisible
(
    IWidget                 *pWDGAlive
);

/** WdgAliveGetImagePosition
* @brief        Get Alive widget's image position
*
* @param[in]    pWDGAlive         The alive widget which want to be gotten
* @param[out]   pPosition         The image position which will be gotten from the alive widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgAliveGetImagePosition
(
    IWidget                 *pWDGAlive,
    WPos_t                  *pPosition
)
{
    return WdgCommonGetProperty(pWDGAlive, PROP_ALIVE_WDG_IMAGE_POS, (u32 *)pPosition);
}

/** WdgAliveGetTextPosition
* @brief        Get Alive widget's text position
*
* @param[in]    pWDGAlive         The alive widget which want to be gotten
* @param[out]   pPosition         The text position which will be gotten from the alive widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgAliveGetTextPosition
(
    IWidget                 *pWDGAlive,
    WPos_t                  *pPosition
)
{
    return WdgCommonGetProperty(pWDGAlive, PROP_ALIVE_WDG_TEXT_POS, (u32 *)pPosition);
}

/** WdgAliveGetCurrentState
* @brief        Get Alive widget's current state
*
* @param[in]    pWDGAlive         The alive widget which want to be gotten
*
* @retval       AliveWidget_State_e   The current state which will be gotten from the alive widget
*
*/
AliveWidget_State_e WdgAliveGetCurrentState
(
    IWidget                 *pWDGAlive
);

/** WdgAliveGetClockMinuteLength
* @brief        Get Alive widget's clock minute length
*
* @param[in]    pWDGAlive       The alive widget which want to be gotten
*
* @retval       u8               The clock minute length which will be gotten from the alive widget
*
*/
u8 WdgAliveGetClockMinuteLength
(
    IWidget                 *pWDGAlive
);

/** WdgAliveGetClockHourLength
* @brief        Get Alive widget's clock hour length
*
* @param[in]    pWDGAlive       The alive widget which want to be gotten
*
* @retval       u8               The clock hour length which will be gotten from the alive widget
*
*/
u8 WdgAliveGetClockHourLength
(
    IWidget                 *pWDGAlive
);

/** WdgAliveGetClockBrushSize
* @brief        Get Alive widget's clock brush size
*
* @param[in]    pWDGAlive       The alive widget which want to be gotten
*
* @retval       u8               The clock brush size which will be gotten from the alive widget
*
*/
u8 WdgAliveGetClockBrushSize
(
    IWidget                 *pWDGAlive
);

/** WdgAliveGetClockHandColor
* @brief        Get Alive widget's clock hand color
*
* @param[in]    pWDGAlive         The alive widget which want to be gotten
* @param[out]   pHandColor        The clock hand color which will be gotten from the alive widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgAliveGetClockHandColor
(
    IWidget                 *pWDGAlive,
    RGBColor_t              *pHandColor
)
{
    return WdgCommonGetProperty(pWDGAlive, PROP_ALIVE_WDG_CLOCK_HAND_COLOR, (u32 *)pHandColor);
}

/** WdgAliveRegisterTouchReleaseInCb
* @brief        Register callback : CB will be triggered when user release touch inside the region of widget.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data passed to the callback function.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveRegisterTouchReleaseInCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveTouchReleaseIn   pfn,
    void                    *pUserData
);

/** WdgAliveRegisterTouchReleaseOutCb
* @brief        Register callback : CB will be triggered when user release touch outside the region of widget.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data passed to the callback function.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveRegisterTouchReleaseOutCb
(
    IWidget                         *pWDGAlive,
    PfnWdgAliveTouchReleaseOut      pfn,
    void                            *pUserData
);

/** WdgAliveRegisterTouchMoveToTopCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement move to top function for the widget.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data passed to the callback function.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveRegisterTouchMoveToTopCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveTouchMoveToTop   pfn,
    void                    *pUserData
);

/** WdgAliveRegisterLaunchSMSInboxCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching SMS inbox function.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data passed to the callback function.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveRegisterLaunchSMSInboxCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveLaunchSMSInbox   pfn,
    void                        *pUserData
);

/** WdgAliveRegisterLaunchCallLogCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching calllog app function.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data passed to the callback function.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveRegisterLaunchCallLogCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveLaunchCallLog    pfn,
    void                        *pUserData
);

/** WdgAliveRegisterLaunchMediaPlayerCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching Media Player app function.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data passed to the callback function.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgAliveRegisterLaunchMediaPlayerCb
(
    IWidget                         *pWDGAlive,
    PfnWdgAliveLaunchMediaPlayer    pfn,
    void                            *pUserData
);

/** WdgAliveRegisterLaunchFMRadioCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching FM Radio app function.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data passed to the callback function.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveRegisterLaunchFMRadioCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveLaunchFMRadio    pfn,
    void                        *pUserData
);

/** WdgAliveRegisterLaunchTimeCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching time app function.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data passed to the callback function.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveRegisterLaunchTimeCb
(
    IWidget                 *pWDGAlive,
    PfnWdgAliveLaunchTime   pfn,
    void                    *pUserData
);

/** WdgAliveDeregisterTouchReleaseInCb
* @brief        Deregister callback.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          Registered User Data.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveDeregisterTouchReleaseInCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveTouchReleaseIn   pfn,
    void                        *pUserData
);

/** WdgAliveDeregisterTouchReleaseOutCb
* @brief        Deregister callback.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          Registered User Data.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveDeregisterTouchReleaseOutCb
(
    IWidget                         *pWDGAlive,
    PfnWdgAliveTouchReleaseOut      pfn,
    void                            *pUserData
);

/** WdgAliveDeregisterTouchMoveToTopCb
* @brief        Deregister callback.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          Registered User Data.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveDeregisterTouchMoveToTopCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveTouchMoveToTop   pfn,
    void                        *pUserData
);

/** WdgAliveDeregisterLaunchSMSInboxCb
* @brief        Deregister callback.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          Registered User Data.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveDeregisterLaunchSMSInboxCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveLaunchSMSInbox   pfn,
    void                        *pUserData
);

/** WdgAliveDeregisterLaunchCallLogCb
* @brief        Deregister callback.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          Registered User Data.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveDeregisterLaunchCallLogCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveLaunchCallLog    pfn,
    void                        *pUserData
);

/** WdgAliveDeregisterLaunchMediaPlayerCb
* @brief        Deregister callback.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          Registered User Data.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveDeregisterLaunchMediaPlayerCb
(
    IWidget                         *pWDGAlive,
    PfnWdgAliveLaunchMediaPlayer    pfn,
    void                            *pUserData
);

/** WdgAliveDeregisterLaunchFMRadioCb
* @brief        Deregister callback.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          Registered User Data.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveDeregisterLaunchFMRadioCb
(
    IWidget                     *pWDGAlive,
    PfnWdgAliveLaunchFMRadio    pfn,
    void                        *pUserData
);

/** WdgAliveDeregisterLaunchTimeCb
* @brief        Deregister callback.
*
* @param[in]    pWDGAlive         The alive widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          Registered User Data.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAliveDeregisterLaunchTimeCb
(
    IWidget                 *pWDGAlive,
    PfnWdgAliveLaunchTime   pfn,
    void                    *pUserData
);


/*=============================================================*/
// functions
/*=============================================================*/

#endif 
#endif //__MMI_WDG_ALIVE_H__
/*=============================================================*/
// end of file
