#ifndef __MMI_WDG_IMAGE_DOUBLEITEM_H__
#define __MMI_WDG_IMAGE_DOUBLEITEM_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*     Image-Double-Item widget is developed to be a combined widget for the needs.
*     It usually is used to display in List or YES/NO selection for users. It is composed of
*     three widgets, up widget, down widget, and head widget (as below illustrated).
*     There are three types of this widget: Image_Double-Text, Image_Text-Image_Text,
*     and Image_Text-Image_Text-Image, introduced in the type and define section.
*
*
*    ex: Image-Double-Item widget
*    -------------------------------------------
*    |  ---------------------------------------|
*    | |         | | UpperItem               | |      IMG:       head widget
*    | | IMG     | --------------------------- |      UpperItem: up widget
*    | |         | | DownItem                | |      DownItem:  down widget
*    |  ---------------------------------------|
*    -------------------------------------------
*/

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


/*=============================================================*/
// type and define
/*=============================================================*/

/** ImageDoubleItemStyle_e
 *
 *  @brief      ImageDoubleItem styles as below:
 *
 *  IMAGEDOUBLEITEM_STYLE_DOUBLE_TEXT:
 *  --------------------------------------------
 *  |  --------------------------------------- |
 *  | |         | | Text                      ||
 *  | | IMG     | ---------------------------- |
 *  | |         | | Text                      ||
 *  |  --------------------------------------- |
 *  --------------------------------------------
 *
 *
 *  IMAGEDOUBLEITEM_STYLE_TITEXT
 *  ---------------------------------------------
 *  |  ---------------------------------------- |
 *  | |           | | Text1             | IMG2 ||
 *  | | IMG1      | --------------------------- |
 *  | |           | | Text2                    ||
 *  |  ---------------------------------------- |
 *  ---------------------------------------------
 *
 *
 *  IMAGEDOUBLEITEM_STYLE_TITI
 *  -------------------------------------------
 *  |  -------------------------------------- |
 *  | |           | | Text1           | IMG2 ||
 *  | | IMG1      | ------------------------- |
 *  | |           | | Text2           | IMG3 ||
 *  |  -------------------------------------- |
 *  -------------------------------------------
 *
 */
typedef enum
{
    IMAGEDOUBLEITEM_STYLE_DOUBLE_TEXT,
    IMAGEDOUBLEITEM_STYLE_TITEXT,
    IMAGEDOUBLEITEM_STYLE_TITI
} ImageDoubleItemStyle_e;

/** ImageDoubleItemInfo
*
* @brief    pPreImage:          IImage pointer for PreImage widget
*           pPostUpperItem:     Data pointer for UpperItem widget.
*           pPostDownItem:      Data pointer for DownItem widget.
*
*/
typedef struct {
	IImage 	*pPreImage;			
	void 	*pPostUpperItem;	
	void 	*pPostDownItem;		
} ImageDoubleItemInfo;

/** Image_DoubleText_Info_st
*
* @brief    pPreImage:          IImage pointer for PreImage widget
*           pStr1:              
*           pStr2:              
*
*/
typedef struct {
	IImage *pPreImage;
	MAE_WChar *pStr1;
	MAE_WChar *pStr2;
} Image_DoubleText_Info_st;

/** Image_TextImage_Text_Info_st
*
* @brief    pPreImage:          IImage pointer for PreImage widget
*           pTextImageInfo:              
*           pStr:              
*
*/
typedef struct {
	IImage *pPreImage;
	TextImageInfo_st *pTextImageInfo;
	MAE_WChar *pStr;
} Image_TextImage_Text_Info_st;

/** Image_TextImage_TextImage_Info_st
*
* @brief    pPreImage:          IImage pointer for PreImage widget
*           pTextImageInfo1:              
*           pTextImageInfo2:              
*
*/
typedef struct {
	IImage *pPreImage;
	TextImageInfo_st *pTextImageInfo1;
	TextImageInfo_st *pTextImageInfo2;
} Image_TextImage_TextImage_Info_st;

/* Child widget*/
typedef enum
{
	IMGDOUBLEITEMWIDGET_PRE_IMG_WIDGET,
	IMGDOUBLEITEMWIDGET_POST_UPPER_WIDGET,
	IMGDOUBLEITEMWIDGET_POST_DOWN_WIDGET,
}ImgDoubleItemWidgetChildWidget_e;

/** WdgImageDoubleItemConfigData_t
*
* @brief    pSize:          Size and visible of widget.
*
*/
typedef struct
{
    WidgetSize_t            *pSize;
}WdgImageDoubleItemConfigData_t;


/** WdgImageDoubleItemDoubleText_t
*
* @brief    For setting data by ID to IMAGEDOUBLEITEM_STYLE_DOUBLE_TEXT.
*
*           nImgID:          Item image ID
*           nStr1ID:         Item text-1 ID     
*           nStr2ID:         Item text-2 ID
*
*/
typedef struct
{
   u32  nImgID;
   u32  nStr1ID;
   u32  nStr2ID; 
}WdgImageDoubleItemDoubleText_t;

/** WDG_DoubleItem_TIT
*
* @brief    For setting data by ID to IMAGEDOUBLEITEM_STYLE_TITEXT.
*
*/

/** WdgImageDoubleItemTextInfo_t
*
* @brief    For setting data by ID to IMAGEDOUBLEITEM_STYLE_TITEXT.
*
*           nImg1ID:          Item image-1 ID
*           nStr1ID:          Item text-1 ID
*           nImg2ID:          Item image-2 ID
*           nStr2ID:          Item text-2 ID
*
*/
typedef struct
{
   u32  nImg1ID;
   u32  nStr1ID;
   u32  nImg2ID; 
   u32  nStr2ID;
}WdgImageDoubleItemTextInfo_t;

/** WdgImageDoubleItemTextImgInfo_t
*
* @brief    For setting data by ID to IMAGEDOUBLEITEM_STYLE_TITI.
*
*           nImg1ID:          Item image-1 ID
*           nStr1ID:          Item text-1 ID
*           nImg2ID:          Item image-2 ID
*           nStr2ID:          Item text-2 ID
*           nImg3ID:          Item image-3 ID
*
*/
typedef struct
{
   u32  nImg1ID;
   u32  nStr1ID;
   u32  nImg2ID;
   u32  nStr2ID;
   u32  nImg3ID;
}WdgImageDoubleItemTextImgInfo_t;

/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgImageDoubleItemWidgetDataChange
* @brief      CB register by "WdgImageDoubleItemRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgImageDoubleItemWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pIWidget);

/*=============================================================*/
/** WdgImageDoubleItemCreateForWnd
* @brief        ImageDoubleItem widget create function for Window
*
* @param[in]    hWin         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    eStyle          The image double item widget style
*
* @retval       The pointer of ImageDoubleItem  Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgImageDoubleItemCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    ImageDoubleItemStyle_e  eStyle
);
/*=============================================================*/
/** WdgImageDoubleItemCreate
* @brief        Create Image Double Item widget
*
* @param[in]    eStyle                  ImageDoubleItem initial style
*
* @retval       The pointer of ImageDoubleItem  Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgImageDoubleItemCreate
(
    ImageDoubleItemStyle_e  eStyle
);

/** WdgImageDoubleItemDBTextSetData
* @brief        Set display data for IMAGEDOUBLEITEM_STYLE_DOUBLE_TEXT style ImageDoubleItem widget.
*               Specific data for ImageDoubleItem widget.
*
* @param[in]    pWDGImageDoubleItem  Pointer to the ImageDoubleItem widget
* @param[in]    pDispData            Display data of ImageDoubleItem Widget, refer to Image_DoubleText_Info_st.
* @param[in]    pfFree               Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgImageDoubleItemDBTextSetData
(
    IWidget                         *pWDGImageDoubleItem,
    Image_DoubleText_Info_st        *pDispData,
    PfnDataFree                     pfFree
);

/** WdgImageDoubleItemDBTextSetDataByID
* @brief        Set display data by resource ID for IMAGEDOUBLEITEM_STYLE_DOUBLE_TEXT
*                  style ImageDoubleItem widget. Specific data for DoubleItem widget.
*
* @param[in]    pWDGImageDoubleItem  Pointer to the ImageDoubleItem widget
* @param[in]    pDispData            Display data of ImageDoubleItem Widget, refer to WdgImageDoubleItemDoubleText.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgImageDoubleItemDBTextSetDataByID
(
    IWidget                         *pWDGImageDoubleItem,
    WdgImageDoubleItemDoubleText_t  *pDispData
);

/** WdgImageDoubleItemTITEXTSetData
* @brief        Set display data for IMAGEDOUBLEITEM_STYLE_TITEXT style ImageDoubleItem widget.
*               Specific data for ImageDoubleItem widget.
*
* @param[in]    pWDGImageDoubleItem  Pointer to the ImageDoubleItem widget
* @param[in]    pDispData            Display data of ImageDoubleItem Widget, refer to Image_TextImage_Text_Info_st.
* @param[in]    pfFree               Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgImageDoubleItemTITEXTSetData
(
    IWidget                         *pWDGImageDoubleItem,
    Image_TextImage_Text_Info_st    *pDispData,
    PfnDataFree                     pfFree
);

/** WdgImageDoubleItemTITEXTSetDataByID
* @brief        Set display data by resource ID for IMAGEDOUBLEITEM_STYLE_TITEXT style ImageDoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGImageDoubleItem  Pointer to the ImageDoubleItem widget
* @param[in]    pDispData            Display data of ImageDoubleItem Widget, refer to WdgImageDoubleItemTextInfo.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgImageDoubleItemTITEXTSetDataByID
(
    IWidget                         *pWDGImageDoubleItem,
    WdgImageDoubleItemTextInfo_t    *pDispData
);

/** WdgImageDoubleItemTITISetData
* @brief        Set display data for IMAGEDOUBLEITEM_STYLE_TITI style ImageDoubleItem widget.
*               Specific data for ImageDoubleItem widget.
*
* @param[in]    pWDGImageDoubleItem  Pointer to the ImageDoubleItem widget
* @param[in]    pDispData            Display data of ImageDoubleItem Widget, refer to Image_TextImage_TextImage_Info_st.
* @param[in]    pfFree               Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgImageDoubleItemTITISetData
(
    IWidget                             *pWDGImageDoubleItem,
    Image_TextImage_TextImage_Info_st   *pDispData,
    PfnDataFree                         pfFree
);

/** WdgImageDoubleItemTITISetDataByID
* @brief        Set display data by resource ID for IMAGEDOUBLEITEM_STYLE_TITI style ImageDoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGImageDoubleItem  Pointer to the ImageDoubleItem widget
* @param[in]    pDispData            Display data of ImageDoubleItem Widget, refer to WdgImageDoubleItemTextImgInfo.
*
* @retval       MAE_RET_SUCCESS      Success
* @retval       others               Failed
*
*/
MAE_Ret WdgImageDoubleItemTITISetDataByID
(
    IWidget                             *pWDGImageDoubleItem,
    WdgImageDoubleItemTextImgInfo_t     *pDispData
);

void WdgImageDoubleItemSetFocusOnChildWidget
(
    IWidget                             *pWDGImageDoubleItem,
    ImgDoubleItemWidgetChildWidget_e    eChildWidget
);

/** WdgImageDoubleItemSetLayoutStyle
* @brief        Set the widget layout vertical, horizontal or ...
*
* @param[in]    pWDGImageDoubleItem           The image double item widget which want to be set
* @param[in]    nLayoutStyle      Layout Style, refer to WdgLayoutStyle_t.
*                                  Ex, LAYOUT_STYLE_VERTICAL   ==> Vertical layout style
*                                     LAYOUT_STYLE_HORIZONTAL ==> Horizontal layout style
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
void WdgImageDoubleItemSetLayoutStyle
(
    IWidget             *pWDGImageDoubleItem,
    WdgLayoutStyle_t    nLayoutStyle
);

/** WdgImageDoubleItemSetEnableAnimate
* @brief        Turn on/off animation to widget
*
* @param[in]    pWDGImageDoubleItem  Pointer to the ImageDoubleItem widget
* @param[in]    bEnableAnimate       TRUE, turn on,
*                                    FALSE, turn off.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
void WdgImageDoubleItemSetEnableAnimate
(
    IWidget                 *pWDGImageDoubleItem,
    boolean                 bEnableAnimate
);

/** WdgImageDoubleItemGetPreImageWidget
* @brief        Get Image Double Item widget's pre image widget
*
* @param[in]    pWDGImageDoubleItem The image double item widget which want to be gotten
*
* @retval       The pre image widget
*
*/
IWidget* WdgImageDoubleItemGetPreImageWidget
(
    IWidget                 *pWDGImageDoubleItem
);

/** WdgImageDoubleItemGetPostUpperItemWidget
* @brief        Get Image Double Item widget's post upper item widget
*
* @param[in]    pWDGImageDoubleItem     The image double item widget which want to be gotten
*
* @retval       The post upper item widget
*
*/
IWidget* WdgImageDoubleItemGetPostUpperItemWidget
(
    IWidget                 *pWDGImageDoubleItem
);

/** WdgImageDoubleItemGetPostDownItemWidget
* @brief        Get Image Double Item widget's post down item widget
*
* @param[in]    pWDGImageDoubleItem     The image double item widget which want to be gotten
*
* @retval       The post down item widget
*
*/
IWidget* WdgImageDoubleItemGetPostDownItemWidget
(
    IWidget               *pWDGImageDoubleItem
);

/** WdgImageDoubleItemGetLayoutStyle
* @brief        Get the widget layout vertical or horizontal.
*
* @param[in]    pWDGImageDoubleItem     The image double item widget which want to be set
* @param[out]   pLayoutStyle            Layout Style
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageDoubleItemGetLayoutStyle
(
    IWidget                 *pWDGImageDoubleItem,
    WdgLayoutStyle_t        *pLayoutStyle
);

/** WdgImageDoubleItemRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGImageDoubleItem  The image double item widget which want to set callback
* @param[in]    pfn                  callback function
* @param[in]    pUserData             User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageDoubleItemRegisterDataChangeCb
(
    IWidget                                     *pWDGImageDoubleItem,
    PfnWdgImageDoubleItemWidgetDataChange    pfn,
    void                                        *pUserData
);

/** WdgImageDoubleItemDeregisterDataChangeCb
* @brief        Deregister data change callback.
*
* @param[in]    pWDGImageDoubleItem  The image double item widget which want to set callback
* @param[in]    pfn                  callback function
* @param[in]    pUserData             User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageDoubleItemDeregisterDataChangeCb
(
    IWidget                                     *pWDGImageDoubleItem,
    PfnWdgImageDoubleItemWidgetDataChange    pfn,
    void                                        *pUserData
);

#endif //__MMI_WDG_IMAGE_DOUBLEITEM_H__
/*=============================================================*/
// end of file
