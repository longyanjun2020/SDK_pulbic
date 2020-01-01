/**
* @file    mmi_srv_mms.h
* @brief   
*          
*
* @author  
* @version $Id:
*/

#ifndef __MMI_SRV_MMS_H__
#define __MMI_SRV_MMS_H__


/*-----------------------------------------------------*/
#include "mmi_mmssrv.h"
#include "mmi_srv_client_commondefine.h"
#include "stdio.h"
#include "stdlib.h"

/**
SRV_MMS EV and Callback Function descript
@brief  The interface of Service Client is use to set the indicator-callback to CB module

MMS_NOTIFY_MASK_SERVICE_STATUS_IND
Group1:SrvMmsStatus_CB
MMS_EVT_ServiceNotReadyInd
MMS_EVT_ServiceReadyInd
MMS_EVT_ServiceSuspendInd
MMS_EVT_ServiceResumedInd
MMS_EVT_MessageReSyncStartInd
MMS_EVT_MessageReSyncEndInd

*/

typedef void (* SrvMmsServiceNotReadyInd_CB)(void *pThis); 
/**
SRV_SMI_SetServiceNotReadyIndCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             MMS_EVT_ServiceNotReadyInd CB func point
*/
void SrvMmsSetServiceNotReadyIndCB(SrvMmsServiceNotReadyInd_CB pfnCallBack);

typedef void (* SrvMmsServiceReadyInd_CB)(void *pThis); 
/**
SrvMmsSetServiceReadyIndCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             MMS_EVT_ServiceReadyInd CB func point
*/
void SrvMmsSetServiceReadyIndCB(SrvMmsServiceReadyInd_CB pfnCallBack);

typedef void (* SrvMmsServiceSuspendInd_CB)(void *pThis); 
/**
SrvMmsSetServiceSuspendIndCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             MMS_EVT_ServiceSuspendInd CB func point
*/
void SrvMmsSetServiceSuspendIndCB(SrvMmsServiceSuspendInd_CB pfnCallBack);

typedef void (* SrvMmsServiceResumedInd_CB)(void *pThis); 
/**
SrvMmsSetServiceResumedIndCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             MMS_EVT_ServiceResumedInd CB func point
*/
void SrvMmsSetServiceResumedIndCB(SrvMmsServiceResumedInd_CB pfnCallBack);

typedef void (* SrvMmsMessageReSyncStartInd_CB)(void *pThis); 
/**
SrvMmsSetMessageReSyncStartIndCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             MMS_EVT_MessageReSyncStartInd CB func point
*/
void SrvMmsSetMessageReSyncStartIndCB(SrvMmsMessageReSyncStartInd_CB pfnCallBack);

typedef void (* SrvMmsMessageReSyncEndInd_CB)(void *pThis); 
/**
SrvMmsSetMessageReSyncEndIndCB
@brief  The interface of Service Client is use to set CB to listen the status

@param[in]      pfnCallBack             MMS_EVT_MessageReSyncEndInd CB func point
*/
void SrvMmsSetMessageReSyncEndIndCB(SrvMmsMessageReSyncEndInd_CB pfnCallBack);

/**
 SrvMmsIsActive
@brief  The interface of Service Client is used to query if MMS Service is active or not.If active, return TRUE; else return FALSE.

@return TURE                If MMS Service is active.
@return FALSE               If MMS Service is not active. 
*/
boolean SrvMmsIsActive(void);

/**
 SrvMmsQueryMessageStatus
@brief  The interface of Service Client is used to query MMS service status.

@param[in]      nMsgId                      The message id for this request.

@return MMS_MSG_STATUS_QUEUED_FOR_SENDING   The message of specified id is queued for sending.
@return MMS_MSG_STATUS_SENDING              The message of specified id is sending.
@return MMS_MSG_STATUS_QUEUED_FOR_RETRIEVING    The message of specified id is queued for retrieving.
@return MMS_MSG_STATUS_RETRIEVING           The message of specified id is retrieving.
@return MMS_MSG_STATUS_NOT_FOUND            The message of specified id is not in queue.
 */
MMS_Message_Status_e SrvMmsQueryMessageStatus(u16 nMsgId);

/**
 SrvMmsRetrieveMessage
@brief  The interface of Service Client is used toretrieve a message by a specified id.

@param[in]      nMsgId              The message id for this request.

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_BUSY                If service is suspended. 
@return MAE_RET_NOT_READY           If service not ready. 
 */
MAE_Ret SrvMmsRetrieveMessage(u16 nMsgId);

/**
 SrvMmsSendMessage
@brief  The interface of Service Client is used to send a message by a specified id.

@param[in]      nMsgId              The message id for this request.
@param[in]      eDualMode           The SIM module id for this request.

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_NOT_READY           If service not ready. 
 */
MAE_Ret SrvMmsSendMessage(u16 nMsgId, MAE_DualMode_t eDualMode);
#ifdef __MMS_READ_REPORT__
/**
 SrvMmsSendReadReply
@brief  The interface of Service Client is used to send a read reply by a specified id.

@param[in]      nMsgId              The message id for this request.
@param[in]      eDualMode           The SIM module id for this request.

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_NOT_READY           If service not ready. 
 */
MAE_Ret SrvMmsSendReadReply(u16 nMsgId, MAE_DualMode_t eDualMode);
#endif
/**
 SrvMmsIsServiceReady
@brief  The interface of Service Client is used to query if MMS service is ready.If the MMS Service is ready for using then return TRUE else return FALSE.

@return TRUE                If MMS Service is ready for using.
@return FALSE               If MMS Service is not ready for using. 
*/
boolean SrvMmsIsServiceReady(void);

/**
 SrvMmsServiceSuspend
@brief  The interface of Service Client is used to suspend the MMS service for network resource control.

@param[in]      pUsrData                The instance pointer of requestor.
*/
void SrvMmsServiceSuspend(void *pUsrData);

/**
 SrvMmsServiceResume
@brief  The interface of Service Client is used to resume the MMS service for network resource control.

@param[in]      pUsrData                The instance pointer of requestor.
*/
void SrvMmsServiceResume(void *pUsrData);

/**
 SrvMmsIsReloading
@brief  The interface of Service Client is used If the MMS Service is busy reloading messages for each mailbox then return TRUE else return FALSE.

@return TRUE                If MMS Service is busy reloading messages for each mailbox.
@return FALSE               If MMS Service is not reloading messages for each mailbox. 
*/
boolean SrvMmsIsReloading(void);

/**
 SrvMmsIsEditorReady
@brief  The interface of Service Client is used If the MMS Editor is ready to load return return TXT_NULL_ID else return result string ID.
*/
u32 SrvMmsIsEditorReady(void);

MAE_Ret SrvMmsSetStorage(VFS_VOL_TYPE eStorage, boolean bNeedReload);

/**
 SrvMmsSendSDKMessage
@brief  The interface of Service Client is used to send the specified MMS.

@return TRUE                If the specified MMS can saved successfully.
@return FALSE               If the specified MMS can't saved successfully.
*/
MAE_Ret SrvMmsSendSDKMessage(u8 nModuleId, u8* pAppId, u8* pReplyToAppId, MMI_MMS_SendReq_t* pSendReq, pfnMmsSendCnf_t fnSendCnf, u32 nCallerID);

/*-----------------------------------------------------*/

#endif /* __MMI_SRV_MMS_H__ */
