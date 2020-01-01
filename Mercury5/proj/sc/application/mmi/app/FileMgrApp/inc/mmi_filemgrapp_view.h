////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_filemgrapp_view.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_VIEW_H__
#define __MMI_FILEMGRAPP_VIEW_H__

#include "mae_textlabel.h"
#include "mmi_common_wdgvar.h"
#include "mmi_filemgrapp_util.h"

typedef struct
{
    IWidget *pMenuWidget;
}FileMgrAppMedialstContentViewWdgList_t;

MAE_Ret FileMgrAppCreateMedialstContentView(HWIN hWin, FileMgrAppMedialstContentViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pImgWidget;
    IWidget *pMenuWidget;
}FileMgrAppCntgridTthumbView2WdgList_t;

MAE_Ret FileMgrAppCreateCntgridThumbView2(HWIN hWin, FileMgrAppCntgridTthumbView2WdgList_t *pWdgList);

typedef struct
{
    IWidget *pImgWidget;
    IWidget *pMenuWidget;
}FileMgrAppCntgridThumbViewWdgList_t;

MAE_Ret FileMgrAppCreateCntgridThumbView(HWIN hWin, FileMgrAppCntgridThumbViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pMenuWidget;
}FileMgrAppListerRootView2WdgList_t;

MAE_Ret FileMgrAppCreateListerRootView2(HWIN hWin, FileMgrAppListerRootView2WdgList_t *pWdgList);

typedef struct
{
    IWidget *pMenuWidget;
}FileMgrAppListerRootViewWdgList_t;

MAE_Ret FileMgrAppCreateListerRootView(HWIN hWin, FileMgrAppListerRootViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pMenuWidget;
}FileMgrAppListerContentViewWdgList_t;

MAE_Ret FileMgrAppCreateListerContentView(HWIN hWin, FileMgrAppListerContentViewWdgList_t *pWdgList);
MAE_Ret FileMgrAppCreateListerContentView2(HWIN hWin, FileMgrAppListerContentViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pImgWidget;
    IWidget *pTitleWidget;
    IWidget *pTitle2Widget;
    IWidget *pThmTextWidget;
}FileMgrAppEmptyFolderViewWdgList_t;

MAE_Ret FileMgrAppCreateEmptyFolderView(HWIN hWin, FileMgrAppEmptyFolderViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pMenuWidget;
}FileMgrAppMultiselContentViewWdgList_t;

MAE_Ret FileMgrAppCreateMultiselContentView(HWIN hWin, FileMgrAppMultiselContentViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pImgWidget;
    IWidget *pMenuWidget;
}FileMgrAppMultiselThumbViewWdgList_t;

MAE_Ret FileMgrAppCreateMultiselThumbView(HWIN hWin, FileMgrAppMultiselThumbViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pMenuWidget;
}FileMgrAppSortbySelViewWdgList_t;

__SLDPM_FREE__ MAE_Ret FileMgrAppCreateSortbyselView(HWIN hWin, FileMgrAppSortbySelViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pMenuWidget;
}FileMgrAppCpmvStorageSelViewWdgList_t;

__SLDPM_FREE__ MAE_Ret FileMgrAppCreateCpmvStorageSelView(
    HWIN hWin
    ,FileMgrAppCpmvStorageSelViewWdgList_t *pWdgList
    ,FileMgrAppOpOP_e eOpId
    ,boolean bIsExtMemPresented
#if defined(__DUAL_CARD__)
    ,boolean bIsExtMem2Presented
#endif
    );

typedef struct
{
    IWidget *pMenuWidget;
}FileMgrAppCpmvDestSelViewWdgList_t;

__SLDPM_FREE__ MAE_Ret FileMgrAppCreateCpmvDestSelView(HWIN hWin, FileMgrAppCpmvDestSelViewWdgList_t *pWdgList);

typedef struct
{
    IWidget *pTextWidget;
}FileMgrAppCpmvEmptyFolderViewWdglist_t;

#endif //__MMI_FILEMGRAPP_VIEW_H__

