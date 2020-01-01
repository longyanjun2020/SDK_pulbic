/**
 * @file    mmi_wdg_aclockdesktop_priv.h
 * @brief   The internal structure of the digital clock desktopwidget

 */

#ifndef __MMI_WDG_ACLOCKDESKTOP_PRIV_H__
#define __MMI_WDG_ACLOCKDESKTOP_PRIV_H__

#include "mmi_wdg_desktop.h"
#include "mmi_settingapp.h"
#include "mmi_common_util.h"
#include "mmi_common_cfg.h"
#include "mmi_mae_image.h"
#include "rs_layout_id.h"
#include "mmi_coresrv.h"
#include "mmi_mae_clock_types.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)

#ifdef __UI_STYLE_MMI_ANDROID_4_0_GADGET__
#define __ANDROID4_ACLOCK_DESKTOPWDG__
#endif // __UI_STYLE_MMI_ANDROID_4_0_GADGET__

//These release/free macro does not clear the variable to 0
#define ACLOCK_RELEASEIF(_pObj, pOwner)  (void)((_pObj)&&RELEASE(_pObj, pOwner))
#define ACLOCK_FREEIF(_pMem)  (void)((_pMem)&&FREE(_pMem))
#define PI                       3.14159265
#define ANGLE_ARC   PI / 180

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
#define __ACLOCKDESKTOP_DRAW_HANDS_USE_2D__
#define __ACLOCKDESKTOP_NO_SECHAND__

typedef enum
{
    ACLOCKDESKTOP_DRAWITEM_BG = 0,
    ACLOCKDESKTOP_DRAWITEM_SECHAND,
    ACLOCKDESKTOP_DRAWITEM_MINBG,
    ACLOCKDESKTOP_DRAWITEM_AMPM,
    ACLOCKDESKTOP_DRAWITEM_TIMEZONE,
    ACLOCKDESKTOP_DRAWITEM_HOURHAND,
    ACLOCKDESKTOP_DRAWITEM_MINHAND,

    ACLOCKDESKTOP_DRAWITEM_COUNT
}AclockDesktopDrawItems;

typedef enum
{
    ACLOCKDESKTOP_HAND_SECOND = 0,
    ACLOCKDESKTOP_HAND_MINITE,
    ACLOCKDESKTOP_HAND_HOUR,

    ACLOCKDESKTOP_HAND_COUNT
}AclockDesktopHandIndex;
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)

typedef struct
{
	u8  hour;			///< Hour, value range is 0~23
	u8  minute;			///< Minute, value range is 0~59
	u8  second;			///< Second, value range is 0~59 (Not use)
}AclockDesktopWidget_DateTime_t;

enum
{
	ACLOCKDESKTOPWIDGET_SMALL_MODE,
	ACLOCKDESKTOPWIDGET_LARGE_MODE,

	ACLOCKDESKTOPWIDGET_MODE_COUNT
};

typedef u8 AclockDesktopWidget_Mode_e;

typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

	// Subwidget codes
	ClockListener_t IClockListener;
	IClock			*pIClock;
	ICORESRV		*pICoreSrv;

	SetPhoneTimeFormat_e	eTimeFormat;
    AClockDesktopWidget_Style_e  eAClockStyle;
    IWidget         *pMinDotImageWdg;
    IWidget         *pHourDotImageWdg;

#if defined(__ACLOCKDESKTOP_DRAW_HANDS_USE_2D__)
    IWidget         *pAMPMImageWdg;
    IWidget         *pMinBGImageWdg;
    IWidget         *pSecHandImageWdg;
#endif
    IWidget         *pMinHandImageWdg;
    IWidget         *pHourHandImageWdg;

    IWidget         *pIconMinHandImageWdg;
    IWidget         *pIconHourHandImageWdg;

	AclockDesktopWidget_Mode_e eAclockMode;

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
    u32             nNodeId;

    boolean         bPauseTimeUpdate;

    u32             nImgIdDrawItems[ACLOCKDESKTOP_DRAWITEM_COUNT];
    float           fHandsAngle[ACLOCKDESKTOP_HAND_COUNT];

    // World clock
    MAE_TimeZone_e  eTimeZone;
    IWidget         *pTimeZoneTextWdg;
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)

	// For Time information
	AclockDesktopWidget_DateTime_t stClockTime;
	boolean bUpdateTimeBeforeDraw;

} AclockDesktopWdg_t;

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/

void AclockDesktopWidget_Draw(IAbsContainer *pIAbsContainer, IDispCanvas *pDispCanvas, s32 x, s32 y);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__ || __3D_UI_IDLE_SIMPLE__

#endif //__MMI_WDG_ACLOCKDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
