#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
/**
* @file 	mae_softkeyboard_highlightwidget_priv.h
* @brief
*
* @version $Id: mae_softkeyboard_highlightwidget_priv.h  2009-09-15 kim.chuang $
*/
#ifndef __MAE_SOFTKEYBOARD_HIGHLIGHTWIDGET_PRIV_H__
#define __MAE_SOFTKEYBOARD_HIGHLIGHTWIDGET_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/

#include "mmi_mae_softkeyboard_highlightwidget.h"
#include "mae_abscontainerbase.h"
#include "mmi_wdg_button.h"
#include "mmi_mae_vectormodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
    ButtonData_t SKBButtonData;
    u8 SKBCodeType_e;
} SKBHighlightWdg_ButtonData_t;

typedef struct {
    u32 nChar;
    u32 SKBCodeType_e;
} SKBHighlightWdg_VectorModelData_t;

typedef struct {
    AbsContainerBase_t	AbsCntrBase;
    IWidget         *pITextWidget;
    IWidget         *pIBgImageWidget;
    
    IWidget         *pListWidget;
    IWidget         *pButtonWidget;
    IWidget         *pCandidateImgWdg[HIGHLIGHT_LIST_MAX];  // 0 base enum

    ModelListener_t ListViewMdlLsn;

    MAE_WChar   pHighlightStr[CANDIDATE_NUM];
    MAE_WChar   HighlightChar[4];

    //u32 nButtonTextColor;

    u32 u32XPosition;
    //u32 u32YPosition;    

    Softkeyboard_HighlightStyle_t eHighlight_Style;

} _Softkeyboard_HighlightWdg_t;

/*------------------------------------------------------------------------------------------
* new function constructor and destructor for widget base
------------------------------------------------------------------------------------------*/
static void Softkeyboard_HighlightWidget_GetPreferredSize(IAbsContainer *pHighlightWidget, WidgetSize_t *pSize);
static boolean Softkeyboard_HighlightWidget_HandleEvent(IAbsContainer *pHighlightWidget, MAE_EventId evt, u32 P1, u32 P2);
static MAE_Ret Softkeyboard_HighlightWidgetStrucCtor(_Softkeyboard_HighlightWdg_t *pThis);
static void Softkeyboard_HighlightWidgetStrucDtor(_Softkeyboard_HighlightWdg_t* pThis);

MAE_Ret Softkeyboard_Highlightwidget_New(MAE_ClsId ClsID, void **ppObj);

static MAE_Ret SKBHighlightWdg_SetBGImg(_Softkeyboard_HighlightWdg_t *pThis);
static MAE_Ret SKBHighlightWdg_CreateTextWdg(_Softkeyboard_HighlightWdg_t *pThis);
static MAE_Ret SKBHighlightWdg_CreateListWdg(_Softkeyboard_HighlightWdg_t *pThis);
static MAE_Ret SKBHighlightWdg_ShowListWdg(_Softkeyboard_HighlightWdg_t *pThis);
static MAE_Ret SKBHighlightWdg_AddImg(_Softkeyboard_HighlightWdg_t *pThis, u32 nImageID, IWidget **ppImgWidget);
static MAE_Ret SKBHighlightWdg_CreateButtonWidget(_Softkeyboard_HighlightWdg_t *pThis);
static void SKBHighlightWdg_ItemWdgAdaptSet(void *pCtxData, void *pDataIn, s32 nLenIn, void **ppDataOut, s32 *pnLenOut, PfnModelFree *ppFreeFunc, IBase **ppOwner);
static void SKBHighlightWdg_FreeButtonModel(void *pData, IBase *pOwner);
static void SKBHighlightWdg_ListWidget_FreeModel(void* pData, IBase *pOwner);
static MAE_Ret SKBHighlightWdg_ListWdg_InsertVectorItem(_Softkeyboard_HighlightWdg_t *pThis, IVectorModel *pVectorModel, u32 u32ListLen);
static void SKBHighlightWdg_Notify(_Softkeyboard_HighlightWdg_t *pThis, u32 MdlEvt, u32 dwParam);

static void SKBHighlightWdg_ListWdgViewMdlLsn(void *pUsrData, ModelEvent_t *pMdlEvent);

//static boolean SKBHighlightWdg_IsLargeChar(MAE_WChar nChar);

#endif //__MAE_SOFTKEYBOARD_HIGHLIGHTWIDGET_PRIV_H__
/*=============================================================*/
// end of file

#endif
