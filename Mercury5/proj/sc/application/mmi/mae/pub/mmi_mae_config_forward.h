/**
 * @file mmi_mae_config_forward.h
 *
 * 
 *
 * @version $Id: mmi_mae_config_forward.h $
 */

#ifndef __MMI_MAE_CONFIG_FORWARD_H__
#define __MMI_MAE_CONFIG_FORWARD_H__

#include "mmi_mae_common_def.h"

typedef struct ConfigListener_t_ ConfigListener_t;
typedef u32 MAECfgCategory_t; ///enum MAECfgCategory_t_
typedef u32 MAECfgItemId_t; ///enum MAECfgItemId_t_

typedef void (*PfnCfgListener) (void *pUsrData, MAECfgCategory_t cat, MAECfgItemId_t id, void *pItemData);

#endif //__MMI_MAE_CONFIG_FORWARD_H__

