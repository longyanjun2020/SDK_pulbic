/**
 * \file    mae_config_priv.h
 * \brief   The document describes the private data structure used in mae_config.c
 * \author  sam.chen@mstarsemi.com
 * @version
 */
#ifndef __MAE_CONFIG_PRIV_H__
#define __MAE_CONFIG_PRIV_H__

#include "mmi_mae_config.h"

/**
 *  MAEConfig_Init(void)
 *
 *  @brief  This function initializes everything for IConfig
 *
 *  @retval MAE_RET_SUCCESS    Successfully
 */
MAE_Ret MAEConfig_Init(void);

/**
 *  MAEConfig_AddListener(MAECfgCategory_t nCat, ConfigListener_t *pCfgLsn)
 *
 *  @brief  This function adds listener to IConfig
 *
 *  @param  nCat           [in]Category nId
 *  @param  pCfgLsn       [in]Pointer to ConfigListener_t to register
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 *  @retval MAE_RET_NOT_READY      IConfig is not created yet
 */
MAE_Ret MAEConfig_AddListener(MAECfgCategory_t nCat, ConfigListener_t *pCfgLsn);

/**
 *  MAEConfig_CancelListener(MAECfgCategory_t nCat, ConfigListener_t *pCfgLsn)
 *
 *  @brief  This function cancels listener to IConfig
 *
 *  @param  nCat           [in]Category nId
 *  @param  pCfgLsn       [in]Pointer to ConfigListener_t to cancel
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_NOT_READY      IConfig is not created yet
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 */
MAE_Ret MAEConfig_CancelListener(MAECfgCategory_t nCat, ConfigListener_t *pCfgLsn);

#endif /* __MAE_CONFIG_PRIV_H__ */
