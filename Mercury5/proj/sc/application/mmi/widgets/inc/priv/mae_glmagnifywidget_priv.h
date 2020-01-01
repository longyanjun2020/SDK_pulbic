/**
* @file 	mae_glmagnifywidget_priv.h
* @brief
*
* @version $Id:$
*/

#ifndef __MAE_GLMAGNIFYWIDGET_PRIV_H__
#define __MAE_GLMAGNIFYWIDGET_PRIV_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_glmagnifywidget.h"
#include "mae_widgetbase.h"
#include "mmi_mae_util_easing.h"
#include "mmi_common_util.h"
#include "mgl_Core_shape.h"
#include "mgl_Scene_Environment.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
	WidgetBaseEx_t  WdgBase;
	ModelListener_t MdlLsnr;
	s32 nDrawX;
	s32 nDrawY;
	Vertex2D size;
	boolean	bTouched;
	u16     u16SceneHandleId;
	u32     nodeID;
	mgl_u32         nRawDataID;
	s32		nTS_CurrentX, nTS_CurrentY;
	s32		nTS_MoveX, nTS_MoveY;

	float t;
	float	fTS_X, fTS_Y;
	IBitmap         *pCacheScreenBmp;
	IWidget	*pMagnImgWidget;
	ITouchSrv         *pITouchSrv;
} MagnifyWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret MagnifyWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret MagnifyWdg_Ctor(MagnifyWdg_t *pThis);
static void MagnifyWdg_Dtor(MagnifyWdg_t *pThis);
static void MagnifyWdg_WidgetFree(void *pData);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean MagnifyWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void MagnifyWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
boolean _MagnifyWdg_SetProperty(MagnifyWdg_t *pThis, u32 P1, u32 P2);
boolean _MagnifyWdg_GetProperty(MagnifyWdg_t *pThis, u32 P1, u32 P2);

#endif //__MAE_GLMAGNIFYWIDGET_PRIV_H__
