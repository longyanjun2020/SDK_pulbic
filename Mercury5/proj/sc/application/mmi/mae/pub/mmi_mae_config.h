/**
 * @file    mmi_mae_config.h
 * @brief   The document describes the interface of IConfig
 * @version
 */

#ifndef __MMI_MAE_CONFIG_H__
#define __MMI_MAE_CONFIG_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_handler.h"
#include "mmi_mae_config_forward.h"

#define MAECFGMASK(ID)  (1<<(ID&0x00FF))

#define INHERIT_IConfig(IName)\
	INHERIT_IHandler(IName);\
	MAE_Ret (*SetItem)        (IName *pIConfig, MAECfgCategory_t Cat, MAECfgItemId_t ID, void *pData, u32 size);\
	MAE_Ret (*GetItem)        (IName *pIConfig, MAECfgCategory_t Cat, MAECfgItemId_t ID, void *pData, u32 size);\
	MAE_Ret (*AddListener)    (IName *pIConfig, MAECfgCategory_t Cat, ConfigListener_t *pCfgLsn);\
	MAE_Ret (*CancelListener) (IName *pIConfig, MAECfgCategory_t Cat, ConfigListener_t *pCfgLsn)

DEFINE_INTERFACE(IConfig);

#define CFGLISTENER_INIT(_pCfgLsn, _pfn, _pUserData, _mask) do{ \
	(_pCfgLsn)->pUsrData = (void*)(_pUserData); \
	(_pCfgLsn)->pCfgListener = _pfn; \
	(_pCfgLsn)->nMask = (_mask); \
	(_pCfgLsn)->pConfig = NULL; \
	(_pCfgLsn)->pNext = NULL; \
}while(0)

#define CFGLISTENER_CANCEL(_pCfgLsn, _cat) do{\
	if((_pCfgLsn)->pConfig) {\
		ICONFIG_CancelListener((_pCfgLsn)->pConfig,_cat,_pCfgLsn); }\
}while(0)

/**
 *  ICONFIG_QueryInterface(IConfig *pIConfig, MAE_IId id, void **ppObj, IBase *pOwner)
 *
 *  @brief  Inherit addref from IBase to query interface. It only support the interface of IConfig.
 *
 *  @param  pIConfig        [in]Pointer to the IConfig interface
 *  @param  id              [in]Interface ID. In this function, only IID_CONFIG is supported.
 *  @param  ppObj           [out]Reference to a pointer to a function table if this interface is supported
 *  @param  pOwner			[in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval MAE_RET_SUCCESS         Success
 *  @retval MAE_RET_NOT_SUPPORTED   Not support this interface
 *
 */
#define ICONFIG_QueryInterface(pIConfig,id,pp,pOwner)      GET_FUNCTBL(pIConfig,IConfig)->QueryInterface(pIConfig,id,pp,pOwner)

/**
 *  ICONFIG_SetItem(IConfig *pIConfig, MAECfgCategory_t Cat, MAECfgItemId_t ID, void *pData, u32 size)
 *
 *  @brief  This function sets config item to IConfig
 *
 *  @param  pIConfig      [in]Pointer to the IConfig interface object
 *  @param  Cat           [in]Category ID
 *  @param  ID            [in]Item ID
 *  @param  pData         [in]Pointer to the memory of item data
 *  @param  size          [in]Size of the data in pData
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_NOT_READY      IConfig is not created yet
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED  Category ID or Item ID is not supported
 */
#define ICONFIG_SetItem(pIConfig,Cat,ID,pData,size)        GET_FUNCTBL(pIConfig,IConfig)->SetItem(pIConfig,Cat,ID,pData,size)

/**
 *  MAEConfig_GetItem(IConfig *pIConfig, MAECfgCategory_t Cat, MAECfgItemId_t ID, void *pData, u32 size)
 *
 *  @brief  This function gets config item from IConfig
 *
 *  @param  pIConfig      [in]Pointer to the IConfig interface object
 *  @param  Cat           [in]Category ID
 *  @param  ID            [in]Item ID
 *  @param  pData         [out]Pointer to the memory of item data to store
 *  @param  size          [in]Size of the memory pData points to
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_NOT_READY      IConfig is not created yet
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED  Category ID or Item ID is not supported
 */
#define ICONFIG_GetItem(pIConfig,Cat,ID,pData,size)        GET_FUNCTBL(pIConfig,IConfig)->GetItem(pIConfig,Cat,ID,pData,size)

/**
 *  ICONFIG_AddListener(IConfig *pIConfig, MAECfgCategory_t Cat, ConfigListener_t *pCfgLsn)
 *
 *  @brief  This function adds listener to IConfig
 *
 *  @param  pIConfig      [in]Pointer to the IConfig interface object
 *  @param  Cat           [in]Category ID
 *  @param  pCfgLsn       [in]Pointer to ConfigListener_t to register
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 *  @retval MAE_RET_NOT_READY      IConfig is not created yet
 */
#define ICONFIG_AddListener(pIConfig,Cat,pCfgLsn)          GET_FUNCTBL(pIConfig,IConfig)->AddListener(pIConfig,Cat,pCfgLsn)

/**
 *  ICONFIG_CancelListener(IConfig *pIConfig, MAECfgCategory_t Cat, ConfigListener_t *pCfgLsn)
 *
 *  @brief  This function cancels listener to IConfig
 *
 *  @param  pIConfig      [in]Pointer to the IConfig interface object
 *  @param  Cat           [in]Category ID
 *  @param  pCfgLsn       [in]Pointer to ConfigListener_t to cancel
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_NOT_READY      IConfig is not created yet
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 */
#define ICONFIG_CancelListener(pIConfig,Cat,pCfgLsn)       GET_FUNCTBL(pIConfig,IConfig)->CancelListener(pIConfig,Cat,pCfgLsn)

/**
 * Functions
 */
/**
 *  MAEConfig_New(MAE_ClsId nClsID, void **ppObj)
 *
 *  @brief  This function creates IConfig interface object
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_OUT_OF_MEMORY  Cannot allocate memory for new object
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 */
MAE_Ret MAEConfig_New(MAE_ClsId nClsID, void **ppObj);

/**
 *  MAEConfig_SetItem(MAECfgCategory_t nCat, MAECfgItemId_t nId, void *pData, u32 nSize)
 *
 *  @brief  This function sets config item to IConfig
 *
 *  @param  nCat           [in]Category nId
 *  @param  nId            [in]Item nId
 *  @param  pData         [in]Pointer to the memory of item data
 *  @param  nSize          [in]Size of the data in pData
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_NOT_READY      IConfig is not created yet
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED  Category nId or Item nId is not supported
 */
MAE_Ret MAEConfig_SetItem(MAECfgCategory_t nCat, MAECfgItemId_t nId, void *pData, u32 nSize);

/**
 *  MAEConfig_GetItem(MAECfgCategory_t nCat, MAECfgItemId_t nId, void *pData, u32 nSize)
 *
 *  @brief  This function gets config item from IConfig
 *
 *  @param  nCat           [in]Category nId
 *  @param  nId            [in]Item nId
 *  @param  pData         [out]Pointer to the memory of item data to store
 *  @param  nSize          [in]Size of the memory pData points to
 *
 *  @retval MAE_RET_SUCCESS        Successfully
 *  @retval MAE_RET_NOT_READY      IConfig is not created yet
 *  @retval MAE_RET_BAD_PARAM      Illigal parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED  Category nId or Item nId is not supported
 */
MAE_Ret MAEConfig_GetItem(MAECfgCategory_t nCat, MAECfgItemId_t nId, void *pData, u32 nSize);


#endif /* __MAE_CONFIG_H__ */
