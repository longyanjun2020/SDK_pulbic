/**
 * @file    mmi_unitconverter_cfg.h
 *
 * @brief   This file is auto generate by XRG tool. Do not modify file directly
 *
 * @version $Id:$
 *
 * @time
 */

#ifndef __MMI_UNITCONVERTER_CFG__H__
#define __MMI_UNITCONVERTER_CFG__H__

#include "mmi_mae_common_def.h"
#define NUM_CURRENCY (12+1)
#define CUSTOM_CURRENCY_STRLEN (40+1)
typedef struct _UnitConverter_Selection_t
{
    u32 nLastSelectedConType;
    u32 nLastSelectedUnitType1;
    u32 nLastSelectedUnitType2;
} UnitConverter_Selection_t;
typedef struct _UnitConverter_DataStore_t
{
    double rates[NUM_CURRENCY][NUM_CURRENCY];
    MAE_WChar Text[CUSTOM_CURRENCY_STRLEN];
} UnitConverter_DataStore_t;

#endif /* __MMI_UNITCONVERTER_CFG__H__ */
