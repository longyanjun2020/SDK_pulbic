/**
* @file    mmi_srv_config.h
* @brief
*
*/

#ifndef __MMI_SRV_CFG_H__
#define __MMI_SRV_CFG_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_cfgsrv.h"

typedef union
{
    MAE_Ret nRstoreRet;
    CFGItemID_e eItemUpdateID;
} SrvCfgItemUpdateResult_t;

enum
{
    SrvCfgItemUpdate, //eid
    SrvCfgItemRestoreStart, //nResult
    SrvCfgItemRestoreEnd  //nResult
};
typedef u8 SrvCfgItemStatusChangeType_e;

typedef void (* SrvCfgRestoreItemResultCB)(void *pThis, u8 u8Result); //ICFGSrv_EVT_RESTORE_ITEM_RESULT, RESTORE_ITEM_RESULT_SUCCESS

// model listener notify event : ICFGSrv_EVT_ITEM_RESTORE_START
// model listener notify event : ICFGSrv_EVT_ITEM_RESTORE_END
// model listener notify event : ICFGSrv_EVT_ITEM_UPDATE
typedef void (* SrvCfgItemUpdateIndCB)(void *pThis, SrvCfgItemStatusChangeType_e IndType, SrvCfgItemUpdateResult_t tresult);

/** SrvCfgSetItemUpdateIndCB
@brief  The interface of Service Client is use to set CB to listen the item statue change Ind

@param[in]      pfnCallBack         SrvCfgItemUpdateIndCB Call back function point

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
*/
MAE_Ret SrvCfgSetItemUpdateIndCB(SrvCfgItemUpdateIndCB pfnStatusCB);

/** SrvCfgGetItem
@brief  The interface is use to get configuration item value

@param[in]      eId                 Configuration item id
@param[Out]     pItemBuffer         Pointer to the memory buffer which will store Configuration item value.
                                    Buffer have to be prepared by user.
@param[in]      nBufferSize         ItemBuffer size for configuration item

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
*/
__SLDPM_FREE__ MAE_Ret SrvCfgGetItem(CFGItemID_e eId, void *pItemBuffer, u32 nBufferSize);

/** SrvCfgSetItem
@brief  The interface is use to set configuration item value

@param[in]      eId                 Configuration item id
@param[Out]     pItemBuffer         Pointer to the memory buffer which will store Configuration item value.
                                    Buffer have to be prepared by user.
@param[in]      nBufferSize         ItemBuffer size for configuration item

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
*/
MAE_Ret SrvCfgSetItem(CFGItemID_e eId, void *pItemBuffer, u32 nBufferSize);

/** SrvCfgSetItemsByBatch
@brief  The interface is use to set numbers of configuration item value

@param[Out]     pItemBuffer         Pointer to the memory buffer which will store  Configuration items value.
                                    Buffer have to be prepared by user.
@param[in]      nNumItemInfo        Numbers of configuration item

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
*/
MAE_Ret SrvCfgSetItemsByBatch(CFGSetItemInfo *pCFGItemInfo, u32 nNumItemInfo);

/** SrvCfgGetDefaultItem
@brief  The interface is use to get default configuration item value

@param[in]      eId                 Configuration item id
@param[Out]     pItemBuffer         Pointer to the memory buffer which will store Configuration item value.
                                    Buffer have to be prepared by user.
@param[in]      nBufferSize         ItemBuffer size for configuration item

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
*/
MAE_Ret SrvCfgGetDefaultItem(CFGItemID_e eId, void *pItemBuffer, u32 nBufferSize);

/** SrvCfgSetDefaultItem
@brief  The interface is use to set default configuration item value

@param[in]      eId                 Configuration item id
@param[Out]     pItemBuffer         Pointer to the memory buffer which will store Configuration item value.
                                    Buffer have to be prepared by user.
@param[in]      nBufferSize         ItemBuffer size for configuration item

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
*/
MAE_Ret SrvCfgSetDefaultItem(CFGItemID_e eId, void *pItemBuffer, u32 nBufferSize);

/** SrvCfgGetSize
@brief  The interface is use to get configuration item size

@param[in]      eId                 Configuration item id
@param[out]     pItemSize           point of the size for configuration item

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
*/
MAE_Ret SrvCfgGetSize(CFGItemID_e eId, u32 *pItemSize);

/** SrvCfgDisableEvent
@brief  The interface is use to disable or enable event notify

@param[in]      bDisable            disable or enable event notify

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
*/
MAE_Ret SrvCfgDisableEvent(boolean bDisable);

/** SrvCfgRestoreCFGItem
@brief  The interface is use to restore the configure item

@param[in]      pCaller             point to instance for Config srv used

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           CFGSRV is already terminated!!! or is doing master reset.
 + post event ICFGSrv_EVT_RESTORE_ITEM_RESULT,
 + pCall used to event posting
*/
__SLDPM_FREE__ MAE_Ret SrvCfgRestoreCFGItem(void *pCaller, SrvCfgRestoreItemResultCB pfnCB);


/*-----------------------------------------------------*/
#endif //__MMI_SRV_CFG_H__
