/**
* @file    mmi_wdg_snapshot.h
*/
#ifndef __MMI_WDG_SNAPSHOT_H__
#define __MMI_WDG_SNAPSHOT_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** WdgSnapshotCfgData_t
*
* @brief    pDecoratorWdg:  The widget be decorator.
*
*/
typedef struct
{
    IWidget                 *pDecoratorWdg;
} WdgSnapshotCfgData_t;
/*=============================================================*/
// functions
/*=============================================================*/

/** WdgSnapshotCreateForWnd
* @brief        Snapshot widget create function for Window
*
* @param[in]    hWin           The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
* @param[in]    pData          Snapshot widget Common Data
*
* @retval       The pointer of Image   Success.
* @retval       NULL                   Failed.
*
*/
IWidget* WdgSnapshotCreateForWnd
(
 HWIN                    hWin,
 Pos_t                   *pPos,
 WidgetSize_t            *pSize,
 u16                     nWidgetID,
 WdgSnapshotCfgData_t    *pData
 );

/** WdgSnapshotCreate
* @brief        Create Snapshot widget
*
* @retval       The pointer of Image    Success.
* @retval       NULL                    Failed.
*
*/
IWidget* WdgSnapshotCreate
(
    void
);

/** WdgSnapshotSetDecoratorWdg
* @brief         Set the widget which want to be decorated by snapshot widget
*                Ex, To decorate text widget with snapshot widget when you want to show snapshot bmp if the text content unchange
*
* @param[in]     pWDGSnapshot      The snapshot widget which want to be set
* @param[in]     pViewWidget       The widget which want to be decorated by snapshot widget.
*
* @retval        None.
*
*/
void WdgSnapshotSetDecoratorWdg
(
 IWidget                 *pWDGSnapshot,
 IWidget                 *pChild
 );

/** WdgSnapshotSetEnableSnapshot
* @brief         Set Snapshot widget's EnableSnapshot situation
*
* @param[in]     pWDGSnapshot        The snapshot widget which want to be set
* @param[in]     bEnableSnapshot     TRUE : Snapshot widget is invalid, and the snapshot bmp will be released
*                                    FALSE: Snapshot widget works
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgSnapshotSetEnableSnapshot
(
 IWidget                 *pWDGSnapshot,
 boolean			     bEnableSnapshot
 )
{
    return WdgCommonSetProperty(pWDGSnapshot, PROP_SNAPSHOT_WDG_ENABLE_SNAPSHOT, (u32)bEnableSnapshot);
}

/** WdgSnapshotGetEnableSnapshot
* @brief         Get Snapshot widget's EnableSnapshot property
*
* @param[in]     pWDGSnapshot      The snapshot widget which want to be gotten
*
* @retval        bEnableSnapshot        The EnableSnapshot situation is TRUE or FALSE
*
*/
__INLINE boolean WdgSnapshotGetEnableSnapshot
(
 IWidget                 *pWDGSnapshot
 )
{
    boolean bEnableSnapshot = FALSE;

    WdgCommonGetProperty(pWDGSnapshot, PROP_SNAPSHOT_WDG_ENABLE_SNAPSHOT, &bEnableSnapshot);

    return bEnableSnapshot;
}

#endif
