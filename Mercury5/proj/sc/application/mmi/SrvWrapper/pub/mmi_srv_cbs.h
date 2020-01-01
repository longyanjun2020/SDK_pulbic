/**
* @file    mmi_srv_cbs.h
* @brief   
*          
*
* @author  
* @version $Id:
*/

#ifndef __MMI_SRV_CBS_H__
#define __MMI_SRV_CBS_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_cbsrv.h"

/**
SRV_CBS EV and Callback Function descript
@brief  The interface of Service Client is use to set the indicator-callback to CB module

CBS_Notify_Mask_Ready
Group1:CBS_Notify_Mask_Ready
CBS_EVT_READY

Group2:CBS_Notify_Mask_Status
CBS_EVT_NEW_CBMSG
CBS_EVT_UPDATE_CBNUM
CBS_EVT_DEL_CBMSG
*/

typedef void (* SrvCbsReadyNotify_CB)(void *pThis);
/** SrvCbsSetReadyCB
@brief  The interface of Service Client is use to set CB to listen the ready

@param[in]  pfnCallBack     CBS_EVT_READY Call back function point

@retval MAE_RET_SUCCESS     Success
@retval MAE_RET_BAD_PARAM   Failed, NULL cbs instance or NULL resigter instance
*/
MAE_Ret SrvCbsSetReadyNotifyCB(SrvCbsReadyNotify_CB pfnCallBack);

typedef void (* SrvCbsNewCbMsgNotify_CB)(void *pThis, SMI_MsgID_t MsgID);
/** SrvCbsSetNewCbMsgNotifyCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]  pfnCallBack     CBS_EVT_NEW_CBMSG CB func point

@retval MAE_RET_SUCCESS     Success
@retval MAE_RET_BAD_PARAM   Failed, NULL cbs instance or NULL resigter instance
*/
MAE_Ret SrvCbsSetNewCbMsgNotifyCB(SrvCbsNewCbMsgNotify_CB pfnCallBack);

typedef void (* SrvCbsCbNumUpdateNotify_CB)(void *pThis, u32 num);
/** SrvCbsSetCbNumUpdateNotifyCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]  pfnCallBack     CBS_EVT_UPDATE_CBNUM CB func point

@retval MAE_RET_SUCCESS     Success
@retval MAE_RET_BAD_PARAM   Failed, NULL cbs instance or NULL resigter instance
*/
MAE_Ret SrvCbsSetCbNumUpdateNotifyCB(SrvCbsCbNumUpdateNotify_CB pfnCallBack);

typedef void (* SrvCbsDelCbMsgNotify_CB)(void *pThis, SMI_MsgID_t MsgID);
/** SrvCbsDelCbMsgNotifyCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]  pfnCallBack     CBS_EVT_DEL_CBMSG CB func point

@retval MAE_RET_SUCCESS     Success
@retval MAE_RET_BAD_PARAM   Failed, NULL cbs instance or NULL resigter instance
*/
MAE_Ret SrvCbsDelCbMsgNotifyCB(SrvCbsDelCbMsgNotify_CB pfnCallBack);

/** SrvCbsisReady
@brief  The interface of Service Client is used to get current cbs srv status.

@retval bReady              Pointer to an boolean returning cbs status
*/
boolean SrvCbsisReady(void);

/** SrvCbsGet_CBMsgByIdx
@brief  The interface of Service Client is used to get cb Msg info by index.

@param[out]  pCBMsg         return pointer of new cb message info.
@param[in]   nIdx           idx of CBS.

@retval MAE_RET_SUCCESS     Success
@retval MAE_RET_NOT_FOUND   Failed,no CB msg  
*/
MAE_Ret SrvCbsGet_CBMsgByIdx(CBS_MsgInfo_t **pCBMsg, u32 nIdx);

/** SrvCbsGet_TotalCBMsgCount
@brief  The interface of Service Client is used to get current CB msg total number.

@param[out]     nCount      return count of cb msg.

@retval MAE_RET_SUCCESS     If successful.
@retval MAE_RET_FAILED      If an error happen. 
*/
MAE_Ret SrvCbsGet_TotalCBMsgCount(u32 *nCount);

/** SrvCbsGet_CBAreaCode
@brief  The interface of Service Client is used to get current CBM Area Code.
@param[in]      nSIMModule           SIM id
@param[out]     ppCBAreaCode

@retval MAE_RET_SUCCESS     If successful.
@retval MAE_RET_FAILED      If an error happen. 
*/
MAE_Ret SrvCbsGet_CBAreaCode(u16 **ppCBAreaCode, u8 nSIMModule);

/** SrvCbsDel_CBMsgByID
@brief  The interface of Service Client is used to delete CB msg by MsgID.

@param[in]      nID         CB msgID.

@retval MAE_RET_SUCCESS     Success
@retval MAE_RET_NOT_FOUND   Failed, no CBMsg 
*/
MAE_Ret SrvCbsDel_CBMsgByID(u32 nID);

/*-----------------------------------------------------*/

#endif /* __MMI_SRV_CBS_H__ */
