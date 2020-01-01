/**
 * @file    mmi_wdg_indicator.h
 * @brief   This file defines the interface of indicaotr widget.
 *
 *   Indicator widget provides the display of indicator. For example, if Radio Frequency AP
 *   wants to display, it can use the Indicator widget. Indicator widget is composed of three
 *   objects, and they are background area, foreground area and indicator. AP can adjust
 *   the indicator offset and the foreground offset according to demand. In addition,
 *   background area image, indicator image and the foreground area image can also be
 *   replaced. Indicator widget can also be vertical.
 *
 *      ex: Horizontal Indicator widget
 *       +-----------------------------------------------------------------------------+
 *       | BG                /\                                                        |
 *       |                 FG Top                                                      |
 *       |                 Offset                                                      |
 *       |                   \/    +---+                                               |
 *       |               +---------|   |-----------------------------------+           |
 *       |               |/// FG// |Ind|*****DWN*****|                     |           |
 *       |<   FG Left   >|/////////|   |*************|                     |< FG Right>|
 *       |    Offset     +---------|   |-----|----------|----------|-------+   Offset  |
 *       |                   /\    +---+    10         15         20                   |
 *       |                 FG Bottom                                                   |
 *       |                  Offset                                                     |
 *       |                   \/                                                        |
 *       +-----------------------------------------------------------------------------+
 *
 */

#ifndef __MMI_WDG_INDICATOR_H__
#define __MMI_WDG_INDICATOR_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"
/*=============================================================*/
// type and define
/*=============================================================*/

/** IndicatorData_t
*
* @brief    nStart:         The Left/Top number
*           nEnd:           The Right/Bottom number
*           nPos:           Indicate number
*           nDownloadStart: Download Progress Left/Top number
*           nDownloadEnd:   Download Progress Right/Bottom number
*
*/
typedef struct{
    s32 nStart;
    s32 nEnd;
    s32 nPos;
#ifdef __DOWNLOAD_PROGRESS__
    s32 nDownloadStart;
    s32 nDownloadEnd;
#endif	//__DOWNLOAD_PROGRESS__
}IndicatorData_t;

/** PfnWdgIndicatorIndicatorPress
* @brief      CB register by "PfnWdgIndicatorIndicatorPress"
*             and will be triggered if indicator is pressed.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nNewPos           The new position of indicator
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgIndicatorIndicatorPress) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nNewPos, IWidget *pWidget);

/** PfnWdgIndicatorIndicatorRelease
* @brief      CB register by "PfnWdgIndicatorIndicatorRelease"
*             and will be triggered if indicator is released.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nNewPos           The new position of indicator
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgIndicatorIndicatorRelease) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nNewPos, IWidget *pWidget);

/** PfnWdgIndicatorIndicatorMove
* @brief      CB register by "PfnWdgIndicatorIndicatorMove"
*             and CB will be triggered if indicator is moving.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nNewPos           The new position of indicator
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgIndicatorIndicatorMove) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nNewPos, IWidget *pWidget);

/** PfnWdgIndicatorWidgetDataChange
* @brief      CB register by "PfnWdgIndicatorWidgetDataChange"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgIndicatorWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);


/*=============================================================*/
// Interface functions
/*=============================================================*/
/** WdgIndicatorCreateForWnd
* @brief      Create Indicator widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    eWdgLayoutStyle     The widget layout style which will be set to the Indicator widget
*
* @retval       The pointer of Indicator        Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgIndicatorCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    WdgLayoutStyle_e        eWdgLayoutStyle
);


/** WdgIndicatorSetData
* @brief        Set display data for Indicator widget.
*               Specific data for Indicator widget.
*
* @param[in]    pWDGIndicator      Pointer to the Indicator widget
* @param[in]    pSpecData          Display data of Indicator Widget.
*
* @retval       MAE_RET_SUCCESS    Success
* @retval       others             Failed
*
*/
MAE_Ret WdgIndicatorSetData
(
    IWidget                     *pWDGIndicator,
    IndicatorData_t             *pSpecData
);
/*=============================================================*/
/** WdgIndicatorCreate
* @brief        Create Indicator widget
*
* @retval       The pointer of Indicator            Success.
* @retval       NULL                                Failed.
*
*/
IWidget* WdgIndicatorCreate
(
    void
);

/** WdgIndicatorSetLayoutStyle
* @brief        Set Indicator widget layout style
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    eWdgLayoutStyle   The widget layout style which will be set to the Indicator widget
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetLayoutStyle
(
    IWidget                 *pWDGIndicator,
    WdgLayoutStyle_e        eWdgLayoutStyle
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_LAYOUT_STYLE, (u32)eWdgLayoutStyle);
}

#ifdef __TOUCH_SCREEN_MMI__
/** WdgIndicatorSetDisableHandleTouchEvent
* @brief        Set Indicator widget's handle touch event disable/enable status
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    bDisable          The widget's handle touch event disable/enable status which will be set to the Indicator widget
*
* @retval     void
*
*/
__INLINE void WdgIndicatorSetDisableHandleTouchEvent
(
    IWidget                 *pWDGIndicator,
    boolean                 bDisable
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_DISABLE_HANDLE_TOUCH_EVT, (u32)bDisable);
}
#endif

/** WdgIndicatorSetFGTopOffset
* @brief        Set Indicator widget's Foreground top offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nFGTopOffset      Foreground top offset in pixels
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetFGTopOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nFGTopOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_FG_TOP_OFFSET, (u32)nFGTopOffset);
}

/** WdgIndicatorSetFGBottomOffset
* @brief        Set Indicator widget's Foreground bottom offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nFGBottomOffset   Foreground bottom offset in pixels
*
* @retval      void
*
*/
__INLINE void WdgIndicatorSetFGBottomOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nFGBottomOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_FG_BOTTOM_OFFSET, (u32)nFGBottomOffset);
}

/** WdgIndicatorSetFGLeftOffset
* @brief        Set Indicator widget's Foreground left offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nFGLeftOffset     Foreground left offset in pixels
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetFGLeftOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nFGLeftOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_FG_LEFT_OFFSET, (u32)nFGLeftOffset);
}

/** WdgIndicatorSetFGRightOffset
* @brief        Set Indicator widget's Foreground right offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nFGRightOffset    Foreground right offset in pixels
*
* @retval     void
*
*/
__INLINE void WdgIndicatorSetFGRightOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nFGRightOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_FG_RIGHT_OFFSET, (u32)nFGRightOffset);
}

#ifdef __DOWNLOAD_PROGRESS__
/** WdgIndicatorSetDWNTopOffset
* @brief        Set Indicator widget's Download top offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nDWNTopOffset     Download top offset in pixels
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetDWNTopOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nDWNTopOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_DWN_TOP_OFFSET, (u32)nDWNTopOffset);
}

/** WdgIndicatorSetDWNBottomOffset
* @brief        Set Indicator widget's Download bottom offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nDWNBottomOffset  Download bottom offset in pixels
*
* @retval      void
*
*/
__INLINE void WdgIndicatorSetDWNBottomOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nDWNBottomOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_DWN_BOTTOM_OFFSET, (u32)nDWNBottomOffset);
}

/** WdgIndicatorSetDWNLeftOffset
* @brief        Set Indicator widget's Download left offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nDWNLeftOffset    Download left offset in pixels
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetDWNLeftOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nDWNLeftOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_DWN_LEFT_OFFSET, (u32)nDWNLeftOffset);
}

/** WdgIndicatorSetDWNRightOffset
* @brief        Set Indicator widget's Download right offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nDWNRightOffset   Download right offset in pixels
*
* @retval     void
*
*/
__INLINE void WdgIndicatorSetDWNRightOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nDWNRightOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_DWN_RIGHT_OFFSET, (u32)nDWNRightOffset);
}

/** WdgIndicatorSetDWNEndOffset
* @brief        Set Indicator widget's Indicator offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nDWNEndOffset     Download end offset in pixels
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetDWNEndOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nDWNEndOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_DWN_END_OFFSET, (u32)nDWNEndOffset);
}
#endif	//__DOWNLOAD_PROGRESS__

/** WdgIndicatorSetINDOffset
* @brief        Set Indicator widget's Indicator offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nINDOffset        Indicator offset in pixels
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetINDOffset
(
    IWidget                 *pWDGIndicator,
    u8                      nINDOffset
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_IND_OFFSET, (u32)nINDOffset);
}

/** WdgIndicatorSetINDImage
* @brief        Set Indicator widget's Indicator Image
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    pINDImage         Indicator Image
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetINDImage
(
    IWidget                 *pWDGIndicator,
    IImage                  *pINDImage
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_IND_IMG, (u32)pINDImage);
}

/** WdgIndicatorSetFGImage
* @brief        Set Indicator widget's Foreground Image
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    pFGImage          Foreground Image
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetFGImage
(
    IWidget                 *pWDGIndicator,
    IImage                  *pFGImage
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_FG_IMG, (u32)pFGImage);
}

#ifdef __DOWNLOAD_PROGRESS__
/** WdgIndicatorSetDWNImage
* @brief        Set Indicator widget's Download Progress Image
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    pDWNImage         Download Image
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetDWNImage
(
    IWidget                 *pWDGIndicator,
    IImage                  *pDWNImage
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_DWN_IMG, (u32)pDWNImage);
}

/** WdgIndicatorSetDWNENDImage
* @brief        Set Indicator widget's Download Progress End Image
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    pDWNENDImage         Download Progress End Image
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetDWNENDImage
(
    IWidget                 *pWDGIndicator,
    IImage                  *pDWNENDImage
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_DWN_END_IMG, (u32)pDWNENDImage);
}
#endif	//__DOWNLOAD_PROGRESS__

/** WdgIndicatorSetBGImage
* @brief        Set Indicator widget's Background Image
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    pBGImage          Background Image
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetBGImage
(
    IWidget                *pWDGIndicator,
    IImage                 *pBGImage
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_BG_IMG, (u32)pBGImage);
}

/** WdgIndicatorSetINDImageID
* @brief        Set Indicator widget's Indicator image id
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nImageID          Indicator image id
*
* @retval       void
*
*/
__INLINE void WdgIndicatorSetINDImageID
(
    IWidget                 *pWDGIndicator,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_IND_IMG_ID, (u32)nImageID);
}

/** WdgIndicatorSetFGImageID
* @brief        Set Indicator widget's Foreground image id
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nImageID          Foreground image id
*
* @retval     void
*
*/
__INLINE void WdgIndicatorSetFGImageID
(
    IWidget                 *pWDGIndicator,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_FG_IMG_ID, (u32)nImageID);
}

#ifdef __DOWNLOAD_PROGRESS__
/** WdgIndicatorSetDWNImageID
* @brief        Set Indicator widget's Download Progress image id
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nImageID          Download Progress image id
*
* @retval     void
*
*/
__INLINE void WdgIndicatorSetDWNImageID
(
    IWidget                 *pWDGIndicator,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_DWN_IMG_ID, (u32)nImageID);
}

/** WdgIndicatorSetDWNENDImageID
* @brief        Set Indicator widget's Download Progress End image id
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nImageID          Download Progress End image id
*
* @retval     void
*
*/
__INLINE void WdgIndicatorSetDWNENDImageID
(
    IWidget                 *pWDGIndicator,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_DWN_END_IMG_ID, (u32)nImageID);
}

/** WdgIndicatorSetDisableIndMoveDwnBoundaryChk
* @brief        Disable indicator move download boundary check.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    bDisable          Disable indicator move download boundary check.
*
* @retval     void
*
*/
__INLINE void WdgIndicatorSetDisableIndMoveDwnBoundaryChk
(
    IWidget                 *pWDGIndicator,
    boolean                 bDisable
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_DISABLE_IND_MOVE_DWN_BOUNDARY_CHK, (u32)bDisable);
}
#endif	//__DOWNLOAD_PROGRESS__

/** WdgIndicatorSetBGImageID
* @brief        Set Indicator widget's Background image id
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be set
* @param[in]    nImageID          Background image id
*
* @retval     void
*/
__INLINE void WdgIndicatorSetBGImageID
(
    IWidget                 *pWDGIndicator,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGIndicator, PROP_INDICATOR_WDG_BG_IMG_ID, (u32)nImageID);
}

/** WdgIndicatorGetData
* @brief        GetData display data for Indicator widget.
*
* @param[in]    pWDGIndicator      Pointer to the Indicator widget
* @param[out]   pSpecData          Display data of Indicator Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorGetData
(
    IWidget                     *pWDGIndicator,
    IndicatorData_t             *pSpecData
);

/** WdgIndicatorGetLayoutStyle
* @brief        Get Indicator widget layout style
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pWdgLayoutStyle   The widget layout style which will be get to the Indicator widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetLayoutStyle
(
    IWidget                 *pWDGIndicator,
    WdgLayoutStyle_e        *pWdgLayoutStyle
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_LAYOUT_STYLE, (u32*)pWdgLayoutStyle);
}

/** WdgIndicatorGetFGTopOffset
* @brief        Get Indicator widget's Foreground top offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pFGTopOffset      Foreground top offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetFGTopOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pFGTopOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_FG_TOP_OFFSET, (u32*)pFGTopOffset);
}

/** WdgIndicatorGetFGBottomOffset
* @brief        Get Indicator widget's Foreground bottom offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pFGBottomOffset   Foreground bottom offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetFGBottomOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pFGBottomOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_FG_BOTTOM_OFFSET, (u32*)pFGBottomOffset);
}

/** WdgIndicatorGetFGLeftOffset
* @brief        Get Indicator widget's Foreground left offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pFGLeftOffset     Foreground left offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetFGLeftOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pFGLeftOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_FG_LEFT_OFFSET, (u32*)pFGLeftOffset);
}

/** WdgIndicatorGetFGRightOffset
* @brief        Get Indicator widget's Foreground right offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pFGRightOffset    Foreground right offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetFGRightOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pFGRightOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_FG_RIGHT_OFFSET, (u32*)pFGRightOffset);
}

#ifdef __DOWNLOAD_PROGRESS__
/** WdgIndicatorGetDWNTopOffset
* @brief        Get Indicator widget's Download top offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pDWNTopOffset     Download top offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetDWNTopOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pDWNTopOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_DWN_TOP_OFFSET, (u32*)pDWNTopOffset);
}

/** WdgIndicatorGetDWNBottomOffset
* @brief        Get Indicator widget's Download bottom offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pDWNBottomOffset  Download bottom offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetDWNBottomOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pDWNBottomOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_DWN_BOTTOM_OFFSET, (u32*)pDWNBottomOffset);
}

/** WdgIndicatorGetDWNLeftOffset
* @brief        Get Indicator widget's Download left offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pDWNLeftOffset    Download left offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetDWNLeftOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pDWNLeftOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_DWN_LEFT_OFFSET, (u32*)pDWNLeftOffset);
}

/** WdgIndicatorGetDWNRightOffset
* @brief        Get Indicator widget's Download right offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pDWNRightOffset   Download right offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetDWNRightOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pDWNRightOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_DWN_RIGHT_OFFSET, (u32*)pDWNRightOffset);
}

/** WdgIndicatorGetDWNEndOffset
* @brief        Get Indicator widget's Indicator offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pDWNEndOffset     Download end offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetDWNEndOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pDWNEndOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_DWN_END_OFFSET, (u32*)pDWNEndOffset);
}
#endif	//__DOWNLOAD_PROGRESS__

/** WdgIndicatorGetINDOffset
* @brief        Get Indicator widget's Indicator offset in pixels
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pINDOffset        Indicator offset in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetINDOffset
(
    IWidget                 *pWDGIndicator,
    u8                      *pINDOffset
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_INDICATOR_IND_OFFSET, (u32*)pINDOffset);
}

#ifdef __TOUCH_SCREEN_MMI__
/** WdgIndicatorGetDisableHandleTouchEvent
* @brief        Get Indicator widget's handle touch event disable/enable status
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
* @param[out]   pDisable          The widget's handle touch event disable/enable status which will be get to the Indicator widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgIndicatorGetDisableHandleTouchEvent
(
    IWidget                 *pWDGIndicator,
    boolean                 *pDisable
)
{
    return WdgCommonGetProperty(pWDGIndicator, PROP_DISABLE_HANDLE_TOUCH_EVT, (u32*)pDisable);
}

/** WdgIndicatorisTouchPressed
* @brief        check if the Indicator widget is touch pressed now
*
* @param[in]    pWDGIndicator     The Indicator widget which want to be get
*
* @retval       TRUE             the Indicator widget is touch pressed
* @retval       FALSE            the Indicator widget is not touch pressed
*
*/
boolean WdgIndicatorisTouchPressed
(
    IWidget                     *pWDGIndicator
);
#endif

/** WdgIndicatorRegisterIndicatorPressCb
* @brief        Register indicator press callback; CB will be triggered if indicator is pressed.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorRegisterIndicatorPressCb
(
    IWidget                         *pWDGIndicator,
    PfnWdgIndicatorIndicatorPress   pfn,
    void                            *pUserData
);

/** WdgIndicatorRegisterIndicatorReleaseCb
* @brief        Register indicator release callback; CB will be triggered if indicator is released.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorRegisterIndicatorReleaseCb
(
    IWidget                         *pWDGIndicator,
    PfnWdgIndicatorIndicatorRelease pfn,
    void                            *pUserData
);

/** WdgIndicatorRegisterIndicatorMoveCb
* @brief        Register indicator move callback; CB will be triggered if indicator is moving.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorRegisterIndicatorMoveCb
(
    IWidget                         *pWDGIndicator,
    PfnWdgIndicatorIndicatorMove    pfn,
    void                            *pUserData
);

/** WdgIndicatorRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorRegisterDataChangeCb
(
    IWidget                             *pWDGIndicator,
    PfnWdgIndicatorWidgetDataChange  pfn,
    void                                *pUserData
);

/** WdgIndicatorDeregisterIndicatorPressCb
* @brief        Deregister indicator press callback; CB will be triggered if indicator is pressed.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorDeregisterIndicatorPressCb
(
    IWidget                         *pWDGIndicator,
    PfnWdgIndicatorIndicatorPress   pfn,
    void                            *pUserData
);

/** WdgIndicatorDeregisterIndicatorReleaseCb
* @brief        Deregister indicator release callback; CB will be triggered if indicator is released.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorDeregisterIndicatorReleaseCb
(
    IWidget                         *pWDGIndicator,
    PfnWdgIndicatorIndicatorRelease pfn,
    void                            *pUserData
);

/** WdgIndicatorDeregisterIndicatorMoveCb
* @brief        Deregister indicator move callback; CB will be triggered if indicator is moving.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorDeregisterIndicatorMoveCb
(
    IWidget                         *pWDGIndicator,
    PfnWdgIndicatorIndicatorMove    pfn,
    void                            *pUserData
);

/** WdgIndicatorDeregisterDataChangeCb
* @brief        Deregister data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGIndicator     The Indicator widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgIndicatorDeregisterDataChangeCb
(
    IWidget                             *pWDGIndicator,
    PfnWdgIndicatorWidgetDataChange  pfn,
    void                                *pUserData
);

#endif //__MMI_WDG_INDICATOR_H__
/*=============================================================*/
// end of file
