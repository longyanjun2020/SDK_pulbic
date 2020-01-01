/**
* @file    mmi_srv_config.h
* @brief   The document describes the service wrapper interface of IConfig
*          
*/

#ifndef __MMI_SRV_CONFIG_H__
#define __MMI_SRV_CONFIG_H__

/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_config.h"

/*-----------------------------------------------------*/
typedef void (* SrvConfigLanguageCB)(void *pThis, MAE_LANG_CODE_e eCode); // MAECFGSYS_ID_LANGUAGE
typedef void (* SrvConfigOSDStatMainDispCB)(void *pThis, boolean bOn); // MAECFGSYS_ID_OSDSTAT_MAINDISP
typedef void (* SrvConfigOSDStatSubDispCB)(void *pThis, boolean bOn); // MAECFGSYS_ID_OSDSTAT_SUBDISP
typedef void (* SrvConfigMotionDetectorStatCB)(void *pThis, boolean bOn); // MAECFGSYS_ID_MOTION_DETECTOR_STAT


typedef struct
{
    MAECfgCategory_t eCategory;
    MAECfgItemId_t eItemID;
    void *pItemData;
} SysConfigChangeInfo_t;

/*-----------------------------------------------------*/

/** SrvConfigSetItem
@brief  This function sets config item to IConfig
 
@param[in] eCategory        Category ID
@param[in] eID              Item ID
@param[in] pData            Pointer to the memory of item data
@param[in] nSize            Size of the data in pData

@retval MAE_RET_SUCCESS     If successful.            
*/
MAE_Ret SrvConfigSetItem(MAECfgCategory_t eCategory, MAECfgItemId_t eID, void *pData, u32 nSize);

/** SrvConfigGetItem
@brief  This function gets config item from IConfig
 
@param[in]  eCategory       Category ID
@param[in]  eID             Item ID
@param[out] pData           Pointer to the memory of item data to store
@param[in]  nSize           Size of the memory pData points to

@retval MAE_RET_SUCCESS     If successful.            
*/
MAE_Ret SrvConfigGetItem(MAECfgCategory_t eCategory, MAECfgItemId_t eID, void *pData, u32 nSize);

/** SrvConfigSetxxxCB
@brief  This function set CB to listen to the value change of system config items
 
@param[in] pfnCallBack      Pointer to the callback function which listen to the specific event.
 
@retval MAE_RET_SUCCESS     If successful.            
*/
MAE_Ret SrvConfigSetLanguageCB(SrvConfigLanguageCB pfnCallBack);

MAE_Ret SrvConfigSetOSDStatMainDispCB(SrvConfigOSDStatMainDispCB pfnCallBack);

MAE_Ret SrvConfigSetOSDStatSubDispCB(SrvConfigOSDStatSubDispCB pfnCallBack);

MAE_Ret SrvConfigSetMotionDetectorStatCB(SrvConfigMotionDetectorStatCB pfnCallBack);

#endif //__MMI_SRV_CONFIGSERVICE_H__
/*-----------------------------------------------------*/
