/**
 * @file:  mmi_wdg_textbubble.h
 * @brief: This file defines the interface for text bubble widget.
 *
 * @version: mmi_wdg_textbubble.h  2011-06-27 evan.chang
 */

#ifndef __MMI_WDG_TEXTBUBBLE_H__
#define __MMI_WDG_TEXTBUBBLE_H__

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

/** PfnWdgTextBubbleTouchPress
* @brief      CB register by "PfnWdgTextBubbleTouchPress"
*             and will be triggered if text bubble touch is pressed.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nValue            Currently undefine
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTextBubbleTouchPress) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nValue, IWidget *pWidget);

/** PfnWdgTextBubbleTouchRelease
* @brief      CB register by "PfnWdgTextBubbleTouchRelease"
*             and will be triggered if text bubble touch is released.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nValue            Currently undefine
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTextBubbleTouchRelease) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nValue, IWidget *pWidget);

/** PfnWdgTextBubbleTouchClick
* @brief      CB register by "PfnWdgTextBubbleTouchClick"
*             and will be triggered if text bubble touch is clicked.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nValue            Currently undefine
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTextBubbleTouchClick) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nValue, IWidget *pWidget);

/*=============================================================*/
// Interface functions
/*=============================================================*/

/** WdgTextBubbleCreateForWnd
* @brief      Create text bubble widget for window
*
* @param[in]    hWin                The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of text bubble widget       Success.
* @retval       NULL                                    Failed.
*
*/
IWidget* WdgTextBubbleCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID
);

/** WdgTextBubbleCreate
* @brief        Create text bubble widget
*
* @retval       The pointer of text bubble widget       Success.
* @retval       NULL                                    Failed.
*
*/
IWidget* WdgTextBubbleCreate
(
    void
);

/** WdgTextBubbleSetImgID_TopLeft
* @brief        Set text bubble widget's top left image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_TopLeft
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_TOP_LEFT, (u32)nImageID);
}

/** WdgTextBubbleSetImgID_TopMid
* @brief        Set text bubble widget's top middle image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_TopMid
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_TOP_MID, (u32)nImageID);
}

/** WdgTextBubbleSetImgID_TopRight
* @brief        Set text bubble widget's top right image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_TopRight
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_TOP_RIGHT, (u32)nImageID);
}

/** WdgTextBubbleSetImgID_CenterLeft
* @brief        Set text bubble widget's center left image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_CenterLeft
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_CENTER_LEFT, (u32)nImageID);
}

/** WdgTextBubbleSetImgID_CenterMid
* @brief        Set text bubble widget's center middle image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_CenterMid
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_CENTER_MID, (u32)nImageID);
}

/** WdgTextBubbleSetImgID_CenterRight
* @brief        Set text bubble widget's center right image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_CenterRight
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_CENTER_RIGHT, (u32)nImageID);
}

/** WdgTextBubbleSetImgID_BottomLeft
* @brief        Set text bubble widget's bottom left image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_BottomLeft
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_BOTTOM_LEFT, (u32)nImageID);
}

/** WdgTextBubbleSetImgID_BottomMid
* @brief        Set text bubble widget's bottom middle image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_BottomMid
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_BOTTOM_MID, (u32)nImageID);
}

/** WdgTextBubbleSetImgID_BottomRight
* @brief        Set text bubble widget's bottom right image id
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nImageID            Text bubble image id
*
* @retval       void
*
*/
__INLINE void WdgTextBubbleSetImgID_BottomRight
(
    IWidget                 *pWDGTextBubble,
    u32                     nImageID
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_IMG_ID_BOTTOM_RIGHT, (u32)nImageID);
}

/** WdgTextBubbleSetText_Size
* @brief        Set text widget's size
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pTexWdgSize         Text widget size
*
* @retval       void
*
*/
__INLINE MAE_Ret WdgTextBubbleSetText_Size
(
    IWidget                 *pWDGTextBubble,
    WidgetSize_t            *pTexWdgSize
)
{
    return WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_TXT_SIZE, (u32)pTexWdgSize);
}

/** WdgTextBubbleSetText_PosOffset
* @brief        Set text widget's position offset
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pTexWdgPosOffset    Text widget position offset
*
* @retval       void
*
*/
__INLINE MAE_Ret WdgTextBubbleSetText_PosOffset
(
    IWidget                 *pWDGTextBubble,
    Pos_t                   *pTexWdgPosOffset
)
{
    return WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_TXT_OFFSET, (u32)pTexWdgPosOffset);
}

/** WdgTextBubbleSetText_Alignment
* @brief        Set text alignment
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nTextAlignment      Text Alignment
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextBubbleSetText_Alignment
(
    IWidget                 *pWDGTextBubble,
    WdgAlignment_e          nTextAlignment
)
{
    return WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_TXT_ALIGNMENT, (u32)nTextAlignment);
}

/** WdgTextBubbleSetText_Color
* @brief    Set text color
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    TextColor           RGBColor_t value
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
__INLINE MAE_Ret WdgTextBubbleSetText_Color
(
    IWidget                 *pWDGTextBubble,
    RGBColor_t              TextColor
)
{
    return WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_TXT_COLOR, (u32)TextColor);
}

/** WdgTextBubbleSetText_LineHeight
* @brief    Set text line height
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    nLineHeight         Line height in pixels
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*/
__INLINE MAE_Ret WdgTextBubbleSetText_LineHeight
(
    IWidget                 *pWDGTextBubble,
    u32                     nLineHeight
)
{
    return WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_TXT_LINE_HEIGHT, (u32)nLineHeight);
}

/** WdgTextBubbleSetText_FontCat
* @brief    Set font category
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    FontCategory        Type of font category
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*/
__INLINE MAE_Ret WdgTextBubbleSetText_FontCat
(
    IWidget                 *pWDGTextBubble,
    FontCategory_t          FontCategory
)
{
    return WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_TXT_FONT_CAT, (u32)FontCategory);
}

/** WdgTextBubbleSetText_StrData
* @brief        Set MAE_WChar string to the widget.
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pWChar              Pointer to MAE_WChar string.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextBubbleSetText_StrData
(
    IWidget                 *pWDGTextBubble,
    MAE_WChar               *pWChar
)
{
    return WdgCommonSetProperty(pWDGTextBubble, PROP_TEXTBUBBLE_WDG_TXT_DATA, (u32)pWChar);
}

/** WdgTextBubbleGetWdgBaseSize
* @brief        Get text bubble widget base size
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pSize               Widget size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
void WdgTextBubbleGetWdgBaseSize
(
    IWidget                 *pWDGTextBubble,
    WidgetSize_t            *pSize
);

/** WdgTextBubbleGetWdgBasePos
* @brief        Get text bubble widget base position
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pSize               Widget position
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
void WdgTextBubbleGetWdgBasePos
(
    IWidget                 *pWDGTextBubble,
    Pos_t                   *pWdgBasePos
);

/** WdgTextBubbleGetTextInfo
* @brief        Get information about the text stored in the Widget, ex, length of text, string of text...
*
* @param[in]    pWDGTextBubble    Text bubble widget pointer
* @param[out]   pTextInfo         Pointer to a TextInfo data structure, which contains length of text, string of text...
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTextBubbleGetTextInfo
(
    IWidget                 *pWDGTextBubble,
    TextInfo                *pTextInfo
);
#ifdef __TOUCH_SCREEN_MMI__
/** WdgTextBubbleSetDisableHandleTouchEvent
* @brief        Set widget's handle touch event disable/enable status
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    bDisable            Handle touch event disable/enable
*
* @retval     void
*
*/
__INLINE void WdgTextBubbleSetDisableHandleTouchEvent
(
    IWidget                 *pWDGTextBubble,
    boolean                 bDisable
)
{
    WdgCommonSetProperty(pWDGTextBubble, PROP_DISABLE_HANDLE_TOUCH_EVT, (u32)bDisable);
}

/** WdgTextBubbleGetDisableHandleTouchEvent
* @brief        Get widget's handle touch event disable/enable status
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[out]   pDisable            Handle touch event disable/enable
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTextBubbleGetDisableHandleTouchEvent
(
    IWidget                 *pWDGTextBubble,
    boolean                 *pDisable
)
{
    return WdgCommonGetProperty(pWDGTextBubble, PROP_DISABLE_HANDLE_TOUCH_EVT, (u32*)pDisable);
}
#endif

/** WdgTextBubbleRegisterTouchPressCb
* @brief        Register text bubble press callback
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pfn                 callback function
* @param[in]    pUserData           User Data when CB trigger.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgTextBubbleRegisterTouchPressCb
(
    IWidget                         *pWDGTextBubble,
    PfnWdgTextBubbleTouchPress      pfn,
    void                            *pUserData
);

/** WdgTextBubbleRegisterTouchReleaseCb
* @brief        Register text bubble release callback
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pfn                 callback function
* @param[in]    pUserData           User Data when CB trigger.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgTextBubbleRegisterTouchReleaseCb
(
    IWidget                         *pWDGTextBubble,
    PfnWdgTextBubbleTouchRelease    pfn,
    void                            *pUserData
);

/** WdgTextBubbleRegisterTouchClickCb
* @brief        Register text bubble click callback
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pfn                 callback function
* @param[in]    pUserData           User Data when CB trigger.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgTextBubbleRegisterTouchClickCb
(
    IWidget                         *pWDGTextBubble,
    PfnWdgTextBubbleTouchClick      pfn,
    void                            *pUserData
);

/** WdgTextBubbleDeregisterTouchPressCb
* @brief        Deregister text bubble press callback
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pfn                 callback function
* @param[in]    pUserData           User Data when CB trigger.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgTextBubbleDeregisterTouchPressCb
(
    IWidget                         *pWDGTextBubble,
    PfnWdgTextBubbleTouchPress      pfn,
    void                            *pUserData
);

/** WdgTextBubbleDeregisterTouchReleaseCb
* @brief        Deregister text bubble release callback
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pfn                 callback function
* @param[in]    pUserData           User Data when CB trigger.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgTextBubbleDeregisterTouchReleaseCb
(
    IWidget                         *pWDGTextBubble,
    PfnWdgTextBubbleTouchRelease    pfn,
    void                            *pUserData
);

/** WdgTextBubbleDeregisterTouchClickCb
* @brief        Deregister text bubble click callback
*
* @param[in]    pWDGTextBubble      Text bubble widget pointer
* @param[in]    pfn                 callback function
* @param[in]    pUserData           User Data when CB trigger.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgTextBubbleDeregisterTouchClickCb
(
    IWidget                         *pWDGTextBubble,
    PfnWdgTextBubbleTouchClick      pfn,
    void                            *pUserData
);

#endif //__MMI_WDG_TEXTBUBBLE_H__
/*=============================================================*/
