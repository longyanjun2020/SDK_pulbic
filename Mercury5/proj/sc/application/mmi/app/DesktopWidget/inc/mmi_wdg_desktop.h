/**
 * @file    mmi_wdg_desktop.h
 * @brief   This file defines the interface of desktopwidget.

 */

#ifndef __MMI_WDG_DESKTOP_H__
#define __MMI_WDG_DESKTOP_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mae_abscontainerbase.h"
#include "mmi_mae_datamodel.h"
#include "mmi_cfgsrv.h"
#include "mmi_wdg_headers.h"
#include "rs_layout_id.h"
#if defined(__FEATURE_MGL__)
#include "mgl_Utility_common.h"
#endif
#include "widgets_resource.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)

#define GADGET_TS_MOVE_TRESHOLD            10

#define PT_IN_RECT(ptX, ptY, rcX, rcY, rcW, rcH) \
	((u32)(ptX)>(u32)(rcX)) && ((u32)(ptX)<((u32)(rcX)+(u32)(rcW))) && \
	((u32)(ptY)>(u32)(rcY)) && ((u32)(ptY)<((u32)(rcY)+(u32)(rcH)))

typedef void (*FP_ShowSmallWdg)(void*);
typedef void (*FP_ShowLargeWdg)(void*);

#if defined(__UI_STYLE_MMI_ANDROID_IDLE__)
#define DECLARE_BASECLASS_DESKTOPWIDGET \
	AbsContainerBase_t    AbsCntrBase; \
	IAbsContainer    *pParentAbsContainer; \
	WPos_t            stMoveTempPos; \
	u16             uLeftLimit;\
    u16             uRightLimit;\
    u16             uTopLimit;\
    u16             uBottomLimit;\
	WPos_t            stDesktopWidgetPos; \
    WidgetSize_t    stMoveDistance; \
	WPos_t          stMoveBeginPos; \
	boolean            bTouchMoveStatus; \
	boolean            bTouchDragPosChanged; \
	boolean			 bResLoaded; \
	ITouchSrv        *pITouchSrv; \
	DesktopWdg_LaunchApp_Info_t launchApInfo; \
	ICFGSrv         *pICFGSrv; \
	u32                uWidgetPosCfgId; \
	u32                uDesktopWidgetId; \
	u32                uLargeBgImageId;    \
	u32                uSmallBgImageId;    \
	IWidget*        pIBgImageWidget;     \
	FP_ShowSmallWdg        fpShowSmallWdg; \
	FP_ShowLargeWdg        fpShowLargeWdg;\
	IBitmap         *pIDragBmp;\
    boolean 	     bUseSnapShot;\
	boolean         bDragMode;\
	boolean 			bUpdateMovingPos;

#elif defined(__FEATURE_MGL__)
#define DECLARE_BASECLASS_DESKTOPWIDGET \
	AbsContainerBase_t	AbsCntrBase; \
	IAbsContainer	*pParentAbsContainer; \
	WPos_t			stMoveTempPos; \
	u16             uLeftLimit;\
    u16             uRightLimit;\
    u16             uTopLimit;\
    u16             uBottomLimit;\
	WPos_t			stDesktopWidgetPos; \
	WPos_t          stMoveBeginPos; \
    WidgetSize_t    stMoveDistance; \
	boolean			bTouchMoveStatus; \
	boolean			bTouchDragPosChanged; \
    boolean			 bResLoaded; \
    ITouchSrv        *pITouchSrv; \
    DesktopWdg_LaunchApp_Info_t launchApInfo; \
    ICFGSrv         *pICFGSrv; \
    u32                uWidgetPosCfgId; \
    u32                uDesktopWidgetId; \
    u32                uLargeBgImageId;    \
    u32                uSmallBgImageId;    \
    IWidget*        pIBgImageWidget;     \
    FP_ShowSmallWdg        fpShowSmallWdg; \
    FP_ShowLargeWdg        fpShowLargeWdg; \
    boolean				bUpdateMovingPos; \
    mgl_u16 u16SceneHandleId; \
    u32 uIconAnimationFrame; \
    u32 uIconNodeID;\
    u32 uIconTextureId;\
    u32 uCurTouchEvt;\
    boolean bDragAnimation;\
    boolean bEditMode;\
    boolean bMoveCursorNotify;\
    boolean bHookTsEvent;\
    IBitmap *pIconBitmap;\
    boolean 	     bUseSnapShot;\
    IBitmap			*pIDragBmp;
#else
#define DECLARE_BASECLASS_DESKTOPWIDGET \
	AbsContainerBase_t	AbsCntrBase; \
	IAbsContainer	*pParentAbsContainer; \
	WPos_t			stMoveTempPos; \
	WPos_t			stDesktopWidgetPos; \
	WPos_t          stMoveBeginPos; \
    WidgetSize_t    stMoveDistance; \
	boolean			bTouchMoveStatus; \
	boolean			bTouchDragPosChanged; \
    boolean			 bResLoaded; \
	ITouchSrv		*pITouchSrv; \
	DesktopWdg_LaunchApp_Info_t launchApInfo; \
	ICFGSrv         *pICFGSrv; \
	u32				uWidgetPosCfgId; \
	u32				uDesktopWidgetId; \
	u32				uLargeBgImageId;	\
	u32				uSmallBgImageId;	\
	IWidget*        pIBgImageWidget;     \
	FP_ShowSmallWdg		fpShowSmallWdg; \
    FP_ShowLargeWdg        fpShowLargeWdg; \
	boolean 			bUpdateMovingPos;\
    IBitmap         *pIconBitmap;\
    boolean 	    bUseSnapShot;\
    IBitmap			*pIDragBmp;
#endif

enum
{
	//For Desktop widget properties
	PROP_OPDESKTOP_WDG_MASTER_UPDATE = 0,
	PROP_OPDESKTOP_WDG_SLAVE_UPDATE,
	PROP_DESKTOP_WDG_ID,
	PROP_DESKTOP_WDG_POS,
	PROP_DESKTOP_WDG_POS_RESET,
	PROP_DESKTOP_WDG_POS_CFGID,
	PROP_DESKTOP_WDG_SMALLBG_IMGID,
	PROP_DESKTOP_WDG_LARGEBG_IMGID,
	PROP_DESKTOP_WDG_DISPLAY_MODE,
	PROP_DESKTOP_WDG_LAUNCHAP_CLSID,
	PROP_DESKTOP_WDG_LAUNCHAP_PARAM,
	PROP_DESKTOP_WDG_STYEL,
	PROP_DESKTOP_WDG_SHOW_INFO_ICON,
	PROP_TABDESKTOP_WDG_TABPAGE,
	PROP_DCDESKTOP_WDG_SHOW_REVERSE,
    PROP_PHBDESKTOP_WDG_PHBSRV_READY,
    EVT_VIEWMDL_SLIDE_START,         //Pair of EVT_VIEWMDL_SLIDE_COMPLETE
    PROP_PHBDESKTOP_WDG_UPDATE_CONTACTLIST,
    PROP_PHOTODESKTOP_WDG_URLINFO_IDX,
    PROP_PHOTODESKTOP_WDG_URLINFO_URL,
    PROP_PHOTODESKTOP_WDG_UPDATE_FILELIST,
#if defined(__3D_UI_IDLE_MULTIPAGE__)
    PROP_DESKTOP_WDG_ENABLE_EDIT_MODE,
    PROP_SHORTCUTDESKTOP_WDG_SHORTCUT_ID,
#endif
};

enum
{
	DesktopWidget_InputEvent_Begin = 0,
	DesktopWidget_InputEvent_LaunchApp,
	DesktopWidget_InputEvent_Touch_ReleaseIn,
	DesktopWidget_InputEvent_Touch_ReleaseOut,
	DesktopWidget_InputEvent_Touch_MoveToTop,
	DesktopWidget_InputEvent_Touch_Release,

	MpDesktopWidget_InputEvent_AdjustVolume,
	MpDesktopWidget_InputEvent_DeviceNotSupported,

	FmDesktopWidget_InputEvent_AdjustVolume,
	FmDesktopWidget_InputEvent_NoticePlugEarpiece,
	FmDesktopWidget_InputEvent_NoticeAirplaneMode,
	DesktopWidget_InputEvent_Switch_ObverseSide,
	DesktopWidget_InputEvent_Switch_ReverseSide,

#if defined(__3D_UI_IDLE_MULTIPAGE__)
    DesktopWidget_InputEvent_AlignPosToCenter,
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)

	DesktopWidget_InputEvent_End
};
typedef u16 DesktopWidget_InputEvent_e;

// All desktop widget IDs
enum
{
	DesktopWidgetID_Begin = 0,
	DesktopWidgetID_Mplayer = DesktopWidgetID_Begin,
	DesktopWidgetID_FmRadio,
	DesktopWidgetID_Search,
	DesktopWidgetID_Map,
	DesktopWidgetID_Calendar,
    DesktopWidgetID_ToDoList,
    DesktopWidgetID_QQ,
	DesktopWidgetID_Note,
	DesktopWidgetID_Operator,
	DesktopWidgetID_DigitalClock,
	DesktopWidgetID_AnalogClock,
    DesktopWidgetID_PageClock,
	DesktopWidgetID_Profile,
	DesktopWidgetID_Game,
    DesktopWidgetID_LiveWallPaper,
    DesktopWidgetID_WorldClock01,
    DesktopWidgetID_WorldClock02,
    DesktopWidgetID_WorldClock03,
    DesktopWidgetID_Phonebook,
    DesktopWidgetID_Photo,
    DesktopWidgetID_Message,
    DesktopWidgetID_Notepad,
	DesktopWidgetID_Num
};
typedef u16 DesktopWidgetID_e;

enum  // tabDesktopWdgId
{
	TabDesktopWidgetID_Tab0,
	TabDesktopWidgetID_Tab1,
	TabDesktopWidgetID_Tab2,
	TabDesktopWidgetID_Num
};
typedef u16 TabDesktopWidgetID_e;


enum
{
	DesktopWidget_Display_Invalid = 0,
	DesktopWidget_Display_Small_Mode,
	DesktopWidget_Display_Large_Mode,
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
	DesktopWidget_Display_Drag_Mode
#endif

};
typedef u16 DesktopWidget_DisplayMode_e;

enum
{
    DCLOCK_WDG_STYLE_ONLY_TIME,
    DCLOCK_WDG_STYLE_GREEN,
#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
    DCLOCK_WDG_STYLE_CIRCLE_SMALL,
    DCLOCK_WDG_STYLE_CIRCLE_LARGE,
    DCLOCK_WDG_STYLE_WBLACK_SMALL,
    DCLOCK_WDG_STYLE_WBLACK_LARGE,
    DCLOCK_WDG_STYLE_PAGE,
    DCLOCK_WDG_STYLE_SIMPLE,    
#elif defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
    DCLOCK_WDG_STYLE_WBLACK_LARGE, // Android 4.0 only use world clock
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)

    DCLOCK_WDG_STYLE_NUM
};
typedef u16 DClockDesktopWidget_Style_e;

enum
{
    ACLOCK_WDG_STYLE_5,
#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
    ACLOCK_WDG_STYLE_TRANSSLIVER_SMALL,
    ACLOCK_WDG_STYLE_TRANSSLIVER_LARGE,
    ACLOCK_WDG_STYLE_WANALOGBLACK_SMALL,
    ACLOCK_WDG_STYLE_WANALOGBLACK_LARGE,
    ACLOCK_WDG_STYLE_SIMPLE_LARGE,    
#elif defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
    ACLOCK_WDG_ANDROID_STYLE,
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)
    ACLOCK_WDG_STYLE_NUM
};
typedef u16 AClockDesktopWidget_Style_e;

enum
{
#if defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
    CALENDAR_WDG_STYLE_SMALL, // Only use small style
#else
    CALENDAR_WDG_STYLE_SMALL,
    CALENDAR_WDG_STYLE_LARGE,
#endif // __UI_STYLE_MMI_ANDROID_4_0_GADGET__
    CALENDAR_WDG_STYLE_SIMPLE,    
    CALENDAR_WDG_STYLE_NUM
};
typedef u16 CalendarDesktopWidget_Style_e;

enum
{
    PROFILE_WDG_STYLE_GRAY,
    PROFILE_WDG_STYLE_SILVER
};
typedef u16 ProfileDesktopWidget_Style_e;

enum
{
#ifdef __UI_STYLE_MMI_ANDROID_4_0_GADGET__
    MPLAYER_WDG_STYLE_SMALL, // Only use small style
#else
    MPLAYER_WDG_STYLE_GREEN,
    MPLAYER_WDG_STYLE_YELLOW,
#if defined(__3D_UI_IDLE_MULTIPAGE__)
    MPLAYER_WDG_STYLE_SMALL,
    MPLAYER_WDG_STYLE_LARGE,
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)
#endif // End of __UI_STYLE_MMI_ANDROID_4_0_GADGET__
    MPLAYER_WDG_STYLE_NUM
};
typedef u16 MplayerDesktopWidget_Style_e;

enum
{
#if defined(__3D_UI_IDLE_MULTIPAGE__)
    FM_WDG_STYLE_SMALL,
    FM_WDG_STYLE_LARGE,
#elif defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
    FM_WDG_STYLE_LARGE, // Only use large style
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)

    FM_WDG_STYLE_NUM
};
typedef u16 FmDesktopWidget_Style_e;

enum
{
    OP_WDG_STYLE_BLACK,
    OP_WDG_STYLE_SILVER
};
typedef u16 OpDesktopWidget_Style_e;

typedef struct _DesktopWdg_LaunchApp_Info
{
	boolean bIsStartEx;
	MAEClsId_t apClsid;
	u32 uParam;								// Only used in startEx
	PfnStartParamCleanup fnClean;			// Only used in startEx

}DesktopWdg_LaunchApp_Info_t;

// For storing subwidget position and dimension
typedef struct _Subwidget_Geometry_Info_
{
	IWidget* pIWidget;
	Rect_t rcWidget;
	WidgetHandler_t handler;
	boolean bIsEnable;		// If this subwidget handles event
}Subwidget_Geometry_Info;

typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET
} DesktopWdg_t;

/*=============================================================*/
// type and define
/*=============================================================*/
/** PfnWdgDesktopTouchReleaseIn
* @brief      CB register by "WdgDesktopRegisterTouchReleaseInCb"
*             and will be trigger when user release touch inside the region of widget.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pMoveData         The info of touch release inside the region of widget., refer to ShortMoveData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgDesktopTouchReleaseIn) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pMoveData, IWidget *pWidget);

/** PfnWdgDesktopTouchReleaseOut
* @brief      CB register by "WdgDesktopRegisterTouchReleaseOutCb"
*             and will be trigger when user release touch outside the region of widget.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pMoveData         The info of touch release outside the region of widget, refer to ShortMoveData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgDesktopTouchReleaseOut) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pMoveData ,IWidget *pWidget);

/** PfnWdgDesktopTouchRelease
* @brief      CB register by "WdgDesktopRegisterTouchReleaseCb"
*             and will be trigger when user release touch.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pMoveData         The info of touch release, refer to ShortMoveData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgDesktopTouchRelease) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pMoveData ,IWidget *pWidget);

/** PfnWdgDesktopTouchMoveToTop
* @brief      CB register by "WdgDesktopRegisterTouchMoveToTopCb"
*             and will be trigger when widget be touched.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pDesktopWdg       The touched widget, refer to DesktopWdg_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgDesktopTouchMoveToTop) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, DesktopWdg_t *pDesktopWdg, IWidget *pWidget);

/** PfnWdgDesktopLaunchApplet
* @brief      CB register by "WdgDesktopRegisterLaunchAppletCb"
*             and will be trigger when widget be touched.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pLaunchApInfo     The info of launch application, refer to DesktopWdg_LaunchApp_Info_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgDesktopLaunchApplet) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, DesktopWdg_LaunchApp_Info_t *pLaunchApInfo, IWidget *pWidget);

#if defined(__3D_UI_IDLE_MULTIPAGE__)
/** PfnWdgDesktopAlignPosToCenter
* @brief      CB register by "WdgDesktopRegisterAlignPosToCenterCb"
*             and will be trigger when widget be touched.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pDesktopWdg       The touched widget, refer to DesktopWdg_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgDesktopAlignPosToCenter) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, DesktopWdg_t *pDesktopWdg, IWidget *pWidget);
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/
void DesktopWidget_Draw(IAbsContainer*, IDispCanvas*, s32, s32);

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
MAE_Ret DesktopWidget_Ctor(DesktopWdg_t*);
void DesktopWidget_Dtor(DesktopWdg_t*);

boolean DesktopWidget_DefHandleEvent(IAbsContainer*, MAEEvent_t, u32, u32);
boolean DesktopWidget_HandleTouchEvent(DesktopWdg_t*, MAE_EventId, u32, u32);
void DesktopWidget_TouchUpdatePosition(DesktopWdg_t*, s32, s32);
boolean DesktopWidget_TouchInSubwidget(DesktopWdg_t*, u32, u32);
boolean DesktopWidget_HandleSubwidgetEvent(DesktopWdg_t*, MAE_EventId, u32, u32);
void DesktopWidget_SetParent(IAbsContainer*, IContainer*);
boolean DesktopWidget_IsPositionInShortcut(DesktopWdg_t*, MAE_EventId, s32, s32);
MAE_Ret DesktopWidget_LoadImg(DesktopWdg_t *pThis, IWidget *pImgWdg, u32 uBgImageId);
void DesktopWidget_AdjustPosition(IWidget* pIWidget);

/** WdgDesktopRegisterTouchReleaseInCb
* @brief        Register callback : CB will be triggered when user release touch inside the region of widget.
*
* @param[in]    pWDGDesktop   The Desktop widget which want to set callback
* @param[in]    pfn                callback function
* @param[in]    pUsrData           User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS    Success
* @retval       others             Failed
*
*/
MAE_Ret WdgDesktopRegisterTouchReleaseInCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopTouchReleaseIn    pfn,
    void                    *pUserData
);

/** WdgDesktopRegisterTouchReleaseOutCb
* @brief        Register callback : CB will be triggered when user release touch outside the region of widget.
*
* @param[in]    pWDGDesktop   The Desktop widget which want to set callback
* @param[in]    pfn                callback function
* @param[in]    pUsrData           User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS    Success
* @retval       others             Failed
*
*/
MAE_Ret WdgDesktopRegisterTouchReleaseOutCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopTouchReleaseOut   pfn,
    void                    *pUserData
);

/** WdgDesktopRegisterTouchReleaseCb
* @brief        Register callback : CB will be triggered when user release touch.
*
* @param[in]    pWDGDesktop  The Desktop widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDesktopRegisterTouchReleaseCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopTouchRelease  pfn,
    void                    *pUserData
);

/** WdgDesktopRegisterTouchMoveToTopCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement move to top function for the widget.
*
* @param[in]    pWDGDesktop  The Desktop widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDesktopRegisterTouchMoveToTopCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopTouchMoveToTop    pfn,
    void                    *pUserData
);

/** WdgDesktopRegisterLaunchAppletCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching specific app function.
*
* @param[in]    pWDGDesktop   The Desktop widget which want to set callback
* @param[in]    pfn                callback function
* @param[in]    pUsrData           User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS    Success
* @retval       others             Failed
*
*/
MAE_Ret WdgDesktopRegisterLaunchAppletCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopLaunchApplet  pfn,
    void                    *pUserData
);

#if defined(__3D_UI_IDLE_MULTIPAGE__)
/** WdgDesktopRegisterAlignPosToCenterCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching specific app function.
*
* @param[in]    pWDGDesktop   The Desktop widget which want to set callback
* @param[in]    pfn                callback function
* @param[in]    pUsrData           User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS    Success
* @retval       others             Failed
*
*/
MAE_Ret WdgDesktopRegisterAlignPosToCenterCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopAlignPosToCenter  pfn,
    void                        *pUserData
);
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)

/** WdgDesktopDeregisterTouchReleaseInCb
* @brief        Deregister callback
*
* @param[in]    pWDGDesktop   The Desktop widget which want to deregister callback
* @param[in]    pfn                callback function
* @param[in]    pUsrData           User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS    Success
* @retval       others             Failed
*
*/
MAE_Ret WdgDesktopDeregisterTouchReleaseInCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopTouchReleaseIn    pfn,
    void                    *pUserData
);

/** WdgDesktopDeregisterTouchReleaseOutCb
* @brief        Deregister callback
*
* @param[in]    pWDGDesktop   The Desktop widget which want to deregister callback
* @param[in]    pfn                callback function
* @param[in]    pUsrData           User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS    Success
* @retval       others             Failed
*
*/
MAE_Ret WdgDesktopDeregisterTouchReleaseOutCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopTouchReleaseOut   pfn,
    void                    *pUserData
);

/** WdgDesktopDeregisterTouchReleaseCb
* @brief        Deregister callback
*
* @param[in]    pWDGDesktop  The Desktop widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDesktopDeregisterTouchReleaseCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopTouchRelease  pfn,
    void                    *pUserData
);

/** WdgDesktopDeregisterTouchMoveToTopCb
* @brief        Deregister callback
*
* @param[in]    pWDGDesktop    The Desktop widget which want to deregister callback
* @param[in]    pfn                 callback function
* @param[in]    pUsrData            User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgDesktopDeregisterTouchMoveToTopCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopTouchMoveToTop    pfn,
    void                    *pUserData
);

/** WdgDesktopDeregisterLaunchAppletCb
* @brief        Deregister callback
*
* @param[in]    pWDGDesktop  The Desktop widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDesktopDeregisterLaunchAppletCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopLaunchApplet  pfn,
    void                    *pUserData
);

#if defined(__3D_UI_IDLE_MULTIPAGE__)
/** WdgDesktopDeregisterAlignPosToCenterCb
* @brief        Deregister callback
*
* @param[in]    pWDGDesktop  The Desktop widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgDesktopDeregisterAlignPosToCenterCb
(
    IWidget                 *pWDGDesktop,
    PfnWdgDesktopAlignPosToCenter  pfn,
    void                        *pUserData
);
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)

boolean DesktopWidget_IsUseSnapshot(DesktopWdg_t *pThis);
void DesktopWidget_SetUseSnapshot(DesktopWdg_t *pThis, boolean bUseSnapShot);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__ || __3D_UI_IDLE_SIMPLE__

#endif //__MMI_WDG_DESKTOP_H__
/*=============================================================*/
// end of file
