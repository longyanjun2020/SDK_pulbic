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
* @file    mmi_wifiapp_view.h
* @version
* @brief   Wifi applet view header file
*
*/

#ifndef __MMI_WIFIAPP_VIEW_H__
#define __MMI_WIFIAPP_VIEW_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_common_vtm.h"
#include "mmi_common_wdgvar.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    IWidget *pIMenuWdg_OnOff;
    IWidget *pIMenuWdg;
} WiFiAppMainViewWdgList_t;

typedef struct
{
    IWidget *pIMenuWdg;
} WiFiAppMainOptionMenuWdgList_t;

typedef struct
{
    IWidget *pPwdInputTitleWdg;
    IWidget *pPwdInputWdg;
} WiFiAppPasswordInputWdgList_t;

typedef struct
{
    IWidget *pNameInputTitleWdg;
    IWidget *pNameInputWdg;
} WiFiAppNameInputWdgList_t;

typedef struct
{
    IWidget *pIpInputTitleWdg;
    IWidget *pIpInputWdg;
} WiFiAppIpInputWdgList_t;

typedef struct
{
    IWidget *pIHideAPMenuWdg;
} WiFiAppHideAPWdgList_t;

typedef struct
{
    IWidget *pIConnectSetMenuWdg;
} WiFiAppConnectSetWdgList_t;

typedef struct
{
    IWidget *pIOtherMenuWdg;
} WiFiAppOtherWdgList_t;

typedef struct
{
    IWidget *pISecurityMenuWdg;
} WiFiAppSecurityWdgList_t;

typedef struct
{
    IWidget *pIThmTxtWdg;
} WiFiAppMACAddressWdgList_t;

typedef struct
{
    IWidget *pIThmTxtWdg;
} WiFiAppDetailsWdgList_t;

typedef struct
{
    IWidget *pICertListMenuWdg;
} WiFiAppCertWdgList_t;

typedef struct
{
    IWidget *pICertOptionMenuWdg;
} WiFiAppCertOptionWdgList_t;

typedef struct
{
    IWidget *pIThmTxtWdg;
} WiFiAppCertOptionDetailsWdgList_t;

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret WiFiCreateMainView(HWIN hWin, WiFiAppMainViewWdgList_t *pWdgList);
MAE_Ret WiFiSetMainView(HWIN hWin, WiFiAppMainViewWdgList_t *pWdgList);
MAE_Ret WiFiCreateMainOptionMenuView(HWIN hWin, WiFiAppMainOptionMenuWdgList_t *pWdgList);
MAE_Ret WiFiCreatePasswordInputView(HWIN hWin, WiFiAppPasswordInputWdgList_t *pWdgList);
MAE_Ret WiFiCreateNameInputView(HWIN hWin, WiFiAppNameInputWdgList_t *pWdgList);
MAE_Ret WiFiCreateIpInputView(HWIN hWin, WiFiAppIpInputWdgList_t *pWdgList);
MAE_Ret WiFiCreateHideAPView(HWIN hWin, WiFiAppHideAPWdgList_t *pWdgList);
MAE_Ret WiFiCreateConnectSetView(HWIN hWin, WiFiAppConnectSetWdgList_t *pWdgList);
MAE_Ret WiFiCreateOtherView(HWIN hWin, WiFiAppOtherWdgList_t *pWdgList);
MAE_Ret WiFiCreateSecurityView(HWIN hWin, WiFiAppSecurityWdgList_t *pWdgList);
MAE_Ret WiFiCreateMACAddressView(HWIN hWin, WiFiAppMACAddressWdgList_t *pWdgList);
MAE_Ret WiFiCreateDetailsView(HWIN hWin, WiFiAppDetailsWdgList_t *pWdgList);
MAE_Ret WiFiCreateCertListView(HWIN hWin, WiFiAppCertWdgList_t *pWdgList);
MAE_Ret WiFiCreateCertListOptionView(HWIN hWin, WiFiAppCertOptionWdgList_t *pWdgList);
MAE_Ret WiFiCreateCertListOptionDetailsView(HWIN hWin, WiFiAppCertOptionDetailsWdgList_t *pWdgList);

#endif //__MMI_WIFIAPP_VIEW_H__
