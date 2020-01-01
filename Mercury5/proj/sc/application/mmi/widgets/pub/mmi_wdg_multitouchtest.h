/**
* @file    mmi_wdg_multitouchtest.h
*/
#ifndef __MMI_WDG_MULTITOUCHTEST_H__
#define __MMI_WDG_MULTITOUCHTEST_H__

/*=============================================================*/
// include
/*=============================================================*/
#ifdef __MULTI_TOUCH__
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"

#include "mmi_wdg_image.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum
{
    MULTITOUCHTEST_TYPE_NORMAL
   ,MULTITOUCHTEST_TYPE_CASE
   ,MULTITOUCHTEST_TYPE_DEMO
   ,MULTITOUCHTEST_TYPE_EM
   ,MULTITOUCHTEST_TYPE_NUM
} MultiTouchTestType_e;

typedef enum
{
    MULTITOUCHTEST_EMTYPE_SINGLE
  , MULTITOUCHTEST_EMTYPE_MULTI_HOOK
  , MULTITOUCHTEST_EMTYPE_MULTI_NONEHOOK
  , MULTITOUCHTEST_EMTYPE_NUM
} MultiTouchTestEmType_e;

/*=============================================================*/
// functions
/*=============================================================*/

/** WdgMultiTouchTestCreateForWnd
* @brief        MultiTouchTest widget create function for Window
*
* @param[in]    hWin           The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID      The widget unique ID of window
*
* @retval       The pointer of Image   Success.
* @retval       NULL                   Failed.
*
*/
IWidget* WdgMultiTouchTestCreateForWnd
(
    HWIN                    hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID
);

/** WdgMultiTouchTestCreate
* @brief        Create MultiTouchTest widget
*
* @retval       The pointer of Image    Success.
* @retval       NULL                    Failed.
*
*/
IWidget* WdgMultiTouchTestCreate(void);

MAE_Ret WdgMultiTouchTestSetType(IWidget *pMultiTouchWdg, MultiTouchTestType_e eType);
MAE_Ret WdgMultiTouchTestSetEmType(IWidget *pMultiTouchWdg, MultiTouchTestEmType_e eEmType);

MultiTouchTestType_e WdgMultiTouchTestGetType(IWidget *pMultiTouchWdg);
MultiTouchTestEmType_e WdgMultiTouchTestGetEmType(IWidget *pMultiTouchWdg);

u32 WdgMultiTouchGetTestCaseNum(IWidget *pMultiTouchWdg);
MAE_Ret WdgMultiTouchRunTestCase(IWidget *pMultiTouchWdg, u32 nIndex);

#endif //__MULTI_TOUCH__
#endif //__MMI_WDG_MULTITOUCHTEST_H__
/*=============================================================*/
// end of file
