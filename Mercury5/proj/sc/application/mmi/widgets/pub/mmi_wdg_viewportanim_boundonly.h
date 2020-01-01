#ifndef __MMI_WDG_VIEWPORTANIM_BOUNDONLY_H__
#define __MMI_WDG_VIEWPORTANIM_BOUNDONLY_H__

#include "mmi_wdg_viewport.h"

ViewportAnimStyleData_t *BoundonlyStyleCreate(IWidget *pViewportWdg, ViewportAnimInitData_t *pViewportInitData, ViewportAnimUserData_t *pAnimUserData);
MAE_Ret BoundonlyStyleSet(ViewportAnimStyleData_t *pAnimData, ViewportAnimCommonData_t *pViewportCommonData);
MAE_Ret BoundonlyStyleStart(ViewportAnimStyleData_t *pAnimData);
MAE_Ret BoundonlyStyleStop(ViewportAnimStyleData_t *pAnimData);
MAE_Ret BoundonlyStyleDestroy(ViewportAnimStyleData_t *pAnimData);

#endif
