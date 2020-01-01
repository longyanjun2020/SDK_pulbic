#ifndef __MMI_WDG_BITMAP_PRIV_H__
#define __MMI_WDG_BITMAP_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
    WidgetBaseEx_t  WdgBase;
    IBitmap        *pBitmap;
    u8              AlignFlag;
    WidgetSize_t    PreferredSize;
    s32             xOffset;
    s32             yOffset;

    ModelListener_t MdlLsnr;
    MAE_WChar       *pwLinkAddr;
    boolean         bLinked;
    boolean         bTouched;
#ifdef __TOUCH_SCREEN_MMI__
    ITouchSrv *pITouchSrv;  //< Touch service
#endif

#if defined(__G3D_MMI__)
    u32		nBmpRawDataID;		///< raw data (texture) ID for bitmap
#endif

}WdgBitmap_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret BitmapWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgBitmapDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
	static MAE_Ret _WdgBitmapConstructor(WdgBitmap_t *pThis);

	static void _WdgBitmapDestructor(WdgBitmap_t *pThis);

	static void _WdgBitmapSetSize(IWidget*, WidgetSize_t*);

	static void _WdgBitmapGetPreferredSize(IWidget*, WidgetSize_t*);

	static boolean _WdgBitmapIntersectOpaque(IWidget*, const Rect_t*, Rect_t*);

	static void _WdgBitmapDraw(IWidget*, IDispCanvas*, s32, s32);

	static MAE_Ret _WdgBitmapSetModel(IWidget*, IModel*, IBase*);

	static void _WdgBitmapModelListener(void*, ModelEvent_t*);

	static void _WdgBitmapCalculateOffset(WdgBitmap_t*);

#ifdef __TOUCH_SCREEN_MMI__
	static void _WdgBitmapNotifyClick(WdgBitmap_t *pThis);
#endif /* __TOUCH_SCREEN_MMI__ */


#endif //__MMI_WDG_BITMAP_PRIV_H__
/*=============================================================*/
// end of file
