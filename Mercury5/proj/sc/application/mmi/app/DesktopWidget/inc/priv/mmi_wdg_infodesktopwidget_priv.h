/**
 * @file    mmi_infodesktopwidget_priv.h
 * @brief   The internal structure of the mp desktopwidget

 */

#ifndef __MAE_INFODESKTOPWIDGET_PRIV_H__
#define __MAE_INFODESKTOPWIDGET_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_abscontainer.h"
//#include "mae_abscontainer_priv.h"
#include "mmi_mae_datamodel.h"

//#include "mmi_wdg_desktop_priv.h"
#include "mmi_wdg_desktop.h"
//#include "mmi_mplayersrv.h"
#include "mmi_audioplayersrv.h"
#include "mmi_cfgsrv.h"
#include "mmi_srv_cbs.h"
#include "mmi_srv_mci.h"
#ifdef __NATIVE_GAME_MMI_PEDOMETER__
#include "mmi_pedometersrv.h"
#endif
#include "mmi_desktopwidget_rs.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)

#define INFODESKTOPWDG_STEPTS_NUM_LEN   16


typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

	IAUDIOPLAYERSRV     *pIMPlayerSrv;
    ICBS           *pICBS;
    IMCI            *pIMCI;
    ModelListener_t CBTextViewMdlListener;
    boolean         bCBSliding;
    Msg_CB_Setting_e eCBMsgSetting;

#ifdef __NATIVE_GAME_MMI_PEDOMETER__
    ModelListener_t PedometerMdlListener;
    IPEDOMETERSRV   *pIPedometerSrv;
#endif

    boolean bSkipBackgroundInd; // A tricky flag tells MP desktop widget doesn't update title and buttons when this flag is set as TRUE


	IWidget			*pITextInfoWidget;
	IWidget			*pITextStepsWidget;
	IWidget			*pITextStepsNumWidget;
	IWidget			*pITextSongWidget;
	IWidget			*pITextCBSWidget;
    IWidget			*pITextNoInfoWidget;
	MAE_WChar		strStepsNum[INFODESKTOPWDG_STEPTS_NUM_LEN];
    boolean         bNoInfoTextExist;

} InfoDesktopWdg_t;


/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
static MAE_Ret InfoDesktopWidget_Ctor(InfoDesktopWdg_t*);
static void InfoDesktopWidget_Dtor(InfoDesktopWdg_t*);
static boolean InfoDesktopWidget_SetProperty(InfoDesktopWdg_t*, u32, u32);
static boolean InfoDesktopWidget_GetProperty(InfoDesktopWdg_t*, u32, u32);

static boolean InfoDesktopWidget_DefHandleEvent(IAbsContainer*, MAEEvent_t, u32, u32);

static MAE_Ret InfoDesktopWidget_UpdateTitle(InfoDesktopWdg_t*);

static void InfoDesktopWidget_ShowLargeWdg(void* pData);
static void InfoDesktopWidget_ShowSmallWdg(void* pData);
static MAE_Ret InfoDesktopWidget_SetStyle(InfoDesktopWdg_t *pThis);
MAE_Ret InfoDesktopWidget_PlayCBMsg(InfoDesktopWdg_t* pThis, u32 nMsgID);
static void InfoDesktopWidget_CBTextViewModelListener(void *pUserData, ModelEvent_t *pMdlEvent);



#endif //defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
#endif //__MAE_DESKTOPWIDGET_PRIV_H__
/*=============================================================*/


// end of file
