/**
 * @file mmi_wdg_scrollbar_priv.h
 * @brief This file defines the data structure of scroll bar widget
 *
 * @version $Id: mmi_wdg_scrollbar_priv.h 29550 2009-04-29 07:59:45Z steve.lee $
 */
#ifndef __MMI_WDG_SCROLLBAR_PRIV_H__
#define __MMI_WDG_SCROLLBAR_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_image.h"
#include "mmi_wdg_scrollbar.h"
#include "mae_scrollcommon.h"

/*=============================================================*/
// type and define
/*=============================================================*/
//#define TouchScreenLongPressTime  300
//==>deprecated, use...

typedef struct{
    u32 nVisible;   //number of items in the visible range
    u32 nTotal;     //number of total items
    u32 nPos;       //current position 0-based, if Scroll Change, the nPos means top Pos
    u16 nStep;
    boolean bHdlFcsEvt; //if TRUE check Focus change event, if FALSE check Scroll Change event
}ScrollInfo;

#define SCROLL_SIZE_PRESS_NONE  SCROLL_PRESS_NONE
#define SCROLL_SIZE_PRESS_DOWN  SCROLL_PRESS_DOWN
#define SCROLL_SIZE_ALL_STYLE SCROLL_PRESS_STYLE
#define SCROLL_SIZE_TOTAL SCROLL_SIZE_ALL_STYLE+1


#define SCROLL_ELEMENT_BAR   1
#define SCROLL_ELEMENT_IND   2
#define SCROLL_ELEMENT_ARROW 4

typedef struct{
    s32 IndTPOffset[SCROLL_DIR_NUM];  //The Offset of Touch Press position and the Indication Start Pos, 0=>horizontal Ind X Offset, 1=>vertical Ind Y Offset
    s32 IndStartPos[SCROLL_DIR_NUM]; //0=>horizontal Ind X, 1=>vertical Ind Y, include the HorBarX/VerBarY
    u32 IndSize[SCROLL_DIR_NUM]; //0=>horizontal Ind Width, 1=>vertical Ind Height
}ScrollIndData_t;

typedef enum{
    Scroll_E_TS_Press_NONE=0,
    Scroll_E_TS_Press_Previous,
    Scroll_E_TS_Press_Next,
}Scroll_TSPress_e;

typedef struct{
    //boolean bTSPressOnChild;
    boolean bTSScrollAbility[SCROLL_DIR_NUM]; //Touch the Scroll bar/arrow/ind to move the scroll pos
    boolean bTSPressOnInd[SCROLL_DIR_NUM];   //0=>horizontal, 1=>vertical
    Scroll_TSPress_e bTSPressOnArrow[SCROLL_DIR_NUM];   //
    Scroll_TSPress_e bTSPressOnBar[SCROLL_DIR_NUM];   //
    s32 BarTSPos[SCROLL_DIR_NUM]; //include the Bar Start Pos (HorBarX/VerBarY) => for the TS Prss On Bar
}TSPressInfo_t;

typedef struct{
    boolean bReady;
    ScrollArrow_Imgs_t Imgs;
}Scrollbar_ArrowImgs_Info_t;

typedef struct{
    boolean bReady;
    ScrollBarInd_Imgs_t Imgs;
}Scrollbar_BarIndImgs_Info_t;

typedef enum
{
    Scroll_e_Img_Start=0,
    Scroll_e_Img_Repeat,
    Scroll_e_Img_Center,
    Scroll_e_Img_End,
    Scroll_e_Img_Previous_Arrow,
    Scroll_e_Img_Next_Arrow
}Scrollbar_BarIndImg_Type_e;

typedef struct{
   WidgetSize_t StartImg[SCROLL_SIZE_TOTAL];
   WidgetSize_t RepeatImg[SCROLL_SIZE_TOTAL];
   WidgetSize_t CenterImg[SCROLL_SIZE_TOTAL];
   WidgetSize_t EndImg[SCROLL_SIZE_TOTAL];
   boolean bDynamicSize[SCROLL_PRESS_STYLE];
   WidgetSize_t MinElement[SCROLL_SIZE_TOTAL];
}Scrollbar_BarIndImg_Sizt_t;

typedef struct{
   WidgetSize_t Previous[SCROLL_SIZE_TOTAL];
   WidgetSize_t Next[SCROLL_SIZE_TOTAL];
   WidgetSize_t CurrentElement[SCROLL_SIZE_TOTAL];
}Scrollbar_ArrowImg_Sizt_t;

typedef struct{
    Rect_t ChildRect;
    Rect_t BarRect[SCROLL_DIR_NUM];
    s32 nX;
    s32 nY;
}Scrollbar_Layout_t;

typedef enum
{
    MAE_SCROLLBAR_IND_IMAGE_START,
    MAE_SCROLLBAR_IND_IMAGE_END,
    MAE_SCROLLBAR_IND_IMAGE_CENTER,
    MAE_SCROLLBAR_IND_IMAGE_REPERT
} MaeScrollbarIndImageType_e;

typedef struct {
    DecoratorEx_t DecBase;
    Scrollbar_ArrowImgs_Info_t ArrowImg[SCROLL_DIR_NUM];
    Scrollbar_BarIndImgs_Info_t BarImg[SCROLL_DIR_NUM];
    Scrollbar_BarIndImgs_Info_t IndImg[SCROLL_DIR_NUM];

    Scrollbar_ArrowImg_Sizt_t ArrowSize[SCROLL_DIR_NUM];
    Scrollbar_BarIndImg_Sizt_t BarSize[SCROLL_DIR_NUM];
    Scrollbar_BarIndImg_Sizt_t IndSize[SCROLL_DIR_NUM];

    ScrollBarRectInfo BarInfo;   //if the pImg_XXXBar doesn't set, draw the rect instead of the bar image
    ScrollBarRectInfo IndInfo;  //if the pImg_XXXIndicator doesn't set, draw the rect instead of the Indicator image

    boolean bKeppSpace[SCROLL_DIR_NUM];  //0=>horizontal, 1=>vertical
    Scrollbar_Layout_t layout;

    ScrollInfo scrollInfo[SCROLL_DIR_NUM]; //0=>horizontal, 1=>vertical

    ModelListener_t ScrollMdlLsn; //the model listener

    ScrollIndData_t ScrollIndData;

	ModelListener_t ThemeMdlLsn;	///< A model listener for Theme Manager
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
#ifdef __TOUCH_SCREEN_MMI__
    TSPressInfo_t TSPressInfo;
	ITouchSrv *pITouchSrv;
	u8 bUpdateScrlDataTimerRunning;
	u8 nScrlDirToUpdate;
#endif
    u8 ScrollStyle;

    IBitmap *pBitmap; //tmp bitmap for G3D

#ifdef __FADE_OUT_SCROLLBAR__
    // fade out animation step
    u8 nAlpha;
#endif // __FADE_OUT_SCROLLBAR__

} ScrollbarWidget_t;

#ifdef __TOUCH_SCREEN_MMI__
#define SCROLLBAR_IS_TS_PRESS(pThis, ScrollType)   (Scroll_E_TS_Press_NONE!=pThis->TSPressInfo.bTSPressOnBar[ScrollType] || Scroll_E_TS_Press_NONE!=pThis->TSPressInfo.bTSPressOnArrow[ScrollType] ||  pThis->TSPressInfo.bTSPressOnInd[ScrollType])
#endif

// RELOAD flag
enum
{
	SCROLLBAR_WDG_RELOAD_FLAG_START = 0,
	SCROLLBAR_WDG_RELOAD_FLAG_BARINFO = SCROLLBAR_WDG_RELOAD_FLAG_START,   ///< BarInfo
	SCROLLBAR_WDG_RELOAD_FLAG_INDINFO,	///< IndInfo
	SCROLLBAR_WDG_RELOAD_FLAG_SCROLLSTYLE,	///< ScrollStyle
	SCROLLBAR_WDG_RELOAD_FLAG_BARSIZE,	///< BarSize
	SCROLLBAR_WDG_RELOAD_FLAG_INDSIZE,	///< IndSize
	SCROLLBAR_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define SCROLLBAR_WDG_RELOAD_MASK_BARINFO         (1<<SCROLLBAR_WDG_RELOAD_FLAG_BARINFO)
#define SCROLLBAR_WDG_RELOAD_MASK_INDINFO        (1<<SCROLLBAR_WDG_RELOAD_FLAG_INDINFO)
#define SCROLLBAR_WDG_RELOAD_MASK_SCROLLSTYLE         (1<<SCROLLBAR_WDG_RELOAD_FLAG_SCROLLSTYLE)
#define SCROLLBAR_WDG_RELOAD_MASK_BARSIZE         (1<<SCROLLBAR_WDG_RELOAD_FLAG_BARSIZE)
#define SCROLLBAR_WDG_RELOAD_MASK_INDSIZE         (1<<SCROLLBAR_WDG_RELOAD_FLAG_INDSIZE)
/**
* Macro to get flag value
*/
#define SCROLLBAR_WDG_BARINFO_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&SCROLLBAR_WDG_RELOAD_MASK_BARINFO)>>SCROLLBAR_WDG_RELOAD_FLAG_BARINFO)
#define SCROLLBAR_WDG_INDINFO_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLBAR_WDG_RELOAD_MASK_INDINFO)>>SCROLLBAR_WDG_RELOAD_FLAG_INDINFO)
#define SCROLLBAR_WDG_SCROLLSTYLE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLBAR_WDG_RELOAD_MASK_SCROLLSTYLE)>>SCROLLBAR_WDG_RELOAD_FLAG_SCROLLSTYLE)
#define SCROLLBAR_WDG_BARSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLBAR_WDG_RELOAD_MASK_BARSIZE)>>SCROLLBAR_WDG_RELOAD_FLAG_BARSIZE)
#define SCROLLBAR_WDG_INDSIZE_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SCROLLBAR_WDG_RELOAD_MASK_INDSIZE)>>SCROLLBAR_WDG_RELOAD_FLAG_INDSIZE)
/**
* Macro to Set flag value
*/
#define SCROLLBAR_WDG_BARINFO_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLBAR_WDG_RELOAD_MASK_BARINFO))|(((u32)_b)<<SCROLLBAR_WDG_RELOAD_FLAG_BARINFO)
#define SCROLLBAR_WDG_INDINFO_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLBAR_WDG_RELOAD_MASK_INDINFO))|(((u32)_b)<<SCROLLBAR_WDG_RELOAD_FLAG_INDINFO)
#define SCROLLBAR_WDG_SCROLLSTYLE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLBAR_WDG_RELOAD_MASK_SCROLLSTYLE))|(((u32)_b)<<SCROLLBAR_WDG_RELOAD_FLAG_SCROLLSTYLE)
#define SCROLLBAR_WDG_BARSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLBAR_WDG_RELOAD_MASK_BARSIZE))|(((u32)_b)<<SCROLLBAR_WDG_RELOAD_FLAG_BARSIZE)
#define SCROLLBAR_WDG_INDSIZE_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SCROLLBAR_WDG_RELOAD_MASK_INDSIZE))|(((u32)_b)<<SCROLLBAR_WDG_RELOAD_FLAG_INDSIZE)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret ScrollbarWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean ScrollbarWidget_HandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret ScrollbarWidgetStrucCtor(ScrollbarWidget_t *pThis);
void ScrollbarWidgetStrucDtor(ScrollbarWidget_t *pThis);

__SLDPM_FREE__ void ScrollbarWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);

void ScrollbarWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
__SLDPM_FREE__ boolean ScrollbarWidget_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
__SLDPM_FREE__ void ScrollbarWidget_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);

__SLDPM_FREE__ void ScrollbarWidget_SetWidget(IDecorator *pIDecorator, IWidget *pChild);

__SLDPM_FREE__ void ScrollbarContainer_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);

__SLDPM_FREE__ static void ScrollbarWidget_ModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
__SLDPM_FREE__ static boolean ScrollbarWidget_IsVisible(ScrollbarWidget_t *pThis, u8 ScrollType);
//static MAE_Ret ScrollbarWidget_GetScrollElementSize(ScrollbarWidget_t *pThis, u8 ScrollType, u8 ElementType, u32* width, u32* height, boolean bCareVisible);
__SLDPM_FREE__ static void ScrollbarWidget_GetNewLayoutRect(ScrollbarWidget_t *pThis, Rect_t *pChildRect, Rect_t *pVerBarRect, Rect_t *pHorBarRect);
//static MAE_Ret ScrollbarWidget_DrawImage(IImage *pImage, IDispCanvas *pIDispCanvas, Rect_t *pBarRect);
__SLDPM_FREE__ static void ScrollbarWidget_DrawScrollBar(ScrollbarWidget_t *pThis, IDispCanvas *pIDispCanvas, s32 x, s32 y, Rect_t ChildRect);
static void ScrollbarWidget_DrawScrollElementBarInd(ScrollbarWidget_t *pThis, IDisplay *pIDisplay, s32 x, s32 y, u8 ScrollType, u8 ElementType, boolean bPressed, boolean b3D);
static void ScrollbarWidget_DrawSubBarIndImg(ScrollbarWidget_t *pThis, IDisplay *pIDisplay, IImage *pImage, WidgetSize_t ImgSize, boolean bRepeat, u8 ScrollType, s32 SubLayoutSize, Rect_t LayoutRect, boolean b3D);
#ifndef __FADE_OUT_SCROLLBAR__
static void ScrollbarWidget_DrawScrollElementArrow(ScrollbarWidget_t *pThis, IDisplay *pIDisplay, s32 x, s32 y, u8 ScrollType, boolean bPreviousArrow, boolean bPressed, boolean b3D);
#endif
__SLDPM_FREE__ static void ScrollbarWidget_DrawImg(ScrollbarWidget_t *pThis, IImage *pIImage, IDisplay *pIDisplay, Rect_t LayoutRect, Rect_t ImageRect, u8 ScrollType, Rect_t *pDrawRect, boolean b3D);
#if defined(__G3D_MMI__)
static void ScrollbarWidget_DrawRect(ScrollbarWidget_t *pThis, IDisplay *pIDisplay, const Rect_t *pRC, ScrollBarRectInfo *pRcInfo, boolean b3D);
#endif

__SLDPM_FREE__ static void ScrollbarWidget_UpdateScrollIndSize(ScrollbarWidget_t *pThis, u8 ScrollType);
__SLDPM_FREE__ static void ScrollbarWidget_UpdateScrollIndStartPos(ScrollbarWidget_t *pThis, u8 ScrollType);
static MAE_Ret ScrollbarWidget_GetScrollPosByTouchPos(ScrollbarWidget_t *pThis, u8 ScrollType, s32 TSPos, boolean bIndStartPos, u32 *pScrollPos);
static MAE_Ret ScrollbarWidget_ResetScrollPosByTouchPos(ScrollbarWidget_t *pThis, u8 ScrollType, boolean bNewPos, s32 Pos);
static void ScrollbarWidget_CalWidgetSize(ScrollbarWidget_t * pThis, WidgetSize_t * pWidgetSize, WidgetSize_t * pContentSize);
__SLDPM_FREE__ static void ScrollbarWidget_GetScrollMinLayout(ScrollbarWidget_t * pThis, u32 *pHor_height, u32 *pVer_width);
__SLDPM_FREE__ static void ScrollbarWidget_DoLayout(ScrollbarWidget_t * pThis, boolean bUpdateVerInd, boolean bUpdateHorInd);
__SLDPM_FREE__ static void ScrollbarWidget_GetChildScrollInfo(ScrollbarWidget_t *pThis);
#ifdef __TOUCH_SCREEN_MMI__
static boolean ScrollbarWidget_TSPress(ScrollbarWidget_t *pThis, s32 X, s32 Y);
static void ScrollbarWidget_ResetTSPressInfo(ScrollbarWidget_t *pThis);
static boolean ScrollbarWidget_TSMoveOrRelease(ScrollbarWidget_t *pThis, MAE_EventId evt, s32 X, s32 Y);
static void ScrollbarWidget_TSArrowLongPress(void * pUser);
static void ScrollbarWidget_TSBarLongPress(void * pUser);
static void _ScrlbarWdg_ScrlUpdateTimeout(void *pUser);
static void _ScrlbarWdg_UpdateScrollDataToChild(ScrollbarWidget_t *pThis, u8 nScrollDir);
#endif /* __TOUCH_SCREEN_MMI__ */

__SLDPM_FREE__ static boolean ScrollbarWidget_UpdateScrollElement(ScrollbarWidget_t *pThis, u8 ScrollType, u8 ElementType, void *pImgs);
__SLDPM_FREE__ static boolean ScrollbarWidget_UpdateElementImgs(ScrollbarWidget_t *pThis, u8 ScrollType, u8 ElementType, void *pImgs);
__SLDPM_FREE__ static void ScrollbarWidget_UpdateImgsSizeInfo(ScrollbarWidget_t *pThis, u8 ScrollType, u8 ElementType);
__SLDPM_FREE__ static void ScrollbarWidget_UpdateImgSizeInfoByImgType(void *pImgsInfo, void *pSize, Scrollbar_BarIndImg_Type_e ImgType);

__SLDPM_FREE__ static void ScrollbarWidget_ReleaseBarIndImgs(ScrollbarWidget_t *pThis, ScrollBarInd_Imgs_t * pBarIndImgs);
__SLDPM_FREE__ static void ScrollbarWidget_ReleaseArrowImgs(ScrollbarWidget_t *pThis, ScrollArrow_Imgs_t * pArrowImgs);

__SLDPM_FREE__ static void _ScrollbarWidget_LoadResource(ScrollbarWidget_t *pThis);

#ifndef __FADE_OUT_SCROLLBAR__
static void _ScrollbarWidget_DecodeArrowImgs(ScrollbarWidget_t *pThis, u8 u8ScrollDir, boolean bUpImage, u8 u8PressStyle, WidgetSize_t sSize);
#endif
__SLDPM_FREE__ static void _ScrollbarWidget_DecodeBarIndImgs(ScrollbarWidget_t *pThis, u8 u8ScrollDir, u8 u8ElementType, u8 u8PressStyle, MaeScrollbarIndImageType_e eType, WidgetSize_t sSize);

__SLDPM_FREE__ static void _ScrollbarWidget_FreeDecodeImgs(ScrollbarWidget_t *pThis);

#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _ScrollbarWidget_ReloadRC(ScrollbarWidget_t *pThis, DisplayMode_e nDispMode);
#endif // __AUTO_ROTATE_DISPLAY__
boolean ScrollbarWidget_NotifyScrollFinish(ScrollbarWidget_t *pThis, u32 nParam);

#endif //__MMI_WDG_SCROLLBAR_PRIV_H__
/*=============================================================*/
// end of file
