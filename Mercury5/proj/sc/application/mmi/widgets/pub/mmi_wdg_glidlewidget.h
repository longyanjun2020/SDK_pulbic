/**
 * @file    mae_glidlewidget.h
 * @brief   This file defines the interface of glidle widget
 * @author  otto.wu@mstarsemi.com
 * @version $Id: mae_glidlewidget.h $
 */

#ifndef __MMI_WDG_GLIDLEWIDGET_H__
#define __MMI_WDG_GLIDLEWIDGET_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_interfacemodel.h"
#include "mmi_mae_window.h"

// events
#define EVT_GLIDLE_LAUNCH_APP       (CLSID_GLIDLEWIDGET << 16 | 0x01)
#define EVT_GLIDLE_WALLPAPER_ID     (CLSID_GLIDLEWIDGET << 16 | 0x02)  
#define EVT_GLIDLE_CUBE_FOCUS_ID    (CLSID_GLIDLEWIDGET << 16 | 0x03)  
#define EVT_GLIDLE_WP_DECODE_DONE   (CLSID_GLIDLEWIDGET << 16 | 0x04)  

//typedef IWidget IBitmapWidget;
/*=============================================================*/
// type and define
/*=============================================================*/

#define GLIDLEWIDGET_BG_IMAGE_NUM 	2
#define GLIDLEWIDGET_CUBE_FACE_NUM 	5

enum
{
    PROP_GLIDLE_WDG_VIEW_TYPE=0,
    PROP_GLIDLE_WDG_WALLPAPER,
    PROP_GLIDLE_WDG_WALLPAPER_ID,
    PROP_GLIDLE_WDG_CUBE_FOCUS_ID,
	PROP_GLIDLE_WDG_WP_CID_LIST,
    PROP_GLIDLE_WDG_PET_VISIBLE,
    PROP_GLIDLE_WDG_WP_CALLBACK,
	PROP_GLIDLE_WDG_WINDMILL_LOCK_MODE,
	PROP_GLIDLE_WDG_WINDMILL_PAUSE,
    PROP_GLIDLE_WDG_RELEASE_WALLPAPER,
    PROP_GLIDLE_WDG_DISABLE_ANIMATION,
};
typedef u16 GlIdleWdg_Properity_e;

enum
{
    PROP_GLIDLE_WDG_VIEW_BASE=0,
    PROP_GLIDLE_WDG_VIEW_SCREENLOCK,
};
typedef u16 GlIdleWdg_ViewType_e;

enum
{
    ScreenLock_NotifyEvent_LaunchApp,
    ScreenLock_NotifyEvent_WallPaperId,
	ScreenLock_NotifyEvent_WPContentId,
    ScreenLock_NotifyEvent_CubeFocusId,
    ScreenLock_NotifyEvent_End
};
typedef u16 GlIdleWdg_NotifyEvent_e;

#define IGLIDLEWIDGET_QueryInterface(p,id,pp,pOwner)      IWIDGET_QueryInterface((IWidget*)p,id,pp,pOwner)
#define IGLIDLEWIDGET_HandleEvent(p,e,p1,p2)       IWIDGET_HandleEvent((IWidget*)p,e,p1,p2)
#define IGLIDLEWIDGET_SetHandler(p,pHD)            IWIDGET_SetHandler((IWidget*)p,pHD)

typedef MAE_Ret (*PfnGlIdleCacheWallpaperCb)(void *pUserData, IImage *pIImage, MAE_WChar *pUrl);
typedef MAE_Ret (*PfnGlIdleGetWallpaperCb)(void *pUserData, u32 nIndex, MAE_WChar **ppWallPaperUrl, boolean bLoadDefault);
typedef void (*PfnGlIdleWpDecodeDoneCb)(void *pUserData);

typedef struct
{
    PfnGlIdleCacheWallpaperCb pCacheWallPaperCb;
    PfnGlIdleGetWallpaperCb pGetWallPaperCb;
	PfnGlIdleWpDecodeDoneCb pWpDecodeDoneCb;
    void *pUserData;
}GlIdleCbData_t;

typedef struct
{
    IImage *pIImage;
    MAE_WChar *pUrl;
}GlIdleCacheWallpaperData_t;

/*! @brief This function sets bitmap to given IBitmapWidget
 *
 *  @param p     Pointer to the IBitmapWidget
 *  @param p1    Pointer to the IBitmap to set to IBitmapWidget
 *
 *  @return Always returns TRUE
 */
//#define IGLIDLEWIDGET_SetBitmap(p,p1) \
//	WdgCommonSetProperty((IWidget*)p, PROP_BMP_WDG_BITMAP, (u32)p1)
	//IWIDGET_HandleEvent((IWidget*)p,EVT_WIDGET_SET_PROPERTY,PROP_BMP_WDG_BITMAP,(u32)p1)

/*! @brief This function sets alignment to the bitmap widget
 *
 *  @param p     Pointer to the IBitmapWidget
 *  @param AF    alignment flag
 *
 *  @return Always returns TRUE
 *
 *  Note: pAF => u8
 */
#define IGLIDLEWIDGET_SetAlignment(p,AF) \
	WdgCommonSetAlignment((IWidget*)p, AF)
	//IWIDGET_HandleEvent((IWidget *)p,EVT_WIDGET_SET_PROPERTY,PROP_WDG_ALIGNMENT,(u32)AF)

/*! @brief This function gets the alignment flag of the given bitmap widget
 *
 *  @param p     Pointer to the IBitmapWidget
 *  @param pAF   Pointer to the memory to fill with alignment flag
 *
 *  @return Always returns TRUE
 *
 *  Note: pAF => u8 pointer
 */
#define IGLIDLEWIDGET_GetAlignment(p,pAF) \
	WdgCommonGetAlignment((IWidget *)p, pAF)
	//IWIDGET_HandleEvent((IWidget *)p,EVT_WIDGET_GET_PROPERTY,PROP_WDG_ALIGNMENT,(u32)pAF)


/*! @brief This function gets bitmap from the given IBitmapWidget
 *
 *  @param pWdg     Pointer to the IBitmapWidget
 *  @param pOwner   Pointer to the object which wants to get the IBitmap
 *
 *  @return the IBitmap in the interface model of the IBitmapWidget
 */
//IBitmap *IBITMAPWIDGET_GetBitmap(IWidget *pWdg, IBase *pOwner);
void WdgGlIdleAddForWnd(HWIN hWin,IWidget *pWidget,Pos_t *pPos,WidgetSize_t *pSize,u16 nWidgetID);
IWidget* WdgGlIdleCreateForWnd(HWIN hWin,Pos_t *pPos,WidgetSize_t *pSize,u16 nWidgetID);
IWidget* WdgGlIdleCreate(void);
IWidget* WdgGlIdleGetOPSlaveWdg(IWidget *pWDGGlIdle);
IWidget* WdgGlIdleGetOPMasterWdg(IWidget *pWDGGlIdle);
void WdgGlIdleSetViewType(IWidget *pWDGGlIdle, GlIdleWdg_ViewType_e eViewType);
void WdgGlIdleSetCubeFocusID(IWidget *pWDGGlIdle, u8 nCubeFucosID);
void WdgGlIdleSetPetVisible(IWidget *pWDGGlIdle, boolean bPetVisible);
void WdgGlIdleSetWindmillLockMode(IWidget *pWDGGlIdle, boolean bLockMode);
void WdgGlIdleSetWindmillPause(IWidget *pWDGGlIdle, boolean bPause);
void WdgGlIdleSetWPCallback(IWidget *pWDGGlIdle, u32 nCallbackAddr);
void WdgGlIdleSetWPCidList(IWidget *pWDGGlIdle, u32 nCidList);
void WdgGlIdleSetWP(IWidget *pWDGGlIdle, GlIdleCacheWallpaperData_t *pGlIdleCacheWallpaperData);
void WdgGlIdleSetWPID(IWidget *pWDGGlIdle, u32 nWPID);

void WdgGlIdleReleaseCacheWallpaper(IWidget *pWDGGlIdle, IImage *pIImage);
void WdgGlIdleDisableAnimation(IWidget *pWDGGlIdle);

#endif /* __MAE_GLIDLEWIDGET_H__ */
