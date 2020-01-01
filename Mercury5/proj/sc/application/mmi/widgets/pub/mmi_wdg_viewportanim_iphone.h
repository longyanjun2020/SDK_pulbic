#ifndef __MMI_WDG_VIEWPORTANIM_IPHONE_H__
#define __MMI_WDG_VIEWPORTANIM_IPHONE_H__

#include "mmi_wdg_viewport.h"

ViewportAnimStyleData_t *IPhoneStyleCreate(IWidget *pViewportWdg, ViewportAnimInitData_t *pViewportInitData, ViewportAnimUserData_t *pAnimUserData);
MAE_Ret IPhoneStyleSet(ViewportAnimStyleData_t *pAnimData, ViewportAnimCommonData_t *pViewportCommonData);
MAE_Ret IPhoneStyleStart(ViewportAnimStyleData_t *pAnimData);
MAE_Ret IPhoneStyleStop(ViewportAnimStyleData_t *pAnimData);
MAE_Ret IPhoneStyleDestroy(ViewportAnimStyleData_t *pAnimData);

#endif
