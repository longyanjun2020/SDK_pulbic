/**
* @file    mmi_wdg_tab.h
* @version $Id: mmi_wdg_tab.h 14596 2008-10-01 09:04:35Z paul.ouyang $
* @brief   Tab Widget
*<Description>
*    The layout in different mode:
*<pre>
*    TAB_WDG_MODE_TOP_IMAGETEXT mode:
*                      +--------------+
*      +--------------+|              |+--------------+
*      | Image Text   || Image Text   || Image Text   |
*      |     One      ||     Two      ||     Three    |
*    ------------------+              +------------------
*
*    TAB_WDG_MODE_TOP_IMAGE_ONLY mode:
*                                      +--------------+
*      +--------------++--------------+|              |
*      |    Image     ||    Image     ||    Image     |
*      |     One      ||     Two      ||     Three    |
*    ----------------------------------+              +--
*
*    TAB_WDG_MODE_TOP_TEXT_ONLY mode:
*      +--------------+
*      |              |+--------------++--------------+
*      | Text         || Text         || Text         |
*      |     One      ||     Two      ||     Three    |
*    --+              +----------------------------------
*
*
*    TAB_WDG_MODE_BOTTOM_IMAGE_RING mode:
*                       +--------------+
*      +--------------+ |              | +--------------+
*      |    Image     | |    Image     | |    Image     |
*      |     One      | |     Two      | |     Three    |
*    -------------------+              +-------------------
*</pre>
*
*
*/
#ifndef __MMI_WDG_TAB_H__
#define __MMI_WDG_TAB_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_sheetcontainer.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"
/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum
{
	TAB_WDG_MODE_TOP_IMAGETEXT = 0, // deprecated ???
	TAB_WDG_MODE_TOP_IMAGE_ONLY,
	TAB_WDG_MODE_TOP_TEXT_ONLY,
#ifndef __WIDGET_DISABLE_FINGLIST__
	TAB_WDG_MODE_BOTTOM_IMAGE_RING,
#endif
	TAB_WDG_MODE_TOTAL
} TabWdgMode_t;
typedef u8 TabWdgMode_e;

typedef struct {
	IBase      *ImagePtr; ///< An IImage or IBitmap object
	MAE_WChar  *TextPtr;
	IBase      *LargeImagePtr;///< An IImage or IBitmap object, for TAB_WDG_MODE_BOTTOM_IMAGE_RING mode only.
} TabInfo_t;

#define TABWDG_FLAG_WRAP	0x0001 //wrap to first/last element

/** WdgTabInfo_t
*
* @brief    nImageID:       The display image data of Top Image or Bottom Image.
*           nTextID:        The display text data.
*
*/
typedef struct {
    u32         nImageID;   //Image ID
    u32         nTextID;    //Text ID
} WdgTabInfo_t;

/** PfnWdgTabTabChange
* @brief      CB register by "WdgTabRegisterTabChangeCb"
*             and will be trigger when the active table is changed; Ex,WdgTabSetFocusIndex
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pTabData          The info can get when tab changed, refer to TabChangeData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgTabTabChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);

/*=============================================================*/
// interface functions
/*=============================================================*/
/** WdgTabCreateForWnd
* @brief        Create Tab widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of Tab          Success.
* @retval       NULL                        Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgTabCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID
);

/** WdgTabCreate
* @brief        Create Tab widget
*
* @retval       The pointer of Tab          Success.
* @retval       NULL                        Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgTabCreate
(
    void
);

/** WdgTabSetData
* @brief        Set display data for tab widget.
*               Specific data for tab widget.
*
* @param[in]    pWDGTab             Pointer to the tab widget
* @param[in]    pWdgTabInfo        nItemNum display data array, refer to TabInfo_t.
*                                   TAB_WDG_MODE_TOP_IMAGE_ONLY ==> TabInfo_t.TextPtr and TabInfo_t.LargeImagePtr must be NULL.
*                                   TAB_WDG_MODE_TOP_TEXT_ONLY ==> TabInfo_t.ImagePtr and TabInfo_t.LargeImagePtr must be NULL.
*                                   TAB_WDG_MODE_TOP_IMAGETEXT ==> TabInfo_t.LargeImagePtr must be NULL.
*                                   TAB_WDG_MODE_BOTTOM_IMAGE_RING ==> TabInfo_t.TextPtr and TabInfo_t.ImagePtr must be NULL.
*
* @param[in]    nItemNum            number of display data
* @param[in]    pfFree              Free CB function for free data allocate by User while widget destroy.
* @param[in]    pOwner              Shall be an IBase interface object to keep the return object.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgTabSetData
(
    IWidget         *pWDGTab,
    TabInfo_t       **pWdgTabInfo,
    u32             nItemNum,
    PfnDataFree     pfFree,
    IBase           *pOwner
);

/** WdgTabSetDataByID
* @brief        Set display data for tab widget By ID.
*               Specific data for tab widget.
*
* @param[in]    pWDGTab             Pointer to the tab widget
* @param[in]    pTabInfo            nItemNum display data array, refer to WdgTabInfo_t.
*                                   TAB_WDG_MODE_TOP_IMAGE_ONLY ==> WdgTabInfo_t.nImageID is top image.
*                                   TAB_WDG_MODE_TOP_TEXT_ONLY ==> WdgTabInfo_t.nTextID is top text.
*                                   TAB_WDG_MODE_TOP_IMAGETEXT ==> WdgTabInfo_t.nImageID is top image, WdgTabInfo_t.nTextID is top text.
*                                   TAB_WDG_MODE_BOTTOM_IMAGE_RING ==> WdgTabInfo_t.nImageID is bottom image.
*
* @param[in]    nItemNum            number of display data
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgTabSetDataByID
(
    IWidget         *pWDGTab,
    WdgTabInfo_t    *pTabInfo,
    u32             nItemNum
);

/** WdgTabAddToTopMost
* @brief        Add widget to top most of tab widget
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    pIWidget          The widget will be added to top most of tab widget
* @param[in]    pThis            IBase widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgTabAddToTopMost
(
    IWidget                 *pWDGTab,
    IWidget                 *pIWidget,
    IBase                   *pThis
);

/** WdgTabSetFocusIndex
* @brief        Set Tab widget Focus Index
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nIndex            The index of focused element
*
* @retval       None
*
*/
__INLINE void WdgTabSetFocusIndex
(
    IWidget                 *pWDGTab,
    u32                     nIndex
)
{
    WdgCommonSetProperty(pWDGTab, PROP_FOCUS_INDEX, (u32)nIndex);
}

/** WdgTabSetFCSItemBGImage
* @brief        Set Tab Widget the background picture of highlighted item
*
* @param[in]    pWDGTab  The pointer of IWidget interface object
* @param[in]    pFCSItemBGImage   The background picture of highlighted item
*
* @retval      void
*
*/
__INLINE void WdgTabSetFCSItemBGImage
(
    IWidget                 *pWDGTab,
    IImage                  *pFCSItemBGImage
)
{
    WdgCommonSetProperty(pWDGTab, PROP_FCS_ITEM_BG_IMAGE, (u32)pFCSItemBGImage);
}

/** WdgTabSetUnFcsItemBGImage
* @brief        Set the background image for unfocused item widget
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    pImage            An image object pointer.
*
* @retval       None
*
*/
__INLINE void WdgTabSetUnFcsItemBGImage
(
    IWidget                 *pWDGTab,
    IImage                  *pImage
)
{
    WdgCommonSetProperty(pWDGTab, PROP_UNFCS_ITEM_BG_IMAGE, (u32)pImage);
}

/** WdgTabSetTabMode
* @brief        Set tabwidget's mode.
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nMode             A kind of tabwidget mode: refer to TabWdgMode_e.
*                                 You can set TAB_WDG_MODE_TOP_IMAGETEXT, TAB_WDG_MODE_TOP_IMAGE_ONLY,
*                                 TAB_WDG_MODE_TOP_TEXT_ONLY or TAB_WDG_MODE_BOTTOM_IMAGE_RING.
*
* @retval       None
*
*/
__INLINE void WdgTabSetMode
(
    IWidget                 *pWDGTab,
    TabWdgMode_e            nMode
)
{
    WdgCommonSetProperty(pWDGTab, PROP_TABWDG_MODE, (u32)nMode);
}

/** WdgTabSetActiveWidth
* @brief        Set active tab's width
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nWidth            Active tab's width in pixels.
*
* @retval       None
*
*/
__INLINE void WdgTabSetActiveWidth
(
    IWidget                 *pWDGTab,
    u16                     nWidth
)
{
    WdgCommonSetProperty(pWDGTab, PROP_TABWDG_ACTIVE_WIDTH, (u32)nWidth);
}

/** WdgTabSetInactiveWidth
* @brief        Set inactive tab's width
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nWidth            Inactive tab's width in pixels.
*
* @retval       None
*
*/
__INLINE void WdgTabSetInactiveWidth
(
    IWidget                 *pWDGTab,
    u32                     nWidth
)
{
    WdgCommonSetProperty(pWDGTab, PROP_TABWDG_INACTIVE_WIDTH, (u32)nWidth);
}

/** WdgTabSetTabHeight
* @brief        Set all tab's height
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nHeight           Tab's height in pixels.
*
* @retval       None
*
*/
__INLINE void WdgTabSetTabHeight
(
    IWidget                 *pWDGTab,
    u32                     nHeight
)
{
    WdgCommonSetProperty(pWDGTab, PROP_TABWDG_TAB_HEIGHT, (u32)nHeight);
}

/** WdgTabSetTabHeightOffset
* @brief        Set the height difference of Active and Inactive tab.
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nOffset           Tab's height offset in pixels.
*
* @retval       None
*
*/
__INLINE void WdgTabSetTabHeightOffset
(
    IWidget                 *pWDGTab,
    u16                     nOffset
)
{
    WdgCommonSetProperty(pWDGTab, PROP_TABWDG_TAB_HEIGHT_OFFSET, (u32)nOffset);
}

/** WdgTabSetTabPaddingLeft
* @brief        Set all tab's padding left
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nPaddingLeft      Tab widget padding left
*
* @retval       None
*
*/
__INLINE void WdgTabSetTabPaddingLeft
(
    IWidget                 *pWDGTab,
    u8                      nPaddingLeft
)
{
    WdgCommonSetProperty(pWDGTab, PROP_TABWDG_TAB_LEFT_PADDING, (u32)nPaddingLeft);
}

/** WdgTabSetTabPaddingRight
* @brief        Set all tab's padding right
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nPaddingRight     Tab widget padding right
*
* @retval       None
*
*/
__INLINE void WdgTabSetTabPaddingRight
(
    IWidget                 *pWDGTab,
    u8                      nPaddingRight
)
{
    WdgCommonSetProperty(pWDGTab, PROP_TABWDG_TAB_RIGHT_PADDING, (u32)nPaddingRight);
}

/** WdgTabSetTabGap
* @brief        Set all tab's tab gap
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    nTabGap           Column gap in pixel between every item.
*
* @retval       None
*
*/
__INLINE void WdgTabSetTabGap
(
    IWidget                 *pWDGTab,
    u16                     nTabGap
)
{
    WdgCommonSetProperty(pWDGTab, PROP_TABWDG_TAB_GAP, (u32)nTabGap);
}

/** WdgTabSetDisableHandleKeyEvt
* @brief        Disable Handle Hot Key Event, For Handle Left and Right Hot Key
*               If set disable, you can't change tab by Left or Right Key anymore.
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    bDisable          Handle key event disable on / off
*
* @retval       None
*
*/
__INLINE void WdgTabSetDisableHandleKeyEvt
(
    IWidget                 *pWDGTab,
    boolean                 bDisable
)
{
    WdgCommonSetProperty(pWDGTab, PROP_DISABLE_HANDLE_KEY_EVT, (u32)bDisable);
}

/** WdgTabGetFocusIndex
* @brief        Get Tab widget's focus index
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @retval       The focused index
*
*/
u32 WdgTabGetFocusIndex
(
    IWidget                 *pWDGTab
);

/** WdgTabGetMode
* @brief        Get tabwidget's mode
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[out]   pMode             A kind of tabwidget mode, refer to TabWdgMode_e.
*                                 You can get TAB_WDG_MODE_TOP_IMAGETEXT, TAB_WDG_MODE_TOP_IMAGE_ONLY,
*                                 TAB_WDG_MODE_TOP_TEXT_ONLY or TAB_WDG_MODE_BOTTOM_IMAGE_RING.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTabGetMode
(
    IWidget                 *pWDGTab,
    TabWdgMode_e            *pMode
)
{
    return WdgCommonGetProperty(pWDGTab, PROP_TABWDG_MODE, (u32*)pMode);
}

/** WdgTabGetActiveWidth
* @brief        Get active tab's width
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @retval       Width             Active tab's width in pixels.
*
*/
u32 WdgTabGetActiveWidth
(
    IWidget                 *pWDGTab
);

/** WdgTabGetInactiveWidth
* @brief        Get inactive tab's width
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @retval       Width             Inactive tab's width in pixels.
*
*/
u32 WdgTabGetInactiveWidth
(
    IWidget                 *pWDGTab
    //u32                     *pWidth
);

/** WdgTabGetTabHeight
* @brief        Get active tab's height
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @return       Active tab's height
*
*/
u32 WdgTabGetTabHeight
(
    IWidget                 *pWDGTab
);

/** WdgTabGetTabHeightOffset
* @brief        Get all tab's height offset
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @retval       Offset            Tab's height offset in pixels.
*
*/
u32 WdgTabGetTabHeightOffset
(
    IWidget                 *pWDGTab
);

/** WdgTabGetTabPaddingLeft
* @brief        Get all tab's padding left
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @return       Tab widget padding left
*
*/
u8 WdgTabGetTabPaddingLeft
(
    IWidget                 *pWDGTab
);

/** WdgTabGetTabPaddingRight
* @brief        Get all tab's padding right
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @retval       PaddingRight      Tab widget padding right
*
*
*/
u8 WdgTabGetTabPaddingRight
(
    IWidget                 *pWDGTab
);

/** WdgTabGetTabGap
* @brief        Get all tab's tab gap
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @retval       TabGap            Column gap in pixel between every item.
*
*
*/
u16 WdgTabGetTabGap
(
    IWidget               *pWDGTab
);

/** WdgTabGetDisableHandleKeyEvt
* @brief        Get tab widget's handle key event on / off
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
*
* @retval       Disable           Handle key event disable on / off
*
*/
boolean WdgTabGetDisableHandleKeyEvt
(
    IWidget                 *pWDGTab
);

/** WdgTabGetComponentWidget
* @brief        Get tab widget's component widget
*
* @param[in]    pWDGTab           The pointer of IWidget interface object
* @param[in]    pThis            IBase widget
*
* @retval       Tab widget's component widget
*
*/
//Not appropriate API: Need Check
__INLINE IWidget* WdgTabGetComponentWidget
(
    IWidget               *pWDGTab,
    IBase                 *pThis
)
{
    return WdgCommonGetComponet(pWDGTab, PROP_TABWDG_COMP_WDG_SHEET);
}

/** WdgTabRegisterTabChangeCb
* @brief        Register callback : For Tab widget, CB will be triggered when tab focus changes.
*
* @param[in]    pWDGTab           The tab widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgTabRegisterTabChangeCb
(
    IWidget                 *pWDGTab,
    PfnWdgTabTabChange      pfn,
    void                    *pUserData
);

/** WdgTabDeregisterTabChangeCb
* @brief        Deregister callback
*
* @param[in]    pWDGTab           The tab widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgTabDeregisterTabChangeCb
(
    IWidget                 *pWDGTab,
    PfnWdgTabTabChange      pfn,
    void                    *pUserData
);


#endif /* __MMI_WDG_TAB_H__ */
/*=============================================================*/
// end of file
