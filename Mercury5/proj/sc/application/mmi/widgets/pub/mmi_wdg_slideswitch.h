/**
* @file    mmi_wdg_slideswitch.h
* @author  christoph.kuo@mstarsemi.com
* 
*    Side-Switch is a widget that composed of two image widget, Slider background
*    Image and Switch Image. User can touch the Switch to slide-move on the Slider
*    background. When Switch Image reaches the maximum x-position of the Slider,
*    it will send a notice EVT_VIEWMDL_SLIDE_COMPLETE to inform AP. AP
*    can set the maximum x-position by setting property.
*
*
*     ex: Slide-Switch Widget
*    +-------------------------+
*    |    __________________   |
*    |   $__________________|  |  <- slider background
*    +-------------------------+
*         ^ $: switch
*
*    +---------------------------+
*    |     __________________    |
*    |    |__________________$   |  <- switch reaches the maximum x-position,
*    +---------------------------+      it will send an event to AP.
*
*
*/
#ifndef __MMI_WDG_SLIDESWITCH_H__
#define __MMI_WDG_SLIDESWITCH_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/


/** WdgSlideSwitchItemStyle_t
*
* @brief    pIImage:    
*           pWPos:      
*           pWidgetSize:     
*
*/
typedef struct
{
	IImage          *pIImage;
	WPos_t          *pWPos;
	WidgetSize_t    *pWidgetSize;
} WdgSlideSwitchItemStyle_t;

/** PfnWdgSlideSwitchSlideComplete
* @brief      CB register by "WdgSlideSwitchRegisterSlideCompleteCB"
*             and will be trigger when the position of switch reaches the maximum x-position.
*
* @param[in]  pApplet       The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData      User data ap developer setting when register CB.
* @param[in]  nEvtCode      Widget Event Code, only useful for softkey event
* @param[in]  nReserve      Unuseful parameter
* @param[in]  pIWidget      The widget instance
*
*/
typedef void (*PfnWdgSlideSwitchSlideComplete) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgSlideSwitchCommonSetSlideStyle
* @brief      Set SlideSwitch widget slide style
*
* @param[out] pWDGSlideSwitch    The pointer to IWidget interface object
* @param[in]  pStyle              Slide Style: Image, Position, Size
*
* @retval     MAE_RET_SUCCESS     Success
* @retval     MAE_RET_BAD_PARAM   Failed. pStyle is NULL
* @retval     MAE_RET_FAILED      Failed.

*
*/
MAE_Ret WdgSlideSwitchCommonSetSlideStyle
(
 IWidget *pWDGSlideSwitch,
 WdgSlideSwitchItemStyle_t   *pStyle
 );

/** WdgSlideSwitchCommonSetSwitchStyle
* @brief      Set SlideSwitch widget switch style
*
* @param[out] pWDGSlideSwitch    The pointer to IWidget interface object
* @param[in]  pStyle              Switch Style: Image, Position, Size
*
* @retval     MAE_RET_SUCCESS     Success
* @retval     MAE_RET_BAD_PARAM   Failed. pStyle is NULL
* @retval     MAE_RET_FAILED      Failed.
*
*/
MAE_Ret WdgSlideSwitchCommonSetSwitchStyle
(
 IWidget *pWDGSlideSwitch,
 WdgSlideSwitchItemStyle_t   *pStyle
 );
/*=============================================================*/
/** WdgSlideSwitchCreateForWnd
* @brief        Create SlideSwitch widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of SlideSwitch  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgSlideSwitchCreateForWnd
(
 HWIN      hWin,
 Pos_t            *pPos,
 WidgetSize_t     *pSize,
 u16              nWidgetID
 );

/** WdgSlideSwitchCreate
* @brief        Create SlideSwitch widget
*
* @retval       The pointer of SlideSwitch  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgSlideSwitchCreate
(
 void
 );

/** WdgSlideSwitchSetSliderBGImage
* @brief        Set SliderSwitch widget background image
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[in]    pIImage           The pointer of IImage interface object
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchSetSliderBGImage
(
 IWidget                 *pWDGSlideSwitch,
 IImage                  *pIImage
 )
{
    return WdgCommonSetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SLIDERBG_IMAGE, (u32)pIImage);
}

/** WdgSlideSwitchSetSliderBGPos
* @brief        Set SlideSwitch widget background image position
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[in]    pWPos             The position of SlideSwitch widget background image position
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchSetSliderBGPos
(
 IWidget                *pWDGSlideSwitch,
 WPos_t                 *pWPos
 )
{
    return WdgCommonSetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SLIDERBG_POS, (u32)pWPos);
}

/** WdgSlideSwitchSetSliderBGSize
* @brief        Set SlideSwitch widget background size
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[in]    pWidgetSize       The SlideSwitch widget background size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchSetSliderBGSize
(
 IWidget              *pWDGSlideSwitch,
 WidgetSize_t         *pWidgetSize
 )
{
    return WdgCommonSetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SLIDERBG_SIZE, (u32)pWidgetSize);
}

/** WdgSlideSwitchSetSwitchImage
* @brief        Set SlideSwitch widget switch image
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[in]    pIImage           SlideSwitch widget switch image
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchSetSwitchImage
(
 IWidget                *pWDGSlideSwitch,
 IImage                 *pIImage
 )
{
    return WdgCommonSetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SWITCH_IMAGE, (u32)pIImage);
}

/** WdgSlideSwitchSetSwitchPos
* @brief        Set SlideSwitch widget switch position
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[in]    pWPos             The position of SlideSwitch widget switch position
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchSetSwitchPos
(
 IWidget                *pWDGSlideSwitch,
 WPos_t                 *pWPos
 )
{
    return WdgCommonSetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SWITCH_POS, (u32)pWPos);
}

/** WdgSlideSwitchSetSwitchSize
* @brief        Set SlideSwitch widget switch size
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[in]    pWidgetSize       The SlideSwitch widget switch size
*
* @retval       None
*
*/
__INLINE MAE_Ret WdgSlideSwitchSetSwitchSize
(
 IWidget              *pWDGSlideSwitch,
 WidgetSize_t         *pWidgetSize
 )
{
    return WdgCommonSetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SWITCH_SIZE, (u32)pWidgetSize);
}

/** WdgSlideSwitchSetSlideMaxValue
* @brief        Set Slide Max Value in Pixel unit.
*               To trigger PfnWdgSlideSwitchSlideComplete while Switch Image reach Max Value.
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[in]    nMax              Slide Max Value in Pixel unit.
*
* @retval       None
*
*/
__INLINE void WdgSlideSwitchSetSlideMaxValue
(
 IWidget              *pWDGSlideSwitch,
 u32                  nMax
 )
{
	WdgCommonSetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SWITCH_MAX_X, (u32)nMax);
}

/** WdgSlideSwitchGetSliderBGPos
* @brief        Get SliderSwitch widget background position
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[out]   pWPos_t           SliderSwitch widget background position
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchGetSliderBGPos
(
 IWidget                *pWDGSlideSwitch,
 WPos_t                 *pWPos_t
 )
{
	return WdgCommonGetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SLIDERBG_POS, (u32*)pWPos_t);
}

/** WdgSlideSwitchGetSliderBGSize
* @brief        Get SlideSwitch widget background size
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[out]   pWidgetSize       The SlideSwitch widget background size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchGetSliderBGSize
(
 IWidget              *pWDGSlideSwitch,
 WidgetSize_t         *pWidgetSize
 )
{
	return WdgCommonGetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SLIDERBG_SIZE, (u32*)pWidgetSize);
}

/** WdgSlideSwitchGetSwitchPos
* @brief        Get SlideSwitch widget position
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[out]   pWPos             SlideSwitch widget position
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchGetSwitchPos
(
 IWidget                *pWDGSlideSwitch,
 WPos_t                 *pWPos
 )
{
	return WdgCommonGetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SWITCH_POS, (u32*)pWPos);
}

/** WdgSlideSwitchGetSwitchSize
* @brief        Get SlideSwitch widget switch size
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[out]   pWidgetSize       The SlideSwitch widget switch size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSlideSwitchGetSwitchSize
(
 IWidget              *pWDGSlideSwitch,
 WidgetSize_t         *pWidgetSize
 )
{
	return WdgCommonGetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SWITCH_SIZE, (u32*)pWidgetSize);
}

/** WdgSlideSwitchGetSlideMaxValue
* @brief        Get Slide Max Value in Pixel unit.
*
* @param[in]    pWDGSlideSwitch  The pointer of IWidget interface object
*
* @retval       Max              Slide Max Value in Pixel unit.
*
*/
u32 WdgSlideSwitchGetSlideMaxValue
(
 IWidget                 *pWDGSlideSwitch
 );

#ifndef __SLIDEBG_AS_IMAGE__
/** WdgSlideSwitchSetSliderBGTextByID
* @brief        Set SliderSwitch widget text by ID
*
* @param[in]    pWDGSlideSwitch   The pointer of IWidget interface object
* @param[in]    nTextID           Id of the text label
*
* @retval       None
*
*/
__INLINE void WdgSlideSwitchSetSliderBGTextByID
(
 IWidget                 *pWDGSlideSwitch,
 u32                     nTextID
 )
{
	WdgCommonSetProperty(pWDGSlideSwitch, PROP_SLIDESWITCH_WDG_SLIDERBG_TEXT_ID, nTextID);
}
#endif


/** WdgSlideSwitchRegisterSlideCompleteCb
* @brief        Register callback : For SlideSwitch Widget,
*               CB will be triggered when the position of switch reaches the maximum x-position.
*
* @param[in]    pWDGSlideSwitch   The slides witch widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgSlideSwitchRegisterSlideCompleteCb
(
 IWidget                         *pWDGSlideSwitch,
 PfnWdgSlideSwitchSlideComplete  pfn,
 void                            *pUserData
 );

/** WdgSlideSwitchDeregisterSlideCompleteCb
* @brief        Deregister callback
*
* @param[in]    pWDGSlideSwitch   The slide switch widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgSlideSwitchDeregisterSlideCompleteCb
(
 IWidget                         *pWDGSlideSwitch,
 PfnWdgSlideSwitchSlideComplete  pfn,
 void                            *pUserData
 );

#endif /*__MMI_WDG_SLIDESWITCH_H__ */
