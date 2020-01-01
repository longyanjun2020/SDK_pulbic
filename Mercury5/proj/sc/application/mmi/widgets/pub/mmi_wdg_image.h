/**
* @file    mmi_wdg_image.h
* @version $Id: mmi_wdg_image.h 20863 2009-01-19 10:59:56Z paul.ouyang $
* 
* @brief   This file defines CLSID_IMAGEWIDGET class which is a kind of Widget object.
*
*     The function of Image widget is to display a picture or an animation (gif). It is similar
*     to Bitmap widget but with more powerful features. It can show an IBitmap object or
*     IImage object. If you want to show the animation (gif), it must load IImage object. Image
*     widget supports alignment, rotate angle, and scale size. If it spends too much time to
*     decode an image, AP can decided to let the Image widget to automatically display a
*     default picture.
*
*     Image widget also supports to record a linking information (WdgImageSetLinkingText())
*     A touch on this widget will trigger a notice event. Applet should register a listening
*     handler to receive the event, and get the linking information (WdgImageGetLinkingText()).
*     Applet also can change the link state (WdgImageSetLinkedState()). This Linked state
*     property only for applet to keep the linked state. Applet can use this property to keep
*     the linked state and display different text color if applet need to different the linking is
*     be touched or not.
*
*
*/
#ifndef __MMI_WDG_IMAGE_H__
#define __MMI_WDG_IMAGE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"


/*=============================================================*/
// type and define
/*=============================================================*/
#define DEFAULT_FRAME_INTERVAL  500

enum
{
	IMGWDG_AUTO_FIT_START = 0,
	
	IMGWDG_DISABLE_AUTO_FIT = IMGWDG_AUTO_FIT_START,
	IMGWDG_AUTO_FIT_WIDTH,        ///< keep image width <= widget width. keep ratio
	IMGWDG_AUTO_FIT_HEIGHT,       ///< keep image height <= widget height. keep ratio
	
	IMGWDG_AUTO_FIT_WDGSIZE,      ///< keep whole image inside the widget. keep ratio
	IMGWDG_AUTO_FIT_WDGSIZE_CROP, ///< fill widget with the image as more as possible. keep ratio
	IMGWDG_AUTO_FIT_WDGSIZE_STRETCH,  ///< stretch the image size to widget size. do NOT keep ratio
	
	IMGWDG_AUTO_FIT_TOTAL
};
typedef u32 ImgWdgAutoFit_t;

/** ImgScaleRotate_t
*
* @brief    width:         
*           height:            
*           angle:     
*
*/
typedef struct ImgScaleRotate_tag
{
	u32           width;
	u32           height;
	ImgDecAngle_t angle;	
}ImgScaleRotate_t;

/** ImgWdg_ImgInfo_t
*
* @brief    imgInfo:                the IMG_DECODE_INFO of the image or bitmap
*           PrefferedFameWidth:     If the (imgInfo.frames==1) => Image Widget use the PreferredFrameWidth (Set by the PROP_IMG_WDG_IMAGE_PREFERRED_FRAME_WIDTH) to draw the image   
*
*/
typedef struct ImgWdg_ImgInfo_tag
{
    ImageInfo   imgInfo;
    u32         PrefferedFameWidth;
}ImgWdg_ImgInfo_t;

typedef enum
{
    IMAGE_STYLE_COMMON/*,
    IMAGE_STYLE_THEME*/
} ImageStyle_e;
typedef u8 ImageStyle_t;

/** WdgImageConfigData_t
*
* @brief    bAutoFit:         True or False for auto adjust image to fit widget size.
*           nImageID:         The display image data.
*
*/
typedef struct
{
    boolean                  bAutoFit;
    u32                      nImageID;
}WdgImageConfigData_t;


/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgImageWidgetSizeChange
* @brief      CB register by "WdgImageRegisterSizeChangeCb"
*             and will be trigger when the size of widget is changed; Ex,WdgCommonSetSize
*
* @param[in]  pApplet        The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData       User data ap developer setting when register CB.
* @param[in]  nEvtCode       Widget Event Code, only useful for softkey event
* @param[in]  pWidgetSize    The size be changed of widget, refer to WidgetSize_t
* @param[in]  pIWidget       The widget instance
*
*/
typedef void (*PfnWdgImageWidgetSizeChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, WidgetSize_t *pWidgetSize, IWidget *pIWidget);

/** PfnWdgImageLinkImageClick
* @brief      CB register by "WdgImageRegisterLinkImageClickCb"
*             and will be trigger when Image be Click; EX, Work if WdgImageSetLinkingText
*
* @param[in]  pApplet       The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData      User data ap developer setting when register CB.
* @param[in]  nEvtCode      Widget Event Code, only useful for softkey event
* @param[in]  pNotifyWidget The widget instance
* @param[in]  pIWidget      The widget instance
*
*/
typedef void (*PfnWdgImageLinkImageClick) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, IWidget *pNotifyWidget, IWidget *pIWidget);

/** PfnWdgImageWidgetInterfaceChange
* @brief      CB register by "WdgImageRegisterInterfaceChangeCb"
*             and will be trigger when the data of widget is changed; Ex,WdgImageSetDataByID
*
* @param[in]  pApplet        The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData       User data ap developer setting when register CB.
* @param[in]  nEvtCode       Widget Event Code, only useful for softkey event
* @param[in]  nReserve       Unuseful parameter
* @param[in]  pIWidget       The widget instance
*
*/
typedef void (*PfnWdgImageWidgetInterfaceChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
/*=============================================================*/
/** WdgImageCreateForWnd
* @brief        Image widget create function for Window
*
* @param[in]    hWin        The window handle
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
IWidget* WdgImageCreateForWnd
(
    HWIN          hWin,
    Pos_t                *pPos,
    WidgetSize_t         *pSize,
    u16                  nWidgetID,
    ImageStyle_e         eStyle,
    WdgImageConfigData_t *pData
);
/*=============================================================*/
/** WdgImageCreate
* @brief        Create Image widget
*
* @param[in]    eImageStyle    ImageWidget initial style
*
* @retval       The pointer of Image    Success.
* @retval       NULL                    Failed.
*
*/
IWidget* WdgImageCreate
(
    ImageStyle_e    eImageStyle
);

/** WdgImageSetData
* @brief        Set Image to widget for display;
*               Specific data for IMAGE_STYLE_COMMON and IMAGE_STYLE_THEME of Image widget.
*
* @param[in]    pWDGImage      The image widget which want to be set
* @param[in]    *pImageData    The image data can be IImage or IImage
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageSetData
(
    IWidget                 *pWDGImage,
    void                    *pImageData
);

/** WdgImageSetDataByID
* @brief        Set Image to widget for display;
*               Specific data for IMAGE_STYLE_COMMON and IMAGE_STYLE_THEME of Image widget.
*
* @param[in]    pWDGImage         The image widget which want to be set
* @param[in]    nImageID       The image data resource ID
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageSetDataByID
(
    IWidget                 *pWDGImage,
    u32                     nImageID
);
/** WdgImageSetDataByBuffer
* @brief        Set Image to widget for display;
*               Specific data for IMAGE_STYLE_COMMON and IMAGE_STYLE_THEME of Image widget.
*
* @param[in]    pWDGImage         The image widget which want to be set
* @param[in]    *pImageBuffer     The image data buffer,bitstream read from JPG or GIF or ...
* @param[in]    *nDataSize        The Size of image data
* @param[in]    pfnFree      		  The free image data buffer callback function
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageSetDataByBuffer
(
    IWidget                 *pWDGImage,
    u8                        *pImageBuffer,
    u32                     nDataSize,
    PfnMAE_ImgBuffer         pfnFree
);

/** WdgImageSetImageScaleRotate
* @brief        Set Image widget's image scale size and rotate angle
*               PS: Working when WdgImageSetAutoFit is "IMGWDG_DISABLE_AUTO_FIT"
*
* @param[in]    pWDGImage          The image widget which want to be set
* @param[in]    *pImageScaleRotate The image scale size and rotate angle
*                                  Please refer to ImgScaleRotate_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetImageScaleRotate
(
    IWidget                 *pWDGImage,
    ImgScaleRotate_t        *pImageScaleRotate
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_IMAGE_SCALE_ROTATE, (u32)pImageScaleRotate);
}

/** WdgImageSetFrameWidth
* @brief        Set Image widget's width of each frame (for animation image)
*               PS: Precondition WdgImageSetEnablePartialDecode is Disable.
*
* @param[in]    pWDGImage         The image widget which want to be set
* @param[in]    nWidth            The width of each frame which will be set to the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetFrameWidth
(
    IWidget              *pWDGImage,
    u32                  nWidth
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_FRAME_WIDTH, (u32)nWidth);
}

/** WdgImageSetFrameInterval
* @brief        Set Image widget's interval of frames (for animation image)
*
* @param[in]    pWDGImage      The image widget which want to be set
* @param[in]    nInterval      The interval of frames which will be set to the image widget (in milliseconds)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetFrameInterval
(
    IWidget              *pWDGImage,
    u32                  nInterval
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_FRAME_INTERVAL, (u32)nInterval);
}

/** WdgImageSetAutoFit
* @brief        Set Image widget's option of auto fit
*               PS: The setting working when original image size is large than widget size.
*
* @param[in]    pWDGImage  The image widget which want to be set
* @param[in]    tAutoFit   The option of auto fit which will be set to the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgImageSetAutoFit
(
    IWidget                 *pWDGImage,
    ImgWdgAutoFit_t         tAutoFit
)
{
    return WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_AUTO_FIT, (u32)tAutoFit);
}

/** WdgImageSetEnableUpscale
* @brief        Turn on/off Image widget's unscaled capability; Enable will scale image up to widget size.
*               PS: The setting working when original image size is samll than widget size.
*
*
* @param[in]    pWDGImage   The image widget which want to be set
* @param[in]    bEnable     The widget's upscale on/off status which will be set to the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetEnableUpscale
(
    IWidget                 *pWDGImage,
    boolean                 bEnable
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_ENABLE_UPSCALE, (u32)bEnable);
}

/** WdgImageSetAnimationPlayOnce
* @brief        Turn on/off Image widget's property; Enable will let animation image play once.
*
*
* @param[in]    pWDGImage   The image widget which want to be set
* @param[in]    bAnimateOnce   To set the widget's animation property
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetAnimationPlayOnce
(
    IWidget                 *pWDGImage,
    boolean                 bAnimateOnce
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_ANIMATE_ONCE, (u32)bAnimateOnce);
}

/** WdgImageSetKeepDecodeBuffer
* @brief        Turn on/off Image widget's property; Enable will not auto free decoded buffer when recieve an inactive event.
*
*
* @param[in]    pWDGImage   The image widget which want to be set
* @param[in]    bKeepBuffer   To set the widget's property
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetKeepDecodeBuffer
(
    IWidget                 *pWDGImage,
    boolean                 bKeepBuffer
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_KEEP_BUFFER, (u32)bKeepBuffer);
}


/** WdgImageSetEnablePartialDecode
* @brief        Turn on/off Image widget's partial decoding capability (Enable partial decode of HW, default is off)
*
* @param[in]    pWDGImage   The image widget which want to be set
* @param[in]    bEnable     The partial decoding on/off status which will be set to the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetEnablePartialDecode
(
    IWidget                 *pWDGImage,
    boolean                 bEnable
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_ENABLE_PARTIAL_DEC, (u32)bEnable);
}

/** WdgImageSetEnableDefaultImage
* @brief        Turn on/off Image widget's default image, while decoding(default is on)
*
* @param[in]    pWDGImage   The image widget which want to be set
* @param[in]    bEnable     The default image on/off status which will be set to the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetEnableDefaultImage
(
    IWidget                 *pWDGImage,
    boolean                 bEnable
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_ENABLE_DEF_IMAGE, (u32)bEnable);
}

/** WdgImageSetDefaultImageID
* @brief        Set Image widget's default image ID
*               *PS Use Case: If the timer is too long to decode an image,
*               AP can decided to let the Image widget to automatically display a default picture.
*               Before use this API, need to turn on feature by WdgImageSetEnableDefaultImage.
*
* @param[in]    pWDGImage     The image widget which want to be set
* @param[in]    nImageID      The default image ID which will be set to the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetDefaultImageID
(
    IWidget              *pWDGImage,
    u32                  nImageID
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_DEF_IMAGE_ID, (u32)nImageID);
}

/** WdgImageSetLinkingText
* @brief        Set Image widget's linking text
*
* @param[in]    pWDGImage       The image widget which want to be set
* @param[in]    *pLinkingText   The linking text which will be set to the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetLinkingText
(
    IWidget          *pWDGImage,
    MAE_WChar        *pLinkingText
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_LINK_ADDR, (u32)pLinkingText);
}

/** WdgImageSetLinkedState
* @brief        Set Image widget's linked state
*
* @param[in]    pWDGImage     The image widget which want to be set
* @param[in]    bLinkedState  The linked state which will be set to the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetLinkedState
(
    IWidget                 *pWDGImage,
    boolean                 bLinkedState
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_LINKED_STATE, (u32)bLinkedState);
}

/** WdgImageSetAlignment
* @brief         Set Image widget's alignment flag
*
* @param[in]     pWDGImage         The Image widget which want to be set
* @param[in]     eWdgAlignment     The widget alignment flag which will be set to the Image widget
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE void WdgImageSetAlignment
(
    IWidget           *pWDGImage,
    WdgAlignment_e    eWdgAlignment
)
{
    WdgCommonSetProperty(pWDGImage, PROP_WDG_ALIGNMENT, (u32)eWdgAlignment);
}

/** WdgImageSetAsBackground
* @brief        Set to be a background for other widgets; The effect as a background picture behind a widget.
*               Ex, Set to a text widget, the image will be the background.
*
* @param[in]    pWDGImage         The image widget which want to be set
* @param[in]    pWDGForeground    The widget which put in front of the image .
*
* @retval       None.
*
*/
void WdgImageSetAsBackground
(
    IWidget                 *pWDGImage,
    IWidget                 *pWDGForeground
);

/** WdgImageSetEnableAnimate
* @brief        Turn on/off animation to widget
*
* @param[in]    pWDGImage         Pointer to the Image widget
* @param[in]    bEnableAnimate    TRUE, turn on,
*                                 FALSE, turn off.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetEnableAnimate
(
    IWidget                 *pWDGImage,
    boolean                 bEnableAnimate
)
{
    WdgCommonSetProperty(pWDGImage, PROP_WDG_ENABLE_ANIMATE, (u32)bEnableAnimate);
}

/** WdgImageSetCanUsePaletteData
* @brief        set if this image widget can use palette image data, which is 8 bit color format
*
* @param[in]    pWDGImage         Pointer to the Image widget
* @param[in]    bCanUse    TRUE, can use
*                                 FALSE, can not use.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE void WdgImageSetCanUsePaletteData
(
    IWidget                 *pWDGImage,
    boolean                 bCanUse
)
{
    WdgCommonSetProperty(pWDGImage, PROP_IMG_WDG_CAN_USE_PALETTE_DATA, (u32)bCanUse);
}

/** WdgImageGetImageInfo
* @brief        Get Image widget's drawing image information
*
* @param[in]    pWDGImage      The image widget which want to be gotten
* @param[out]   pImageInfo     The drawing image information which will be gotten from the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgImageGetImageInfo
(
    IWidget                 *pWDGImage,
    ImgWdg_ImgInfo_t        *pImageInfo
)
{
    return WdgCommonGetProperty(pWDGImage, PROP_IMG_WDG_IMGINFO, (u32 *)pImageInfo);
}

/** WdgImageGetAutoFit
* @brief        Get Image widget's option of auto fit
*
* @param[in]    pWDGImage    The image widget which want to be gotten
* @param[out]   pAutoFit     The option of auto fit which will be gotten from the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
/*
__INLINE MAE_Ret WdgImageGetAutoFit
(
    IWidget          *pWDGImage,
    ImgWdgAutoFit_t  *pAutoFit
)
{
    return WdgCommonGetProperty(pWDGImage, PROP_IMG_WDG_AUTO_FIT, (u32 *)pAutoFit);
}
*/

/** WdgImageGetEnableUpscale
* @brief        Get Image widget's upscale on/off status
*
* @param[in]    pWDGImage    The image widget which want to be gotten
*
* @return       Image widget's upscale on/off status
*
*/
boolean WdgImageGetEnableUpscale
(
    IWidget                 *pWDGImage
);

/** WdgImageGetEnablePartialDecode
* @brief        Get Image widget's partial decoding on/off status (default is off)
*
* @param[in]    pWDGImage     The image widget which want to be gotten
* @param[out]   pEnable       The partial decoding on/off status which will be gotten from the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgImageGetEnablePartialDecode
(
    IWidget                 *pWDGImage,
    boolean                 *pEnable
)
{
    return WdgCommonGetProperty(pWDGImage, PROP_IMG_WDG_ENABLE_PARTIAL_DEC, (u32 *)pEnable);
}

/** WdgImageGetEnableDefaultImage
* @brief        Get Image widget's default image on/off status (default is on)
*
* @param[in]    pWDGImage     The image widget which want to be gotten
*
* @return       Image widget's default image on/off status
*
*/
boolean WdgImageGetEnableDefaultImage
(
    IWidget                 *pWDGImage
);

/** WdgImageGetDefaultImageID
* @brief        Get Image widget's default image ID
*
* @param[in]    pWDGImage       The image widget which want to be gotten
*
* @return       Image widget's default image ID
*
*/
u32 WdgImageGetDefaultImageID
(
    IWidget               *pWDGImage
);

/** WdgImageGetLinkingText
* @brief        Get Image widget's linking text
*
* @param[in]    pWDGImage         The image widget which want to be gotten
*
* @return       Image widget's linking text
*
*/
MAE_WChar* WdgImageGetLinkingText
(
    IWidget                 *pWDGImage
);

/** WdgImageGetLinkedState
* @brief        Get Image widget's linked state
*
* @param[in]    pWDGImage         The image widget which want to be gotten
* @param[out]   pLinkedState      The linked state which will be gotten from the image widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgImageGetLinkedState
(
    IWidget                 *pWDGImage,
    boolean                 *pLinkedState
)
{
    return WdgCommonGetProperty(pWDGImage, PROP_IMG_WDG_LINKED_STATE, (u32 *)pLinkedState);
}

/** WdgImageGetAlignment
* @brief         Get Image widget's alignment flag
*
* @param[in]     pWDGImage         The Image widget which want to be gotten
*
* @return        Image widget's alignment flag
*
*/
WdgAlignment_e WdgImageGetAlignment
(
    IWidget                 *pWDGImage
);

/** WdgImageGetObjFromBackground
* @brief        Get Foreground widget from this image; if the image is a background for a widgets
*                   Ex, Set to a text widget, the image will be the background.
*                   Then you can get text widget from the image.
*
* @param[in]    pWDGImage         The image widget which want to be set
*
* @retval       The widget which put in front of the image .
*
*/
IWidget* WdgImageGetObjFromBackground
(
    IWidget                *pWDGImage
);

/** WdgImageCalculateFitSize
* @brief        Get fit size of image widget depends on autofit type and its own size
*
* @param[in]    pWDGImage         The image widget which want to be set
* @param[in]    width             Image/bitmap original width in pixels
* @param[in]    height            Image/bitmap original height in pixels
* @param[out]   pDecSize          Decode size of the image
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       MAE_RET_BAD_PARAM Failed
*
*/
MAE_Ret WdgImageCalculateFitSize
(
    IWidget                 *pWDGImage, 
    u32                     width, 
    u32                     height, 
    ImageSize_t             *pDecSize
);

/** WdgImageRegisterSizeChangeCb
* @brief        Register size change callback; CB will be triggered if widget size changed.
*
* @param[in]    pWDGImage    The image widget which want to set callback
* @param[in]    pfn          callback function
* @param[in]    pUserData     User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageRegisterSizeChangeCb
(
    IWidget                         *pWDGImage,
    PfnWdgImageWidgetSizeChange     pfn,
    void                            *pUserData
);

#ifdef __TOUCH_SCREEN_MMI__
/** WdgImageRegisterLinkImageClickCb
* @brief        Register link image click callback;
*               CB will be triggered if link image(image on website) click.
*
* @param[in]    pWDGImage      The image widget which want to set callback
* @param[in]    pfn            callback function
* @param[in]    pUserData       User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageRegisterLinkImageClickCb
(
    IWidget                     *pWDGImage,
    PfnWdgImageLinkImageClick   pfn,
    void                        *pUserData
);
#endif

/** WdgImageRegisterInterfaceChangeCb
* @brief        Register the object change callback;
*               CB will be triggered while image has changed.
*
* @param[in]    pWDGImage        The image widget which want to set callback
* @param[in]    pfn              callback function
* @param[in]    pUserData         User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageRegisterInterfaceChangeCb
(
    IWidget                             *pWDGImage,
    PfnWdgImageWidgetInterfaceChange    pfn,
    void                                *pUserData
);

/** WdgImageDeregisterSizeChangeCb
* @brief        Deregister size change callback.
*
* @param[in]    pWDGImage    The image widget which want to set callback
* @param[in]    pfn          callback function
* @param[in]    pUserData     User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageDeregisterSizeChangeCb
(
    IWidget                         *pWDGImage,
    PfnWdgImageWidgetSizeChange     pfn,
    void                            *pUserData
);

#ifdef __TOUCH_SCREEN_MMI__
/** WdgImageDeregisterLinkImageClickCb
* @brief        Deregister link image click callback.
*
* @param[in]    pWDGImage    The image widget which want to set callback
* @param[in]    pfn          callback function
* @param[in]    pUserData     User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageDeregisterLinkImageClickCb
(
    IWidget                     *pWDGImage,
    PfnWdgImageLinkImageClick   pfn,
    void                        *pUserData
);
#endif

/** WdgImageDeregisterInterfaceChangeCb
* @brief        Deregister the object change callback.
*
* @param[in]    pWDGImage         The image widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgImageDeregisterInterfaceChangeCb
(
    IWidget                             *pWDGImage,
    PfnWdgImageWidgetInterfaceChange    pfn,
    void                                *pUserData
);


#endif //__MMI_WDG_IMAGE_H__
/*=============================================================*/
// end of file
