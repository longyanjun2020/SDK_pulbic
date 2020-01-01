#ifndef __MMI_WDG_PROGRESS_PRIV_H__
#define __MMI_WDG_PROGRESS_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct{
    RGBColor_t ClrBorder;
    RGBColor_t ClrFill;
    u32 Flags;
}ProgressRectInfo;

#define MakeProgressRectInfo(pDst, CB, CF, FL) \
    do{(pDst)->ClrBorder = CB; \
       (pDst)->ClrFill = CF; \
       (pDst)->Flags = FL;}while(0)

typedef struct {
    WidgetBaseEx_t    WdgBase;
    u16 Total;
    u16 CurPos;
    u16 ProgressType;
    ProgressCellInfo CellInfo;
    ProgressCellInfo PreferCellInfo;
    boolean bPreferCellNum;	//the Last set cell info is CellNum=>TRUE, CellWidth=>FALSE
    IImage *pIBGImg;
    IImage *pIFGImg;
    ProgressRectInfo FGRectInfo;
    ProgressRectInfo BGRectInfo;
	ModelListener_t ThemeMdlLsn;	///< A model listener for Theme Manager
} WdgProgress_t;

/// move to mae_widget_custom.h
//#define PROGRESSWDG_AUTO_STEP_TIME   300

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret ProgressWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgProgressDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgProgressConstructor(WdgProgress_t *pThis);
void _WdgProgressDestructor(WdgProgress_t *pThis);

void _WdgProgressSetSize(IWidget *pIWidget, WidgetSize_t *pSize);
void _WdgProgressGetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);
void _WdgProgressDraw(IWidget *pIWidget, Wdg_Draw_Req_t *pReq);
void _WdgProgressNextStepCallBack(WdgProgress_t *pThis, void * pData);
void _WdgProgressUpdateCellInfo(WdgProgress_t *pThis, u16 NewBGWidth, ProgressCellInfo * pNewCellInfo);
void _WdgProgressGetBGDrawRect(WdgProgress_t *pThis, s32 WdgX, s32 WdgY, Rect_t *pBGRect);
boolean _WdgProgressGetFGDrawRect(WdgProgress_t *pThis, const Rect_t * pBGRect, Rect_t *pFGRect, s32 *pDrawX, s32 *pDrawY);
void _WdgProgressNewIImage(WdgProgress_t *pThis, IImage **ppImage, u16 * FileName);
boolean _WdgProgressSetProperty(WdgProgress_t *pThis, u32 P1, u32 P2);
boolean _WdgProgressGetProperty(WdgProgress_t *pThis, u32 P1, u32 P2);
static void _ProgressWidget_LoadResource(WdgProgress_t *pThis);

#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _ProgressWidget_ReloadRC(WdgProgress_t *pThis, DisplayMode_e nDispMode);
#endif //__AUTO_ROTATE_DISPLAY__

#endif //__MMI_WDG_PROGRESS_PRIV_H__
/*=============================================================*/
// end of file
