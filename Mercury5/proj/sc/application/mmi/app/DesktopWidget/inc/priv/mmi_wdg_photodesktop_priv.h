/**
 * @file    mmi_wdg_phonebookdesktop_priv.h
 * @brief   The internal structure of the phonebook desktopwidget

 */

#ifndef __MMI_WDG_PHOTODESKTOP_PRIV_H__
#define __MMI_WDG_PHOTODESKTOP_PRIV_H__

#if defined (__GADGETS_MMI__) || defined(__3D_UI_IDLE_MULTIPAGE__)

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_settingapp.h"
#include "mmi_common_util.h"
#include "mmi_common_cfg.h"
#include "rs_layout_id.h"
#include "mmi_wdg_photodesktop.h"
#include "mmi_coresrv.h"

#include "mmi_srv_phb.h"
#include "mmi_sssrv.h"
#include "mmi_srv_sim.h"
#include "mmi_srv_cc.h"
#include "mmi_srv_cfg.h"
#include "mmi_ccsrv_def.h"

/*************************************************************************/
/*   For Definition                                                      */
/*************************************************************************/
#define DESKTOP_WDG_BOARDER 8
/*************************************************************************/
/*   For Enumeration                                                     */
/*************************************************************************/


enum
{
    DESKTOPPHOTO_OUTLOOK_L = 0,
    DESKTOPPHOTO_OUTLOOK_P,
    DESKTOPPHOTO_OUTLOOK_NONO,
};
typedef u8 DesktopStatus_e;

/*************************************************************************/
/*   For Structure                                                       */
/*************************************************************************/

typedef struct
{
    DECLARE_BASECLASS_DESKTOPWIDGET
    IWidget                 *pPicImgWdg; 
    IImage                  *pImage;    
    u32                     nSelectedId;
    MAE_WChar               pItemUrl[FILEMGR_MAX_FILEPATH_SIZE];
    FileMgr_ListData_t      tFileListData;
    DesktopStatus_e         eDskLayout;
    u32                     nFileHandle;
    u32                     nFileNum;
    u32                     nPhoneFileHandle;
    u32                     nPhoneFileNum;
    u32                     nInitHandle;
} PhotoDesktopWdg_t;

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/
//static u32 PhotoDesktopWidget_Release(IAbsContainer*);

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
static MAE_Ret PhotoDesktopWidget_Ctor(PhotoDesktopWdg_t*);
static void PhotoDesktopWidget_Dtor(PhotoDesktopWdg_t*);

static boolean PhotoDesktopWidget_DefHandleEvent(IAbsContainer*, MAEEvent_t, u32, u32);
static boolean PhotoDesktopWidget_SetProperty(PhotoDesktopWdg_t*, u32, u32);
static boolean PhotoDesktopWidget_GetProperty(PhotoDesktopWdg_t*, u32, u32);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_PHOTODESKTOP_PRIV_H__
/*=============================================================*/
// end of file
