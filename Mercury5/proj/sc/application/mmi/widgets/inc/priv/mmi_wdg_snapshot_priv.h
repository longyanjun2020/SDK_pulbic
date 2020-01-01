/**
* @file mmi_wdg_snapshot_priv.h
*/
#ifndef __MMI_WDG_SNAPSHOT_PRIV_H__
#define __MMI_WDG_SNAPSHOT_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"

#include "mmi_wdg_snapshot.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
    DecoratorEx_t      DecBase;    ///< Use DecoratorEx_t as base structure and support border/padding/background
    IBitmap            *pSnapshotBmp;
    boolean            bEnableSnapshot;
} SnapshotWidget_t;
/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret SnapshotWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean SnapshotWidget_DefHandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret SnapshotWidgetStrucCtor(SnapshotWidget_t *pThis);
static void SnapshotWidgetStrucDtor(SnapshotWidget_t *pThis);
static void SnapshotWidget_DefDraw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);

#endif //__MMI_WDG_SNAPSHOT_PRIV_H__
/*=============================================================*/
// end of file
