/**
 * @file    mmi_wdg_profile_priv.h
 * @brief   The internal structure of the profilewidget

 */

#ifndef __MMI_WDG_PROFILE_PRIV_H__
#define __MMI_WDG_PROFILE_PRIV_H__

#include "img_data.h"
#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_common_cfg.h"
#include "mmi_srv_header.h"
#include "rs_layout_id.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
#if defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
#define __ANDROID4_PROFILE_DESKTOPWDG__
#endif // __UI_STYLE_MMI_ANDROID_4_0_GADGET__

#ifdef __ANDROID4_PROFILE_DESKTOPWDG__
typedef enum
{
    PROFILE_WDG_ITEM_DISABLE = 0,
    PROFILE_WDG_ITEM_ON,
	PROFILE_WDG_ITEM_OFF,
} ProfileWdgItemStatus_e;

typedef enum
{
    PROFILE_WDG_ITEM_START = 0,
    PROFILE_WDG_ITEM_1 = PROFILE_WDG_ITEM_START,
    PROFILE_WDG_ITEM_2,
    PROFILE_WDG_ITEM_3,
    PROFILE_WDG_ITEM_4,
    PROFILE_WDG_ITEM_5,
    PROFILE_WDG_ITEM_6,
#if defined(__POWER_SAVING_PROFILE_MMI__) && defined(__EXTRA_BLUETOOTH_HEADSET_PROFILE_MMI__)
    PROFILE_WDG_ITEM_7,
    PROFILE_WDG_ITEM_8,
#elif defined(__POWER_SAVING_PROFILE_MMI__) || defined(__EXTRA_BLUETOOTH_HEADSET_PROFILE_MMI__)
    PROFILE_WDG_ITEM_7,
#endif
    PROFILE_WDG_ITEM_NUM // Item total numbers
} ProfileWdgItemIndex_e;

typedef struct
{
    ProfileID_e eProfileID;
    ProfileWdgItemStatus_e eItemStatus;
} ProfileItemRecord_t;

typedef struct
{
    u32 nImgID_ON;
    u32 nImgID_OFF;
} ProfileWdgImg_t;

typedef struct
{
    IWidget *pIconImgWdg;
    IWidget *pStatusBarImgWdg;
} ProfileItemCompWdg_t;

#endif // __ANDROID4_PROFILE_DESKTOPWDG__

typedef struct
{
    DECLARE_BASECLASS_DESKTOPWIDGET

    ProfileSettings_t stProfileSetting;
    IPROFILESRV        *pIPROFILESRV;

    IWidget            *pITitleTextWidget; // Profile title text
    ModelListener_t ProfileModelListener; // Profile model listener
#ifdef __ANDROID4_PROFILE_DESKTOPWDG__
    ProfileItemRecord_t *pProfileItemRecord; // Record the status of each item
    ProfileItemCompWdg_t pProfileItemCompWdg[PROFILE_WDG_ITEM_NUM]; // Forground widgets(icon & statusbar)
#else
    IWidget            *pIFocusWidget[PROFILESRV_IND_END];
#endif //__ANDROID4_PROFILE_DESKTOPWDG__

    DesktopWidget_DisplayMode_e eDisplayMode;
} ProfileWdg_t;

/*********************************************************/
/* Local Functions */
/*********************************************************/

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__

#endif //__MMI_WDG_PROFILE_PRIV_H__
/*=============================================================*/
// end of file
