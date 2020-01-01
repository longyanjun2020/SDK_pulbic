/**
 * @file    mmi_wdg_handwriting_priv.h
 * @brief   The document describes internal declartion of Hand Writing Widget
 * @author  christoph.kuo@mstarsemi.com
 *
 * @version $Id: mmi_wdg_handwriting_priv.h 25372 2009-03-11 08:10:22Z mark.yang $
 */
 
#ifndef __MMI_WDG_HANDWRITING_PRIV_H__
#define __MMI_WDG_HANDWRITING_PRIV_H__

#ifdef __HANDWRITING_MMI__
#ifdef __TOUCH_SCREEN_MMI__

#include "mae_widgetbase.h"
#include "mmi_mae_datamodel.h"
#include "mmi_util_handwriting.h"

/*  Declarations */
#define MAE_HW_STROKE_INC     10
#define MAE_HW_POINT_INC      40

typedef u8 _MAE_HWDrawType_t;

typedef u8 _MAE_HWBool_t;

typedef struct
{
    WidgetBaseEx_t    WdgBase;
    
    ITouchSrv      *pTouchSrv;
    
    MAE_Stroke_t    stStrokeList;
    
    u16             nMaxStrokes;
    u16             nMaxPoints;
    u16             nPointsCnt;
    u16             nStrokesCnt;
    
    u16             nLastDrawPntCnt;
    u16             nLastDrawStkCnt;
    
    _MAE_HWBool_t   bNewStroke;
    _MAE_HWBool_t   bLockScr;
    
    Rect_t          stUpdRect;

	HW_Stroke_Duration_e eStrokeDuration;
	HW_Function_e	eFunction;
//	ConfigListener_t CfgLsn;
    
}_MAE_HandWritingWdg_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret HandWritingWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean HandWritingWdg_HandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);
/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgHandWritingConstructor(_MAE_HandWritingWdg_t *pThis);
void _WdgHandWritingDestructor(_MAE_HandWritingWdg_t *pThis);

static boolean HandWritingWdg_IntersectOpaque(IWidget *pIWidget, const Rect_t *pInRect, Rect_t *pOutRect);
static void HandWritingWdg_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

static void _HandWritingWdg_ReleaseStrokeList(_MAE_HandWritingWdg_t *pThis);
static MAE_Ret _HandWritingWdg_NewStroke(_MAE_HandWritingWdg_t *pThis);
static MAE_Ret _HandWritingWdg_EndStroke(_MAE_HandWritingWdg_t *pThis);
static MAE_Ret _HandWritingWdg_AddNewPoints(_MAE_HandWritingWdg_t *pThis, u32 x, u32 y);
static void _HandWritingWdg_StrokeTimerCB(void* data);
void _HandWritingWdg_FreeStrokeList(_MAE_HandWritingWdg_t *pThis);
static void _HandWritingWdg_FreeOutputCandBuff(void *pData, IBase *pOwner);
//static void _HandWritingWidget_IConfigCB(void *pUsrData, MAECfgCategory_t cat, MAECfgItemId_t id, void *pItemData);
#endif /* __TOUCH_SCREEN_MMI__ */
#endif /* __HANDWRITING_MMI__ */
#endif /* __MMI_WDG_HANDWRITING_PRIV_H__ */
