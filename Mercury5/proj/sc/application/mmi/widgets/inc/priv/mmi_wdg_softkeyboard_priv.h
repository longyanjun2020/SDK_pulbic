/**
 * @file    mmi_wdg_softkeyboard_priv.h
 * @brief   The document describes internal declartion of SoftKeyboard Widget
 * @author  christoph.kuo@mstarsemi.com
 *
 * @version $Id: mmi_wdg_softkeyboard_priv.h 33778 2009-06-18 12:16:19Z brian.tsui $
 */
 
#ifndef __MAE_SOFTKEYBOARDWIDGET_PRIV_H__
#define __MAE_SOFTKEYBOARDWIDGET_PRIV_H__


#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__

//A compile option to turn Image Cache on for SKB Widget
#define __SOFTKEYBOARD_IMG_CACHE_ON__

#include "mae_propcontainerbase.h"
#include "mmi_wdg_list.h"
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
#include "mmi_mae_touchsrv.h"
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__

/*  Declarations */

typedef struct{
	u16 nLanguageId;
	void* pDataArray;
	u16 nTotalKey;
}SoftkeyBoardData_t;


typedef struct {
    ButtonData_t SKBButtonData;
    u8 SKBCodeType_e; //MAE_SKB_CODE_TYPE_e
} SoftKeyBoardWidget_ButtonData_t;

typedef u8 SKWdgBool_t;

typedef struct
{
    PropContainerBase_t PropCntrBase;
    IWidget *pIButtonWdg;
    IWidget *pIGridWidget;
    IDispCanvas *pBufCanvas;
    IDisplay *pBufDisp;
    ModelListener_t ButtonListener;
    u32 nCurrentSKBId;
    u32 nButtonTextColor;
	
	Rect_t  tInvRect;

#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
	ITouchSrv *pITouchSrv;
	boolean bTouchPressed;
	boolean b7ColSoftKeyBoardNoSoftKey; //When use 7Col soft-keyboard, that the UI style don't have "SoftKey",  set this property, the 7Col soft-keyboard high-light widget can show correct.
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__

#ifdef __SOFTKEYBOARD_IMG_CACHE_ON__
    IImage *pPressedImgCache;
    IImage *pUnPressedImgCache;
#endif    
	u32 nSKBFilterMask;
    u32 *SKBImgMapping;
}_MAE_SoftKeyboardWidget;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret SoftKeyboardWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean SoftKeyboardWidget_HandleEvent(IContainer *pIPropContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret _WdgSoftKeyboardConstructor(_MAE_SoftKeyboardWidget *pThis);
__SLDPM_FREE__ void _WdgSoftKeyboardDestructor(_MAE_SoftKeyboardWidget *pThis);

#endif //__IME_MMI_SOFTKEYBOARD__
#endif //__TOUCH_SCREEN_MMI__
#endif /* __MAE_SOFTKEYBOARDWIDGET_PRIV_H__ */
