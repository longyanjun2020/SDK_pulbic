/**
 * @file    mmi_wdg_image_text_image.h
 * @version $Id: mmi_wdg_image_text_image.h 16546 2008-11-17 09:41:56Z jorena.ku $
 * @brief   This file defines the interface of IIMAGETEXTIMAGEWIDGET
 *
 * @CLS ID : CLSID_IMAGETEXTIMAGEWIDGET
 *
 *   In response to the display of different information needs, we developed those 
 *   combination widgets. They are often used in the display of List. Image-Text-Image 
 *   widget, Image-Text widget and Text-Image widget are the same type of widgets, 
 *   mainly deal with image and text combinations. The sketch of these types are in the
 *   type and define section. In the layout, some properties can be set to Image-Text-Image 
 *   widget, and it can be set the Pre-Image width, Post-Image width, and the gap between 
 *   Image and Text.
 *
 *
 *       ex: Image-Text-Image widget
 *       +-------------------------------------------------------------------+
 *       |        +---------+          +--------+         +-------+          |     
 *       |  pre   |  IMG    |    pre   | Text   |   post  | IMG   |   post   |
 *       |< img > |         | < text > |        | < text >|       | < img >  |
 *       |padding +---------+  padding +--------+ padding +-------+  padding |
 *       +-------------------------------------------------------------------+
 *                |<------->|                             |<------>|
 *                pre-image width                       post-image width 
 *
 */
#ifndef __MMI_WDG_IMAGE_TEXT_IMAGE_H
#define __MMI_WDG_IMAGE_TEXT_IMAGE_H


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_common_interface.h"
#include "mmi_mae_image.h"



/*=============================================================*/
// type and define
/*=============================================================*/

enum e_ImageTextImage_Layout
{
  //Layout_ImageTextImage_Start=0x00,
  Layout_ImageTextImage_ShowAll=0x00,
  Layout_ImageTextImage_PreImageHide=0x01,
  Layout_ImageTextImage_PreImageShow=0x00,
  Layout_ImageTextImage_PreImageMask=0x01,
  Layout_ImageTextImage_TextHide=0x02,
  Layout_ImageTextImage_TextShow=0x00,
  Layout_ImageTextImage_TextMask=0x02,
  Layout_ImageTextImage_PostImageHide=0x04,
  Layout_ImageTextImage_PostImageShow=0x00,
  Layout_ImageTextImage_PostImageMask=0x04,
  Layout_ImageTextImage_Total=0x08
};

typedef enum e_ImageTextImage_Layout WdgITILayoutStyle_t;


enum e_ImageText_Layout
{  
    Layout_ImageText_ShowAll		= Layout_ImageTextImage_ShowAll,
    Layout_ImageText_PreImageHide	= Layout_ImageTextImage_PreImageHide,  
    Layout_ImageText_PreImageShow	= Layout_ImageTextImage_PreImageShow,
    Layout_ImageText_PreImageMask = Layout_ImageTextImage_PreImageMask,  
    Layout_ImageText_TextHide		= Layout_ImageTextImage_TextHide,
    Layout_ImageText_TextShow		= Layout_ImageTextImage_TextShow,  
    Layout_ImageText_TextMask		= Layout_ImageTextImage_TextMask
};


enum e_TextImage_Layout
{
    Layout_TextImage_ShowAll		= Layout_ImageTextImage_ShowAll,
    Layout_TextImage_TextHide		= Layout_ImageTextImage_TextHide,
    Layout_TextImage_TextShow		= Layout_ImageTextImage_TextShow,
    Layout_TextImage_TextMask		= Layout_ImageTextImage_TextMask,   
    Layout_TextImage_PostImageHide= Layout_ImageTextImage_PostImageHide,
    Layout_TextImage_PostImageShow= Layout_ImageTextImage_PostImageShow,
    Layout_TextImage_PostImageMask= Layout_ImageTextImage_PostImageMask
};

/** ImageTextInfo_st
*
* @brief    PreImage_Ptr:       pre image
*           WText_Ptr:          text      
*
*/
typedef struct {
    IImage      *PreImage_Ptr;
    MAE_WChar   *WText_Ptr; 
} ImageTextInfo;
typedef ImageTextInfo ImageTextInfo_st;

/** TextImageInfo_st
*
* @brief    WText_Ptr:              text
*           PostImage_Ptr:          post image
*
*/
typedef struct {
    MAE_WChar *  WText_Ptr;
    IImage *     PostImage_Ptr;
} TextImageInfo;
typedef TextImageInfo TextImageInfo_st;

/** ImageTextImageInfo_st
*
* @brief    PreImage_Ptr:       pre image
*           WText_Ptr:          text
*           PostImage_Ptr:      post image
*
*/
typedef struct {
   IImage *     PreImage_Ptr;
   MAE_WChar *  WText_Ptr;
   IImage *     PostImage_Ptr;
} ImageTextImageInfo;
typedef ImageTextImageInfo ImageTextImageInfo_st;


typedef enum
{
    ITI_STYLE_IMAGETEXTIMAGE,
    ITI_STYLE_IMAGETEXT,
    ITI_STYLE_TEXTIMAGE
} ITIStyle_e;

/** WdgITIConfigData_t
*
* @brief    pSize:          Size and visible of widget.
*           tFontCategory:  Font Category : FONT_CAT_NORMAL, FONT_CAT_LARGE...
*           nFontType:      Font Type : FONT_TYPE_NORMAL, FONT_TYPE_OUTLINE...
*           eLangDirection: Language direction : LANG_DIR_L_TO_R(Left to Right), LANG_DIR_R_TO_L.
*
*/
typedef struct
{
    WidgetSize_t            *pSize;
    FontCategory_t          tFontCategory;
    FontType_t              nFontType;
    WdgLangDirection_e      eLangDirection;
}WdgITIConfigData_t;

/** WdgITIStyleITIInfo_t
*
* @brief    nPreImageID:        pre image ID
*           nStrID:             text ID
*           nPostImageID:       post image ID
*
*/
typedef struct
{
   u32  nPreImageID;        
   u32  nStrID;             
   u32  nPostImageID;       
}WdgITIStyleITIInfo_t;

/** WdgITIStyleITInfo_t
*
* @brief    nImageID:       pre image ID
*           nStrID:         text ID     
*
*/
typedef struct
{
   u32  nImageID;
   u32  nStrID;
}WdgITIStyleITInfo_t;

/** WdgITIStyleTIInfo_t
*
* @brief    nStrID:            text ID
*           nImageID:          post image ID
*
*/
typedef struct
{
   u32  nStrID;
   u32  nImageID;  
}WdgITIStyleTIInfo_t;

/*=============================================================*/
// functions
/*=============================================================*/

/** PfnWdgITIWidgetDataChange
* @brief      CB register by "WdgITIRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgITIWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pIWidget);
/*=============================================================*/
/** WdgITICreateForWnd
* @brief        ImageTextImage widget create function for Window
*
* @param[in]    hWin           The window handle
* @param[in]    pPos              A pointer of widget position; can't be NULL.
* @param[in]    pSize             A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID         The widget unique ID of window
* @param[in]    eStyle            The imagetextimage widget style
*
* @retval       The pointer of ImageTextImage   Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgITICreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    ITIStyle_e              eStyle
);
/*=============================================================*/
/** WdgITICreate
* @brief        Create imagetextimage widget
*
* @param[in]    eStyle                  The imagetextimage widget style
*
* @retval       The pointer of imagetextimage   Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgITICreate
(
    ITIStyle_e  eStyle
);

/** WdgITIITIStyleSetData
* @brief        Set display data for ITI_STYLE_IMAGETEXTIMAGE style ImageTextImage widget.
*               Specific data for ImageTextImage widget.
*
* @param[in]    pWDGITI         Pointer to the ImageTextImage widget
* @param[in]    pDispData         Display data of ImageTextImage Widget, refer to ImageTextImageInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgITIITIStyleSetData
(
    IWidget                 *pWDGITI,
    ImageTextImageInfo_st   *pDispData,
    PfnDataFree             pfFree
);

/** WdgITIITIStyleSetDataByID
* @brief        Set display data by resource ID for ITI_STYLE_IMAGETEXTIMAGE style ImageTextImage widget.
*               Specific data for ImageTextImage widget.
*
* @param[in]    pWDGITI         Pointer to the ImageTextImage widget
* @param[in]    pDispData         Display data of ImageTextImage Widget, refer to WdgITIStyleITIInfo.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgITIITIStyleSetDataByID
(
    IWidget                 *pWDGITI,
    WdgITIStyleITIInfo_t    *pDispData
);

/** WdgITIITStyleSetData
* @brief        Set display data for ITI_STYLE_IMAGETEXT style ImageTextImage widget.
*               Specific data for ImageTextImage widget.
*
* @param[in]    pWDGITI         Pointer to the ImageTextImage widget
* @param[in]    pDispData         Display data of ImageTextImage Widget, refer to ImageTextInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgITIITStyleSetData
(
    IWidget                 *pWDGITI,
    ImageTextInfo_st        *pDispData,
    PfnDataFree             pfFree
);

/** WdgITIITStyleSetDataByID
* @brief        Set display data by resource ID for ITI_STYLE_IMAGETEXT style ImageTextImage widget.
*               Specific data for ImageTextImage widget.
*
* @param[in]    pWDGITI         Pointer to the ImageTextImage widget
* @param[in]    pDispData         Display data of ImageTextImage Widget, refer to WdgITIStyleITInfo.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgITIITStyleSetDataByID
(
    IWidget                 *pWDGITI,
    WdgITIStyleITInfo_t     *pDispData
);

/** WdgITITIStyleSetData
* @brief        Set display data for ITI_STYLE_TEXTIMAGE style ImageTextImage widget.
*               Specific data for ImageTextImage widget.
*
* @param[in]    pWDGITI         Pointer to the ImageTextImage widget
* @param[in]    pDispData         Display data of ImageTextImage Widget, refer to TextImageInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgITITIStyleSetData
(
    IWidget                 *pWDGITI,
    TextImageInfo_st        *pDispData,
    PfnDataFree             pfFree
);

/** WdgITITIStyleSetDataByID
* @brief        Set display data by resource ID for ITI_STYLE_TEXTIMAGE style ImageTextImage widget.
*               Specific data for ImageTextImage widget.
*
* @param[in]    pWDGITI         Pointer to the ImageTextImage widget
* @param[in]    pDispData         Display data of ImageTextImage Widget, refer to WdgITIStyleTIInfo.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgITITIStyleSetDataByID
(
    IWidget                 *pWDGITI,
    WdgITIStyleTIInfo_t     *pDispData
);

/** WdgITISetWidgetLayout
* @brief        Set widget layout;
*               for show/hide text or image of ImageTextImage widget.
*
* @param[in]    pWDGITI             The imagetextimage widget which want to be set
* @param[in]    nWidgetLayout       The widget layout, refer to e_ImageTextImage_Layout.
*                                   Ex,  Layout_ImageTextImage_ShowAll=0x00,      ==> show all items.
*                                        Layout_ImageTextImage_PreImageHide=0x01, ==> hide pre-image item.
*
* @retval       void
*
*/
__INLINE void WdgITISetWidgetLayout
(
    IWidget                 *pWDGITI,
    WdgITILayoutStyle_t     nWidgetLayout
)
{
    WdgCommonSetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_LAYOUT, (u32)nWidgetLayout);
}

/** WdgITISetTextLayout
* @brief        Set the text layout of the text;
*               for set single line or multi-line, break line, ellipsis.
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nTextLayout       The text widget layout, refer to e_Text_Layout.
*                                 Ex, LAYOUT_MULTILINE   = 0x01, ==> If the text is single line or multi-line
*                                     LAYOUT_ELLIPSIS    = 0x04, ==> If the text can't be shown completely, should the text add the ellipsis
*
* @retval     void
*
*/
__INLINE void WdgITISetTextLayout
(
    IWidget             *pWDGITI,
    u8                  nTextLayout
)
{
    WdgCommonSetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_TEXT_LAYOUT_FLAG, (u32)nTextLayout);
}

/** WdgITISetPreImageWidth
* @brief        Set the width of the image prior to the text
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nWidth            The width of the image prior to the text
*
* @retval       void
*
*/
__INLINE void WdgITISetPreImageWidth
(
    IWidget             *pWDGITI,
    u16                 nWidth
)
{
    WdgCommonSetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_PRE_IMAGEWIDTH, (u32)nWidth);
}

/** WdgITISetPostImageWidth
* @brief        Set the width of the image posterior to the text
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nWidth            The width of the image posterior to the text
*
* @retval      void
*/
__INLINE void WdgITISetPostImageWidth
(
    IWidget             *pWDGITI,
    u16                 nWidth
)
{
    WdgCommonSetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_POST_IMAGEWIDTH, (u32)nWidth);
}

/** WdgITISetPreImagePrePadding
* @brief        Set the pre padding value of the image widget prior to the text
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nPrePadding       The pre padding of the image prior to the text
*
* @retval       void
*
*/
__INLINE void WdgITISetPreImagePrePadding
(
    IWidget             *pWDGITI,
    u16                 nPrePadding
)
{
    WdgCommonSetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_PRE_IMAGE_PRE_PADDING, (u32)nPrePadding);
}

/** WdgITISetPostImagePostPadding
* @brief        Set the post padding value of the image posterior to the text
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nPostPadding      The post padding of the image posterior to the text
*
* @retval       void
*
*/
__INLINE void WdgITISetPostImagePostPadding
(
    IWidget             *pWDGITI,
    u16                 nPostPadding
)
{
    WdgCommonSetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_POST_IMAGE_POST_PADDING, (u32)nPostPadding);
}

/** WdgITISetTextPrePadding
* @brief        Set the pre padding value of the text
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nPrePadding       The pre padding of the text
*
* @retval       void
*
*/
__INLINE void WdgITISetTextPrePadding
(
    IWidget             *pWDGITI,
    u16                 nPrePadding
)
{
    WdgCommonSetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_TEXT_PRE_PADDING, (u32)nPrePadding);
}

/** WdgITISetTextPostPadding
* @brief        Set the post padding value of the text
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nPostPadding      The post padding of the text
*
* @retval      void
*
*/
__INLINE void WdgITISetTextPostPadding
(
    IWidget             *pWDGITI,
    u16                 nPostPadding
)
{
    WdgCommonSetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_TEXT_POST_PADDING, (u32)nPostPadding);
}

/** WdgITISetFontCategory
* @brief    Set font category of widget.
*
* @param[in]    pWDGITI      The imagetextimage widget which want to be set
* @param[in]    FC                    A kind of font category enum value, refer to mae_font.h
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
__INLINE MAE_Ret WdgITISetFontCategory
(
    IWidget                 *pWDGITI,
    FontCategory_t          FC
)
{
    return WdgCommonSetProperty(pWDGITI, PROP_WDG_FONT_CATE, (u32)FC);
}

/** WdgITISetTextOutlineColor
* @brief        Set widget's text outline color
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nTextColor        The widget text outline color
*
* @retval       void
*
*/
__INLINE void WdgITISetTextOutlineColor
(
    IWidget             *pWDGITI,
    RGBColor_t          nTextColor
)
{
    WdgCommonSetProperty(pWDGITI, PROP_WDG_TEXT_OUTLINE_COLOR, (u32)nTextColor);
}

/** WdgITISetHighlightTextOutlineColor
* @brief        Set widget's highlighted text outline color
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nTextColor        The highlighted widget's text outline color
*
* @retval       void
*
*/
__INLINE void WdgITISetHighlightTextOutlineColor
(
    IWidget             *pWDGITI,
    RGBColor_t          nTextColor
)
{
    WdgCommonSetProperty(pWDGITI, PROP_WDG_HIGHLIGHT_TEXT_OUTLINE_COLOR, (u32)nTextColor);
}

/** WdgITISetHighlightTextColor
* @brief        Set widget's highlighted text color
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nTextColor        The highlighted widget's text color
*
* @retval       void
*
*/
__INLINE void WdgITISetHighlightTextColor
(
    IWidget             *pWDGITI,
    RGBColor_t          nTextColor
)
{
    WdgCommonSetProperty(pWDGITI, PROP_WDG_HIGHLIGHT_TEXT_COLOR, (u32)nTextColor);
}

/** WdgITISetHighlighted
* @brief        Set widget to be highlighted or not
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    bHighlighted      Flag of highlighted or not
*
* @retval       void
*
*/
__INLINE void WdgITISetHighlighted
(
    IWidget             *pWDGITI,
    boolean             bHighlighted
)
{
    WdgCommonSetProperty(pWDGITI, PROP_WDG_HIGHLIGHTED, (u32)bHighlighted);
}

/** WdgITISetAutoAnimate
* @brief        Set widget to be auto animate for text slide if text length is large than widget width
*               If auto is TRUE: Text slide effect enable if text length is large than widget width
*               If auto is FALSE: Text slide effect disable.
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    bAutoAnimate      The widget auto animate status
*
* @retval       void
*
*/
__INLINE void WdgITISetAutoAnimate
(
    IWidget                 *pWDGITI,
    boolean                 bAutoAnimate
)
{
    WdgCommonSetProperty(pWDGITI, PROP_WDG_BE_AUTO_ANIMATE, (u32)bAutoAnimate);
}

/** WdgITISetEnableAnimate
* @brief        Turn on/off animation to widget
*
* @param[in]    pWDGITI           Pointer to the ITI widget
* @param[in]    bEnableAnimate    TRUE, turn on,
*                                 FALSE, turn off.
*
* @retval       void
*
*/
__INLINE void WdgITISetEnableAnimate
(
    IWidget                 *pWDGITI,
    boolean                 bEnableAnimate
)
{
    WdgCommonSetProperty(pWDGITI, PROP_WDG_ENABLE_ANIMATE, (u32)bEnableAnimate);
}

/** WdgITISetLayoutStyle
* @brief        Set the widget layout vertical or horizontal.
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[in]    nLayoutStyle      Layout Style
*
* @retval        void
*
*/
__INLINE void WdgITISetLayoutStyle
(
    IWidget                 *pWDGITI,
    WdgLayoutStyle_t        nLayoutStyle
)
{
    WdgCommonSetProperty(pWDGITI, PROP_LAYOUT_STYLE, (u32)nLayoutStyle);
}

/** WdgITIGetWidgetLayout
* @brief        Get widget's widget layout
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be gotten
* @param[out]   pWidgetLayout     The widget layout, refer to e_ImageTextImage_Layout.
*                                 Ex,  Layout_ImageTextImage_ShowAll=0x00,      ==> show all items.
*                                      Layout_ImageTextImage_PreImageHide=0x01, ==> hide pre-image item.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgITIGetWidgetLayout
(
    IWidget                 *pWDGITI,
    WdgITILayoutStyle_t     *pWidgetLayout
)
{
    return WdgCommonGetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_LAYOUT, (u32 *)pWidgetLayout);
}

/** WdgITIGetData
* @brief        Get display data for ITI widget.
*
* @param[in]    pWDGITI         Pointer to the ImageTextImage widget
* @param[in]    ppData        the return pointer of data keeps in this widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgITIGetData
(
    IWidget                 *pWDGITI,
	void						  **ppData
);

/** WdgITIGetTextLayout
* @brief        Get the text layout of the text.
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be gotten
* @param[out]   pTextLayout       The text widget layout, refer to e_Text_Layout.
*                                 Ex, LAYOUT_MULTILINE   = 0x01, ==> If the text is single line or multi-line
*                                     LAYOUT_ELLIPSIS    = 0x04, ==> If the text can't be shown completely, should the text add the ellipsis
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgITIGetTextLayout
(
    IWidget                 *pWDGITI,
    u8                      *pTextLayout
)
{
    return WdgCommonGetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_TEXT_LAYOUT_FLAG, (u32 *)pTextLayout);
}

/** WdgITIGetPreImageWidth
* @brief        Get the width of the image widget prior to the text
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be gotten
* @param[out]   pWidth            The width of the image prior to the text
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgITIGetPreImageWidth
(
    IWidget             *pWDGITI,
    u16                 *pWidth
)
{
    return WdgCommonGetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_PRE_IMAGEWIDTH, (u32 *)pWidth);
}

/** WdgITIGetPostImageWidth
* @brief        Get the width of the image widget posterior to the text
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be gotten
* @param[out]   pWidth            The width of the image posterior to the text
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgITIGetPostImageWidth
(
    IWidget             *pWDGITI,
    u16                 *pWidth
)
{
    return WdgCommonGetProperty(pWDGITI, PROP_IMGTEXTIMG_WDG_POST_IMAGEWIDTH, (u32 *)pWidth);
}

/** WdgITIGetLayoutStyle
* @brief        Get the widget layout vertical or horizontal.
*
* @param[in]    pWDGITI           The imagetextimage widget which want to be set
* @param[out]   pLayoutStyle      Layout Style, refer to WdgLayoutStyle_t.
*                                  Ex, LAYOUT_STYLE_VERTICAL      ==> Vertical layout style
*                                     LAYOUT_STYLE_HORIZONTAL    ==> Horizontal layout style
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgITIGetLayoutStyle
(
    IWidget                 *pWDGITI,
    WdgLayoutStyle_t        *pLayoutStyle
)
{
    return WdgCommonGetProperty(pWDGITI, PROP_LAYOUT_STYLE, (u32 *)pLayoutStyle);
}

/** WdgITIRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGITI           The imagetextimage widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgITIRegisterDataChangeCb
(
    IWidget                         *pWDGITI,
    PfnWdgITIWidgetDataChange    pfn,
    void                            *pUserData
);

/** WdgITIDeregisterDataChangeCb
* @brief        Deregister data change callback.
*
* @param[in]    pWDGITI           The imagetextimage widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgITIDeregisterDataChangeCb
(
    IWidget                         *pWDGITI,
    PfnWdgITIWidgetDataChange    pfn,
    void                            *pUserData
);


#endif	//__MMI_WDG_IMAGE_TEXT_IMAGE_H
/*=============================================================*/
// end of file
