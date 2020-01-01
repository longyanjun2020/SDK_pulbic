/**
*    Transition widget is a special effect widget to display, and its function is to
*    display the special effect of the conversion process from one widget to another.
*    Transition widget offers three types of effect, Fly, Blinds and Irritation.
*
*     ex: the Fly special effect of Transition widget
*    +------------+            +------------+             +------------+
*    |      @     |      -->   |@          %|      -->    |      %     |     switch from @ widget to % widget
*    +------------+            +------------+             +------------+
*
*/

#ifndef __MMI_WDG_TRANSITION_H__
#define __MMI_WDG_TRANSITION_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_transition.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_retcode.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_headers.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef u8 TransitionDataType_t;
enum {
    TRANS_TYPE_IMAGE_ID,
    TRANS_TYPE_IMAGE_DATA,
    TRANS_TYPE_BITMAP_DATA,
    TRANS_TYPE_MAX
};

/** WdgTransitionParam_t
*
* @brief    type:
*           direction:
*           pNewWdg:
*           duration:
*
*/
typedef struct
{
    TransitionType_t        type;
    TransitionDirection_t   direction;
    IWidget                 *pNewWdg;
    u32                     duration;
}WdgTransitionParam_t;

/** WdgTransitionPos_t
*
* @brief    xoffset:
*             yoffset:
*
*/
typedef struct
{
    s16 xoffset;
    s16 yoffset;
}WdgTransitionPos_t;

#if defined(__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_ANDROID_IDLE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
/** WdgTransitionPosParam_t
*
* @brief    type:
*             pLeftWdg:
*             pRightWdg:
*             duration:
*             xoffset:
*             yoffset:
*/
typedef struct
{
	TransitionType_t    type;
	IWidget             *pLeftWdg;
	IWidget             *pRightWdg;
	u32                 duration;
	s16                 xoffset;
	s16                 yoffset;
}WdgTransitionPosParam_t;

#endif /* __UI_STYLE_MMI_IFONE__*/

typedef struct
{
    TransitionType_t    type;
    TransitionDirection_t   direction;
    IWidget             *pNewWdg;
    u32                 duration;
    s16                 xoffset;
    s16                 yoffset;
}WdgTransitionSlipParam_t;

typedef struct
{
    TransitionDirection_t   direction;
    s16                 xoffset;
    s16                 yoffset;
}WdgTransitionSlipEndParam_t;

/** WdgTransitionWDGTransitSetting_t
*
* @brief    nWDGInterval:       Interval between frames, in ms
*           nWDGBlockSize:      width/height of a block, in pixel
*
*/
typedef struct
{
    u16                        nWDGInterval;     //Interval between frames, in ms
    u16                        nWDGBlockSize;    //width/height of a block, in pixel
}WdgTransitionWDGTransitSetting_t;

/** WdgTransitionDstImageProperty_t
*
* @brief    pSize:                  Destination Image Size
*           pEnablePartialDec:      Enable/Disable Partial Decode
*           pEnalbeDefImage:        Enable/Disable Default Image
*           pImageAutoFit:          AutoFit Type
*
*/
typedef struct WdgTransitionDstImageProperty_t_
{
	WidgetSize_t *pSize;				// Destination Image Size
	boolean *pEnablePartialDec;			// Enable/Disable Partial Decode
	boolean *pEnalbeDefImage;			// Enable/Disable Default Image
	ImgWdgAutoFit_t *pImageAutoFit;		// AutoFit Type
} WdgTransitionDstImageProperty_t;

/** WdgTransitionImgData_t
*
* @brief    transType:
*           direction:
*           duration:
*           transDataType:
*           nAlignment:
*           nBGColor:
*           pDstImageProperty:
*           tDstImage:
*
*/
typedef struct
{
    TransitionType_t        transType;
    TransitionDirection_t   direction;
    u32                     duration;       //ms
    TransitionDataType_t    transDataType;
    WdgAlignment_e          nAlignment;
    RGBColor_t              nBGColor;
	WdgTransitionDstImageProperty_t *pDstImageProperty;

    union
    {
        u32 nImageID;           // Image ID of IImage or IBitmap.
        IImage *pIImage;        // Pointer to IImage.
        IBitmap *pIBitmap;      // Pointer to IBitmap.
    } tDstImage;

}WdgTransitionImgData_t;

typedef struct
{
    TransitionType_t        transType;
    TransitionDirection_t   direction;
    u32                     duration;       //ms
    TransitionDataType_t    transDataType;
    WdgAlignment_e          nAlignment;
    RGBColor_t              nBGColor;
    WdgTransitionDstImageProperty_t *pDstImageProperty;
    s16 xoffset;
    s16 yoffset;

    union
    {
        u32 nImageID;           // Image ID of IImage or IBitmap.
        IImage *pIImage;        // Pointer to IImage.
        IBitmap *pIBitmap;      // Pointer to IBitmap.
    } tDstImage;

}WdgTransitionImgSlipData_t;

/** PfnWdgTransitionTransitDone
* @brief      CB register by "WdgTransitionRegisterTransitDoneCb"
*             and will be trigger when the transition is done.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef enum
{
    TRANSIT_LOCATION_UP,
    TRANSIT_LOCATION_DOWN,
    TRANSIT_LOCATION_LEFT,
    TRANSIT_LOCATION_RIGHT,
    TRANSIT_LOCATION_INPLACE
}WdgTransitionLocation_e;

typedef struct  
{
    TransitionType_t        transType;
    TransitionDirection_t   direction;
    WdgTransitionLocation_e location;
}WdgTransitionTransitDoneData_t;

typedef void (*PfnWdgTransitionTransitDone) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgTransitionCreateForWnd
* @brief        Create Transition widget and set size for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of Transition   Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgTransitionCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID
);
/*=============================================================*/
/** WdgTransitionCreate
* @brief        Create Transition widget
*
* @retval       The pointer of Transition   Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgTransitionCreate
(
    void
);
/*=============================================================*/

/** WdgTransitionSetWDGStart
* @brief        Start to transit from original widget to new widget
*
* @param[in]    pWDGTransition       Pointer to the Transition Widget
* @param[in]    pWDGStart            Start effect
*
*                                    pWDGStart.type     : Transition type
*                                    pWDGStart.pWdg     : Pointer of IWidget to transit in. NULL is allowed.
*                                    pWDGStart.duration : Transition duration in msec
*                                    pWDGStart.dir      : Transition direction
*
* @retval       None
*
*/
void WdgTransitionSetWDGStart
(
    IWidget                 *pWDGTransition,
    WdgTransitionParam_t    *pWDGStart
);

/** WdgTransitionSetImgStart
* @brief        Start to transit from original image to new image
*
* @param[in]    pWDGTransition       Pointer to the Transition Widget
* @param[in]    pWDGStart            Start transition effect
*
*                                    pWDGStart.transType     : Transition type
*                                    pWDGStart.duration      : Transition duration in msec
*                                    pWDGStart.direction     : Transition direction
*                                    pWDGStart.transDataType : Indicate the type of Destination Image Data.
*                                    pWDGStart.tDstImage     : Destination Image Data.
*
* @retval       None
*
*/
void WdgTransitionSetImgStart
(
    IWidget                 *pWDGTransition,
    WdgTransitionImgData_t     *pWDGStart
);

void WdgTransitionSetImgSlipStart
(
    IWidget                 *pWDGTransition,
    WdgTransitionImgSlipData_t     *pWDGStart
);

/** WdgTransitionStop
* @brief        Stop transition
*
* @param[in]    pWDGTransition       Pointer to the Transition Widget
*
* @retval       None
*
*/
void WdgTransitionStop
(
    IWidget                 *pWDGTransition
);

/** WdgTransitionSetWDGInterval
* @brief        Set Interval; total time of trasition is duration/Interval.
*
* @param[in]    pWDGTransition       Pointer to the Transition Widget
* @param[in]    nWDGInterval         Interval between frames, in ms
*
* @retval       None
*
*/
void WdgTransitionSetWDGInterval
(
    IWidget                 *pWDGTransition,
    u16                     nWDGInterval
);

/** WdgTransitionSetWDGBlockSize
* @brief        Set BlockSize; only for TRANSITION_BLINDS transition style.
*
* @param[in]    pWDGTransition       Pointer to the Transition Widget
* @param[in]    nWDGBlockSize        width/height of a block, in pixel
*
* @retval       None
*
*/
void WdgTransitionSetWDGBlockSize
(
    IWidget                 *pWDGTransition,
    u16                     nWDGBlockSize
);

/** WdgTransitionSetOriginalWdg
* @brief        Set the widget be the Original before transition.
*               The transition effect will start to transit from "Original" to "pNewWdg of WdgTransitionSetWDGStart"
*
* @param[in]    pWDGTransition    The Transition widget which want to be set
* @param[in]    pWidget        The destination widget.
*
* @retval       None.
*
*/
void WdgTransitionSetOriginalWdg
(
    IWidget                 *pWDGTransition,
    IWidget                 *pWidget
);
/*=============================================================*/
/** WdgTransitionGetOriginalWdg
* @brief        Get the Original widget of transition widget
*               The transition effect will start to transit from "Original" to "pNewWdg of WdgTransitionSetWDGStart"
*
* @param[in]    pWDGTransition    The Transition widget
*
* @retval        The Original widget
*
*/
IWidget* WdgTransitionGetOriginalWdg
(
    IWidget                 *pWDGTransition
);

/** WdgTransitionRegisterTransitDoneCb
* @brief        Register callback : For transition widget, CB will be triggered when the transition is done.
*
* @param[in]    pWDGTransition    The Transition widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTransitionRegisterTransitDoneCb
(
    IWidget                     *pWDGTransition,
    PfnWdgTransitionTransitDone pfn,
    void                        *pUserData
);

/** WdgTransitionDeregisterTransitDoneCb
* @brief        Deregister PfnWdgTransitionTransitDone callback
*
* @param[in]    pWDGTransition    The Transition widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTransitionDeregisterTransitDoneCb
(
    IWidget                     *pWDGTransition,
    PfnWdgTransitionTransitDone pfn,
    void                        *pUserData
);

MAE_Ret WdgTransitionRegisterTransitCancelCb
(
 IWidget                     *pWDGTransition,
 PfnWdgTransitionTransitDone pfn,
 void                        *pUserData
 );

MAE_Ret WdgTransitionDeregisterTransitCancelCb
(
 IWidget                     *pWDGTransition,
 PfnWdgTransitionTransitDone pfn,
 void                        *pUserData
);

MAE_Ret WdgTransitionRegisterTransitSlipChangeCb
(
 IWidget                     *pWDGTransition,
 PfnWdgTransitionTransitDone pfn,
 void                        *pUserData
);

MAE_Ret WdgTransitionDeregisterTransitSlipChangeCb
(
 IWidget                     *pWDGTransition,
 PfnWdgTransitionTransitDone pfn,
 void                        *pUserData
);

void WdgTransitionSetAnimOffset
(
 IWidget                 *pWDGTransition,
 u16                     nAnimOffset
);

#if defined(__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_ANDROID_IDLE__)  || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
/** WdgTransitionStartIfoneSet
* @brief        Set left and right widget for ifone transition effect
*
* @param[in]    pWDGTransition    The Transition widget
* @param[in]    pWDGStart            Start effect
*                                    pWDGStart.type         : Transition type
*                                    pWDGStart.pLeftWdg   : Pointer of left IWidget to transit in
*                                    pWDGStart.pRightWdg  : Pointer of right IWidget to transit in
*                                    pWDGStart.duration     : Transition duration in msec
*                                    pWDGStart.xoffset      : Transition x position offset
*                                    pWDGStart.yoffset      : Transition y postition offset
*
*/
void WdgTransitionStartIfoneSet
(
    IWidget                      *pWDGTransition,
    WdgTransitionPosParam_t      *pWDGStart
);


/** WdgTransitionStartIfoneDraw
* @brief        Start ifone style transition
*
* @param[in]    pWDGTransition    The Transition widget
* @param[in]    pWDGStart            Start effect
*                                    pWDGStart.xoffset      : Transition x position offset
*                                    pWDGStart.yoffset      : Transition y postition offset
*/
void WdgTransitionStartIfoneDraw
(
    IWidget             *pWDGTransition,
    WdgTransitionPos_t  *pWDGStart
);

/** WdgTransitionStartIfoneEnd
* @brief        ifone style transition end
*
* @param[in]    pWDGTransition    The Transition widget
* @param[in]    dir                      Direction of transition
*
*/
void WdgTransitionStartIfoneEnd
(
    IWidget                 *pWDGTransition,
    TransitionDirection_t   dir
);
#endif /*#ifdef __UI_STYLE_MMI_IFONE__*/

void WdgTransitionSetSlipStart
(
 IWidget                      *pWDGTransition,
 WdgTransitionSlipParam_t      *pWDGStart
);

void WdgTransitionSetSlipDraw
(
 IWidget             *pWDGTransition,
 WdgTransitionPos_t  *pWDGStart,
 boolean             bSlip
);

void WdgTransitionSetSlipEnd
(
 IWidget                 *pWDGTransition,
 WdgTransitionSlipEndParam_t   *pWDGEnd
);

#endif //__MMI_WDG_TRANSITION_H__
