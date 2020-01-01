/**
 * @file    mmi_pedometerwidget_priv.h
 * @brief   The internal structure of the pedometer widget

 */

#ifndef __MAE_PEDOMETERWIDGET_PRIV_H__
#define __MAE_PEDOMETERWIDGET_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_settingapp.h"
#include "mmi_common_cfg.h"
#include "rs_layout_id.h"

typedef struct _PedoWdg_LaunchApp_Info
{
	boolean bIsStartEx;
	MAEClsId_t apClsid;
	u32 uParam;								// Only used in startEx
	pfnStartParamCleanup_t fnClean;			// Only used in startEx

}PedoWdg_LaunchApp_Info;

typedef struct
{
    //DECLARE_BASECLASS_DESKTOPWIDGET
    AbsContainer_t	AbsCntrBase;
    // Subwidget codes
    IWidget			*pITextWidget;
    IPEDOMETERSRV   *pIPedometerSrv;
    PedoWdg_LaunchApp_Info launchApInfo;

} PedometerWdg_t;

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/
static u32 PedometerWidget_AddRef(IAbsContainer*);
static u32 PedometerWidget_Release(IAbsContainer*);

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/
void PedometerWidget_Draw(IAbsContainer *pIAbsContainer, IDispCanvas *pDispCanvas, s32 x, s32 y);

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
static MAE_Ret PedometerWidget_Ctor(PedometerWdg_t*);
static void PedometerWidget_Dtor(PedometerWdg_t*);

static boolean PedometerWidget_DefHandleEvent(IAbsContainer*, MAEEvent_t, u32, u32);

#endif //__MAE_PEDOMETERWIDGET_PRIV_H__
/*=============================================================*/
// end of file

