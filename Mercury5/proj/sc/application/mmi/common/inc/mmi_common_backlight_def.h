/**
 * @file    mmi_common_backlight_def.h
 * @brief   The document describes the backlight definitions 
 * 
 */
 
#ifndef __MMI_COMMON_BACKLIGHT_DEF_H__
#define __MMI_COMMON_BACKLIGHT_DEF_H__

#include "mmi_mae_common_def.h"
#include "mmi_class.h"
#include "mmi_coresrv.h"

typedef struct {
    MAE_ClsId   nClsId;
    MultiBKLSetting tBacklightSetting;
}BacklightMapping_t;

__SLDPM_FREE__ static const BacklightMapping_t Backlight_Mapping[] = {{0}};
    /*{CLSID_IDLEAPP, {NULL, CORESRV_BACKLIGHT_4LAYER, {{CORESRV_BACKLIGHT_LEVEL_6, 5000, NULL}, {CORESRV_BACKLIGHT_LEVEL_4, 5000, NULL}, {CORESRV_BACKLIGHT_LEVEL_1, 5000, NULL}, {CORESRV_BACKLIGHT_LEVEL_0, 5000, NULL} }, TRUE}    },*/


#endif /* __MMI_COMMON_BACKLIGHT_DEF_H__ */

