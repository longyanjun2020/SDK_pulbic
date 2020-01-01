/**
 * @file    mmi_wdg_glowtext_priv.h
 *
 */

#ifndef __MMI_WDG_GLOWTEXT_PRIV_H__
#define __MMI_WDG_GLOWTEXT_PRIV_H__

#ifdef __3D_UI_KEYGUARD_GLOW__

#include "mae_abscontainerbase.h"
#include "mae_animation.h"

/*  Declarations */

typedef struct
{
    AbsContainerBase_t AbsCntrBase;
    ICORESRV  *pICoreSrv;
	IWidget *pITextWdg;
	IWidget *pIImgWdg;    
    MAE_WChar* pStrResult;        
    boolean bWait;    
    u32     nWaitSteps;
	u32	nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
}_MAE_GlowTextWidget;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/

MAE_Ret GlowTextWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean GlowTextWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/

MAE_Ret _WdgGlowTextConstructor(_MAE_GlowTextWidget *pThis);
void _WdgGlowTextDestructor(_MAE_GlowTextWidget *pThis);

#endif

#endif /* __MMI_WDG_GLOWTEXT_PRIV_H__ */

