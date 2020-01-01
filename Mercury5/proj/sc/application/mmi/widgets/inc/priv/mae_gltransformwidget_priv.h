/**
 * @brief
 * @file 	mae_gltransformwidget_priv.h
 * @version	$Id:$
 *
 */
#ifndef __MAE_GLTRANSFORMWIDGET_PRIV_H__
#define __MAE_GLTRANSFORMWIDGET_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mgl_Utility_common.h"
#include "mmi_wdg_gltransformwidget.h"
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"
#include "mmi_mae_model.h"
#include "mae_wdgbackground.h"

/*=============================================================*/
// type and define
/*=============================================================*/


typedef struct {
	DecoratorEx_t	DecBase;			///< Use DecoratorEx_t structure as base structure for border.
	ModelListener_t	DataMdlLsn;			///< IDataModel listener.
	mgl_u16 u16SceneHandleId;
	mgl_u32 u32NodeID;
	mgl_u32 u32ChildWdgRawDataId;
	boolean bChildWdgDirty;
	s16 animationTick;
	GLTRANSFORM_STATE_e bAnimIsEnd;
	s32 x;
	s32 y;
	mgl_u16  u16FrameCnt;
	GLTRANSFORM_TYPE_e eTransformType;

} GLTransformWidget_t;

#define GLTRANSFORM_ROTATE_ANGLE (80.0f)
#define GLTRANSFORM_ANI_TIMER (10)

/*=============================================================*/
// functions
/*=============================================================*/

/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GLTransformWidget_New(MAE_ClsId ClsID, void **ppObj);
static MAE_Ret GLTransformWidgetStructCtor(GLTransformWidget_t *pThis);
static void GLTransformWidgetStructDtor(GLTransformWidget_t *pThis);

/*------------------------------------------------------------------------------------------
* For IBase interface
------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
* For IContainer interface
------------------------------------------------------------------------------------------*/
//add => use decorator base
//delete => use decorator base
//move => use decorator base
//get widget => use decorator base
//invalidate
static void GLTransformWidget_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
/*------------------------------------------------------------------------------------------
* For IDecorator interface
------------------------------------------------------------------------------------------*/
//get dec widget => use decorator base
//set dec widget

/*------------------------------------------------------------------------------------------
* For other functions
------------------------------------------------------------------------------------------*/


#endif //__MAE_GLTRANSFORMWIDGET_PRIV_H__
/*=============================================================*/
// end of file
