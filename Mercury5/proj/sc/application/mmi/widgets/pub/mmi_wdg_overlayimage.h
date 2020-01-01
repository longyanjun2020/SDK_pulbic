/**
* @file    mmi_wdg_overlayimage.h
*/
#ifndef __MMI_WDG_OVERLAYIMAGE_H__
#define __MMI_WDG_OVERLAYIMAGE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"

#include "mmi_wdg_image.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define OVERLAY_ICON_NUM    9

/** WdgOverlayIcon_t
*
* @brief    eAlign:         The alignment must be one of nine positions {ALIGN_H_LEFT, ALIGN_H_RIGHT, ALIGN_H_CENTER} X {ALIGN_V_TOP, ALIGN_V_BOTTOM, ALIGN_V_MIDDLE}
*           nImgID:         The display overlay image icon.
*
*/
typedef struct  
{
    WdgAlignment_e eAlign;
    u32 nImgID;
} WdgOverlayIcon_t;

/** WdgOverlayImageDataID_t
*
* @brief    nBaseImg:       The base image.
*           aIcon:          The overlay image icons of nine corner on top of base image.
*
*/
typedef struct 
{
    u32 nBaseImg;
    WdgOverlayIcon_t aIcon[OVERLAY_ICON_NUM];
} WdgOverlayImageDataID_t;

/*=============================================================*/
// functions
/*=============================================================*/

/** WdgOverlayImageCreateForWnd
* @brief        OverlayImage widget create function for Window
*
* @param[in]    hWin           The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
* @param[in]    eStyle         The image widget style
* @param[in]    pData          Image widget Common Data, refer to WdgImageConfigData_t.
*                              If set pScaleRotate = NULL : means you want Default Value;
*
* @retval       The pointer of Image   Success.
* @retval       NULL                   Failed.
*
*/
IWidget* WdgOverlayImageCreateForWnd
(
    HWIN                    hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    ImageStyle_e            eStyle,
    WdgImageConfigData_t    *pData
);

/** WdgOverlayImageCreate
* @brief        Create OverlayImage widget
*
* @param[in]    eImageStyle    ImageWidget initial style
*
* @retval       The pointer of Image    Success.
* @retval       NULL                    Failed.
*
*/
IWidget* WdgOverlayImageCreate(ImageStyle_e eStyle);

/** WdgOverlayImageSetIconByID
* @brief        Set overlay icon by image id. 
*               and the drawing order depends on the order of adding 
*               and the duplicated alignment icon would cover original one
*               and it would remove overlay icon when given IMG_NULL_ID
*
* @param[in]    pWDGOverlayImage    The instance of widget "Owner"(AP instance)
* @param[in]    eAlign              The one of nine alignment.
* @param[in]    nImageID            The overlay image icon.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgOverlayImageSetIconByID(IWidget *pWDGOverlayImage, WdgAlignment_e eAlign, u32 nImageID);

/** WdgOverlayImageClear
* @brief        Clear all overlay image icon
*
* @param[in]    pWDGOverlayImage    The instance of widget "Owner"(AP instance)
* @param[in]    eAlign              The one of nine alignment.
* @param[in]    nImageID            The overlay image icon.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgOverlayImageClear(IWidget *pWDGOverlayImage);


/** WdgOverlayImageSetDataByID
* @brief      The drawing order depends on given by user.
*             and alignment must be unique, or the second one would cover the first one
*             and it ends of drawing when nImgID is IMG_NULL_ID
*             and it would clear all overlay image icons at first, and then draw each overlay image icon given by pDataID
*
* @param[in]  pWDGOverlayImage      The instance of widget "Owner"(AP instance)
* @param[in]  pDataID               OverlayImage widget Common Data, refer to WdgOverlayImageDataID_t.
*
*/
MAE_Ret WdgOverlayImageSetDataByID(IWidget *pWDGOverlayImage, WdgOverlayImageDataID_t *pDataID);

#endif //__MMI_WDG_OVERLAYIMAGE_H__
/*=============================================================*/
// end of file
