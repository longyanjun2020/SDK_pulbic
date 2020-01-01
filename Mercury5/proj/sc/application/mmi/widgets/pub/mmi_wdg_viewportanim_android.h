#ifndef __MMI_WDG_VIEWPORTANIM_ANDROID_H__
#define __MMI_WDG_VIEWPORTANIM_ANDROID_H__

#include "mmi_wdg_viewport.h"

ViewportAnimStyleData_t *AndroidStyleCreate(IWidget *pViewportWdg, ViewportAnimInitData_t *pViewportInitData, ViewportAnimUserData_t *pAnimUserData);
MAE_Ret AndroidStyleSet(ViewportAnimStyleData_t *pAnimData, ViewportAnimCommonData_t *pViewportCommonData);
MAE_Ret AndroidStyleStart(ViewportAnimStyleData_t *pAnimData);
MAE_Ret AndroidStyleStop(ViewportAnimStyleData_t *pAnimData);
MAE_Ret AndroidStyleDestroy(ViewportAnimStyleData_t *pAnimData);

typedef struct
{
    boolean bSnapToGrid;
    u32 nGridSizeY;
} AndroidStyleUserData_t;

#endif
