/**
 * @file    mmi_wdg_fmdesktop_priv.h
 * @brief   The internal structure of the fm desktopwidget

 */

#ifndef ____MMI_WDG_FMDESKTOP_PRIV_H__
#define ____MMI_WDG_FMDESKTOP_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_fmradiosrv.h"
#include "mmi_cfgsrv.h"
#include "rs_layout_id.h"
#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__)

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
#define __FM_DESKTOPWDG_3D_UI_STYLE__
#endif // 3D UI

#if defined(__APP_MMI_FM_RADIO__)
#define FMDESKTOPWDG_MAX_TITLE_LEN  26

#if defined(__FM_DESKTOPWDG_3D_UI_STYLE__)
#define FMDESKTOPWDG_FREQ_TEXT_MAX_LEN      5
#endif

enum
{
    FM_WDG_SUBWIDGET_VOL,
    FM_WDG_SUBWIDGET_BACK,
    FM_WDG_SUBWIDGET_NEXT,
    FM_WDG_SUBWIDGET_POWER,

// Note this is # of subwidgets need to handle event
    FM_WDG_SUBWIDGET_NUM
};
typedef u16 FmDesktopWidget_SubWidget_e;

typedef struct
{
    DECLARE_BASECLASS_DESKTOPWIDGET

	// Subwidget codes
#if defined(__FM_DESKTOPWDG_3D_UI_STYLE__)
	FmDesktopWidget_Style_e  eFmDeskStyle;
#endif

#if defined(__FM_DESKTOPWDG_3D_UI_STYLE__)
	IWidget 		*pIFreqTextWidget[FMDESKTOPWDG_FREQ_TEXT_MAX_LEN];
	IWidget			*pINameTextWidget;
	IWidget			*pIUnitImageWidget;
#else
	IWidget 		*pIFreqTextWidget;
#endif //#if defined(__3D_UI_IDLE_MULTIPAGE__)
	IWidget			*pIVolumeBtnWidget;
	IWidget			*pIPreviousBtnWidget;
	IWidget			*pINextBtnWidget;
	IWidget			*pIPowerBtnWidget;

    ModelListener_t accListener;
    ModelListener_t usbListener;

    FmrSrvHdl_t     *pIFMRadioSrv;
    IACCESSORYSRV   *pIAccessorySrv;
    IUSBSRV         *pIUsbSrv;

    boolean         bIsLongPressed;         // For skip click event after long press
    boolean         bTouchInSubwidget;

    u16             uSubwidgetIndex;
    u32             uCurFrequency;

	MAE_WChar		strFrequency[FMDESKTOPWDG_MAX_TITLE_LEN];
#if defined(__FM_DESKTOPWDG_3D_UI_STYLE__)
	FMR_CHANNEL_RECORD_t    tMyChannelList[FMR_CHANNEL_NUM_MAX];
#endif //#if defined(__FM_DESKTOPWDG_3D_UI_STYLE__)

    Subwidget_Geometry_Info subwgtGeoInfo[FM_WDG_SUBWIDGET_NUM];

} FmDesktopWdg_t;

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
#if defined(__FM_DESKTOPWDG_3D_UI_STYLE__)
MAE_WChar* FmDesktopWidget_GetChannelName(FmDesktopWdg_t* pThis, u32 nFreq);
#endif //#if defined(__FM_DESKTOPWDG_3D_UI_STYLE__)
void FmDesktopWidgetFreeButtonDataModel(void *pUserData, IBase *pOwner);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__
#endif // __APP_MMI_FM_RADIO__

#endif //____MMI_WDG_FMDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
