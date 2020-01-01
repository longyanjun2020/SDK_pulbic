/**
* @file    mmi_wdg_pulldown.h
* @version $Id: mmi_wdg_pulldown.h 39576 2009-09-07 08:54:00Z steve.lee $
*
*     If AP wants to show many types of messages in the screen, but in the one time 
*     only a certain type of message can be displayed, the AP may choose Tab widget. 
*     Tab widget is divided into Tab area and Content area. Tab area will always display 
*     one active tab, and the rest are inactive tabs. When the active tab is changed, the 
*     content in content area will also be changed. Content area is formed by a Sheet 
*     container, when the Tab widget is created, the Sheet container is generated together. 
*
*          ex: Pull-Down widget
*
*   The layout of single display item:
*   +----------------------------------+
*   | +-------------------------++----+|
*   | |    item selected        || <- +|    a down arrow image
*   | +-------------------------++----+|
*   +----------------------------------+
*              ||  
*              ||  When press arrow
*              \/
*   +------------------------------------+
*   |  +-------------------------++----+ |
*   |  |    item selected        |  |  + |
*   |  +-------------------------++----+ |
*   |  +-------------------------------+ |
*   |  +-------------------------------+ |
*   |  |         item 1                | |
*   |  +-------------------------------+ |
*   |  +-------------------------------+ |
*   |  |         item 2                | |
*   |  +-------------------------------+ |
*   |  +-------------------------------+ |
*   |  |         item 3                | |
*   |  +-------------------------------+ |
*   +------------------------------------+
*
*
*/

#ifndef __MMI_WDG_PULLDOWN_H__
#define __MMI_WDG_PULLDOWN_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_image_text_image.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"
/*=============================================================*/
// type and define
/*=============================================================*/
enum {
	PULLDOWN_WDG_MODE_TEXT_ONLY = 0,
	PULLDOWN_WDG_MODE_IMAGE_ONLY,
	PULLDOWN_WDG_MODE_IMAGE_TEXT,
	PULLDOWN_WDG_MODE_TOTAL
};
typedef u8 PullDownWdgMode_et;

/** WdgPullDownInfo_t
*
* @brief    nImageID:       The display image data.
*           nTextID:        The display text data.
*
*/
typedef struct
{
    u32         nImageID;
    u32         nTextID;
} WdgPullDownInfo_t;

/** PfnWdgPullDownFocusChange
* @brief      CB register by "WdgPullDownRegFoucedChangeCb"
*             and will be trigger when the focus of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pFocusData        The info can get when focus changed, refer to FocusChangeData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgPullDownFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusData, IWidget *pWidget);

/*=============================================================*/
// Interface functions
/*=============================================================*/

/** WdgPullDownCreateForWnd
* @brief        Create PullDown widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of PullDown         Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgPullDownCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID
);

/** WdgPullDownCreate
* @brief        Create PullDown widget
*
* @retval       The pointer of PullDown         Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgPullDownCreate
(
    void
);

/** WdgPullDownSetData
* @brief        Set display data for PullDown widget.
*               Specific data for PullDown widget.
*
* @param[in]    pPullDown           Pointer to the PullDown widget
* @param[in]    ppWdgPullDownInfo   nItemNum display data array, refer to ImageTextInfo_st.
*                                   PULLDOWN_WDG_MODE_TEXT_ONLY ==> ImageTextInfo_st.PreImage_Ptr must be NULL.
*                                   PULLDOWN_WDG_MODE_IMAGE_ONLY==> ImageTextInfo_st.WText_Ptr must be NULL.
*                                   PULLDOWN_WDG_MODE_IMAGE_TEXT==> ImageTextInfo_st.PreImage_Ptr and ImageTextInfo_st.WText_Ptr must not NULL.
*
* @param[in]    nItemNum            number of display data
* @param[in]    pfFree              Free CB function for free data allocate by User while widget destroy.
* @param[in]    pOwner              Shall be an IBase interface object to keep the return object.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgPullDownSetData
(
    IWidget             *pPullDown,
    ImageTextInfo_st    **ppWdgPullDownInfo,
    u32                 nItemNum,
    PfnDataFree         pfFree,
    IBase               *pOwner
);

/** WdgPullDownSetDataById
* @brief        Set display data for PullDown widget By ID.
*               Specific data for PullDown widget.
*
* @param[in]    pPullDown        Pointer to the PullDown widget
* @param[in]    pPullDownInfo    nItemNum display data array, refer to WdgPullDownInfo_t.
*                                PULLDOWN_WDG_MODE_TEXT_ONLY ==> WdgPullDownInfo_t.nImageID is image data.
*                                PULLDOWN_WDG_MODE_IMAGE_ONLY==> WdgPullDownInfo_t.nTextID is text data.
*                                PULLDOWN_WDG_MODE_IMAGE_TEXT==> WdgPullDownInfo_t.nImageID is image data and WdgPullDownInfo_t.nTextID is text data.
*
* @param[in]    nItemNum         number of display data
*
* @retval       MAE_RET_SUCCESS  Success
* @retval       others           Failed
*
*/
MAE_Ret WdgPullDownSetDataById
(
    IWidget             *pPullDown,
    WdgPullDownInfo_t   *pPullDownInfo,
    u32                 nItemNum
);

/** WdgPullDownSetFocusIndex
* @brief        Set PullDown widget focus index
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    nIndex         The Focus index of PullDown widget
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetFocusIndex
(
    IWidget                 *pPullDown,
    u32                     nIndex
)
{
    WdgCommonSetProperty(pPullDown, PROP_FOCUS_INDEX, (u32)nIndex);
}

/** WdgPullDownSetLayoutMode
* @brief        Set PullDown widget layout mode
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    nMode          Layout mode of PullDown widget, refer to PullDownWdgMode_et.
*                              PULLDOWN_WDG_MODE_TEXT_ONLY
*                              PULLDOWN_WDG_MODE_IMAGE_ONLY
*                              PULLDOWN_WDG_MODE_IMAGE_TEXT
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetLayoutMode
(
    IWidget                 *pPullDown,
    PullDownWdgMode_et      nMode
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_LAYOUT_MODE, (u32)nMode);
}

/** WdgPullDownSetNaviUpKey
* @brief        Set PullDown widget navigation up key code, hard key in cellphone.
*               Default is MAE_KEY_UP(Up key of cellphone);
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    nUpKeyCode     The up key code: see mae_event.h
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetNaviUpKey
(
    IWidget                 *pPullDown,
    MAE_Key_t               nUpKeyCode
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_NAVI_UP_KEY, (u32)nUpKeyCode);
}

/** WdgPullDownSetNaviDownKey
* @brief        Set PullDown widget navigation down key code, hard key in cellphone.
*               Default is MAE_KEY_DOWN(Down key of cellphone).
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    nDownKeyCode   The down key code: see mae_event.h
*
* @retval       void
*/
__INLINE void WdgPullDownSetNaviDownKey
(
    IWidget                 *pPullDown,
    MAE_Key_t               nDownKeyCode
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_NAVI_DOWN_KEY, (u32)nDownKeyCode);
}

/** WdgPullDownSetToggleListKey
* @brief        Set PullDown widget toggle list key code, hard key in cellphone.
*               Default is MAE_KEY_ACTION(Action key of cellphone).
*
* @param[in]    pPullDown               The pointer of IWidget interface object
* @param[in]    nToggleDropListKeyCode  The toggle drop list key code
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetToggleListKey
(
    IWidget                 *pPullDown,
    MAE_Key_t               nToggleDropListKeyCode
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_TOGGLE_LIST_KEY, (u32)nToggleDropListKeyCode);
}

/** WdgPullDownSetArrowWidth
* @brief        The arrow width of this pull-down widget. A u16 variable.
*               Default value is PULLDOWN_WDG_ARROW_WIDTH which is defined at mmi_layout.h
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    nArrowWidth    The Arrow width of PullDown widget in pixel
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetArrowWidth
(
    IWidget                 *pPullDown,
    u32                     nArrowWidth
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_ARROW_WIDTH, (u32)nArrowWidth);
}

/** WdgPullDownSetArrowImage
* @brief        The arrow image of pull-down widget.
*               A IBitmap object pointer. User can set it only, can not get it from this widget.
*               The default image id is "COMMON_IMG_ARROW_DOWN_UNPRESSED", which is defined at Img_data.h.
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    pIBitmap       The bitmap image of Arrow
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetArrowImage
(
    IWidget                 *pPullDown,
    IBitmap                 *pIBitmap
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_ARROW_IMG, (u32)pIBitmap);
}

#ifdef __TOUCH_SCREEN_MMI__
/** WdgPullDownSetPressedArrowImage
* @brief        The touch pressed arrow image of pull-down widget.
*               A IBitmap object pointer.User can set it only, can not get it from this widget.
*               The default image id is "COMMON_IMG_ARROW_DOWN_PRESSED", which is defined at Img_data.h
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    pIBitmap       The bitmap image of pressed Arrow
*
* @retval      void
*/
__INLINE void WdgPullDownSetPressedArrowImage
(
    IWidget                 *pPullDown,
    IBitmap                 *pIBitmap
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_PRESSED_ARROW_IMG, (u32)pIBitmap);
}
#endif

/** WdgPullDownSetTextColor
* @brief        Set PullDown widget text color
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    nTextColor     PullDown widget text color
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetTextColor
(
    IWidget                 *pPullDown,
    RGBColor_t              nTextColor
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_TEXT_COLOR, (u32)nTextColor);
}

/** WdgPullDownSetHighlightTextColor
* @brief        Set PullDown widget highlighted text color
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    tHlTextColor   PullDown widget highlighted text color
*
* @retval        void
*/
__INLINE void WdgPullDownSetHighlightTextColor
(
    IWidget                 *pPullDown,
    RGBColor_t              tHlTextColor
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_HL_TEXT_COLOR, (u32)tHlTextColor);
}

/** WdgPullDownSetHighlightBgColor
* @brief        Set PullDown widget focused highlighted background color
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    tFcsBGColor    The focused highlighted background color of PullDown widget
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetHighlightBgColor
(
    IWidget                 *pPullDown,
    RGBColor_t              tFcsBGColor
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_HL_BG_COLOR, (u32)tFcsBGColor);
}

/** WdgPullDownSetListBorderColor
* @brief        Set PullDown widget border color of dropping list.
*
* @param[in]    pPullDown      The pointer of IWidget interface object
* @param[in]    nBorderColor   The border color of PullDown widget
*
* @retval       void
*
*/
__INLINE void WdgPullDownSetListBorderColor
(
    IWidget                 *pPullDown,
    RGBColor_t              nBorderColor
)
{
    WdgCommonSetProperty(pPullDown, PROP_PULLDOWN_WDG_LIST_BORDER_COLOR, (u32)nBorderColor);
}

/** WdgPullDownGetFocusedIndex
* @brief        Get PullDown widget focused index
*
* @param[in]    pPullDown      The pointer of IWidget interface object
*
* @retval       u32            The Focus index of PullDown widget
*
*/
u32 WdgPullDownGetFocusedIndex
(
    IWidget                 *pPullDown
);

/** WdgPullDownRegFoucedChangeCb
* @brief        Register callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]    pPullDown      The PullDown widget which want to set callback
* @param[in]    pfn            callback function
* @param[in]    pUserData       User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgPullDownRegFoucedChangeCb
(
    IWidget                     *pPullDown,
    PfnWdgPullDownFocusChange   pfn,
    void                        *pUserData
);

/** WdgPullDownDeregFoucedChangeCb
* @brief        Deregister callback for changing focus item
*
* @param[in]    pPullDown      The PullDown widget which want to Deregister callback
* @param[in]    pfn            callback function
* @param[in]    pUserData       User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgPullDownDeregFoucedChangeCb
(
    IWidget                     *pPullDown,
    PfnWdgPullDownFocusChange   pfn,
    void                        *pUserData
);

#endif //__MMI_WDG_PULLDOWN_H__
/*=============================================================*/
// end of file
