#ifndef __MMI_WDG_BITMAP_H__
#define __MMI_WDG_BITMAP_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*   Bitmap widget is a display of IBitmap object of a widget. Bitmap widget is used
*   with Interface model. AP add bitmap object in the Interface model, and Bitmap
*   widget is responsible for this bitmap will be displayed. Bitmap widget supports
*   alignment, and it also can set the background color, background image, Border,
*   Padding.
*
*    ex: Bitmap widget
*      --------------------------
*      |          |             |
*      |   Bitmap |   Bitmap    |  <- top / left alignment
*      |__________|             |
*      |              Widget    |
*      --------------------------
*
*/


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/** PfnWdgBitmapWidgetSizeChange
* @brief      CB register by "WdgBitmapRegisterSizeChangeCb"
*             and will be trigger when the size of widget is changed; Ex,WdgCommonSetSize
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pWidgetSize       The size be changed of widget, refer to WidgetSize_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgBitmapWidgetSizeChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, WidgetSize_t *pWidgetSize, IWidget *pIWidget);

/** PfnWdgBitmapLinkImageClick
* @brief      CB register by "WdgBitmapRegisterLinkImageClickCb"
*             and will be trigger when Image be Click; EX, Work if WdgBitmapSetLinkingText
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pNotifyWidget     The widget instance
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgBitmapLinkImageClick) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, IWidget *pNotifyWidget, IWidget *pIWidget);

/** PfnWdgBitmapWidgetDataChange
* @brief      CB register by "WdgBitmapRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Unuseful parameter
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgBitmapWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
/** WdgBitmapCreateForWnd
* @brief        Bitmap widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of Bitmap pointer     Success.
* @retval       NULL                              Failed.
*
*/
IWidget* WdgBitmapCreateForWnd
(
    HWIN        hWin,
    Pos_t              *pPos,
    WidgetSize_t       *pSize,
    u16                nWidgetID
);

/*=============================================================*/
/** WdgBitmapCreate
* @brief        Create Bitmap widget
*
* @retval       The pointer of Bitmap           Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgBitmapCreate
(
    void
);

/** WdgBitmapSetData
* @brief         Set Bitmap widget's bitmap
*                Specific data for bitmap widget.
*
* @param[in]     pWDGBitmap        The bitmap widget which want to be set
* @param[in]     pBitmap           The bitmap which will be set to the bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgBitmapSetData
(
    IWidget                 *pWDGBitmap,
    IBitmap                 *pBitmap
);

/** WdgBitmapSetDataByID
* @brief         Set Bitmap widget's bitmap by bitmap id
*                Specific data for bitmap widget.
*
* @param[in]     pWDGBitmap        The bitmap widget which want to be set
* @param[in]     nBitmapID         The bitmap ID which will be set to the bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBitmapSetDataByID
(
    IWidget                 *pWDGBitmap,
    u32                     nBitmapID
);

/** WdgBitmapSetLinkingText
* @brief         Set Bitmap widget's linking text
*                Keeping Http Address for Browser to Link WebSite
*
* @param[in]     pWDGBitmap        The bitmap widget which want to be set
* @param[in]     pLinkingText      The linking text which will be set to the bitmap widget
*
*
*/
void WdgBitmapSetLinkingText
(
    IWidget                 *pWDGBitmap,
    MAE_WChar               *pLinkingText
);

/** WdgBitmapSetLinkedState
* @brief         Set Bitmap widget's linked state
*                For Browser to identify is the address be linked
*
* @param[in]     pWDGBitmap        The bitmap widget which want to be set
* @param[in]     bLinkedState      The linked state which will be set to the bitmap widget
*
*
*/
void WdgBitmapSetLinkedState
(
    IWidget                 *pWDGBitmap,
    boolean                 bLinkedState
);

/** WdgBitmapSetAlignment
* @brief         Set Bitmap widget's alignment flag
*
* @param[in]     pWDGBitmap        The bitmap widget which want to be set
* @param[in]     eWdgAlignment     The widget alignment flag which will be set to the bitmap widget
*
*
*/
void WdgBitmapSetAlignment
(
    IWidget                 *pWDGBitmap,
    WdgAlignment_e          eWdgAlignment
);

/** WdgBitmapGetLinkingText
* @brief         Get Bitmap widget's linking text
*                Get Keeping Http Address for Browser to Link WebSite
*
* @param[in]     pWDGBitmap        The bitmap widget which want to be gotten
*
* @retval        MAE_WChar*           The linking text which will be gotten from the bitmap widget
*
*/
MAE_WChar* WdgBitmapGetLinkingText
(
    IWidget                 *pWDGBitmap
);

/** WdgBitmapGetLinkedState
* @brief         Get Bitmap widget's linked state
*                For Browser to identify is the address be linked
*
* @param[in]     pWDGBitmap        The bitmap widget which want to be gotten
*
* @retval        boolean            The linked state which will be gotten from the bitmap widget
*
*/
boolean WdgBitmapGetLinkedState
(
    IWidget                 *pWDGBitmap
);

/** WdgBitmapGetAlignment
* @brief         Get Bitmap widget's alignment flag
*
* @param[in]     pWDGBitmap        The bitmap widget which want to be gotten
* @param[out]    pWdgAlignment     The widget alignment flag which will be gotten from the bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
WdgAlignment_e WdgBitmapGetAlignment
(
    IWidget                 *pWDGBitmap
);

/** WdgBitmapRegisterSizeChangeCb
* @brief         Register size change callback; CB will be triggered if widget size changed.
*
* @param[in]     pWDGImage        The bitmap widget which want to set callback
* @param[in]     pfn              callback function
* @param[in]     pUsrData         User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS  Success
* @retval        others           Failed
*
*/
MAE_Ret WdgBitmapRegisterSizeChangeCb
(
    IWidget                         *pWDGImage,
    PfnWdgBitmapWidgetSizeChange    pfn,
    void                            *pUserData
);

#ifdef __TOUCH_SCREEN_MMI__
/** WdgBitmapRegisterLinkImageClickCb
* @brief         Register link image click callback; CB will be triggered if link image(image on website) click.
*
* @param[in]     pWDGImage        The bitmap widget which want to set callback
* @param[in]     pfn              callback function
* @param[in]     pUsrData         User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS  Success
* @retval        others           Failed
*
*/
MAE_Ret WdgBitmapRegisterLinkImageClickCb
(
    IWidget                     *pWDGImage,
    PfnWdgBitmapLinkImageClick  pfn,
    void                        *pUserData
);
#endif

/** WdgBitmapRegisterDataChangeCb
* @brief         Register the object change callback; CB will be triggered while the object has changed.
*
* @param[in]     pWDGImage         The bitmap widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBitmapRegisterDataChangeCb
(
    IWidget                         *pWDGImage,
    PfnWdgBitmapWidgetDataChange    pfn,
    void                            *pUserData
);

/** WdgBitmapDeregisterSizeChangeCb
* @brief         Deregister size change callback.
*
* @param[in]     pWDGImage         The bitmap widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBitmapDeregisterSizeChangeCb
(
    IWidget                         *pWDGImage,
    PfnWdgBitmapWidgetSizeChange    pfn,
    void                            *pUserData
);

#ifdef __TOUCH_SCREEN_MMI__
/** WdgBitmapDeregisterLinkImageClickCb
* @brief         Deregister link image click callback.
*
* @param[in]     pWDGImage         The bitmap widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBitmapDeregisterLinkImageClickCb
(
    IWidget                     *pWDGImage,
    PfnWdgBitmapLinkImageClick  pfn,
    void                        *pUserData
);
#endif

/** WdgBitmapDeregisterDataChangeCb
* @brief         Deregister the object change callback.
*
* @param[in]     pWDGImage         The bitmap widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBitmapDeregisterDataChangeCb
(
    IWidget                         *pWDGImage,
    PfnWdgBitmapWidgetDataChange    pfn,
    void                            *pUserData
);


/*! @brief This function gets bitmap from the given IBitmapWidget
 *
 *  @param pWdg     Pointer to the IBitmapWidget
 *  @param pOwner   Pointer to the object which wants to get the IBitmap
 *
 *  @return the IBitmap in the IBitmapWidget
 */
IBitmap *IBITMAPWIDGET_GetBitmap(IWidget*, IBase*);

#endif //__MMI_WDG_BITMAP_H__
/*=============================================================*/
// end of file
