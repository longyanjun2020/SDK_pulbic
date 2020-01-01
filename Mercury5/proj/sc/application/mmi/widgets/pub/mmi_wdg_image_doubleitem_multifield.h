/**
* @file    mmi_wdg_image_doubleitem_multifield.h
* @version $Id: mmi_wdg_image_doubleitem_multifield.h added $
* @brief
* @layout

IMAGE_TEXT_ITIT:

*  ------------------------------------------
*  |    ------------------------------- ------ ||
*  | |        |              TEXT              ||
*  | |IMG     ------------------------------   ||
*  | |        |    IMG  TEXT   |  IMG  TEXT    ||
*  |  -----------------------------------------||
*  ------------------------------------------
*/

/**
IMAGE_TEXT_CITT:

*  ------------------------------------------
*  |    ------------------------------- ------ ||
*  | |        |              TEXT              ||
*  | |IMG     ------------------------------   ||
*  | |        |    INDICATOR   |  IMG          ||
*  | |         --------------------------------||
*  | |        |    TEXT        |  TEXT         ||
*  |  -----------------------------------------||
*/


#ifndef __MMI_WDG_IMAGE_DOUBLEITEM_MULTIFIELD_H__
#define __MMI_WDG_IMAGE_DOUBLEITEM_MULTIFIELD_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_shell.h"
#include "mmi_mae_widget.h"
#include "mmi_wdg_image_text_image.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_mae_datamodel.h"
#include "mmi_wdg_indicator.h"

/*=============================================================*/
// type and define
/*=============================================================*/
/**
* ImageTextFourItemInfo
* Data Structure will be stored in data model.
*/
typedef struct {
	IImage 	    *pPreWdgImg;
    MAE_WChar   *pBackUpWdgText;
	IImage 	    *pBackDownFirstImgWdgImg;
	MAE_WChar   *pBackDownFirstTextWdgText;
	IImage 	    *pBackDownSecImgWdgImg;
    MAE_WChar   *pBackDownSecTextWdgText;
} ImageDoubleItemMultiFieldInfo;

typedef struct
{
    IWidget *pItemPreWdg;
	IWidget *pItemBackUpWdg;
    IWidget *pItemBackDownFirstWdg;
    IWidget *pItemBackDownSecWdg;
    IWidget *pItemBackDownThirdWdg;
    IWidget *pItemBackDownFourthWdg;
}ImageDoubleItemMultiFieldComponentWdgInfo;

/**
* ImageTextFourItemCITTInfo
* Data Structure will be stored in data model.
*/
typedef struct {
	IImage 	    *pPreWdgImg;
    MAE_WChar 	*pBackUpWdgText;
	IndicatorData_t tBackDownFirstWdgIndData;
    IImage 	    *pBackDownSecWdgImg;
    MAE_WChar   *pBackDownThirdWdgText;
    MAE_WChar   *pBackDownForthWdgText;

} ImageDoubleItemMultiFieldCITTInfo;


typedef enum
{
	IMG_DOUBLEITEM_MULTIFIELD_WIDGET_PRE_IMG_WIDGET,
	IMG_DOUBLEITEM_MULTIFIELD_WIDGET_BACKUP_WIDGET,
	IMG_DOUBLEITEM_MULTIFIELD_WIDGET_BACKDOWN_FIRST_WIDGET,
	IMG_DOUBLEITEM_MULTIFIELD_WIDGET_BACKDOWN_SECOND_WIDGET,
	IMG_DOUBLEITEM_MULTIFIELD_WIDGET_BACKDOWN_THIRD_WIDGET,
	IMG_DOUBLEITEM_MULTIFIELD_WIDGET_BACKDOWN_FOURTH_WIDGET,
}ImgDoubleItemMultiFieldWidgetChildWidget_e;
typedef enum
{
	IMAGE_TEXT_ITIT,
    IMAGE_TEXT_CITT,
}eDoubleStyle;
typedef u8 ImageDoubleItemMultiFieldStyle_e;

/*=============================================================*/
// InterFacce
/*=============================================================*/

IWidget* WdgImageDoubleItemMultiFieldCreateForWnd
(
 HWIN             hWin,
 Pos_t                   *pPos,
 WidgetSize_t            *pSize,
 u16                     nWidgetID,
 ImageDoubleItemMultiFieldStyle_e  eStyle
 );

IWidget* WdgImageDoubleItemMultiFieldCreate(ImageDoubleItemMultiFieldStyle_e eStyle);

/*=============================================================*/
// end of file
#endif//__MMI_WDG_IMAGE_TDOUBLEITEM_MULTIFIELD_H__

