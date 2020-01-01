#ifndef __MMI_WDG_BASICBITMAP_H__
#define __MMI_WDG_BASICBITMAP_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*    Basic bitmap widget is a widget for drawing some basic graphic like line, rectangle,
*    circle. The default brush and filled color of basic bitmap widget is RGBCOLOR_BLACK
*    and graphic type is WDG_BASIC_BITMAP_NONE (NOTICE: it means that nothing will be
*    draw). Application can change the widget graphic type by setting property
*    "PROP_BASICBMP_WDG_GRAPHIC_TYPE". It also can be set the filled color,
*    brush type, rotate type, and so on.
*
*/


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_headers.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/**
* @brief   enum to define basic graphic type.
*/
enum
{
    WDG_BASIC_BITMAP_NONE,                 ///Empty graphic widget
    WDG_BASIC_BITMAP_VLINE,                ///Vertical line graphic widget 
    WDG_BASIC_BITMAP_HLINE,                ///Horizontal line graphic widget
    WDG_BASIC_BITMAP_SLINE,                ///Slash line graphic widget
    WDG_BASIC_BITMAP_RSLINE,               ///Reserve slash line graphic widget 
    WDG_BASIC_BITMAP_RECTANGLE,            ///Rectangle graphic widget
    WDG_BASIC_BITMAP_CIRCLE                ///Circle graphic widget
};

typedef u8 Wdg_BasicBitmapGraphicType_et;

/**
* @brief   enum to define rotataion.
*/
enum
{
    WDG_BASIC_BITMAP_ROTATE_0,             ///Rotate 0 degree
    WDG_BASIC_BITMAP_ROTATE_90,            ///Rotate 90 degree
    WDG_BASIC_BITMAP_ROTATE_180,           ///Rotate 180 degree
    WDG_BASIC_BITMAP_ROTATE_270            ///Rotate 270 degree
};

typedef u8 Wdg_BasicBitmapRotateType_et;

/**
* @brief   enum to define brush type.
*/
enum
{
    WDG_BASIC_BITMAP_BRUSH_NORMAL,         ///Normal(Small) brush
    WDG_BASIC_BITMAP_BRUSH_SIZE_2,         ///
    WDG_BASIC_BITMAP_BRUSH_MEDIUM,         ///Medium brush
    WDG_BASIC_BITMAP_BRUSH_LARGE,          ///Large brush
    WDG_BASIC_BITMAP_BRUSH_MAX_NUM         ///Max brush number
};

typedef u8 Wdg_BasicBitmapBrushType_et;


/** WdgBasicBitmapConfigData_t
*
* @brief    tGraphicType:   Graphic type we want to draw. ex, Vertical Line, Horizontal Line, Slash Line, Rectangle, and Circle.
*           tBrushType:     Brush Type, Normal brush : 1 pixel, Medium brush : 3 pixel, Large brush : 5 pixels.
*           tRotateType:    The graphic rotation type. (0, 90, 180, 270 degree)
*           tLineColor:     The graphic brush color.
*           bFilled:        The graphic be filled with color.
*           tFilledColor:   The filled color.
*
*/
typedef struct
{
    Wdg_BasicBitmapGraphicType_et   tGraphicType;
    Wdg_BasicBitmapBrushType_et     tBrushType;
    Wdg_BasicBitmapRotateType_et    tRotateType;
    RGBColor_t                      tLineColor;
    boolean                         bFilled;
    RGBColor_t                      tFilledColor;
}WdgBasicBitmapConfigData_t;


/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgBasicBitmapWidgetSizeChange
* @brief      CB register by "WdgBasicBitmapRegisterSizeChangeCb"
*             and will be trigger when the size of widget is changed; Ex,WdgCommonSetSize
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pWidgetSize       The size be changed of widget, refer to WidgetSize_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgBasicBitmapWidgetSizeChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, WidgetSize_t *pWidgetSize, IWidget *pIWidget);

/*=============================================================*/
/** WdgBasicBitmapCreateForWnd
* @brief        Basic Bitmap widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    pData               Widget Common Data, refer to WdgBasicBitmapConfigData_t.
*                                   If set pSize = NULL : means you want Default Value;
*
* @retval       The pointer of Basic Bitmap     Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgBasicBitmapCreateForWnd
(
    HWIN                   		  hWin,
    Pos_t                         *pPos,
    WidgetSize_t                  *pSize,
    u16                           nWidgetID,
    WdgBasicBitmapConfigData_t    *pData
);
/*=============================================================*/
/** WdgBasicBitmapCreate
* @brief        Create BasicBitmap widget
*
* @retval       The pointer of BasicBitmap     Success.
* @retval       NULL                       Failed.
*
*/
IWidget* WdgBasicBitmapCreate
(
    void
);


/** WdgBasicBitmapSetLineColor
* @brief         Set Basic Bitmap widget's line color
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be set
* @param[in]     tLineColor        The line color which will be set to the basic bitmap widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgBasicBitmapSetLineColor
(
    IWidget                 *pWDGBasicBitmap,
    RGBColor_t              tLineColor
);

/** WdgBasicBitmapSetBrushType
* @brief         Set Basic Bitmap widget's brush type
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be set
* @param[in]     tBrushType        The brush type which will be set to the basic bitmap widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgBasicBitmapSetBrushType
(
    IWidget                     *pWDGBasicBitmap,
    Wdg_BasicBitmapBrushType_et tBrushType
);

/** WdgBasicBitmapSetFilledStatus
* @brief         Set Basic Bitmap widget to be filled or not
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be set
* @param[in]     bFilled           The filled status which will be set to the basic bitmap widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgBasicBitmapSetFilledStatus
(
    IWidget                 *pWDGBasicBitmap,
    boolean                 bFilled
);

/** WdgBasicBitmapSetFilledColor
* @brief         Set Basic Bitmap widget's filled color
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be set
* @param[in]     tFilledColor      The filled color which will be set to the basic bitmap widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgBasicBitmapSetFilledColor
(
    IWidget                 *pWDGBasicBitmap,
    RGBColor_t              tFilledColor
);

/** WdgBasicBitmapSetRotateType
* @brief         Set Basic Bitmap widget's rotate type
*                PS: This API is only supported if the widget is added in an AbsContainer or View.
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be set
* @param[in]     tRotateType       The rotate type which will be set to the basic bitmap widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgBasicBitmapSetRotateType
(
    IWidget                         *pWDGBasicBitmap,
    Wdg_BasicBitmapRotateType_et    tRotateType
);

/** WdgBasicBitmapSetGraphicType
* @brief         Set Basic Bitmap widget's graphic type
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be set
* @param[in]     tGraphicType      The graphic type which will be set to the basic bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapSetGraphicType
(
    IWidget                         *pWDGBasicBitmap,
    Wdg_BasicBitmapGraphicType_et   tGraphicType
);

/** WdgBasicBitmapGetLineColor
* @brief         Get Basic Bitmap widget's line color
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be gotten
* @param[out]    pLineColor        The line color which will be gotten from the basic bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapGetLineColor
(
    IWidget                 *pWDGBasicBitmap,
    RGBColor_t              *pLineColor
);

/** WdgBasicBitmapGetBrushType
* @brief         Get Basic Bitmap widget's brush type
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be gotten
* @param[out]    pBrushType        The brush type which will be gotten from the basic bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapGetBrushType
(
    IWidget                     *pWDGBasicBitmap,
    Wdg_BasicBitmapBrushType_et *pBrushType
);

/** WdgBasicBitmapGetFilledStatus
* @brief         Get Basic Bitmap widget's filled status
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be gotten
* @param[out]    pFilled           The filled status which will be gotten from the basic bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapGetFilledStatus
(
    IWidget                 *pWDGBasicBitmap,
    boolean                 *pFilled
);

/** WdgBasicBitmapGetFilledColor
* @brief         Get Basic Bitmap widget's filled color
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be gotten
* @param[out]    pFilledColor      The filled color which will be gotten from the basic bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapGetFilledColor
(
    IWidget                 *pWDGBasicBitmap,
    RGBColor_t              *pFilledColor
);

/** WdgBasicBitmapGetRotateType
* @brief         Get Basic Bitmap widget's rotate type
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be gotten
* @param[out]    pRotateType       The rotate type which will be gotten from the basic bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapGetRotateType
(
    IWidget                         *pWDGBasicBitmap,
    Wdg_BasicBitmapRotateType_et    *pRotateType
);

/** WdgBasicBitmapGetGraphicType
* @brief         Get Basic Bitmap widget's graphic type
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to be gotten
* @param[out]    pGraphicType      The graphic type which will be gotten from the basic bitmap widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapGetGraphicType
(
    IWidget                         *pWDGBasicBitmap,
    Wdg_BasicBitmapGraphicType_et   *pGraphicType
);

/** WdgBasicBitmapRegisterSizeChangeCb
* @brief         Register size change callback; CB will be triggered if widget size changed.
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]    pUserData           User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapRegisterSizeChangeCb
(
    IWidget                             *pWDGBasicBitmap,
    PfnWdgBasicBitmapWidgetSizeChange   pfn,
    void                                *pUserData
);

/** WdgBasicBitmapDeregisterSizeChangeCb
* @brief         Deregister size change callback.
*
* @param[in]     pWDGBasicBitmap   The basic bitmap widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]    pUserData           User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgBasicBitmapDeregisterSizeChangeCb
(
    IWidget                             *pWDGBasicBitmap,
    PfnWdgBasicBitmapWidgetSizeChange   pfn,
    void                                *pUserData
);

#endif //__MMI_WDG_BASICBITMAP_H__
/*=============================================================*/
// end of file
