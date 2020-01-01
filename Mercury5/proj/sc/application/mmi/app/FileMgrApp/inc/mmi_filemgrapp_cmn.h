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
* @file    mmi_filemgrapp_cmn.h
* @version
* @brief
*
*/

#ifndef __MMI_FILEMGRAPP_CMN_H__
#define __MMI_FILEMGRAPP_CMN_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_headers.h"
#include "mmi_launcher_filemanager.h"

typedef enum
{
    MMI_FILEMGRAPP_OPT_MENU_MARKL2,
    MMI_FILEMGRAPP_OPT_MENU_SETTINGL2,
    MMI_FILEMGRAPP_OPT_MENU_VIRTUALROOT,
    MMI_FILEMGRAPP_OPT_MENU_INPUTL1,
    MMI_FILEMGRAPP_OPT_MENU_MULTISEL,
    MMI_FILEMGRAPP_OPT_MENU_LISTERMULTISEL,

    MMI_FILEMGRAPP_OPT_MENU_NUM
}FileMgrAppCmnOptMenuMapping_e;

typedef struct
{
    const WdgStaticMenuItem_t               *ptMenuItem;
    u32                                     nSize;
}FileMgrAppCmnOptMenuMapping_t;

typedef struct
{
    PfnFileMgrSelectCb                      pfnOnSelectCb;
    WdgStaticMenuItem_t                     tMenuItem;
}FileMgrAppOptMenuItem_t;

typedef struct
{
    MMI_Common_SupportedMediaType_e         eMediaType;
    const FileMgrAppOptMenuItem_t           *sMenuItemList;
    const u32                               nMenuItemListSize;
    const FileMgrAppOptMenuItem_t           *sSetAsMenuItemList;
    const u32                               nSetAsMenuItemListSize;
}FileMgrAppMediatypeOptMenuMapping_t;

typedef struct
{
    MMI_Common_SupportedMediaType_e         eMediaType;
    PfnFileMgrSelectCb				        pfnCmnOnSelectCb; // for general case
    PfnFileMgrSelectCb				        pfnSimpleOnSelectCb; // for Simple mode
}FileMgrAppFileAssociation_t;

typedef struct
{
    MMI_Common_SupportedMediaType_e         eMediaType;
    PfnFileMgrSelectCb				        pfnOnSelectCb; // for general case
}FileMgrAppFileAssociation4SingleSelection_t;

extern const VFS_PartialListFilter_t g_tFilterForFileMgrApp;
extern const VFS_PartialListFilter_t g_tFilterOnlyFile;
extern const VFS_PartialListFilter_t g_tFilterOnlyFolder;

void FileMgrAppGetCmnOptMenu(FileMgrAppCmnOptMenuMapping_e eOptMenu, const WdgStaticMenuItem_t **pptSettingL2Menu, u32 *pnSize);

void FileMgrAppGetOptMenuByMediaType(MMI_Common_SupportedMediaType_e nMediaType, const FileMgrAppOptMenuItem_t **pptOptMenuItemList, u32 *pnSize, u32 nNumOfFiles);
void FileMgrAppOptionMenuL2ByMediaType(MMI_Common_SupportedMediaType_e nMediaType, const FileMgrAppOptMenuItem_t **pptL2OptMenuItemList, u32 *pnSize);
void FileMgrAppGetOptionMenuItemCb(u32 nMenuId, const FileMgrAppOptMenuItem_t *ptCurrentOptMenuItemList, u32 pnSize, PfnFileMgrSelectCb *pPfnOnSelectCb);
void FileMgrAppGetOptionMenuSetAsItemSelectCb(u32 nMenuId, MAE_WChar const *pCurrentFolder, VFS_PartialListFileInfo_t *pEfsFileInfo, PfnFileMgrSelectCb *pPfnOnSelectCb);

void FileMgrAppGetFileActCb(boolean bSimple, MMI_Common_SupportedMediaType_e nMediaType, PfnFileMgrSelectCb *pPfnOnSelectCb);
void FileMgrAppGetSingleSelectionActCb(MMI_Common_SupportedMediaType_e nMediaType, PfnFileMgrSelectCb *pPfnSelectCb);

#endif //__MMI_FILEMGRAPP_CMN_H__

