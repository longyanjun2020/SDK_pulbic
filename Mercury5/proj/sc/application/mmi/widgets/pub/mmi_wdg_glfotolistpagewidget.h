/**
* @file    mmi_wdg_glfotolistpagewidget.h
* @brief
* @version $Id: mmi_wdg_glfotolistpagewidget.h 37664 2010-02-12 09:36:01Z Lih.Wang $
*/

#ifndef __MMI_WDG_GLFOTOLISTPAGEWIDGET_H__
#define __MMI_WDG_GLFOTOLISTPAGEWIDGET_H__

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_PHOTOSLIDE_MMI__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_wdg_glfotolistwidget_def.h"
#include "mmi_mae_file_util.h"
#include "mmi_mae_filemgr.h"
#include "mdl_vfs_struct.h"

typedef void (*PfnWdgGlfotoListPageFocusIdxck) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

typedef enum
{
	GLFOTOLISTWDG_STATUS_NONE = 0,
	GLFOTOLISTWDG_STATUS_ANIM_RUNING,
	GLFOTOLISTWDG_STATUS_FILE_INIT,
	GLFOTOLISTWDG_STATUS_LAUNCH_PICVIEWER,
	GLFOTOLISTWDG_STATUS_SHOW_PHOTO_SLIDE,
} WdgGlFotoListStatus_e ;


typedef struct
{
	u32 nTotalFileNum;
	u32 nCurFileIndex;
	MAE_WChar pFileName[FILEMGR_MAX_FILENAME_SIZE];
} FileItemInfo_t;

typedef struct
{
	VFS_FileID_t nFileId;
	MAE_WChar pItemUrl[FILEMGR_MAX_FILEPATH_SIZE];
} ListItemInfo_t;

/////////////////////////////////////////////////////////////

IWidget* WdgGlFotoListPageCreate
(
 void
 );

MAE_Ret GlFotoListPageWdg_RegisterFileInfoCb
(
 IWidget                 *pWDGGlFoto,
 PfnWdgGlfotoListPageFocusIdxck   pfn,
 void                    *pUserData
 );

MAE_Ret GlFotoListPageWdg_DeregisterFileInfoCb
(
 IWidget                 *pWDGGlFoto,
 PfnWdgGlfotoListPageFocusIdxck   pfn,
 void                    *pUserData
 );

MAE_Ret GlFotoListPageWdg_RegisterFocusIdxCb
(
 IWidget                 *pWDGGlFoto,
 PfnWdgGlfotoListPageFocusIdxck   pfn,
 void                    *pUserData
 );

MAE_Ret GlFotoListPageWdg_DeregisterFocusIdxCb
(
 IWidget                 *pWDGGlFoto,
 PfnWdgGlfotoListPageFocusIdxck   pfn,
 void                    *pUserData
 );

MAE_Ret GlFotoListPageWdg_RegisterNoItemNotifyCb
(
 IWidget                 *pWDGGlFoto,
 PfnWdgGlfotoListPageFocusIdxck   pfn,
 void                    *pUserData
 );

MAE_Ret GlFotoListPageWdg_DeregisterNoItemNotifyCb
(
 IWidget                 *pWDGGlFoto,
 PfnWdgGlfotoListPageFocusIdxck   pfn,
 void                    *pUserData
 );

MAE_Ret GlFotoListPageWdg_RegisterStatusChangeNotifyCb
(
 IWidget                 *pWDGGlFoto,
 PfnWdgGlfotoListPageFocusIdxck   pfn,
 void                    *pUserData
 );

MAE_Ret GlFotoListPageWdg_DeregisterStatusChangeNotifyCb
(
 IWidget                 *pWDGGlFoto,
 PfnWdgGlfotoListPageFocusIdxck   pfn,
 void                    *pUserData
 );

#endif // defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_PHOTOSLIDE_MMI__)

#endif /* __MMI_WDG_GLFOTOLISTPAGEWIDGET_H__ */
/*=============================================================*/
// end of file
